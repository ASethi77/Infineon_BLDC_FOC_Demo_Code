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
#include "csa.h"
#include "adc1.h"
#include "csa_defines.h"
#include "RTE_Components.h"

/*******************************************************************************
**                         Global Function Definitions                        **
*******************************************************************************/

void CSA_Init(void)
{
#if (CONFIGWIZARD == 1)
  CSA->CTRL.reg = (uint32) CSA_CTRL;
#else /* (CONFIGWIZARD == 2) */
  CSA->CTRL.reg = (uint32) MF_CSA_CTRL;
#endif
  /* connect CSA input to ADC1 CH1 inputs */
  MF->P2_ADCSEL_CTRL.bit.ADC1_CH1_SEL = 1u;
}


uint16 CSA_Offset_Get(void)
{
  uint16 offset;
  uint32 adc1_dwsel;
  uint32 adc1_sq_fb;
  uint32 adc1_stc_0_3;
  uint32 adc1_globctr;
  uint32 adc1_ie;
  uint32 adc1_ctrl_sts;
  /* save ADC1 settings */
  adc1_dwsel    = ADC1->DWSEL.reg;
  adc1_sq_fb    = ADC1->SQ_FB.reg;
  adc1_stc_0_3  = ADC1->STC_0_3.reg;
  adc1_globctr  = ADC1->GLOBCTR.reg;
  adc1_ie       = ADC1->IE.reg;
  adc1_ctrl_sts = ADC1->CTRL_STS.reg;
  /* disable VZERO */
  CSA->CTRL.bit.VZERO = 0u;
  /* diable ADC1 Ch1 interrupt */
  ADC1_Ch1_Int_Dis();
  /* enable ADC1 if not yet done */
  ADC1_Power_On();
  /* set the ADC1 to normal operation */
  ADC1_ANON_Set((uint8)ADC1_ANON_NORMAL);

  /* check the fSYS and program the ADC1 accordingly */
  if (SystemFrequency > 24000000u)
  {
    /* divide ADC1 clock by 2 if fSYS is greater than 24MHz */
    ADC1_DIVA_Set(1);
  }
  else
  {
    /* program ADC1 clock as fSYS */
    ADC1_DIVA_Set(0);
  }

  /* set ADC1.Ch1 to 10-bit data width */
  ADC1_Ch1_DataWidth_10bit_Set();
  /* set a sample time of 10 ticks for Ch1 */
  ADC1_Ch1_Sample_Time_Set(10);
  /* switch to software mode */
  ADC1_Software_Mode_Sel();

  /* wait in case ADC1 is still busy */
  while (ADC1_Busy() == true) {}

  /* set Ch1 (CSA) for software conversion mode */
  ADC1_SW_Ch_Sel(ADC1_CSA);
  /* start conversion */
  ADC1_SOC_Set();

  /* wait until conversion is done */
  while (ADC1_isEndOfConversion() == false) {}

  /* pick up the ADC1 Ch2 value */
  offset = ADC1_Ch1_Result_Get();
  /* clear the Ch1 interrupt flag */
  ADC1_Ch1_Int_Clr();
  /* restore ADC1 settings */
  ADC1->DWSEL.reg    = adc1_dwsel;
  ADC1->SQ_FB.reg    = adc1_sq_fb;
  ADC1->STC_0_3.reg  = adc1_stc_0_3;
  ADC1->GLOBCTR.reg  = adc1_globctr;
  ADC1->IE.reg       = adc1_ie;
  ADC1->CTRL_STS.reg = adc1_ctrl_sts;
  /* return the CSA offset */
  return (offset);
}
