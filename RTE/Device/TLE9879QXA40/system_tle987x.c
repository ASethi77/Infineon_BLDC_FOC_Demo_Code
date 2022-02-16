/*
 ***********************************************************************************************************************
 *
 * Copyright (c) 2017, Infineon Technologies AG
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
#include "tle987x.h"
#include "bsl_defines.h"
#include "scu.h"
#include "wdt1.h"
#include "tle_variants.h"
#include "RTE_Components.h"
#include "system_tle987x.h"

/*----------------------------------------------------------------------------
  Define BSL parameter
 *----------------------------------------------------------------------------*/
#if defined (__CC_ARM) || defined(__ARMCC_VERSION)
  /* ARMCC v5: __CC_ARM, ARMCC v6: __ARMCC_VERSION */
  #if (CONFIGWIZARD == 1)
    #if (NAC_NAD_EN == 1)
    const uint32 p_NACNAD __attribute__((section(sNADStart), used)) = (uint32)NAD_NAC;
    #endif
  #else /* (CONFIGWIZARD == 2) */
    #if (BSL_NAC_NAD_EN == 1u)
    const uint32 p_NACNAD __attribute__((section(sNADStart), used)) = (uint32)BSL_NAD_NAC;
    #endif
  #endif
#elif defined(__IAR_SYSTEMS_ICC__)
  /* IAR Compiler */
  #if (CONFIGWIZARD == 1)
    #if (NAC_NAD_EN == 1)
    const uint32 p_NACNAD @ "NACStart" = (uint32)NAD_NAC;
    #endif
  #else /* (CONFIGWIZARD == 2) */
    #if (BSL_NAC_NAD_EN == 1u)
    const uint32 p_NACNAD @ "NACStart" = (uint32)BSL_NAD_NAC;
    #endif
  #endif
#else
  #error Unsupported compiler!
#endif

void SystemInit(void)
{
  /* Vector table relocation */
  CPU->VTOR.reg   = ProgFlashStart;
  SCU_ClkInit();
  SysTick_Init();
  WDT1_Init();
  /* erratas */
  /* clear IE flags */
  TIMER2->T2CON1.reg = 0;
  TIMER21->T2CON1.reg = 0;
}
