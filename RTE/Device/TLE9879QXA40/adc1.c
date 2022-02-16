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
**                                  Includes                                  **
*******************************************************************************/
#include "adc1.h"
/** \brief ADC2 definition of VREF is required by VAREF Enable */
#include "adc2.h"
#include "wdt1.h"
#include "sfr_access.h"
#include "RTE_Components.h"

/** \brief digital value of VAREF = 4.75V */
#define VAREF_4750mV ((uint32)(((4.750F * 0.219F) * 1023.0F) / ADC2_VREF))

/*******************************************************************************
**                         Global Function Definitions                        **
*******************************************************************************/
void ADC1_Init(void)
{
  /* Clock Configuration ********************************************************/
  ADC1->GLOBCTR.reg = (uint32) ADC1_GLOBCTR;
  /* Sequencer1-4 configuration */
  ADC1->SQ1_4.reg = (uint32) ADC1_SQ1_4;
  /* Sequencer5-8 configuration */
  ADC1->SQ5_8.reg = (uint32) ADC1_SQ5_8;
  ADC1->SQ_FB.reg = (uint32) ADC1_SQ_FB;
  /* EIS / EMS configuration ***************************************************/
#if (CONFIGWIZARD == 1)
  ADC1->CHx_EIM.reg = (uint32) ADC1_CHX_EIM;
  ADC1->CHx_ESM.reg = (uint32) ADC1_ESM;
#else /* (CONFIGWIZARD == 2) */
  ADC1->CHx_EIM.reg = (uint32) ADC1_CHx_EIM;
  ADC1->CHx_ESM.reg = (uint32) ADC1_CHx_ESM;
#endif
  /* Channel control registers configuration ***********************************/
  /* DWSEL register */
  ADC1->DWSEL.reg = (uint32) ADC1_DWSEL;
  /* STC register */
  ADC1->STC_0_3.reg = (uint32) ADC1_STC_0_3;
  ADC1->STC_4_7.reg = (uint32) ADC1_STC_4_7;
  /* Result Register Configuration **********************************************/
#if (CONFIGWIZARD == 1)
  ADC1->RES_OUT0.reg = (uint32) ADC1_RES0;
  ADC1->RES_OUT1.reg = (uint32) ADC1_RES1;
  ADC1->RES_OUT2.reg = (uint32) ADC1_RES2;
  ADC1->RES_OUT3.reg = (uint32) ADC1_RES3;
  ADC1->RES_OUT4.reg = (uint32) ADC1_RES4;
  ADC1->RES_OUT5.reg = (uint32) ADC1_RES5;
  ADC1->RES_OUT6.reg = (uint32) ADC1_RES6;
  ADC1->RES_OUT_EIM.reg = (uint32) ADC1_RES_EIM;
#else /* (CONFIGWIZARD == 2) */
  ADC1->RES_OUT0.reg = (uint32) ADC1_RES_OUT0;
  ADC1->RES_OUT1.reg = (uint32) ADC1_RES_OUT1;
  ADC1->RES_OUT2.reg = (uint32) ADC1_RES_OUT2;
  ADC1->RES_OUT3.reg = (uint32) ADC1_RES_OUT3;
  ADC1->RES_OUT4.reg = (uint32) ADC1_RES_OUT4;
  ADC1->RES_OUT5.reg = (uint32) ADC1_RES_OUT5;
  ADC1->RES_OUT6.reg = (uint32) ADC1_RES_OUT6;
  ADC1->RES_OUT_EIM.reg = (uint32) ADC1_RES_OUT_EIM;
#endif
  /* Interrupt configuration ****************************************************/
  ADC1->IE.reg = (uint32) ADC1_IE;
  /* Set VMON Attenuator */
  MF->VMON_SEN_CTRL.reg = MF_VMON_SEN_CTRL;
  /* Set VAREF */
  MF->REF2_CTRL.reg = MF_REF2_CTRL;
  /* Enable ADC1 ****************************************************************/
  /* ADC1 is in normal operation. */
  SCU->PMCON1.bit.ADC1_DIS = 0;
  /* Normal Operation */
  ADC1_ANON_Set((uint8)ADC1_ANON_NORMAL);
  /* ADC1 is switched on */
  ADC1_Power_On();
#if (ADC1_XML_VERSION >= 10302)
  /* Port2 input selection */
  MF->P2_ADCSEL_CTRL.reg = MF_P2_ADCSEL_CTRL;
#endif
}

bool VAREF_Enable(void)
{
  uint16 timeout;
  uint32 temp;
  bool res;
  /* set default result 'false' */
  res = false;
  /* disable VAREF */
  MF->REF2_CTRL.bit.VREF5V_PD_N = 0u;
  /* save lower threshold for ADC2.Ch6 (VAREF) */
  temp = ADC2->TH6_9_LOWER.reg;
  /* set lower threshold for ADC2.Ch6 to 0 */
  ADC2->TH6_9_LOWER.bit.CH6 = 0u;
  /* clear VAREF undervoltage/overload status flag */
  timeout = 5u;

  while (((SCUPM->SYS_IS.reg & (uint32)0x5000u) != 0u) && (timeout > (uint16)0))
  {
    SCUPM->SYS_ISCLR.reg = (uint32)0x5000u;
    Delay_us(100u);
    timeout--;
  }

  if (timeout > (uint16)0)
  {
    /* enable VAREF */
    MF->REF2_CTRL.bit.VREF5V_PD_N = 1u;
    /* wait until VAREF has reached at least 4.75V again */
    timeout = 10u;

    while ((ADC2->FILT_OUT6.reg < VAREF_4750mV) && (timeout > (uint16)0))
    {
      Delay_us(100u);
      timeout--;
    }

    if (timeout > (uint16)0)
    {
      /* VAREF is enabled */
      res = true;
    }
  }

  /* restore ADC2.Ch6 lower threshold */
  ADC2->TH6_9_LOWER.reg = temp;
  return (res);
}

bool ADC1_GetChResult(uint16 *pVar, uint8 channel)
{
  const volatile uint32 *pBaseAddr;
  uint32 addr;
  uint8 vf;
  uint16 idx;
  bool res;
  res = false;
  /* violation: cast from pointer to unsigned int [MISRA Rule 45]*/
  addr = (uint32)&ADC1->RES_OUT0.reg;
  idx = (uint16)((uint16)channel << 2u);
  addr -= idx;
  /* violation: cast from unsigned int to pointer [MISRA Rule 45]*/
  pBaseAddr = (volatile uint32 *) addr;
  /* Pos-/Msk-Fields are taken from Channel0, these values are the same for each result register */
  vf = u1_Field_Rd32(pBaseAddr, ADC1_RES_OUT0_VF0_Pos, ADC1_RES_OUT0_VF0_Msk);

  /* update the value only if there is valid data in result register */
  if (vf == (uint8)1)
  {
    /* Pos-/Msk-Fields are taken from Channel0, these values are the same for each result register */
    *pVar = u16_Field_Rd32(pBaseAddr, ADC1_RES_OUT0_OUT_CH0_Pos, ADC1_RES_OUT0_OUT_CH0_Msk);
    *pVar >>= 2u;
    res = true;
  }

  return (res);
} /* End of ADC1_GetChResult */

bool ADC1_GetChResult_mV(uint16 *pVar_mV, uint8 channel)
{
  uint16 var;
  bool res;
  res = false;

  if (ADC1_GetChResult(&var, channel) == true)
  {
    /* ADC1 Voltage(mV) = (10bit_value * VREF_5000(mV)) / MAX_10BIT_VALUE */
    *pVar_mV = (uint16)((var * (uint16)ADC1_VREF_5000mV) / (uint16)1023);

    /* calculate attenuator in case of VDH */
    if (channel == (uint8)ADC1_CH6)
    {
      /* check ADC1 VDH Attenuator Range: 3_18V, or 3_28V */
      if (ADC1_VDH_Attenuator_Range_Get() == (uint8)ADC1_VDH_Attenuator_Range_0_20V)
      {
        /* ADC1 Voltage(mV) = (10bit_value * VREF_22000(mV)) / MAX_10BIT_VALUE */
        *pVar_mV = (uint16)((var * (uint16)ADC1_VREF_22000mV) / (uint16)1023);
      }
      else
      {
        /* ADC1 Voltage(mV) = (10bit_value * VREF_30000(mV)) / MAX_10BIT_VALUE */
        *pVar_mV = (uint16)((var * (uint16)ADC1_VREF_30000mV) / (uint16)1023);
      }
    }

    res = true;
  }

  return (res);
}

bool ADC1_GetEIMResult(uint16 *pVar)
{
  uint8 vf;
  bool res;
  res = false;
  vf = u1_Field_Rd32(&ADC1->RES_OUT_EIM.reg, ADC1_RES_OUT_EIM_VF8_Pos, ADC1_RES_OUT_EIM_VF8_Msk);

  if (vf == (uint8)1)
  {
    *pVar = u16_Field_Rd32(&ADC1->RES_OUT_EIM.reg, ADC1_RES_OUT_EIM_OUT_CH_EIM_Pos, ADC1_RES_OUT_EIM_OUT_CH_EIM_Msk);
    *pVar >>= 2u;
    res = true;
  }

  return (res);
} /* End of ADC1_GetEIMResult */

bool ADC1_GetEIMResult_mV(uint16 *pVar_mV)
{
  uint16 var;
  bool res;
  uint8 eim_ch;
  res = false;

  if (ADC1_GetEIMResult(&var) == true)
  {
    /* ADC1 Voltage(mV) = (10bit_value * VREF_5000(mV)) / MAX_10BIT_VALUE */
    *pVar_mV = (uint16)((var * (uint16)ADC1_VREF_5000mV) / (uint16)1023);
    /* calculate attenuator in case of VDH */
    eim_ch = u8_Field_Rd32(&ADC1->CHx_EIM.reg, ADC1_CHx_EIM_CHx_Pos, ADC1_CHx_EIM_CHx_Msk);

    if (eim_ch == (uint8)ADC1_CH6)
    {
      /* check ADC1 VDH Attenuator Range: 3_18V, or 3_28V */
      if (ADC1_VDH_Attenuator_Range_Get() == (uint8)ADC1_VDH_Attenuator_Range_0_20V)
      {
        /* ADC1 Voltage(mV) = (10bit_value * VREF_22000(mV)) / MAX_10BIT_VALUE */
        *pVar_mV = (uint16)((var * (uint16)ADC1_VREF_22000mV) / (uint16)1023);
      }
      else
      {
        /* ADC1 Voltage(mV) = (10bit_value * VREF_30000(mV)) / MAX_10BIT_VALUE */
        *pVar_mV = (uint16)((var * (uint16)ADC1_VREF_30000mV) / (uint16)1023);
      }
    }

    res = true;
  }

  return (res);
} /* End of ADC1_GetEIMResult */
