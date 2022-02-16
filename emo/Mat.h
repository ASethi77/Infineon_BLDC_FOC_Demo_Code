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

#ifndef MAT_H
#define MAT_H

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "Emo.h"
#include "Table.h"

/*******************************************************************************
**                          Global Macro Definitions                          **
*******************************************************************************/
/* Function-like macro to multiply two fixed-point factors to get a standard fixed-point product */
#define Mat_FixMul(Factor1, Factor2) ((((sint32)(Factor1)) * ((sint32)(Factor2))) >> MAT_FIX_SHIFT)

/* Function-like macro to multiply two fixed-point factors to get a fixed-point product with scaling
 * e.g. scale = 1: shift result left by Scale */
#define Mat_FixMulScale(Factor1, Factor2, Scale) ((((sint32)(Factor1)) * ((sint32)(Factor2))) >> ((uint32)((sint32)MAT_FIX_SHIFT - (Scale))))

/* Shift value for fixed-point format */
#define MAT_FIX_SHIFT (15u)

/* Saturation bit for fixed-point format */
#define MAT_FIX_SAT (16u)

/* (1 / sqrt(3)) in fixed-point format */
#define MAT_ONE_OVER_SQRT_3 (18919u)

/*******************************************************************************
**                           Global Type Definitions                          **
*******************************************************************************/
/** \brief PI status */
typedef struct
{
  sint32 IOut;     /**< \brief I output */
  sint16 Kp;       /**< \brief Proportional parameter */
  sint16 Ki;       /**< \brief Integral parameter */
  sint16 IMin;     /**< \brief Minimum for I output */
  sint16 IMax;     /**< \brief Maximum for I output */
  sint16 PiMin;    /**< \brief Minimum for PI output */
  sint16 PiMax;    /**< \brief Maximum for PI output */
} TMat_Pi;

typedef struct
{
  sint32 IOut;     /**< \brief I output */
  sint16 Dout;     /**< \briwf deltaout */
  sint16 Kp;       /**< \brief Proportional parameter */
  sint16 Ki;       /**< \brief Integral parameter */
  sint16 Ks;       /**< \breif Return parameter to Integral */
  sint16 IMin;     /**< \brief Minimum for I output */
  sint16 IMax;     /**< \brief Maximum for I output */
  sint16 PiMin;    /**< \brief Minimum for PI output */
  sint16 PiMax;    /**< \brief Maximum for PI output */
} TMat_Pi_Windup;

/** \brief low pass status */
typedef struct
{
  sint16 CoefA;    /**< \brief Coefficient A */
  sint16 CoefB;    /**< \brief Coefficient B */
  sint16 Min;      /**< \brief Minimum */
  sint16 Max;      /**< \brief Maximum */
  sint32 Out;      /**< \brief Low pass output */
} TMat_Lp;

/** \brief low pass status */
typedef struct
{
  sint16 CoefA;    /**< \brief Coefficient A */
  sint16 CoefB;    /**< \brief Coefficient B */
  sint32 Out;      /**< \brief Low pass output */
} TMat_Lp_Simple;


/*******************************************************************************
**                        Global Function Declarations                        **
*******************************************************************************/

/* Inline functions ***********************************************************/
__STATIC_INLINE sint16 Mat_ExePi(TMat_Pi *pPi, sint16 Error);
__STATIC_INLINE sint16 Mat_ExePi_Windup(TMat_Pi_Windup *pPi, sint16 Error);
__STATIC_INLINE TComplex Mat_Clarke(TPhaseCurr PhaseCurr);
__STATIC_INLINE TComplex Mat_Park(TComplex StatCurr, uint16 Angle);
__STATIC_INLINE TComplex Mat_InvPark(TComplex RotVolt, uint16 Angle);
__STATIC_INLINE TComplex Mat_PolarKartesisch(uint16 Amp, uint16 Angle);
__STATIC_INLINE sint16 Mat_ExeLp(TMat_Lp *pLp, sint16 Input);
__STATIC_INLINE sint16 Mat_ExeLp_without_min_max(TMat_Lp_Simple *pLp, sint16 Input);
__STATIC_INLINE uint16 Mat_CalcAngleAmp(TComplex Stat, uint16 *pAmp);
__STATIC_INLINE uint16 Mat_CalcAngle(TComplex Stat);
__STATIC_INLINE uint16 Mat_CalcAmp(TComplex Stat);
__STATIC_INLINE sint16 Mat_Ramp(sint16 Input, sint32 Slewrate, sint32 *Output);

/*******************************************************************************
**                     Global Inline Function Definitions                     **
*******************************************************************************/
/** \brief Performs PI control algorithm.
 *
 * \param[inout] pPi Pointer to PI status
 * \param[in] Error Difference between reference and actual value
 *
 * \return PI output
 * \ingroup math_api
 */
__STATIC_INLINE sint16 Mat_ExePi(TMat_Pi *pPi, sint16 Error)
{
  sint32 IOut;
  sint32 PiOut;
  sint32 Min;
  sint32 Max;
  sint32 Temp;
  /* I output = old output + error * I parameter */
  IOut = pPi->IOut + ((sint32)Error * (sint32)pPi->Ki);
  /* Limit I output */
  Min = ((sint32)(pPi->IMin)) << 15u;

  if (IOut < Min)
  {
    IOut = Min;
  }
  else
  {
    Max = ((sint32)(pPi->IMax)) << 15u;

    if (IOut > Max)
    {
      IOut = Max;
    }
  }

  /* Store I output */
  pPi->IOut = IOut;
  /* PI output = upper half of (I output + saturate(error * P parameter) * 64) */
  Temp = __SSAT(Error * ((sint32)pPi->Kp), 31u - 6u);
  PiOut = (IOut + (Temp << 6u)) >> 15u;
  /* Limit PI output */
  Min = (sint32)(pPi->PiMin);

  if (PiOut < Min)
  {
    PiOut = Min;
  }
  else
  {
    Max = (sint32)(pPi->PiMax);

    if (PiOut > Max)
    {
      PiOut = Max;
    }
  }

  return (sint16)PiOut;
} /* End of Mat_ExePi_Windup */

/** \brief Performs PI control algorithm.
 *
 * \param[inout] pPi Pointer to PI status
 * \param[in] Error Difference between reference and actual value
 *
 * \return PI output
 * \ingroup math_api
 */
__STATIC_INLINE sint16 Mat_ExePi_Windup(TMat_Pi_Windup *pPi, sint16 Error)
{
  sint32 IOut;
  sint32 PiOut;
  sint32 Min;
  sint32 Max;
  sint32 Temp;
  /* I output = old output + error * I parameter */
  IOut = pPi->IOut + ((sint32)Error * (sint32)pPi->Ki) - ((sint32)pPi->Dout * (sint32)pPi->Ks);
  /* Limit I output */
  Min = ((sint32)(pPi->IMin)) << 15u;

  if (IOut < Min)
  {
    IOut = Min;
  }
  else
  {
    Max = ((sint32)(pPi->IMax)) << 15u;

    if (IOut > Max)
    {
      IOut = Max;
    }
  }

  /* Store I output */
  pPi->IOut = IOut;
  /* PI output = upper half of (I output + saturate(error * P parameter) * 64) */
  Temp = __SSAT(Error * ((sint32)pPi->Kp), 31u - 6u);
  PiOut = (IOut + (Temp << 6u)) >> 15u;
  pPi->Dout = PiOut;
  /* Limit PI output */
  Min = (sint32)(pPi->PiMin);

  if (PiOut < Min)
  {
    PiOut = Min;
  }
  else
  {
    Max = (sint32)(pPi->PiMax);

    if (PiOut > Max)
    {
      PiOut = Max;
    }
  }

  pPi->Dout = pPi->Dout - PiOut;
  return (sint16)PiOut;
} /* End of Mat_ExePi_Windup */


/** \brief Performs low-pass filter algorithm.
 *
 * \param[inout] pLp Pointer to low-pass filter status
 * \param[in] Input Input in fixed-point format
 *
 * \return Low-pass filter output in fixed-point format
 * \ingroup math_api
 */
__STATIC_INLINE sint16 Mat_ExeLp(TMat_Lp *pLp, sint16 Input)
{
  sint32 Out;
  sint32 Min;
  sint32 Max;
  /* New output = saturate(old output + coefficient A * input - coefficient B * old output/2^15 */
  Out = pLp->Out;
  Out = __SSAT((Out + ((sint32)pLp->CoefA * (sint32)Input)) - ((sint32)pLp->CoefB * (Out >> 15u)), 31u);
  /* Limit new output */
  Min = ((sint32)(pLp->Min)) << 15u;

  if (Out < Min)
  {
    Out = Min;
  }
  else
  {
    Max = ((sint32)(pLp->Max)) << 15u;

    if (Out > Max)
    {
      Out = Max;
    }
  }

  /* Store new output */
  pLp->Out = Out;
  /* return upper part */
  return (sint16)(Out >> 15u);
} /* End of Mat_ExeLp */


/** \brief Performs low-pass filter algorithm.
 *
 * \param[inout] pLp Pointer to low-pass filter status
 * \param[in] Input Input in fixed-point format
 *
 * \return Low-pass filter output in fixed-point format without min and max
 * \ingroup math_api
 */
__STATIC_INLINE sint16 Mat_ExeLp_without_min_max(TMat_Lp_Simple *pLp, sint16 Input)
{
  sint32 Out;
  /* New output = saturate(old output + coefficient A * input - coefficient B * old output/2^15 */
  Out = pLp->Out;
  Out = __SSAT((Out + ((sint32)pLp->CoefA * (sint32)Input)) - ((sint32)pLp->CoefB * (Out >> 15u)), 31u);
  /* Store new output */
  pLp->Out = Out;
  /* return upper part */
  return (sint16)(Out >> 15u);
} /* End of Mat_ExeLp */

/** \brief Performs the Clarke transformation.
 *
 * \param[in] PhaseCurr 3-phase current structure
 * \return 2-phase stationary current structure
 *
 * \ingroup math_api
 */
__STATIC_INLINE TComplex Mat_Clarke(TPhaseCurr PhaseCurr)
{
  TComplex StatCurr = {0, 0};
  /* Real current = saturate(4 * Ia) */
  StatCurr.Real = __SSAT(4 * PhaseCurr.A, MAT_FIX_SAT);
  /* Imag. current = saturate(1 / sqrt(3)) * 4 * (Ia + 2 * Ib) */
  StatCurr.Imag = (sint16)__SSAT(Mat_FixMulScale(MAT_ONE_OVER_SQRT_3, ((sint32)PhaseCurr.A) + (2 * ((sint32)PhaseCurr.B)), 2), MAT_FIX_SAT);
  return StatCurr;
} /* End of Mat_Clarke */


/** \brief Performs the Park transformation.
 *
 * \param[in] StatCurr Stationary 2-phase current structure
 * \param[in] Angle Angle [0..65535 = 0..2Pi]
 * \return Rotating 2-phase current structure
 *
 * \ingroup math_api
 */
__STATIC_INLINE TComplex Mat_Park(TComplex StatCurr, uint16 Angle)
{
  TComplex RotCurrent = {0, 0};
  sint32 Cos;
  sint32 Sin;
  uint32 UAngle;
  /* Take upper 10 bits of 16-bit angle */
  UAngle = Angle >> 6u;
  /* Get angle functions */
  Cos = pTable_Cos[UAngle];
  Sin = Table_Sin[UAngle];
  /* Real output = saturate(real input * cos + imag. input * sin) */
  RotCurrent.Real = (sint16)__SSAT(Mat_FixMul(StatCurr.Real, Cos) + Mat_FixMul(StatCurr.Imag, Sin), MAT_FIX_SAT);
  /* Imag. output = saturate(imag. input * cos - real input * sin) */
  RotCurrent.Imag = (sint16)__SSAT(Mat_FixMul(StatCurr.Imag, Cos) - Mat_FixMul(StatCurr.Real, Sin), MAT_FIX_SAT);
  return RotCurrent;
} /* End of Mat_Park */


/** \brief Performs the inverse Park transformation.
 *
 * \param[in] RotVolt Rotating 2-phase voltage structure
 * \param[in] Angle Angle [0..65535 = 0..2Pi]
 * \return Stationary 2-phase voltage structure
 *
 * \ingroup math_api
 */
__STATIC_INLINE TComplex Mat_InvPark(TComplex RotVolt, uint16 Angle)
{
  TComplex StatVolt = {0, 0};
  sint32 Cos;
  sint32 Sin;
  uint32 UAngle;
  /* Take upper 10 bits of 16-bit angle */
  UAngle = Angle >> 6u;
  /* Get angle functions */
  Cos = pTable_Cos[UAngle];
  Sin = Table_Sin[UAngle];
  /* Real output = saturate(real input * cos / 4 - imag. input * sin / 4) */
  StatVolt.Real = (sint16)(__SSAT(Mat_FixMulScale(RotVolt.Real, Cos, -2) - Mat_FixMulScale(RotVolt.Imag, Sin, -2), MAT_FIX_SAT));
  /* Imaginary output = saturate(real input * sin / 4 + imag. input * cos / 4) */
  StatVolt.Imag = (sint16)(__SSAT(Mat_FixMulScale(RotVolt.Real, Sin, -2) + Mat_FixMulScale(RotVolt.Imag, Cos, -2), MAT_FIX_SAT));
  return StatVolt;
} /* End of Mat_InvPark */

/** \brief Performs the Polar in Kartesisch.
 *
 * \param[in] Amp
 * \param[in] Angle Angle [0..65535 = 0..2Pi]
 * \return Stationary 2-phase voltage structure
 *
 * \ingroup math_api
 */
__STATIC_INLINE TComplex Mat_PolarKartesisch(uint16 Amp, uint16 Angle)
{
  TComplex StatOut = {0, 0};
  sint32 Cos;
  sint32 Sin;
  uint32 UAngle;
  /* Take upper 10 bits of 16-bit angle */
  UAngle = Angle >> 6u;
  /* Get angle functions */
  Cos = pTable_Cos[UAngle];
  Sin = Table_Sin[UAngle];
  /* Real output = saturate(real input * cos / 4 - imag. input * sin / 4) */
  StatOut.Real = (sint16)(__SSAT(Mat_FixMulScale(Amp, Cos, 0), MAT_FIX_SAT));
  /* Imaginary output = saturate(real input * sin / 4 + imag. input * cos / 4) */
  StatOut.Imag = (sint16)(__SSAT(Mat_FixMulScale(Amp, Sin, 0), MAT_FIX_SAT));
  return StatOut;
} /* End of Mat_PolarKartesisch */

/** \brief Calculates angle and amplitude from stationary coordinates.
 *
 * \param[in] Stat Stationary coordinates in fixed-point format
 * \param[out] Pointer to amplitude
 * \return Angle [0..65535 = 0..2Pi]
 *
 * \ingroup math_api
 */
__STATIC_INLINE uint16 Mat_CalcAngleAmp(TComplex Stat, uint16 *pAmp)
{
  sint32 AbsReal;
  sint32 AbsImag;
  uint32 Index;
  uint32 Angle;
  uint32 TableValue;
  /* Get absolute values */
  AbsReal = Stat.Real;

  if (AbsReal < 0)
  {
    AbsReal = -AbsReal;
  }

  AbsImag = Stat.Imag;

  if (AbsImag < 0)
  {
    AbsImag = -AbsImag;
  }

  if (AbsImag <= AbsReal)
  {
    /* Get basic angle from table */
    Index = (((uint32)AbsImag) * 1024u) / ((uint32)AbsReal);
    TableValue = Table_ArcTan[Index];
    /* Get amplitude from table */
    *pAmp = (((uint32)AbsReal) * Table_Amp[Index]) >> 15u;

    /* Get final angle depending on quadrant */
    if (Stat.Real > 0)
    {
      if (Stat.Imag >= 0)
      {
        Angle = TableValue;
      }
      else /* (Stat.Imag < 0) */
      {
        Angle = 0x10000u - TableValue;
      }
    }
    else /* (Stat.Real < 0) */
    {
      if (Stat.Imag >= 0)
      {
        Angle = 0x8000u - TableValue;
      }
      else /* (Stat.Imag < 0) */
      {
        Angle = 0x8000u + TableValue;
      }
    }
  }
  else /* (AbsReal < AbsImag) */
  {
    /* Get basic angle from table */
    Index = (((uint32)AbsReal) * 1024u) / ((uint32)AbsImag);
    TableValue = Table_ArcTan[Index];
    /* Get amplitude from table */
    *pAmp = (((uint32)AbsImag) * Table_Amp[Index]) >> 15u;

    /* Get final angle depending on quadrant */
    if (Stat.Real >= 0)
    {
      if (Stat.Imag > 0)
      {
        Angle = 0x4000u - TableValue;
      }
      else /* (Stat.Imag < 0) */
      {
        Angle = 0xC000u + TableValue;
      }
    }
    else /* (Stat.Real < 0) */
    {
      if (Stat.Imag > 0)
      {
        Angle = 0x4000u + TableValue;
      }
      else /* (Stat.Imag < 0) */
      {
        Angle = 0xC000u - TableValue;
      }
    }
  }

  return (uint16)Angle;
} /* End of Mat_CalcAngleAmp */


/** \brief Calculates angle from stationary coordinates.
 *
 * \param[in] Stat Stationary coordinates in fixed-point format
 * \return Angle [0..65535 = 0..2Pi]
 *
 * \ingroup math_api
 */
__STATIC_INLINE uint16 Mat_CalcAngle(TComplex Stat)
{
  sint32 AbsReal;
  sint32 AbsImag;
  uint32 Index;
  uint32 Angle;
  uint32 TableValue;
  /* Get absolute values */
  AbsReal = Stat.Real;

  if (AbsReal < 0)
  {
    AbsReal = -AbsReal;
  }

  AbsImag = Stat.Imag;

  if (AbsImag < 0)
  {
    AbsImag = -AbsImag;
  }

  if (AbsImag <= AbsReal)
  {
    /* Get basic angle from table */
    Index = (((uint32)AbsImag) * 1024u) / ((uint32)AbsReal);
    TableValue = Table_ArcTan[Index];

    /* Get final angle depending on quadrant */
    if (Stat.Real > 0)
    {
      if (Stat.Imag >= 0)
      {
        Angle = TableValue;
      }
      else /* (Stat.Imag < 0) */
      {
        Angle = 0x10000u - TableValue;
      }
    }
    else /* (Stat.Real < 0) */
    {
      if (Stat.Imag >= 0)
      {
        Angle = 0x8000u - TableValue;
      }
      else /* (Stat.Imag < 0) */
      {
        Angle = 0x8000u + TableValue;
      }
    }
  }
  else /* (AbsReal < AbsImag) */
  {
    /* Get basic angle from table */
    Index = (((uint32)AbsReal) * 1024u) / ((uint32)AbsImag);
    TableValue = Table_ArcTan[Index];

    /* Get final angle depending on quadrant */
    if (Stat.Real >= 0)
    {
      if (Stat.Imag > 0)
      {
        Angle = 0x4000u - TableValue;
      }
      else /* (Stat.Imag < 0) */
      {
        Angle = 0xC000u + TableValue;
      }
    }
    else /* (Stat.Real < 0) */
    {
      if (Stat.Imag > 0)
      {
        Angle = 0x4000u + TableValue;
      }
      else /* (Stat.Imag < 0) */
      {
        Angle = 0xC000u - TableValue;
      }
    }
  }

  return (uint16)Angle;
} /* End of Mat_CalcAngle */

/** \brief Calculates amplitude from stationary coordinates.
 *
 * \param[in] Stat Stationary coordinates in fixed-point format
 * \param[out] Pointer to amplitude
 * \return Angle [0..65535 = 0..2Pi]
 *
 * \ingroup math_api
 */
__STATIC_INLINE uint16 Mat_CalcAmp(TComplex Stat)
{
  sint32 AbsReal;
  sint32 AbsImag;
  uint32 Index;
  uint32 Amp;
  /* Get absolute values */
  AbsReal = Stat.Real;

  if (AbsReal < 0)
  {
    AbsReal = -AbsReal;
  }

  AbsImag = Stat.Imag;

  if (AbsImag < 0)
  {
    AbsImag = -AbsImag;
  }

  if (AbsImag <= AbsReal)
  {
    /* Get basic angle from table */
    Index = (((uint32)AbsImag) * 1024u) / ((uint32)AbsReal);
    /* Get amplitude from table */
    Amp = (((uint32)AbsReal) * Table_Amp[Index]) >> 15u;
  }
  else /* (AbsReal < AbsImag) */
  {
    /* Get basic angle from table */
    Index = (((uint32)AbsReal) * 1024u) / ((uint32)AbsImag);
    /* Get amplitude from table */
    Amp = (((uint32)AbsImag) * Table_Amp[Index]) >> 15u;
  }

  return (uint16)Amp;
} /* End of Mat_CalcAmp */

/** \brief Calculates rampe.
 *
 * \param[in] Slewrate Input in fixed-point format
 * \param[out] output32
 * \return output [-32767..+32767]
 *
 * \ingroup math_api
 */
__STATIC_INLINE sint16 Mat_Ramp(sint16 Input, sint32 Slewrate, sint32 *Output)
{
  sint32 inp;
  sint32 outp;
  outp = * Output;
  inp = Input << 16;

  if (inp > outp)
  {
    outp = outp + Slewrate;

    if (outp > inp)
    {
      outp = inp;
    }
  }
  else
  {
    outp = outp - Slewrate;

    if (outp < inp)
    {
      outp = inp;
    }
  }

  *Output = outp;
  return (outp >> 16);
}
/* End of Mat_Ramp */


#endif /* MAT.H */

