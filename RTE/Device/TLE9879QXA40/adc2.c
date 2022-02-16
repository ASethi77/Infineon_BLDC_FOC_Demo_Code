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
#include "adc2.h"

/*******************************************************************************
**                         Global Function Definitions                        **
*******************************************************************************/

void ADC2_Init(void)
{
#if ((ADC2_CTRL2 & 1u) != 0u)
  ADC2->CTRL1.reg = (uint32) ADC2_CTRL1;
  ADC2->CTRL2.reg = (uint32) ADC2_CTRL2;
  ADC2->CTRL4.reg = (uint32) ADC2_CTRL4;
  ADC2->CTRL_STS.reg = (uint32)(ADC2_CTRL_STS | 1u);
  ADC2->TH0_3_LOWER.reg = (uint32) ADC2_TH0_3_LOWER;
  ADC2->TH0_3_UPPER.reg = (uint32) ADC2_TH0_3_UPPER;
  ADC2->TH4_5_LOWER.reg = (uint32) ADC2_TH4_5_LOWER;
  ADC2->TH4_5_UPPER.reg = (uint32) ADC2_TH4_5_UPPER;
  ADC2->TH6_9_LOWER.reg = (uint32) ADC2_TH6_9_LOWER;
  /*ADC2->TH6_9_UPPER is protected and cannot be changed in user mode*/
  ADC2->FILT_LO_CTRL.reg = ADC2_FILT_LO_CTRL;
  ADC2->FILT_UP_CTRL.reg = ADC2_FILT_UP_CTRL;
  ADC2->FILTCOEFF0_5.reg = (uint32) ADC2_FILTCOEFF0_5;
#if (ADC2_XML_VERSION >= 10300)
  ADC2->CNT0_3_LOWER.reg = (uint32) ADC2_CNT0_3_LOWER;
  ADC2->CNT0_3_UPPER.reg = (uint32) ADC2_CNT0_3_UPPER;
  ADC2->CNT4_5_LOWER.reg = (uint32) ADC2_CNT4_5_LOWER;
  ADC2->CNT4_5_UPPER.reg = (uint32) ADC2_CNT4_5_UPPER;
  ADC2->MMODE0_5.reg = (uint32) ADC2_MMODE0_5;
#endif
#endif
}
