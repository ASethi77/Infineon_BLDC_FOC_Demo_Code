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
/**
 * \file     adc2.h
 *
 * \brief    ADC2 low level access library
 *
 * \version  V0.2.5
 * \date     23. Apr 2021
 *
 * \note This file violates [MISRA Rule 45]
 */

/*******************************************************************************
**                             Author(s) Identity                             **
********************************************************************************
** Initials     Name                                                          **
** ---------------------------------------------------------------------------**
** DM           Daniel Mysliwitz                                              **
** DCM          Dragos C. Molocea                                             **
** BG           Blandine Guillot                                              **
** JO           Julia Ott                                                     **
*******************************************************************************/

/*******************************************************************************
**                          Revision Control History                          **
********************************************************************************
** V0.1.0: 2014-05-13, DM:   Initial version                                  **
** V0.1.1: 2014-09-11, DM:   ADC2->TH6_9_LOWER added to Init function         **
** V0.1.2: 2015-02-10, DM:   Individual header file added                     **
** V0.1.3: 2015-02-24, DM:   Comment for TH6_9_UPPER added                    **
** V0.1.4: 2015-07-16, DM:   GetChResult/GetSwModeResult result register      **
**                           address calculation corrected                    **
** V0.1.5: 2017-01-23, DM:   MMODE and Hysteresis added                       **
** V0.1.6: 2017-07-13, DM:   ADC2_VCCP_Result_mV() renamed to                 **
**                           ADC2_VDDC_Result_mV()                            **
**                           Double declaration of ADC2_Temp_Result_C removed **
** V0.1.7: 2017-09-26, DM:   ADC2_TEMP_WARN_Int_En/Dis macros renamed to      **
**                           ADC2_Temp_Warn_Int_En/Dis                        **
**                           MISRA 2012 compliance, the following PC-Lint     **
**                           rules are globally deactivated:                  **
**                           - Info 793: ANSI/ISO limit of 6 'significant     **
**                             characters in an external identifier           **
**                           - Info 835: A zero has been given as right       **
**                             argument to operator                           **
**                           - Info 845: The left argument to operator '&'    **
**                             is certain to be 0                             **
**                           Replaced macros by INLINE functions              **
**                           Replaced register accesses within functions by   **
**                           function calls                                   **
**                           Replaced __STATIC_INLINE by INLINE               **
** V0.1.8: 2018-07-03, DCM:  Conversion formula from digital value to mV      **
**                           changed based on the software unit test findings **
**                           and simplified according to the new spec         **
** V0.1.9: 2018-11-27, JO:   Moved revision history from adc2.c to adc2.h     **
**                           Included tle_variants.h instead of tle_device.h  **
**                           Added include io.which was included by           **
**                           tle_device.h indirectly                          **
** V0.2.0: 2019-09-10, JO:   Added initialization of ADC2->FILT_LO_CTRL and   **
**                           ADC2->FILT_UP_CTRL to ADC2_Init()                **
** V0.2.1: 2020-04-15, BG:   Updated revision history format                  **
** V0.2.2: 2020-07-13, JO:   EP-431: remove ARMCC v6 Compiler warnings        **
**                           - Added typecasts to remove 'implicit typecast'  **
**                             warning                                        **
** V0.2.3: 2020-07-21, BG:   EP-439: Formatted .h/.c files                    **
** V0.2.4: 2020-10-13, JO:   EP-518: Replaced ° by deg in doxygen comment     **
** V0.2.5: 2021-04-23, BG:   EP-726: Corrected MISRA 2012 violations          **
*******************************************************************************/

#ifndef ADC2_H
#define ADC2_H

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "tle987x.h"
#include "types.h"
#include "adc2_defines.h"
#include "tle_variants.h"
#include "sfr_access.h"

/*******************************************************************************
**                        Global Constant Declarations                        **
*******************************************************************************/
/**\brief ADC2 \f$ V_{BG}\f$ in Volts */
#define ADC2_VREF (1.211F)
/**\brief ADC2 \f$ V_{BG}\f$ (1.211 V) in millivolts */
#define ADC2_VREF_mV (1211)
/**\brief ADC2 Filtered output register maximum value */
#define ADC2_FILTOUT_MAX (1023u)

/**\brief Nominator and Denominator of Attenuator Conversion formula for VS:
    attenuator for VS Range 0..28V is 0.039 => Inverse fraction (1000/39) */
#define VS_ATTEN_CONV_NOMIN_MAX28V  (1000u)
#define VS_ATTEN_CONV_DENOM_MAX28V  (39u)

/**\brief Nominator and Denominator of Attenuator Conversion formula for VS:
    attenuator for VS Range 0..22V is 0.055 => Inverse fraction (200/11) */
#define VS_ATTEN_CONV_NOMIN_MAX22V  (200u)
#define VS_ATTEN_CONV_DENOM_MAX22V  (11u)

/**\brief Nominator and Denominator of Attenuator Conversion formula for VSD:
    attenuator for VSD is 0.039 => Inverse fraction (1000/39) */
#define VSD_ATTEN_CONV_NOMIN    (1000u)
#define VSD_ATTEN_CONV_DENOM    (39u)

/**\brief Nominator and Denominator of Attenuator Conversion formula for VCP:
    attenuator for VCP is 0.023 => Inverse fraction (1000/23) */
#define VCP_ATTEN_CONV_NOMIN    (1000u)
#define VCP_ATTEN_CONV_DENOM    (23u)

/**\brief Nominator and Denominator of Attenuator Conversion formula for MON:
    attenuator for MON is 0.039 => Inverse fraction (1000/39) */
#define MON_ATTEN_CONV_NOMIN    (1000u)
#define MON_ATTEN_CONV_DENOM    (39u)

/**\brief Nominator and Denominator of Attenuator Conversion formula for VDDP:
    attenuator for VDDP is 0.164 => Inverse fraction (250/41) */
#define VDDP_ATTEN_CONV_NOMIN   (250u)
#define VDDP_ATTEN_CONV_DENOM   (41u)

/**\brief Nominator and Denominator of Attenuator Conversion formula for VAREF:
    attenuator for VAREF is 0.219 => Inverse fraction (1000/219) */
#define VAREF_ATTEN_CONV_NOMIN  (1000u)
#define VAREF_ATTEN_CONV_DENOM  (219u)

/**\brief Nominator and Denominator of Attenuator Conversion formula for VBG:
    attenuator for VBG is 0.75 => Inverse fraction (4/3) */
#define VBG_ATTEN_CONV_NOMIN    (4u)
#define VBG_ATTEN_CONV_DENOM    (3u)

/**\brief Nominator and Denominator of Attenuator Conversion formula for VDDC:
    attenuator for VDDC is 0.75 => Inverse fraction (4/3) */
#define VDDC_ATTEN_CONV_NOMIN   (4u)
#define VDDC_ATTEN_CONV_DENOM   (3u)

/**\brief Offset of V_Temp (mV) corresponding to 0 &deg;C reference */
#define V_TEMP_REF_OFFSET_mV    (666u)

/**\brief Scaling factor for V_Temp (mV) */
#define V_TEMP_SCALE_FACT   (100u)

/**\brief Conversion coefficient from V_Temp (mV) to Temperature (&deg;C)
   multiplied by V_TEMP_SCALE_FACT */
#define CONV_COEFF_mV_TO_degC    (231u)

/**\brief ADC2 channel selection macro, channel 0 - VBAT */
#define ADC2_VBAT       (0)
/**\brief ADC2 channel selection macro, channel 1 - VS */
#define ADC2_VS         (1)
/**\brief ADC2 channel selection macro, channel 2 - VSD */
#define ADC2_VSD        (2)
/**\brief ADC2 channel selection macro, channel 3 - VCP */
#define ADC2_VCP        (3)
/**\brief ADC2 channel selection macro, channel 4 - MON */
#define ADC2_MON        (4)
/**\brief ADC2 channel selection macro, channel 5 - VDDP */
#define ADC2_VDDP       (5)
/**\brief ADC2 channel selection macro, channel 6 - VAREF */
#define ADC2_VAREF      (6)
/**\brief ADC2 channel selection macro, channel 7 - VBG */
#define ADC2_VBG        (7)
/**\brief ADC2 channel selection macro, channel 8 - VDDC */
#define ADC2_VDDC       (8)
/**\brief ADC2 channel selection macro, channel 9 - TEMP */
#define ADC2_TEMP       (9)

/*******************************************************************************
**                          Global Macro Declarations                         **
*******************************************************************************/

#if (UC_SERIES == TLE986)
#define ADC2_VBat_Attenuator_Range_3_28V (1u)
#define ADC2_VBat_Attenuator_Range_3_22V (0u)

/** \brief sets ADC2 Channel 0 (VBat) Attenuator Range to Range 2 (from 3 to 28 V).
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC2 Channel 0 (VBat) Attenuator Range to Range 2 (from 3 to 28 V).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VBat_Attenuator_Range_3_28V_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VBat_Attenuator_Range_3_28V_Set(void)
{
  Field_Mod32(&ADC2->CTRL_STS.reg, ADC2_CTRL_STS_VBAT_RANGE_Pos, ADC2_CTRL_STS_VBAT_RANGE_Msk, 1u);
}

/** \brief sets ADC2 Channel 0 (VBat) Attenuator Range to Range 1 (from 3 to 22 V).
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC2 Channel 0 (VBat) Attenuator Range to Range 1 (from 3 to 22 V).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VBat_Attenuator_Range_3_22V_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VBat_Attenuator_Range_3_22V_Set(void)
{
  Field_Mod32(&ADC2->CTRL_STS.reg, ADC2_CTRL_STS_VBAT_RANGE_Pos, ADC2_CTRL_STS_VBAT_RANGE_Msk, 0u);
}

/** \brief gets ADC2 Channel 0 (VBat) Attenuator Range.
 *
 * \retval 1 if Range 2 (from 3 to 22V) is selected.
 * \retval 0 if Range 1 (from 3 to 28V) is selected.
 *
 * \brief <b>Example</b><br>
 * \brief This example reads ADC2 Channel 0 (VBat) Attenuator Range.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   uint8 data;
 *
 *   data = ADC2_VBat_Attenuator_Range_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE uint8 ADC2_VBat_Attenuator_Range_Get(void)
{
  return ( u8_Field_Rd32(&ADC2->CTRL_STS.reg, ADC2_CTRL_STS_VBAT_RANGE_Pos, ADC2_CTRL_STS_VBAT_RANGE_Msk) );
}
#endif

#define ADC2_VS_Attenuator_Range_3_28V (1u)
#define ADC2_VS_Attenuator_Range_3_22V (0u)

/** \brief sets ADC2 Channel 1 (VS) Attenuator Range to Range 2 (from 3 to 28 V).
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC2 Channel 1 (VS) Attenuator Range to Range 2 (from 3 to 28 V).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VS_Attenuator_Range_3_28V_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VS_Attenuator_Range_3_28V_Set(void)
{
  Field_Mod32(&ADC2->CTRL_STS.reg, ADC2_CTRL_STS_VS_RANGE_Pos, ADC2_CTRL_STS_VS_RANGE_Msk, 1u);
}

/** \brief sets ADC2 Channel 1 (VS) Attenuator Range to Range 1 (from 3 to 22 V).
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC2 Channel 1 (VS) Attenuator Range to Range 1 (from 3 to 22 V).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VS_Attenuator_Range_3_22V_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VS_Attenuator_Range_3_22V_Set(void)
{
  Field_Mod32(&ADC2->CTRL_STS.reg, ADC2_CTRL_STS_VS_RANGE_Pos, ADC2_CTRL_STS_VS_RANGE_Msk, 0u);
}

/** \brief gets ADC2 Channel 1 (VS) Attenuator Range.
 *
 * \retval 1 if Range 2 (from 3 to 22V) is selected.
 * \retval 0 if Range 1 (from 3 to 28V) is selected.
 *
 * \brief <b>Example</b><br>
 * \brief This example reads ADC2 Channel 1 (VS) Attenuator Range.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   uint8 data;
 *
 *   data = ADC2_VS_Attenuator_Range_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE uint8 ADC2_VS_Attenuator_Range_Get(void)
{
  return ( u8_Field_Rd32(&ADC2->CTRL_STS.reg, ADC2_CTRL_STS_VS_RANGE_Pos, ADC2_CTRL_STS_VS_RANGE_Msk) );
}

/* ADC2 Interrupt Clear Macros */
/** \brief clears VS Overvoltage Interrupt Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VS Overvoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VS_OV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VS_OV_IS == 1u)
 *   {
 *     ADC2_VS_UP_CALLBACK();
 *     ADC2_VS_OV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VS_OV_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->SYS_SUPPLY_IRQ_CLR.reg, SCUPM_SYS_SUPPLY_IRQ_CLR_VS_OV_ICLR_Pos, SCUPM_SYS_SUPPLY_IRQ_CLR_VS_OV_ICLR_Msk, 1u);
}

/** \brief clears VS Undervoltage Interrupt Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VS Undervoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VS_UV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VS_UV_IS == 1u)
 *   {
 *     ADC2_VS_LO_CALLBACK();
 *     ADC2_VS_UV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VS_UV_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->SYS_SUPPLY_IRQ_CLR.reg, SCUPM_SYS_SUPPLY_IRQ_CLR_VS_UV_ICLR_Pos, SCUPM_SYS_SUPPLY_IRQ_CLR_VS_UV_ICLR_Msk, 1u);
}

/** \brief clears VDDP Overvoltage Interrupt Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VDDP Overvoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VDDP_OV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VDD5V_OV_IS == 1u)
 *   {
 *     ADC2_VDDP_UP_CALLBACK();
 *     ADC2_VDDP_OV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VDDP_OV_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->SYS_SUPPLY_IRQ_CLR.reg, SCUPM_SYS_SUPPLY_IRQ_CLR_VDD5V_OV_ICLR_Pos, SCUPM_SYS_SUPPLY_IRQ_CLR_VDD5V_OV_ICLR_Msk, 1u);
}

/** \brief clears VDDP Undervoltage Interrupt Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VDDP Undervoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VDDP_UV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VDD5V_UV_IS == 1u)
 *   {
 *     ADC2_VDDP_LO_CALLBACK();
 *     ADC2_VDDP_UV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VDDP_UV_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->SYS_SUPPLY_IRQ_CLR.reg, SCUPM_SYS_SUPPLY_IRQ_CLR_VDD5V_UV_ICLR_Pos, SCUPM_SYS_SUPPLY_IRQ_CLR_VDD5V_UV_ICLR_Msk, 1u);
}

/** \brief clears VDDC Overvoltage Interrupt Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VDDC Overvoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VDDC_OV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VDD1V5_OV_IS == 1u)
 *   {
 *     ADC2_VDDC_UP_CALLBACK();
 *     ADC2_VDDC_OV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VDDC_OV_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->SYS_SUPPLY_IRQ_CLR.reg, SCUPM_SYS_SUPPLY_IRQ_CLR_VDD1V5_OV_ICLR_Pos, SCUPM_SYS_SUPPLY_IRQ_CLR_VDD1V5_OV_ICLR_Msk, 1u);
}

/** \brief clears VDDC Undervoltage Interrupt Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VDDC Undervoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VDDC_UV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VDD1V5_UV_IS == 1u)
 *   {
 *     ADC2_VDDC_LO_CALLBACK();
 *     ADC2_VDDC_UV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VDDC_UV_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->SYS_SUPPLY_IRQ_CLR.reg, SCUPM_SYS_SUPPLY_IRQ_CLR_VDD1V5_UV_ICLR_Pos, SCUPM_SYS_SUPPLY_IRQ_CLR_VDD1V5_UV_ICLR_Msk, 1u);
}

/** \brief clears Driver Supply MU High Interrupt Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Driver Supply MU High interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VSD_OV_Int_En();
 *   if (SCUPM->BDRV_IS.bit.VSD_UPTH_IS == 1u)
 *   {
 *     ADC2_VSD_UP_CALLBACK();
 *     ADC2_VSD_OV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VSD_OV_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->BDRV_ISCLR.reg, SCUPM_BDRV_ISCLR_VSD_UPTH_ICLR_Pos, SCUPM_BDRV_ISCLR_VSD_UPTH_ICLR_Msk, 1u);
}

/** \brief clears Driver Supply MU Low interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Driver Supply MU Low interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VSD_UV_Int_En();
 *   if (SCUPM->BDRV_IS.bit.VSD_LOWTH_IS == 1u)
 *   {
 *     ADC2_VSD_LO_CALLBACK();
 *     ADC2_VSD_UV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VSD_UV_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->BDRV_ISCLR.reg, SCUPM_BDRV_ISCLR_VSD_LOWTH_ICLR_Pos, SCUPM_BDRV_ISCLR_VSD_LOWTH_ICLR_Msk, 1u);
}

/** \brief clears Charge Pump MU High Interrupt Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Charge Pump MU High interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VCP_OV_Int_En();
 *   if (SCUPM->BDRV_IS.bit.VCP_UPTH_IS == 1u)
 *   {
 *     ADC2_VCP_UP_CALLBACK();
 *     ADC2_VCP_OV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VCP_OV_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->BDRV_ISCLR.reg, SCUPM_BDRV_ISCLR_VCP_UPTH_ICLR_Pos, SCUPM_BDRV_ISCLR_VCP_UPTH_ICLR_Msk, 1u);
}

/** \brief clears Charge Pump MU Low Interrupt Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Charge Pump MU Low interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VCP_UV_Int_En();
 *   if (SCUPM->BDRV_IS.bit.VCP_LOWTH1_IS == 1u)
 *   {
 *     ADC2_VCP_LO_CALLBACK();
 *     ADC2_VCP_UV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VCP_UV_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->BDRV_ISCLR.reg, SCUPM_BDRV_ISCLR_VCP_LOWTH1_ICLR_Pos, SCUPM_BDRV_ISCLR_VCP_LOWTH1_ICLR_Msk, 1u);
}

#if (UC_SERIES == TLE986)
/** \brief clears VBAT Overvoltage Interrupt Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VBAT Overvoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VBAT_OV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VBAT_OV_IS == 1u)
 *   {
 *     ADC2_VBAT_UP_CALLBACK();
 *     ADC2_VBAT_OV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VBAT_OV_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->SYS_SUPPLY_IRQ_CLR.reg, SCUPM_SYS_SUPPLY_IRQ_CLR_VBAT_OV_ICLR_Pos, SCUPM_SYS_SUPPLY_IRQ_CLR_VBAT_OV_ICLR_Msk, 1u);
}

/** \brief clears VBAT Undervoltage Interrupt Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VBAT Undervoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VBAT_UV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VBAT_UV_IS == 1u)
 *   {
 *     ADC2_VBAT_LO_CALLBACK();
 *     ADC2_VBAT_UV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VBAT_UV_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->SYS_SUPPLY_IRQ_CLR.reg, SCUPM_SYS_SUPPLY_IRQ_CLR_VBAT_UV_ICLR_Pos, SCUPM_SYS_SUPPLY_IRQ_CLR_VBAT_UV_ICLR_Msk, 1u);
}
#endif

#if (UC_SERIES == TLE987)
/** \brief clears MON Overvoltage Interrupt Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON Overvoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_MON_OV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.MON_OV_IS == 1u)
 *   {
 *     ADC2_MON_UP_CALLBACK();
 *     ADC2_MON_OV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_MON_OV_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->SYS_SUPPLY_IRQ_CLR.reg, SCUPM_SYS_SUPPLY_IRQ_CLR_MON_OV_ICLR_Pos, SCUPM_SYS_SUPPLY_IRQ_CLR_MON_OV_ICLR_Msk, 1u);
}

/** \brief clears MON Undervoltage Interrupt Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON Undervoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_MON_UV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.MON_UV_IS == 1u)
 *   {
 *     ADC2_MON_LO_CALLBACK();
 *     ADC2_MON_UV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_MON_UV_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->SYS_SUPPLY_IRQ_CLR.reg, SCUPM_SYS_SUPPLY_IRQ_CLR_MON_UV_ICLR_Pos, SCUPM_SYS_SUPPLY_IRQ_CLR_MON_UV_ICLR_Msk, 1u);
}
#endif

/** \brief clears 8 Bit ADC2 Reference Overvoltage Interrupt Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the 8 Bit ADC2 Reference Overvoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VBG_OV_Int_En();
 *   if (MF->REF1_STS.bit.REFBG_UPTHWARN_STS == 1u)
 *   {
 *     ADC2_VBG_UP_CALLBACK();
 *     ADC2_VBG_OV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VBG_OV_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->SYS_ISCLR.reg, SCUPM_SYS_ISCLR_REFBG_UPTHWARN_ICLR_Pos, SCUPM_SYS_ISCLR_REFBG_UPTHWARN_ICLR_Msk, 1u);
}

/** \brief clears 8 Bit ADC2 Reference Undervoltage Interrupt Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the 8 Bit ADC2 Reference Undervoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VBG_UV_Int_En();
 *   if (MF->REF1_STS.bit.REFBG_LOTHWARN_STS == 1u)
 *   {
 *     ADC2_VBG_LO_CALLBACK();
 *     ADC2_VBG_UV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VBG_UV_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->SYS_ISCLR.reg, SCUPM_SYS_ISCLR_REFBG_LOTHWARN_ICLR_Pos, SCUPM_SYS_ISCLR_REFBG_LOTHWARN_ICLR_Msk, 1u);
}

#if ((ADC2_CTRL2 & (1u << 2u)) == 0u)
/* System Temperature Sensor */
/** \brief clears System Overtemperature Shutdown Interrupt Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the System Overtemperature Shutdown interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_TEMP_OT_Int_En();
 *   if (SCUPM->SYS_IS.bit.SYS_OT_IS == 1u)
 *   {
 *     ADC2_SYS_TEMP_UP_CALLBACK();
 *     ADC2_TEMP_OT_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_TEMP_OT_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->SYS_ISCLR.reg, SCUPM_SYS_ISCLR_SYS_OT_ICLR_Pos, SCUPM_SYS_ISCLR_SYS_OT_ICLR_Msk, 1u);
}

/** \brief clears System Overtemperature Prewarning Interrupt Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the System Overtemperature Prewarning interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_TEMP_WARN_Int_En();
 *   if (SCUPM->SYS_IS.bit.SYS_OTWARN_IS == 1u)
 *   {
 *     ADC2_SYS_TEMP_LO_CALLBACK();
 *     ADC2_TEMP_WARN_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_TEMP_WARN_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->SYS_ISCLR.reg, SCUPM_SYS_ISCLR_SYS_OTWARN_ICLR_Pos, SCUPM_SYS_ISCLR_SYS_OTWARN_ICLR_Msk, 1u);
}
#else
/* PMU Temperature Sensor */
/** \brief clears System Overtemperature Shutdown Interrupt Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the System Overtemperature Shutdown interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_TEMP_OT_Int_En();
 *   if (SCUPM->SYS_IS.bit.SYS_OT_IS == 1u)
 *   {
 *     ADC2_SYS_TEMP_UP_CALLBACK();
 *     ADC2_TEMP_OT_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_TEMP_OT_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->SYS_ISCLR.reg, SCUPM_SYS_ISCLR_PMU_OT_ICLR_Pos, SCUPM_SYS_ISCLR_PMU_OT_ICLR_Msk, 1u);
}

/** \brief clears System Overtemperature Prewarning Interrupt Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the System Overtemperature Prewarning interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_TEMP_WARN_Int_En();
 *   if (SCUPM->SYS_IS.bit.SYS_OTWARN_IS == 1u)
 *   {
 *     ADC2_SYS_TEMP_LO_CALLBACK();
 *     ADC2_TEMP_WARN_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_TEMP_WARN_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->SYS_ISCLR.reg, SCUPM_SYS_ISCLR_PMU_OTWARN_ICLR_Pos, SCUPM_SYS_ISCLR_PMU_OTWARN_ICLR_Msk, 1u);
}
#endif

/* ADC2 Interrupt Enable/Disable Macros */
/** \brief enables VS Overvoltage interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VS Overvoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VS_OV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VS_OV_IS == 1u)
 *   {
 *     ADC2_VS_UP_CALLBACK();
 *     ADC2_VS_OV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VS_OV_Int_En(void)
{
  Field_Mod32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, SCUPM_SYS_SUPPLY_IRQ_CTRL_VS_OV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VS_OV_IE_Msk, 1u);
}

/** \brief disables VS Overvoltage interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VS Overvoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VS_OV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VS_OV_IS == 1u)
 *   {
 *     ADC2_VS_UP_CALLBACK();
 *     ADC2_VS_OV_Int_Clr();
 *   }
 *   ADC2_VS_OV_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VS_OV_Int_Dis(void)
{
  Field_Mod32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, SCUPM_SYS_SUPPLY_IRQ_CTRL_VS_OV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VS_OV_IE_Msk, 0u);
}

/** \brief enables VS Undervoltage interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VS Undervoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VS_UV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VS_UV_IS == 1u)
 *   {
 *     ADC2_VS_LO_CALLBACK();
 *     ADC2_VS_UV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VS_UV_Int_En(void)
{
  Field_Mod32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, SCUPM_SYS_SUPPLY_IRQ_CTRL_VS_UV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VS_UV_IE_Msk, 1u);
}

/** \brief disables VS Undervoltage interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VS Undervoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VS_UV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VS_UV_IS == 1u)
 *   {
 *     ADC2_VS_LO_CALLBACK();
 *     ADC2_VS_UV_Int_Clr();
 *   }
 *   ADC2_VS_UV_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VS_UV_Int_Dis(void)
{
  Field_Mod32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, SCUPM_SYS_SUPPLY_IRQ_CTRL_VS_UV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VS_UV_IE_Msk, 0u);
}

/** \brief enables VDDP Overvoltage interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VDDP Overvoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VDDP_OV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VDD5V_OV_IS == 1u)
 *   {
 *     ADC2_VDDP_UP_CALLBACK();
 *     ADC2_VDDP_OV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VDDP_OV_Int_En(void)
{
  Field_Mod32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD5V_OV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD5V_OV_IE_Msk, 1u);
}

/** \brief disables VDDP Overvoltage interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VDDP Overvoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VDDP_OV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VDD5V_OV_IS == 1u)
 *   {
 *     ADC2_VDDP_UP_CALLBACK();
 *     ADC2_VDDP_OV_Int_Clr();
 *   }
 *   ADC2_VDDP_OV_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VDDP_OV_Int_Dis(void)
{
  Field_Mod32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD5V_OV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD5V_OV_IE_Msk, 0u);
}

/** \brief enables VDDP Undervoltage interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VDDP Undervoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VDDP_UV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VDD5V_UV_IS == 1u)
 *   {
 *     ADC2_VDDP_LO_CALLBACK();
 *     ADC2_VDDP_UV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VDDP_UV_Int_En(void)
{
  Field_Mod32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD5V_UV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD5V_UV_IE_Msk, 1u);
}

/** \brief disables VDDP Undervoltage interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VDDP Undervoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VDDP_UV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VDD5V_UV_IS == 1u)
 *   {
 *     ADC2_VDDP_LO_CALLBACK();
 *     ADC2_VDDP_UV_Int_Clr();
 *   }
 *   ADC2_VDDP_UV_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VDDP_UV_Int_Dis(void)
{
  Field_Mod32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD5V_UV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD5V_UV_IE_Msk, 0u);
}

/** \brief enables VDDC Overvoltage interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VDDC Overvoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VDDC_OV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VDD1V5_OV_IS == 1u)
 *   {
 *     ADC2_VDDC_UP_CALLBACK();
 *     ADC2_VDDC_OV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VDDC_OV_Int_En(void)
{
  Field_Mod32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD1V5_OV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD1V5_OV_IE_Msk, 1u);
}

/** \brief disables VDDC Overvoltage interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VDDC Overvoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VDDC_OV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VDD1V5_OV_IS == 1u)
 *   {
 *     ADC2_VDDC_UP_CALLBACK();
 *     ADC2_VDDC_OV_Int_Clr();
 *   }
 *   ADC2_VDDC_OV_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VDDC_OV_Int_Dis(void)
{
  Field_Mod32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD1V5_OV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD1V5_OV_IE_Msk, 0u);
}

/** \brief enables VDDC Undervoltage interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VDDC Undervoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VDDC_UV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VDD1V5_UV_IS == 1u)
 *   {
 *     ADC2_VDDC_LO_CALLBACK();
 *     ADC2_VDDC_UV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VDDC_UV_Int_En(void)
{
  Field_Mod32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD1V5_UV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD1V5_UV_IE_Msk, 1u);
}

/** \brief disables VDDC Undervoltage interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VDDC Undervoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VDDC_UV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VDD1V5_UV_IS == 1u)
 *   {
 *     ADC2_VDDC_LO_CALLBACK();
 *     ADC2_VDDC_UV_Int_Clr();
 *   }
 *   ADC2_VDDC_UV_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VDDC_UV_Int_Dis(void)
{
  Field_Mod32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD1V5_UV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD1V5_UV_IE_Msk, 0u);
}

/** \brief enables Driver Supply MU High interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Driver Supply MU High interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VSD_OV_Int_En();
 *   if (SCUPM->BDRV_IS.bit.VSD_UPTH_IS == 1u)
 *   {
 *     ADC2_VSD_UP_CALLBACK();
 *     ADC2_VSD_OV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VSD_OV_Int_En(void)
{
  Field_Mod32(&SCUPM->BDRV_IRQ_CTRL.reg, SCUPM_BDRV_IRQ_CTRL_VSD_UPTH_IE_Pos, SCUPM_BDRV_IRQ_CTRL_VSD_UPTH_IE_Msk, 1u);
}

/** \brief disables Driver Supply MU High interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Driver Supply MU High interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VSD_OV_Int_En();
 *   if (SCUPM->BDRV_IS.bit.VSD_UPTH_IS == 1u)
 *   {
 *     ADC2_VSD_UP_CALLBACK();
 *     ADC2_VSD_OV_Int_Clr();
 *   }
 *   ADC2_VSD_OV_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VSD_OV_Int_Dis(void)
{
  Field_Mod32(&SCUPM->BDRV_IRQ_CTRL.reg, SCUPM_BDRV_IRQ_CTRL_VSD_UPTH_IE_Pos, SCUPM_BDRV_IRQ_CTRL_VSD_UPTH_IE_Msk, 0u);
}

/** \brief enables Driver Supply MU Low interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Driver Supply MU Low interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VSD_UV_Int_En();
 *   if (SCUPM->BDRV_IS.bit.VSD_LOWTH_IS == 1u)
 *   {
 *     ADC2_VSD_LO_CALLBACK();
 *     ADC2_VSD_UV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VSD_UV_Int_En(void)
{
  Field_Mod32(&SCUPM->BDRV_IRQ_CTRL.reg, SCUPM_BDRV_IRQ_CTRL_VSD_LOWTH_IE_Pos, SCUPM_BDRV_IRQ_CTRL_VSD_LOWTH_IE_Msk, 1u);
}

/** \brief disables Driver Supply MU Low interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Driver Supply MU Low interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VSD_UV_Int_En();
 *   if (SCUPM->BDRV_IS.bit.VSD_LOWTH_IS == 1u)
 *   {
 *     ADC2_VSD_LO_CALLBACK();
 *     ADC2_VSD_UV_Int_Clr();
 *   }
 *   ADC2_VSD_UV_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VSD_UV_Int_Dis(void)
{
  Field_Mod32(&SCUPM->BDRV_IRQ_CTRL.reg, SCUPM_BDRV_IRQ_CTRL_VSD_LOWTH_IE_Pos, SCUPM_BDRV_IRQ_CTRL_VSD_LOWTH_IE_Msk, 0u);
}

/** \brief enables Charge Pump MU High interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Charge Pump MU High interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VCP_OV_Int_En();
 *   if (SCUPM->BDRV_IS.bit.VCP_UPTH_IS == 1u)
 *   {
 *     ADC2_VCP_UP_CALLBACK();
 *     ADC2_VCP_OV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VCP_OV_Int_En(void)
{
  Field_Mod32(&SCUPM->BDRV_IRQ_CTRL.reg, SCUPM_BDRV_IRQ_CTRL_VCP_UPTH_IE_Pos, SCUPM_BDRV_IRQ_CTRL_VCP_UPTH_IE_Msk, 1u);
}

/** \brief disables Charge Pump MU High interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Charge Pump MU High interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VCP_OV_Int_En();
 *   if (SCUPM->BDRV_IS.bit.VCP_UPTH_IS == 1u)
 *   {
 *     ADC2_VCP_UP_CALLBACK();
 *     ADC2_VCP_OV_Int_Clr();
 *   }
 *   ADC2_VCP_OV_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VCP_OV_Int_Dis(void)
{
  Field_Mod32(&SCUPM->BDRV_IRQ_CTRL.reg, SCUPM_BDRV_IRQ_CTRL_VCP_UPTH_IE_Pos, SCUPM_BDRV_IRQ_CTRL_VCP_UPTH_IE_Msk, 0u);
}

/** \brief enables Charge Pump MU Low interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Charge Pump MU Low interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VCP_UV_Int_En();
 *   if (SCUPM->BDRV_IS.bit.VCP_LOWTH1_IS == 1u)
 *   {
 *     ADC2_VCP_LO_CALLBACK();
 *     ADC2_VCP_UV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VCP_UV_Int_En(void)
{
  Field_Mod32(&SCUPM->BDRV_IRQ_CTRL.reg, SCUPM_BDRV_IRQ_CTRL_VCP_LOWTH1_IE_Pos, SCUPM_BDRV_IRQ_CTRL_VCP_LOWTH1_IE_Msk, 1u);
}

/** \brief disables Charge Pump MU Low interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Charge Pump MU Low interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VCP_UV_Int_En();
 *   if (SCUPM->BDRV_IS.bit.VCP_LOWTH1_IS == 1u)
 *   {
 *     ADC2_VCP_LO_CALLBACK();
 *     ADC2_VCP_UV_Int_Clr();
 *   }
 *   ADC2_VCP_UV_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VCP_UV_Int_Dis(void)
{
  Field_Mod32(&SCUPM->BDRV_IRQ_CTRL.reg, SCUPM_BDRV_IRQ_CTRL_VCP_LOWTH1_IE_Pos, SCUPM_BDRV_IRQ_CTRL_VCP_LOWTH1_IE_Msk, 0u);
}

#if (UC_SERIES == TLE986)
/** \brief enables VBAT Overvoltage Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VBAT Overvoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VBAT_OV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VBAT_OV_IS == 1u)
 *   {
 *     ADC2_VBAT_UP_CALLBACK();
 *     ADC2_VBAT_OV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VBAT_OV_Int_En(void)
{
  Field_Mod32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, SCUPM_SYS_SUPPLY_IRQ_CTRL_VBAT_OV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VBAT_OV_IE_Msk, 1u);
}

/** \brief disables VBAT Overvoltage Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VBAT Overvoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VBAT_OV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VBAT_OV_IS == (uint8)1u)
 *   {
 *     ADC2_VBAT_UP_CALLBACK();
 *     ADC2_VBAT_OV_Int_Clr();
 *   }
 *   ADC2_VBAT_OV_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VBAT_OV_Int_Dis(void)
{
  Field_Mod32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, SCUPM_SYS_SUPPLY_IRQ_CTRL_VBAT_OV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VBAT_OV_IE_Msk, 0u);
}

/** \brief enables VBAT Undervoltage Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VBAT Undervoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VBAT_UV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VBAT_UV_IS == 1u)
 *   {
 *     ADC2_VBAT_LO_CALLBACK();
 *     ADC2_VBAT_UV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VBAT_UV_Int_En(void)
{
  Field_Mod32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, SCUPM_SYS_SUPPLY_IRQ_CTRL_VBAT_UV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VBAT_UV_IE_Msk, 1u);
}

/** \brief disables VBAT Undervoltage Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VBAT Undervoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VBAT_UV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VBAT_UV_IS == (uint8)1u)
 *   {
 *     ADC2_VBAT_LO_CALLBACK();
 *     ADC2_VBAT_UV_Int_Clr();
 *   }
 *   ADC2_VBAT_UV_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VBAT_UV_Int_Dis(void)
{
  Field_Mod32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, SCUPM_SYS_SUPPLY_IRQ_CTRL_VBAT_UV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VBAT_UV_IE_Msk, 0u);
}
#endif

#if (UC_SERIES == TLE987)
/** \brief enables MON Overvoltage Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON Overvoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_MON_OV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.MON_OV_IS == 1u)
 *   {
 *     ADC2_MON_UP_CALLBACK();
 *     ADC2_MON_OV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_MON_OV_Int_En(void)
{
  Field_Mod32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, SCUPM_SYS_SUPPLY_IRQ_CTRL_MON_OV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_MON_OV_IE_Msk, 1u);
}

/** \brief disables MON Overvoltage Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON Overvoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_MON_OV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.MON_OV_IS == 1u)
 *   {
 *     ADC2_MON_UP_CALLBACK();
 *     ADC2_MON_OV_Int_Clr();
 *   }
 *   ADC2_MON_OV_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_MON_OV_Int_Dis(void)
{
  Field_Mod32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, SCUPM_SYS_SUPPLY_IRQ_CTRL_MON_OV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_MON_OV_IE_Msk, 0u);
}

/** \brief enables MON Undervoltage Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON Undervoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_MON_UV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.MON_UV_IS == 1u)
 *   {
 *     ADC2_MON_OL_CALLBACK();
 *     ADC2_MON_UV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_MON_UV_Int_En(void)
{
  Field_Mod32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, SCUPM_SYS_SUPPLY_IRQ_CTRL_MON_UV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_MON_UV_IE_Msk, 1u);
}

/** \brief disables MON Undervoltage Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON Undervoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_MON_UV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.MON_UV_IS == 1u)
 *   {
 *     ADC2_MON_OL_CALLBACK();
 *     ADC2_MON_UV_Int_Clr();
 *   }
 *   ADC2_MON_UV_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_MON_UV_Int_Dis(void)
{
  Field_Mod32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, SCUPM_SYS_SUPPLY_IRQ_CTRL_MON_UV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_MON_UV_IE_Msk, 0u);
}
#endif

/** \brief enables 8 Bit ADC2 Reference Overvoltage interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the 8 Bit ADC2 Reference Overvoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VBG_OV_Int_En();
 *   if (MF->REF1_STS.bit.REFBG_UPTHWARN_STS == 1u)
 *   {
 *     ADC2_VBG_UP_CALLBACK();
 *     ADC2_VBG_OV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VBG_OV_Int_En(void)
{
  Field_Mod32(&SCUPM->SYS_IRQ_CTRL.reg, SCUPM_SYS_IRQ_CTRL_REFBG_UPTHWARN_IE_Pos, SCUPM_SYS_IRQ_CTRL_REFBG_UPTHWARN_IE_Msk, 1u);
}

/** \brief disables 8 Bit ADC2 Reference Overvoltage interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the 8 Bit ADC2 Reference Overvoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VBG_OV_Int_En();
 *   if (MF->REF1_STS.bit.REFBG_UPTHWARN_STS == 1u)
 *   {
 *     ADC2_VBG_UP_CALLBACK();
 *     ADC2_VBG_OV_Int_Clr();
 *   }
 *   ADC2_VBG_OV_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VBG_OV_Int_Dis(void)
{
  Field_Mod32(&SCUPM->SYS_IRQ_CTRL.reg, SCUPM_SYS_IRQ_CTRL_REFBG_UPTHWARN_IE_Pos, SCUPM_SYS_IRQ_CTRL_REFBG_UPTHWARN_IE_Msk, 0u);
}

/** \brief enables 8 Bit ADC2 Reference Undervoltage interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the 8 Bit ADC2 Reference Undervoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VBG_UV_Int_En();
 *   if (MF->REF1_STS.bit.REFBG_LOTHWARN_STS == 1u)
 *   {
 *     ADC2_VBG_LO_CALLBACK();
 *     ADC2_VBG_UV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VBG_UV_Int_En(void)
{
  Field_Mod32(&SCUPM->SYS_IRQ_CTRL.reg, SCUPM_SYS_IRQ_CTRL_REFBG_LOTHWARN_IE_Pos, SCUPM_SYS_IRQ_CTRL_REFBG_LOTHWARN_IE_Msk, 1u);
}

/** \brief disables 8 Bit ADC2 Reference Undervoltage interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the 8 Bit ADC2 Reference Undervoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VBG_UV_Int_En();
 *   if (MF->REF1_STS.bit.REFBG_LOTHWARN_STS == 1u)
 *   {
 *     ADC2_VBG_LO_CALLBACK();
 *     ADC2_VBG_UV_Int_Clr();
 *   }
 *   ADC2_VBG_UV_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VBG_UV_Int_Dis(void)
{
  Field_Mod32(&SCUPM->SYS_IRQ_CTRL.reg, SCUPM_SYS_IRQ_CTRL_REFBG_LOTHWARN_IE_Pos, SCUPM_SYS_IRQ_CTRL_REFBG_LOTHWARN_IE_Msk, 0u);
}

#if ((ADC2_CTRL2 & (1u << 2u)) == 0u)
/* System Temperature Sensor */
/** \brief enables System Overtemperature Shutdown interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the System Overtemperature Shutdown interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_TEMP_OT_Int_En();
 *   if (SCUPM->SYS_IS.bit.SYS_OT_IS == 1u)
 *   {
 *     ADC2_SYS_TEMP_UP_CALLBACK();
 *     ADC2_TEMP_OT_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_Temp_OT_Int_En(void)
{
  Field_Mod32(&SCUPM->SYS_IRQ_CTRL.reg, SCUPM_SYS_IRQ_CTRL_SYS_OT_IE_Pos, SCUPM_SYS_IRQ_CTRL_SYS_OT_IE_Msk, 1u);
}

/** \brief disables System Overtemperature Shutdown interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the System Overtemperature Shutdown interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_TEMP_OT_Int_En();
 *   if (SCUPM->SYS_IS.bit.SYS_OT_IS == 1u)
 *   {
 *     ADC2_SYS_TEMP_UP_CALLBACK();
 *     ADC2_TEMP_OT_Int_Clr();
 *   }
 *   ADC2_TEMP_OT_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_Temp_OT_Int_Dis(void)
{
  Field_Mod32(&SCUPM->SYS_IRQ_CTRL.reg, SCUPM_SYS_IRQ_CTRL_SYS_OT_IE_Pos, SCUPM_SYS_IRQ_CTRL_SYS_OT_IE_Msk, 0u);
}

/** \brief enables System Overtemperature Prewarning interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the System Overtemperature Prewarning interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_TEMP_WARN_Int_En();
 *   if (SCUPM->SYS_IS.bit.SYS_OTWARN_IS == 1u)
 *   {
 *     ADC2_SYS_TEMP_LO_CALLBACK();
 *     ADC2_TEMP_WARN_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_Temp_Warn_Int_En(void)
{
  Field_Mod32(&SCUPM->SYS_IRQ_CTRL.reg, SCUPM_SYS_IRQ_CTRL_SYS_OTWARN_IE_Pos, SCUPM_SYS_IRQ_CTRL_SYS_OTWARN_IE_Msk, 1u);
}

/** \brief disables System Overtemperature Prewarning interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the System Overtemperature Prewarning interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_TEMP_WARN_Int_En();
 *   if (SCUPM->SYS_IS.bit.SYS_OTWARN_IS == 1u)
 *   {
 *     ADC2_SYS_TEMP_LO_CALLBACK();
 *     ADC2_TEMP_WARN_Int_Clr();
 *   }
 *   ADC2_TEMP_WARN_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_Temp_Warn_Int_Dis(void)
{
  Field_Mod32(&SCUPM->SYS_IRQ_CTRL.reg, SCUPM_SYS_IRQ_CTRL_SYS_OTWARN_IE_Pos, SCUPM_SYS_IRQ_CTRL_SYS_OTWARN_IE_Msk, 0u);
}
#else
/* PMU Temperature Sensor */
/** \brief enables System Overtemperature Shutdown interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the System Overtemperature Shutdown interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_TEMP_OT_Int_En();
 *   if (SCUPM->SYS_IS.bit.SYS_OT_IS == 1u)
 *   {
 *     ADC2_SYS_TEMP_UP_CALLBACK();
 *     ADC2_TEMP_OT_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_Temp_OT_Int_En(void)
{
  Field_Mod32(&SCUPM->SYS_IRQ_CTRL.reg, SCUPM_SYS_IRQ_CTRL_PMU_OT_IE_Pos, SCUPM_SYS_IRQ_CTRL_PMU_OT_IE_Msk, 1u);
}

/** \brief disables System Overtemperature Shutdown interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the System Overtemperature Shutdown interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_TEMP_OT_Int_En();
 *   if (SCUPM->SYS_IS.bit.SYS_OT_IS == 1u)
 *   {
 *     ADC2_SYS_TEMP_UP_CALLBACK();
 *     ADC2_TEMP_OT_Int_Clr();
 *   }
 *   ADC2_TEMP_OT_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_Temp_OT_Int_Dis(void)
{
  Field_Mod32(&SCUPM->SYS_IRQ_CTRL.reg, SCUPM_SYS_IRQ_CTRL_PMU_OT_IE_Pos, SCUPM_SYS_IRQ_CTRL_PMU_OT_IE_Msk, 0u);
}

/** \brief enables System Overtemperature Prewarning interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the System Overtemperature Prewarning interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_TEMP_WARN_Int_En();
 *   if (SCUPM->SYS_IS.bit.SYS_OTWARN_IS == 1u)
 *   {
 *     ADC2_SYS_TEMP_LO_CALLBACK();
 *     ADC2_TEMP_WARN_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_Temp_Warn_Int_En(void)
{
  Field_Mod32(&SCUPM->SYS_IRQ_CTRL.reg, SCUPM_SYS_IRQ_CTRL_PMU_OTWARN_IE_Pos, SCUPM_SYS_IRQ_CTRL_PMU_OTWARN_IE_Msk, 1u);
}

/** \brief disables System Overtemperature Prewarning interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the System Overtemperature Prewarning interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_TEMP_WARN_Int_En();
 *   if (SCUPM->SYS_IS.bit.SYS_OTWARN_IS == 1u)
 *   {
 *     ADC2_SYS_TEMP_LO_CALLBACK();
 *     ADC2_TEMP_WARN_Int_Clr();
 *   }
 *   ADC2_TEMP_WARN_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_Temp_Warn_Int_Dis(void)
{
  Field_Mod32(&SCUPM->SYS_IRQ_CTRL.reg, SCUPM_SYS_IRQ_CTRL_PMU_OTWARN_IE_Pos, SCUPM_SYS_IRQ_CTRL_PMU_OTWARN_IE_Msk, 0u);
}
#endif

/*******************************************************************************
**                        Global Function Declarations                        **
*******************************************************************************/
/** \brief Initializes the ADC2 based on the IFXConfigWizard configuration
 *
 * \ingroup adc2_api
 */
void ADC2_Init(void);
INLINE uint16 ADC2_GetChResult(uint8 channel);
#if (UC_SERIES == TLE986)
  INLINE uint16 ADC2_VBat_Result_mV(void);
#endif
INLINE uint16 ADC2_VS_Result_mV(void);
INLINE uint16 ADC2_VSD_Result_mV(void);
INLINE uint16 ADC2_VCP_Result_mV(void);
INLINE uint16 ADC2_MON_Result_mV(void);
INLINE uint16 ADC2_VAREF_Result_mV(void);
INLINE uint16 ADC2_VDDP_Result_mV(void);
INLINE uint16 ADC2_VBG_Result_mV(void);
INLINE uint16 ADC2_VDDC_Result_mV(void);
INLINE sint16 ADC2_Temp_Result_C(void);

/*******************************************************************************
**                     Global Inline Function Definitions                     **
*******************************************************************************/
/** \brief Returns the 10 bit wide result of the selected ADC2 channel
 * \brief Returns 0 if the selected channel number is greater than 9
 *
 * \param channel selected ADC2 channel number (0 to 9)
 * \return 10 bit wide result of the selected channel (FILT_OUT0 to FILT_OUT9)
 *
 * \brief <b>Example</b><br>
 * \brief This example returns the ADC2 Channel 4 result value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 data;
 *
 *     data = ADC2_GetChResult(0x4);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE uint16 ADC2_GetChResult(uint8 channel)
{
  const volatile uint32 *pBaseAddr;
  uint16 Var;
  uint32 addr;
  uint16 idx;

  if ((uint8)ADC2_TEMP >= channel)
  {
    /* violation: intended cast from pointer to unsigned int [MISRA Rule 45]*/
    addr = (uint32)&ADC2->FILT_OUT0.reg;
    /* calculate address offset corresponding to the input channel number */
    idx = (uint16)((uint16)channel << 2u);
    addr += idx;
    /* violation: intended cast from unsigned int to pointer [MISRA Rule 45]*/
    pBaseAddr = (volatile uint32 *) addr;
    /* read the 10 LSbit of the ADC FILT_OUTx register */
    Var = (uint16)((*pBaseAddr) & (uint32)0x000003FF);
  }
  else
  {
    Var = 0;
  }

  return (Var);
} /* End of ADC2_GetChResult */
#if (UC_SERIES == TLE986)
/** \brief returns the Voltage of the VBAT line (ADC2 Channel 0 in TLE986x) in millivolt (mV)
 * \brief calculated based on attenuator conversion factor as follows:
 * \brief \n \n If the VS range is up to 28 V, then
 * \brief \f$ Voltage(mV) = \frac{ADC2.Digital.Result(bit)*(V_{BG}*1000)(mV)}{ADC2.Max.Digital.Value(bit)}*\frac{1000}{39}\f$
 * \brief \n \n If the VS range is up to 22 V, then
 * \brief \f$ Voltage(mV) = \frac{ADC2.Digital.Result(bit)*(V_{BG}*1000)(mV)}{ADC2.Max.Digital.Value(bit)}*\frac{200}{11}\f$
 *
 * \return Voltage of the VBAT line (ADC2 Channel 0) in millivolt
 *
 * \brief <b>Example</b><br>
 * \brief This example returns the specified value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 data;
 *
 *     data = ADC2_VBat_Result_mV();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE uint16 ADC2_VBat_Result_mV(void)
{
  uint16 value;
  value = ADC2_GetChResult(ADC2_VBAT);

  if (ADC2_VBat_Attenuator_Range_Get() == ADC2_VS_Attenuator_Range_3_28V)
  {
    /* Conversion for VBat attenuator range up to 28 V same as for VS */
    value = (uint16)(((value * ((uint32)ADC2_VREF_mV * (uint16)VS_ATTEN_CONV_NOMIN_MAX28V)) / (uint16)ADC2_FILTOUT_MAX) / (uint8)VS_ATTEN_CONV_DENOM_MAX28V);
  }
  else
  {
    /* Conversion for VBat attenuator range up to 22 V same as for VS */
    value = (uint16)(((value * ((uint32)ADC2_VREF_mV * (uint16)VS_ATTEN_CONV_NOMIN_MAX22V)) / (uint16)ADC2_FILTOUT_MAX) / (uint8)VS_ATTEN_CONV_DENOM_MAX22V);
  }

  return (value);
}
#endif
/** \brief returns the Voltage of the VS line (ADC2 Channel 1) in millivolt (mV)
 * \brief calculated based on attenuator conversion factor as follows:
 * \brief \n \n If the VS range is up to 28 V, then
 * \brief \f$ Voltage(mV) = \frac{ADC2.Digital.Result(bit)*(V_{BG}*1000)(mV)}{ADC2.Max.Digital.Value(bit)}*\frac{1000}{39}\f$
 * \brief \n \n If the VS range is up to 22 V, then
 * \brief \f$ Voltage(mV) = \frac{ADC2.Digital.Result(bit)*(V_{BG}*1000)(mV)}{ADC2.Max.Digital.Value(bit)}*\frac{200}{11}\f$
 *
 * \return Voltage of the VS line (ADC2 Channel 1) in millivolt
 *
 * \brief <b>Example</b><br>
 * \brief This example returns the specified value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 data;
 *
 *     data = ADC2_VS_Result_mV();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE uint16 ADC2_VS_Result_mV(void)
{
  uint16 value;
  value = ADC2_GetChResult(ADC2_VS);

  if (ADC2_VS_Attenuator_Range_Get() == ADC2_VS_Attenuator_Range_3_28V)
  {
    /* Conversion for VS attenuator range up to 28 V */
    value = (uint16)(((value * (uint32)((uint16)ADC2_VREF_mV * (uint16)VS_ATTEN_CONV_NOMIN_MAX28V)) / (uint16)ADC2_FILTOUT_MAX) / (uint8)VS_ATTEN_CONV_DENOM_MAX28V);
  }
  else
  {
    /* Conversion for VS attenuator range up to 22 V */
    value = (uint16)(((value * (uint32)((uint16)ADC2_VREF_mV * (uint16)VS_ATTEN_CONV_NOMIN_MAX22V)) / (uint16)ADC2_FILTOUT_MAX) / (uint8)VS_ATTEN_CONV_DENOM_MAX22V);
  }

  return (value);
}
/** \brief returns the Voltage of the VSD line (ADC2 Channel 2) in millivolt
 * \brief calculated based on attenuator conversion factor as follows:
 * \brief \n \n \f$ Voltage(mV) = \frac{ADC2.Digital.Result(bit)*(V_{BG}*1000)(mV)}{ADC2.Max.Digital.Value(bit)}*\frac{1000}{39}\f$
 *
 * \return Voltage of the VSD line (ADC2 Channel 2) in millivolt
 *
 * \brief <b>Example</b><br>
 * \brief This example returns the specified value./
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 data;
 *
 *     data = ADC2_VSD_Result_mV();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE uint16 ADC2_VSD_Result_mV(void)
{
  uint16 value;
  value = ADC2_GetChResult(ADC2_VSD);
  /* Conversion for VSD attenuator (attenuator 0.039 = 39/1000) */
  value = (uint16)(((value * (uint32)((uint16)ADC2_VREF_mV * (uint16)VSD_ATTEN_CONV_NOMIN)) / (uint16)ADC2_FILTOUT_MAX) / (uint8)VSD_ATTEN_CONV_DENOM);
  return (value);
}
/** \brief returns the Voltage of the VCP line (ADC2 Channel 3) in millivolt (mV)
 * \brief calculated based on attenuator conversion factor as follows:
 * \brief \n \n \f$ Voltage(mV) = \frac{ADC2.Digital.Result(bit)*(V_{BG}*1000)(mV)}{ADC2.Max.Digital.Value(bit)}*\frac{1000}{23}\f$
 *
 * \return Voltage of the VCP line (ADC2 Channel 3) in millivolt (mV)
 *
 * \brief <b>Example</b><br>
 * \brief This example returns the specified value./
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 data;
 *
 *     data = ADC2_VCP_Result_mV();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE uint16 ADC2_VCP_Result_mV(void)
{
  uint16 value;
  value = ADC2_GetChResult((uint8)ADC2_VCP);
  /* Conversion for VCP attenuator (attenuator 0.023 = 23/1000) */
  value = (uint16)(((value * ((uint32)ADC2_VREF_mV * (uint16)VCP_ATTEN_CONV_NOMIN)) / (uint16)ADC2_FILTOUT_MAX) / (uint8)VCP_ATTEN_CONV_DENOM);
  return (value);
}

/** \brief returns the Voltage of the MON line (ADC2 Channel 4) in millivolt (mV)
 * \brief calculated based on attenuator conversion factor as follows:
 * \brief \n \n \f$ Voltage(mV) = \frac{ADC2.Digital.Result(bit)*(V_{BG}*1000)(mV)}{ADC2.Max.Digital.Value(bit)}*\frac{1000}{39}\f$
 *
 * \return Voltage of the MON line (ADC2 Channel 4) in millivolt (mV)
 *
 * \brief <b>Example</b><br>
 * \brief This example returns the specified value./
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 data;
 *
 *     data = ADC2_MON_Result_mV();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE uint16 ADC2_MON_Result_mV(void)
{
  uint16 value;
  value = ADC2_GetChResult((uint8)ADC2_MON);
  /* Conversion for MON attenuator (attenuator 0.039 = 39/1000) */
  value = (uint16)(((value * ((uint32)ADC2_VREF_mV * (uint16)MON_ATTEN_CONV_NOMIN)) / (uint16)ADC2_FILTOUT_MAX) / (uint8)MON_ATTEN_CONV_DENOM);
  return (value);
}

/** \brief returns the Voltage of the VDDP line (ADC2 Channel 5) in millivolt (mV)
 * \brief calculated based on attenuator conversion factor as follows:
 * \brief \n \n \f$ Voltage(mV) = \frac{ADC2.Digital.Result(bit)*(V_{BG}*1000)(mV)}{ADC2.Max.Digital.Value(bit)}*\frac{250}{41}\f$
 *
 * \return Voltage of the VDDP line (ADC2 Channel 5) in millivolt (mV)
 *
 * \brief <b>Example</b><br>
 * \brief This example returns the specified value./
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 data;
 *
 *     data = ADC2_VDDP_Result_mV();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE uint16 ADC2_VDDP_Result_mV(void)
{
  uint16 value;
  value = ADC2_GetChResult((uint8)ADC2_VDDP);
  /* Conversion for VDDP attenuator (attenuator 0.164 = 41/250) */
  value = (uint16)(((value * ((uint32)ADC2_VREF_mV * (uint16)VDDP_ATTEN_CONV_NOMIN)) / (uint16)ADC2_FILTOUT_MAX) / (uint8)VDDP_ATTEN_CONV_DENOM);
  return (value);
}

/** \brief returns the Voltage of the VAREF line (ADC2 Channel 6) in millivolt (mV)
 * \brief calculated based on attenuator conversion factor as follows:
 * \brief \n \n \f$ Voltage(mV) = \frac{ADC2.Digital.Result(bit)*(V_{BG}*1000)(mV)}{ADC2.Max.Digital.Value(bit)}*\frac{1000}{219}\f$
 *
 * \return Voltage of the VAREF line (ADC2 Channel 6) in millivolt (mV)
 *
 * \brief <b>Example</b><br>
 * \brief This example returns the specified value./
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 data;
 *
 *     data = ADC2_VAREF_Result_mV();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE uint16 ADC2_VAREF_Result_mV(void)
{
  uint16 value;
  value = ADC2_GetChResult((uint8)ADC2_VAREF);
  /* Conversion for VAREF attenuator (attenuator 0.219 = 219/1000) */
  value = (uint16)(((value * ((uint32)ADC2_VREF_mV * (uint16)VAREF_ATTEN_CONV_NOMIN)) / (uint16)ADC2_FILTOUT_MAX) / (uint8)VAREF_ATTEN_CONV_DENOM);
  return (value);
}

/** \brief returns the Voltage of the VBG line (ADC2 Channel 7) in millivolt (mV)
 * \brief calculated based on attenuator conversion factor as follows:
 * \brief \n \n \f$ Voltage(mV) = \frac{ADC2.Digital.Result(bit)*(V_{BG}*1000)(mV)}{ADC2.Max.Digital.Value(bit)}*\frac{4}{3}\f$
 *
 * \return Voltage of the VBG line (ADC2 Channel 7) in millivolt (mV)
 *
 * \brief <b>Example</b><br>
 * \brief This example returns the specified value./
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 data;
 *
 *     data = ADC2_VBG_Result_mV();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE uint16 ADC2_VBG_Result_mV(void)
{
  uint16 value;
  value = ADC2_GetChResult((uint8)ADC2_VBG);
  /* Conversion for VBG attenuator (attenuator 0.75 = 3/4) */
  value = (uint16)(((value * ((uint32)ADC2_VREF_mV * (uint16)VBG_ATTEN_CONV_NOMIN)) / (uint16)ADC2_FILTOUT_MAX) / (uint8)VBG_ATTEN_CONV_DENOM);
  return (value);
}

/** \brief returns the Voltage of the VDDC line (ADC2 Channel 8) in millivolt (mV)
 * \brief calculated based on attenuator conversion factor as follows:
 * \brief \n \n \f$ Voltage(mV) = \frac{ADC2.Digital.Result(bit)*(V_{BG}*1000)(mV)}{ADC2.Max.Digital.Value(bit)}*\frac{4}{3}\f$
 *
 * \return Voltage of the VDDC line (ADC2 Channel 8) in millivolt (mV)
 *
 * \brief <b>Example</b><br>
 * \brief This example returns the specified value./
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 data;
 *
 *     data = ADC2_VDDC_Result_mV();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE uint16 ADC2_VDDC_Result_mV(void)
{
  uint16 value;
  value = ADC2_GetChResult((uint8)ADC2_VDDC);
  /* Conversion for VDDC attenuator (attenuator 0.75 = 3/4) */
  value = (uint16)(((value * ((uint32)ADC2_VREF_mV * (uint16)VDDC_ATTEN_CONV_NOMIN)) / (uint16)ADC2_FILTOUT_MAX) / (uint8)VDDC_ATTEN_CONV_DENOM);
  return (value);
}

/** \brief Returns the Temperature read by the ADC2 Channel 9 in degrees Celsius (&deg;C).
 * \brief \f$ Temp(&deg;C) = \frac{V_{Temp}(mV)-666(mV)}{2.31\frac{(mV)}{(&deg;C)}}\f$
 * \brief \n where
 * \brief \n \f$ V_{Temp}(mV) = \frac{ADC2.Digital.Result(bit)*(V_{BG}*1000)(mV)}{ADC2.Max.Digital.Value(bit)}\f$
 *
 * \return Temperature read by the ADC2 Channel 9 in degrees Celsius (&deg;C).
 *
 * \brief <b>Example</b><br>
 * \brief This example returns the specified value./
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     sint16 data;
 *
 *     data = ADC2_Temp_Result_C();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE sint16 ADC2_Temp_Result_C(void)
{
  uint16 value;
  uint16 V_Temp_mV;
  sint16 Temperature;
  value = ADC2_GetChResult((uint8)ADC2_TEMP);
  /* Conversion for Temperature in deg C:
  Step 1: Calculate V_Temp(T)(mV): */
  V_Temp_mV = (uint16)(((uint32)value * (uint32)ADC2_VREF_mV) / (uint16)1023);
  /* Step 2: Conversion from V_Temp(T)(mV) to Temperature in deg C  */
  Temperature = (sint16)((((sint16)V_Temp_mV - (sint16)V_TEMP_REF_OFFSET_mV) * (sint16)V_TEMP_SCALE_FACT) / (sint16)CONV_COEFF_mV_TO_degC);
  /* return the calculated Temperature in deg C */
  return (Temperature);
}

#endif
