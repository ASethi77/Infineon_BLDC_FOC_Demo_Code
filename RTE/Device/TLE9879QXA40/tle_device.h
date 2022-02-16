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
 * \file     tle_device.h
 *
 * \brief    SDK initialization
 *
 * \version  V1.1.1
 * \date     21. Jul 2020
 */

/*******************************************************************************
**                             Author(s) Identity                             **
********************************************************************************
** Initials     Name                                                          **
** ---------------------------------------------------------------------------**
** DM           Daniel Mysliwitz                                              **
** JO           Julia Ott                                                     **
** BG           Blandine Guillot                                              **
*******************************************************************************/

/*******************************************************************************
**                          Revision Control History                          **
********************************************************************************
** V0.1.0: 2017-04-18, DM:   Initial version                                  **
** V0.1.1: 2017-11-21, DM:   SDADC added                                      **
**                           MISRA 2012 compliance, the following PC-Lint     **
**                           rules are globally deactivated:                  **
**                           - Info 793: ANSI/ISO limit of 6 'significant     **
**                             characters in an external identifier           **
**                           - Info 718: Symbol '...' undeclared, assumed to  **
**                             return int [MISRA Rule 20], [MISRA Rule 71]    **
**                           - Info 746: call to function '...' not made in   **
**                             the presence of a prototype [MISRA Rule 71]    **
**                           void CMSIS_Irq_Dis(void) added                   **
**                           void CMSIS_Irq_En(void) added                    **
**                           void CMSIS_NOP(void) added                       **
** V1.0.8: 2018-12-05, DM:   Revision history for tle_device.c/.h files       **
**                           merged together                                  **
** V1.0.9: 2018-12-10, JO:   Moved memory layout and defines for the device   **
**                           variant to new file tle_variants.h               **
** V1.1.0: 2020-04-15, BG:   Updated revision history format                  **
** V1.1.1: 2020-07-21, BG:   EP-439: Formatted .h/.c files                    **
*******************************************************************************/

#ifndef _TLE_DEVICE_H
#define _TLE_DEVICE_H

#include "tle_variants.h"
#include "RTE_Components.h"

#ifdef RTE_DEVICE_SDK_BROM
  #include "bootrom.h"
#endif
#ifdef RTE_DEVICE_SDK_WDT1
  #include "wdt1.h"
#endif
#ifdef RTE_DEVICE_SDK_SCU
  #include "scu.h"
#endif
#ifdef RTE_DEVICE_SDK_PMU
  #include "pmu.h"
#endif
#ifdef RTE_DEVICE_SDK_ADC1
  #include "adc1.h"
#endif
#ifdef RTE_DEVICE_SDK_ADC2
  #include "adc2.h"
#endif
#ifdef RTE_DEVICE_SDK_ADC34
  #include "sdadc.h"
#endif
#ifdef RTE_DEVICE_SDK_BDRV
  #include "bdrv.h"
#endif
#ifdef RTE_DEVICE_SDK_CCU6
  #include "ccu6.h"
#endif
#ifdef RTE_DEVICE_SDK_CSA
  #include "csa.h"
#endif
#ifdef RTE_DEVICE_SDK_GPT12E
  #include "gpt12e.h"
#endif
#ifdef RTE_DEVICE_SDK_INT
  #include "int.h"
#endif
#ifdef RTE_DEVICE_SDK_ISR
  #include "isr.h"
#endif
#ifdef RTE_DEVICE_SDK_LIN
  #include "lin.h"
#endif
#ifdef RTE_DEVICE_SDK_MON
  #include "mon.h"
#endif
#ifdef RTE_DEVICE_SDK_PORT
  #include "port.h"
#endif
#ifdef RTE_DEVICE_SDK_SSC
  #include "ssc.h"
#endif
#ifdef RTE_DEVICE_SDK_TIMER2X
  #include "timer2x.h"
#endif
#ifdef RTE_DEVICE_SDK_TIMER3
  #include "timer3.h"
#endif
#ifdef RTE_DEVICE_SDK_UART
  #include "uart.h"
#endif
#ifdef RTE_DEVICE_SDK_DMA
  #include "dma.h"
#endif

/** \brief Initializes the TLE modules.
 *
 * \ingroup tle_api
 */
void TLE_Init(void);

#endif
