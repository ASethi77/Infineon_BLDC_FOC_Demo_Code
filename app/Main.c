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
** DM           Daniel Mysliwitz                                              **
** BG           Blandine Guillot                                              **
*******************************************************************************/

/*******************************************************************************
**                          Revision Control History                          **
********************************************************************************
** V3.8.7: 2016-11-11, DM:   SVM update                                       **
** V3.8.8: 2018-01-25, DM:   Poti is used to set reference speed              **
** V3.8.9: 2019-02-14, DM:   Poti evaluation removed from interrupt, Poti     **
**                           value is now polled and reference speed is set   **
**                           Added hysteresis for starting/stopping the motor **
** V4.0.0: 2020-04-15, BG:   Updated revision history                         **
** V4.0.1: 2020-07-21, BG:   EP-439: Formatted .h/.c files                    **
*******************************************************************************/

/*******************************************************************************
**                                  Abstract                                  **
********************************************************************************
** BLDC: Motor Drive with Sensorless FOC for the QBL4208-61-04-013 motor      **
********************************************************************************
** Use the Poti to start/stop and speed up the motor.                         **
** When using the example as is, the motor spins in one direction. To make it **
** turn in the other direction, replace 'Emo_setspeedreferenz(mV / 2)' with   **
** 'Emo_setspeedreferenz(-mV / 2) in main.c, line 137.                        **
*******************************************************************************/

#include "tle_device.h"
#include "Emo_RAM.h"

static void Main_lStartMotor(void);
static void Main_lStopMotor(void);
void Poti_Handler(void);

int main(void)
{
  /* Initialization of hardware modules based on Config Wizard configuration */
  TLE_Init();
  Emo_Init();

  for (;;)
  {
    /* Watchdog Service */
    (void)WDT1_Service();
    Poti_Handler();
  }
}


static void Main_lStartMotor(void)
{
  uint32 Error;
  Error = EMO_ERROR_NONE;

  if (Error == EMO_ERROR_NONE)
  {
    Error = Emo_StartMotor((uint32)1u);
  }

  if (Error == EMO_ERROR_NONE)
  {
    __NOP();
  }
  else /* Error */
  {
    __NOP();
  }
}


static void Main_lStopMotor(void)
{
  uint32 Error;
  Error = Emo_StopMotor();

  if (Error != EMO_ERROR_NONE)
  {
    __NOP();
  }
}


/* In case the VCP supply fails the motor stops */
void BDRV_Diag_Supply(void)
{
  Main_lStopMotor();
}

/* iI case an overcurrent is detected on one of the MOSFETs, the motor will be switched off */
void BDRV_Diag(void)
{
  Main_lStopMotor();
}


void Poti_Handler(void)
{
  uint16 mV;

  /* Read the value at Ch4 (Poti) in mV - values between 0 and 5000 are possible */
  if (ADC1_GetChResult_mV(&mV, ADC1_CH4) == true)
  {
    Emo_setspeedreferenz(mV / 2);

    if (mV > 1000)
    {
      Main_lStartMotor();
    }
    else if (mV < 800)
    {
      Main_lStopMotor();
    }
    else
    {
      /* do nothing */
    }
  }
}
