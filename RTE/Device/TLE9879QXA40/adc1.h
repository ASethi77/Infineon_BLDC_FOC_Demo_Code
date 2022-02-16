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
 * \file     adc1.h
 *
 * \brief    ADC1 low level access library
 *
 * \version  V0.2.8
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
** V0.1.1: 2015-02-10, DM:   Individual header file added                     **
** V0.1.2: 2015-03-10, DM:   MF->REF2_CTRL added                              **
** V0.1.3: 2015-03-22, DM:   ADC Busy function added                          **
** V0.1.4: 2015-11-26, DM:   VAREF enable function added                      **
** V0.1.5: 2017-02-16, DM:   the attenuator for Channel 6 (VDH) voltage       **
**                           calculation added                                **
**                           Adc1 prefix changed to ADC1                      **
** V0.1.6: 2017-03-23, DM:   ADC1 API extended                                **
** V0.1.7: 2017-11-09, DM:   Port2 analog input init added                    **
** V0.1.8: 2017-11-13, DM:   MISRA 2012 compliance, the following PC-Lint     **
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
** V0.1.9: 2018-03-14, DM:   VAREF_Enable() reworked for MISRA 2012           **
**                           ADC1_MASK_CHx macros rworked for MISRA 2012      **
**                           ADC1_ANON_Sts() converted to infline function    **
**                           due to MISRA 2012                                **
** V0.2.0: 2018-06-27, DCM:  Conversion formula from digital value to         **
**                           millivolts changed based on the software unit    **
**                           test findings and simplified according to the    **
**                           new specifications                               **
** V0.2.1: 2018-07-05, BG:   In adc1.h: ADC1_Chx_Result_Get(),                **
**                           ADC1_EIM_Channel_Set(uint32),                    **
**                           ADC1_SW_Ch_Sel(uint32), ADC1_SOC_Set(),          **
**                           ADC1_ANON_Set(uint32), ADC1_Power_On(),          **
**                           ADC1_EOC_Sts(), ADC1_Busy_Sts(),                 **
**                           ADC1_EIM_Active_Sts(), ADC1_ESM_Active_Sts()     **
**                           reworked for testing lv2 functions               **
** V0.2.2: 2018-08-01, DM:   DoxyGen comments updated,                        **
** V0.2.3: 2018-11-09, JO:   Renamed:                                         **
**                           - ADC1_VDH_Attenuator_Range_0_22V_Set to         **
**                             ADC1_VDH_Attenuator_Range_0_20V_Set            **
**                           - ADC1_VDH_Attenuator_Range_0_28V_Set to         **
**                             ADC1_VDH_Attenuator_Range_0_30V_Set            **
**                           - ADC1_VDH_Attenuator_Range_0_22V to             **
**                             ADC1_VDH_Attenuator_Range_0_20V                **
**                           - ADC1_VDH_Attenuator_Range_0_28V to             **
**                             ADC1_VDH_Attenuator_Range_0_30V                **
** V0.2.4: 2018-11-27, JO:   Moved revision history from adc1.c to adc1.h     **
** V0.2.5: 2020-04-15, BG:   Updated revision history format                  **
** V0.2.6: 2020-07-13, JO:   EP-431: remove ARMCC v6 Compiler warnings        **
**                           - Added typecasts to remove 'implicit typecast'  **
**                             warning                                        **
** V0.2.7: 2020-07-21, BG:   EP-439: Formatted .h/.c files                    **
** V0.2.8: 2021-04-23, BG:   EP-726: Corrected MISRA 2012 violations          **
*******************************************************************************/

#ifndef ADC1_H
#define ADC1_H

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "tle987x.h"
#include "types.h"
#include "adc1_defines.h"
#include "sfr_access.h"

/*******************************************************************************
**                        Global Constant Declarations                        **
*******************************************************************************/

/**\brief ADC1 VDH Attenuator Selection, 0V..30V */
#define ADC1_VDH_Attenuator_Range_0_30V (1u)
/**\brief ADC1 VDH Attenuator Selection, 0V..20V */
#define ADC1_VDH_Attenuator_Range_0_20V (0u)

/**\brief ADC1 Mode Selection, Software Mode */
#define SW_MODE    0u
/**\brief Mode Selection, Sequencer Mode */
#define SEQ_MODE  1u

/**\brief ADC1 Sequencer Configuration, skip channel measurement */
#define SKIP    0u
/**\brief Sequencer Configuration, perform channel measurement */
#define MEAS      1u

/**\brief ADC1 conversion data width selection, 10 bit conversion */
#define BIT10     0u
/**\brief ADC1 conversion data width selection, 8 bit conversion */
#define BIT8      1u

/**\brief ADC1 Interrupt, Disable*/
#define INTDIS    0u
/**\brief ADC1 Interrupt, Enable*/
#define INTEN     1u

/**\brief ADC1 Result Register, Overwrite Mode*/
#define OVERWRITE 0u
/**\brief ADC1 Result Register, Wait For Read Mode*/
#define WFR       1u

/**\brief ADC1 channel selection macro, channel 0 - P2.0 */
#define ADC1_CH0  (0)
/**\brief ADC1 channel selection macro, channel 1 - Current Sense Amplifier */
#define ADC1_CH1  (1)
/**\brief ADC1 channel selection macro, channel 2 - P2.2 */
#define ADC1_CH2  (2)
/**\brief ADC1 channel selection macro, channel 3 - P2.3 */
#define ADC1_CH3  (3)
/**\brief ADC1 channel selection macro, channel 4 - P2.4 */
#define ADC1_CH4  (4)
/**\brief ADC1 channel selection macro, channel 5 - P2.5 */
#define ADC1_CH5  (5)
/**\brief ADC1 channel selection macro, channel 6 - P2.6 */
#define ADC1_CH6  (6)
/**\brief ADC1 channel selection macro, Exceptional Interrupt Measurement - EIM */
#define ADC1_EIM  (8)

/**\brief ADC1 channel selection macro, channel 0 - P2.0 */
#define ADC1_P20  ADC1_CH0
/**\brief ADC1 channel selection macro, channel 1 - Current Sense Amplifier */
#define ADC1_CSA  ADC1_CH1
/**\brief ADC1 channel selection macro, channel 2 - P2.2 */
#define ADC1_P22  ADC1_CH2
/**\brief ADC1 channel selection macro, channel 3 - P2.3 */
#define ADC1_P23  ADC1_CH3
/**\brief ADC1 channel selection macro, channel 4 - P2.4 */
#define ADC1_P24  ADC1_CH4
/**\brief ADC1 channel selection macro, channel 5 - P2.5 */
#define ADC1_P25  ADC1_CH5
/**\brief ADC1 channel selection macro, channel 6 - P2.6 */
#define ADC1_VDH  ADC1_CH6

/* ESM Channel */
/**\brief ADC1 Sequencer/ESM channel selection macro, channel 0 - P2.0 */
#define ADC1_MASK_CH0 ((uint32)1u << ADC1_CH0)
/**\brief ADC1 Sequencer/ESM channel selection macro, channel 1 - CSA */
#define ADC1_MASK_CH1 ((uint32)1u << ADC1_CH1)
/**\brief ADC1 Sequencer/ESM channel selection macro, channel 2 - P2.2 */
#define ADC1_MASK_CH2 ((uint32)1u << ADC1_CH2)
/**\brief ADC1 Sequencer/ESM channel selection macro, channel 3 - P2.3 */
#define ADC1_MASK_CH3 ((uint32)1u << ADC1_CH3)
/**\brief ADC1 Sequencer/ESM channel selection macro, channel 4 - P2.4 */
#define ADC1_MASK_CH4 ((uint32)1u << ADC1_CH4)
/**\brief ADC1 Sequencer/ESM channel selection macro, channel 5 - P2.5 */
#define ADC1_MASK_CH5 ((uint32)1u << ADC1_CH5)
/**\brief ADC1 Sequencer/ESM channel selection macro, channel 6 - P2.6 */
#define ADC1_MASK_CH6 ((uint32)1u << ADC1_CH6)

/**\brief ADC1 Sequencer/ESM channel selection macro, channel 0 - P2.0 */
#define ADC1_MASK_P20 (ADC1_MASK_CH0)
/**\brief ADC1 Sequencer/ESM channel selection macro, channel 1 - CSA */
#define ADC1_MASK_CSA (ADC1_MASK_CH1)
/**\brief ADC1 Sequencer/ESM channel selection macro, channel 2 - P2.2 */
#define ADC1_MASK_P22 (ADC1_MASK_CH2)
/**\brief ADC1 Sequencer/ESM channel selection macro, channel 3 - P2.3 */
#define ADC1_MASK_P23 (ADC1_MASK_CH3)
/**\brief ADC1 Sequencer/ESM channel selection macro, channel 4 - P2.4 */
#define ADC1_MASK_P24 (ADC1_MASK_CH4)
/**\brief ADC1 Sequencer/ESM channel selection macro, channel 5 - P2.5 */
#define ADC1_MASK_P25 (ADC1_MASK_CH5)
/**\brief ADC1 Sequencer/ESM channel selection macro, channel 6 - P2.6 */
#define ADC1_MASK_VDH (ADC1_MASK_CH6)

/**\brief ADC1 reference voltage 5.0V */
#define ADC1_VREF_5000mV 5000u
/**\brief ADC1 virtual reference voltage 22.0V for VDH Attenuator Range 0-22V */
#define ADC1_VREF_22000mV 22000u
/**\brief ADC1 virtual reference voltage 30.0V for VDH Attenuator Range 0-30V */
#define ADC1_VREF_30000mV 30000u

/*******************************************************************************
** ADC1 Analog Module select enum                                             **
*******************************************************************************/
/** \enum TADC1_ANON
 *  \brief This enum lists the options for the Analog Module
 */
typedef enum
{
  ADC1_ANON_OFF       = 0, /**< ADC1 Analog Module Mode - Off Mode */
  ADC1_ANON_S_STANDBY = 1, /**< ADC1 Analog Module Mode - Slow Standby Mode */
  ADC1_ANON_F_STANDBY = 2, /**< ADC1 Analog Module Mode - Fast Standby Mode */
  ADC1_ANON_NORMAL    = 3  /**< ADC1 Analog Module Mode - Normal Mode (On-Mode) */
} TADC1_ANON;

typedef union
{
  uint32 dword;
  TADC1_ANON  adc1_anon;
} TADC1_ANON_U;

/*******************************************************************************
** ADC1 trigger select enum                                                   **
*******************************************************************************/
/** \enum TADC1_TRIGG_SEL
 *  \brief This enum lists the options for the trigger select for EIM and ESM
 */
typedef enum
{
  ADC1_Trigg_None      = 0, /**< no trigger source connected */
  ADC1_Trigg_CCU6_Ch3  = 1, /**< CCU6 Channel 3 (COUT63), rising edge */
  ADC1_Trigg_GPT12E_T6 = 2, /**< GPT12E Timer6, T6OUT */
  ADC1_Trigg_GPT12E_T3 = 3, /**< GPT12E Timer6, T3OUT */
  ADC1_Trigg_Timer2    = 4, /**< Timer2 output */
  ADC1_Trigg_Timer21   = 5, /**< Timer21 output */
  ADC1_Trigg_Timer3    = 6  /**< Timer3 output */
} TADC1_TRIGG_SEL;

/*******************************************************************************
** ADC1 EIM repeat count enum                                                 **
*******************************************************************************/
/** \enum TADC1_EIM_REP_CNT
 *  \brief This enum lists the options for the EIM repeat count setting
 *  \brief The number of measurements to be done until EIM interrupt is requested.
 */
typedef enum
{
  ADC1_1_Meas   = 0, /**< EIM irq every measurement */
  ADC1_2_Meas   = 1, /**< EIM irq every 2nd measurement */
  ADC1_4_Meas   = 2, /**< EIM irq every 4th measurement */
  ADC1_8_Meas   = 3, /**< EIM irq every 8th measurement */
  ADC1_16_Meas  = 4, /**< EIM irq every 16th measurement */
  ADC1_32_Meas  = 5, /**< EIM irq every 32nd measurement */
  ADC1_64_Meas  = 6, /**< EIM irq every 64th measurement */
  ADC1_128_Meas = 7  /**< EIM irq every 128th measurement */
} TADC1_EIM_REP_CNT;

/*******************************************************************************
**                        Global Function Declarations                        **
*******************************************************************************/

/******************************************************************************/
/** \brief Initializes the ADC1 based on the IFXConfigWizard configuration
 *
 * \ingroup ADC1_api
 */
void ADC1_Init(void);


/** \brief Re-enables the internal VAREF LDO in case it was shutdown due to a previous failure.
 *
 * \retval true VAREF enabled
 * \retval false VAREF enabling failed
 *
 * \brief <b>Example</b><br>
 * \brief This example checks if the internal VAREF LDO is re-enabling.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     while(VAREF_Enable() == false)
 *     {
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
bool VAREF_Enable(void);


/** \brief Get the 10-bit/8-bit value of the ADC1 Result Register of the selected ADC1 channel and returns the validity info
 *  \note This function violates [MISRA Rule 45]
 *
 * \param channel channel number (defined in adc1.h)
 * \param[out] *pVar 10-bit ADC1 Result Value of the selected "channel number" (in case the Data Width is set to 8-bit, then the 8-bit value is left aligned in 10-bit *pVar)
 * \retval true : the value of *pVar is valid (ValidFlag bit is set)
 * \retval false : the value of *pVar is invalid (ValidFlag bit is reset)
 *
 * \brief <b>Example</b><br>
 * \brief This example returns the ADC1 Channel 5 result in Millivolt (mV).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     bool value_valid;
 *     uint16 var_mV;
 *     uint16 var;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     if (ADC1_GetChResult(&var, ADC1_CH5) == true)
 *     {
 *       value_valid = ADC1_GetChResult_mV(&var_mV, ADC1_CH5);
 *     }
 *
 *     return(value_valid);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
bool ADC1_GetChResult(uint16 *pVar, uint8 channel);


/** \brief Get the value of the ADC1 Result Register of the selected ADC1 channel in Millivolt (mV) and returns the validity info
 *
 * \param channel channel number(defined in adc1.h)
 * \param[out] *pVar_mV ADC1 Result Register value of the selected channel number converted to Millivolt (mV)
 * \retval true : the value of *pVar_mV is valid
 * \retval false : the value of *pVar_mV is invalid
 *
 * \brief <b>Example</b><br>
 * \brief This example returns the ADC1 Channel 5 result in Millivolt (mV).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     bool value_valid;
 *     uint16 var_mV;
 *     uint16 var;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     if (ADC1_GetChResult(&var, ADC1_CH5) == true)
 *     {
 *       value_valid = ADC1_GetChResult_mV(&var_mV, ADC1_CH5);
 *     }
 *
 *     return(value_valid);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
bool ADC1_GetChResult_mV(uint16 *pVar_mV, uint8 channel);


/** \brief Get the 10-bit/8-bit value of the ADC1 EIM Result Register and returns the validity info
 *
 * \param[out] *pVar : 10-bit ADC1 EIM Result Value (in case the Data Width is set to 8-bit, then the 8-bit value is left aligned in 10-bit *pVar)
 * \retval true : the value of *pVar is valid (ValidFlag bit is set)
 * \retval false : the value of *pVar is invalid (ValidFlag bit is reset)
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, programs channel 2 (P2.2) and reads the result value in mV.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     bool value_valid;
 *     uint16 var_mV;
 *     uint16 var;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_SetEIMChannel( ADC1_P22 );
 *     if (ADC1_GetEIMResult(&var) == true)
 *     {
 *       value_valid = ADC1_GetEIMResult_mV(&var_mV);
 *     }
 *
 *     return(value_valid);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
bool ADC1_GetEIMResult(uint16 *pVar);


/** \brief Get the value of the ADC1 EIM Result Register in Millivolt (mV) and returns the validity info
 *
 * \param[out] *pVar_mV ADC1 EIM Result Register value converted to Millivolt (mV)
 * \retval true : the value of *pVar_mV is valid
 * \retval false : the value of *pVar_mV is invalid
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, programs channel 2 (P2.2) and reads the result value in mV.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     bool value_valid;
 *     uint16 var_mV;
 *     uint16 var;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_SetEIMChannel( ADC1_P22 );
 *     if (ADC1_GetEIMResult(&var) == true)
 *     {
 *       value_valid = ADC1_GetEIMResult_mV(&var_mV);
 *     }
 *
 *     return(value_valid);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
bool ADC1_GetEIMResult_mV(uint16 *pVar_mV);


/** \brief Set(Change) ADC1 EIM channel
 *
 * \param channel channel number to be converted
 * \return void
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, programs channel 2 (P2.2) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_SetEIMChannel( ADC1_P22 );
 *
 *     while (ADC1->FILT_OUTEIM.bit.VF_EIM == 0u)
 *     {
 *     }
 *
 *     adc_result = ADC1_EIM_Result_Get();
 *
 *     return(adc_result);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_SetEIMChannel(uint8 channel);


/** \brief Selects a channel for the software conversion.
 *
 * \param channel channel which should be measured
 *
 * \brief <b>Example</b><br>
 * \brief This example starts an ADC1 conversion on channel 1 - CSA.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_SetSwMode_Channel(ADC1_CSA);
 *     ADC1_SOC_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_SetSwMode_Channel(uint8 channel);


/** \brief Start ADC1 conversion mode selection
 *
 * \param mode Sequencer mode, Software mode
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Software Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_SetMode(SW_MODE);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_SetMode(uint8 mode);


/** \brief Starts ADC1 software mode conversion
 *
 * \param Ch Channel to be converted
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC and starts SW_MODE conversion for channel 0.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_SetSocSwMode(ADC1_P20);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_SetSocSwMode(uint8 Ch);


/** \brief Get ADC1 end of conversion status
 *
 * \retval true conversion done
 * \retval false conversion ongoing
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Software Mode, starts a measurement and waits for it to be finished.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Software_Mode_Sel();
 *     ADC1_SW_Ch_Sel( ADC1_P20 );
 *     ADC1_SOS_Set();
 *
 *     while ( ADC1_GetEocSwMode() == false ) {}
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE bool ADC1_GetEocSwMode(void);


/** \brief Get ADC1 latest software mode result
 *
 * \param[out] *pVar result for the recent software mode conversion
 * \retval true *pVar valid
 * \retval false *pVar invalid
 *
 * \brief <b>Example</b><br>
 * \brief This example returns the ADC1 latest software mode result in Millivolt (mV).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     bool value_valid;
 *     uint16 var_mV;
 *     uint16 var;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Software_Mode_Sel();
 *     ADC1_SW_Ch_Sel( ADC1_P20 );
 *     if (ADC1_GetSwModeResult(&var) == true)
 *     {
 *       value_valid = ADC1_GetSwModeResult_mV(&var_mV);
 *     }
 *
 *     return(value_valid);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE bool ADC1_GetSwModeResult(uint16 *pVar);


/** \brief Get ADC1 software mode result in Millivolt
 *
 * \param[out] *pVar_mV ADC value in mV of the recent conversion
 * \retval true pVar_mV valid
 * \retval false pVar_mV invalid
 *
 * \brief <b>Example</b><br>
 * \brief This example returns the ADC1 latest software mode result in Millivolt (mV).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     bool value_valid;
 *     uint16 var_mV;
 *     uint16 var;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Software_Mode_Sel();
 *     ADC1_SW_Ch_Sel( ADC1_P20 );
 *     if (ADC1_GetSwModeResult(&var) == true)
 *     {
 *       value_valid = ADC1_GetSwModeResult_mV(&var_mV);
 *     }
 *
 *     return(value_valid);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE bool ADC1_GetSwModeResult_mV(uint16 *pVar_mV);


/** \brief Reads the overall status of the ADC1.
 *
 * \retval true ADC1 busy
 * \retval false ADC1 ready
 *
 * \brief <b>Example</b><br>
 * \brief This example reads the busy status of the ADC1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Software_Mode_Sel();
 *     ADC1_SW_Ch_Sel( ADC1_CSA );
 *     ADC1_SOC_Set();
 *
 *     while ( ADC1_Busy() == true )
 *     {
 *       //ADC1 still busy
 *     }
 *
 *     while ( ADC1_EOC_Sts() != 1u ) {}
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE bool ADC1_Busy(void);


/** \brief Get ADC1 EIM Trigger Selection
 *
 * \param trigsel Trigger select, TADC1_TRIGG_SEL
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and configures EIM Trigger Selection as Timer2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_EIM_Trigger_Select(ADC1_Trigg_Timer2);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_EIM_Trigger_Select(TADC1_TRIGG_SEL trigsel);


/** \brief Set ADC1 EIM Repeat Counter
 *
 * \param repcnt repeat counter for EIM measurement, \link TADC1_EIM_REP_CNT \endlink
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and configures EIM Repeat Counter as 4 Measures.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_EIM_Repeat_Counter_Set(ADC1_4_Meas);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_EIM_Repeat_Counter_Set(TADC1_EIM_REP_CNT repcnt);


/** \brief Set ADC1 ESM Trigger Selection
 *
 * \param trigsel Trigger select, \link TADC1_TRIGG_SEL \endlink
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and configures ESM Trigger Selection as Timer2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_ESM_Trigger_Select(ADC1_Trigg_Timer2);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_ESM_Trigger_Select(TADC1_TRIGG_SEL trigsel);


/** \brief checks EndOfConversion ready (Software Mode)
 *
 * \retval true conversion done
 * \retval false conversion ongoing
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Software Mode and checks if EndOfConversion is ready.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Software_Mode_Sel();
 *     ADC1_SW_Ch_Sel( ADC1_CSA );
 *     ADC1_SOS_Set();
 *
 *     while ( ADC1_isEndOfConversion() == false ) {}
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE bool ADC1_isEndOfConversion(void);


/** \brief checks Exceptional Interrupt Mode active
 *
 * \retval true EIM mode is active
 * \retval false EIM mode is not active
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode and checks if the Exceptional Interrupt Measurement (EIM) is active.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_EIM_Channel_Set( ADC1_CH2 );
 *
 *     while (ADC1_isEIMactive() == false)
 *     {
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE bool ADC1_isEIMactive(void);


/** \brief checks Exceptional Sequencer Mode active
 *
 * \retval true ESM mode is active
 * \retval false ESM mode is not active
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode and checks if Exceptional Sequencer Measurement (ESM) is ready.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_ESM_Channel_Set( ADC1_CH2 );
 *
 *     while (ADC1_isESMactive() == false)
 *     {
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE bool ADC1_isESMactive(void);


/** \brief Reads the Analog Part Switched On Mode status.
 *
 * \return TADC1_ANON, see \link TADC1_ANON \endlink
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and waits until ADC1 has reached normal mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *
 *     while ( ADC1_ANON_Sts() != ADC1_ANON_NORMAL ) {}
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE TADC1_ANON ADC1_ANON_Sts(void);


/*******************************************************************************
**                     Global Inline Function Definitions                     **
*******************************************************************************/
/** \brief Enables the ADC1 module.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables the ADC1 module.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Power_On(void)
{
  Field_Mod32(&ADC1->CTRL_STS.reg, ADC1_CTRL_STS_PD_N_Pos, ADC1_CTRL_STS_PD_N_Msk, 1u);
}

/** \brief Disables the ADC1 module.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables the ADC1 module.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_Off();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Power_Off(void)
{
  Field_Mod32(&ADC1->CTRL_STS.reg, ADC1_CTRL_STS_PD_N_Pos, ADC1_CTRL_STS_PD_N_Msk, 0u);
}

/** \brief ADC1 Start of Conversion, for Software mode only.
 *
 * \brief <b>Example</b><br>
 * \brief This example starts an ADC1 conversion.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_SOC_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_SOC_Set(void)
{
  Field_Mod32(&ADC1->CTRL_STS.reg, ADC1_CTRL_STS_SOC_Pos, ADC1_CTRL_STS_SOC_Msk, 1u);
}

/** \brief Selects a channel for the software conversion.
 *
 * \param a channel which should be measured
 *
 * \brief <b>Example</b><br>
 * \brief This example starts an ADC1 conversion on channel 1 - CSA.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_SW_Ch_Sel(ADC1_CSA);
 *     ADC1_SOC_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_SW_Ch_Sel(uint32 a)
{
  Field_Mod32(&ADC1->CTRL_STS.reg, ADC1_CTRL_STS_IN_MUX_SEL_Pos, ADC1_CTRL_STS_IN_MUX_SEL_Msk, a);
}

/** \brief ADC1 analog clock divider. \f$f_{ADC1} = \frac{f_{SYS}}{DIVA}\f$.
 *
 * \param a division factor, values between 0..63 are allowed, resulting in a divider of DIVA = 1..64
 *
 * \brief <b>Example</b><br>
 * \brief This example sets the fADC1 to half of fSYS.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     //fADC1 = fSYS / 2
 *     ADC1_DIVA_Set( 1 );
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_DIVA_Set(uint32 a)
{
  Field_Mod32(&ADC1->GLOBCTR.reg, ADC1_GLOBCTR_DIVA_Pos, ADC1_GLOBCTR_DIVA_Msk, a);
}

/** \brief ADC1 set the Analog Module Mode.
 *
 * \param a analog module mode, see \link TADC1_ANON \endlink
 *
 * \brief <b>Example</b><br>
 * \brief This example sets the ADC1 to normal mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_ANON_Set(uint32 a)
{
  Field_Mod32(&ADC1->GLOBCTR.reg, ADC1_GLOBCTR_ANON_Pos, ADC1_GLOBCTR_ANON_Msk, a);
}

/** \brief ADC1 selects the Sequencer Mode.
 * \note EIM/ESM measurements are only possible in Sequencer mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Sequencer_Mode_Sel(void)
{
  Field_Mod32(&ADC1->SQ_FB.reg, ADC1_SQ_FB_SQ_RUN_Pos, ADC1_SQ_FB_SQ_RUN_Msk, 1u);
}

/** \brief ADC1 selects the Software Mode, measurements are performed on user request.
 * \note EIM/ESM measurements are only possible in \link ADC1_Sequencer_Mode_Sel \endlink.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Software Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Software_Mode_Sel();
 *     ADC1_SW_Ch_Sel( ADC1_CSA );
 *     ADC1_SOC_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Software_Mode_Sel(void)
{
  Field_Mod32(&ADC1->SQ_FB.reg, ADC1_SQ_FB_SQ_RUN_Pos, ADC1_SQ_FB_SQ_RUN_Msk, 0u);
}

/** \brief Reads the End-of-Conversion status.
 *
 * \retval 1 if conversion has ended
 * \retval 0 if conversion still ongoing
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Software Mode, starts a measurement and waits for it to be finished.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Software_Mode_Sel();
 *     ADC1_SW_Ch_Sel( ADC1_CSA );
 *     ADC1_SOC_Set();
 *
 *     while ( ADC1_EOC_Sts() != 1u ) {}
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint8 ADC1_EOC_Sts(void)
{
  return ( u1_Field_Rd32(&ADC1->CTRL_STS.reg, ADC1_CTRL_STS_EOC_Pos, ADC1_CTRL_STS_EOC_Msk) );
}

/** \brief Reads the channel for currently ongoing conversion, if no conversion is ongoing, then it returns the channel of the last conversion.
 *
 * \return uint8, channel number
 *
 * \brief <b>Example</b><br>
 * \brief This example reads the current channel number into 'ch_no'.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch_no;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Software_Mode_Sel();
 *     ADC1_SW_Ch_Sel( ADC1_CSA );
 *     ADC1_SOC_Set();
 *
 *     ch_no = ADC1_Current_Ch_Sts();
 *
 *     while ( ADC1_EOC_Sts() != 1u ) {}
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint8 ADC1_Current_Ch_Sts(void)
{
  return ( u8_Field_Rd32(&ADC1->GLOBSTR.reg, ADC1_GLOBSTR_CHNR_Pos, ADC1_GLOBSTR_CHNR_Msk) );
}

/** \brief Reads the sample status of a ongoing measurement.
 * \brief During the sample phase of a measurement the signal should not change. The sampling time can be set by ADC1_ChX_Sample_Time_Set(), i.e. \link ADC1_Ch0_Sample_Time_Set \endlink
 *
 * \retval 1 sampling phase ongoing
 * \retval 0 sampling phase done, or no measurement ongoing
 *
 * \brief <b>Example</b><br>
 * \brief This example reads the sample status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Software_Mode_Sel();
 *     ADC1_SW_Ch_Sel( ADC1_CSA );
 *     ADC1_SOC_Set();
 *
 *     while ( ADC1_Sample_Sts() == 1u )
 *     {
 *       //sampling ongoing
 *     }
 *
 *     while ( ADC1_EOC_Sts() != 1u ) {}
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint8 ADC1_Sample_Sts(void)
{
  return ( u1_Field_Rd32(&ADC1->GLOBSTR.reg, ADC1_GLOBSTR_SAMPLE_Pos, ADC1_GLOBSTR_SAMPLE_Msk) );
}

/** \brief Reads the overall status of the ADC1.
 *
 * \retval 1 if ADC1 busy
 * \retval 0 if ADC1 ready
 *
 * \brief <b>Example</b><br>
 * \brief This example reads the busy status of the ADC1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Software_Mode_Sel();
 *     ADC1_SW_Ch_Sel( ADC1_CSA );
 *     ADC1_SOC_Set();
 *
 *     while ( ADC1_Busy_Sts() == 1u )
 *     {
 *       //ADC1 still busy
 *     }
 *
 *     while ( ADC1_EOC_Sts() != 1u ) {}
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint8 ADC1_Busy_Sts(void)
{
  return ( u1_Field_Rd32(&ADC1->GLOBSTR.reg, ADC1_GLOBSTR_BUSY_Pos, ADC1_GLOBSTR_BUSY_Msk) );
}

/** \brief Reads the active status of the Exceptional Interrupt Measurement (EIM).
 *
 * \retval 1 EIM ongoing
 * \retval 0 no EIM active
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode and reads the active status of the Exceptional Interrupt Measurement (EIM).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_EIM_Channel_Set( ADC1_P22 );
 *
 *     while (ADC1_EIM_Active_Sts() == 0u)
 *     {
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint8 ADC1_EIM_Active_Sts(void)
{
  return ( u1_Field_Rd32(&ADC1->SQ_FB.reg, ADC1_SQ_FB_EIM_ACTIVE_Pos, ADC1_SQ_FB_EIM_ACTIVE_Msk) );
}

/** \brief Reads the active status of the Exceptional Sequencer Measurement (ESM).
 *
 * \retval 1 ESM ongoing
 * \retval 0 no ESM active
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode and reads the active status of the Exceptional Sequencer Measurement (ESM).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_ESM_Channel_Set( ADC1_P22 );
 *
 *     while (ADC1_ESM_Active_Sts() == 0u)
 *     {
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint8 ADC1_ESM_Active_Sts(void)
{
  return ( u1_Field_Rd32(&ADC1->SQ_FB.reg, ADC1_SQ_FB_ESM_ACTIVE_Pos, ADC1_SQ_FB_ESM_ACTIVE_Msk) );
}

/** \brief Reads the currently active channel in Sequencer Mode.
 *
 * \return uint8, number of the current channel, values between 0..13
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode and reads the currently active channel in Sequencer Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_SW_Channel_Sel( ADC1_P20 );
 *     while (ADC1_Current_Active_Sequence_Sts() & 0x6 != 0x6)
 *     {
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint8 ADC1_Current_Active_Sequence_Sts(void)
{
  return ( u8_Field_Rd32(&ADC1->SQ_FB.reg, ADC1_SQ_FB_SQx_Pos, ADC1_SQ_FB_SQx_Msk) );
}

/** \brief Reads the currently active channel.
 *
 * \return uint8, number of the current channel, values between 0..13
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Software Mode and reads the currently active channel 6.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_Software_Mode_Sel();
 *     ADC1_SW_Channel_Sel( ADC1_P20 );
 *     while (ADC1_Current_Active_Channel_Sts() & 0x6 != 0x6)
 *     {
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint8 ADC1_Current_Active_Channel_Sts(void)
{
  return ( u8_Field_Rd32(&ADC1->SQ_FB.reg, ADC1_SQ_FB_CHx_Pos, ADC1_SQ_FB_CHx_Msk) );
}

/** \brief Defines the channels to be measured in Sequence 0, only valid in Sequencer Mode, see \link ADC1_Sequencer_Mode_Sel \endlink.
 *
 * \param mask_ch a bit mask of channels to be set for this sequence
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 1 (CSA) and channel 6 (VDH).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_CSA | ADC1_MASK_VDH );
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Sequence0_Set(uint32 mask_ch)
{
  Field_Mod32(&ADC1->SQ1_4.reg, ADC1_SQ1_4_SQ1_Pos, ADC1_SQ1_4_SQ1_Msk, (mask_ch));
}

/** \brief Defines the channels to be measured in Sequence 1, only valid in Sequencer Mode, see \link ADC1_Sequencer_Mode_Sel \endlink.
 *
 * \param mask_ch a bit mask of channels to be set for this sequence
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 1 (CSA) and channel 6 (VDH).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence1_Set( ADC1_MASK_CSA | ADC1_MASK_VDH );
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Sequence1_Set(uint32 mask_ch)
{
  Field_Mod32(&ADC1->SQ1_4.reg, ADC1_SQ1_4_SQ2_Pos, ADC1_SQ1_4_SQ2_Msk, (mask_ch));
}

/** \brief Defines the channels to be measured in Sequence 2, only valid in Sequencer Mode, see \link ADC1_Sequencer_Mode_Sel \endlink.
 *
 * \param mask_ch a bit mask of channels to be set for this sequence
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 1 (CSA) and channel 6 (VDH).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence2_Set( ADC1_MASK_CSA | ADC1_MASK_VDH );
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Sequence2_Set(uint32 mask_ch)
{
  Field_Mod32(&ADC1->SQ1_4.reg, ADC1_SQ1_4_SQ3_Pos, ADC1_SQ1_4_SQ3_Msk, (mask_ch));
}

/** \brief Defines the channels to be measured in Sequence 3, only valid in Sequencer Mode, see \link ADC1_Sequencer_Mode_Sel \endlink.
 *
 * \param mask_ch a bit mask of channels to be set for this sequence
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 1 (CSA) and channel 6 (VDH).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence3_Set( ADC1_MASK_CSA | ADC1_MASK_VDH );
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Sequence3_Set(uint32 mask_ch)
{
  Field_Mod32(&ADC1->SQ1_4.reg, ADC1_SQ1_4_SQ4_Pos, ADC1_SQ1_4_SQ4_Msk, (mask_ch));
}

/** \brief Defines the channels to be measured in Sequence 4, only valid in Sequencer Mode, see \link ADC1_Sequencer_Mode_Sel \endlink.
 *
 * \param mask_ch a bit mask of channels to be set for this sequence
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 1 (CSA) and channel 6 (VDH).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence4_Set( ADC1_MASK_CSA | ADC1_MASK_VDH );
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Sequence4_Set(uint32 mask_ch)
{
  Field_Mod32(&ADC1->SQ5_8.reg, ADC1_SQ5_8_SQ5_Pos, ADC1_SQ5_8_SQ5_Msk, (mask_ch));
}

/** \brief Defines the channels to be measured in Sequence 5, only valid in Sequencer Mode, see \link ADC1_Sequencer_Mode_Sel \endlink.
 *
 * \param mask_ch a bit mask of channels to be set for this sequence
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 1 (CSA) and channel 6 (VDH).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence5_Set( ADC1_MASK_CSA | ADC1_MASK_VDH );
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Sequence5_Set(uint32 mask_ch)
{
  Field_Mod32(&ADC1->SQ5_8.reg, ADC1_SQ5_8_SQ6_Pos, ADC1_SQ5_8_SQ6_Msk, (mask_ch));
}

/** \brief Defines the channels to be measured in Sequence 6, only valid in Sequencer Mode, see \link ADC1_Sequencer_Mode_Sel \endlink.
 *
 * \param mask_ch a bit mask of channels to be set for this sequence
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 1 (CSA) and channel 6 (VDH).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence6_Set( ADC1_MASK_CSA | ADC1_MASK_VDH );
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Sequence6_Set(uint32 mask_ch)
{
  Field_Mod32(&ADC1->SQ5_8.reg, ADC1_SQ5_8_SQ7_Pos, ADC1_SQ5_8_SQ7_Msk, (mask_ch));
}

/** \brief Defines the channels to be measured in Sequence 7, only valid in Sequencer Mode, see \link ADC1_Sequencer_Mode_Sel \endlink.
 *
 * \param mask_ch a bit mask of channels to be set for this sequence
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 1 (CSA) and channel 6 (VDH).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence7_Set( ADC1_MASK_CSA | ADC1_MASK_VDH );
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Sequence7_Set(uint32 mask_ch)
{
  Field_Mod32(&ADC1->SQ5_8.reg, ADC1_SQ5_8_SQ8_Pos, ADC1_SQ5_8_SQ8_Msk, (mask_ch));
}

/** \brief Reads the converted value from the channel 0 result register.
 *
 * \return 12-bit value, with left aligned 10-bit/8-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 0 (P2.0) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P20 );
 *
 *     if ( ADC1_Ch0_ResultValid_Get() == 1u )
 *     {
 *         adc_result = ADC1_Ch0_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_Ch0_Result_Get(void)
{
  return ( u16_Field_Rd32(&ADC1->RES_OUT0.reg, ADC1_RES_OUT0_OUT_CH0_Pos, ADC1_RES_OUT0_OUT_CH0_Msk) );
}

/** \brief Reads the converted value from the channel 1 result register.
 *
 * \return 12-bit value, with left aligned 10-bit/8-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 1 (CSA) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_CSA );
 *
 *     if ( ADC1_Ch1_ResultValid_Get() == 1u )
 *     {
 *         adc_result = ADC1_Ch1_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_Ch1_Result_Get(void)
{
  return ( u16_Field_Rd32(&ADC1->RES_OUT1.reg, ADC1_RES_OUT1_OUT_CH1_Pos, ADC1_RES_OUT1_OUT_CH1_Msk) );
}

/** \brief Reads the converted value from the channel 2 result register.
 *
 * \return 12-bit value, with left aligned 10-bit/8-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 2 (P2.2) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P22 );
 *
 *     if ( ADC1_Ch2_ResultValid_Get() == 1u )
 *     {
 *         adc_result = ADC1_Ch2_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_Ch2_Result_Get(void)
{
  return ( u16_Field_Rd32(&ADC1->RES_OUT2.reg, ADC1_RES_OUT2_OUT_CH2_Pos, ADC1_RES_OUT2_OUT_CH2_Msk) );
}

/** \brief Reads the converted value from the channel 3 result register.
 *
 * \return 12-bit value, with left aligned 10-bit/8-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 3 (P2.3) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P23 );
 *
 *     if ( ADC1_Ch3_ResultValid_Get() == 1u )
 *     {
 *         adc_result = ADC1_Ch3_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_Ch3_Result_Get(void)
{
  return ( u16_Field_Rd32(&ADC1->RES_OUT3.reg, ADC1_RES_OUT3_OUT_CH3_Pos, ADC1_RES_OUT3_OUT_CH3_Msk) );
}

/** \brief Reads the converted value from the channel 4 result register.
 *
 * \return 12-bit value, with left aligned 10-bit/8-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 4 (P2.4) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P24 );
 *
 *     if ( ADC1_Ch4_ResultValid_Get() == 1u )
 *     {
 *         adc_result = ADC1_Ch4_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_Ch4_Result_Get(void)
{
  return ( u16_Field_Rd32(&ADC1->RES_OUT4.reg, ADC1_RES_OUT4_OUT_CH4_Pos, ADC1_RES_OUT4_OUT_CH4_Msk) );
}

/** \brief Reads the converted value from the channel 5 result register.
 *
 * \return 12-bit value, with left aligned 10-bit/8-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 5 (P2.5) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P25 );
 *
 *     if ( ADC1_Ch5_ResultValid_Get() == 1u )
 *     {
 *         adc_result = ADC1_Ch5_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_Ch5_Result_Get(void)
{
  return ( u16_Field_Rd32(&ADC1->RES_OUT5.reg, ADC1_RES_OUT5_OUT_CH5_Pos, ADC1_RES_OUT5_OUT_CH5_Msk) );
}

/** \brief Reads the converted value from the channel 6 (VDH) result register.
 *
 * \return 12-bit value, with left aligned 10-bit/8-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 6 (VDH) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_VDH );
 *
 *     if ( ADC1_Ch6_ResultValid_Get() == 1u )
 *     {
 *         adc_result = ADC1_Ch6_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_Ch6_Result_Get(void)
{
  return ( u16_Field_Rd32(&ADC1->RES_OUT6.reg, ADC1_RES_OUT6_OUT_CH6_Pos, ADC1_RES_OUT6_OUT_CH6_Msk) );
}

/** \brief Reads the converted value from the EIM result register.
 *
 * \return 12-bit value, with left aligned 10-bit/8-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 2 (P2.2) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_EIM_Channel_Set( ADC1_CH2 );
 *
 *     while ( ADC1_EIM_ResultValid_Get() == 0u )
 *     {
 *     }
 *
 *     adc_result = ADC1_EIM_Result_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_EIM_Result_Get(void)
{
  return ( u16_Field_Rd32(&ADC1->RES_OUT_EIM.reg, ADC1_RES_OUT_EIM_OUT_CH_EIM_Pos, ADC1_RES_OUT_EIM_OUT_CH_EIM_Msk) );
}

/** \brief Reads the converted value from the channel 0 result register.
 *
 * \return 12-bit value, with left aligned 10-bit/8-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 0 (P2.0) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P20 );
 *
 *     if ( ADC1_Ch0_ResultValid_Get() == 1u )
 *     {
 *         adc_result = ADC1_P20_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_P20_Result_Get(void)
{
  return ( ADC1_Ch0_Result_Get() );
}

/** \brief Reads the converted value from the channel 1 result register.
 *
 * \return 12-bit value, with left aligned 10-bit/8-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 1 (CSA) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_CSA );
 *
 *     if ( ADC1_Ch1_ResultValid_Get() == 1u )
 *     {
 *         adc_result = ADC1_CSA_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_CSA_Result_Get(void)
{
  return ( ADC1_Ch1_Result_Get() );
}

/** \brief Reads the converted value from the channel 2 result register.
 *
 * \return 12-bit value, with left aligned 10-bit/8-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 2 (P2.2) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P22 );
 *
 *     if ( ADC1_Ch2_ResultValid_Get() == 1u )
 *     {
 *         adc_result = ADC1_P22_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_P22_Result_Get(void)
{
  return ( ADC1_Ch2_Result_Get() );
}

/** \brief Reads the converted value from the channel 3 result register.
 *
 * \return 12-bit value, with left aligned 10-bit/8-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 3 (P2.3) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P23 );
 *
 *     if ( ADC1_Ch3_ResultValid_Get() == 1u )
 *     {
 *         adc_result = ADC1_P23_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_P23_Result_Get(void)
{
  return ( ADC1_Ch3_Result_Get() );
}

/** \brief Reads the converted value from the channel 4 result register.
 *
 * \return 12-bit value, with left aligned 10-bit/8-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 4 (P2.4) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P24 );
 *
 *     if ( ADC1_Ch4_ResultValid_Get() == 1u )
 *     {
 *         adc_result = ADC1_P24_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_P24_Result_Get(void)
{
  return ( ADC1_Ch4_Result_Get() );
}

/** \brief Reads the converted value from the channel 5 result register.
 *
 * \return 12-bit value, with left aligned 10-bit/8-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 5 (P2.5) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P25 );
 *
 *     if ( ADC1_Ch5_ResultValid_Get() == 1u )
 *     {
 *         adc_result = ADC1_P25_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_P25_Result_Get(void)
{
  return ( ADC1_Ch5_Result_Get() );
}

/** \brief Reads the converted value from the channel 6 (VDH) result register.
 *
 * \return 12-bit value, with left aligned 10-bit/8-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 6 (VDH) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_VDH );
 *
 *     if ( ADC1_Ch6_ResultValid_Get() == 1u )
 *     {
 *         adc_result = ADC1_VDH_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_VDH_Result_Get(void)
{
  return ( ADC1_Ch6_Result_Get() );
}

/** \brief Reads the valid flag for the channel 0 (P2.0) result.
 * \note The flag gets reset by reading.
 *
 * \retval 1 if result is valid
 * \retval 0 if result is not valid, or already read
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 0 (P2.0) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P20 );
 *
 *     if ( ADC1_Ch0_ResultValid_Get() == 1u )
 *     {
 *         adc_result = ADC1_P20_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint8 ADC1_Ch0_ResultValid_Get(void)
{
  return ( u1_Field_Rd32(&ADC1->RES_OUT0.reg, ADC1_RES_OUT0_VF0_Pos, ADC1_RES_OUT0_VF0_Msk) );
}

/** \brief Reads the valid flag for the channel 1 (CSA) result.
 * \note The flag gets reset by reading.
 *
 * \retval 1 if result is valid
 * \retval 0 if result is not valid, or already read
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 1 (CSA) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_CSA );
 *
 *     if ( ADC1_Ch1_ResultValid_Get() == 1u )
 *     {
 *         adc_result = ADC1_CSA_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint8 ADC1_Ch1_ResultValid_Get(void)
{
  return ( u1_Field_Rd32(&ADC1->RES_OUT1.reg, ADC1_RES_OUT1_VF1_Pos, ADC1_RES_OUT1_VF1_Msk) );
}

/** \brief Reads the valid flag for the channel 2 (P2.2) result.
 * \note The flag gets reset by reading.
 *
 * \retval 1 if result is valid
 * \retval 0 if result is not valid, or already read
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 2 (P2.2) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P22 );
 *
 *     if ( ADC1_Ch2_ResultValid_Get() == 1u )
 *     {
 *         adc_result = ADC1_P22_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint8 ADC1_Ch2_ResultValid_Get(void)
{
  return ( u1_Field_Rd32(&ADC1->RES_OUT2.reg, ADC1_RES_OUT2_VF2_Pos, ADC1_RES_OUT2_VF2_Msk) );
}

/** \brief Reads the valid flag for the channel 3 (P2.3) result.
 * \note The flag gets reset by reading.
 *
 * \retval 1 if result is valid
 * \retval 0 if result is not valid, or already read
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 3 (P2.3) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P23 );
 *
 *     if ( ADC1_Ch3_ResultValid_Get() == 1u )
 *     {
 *         adc_result = ADC1_P23_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint8 ADC1_Ch3_ResultValid_Get(void)
{
  return ( u1_Field_Rd32(&ADC1->RES_OUT3.reg, ADC1_RES_OUT3_VF3_Pos, ADC1_RES_OUT3_VF3_Msk) );
}

/** \brief Reads the valid flag for the channel 4 (P2.4) result.
 * \note The flag gets reset by reading.
 *
 * \retval 1 if result is valid
 * \retval 0 if result is not valid, or already read
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 4 (P2.4) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P24 );
 *
 *     if ( ADC1_Ch4_ResultValid_Get() == 1u )
 *     {
 *         adc_result = ADC1_P24_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint8 ADC1_Ch4_ResultValid_Get(void)
{
  return ( u1_Field_Rd32(&ADC1->RES_OUT4.reg, ADC1_RES_OUT4_VF4_Pos, ADC1_RES_OUT4_VF4_Msk) );
}

/** \brief Reads the valid flag for the channel 5 (P2.5) result.
 * \note The flag gets reset by reading.
 *
 * \retval 1 if result is valid
 * \retval 0 if result is not valid, or already read
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 5 (P2.5) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P25 );
 *
 *     if ( ADC1_Ch5_ResultValid_Get() == 1u )
 *     {
 *         adc_result = ADC1_P25_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint8 ADC1_Ch5_ResultValid_Get(void)
{
  return ( u1_Field_Rd32(&ADC1->RES_OUT5.reg, ADC1_RES_OUT5_VF5_Pos, ADC1_RES_OUT5_VF5_Msk) );
}

/** \brief Reads the valid flag for the channel 6 (VDH) result.
 * \note The flag gets reset by reading.
 *
 * \retval 1 if result is valid
 * \retval 0 if result is not valid, or already read
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 6 (VDH) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_VDH );
 *
 *     if ( ADC1_Ch6_ResultValid_Get() == 1u )
 *     {
 *         adc_result = ADC1_VDH_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint8 ADC1_Ch6_ResultValid_Get(void)
{
  return ( u1_Field_Rd32(&ADC1->RES_OUT6.reg, ADC1_RES_OUT6_VF6_Pos, ADC1_RES_OUT6_VF6_Msk) );
}

/** \brief Reads the valid flag for the channel 6 (VDH) result.
 * \note The flag gets reset by reading.
 *
 * \retval 1 if result is valid
 * \retval 0 if result is not valid, or already read
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 2 (P2.2) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_EIM_Channel_Set( ADC1_CH2 );
 *
 *     while ( ADC1_EIM_ResultValid_Get() == 0u )
 *     {
 *     }
 *
 *     adc_result = ADC1_EIM_Result_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint8 ADC1_EIM_ResultValid_Get(void)
{
  return ( u1_Field_Rd32(&ADC1->RES_OUT_EIM.reg, ADC1_RES_OUT_EIM_VF8_Pos, ADC1_RES_OUT_EIM_VF8_Msk) );
}

/** \brief Sets the ADC1 channel 0 conversion data width to 8-bit.
 * \note The 8-bit word is left aligned in the 12-bit result value, \link ADC1_P20_Result_Get \endlink.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Software Mode, starts a measurement and waits for it to be finished.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Software_Mode_Sel();
 *     ADC1_Ch0_DataWidth_8bit_Set();
 *     ADC1_SW_Ch_Sel( ADC1_P20 );
 *     ADC1_SOC_Set();
 *
 *     while ( ADC1_EOC_Sts() != 1u ) {}
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch0_DataWidth_8bit_Set(void)
{
  Field_Mod32(&ADC1->DWSEL.reg, ADC1_DWSEL_ch0_Pos, ADC1_DWSEL_ch0_Msk, 1u);
}

/** \brief Sets the ADC1 channel 0 conversion data width to 10-bit.
 * \note The 10-bit word is left aligned in the 12-bit result value, \link ADC1_P20_Result_Get \endlink.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Software Mode, starts a measurement and waits for it to be finished.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Software_Mode_Sel();
 *     ADC1_Ch0_DataWidth_10bit_Set();
 *     ADC1_SW_Ch_Sel( ADC1_P20 );
 *     ADC1_SOC_Set();
 *
 *     while ( ADC1_EOC_Sts() != 1u ) {}
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch0_DataWidth_10bit_Set(void)
{
  Field_Mod32(&ADC1->DWSEL.reg, ADC1_DWSEL_ch0_Pos, ADC1_DWSEL_ch0_Msk, 0u);
}

/** \brief Sets the ADC1 channel 1 conversion data width to 8-bit.
 * \note The 8-bit word is left aligned in the 12-bit result value, \link ADC1_CSA_Result_Get \endlink.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Software Mode, starts a measurement and waits for it to be finished.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Software_Mode_Sel();
 *     ADC1_Ch1_DataWidth_8bit_Set();
 *     ADC1_SW_Ch_Sel( ADC1_CSA );
 *     ADC1_SOC_Set();
 *
 *     while ( ADC1_EOC_Sts() != 1u ) {}
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch1_DataWidth_8bit_Set(void)
{
  Field_Mod32(&ADC1->DWSEL.reg, ADC1_DWSEL_ch1_Pos, ADC1_DWSEL_ch1_Msk, 1u);
}

/** \brief Sets the ADC1 channel 1 conversion data width to 10-bit.
 * \note The 10-bit word is left aligned in the 12-bit result value, \link ADC1_CSA_Result_Get \endlink.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Software Mode, starts a measurement and waits for it to be finished.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Software_Mode_Sel();
 *     ADC1_Ch1_DataWidth_10bit_Set();
 *     ADC1_SW_Ch_Sel( ADC1_CSA );
 *     ADC1_SOC_Set();
 *
 *     while ( ADC1_EOC_Sts() != 1u ) {}
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch1_DataWidth_10bit_Set(void)
{
  Field_Mod32(&ADC1->DWSEL.reg, ADC1_DWSEL_ch1_Pos, ADC1_DWSEL_ch1_Msk, 0u);
}

/** \brief Sets the ADC1 channel 2 conversion data width to 8-bit.
 * \note The 8-bit word is left aligned in the 12-bit result value, \link ADC1_P22_Result_Get \endlink.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Software Mode, starts a measurement and waits for it to be finished.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Software_Mode_Sel();
 *     ADC1_Ch2_DataWidth_8bit_Set();
 *     ADC1_SW_Ch_Sel( ADC1_P22 );
 *     ADC1_SOC_Set();
 *
 *     while ( ADC1_EOC_Sts() != 1u ) {}
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch2_DataWidth_8bit_Set(void)
{
  Field_Mod32(&ADC1->DWSEL.reg, ADC1_DWSEL_ch2_Pos, ADC1_DWSEL_ch2_Msk, 1u);
}

/** \brief Sets the ADC1 channel 2 conversion data width to 10-bit.
 * \note The 10-bit word is left aligned in the 12-bit result value, \link ADC1_P22_Result_Get \endlink.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Software Mode, starts a measurement and waits for it to be finished.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Software_Mode_Sel();
 *     ADC1_Ch2_DataWidth_10bit_Set();
 *     ADC1_SW_Ch_Sel( ADC1_P22 );
 *     ADC1_SOC_Set();
 *
 *     while ( ADC1_EOC_Sts() != 1u ) {}
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch2_DataWidth_10bit_Set(void)
{
  Field_Mod32(&ADC1->DWSEL.reg, ADC1_DWSEL_ch2_Pos, ADC1_DWSEL_ch2_Msk, 0u);
}

/** \brief Sets the ADC1 channel 3 conversion data width to 8-bit.
 * \note The 8-bit word is left aligned in the 12-bit result value, \link ADC1_P23_Result_Get \endlink.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Software Mode, starts a measurement and waits for it to be finished.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Software_Mode_Sel();
 *     ADC1_Ch3_DataWidth_8bit_Set();
 *     ADC1_SW_Ch_Sel( ADC1_P23 );
 *     ADC1_SOC_Set();
 *
 *     while ( ADC1_EOC_Sts() != 1u ) {}
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch3_DataWidth_8bit_Set(void)
{
  Field_Mod32(&ADC1->DWSEL.reg, ADC1_DWSEL_ch3_Pos, ADC1_DWSEL_ch3_Msk, 1u);
}

/** \brief Sets the ADC1 channel 3 conversion data width to 10-bit.
 * \note The 10-bit word is left aligned in the 12-bit result value, \link ADC1_P23_Result_Get \endlink.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Software Mode, starts a measurement and waits for it to be finished.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Software_Mode_Sel();
 *     ADC1_Ch3_DataWidth_10bit_Set();
 *     ADC1_SW_Ch_Sel( ADC1_P23 );
 *     ADC1_SOC_Set();
 *
 *     while ( ADC1_EOC_Sts() != 1u ) {}
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch3_DataWidth_10bit_Set(void)
{
  Field_Mod32(&ADC1->DWSEL.reg, ADC1_DWSEL_ch3_Pos, ADC1_DWSEL_ch3_Msk, 0u);
}

/** \brief Sets the ADC1 channel 4 conversion data width to 8-bit.
 * \note The 8-bit word is left aligned in the 12-bit result value, \link ADC1_P24_Result_Get \endlink.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Software Mode, starts a measurement and waits for it to be finished.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Software_Mode_Sel();
 *     ADC1_Ch4_DataWidth_8bit_Set();
 *     ADC1_SW_Ch_Sel( ADC1_P24 );
 *     ADC1_SOC_Set();
 *
 *     while ( ADC1_EOC_Sts() != 1u ) {}
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch4_DataWidth_8bit_Set(void)
{
  Field_Mod32(&ADC1->DWSEL.reg, ADC1_DWSEL_ch4_Pos, ADC1_DWSEL_ch4_Msk, 1u);
}

/** \brief Sets the ADC1 channel 4 conversion data width to 10-bit.
 * \note The 10-bit word is left aligned in the 12-bit result value, \link ADC1_P24_Result_Get \endlink.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Software Mode, starts a measurement and waits for it to be finished.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Software_Mode_Sel();
 *     ADC1_Ch4_DataWidth_10bit_Set();
 *     ADC1_SW_Ch_Sel( ADC1_P24 );
 *     ADC1_SOC_Set();
 *
 *     while ( ADC1_EOC_Sts() != 1u ) {}
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch4_DataWidth_10bit_Set(void)
{
  Field_Mod32(&ADC1->DWSEL.reg, ADC1_DWSEL_ch4_Pos, ADC1_DWSEL_ch4_Msk, 0u);
}

/** \brief Sets the ADC1 channel 5 conversion data width to 8-bit.
 * \note The 8-bit word is left aligned in the 12-bit result value, \link ADC1_P25_Result_Get \endlink.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Software Mode, starts a measurement and waits for it to be finished.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Software_Mode_Sel();
 *     ADC1_Ch5_DataWidth_8bit_Set();
 *     ADC1_SW_Ch_Sel( ADC1_P25 );
 *     ADC1_SOC_Set();
 *
 *     while ( ADC1_EOC_Sts() != 1u ) {}
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch5_DataWidth_8bit_Set(void)
{
  Field_Mod32(&ADC1->DWSEL.reg, ADC1_DWSEL_ch5_Pos, ADC1_DWSEL_ch5_Msk, 1u);
}

/** \brief Sets the ADC1 channel 5 conversion data width to 10-bit.
 * \note The 10-bit word is left aligned in the 12-bit result value, \link ADC1_P25_Result_Get \endlink.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Software Mode, starts a measurement and waits for it to be finished.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Software_Mode_Sel();
 *     ADC1_Ch5_DataWidth_10bit_Set();
 *     ADC1_SW_Ch_Sel( ADC1_P25 );
 *     ADC1_SOC_Set();
 *
 *     while ( ADC1_EOC_Sts() != 1u ) {}
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch5_DataWidth_10bit_Set(void)
{
  Field_Mod32(&ADC1->DWSEL.reg, ADC1_DWSEL_ch5_Pos, ADC1_DWSEL_ch5_Msk, 0u);
}

/** \brief Sets the ADC1 channel 6 conversion data width to 8-bit.
 * \note The 8-bit word is left aligned in the 12-bit result value, \link ADC1_VDH_Result_Get \endlink.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Software Mode, starts a measurement and waits for it to be finished.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Software_Mode_Sel();
 *     ADC1_Ch6_DataWidth_8bit_Set();
 *     ADC1_SW_Ch_Sel( ADC1_VDH );
 *     ADC1_SOC_Set();
 *
 *     while ( ADC1_EOC_Sts() != 1u ) {}
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch6_DataWidth_8bit_Set(void)
{
  Field_Mod32(&ADC1->DWSEL.reg, ADC1_DWSEL_ch6_Pos, ADC1_DWSEL_ch6_Msk, 1u);
}

/** \brief Sets the ADC1 channel 6 conversion data width to 10-bit.
 * \note The 10-bit word is left aligned in the 12-bit result value, \link ADC1_VDH_Result_Get \endlink.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Software Mode, starts a measurement and waits for it to be finished.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Software_Mode_Sel();
 *     ADC1_Ch6_DataWidth_10bit_Set();
 *     ADC1_SW_Ch_Sel( ADC1_VDH );
 *     ADC1_SOC_Set();
 *
 *     while ( ADC1_EOC_Sts() != 1u ) {}
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch6_DataWidth_10bit_Set(void)
{
  Field_Mod32(&ADC1->DWSEL.reg, ADC1_DWSEL_ch6_Pos, ADC1_DWSEL_ch6_Msk, 0u);
}

/** \brief Sets the ADC1 channel 0 number of sampling ticks.
 * \note The effective sampling time is calculated by: \f$t_{sampling} = \frac{2+stc}{f_{ADC1}}\f$.
 *
 * \param stc sampling tick count
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Software Mode, starts a measurement and waits for it to be finished.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Software_Mode_Sel();
 *     ADC1_Ch0_DataWidth_10bit_Set();
 *     ADC1_Ch0_Sample_Time_Set( 10 );
 *     ADC1_SW_Ch_Sel( ADC1_P20 );
 *     ADC1_SOC_Set();
 *
 *     while ( ADC1_EOC_Sts() != 1u ) {}
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch0_Sample_Time_Set(uint32 stc)
{
  Field_Mod32(&ADC1->STC_0_3.reg, ADC1_STC_0_3_ch0_Pos, ADC1_STC_0_3_ch0_Msk, stc);
}

/** \brief Sets the ADC1 channel 1 number of sampling ticks.
 * \note The effective sampling time is calculated by: \f$t_{sample} = \frac{2+stc}{f_{ADC1}}\f$.
 *
 * \param stc sampling tick count
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Software Mode, starts a measurement and waits for it to be finished.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Software_Mode_Sel();
 *     ADC1_Ch1_DataWidth_10bit_Set();
 *     ADC1_Ch1_Sample_Time_Set( 10 );
 *     ADC1_SW_Ch_Sel( ADC1_CSA );
 *     ADC1_SOC_Set();
 *
 *     while ( ADC1_EOC_Sts() != 1u ) {}
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch1_Sample_Time_Set(uint32 stc)
{
  Field_Mod32(&ADC1->STC_0_3.reg, ADC1_STC_0_3_ch1_Pos, ADC1_STC_0_3_ch1_Msk, stc);
}

/** \brief Sets the ADC1 channel 2 number of sampling ticks.
 * \note The effective sampling time is calculated by: \f$t_{sample} = \frac{2+stc}{f_{ADC1}}\f$.
 *
 * \param stc sampling tick count
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Software Mode, starts a measurement and waits for it to be finished.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Software_Mode_Sel();
 *     ADC1_Ch2_DataWidth_10bit_Set();
 *     ADC1_Ch2_Sample_Time_Set( 10 );
 *     ADC1_SW_Ch_Sel( ADC1_P22 );
 *     ADC1_SOC_Set();
 *
 *     while ( ADC1_EOC_Sts() != 1u ) {}
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch2_Sample_Time_Set(uint32 stc)
{
  Field_Mod32(&ADC1->STC_0_3.reg, ADC1_STC_0_3_ch2_Pos, ADC1_STC_0_3_ch2_Msk, stc);
}

/** \brief Sets the ADC1 channel 3 number of sampling ticks.
 * \note The effective sampling time is calculated by: \f$t_{sample} = \frac{2+stc}{f_{ADC1}}\f$.
 *
 * \param stc sampling tick count
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Software Mode, starts a measurement and waits for it to be finished.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Software_Mode_Sel();
 *     ADC1_Ch3_DataWidth_10bit_Set();
 *     ADC1_Ch3_Sample_Time_Set( 10 );
 *     ADC1_SW_Ch_Sel( ADC1_P23 );
 *     ADC1_SOC_Set();
 *
 *     while ( ADC1_EOC_Sts() != 1u ) {}
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch3_Sample_Time_Set(uint32 stc)
{
  Field_Mod32(&ADC1->STC_0_3.reg, ADC1_STC_0_3_ch3_Pos, ADC1_STC_0_3_ch3_Msk, stc);
}

/** \brief Sets the ADC1 channel 4 number of sampling ticks.
 * \note The effective sampling time is calculated by: \f$t_{sample} = \frac{2+stc}{f_{ADC1}}\f$.
 *
 * \param stc sampling tick count
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Software Mode, starts a measurement and waits for it to be finished.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Software_Mode_Sel();
 *     ADC1_Ch4_DataWidth_10bit_Set();
 *     ADC1_Ch4_Sample_Time_Set( 10 );
 *     ADC1_SW_Ch_Sel( ADC1_P24 );
 *     ADC1_SOC_Set();
 *
 *     while ( ADC1_EOC_Sts() != 1u ) {}
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch4_Sample_Time_Set(uint32 stc)
{
  Field_Mod32(&ADC1->STC_4_7.reg, ADC1_STC_4_7_ch4_Pos, ADC1_STC_4_7_ch4_Msk, stc);
}

/** \brief Sets the ADC1 channel 5 number of sampling ticks.
 * \note The effective sampling time is calculated by: \f$t_{sample} = \frac{2+stc}{f_{ADC1}}\f$.
 *
 * \param stc sampling tick count
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Software Mode, starts a measurement and waits for it to be finished.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Software_Mode_Sel();
 *     ADC1_Ch5_DataWidth_10bit_Set();
 *     ADC1_Ch5_Sample_Time_Set( 10 );
 *     ADC1_SW_Ch_Sel( ADC1_P25 );
 *     ADC1_SOC_Set();
 *
 *     while ( ADC1_EOC_Sts() != 1u ) {}
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch5_Sample_Time_Set(uint32 stc)
{
  Field_Mod32(&ADC1->STC_4_7.reg, ADC1_STC_4_7_ch5_Pos, ADC1_STC_4_7_ch5_Msk, stc);
}

/** \brief Sets the ADC1 channel 6 number of sampling ticks.
 * \note The effective sampling time is calculated by: \f$t_{sample} = \frac{2+stc}{f_{ADC1}}\f$.
 *
 * \param stc sampling tick count
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Software Mode, starts a measurement and waits for it to be finished.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Software_Mode_Sel();
 *     ADC1_Ch6_DataWidth_10bit_Set();
 *     ADC1_Ch6_Sample_Time_Set( 10 );
 *     ADC1_SW_Ch_Sel( ADC1_VDH );
 *     ADC1_SOC_Set();
 *
 *     while ( ADC1_EOC_Sts() != 1u ) {}
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch6_Sample_Time_Set(uint32 stc)
{
  Field_Mod32(&ADC1->STC_4_7.reg, ADC1_STC_4_7_ch6_Pos, ADC1_STC_4_7_ch6_Msk, stc);
}

/** \brief Sets the ADC1 channel 0 result register to "wait for read".
 * \note A valid result will not be overwritten by a subsequent conversion until the result is read.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 0 (P2.0) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P20 );
 *     ADC1_Ch0_WaitForRead_Set();
 *
 *     if ( ADC1_Ch0_ResultValid_Get() == true )
 *     {
 *         adc_result = ADC1_P20_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch0_WaitForRead_Set(void)
{
  Field_Mod32(&ADC1->RES_OUT0.reg, ADC1_RES_OUT0_WFR0_Pos, ADC1_RES_OUT0_WFR0_Msk, 1u);
}

/** \brief Sets the ADC1 channel 0 result register to "overwrite".
 * \note A valid result will be overwritten by a subsequent conversion, a previous unread conversion is lost.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 0 (P2.0) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P20 );
 *     ADC1_Ch0_Overwrite_Set();
 *
 *     if ( ADC1_Ch0_ResultValid_Get() == 1u )
 *     {
 *         adc_result = ADC1_P20_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch0_Overwrite_Set(void)
{
  Field_Mod32(&ADC1->RES_OUT0.reg, ADC1_RES_OUT0_WFR0_Pos, ADC1_RES_OUT0_WFR0_Msk, 0u);
}

/** \brief Sets ADC1 channel 1 the result register to "wait for read".
 * \note A valid result will not be overwritten by a subsequent conversion until the result is read.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 1 (CSA) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_CSA );
 *     ADC1_Ch1_WaitForRead_Set();
 *
 *     if ( ADC1_Ch1_ResultValid_Get() == 1u )
 *     {
 *         adc_result = ADC1_CSA_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch1_WaitForRead_Set(void)
{
  Field_Mod32(&ADC1->RES_OUT1.reg, ADC1_RES_OUT1_WFR1_Pos, ADC1_RES_OUT1_WFR1_Msk, 1u);
}

/** \brief Sets the ADC1 channel 1 result register to "overwrite".
 * \note A valid result will be overwritten by a subsequent conversion, a previous unread conversion is lost.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 1 (CSA) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_CSA );
 *     ADC1_Ch1_Overwrite_Set();
 *
 *     if ( ADC1_Ch1_ResultValid_Get() == 1u )
 *     {
 *         adc_result = ADC1_CSA_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch1_Overwrite_Set(void)
{
  Field_Mod32(&ADC1->RES_OUT1.reg, ADC1_RES_OUT1_WFR1_Pos, ADC1_RES_OUT1_WFR1_Msk, 0u);
}

/** \brief Sets the ADC1 channel 2 result register to "wait for read".
 * \note A valid result will not be overwritten by a subsequent conversion until the result is read.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 2 (P2.2) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P22 );
 *     ADC1_Ch2_WaitForRead_Set();
 *
 *     if ( ADC1_Ch2_ResultValid_Get() == 1u )
 *     {
 *         adc_result = ADC1_P22_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch2_WaitForRead_Set(void)
{
  Field_Mod32(&ADC1->RES_OUT2.reg, ADC1_RES_OUT2_WFR2_Pos, ADC1_RES_OUT2_WFR2_Msk, 1u);
}

/** \brief Sets the ADC1 channel 2 result register to "overwrite".
 * \note A valid result will be overwritten by a subsequent conversion, a previous unread conversion is lost.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 2 (P2.2) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P22 );
 *     ADC1_Ch2_Overwrite_Set();
 *
 *     if ( ADC1_Ch2_ResultValid_Get() == 1u )
 *     {
 *         adc_result = ADC1_P22_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch2_Overwrite_Set(void)
{
  Field_Mod32(&ADC1->RES_OUT2.reg, ADC1_RES_OUT2_WFR2_Pos, ADC1_RES_OUT2_WFR2_Msk, 0u);
}

/** \brief Sets the ADC1 channel 3 result register to "wait for read".
 * \note A valid result will not be overwritten by a subsequent conversion until the result is read.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 3 (P2.3) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P23 );
 *     ADC1_Ch3_WaitForRead_Set();
 *
 *     if ( ADC1_Ch3_ResultValid_Get() == 1u )
 *     {
 *         adc_result = ADC1_P23_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch3_WaitForRead_Set(void)
{
  Field_Mod32(&ADC1->RES_OUT3.reg, ADC1_RES_OUT3_WFR3_Pos, ADC1_RES_OUT3_WFR3_Msk, 1u);
}

/** \brief Sets the ADC1 channel 3 result register to "overwrite".
 * \note A valid result will be overwritten by a subsequent conversion, a previous unread conversion is lost.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 3 (P2.3) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P23 );
 *     ADC1_Ch3_Overwrite_Set();
 *
 *     if ( ADC1_Ch3_ResultValid_Get() == 1u )
 *     {
 *         adc_result = ADC1_P23_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch3_Overwrite_Set(void)
{
  Field_Mod32(&ADC1->RES_OUT3.reg, ADC1_RES_OUT3_WFR3_Pos, ADC1_RES_OUT3_WFR3_Msk, 0u);
}

/** \brief Sets the ADC1 channel 4 result register to "wait for read".
 * \note A valid result will not be overwritten by a subsequent conversion until the result is read.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 4 (P2.4) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P24 );
 *     ADC1_Ch4_WaitForRead_Set();
 *
 *     if ( ADC1_Ch4_ResultValid_Get() == 1u )
 *     {
 *         adc_result = ADC1_P24_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch4_WaitForRead_Set(void)
{
  Field_Mod32(&ADC1->RES_OUT4.reg, ADC1_RES_OUT4_WFR4_Pos, ADC1_RES_OUT4_WFR4_Msk, 1u);
}

/** \brief Sets the ADC1 channel 4 result register to "overwrite".
 * \note A valid result will be overwritten by a subsequent conversion, a previous unread conversion is lost.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 4 (P2.4) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P24 );
 *     ADC1_Ch4_Overwrite_Set();
 *
 *     if ( ADC1_Ch4_ResultValid_Get() == 1u )
 *     {
 *         adc_result = ADC1_P24_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch4_Overwrite_Set(void)
{
  Field_Mod32(&ADC1->RES_OUT4.reg, ADC1_RES_OUT4_WFR4_Pos, ADC1_RES_OUT4_WFR4_Msk, 0u);
}

/** \brief Sets the ADC1 channel 5 result register to "wait for read".
 * \note A valid result will not be overwritten by a subsequent conversion until the result is read.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 5 (P2.5) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P25 );
 *     ADC1_Ch5_WaitForRead_Set();
 *
 *     if ( ADC1_Ch5_ResultValid_Get() == 1u )
 *     {
 *         adc_result = ADC1_P25_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch5_WaitForRead_Set(void)
{
  Field_Mod32(&ADC1->RES_OUT5.reg, ADC1_RES_OUT5_WFR5_Pos, ADC1_RES_OUT5_WFR5_Msk, 1u);
}

/** \brief Sets the ADC1 channel 5 result register to "overwrite".
 * \note A valid result will be overwritten by a subsequent conversion, a previous unread conversion is lost.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 5 (P2.5) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P25 );
 *     ADC1_Ch5_Overwrite_Set();
 *
 *     if ( ADC1_Ch5_ResultValid_Get() == 1u )
 *     {
 *         adc_result = ADC1_P25_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch5_Overwrite_Set(void)
{
  Field_Mod32(&ADC1->RES_OUT5.reg, ADC1_RES_OUT5_WFR5_Pos, ADC1_RES_OUT5_WFR5_Msk, 0u);
}

/** \brief Sets the ADC1 channel 6 result register to "wait for read".
 * \note A valid result will not be overwritten by a subsequent conversion until the result is read.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 6 (VDH) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_VDH );
 *     ADC1_Ch6_WaitForRead_Set();
 *
 *     if ( ADC1_Ch6_ResultValid_Get() == 1u )
 *     {
 *         adc_result = ADC1_VDH_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch6_WaitForRead_Set(void)
{
  Field_Mod32(&ADC1->RES_OUT6.reg, ADC1_RES_OUT6_WFR6_Pos, ADC1_RES_OUT6_WFR6_Msk, 1u);
}

/** \brief Sets the ADC1 channel 6 result register to "overwrite".
 * \note A valid result will be overwritten by a subsequent conversion, a previous unread conversion is lost.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 6 (VDH) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_VDH );
 *     ADC1_Ch6_Overwrite_Set();
 *
 *     if ( ADC1_Ch6_ResultValid_Get() == 1u )
 *     {
 *         adc_result = ADC1_P26_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch6_Overwrite_Set(void)
{
  Field_Mod32(&ADC1->RES_OUT6.reg, ADC1_RES_OUT6_WFR6_Pos, ADC1_RES_OUT6_WFR6_Msk, 0u);
}

/** \brief Set EIM channel for measurement.
 *
 * \param ch channel to be measured
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 2 (P2.2) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_EIM_Channel_Set( ADC1_CH2 );
 *
 *     while ( ADC1_EIM_ResultValid_Get() == 0u )
 *     {
 *     }
 *
 *     adc_result = ADC1_EIM_Result_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_EIM_Channel_Set(uint32 ch)
{
  Field_Mod32(&ADC1->CHx_EIM.reg, ADC1_CHx_EIM_CHx_Pos, ADC1_CHx_EIM_CHx_Msk, ch);
}

/** \brief Set channels in ESM sequence.
 *
 * \param mask_ch bit mask of channels to be measured
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1, switches to Sequencer Mode, programs channel 1 (CSA) and channel 6 (VDH), and reads the result of VDH.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_ESM_Channel_Set( ADC1_MASK_CSA | ADC1_MASK_VDH );
 *
 *     while ( ADC1_Ch6_ResultValid_Get() == 0u )
 *     {
 *     }
 *
 *     adc_result = ADC1_VDH_Result_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_ESM_Channel_Set(uint32 mask_ch)
{
  Field_Mod32(&ADC1->CHx_ESM.reg, ADC1_CHx_ESM_ESM_0_Pos, ADC1_CHx_ESM_ESM_0_Msk, (mask_ch));
}

/** \brief Enables the input attenuator for VDH.
 * \note If the input attenuator is disabled \link ADC1_VDH_Attenuator_Off \endlink then the VDH input is basically disconnected from the ADC1.Channel6 input.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, enables the input attenuator, programs channel 6 (VDH) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * uint16 Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_VDH_Attenuator_On();
 *     ADC1_Ch6_DataWidth_10bit_Set();
 *     ADC1_Ch6_Sample_Time_Set( 10 );
 *     ADC1_Sequence0_Set( ADC1_MASK_VDH );
 *     ADC1_Ch6_WaitForRead_Set();
 *
 *     while ( ADC1_Ch6_ResultValid_Get() == 0u )
 *     {
 *     }
 *
 *     adc_result = ADC1_VDH_Result_Get();
 *
 *     return(adc_result);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_VDH_Attenuator_On(void)
{
  Field_Mod32(&MF->VMON_SEN_CTRL.reg, MF_VMON_SEN_CTRL_VMON_SEN_PD_N_Pos, MF_VMON_SEN_CTRL_VMON_SEN_PD_N_Msk, 1u);
}

/** \brief Disables the input attenuator for VDH.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, disables the input attenuator, programs channel 6 (VDH) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * uint16 Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_VDH_Attenuator_Off();
 *     ADC1_Ch6_DataWidth_10bit_Set();
 *     ADC1_Ch6_Sample_Time_Set( 10 );
 *     ADC1_Sequence0_Set( ADC1_MASK_VDH );
 *     ADC1_Ch6_WaitForRead_Set();
 *
 *     while ( ADC1_Ch6_ResultValid_Get() == 0u )
 *     {
 *     }
 *
 *     adc_result = ADC1_VDH_Result_Get();
 *
 *     return(adc_result);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_VDH_Attenuator_Off(void)
{
  Field_Mod32(&MF->VMON_SEN_CTRL.reg, MF_VMON_SEN_CTRL_VMON_SEN_PD_N_Pos, MF_VMON_SEN_CTRL_VMON_SEN_PD_N_Msk, 0u);
}

/** \brief Enables the output attenuator for VDH.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, enables the output attenuator, programs channel 6 (VDH) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * uint16 Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_VDH_Attenuator_On();
 *     ADC1_VDH_Attenuator_Zhigh_Set();
 *     ADC1_Ch6_DataWidth_10bit_Set();
 *     ADC1_Ch6_Sample_Time_Set( 10 );
 *     ADC1_Sequence0_Set( ADC1_MASK_VDH );
 *     ADC1_Ch6_WaitForRead_Set();
 *
 *     while ( ADC1_Ch6_ResultValid_Get() == 0u )
 *     {
 *     }
 *
 *     adc_result = ADC1_VDH_Result_Get();
 *
 *     return(adc_result);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_VDH_Attenuator_Zhigh_Set(void)
{
  Field_Mod32(&MF->VMON_SEN_CTRL.reg, MF_VMON_SEN_CTRL_VMON_SEN_HRESO_5V_Pos, MF_VMON_SEN_CTRL_VMON_SEN_HRESO_5V_Msk, 1u);
}

/** \brief Disables the output attenuator for VDH.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, disables the output attenuator, programs channel 6 (VDH) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * uint16 Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_VDH_Attenuator_On();
 *     ADC1_VDH_Attenuator_Zlow_Set();
 *     ADC1_Ch6_DataWidth_10bit_Set();
 *     ADC1_Ch6_Sample_Time_Set( 10 );
 *     ADC1_Sequence0_Set( ADC1_MASK_VDH );
 *     ADC1_Ch6_WaitForRead_Set();
 *
 *     while ( ADC1_Ch6_ResultValid_Get() == 0u )
 *     {
 *     }
 *
 *     adc_result = ADC1_VDH_Result_Get();
 *
 *     return(adc_result);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_VDH_Attenuator_Zlow_Set(void)
{
  Field_Mod32(&MF->VMON_SEN_CTRL.reg, MF_VMON_SEN_CTRL_VMON_SEN_HRESO_5V_Pos, MF_VMON_SEN_CTRL_VMON_SEN_HRESO_5V_Msk, 0u);
}

/** \brief clears ADC1 Channel 0 Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Channel 0 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch0_Int_En();
 *   if (ADC1->IS.bit.CH0_STS == 1u)
 *   {
 *     ADC1_CH0_CALLBACK();
 *     ADC1_Ch0_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch0_Int_Clr(void)
{
  Field_Wrt32(&ADC1->ICLR.reg, ADC1_ICLR_CH0_ICLR_Pos, ADC1_ICLR_CH0_ICLR_Msk, 1u);
}

/** \brief clears ADC1 Channel 1 Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Channel 1 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch1_Int_En();
 *   if (ADC1->IS.bit.CH1_STS == 1u)
 *   {
 *     ADC1_CH1_CALLBACK();
 *     ADC1_Ch1_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch1_Int_Clr(void)
{
  Field_Wrt32(&ADC1->ICLR.reg, ADC1_ICLR_CH1_ICLR_Pos, ADC1_ICLR_CH1_ICLR_Msk, 1u);
}

/** \brief clears ADC1 Channel 2 Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Channel 2 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch2_Int_En();
 *   if (ADC1->IS.bit.CH2_STS == 1u)
 *   {
 *     ADC1_CH2_CALLBACK();
 *     ADC1_Ch2_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch2_Int_Clr(void)
{
  Field_Wrt32(&ADC1->ICLR.reg, ADC1_ICLR_CH2_ICLR_Pos, ADC1_ICLR_CH2_ICLR_Msk, 1u);
}

/** \brief clears ADC1 Channel 3 Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Channel 3 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch3_Int_En();
 *   if (ADC1->IS.bit.CH3_STS == 1u)
 *   {
 *     ADC1_CH3_CALLBACK();
 *     ADC1_Ch3_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch3_Int_Clr(void)
{
  Field_Wrt32(&ADC1->ICLR.reg, ADC1_ICLR_CH3_ICLR_Pos, ADC1_ICLR_CH3_ICLR_Msk, 1u);
}

/** \brief clears ADC1 Channel 4 Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Channel 4 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch4_Int_En();
 *   if (ADC1->IS.bit.CH4_STS == 1u)
 *   {
 *     ADC1_CH4_CALLBACK();
 *     ADC1_Ch4_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch4_Int_Clr(void)
{
  Field_Wrt32(&ADC1->ICLR.reg, ADC1_ICLR_CH4_ICLR_Pos, ADC1_ICLR_CH4_ICLR_Msk, 1u);
}

/** \brief clears ADC1 Channel 5 Interrupt flag.
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Channel 5 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch5_Int_En();
 *   if (ADC1->IS.bit.CH5_STS == 1u)
 *   {
 *     ADC1_CH5_CALLBACK();
 *     ADC1_Ch5_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch5_Int_Clr(void)
{
  Field_Wrt32(&ADC1->ICLR.reg, ADC1_ICLR_CH5_ICLR_Pos, ADC1_ICLR_CH5_ICLR_Msk, 1u);
}

/** \brief clears ADC1 Channel 6 Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Channel 6 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch6_Int_En();
 *   if (ADC1->IS.bit.CH6_STS == 1u)
 *   {
 *     ADC1_CH6_CALLBACK();
 *     ADC1_Ch6_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch6_Int_Clr(void)
{
  Field_Wrt32(&ADC1->ICLR.reg, ADC1_ICLR_CH6_ICLR_Pos, ADC1_ICLR_CH6_ICLR_Msk, 1u);
}

/** \brief clears Exceptional Interrupt Measurement (EIM) flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Exceptional Interrupt Measurement (EIM).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_EIM_En();
 *   ADC1_EIM_Int_En();
 *   if (ADC1->IS.bit.EIM_STS == 1u)
 *   {
 *     ADC1_EIM_CALLBACK();
 *     ADC1_EIM_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_EIM_Int_Clr(void)
{
  Field_Wrt32(&ADC1->ICLR.reg, ADC1_ICLR_EIM_ICLR_Pos, ADC1_ICLR_EIM_ICLR_Msk, 1u);
}

/** \brief clears Exceptional Sequence Measurement (ESM) flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Exceptional Sequence Measurement (ESM).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_ESM_Int_En();
 *   if (ADC1->IS.bit.ESM_STS == 1u)
 *   {
 *     ADC1_ESM_CALLBACK();
 *     ADC1_ESM_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_ESM_Int_Clr(void)
{
  Field_Wrt32(&ADC1->ICLR.reg, ADC1_ICLR_ESM_ICLR_Pos, ADC1_ICLR_ESM_ICLR_Msk, 1u);
}

/** \brief enables ADC1 Channel 0 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Channel 0 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch0_Int_En();
 *   if (ADC1->IS.bit.CH0_STS == 1u)
 *   {
 *     ADC1_CH0_CALLBACK();
 *     ADC1_Ch0_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch0_Int_En(void)
{
  Field_Mod32(&ADC1->IE.reg, ADC1_IE_CH0_IE_Pos, ADC1_IE_CH0_IE_Msk, 1u);
}

/** \brief disables ADC1 Channel 0 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Channel 0 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch0_Int_En();
 *   if (ADC1->IS.bit.CH0_STS == 1u)
 *   {
 *     ADC1_CH0_CALLBACK();
 *     ADC1_Ch0_Int_Clr();
 *   }
 *   ADC1_Ch0_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch0_Int_Dis(void)
{
  Field_Mod32(&ADC1->IE.reg, ADC1_IE_CH0_IE_Pos, ADC1_IE_CH0_IE_Msk, 0u);
}

/** \brief enables ADC1 Channel 1 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Channel 1 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch1_Int_En();
 *   if (ADC1->IS.bit.CH1_STS == 1u)
 *   {
 *     ADC1_CH1_CALLBACK();
 *     ADC1_Ch1_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch1_Int_En(void)
{
  Field_Mod32(&ADC1->IE.reg, ADC1_IE_CH1_IE_Pos, ADC1_IE_CH1_IE_Msk, 1u);
}

/** \brief disables ADC1 Channel 1 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Channel 1 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch1_Int_En();
 *   if (ADC1->IS.bit.CH1_STS == 1u)
 *   {
 *     ADC1_CH1_CALLBACK();
 *     ADC1_Ch1_Int_Clr();
 *   }
 *   ADC1_Ch1_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch1_Int_Dis(void)
{
  Field_Mod32(&ADC1->IE.reg, ADC1_IE_CH1_IE_Pos, ADC1_IE_CH1_IE_Msk, 0u);
}

/** \brief enables ADC1 Channel 2 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Channel 2 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch2_Int_En();
 *   if (ADC1->IS.bit.CH2_STS == 1u)
 *   {
 *     ADC1_CH2_CALLBACK();
 *     ADC1_Ch2_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch2_Int_En(void)
{
  Field_Mod32(&ADC1->IE.reg, ADC1_IE_CH2_IE_Pos, ADC1_IE_CH2_IE_Msk, 1u);
}

/** \brief disables ADC1 Channel 2 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Channel 2 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch2_Int_En();
 *   if (ADC1->IS.bit.CH2_STS == 1u)
 *   {
 *     ADC1_CH2_CALLBACK();
 *     ADC1_Ch2_Int_Clr();
 *   }
 *   ADC1_Ch2_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch2_Int_Dis(void)
{
  Field_Mod32(&ADC1->IE.reg, ADC1_IE_CH2_IE_Pos, ADC1_IE_CH2_IE_Msk, 0u);
}

/** \brief enables ADC1 Channel 3 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Channel 3 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch3_Int_En();
 *   if (ADC1->IS.bit.CH3_STS == 1u)
 *   {
 *     ADC1_CH3_CALLBACK();
 *     ADC1_Ch3_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch3_Int_En(void)
{
  Field_Mod32(&ADC1->IE.reg, ADC1_IE_CH3_IE_Pos, ADC1_IE_CH3_IE_Msk, 1u);
}

/** \brief disables ADC1 Channel 3 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Channel 3 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch3_Int_En();
 *   if (ADC1->IS.bit.CH3_STS == 1u)
 *   {
 *     ADC1_CH3_CALLBACK();
 *     ADC1_Ch3_Int_Clr();
 *   }
 *   ADC1_Ch3_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch3_Int_Dis(void)
{
  Field_Mod32(&ADC1->IE.reg, ADC1_IE_CH3_IE_Pos, ADC1_IE_CH3_IE_Msk, 0u);
}

/** \brief enables ADC1 Channel 4 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Channel 4 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch4_Int_En();
 *   if (ADC1->IS.bit.CH4_STS == 1u)
 *   {
 *     ADC1_CH4_CALLBACK();
 *     ADC1_Ch4_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch4_Int_En(void)
{
  Field_Mod32(&ADC1->IE.reg, ADC1_IE_CH4_IE_Pos, ADC1_IE_CH4_IE_Msk, 1u);
}

/** \brief disables ADC1 Channel 4 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Channel 4 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch4_Int_En();
 *   if (ADC1->IS.bit.CH4_STS == 1u)
 *   {
 *     ADC1_CH4_CALLBACK();
 *     ADC1_Ch4_Int_Clr();
 *   }
 *   ADC1_Ch4_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch4_Int_Dis(void)
{
  Field_Mod32(&ADC1->IE.reg, ADC1_IE_CH4_IE_Pos, ADC1_IE_CH4_IE_Msk, 0u);
}

/** \brief enables ADC1 Channel 5 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Channel 5 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch5_Int_En();
 *   if (ADC1->IS.bit.CH5_STS == 1u)
 *   {
 *     ADC1_CH5_CALLBACK();
 *     ADC1_Ch5_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch5_Int_En(void)
{
  Field_Mod32(&ADC1->IE.reg, ADC1_IE_CH5_IE_Pos, ADC1_IE_CH5_IE_Msk, 1u);
}

/** \brief disables ADC1 Channel 5 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Channel 5 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch5_Int_En();
 *   if (ADC1->IS.bit.CH5_STS == 1u)
 *   {
 *     ADC1_CH5_CALLBACK();
 *     ADC1_Ch5_Int_Clr();
 *   }
 *   ADC1_Ch5_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch5_Int_Dis(void)
{
  Field_Mod32(&ADC1->IE.reg, ADC1_IE_CH5_IE_Pos, ADC1_IE_CH5_IE_Msk, 0u);
}

/** \brief enables ADC1 Channel 6 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Channel 6 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch6_Int_En();
 *   if (ADC1->IS.bit.CH6_STS == 1u)
 *   {
 *     ADC1_CH6_CALLBACK();
 *     ADC1_Ch6_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch6_Int_En(void)
{
  Field_Mod32(&ADC1->IE.reg, ADC1_IE_CH6_IE_Pos, ADC1_IE_CH6_IE_Msk, 1u);
}

/** \brief disables ADC1 Channel 6 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Channel 6 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch6_Int_En();
 *   if (ADC1->IS.bit.CH6_STS == 1u)
 *   {
 *     ADC1_CH6_CALLBACK();
 *     ADC1_Ch6_Int_Clr();
 *   }
 *   ADC1_Ch6_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch6_Int_Dis(void)
{
  Field_Mod32(&ADC1->IE.reg, ADC1_IE_CH6_IE_Pos, ADC1_IE_CH6_IE_Msk, 0u);
}

/** \brief enables Exceptional Interrupt Measurement (EIM).
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Exceptional Interrupt Measurement (EIM).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_EIM_En();
 *   ADC1_EIM_Int_En();
 *   if (ADC1->IS.bit.EIM_STS == 1u)
 *   {
 *     ADC1_EIM_CALLBACK();
 *     ADC1_EIM_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_EIM_Int_En(void)
{
  Field_Mod32(&ADC1->IE.reg, ADC1_IE_EIM_IE_Pos, ADC1_IE_EIM_IE_Msk, 1u);
}

/** \brief disables Exceptional Interrupt Measurement (EIM).
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Exceptional Interrupt Measurement (EIM).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_EIM_En();
 *   ADC1_EIM_Int_En();
 *   if (ADC1->IS.bit.EIM_STS == 1u)
 *   {
 *     ADC1_EIM_CALLBACK();
 *     ADC1_EIM_Int_Clr();
 *   }
 *   ADC1_EIM_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_EIM_Int_Dis(void)
{
  Field_Mod32(&ADC1->IE.reg, ADC1_IE_EIM_IE_Pos, ADC1_IE_EIM_IE_Msk, 0u);
}

/** \brief enables Exceptional Sequence Measurement (ESM).
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Exceptional Sequence Measurement (ESM).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_ESM_Int_En();
 *   if (ADC1->IS.bit.ESM_STS == 1u)
 *   {
 *     ADC1_ESM_CALLBACK();
 *     ADC1_ESM_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_ESM_Int_En(void)
{
  Field_Mod32(&ADC1->IE.reg, ADC1_IE_ESM_IE_Pos, ADC1_IE_ESM_IE_Msk, 1u);
}

/** \brief disables Exceptional Sequence Measurement (ESM).
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Exceptional Sequence Measurement (ESM).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_ESM_Int_En();
 *   if (ADC1->IS.bit.ESM_STS == 1u)
 *   {
 *     ADC1_ESM_CALLBACK();
 *     ADC1_ESM_Int_Clr();
 *   }
 *   ADC1_ESM_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_ESM_Int_Dis(void)
{
  Field_Mod32(&ADC1->IE.reg, ADC1_IE_ESM_IE_Pos, ADC1_IE_ESM_IE_Msk, 0u);
}

/** \brief sets the VDH Monitoring Input Attenuator Input Range to 0 - 30V.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 6 (VDH) and sets the Attenuator Input Range to 0 - 28V.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 data;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_VDH );
 *     ADC1_VDH_Attenuator_On();
 *     ADC1_VDH_Attenuator_Range_0_30V_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_VDH_Attenuator_Range_0_30V_Set(void)
{
  Field_Mod32(&MF->VMON_SEN_CTRL.reg, MF_VMON_SEN_CTRL_VMON_SEN_SEL_INRANGE_Pos, MF_VMON_SEN_CTRL_VMON_SEN_SEL_INRANGE_Msk, ADC1_VDH_Attenuator_Range_0_30V);
}
/** \brief sets the VDH Monitoring Input Attenuator Input Range to 0 - 22V.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 6 (VDH) and sets the Attenuator Input Range to 0 - 20V.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 data;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_VDH );
 *     ADC1_VDH_Attenuator_On();
 *     ADC1_VDH_Attenuator_Range_0_20V_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_VDH_Attenuator_Range_0_20V_Set(void)
{
  Field_Mod32(&MF->VMON_SEN_CTRL.reg, MF_VMON_SEN_CTRL_VMON_SEN_SEL_INRANGE_Pos, MF_VMON_SEN_CTRL_VMON_SEN_SEL_INRANGE_Msk, ADC1_VDH_Attenuator_Range_0_20V);
}


/** \brief Reads the VDH Monitoring Input Attenuator Input Range Configuration.
 *
 * \retval 1 0 - 30V Range is selected.
 * \retval 0 0 - 20V Range is selected.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 6 (VDH) and reads the Attenuator Input Range.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 data;
 *
 *     ADC1_Power_On();
 *     ADC1_ANON_Set( ADC1_ANON_NORMAL );
 *     ADC1_DIVA_Set( 1 );
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_VDH );
 *     ADC1_VDH_Attenuator_On();
 *     data = ADC1_VDH_Attenuator_Range_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint8 ADC1_VDH_Attenuator_Range_Get(void)
{
  return ( u8_Field_Rd32(&MF->VMON_SEN_CTRL.reg, MF_VMON_SEN_CTRL_VMON_SEN_SEL_INRANGE_Pos, MF_VMON_SEN_CTRL_VMON_SEN_SEL_INRANGE_Msk) );
}

/*******************************************************************************
**                     Global Inline Function Definitions                     **
*******************************************************************************/
INLINE void ADC1_SetEIMChannel(uint8 channel)
{
  ADC1_EIM_Channel_Set(channel);
} /* End of ADC1_SetEIMChannel */

INLINE void ADC1_SetSwMode_Channel(uint8 channel)
{
  ADC1_SW_Ch_Sel(channel);
} /* End of ADC1_SetSwMode_Channel */

INLINE void ADC1_SetMode(uint8 mode)
{
  /* Set the "mode" input to ADC1->SQ_FB.bit.SQ_RUN */
  Field_Mod32(&ADC1->SQ_FB.reg, ADC1_SQ_FB_SQ_RUN_Pos, ADC1_SQ_FB_SQ_RUN_Msk, mode);
} /* End of ADC1_SetMode */

INLINE void ADC1_SetSocSwMode(uint8 Ch)
{
  ADC1_SW_Ch_Sel(Ch);
  ADC1_SOC_Set();
} /* End of ADC1_SetSocSwMode */

INLINE bool ADC1_GetEocSwMode(void)
{
  bool res = false;

  if (ADC1_EOC_Sts() == (uint8)1)
  {
    res = true;
  }

  return (res);
} /* End of ADC1_GetEocSwMode */

INLINE bool ADC1_GetSwModeResult(uint16 *pVar)
{
  uint8 channel;
  channel = u8_Field_Rd32(&ADC1->CTRL_STS.reg, ADC1_CTRL_STS_IN_MUX_SEL_Pos, ADC1_CTRL_STS_IN_MUX_SEL_Msk);
  return (ADC1_GetChResult(pVar, channel));
} /* End of ADC1_GetSwModeResult */

INLINE bool ADC1_GetSwModeResult_mV(uint16 *pVar_mV)
{
  uint8 channel;
  channel = u8_Field_Rd32(&ADC1->CTRL_STS.reg, ADC1_CTRL_STS_IN_MUX_SEL_Pos, ADC1_CTRL_STS_IN_MUX_SEL_Msk);
  return (ADC1_GetChResult_mV(pVar_mV, channel));
} /* End of ADC1_GetSwModeResult */

INLINE bool ADC1_Busy(void)
{
  bool res = false;

  if (ADC1_Busy_Sts() == (uint8)1)
  {
    res = true;
  }

  return (res);
} /* End of ADC1_GetSwModeResult */

INLINE void ADC1_EIM_Trigger_Select(TADC1_TRIGG_SEL trigsel)
{
  /* Set the "trigsel" input to ADC1->CHx_EIM.bit.TRIG_SEL */
  Field_Mod32(&ADC1->CHx_EIM.reg, ADC1_CHx_EIM_TRIG_SEL_Pos, ADC1_CHx_EIM_TRIG_SEL_Msk, (uint8)trigsel);
}

INLINE void ADC1_EIM_Repeat_Counter_Set(TADC1_EIM_REP_CNT repcnt)
{
  /* Set the "repcnt" input to ADC1->CHx_EIM.bit.REP */
  Field_Mod32(&ADC1->CHx_EIM.reg, ADC1_CHx_EIM_REP_Pos, ADC1_CHx_EIM_REP_Msk, (uint8)repcnt);
}

INLINE void ADC1_ESM_Trigger_Select(TADC1_TRIGG_SEL trigsel)
{
  /* Set the "trigsel" input to ADC1->CHx_ESM.bit.TRIG_SEL */
  Field_Mod32(&ADC1->CHx_ESM.reg, ADC1_CHx_ESM_TRIG_SEL_Pos, ADC1_CHx_ESM_TRIG_SEL_Msk, (uint8)trigsel);
}

INLINE bool ADC1_isEndOfConversion(void)
{
  bool res = false;

  if (ADC1_EOC_Sts() == (uint8)1)
  {
    res = true;
  }

  return (res);
}

INLINE bool ADC1_isEIMactive(void)
{
  bool res = false;

  if (ADC1_EIM_Active_Sts() == (uint8)1)
  {
    res = true;
  }

  return (res);
}

INLINE bool ADC1_isESMactive(void)
{
  bool res = false;

  if (ADC1_ESM_Active_Sts() == (uint8)1)
  {
    res = true;
  }

  return (res);
}

INLINE TADC1_ANON ADC1_ANON_Sts(void)
{
  TADC1_ANON_U res;
  res.dword = u32_Field_Rd32(&ADC1->GLOBSTR.reg, ADC1_GLOBSTR_ANON_ST_Pos, ADC1_GLOBSTR_ANON_ST_Msk);
  return (res.adc1_anon);
}

#endif /* ADC1_H */
