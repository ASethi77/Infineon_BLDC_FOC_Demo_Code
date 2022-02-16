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
#include "gpt12e.h"

/*******************************************************************************
**                         Global Function Definitions                        **
*******************************************************************************/

void GPT12E_Init(void)
{
  GPT12E->T2CON.reg = GPT12E_T2CON;
  GPT12E->T2.reg = GPT12E_T2;
  GPT12E->T3CON.reg = GPT12E_T3CON;
  GPT12E->T3.reg = GPT12E_T3;
  GPT12E->T4CON.reg = GPT12E_T4CON;
  GPT12E->T4.reg = GPT12E_T4;
  GPT12E->T5CON.reg = GPT12E_T5CON;
  GPT12E->T5.reg = GPT12E_T5;
  GPT12E->T6CON.reg = GPT12E_T6CON;
  GPT12E->T6.reg = GPT12E_T6;
  GPT12E->CAPREL.reg = GPT12E_CAPREL;
  GPT12E->PISEL.reg = GPT12E_PISEL;
}


bool GPT12E_T3_Interval_Timer_Setup(uint32 timer_interval_us)
{
  bool res;
  uint64 timer_ticks;
  uint32 gpt_frequency;
  uint32 clk_prescaler;
  /* set initial result to false */
  res = false;
  /* get GPT1 clock prescaler */
  gpt_frequency = SystemFrequency >> (GPT12E_GPT1_Clk_Prescaler_Get() + (uint16)2);
  /* calculate timer ticks based on GPT1 frequency */
  timer_ticks = ((uint64)timer_interval_us * ((uint64)gpt_frequency / (uint64)1000)) / (uint64)1000;
  /* preload t3 clock prescaler with 'div 1' */
  clk_prescaler = (uint32)GPT_Clk_Div_1;

  /* as long as calculated timer ticks is larger than the T3 value register **
  ** can hold (16bit), increase the prescaler by one, and divide the timer  **
  ** ticks by 2                                                             */
  while (timer_ticks > (uint64)0xFFFFu)
  {
    clk_prescaler++;
    timer_ticks >>= 1u;
  }

  /* if the clock prescaler is within the allowed range */
  if (clk_prescaler <= (uint32)GPT_Clk_Div_128)
  {
    /* select T3 Mode as Timer */
    GPT12E_T3_Mode_Timer_Sel();
    /* program the calculated prescaler */
    GPT12E_T3_Mode_Timer_Clk_Prescaler_Sel((uint8)clk_prescaler);
    /* external up/down count control disabled */
    GPT12E_T3_UpDownCount_Ext_Dis();
    /* select down count */
    GPT12E_T3_DownCount_Sel();
    /* set T3 value (timer ticks) */
    GPT12E_T3_Value_Set((uint16)timer_ticks);
    /* set T2 to Reload Mode */
    GPT12E_T2_Mode_Reload_Sel();
    /* set T2 value as reload value */
    GPT12E_T2_Value_Set((uint16)timer_ticks);
    /* set T2 reload trigger to use T3Our (T3OTL) */
    GPT12E_T2_Mode_Reload_Input_T3Out_Sel();
    /* set T2 to trigger reload every T3Out (T3OTL) toggle */
    GPT12E_T2_Mode_Reload_Input_Falling_T3Out_En();
    GPT12E_T2_Mode_Reload_Input_Rising_T3Out_En();
    /* set result to true */
    res = true;
  }

  return (res);
}


bool GPT12E_T6_Interval_Timer_Setup(uint32 timer_interval_us)
{
  bool res;
  uint64 timer_ticks;
  uint32 gpt_frequency;
  uint32 clk_prescaler;
  /* set initial result to false */
  res = false;
  /* get GPT2 clock prescaler */
  gpt_frequency = SystemFrequency >> (GPT12E_GPT2_Clk_Prescaler_Get() + (uint16)1);
  /* calculate timer ticks based on GPT2 frequency */
  timer_ticks = ((uint64)timer_interval_us * ((uint64)gpt_frequency / (uint64)1000)) / (uint64)1000;
  /* preload t6 clock prescaler with 'div 1' */
  clk_prescaler = (uint32)GPT_Clk_Div_1;

  /* as long as calculated timer ticks is larger than the T6 value register **
  ** can hold (16bit), increase the prescaler by one, and divide the timer  **
  ** ticks by 2                                                             */
  while (timer_ticks > (uint64)0xFFFF)
  {
    clk_prescaler++;
    timer_ticks >>= 1u;
  }

  /* if the clock prescaler is within the allowed range */
  if (clk_prescaler <= (uint32)GPT_Clk_Div_128)
  {
    /* select T6 Mode as Timer */
    GPT12E_T6_Mode_Timer_Sel();
    /* program the calculated prescaler */
    GPT12E_T6_Mode_Timer_Clk_Prescaler_Sel((uint8)clk_prescaler);
    /* external up/down count control disabled */
    GPT12E_T6_UpDownCount_Ext_Dis();
    /* select down count */
    GPT12E_T6_DownCount_Sel();
    /* set T6 value (timer ticks) */
    GPT12E_T6_Value_Set((uint16)timer_ticks);
    /* set T6 reload value (timer ticks) */
    GPT12E_T6_Reload_Value_Set((uint16)timer_ticks);
    /* set T6 reload by CAPREL enable */
    GPT12E_T6_Reload_En();
    /* set result to true */
    res = true;
  }

  return (res);
}

