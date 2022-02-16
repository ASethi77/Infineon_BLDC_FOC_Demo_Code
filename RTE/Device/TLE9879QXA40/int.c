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
#include "int.h"
#include "int_defines.h"
#include "scu_defines.h"
#include "RTE_Components.h"

/*******************************************************************************
**                         Global Function Definitions                        **
*******************************************************************************/

void INT_Init(void)
{
  /**************************************************************************
  ** Interrupt Control                                                     **
  **************************************************************************/
  SCU->NMICLR.reg = (uint8) SCU_NMICON;
  SCU->NMICON.reg = (uint8) SCU_NMICON;
  SCU->EXICON0.reg = (uint8) SCU_EXICON0;
  SCU->MODIEN1.reg = (uint8) SCU_MODIEN1;
  SCU->MODIEN2.reg = (uint8) SCU_MODIEN2;
  SCU->MODIEN3.reg = (uint8) SCU_MODIEN3;
  SCU->MODIEN4.reg = (uint8) SCU_MODIEN4;
  SCU->GPT12IEN.reg = (uint8) SCU_GPT12IEN;
  SCUPM->SYS_SUPPLY_IRQ_CLR.reg = (uint32) 0x00FF00FF;
  SCUPM->SYS_ISCLR.reg = (uint32)0x3F3FFFC7;
#if (CONFIGWIZARD == 1)
  SCUPM->SYS_SUPPLY_IRQ_CTRL.reg = (uint32) SCU_SYS_SUPPLY_IRQ_CTRL;
  SCUPM->SYS_IRQ_CTRL.reg = SCU_SYS_IRQ_CTRL;
#else
  SCUPM->SYS_SUPPLY_IRQ_CTRL.reg = (uint32) SCUPM_SYS_SUPPLY_IRQ_CTRL;
  SCUPM->SYS_IRQ_CTRL.reg = SCUPM_SYS_IRQ_CTRL;
#endif /* (CONFIGWIZARD == 1) */
  SCU->EDCCON.reg = (uint8) SCU_EDCCON;
#ifdef SCU_BDRV_IRQ_CTRL
  SCUPM->BDRV_IRQ_CTRL.reg = (uint32) SCU_BDRV_IRQ_CTRL;
#endif
#ifdef SCUPM_BDRV_IRQ_CTRL
  SCUPM->BDRV_IRQ_CTRL.reg = (uint32) SCUPM_BDRV_IRQ_CTRL;
#endif
  CPU->NVIC_IPR0.reg = (uint32) CPU_NVIC_IPR0;
  CPU->NVIC_IPR1.reg = (uint32) CPU_NVIC_IPR1;
  CPU->NVIC_IPR2.reg = (uint32) CPU_NVIC_IPR2;
  CPU->NVIC_IPR3.reg = (uint32) CPU_NVIC_IPR3;
  CPU->NVIC_ISER0.reg = (uint32) CPU_NVIC_ISER0;
  SCU->IEN0.reg = (uint8) SCU_IEN0;
#if (INT_XML_VERSION >= 10109)
  SCU->DMAIRC1CLR.reg = (uint8)0xFF;
  SCU->DMAIRC2CLR.reg = (uint8)0xFF;
#ifdef SCU_DMAIEN1
  SCU->DMAIEN1.reg = (uint8) SCU_DMAIEN1;
#endif
#ifdef SCU_DMAIEN2
  SCU->DMAIEN2.reg = (uint8) SCU_DMAIEN2;
#endif
#endif
#if (CONFIGWIZARD == 1)
#if (INT_XML_VERSION >= 10300)
  CPU->SHPR3.reg = (uint32) CPU_NVIC_SHPR3;
#endif
#else /* (CONFIGWIZARD == 2) */
  CPU->SHPR3.reg = (uint32) CPU_SHPR3;
#endif
}
