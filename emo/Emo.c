/*
 ***********************************************************************************************************************
 *
 * Copyright (c) 2015, Infineon Technologies AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the
 * following conditions are met:
 *
 *   Redistributions of source code must retain the above copyright notice, this list of conditions and the  following
 *   disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 *   following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 *   Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote
 *   products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT  OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 **********************************************************************************************************************/

/*******************************************************************************
**                             Author(s) Identity                             **
********************************************************************************
** Initials     Name                                                          **
** ---------------------------------------------------------------------------**
** BG           Blandine Guillot                                              **
*******************************************************************************/

/*******************************************************************************
**                          Revision Control History                          **
********************************************************************************
** V1.0.0: 2020-04-15, BG:   Initial version of revision history              **
*******************************************************************************/

#include "Emo_RAM.h"
#include "foc_defines.h"
#include "scu_defines.h"
#include "gpt12e_defines.h"

/*******************************************************************************
**                 Global Constant Definitions to be changed                  **
*******************************************************************************/
/* Constants for MCMOUTS register */
#define CCU6_MASK_MCMOUTS_ENABLE_MCMOUTS  (0x00BFu)
TEmo_Status Emo_Status;
uint16 CSA_Offset;

/** \brief Initializes E-Motor HW and SW.
 *
 * \param None
 * \return Error or EMO_ERROR_NONE
 *
 * \ingroup emo_api
 */
uint32 Emo_Init(void)
{
  if (Emo_Status.MotorState != EMO_MOTOR_STATE_UNINIT)
  {
    /* Error detected: return with error */
    return EMO_ERROR_MOTOR_INIT;
  }

  GPT12E_T2_Start();
  /* Initialize FOC parameters */
  Emo_lInitFocPar();
  /* Initialize motor state */
  Emo_Status.MotorState = EMO_MOTOR_STATE_STOP;
  /* Return without error */
  return EMO_ERROR_NONE;
} /* End of Emo_Init */


/** \brief Sets the reference speed of the motor.
 *
 * \param Reference speed [rpm]
 * \return None
 *
 * \ingroup emo_api
 */
void Emo_SetRefSpeed(sint16 RefSpeed)
{
} /* End of Emo_SetRefSpeed */

/** \brief Gets motor speed.
 *
 * \param None
 * \return None
 *
 * \ingroup emo_api
 */
uint32 Emo_GetSpeed(void)
{
  uint32 Speed;

  /* Get FOC speed */
  if (Emo_Ctrl.ActSpeed >= 0)
  {
    Speed = (uint16)Emo_Ctrl.ActSpeed;
  }
  else
  {
    Speed = (uint16)(-Emo_Ctrl.ActSpeed);
  }

  return Speed;
}

/** \brief Starts the motor.
 *
 * \param None
 * \return Error or EMO_ERROR_NONE
 *
 * \note Service should only be called when motor is stopped.
 *
 * \ingroup emo_api
 */
uint32 Emo_StartMotor(uint32 EnableBridge)
{
  if (Emo_Status.MotorState != EMO_MOTOR_STATE_STOP)
  {
    /* Error detected: return with error */
    return EMO_ERROR_MOTOR_NOT_STOPPED;
  }

  /* Start PWM */
  CCU6_StartTmr_T12();
  /* Disable output pattern */
  CCU6_Multi_Ch_PWM_Shadow_Reg_Load(0x0000);
  /* Enable Shadow Transfer Request for MCMPS */
  CCU6_MCM_PWM_Str_SW_En();
  /* Clear all Error and Warning Flags */
  BDRV_Clr_Sts(0x1F1FFC00);
  /* Enable bridge (after starting PWM according to UM) */
  BDRV_Set_Bridge(Ch_PWM, Ch_PWM, Ch_PWM, Ch_PWM, Ch_PWM, Ch_PWM);
  /* Initialize variables */
  Emo_lInitFocVar();
  /* Set start state */
  Emo_Status.MotorState = EMO_MOTOR_STATE_START;
  /* Return without error */
  return EMO_ERROR_NONE;
} /* End of Emo_StartMotor */


/** \brief Stops the motor.
 *
 * \param None
 * \return Error code
 *
 * \note Service should only be called when motor was started before.
 *
 * \ingroup emo_api
 */
uint32 Emo_StopMotor(void)
{
  if ((Emo_Status.MotorState != EMO_MOTOR_STATE_RUN) &&
      ((Emo_Status.MotorState != EMO_MOTOR_STATE_START) &&
       (Emo_Status.MotorState != EMO_MOTOR_STATE_FAULT)))
  {
    /* Error detected: return with error */
    return EMO_ERROR_MOTOR_NOT_STARTED;
  }

  /* Disable bridge */
  BDRV_Set_Bridge(Ch_Off, Ch_Off, Ch_Off, Ch_Off, Ch_Off, Ch_Off);
  /* Stop PWM */
  CCU6_StopTmr_T12();
  /* Set stop state */
  Emo_Status.MotorState = EMO_MOTOR_STATE_STOP;
  /* Return without error */
  return EMO_ERROR_NONE;
} /* End of Emo_StopMotor */

void Emo_lInitFocPar(void)
{
  /* set to 15V */
  float KU = 15.0;
  float KI;
  /* set to 0.1V/s */
  float KPSIE = 0.1;
  float KUZ;
  static float x;
  float CoAFlux = 200.0;
  float OpGain;
  uint16 i;
  Emo_Status.MotorStartError = 0;
  Emo_Svm.MaxAmp = (uint16)(CCU6_T12PR / EMO_CFG_FOC_TABLE_SCALE);
  /*vectorial voltage limitation, for block limitation algorithm*/
  /*0.9091 * MaxAmp*/
  Emo_Svm.MaxAmp9091pr = (29789 * Emo_Svm.MaxAmp) >> MAT_FIX_SHIFT;
  /*0.4164 * MaxAmp*/
  Emo_Svm.MaxAmp4164pr = (13643 * Emo_Svm.MaxAmp) >> MAT_FIX_SHIFT;
  Emo_Svm.MaxAmpQuadrat = (uint32)Emo_Svm.MaxAmp * Emo_Svm.MaxAmp;
  Emo_Svm.Kfact256 = 8388608 / Emo_Svm.MaxAmp; //2 exp23/MaxAmp
  OpGain = 10.0;
  CSA_Set_Gain(0u);
  /* 1.25 => 125mV, secured OpAmp differential input voltage range */
  x = Emo_Focpar_Cfg.NominalCurrent * Emo_Focpar_Cfg.Rshunt * 10.0;

  if (x < 1.25)
  {
    OpGain = 10.0;
    CSA_Set_Gain(0u);
  }

  x = Emo_Focpar_Cfg.NominalCurrent * Emo_Focpar_Cfg.Rshunt * 20.0;

  if (x < 1.25)
  {
    OpGain = 20.0;
    CSA_Set_Gain(1u);
  }

  x = Emo_Focpar_Cfg.NominalCurrent * Emo_Focpar_Cfg.Rshunt * 40.0;

  if (x < 1.25)
  {
    OpGain = 40.0;
    CSA_Set_Gain(2u);
  }

  x = Emo_Focpar_Cfg.NominalCurrent * Emo_Focpar_Cfg.Rshunt * 60.0;

  if (x < 1.25)
  {
    OpGain = 60.0;
    CSA_Set_Gain(3u);
  }

  /* KI current regulator parameter          **
  ** 5.0 => 5V ADC referenc voltage          */
  KI = 5.0 * 2.0 / (Emo_Focpar_Cfg.Rshunt * OpGain);
  /* KUZ Battery Voltage parameter */
  KUZ = 32768.0 * 12.0 / 1612.0; /* 12V = 1612Ink ADW */
  /* Measuring the CSA Offset */
  CSA->CTRL.bit.VZERO = 0;
  ADC1_SetMode(SW_MODE);

  while (ADC1_Busy() == true) {}

  ADC1_SetSocSwMode(ADC1_CH1);

  while (ADC1_GetEocSwMode() == false) {}

  while (ADC1->RES_OUT1.bit.VF1 == 0) {}

  CSA_Offset = ADC1->RES_OUT1.bit.OUT_CH1;
  ADC1_SetMode(SEQ_MODE);

  while (ADC1_Busy() == false) {}

  i = CSA_Offset;

  if (i > 1800)
  {
    i = 1800;
    Emo_Status.MotorStartError = Emo_Status.MotorStartError | EMO_ERROR_CSAOFFSET;
  }

  if (i < 1500)
  {
    i = 1500;
    Emo_Status.MotorStartError = Emo_Status.MotorStartError | EMO_ERROR_CSAOFFSET;
  }

  Emo_Svm.CsaOffset = i;
  /* Initialize parameters for FOC */
  x = 32768.0 * KI * Emo_Focpar_Cfg.PhaseRes / KU;

  if (x > 32767.0)
  {
    x = 32767.0;
  }

  Emo_Foc.PhaseRes = (uint16)x;
  x = 32768.0 * KI * Emo_Focpar_Cfg.PhaseInd / KPSIE;

  if (x > 32767.0)
  {
    x = 32767.0;
  }

  Emo_Foc.PhaseInd = (uint16)x;
  Emo_Foc.Kdcdivident1 = (uint32)(KU * 1.7320508 * Emo_Svm.MaxAmp / KUZ * 32768 / 2.0);
  Emo_Foc.Kdcfactor2 = (uint16)(KUZ * 32768.0 * 32768.0 / (KU * 1.7320508 * Emo_Svm.MaxAmp * 64));
  Emo_Foc.Kdcfactoriqc = (uint16)(32768.0 * KUZ / (1.7320508 * KU * 32.0));
  Emo_Foc.PolePair = (uint16)Emo_Focpar_Cfg.PolePair;
  x = Emo_Focpar_Cfg.StartCurrent / KI * 32768.0;

  if (x > 32767)
  {
    x = 32767;
    Emo_Status.MotorStartError = Emo_Status.MotorStartError | EMO_ERROR_STARTCURRENT;
  }

  if (x < 1)
  {
    x = 1;
    Emo_Status.MotorStartError = Emo_Status.MotorStartError | EMO_ERROR_STARTCURRENT;
  }

  Emo_Foc.StartCurrent = (sint16)x;
  x = Emo_Focpar_Cfg.TimeSpeedzero * SCU_FSYS / ((GPT12E_T2) * 4.0);

  if (x > 32767)
  {
    x = 32767;
    Emo_Status.MotorStartError = Emo_Status.MotorStartError | EMO_ERROR_STARTTIME;
  }

  if (x < 1)
  {
    x = 1;
    Emo_Status.MotorStartError = Emo_Status.MotorStartError | EMO_ERROR_STARTTIME;
  }

  Emo_Foc.TimeSpeedzero = (uint16)x;
  Emo_Foc.StartEndSpeed = (sint16)Emo_Focpar_Cfg.StartSpeedEnd;
  x = ((GPT12E_T2) * 4.0) / SCU_FSYS * Emo_Focpar_Cfg.StartSpeedSlewRate * 65536.0;

  if (x > 2147483647)
  {
    x = 2147483647;
    Emo_Status.MotorStartError = Emo_Status.MotorStartError | EMO_ERROR_SPEEDSLEWRATE;
  }

  if (x < 1)
  {
    x = 1;
    Emo_Status.MotorStartError = Emo_Status.MotorStartError | EMO_ERROR_SPEEDSLEWRATE;
  }

  Emo_Foc.StartSpeedSlewRate = (sint32)x;
  Emo_Foc.SpeedtoFrequency = (sint16)((32768.0 * (1.0 / CCU6_T12_FREQ) * 32768.0 / 30.0) * FOC_POLE_PAIRS);
  CoAFlux = 32768.0 * KU / (KPSIE * CCU6_T12_FREQ);
  Emo_Foc.RealFluxLp.CoefA = (sint16)CoAFlux;
  Emo_Foc.ImagFluxLp.CoefA = (sint16)CoAFlux;
  Emo_Foc.LpCoefb1 = (uint16)(32768.0 / (Emo_Focpar_Cfg.TimeConstantEstFluxFilter * CCU6_T12_FREQ)); //Time const = 0.10s
  Emo_Foc.LpCoefb2 = (uint16)(32768.0 / (0.01 * CCU6_T12_FREQ)); //Time const = 0.010s
  Emo_Foc.RealFluxLp.CoefB = Emo_Foc.LpCoefb1;
  Emo_Foc.ImagFluxLp.CoefB = Emo_Foc.LpCoefb1;
  Emo_Ctrl.SpeedPi.Kp = Emo_Focpar_Cfg.SpeedPi_Kp;
  Emo_Ctrl.SpeedPi.Ki = Emo_Focpar_Cfg.SpeedPi_Ki;
  Emo_Ctrl.SpeedPi.PiMin = (sint16)(32767.0 * Emo_Focpar_Cfg.MinRefStartCurr / KI);
  Emo_Ctrl.SpeedPi.PiMax = (sint16)(32767.0 * Emo_Focpar_Cfg.MaxRefStartCurr / KI);
  x = 32767.0 * Emo_Focpar_Cfg.MaxRefCurr / KI;

  if (x > 32767)
  {
    x = 32767;
    Emo_Status.MotorStartError = Emo_Status.MotorStartError | EMO_ERROR_REFCURRENT;
  }

  Emo_Ctrl.MaxRefCurrent = (sint16)x;
  x = 32767.0 * Emo_Focpar_Cfg.MinRefCurr / KI;

  if (x < -32767)
  {
    x = -32767;
    Emo_Status.MotorStartError = Emo_Status.MotorStartError | EMO_ERROR_REFCURRENT;
  }

  Emo_Ctrl.MinRefCurrent = (sint16)x;
  x = 32767.0 * Emo_Focpar_Cfg.MaxRefStartCurr / KI;

  if (x > 32767)
  {
    x = 32767;
    Emo_Status.MotorStartError = Emo_Status.MotorStartError | EMO_ERROR_REFCURRENT;
  }

  Emo_Ctrl.MaxRefStartCurrent = (sint16)x;
  x = 32767.0 * Emo_Focpar_Cfg.MinRefStartCurr / KI;

  if (x < -32767)
  {
    x = -32767;
    Emo_Status.MotorStartError = Emo_Status.MotorStartError | EMO_ERROR_REFCURRENT;
  }

  Emo_Ctrl.MinRefStartCurrent = (sint16)x;
  Emo_Ctrl.Speedlevelmaxstart = (sint16)Emo_Focpar_Cfg.SpeedLevelPos;
  Emo_Ctrl.Speedlevelminstart = (sint16)Emo_Focpar_Cfg.SpeedLevelNeg;
  Emo_Ctrl.SpeedLevelSwitchOn = (sint16)Emo_Focpar_Cfg.SpeedLevelSwitchOn;

  if (Emo_Ctrl.Speedlevelmaxstart < Emo_Ctrl.Speedlevelminstart)
  {
    Emo_Status.MotorStartError = Emo_Status.MotorStartError | EMO_ERROR_SPEED_POINTS;
  }

  if (Emo_Ctrl.Speedlevelmaxstart < Emo_Ctrl.SpeedLevelSwitchOn)
  {
    Emo_Status.MotorStartError = Emo_Status.MotorStartError | EMO_ERROR_SPEED_POINTS;
  }

  if ((Emo_Ctrl.Speedlevelminstart + Emo_Ctrl.SpeedLevelSwitchOn) > 0)
  {
    Emo_Status.MotorStartError = Emo_Status.MotorStartError | EMO_ERROR_SPEED_POINTS;
  }

  if (Emo_Foc.StartEndSpeed < Emo_Ctrl.SpeedLevelSwitchOn)
  {
    Emo_Status.MotorStartError = Emo_Status.MotorStartError | EMO_ERROR_SPEED_POINTS;
  }

  if (Emo_Ctrl.MaxRefCurrent < Emo_Ctrl.MaxRefStartCurrent)
  {
    Emo_Status.MotorStartError = Emo_Status.MotorStartError | EMO_ERROR_LIMITS_REFCURRENT;
  }

  if (Emo_Ctrl.MinRefCurrent > Emo_Ctrl.MinRefStartCurrent)
  {
    Emo_Status.MotorStartError = Emo_Status.MotorStartError | EMO_ERROR_LIMITS_REFCURRENT;
  }

  x = Emo_Focpar_Cfg.AdjustmCurrentControl;

  if ((x > 1) || (x < 0.01))
  {
    Emo_Status.MotorStartError = Emo_Status.MotorStartError | EMO_ERROR_VALUE_CU_ADCC;
  }

  x = Emo_Focpar_Cfg.AdjustmCurrentControl * KI * Emo_Focpar_Cfg.PhaseInd / (256.0 * (1.0 / CCU6_T12_FREQ) * KU) * 32767.0;

  if (x > 32767)
  {
    x = 32767;
    Emo_Status.MotorStartError = Emo_Status.MotorStartError | EMO_ERROR_VALUE_CU_KP;
  }

  if (x < 1)
  {
    x = 1;
    Emo_Status.MotorStartError = Emo_Status.MotorStartError | EMO_ERROR_VALUE_CU_KP;
  }

  Emo_Ctrl.RealCurrPi.Kp = (sint16)x;
  x = Emo_Focpar_Cfg.AdjustmCurrentControl * KI * Emo_Focpar_Cfg.PhaseRes / (4.0 * KU) * 32767.0;

  if (x > 32767)
  {
    x = 32767;
    Emo_Status.MotorStartError = Emo_Status.MotorStartError | EMO_ERROR_VALUE_CU_KI;
  }

  if (x < 1)
  {
    x = 1;
    Emo_Status.MotorStartError = Emo_Status.MotorStartError | EMO_ERROR_VALUE_CU_KI;
  }

  Emo_Ctrl.RealCurrPi.Ki = (sint16)x;
  /* id = PI regulator limits */
  Emo_Ctrl.RealCurrPi.IMin = -28272;
  Emo_Ctrl.RealCurrPi.IMax = 28272;
  Emo_Ctrl.RealCurrPi.PiMin = -28272;
  Emo_Ctrl.RealCurrPi.PiMax = 28272;
  Emo_Ctrl.ImagCurrPi.Kp =  Emo_Ctrl.RealCurrPi.Kp;
  Emo_Ctrl.ImagCurrPi.Ki =  Emo_Ctrl.RealCurrPi.Ki;
  /* iq = PI regulator limits, iq needs higher range than id */
  Emo_Ctrl.ImagCurrPi.IMin = -16580;
  Emo_Ctrl.ImagCurrPi.IMax = 16580;
  Emo_Ctrl.ImagCurrPi.PiMin = -16580;
  Emo_Ctrl.ImagCurrPi.PiMax = 16580;
  x = (1.0 / CCU6_T12_FREQ) / (Emo_Focpar_Cfg.TimeConstantSpeedFilter) * 32768.0;

  if (x > 32767)
  {
    x = 32767;
    Emo_Status.MotorStartError = Emo_Status.MotorStartError | EMO_ERROR_T_SPEED_LP;
  }

  if (x < 1)
  {
    x = 1;
    Emo_Status.MotorStartError = Emo_Status.MotorStartError | EMO_ERROR_T_SPEED_LP;
  }

  Emo_Ctrl.RotCurrImagLpdisplay.CoefA = 10;
  Emo_Ctrl.RotCurrImagLpdisplay.CoefB = 10;
  Emo_Ctrl.SpeedLp.CoefA = (sint16)x;
  Emo_Ctrl.SpeedLp.CoefB = (sint16)x;
  Emo_Ctrl.FluxbtrLp.CoefA = 1000;
  Emo_Ctrl.FluxbtrLp.CoefB = 1000;
  Emo_Ctrl.SpeedLpdisplay.CoefA = 1000;
  Emo_Ctrl.SpeedLpdisplay.CoefB = 1000;
  Emo_Ctrl.Pllkp = 100;
  x = 60.0 * Emo_Focpar_Cfg.PWM_Frequency / 64.0;

  if (x > 32767.0)
  {
    x = 32767;
  }

  Emo_Ctrl.Factorspeed = (uint16)x;
  /* Speed PLL adjustment based on max. mech. speed             **
  ** 60.0 => conversion frequency into rpm (seconds to minutes) **
  ** 4.0 => 1/4 electrical rotation => 90°                      */
  x = 60.0 * Emo_Focpar_Cfg.PWM_Frequency / (Emo_Focpar_Cfg.MaxSpeed * Emo_Focpar_Cfg.PolePair * 4.0);

  if (x >= 32.0)
  {
    Emo_Ctrl.Exppllhigh = 5;
    Emo_Ctrl.Anglersptr = 32;
    Emo_Ctrl.Expspeedhigh = 0;
  }
  else
  {
    if (x >= 16.0)
    {
      Emo_Ctrl.Exppllhigh = 4;
      Emo_Ctrl.Anglersptr = 16;
      Emo_Ctrl.Expspeedhigh = 1;
    }
    else
    {
      if (x >= 8.0)
      {
        Emo_Ctrl.Exppllhigh = 3;
        Emo_Ctrl.Anglersptr = 8;
        Emo_Ctrl.Expspeedhigh = 2;
      }
      else
      {
        if (x >= 4.0)
        {
          Emo_Ctrl.Exppllhigh = 2;
          Emo_Ctrl.Anglersptr = 4;
          Emo_Ctrl.Expspeedhigh = 3;
        }
        else
        {
          Emo_Ctrl.Exppllhigh = 1;
          Emo_Ctrl.Anglersptr = 2;
          Emo_Ctrl.Expspeedhigh = 4;
        }
      }
    }
  }
} /* End of Emo_lInitFocPar */

void Emo_lInitFocVar(void)
{
  uint16 i;
  /* Initialize variables for SVM */
  Emo_Svm.Angle = 0u;
  Emo_Svm.Amp = 0u;
  Emo_Svm.Sector = 0u;
  Emo_Svm.T1 = 0u;
  Emo_Svm.T2 = 0u;
  Emo_Svm.PhaseCurr.A = 0;
  Emo_Svm.PhaseCurr.B = 0;
  Emo_Svm.comp60up = 0;
  Emo_Svm.comp61up = 0;
  Emo_Svm.comp62up = 0;
  Emo_Svm.comp60up = 0;
  Emo_Svm.comp61down = 0;
  Emo_Svm.comp62down = 0;
  /* Initialize variables for FOC */
  Emo_Foc.StatCurr.Real = 0;
  Emo_Foc.StatCurr.Imag = 0;
  Emo_Foc.RotCurr.Real = 0;
  Emo_Foc.RotCurr.Imag = 0;
  Emo_Foc.StatVolt.Real = 0;
  Emo_Foc.StatVolt.Imag = 0;
  Emo_Foc.RotVolt.Real = 0;
  Emo_Foc.RotVolt.Imag = 0;
  Emo_Foc.Angle = 0u;
  Emo_Foc.FluxAngle = 0u;
  Emo_Foc.StoredAngle = 0u;
  Emo_Foc.RealFluxLp.Out = 0;
  Emo_Foc.ImagFluxLp.Out = 0;
  Emo_Ctrl.ActSpeed = 0;
  Emo_Ctrl.RefCurr = 0;
  Emo_Ctrl.RealCurrPi.IOut = 0;
  Emo_Ctrl.ImagCurrPi.IOut = 0;
  Emo_Ctrl.SpeedLp.Out = 0;
  Emo_Foc.StartSpeedSlopeMem = 0;
  Emo_Foc.CountStart = Emo_Foc.TimeSpeedzero;
  /* define 30° as start angle */
  Emo_Foc.StartAngle = (uint16)(30.0 / 360.0 * 65536.0);

  for (i = 0; i < 31; i++)
  {
    Emo_Ctrl.AngleBuffer[i] = 0;
  }

  Emo_Ctrl.SpeedLpdisplay.Out = 0;
  Emo_Ctrl.SpeedLp.Out = 0;
  Emo_Svm.CounterOffsetAdw = 0;
  Emo_Svm.CsaOffsetAdwSumme = 0;
} /* End of Emo_lInitFocVar */


/** \brief Handles T2 overflow.
 *
 * \param None
 * \return None
 *
 * \ingroup emo_api
 */
void Emo_HandleT2Overflow(void)
{
  if (Emo_Status.MotorState == EMO_MOTOR_STATE_START)
  {
    /* Open loop: */
    /* Perform ramp to start end speed */
    if (Emo_Foc.CountStart == 0)
    {
      /* I/F Start-up */
      if (Emo_Ctrl.RefSpeed > 0)
      {
        /* positive rotation */
        /* apply start up ramp */
        Emo_Foc.StartSpeedSlope = Mat_Ramp(Emo_Foc.StartEndSpeed, Emo_Foc.StartSpeedSlewRate, &Emo_Foc.StartSpeedSlopeMem);
        /* calculate frequency out of ramp */
        Emo_Foc.StartFrequencySlope = __SSAT(Mat_FixMulScale(Emo_Foc.StartSpeedSlope, Emo_Foc.SpeedtoFrequency, 0), MAT_FIX_SAT);

        if (Emo_Foc.StartSpeedSlope == Emo_Foc.StartEndSpeed)
        {
          /* end speed reached */
#if (EMO_RUN==1)
          Emo_Status.MotorState = EMO_MOTOR_STATE_RUN;                       /*Start Foc */
#endif
          /* preload speed regulator */
          Emo_Ctrl.SpeedPi.IOut = Emo_Ctrl.RefCurr << 14;
        }
      }
      else
      {
        /* negative rotation */
        /* apply start up ramp */
        Emo_Foc.StartSpeedSlope = Mat_Ramp(-Emo_Foc.StartEndSpeed, Emo_Foc.StartSpeedSlewRate, &Emo_Foc.StartSpeedSlopeMem);
        /* calculate frequency out of ramp */
        Emo_Foc.StartFrequencySlope = __SSAT(Mat_FixMulScale(Emo_Foc.StartSpeedSlope, Emo_Foc.SpeedtoFrequency, 0), MAT_FIX_SAT);

        if (Emo_Foc.StartSpeedSlope == -Emo_Foc.StartEndSpeed)
        {
#if (EMO_RUN==1)
          Emo_Status.MotorState = EMO_MOTOR_STATE_RUN;                       /*Start Foc */
#endif
          Emo_Ctrl.SpeedPi.IOut = Emo_Ctrl.RefCurr << 14;
        }
      }
    }
    else
    {
      if (Emo_Focpar_Cfg.EnableFrZero == 1)
      {
        Emo_Foc.CountStart--;
      }
      else
      {
        Emo_Foc.CountStart = 0;    /*Starttime for (Frequenz=0)  =0  */
      }

      Emo_Foc.StartFrequencySlope = 0;
    }

    Emo_Ctrl.ActSpeeddisplay = Mat_ExeLp_without_min_max(&Emo_Ctrl.SpeedLpdisplay, Emo_Ctrl.ActSpeed);
    Emo_Ctrl.EnableStartVoltage = 1;
  }
  else if (Emo_Status.MotorState == EMO_MOTOR_STATE_RUN)
  {
    /* switch speed regulator current limits based on speed */
    if (Emo_Ctrl.ActSpeed > Emo_Ctrl.Speedlevelmaxstart)
    {
      Emo_Ctrl.SpeedPi.PiMax = Emo_Ctrl.MaxRefCurrent;
      Emo_Ctrl.SpeedPi.IMax = Emo_Ctrl.MaxRefCurrent;
    }
    else
    {
      if (Emo_Ctrl.ActSpeed < Emo_Ctrl.Speedlevelminstart)
      {
        Emo_Ctrl.SpeedPi.PiMin = Emo_Ctrl.MinRefCurrent;
        Emo_Ctrl.SpeedPi.IMin = Emo_Ctrl.MinRefCurrent;
      }
      else
      {
        Emo_Ctrl.SpeedPi.PiMax = Emo_Ctrl.MaxRefStartCurrent;
        Emo_Ctrl.SpeedPi.IMax = Emo_Ctrl.MaxRefStartCurrent;
        Emo_Ctrl.SpeedPi.PiMin = Emo_Ctrl.MinRefStartCurrent;
        Emo_Ctrl.SpeedPi.IMin = Emo_Ctrl.MinRefStartCurrent;
      }
    }

    /* Speed Regulator: Execute PI algorithm for (imaginary) reference current */
    Emo_Ctrl.RefCurr = Mat_ExePi(&Emo_Ctrl.SpeedPi, Emo_Ctrl.RefSpeed - Emo_Ctrl.ActSpeed);
    /* Actual Speed Filter */
    Emo_Ctrl.ActSpeeddisplay = Mat_ExeLp_without_min_max(&Emo_Ctrl.SpeedLpdisplay, Emo_Ctrl.ActSpeed);
  }
  else
  {
    Emo_StopMotor();
  }

  if (Emo_Status.MotorState == EMO_MOTOR_STATE_STOP)
  {
    Emo_Ctrl.ActSpeed = Mat_ExeLp_without_min_max(&Emo_Ctrl.SpeedLp, 0);
    Emo_Ctrl.ActSpeeddisplay = Mat_ExeLp_without_min_max(&Emo_Ctrl.SpeedLpdisplay, Emo_Ctrl.ActSpeed);
  }

  /* read DC-Link-Voltage */
  Emo_Foc.DcLinkVoltage = ADC1->RES_OUT6.reg;
  Emo_Foc.Dcfactor1 = Emo_Foc.Kdcdivident1 / Emo_Foc.DcLinkVoltage;
  Emo_Foc.Dcfactor2 = __SSAT(Mat_FixMulScale(Emo_Foc.DcLinkVoltage, Emo_Foc.Kdcfactor2, 3), MAT_FIX_SAT);
  Emo_Ctrl.ImagCurrPi.IMax = __SSAT(Mat_FixMulScale(Emo_Foc.DcLinkVoltage, Emo_Foc.Kdcfactoriqc, 5), MAT_FIX_SAT);
  Emo_Ctrl.ImagCurrPi.PiMax = Emo_Ctrl.ImagCurrPi.IMax;
  Emo_Ctrl.ImagCurrPi.IMin = -Emo_Ctrl.ImagCurrPi.IMax;
  Emo_Ctrl.ImagCurrPi.PiMin = Emo_Ctrl.ImagCurrPi.IMin;

  if (Emo_Ctrl.EnableStartVoltage == 1)
  {
    /* correct Start Voltage based on currently measured DC-Link voltage */
    Emo_Foc.StartVoltAmpDivUz = __SSAT(Mat_FixMulScale(Emo_Foc.StartVoltAmp, Emo_Foc.Dcfactor1, 1), MAT_FIX_SAT);
  }

  Emo_Ctrl.SpeedPi.IMin = Emo_Ctrl.SpeedPi.PiMin;
  Emo_Ctrl.SpeedPi.IMax = Emo_Ctrl.SpeedPi.PiMax;

  if (Emo_Svm.Amp < Emo_Svm.MaxAmp9091pr)
  {
    Emo_Foc.RealFluxLp.CoefB = Emo_Foc.LpCoefb1;
    Emo_Foc.ImagFluxLp.CoefB = Emo_Foc.LpCoefb1;
  }
  else
  {
    Emo_Foc.RealFluxLp.CoefB = Emo_Foc.LpCoefb2;
    Emo_Foc.ImagFluxLp.CoefB = Emo_Foc.LpCoefb2;
  }
} /* End of Emo_HandleT2Overflow */

void GPT1_T2_Handler(void)
{
  /* T2 overflow: */
  /* Set T2 to reload value */
  GPT12E->T2.reg += GPT12E_T2_TICK;
  /* Handle T2 overflow */
  Emo_HandleT2Overflow();
} /* End of GPT1_IRQHandler */


