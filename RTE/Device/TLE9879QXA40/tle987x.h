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
 * \file     tle987x.h
 *
 * \brief    CMSIS register HeaderFile
 *
 * \version  V3.0.7
 * \date     21. Jul 2020
 *
 * \note This file violates [MISRA Rule 45]
 */

/*******************************************************************************
**                             Author(s) Identity                             **
********************************************************************************
**                                                                            **
** Initials     Name                                                          **
** ---------------------------------------------------------------------------**
** BG           Blandine Guillot                                              **
** JO           Julia Ott                                                     **
*******************************************************************************/

/*******************************************************************************
**                          Revision Control History                          **
********************************************************************************
** V3.0.4: 2020-04-15, BG:   Initial version of revision history              **
** V3.0.5: 2020-07-16, JO:   EP-392: Added field ADC2->CTRL2.bit.SEL_TS_COUNT **
** V3.0.6: 2020-07-14, JO:   EP-431: Added '#pragma clang diagnostic ignored' **
**                           to disable compiler warnings (-Wpadded,          **
**                           -Wcovered-switch-default, -Wself-assign) for     **
**                           ARMCC v6                                         **
** V3.0.7: 2020-07-21, BG:   EP-439: Formatted .h/.c files                    **
*******************************************************************************/


/** @addtogroup Infineon
  * @{
  */


/** @addtogroup TLE987x
  * @{
  */


#ifndef TLE987X_H
#define TLE987X_H

#ifdef __cplusplus
extern "C" {
#endif


/** @addtogroup Configuration_of_CMSIS
  * @{
  */



/* =========================================================================================================================== */
/* ================                                Interrupt Number Definition                                ================ */
/* =========================================================================================================================== */

typedef enum
{
  /* =======================================  ARM Cortex-M3 Specific Interrupt Numbers  ======================================== */
  Reset_IRQn                = -15,              /*!< -15  Reset Vector, invoked on Power up and warm reset                     */
  NonMaskableInt_IRQn       = -14,              /*!< -14  Non maskable Interrupt, cannot be stopped or preempted               */
  HardFault_IRQn            = -13,              /*!< -13  Hard Fault, all classes of Fault                                     */
  MemoryManagement_IRQn     = -12,              /*!< -12  Memory Management, MPU mismatch, including Access Violation
                                                     and No Match                                                              */
  BusFault_IRQn             = -11,              /*!< -11  Bus Fault, Pre-Fetch-, Memory Access Fault, other address/memory
                                                     related Fault                                                             */
  UsageFault_IRQn           = -10,              /*!< -10  Usage Fault, i.e. Undef Instruction, Illegal State Transition        */
  SVCall_IRQn               =  -5,              /*!< -5 System Service Call via SVC instruction                                */
  DebugMonitor_IRQn         =  -4,              /*!< -4 Debug Monitor                                                          */
  PendSV_IRQn               =  -2,              /*!< -2 Pendable request for system service                                    */
  SysTick_IRQn              =  -1,              /*!< -1 System Tick Timer                                                      */
  /* ==========================================  TLE987x Specific Interrupt Numbers  =========================================== */
  GPT1_Int                  =   0,              /*!< 0  Interrupt node 0: GPT1 Block                                           */
  GPT2_Int                  =   1,              /*!< 1  Interrupt node 1: GPT2 Block                                           */
  ADC2_Tmr3_Int             =   2,              /*!< 2  Interrupt node 2: ADC2, Timer3, BEMF, ADC3/4                           */
  ADC1_VREF5_Int            =   3,              /*!< 3  Interrupt node 3: ADC1, VAREF                                          */
  CCU6_SR0_Int              =   4,              /*!< 4  Interrupt node 4: CCU6 node0                                           */
  CCU6_SR1_Int              =   5,              /*!< 5  Interrupt node 5: CCU6 node1                                           */
  CCU6_SR2_Int              =   6,              /*!< 6  Interrupt node 6: CCU6 node2                                           */
  CCU6_SR3_Int              =   7,              /*!< 7  Interrupt node 7: CCU6 node3                                           */
  SSC1_Int                  =   8,              /*!< 8  Interrupt node 8: SSC1                                                 */
  SSC2_Int                  =   9,              /*!< 9  Interrupt node 9: SSC2                                                 */
  UART1_LIN_Tmr2_Int        =  10,              /*!< 10 Interrupt node10: UART1(ASC,LIN), Timer2                               */
  UART2_Tmr21_EINT2_Int     =  11,              /*!< 11 Interrupt node11: UART2, Timer21, EINT2                                */
  EXINT0_MON_Int            =  12,              /*!< 12 Interrupt node12: EINT0, MON                                           */
  EXINT1_Int                =  13,              /*!< 13 Interrupt node13: EINT1                                                */
  BDRV_CP_Int               =  14,              /*!< 14 Interrupt node14: BDRV, Charge Pump                                    */
  DMA_Int                   =  15               /*!< 15 Interrupt node15: DMA                                                  */
} IRQn_Type;



/* =========================================================================================================================== */
/* ================                           Processor and Core Peripheral Section                           ================ */
/* =========================================================================================================================== */

/* ===========================  Configuration of the ARM Cortex-M3 Processor and Core Peripherals  =========================== */
#define __CM3_REV                 0x0000U       /*!< CM3 Core Revision                                                         */
#define __NVIC_PRIO_BITS               4        /*!< Number of Bits used for Priority Levels                                   */
#define __Vendor_SysTickConfig         0        /*!< Set to 1 if different SysTick Config is used                              */
#define __MPU_PRESENT                  0        /*!< MPU present or not                                                        */
#define __FPU_PRESENT                  0        /*!< FPU present or not                                                        */


/** @} */ /* End of group Configuration_of_CMSIS */

#include "core_cm3.h"                           /*!< ARM Cortex-M3 processor and core peripherals                              */
#include "system_tle987x.h"                     /*!< TLE987x System                                                            */

#ifndef __IM                                    /*!< Fallback for older CMSIS versions                                         */
#define __IM   __I
#endif
#ifndef __OM                                    /*!< Fallback for older CMSIS versions                                         */
#define __OM   __O
#endif
#ifndef __IOM                                   /*!< Fallback for older CMSIS versions                                         */
#define __IOM  __IO
#endif

#ifdef UNIT_TESTING_LV2
#undef __IM
#define __IM volatile
#endif

/* Ignore the following warnings from ARMCC v6:
* - tle987x.h: warning: padding size of 'struct ...' with ... bits to alignment boundary [-Wpadded] (~1000 occurences)
* - dma.c: warning: default label in switch which covers all enumeration values [-Wcovered-switch-default] (2 occurences)
* - scu.c: warning: explicitly assigning value of variable of type 'uint8' (aka 'unsigned char') to itself [-Wself-assign] (2 occurences)
*/
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wself-assign"
#endif

/* =========================================================================================================================== */
/* ================                            Device Specific Peripheral Section                             ================ */
/* =========================================================================================================================== */


/** @addtogroup Device_Peripheral_peripherals
  * @{
  */



/* =========================================================================================================================== */
/* ================                                           ADC1                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief ADC1 Module (ADC1)
  */

typedef struct                                  /*!< (@ 0x40004000) ADC1 Structure                                             */
{

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) ADC1 Control and Status Register                           */

    struct
    {
      __IOM uint32_t PD_N       : 1;            /*!< [0..0] ADC1 Power Down Signal                                             */
      __IM  uint32_t            : 1;
      __IOM uint32_t SOC        : 1;            /*!< [2..2] ADC1 Start of Conversion (software mode)                           */
      __IM  uint32_t EOC        : 1;            /*!< [3..3] ADC1 End of Conversion (software mode)                             */
      __IOM uint32_t IN_MUX_SEL : 3;            /*!< [6..4] Channel for software mode                                          */
    } bit;
  } CTRL_STS;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) Global Control Register                                    */

    struct
    {
      __IOM uint32_t DIVA       : 6;            /*!< [5..0] Divide Factor for the Analog internal clock: 0x00=Fadci
                                                     = Fadc, 0x01=Fadci = Fadc/2, 0x02=Fadci = Fadc/3, 0x02=...,
                                                     0x3F=Fadci = Fadc/64,                                                     */
      __IM  uint32_t            : 2;
      __IOM uint32_t ANON       : 2;            /*!< [9..8] Analog Part Switched On                                            */
    } bit;
  } GLOBCTR;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) Channel Settings Bits for Exceptional Interrupt
                                                                    Measurement                                                */

    struct
    {
      __IOM uint32_t CHx        : 3;            /*!< [2..0] Channel set for exceptional interrupt measurement (EIM)            */
      __IM  uint32_t            : 1;
      __IOM uint32_t REP        : 3;            /*!< [6..4] Repeat count for exceptional interrupt measurement (EIM)           */
      __IM  uint32_t            : 9;
      __IOM uint32_t TRIG_SEL   : 3;            /*!< [18..16] Trigger selection for exceptional interrupt measurement
                                                     (EIM)                                                                     */
    } bit;
  } CHx_EIM;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) Channel Settings Bits for Exceptional Sequence
                                                                    Measurement                                                */

    struct
    {
      __IOM uint32_t ESM_0      : 8;            /*!< [7..0] Channel Sequence for Exceptional Sequence Measurement
                                                     (ESM)                                                                     */
      __IM  uint32_t            : 8;
      __IOM uint32_t TRIG_SEL   : 3;            /*!< [18..16] Trigger selection for exceptional interrupt measurement
                                                     (ESM)                                                                     */
    } bit;
  } CHx_ESM;
  __IM  uint32_t  RESERVED[2];

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000018) Measurement Channel Enable Bits for Cycle 1 -
                                                                    4                                                          */

    struct
    {
      __IOM uint32_t SQ1        : 8;            /*!< [7..0] Sequence 1 channel enable                                          */
      __IOM uint32_t SQ2        : 8;            /*!< [15..8] Sequence 2 channel enable                                         */
      __IOM uint32_t SQ3        : 8;            /*!< [23..16] Sequence 3 channel enable                                        */
      __IOM uint32_t SQ4        : 8;            /*!< [31..24] Sequence 4 channel enable                                        */
    } bit;
  } SQ1_4;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x0000001C) Measurement Channel Enable Bits for Cycle 5 -
                                                                    8                                                          */

    struct
    {
      __IOM uint32_t SQ5        : 8;            /*!< [7..0] Sequence 5 channel enable                                          */
      __IOM uint32_t SQ6        : 8;            /*!< [15..8] Sequence 6 channel enable                                         */
      __IOM uint32_t SQ7        : 8;            /*!< [23..16] Sequence 7 channel enable                                        */
      __IOM uint32_t SQ8        : 8;            /*!< [31..24] Sequence 8 channel enable                                        */
    } bit;
  } SQ5_8;
  __IM  uint32_t  RESERVED1;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000024) Measurement Channel Data Width Selection                   */

    struct
    {
      __IOM uint32_t ch0        : 1;            /*!< [0..0] Data Width channel 0                                               */
      __IOM uint32_t ch1        : 1;            /*!< [1..1] Data Width channel 1                                               */
      __IOM uint32_t ch2        : 1;            /*!< [2..2] Data Width channel 2                                               */
      __IOM uint32_t ch3        : 1;            /*!< [3..3] Data Width channel 3                                               */
      __IOM uint32_t ch4        : 1;            /*!< [4..4] Data Width channel 4                                               */
      __IOM uint32_t ch5        : 1;            /*!< [5..5] Data Width channel 5                                               */
      __IOM uint32_t ch6        : 1;            /*!< [6..6] Data Width channel 6                                               */
      __IOM uint32_t ch7        : 1;            /*!< [7..7] Data Width channel 7                                               */
    } bit;
  } DWSEL;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000028) Measurement Channel Sample Time Control 0 - 3              */

    struct
    {
      __IOM uint32_t ch0        : 8;            /*!< [7..0] Sample Time Control for Channel 0                                  */
      __IOM uint32_t ch1        : 8;            /*!< [15..8] Sample Time Control for Channel 1                                 */
      __IOM uint32_t ch2        : 8;            /*!< [23..16] Sample Time Control for Channel 2                                */
      __IOM uint32_t ch3        : 8;            /*!< [31..24] Sample Time Control for Channel 3                                */
    } bit;
  } STC_0_3;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x0000002C) Measurement Channel Sample Time Control 4 - 7              */

    struct
    {
      __IOM uint32_t ch4        : 8;            /*!< [7..0] Sample Time Control for Channel 4                                  */
      __IOM uint32_t ch5        : 8;            /*!< [15..8] Sample Time Control for Channel 5                                 */
      __IOM uint32_t ch6        : 8;            /*!< [23..16] Sample Time Control for Channel 6                                */
      __IOM uint32_t ch7        : 8;            /*!< [31..24] Sample Time Control for Channel 7                                */
    } bit;
  } STC_4_7;
  __IM  uint32_t  RESERVED2[4];

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000040) ADC1 Output Channel EIM                                    */

    struct
    {
      __IM  uint32_t OUT_CH_EIM : 12;           /*!< [11..0] ADC1 output result value EIM                                      */
      __IM  uint32_t            : 4;
      __IOM uint32_t WFR8       : 1;            /*!< [16..16] Wait for Read Mode                                               */
      __IM  uint32_t VF8        : 1;            /*!< [17..17] Valid Flag                                                       */
      __IM  uint32_t OF8        : 1;            /*!< [18..18] Overrun Flag                                                     */
    } bit;
  } RES_OUT_EIM;
  __IM  uint32_t  RESERVED3[3];

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000050) Sequencer Feedback Register                                */

    struct
    {
      __IM  uint32_t            : 8;
      __IOM uint32_t SQ_RUN     : 1;            /*!< [8..8] ADC1 Sequencer RUN                                                 */
      __IM  uint32_t EIM_ACTIVE : 1;            /*!< [9..9] ADC1 EIM active                                                    */
      __IM  uint32_t ESM_ACTIVE : 1;            /*!< [10..10] ADC1 ESM active                                                  */
      __IM  uint32_t SQx        : 3;            /*!< [13..11] Current Active Sequence in Sequencer Mode                        */
      __IM  uint32_t            : 2;
      __IM  uint32_t CHx        : 3;            /*!< [18..16] Current Channel                                                  */
    } bit;
  } SQ_FB;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000054) ADC1 Output Channel 7                                      */

    struct
    {
      __IM  uint32_t OUT_CH7    : 12;           /*!< [11..0] ADC1 output result value channel 7                                */
      __IM  uint32_t            : 4;
      __IOM uint32_t WFR7       : 1;            /*!< [16..16] Wait for Read Mode                                               */
      __IM  uint32_t VF7        : 1;            /*!< [17..17] Valid Flag                                                       */
      __IM  uint32_t OF7        : 1;            /*!< [18..18] Overrun Flag                                                     */
    } bit;
  } RES_OUT7;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000058) ADC1 Output Channel 6                                      */

    struct
    {
      __IM  uint32_t OUT_CH6    : 12;           /*!< [11..0] ADC1 output result value channel 6                                */
      __IM  uint32_t            : 4;
      __IOM uint32_t WFR6       : 1;            /*!< [16..16] Wait for Read Mode                                               */
      __IM  uint32_t VF6        : 1;            /*!< [17..17] Valid Flag                                                       */
      __IM  uint32_t OF6        : 1;            /*!< [18..18] Overrun Flag                                                     */
    } bit;
  } RES_OUT6;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x0000005C) ADC1 Output Channel 5                                      */

    struct
    {
      __IM  uint32_t OUT_CH5    : 12;           /*!< [11..0] ADC1 output result value channel 5                                */
      __IM  uint32_t            : 4;
      __IOM uint32_t WFR5       : 1;            /*!< [16..16] Wait for Read Mode                                               */
      __IM  uint32_t VF5        : 1;            /*!< [17..17] Valid Flag                                                       */
      __IM  uint32_t OF5        : 1;            /*!< [18..18] Overrun Flag                                                     */
    } bit;
  } RES_OUT5;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000060) ADC1 Output Channel 4                                      */

    struct
    {
      __IM  uint32_t OUT_CH4    : 12;           /*!< [11..0] ADC1 output result value channel 4                                */
      __IM  uint32_t            : 4;
      __IOM uint32_t WFR4       : 1;            /*!< [16..16] Wait for Read Mode                                               */
      __IM  uint32_t VF4        : 1;            /*!< [17..17] Valid Flag                                                       */
      __IM  uint32_t OF4        : 1;            /*!< [18..18] Overrun Flag                                                     */
    } bit;
  } RES_OUT4;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000064) ADC1 Output Channel 3                                      */

    struct
    {
      __IM  uint32_t OUT_CH3    : 12;           /*!< [11..0] ADC1 output result value channel 3                                */
      __IM  uint32_t            : 4;
      __IOM uint32_t WFR3       : 1;            /*!< [16..16] Wait for Read Mode                                               */
      __IM  uint32_t VF3        : 1;            /*!< [17..17] Valid Flag                                                       */
      __IM  uint32_t OF3        : 1;            /*!< [18..18] Overrun Flag                                                     */
    } bit;
  } RES_OUT3;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000068) ADC1 Output Channel 2                                      */

    struct
    {
      __IM  uint32_t OUT_CH2    : 12;           /*!< [11..0] ADC1 output result value channel 2                                */
      __IM  uint32_t            : 4;
      __IOM uint32_t WFR2       : 1;            /*!< [16..16] Wait for Read Mode                                               */
      __IM  uint32_t VF2        : 1;            /*!< [17..17] Valid Flag                                                       */
      __IM  uint32_t OF2        : 1;            /*!< [18..18] Overrun Flag                                                     */
    } bit;
  } RES_OUT2;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x0000006C) ADC1 Output Channel 1                                      */

    struct
    {
      __IM  uint32_t OUT_CH1    : 12;           /*!< [11..0] ADC1 output result value channel 1                                */
      __IM  uint32_t            : 4;
      __IOM uint32_t WFR1       : 1;            /*!< [16..16] Wait for Read Mode                                               */
      __IM  uint32_t VF1        : 1;            /*!< [17..17] Valid Flag                                                       */
      __IM  uint32_t OF1        : 1;            /*!< [18..18] Overrun Flag                                                     */
    } bit;
  } RES_OUT1;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000070) ADC1 Output Channel 0                                      */

    struct
    {
      __IM  uint32_t OUT_CH0    : 12;           /*!< [11..0] ADC1 output reset value channel 0                                 */
      __IM  uint32_t            : 4;
      __IOM uint32_t WFR0       : 1;            /*!< [16..16] Wait for Read Mode                                               */
      __IM  uint32_t VF0        : 1;            /*!< [17..17] Valid Flag                                                       */
      __IM  uint32_t OF0        : 1;            /*!< [18..18] Overrun Flag                                                     */
    } bit;
  } RES_OUT0;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000074) Global Status Register                                     */

    struct
    {
      __IM  uint32_t BUSY       : 1;            /*!< [0..0] Analog Part Busy                                                   */
      __IM  uint32_t SAMPLE     : 1;            /*!< [1..1] Sample Phase Indication                                            */
      __IM  uint32_t            : 1;
      __IM  uint32_t CHNR       : 3;            /*!< [5..3] Channel Number                                                     */
      __IM  uint32_t            : 2;
      __IM  uint32_t ANON_ST    : 2;            /*!< [9..8] Analog Part Switched On                                            */
    } bit;
  } GLOBSTR;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000078) ADC1 Interrupt Status Register                             */

    struct
    {
      __IM  uint32_t CH0_STS    : 1;            /*!< [0..0] ADC1 Channel 0 Interrupt Status                                    */
      __IM  uint32_t CH1_STS    : 1;            /*!< [1..1] ADC1 Channel 1 Interrupt Status                                    */
      __IM  uint32_t CH2_STS    : 1;            /*!< [2..2] ADC1 Channel 2 Interrupt Status                                    */
      __IM  uint32_t CH3_STS    : 1;            /*!< [3..3] ADC1 Channel 3 Interrupt Status                                    */
      __IM  uint32_t CH4_STS    : 1;            /*!< [4..4] ADC1 Channel 4 Interrupt Status                                    */
      __IM  uint32_t CH5_STS    : 1;            /*!< [5..5] ADC1 Channel 5 Interrupt Status                                    */
      __IM  uint32_t CH6_STS    : 1;            /*!< [6..6] ADC1 Channel 6 Interrupt Status                                    */
      __IM  uint32_t CH7_STS    : 1;            /*!< [7..7] ADC1 Channel 7 Interrupt Status                                    */
      __IM  uint32_t EIM_STS    : 1;            /*!< [8..8] Exceptional Interrupt Measurement (EIM) Status                     */
      __IM  uint32_t ESM_STS    : 1;            /*!< [9..9] Exceptional Sequence Measurement (ESM) Status                      */
    } bit;
  } IS;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x0000007C) ADC1 Interrupt Enable Register                             */

    struct
    {
      __IOM uint32_t CH0_IE     : 1;            /*!< [0..0] ADC1 Channel 0 Interrupt Enable                                    */
      __IOM uint32_t CH1_IE     : 1;            /*!< [1..1] ADC1 Channel 1 Interrupt Enable                                    */
      __IOM uint32_t CH2_IE     : 1;            /*!< [2..2] ADC1 Channel 2 Interrupt Enable                                    */
      __IOM uint32_t CH3_IE     : 1;            /*!< [3..3] ADC1 Channel 3 Interrupt Enable                                    */
      __IOM uint32_t CH4_IE     : 1;            /*!< [4..4] ADC1 Channel 4 Interrupt Enable                                    */
      __IOM uint32_t CH5_IE     : 1;            /*!< [5..5] ADC1 Channel 5 Interrupt Enable                                    */
      __IOM uint32_t CH6_IE     : 1;            /*!< [6..6] ADC1 Channel 6 Interrupt Enable                                    */
      __IOM uint32_t CH7_IE     : 1;            /*!< [7..7] ADC1 Channel 7 Interrupt Enable                                    */
      __IOM uint32_t EIM_IE     : 1;            /*!< [8..8] Exceptional Interrupt Measurement (EIM) Interrupt Enable           */
      __IOM uint32_t ESM_IE     : 1;            /*!< [9..9] Exceptional Sequence Measurement (ESM) Interrupt Enable            */
    } bit;
  } IE;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000080) ADC1 Interrupt Status Clear Register                       */

    struct
    {
      __OM  uint32_t CH0_ICLR   : 1;            /*!< [0..0] ADC1 Channel 0 Interrupt Status Clear                              */
      __OM  uint32_t CH1_ICLR   : 1;            /*!< [1..1] ADC1 Channel 1 Interrupt Status Clear                              */
      __OM  uint32_t CH2_ICLR   : 1;            /*!< [2..2] ADC1 Channel 2 Interrupt Status Clear                              */
      __OM  uint32_t CH3_ICLR   : 1;            /*!< [3..3] ADC1 Channel 3 Interrupt Status Clear                              */
      __OM  uint32_t CH4_ICLR   : 1;            /*!< [4..4] ADC1 Channel 4 Interrupt Status Clear                              */
      __OM  uint32_t CH5_ICLR   : 1;            /*!< [5..5] ADC1 Channel 5 Interrupt Status Clear                              */
      __OM  uint32_t CH6_ICLR   : 1;            /*!< [6..6] ADC1 Channel 6 Interrupt Status Clear                              */
      __OM  uint32_t CH7_ICLR   : 1;            /*!< [7..7] ADC1 Channel 7 Interrupt Status Clear                              */
      __OM  uint32_t EIM_ICLR   : 1;            /*!< [8..8] Exceptional Interrupt Measurement (EIM) Status Clear               */
      __OM  uint32_t ESM_ICLR   : 1;            /*!< [9..9] Exceptional Sequence Measurement (ESM) Status Clear                */
    } bit;
  } ICLR;
} ADC1_Type;                                    /*!< Size = 132 (0x84)                                                         */



/* =========================================================================================================================== */
/* ================                                           ADC2                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief ADC2 Module (ADC2)
  */

typedef struct                                  /*!< (@ 0x4801C000) ADC2 Structure                                             */
{

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) ADC2 Control and Status Register                           */

    struct
    {
      __IM  uint32_t            : 17;
      __IOM uint32_t VS_RANGE   : 1;            /*!< [17..17] ADC2 Channel 1 Range Selection                                   */
    } bit;
  } CTRL_STS;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) Sequencer Feedback Register                                */

    struct
    {
      __IM  uint32_t SQ_FB      : 4;            /*!< [3..0] Current Sequence that caused software mode                         */
      __IM  uint32_t            : 4;
      __IM  uint32_t SQ_STOP    : 1;            /*!< [8..8] ADC2 Sequencer Stop Signal for DPP                                 */
      __IM  uint32_t EIM_ACTIVE : 1;            /*!< [9..9] ADC2 EIM active                                                    */
      __IM  uint32_t ESM_ACTIVE : 1;            /*!< [10..10] ADC2 ESM active                                                  */
      __IM  uint32_t SQx        : 4;            /*!< [14..11] Current Active Sequencer                                         */
      __IM  uint32_t            : 1;
      __IM  uint32_t CHx        : 5;            /*!< [20..16] Current ADC2 Channel                                             */
    } bit;
  } SQ_FB;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) Channel Settings Bits for Exceptional Interrupt
                                                                    Measurement                                                */

    struct
    {
      __IOM uint32_t CHx        : 5;            /*!< [4..0] Channel set for exceptional interrupt measurement (EIM)            */
      __IM  uint32_t            : 3;
      __IOM uint32_t REP        : 3;            /*!< [10..8] Repeat count for exceptional interrupt measurement (EIM)          */
      __IOM uint32_t EN         : 1;            /*!< [11..11] Exceptional interrupt measurement (EIM) Trigger Event
                                                     enable                                                                    */
      __IOM uint32_t SEL        : 1;            /*!< [12..12] Exceptional interrupt measurement (EIM) Trigger Trigger
                                                     select                                                                    */
    } bit;
  } CHx_EIM;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) Channel Settings Bits for Exceptional Sequence
                                                                    Measurement                                                */

    struct
    {
      __IOM uint32_t ESM_0      : 6;            /*!< [5..0] Channel Sequence for Exceptional Sequence Measurement
                                                     (ESM)                                                                     */
      __IOM uint32_t ESM_1      : 4;            /*!< [9..6] Channel Sequence for Exceptional Sequence Measurement
                                                     (ESM)                                                                     */
      __IOM uint32_t SEL        : 1;            /*!< [10..10] Exceptional Sequence Measurement Trigger Select                  */
      __IM  uint32_t            : 5;
      __IOM uint32_t EN         : 1;            /*!< [16..16] Enable for Exceptional Sequence Measurement Trigger
                                                     Event                                                                     */
      __IM  uint32_t STS        : 1;            /*!< [17..17] Exceptional Sequence Measurement is finished                     */
    } bit;
  } CHx_ESM;
  __IM  uint32_t  RESERVED;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000014) Measurement Unit Control Register 1                        */

    struct
    {
      __IOM uint32_t CALIB_EN   : 6;            /*!< [5..0] Calibration Enable for Channels 0 to 5                             */
    } bit;
  } CTRL1;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000018) Measurement Unit Control Register 2                        */

    struct
    {
      __IOM uint32_t MCM_PD_N   : 1;            /*!< [0..0] Power Down Signal for MCM                                          */
      __IOM uint32_t TS_SD_SEL_CONF : 1;        /*!< [1..1] Temperature Sensor Control Configuration                           */
      __IOM uint32_t TSENSE_SD_SEL : 1;         /*!< [2..2] Temperature Sensor selection connected to Ch9                      */
      __IM  uint32_t            : 4;
      __IM  uint32_t MCM_RDY    : 1;            /*!< [7..7] Ready Signal for MCM after Power On or Reset                       */
      __IOM uint32_t SAMPLE_TIME_int : 4;       /*!< [11..8] Sample time of ADC2                                               */
      __IM  uint32_t            : 4;
      __IOM uint32_t SEL_TS_COUNT : 4;          /*!< [19..16] Time for automatic multiplexing of temperature sensor            */
    } bit;
  } CTRL2;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x0000001C) Measurement Unit Control Register 4                        */

    struct
    {
      __IOM uint32_t FILT_OUT_SEL_5_0 : 6;      /*!< [5..0] Output Filter Selection for Channels 0 to 5                        */
      __IM  uint32_t            : 2;
      __IOM uint32_t FILT_OUT_SEL_9_6 : 4;      /*!< [11..8] Output Filter Selection for Channels 6 to 9                       */
    } bit;
  } CTRL4;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000020) Measurement Channel Enable Bits for Cycle 1-4              */

    struct
    {
      __IOM uint32_t SQ1        : 6;            /*!< [5..0] Sequence 1 channel enable                                          */
      __IM  uint32_t            : 2;
      __IOM uint32_t SQ2        : 6;            /*!< [13..8] Sequence 2 channel enable                                         */
      __IM  uint32_t            : 2;
      __IOM uint32_t SQ3        : 6;            /*!< [21..16] Sequence 3 channel enable                                        */
      __IM  uint32_t            : 2;
      __IOM uint32_t SQ4        : 6;            /*!< [29..24] Sequence 4 channel enable                                        */
    } bit;
  } SQ1_4;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000024) Measurement Channel Enable Bits for Cycle 5 -
                                                                    8                                                          */

    struct
    {
      __IOM uint32_t SQ5        : 6;            /*!< [5..0] Sequence 5 channel enable                                          */
      __IM  uint32_t            : 2;
      __IOM uint32_t SQ6        : 6;            /*!< [13..8] Sequence 6 channel enable                                         */
      __IM  uint32_t            : 2;
      __IOM uint32_t SQ7        : 6;            /*!< [21..16] Sequence 7 channel enable                                        */
      __IM  uint32_t            : 2;
      __IOM uint32_t SQ8        : 6;            /*!< [29..24] Sequence 8 channel enable                                        */
    } bit;
  } SQ5_8;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000028) Measurement Channel Enable Bits for Cycle 9 -
                                                                    10                                                         */

    struct
    {
      __IOM uint32_t SQ9        : 6;            /*!< [5..0] Sequence 9 channel enable                                          */
      __IM  uint32_t            : 2;
      __IOM uint32_t SQ10       : 6;            /*!< [13..8] Sequence 10 channel enable                                        */
    } bit;
  } SQ9_10;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x0000002C) Measurement Channel Enable Bits for Cycle 1 -
                                                                    8                                                          */

    struct
    {
      __IM  uint32_t SQ1_int    : 4;            /*!< [3..0] Sequence 1 channel enable                                          */
      __IM  uint32_t SQ2_int    : 4;            /*!< [7..4] Sequence 2 channel enable                                          */
      __IM  uint32_t SQ3_int    : 4;            /*!< [11..8] Sequence 3 channel enable                                         */
      __IM  uint32_t SQ4_int    : 4;            /*!< [15..12] Sequence 4 channel enable                                        */
      __IM  uint32_t SQ5_int    : 4;            /*!< [19..16] Sequence 5 channel enable                                        */
      __IM  uint32_t SQ6_int    : 4;            /*!< [23..20] Sequence 6 channel enable                                        */
      __IM  uint32_t SQ7_int    : 4;            /*!< [27..24] Sequence 7 channel enable                                        */
      __IM  uint32_t SQ8_int    : 4;            /*!< [31..28] Sequence 8 channel enable                                        */
    } bit;
  } SQ1_8_int;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000030) Measurement Channel Enable Bits for Cycle 9 and
                                                                    10                                                         */

    struct
    {
      __IM  uint32_t SQ9_int    : 4;            /*!< [3..0] Sequence 9 channel enable                                          */
      __IM  uint32_t SQ10_int   : 4;            /*!< [7..4] Sequence 10 channel enable                                         */
    } bit;
  } SQ9_10_int;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000034) Calibration for Channel 0 and 1                            */

    struct
    {
      __IOM uint32_t OFFS_CH0   : 8;            /*!< [7..0] Offset Calibration for channel 0                                   */
      __IOM uint32_t GAIN_CH0   : 8;            /*!< [15..8] Gain Calibration for channel 0                                    */
      __IOM uint32_t OFFS_CH1   : 8;            /*!< [23..16] Offset Calibration for channel 1                                 */
      __IOM uint32_t GAIN_CH1   : 8;            /*!< [31..24] Gain Calibration for channel 1                                   */
    } bit;
  } CAL_CH0_1;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000038) Calibration for Channel 2 and 3                            */

    struct
    {
      __IOM uint32_t OFFS_CH2   : 8;            /*!< [7..0] Offset Calibration for channel 2                                   */
      __IOM uint32_t GAIN_CH2   : 8;            /*!< [15..8] Gain Calibration for channel 2                                    */
      __IOM uint32_t OFFS_CH3   : 8;            /*!< [23..16] Offset Calibration for channel 3                                 */
      __IOM uint32_t GAIN_CH3   : 8;            /*!< [31..24] Gain Calibration for channel 3                                   */
    } bit;
  } CAL_CH2_3;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x0000003C) Calibration for Channel 4 and 5                            */

    struct
    {
      __IOM uint32_t OFFS_CH4   : 8;            /*!< [7..0] Offset Calibration for channel 4                                   */
      __IOM uint32_t GAIN_CH4   : 8;            /*!< [15..8] Gain Calibration for channel 4                                    */
      __IOM uint32_t OFFS_CH5   : 8;            /*!< [23..16] Offset Calibration for channel 5                                 */
      __IOM uint32_t GAIN_CH5   : 8;            /*!< [31..24] Gain Calibration for channel 5                                   */
    } bit;
  } CAL_CH4_5;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000040) Calibration for Channel 6 and 7                            */

    struct
    {
      __IM  uint32_t OFFS_CH6   : 8;            /*!< [7..0] Offset Calibration for channel 6                                   */
      __IM  uint32_t GAIN_CH6   : 8;            /*!< [15..8] Gain Calibration for channel 6                                    */
      __IM  uint32_t OFFS_CH7   : 8;            /*!< [23..16] Offset Calibration for channel 7                                 */
      __IM  uint32_t GAIN_CH7   : 8;            /*!< [31..24] Gain Calibration for channel 7                                   */
    } bit;
  } CAL_CH6_7;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000044) Calibration for Channel 8 and 9                            */

    struct
    {
      __IM  uint32_t OFFS_CH8   : 8;            /*!< [7..0] Offset Calibration for channel 8                                   */
      __IM  uint32_t GAIN_CH8   : 8;            /*!< [15..8] Gain Calibration for channel 8                                    */
      __IM  uint32_t OFFS_CH9   : 8;            /*!< [23..16] Offset Calibration for channel 9                                 */
      __IM  uint32_t GAIN_CH9   : 8;            /*!< [31..24] Gain Calibration for channel 9                                   */
    } bit;
  } CAL_CH8_9;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000048) Filter Coefficients ADC Channel 0-5                        */

    struct
    {
      __IOM uint32_t CH0        : 2;            /*!< [1..0] Filter Coefficients ADC channel 0                                  */
      __IOM uint32_t CH1        : 2;            /*!< [3..2] Filter Coefficients ADC channel 1                                  */
      __IOM uint32_t CH2        : 2;            /*!< [5..4] Filter Coefficients ADC channel 2                                  */
      __IOM uint32_t CH3        : 2;            /*!< [7..6] Filter Coefficients ADC channel 3                                  */
      __IOM uint32_t CH4        : 2;            /*!< [9..8] Filter Coefficients ADC channel 4                                  */
      __IOM uint32_t CH5        : 2;            /*!< [11..10] Filter Coefficients ADC channel 5                                */
    } bit;
  } FILTCOEFF0_5;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x0000004C) Filter Coefficents ADC Channel 6-9                         */

    struct
    {
      __IM  uint32_t CH6        : 2;            /*!< [1..0] Filter Coefficients ADC channel 6                                  */
      __IM  uint32_t CH7        : 2;            /*!< [3..2] Filter Coefficients ADC channel 7                                  */
      __IM  uint32_t CH8        : 2;            /*!< [5..4] Filter Coefficients ADC channel 8                                  */
      __IM  uint32_t CH9        : 2;            /*!< [7..6] Filter Coefficients ADC channel 9                                  */
    } bit;
  } FILTCOEFF6_9;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000050) ADC or Filter Output Channel 0                             */

    struct
    {
      __IM  uint32_t OUT_CH0    : 10;           /*!< [9..0] ADC or filter output value channel 0                               */
    } bit;
  } FILT_OUT0;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000054) ADC or Filter Output Channel 1                             */

    struct
    {
      __IM  uint32_t OUT_CH1    : 10;           /*!< [9..0] ADC or filter output value channel 1                               */
    } bit;
  } FILT_OUT1;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000058) ADC or Filter Output Channel 2                             */

    struct
    {
      __IM  uint32_t OUT_CH2    : 10;           /*!< [9..0] ADC or filter output value channel 2                               */
    } bit;
  } FILT_OUT2;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x0000005C) ADC or Filter Output Channel 3                             */

    struct
    {
      __IM  uint32_t OUT_CH3    : 10;           /*!< [9..0] ADC or filter output value channel 3                               */
    } bit;
  } FILT_OUT3;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000060) ADC or Filter Output Channel 4                             */

    struct
    {
      __IM  uint32_t OUT_CH4    : 10;           /*!< [9..0] ADC or filter output value channel 4                               */
    } bit;
  } FILT_OUT4;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000064) ADC or Filter Output Channel 5                             */

    struct
    {
      __IM  uint32_t OUT_CH5    : 10;           /*!< [9..0] ADC or filter output value channel 5                               */
    } bit;
  } FILT_OUT5;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000068) ADC or Filter Output Channel 6                             */

    struct
    {
      __IM  uint32_t OUT_CH6    : 10;           /*!< [9..0] ADC or filter output value channel 6                               */
    } bit;
  } FILT_OUT6;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x0000006C) ADC or Filter Output Channel 7                             */

    struct
    {
      __IM  uint32_t OUT_CH7    : 10;           /*!< [9..0] ADC or filter output value channel 7                               */
    } bit;
  } FILT_OUT7;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000070) ADC or Filter Output Channel 8                             */

    struct
    {
      __IM  uint32_t OUT_CH8    : 10;           /*!< [9..0] ADC or filter output value channel 8                               */
    } bit;
  } FILT_OUT8;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000074) ADC or Filter Output Channel 9                             */

    struct
    {
      __IM  uint32_t OUT_CH9    : 10;           /*!< [9..0] ADC or filter output value channel 9                               */
    } bit;
  } FILT_OUT9;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000078) Upper Threshold Filter Enable                              */

    struct
    {
      __IOM uint32_t Ch0_EN     : 1;            /*!< [0..0] Upper threshold IIR filter enable ch 0                             */
      __IOM uint32_t Ch1_EN     : 1;            /*!< [1..1] Upper threshold IIR filter enable ch 1                             */
      __IOM uint32_t Ch2_EN     : 1;            /*!< [2..2] Upper threshold IIR filter enable ch 2                             */
      __IOM uint32_t Ch3_EN     : 1;            /*!< [3..3] Upper threshold IIR filter enable ch 3                             */
      __IOM uint32_t Ch4_EN     : 1;            /*!< [4..4] Upper threshold IIR filter enable ch 4                             */
      __IOM uint32_t Ch5_EN     : 1;            /*!< [5..5] Upper threshold IIR filter enable ch 5                             */
    } bit;
  } FILT_UP_CTRL;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x0000007C) Lower Threshold Filter Enable                              */

    struct
    {
      __IOM uint32_t Ch0_EN     : 1;            /*!< [0..0] Lower threshold IIR filter enable ch 0                             */
      __IOM uint32_t Ch1_EN     : 1;            /*!< [1..1] Lower threshold IIR filter enable ch 1                             */
      __IOM uint32_t Ch2_EN     : 1;            /*!< [2..2] Lower threshold IIR filter enable ch 2                             */
      __IOM uint32_t Ch3_EN     : 1;            /*!< [3..3] Lower threshold IIR filter enable ch 3                             */
      __IOM uint32_t Ch4_EN     : 1;            /*!< [4..4] Lower threshold IIR filter enable ch 4                             */
      __IOM uint32_t Ch5_EN     : 1;            /*!< [5..5] Lower threshold IIR filter enable ch 5                             */
    } bit;
  } FILT_LO_CTRL;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000080) Lower Comparator Trigger Level Channel 0 -3                */

    struct
    {
      __IOM uint32_t CH0        : 8;            /*!< [7..0] Channel 0 lower trigger level                                      */
      __IOM uint32_t CH1        : 8;            /*!< [15..8] Channel 1 lower trigger level                                     */
      __IOM uint32_t CH2        : 8;            /*!< [23..16] Channel 2 lower trigger level                                    */
      __IOM uint32_t CH3        : 8;            /*!< [31..24] Channel 3 lower trigger level                                    */
    } bit;
  } TH0_3_LOWER;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000084) Lower Comparator Trigger Level Channel 4 and
                                                                    5                                                          */

    struct
    {
      __IOM uint32_t CH4        : 8;            /*!< [7..0] Channel 4 lower trigger level                                      */
      __IOM uint32_t CH5        : 8;            /*!< [15..8] Channel 5 lower trigger level                                     */
    } bit;
  } TH4_5_LOWER;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000088) Lower Comparator Trigger Level Channel 6 -9                */

    struct
    {
      __IOM uint32_t CH6        : 8;            /*!< [7..0] Channel 6 lower trigger level                                      */
      __IM  uint32_t CH7        : 8;            /*!< [15..8] Channel 7 lower trigger level                                     */
      __IOM uint32_t CH8        : 8;            /*!< [23..16] Channel 8 lower trigger level                                    */
      __IOM uint32_t CH9        : 8;            /*!< [31..24] Channel 9 lower trigger level                                    */
    } bit;
  } TH6_9_LOWER;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x0000008C) Upper Comparator Trigger Level Channel 0-3                 */

    struct
    {
      __IOM uint32_t CH0        : 8;            /*!< [7..0] Channel 0 upper trigger level                                      */
      __IOM uint32_t CH1        : 8;            /*!< [15..8] Channel 1 upper trigger level                                     */
      __IOM uint32_t CH2        : 8;            /*!< [23..16] Channel 2 upper trigger level                                    */
      __IOM uint32_t CH3        : 8;            /*!< [31..24] Channel 3 upper trigger level                                    */
    } bit;
  } TH0_3_UPPER;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000090) Upper Comparator Trigger Level Channel 4 -5                */

    struct
    {
      __IOM uint32_t CH4        : 8;            /*!< [7..0] Channel 4 upper trigger level                                      */
      __IOM uint32_t CH5        : 8;            /*!< [15..8] Channel 5 upper trigger level                                     */
    } bit;
  } TH4_5_UPPER;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000094) Upper Comparator Trigger Level Channel 6 -9                */

    struct
    {
      __IM  uint32_t CH6        : 8;            /*!< [7..0] Channel 6 upper trigger level                                      */
      __IM  uint32_t CH7        : 8;            /*!< [15..8] Channel 7 upper trigger level                                     */
      __IM  uint32_t CH8        : 8;            /*!< [23..16] Channel 8 upper trigger level                                    */
      __IM  uint32_t CH9        : 8;            /*!< [31..24] Channel 9 upper trigger level                                    */
    } bit;
  } TH6_9_UPPER;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000098) Lower Counter Trigger Level Channel 0 - 3                  */

    struct
    {
      __IOM uint32_t CNT_LO_CH0 : 3;            /*!< [2..0] Lower timer trigger threshold channel 0                            */
      __IOM uint32_t HYST_LO_CH0 : 2;           /*!< [4..3] Channel 0 lower hysteresis                                         */
      __IM  uint32_t            : 3;
      __IOM uint32_t CNT_LO_CH1 : 3;            /*!< [10..8] Lower timer trigger threshold channel 1                           */
      __IOM uint32_t HYST_LO_CH1 : 2;           /*!< [12..11] Channel 1 lower hysteresis                                       */
      __IM  uint32_t            : 3;
      __IOM uint32_t CNT_LO_CH2 : 3;            /*!< [18..16] Lower timer trigger threshold channel 2                          */
      __IOM uint32_t HYST_LO_CH2 : 2;           /*!< [20..19] Channel 2 lower hysteresis                                       */
      __IM  uint32_t            : 3;
      __IOM uint32_t CNT_LO_CH3 : 3;            /*!< [26..24] Lower timer trigger threshold channel 3                          */
      __IOM uint32_t HYST_LO_CH3 : 2;           /*!< [28..27] Channel 3 lower hysteresis                                       */
    } bit;
  } CNT0_3_LOWER;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x0000009C) Lower Counter Trigger Level Channel 4 and 5                */

    struct
    {
      __IOM uint32_t CNT_LO_CH4 : 3;            /*!< [2..0] Lower timer trigger threshold channel 4                            */
      __IOM uint32_t HYST_LO_CH4 : 2;           /*!< [4..3] Channel 4 lower hysteresis                                         */
      __IM  uint32_t            : 3;
      __IOM uint32_t CNT_LO_CH5 : 3;            /*!< [10..8] Lower timer trigger threshold channel 5                           */
      __IOM uint32_t HYST_LO_CH5 : 2;           /*!< [12..11] Channel 5 lower hysteresis                                       */
    } bit;
  } CNT4_5_LOWER;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x000000A0) Lower Counter Trigger Level Channel 6 - 9                  */

    struct
    {
      __IM  uint32_t CNT_LO_CH6 : 3;            /*!< [2..0] Lower timer trigger threshold channel 6                            */
      __IM  uint32_t HYST_LO_CH6 : 2;           /*!< [4..3] Channel 6 lower hysteresis                                         */
      __IM  uint32_t            : 3;
      __IM  uint32_t CNT_LO_CH7 : 3;            /*!< [10..8] Lower timer trigger threshold channel 7                           */
      __IM  uint32_t HYST_LO_CH7 : 2;           /*!< [12..11] Channel 7 lower hysteresis                                       */
      __IM  uint32_t            : 3;
      __IM  uint32_t CNT_LO_CH8 : 3;            /*!< [18..16] Lower timer trigger threshold channel 8                          */
      __IM  uint32_t HYST_LO_CH8 : 2;           /*!< [20..19] Channel 8 lower hysteresis                                       */
      __IM  uint32_t            : 3;
      __IM  uint32_t CNT_LO_CH9 : 3;            /*!< [26..24] Lower timer trigger threshold channel 9                          */
      __IM  uint32_t HYST_LO_CH9 : 2;           /*!< [28..27] Channel 9 lower hysteresis                                       */
    } bit;
  } CNT6_9_LOWER;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x000000A4) Upper Counter Trigger Level Channel 0 - 3                  */

    struct
    {
      __IOM uint32_t CNT_UP_CH0 : 3;            /*!< [2..0] Upper timer trigger threshold channel 0                            */
      __IOM uint32_t HYST_UP_CH0 : 2;           /*!< [4..3] Channel 0 upper hysteresis                                         */
      __IM  uint32_t            : 3;
      __IOM uint32_t CNT_UP_CH1 : 3;            /*!< [10..8] Upper timer trigger threshold channel 1                           */
      __IOM uint32_t HYST_UP_CH1 : 2;           /*!< [12..11] Channel 1 upper hysteresis                                       */
      __IM  uint32_t            : 3;
      __IOM uint32_t CNT_UP_CH2 : 3;            /*!< [18..16] Upper timer trigger threshold channel 2                          */
      __IOM uint32_t HYST_UP_CH2 : 2;           /*!< [20..19] Channel 2 upper hysteresis                                       */
      __IM  uint32_t            : 3;
      __IOM uint32_t CNT_UP_CH3 : 3;            /*!< [26..24] Upper timer trigger threshold channel 3                          */
      __IOM uint32_t HYST_UP_CH3 : 2;           /*!< [28..27] Channel 3 upper hysteresis                                       */
    } bit;
  } CNT0_3_UPPER;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x000000A8) Upper Counter Trigger Level Channel 4 and 5                */

    struct
    {
      __IOM uint32_t CNT_UP_CH4 : 3;            /*!< [2..0] Upper timer trigger threshold channel 4                            */
      __IOM uint32_t HYST_UP_CH4 : 2;           /*!< [4..3] Channel 4 upper hysteresis                                         */
      __IM  uint32_t            : 3;
      __IOM uint32_t CNT_UP_CH5 : 3;            /*!< [10..8] Upper timer trigger threshold channel 5                           */
      __IOM uint32_t HYST_UP_CH5 : 2;           /*!< [12..11] Channel 5 upper hysteresis                                       */
    } bit;
  } CNT4_5_UPPER;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x000000AC) Upper Counter Trigger Level Channel 6 -9                   */

    struct
    {
      __IM  uint32_t CNT_UP_CH6 : 3;            /*!< [2..0] Upper timer trigger threshold channel 6                            */
      __IM  uint32_t HYST_UP_CH6 : 2;           /*!< [4..3] Channel 6 upper hysteresis                                         */
      __IM  uint32_t            : 3;
      __IM  uint32_t CNT_UP_CH7 : 3;            /*!< [10..8] Upper timer trigger threshold channel 7                           */
      __IM  uint32_t HYST_UP_CH7 : 2;           /*!< [12..11] Channel 7 upper hysteresis                                       */
      __IM  uint32_t            : 3;
      __IM  uint32_t CNT_UP_CH8 : 3;            /*!< [18..16] Upper timer trigger threshold channel 8                          */
      __IM  uint32_t HYST_UP_CH8 : 2;           /*!< [20..19] Channel 8 upper hysteresis                                       */
      __IM  uint32_t            : 3;
      __IM  uint32_t CNT_UP_CH9 : 3;            /*!< [26..24] Upper timer trigger threshold channel 9                          */
      __IM  uint32_t HYST_UP_CH9 : 2;           /*!< [28..27] Channel 9 upper hysteresis                                       */
    } bit;
  } CNT6_9_UPPER;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x000000B0) Overvoltage Measurement Mode of Ch 0-5                     */

    struct
    {
      __IOM uint32_t Ch0        : 2;            /*!< [1..0] Measurement mode ch 0                                              */
      __IOM uint32_t Ch1        : 2;            /*!< [3..2] Measurement mode ch 1                                              */
      __IOM uint32_t Ch2        : 2;            /*!< [5..4] Measurement mode ch 2                                              */
      __IOM uint32_t Ch3        : 2;            /*!< [7..6] Measurement mode ch 3                                              */
      __IOM uint32_t Ch4        : 2;            /*!< [9..8] Measurement mode ch 4                                              */
      __IOM uint32_t Ch5        : 2;            /*!< [11..10] Measurement mode ch 5                                            */
    } bit;
  } MMODE0_5;
  __IM  uint32_t  RESERVED1[2];

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x000000BC) ADC2 HV Status Register                                    */

    struct
    {
      __IM  uint32_t            : 1;
      __IM  uint32_t READY      : 1;            /*!< [1..1] HVADC Ready bit                                                    */
    } bit;
  } HV_STS;
} ADC2_Type;                                    /*!< Size = 192 (0xc0)                                                         */



/* =========================================================================================================================== */
/* ================                                           ADC34                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief ADC34 (ADC34)
  */

typedef struct                                  /*!< (@ 0x40008000) ADC34 Structure                                            */
{

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) ADC3 and ADC4 Control and Status                           */

    struct
    {
      __IOM uint32_t ADC3_EN    : 1;            /*!< [0..0] ADC3 analog frontend Enable                                        */
      __IOM uint32_t ADC3_OFS_MEAS_EN : 1;      /*!< [1..1] ADC3 Offset Measurement Enable                                     */
      __IOM uint32_t ADC3_SOC   : 1;            /*!< [2..2] ADC3 conversion enable (set after enabling ADC to allow
                                                     settling of the analog converter part)                                    */
      __IM  uint32_t            : 1;
      __IM  uint32_t ADC3_EoC_STS : 1;          /*!< [4..4] ADC3 End of Conversion                                             */
      __IM  uint32_t ADC34_DREQ_SEL : 2;        /*!< [6..5] DMA Ch13 request source select                                     */
      __IM  uint32_t            : 4;
      __IOM uint32_t ADC34_REF_SEL : 1;         /*!< [11..11] ADC34 reference voltage selection                                */
      __IOM uint32_t ADC3_OSR   : 4;            /*!< [15..12] ADC3 Oversampling Ratio                                          */
      __IOM uint32_t ADC4_EN    : 1;            /*!< [16..16] ADC4 analog frontend Enable                                      */
      __IOM uint32_t ADC4_OFS_MEAS_EN : 1;      /*!< [17..17] ADC4 Offset Measurement Enable                                   */
      __IOM uint32_t ADC4_SOC   : 1;            /*!< [18..18] ADC4 conversion enable (set after enabling ADC to allow
                                                     settling of the analog converter part)                                    */
      __IM  uint32_t            : 1;
      __IM  uint32_t ADC4_EoC_STS : 1;          /*!< [20..20] ADC4 End of Conversion                                           */
      __IOM uint32_t ADC34_EoC_CNT : 2;         /*!< [22..21] ADC34 EoC counter                                                */
      __IOM uint32_t ADC34_DITHEN : 1;          /*!< [23..23] ADC34 Dithering Enable                                           */
      __IOM uint32_t ADC34_DITHVAL : 4;         /*!< [27..24] ADC34 Dither Value                                               */
      __IOM uint32_t ADC4_OSR   : 4;            /*!< [31..28] ADC4 Oversampling Ratio                                          */
    } bit;
  } CTRL_STS;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) ADC3_ADC4_RESU                                             */

    struct
    {
      __IM  uint32_t ADC3_RESU  : 16;           /*!< [15..0] ADC3 Result Register                                              */
      __IM  uint32_t ADC4_RESU  : 16;           /*!< [31..16] ADC4 Result Register                                             */
    } bit;
  } RESU;
} ADC34_Type;                                   /*!< Size = 8 (0x8)                                                            */



/* =========================================================================================================================== */
/* ================                                           BDRV                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief Bridge Driver (BDRV)
  */

typedef struct                                  /*!< (@ 0x40034000) BDRV Structure                                             */
{

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) H-Bridge Driver Control 1                                  */

    struct
    {
      __IOM uint32_t LS1_EN     : 1;            /*!< [0..0] Low Side Driver 1 Enable                                           */
      __IOM uint32_t LS1_PWM    : 1;            /*!< [1..1] Low Side Driver 1 PWM Enable                                       */
      __IOM uint32_t LS1_ON     : 1;            /*!< [2..2] Low Side Driver 1 On                                               */
      __IOM uint32_t LS1_DCS_EN : 1;            /*!< [3..3] Low Side Driver 1 Diagnosis Current Source Enable                  */
      __IM  uint32_t LS1_DS_STS : 1;            /*!< [4..4] Low Side Driver 1 Drain Source Monitoring Status in OFF-State      */
      __IM  uint32_t LS1_SUPERR_STS : 1;        /*!< [5..5] Low Side Driver 1 Supply Error Status                              */
      __IM  uint32_t LS1_OC_STS : 1;            /*!< [6..6] External Low Side 1 FET Over-current Status                        */
      __IOM uint32_t LS1_OC_DIS : 1;            /*!< [7..7] Low Side Driver 1 Overcurrent Shutdown Disable                     */
      __IOM uint32_t LS2_EN     : 1;            /*!< [8..8] Low Side Driver 2 Enable                                           */
      __IOM uint32_t LS2_PWM    : 1;            /*!< [9..9] Low Side Driver 2 PWM Enable                                       */
      __IOM uint32_t LS2_ON     : 1;            /*!< [10..10] Low Side Driver 2 On                                             */
      __IOM uint32_t LS2_DCS_EN : 1;            /*!< [11..11] Low Side Driver 2 Diagnosis Current Source Enable                */
      __IM  uint32_t LS2_DS_STS : 1;            /*!< [12..12] Low Side Driver 2 Drain Source Monitoring Status in
                                                     OFF-State                                                                 */
      __IM  uint32_t LS2_SUPERR_STS : 1;        /*!< [13..13] Low Side Driver 2 Supply Error Status                            */
      __IM  uint32_t LS2_OC_STS : 1;            /*!< [14..14] External Low Side 2 FET Over-current Status                      */
      __IOM uint32_t LS2_OC_DIS : 1;            /*!< [15..15] Low Side Driver Overcurrent Shutdown Disable                     */
      __IOM uint32_t HS1_EN     : 1;            /*!< [16..16] High Side Driver 1 Enable                                        */
      __IOM uint32_t HS1_PWM    : 1;            /*!< [17..17] High Side Driver 1 PWM Enable                                    */
      __IOM uint32_t HS1_ON     : 1;            /*!< [18..18] High Side Driver 1 On                                            */
      __IOM uint32_t HS1_DCS_EN : 1;            /*!< [19..19] High Side Driver 1 Diagnosis Current Source Enable               */
      __IM  uint32_t HS1_DS_STS : 1;            /*!< [20..20] High Side Driver 1 Drain Source Monitoring Status in
                                                     OFF-State                                                                 */
      __IM  uint32_t HS1_SUPERR_STS : 1;        /*!< [21..21] High Side Driver 1 Supply Error Status                           */
      __IM  uint32_t HS1_OC_STS : 1;            /*!< [22..22] External High Side 1 FET Over-current Status                     */
      __IOM uint32_t HS1_OC_DIS : 1;            /*!< [23..23] High Side Driver Overcurrent Shutdown Disable                    */
      __IOM uint32_t HS2_EN     : 1;            /*!< [24..24] High Side Driver 2 Enable                                        */
      __IOM uint32_t HS2_PWM    : 1;            /*!< [25..25] High Side Driver 2 PWM Enable                                    */
      __IOM uint32_t HS2_ON     : 1;            /*!< [26..26] High Side Driver 2 On                                            */
      __IOM uint32_t HS2_DCS_EN : 1;            /*!< [27..27] High Side Driver 2 Diagnosis Current Source Enable               */
      __IM  uint32_t HS2_DS_STS : 1;            /*!< [28..28] High Side Driver 2 Drain Source Monitoring Status in
                                                     OFF-State                                                                 */
      __IM  uint32_t HS2_SUPERR_STS : 1;        /*!< [29..29] High Side Driver 2 Supply Error Status                           */
      __IM  uint32_t HS2_OC_STS : 1;            /*!< [30..30] External High Side 2 FET Over-current Status                     */
      __IOM uint32_t HS2_OC_DIS : 1;            /*!< [31..31] High Side Driver Overcurrent Shutdown Disable                    */
    } bit;
  } CTRL1;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) H-Bridge Driver Control 2                                  */

    struct
    {
      __IOM uint32_t LS3_EN     : 1;            /*!< [0..0] Low Side Driver 3 Enable                                           */
      __IOM uint32_t LS3_PWM    : 1;            /*!< [1..1] Low Side Driver 3 PWM Enable                                       */
      __IOM uint32_t LS3_ON     : 1;            /*!< [2..2] Low Side Driver 3 On                                               */
      __IOM uint32_t LS3_DCS_EN : 1;            /*!< [3..3] Low Side Driver 3 Diagnosis Current Source Enable                  */
      __IM  uint32_t LS3_DS_STS : 1;            /*!< [4..4] Low Side Driver 3 Drain Source Monitoring Status in OFF-State      */
      __IM  uint32_t LS3_SUPERR_STS : 1;        /*!< [5..5] Low Side Driver 3 Supply Error Status                              */
      __IM  uint32_t LS3_OC_STS : 1;            /*!< [6..6] External Low Side 3 FET Over-current Status                        */
      __IOM uint32_t LS3_OC_DIS : 1;            /*!< [7..7] Low Side Driver 3 Over-current Shutdown Disable                    */
      __IOM uint32_t HS3_EN     : 1;            /*!< [8..8] High Side Driver 3 Enable                                          */
      __IOM uint32_t HS3_PWM    : 1;            /*!< [9..9] High Side Driver 3 PWM Enable                                      */
      __IOM uint32_t HS3_ON     : 1;            /*!< [10..10] High Side Driver 3 On                                            */
      __IOM uint32_t HS3_DCS_EN : 1;            /*!< [11..11] High Side Driver 3 Diagnosis Current Source Enable               */
      __IM  uint32_t HS3_DS_STS : 1;            /*!< [12..12] High Side Driver 3 Drain Source Monitoring Status                */
      __IM  uint32_t HS3_SUPERR_STS : 1;        /*!< [13..13] High Side Driver 3 Supply Error Status                           */
      __IM  uint32_t HS3_OC_STS : 1;            /*!< [14..14] External High Side 3 FET Over-current Status                     */
      __IOM uint32_t HS3_OC_DIS : 1;            /*!< [15..15] High Side Driver 3 Over-current Shutdown Disable                 */
      __IM  uint32_t DLY_DIAG_TIM : 10;         /*!< [25..16] Ext. power on/off diag timer result register                     */
      __OM  uint32_t DLY_DIAG_SCLR : 1;         /*!< [26..26] Ext. power diag timer valid flag clear                           */
      __IM  uint32_t DLY_DIAG_STS : 1;          /*!< [27..27] Ext. power diag timer valid flag                                 */
      __IOM uint32_t DLY_DIAG_CHSEL : 3;        /*!< [30..28] Ext. power on/off timer channel select                           */
      __IOM uint32_t DLY_DIAG_DIRSEL : 1;       /*!< [31..31] Ext. power diag timer on / off select                            */
    } bit;
  } CTRL2;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) H-Bridge Driver Control 3                                  */

    struct
    {
      __IOM uint32_t ICHARGE_TRIM : 5;          /*!< [4..0] Trimming of the internal driver charge current                     */
      __IM  uint32_t            : 1;
      __IOM uint32_t ICHARGEDIV2_N : 1;         /*!< [6..6] ICHARGE Current divide by 2 not                                    */
      __IOM uint32_t ON_SEQ_EN  : 1;            /*!< [7..7] Turn On SlewrateSequencer enable                                   */
      __IOM uint32_t IDISCHARGE_TRIM : 5;       /*!< [12..8] Trimming of the internal driver dis-charge current                */
      __IM  uint32_t            : 1;
      __IOM uint32_t IDISCHARGEDIV2_N : 1;      /*!< [14..14] IDISCHARGE Current divide by 2 not                               */
      __IOM uint32_t OFF_SEQ_EN : 1;            /*!< [15..15] Turn Off Slewrate Sequencer enable                               */
      __IOM uint32_t DSMONVTH   : 3;            /*!< [18..16] Voltage Threshold for Drain-Source Monitoring of external
                                                     FETs                                                                      */
      __IM  uint32_t            : 5;
      __IOM uint32_t DRV_CCP_TIMSEL : 2;        /*!< [25..24] minimum cross conduction protection time setting                 */
      __IOM uint32_t DRV_CCP_DIS : 1;           /*!< [26..26] Dynamic cross conduction protection Disable                      */
    } bit;
  } CTRL3;
  __IM  uint32_t  RESERVED;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) Turn on Slewrate Sequencer Control                         */

    struct
    {
      __IOM uint32_t DRV_OFF_t_4 : 3;           /*!< [2..0] Slew rate sequencer off phase 4 time                               */
      __IOM uint32_t DRV_OFF_I_4 : 5;           /*!< [7..3] Slew rate sequencer off phase 4 current                            */
      __IOM uint32_t DRV_OFF_t_3 : 3;           /*!< [10..8] Slew rate sequencer off phase 3 time                              */
      __IOM uint32_t DRV_OFF_I_3 : 5;           /*!< [15..11] Slew rate sequencer off phase 3 current                          */
      __IOM uint32_t DRV_OFF_t_2 : 3;           /*!< [18..16] Slew rate sequencer off phase 2 time                             */
      __IOM uint32_t DRV_OFF_I_2 : 5;           /*!< [23..19] Slew rate sequencer off phase 2 current                          */
      __IOM uint32_t DRV_OFF_t_1 : 3;           /*!< [26..24] Slew rate sequencer off phase 1 time                             */
      __IOM uint32_t DRV_OFF_I_1 : 5;           /*!< [31..27] Slew rate sequencer off phase 1 current                          */
    } bit;
  } OFF_SEQ_CTRL;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000014) Turn off Slewrate Sequencer Control                        */

    struct
    {
      __IOM uint32_t DRV_ON_t_4 : 3;            /*!< [2..0] Slew rate sequencer on phase 4 time                                */
      __IOM uint32_t DRV_ON_I_4 : 5;            /*!< [7..3] Slew rate sequencer on phase 4 current                             */
      __IOM uint32_t DRV_ON_t_3 : 3;            /*!< [10..8] Slew rate sequencer on phase 3 time                               */
      __IOM uint32_t DRV_ON_I_3 : 5;            /*!< [15..11] Slew rate sequencer on phase 3 current                           */
      __IOM uint32_t DRV_ON_t_2 : 3;            /*!< [18..16] Slew rate sequencer on phase 2 time                              */
      __IOM uint32_t DRV_ON_I_2 : 5;            /*!< [23..19] Slew rate sequencer on phase 2 current                           */
      __IOM uint32_t DRV_ON_t_1 : 3;            /*!< [26..24] Slew rate sequencer on phase 1 time                              */
      __IOM uint32_t DRV_ON_I_1 : 5;            /*!< [31..27] Slew rate sequencer on phase 1 current                           */
    } bit;
  } ON_SEQ_CTRL;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000018) Trimming of Driver                                         */

    struct
    {
      __IOM uint32_t LS_HS_BT_TFILT_SEL : 2;    /*!< [1..0] Blanking Time for Drain-Source Monitoring of Low / High
                                                     Side Drivers                                                              */
      __IM  uint32_t            : 3;
      __IOM uint32_t DRV_CCPTIMMUL : 2;         /*!< [6..5] Multiplier bits for cross conduction time settings in
                                                     register DRV_CCP_TIMSEL                                                   */
      __IM  uint32_t            : 1;
      __IOM uint32_t LSDRV_DS_TFILT_SEL : 2;    /*!< [9..8] Filter Time for Drain-Source Monitoring of Low Side Drivers        */
      __IOM uint32_t LS1DRV_FDISCHG_DIS : 1;    /*!< [10..10] Low Side 1 Predriver in overcurrent situation disable            */
      __IOM uint32_t LS2DRV_FDISCHG_DIS : 1;    /*!< [11..11] Low Side 2 Predriver in overcurrent situation disable            */
      __IOM uint32_t LS3DRV_FDISCHG_DIS : 1;    /*!< [12..12] Low Side 3 Predriver in overcurrent situation disable            */
      __IOM uint32_t LS1DRV_OCSDN_DIS : 1;      /*!< [13..13] Low Side 1 Predriver in overcurrent situation disable            */
      __IOM uint32_t LS2DRV_OCSDN_DIS : 1;      /*!< [14..14] Low Side 2 Predriver in overcurrent situation disable            */
      __IOM uint32_t LS3DRV_OCSDN_DIS : 1;      /*!< [15..15] Low Side 3 Predriver in overcurrent situation disable            */
      __IOM uint32_t HSDRV_DS_TFILT_SEL : 2;    /*!< [17..16] Filter Time for Drain-Source Monitoring of High Side
                                                     Drivers                                                                   */
      __IOM uint32_t HS1DRV_FDISCHG_DIS : 1;    /*!< [18..18] High Side 1 Predriver in overcurrent situation disable           */
      __IOM uint32_t HS2DRV_FDISCHG_DIS : 1;    /*!< [19..19] High Side 2 Predriver in overcurrent situation disable           */
      __IOM uint32_t HS3DRV_FDISCHG_DIS : 1;    /*!< [20..20] High Side 3 Predriver in overcurrent situation disable           */
      __IOM uint32_t HS1DRV_OCSDN_DIS : 1;      /*!< [21..21] High Side 1 Predriver in overcurrent situation disable           */
      __IOM uint32_t HS2DRV_OCSDN_DIS : 1;      /*!< [22..22] High Side 2 Predriver in overcurrent situation disable           */
      __IOM uint32_t HS3DRV_OCSDN_DIS : 1;      /*!< [23..23] High Side 3 Predriver in overcurrent situation disable           */
      __IOM uint32_t CPLOW_TFILT_SEL : 2;       /*!< [25..24] Filter Time for Charge Pump Voltage Low Diagnosis                */
    } bit;
  } TRIM_DRVx;
  __IM  uint32_t  RESERVED1;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000020) Charge Pump Control and Status Register                    */

    struct
    {
      __IOM uint32_t CP_EN      : 1;            /*!< [0..0] Charge Pump Enable                                                 */
      __IM  uint32_t            : 1;
      __IOM uint32_t CP_RDY_EN  : 1;            /*!< [2..2] Bridge Driver on Charge Pump Ready Enable                          */
      __IM  uint32_t            : 2;
      __IM  uint32_t VCP_LOTH2_STS : 1;         /*!< [5..5] Charge Pump Low Status                                             */
      __IM  uint32_t            : 2;
      __IOM uint32_t VCP_LOWTH2 : 3;            /*!< [10..8] Charge Pump Output Voltage Lower Threshold Detection
                                                     Level                                                                     */
      __IM  uint32_t            : 5;
      __IOM uint32_t DRVx_VCPLO_DIS : 1;        /*!< [16..16] Driver Shutdown on Charge Pump Low Voltage                       */
      __IM  uint32_t VCP_LOTH1_STS : 1;         /*!< [17..17] Charge Pump MU Low Status                                        */
      __IOM uint32_t DRVx_VCPUP_DIS : 1;        /*!< [18..18] Driver shutdown on Charge Pump Upper Voltage                     */
      __IM  uint32_t VCP_UPTH_STS : 1;          /*!< [19..19] Charge Pump MU High Status                                       */
      __IOM uint32_t DRVx_VSDLO_DIS : 1;        /*!< [20..20] Driver shutdown on VSD Lower Voltage                             */
      __IM  uint32_t VSD_LOTH_STS : 1;          /*!< [21..21] Driver Supply MU Low Status                                      */
      __IOM uint32_t DRVx_VSDUP_DIS : 1;        /*!< [22..22] Driver shutdown on VSD Upper Voltage                             */
      __IM  uint32_t VSD_UPTH_STS : 1;          /*!< [23..23] Driver Supply MU High Status                                     */
      __IOM uint32_t CPLOPWRM_EN : 1;           /*!< [24..24] Charge Pump Low Power Mode Enable                                */
      __IOM uint32_t VCP9V_SET  : 1;            /*!< [25..25] Charge Pump 9 V Output Voltage Set                               */
      __IOM uint32_t VTHVCP9V_TRIM : 2;         /*!< [27..26] Charge Pump Output Voltage 9V Trimming                           */
    } bit;
  } CP_CTRL_STS;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000024) Charge Pump Clock Control Register                         */

    struct
    {
      __IOM uint32_t DITH_LOWER : 5;            /*!< [4..0] CP_CLK lower frequency boundary during dithering                   */
      __IM  uint32_t            : 3;
      __IOM uint32_t DITH_UPPER : 5;            /*!< [12..8] CP_CLK upper frequency boundary during dithering                  */
      __IOM uint32_t F_CP       : 2;            /*!< [14..13] MSB of CP_CLK divider                                            */
      __IOM uint32_t CPCLK_EN   : 1;            /*!< [15..15] Charge Pump Clock Enable                                         */
    } bit;
  } CP_CLK_CTRL;
} BDRV_Type;                                    /*!< Size = 40 (0x28)                                                          */



/* =========================================================================================================================== */
/* ================                                           CCU6                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief Capture Compare Unit 6 (CCU6)
  */

typedef struct                                  /*!< (@ 0x4000C000) CCU6 Structure                                             */
{

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000000) Capture/Compare Register for Channel CC63                  */

    struct
    {
      __IM  uint16_t CCV        : 16;           /*!< [15..0] Channel CC63 Compare Value                                        */
    } bit;
  } CC63R;
  __IM  uint16_t  RESERVED;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000004) Timer Control Register 4                                   */

    struct
    {
      __OM  uint16_t T12RR      : 1;            /*!< [0..0] Timer T12 Run Reset                                                */
      __OM  uint16_t T12RS      : 1;            /*!< [1..1] Timer T12 Run Set                                                  */
      __OM  uint16_t T12RES     : 1;            /*!< [2..2] Timer T12 Reset                                                    */
      __OM  uint16_t DTRES      : 1;            /*!< [3..3] Dead-Time Counter Reset                                            */
      __IM  uint16_t            : 1;
      __OM  uint16_t T12CNT     : 1;            /*!< [5..5] Timer T12 Count Event                                              */
      __OM  uint16_t T12STR     : 1;            /*!< [6..6] Timer T12 Shadow Transfer Request                                  */
      __OM  uint16_t T12STD     : 1;            /*!< [7..7] Timer T12 Shadow Transfer Disable                                  */
      __OM  uint16_t T13RR      : 1;            /*!< [8..8] Timer T13 Run Reset                                                */
      __OM  uint16_t T13RS      : 1;            /*!< [9..9] Timer T13 Run Set                                                  */
      __OM  uint16_t T13RES     : 1;            /*!< [10..10] Timer T13 Reset                                                  */
      __IM  uint16_t            : 2;
      __OM  uint16_t T13CNT     : 1;            /*!< [13..13] Timer T13 Count Event                                            */
      __OM  uint16_t T13STR     : 1;            /*!< [14..14] Timer T13 Shadow Transfer Request                                */
      __OM  uint16_t T13STD     : 1;            /*!< [15..15] Timer T13 Shadow Transfer Disable                                */
    } bit;
  } TCTR4;
  __IM  uint16_t  RESERVED1;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000008) Multi-Channel Mode Output Shadow Register                  */

    struct
    {
      __IOM uint16_t MCMPS      : 6;            /*!< [5..0] Multi-Channel PWM Pattern Shadow                                   */
      __IM  uint16_t            : 1;
      __IOM uint16_t STRMCM     : 1;            /*!< [7..7] Shadow Transfer Request for MCMPS                                  */
      __IOM uint16_t EXPHS      : 3;            /*!< [10..8] Expected Hall Pattern Shadow                                      */
      __IOM uint16_t CURHS      : 3;            /*!< [13..11] Current Hall Pattern Shadow                                      */
      __IM  uint16_t            : 1;
      __IOM uint16_t STRHP      : 1;            /*!< [15..15] Shadow Transfer Request for the Hall Pattern                     */
    } bit;
  } MCMOUTS;
  __IM  uint16_t  RESERVED2;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x0000000C) Capture/Compare Interrupt Status Reset Register            */

    struct
    {
      __OM  uint16_t RCC60R     : 1;            /*!< [0..0] Reset Capture, Compare-Match Rising Edge Flag                      */
      __OM  uint16_t RCC60F     : 1;            /*!< [1..1] Reset Capture, Compare-Match Falling Edge Flag                     */
      __OM  uint16_t RCC61R     : 1;            /*!< [2..2] Reset Capture, Compare-Match Rising Edge Flag                      */
      __OM  uint16_t RCC61F     : 1;            /*!< [3..3] Reset Capture, Compare-Match Falling Edge Flag                     */
      __OM  uint16_t RCC62R     : 1;            /*!< [4..4] Reset Capture, Compare-Match Rising Edge Flag                      */
      __OM  uint16_t RCC62F     : 1;            /*!< [5..5] Reset Capture, Compare-Match Falling Edge Flag                     */
      __OM  uint16_t RT12OM     : 1;            /*!< [6..6] Reset Timer T12 One-Match Flag                                     */
      __OM  uint16_t RT12PM     : 1;            /*!< [7..7] Reset Timer T12 Period-Match Flag                                  */
      __OM  uint16_t RT13CM     : 1;            /*!< [8..8] Reset Timer T13 Compare-Match Flag                                 */
      __OM  uint16_t RT13PM     : 1;            /*!< [9..9] Reset Timer T13 Period-Match Flag                                  */
      __OM  uint16_t RTRPF      : 1;            /*!< [10..10] Reset Trap Flag                                                  */
      __IM  uint16_t            : 1;
      __OM  uint16_t RCHE       : 1;            /*!< [12..12] Reset Correct Hall Event Flag                                    */
      __OM  uint16_t RWHE       : 1;            /*!< [13..13] Reset Wrong Hall Event Flag                                      */
      __OM  uint16_t RIDLE      : 1;            /*!< [14..14] Reset IDLE Flag                                                  */
      __OM  uint16_t RSTR       : 1;            /*!< [15..15] Reset STR Flag                                                   */
    } bit;
  } ISR;
  __IM  uint16_t  RESERVED3;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000010) Compare State Modification Register                        */

    struct
    {
      __OM  uint16_t MCC60S     : 1;            /*!< [0..0] Capture/Compare Status Modification Bits (Set) (x = 0,
                                                     1, 2, 3)                                                                  */
      __OM  uint16_t MCC61S     : 1;            /*!< [1..1] Capture/Compare Status Modification Bits (Set) (x = 0,
                                                     1, 2, 3)                                                                  */
      __OM  uint16_t MCC62S     : 1;            /*!< [2..2] Capture/Compare Status Modification Bits (Set) (x = 0,
                                                     1, 2, 3)                                                                  */
      __IM  uint16_t            : 3;
      __OM  uint16_t MCC63S     : 1;            /*!< [6..6] Capture/Compare Status Modification Bits (Set) (x = 0,
                                                     1, 2, 3)                                                                  */
      __IM  uint16_t            : 1;
      __OM  uint16_t MCC60R     : 1;            /*!< [8..8] Capture/Compare Status Modification Bits (Reset) (x =
                                                     0, 1, 2, 3)                                                               */
      __OM  uint16_t MCC61R     : 1;            /*!< [9..9] Capture/Compare Status Modification Bits (Reset) (x =
                                                     0, 1, 2, 3)                                                               */
      __OM  uint16_t MCC62R     : 1;            /*!< [10..10] Capture/Compare Status Modification Bits (Reset) (x
                                                     = 0, 1, 2, 3)                                                             */
      __IM  uint16_t            : 3;
      __OM  uint16_t MCC63R     : 1;            /*!< [14..14] Capture/Compare Status Modification Bits (Reset) (x
                                                     = 0, 1, 2, 3)                                                             */
    } bit;
  } CMPMODIF;
  __IM  uint16_t  RESERVED4;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000014) Capture/Compare Shadow Register for Channel CC60           */

    struct
    {
      __IOM uint16_t CCS        : 16;           /*!< [15..0] Shadow Register for Channel x Capture/Compare Value               */
    } bit;
  } CC60SR;
  __IM  uint16_t  RESERVED5;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000018) Capture/Compare Shadow Register for Channel CC61           */

    struct
    {
      __IOM uint16_t CCS        : 16;           /*!< [15..0] Shadow Register for Channel x Capture/Compare Value               */
    } bit;
  } CC61SR;
  __IM  uint16_t  RESERVED6;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x0000001C) Capture/Compare Shadow Register for Channel CC62           */

    struct
    {
      __IOM uint16_t CCS        : 16;           /*!< [15..0] Shadow Register for Channel x Capture/Compare Value               */
    } bit;
  } CC62SR;
  __IM  uint16_t  RESERVED7;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000020) Capture/Compare Shadow Register for Channel CC63           */

    struct
    {
      __IOM uint16_t CCS        : 16;           /*!< [15..0] Shadow Register for Channel CC63 Compare Value                    */
    } bit;
  } CC63SR;
  __IM  uint16_t  RESERVED8;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000024) Timer T12 Period Register                                  */

    struct
    {
      __IOM uint16_t T12PV      : 16;           /*!< [15..0] T12 Period Value                                                  */
    } bit;
  } T12PR;
  __IM  uint16_t  RESERVED9;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000028) Timer T13 Period Register                                  */

    struct
    {
      __IOM uint16_t T13PV      : 16;           /*!< [15..0] T13 Period Value                                                  */
    } bit;
  } T13PR;
  __IM  uint16_t  RESERVED10;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x0000002C) Timer T12 Dead-Time Control Register                       */

    struct
    {
      __IOM uint16_t DTM        : 8;            /*!< [7..0] Dead-Time                                                          */
      __IOM uint16_t DTE0       : 1;            /*!< [8..8] Dead-Time Enable Bits                                              */
      __IOM uint16_t DTE1       : 1;            /*!< [9..9] Dead-Time Enable Bits                                              */
      __IOM uint16_t DTE2       : 1;            /*!< [10..10] Dead-Time Enable Bits                                            */
      __IM  uint16_t            : 1;
      __IM  uint16_t DTR0       : 1;            /*!< [12..12] Dead-Time Run Indication Bits                                    */
      __IM  uint16_t DTR1       : 1;            /*!< [13..13] Dead-Time Run Indication Bits                                    */
      __IM  uint16_t DTR2       : 1;            /*!< [14..14] Dead-Time Run Indication Bits                                    */
    } bit;
  } T12DTC;
  __IM  uint16_t  RESERVED11;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000030) Timer Control Register 0                                   */

    struct
    {
      __IOM uint16_t T12CLK     : 3;            /*!< [2..0] Timer T12 Input Clock Select                                       */
      __IOM uint16_t T12PRE     : 1;            /*!< [3..3] Timer T12 Prescaler Bit                                            */
      __IM  uint16_t T12R       : 1;            /*!< [4..4] Timer T12 Run Bit                                                  */
      __IM  uint16_t STE12      : 1;            /*!< [5..5] Timer T12 Shadow Transfer Enable                                   */
      __IM  uint16_t CDIR       : 1;            /*!< [6..6] Count Direction of Timer T12                                       */
      __IOM uint16_t CTM        : 1;            /*!< [7..7] T12 Operating Mode                                                 */
      __IOM uint16_t T13CLK     : 3;            /*!< [10..8] Timer T13 Input Clock Select                                      */
      __IOM uint16_t T13PRE     : 1;            /*!< [11..11] Timer T13 Prescaler Bit                                          */
      __IM  uint16_t T13R       : 1;            /*!< [12..12] Timer T13 Run Bit                                                */
      __IM  uint16_t STE13      : 1;            /*!< [13..13] Timer T13 Shadow Transfer Enable                                 */
    } bit;
  } TCTR0;
  __IM  uint16_t  RESERVED12;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000034) Capture/Compare Register for Channel CC60                  */

    struct
    {
      __IM  uint16_t CCV        : 16;           /*!< [15..0] Channel x Capture/Compare Value                                   */
    } bit;
  } CC60R;
  __IM  uint16_t  RESERVED13;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000038) Capture/Compare Register for Channel CC61                  */

    struct
    {
      __IM  uint16_t CCV        : 16;           /*!< [15..0] Channel x Capture/Compare Value                                   */
    } bit;
  } CC61R;
  __IM  uint16_t  RESERVED14;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x0000003C) Capture/Compare Register for Channel CC62                  */

    struct
    {
      __IM  uint16_t CCV        : 16;           /*!< [15..0] Channel x Capture/Compare Value                                   */
    } bit;
  } CC62R;
  __IM  uint16_t  RESERVED15;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000040) Capture/Compare T12 Mode Select Register                   */

    struct
    {
      __IOM uint16_t MSEL60     : 4;            /*!< [3..0] Capture/Compare Mode Selection                                     */
      __IOM uint16_t MSEL61     : 4;            /*!< [7..4] Capture/Compare Mode Selection                                     */
      __IOM uint16_t MSEL62     : 4;            /*!< [11..8] Capture/Compare Mode Selection                                    */
      __IOM uint16_t HSYNC      : 3;            /*!< [14..12] Hall Synchronization                                             */
      __IOM uint16_t DBYP       : 1;            /*!< [15..15] Delay Bypass                                                     */
    } bit;
  } T12MSEL;
  __IM  uint16_t  RESERVED16;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000044) Capture/Compare Interrupt Enable Register                  */

    struct
    {
      __IOM uint16_t ENCC60R    : 1;            /*!< [0..0] Capture, Compare-Match Rising Edge Interrupt Enable for
                                                     Channel 0                                                                 */
      __IOM uint16_t ENCC60F    : 1;            /*!< [1..1] Capture, Compare-Match Falling Edge Interrupt Enable
                                                     for Channel 0                                                             */
      __IOM uint16_t ENCC61R    : 1;            /*!< [2..2] Capture, Compare-Match Rising Edge Interrupt Enable for
                                                     Channel 1                                                                 */
      __IOM uint16_t ENCC61F    : 1;            /*!< [3..3] Capture, Compare-Match Falling Edge Interrupt Enable
                                                     for Channel 1                                                             */
      __IOM uint16_t ENCC62R    : 1;            /*!< [4..4] Capture, Compare-Match Rising Edge Interrupt Enable for
                                                     Channel 2                                                                 */
      __IOM uint16_t ENCC62F    : 1;            /*!< [5..5] Capture, Compare-Match Falling Edge Interrupt Enable
                                                     for Channel 2                                                             */
      __IOM uint16_t ENT12OM    : 1;            /*!< [6..6] Enable Interrupt for T12 One-Match                                 */
      __IOM uint16_t ENT12PM    : 1;            /*!< [7..7] Enable Interrupt for T12 Period-Match                              */
      __IOM uint16_t ENT13CM    : 1;            /*!< [8..8] Enable Interrupt for T13 Compare-Match                             */
      __IOM uint16_t ENT13PM    : 1;            /*!< [9..9] Enable Interrupt for T13 Period-Match                              */
      __IOM uint16_t ENTRPF     : 1;            /*!< [10..10] Enable Interrupt for Trap Flag                                   */
      __IM  uint16_t            : 1;
      __IOM uint16_t ENCHE      : 1;            /*!< [12..12] Enable Interrupt for Correct Hall Event                          */
      __IOM uint16_t ENWHE      : 1;            /*!< [13..13] Enable Interrupt for Wrong Hall Event                            */
      __IOM uint16_t ENIDLE     : 1;            /*!< [14..14] Enable Idle                                                      */
      __IOM uint16_t ENSTR      : 1;            /*!< [15..15] Enable Multi-Channel Mode Shadow Transfer Interrupt              */
    } bit;
  } IEN;
  __IM  uint16_t  RESERVED17;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000048) Capture/Compare Interrupt Node Pointer Register            */

    struct
    {
      __IOM uint16_t INPCC60    : 2;            /*!< [1..0] Interrupt Node Pointer for Channel 0 Interrupts                    */
      __IOM uint16_t INPCC61    : 2;            /*!< [3..2] Interrupt Node Pointer for Channel 1 Interrupts                    */
      __IOM uint16_t INPCC62    : 2;            /*!< [5..4] Interrupt Node Pointer for Channel 2 Interrupts                    */
      __IOM uint16_t INPCHE     : 2;            /*!< [7..6] Interrupt Node Pointer for the CHE Interrupt                       */
      __IOM uint16_t INPERR     : 2;            /*!< [9..8] Interrupt Node Pointer for Error Interrupts                        */
      __IOM uint16_t INPT12     : 2;            /*!< [11..10] Interrupt Node Pointer for Timer T12 Interrupts                  */
      __IOM uint16_t INPT13     : 2;            /*!< [13..12] Interrupt Node Pointer for Timer T13 Interrupts                  */
    } bit;
  } INP;
  __IM  uint16_t  RESERVED18;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x0000004C) Capture/Compare Interrupt Status Set Register              */

    struct
    {
      __OM  uint16_t SCC60R     : 1;            /*!< [0..0] Set Capture, Compare-Match Rising Edge Flag                        */
      __OM  uint16_t SCC60F     : 1;            /*!< [1..1] Set Capture, Compare-Match Falling Edge Flag                       */
      __OM  uint16_t SCC61R     : 1;            /*!< [2..2] Set Capture, Compare-Match Rising Edge Flag                        */
      __OM  uint16_t SCC61F     : 1;            /*!< [3..3] Set Capture, Compare-Match Falling Edge Flag                       */
      __OM  uint16_t SCC62R     : 1;            /*!< [4..4] Set Capture, Compare-Match Rising Edge Flag                        */
      __OM  uint16_t SCC62F     : 1;            /*!< [5..5] Set Capture, Compare-Match Falling Edge Flag                       */
      __OM  uint16_t ST12OM     : 1;            /*!< [6..6] Set Timer T12 One-Match Flag                                       */
      __OM  uint16_t ST12PM     : 1;            /*!< [7..7] Set Timer T12 Period-Match Flag                                    */
      __OM  uint16_t ST13CM     : 1;            /*!< [8..8] Set Timer T13 Compare-Match Flag                                   */
      __OM  uint16_t ST13PM     : 1;            /*!< [9..9] Set Timer T13 Period-Match Flag                                    */
      __OM  uint16_t STRPF      : 1;            /*!< [10..10] Set Trap Flag                                                    */
      __OM  uint16_t SWHC       : 1;            /*!< [11..11] Software Hall Compare                                            */
      __OM  uint16_t SCHE       : 1;            /*!< [12..12] Set Correct Hall Event Flag                                      */
      __OM  uint16_t SWHE       : 1;            /*!< [13..13] Set Wrong Hall Event Flag                                        */
      __OM  uint16_t SIDLE      : 1;            /*!< [14..14] Set IDLE Flag                                                    */
      __OM  uint16_t SSTR       : 1;            /*!< [15..15] Set STR Flag                                                     */
    } bit;
  } ISS;
  __IM  uint16_t  RESERVED19;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000050) Passive State Level Register                               */

    struct
    {
      __IOM uint16_t PSL        : 6;            /*!< [5..0] Compare Outputs Passive State Level                                */
      __IM  uint16_t            : 1;
      __IOM uint16_t PSL63      : 1;            /*!< [7..7] Passive State Level of Output COUT63                               */
    } bit;
  } PSLR;
  __IM  uint16_t  RESERVED20;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000054) Multi-Channel Mode Control Register                        */

    struct
    {
      __IOM uint16_t SWSEL      : 3;            /*!< [2..0] Switching Selection                                                */
      __IM  uint16_t            : 1;
      __IOM uint16_t SWSYN      : 2;            /*!< [5..4] Switching Synchronization                                          */
      __IM  uint16_t            : 2;
      __IOM uint16_t STE12U     : 1;            /*!< [8..8] Shadow Transfer Enable for T12 Upcounting                          */
      __IOM uint16_t STE12D     : 1;            /*!< [9..9] Shadow Transfer Enable for T12 Downcounting                        */
      __IOM uint16_t STE13U     : 1;            /*!< [10..10] Shadow Transfer Enable for T13 Upcounting                        */
    } bit;
  } MCMCTR;
  __IM  uint16_t  RESERVED21;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000058) Timer Control Register 2                                   */

    struct
    {
      __IOM uint16_t T12SSC     : 1;            /*!< [0..0] Timer T12 Single Shot Control                                      */
      __IOM uint16_t T13SSC     : 1;            /*!< [1..1] Timer T13 Single Shot Control                                      */
      __IOM uint16_t T13TEC     : 3;            /*!< [4..2] T13 Trigger Event Control                                          */
      __IOM uint16_t T13TED     : 2;            /*!< [6..5] Timer T13 Trigger Event Direction                                  */
      __IM  uint16_t            : 1;
      __IOM uint16_t T12RSEL    : 2;            /*!< [9..8] Timer T12 External Run Selection                                   */
      __IOM uint16_t T13RSEL    : 2;            /*!< [11..10] Timer T13 External Run Selection                                 */
    } bit;
  } TCTR2;
  __IM  uint16_t  RESERVED22;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x0000005C) Modulation Control Register                                */

    struct
    {
      __IOM uint16_t T12MODEN   : 6;            /*!< [5..0] T12 Modulation Enable                                              */
      __IM  uint16_t            : 1;
      __IOM uint16_t MCMEN      : 1;            /*!< [7..7] Multi-Channel Mode Enable                                          */
      __IOM uint16_t T13MODEN   : 6;            /*!< [13..8] T13 Modulation Enable                                             */
      __IM  uint16_t            : 1;
      __IOM uint16_t ECT13O     : 1;            /*!< [15..15] Enable Compare Timer T13 Output                                  */
    } bit;
  } MODCTR;
  __IM  uint16_t  RESERVED23;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000060) Trap Control Register                                      */

    struct
    {
      __IOM uint16_t TRPM0      : 1;            /*!< [0..0] Trap Mode Control Bits 1, 0                                        */
      __IOM uint16_t TRPM1      : 1;            /*!< [1..1] Trap Mode Control Bits 1, 0                                        */
      __IOM uint16_t TRPM2      : 1;            /*!< [2..2] Trap Mode Control Bit 2                                            */
      __IM  uint16_t            : 5;
      __IOM uint16_t TRPEN      : 6;            /*!< [13..8] Trap Enable Control                                               */
      __IOM uint16_t TRPEN13    : 1;            /*!< [14..14] Trap Enable Control for Timer T13                                */
      __IOM uint16_t TRPPEN     : 1;            /*!< [15..15] Trap Pin Enable                                                  */
    } bit;
  } TRPCTR;
  __IM  uint16_t  RESERVED24;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000064) Multi-Channel Mode Output Register                         */

    struct
    {
      __IM  uint16_t MCMP       : 6;            /*!< [5..0] Multi-Channel PWM Pattern                                          */
      __IM  uint16_t R          : 1;            /*!< [6..6] Reminder Flag                                                      */
      __IM  uint16_t            : 1;
      __IM  uint16_t EXPH       : 3;            /*!< [10..8] Expected Hall Pattern                                             */
      __IM  uint16_t CURH       : 3;            /*!< [13..11] Current Hall Pattern                                             */
    } bit;
  } MCMOUT;
  __IM  uint16_t  RESERVED25;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000068) Capture/Compare Interrupt Status Register                  */

    struct
    {
      __IM  uint16_t ICC60R     : 1;            /*!< [0..0] Capture, Compare-Match Rising Edge Flag (x = 0, 1, 2)              */
      __IM  uint16_t ICC60F     : 1;            /*!< [1..1] Capture, Compare-Match Falling Edge Flag (x = 0, 1, 2)             */
      __IM  uint16_t ICC61R     : 1;            /*!< [2..2] Capture, Compare-Match Rising Edge Flag (x = 0, 1, 2)              */
      __IM  uint16_t ICC61F     : 1;            /*!< [3..3] Capture, Compare-Match Falling Edge Flag (x = 0, 1, 2)             */
      __IM  uint16_t ICC62R     : 1;            /*!< [4..4] Capture, Compare-Match Rising Edge Flag (x = 0, 1, 2)              */
      __IM  uint16_t ICC62F     : 1;            /*!< [5..5] Capture, Compare-Match Falling Edge Flag (x = 0, 1, 2)             */
      __IM  uint16_t T12OM      : 1;            /*!< [6..6] Timer T12 One-Match Flag                                           */
      __IM  uint16_t T12PM      : 1;            /*!< [7..7] Timer T12 Period-Match Flag                                        */
      __IM  uint16_t T13CM      : 1;            /*!< [8..8] Timer T13 Compare-Match Flag                                       */
      __IM  uint16_t T13PM      : 1;            /*!< [9..9] Timer T13 Period-Match Flag                                        */
      __IM  uint16_t TRPF       : 1;            /*!< [10..10] Trap Flag                                                        */
      __IM  uint16_t TRPS       : 1;            /*!< [11..11] Trap State                                                       */
      __IM  uint16_t CHE        : 1;            /*!< [12..12] Correct Hall Event                                               */
      __IM  uint16_t WHE        : 1;            /*!< [13..13] Wrong Hall Event                                                 */
      __IM  uint16_t IDLE       : 1;            /*!< [14..14] IDLE State                                                       */
      __IM  uint16_t STR        : 1;            /*!< [15..15] Multi-Channel Mode Shadow Transfer Request                       */
    } bit;
  } IS;
  __IM  uint16_t  RESERVED26;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x0000006C) Port Input Select Register 0                               */

    struct
    {
      __IOM uint16_t ISCC60     : 2;            /*!< [1..0] Input Select for CC60                                              */
      __IOM uint16_t ISCC61     : 2;            /*!< [3..2] Input Select for CC61                                              */
      __IOM uint16_t ISCC62     : 2;            /*!< [5..4] Input Select for CC62                                              */
      __IOM uint16_t ISTRP      : 2;            /*!< [7..6] Input Select for CTRAP                                             */
      __IOM uint16_t ISPOS0     : 2;            /*!< [9..8] Input Select for CCPOS0                                            */
      __IOM uint16_t ISPOS1     : 2;            /*!< [11..10] Input Select for CCPOS1                                          */
      __IOM uint16_t ISPOS2     : 2;            /*!< [13..12] Input Select for CCPOS2                                          */
      __IOM uint16_t IST12HR    : 2;            /*!< [15..14] Input Select for T12HR                                           */
    } bit;
  } PISEL0;
  __IM  uint16_t  RESERVED27[3];

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000074) Port Input Select Register 2                               */

    struct
    {
      __IOM uint16_t IST13HR    : 2;            /*!< [1..0] Input Select for T13HR                                             */
      __IOM uint16_t ISCNT12    : 2;            /*!< [3..2] Input Select for T12 Counting Input                                */
      __IOM uint16_t ISCNT13    : 2;            /*!< [5..4] Input Select for T13 Counting Input                                */
      __IOM uint16_t T12EXT     : 1;            /*!< [6..6] Extension for T12HR Inputs                                         */
      __IOM uint16_t T13EXT     : 1;            /*!< [7..7] Extension for T13HR Inputs                                         */
    } bit;
  } PISEL2;
  __IM  uint16_t  RESERVED28;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000078) Timer T12 Counter Register                                 */

    struct
    {
      __IOM uint16_t T12CV      : 16;           /*!< [15..0] Timer T12 Counter Value                                           */
    } bit;
  } T12;
  __IM  uint16_t  RESERVED29;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x0000007C) Timer T13 Counter Register                                 */

    struct
    {
      __IOM uint16_t T13CV      : 16;           /*!< [15..0] Timer T13 Counter Value                                           */
    } bit;
  } T13;
  __IM  uint16_t  RESERVED30;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000080) Compare State Register                                     */

    struct
    {
      __IM  uint16_t CC60ST     : 1;            /*!< [0..0] Capture/Compare State Bits (x = 0, 1, 2, 3)                        */
      __IM  uint16_t CC61ST     : 1;            /*!< [1..1] Capture/Compare State Bits (x = 0, 1, 2, 3)                        */
      __IM  uint16_t CC62ST     : 1;            /*!< [2..2] Capture/Compare State Bits (x = 0, 1, 2, 3)                        */
      __IM  uint16_t CCPOS0     : 1;            /*!< [3..3] Sampled Hall Pattern Bits (x = 0, 1, 2)                            */
      __IM  uint16_t CCPOS1     : 1;            /*!< [4..4] Sampled Hall Pattern Bits (x = 0, 1, 2)                            */
      __IM  uint16_t CCPOS2     : 1;            /*!< [5..5] Sampled Hall Pattern Bits (x = 0, 1, 2)                            */
      __IM  uint16_t CC63ST     : 1;            /*!< [6..6] Capture/Compare State Bits (x = 0, 1, 2, 3)                        */
      __IM  uint16_t            : 1;
      __IOM uint16_t CC60PS     : 1;            /*!< [8..8] Passive State Select for Compare Outputs                           */
      __IOM uint16_t COUT60PS   : 1;            /*!< [9..9] Passive State Select for Compare Outputs                           */
      __IOM uint16_t CC61PS     : 1;            /*!< [10..10] Passive State Select for Compare Outputs                         */
      __IOM uint16_t COUT61PS   : 1;            /*!< [11..11] Passive State Select for Compare Outputs                         */
      __IOM uint16_t CC62PS     : 1;            /*!< [12..12] Passive State Select for Compare Outputs                         */
      __IOM uint16_t COUT62PS   : 1;            /*!< [13..13] Passive State Select for Compare Outputs                         */
      __IOM uint16_t COUT63PS   : 1;            /*!< [14..14] Passive State Select for Compare Outputs                         */
      __IOM uint16_t T13IM      : 1;            /*!< [15..15] T13 Inverted Modulation                                          */
    } bit;
  } CMPSTAT;
} CCU6_Type;                                    /*!< Size = 130 (0x82)                                                         */



/* =========================================================================================================================== */
/* ================                                            CPU                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief CPU Core (CPU)
  */

typedef struct                                  /*!< (@ 0xE000E000) CPU Structure                                              */
{
  __IM  uint32_t  RESERVED;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) Interrupt Controller Type                                  */

    struct
    {
      __IM  uint32_t INTLINESNUM : 5;           /*!< [4..0] Interrupt Lines                                                    */
    } bit;
  } ICT;
  __IM  uint32_t  RESERVED1[2];

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) SysTick Control and Status                                 */

    struct
    {
      __IOM uint32_t ENABLE     : 1;            /*!< [0..0] Enable                                                             */
      __IOM uint32_t TICKINT    : 1;            /*!< [1..1] Enables SysTick exception request                                  */
      __IOM uint32_t CLKSOURCE  : 1;            /*!< [2..2] CLK Source                                                         */
      __IM  uint32_t            : 13;
      __IOM uint32_t COUNTFLAG  : 1;            /*!< [16..16] Count Flag                                                       */
    } bit;
  } SYSTICK_CS;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000014) SysTick Reload Value                                       */

    struct
    {
      __IOM uint32_t RELOAD     : 24;           /*!< [23..0] Reload                                                            */
    } bit;
  } SYSTICK_RL;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000018) SysTick Current Value                                      */

    struct
    {
      __IOM uint32_t CURRENT    : 24;           /*!< [23..0] Current                                                           */
    } bit;
  } SYSTICK_CUR;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x0000001C) SysTick Calibration Value                                  */

    struct
    {
      __IM  uint32_t TENMS      : 24;           /*!< [23..0] Tenms                                                             */
      __IM  uint32_t            : 6;
      __IM  uint32_t SKEW       : 1;            /*!< [30..30] Skew                                                             */
      __IM  uint32_t NOREF      : 1;            /*!< [31..31] No Reference Clock                                               */
    } bit;
  } SYSTICK_CAL;
  __IM  uint32_t  RESERVED2[56];

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000100) Interrupt Set-Enable                                       */

    struct
    {
      __IOM uint32_t Int_GPT1   : 1;            /*!< [0..0] Interrupt Set for GPT1                                             */
      __IOM uint32_t Int_GPT2   : 1;            /*!< [1..1] Interrupt Set for GPT2                                             */
      __IOM uint32_t Int_ADC2   : 1;            /*!< [2..2] Interrupt Set for MU, ADC2                                         */
      __IOM uint32_t Int_ADC1   : 1;            /*!< [3..3] Interrupt Set for ADC1                                             */
      __IOM uint32_t Int_CCU6SR0 : 1;           /*!< [4..4] Interrupt Set for CCU6 SR0                                         */
      __IOM uint32_t Int_CCU6SR1 : 1;           /*!< [5..5] Interrupt Set for CCU6 SR1                                         */
      __IOM uint32_t Int_CCU6SR2 : 1;           /*!< [6..6] Interrupt Set for CCU6 SR2                                         */
      __IOM uint32_t Int_CCU6SR3 : 1;           /*!< [7..7] Interrupt Set for CCU6 SR3                                         */
      __IOM uint32_t Int_SSC1   : 1;            /*!< [8..8] Interrupt Set for SSC1                                             */
      __IOM uint32_t Int_SSC2   : 1;            /*!< [9..9] Interrupt Set for SSC2                                             */
      __IOM uint32_t Int_UART1  : 1;            /*!< [10..10] Interrupt Set for UART1                                          */
      __IOM uint32_t Int_UART2  : 1;            /*!< [11..11] Interrupt Set for UART2                                          */
      __IOM uint32_t Int_EXINT0 : 1;            /*!< [12..12] Interrupt Set for External Int 0                                 */
      __IOM uint32_t Int_EXINT1 : 1;            /*!< [13..13] Interrupt Set for External Int 1                                 */
      __IOM uint32_t Int_BDRV   : 1;            /*!< [14..14] Interrupt Set for Bridge Driver                                  */
      __IOM uint32_t Int_DMA    : 1;            /*!< [15..15] Interrupt Set for DMA                                            */
    } bit;
  } NVIC_ISER0;
  __IM  uint32_t  RESERVED3[31];

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000180) Interrupt Clear-Enable                                     */

    struct
    {
      __IOM uint32_t Int_GPT1   : 1;            /*!< [0..0] Interrupt Clear for GPT1                                           */
      __IOM uint32_t Int_GPT2   : 1;            /*!< [1..1] Interrupt Clear for GPT2                                           */
      __IOM uint32_t Int_ADC2   : 1;            /*!< [2..2] Interrupt Clear for MU, ADC2                                       */
      __IOM uint32_t Int_ADC1   : 1;            /*!< [3..3] Interrupt Clear for ADC1                                           */
      __IOM uint32_t Int_CCU6SR0 : 1;           /*!< [4..4] Interrupt Clear for CCU6 SR0                                       */
      __IOM uint32_t Int_CCU6SR1 : 1;           /*!< [5..5] Interrupt Clear for CCU6 SR1                                       */
      __IOM uint32_t Int_CCU6SR2 : 1;           /*!< [6..6] Interrupt Clear for CCU6 SR2                                       */
      __IOM uint32_t Int_CCU6SR3 : 1;           /*!< [7..7] Interrupt Clear for CCU6 SR3                                       */
      __IOM uint32_t Int_SSC1   : 1;            /*!< [8..8] Interrupt Clear for SSC1                                           */
      __IOM uint32_t Int_SSC2   : 1;            /*!< [9..9] Interrupt Clear for SSC2                                           */
      __IOM uint32_t Int_UART1  : 1;            /*!< [10..10] Interrupt Clear for UART1                                        */
      __IOM uint32_t Int_UART2  : 1;            /*!< [11..11] Interrupt Clear for UART2                                        */
      __IOM uint32_t Int_EXINT0 : 1;            /*!< [12..12] Interrupt Clear for External Int 0                               */
      __IOM uint32_t Int_EXINT1 : 1;            /*!< [13..13] Interrupt Clear for External Int 1                               */
      __IOM uint32_t Int_BDRV   : 1;            /*!< [14..14] Interrupt Clear for Bridge Driver                                */
      __IOM uint32_t Int_DMA    : 1;            /*!< [15..15] Interrupt Clr for DMA                                            */
    } bit;
  } NVIC_ICER0;
  __IM  uint32_t  RESERVED4[31];

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000200) Interrupt Set-Pending                                      */

    struct
    {
      __IOM uint32_t Int_GPT1   : 1;            /*!< [0..0] Interrupt Set Pending for GPT1                                     */
      __IOM uint32_t Int_GPT2   : 1;            /*!< [1..1] Interrupt Set Pending for GPT2                                     */
      __IOM uint32_t Int_ADC2   : 1;            /*!< [2..2] Interrupt Set Pending for MU, ADC2                                 */
      __IOM uint32_t Int_ADC1   : 1;            /*!< [3..3] Interrupt Set Pending for ADC1                                     */
      __IOM uint32_t Int_CCU6SR0 : 1;           /*!< [4..4] Interrupt Set Pending for CCU6 SR0                                 */
      __IOM uint32_t Int_CCU6SR1 : 1;           /*!< [5..5] Interrupt Set Pending for CCU6 SR1                                 */
      __IOM uint32_t Int_CCU6SR2 : 1;           /*!< [6..6] Interrupt Set Pending for CCU6 SR2                                 */
      __IOM uint32_t Int_CCU6SR3 : 1;           /*!< [7..7] Interrupt Set Pending for CCU6 SR3                                 */
      __IOM uint32_t Int_SSC1   : 1;            /*!< [8..8] Interrupt Set Pending for SSC1                                     */
      __IOM uint32_t Int_SSC2   : 1;            /*!< [9..9] Interrupt Set Pending for SSC2                                     */
      __IOM uint32_t Int_UART1  : 1;            /*!< [10..10] Interrupt Set Pending for UART1                                  */
      __IOM uint32_t Int_UART2  : 1;            /*!< [11..11] Interrupt Set Pending for UART2                                  */
      __IOM uint32_t Int_EXINT0 : 1;            /*!< [12..12] Interrupt Set Pending for External Int 0                         */
      __IOM uint32_t Int_EXINT1 : 1;            /*!< [13..13] Interrupt Set Pending for External Int 1                         */
      __IOM uint32_t Int_BDRV   : 1;            /*!< [14..14] Interrupt Set Pending for Bridge Driver                          */
      __IOM uint32_t Int_DMA    : 1;            /*!< [15..15] Interrupt Set Pend for DMA                                       */
    } bit;
  } NVIC_ISPR0;
  __IM  uint32_t  RESERVED5[31];

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000280) Interrupt Clear-Pending                                    */

    struct
    {
      __IOM uint32_t Int_GPT1   : 1;            /*!< [0..0] Interrupt Clear Pending for GPT1                                   */
      __IOM uint32_t Int_GPT2   : 1;            /*!< [1..1] Interrupt Clear Pending for GPT2                                   */
      __IOM uint32_t Int_ADC2   : 1;            /*!< [2..2] Interrupt Clear Pending for MU, ADC2                               */
      __IOM uint32_t Int_ADC1   : 1;            /*!< [3..3] Interrupt Clear Pending for ADC1                                   */
      __IOM uint32_t Int_CCU6SR0 : 1;           /*!< [4..4] Interrupt Clear Pending for CCU6 SR0                               */
      __IOM uint32_t Int_CCU6SR1 : 1;           /*!< [5..5] Interrupt Clear Pending for CCU6 SR1                               */
      __IOM uint32_t Int_CCU6SR2 : 1;           /*!< [6..6] Interrupt Clear Pending for CCU6 SR2                               */
      __IOM uint32_t Int_CCU6SR3 : 1;           /*!< [7..7] Interrupt Clear Pending for CCU6 SR3                               */
      __IOM uint32_t Int_SSC1   : 1;            /*!< [8..8] Interrupt Clear Pending for SSC1                                   */
      __IOM uint32_t Int_SSC2   : 1;            /*!< [9..9] Interrupt Clear Pending for SSC2                                   */
      __IOM uint32_t Int_UART1  : 1;            /*!< [10..10] Interrupt Clear Pending for UART1                                */
      __IOM uint32_t Int_UART2  : 1;            /*!< [11..11] Interrupt Clear Pending for UART2                                */
      __IOM uint32_t Int_EXINT0 : 1;            /*!< [12..12] Interrupt Clear Pending for External Int 0                       */
      __IOM uint32_t Int_EXINT1 : 1;            /*!< [13..13] Interrupt Clear Pending for External Int 1                       */
      __IOM uint32_t Int_BDRV   : 1;            /*!< [14..14] Interrupt Clear Pending for Bridge Driver                        */
      __IOM uint32_t Int_DMA    : 1;            /*!< [15..15] Interrupt Clr Pend for DMA                                       */
    } bit;
  } NVIC_ICPR0;
  __IM  uint32_t  RESERVED6[31];

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000300) Active Bit Register Interrupt Active Flags                 */

    struct
    {
      __IM  uint32_t Int_GPT1   : 1;            /*!< [0..0] Interrupt Active for GPT1                                          */
      __IM  uint32_t Int_GPT2   : 1;            /*!< [1..1] Interrupt Active for GPT2                                          */
      __IM  uint32_t Int_ADC2   : 1;            /*!< [2..2] Interrupt Active for MU, ADC2                                      */
      __IM  uint32_t Int_ADC1   : 1;            /*!< [3..3] Interrupt Active for ADC1                                          */
      __IM  uint32_t Int_CCU6SR0 : 1;           /*!< [4..4] Interrupt Active for CCU6 SR0                                      */
      __IM  uint32_t Int_CCU6SR1 : 1;           /*!< [5..5] Interrupt Active for CCU6 SR1                                      */
      __IM  uint32_t Int_CCU6SR2 : 1;           /*!< [6..6] Interrupt Active for CCU6 SR2                                      */
      __IM  uint32_t Int_CCU6SR3 : 1;           /*!< [7..7] Interrupt Active for CCU6 SR3                                      */
      __IM  uint32_t Int_SSC1   : 1;            /*!< [8..8] Interrupt Active for SSC1                                          */
      __IM  uint32_t Int_SSC2   : 1;            /*!< [9..9] Interrupt Active for SSC2                                          */
      __IM  uint32_t Int_UART1  : 1;            /*!< [10..10] Interrupt Active for UART1                                       */
      __IM  uint32_t Int_UART2  : 1;            /*!< [11..11] Interrupt Active for UART2                                       */
      __IM  uint32_t Int_EXINT0 : 1;            /*!< [12..12] Interrupt Active for External Int 0                              */
      __IM  uint32_t Int_EXINT1 : 1;            /*!< [13..13] Interrupt Active for External Int 1                              */
      __IM  uint32_t Int_BDRV   : 1;            /*!< [14..14] Interrupt Active for Bridge Driver                               */
      __IM  uint32_t Int_DMA    : 1;            /*!< [15..15] Interrupt Active for DMA                                         */
    } bit;
  } NVIC_IABR0;
  __IM  uint32_t  RESERVED7[63];

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000400) Interrupt Priority                                         */

    struct
    {
      __IOM uint32_t PRI_GPT1   : 8;            /*!< [7..0] Priority for GPT1                                                  */
      __IOM uint32_t PRI_GPT2   : 8;            /*!< [15..8] Priority for GPT2                                                 */
      __IOM uint32_t PRI_ADC2   : 8;            /*!< [23..16] Priority for MU, ADC2                                            */
      __IOM uint32_t PRI_ADC1   : 8;            /*!< [31..24] Priority for ADC1                                                */
    } bit;
  } NVIC_IPR0;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000404) Interrupt Priority                                         */

    struct
    {
      __IOM uint32_t PRI_CCU6SR0 : 8;           /*!< [7..0] Priority for CCU6 SR0                                              */
      __IOM uint32_t PRI_CCU6SR1 : 8;           /*!< [15..8] Priority for CCU6 SR1                                             */
      __IOM uint32_t PRI_CCU6SR2 : 8;           /*!< [23..16] Priority for CCU6 SR2                                            */
      __IOM uint32_t PRI_CCU6SR3 : 8;           /*!< [31..24] Priority for CCU6 SR3                                            */
    } bit;
  } NVIC_IPR1;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000408) Interrupt Priority                                         */

    struct
    {
      __IOM uint32_t PRI_SSC1   : 8;            /*!< [7..0] Priority for SSC1                                                  */
      __IOM uint32_t PRI_SSC2   : 8;            /*!< [15..8] Priority for SSC2                                                 */
      __IOM uint32_t PRI_UART1  : 8;            /*!< [23..16] Priority for UART1                                               */
      __IOM uint32_t PRI_UART2  : 8;            /*!< [31..24] Priority for UART2                                               */
    } bit;
  } NVIC_IPR2;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x0000040C) Interrupt Priority                                         */

    struct
    {
      __IOM uint32_t PRI_EXINT0 : 8;            /*!< [7..0] Priority for Ext. Int 0                                            */
      __IOM uint32_t PRI_EXINT1 : 8;            /*!< [15..8] Priority for Ext. Int 1                                           */
      __IOM uint32_t PRI_BDRV   : 8;            /*!< [23..16] Priority for Bridge Driver                                       */
      __IOM uint32_t PRI_DMA    : 8;            /*!< [31..24] Priority for DMA                                                 */
    } bit;
  } NVIC_IPR3;
  __IM  uint32_t  RESERVED8[572];

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000D00) CPU ID Base Register                                       */

    struct
    {
      __IM  uint32_t REVISION   : 4;            /*!< [3..0] Revision Number                                                    */
      __IM  uint32_t PARTNO     : 12;           /*!< [15..4] Part Number                                                       */
      __IM  uint32_t ARCHITECTURE : 4;          /*!< [19..16] Architecture                                                     */
      __IM  uint32_t VARIANT    : 4;            /*!< [23..20] Variant Number                                                   */
      __IM  uint32_t IMPLEMENTER : 8;           /*!< [31..24] Implementer Code                                                 */
    } bit;
  } CPUID;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000D04) Interrupt Control State Register                           */

    struct
    {
      __IM  uint32_t VECTACTIVE : 9;            /*!< [8..0] Active ISR number field                                            */
      __IM  uint32_t            : 2;
      __IM  uint32_t RETTOBASE  : 1;            /*!< [11..11] RETTOBASE                                                        */
      __IM  uint32_t VECTPENDING : 9;           /*!< [20..12] Pending ISR number field                                         */
      __IM  uint32_t            : 1;
      __IM  uint32_t ISRPENDING : 1;            /*!< [22..22] Interrupt pending flag. Excludes NMI and Faults                  */
      __IM  uint32_t ISRPREEMPT : 1;            /*!< [23..23] ISRPREEMPT                                                       */
      __IM  uint32_t            : 1;
      __OM  uint32_t PENDSTCLR  : 1;            /*!< [25..25] SysTick exception clear-pending bit                              */
      __IOM uint32_t PENDSTSET  : 1;            /*!< [26..26] SysTick exception set-pending bit                                */
      __OM  uint32_t PENDSVCLR  : 1;            /*!< [27..27] PendSV clear-pending bit                                         */
      __IOM uint32_t PENDSVSET  : 1;            /*!< [28..28] PendSV set-pending bit                                           */
      __IM  uint32_t            : 2;
      __IOM uint32_t NMIPENDSET : 1;            /*!< [31..31] NMI PendSet                                                      */
    } bit;
  } ICSR;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000D08) Vector Table Offset Register                               */

    struct
    {
      __IM  uint32_t            : 7;
      __IOM uint32_t TBLOFF     : 25;           /*!< [31..7] Vector Table Offset                                               */
    } bit;
  } VTOR;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000D0C) Application Interrupt/Reset Control Register               */

    struct
    {
      __IOM uint32_t VECTRESET  : 1;            /*!< [0..0] VECTRESET for debug only                                           */
      __IOM uint32_t VECTCLRACTIVE : 1;         /*!< [1..1] VECTCLRACTIVE for debug only                                       */
      __IOM uint32_t SYSRESETREQ : 1;           /*!< [2..2] System Reset Request                                               */
      __IM  uint32_t            : 5;
      __IOM uint32_t PRIGROUP   : 3;            /*!< [10..8] Priority Grouping                                                 */
      __IM  uint32_t            : 4;
      __IM  uint32_t ENDIANNESS : 1;            /*!< [15..15] Memory System Endianness                                         */
      __IOM uint32_t VECTKEY    : 16;           /*!< [31..16] Vector Key                                                       */
    } bit;
  } AIRCR;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000D10) System Control Register                                    */

    struct
    {
      __IM  uint32_t            : 1;
      __IOM uint32_t SLEEPONEXIT : 1;           /*!< [1..1] Sleep on Exit                                                      */
      __IOM uint32_t SLEEPDEEP  : 1;            /*!< [2..2] Sleep Deep                                                         */
      __IM  uint32_t            : 1;
      __IOM uint32_t SEVONPEND  : 1;            /*!< [4..4] SEVONPEND                                                          */
    } bit;
  } SCR;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000D14) Configuration Control Register                             */

    struct
    {
      __IOM uint32_t NONBASETHRDENA : 1;        /*!< [0..0] Indicates how the processor enters Thread mode                     */
      __IOM uint32_t USERSETMPEND : 1;          /*!< [1..1] Enables unprivileged software access to the STIR                   */
      __IM  uint32_t            : 1;
      __IOM uint32_t UNALIGN_TRP : 1;           /*!< [3..3] Enables unaligned access traps                                     */
      __IOM uint32_t DIV_0_TRP  : 1;            /*!< [4..4] Enables faulting or halting when the processor executes
                                                     an SDIV or UDIV instruction with a divisor of 0                           */
      __IM  uint32_t            : 3;
      __IOM uint32_t BFHFMIGN   : 1;            /*!< [8..8] Enables handlers with priority -1 or -2 to ignore data
                                                     BusFaults caused by load and store instructions                           */
      __IOM uint32_t STKALIGN   : 1;            /*!< [9..9] stack alignment                                                    */
    } bit;
  } CCR;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000D18) System Handler Priority Register 1                         */

    struct
    {
      __IOM uint32_t PRI_4      : 8;            /*!< [7..0] Priority of System Handler 4, MemManage                            */
      __IOM uint32_t PRI_5      : 8;            /*!< [15..8] Priority of System Handler 5, BusFault                            */
      __IOM uint32_t PRI_6      : 8;            /*!< [23..16] Priority of System Handler 6, UsageFault                         */
      __IOM uint32_t PRI_7      : 8;            /*!< [31..24] Reserved for Priority of System Handler 7                        */
    } bit;
  } SHPR1;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000D1C) System Handler Priority Register 2                         */

    struct
    {
      __IOM uint32_t PRI_8      : 8;            /*!< [7..0] Reserved for Priority of System Handler 8                          */
      __IOM uint32_t PRI_9      : 8;            /*!< [15..8] Reserved for Priority of System Handler 9                         */
      __IOM uint32_t PRI_10     : 8;            /*!< [23..16] Reserved for Priority of System Handler 10                       */
      __IOM uint32_t PRI_11     : 8;            /*!< [31..24] Priority of System Handler 11, SVCall                            */
    } bit;
  } SHPR2;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000D20) System Handler Priority Register 3                         */

    struct
    {
      __IOM uint32_t PRI_12     : 8;            /*!< [7..0] Priority of System Handler 12, DebugMonitor                        */
      __IOM uint32_t PRI_13     : 8;            /*!< [15..8] Reserved for Priority of System Handler 13                        */
      __IOM uint32_t PRI_14     : 8;            /*!< [23..16] Priority of System Handler 14, PendSV                            */
      __IOM uint32_t PRI_15     : 8;            /*!< [31..24] Priority of System Handler 15, SysTick                           */
    } bit;
  } SHPR3;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000D24) System Handler Control and State Register                  */

    struct
    {
      __IOM uint32_t MEMFAULTACT : 1;           /*!< [0..0] MEMFAULTACT                                                        */
      __IOM uint32_t BUSFAULTACT : 1;           /*!< [1..1] BUSFAULTACT                                                        */
      __IM  uint32_t            : 1;
      __IOM uint32_t USGFAULTACT : 1;           /*!< [3..3] USGFAULTACT                                                        */
      __IM  uint32_t            : 3;
      __IOM uint32_t SVCALLACT  : 1;            /*!< [7..7] SVCALLACT                                                          */
      __IOM uint32_t MONITORACT : 1;            /*!< [8..8] MONITORACT                                                         */
      __IM  uint32_t            : 1;
      __IOM uint32_t PENDSVACT  : 1;            /*!< [10..10] PENDSVACT                                                        */
      __IOM uint32_t SYSTICKACT : 1;            /*!< [11..11] SYSTICKACT                                                       */
      __IOM uint32_t USGFAULTPENDED : 1;        /*!< [12..12] USGFAULTPENDED                                                   */
      __IOM uint32_t MEMFAULTPENDED : 1;        /*!< [13..13] MEMFAULTPENDED                                                   */
      __IOM uint32_t BUSFAULTPENDED : 1;        /*!< [14..14] BUSFAULTPENDED                                                   */
      __IOM uint32_t SVCALLPENDED : 1;          /*!< [15..15] SVCALLPENDED                                                     */
      __IOM uint32_t MEMFAULTENA : 1;           /*!< [16..16] MEMFAULTENA                                                      */
      __IOM uint32_t BUSFAULTENA : 1;           /*!< [17..17] BUSFAULTENA                                                      */
      __IOM uint32_t USGFAULTENA : 1;           /*!< [18..18] USGFAULTENA                                                      */
    } bit;
  } SHCSR;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000D28) Configurable Fault Status Register                         */

    struct
    {
      __IOM uint32_t IACCVIOL   : 1;            /*!< [0..0] Instruction access violation flag                                  */
      __IOM uint32_t DACCVIOL   : 1;            /*!< [1..1] Data access violation flag                                         */
      __IM  uint32_t            : 1;
      __IOM uint32_t MUNSTKERR  : 1;            /*!< [3..3] MemManage fault on unstacking for a return from exception          */
      __IOM uint32_t MSTERR     : 1;            /*!< [4..4] MemManage fault on stacking for exception entry                    */
      __IM  uint32_t            : 2;
      __IOM uint32_t MMARVALID  : 1;            /*!< [7..7] MemManage Fault Address Register (MMFAR) valid flag                */
      __IOM uint32_t IBUSERR    : 1;            /*!< [8..8] Instruction bus error                                              */
      __IOM uint32_t PRECISERR  : 1;            /*!< [9..9] Precise data bus error                                             */
      __IOM uint32_t IMPRECISERR : 1;           /*!< [10..10] Imprecise data bus error                                         */
      __IOM uint32_t UNSTKERR   : 1;            /*!< [11..11] BusFault on unstacking for a return from exception               */
      __IOM uint32_t STKERR     : 1;            /*!< [12..12] BusFault on stacking for exception entry                         */
      __IM  uint32_t            : 2;
      __IOM uint32_t BFARVALID  : 1;            /*!< [15..15] BFAR Valid                                                       */
      __IOM uint32_t UNDEFINSTR : 1;            /*!< [16..16] Undefined instruction UsageFault                                 */
      __IOM uint32_t INVSTATE   : 1;            /*!< [17..17] Invalid state UsageFault                                         */
      __IOM uint32_t INVPC      : 1;            /*!< [18..18] Invalid PC load UsageFault                                       */
      __IOM uint32_t NOCP       : 1;            /*!< [19..19] No coprocessor UsageFault                                        */
      __IM  uint32_t            : 4;
      __IOM uint32_t UNALIGNED  : 1;            /*!< [24..24] Unaligned access UsageFault                                      */
      __IOM uint32_t DIVBYZERO  : 1;            /*!< [25..25] Divide by Zero                                                   */
    } bit;
  } CFSR;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000D2C) Hard Fault Status Register                                 */

    struct
    {
      __IM  uint32_t            : 1;
      __IOM uint32_t VECTTBL    : 1;            /*!< [1..1] VECTTBL                                                            */
      __IM  uint32_t            : 28;
      __IOM uint32_t FORCED     : 1;            /*!< [30..30] Forced                                                           */
      __IOM uint32_t DEBUGEVT   : 1;            /*!< [31..31] Debug Event                                                      */
    } bit;
  } HFSR;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000D30) Debug Fault Status Register                                */

    struct
    {
      __IOM uint32_t HALTED     : 1;            /*!< [0..0] HALTED                                                             */
      __IOM uint32_t BKPT       : 1;            /*!< [1..1] BKPT                                                               */
      __IOM uint32_t DWTTRAP    : 1;            /*!< [2..2] DWTTRAP                                                            */
      __IOM uint32_t VCATCH     : 1;            /*!< [3..3] Vector Catch                                                       */
      __IOM uint32_t EXTERNAL   : 1;            /*!< [4..4] External                                                           */
    } bit;
  } DFSR;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000D34) MemManage Fault Status Register                            */

    struct
    {
      __IOM uint32_t ADDRESS    : 32;           /*!< [31..0] Data Address for an MPU Fault                                     */
    } bit;
  } MMFAR;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000D38) Bus Fault Status Register                                  */

    struct
    {
      __IOM uint32_t ADDRESS    : 32;           /*!< [31..0] Data Address for a precise BusFault                               */
    } bit;
  } BFAR;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000D3C) Auxiliary Fault Status Register                            */

    struct
    {
      __IOM uint32_t CP0        : 2;            /*!< [1..0] Access Privileges for Coprocessor 0 (n= 0-7, 10, 11)               */
      __IOM uint32_t CP1        : 2;            /*!< [3..2] Access Privileges for Coprocessor 1 (n= 0-7, 10, 11)               */
      __IOM uint32_t CP2        : 2;            /*!< [5..4] Access Privileges for Coprocessor 2 (n= 0-7, 10, 11)               */
      __IOM uint32_t CP3        : 2;            /*!< [7..6] Access Privileges for Coprocessor 3 (n= 0-7, 10, 11)               */
      __IOM uint32_t CP4        : 2;            /*!< [9..8] Access Privileges for Coprocessor 4 (n= 0-7, 10, 11)               */
      __IOM uint32_t CP5        : 2;            /*!< [11..10] Access Privileges for Coprocessor 5 (n= 0-7, 10, 11)             */
      __IOM uint32_t CP6        : 2;            /*!< [13..12] Access Privileges for Coprocessor 6 (n= 0-7, 10, 11)             */
      __IOM uint32_t CP7        : 2;            /*!< [15..14] Access Privileges for Coprocessor 7 (n= 0-7, 10, 11)             */
      __IM  uint32_t            : 4;
      __IOM uint32_t CP10       : 2;            /*!< [21..20] Access Privileges for Coprocessor 10 (n= 0-7, 10, 11)            */
      __IOM uint32_t CP11       : 2;            /*!< [23..22] Access Privileges for Coprocessor 11 (n= 0-7, 10, 11)            */
    } bit;
  } AFSR;
} CPU_Type;                                     /*!< Size = 3392 (0xd40)                                                       */



/* ================================================================================ */
/* ================                       CSA                      ================ */
/* ================================================================================ */


/**
  * @brief Current Sense Amplifier (CSA)
  */

typedef struct                                      /*!< (@ 0x48018000) CSA Structure                                          */
{
  __I  uint32_t  RESERVED0[3];

  union
  {
    __IO uint32_t  reg;                             /*!< (@ 0x4801800C) Current Sense Amplifier Control Register               */

    struct
    {
      __IO uint32_t  EN         :  1;               /*!< [0..0] OPA enable                                                     */
      __IO uint32_t  GAIN       :  2;               /*!< [1..2] OPA gain setting                                               */
      uint32_t             :  5;
      __IO uint32_t  VZERO      :  1;               /*!< [8..8] Current Sense Output Voltage Level to Ground                   */
    } bit;                                          /*!< [9] BitSize                                                           */
  } CTRL;
} CSA_Type;


/* =========================================================================================================================== */
/* ================                                            DMA                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief Direct Memeory Access (DMA)
  */

typedef struct                                  /*!< (@ 0x50014000) DMA Structure                                              */
{

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) DMA Status                                                 */

    struct
    {
      __IM  uint32_t MASTER_ENABLE : 1;         /*!< [0..0] Enable Status of the Controller                                    */
      __IM  uint32_t            : 3;
      __IM  uint32_t STATE      : 4;            /*!< [7..4] Current State of the Control State Machine                         */
      __IM  uint32_t            : 8;
      __IM  uint32_t CHNLS_MINUS1 : 5;          /*!< [20..16] Available Channels minus 1                                       */
    } bit;
  } STATUS;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) DMA Configuration                                          */

    struct
    {
      __OM  uint32_t MASTER_ENABLE : 1;         /*!< [0..0] Enable for the Controller                                          */
      __IM  uint32_t            : 4;
      __OM  uint32_t CHN1_PROT_CTRL : 3;        /*!< [7..5] CHN1_PROT_CTRL                                                     */
    } bit;
  } CFG;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) Channel Control Data Base Pointer                          */

    struct
    {
      __IM  uint32_t            : 9;
      __IOM uint32_t CTRL_BASE_PTR : 23;        /*!< [31..9] CTRL_BASE_PTR                                                     */
    } bit;
  } CTRL_BASE_PTR;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) Channel Alternate Control Data Base Pointer                */

    struct
    {
      __IM  uint32_t ALT_CTRL_BASE_PTR : 32;    /*!< [31..0] Base Address of the Alternate Data Structure                      */
    } bit;
  } ALT_CTRL_BASE_PTR;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) Channel Wait on Request Status                             */

    struct
    {
      __IM  uint32_t WAITONREQ_STATUS : 14;     /*!< [13..0] Channel Wait on Request Status                                    */
    } bit;
  } WAITONREQ_STATUS;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000014) Channel Software Request                                   */

    struct
    {
      __OM  uint32_t CHNL_SW_REQUEST : 14;      /*!< [13..0] CHNL_SW_REQUEST                                                   */
    } bit;
  } CHNL_SW_REQUEST;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000018) Channel Useburst Set                                       */

    struct
    {
      __IOM uint32_t CHNL_USEBURST_SET : 14;    /*!< [13..0] CHNL_USEBURST_SET: 0b0=on read: DMA channel n responds
                                                     to requests that it receives on dma_req[C] or dma_sreq[C].
                                                     The controller performs 2, or single, bus transfers., 0b1=on
                                                     read: DMA channel n does not respond to requests that it
                                                     receives on dma_req[C] or dma_sreq[C]. The controller only
                                                     reponds to dma_req[C] requests and performs 2 transfers.,
                                                     0b0=on write: No effect. Use the CHNL_USEBURST_CLR Register
                                                     to set bit [C] to 0., 0b1=on write: Disables dma_sreq[C]
                                                     from generating DMA requests. The controller                              */
    } bit;
  } CHNL_USEBURST_SET;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x0000001C) Channel Useburst Clear                                     */

    struct
    {
      __OM  uint32_t CHNL_USEBURST_CLR : 14;    /*!< [13..0] CHNL_USEBURST_CLR                                                 */
    } bit;
  } CHNL_USEBURST_CLR;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000020) Channel Request Mask Set                                   */

    struct
    {
      __IOM uint32_t CHNL_REQ_MASK_SET : 14;    /*!< [13..0] CHNL_REQ_MASK_SET: 0b0=on read: External requests are
                                                     enabled for channel C., 0b1=on read: External requests
                                                     are disabled for channel C., 0b0=on write: No effect. Use
                                                     the CHNL_REQ_MASK_CLR Register to enable DMA requests.,
                                                     0b1=on write: Disables dma_req[C] and dma_sreq[C] from
                                                     generating DMA requests.,                                                 */
    } bit;
  } CHNL_REQ_MASK_SET;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000024) Channel Request Mask Clear                                 */

    struct
    {
      __OM  uint32_t CHNL_REQ_MASK_CLR : 14;    /*!< [13..0] CHNL_REQ_MASK_CLR                                                 */
    } bit;
  } CHNL_REQ_MASK_CLR;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000028) Channel Enable Set                                         */

    struct
    {
      __IOM uint32_t CHNL_ENABLE_SET : 14;      /*!< [13..0] CHNL_ENABLE_SET: 0b0=on read: Channel C is disabled.,
                                                     0b1=on read: Channel C is enabled., 0b0=on write: No effect.
                                                     Use the CHNL_ENABLE_CLR Register to disable a channel.,
                                                     0b1=on write: Enables channel C.,                                         */
    } bit;
  } CHNL_ENABLE_SET;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x0000002C) Channel Enable Clear                                       */

    struct
    {
      __OM  uint32_t CHNL_ENABLE_CLR : 14;      /*!< [13..0] CHNL_ENABLE_CLR                                                   */
    } bit;
  } CHNL_ENABLE_CLR;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000030) Channel Primary-Alternate Set                              */

    struct
    {
      __IOM uint32_t CHNL_PRI_ALT_SET : 14;     /*!< [13..0] CHNL_PRI_ALT_SET: 0b0=on read: DMA channel C is using
                                                     the primary data structure., 0b1=on read: DMA channel C
                                                     is using the alternate data structure., 0b0=on write: No
                                                     effect. Use the CHNL_PRI_ALT_CLR Register to set bit [C]
                                                     to 0., 0b1=on write: Selects the alternate data structure
                                                     for channel C.,                                                           */
    } bit;
  } CHNL_PRI_ALT_SET;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000034) Channel Primary-Alternate Clear                            */

    struct
    {
      __OM  uint32_t CHNL_PRI_ALT_CLR : 14;     /*!< [13..0] CHNL_PRI_ALT_CLR                                                  */
    } bit;
  } CHNL_PRI_ALT_CLR;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000038) Channel Priority Set                                       */

    struct
    {
      __IOM uint32_t CHNL_PRIORITY_SET : 14;    /*!< [13..0] CHNL_PRIORITY_SET: 0b0=on read: DMA channel C is using
                                                     the default priority level., 0b1=on read: DMA channel C
                                                     is using a high priority level., 0b0=on write: No effect.
                                                     Use the CHNL_ENABLE_CLR Register to set channel C to the
                                                     default priority level., 0b1=on write: Channel C uses the
                                                     high priority level.,                                                     */
    } bit;
  } CHNL_PRIORITY_SET;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x0000003C) Channel Priority Clear                                     */

    struct
    {
      __OM  uint32_t CHNL_PRIORITY_CLR : 14;    /*!< [13..0] CHNL_PRIORITY_CLR                                                 */
    } bit;
  } CHNL_PRIORITY_CLR;
  __IM  uint32_t  RESERVED[3];

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x0000004C) Bus Error Clear                                            */

    struct
    {
      __IOM uint32_t ERR_CLR    : 1;            /*!< [0..0] ERR_CLR: 0b0=on read: dma_err is LOW., 0b1=on read: dma_err
                                                     is HIGH., 0b0=on write: No effect, status of dma_err is
                                                     unchanged., 0b1=on write: Sets dma_err LOW.,                              */
    } bit;
  } ERR_CLR;
} DMA_Type;                                     /*!< Size = 80 (0x50)                                                          */



/* =========================================================================================================================== */
/* ================                                          GPT12E                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief General Purpose Timer 12E (GPT12E)
  */

typedef struct                                  /*!< (@ 0x40010000) GPT12E Structure                                           */
{

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000000) Module Identification Register                             */

    struct
    {
      __IM  uint16_t MOD_REV    : 8;            /*!< [7..0] Module Revision Number                                             */
      __IM  uint16_t MOD_TYPE   : 8;            /*!< [15..8] Module Identification Number                                      */
    } bit;
  } ID;
  __IM  uint16_t  RESERVED;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000004) Port Input Select Register                                 */

    struct
    {
      __IOM uint16_t IST2IN     : 1;            /*!< [0..0] Input Select for T2IN                                              */
      __IOM uint16_t IST2EUD    : 1;            /*!< [1..1] Input Select for T2EUD                                             */
      __IOM uint16_t IST3IN     : 2;            /*!< [3..2] Input Select for T3IN                                              */
      __IOM uint16_t IST3EUD    : 2;            /*!< [5..4] Input Select for T3EUD                                             */
      __IOM uint16_t IST4IN     : 2;            /*!< [7..6] Input Select for T4IN                                              */
      __IOM uint16_t IST4EUD    : 2;            /*!< [9..8] Input Select for T4EUD                                             */
      __IOM uint16_t IST5IN     : 1;            /*!< [10..10] Input Select for T5IN                                            */
      __IOM uint16_t IST5EUD    : 1;            /*!< [11..11] Input Select for T5EUD                                           */
      __IOM uint16_t IST6IN     : 1;            /*!< [12..12] Input Select for T6IN                                            */
      __IOM uint16_t IST6EUD    : 1;            /*!< [13..13] Input Select for T6EUD                                           */
      __IOM uint16_t ISCAPIN    : 2;            /*!< [15..14] Input Select for CAPIN                                           */
    } bit;
  } PISEL;
  __IM  uint16_t  RESERVED1;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000008) Timer T2 Control Register                                  */

    struct
    {
      __IOM uint16_t T2I        : 3;            /*!< [2..0] Timer T2 Input Parameter Selection                                 */
      __IOM uint16_t T2M        : 3;            /*!< [5..3] Timer T2 Mode Control (Basic Operating Mode)                       */
      __IOM uint16_t T2R        : 1;            /*!< [6..6] Timer T2 Run Bit                                                   */
      __IOM uint16_t T2UD       : 1;            /*!< [7..7] Timer T2 Up/Down Control                                           */
      __IOM uint16_t T2UDE      : 1;            /*!< [8..8] Timer T2 External Up/Down Enable                                   */
      __IOM uint16_t T2RC       : 1;            /*!< [9..9] Timer T2 Remote Control                                            */
      __IM  uint16_t            : 2;
      __IOM uint16_t T2IRDIS    : 1;            /*!< [12..12] Timer T2 Interrupt Disable                                       */
      __IOM uint16_t T2EDGE     : 1;            /*!< [13..13] Timer T2 Edge Detection                                          */
      __IOM uint16_t T2CHDIR    : 1;            /*!< [14..14] Timer T2 Count Direction Change                                  */
      __IM  uint16_t T2RDIR     : 1;            /*!< [15..15] Timer T2 Rotation Direction                                      */
    } bit;
  } T2CON;
  __IM  uint16_t  RESERVED2;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x0000000C) Timer T3 Control Register                                  */

    struct
    {
      __IOM uint16_t T3I        : 3;            /*!< [2..0] Timer T3 Input Parameter Selection                                 */
      __IOM uint16_t T3M        : 3;            /*!< [5..3] Timer T3 Mode Control                                              */
      __IOM uint16_t T3R        : 1;            /*!< [6..6] Timer T3 Run Bit                                                   */
      __IOM uint16_t T3UD       : 1;            /*!< [7..7] Timer T3 Up/Down Control                                           */
      __IOM uint16_t T3UDE      : 1;            /*!< [8..8] Timer T3 External Up/Down Enable                                   */
      __IOM uint16_t T3OE       : 1;            /*!< [9..9] Overflow/Underflow Output Enable                                   */
      __IOM uint16_t T3OTL      : 1;            /*!< [10..10] Timer T3 Overflow Toggle Latch                                   */
      __IOM uint16_t BPS1       : 2;            /*!< [12..11] GPT1 Block Prescaler Control                                     */
      __IOM uint16_t T3EDGE     : 1;            /*!< [13..13] Timer T3 Edge Detection Flag                                     */
      __IOM uint16_t T3CHDIR    : 1;            /*!< [14..14] Timer T3 Count Direction Change Flag                             */
      __IM  uint16_t T3RDIR     : 1;            /*!< [15..15] Timer T3 Rotation Direction Flag                                 */
    } bit;
  } T3CON;
  __IM  uint16_t  RESERVED3;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000010) Timer T4 Control Register                                  */

    struct
    {
      __IOM uint16_t T4I        : 3;            /*!< [2..0] Timer T4 Input Parameter Selection                                 */
      __IOM uint16_t T4M        : 3;            /*!< [5..3] Timer T4 Mode Control (Basic Operating Mode)                       */
      __IOM uint16_t T4R        : 1;            /*!< [6..6] Timer T4 Run Bit                                                   */
      __IOM uint16_t T4UD       : 1;            /*!< [7..7] Timer T4 Up/Down Control                                           */
      __IOM uint16_t T4UDE      : 1;            /*!< [8..8] Timer T4 External Up/Down Enable                                   */
      __IOM uint16_t T4RC       : 1;            /*!< [9..9] Timer T4 Remote Control                                            */
      __IOM uint16_t CLRT2EN    : 1;            /*!< [10..10] Clear Timer T2 Enable                                            */
      __IOM uint16_t CLRT3EN    : 1;            /*!< [11..11] Clear Timer T3 Enable                                            */
      __IOM uint16_t T4IRDIS    : 1;            /*!< [12..12] Timer T4 Interrupt Disable                                       */
      __IOM uint16_t T4EDGE     : 1;            /*!< [13..13] Timer T4 Edge Detection                                          */
      __IOM uint16_t T4CHDIR    : 1;            /*!< [14..14] Timer T4 Count Direction Change                                  */
      __IM  uint16_t T4RDIR     : 1;            /*!< [15..15] Timer T4 Rotation Direction                                      */
    } bit;
  } T4CON;
  __IM  uint16_t  RESERVED4;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000014) Timer 5 Control Register                                   */

    struct
    {
      __IOM uint16_t T5I        : 3;            /*!< [2..0] Timer T5 Input Parameter Selection                                 */
      __IOM uint16_t T5M        : 2;            /*!< [4..3] Timer T5 Mode Control (Basic Operating Mode)                       */
      __IM  uint16_t            : 1;
      __IOM uint16_t T5R        : 1;            /*!< [6..6] Timer T5 Run Bit                                                   */
      __IOM uint16_t T5UD       : 1;            /*!< [7..7] Timer T5 Up/Down Control                                           */
      __IOM uint16_t T5UDE      : 1;            /*!< [8..8] Timer T5 External Up/Down Enable                                   */
      __IOM uint16_t T5RC       : 1;            /*!< [9..9] Timer T5 Remote Control                                            */
      __IOM uint16_t CT3        : 1;            /*!< [10..10] Timer T3 Capture Trigger Enable                                  */
      __IM  uint16_t            : 1;
      __IOM uint16_t CI         : 2;            /*!< [13..12] Register CAPREL Capture Trigger Selection                        */
      __IOM uint16_t T5CLR      : 1;            /*!< [14..14] Timer T5 Clear Enable Bit                                        */
      __IOM uint16_t T5SC       : 1;            /*!< [15..15] Timer T5 Capture Mode Enable                                     */
    } bit;
  } T5CON;
  __IM  uint16_t  RESERVED5;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000018) Timer T6 Control Register                                  */

    struct
    {
      __IOM uint16_t T6I        : 3;            /*!< [2..0] Timer T6 Input Parameter Selection                                 */
      __IOM uint16_t T6M        : 3;            /*!< [5..3] Timer T6 Mode Control (Basic Operating Mode)                       */
      __IOM uint16_t T6R        : 1;            /*!< [6..6] Timer T6 Run Bit                                                   */
      __IOM uint16_t T6UD       : 1;            /*!< [7..7] Timer T6 Up/Down Control                                           */
      __IOM uint16_t T6UDE      : 1;            /*!< [8..8] Timer T6 External Up/Down Enable                                   */
      __IOM uint16_t T6OE       : 1;            /*!< [9..9] Overflow/Underflow Output Enable                                   */
      __IOM uint16_t T6OTL      : 1;            /*!< [10..10] Timer T6 Overflow Toggle Latch                                   */
      __IOM uint16_t BPS2       : 2;            /*!< [12..11] GPT2 Block Prescaler Control                                     */
      __IM  uint16_t            : 1;
      __IOM uint16_t T6CLR      : 1;            /*!< [14..14] Timer T6 Clear Enable Bit                                        */
      __IOM uint16_t T6SR       : 1;            /*!< [15..15] Timer T6 Reload Mode Enable                                      */
    } bit;
  } T6CON;
  __IM  uint16_t  RESERVED6;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x0000001C) Capture/Reload Register                                    */

    struct
    {
      __IOM uint16_t CAPREL     : 16;           /*!< [15..0] Current reload value or Captured value                            */
    } bit;
  } CAPREL;
  __IM  uint16_t  RESERVED7;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000020) Timer T2 Count Register                                    */

    struct
    {
      __IOM uint16_t T2         : 16;           /*!< [15..0] Timer T2 Current Value                                            */
    } bit;
  } T2;
  __IM  uint16_t  RESERVED8;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000024) Timer T3 Count Register                                    */

    struct
    {
      __IOM uint16_t T3         : 16;           /*!< [15..0] Timer T3 Current Value                                            */
    } bit;
  } T3;
  __IM  uint16_t  RESERVED9;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000028) Timer T4 Count Register                                    */

    struct
    {
      __IOM uint16_t T4         : 16;           /*!< [15..0] Timer T4 Current Value                                            */
    } bit;
  } T4;
  __IM  uint16_t  RESERVED10;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x0000002C) Timer 5 Count Register                                     */

    struct
    {
      __IOM uint16_t T5         : 16;           /*!< [15..0] Timer T5 Current Value                                            */
    } bit;
  } T5;
  __IM  uint16_t  RESERVED11;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000030) Timer T6 Count Register                                    */

    struct
    {
      __IOM uint16_t T6         : 16;           /*!< [15..0] Timer T6 Current Value                                            */
    } bit;
  } T6;
} GPT12E_Type;                                  /*!< Size = 50 (0x32)                                                          */



/* =========================================================================================================================== */
/* ================                                            LIN                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief Local Interconnect Network (LIN)
  */

typedef struct                                  /*!< (@ 0x4801E000) LIN Structure                                              */
{

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) LIN Transceiver Control and Status                         */

    struct
    {
      __IM  uint32_t            : 1;
      __IOM uint32_t MODE       : 2;            /*!< [2..1] LIN transceiver power mode control                                 */
      __IM  uint32_t M_SM_ERR   : 1;            /*!< [3..3] LIN Transceiver Mode or Slope Mode Error                           */
      __IM  uint32_t OT_STS     : 1;            /*!< [4..4] LIN Receiver Overtemperature Status                                */
      __IM  uint32_t OC_STS     : 1;            /*!< [5..5] LIN Receiver Overcurrent Status                                    */
      __IM  uint32_t TXD_TMOUT_STS : 1;         /*!< [6..6] LIN TXD time-out status                                            */
      __IM  uint32_t            : 2;
      __IOM uint32_t TXD        : 1;            /*!< [9..9] LIN Transmitter switch on (only used when LIN_HV_MODE
                                                     is set)                                                                   */
      __IM  uint32_t RXD        : 1;            /*!< [10..10] Output Signal of Receiver                                        */
      __IOM uint32_t SM         : 2;            /*!< [12..11] LIN Transmitter Slope mode control                               */
      __IM  uint32_t FB_SM1     : 1;            /*!< [13..13] Feedback Signal 1 for Slope Mode Setting                         */
      __IM  uint32_t FB_SM2     : 1;            /*!< [14..14] Feedback Signal 2 for Slope Mode Setting                         */
      __IM  uint32_t FB_SM3     : 1;            /*!< [15..15] Feedback Signal 3 for Slope Mode Setting                         */
      __IM  uint32_t MODE_FB    : 3;            /*!< [18..16] Feedback Signals for LIN Transmitter Mode Settings               */
      __IM  uint32_t            : 2;
      __IOM uint32_t HV_MODE    : 1;            /*!< [21..21] LIN Transceiver High Voltage Input - Output Mode                 */
      __IM  uint32_t            : 2;
      __IOM uint32_t M_SM_ERR_CLR : 1;          /*!< [24..24] LIN Transceiver Mode or Slope Mode Error Clear                   */
    } bit;
  } CTRL_STS;
} LIN_Type;                                     /*!< Size = 4 (0x4)                                                            */



/* =========================================================================================================================== */
/* ================                                            MF                                             ================ */
/* =========================================================================================================================== */


/**
  * @brief Measurement Function (MF)
  */

typedef struct                                  /*!< (@ 0x48018000) MF Structure                                               */
{

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) Port 2 ADC Selection Control Register                      */

    struct
    {
      __IOM uint32_t P2_0_ADC_SEL : 1;          /*!< [0..0] Port 2.0 Input Selection                                           */
      __IOM uint32_t P2_2_ADC_SEL : 1;          /*!< [1..1] Port 2.2 Input Selection                                           */
      __IOM uint32_t P2_3_ADC_SEL : 1;          /*!< [2..2] Port 2.3 Input Selection                                           */
      __IOM uint32_t P2_4_ADC_SEL : 1;          /*!< [3..3] Port 2.4 Input Selection                                           */
      __IOM uint32_t P2_5_ADC_SEL : 1;          /*!< [4..4] Port 2.5 Input Selection                                           */
      __IM  uint32_t            : 3;
      __IOM uint32_t ADC3_INP_SEL : 1;          /*!< [8..8] ADC3 Positive Input Selection                                      */
      __IOM uint32_t ADC3_INN_SEL : 1;          /*!< [9..9] ADC3 Negative Input Selection                                      */
      __IOM uint32_t ADC1_CH1_SEL : 1;          /*!< [10..10] ADC1 Channel 1 Input Selection                                   */
    } bit;
  } P2_ADCSEL_CTRL;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) Supply Sense Control Register                              */

    struct
    {
      __IOM uint32_t VMON_SEN_PD_N : 1;         /*!< [0..0] Monitoring Input Attenuator enable                                 */
      __IM  uint32_t            : 3;
      __IOM uint32_t VMON_SEN_HRESO_5V : 1;     /*!< [4..4] Monitoring Input Attenuator High Impedance Output Control          */
      __IOM uint32_t VMON_SEN_SEL_INRANGE : 1;  /*!< [5..5] Monitoring Input Attenuator Select Inputrange                      */
    } bit;
  } VMON_SEN_CTRL;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) BEMF Comparator Control Status Register                    */

    struct
    {
      __IOM uint32_t PHUCOMP_EN : 1;            /*!< [0..0] Phase U Comparator enable                                          */
      __IOM uint32_t PHVCOMP_EN : 1;            /*!< [1..1] Phase V Comparator enable                                          */
      __IOM uint32_t PHWCOMP_EN : 1;            /*!< [2..2] Phase W Comparator enable                                          */
      __IOM uint32_t DEMGFILTDIS : 1;           /*!< [3..3] BEMF Comparator Demagnetisation (Demag) Filter Disable             */
      __IOM uint32_t FILTBYPS   : 1;            /*!< [4..4] BEMF Comparator Output Filter Bypass                               */
      __IOM uint32_t GPT12CAPINSW : 1;          /*!< [5..5] GPT12 CAPIN software trigger                                       */
      __IM  uint32_t            : 2;
      __IOM uint32_t PHUCOMP_ON : 1;            /*!< [8..8] Phase U Comparator on                                              */
      __IOM uint32_t PHVCOMP_ON : 1;            /*!< [9..9] Phase V Comparator on                                              */
      __IOM uint32_t PHWCOMP_ON : 1;            /*!< [10..10] Phase W Comparator on                                            */
      __IM  uint32_t            : 1;
      __IOM uint32_t CCPOS_INSEL : 1;           /*!< [12..12] CCPOSx_3 INSEL select, x = 0,1,2                                 */
      __IM  uint32_t            : 3;
      __IM  uint32_t PHU_ZC_STS : 1;            /*!< [16..16] Phase U Comparator zero crossing status                          */
      __IM  uint32_t PHV_ZC_STS : 1;            /*!< [17..17] Phase V Comparator zero crossing status                          */
      __IM  uint32_t PHW_ZC_STS : 1;            /*!< [18..18] Phase W Comparator zero crossing status                          */
    } bit;
  } BEMFC_CTRL_STS;
  __IM  uint32_t  RESERVED0;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) Temperature Sensor Control Register                        */

    struct
    {
      __IM  uint32_t            : 4;
      __IM  uint32_t PMU_OTWARN_STS : 1;        /*!< [4..4] PMU Regulator Overtemperature Warning (MU) Status                  */
      __IM  uint32_t PMU_OT_STS : 1;            /*!< [5..5] PMU Regulator Overtemperature (MU) Status                          */
      __IM  uint32_t SYS_OTWARN_STS : 1;        /*!< [6..6] System Overtemperature Warning (MU) Status                         */
      __IM  uint32_t SYS_OT_STS : 1;            /*!< [7..7] System Overtemperature (MU) Status                                 */
    } bit;
  } TEMPSENSE_CTRL;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000014) Reference 1 Status Register                                */

    struct
    {
      __IM  uint32_t            : 4;
      __IM  uint32_t REFBG_LOTHWARN_STS : 1;    /*!< [4..4] Status for Undervoltage Threshold Measurement of internal
                                                     VAREF                                                                     */
      __IM  uint32_t REFBG_UPTHWARN_STS : 1;    /*!< [5..5] Status for Overvoltage Threshold Measurement of internal
                                                     VAREF                                                                     */
    } bit;
  } REF1_STS;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000018) Reference 2 Control Register                               */

    struct
    {
      __IOM uint32_t VREF5V_PD_N : 1;           /*!< [0..0] ADC1 Bit Reference Voltage Generation Power Down Bit               */
      __IM  uint32_t VREF5V_OVL_STS : 1;        /*!< [1..1] ADC1 Bit Reference Voltage Generation Over Load Bit                */
      __IM  uint32_t VREF5V_UV_STS : 1;         /*!< [2..2] ADC1 Bit Reference Voltage Generation Undervoltage Bit             */
      __IM  uint32_t VREF5V_OV_STS : 1;         /*!< [3..3] ADC1 Bit Reference Voltage Generation Overvoltage Bit              */
    } bit;
  } REF2_CTRL;
  __IM  uint32_t  RESERVED1;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000020) Trimming of Driver                                         */

    struct
    {
      __IOM uint32_t BEMF_BT_TFILT_SEL : 3;     /*!< [2..0] Blanking Time for BEMF Comparator Output Signal                    */
      __IM  uint32_t            : 1;
      __IOM uint32_t BEMF_GPT_CAPIN_SEL : 2;    /*!< [5..4] GPT12 CAPIN input selector                                         */
      __IM  uint32_t            : 2;
      __IOM uint32_t BEMF_TFILT_SEL : 2;        /*!< [9..8] Filter Time for BEMF Comparator Output Signal                      */
    } bit;
  } TRIM_BEMFx;
} MF_Type;                                      /*!< Size = 36 (0x24)                                                          */


/* =========================================================================================================================== */
/* ================                                            MON                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief MON (MON)
  */

typedef struct                                      /*!< (@ 0x50004000) MON Structure                                          */
{
  __I  uint32_t  RESERVED0[13];

  union
  {
    __IO uint8_t   reg;                             /*!< (@ 0x50004034) Settings Monitor 1                                     */

    struct
    {
      __IO uint8_t   EN         :  1;               /*!< [0..0] MON Enable                                                     */
      __IO uint8_t   FALL       :  1;               /*!< [1..1] MON Wake-up on Falling Edge Enable                             */
      __IO uint8_t   RISE       :  1;               /*!< [2..2] MON Wake-up on Rising Edge Enable                              */
      __IO uint8_t   CYC        :  1;               /*!< [3..3] MON for Cycle Sense Enable                                     */
      __IO uint8_t   PD         :  1;               /*!< [4..4] Pull-Down Current Source for MON Input Enable                  */
      __IO uint8_t   PU         :  1;               /*!< [5..5] Pull-Up Current Source for MON Input Enable                    */
      uint8_t              :  1;
      __I  uint8_t   STS        :  1;               /*!< [7..7] MON Status Input                                               */
    } bit;                                          /*!< [8] BitSize                                                           */
  } CNF;
} MON_Type;


/* =========================================================================================================================== */
/* ================                                            PMU                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief Power Management Unit (PMU)
  */

typedef struct                                  /*!< (@ 0x50004000) PMU Structure                                              */
{

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000000) Main wake status register                                  */

    struct
    {
      __IM  uint8_t LIN_WAKE    : 1;            /*!< [0..0] Wake-up via LIN- Message                                           */
      __IM  uint8_t MON_WAKE    : 1;            /*!< [1..1] Wake-up via MON                                                    */
      __IM  uint8_t GPIO0       : 1;            /*!< [2..2] Wake-up via GPIO0 which is a logical OR combination of
                                                     all Wake_STS_GPIO0 bits                                                   */
      __IM  uint8_t GPIO1       : 1;            /*!< [3..3] Wake-up via GPIO1 which is a logical OR combination of
                                                     all Wake_STS_GPIO1 bits                                                   */
      __IM  uint8_t CYC_WAKE    : 1;            /*!< [4..4] Wake-up caused by Cyclic Wake                                      */
      __IM  uint8_t FAIL        : 1;            /*!< [5..5] Wake-up after VDDEXT Fail                                          */
    } bit;
  } WAKE_STATUS;
  __IM  uint8_t   RESERVED[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000004) Voltage Reg Status Register                                */

    struct
    {
      __IM  uint8_t PMU_1V5_OVERVOLT : 1;       /*!< [0..0] Overvoltage at VDDC regulator                                      */
      __IM  uint8_t PMU_1V5_OVERLOAD : 1;       /*!< [1..1] Overload at VDDC regulator                                         */
      __IOM uint8_t PMU_1V5_FAIL_EN : 1;        /*!< [2..2] Enabling of VDDC status information as interrupt source            */
      __IM  uint8_t             : 1;
      __IM  uint8_t PMU_5V_OVERVOLT : 1;        /*!< [4..4] Overvoltage at VDDP regulator                                      */
      __IM  uint8_t PMU_5V_OVERLOAD : 1;        /*!< [5..5] Overload at VDDP regulator                                         */
      __IOM uint8_t PMU_5V_FAIL_EN : 1;         /*!< [6..6] Enabling of VDDP status information as interrupt source            */
    } bit;
  } PMU_SUPPLY_STS;
  __IM  uint8_t   RESERVED1[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000008) VDDEXT Control                                             */

    struct
    {
      __IOM uint8_t ENABLE      : 1;            /*!< [0..0] VDDEXT Supply Enable                                               */
      __IOM uint8_t CYC_EN      : 1;            /*!< [1..1] VDDEXT Supply for Cyclic Sense Enable                              */
      __IOM uint8_t FAIL_EN     : 1;            /*!< [2..2] Enabling of VDDEXT Supply status information as interrupt
                                                     source                                                                    */
      __IOM uint8_t SHORT       : 1;            /*!< [3..3] VDDEXT Supply Shorted Output                                       */
      __IOM uint8_t OVERVOLT    : 1;            /*!< [4..4] VDDEXT Supply Overvoltage                                          */
      __IOM uint8_t OVERLOAD    : 1;            /*!< [5..5] VDDEXT Supply Overload                                             */
      __IM  uint8_t OK          : 1;            /*!< [6..6] VDDEXT Supply works inside its specified range 2                   */
      __IM  uint8_t STABLE      : 1;            /*!< [7..7] VDDEXT Supply works inside its specified range 1                   */
    } bit;
  } VDDEXT_CTRL;
  __IM  uint8_t   RESERVED2[7];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000010) Reset Status Hard Register                                 */

    struct
    {
      __IOM uint8_t SYS_FAIL    : 1;            /*!< [0..0] Flag which indicates a reset caused by a System Fail
                                                     reported in the corresponding Fail Register                               */
      __IOM uint8_t PMU_WAKE    : 1;            /*!< [1..1] Flag which indicates a reset caused by Stop-Exit                   */
      __IOM uint8_t PMU_SleepEX : 1;            /*!< [2..2] Flag which indicates a reset caused by Sleep-Exit                  */
      __IOM uint8_t PMU_LPR     : 1;            /*!< [3..3] Low Priority Resets (see PMU_RESET_STS2)                           */
      __IOM uint8_t PMU_ClkWDT  : 1;            /*!< [4..4] Clock Watchdog (CLKWDT) Reset Flag                                 */
      __IOM uint8_t PMU_ExtWDT  : 1;            /*!< [5..5] External Watchdog (WDT1) Reset Flag                                */
      __IOM uint8_t PMU_PIN     : 1;            /*!< [6..6] PIN-Reset Flag                                                     */
      __IOM uint8_t PMU_1V5DidPOR : 1;          /*!< [7..7] Power-On Reset Flag                                                */
    } bit;
  } PMU_RESET_STS1;
  __IM  uint8_t   RESERVED3[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000014) Reset Status Soft Register                                 */

    struct
    {
      __IOM uint8_t PMU_IntWDT  : 1;            /*!< [0..0] Internal Watchdog Reset Flag                                       */
      __IOM uint8_t PMU_SOFT    : 1;            /*!< [1..1] Soft-Reset Flag                                                    */
      __IOM uint8_t LOCKUP      : 1;            /*!< [2..2] Lockup-Reset Flag                                                  */
    } bit;
  } PMU_RESET_STS2;
  __IM  uint8_t   RESERVED4[11];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000020) PMU Settings Register                                      */

    struct
    {
      __IOM uint8_t WAKE_W_RST  : 1;            /*!< [0..0] Wake-up with reset execution                                       */
      __IOM uint8_t EN_0V9_N    : 1;            /*!< [1..1] Disables the reduction of the VDDC regulator output to
                                                     0.9 V during Stop-Mode                                                    */
      __IOM uint8_t CYC_WAKE_EN : 1;            /*!< [2..2] Enabling Cyclic Wake                                               */
      __IOM uint8_t CYC_SENSE_EN : 1;           /*!< [3..3] Enabling Cyclic Sense                                              */
      __IM  uint8_t             : 3;
      __IOM uint8_t EN_VDDEXT_OC_OFF_N : 1;     /*!< [7..7] Disabling VDDEXT Shutdown in Overload Condition                    */
    } bit;
  } CNF_PMU_SETTINGS;
  __IM  uint8_t   RESERVED5[7];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000028) Dead Time in Cyclic Sense Register                         */

    struct
    {
      __IOM uint8_t M03         : 4;            /*!< [3..0] Mantissa                                                           */
      __IOM uint8_t E01         : 2;            /*!< [5..4] Exponent                                                           */
      __IM  uint8_t             : 1;
      __IOM uint8_t OSC_100kHz_EN : 1;          /*!< [7..7] 100 kHz Oscillator Enable                                          */
    } bit;
  } CNF_CYC_SENSE;
  __IM  uint8_t   RESERVED6[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x0000002C) Dead Time in Cyclic Wake Register                          */

    struct
    {
      __IOM uint8_t M03         : 4;            /*!< [3..0] Mantissa                                                           */
      __IOM uint8_t E01         : 2;            /*!< [5..4] Exponent                                                           */
    } bit;
  } CNF_CYC_WAKE;
  __IM  uint8_t   RESERVED7[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000030) Sample Delay in Cyclic Sense Register                      */

    struct
    {
      __IOM uint8_t M03         : 4;            /*!< [3..0] Mantissa                                                           */
    } bit;
  } CNF_CYC_SAMPLE_DEL;
  __IM  uint8_t   RESERVED9[31];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000050) LIN Wake Enable                                            */

    struct
    {
      __IM  uint8_t             : 7;
      __IOM uint8_t LIN_EN      : 1;            /*!< [7..7] Lin Wake enable                                                    */
    } bit;
  } LIN_WAKE_EN;
  __IM  uint8_t   RESERVED10[27];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x0000006C) Reset Blind Time Register                                  */

    struct
    {
      __IOM uint8_t RST_TFB     : 2;            /*!< [1..0] Reset Pin Blind Time Selection Bits                                */
    } bit;
  } CNF_RST_TFB;
  __IM  uint8_t   RESERVED11[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000070) System Fail Status Register                                */

    struct
    {
      __IOM uint8_t SUPP_SHORT  : 1;            /*!< [0..0] Supply Short                                                       */
      __IOM uint8_t SUPP_TMOUT  : 1;            /*!< [1..1] Supply Time Out                                                    */
      __IOM uint8_t PMU_1V5_OVL : 1;            /*!< [2..2] VDDC Overload Flag                                                 */
      __IOM uint8_t PMU_5V_OVL  : 1;            /*!< [3..3] VDDP Overload Flag                                                 */
      __IM  uint8_t             : 1;
      __IOM uint8_t SYS_OT      : 1;            /*!< [5..5] System Overtemperature Indication Flag                             */
      __IOM uint8_t WDT1_SEQ_FAIL : 1;          /*!< [6..6] External Watchdog (WDT1) Sequential Fail                           */
    } bit;
  } SYS_FAIL_STS;
  __IM  uint8_t   RESERVED12[15];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000080) Wake Status Fail Register                                  */

    struct
    {
      __IOM uint8_t SUPPFAIL    : 1;            /*!< [0..0] Stop-Exit due to overvoltage at the VDDEXT Supply                  */
      __IM  uint8_t             : 1;
      __IOM uint8_t VDDEXTSHORT : 1;            /*!< [2..2] Stop-Exit due to short circuit at the VDDEXT Supply                */
    } bit;
  } WAKE_STS_FAIL;
  __IM  uint8_t   RESERVED13[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000084) Wake Source MON Input Register                             */

    struct
    {
      __IM  uint8_t WAKE_STS    : 1;            /*!< [0..0] Status of MON                                                      */
    } bit;
  } WAKE_STS_MON;
  __IM  uint8_t   RESERVED14[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000088) Wake Status GPIO 0 Register                                */

    struct
    {
      __IM  uint8_t GPIO0_STS_0 : 1;            /*!< [0..0] Status of GPIO0_0                                                  */
      __IM  uint8_t GPIO0_STS_1 : 1;            /*!< [1..1] Status of GPIO0_1                                                  */
      __IM  uint8_t GPIO0_STS_2 : 1;            /*!< [2..2] Status of GPIO0_2                                                  */
      __IM  uint8_t GPIO0_STS_3 : 1;            /*!< [3..3] Status of GPIO0_3                                                  */
      __IM  uint8_t GPIO0_STS_4 : 1;            /*!< [4..4] Status of GPIO0_4                                                  */
    } bit;
  } WAKE_STS_GPIO0;
  __IM  uint8_t   RESERVED15[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x0000008C) Wake Status GPIO 1 Register                                */

    struct
    {
      __IM  uint8_t GPIO1_STS_0 : 1;            /*!< [0..0] Wake GPIO1_0                                                       */
      __IM  uint8_t GPIO1_STS_1 : 1;            /*!< [1..1] Wake GPIO1_1                                                       */
      __IM  uint8_t GPIO1_STS_2 : 1;            /*!< [2..2] Wake GPIO1_2                                                       */
      __IM  uint8_t GPIO1_STS_3 : 1;            /*!< [3..3] Wake GPIO1_3                                                       */
      __IM  uint8_t GPIO1_STS_4 : 1;            /*!< [4..4] Wake GPIO1_4                                                       */
    } bit;
  } WAKE_STS_GPIO1;
  __IM  uint8_t   RESERVED16[31];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x000000AC) PMU Wake-up Timing Register                                */

    struct
    {
      __IOM uint8_t CNF_LIN_FT  : 1;            /*!< [0..0] Wake-up Filter time for LIN WAKE                                   */
      __IOM uint8_t CNF_MON_FT  : 1;            /*!< [1..1] Wake-up Filter time for Monitoring Inputs                          */
      __IOM uint8_t CNF_GPIO_FT : 2;            /*!< [3..2] Wake-up Filter time for General Purpose IO                         */
    } bit;
  } CNF_WAKE_FILTER;
  __IM  uint8_t   RESERVED17[19];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x000000C0) General Purpose User DATA0                                 */

    struct
    {
      __IOM uint8_t DATA0       : 8;            /*!< [7..0] DATA0 Storage Byte                                                 */
    } bit;
  } GPUDATA00;
  __IM  uint8_t   RESERVED18[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x000000C4) General Purpose User DATA1                                 */

    struct
    {
      __IOM uint8_t DATA1       : 8;            /*!< [7..0] DATA1 Storage Byte                                                 */
    } bit;
  } GPUDATA01;
  __IM  uint8_t   RESERVED19[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x000000C8) General Purpose User DATA2                                 */

    struct
    {
      __IOM uint8_t DATA2       : 8;            /*!< [7..0] DATA2 Storage Byte                                                 */
    } bit;
  } GPUDATA02;
  __IM  uint8_t   RESERVED20[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x000000CC) General Purpose User DATA3                                 */

    struct
    {
      __IOM uint8_t DATA3       : 8;            /*!< [7..0] DATA3 Storage Byte                                                 */
    } bit;
  } GPUDATA03;
  __IM  uint8_t   RESERVED21[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x000000D0) General Purpose User DATA4                                 */

    struct
    {
      __IOM uint8_t DATA4       : 8;            /*!< [7..0] DATA4 Storage Byte                                                 */
    } bit;
  } GPUDATA04;
  __IM  uint8_t   RESERVED22[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x000000D4) General Purpose User DATA5                                 */

    struct
    {
      __IOM uint8_t DATA5       : 8;            /*!< [7..0] DATA5 Storage Byte                                                 */
    } bit;
  } GPUDATA05;
  __IM  uint8_t   RESERVED23[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x000000D8) Wake Configuration GPIO Port 0 Rising Edge Register        */

    struct
    {
      __IOM uint8_t GPIO0_RI_0  : 1;            /*!< [0..0] Port 0_0 Wake-up on Rising Edge enable                             */
      __IOM uint8_t GPIO0_RI_1  : 1;            /*!< [1..1] Port 0_1 Wake-up on Rising Edge enable                             */
      __IOM uint8_t GPIO0_RI_2  : 1;            /*!< [2..2] Port 0_2 Wake-up on Rising Edge enable                             */
      __IOM uint8_t GPIO0_RI_3  : 1;            /*!< [3..3] Port 0_3 Wake-up on Rising Edge enable                             */
      __IOM uint8_t GPIO0_RI_4  : 1;            /*!< [4..4] Port 0_4 Wake-up on Rising Edge enable                             */
    } bit;
  } WAKE_CONF_GPIO0_RISE;
  __IM  uint8_t   RESERVED24[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x000000DC) Wake Configuration GPIO Port 0 Falling Edge Register       */

    struct
    {
      __IOM uint8_t GPIO0_FA_0  : 1;            /*!< [0..0] Port 0_0 Wake-up on Falling Edge enable                            */
      __IOM uint8_t GPIO0_FA_1  : 1;            /*!< [1..1] Port 0_1 Wake-up on Falling Edge enable                            */
      __IOM uint8_t GPIO0_FA_2  : 1;            /*!< [2..2] Port 0_2 Wake-up on Falling Edge enable                            */
      __IOM uint8_t GPIO0_FA_3  : 1;            /*!< [3..3] Port 0_3 Wake-up on Falling Edge enable                            */
      __IOM uint8_t GPIO0_FA_4  : 1;            /*!< [4..4] Port 0_4 Wake-up on Falling Edge enable                            */
    } bit;
  } WAKE_CONF_GPIO0_FALL;
  __IM  uint8_t   RESERVED25[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x000000E0) Wake Port 0 Cycle Enabled Register                         */

    struct
    {
      __IOM uint8_t GPIO0_CYC_0 : 1;            /*!< [0..0] GPIO0_0 input for cycle sense enable                               */
      __IOM uint8_t GPIO0_CYC_1 : 1;            /*!< [1..1] GPIO0_1 input for cycle sense enable                               */
      __IOM uint8_t GPIO0_CYC_2 : 1;            /*!< [2..2] GPIO0_2 input for cycle sense enable                               */
      __IOM uint8_t GPIO0_CYC_3 : 1;            /*!< [3..3] GPIO0_3 input for cycle sense enable                               */
      __IOM uint8_t GPIO0_CYC_4 : 1;            /*!< [4..4] GPIO0_4 input for cycle sense enable                               */
    } bit;
  } WAKE_CONF_GPIO0_CYC;
  __IM  uint8_t   RESERVED26[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x000000E4) Wake Configuration GPIO Port 1 Rising Edge Register        */

    struct
    {
      __IOM uint8_t GPIO1_RI_0  : 1;            /*!< [0..0] Port 1_0 Wake-up on Rising Edge enable                             */
      __IOM uint8_t GPIO1_RI_1  : 1;            /*!< [1..1] Port 1_1 Wake-up on Rising Edge enable                             */
      __IOM uint8_t GPIO1_RI_2  : 1;            /*!< [2..2] Port 1_2 Wake-up on Rising Edge enable                             */
      __IOM uint8_t GPIO1_RI_3  : 1;            /*!< [3..3] Port 1_3 Wake-up on Rising Edge enable                             */
      __IOM uint8_t GPIO1_RI_4  : 1;            /*!< [4..4] Port 1_4 Wake-up on Rising Edge enable                             */
    } bit;
  } WAKE_CONF_GPIO1_RISE;
  __IM  uint8_t   RESERVED27[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x000000E8) Wake Configuration GPIO Port 1 Falling Edge Register       */

    struct
    {
      __IOM uint8_t GPIO1_FA_0  : 1;            /*!< [0..0] Port 1_0 Wake-up on Falling Edge enable                            */
      __IOM uint8_t GPIO1_FA_1  : 1;            /*!< [1..1] Port 1_1 Wake-up on Falling Edge enable                            */
      __IOM uint8_t GPIO1_FA_2  : 1;            /*!< [2..2] Port 1_2 Wake-up on Falling Edge enable                            */
      __IOM uint8_t GPIO1_FA_3  : 1;            /*!< [3..3] Port 1_3 Wake-up on Falling Edge enable                            */
      __IOM uint8_t GPIO1_FA_4  : 1;            /*!< [4..4] Port 1_4 Wake-up on Falling Edge enable                            */
    } bit;
  } WAKE_CONF_GPIO1_FALL;
  __IM  uint8_t   RESERVED28[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x000000EC) Wake Port 1 Cycle Enabled Register                         */

    struct
    {
      __IOM uint8_t GPIO1_CYC_0 : 1;            /*!< [0..0] GPIO1_0 input for cycle sense enable                               */
      __IOM uint8_t GPIO1_CYC_1 : 1;            /*!< [1..1] GPIO1_1 input for cycle sense enable                               */
      __IOM uint8_t GPIO1_CYC_2 : 1;            /*!< [2..2] GPIO1_2 input for cycle sense enable                               */
      __IOM uint8_t GPIO1_CYC_3 : 1;            /*!< [3..3] GPIO1_3 input for cycle sense enable                               */
      __IOM uint8_t GPIO1_CYC_4 : 1;            /*!< [4..4] GPIO1_4 input for cycle sense enable                               */
    } bit;
  } WAKE_CONF_GPIO1_CYC;
  __IM  uint8_t   RESERVED29[487];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x000002D4) System Startup Config                                      */

    struct
    {
      __IOM uint8_t MBIST_EN    : 1;            /*!< [0..0] System Startup Configuration Bit for RAM MBIST at Sleep
                                                     Mode exit                                                                 */
    } bit;
  } SystemStartConfig;
} PMU_Type;                                     /*!< Size = 725 (0x2d5)                                                        */



/* =========================================================================================================================== */
/* ================                                           PORT                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief GPIO PORTs (PORT)
  */

typedef struct                                  /*!< (@ 0x48028000) PORT Structure                                             */
{

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000000) Port 0 Data Register                                       */

    struct
    {
      __IOM uint8_t P0          : 1;            /*!< [0..0] Port 0 Pin 0 Data Value                                            */
      __IOM uint8_t P1          : 1;            /*!< [1..1] Port 0 Pin 1 Data Value                                            */
      __IOM uint8_t P2          : 1;            /*!< [2..2] Port 0 Pin 2 Data Value                                            */
      __IOM uint8_t P3          : 1;            /*!< [3..3] Port 0 Pin 3 Data Value                                            */
      __IOM uint8_t P4          : 1;            /*!< [4..4] Port 0 Pin 4 Data Value                                            */
    } bit;
  } P0_DATA;
  __IM  uint8_t   RESERVED[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000004) Port 0 Direction Register                                  */

    struct
    {
      __IOM uint8_t P0          : 1;            /*!< [0..0] Port 0 Pin 0 Direction Control                                     */
      __IOM uint8_t P1          : 1;            /*!< [1..1] Port 0 Pin 1 Direction Control                                     */
      __IOM uint8_t P2          : 1;            /*!< [2..2] Port 0 Pin 2 Direction Control                                     */
      __IOM uint8_t P3          : 1;            /*!< [3..3] Port 0 Pin 3 Direction Control                                     */
      __IOM uint8_t P4          : 1;            /*!< [4..4] Port 0 Pin 4 Direction Control                                     */
    } bit;
  } P0_DIR;
  __IM  uint8_t   RESERVED1[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000008) Port 1 Data Register                                       */

    struct
    {
      __IOM uint8_t P0          : 1;            /*!< [0..0] Port 1 Pin 0 Data Value                                            */
      __IOM uint8_t P1          : 1;            /*!< [1..1] Port 1 Pin 1 Data Value                                            */
      __IOM uint8_t P2          : 1;            /*!< [2..2] Port 1 Pin 2 Data Value                                            */
      __IOM uint8_t P3          : 1;            /*!< [3..3] Port 1 Pin 3 Data Value                                            */
      __IOM uint8_t P4          : 1;            /*!< [4..4] Port 1 Pin 4 Data Value                                            */
    } bit;
  } P1_DATA;
  __IM  uint8_t   RESERVED2[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x0000000C) Port 1 Direction Register                                  */

    struct
    {
      __IOM uint8_t P0          : 1;            /*!< [0..0] Port 1 Pin 0 Direction Control                                     */
      __IOM uint8_t P1          : 1;            /*!< [1..1] Port 1 Pin 1 Direction Control                                     */
      __IOM uint8_t P2          : 1;            /*!< [2..2] Port 1 Pin 2 Direction Control                                     */
      __IOM uint8_t P3          : 1;            /*!< [3..3] Port 1 Pin 3 Direction Control                                     */
      __IOM uint8_t P4          : 1;            /*!< [4..4] Port 1 Pin 4 Direction Control                                     */
    } bit;
  } P1_DIR;
  __IM  uint8_t   RESERVED3[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000010) Port 2 Data Register                                       */

    struct
    {
      __IM  uint8_t P0          : 1;            /*!< [0..0] Port 2 Pin 0 Data Value                                            */
      __IM  uint8_t             : 1;
      __IM  uint8_t P2          : 1;            /*!< [2..2] Port 2 Pin 2 Data Value                                            */
      __IM  uint8_t P3          : 1;            /*!< [3..3] Port 2 Pin 3 Data Value                                            */
      __IM  uint8_t P4          : 1;            /*!< [4..4] Port 2 Pin 4 Data Value                                            */
      __IM  uint8_t P5          : 1;            /*!< [5..5] Port 2 Pin 5 Data Value                                            */
    } bit;
  } P2_DATA;
  __IM  uint8_t   RESERVED4[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000014) Port 2 Direction Register                                  */

    struct
    {
      __IOM uint8_t P0          : 1;            /*!< [0..0] Port 2 Pin 0 Driver Control                                        */
      __IM  uint8_t             : 1;
      __IOM uint8_t P2          : 1;            /*!< [2..2] Port 2 Pin 2 Driver Control                                        */
      __IOM uint8_t P3          : 1;            /*!< [3..3] Port 2 Pin 3 Driver Control                                        */
      __IOM uint8_t P4          : 1;            /*!< [4..4] Port 2 Pin 4 Driver Control                                        */
      __IOM uint8_t P5          : 1;            /*!< [5..5] Port 2 Pin 5 Driver Control                                        */
    } bit;
  } P2_DIR;
  __IM  uint8_t   RESERVED5[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000018) Port 0 Pull-Up/Pull-Down Select Register                   */

    struct
    {
      __IOM uint8_t P0          : 1;            /*!< [0..0] Pull-Up/Pull-Down Select Port 0 Bit 0                              */
      __IOM uint8_t P1          : 1;            /*!< [1..1] Pull-Up/Pull-Down Select Port 0 Bit 1                              */
      __IOM uint8_t P2          : 1;            /*!< [2..2] Pull-Up/Pull-Down Select Port 0 Bit 2                              */
      __IOM uint8_t P3          : 1;            /*!< [3..3] Pull-Up/Pull-Down Select Port 0 Bit 3                              */
      __IOM uint8_t P4          : 1;            /*!< [4..4] Pull-Up/Pull-Down Select Port 0 Bit 4                              */
    } bit;
  } P0_PUDSEL;
  __IM  uint8_t   RESERVED6[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x0000001C) Port 0 Pull-Up/Pull-Down Enable Register                   */

    struct
    {
      __IOM uint8_t P0          : 1;            /*!< [0..0] Pull-Up/Pull-Down Enable at Port 0 Bit 0                           */
      __IOM uint8_t P1          : 1;            /*!< [1..1] Pull-Up/Pull-Down Enable at Port 0 Bit 1                           */
      __IOM uint8_t P2          : 1;            /*!< [2..2] Pull-Up/Pull-Down Enable at Port 0 Bit 2                           */
      __IOM uint8_t P3          : 1;            /*!< [3..3] Pull-Up/Pull-Down Enable at Port 0 Bit 3                           */
      __IOM uint8_t P4          : 1;            /*!< [4..4] Pull-Up/Pull-Down Enable at Port 0 Bit 4                           */
    } bit;
  } P0_PUDEN;
  __IM  uint8_t   RESERVED7[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000020) Port 1 Pull-Up/Pull-Down Select Register                   */

    struct
    {
      __IOM uint8_t P0          : 1;            /*!< [0..0] Pull-Up/Pull-Down Select Port 1 Bit 0                              */
      __IOM uint8_t P1          : 1;            /*!< [1..1] Pull-Up/Pull-Down Select Port 1 Bit 1                              */
      __IOM uint8_t P2          : 1;            /*!< [2..2] Pull-Up/Pull-Down Select Port 1 Bit 2                              */
      __IOM uint8_t P3          : 1;            /*!< [3..3] Pull-Up/Pull-Down Select Port 1 Bit 3                              */
      __IOM uint8_t P4          : 1;            /*!< [4..4] Pull-Up/Pull-Down Select Port 1 Bit 4                              */
    } bit;
  } P1_PUDSEL;
  __IM  uint8_t   RESERVED8[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000024) Port 1 Pull-Up/Pull-Down Enable Register                   */

    struct
    {
      __IOM uint8_t P0          : 1;            /*!< [0..0] Pull-Up/Pull-Down Enable at Port 1 Bit 0                           */
      __IOM uint8_t P1          : 1;            /*!< [1..1] Pull-Up/Pull-Down Enable at Port 1 Bit 1                           */
      __IOM uint8_t P2          : 1;            /*!< [2..2] Pull-Up/Pull-Down Enable at Port 1 Bit 2                           */
      __IOM uint8_t P3          : 1;            /*!< [3..3] Pull-Up/Pull-Down Enable at Port 1 Bit 3                           */
      __IOM uint8_t P4          : 1;            /*!< [4..4] Pull-Up/Pull-Down Enable at Port 1 Bit 4                           */
    } bit;
  } P1_PUDEN;
  __IM  uint8_t   RESERVED9[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000028) Port 2 Pull-Up/Pull-Down Select Register                   */

    struct
    {
      __IOM uint8_t P0          : 1;            /*!< [0..0] Pull-Up/Pull-Down Select Port 2 Bit 0                              */
      __IM  uint8_t             : 1;
      __IOM uint8_t P2          : 1;            /*!< [2..2] Pull-Up/Pull-Down Select Port 2 Bit 2                              */
      __IOM uint8_t P3          : 1;            /*!< [3..3] Pull-Up/Pull-Down Select Port 2 Bit 3                              */
      __IOM uint8_t P4          : 1;            /*!< [4..4] Pull-Up/Pull-Down Select Port 2 Bit 4                              */
      __IOM uint8_t P5          : 1;            /*!< [5..5] Pull-Up/Pull-Down Select Port 2 Bit 5                              */
    } bit;
  } P2_PUDSEL;
  __IM  uint8_t   RESERVED10[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x0000002C) Port 2 Pull-Up/Pull-Down Enable Register                   */

    struct
    {
      __IOM uint8_t P0          : 1;            /*!< [0..0] Pull-Up/Pull-Down Enable at Port 2 Bit 0                           */
      __IM  uint8_t             : 1;
      __IOM uint8_t P2          : 1;            /*!< [2..2] Pull-Up/Pull-Down Enable at Port 2 Bit 2                           */
      __IOM uint8_t P3          : 1;            /*!< [3..3] Pull-Up/Pull-Down Enable at Port 2 Bit 3                           */
      __IOM uint8_t P4          : 1;            /*!< [4..4] Pull-Up/Pull-Down Enable at Port 2 Bit 4                           */
      __IOM uint8_t P5          : 1;            /*!< [5..5] Pull-Up/Pull-Down Enable at Port 2 Bit 5                           */
    } bit;
  } P2_PUDEN;
  __IM  uint8_t   RESERVED11[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000030) Port 0 Alternate Select Register                           */

    struct
    {
      __IOM uint8_t P0          : 1;            /*!< [0..0] Alternate Select Port 0 Bit 0                                      */
      __IOM uint8_t P1          : 1;            /*!< [1..1] Alternate Select Port 0 Bit 1                                      */
      __IOM uint8_t P2          : 1;            /*!< [2..2] Alternate Select Port 0 Bit 2                                      */
      __IOM uint8_t P3          : 1;            /*!< [3..3] Alternate Select Port 0 Bit 3                                      */
      __IOM uint8_t P4          : 1;            /*!< [4..4] Alternate Select Port 0 Bit 4                                      */
    } bit;
  } P0_ALTSEL0;
  __IM  uint8_t   RESERVED12[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000034) Port 0 Alternate Select Register                           */

    struct
    {
      __IOM uint8_t P0          : 1;            /*!< [0..0] Alternate Select Port 0 Bit 0                                      */
      __IOM uint8_t P1          : 1;            /*!< [1..1] Alternate Select Port 0 Bit 1                                      */
      __IOM uint8_t P2          : 1;            /*!< [2..2] Alternate Select Port 0 Bit 2                                      */
      __IOM uint8_t P3          : 1;            /*!< [3..3] Alternate Select Port 0 Bit 3                                      */
      __IOM uint8_t P4          : 1;            /*!< [4..4] Alternate Select Port 0 Bit 4                                      */
    } bit;
  } P0_ALTSEL1;
  __IM  uint8_t   RESERVED13[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000038) Port 1 Alternate Select Register                           */

    struct
    {
      __IOM uint8_t P0          : 1;            /*!< [0..0] Alternate Select Port 1 Bit 0                                      */
      __IOM uint8_t P1          : 1;            /*!< [1..1] Alternate Select Port 1 Bit 1                                      */
      __IOM uint8_t P2          : 1;            /*!< [2..2] Alternate Select Port 1 Bit 2                                      */
      __IOM uint8_t P3          : 1;            /*!< [3..3] Alternate Select Port 1 Bit 3                                      */
      __IOM uint8_t P4          : 1;            /*!< [4..4] Alternate Select Port 1 Bit 4                                      */
    } bit;
  } P1_ALTSEL0;
  __IM  uint8_t   RESERVED14[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x0000003C) Port 1 Alternate Select Register                           */

    struct
    {
      __IOM uint8_t P0          : 1;            /*!< [0..0] Alternate Select Port 1 Bit 0                                      */
      __IOM uint8_t P1          : 1;            /*!< [1..1] Alternate Select Port 1 Bit 1                                      */
      __IOM uint8_t P2          : 1;            /*!< [2..2] Alternate Select Port 1 Bit 2                                      */
      __IOM uint8_t P3          : 1;            /*!< [3..3] Alternate Select Port 1 Bit 3                                      */
      __IOM uint8_t P4          : 1;            /*!< [4..4] Alternate Select Port 1 Bit 4                                      */
    } bit;
  } P1_ALTSEL1;
  __IM  uint8_t   RESERVED15[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000040) Port 0 Open Drain Control Register                         */

    struct
    {
      __IOM uint8_t P0          : 1;            /*!< [0..0] Port 0 Pin 0 Open Drain Mode                                       */
      __IOM uint8_t P1          : 1;            /*!< [1..1] Port 0 Pin 1 Open Drain Mode                                       */
      __IOM uint8_t P2          : 1;            /*!< [2..2] Port 0 Pin 2 Open Drain Mode                                       */
      __IOM uint8_t P3          : 1;            /*!< [3..3] Port 0 Pin 3 Open Drain Mode                                       */
      __IOM uint8_t P4          : 1;            /*!< [4..4] Port 0 Pin 4 Open Drain Mode                                       */
    } bit;
  } P0_OD;
  __IM  uint8_t   RESERVED16[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000044) Port 1 Open Drain Control Register                         */

    struct
    {
      __IM  uint8_t             : 1;
      __IOM uint8_t P0          : 1;            /*!< [1..1] P1.0 Open Drain Mode                                               */
      __IOM uint8_t P1          : 1;            /*!< [2..2] P1.1 Open Drain Mode                                               */
      __IOM uint8_t P3_P2       : 1;            /*!< [3..3] P1.3/P1.2 Open Drain Mode                                          */
      __IOM uint8_t P4          : 1;            /*!< [4..4] P1.4 Open Drain Mode                                               */
    } bit;
  } P1_OD;
} PORT_Type;                                    /*!< Size = 69 (0x45)                                                          */



/* =========================================================================================================================== */
/* ================                                            SCU                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief System Control Unit (SCU)
  */

typedef struct                                  /*!< (@ 0x50005000) SCU Structure                                              */
{

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000000) NMI Clear Register, RESET_TYPE_3                           */

    struct
    {
      __OM  uint8_t NMIWDTC     : 1;            /*!< [0..0] Watchdog Timer NMI Clear                                           */
      __OM  uint8_t NMIPLLC     : 1;            /*!< [1..1] PLL Loss of Lock NMI Clear                                         */
      __OM  uint8_t NMINVMC     : 1;            /*!< [2..2] NVM Operation Complete NMI Clear                                   */
      __OM  uint8_t NMIOTC      : 1;            /*!< [3..3] NMI OT Clear                                                       */
      __OM  uint8_t NMIOWDC     : 1;            /*!< [4..4] Oscillator Watchdog NMI Clear                                      */
      __OM  uint8_t NMIMAPC     : 1;            /*!< [5..5] NVM Map Error NMI Clear                                            */
      __OM  uint8_t NMIECCC     : 1;            /*!< [6..6] ECC Error NMI Clear                                                */
      __OM  uint8_t NMISUPC     : 1;            /*!< [7..7] Supply Prewarning NMI Clear                                        */
    } bit;
  } NMICLR;
  __IM  uint8_t   RESERVED[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000004) Interrupt Request Register 0, RESET_TYPE_3                 */

    struct
    {
      __IM  uint8_t EXINT0R     : 1;            /*!< [0..0] Interrupt Flag for External Interrupt 0x on rising edge            */
      __IM  uint8_t EXINT0F     : 1;            /*!< [1..1] Interrupt Flag for External Interrupt 0x on falling edge           */
      __IM  uint8_t EXINT1R     : 1;            /*!< [2..2] Interrupt Flag for External Interrupt 1x on rising edge            */
      __IM  uint8_t EXINT1F     : 1;            /*!< [3..3] Interrupt Flag for External Interrupt 1x on falling edge           */
      __IM  uint8_t EXINT2R     : 1;            /*!< [4..4] Interrupt Flag for External Interrupt 2x on rising edge            */
      __IM  uint8_t EXINT2F     : 1;            /*!< [5..5] Interrupt Flag for External Interrupt 2x on falling edge           */
      __IM  uint8_t MONR        : 1;            /*!< [6..6] Interrupt Flag for External Interrupt MON on rising edge           */
      __IM  uint8_t MONF        : 1;            /*!< [7..7] Interrupt Flag for External Interrupt MON on falling
                                                     edge                                                                      */
    } bit;
  } IRCON0;
  __IM  uint8_t   RESERVED1[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000008) Interrupt Request Register 1, RESET_TYPE_3                 */

    struct
    {
      __IM  uint8_t EIR         : 1;            /*!< [0..0] Error Interrupt Flag for SSC1                                      */
      __IM  uint8_t TIR         : 1;            /*!< [1..1] Transmit Interrupt Flag for SSC1                                   */
      __IM  uint8_t RIR         : 1;            /*!< [2..2] Receive Interrupt Flag for SSC1                                    */
    } bit;
  } IRCON1;
  __IM  uint8_t   RESERVED2[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x0000000C) Interrupt Request Register 2, RESET_TYPE_3                 */

    struct
    {
      __IM  uint8_t EIR         : 1;            /*!< [0..0] Error Interrupt Flag for SSC2                                      */
      __IM  uint8_t TIR         : 1;            /*!< [1..1] Transmit Interrupt Flag for SSC2                                   */
      __IM  uint8_t RIR         : 1;            /*!< [2..2] Receive Interrupt Flag for SSC2                                    */
    } bit;
  } IRCON2;
  __IM  uint8_t   RESERVED3[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000010) Interrupt Request Register 3, RESET_TYPE_3                 */

    struct
    {
      __IM  uint8_t CCU6SR0     : 1;            /*!< [0..0] Interrupt Flag 0 for CCU6                                          */
      __IM  uint8_t             : 3;
      __IM  uint8_t CCU6SR1     : 1;            /*!< [4..4] Interrupt Flag 1 for CCU6                                          */
    } bit;
  } IRCON3;
  __IM  uint8_t   RESERVED4[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000014) Interrupt Request Register 4, RESET_TYPE_3                 */

    struct
    {
      __IM  uint8_t CCU6SR2     : 1;            /*!< [0..0] Interrupt Flag 2 for CCU6                                          */
      __IM  uint8_t             : 3;
      __IM  uint8_t CCU6SR3     : 1;            /*!< [4..4] Interrupt Flag 3 for CCU6                                          */
    } bit;
  } IRCON4;
  __IM  uint8_t   RESERVED5[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000018) NMI Status Register, RESET_TYPE_4                          */

    struct
    {
      __IM  uint8_t FNMIWDT     : 1;            /*!< [0..0] Watchdog Timer NMI Flag                                            */
      __IM  uint8_t FNMIPLL     : 1;            /*!< [1..1] PLL NMI Flag                                                       */
      __IM  uint8_t FNMINVM     : 1;            /*!< [2..2] NVM Operation Complete NMI Flag                                    */
      __IM  uint8_t FNMIOT      : 1;            /*!< [3..3] Over-temperature NMI Flag                                          */
      __IM  uint8_t FNMIOWD     : 1;            /*!< [4..4] Oscillator Watchdog or MI_CLK Watchdog NMI Flag                    */
      __IM  uint8_t FNMIMAP     : 1;            /*!< [5..5] NVM Map Error NMI Flag                                             */
      __IM  uint8_t FNMIECC     : 1;            /*!< [6..6] ECC Error NMI Flag                                                 */
      __IM  uint8_t FNMISUP     : 1;            /*!< [7..7] Supply Prewarning NMI Flag                                         */
    } bit;
  } NMISR;
  __IM  uint8_t   RESERVED6[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x0000001C) Interrupt Enable Register 0, RESET_TYPE_4                  */

    struct
    {
      __IM  uint8_t             : 7;
      __IOM uint8_t EA          : 1;            /*!< [7..7] Global Interrupt Mask                                              */
    } bit;
  } IEN0;
  __IM  uint8_t   RESERVED7[7];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000024) NMI Control Register, RESET_TYPE_4                         */

    struct
    {
      __IOM uint8_t NMIWDT      : 1;            /*!< [0..0] Watchdog Timer NMI Enable                                          */
      __IOM uint8_t NMIPLL      : 1;            /*!< [1..1] PLL Loss of Lock NMI Enable                                        */
      __IOM uint8_t NMINVM      : 1;            /*!< [2..2] NVM Operation Complete NMI Enable                                  */
      __IOM uint8_t NMIOT       : 1;            /*!< [3..3] NMI OT Enable                                                      */
      __IOM uint8_t NMIOWD      : 1;            /*!< [4..4] Oscillator Watchdog NMI Enable                                     */
      __IOM uint8_t NMIMAP      : 1;            /*!< [5..5] NVM Map Error NMI Enable                                           */
      __IOM uint8_t NMIECC      : 1;            /*!< [6..6] ECC Error NMI Enable                                               */
      __IOM uint8_t NMISUP      : 1;            /*!< [7..7] Supply Prewarning NMI Enable                                       */
    } bit;
  } NMICON;
  __IM  uint8_t   RESERVED8[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000028) External Interrupt Control Register 0, RESET_TYPE_3        */

    struct
    {
      __IOM uint8_t EXINT0      : 2;            /*!< [1..0] External Interrupt 0 Trigger Select                                */
      __IOM uint8_t EXINT1      : 2;            /*!< [3..2] External Interrupt 1 Trigger Select                                */
      __IOM uint8_t EXINT2      : 2;            /*!< [5..4] External Interrupt 2 Trigger Select                                */
      __IOM uint8_t MON_Trig_Sel : 2;           /*!< [7..6] MON Input Trigger Select                                           */
    } bit;
  } EXICON0;
  __IM  uint8_t   RESERVED9[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x0000002C) Interrupt Request 0 Clear Register, RESET_TYPE_3           */

    struct
    {
      __OM  uint8_t EXINT0RC    : 1;            /*!< [0..0] Interrupt Flag for External Interrupt 0x on rising edge
                                                     clear                                                                     */
      __OM  uint8_t EXINT0FC    : 1;            /*!< [1..1] Interrupt Flag for External Interrupt 0x on falling edge
                                                     clear                                                                     */
      __OM  uint8_t EXINT1RC    : 1;            /*!< [2..2] Interrupt Flag for External Interrupt 1x on rising edge
                                                     clear                                                                     */
      __OM  uint8_t EXINT1FC    : 1;            /*!< [3..3] Interrupt Flag for External Interrupt 1x on falling edge
                                                     clear                                                                     */
      __OM  uint8_t EXINT2RC    : 1;            /*!< [4..4] Interrupt Flag for External Interrupt 2x on rising edge
                                                     clear                                                                     */
      __OM  uint8_t EXINT2FC    : 1;            /*!< [5..5] Interrupt Flag for External Interrupt 2x on falling edge
                                                     clear                                                                     */
      __OM  uint8_t MONRC       : 1;            /*!< [6..6] Interrupt Flag for External Interrupt MON on rising edge
                                                     clear                                                                     */
      __OM  uint8_t MONFC       : 1;            /*!< [7..7] Interrupt Flag for External Interrupt MON on falling
                                                     edge clear                                                                */
    } bit;
  } IRCON0CLR;
  __IM  uint8_t   RESERVED10[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000030) Peripheral Interrupt Enable Register 1, RESET_TYPE_3       */

    struct
    {
      __IOM uint8_t EIREN1      : 1;            /*!< [0..0] SSC 1 Error Interrupt Enable                                       */
      __IOM uint8_t TIREN1      : 1;            /*!< [1..1] SSC 1 Transmit Interrupt Enable                                    */
      __IOM uint8_t RIREN1      : 1;            /*!< [2..2] SSC 1 Receive Interrupt Enable                                     */
      __IM  uint8_t             : 3;
      __IOM uint8_t RIEN1       : 1;            /*!< [6..6] UART 1 Receive Interrupt Enable                                    */
      __IOM uint8_t TIEN1       : 1;            /*!< [7..7] UART 1 Transmit Interrupt Enable                                   */
    } bit;
  } MODIEN1;
  __IM  uint8_t   RESERVED11[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000034) Peripheral Interrupt Enable Register 2, RESET_TYPE_3       */

    struct
    {
      __IOM uint8_t EIREN2      : 1;            /*!< [0..0] SSC 2 Error Interrupt Enable                                       */
      __IOM uint8_t TIREN2      : 1;            /*!< [1..1] SSC 2 Transmit Interrupt Enable                                    */
      __IOM uint8_t RIREN2      : 1;            /*!< [2..2] SSC 2 Receive Interrupt Enable                                     */
      __IM  uint8_t             : 2;
      __IOM uint8_t EXINT2_EN   : 1;            /*!< [5..5] External Interrupt 2 Enable                                        */
      __IOM uint8_t RIEN2       : 1;            /*!< [6..6] UART 2 Receive Interrupt Enable                                    */
      __IOM uint8_t TIEN2       : 1;            /*!< [7..7] UART 2 Transmit Interrupt Enable                                   */
    } bit;
  } MODIEN2;
  __IM  uint8_t   RESERVED12[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000038) Peripheral Interrupt Enable Register 3, RESET_TYPE_3       */

    struct
    {
      __IOM uint8_t IE0         : 1;            /*!< [0..0] External Interrupt Enable                                          */
      __IM  uint8_t             : 3;
      __IOM uint8_t MONIE       : 1;            /*!< [4..4] MON Interrupt Enable                                               */
      __IM  uint8_t MONSTS      : 1;            /*!< [5..5] MON Input Status                                                   */
    } bit;
  } MODIEN3;
  __IM  uint8_t   RESERVED13[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x0000003C) Peripheral Interrupt Enable Register 4, RESET_TYPE_3       */

    struct
    {
      __IOM uint8_t IE1         : 1;            /*!< [0..0] External Interrupt Enable                                          */
    } bit;
  } MODIEN4;
  __IM  uint8_t   RESERVED14[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000040) Power Mode Control Register 0, RESET_TYPE_3                */

    struct
    {
      __IOM uint8_t XTAL_ON     : 1;            /*!< [0..0] OSC_HP Operation in Power Down Mode                                */
      __IOM uint8_t SL          : 1;            /*!< [1..1] Sleep Mode Enable. Active High.                                    */
      __IOM uint8_t PD          : 1;            /*!< [2..2] Power Down Mode Enable. Active High.                               */
      __IOM uint8_t SD          : 1;            /*!< [3..3] Slow Down Mode Enable. Active High.                                */
    } bit;
  } PMCON0;
  __IM  uint8_t   RESERVED15[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000044) PLL Control Register, RESET_TYPE_4                         */

    struct
    {
      __IM  uint8_t LOCK        : 1;            /*!< [0..0] PLL Lock Status Flag                                               */
      __IOM uint8_t RESLD       : 1;            /*!< [1..1] Restart Lock Detection                                             */
      __IOM uint8_t OSCDISC     : 1;            /*!< [2..2] Oscillator Disconnect                                              */
      __IOM uint8_t VCOBYP      : 1;            /*!< [3..3] PLL VCO Bypass Mode Select                                         */
      __IOM uint8_t NDIV        : 4;            /*!< [7..4] PLL N-Divider                                                      */
    } bit;
  } PLL_CON;
  __IM  uint8_t   RESERVED16[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000048) Clock Control Register 1, RESET_TYPE_4                     */

    struct
    {
      __IOM uint8_t CLKREL      : 4;            /*!< [3..0] Slow Down Clock Divider for fCCLK Generation                       */
      __IOM uint8_t K2DIV       : 2;            /*!< [5..4] PLL K2-Divider                                                     */
      __IOM uint8_t K1DIV       : 1;            /*!< [6..6] PLL K1-Divider                                                     */
      __IOM uint8_t VCOSEL      : 1;            /*!< [7..7] VCOSEL Setting                                                     */
    } bit;
  } CMCON1;
  __IM  uint8_t   RESERVED17[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x0000004C) Clock Control Register 2, RESET_TYPE_4                     */

    struct
    {
      __IOM uint8_t PBA0CLKREL  : 1;            /*!< [0..0] PBA0 Clock Divider                                                 */
    } bit;
  } CMCON2;
  __IM  uint8_t   RESERVED18[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000050) Watchdog Timer Control Register, RESET_TYPE_3              */

    struct
    {
      __IOM uint8_t WDTIN       : 1;            /*!< [0..0] Watchdog Timer Input Frequency Selection                           */
      __IOM uint8_t WDTRS       : 1;            /*!< [1..1] WDT Refresh Start                                                  */
      __IOM uint8_t WDTEN       : 1;            /*!< [2..2] WDT Enable                                                         */
      __IM  uint8_t             : 1;
      __IM  uint8_t WDTPR       : 1;            /*!< [4..4] Watchdog Prewarning Mode Flag                                      */
      __IOM uint8_t WINBEN      : 1;            /*!< [5..5] Watchdog Window-Boundary Enable                                    */
    } bit;
  } WDTCON;
  __IM  uint8_t   RESERVED19[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000054) Analog Peripheral Clock Control 1 Register, RESET_TYPE_4   */

    struct
    {
      __IM  uint8_t PLL_LOCK    : 1;            /*!< [0..0] PLL Lock Indicator                                                 */
      __IOM uint8_t APCLK_SET   : 1;            /*!< [1..1] Set and Overtake Flag for Clock Settings                           */
      __IOM uint8_t T3CLK_SEL   : 1;            /*!< [2..2] Timer 3 Clock Selection                                            */
      __IOM uint8_t CLKWDT_IE   : 1;            /*!< [3..3] Clock Watchdog Interrupt Enable                                    */
      __IOM uint8_t BGCLK_SEL   : 1;            /*!< [4..4] Bandgap Clock Selection                                            */
      __IOM uint8_t BGCLK_DIV   : 1;            /*!< [5..5] Bandgap Clock Divider                                              */
      __IOM uint8_t CPCLK_SEL   : 1;            /*!< [6..6] Charge Pump Clock Selection                                        */
      __IOM uint8_t CPCLK_DIV   : 1;            /*!< [7..7] Charge Pump Clock Divider                                          */
    } bit;
  } APCLK_CTRL1;
  __IM  uint8_t   RESERVED20[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000058) Analog Peripheral Clock Register 1, RESET_TYPE_4           */

    struct
    {
      __IOM uint8_t APCLK1FAC   : 2;            /*!< [1..0] Analog Module Clock Factor                                         */
      __IOM uint8_t APCLK1SCLR  : 1;            /*!< [2..2] Analog Peripherals Clock Status Clear                              */
      __IM  uint8_t             : 1;
      __IM  uint8_t APCLK1STS   : 2;            /*!< [5..4] Analog Peripherals Clock Status                                    */
      __IM  uint8_t APCLK3STS   : 1;            /*!< [6..6] Loss of Clock Status                                               */
      __IOM uint8_t APCLK3SCLR  : 1;            /*!< [7..7] Analog Peripherals Clock Status Clear                              */
    } bit;
  } APCLK1;
  __IM  uint8_t   RESERVED21[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x0000005C) Analog Peripheral Clock Register 2, RESET_TYPE_4           */

    struct
    {
      __IOM uint8_t APCLK2FAC   : 5;            /*!< [4..0] Slow Down Clock Divider for TFILT_CLK Generation                   */
      __IM  uint8_t APCLK2STS   : 2;            /*!< [6..5] Analog Peripherals Clock Status                                    */
      __IOM uint8_t APCLK2SCLR  : 1;            /*!< [7..7] Analog Peripherals Clock Status Clear                              */
    } bit;
  } APCLK2;
  __IM  uint8_t   RESERVED22[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000060) Peripheral Management Control Register 1, RESET_TYPE_3     */

    struct
    {
      __IOM uint8_t ADC1_DIS    : 1;            /*!< [0..0] ADC1 Disable Request. Active high.                                 */
      __IOM uint8_t SSC1_DIS    : 1;            /*!< [1..1] SSC1 Disable Request. Active high.                                 */
      __IOM uint8_t CCU6_DIS    : 1;            /*!< [2..2] CCU6 Disable Request. Active high.                                 */
      __IOM uint8_t T2_DIS      : 1;            /*!< [3..3] T2 Disable Request. Active high.                                   */
      __IOM uint8_t GPT12_DIS   : 1;            /*!< [4..4] General Purpose Timer 12 Disable Request. Active high.             */
    } bit;
  } PMCON1;
  __IM  uint8_t   RESERVED23[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000064) Peripheral Management Control Register 2, RESET_TYPE_3     */

    struct
    {
      __IM  uint8_t             : 1;
      __IOM uint8_t SSC2_DIS    : 1;            /*!< [1..1] SSC2 Disable Request. Active high.                                 */
      __IM  uint8_t             : 1;
      __IOM uint8_t T21_DIS     : 1;            /*!< [3..3] T21 Disable Request. Active high.                                  */
      __IM  uint8_t             : 1;
      __IOM uint8_t T3_DIS      : 1;            /*!< [5..5] T3 Disable Request. Active high.                                   */
    } bit;
  } PMCON2;
  __IM  uint8_t   RESERVED24[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000068) Reset Control Register, RESET_TYPE_3                       */

    struct
    {
      __IOM uint8_t LOCKUP      : 1;            /*!< [0..0] Lockup Flag                                                        */
      __IM  uint8_t             : 6;
      __IOM uint8_t LOCKUP_EN   : 1;            /*!< [7..7] Lockup Reset Enable Flag                                           */
    } bit;
  } RSTCON;
  __IM  uint8_t   RESERVED25[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x0000006C) Analog Peripheral Clock Control 2 Register, RESET_TYPE_4   */

    struct
    {
      __IOM uint8_t SDADCCLK_DIV : 2;           /*!< [1..0] SD-ADC Clock Divider                                               */
      __IOM uint8_t T3CLK_DIV   : 2;            /*!< [3..2] Timer 3 Clock Divider                                              */
    } bit;
  } APCLK_CTRL2;
  __IM  uint8_t   RESERVED26[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000070) System Control Register 0, RESET_TYPE_4                    */

    struct
    {
      __IM  uint8_t             : 4;
      __IOM uint8_t NVMCLKFAC   : 2;            /*!< [5..4] NVM Access Clock Factor                                            */
      __IOM uint8_t SYSCLKSEL   : 2;            /*!< [7..6] System Clock Select                                                */
    } bit;
  } SYSCON0;
  __IM  uint8_t   RESERVED27[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000074) System Startup Status Register                             */

    struct
    {
      __IOM uint8_t INIT_FAIL   : 1;            /*!< [0..0] Initialization at startup failed                                   */
      __IOM uint8_t MRAMINITSTS : 1;            /*!< [1..1] Map RAM Initialization Status                                      */
      __IOM uint8_t PG100TP_CHKS_ERR : 1;       /*!< [2..2] 100 TP Page Checksum Error                                         */
    } bit;
  } SYS_STRTUP_STS;
  __IM  uint8_t   RESERVED28[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000078) Watchdog Timer Reload Register, RESET_TYPE_3               */

    struct
    {
      __IOM uint8_t WDTREL      : 8;            /*!< [7..0] Watchdog Timer Reload Value                                        */
    } bit;
  } WDTREL;
  __IM  uint8_t   RESERVED29[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x0000007C) Watchdog Window-Boundary Count, RESET_TYPE_3               */

    struct
    {
      __IOM uint8_t WDTWINB     : 8;            /*!< [7..0] Watchdog Window-Boundary Count Value                               */
    } bit;
  } WDTWINB;
  __IM  uint8_t   RESERVED30[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000080) Watchdog Timer, Low Byte, RESET_TYPE_3                     */

    struct
    {
      __IM  uint8_t WDT         : 8;            /*!< [7..0] Watchdog Timer Current Value                                       */
    } bit;
  } WDTL;
  __IM  uint8_t   RESERVED31[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000084) Watchdog Timer, High Byte, RESET_TYPE_3                    */

    struct
    {
      __IM  uint8_t WDT         : 8;            /*!< [7..0] Watchdog Timer Current Value                                       */
    } bit;
  } WDTH;
  __IM  uint8_t   RESERVED32[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000088) Baud Rate Control Register 1, RESET_TYPE_3                 */

    struct
    {
      __IOM uint8_t R           : 1;            /*!< [0..0] Baud Rate Generator Run Control Bit                                */
      __IOM uint8_t BRPRE       : 3;            /*!< [3..1] Prescaler Bit                                                      */
    } bit;
  } BCON1;
  __IM  uint8_t   RESERVED33[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x0000008C) Baud Rate Timer/Reload Register, Low Byte 1,
                                                                    RESET_TYPE_3                                               */

    struct
    {
      __IOM uint8_t FD_SEL      : 5;            /*!< [4..0] Fractional Divider Selection                                       */
      __IOM uint8_t BR_VALUE    : 3;            /*!< [7..5] Baud Rate Timer/Reload Value                                       */
    } bit;
  } BGL1;
  __IM  uint8_t   RESERVED34[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000090) Baud Rate Timer/Reload Register, High Byte, RESET_TYPE_3   */

    struct
    {
      __IOM uint8_t BR_VALUE    : 8;            /*!< [7..0] Baud Rate Timer/Reload Value                                       */
    } bit;
  } BGH1;
  __IM  uint8_t   RESERVED35[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000094) LIN Status Register, RESET_TYPE_3                          */

    struct
    {
      __IOM uint8_t BRDIS       : 1;            /*!< [0..0] Baud Rate Detection Disable                                        */
      __IOM uint8_t BGSEL       : 2;            /*!< [2..1] Baud Rate Select for Detection                                     */
      __IM  uint8_t BRK         : 1;            /*!< [3..3] Break Field Flag                                                   */
      __IM  uint8_t EOFSYN      : 1;            /*!< [4..4] End of SYN Byte Interrupt Flag                                     */
      __IM  uint8_t ERRSYN      : 1;            /*!< [5..5] SYN Byte Error Interrupt Flag                                      */
      __IOM uint8_t SYNEN       : 1;            /*!< [6..6] End of SYN Byte and SYN Byte Error Interrupts Enable               */
    } bit;
  } LINST;
  __IM  uint8_t   RESERVED36[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000098) Baud Rate Control Register 2, RESET_TYPE_3                 */

    struct
    {
      __IOM uint8_t R           : 1;            /*!< [0..0] Baud Rate Generator Run Control Bit                                */
      __IOM uint8_t BRPRE       : 3;            /*!< [3..1] Prescaler Bit                                                      */
    } bit;
  } BCON2;
  __IM  uint8_t   RESERVED37[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x0000009C) Baud Rate Timer/Reload Register, Low Byte 2,
                                                                    RESET_TYPE_3                                               */

    struct
    {
      __IOM uint8_t FD_SEL      : 5;            /*!< [4..0] Fractional Divider Selection                                       */
      __IOM uint8_t BR_VALUE    : 3;            /*!< [7..5] Baud Rate Timer/Reload Value                                       */
    } bit;
  } BGL2;
  __IM  uint8_t   RESERVED38[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x000000A0) Baud Rate Timer/Reload Register, High Byte, RESET_TYPE_3   */

    struct
    {
      __IOM uint8_t BR_VALUE    : 8;            /*!< [7..0] Baud Rate Timer/Reload Value                                       */
    } bit;
  } BGH2;
  __IM  uint8_t   RESERVED39[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x000000A4) LIN Status Clear Register, RESET_TYPE_3                    */

    struct
    {
      __IM  uint8_t             : 3;
      __OM  uint8_t BRKC        : 1;            /*!< [3..3] Break Field Flag Clear                                             */
      __OM  uint8_t EOFSYNC     : 1;            /*!< [4..4] End of SYN Byte Interrupt Flag Clear                               */
      __OM  uint8_t ERRSYNC     : 1;            /*!< [5..5] SYN Byte Error Interrupt Flag                                      */
    } bit;
  } LINSCLR;
  __IM  uint8_t   RESERVED40[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x000000A8) Identity Register, RESET_TYPE_3                            */

    struct
    {
      __IM  uint8_t VERID       : 3;            /*!< [2..0] Version ID                                                         */
      __IM  uint8_t PRODID      : 5;            /*!< [7..3] Product ID                                                         */
    } bit;
  } ID;
  __IM  uint8_t   RESERVED41[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x000000AC) Password Register, RESET_TYPE_3                            */

    struct
    {
      __IOM uint8_t MODE        : 2;            /*!< [1..0] Bit-Protection Scheme Control Bit                                  */
      __IM  uint8_t PROTECT_S   : 1;            /*!< [2..2] Bit-Protection Signal Status Bit                                   */
      __IOM uint8_t PASS        : 5;            /*!< [7..3] Password Bits                                                      */
    } bit;
  } PASSWD;
  __IM  uint8_t   RESERVED42[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x000000B0) OSC Control Register, RESET_TYPE_4                         */

    struct
    {
      __IOM uint8_t OSCSS       : 2;            /*!< [1..0] Oscillator Source Select                                           */
      __IOM uint8_t OSCWDTRST   : 1;            /*!< [2..2] Oscillator Watchdog Reset                                          */
      __IM  uint8_t OSC2L       : 1;            /*!< [3..3] OSC-Too-Low Condition Flag                                         */
      __IOM uint8_t XPD         : 1;            /*!< [4..4] XTAL (OSC_HP) Power Down Control                                   */
      __IM  uint8_t             : 2;
      __IOM uint8_t OSCTRIM_8   : 1;            /*!< [7..7] OSC_PLL Trim Configuration Bit [8]                                 */
    } bit;
  } OSC_CON;
  __IM  uint8_t   RESERVED43[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x000000B4) Clock Output Control Register, RESET_TYPE_4                */

    struct
    {
      __IOM uint8_t COREL       : 4;            /*!< [3..0] Clock Output Divider                                               */
      __IOM uint8_t COUTS0      : 1;            /*!< [4..4] Clock Out Source Select Bit 0                                      */
      __IOM uint8_t TLEN        : 1;            /*!< [5..5] Toggle Latch Enable                                                */
      __IOM uint8_t COUTS1      : 1;            /*!< [6..6] Clock Out Source Select Bit 1                                      */
      __IOM uint8_t EN          : 1;            /*!< [7..7] CLKOUT Enable                                                      */
    } bit;
  } COCON;
  __IM  uint8_t   RESERVED44[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x000000B8) Peripheral Input Select Register, RESET_TYPE_3             */

    struct
    {
      __IOM uint8_t EXINT0IS    : 2;            /*!< [1..0] External Interrupt 0 Input Select                                  */
      __IOM uint8_t EXINT1IS    : 2;            /*!< [3..2] External Interrupt 1 Input Select                                  */
      __IOM uint8_t EXINT2IS    : 2;            /*!< [5..4] External Interrupt 2 Input Select                                  */
      __IOM uint8_t URIOS1      : 1;            /*!< [6..6] UART1 Input/Output Select                                          */
      __IOM uint8_t U_TX_CONDIS : 1;            /*!< [7..7] UART1 TxD Connection Disable                                       */
    } bit;
  } MODPISEL;
  __IM  uint8_t   RESERVED45[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x000000BC) Peripheral Input Select Register 1, RESET_TYPE_3           */

    struct
    {
      __IOM uint8_t GPT12CAPINB : 1;            /*!< [0..0] GPT12 CAPINB Input Control                                         */
      __IM  uint8_t             : 5;
      __IOM uint8_t T2EXCON     : 1;            /*!< [6..6] Timer 2 External Input Control                                     */
      __IOM uint8_t T21EXCON    : 1;            /*!< [7..7] Timer 21 External Input Control                                    */
    } bit;
  } MODPISEL1;
  __IM  uint8_t   RESERVED46[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x000000C0) Peripheral Input Select Register 2, RESET_TYPE_3           */

    struct
    {
      __IOM uint8_t T2IS        : 2;            /*!< [1..0] Timer 2 Input Select                                               */
      __IOM uint8_t T21IS       : 2;            /*!< [3..2] Timer 21 Input Select                                              */
      __IOM uint8_t T2EXIS      : 2;            /*!< [5..4] Timer 2 External Input Select                                      */
      __IOM uint8_t T21EXIS     : 2;            /*!< [7..6] Timer 21 External Input Select                                     */
    } bit;
  } MODPISEL2;
  __IM  uint8_t   RESERVED47[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x000000C4) Peripheral Input Select Register, RESET_TYPE_3             */

    struct
    {
      __IM  uint8_t             : 6;
      __IOM uint8_t URIOS2      : 1;            /*!< [6..6] UART2 Input/Output Select                                          */
    } bit;
  } MODPISEL3;
  __IM  uint8_t   RESERVED48[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x000000C8) Module Suspend Control Register 1, RESET_TYPE_3            */

    struct
    {
      __IOM uint8_t WDTSUSP     : 1;            /*!< [0..0] SCU Watchdog Timer Debug Suspend Bit                               */
      __IOM uint8_t T12SUSP     : 1;            /*!< [1..1] Timer 12 Debug Suspend Bit                                         */
      __IOM uint8_t T13SUSP     : 1;            /*!< [2..2] Timer 13 Debug Suspend Bit                                         */
      __IOM uint8_t T2_SUSP     : 1;            /*!< [3..3] Timer2 Debug Suspend Bit                                           */
      __IOM uint8_t GPT12_SUSP  : 1;            /*!< [4..4] GPT12 Debug Suspend Bit                                            */
      __IM  uint8_t             : 1;
      __IOM uint8_t T21_SUSP    : 1;            /*!< [6..6] Timer21 Debug Suspend Bit                                          */
    } bit;
  } MODSUSP1;
  __IM  uint8_t   RESERVED49[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x000000CC) Module Suspend Control Register 2, RESET_TYPE_3            */

    struct
    {
      __IOM uint8_t T3_SUSP     : 1;            /*!< [0..0] Measurement Unit Debug Suspend Bit                                 */
      __IOM uint8_t MU_SUSP     : 1;            /*!< [1..1] Measurement Unit Debug Suspend Bit                                 */
      __IOM uint8_t ADC1_SUSP   : 1;            /*!< [2..2] ADC1 Unit Debug Suspend Bit                                        */
    } bit;
  } MODSUSP2;
  __IM  uint8_t   RESERVED50[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x000000D0) GPT12 Peripheral Input Select Register, RESET_TYPE_3       */

    struct
    {
      __IOM uint8_t GPT12       : 4;            /*!< [3..0] GPT12 TIN3B / TIN4D Input Select                                   */
      __IOM uint8_t TRIG_CONF   : 1;            /*!< [4..4] CCU6 Trigger Configuration.                                        */
      __IOM uint8_t T3_GPT12_SEL : 1;           /*!< [5..5] CCU6_INT_SEL.                                                      */
    } bit;
  } GPT12PISEL;
  __IM  uint8_t   RESERVED51[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x000000D4) Error Detection and Correction Control Register,
                                                                    RESET_TYPE_3                                               */

    struct
    {
      __IOM uint8_t RIE         : 1;            /*!< [0..0] RAM Double Bit ECC Error Interrupt Enable                          */
      __IM  uint8_t             : 1;
      __IOM uint8_t NVMIE       : 1;            /*!< [2..2] NVM Double Bit ECC Error Interrupt Enable                          */
    } bit;
  } EDCCON;
  __IM  uint8_t   RESERVED52[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x000000D8) Error Detection and Correction Status Register,
                                                                    RESET_TYPE_4                                               */

    struct
    {
      __IM  uint8_t RDBE        : 1;            /*!< [0..0] RAM Double Bit Error                                               */
      __IM  uint8_t             : 1;
      __IM  uint8_t NVMDBE      : 1;            /*!< [2..2] NVM Double Bit Error                                               */
      __IM  uint8_t             : 1;
      __IM  uint8_t RSBE        : 1;            /*!< [4..4] RAM Single Bit Error                                               */
    } bit;
  } EDCSTAT;
  __IM  uint8_t   RESERVED53[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x000000DC) Memory Status Register, RESET_TYPE_3                       */

    struct
    {
      __IOM uint8_t SECTORINFO  : 6;            /*!< [5..0] Sector Information                                                 */
      __IOM uint8_t SASTATUS    : 2;            /*!< [7..6] Service Algorithm Status                                           */
    } bit;
  } MEMSTAT;
  __IM  uint8_t   RESERVED54[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x000000E0) NVM Protection Status Register, RESET_TYPE_4               */

    struct
    {
      __IOM uint8_t NVMPROTSTSL_0 : 1;          /*!< [0..0] NVM Protection Status Register Low Flags                           */
      __IOM uint8_t NVMPROTSTSL_1 : 1;          /*!< [1..1] NVM Protection Status Register Low Flags                           */
      __IOM uint8_t NVMPROTSTSL_2 : 1;          /*!< [2..2] NVM Protection Status Register Low Flags                           */
      __IOM uint8_t NVMPROTSTSL_3 : 1;          /*!< [3..3] NVM Protection Status Register Low Flags                           */
    } bit;
  } NVM_PROT_STS;
  __IM  uint8_t   RESERVED55[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x000000E4) Memory Access Status Register, RESET_TYPE_3                */

    struct
    {
      __IM  uint8_t NVM_PROT_ERR : 1;           /*!< [0..0] NVM Access Protection                                              */
      __IM  uint8_t NVM_ADDR_ERR : 1;           /*!< [1..1] NVM Address Protection                                             */
      __IM  uint8_t NVM_SFR_PROT_ERR : 1;       /*!< [2..2] NVM SFR Access Protection                                          */
      __IM  uint8_t NVM_SFR_ADDR_ERR : 1;       /*!< [3..3] NVM SFR Address Protection                                         */
      __IM  uint8_t ROM_PROT_ERR : 1;           /*!< [4..4] ROM Access Protection                                              */
      __IM  uint8_t ROM_ADDR_ERR : 1;           /*!< [5..5] ROM Address Protection                                             */
      __IM  uint8_t RAM_PROT_ERR : 1;           /*!< [6..6] RAM Access Protection                                              */
    } bit;
  } MEM_ACC_STS;
  __IM  uint8_t   RESERVED56[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x000000E8) Port Output Control Register, RESET_TYPE_3                 */

    struct
    {
      __IOM uint8_t PDM0        : 3;            /*!< [2..0] P0.0 Port Driver Mode                                              */
      __IM  uint8_t             : 1;
      __IOM uint8_t PDM1        : 3;            /*!< [6..4] P0.1 Port Driver Mode                                              */
    } bit;
  } P0_POCON0;
  __IM  uint8_t   RESERVED57[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x000000EC) Port Output Control Register, RESET_TYPE_3                 */

    struct
    {
      __IOM uint8_t PDM2        : 3;            /*!< [2..0] P0.2 Port Driver Mode                                              */
      __IM  uint8_t             : 1;
      __IOM uint8_t PDM3        : 3;            /*!< [6..4] P0.3 Port Driver Mode                                              */
    } bit;
  } P0_POCON1;
  __IM  uint8_t   RESERVED58[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x000000F0) Port Output Control Register, RESET_TYPE_3                 */

    struct
    {
      __IOM uint8_t PDM4        : 3;            /*!< [2..0] P0.4 Port Driver Mode                                              */
    } bit;
  } P0_POCON2;
  __IM  uint8_t   RESERVED59[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x000000F4) Temperature Compensation Control Register, RESET_TYPE_3    */

    struct
    {
      __IOM uint8_t TCC         : 2;            /*!< [1..0] Temperature Compensation Control                                   */
    } bit;
  } TCCR;
  __IM  uint8_t   RESERVED60[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x000000F8) Port Output Control Register, RESET_TYPE_3                 */

    struct
    {
      __IOM uint8_t PDM0        : 3;            /*!< [2..0] P1.0 Port Driver Mode                                              */
      __IM  uint8_t             : 1;
      __IOM uint8_t PDM1        : 3;            /*!< [6..4] P1.1 Port Driver Mode                                              */
    } bit;
  } P1_POCON0;
  __IM  uint8_t   RESERVED61[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x000000FC) Port Output Control Register, RESET_TYPE_3                 */

    struct
    {
      __IOM uint8_t PDM2        : 3;            /*!< [2..0] P1.2 Port Driver Mode                                              */
      __IM  uint8_t             : 1;
      __IOM uint8_t PDM3        : 3;            /*!< [6..4] P1.3 Port Driver Mode                                              */
    } bit;
  } P1_POCON1;
  __IM  uint8_t   RESERVED62[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000100) Port Output Control Register, RESET_TYPE_3                 */

    struct
    {
      __IOM uint8_t PDM4        : 3;            /*!< [2..0] P1.4 Port Driver Mode                                              */
    } bit;
  } P1_POCON2;
  __IM  uint8_t   RESERVED63[11];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x0000010C) Error Detection and Correction Status Clear Register,
                                                                    RESET_TYPE_3                                               */

    struct
    {
      __OM  uint8_t RDBEC       : 1;            /*!< [0..0] RAM Double Bit Error Clear                                         */
      __IM  uint8_t             : 1;
      __OM  uint8_t NVMDBEC     : 1;            /*!< [2..2] NVM Double Bit Error Clear                                         */
      __IM  uint8_t             : 1;
      __OM  uint8_t RSBEC       : 1;            /*!< [4..4] RAM Single Bit Error Clear                                         */
    } bit;
  } EDCSCLR;
  __IM  uint8_t   RESERVED64[55];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000144) DMA Interrupt Enable Register 1, RESET_TYPE_3              */

    struct
    {
      __IOM uint8_t CH1IE       : 1;            /*!< [0..0] DMA Channel 4 Interrupt Enable (ADC1 Channel 0)                    */
      __IOM uint8_t CH2IE       : 1;            /*!< [1..1] DMA Channel 5 Interrupt Enable (ADC1 Channel 1)                    */
      __IOM uint8_t CH3IE       : 1;            /*!< [2..2] DMA Channel 6 Interrupt Enable (ADC1 Channel 2)                    */
      __IOM uint8_t CH4IE       : 1;            /*!< [3..3] DMA Channel 7 Interrupt Enable (ADC1 Channel 3)                    */
      __IOM uint8_t CH5IE       : 1;            /*!< [4..4] DMA Channel 8 Interrupt Enable (ADC1 Channel 4)                    */
      __IOM uint8_t CH6IE       : 1;            /*!< [5..5] DMA Channel 9 Interrupt Enable (ADC1 Channel 5)                    */
      __IOM uint8_t CH7IE       : 1;            /*!< [6..6] DMA Channel 10 Interrupt Enable (ADC1 Channel 6)                   */
      __IOM uint8_t CH8IE       : 1;            /*!< [7..7] DMA Channel 11 Interrupt Enable (ADC1 Channel 7)                   */
    } bit;
  } DMAIEN1;
  __IM  uint8_t   RESERVED65[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000148) DMA Interrupt Enable Register 2, RESET_TYPE_3              */

    struct
    {
      __IOM uint8_t TRERRIE     : 1;            /*!< [0..0] DMA Transfer Error Interrupt Enable                                */
      __IOM uint8_t TRSEQ1RDYIE : 1;            /*!< [1..1] DMA Channel 0 Interrupt Enable (ADC1 Sequence)                     */
      __IOM uint8_t TRSEQ2RDYIE : 1;            /*!< [2..2] DMA Channel 1 Interrupt Enable (ADC1 ESM)                          */
      __IOM uint8_t SSCTXIE     : 1;            /*!< [3..3] DMA Channel 2 Interrupt Enable (SSCx Transmit)                     */
      __IOM uint8_t SSCRXIE     : 1;            /*!< [4..4] DMA Channel 3 Interrupt Enable (SSCx Receive)                      */
      __IOM uint8_t GPT12IE     : 1;            /*!< [5..5] DMA Channel 12 Interrupt Enable (GPT12/Timer3)                     */
      __IOM uint8_t SDADCIE     : 1;            /*!< [6..6] DMA Channel 13 Interrupt Enable (SDADC)                            */
    } bit;
  } DMAIEN2;
  __IM  uint8_t   RESERVED66[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x0000014C) DMA Source Selection Register, RESET_TYPE_3                */

    struct
    {
      __IOM uint8_t SSCTXSRCSEL : 1;            /*!< [0..0] SSCx Transmit Source Select                                        */
      __IOM uint8_t SSCRXSRCSEL : 1;            /*!< [1..1] SSCx Receive Source Select                                         */
      __IOM uint8_t T12ZM_DMAEN : 1;            /*!< [2..2] CC6_T12_ZM (Zero Match) DMA muxer, DMA channel 9                   */
      __IOM uint8_t T12PM_DMAEN : 1;            /*!< [3..3] CC6_T12_PM (Period Match) DMA muxer, DMA channel 11                */
      __IM  uint8_t             : 1;
      __IM  uint8_t SSCTX       : 1;            /*!< [5..5] DMA Channel 2 Request (SSCx Transmit)                              */
      __IM  uint8_t SSCRX       : 1;            /*!< [6..6] DMA Channel 3 Request (SSCx Receive)                               */
      __IM  uint8_t GPT12_T3    : 1;            /*!< [7..7] DMA Channel 12 Request (GPT12E, Timer3)                            */
    } bit;
  } DMASRCSEL;
  __IM  uint8_t   RESERVED67[7];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000154) DMA Interrupt Control Register 1, RESET_TYPE_3             */

    struct
    {
      __IM  uint8_t CH1         : 1;            /*!< [0..0] DMA Channel 4 Interrupt Status (ADC1 Channel 0)                    */
      __IM  uint8_t CH2         : 1;            /*!< [1..1] DMA Channel 5 Interrupt Status (ADC1 Channel 1)                    */
      __IM  uint8_t CH3         : 1;            /*!< [2..2] DMA Channel 6 Interrupt Status (ADC1 Channel 2)                    */
      __IM  uint8_t CH4         : 1;            /*!< [3..3] DMA Channel 7 Interrupt Status (ADC1 Channel 3)                    */
      __IM  uint8_t CH5         : 1;            /*!< [4..4] DMA Channel 8 Interrupt Status (ADC1 Channel 4)                    */
      __IM  uint8_t CH6         : 1;            /*!< [5..5] DMA Channel 9 Interrupt Status (ADC1 Channel 5)                    */
      __IM  uint8_t CH7         : 1;            /*!< [6..6] DMA Channel 10 Interrupt Status (ADC1 Channel 6)                   */
      __IM  uint8_t CH8         : 1;            /*!< [7..7] DMA Channel 11 Interrupt Status (ADC1 Channel 7)                   */
    } bit;
  } DMAIRC1;
  __IM  uint8_t   RESERVED68[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000158) ADC1 Interrupt Control Register 2, RESET_TYPE_3            */

    struct
    {
      __IM  uint8_t STRDY       : 1;            /*!< [0..0] DMA Single Transfer Ready                                          */
      __IM  uint8_t TRSEQ1DY    : 1;            /*!< [1..1] DMA Channel 0 Interrupt Status (ADC1 Sequence)                     */
      __IM  uint8_t TRSEQ2DY    : 1;            /*!< [2..2] DMA Channel 1 Interrupt Status (ADC1 ESM)                          */
      __IM  uint8_t SSC1RDY     : 1;            /*!< [3..3] DMA Channel 2 Interrupt Status (SSCx Transmit)                     */
      __IM  uint8_t SSC2RDY     : 1;            /*!< [4..4] DMA Channel 3 Interrupt Status (SSCx Receive)                      */
      __IM  uint8_t GPT12       : 1;            /*!< [5..5] DMA Channel 12 Interrupt Status (GPT12/Timer3)                     */
      __IM  uint8_t SDADC       : 1;            /*!< [6..6] DMA Channel 13 Interrupt Status (SDADC)                            */
    } bit;
  } DMAIRC2;
  __IM  uint8_t   RESERVED69[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x0000015C) General Purpose Timer 12 Interrupt Enable Register
                                                                    , RESET_TYPE_3                                             */

    struct
    {
      __IOM uint8_t T2IE        : 1;            /*!< [0..0] General Purpose Timer 12 T2 Interrupt Enable                       */
      __IOM uint8_t T3IE        : 1;            /*!< [1..1] General Purpose Timer 12 T3 Interrupt Enable                       */
      __IOM uint8_t T4IE        : 1;            /*!< [2..2] General Purpose Timer 12 T4 Interrupt Enable                       */
      __IOM uint8_t T5IE        : 1;            /*!< [3..3] General Purpose Timer 12 T5 Interrupt Enable                       */
      __IOM uint8_t T6IE        : 1;            /*!< [4..4] General Purpose Timer 12 T6 Interrupt Enable                       */
      __IOM uint8_t CRIE        : 1;            /*!< [5..5] General Purpose Timer 12 Capture and Reload Interrupt
                                                     Enable                                                                    */
    } bit;
  } GPT12IEN;
  __IM  uint8_t   RESERVED70[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000160) Timer and Counter Control/Status Register, RESET_TYPE_3    */

    struct
    {
      __IM  uint8_t T2          : 1;            /*!< [0..0] GPT Module 1 Timer 2 Interrupt Status                              */
      __IM  uint8_t T3          : 1;            /*!< [1..1] GPT Module 1 Timer3 Interrupt Status                               */
      __IM  uint8_t T4          : 1;            /*!< [2..2] GPT Module 1 Timer4 Interrupt Status                               */
      __IM  uint8_t T5          : 1;            /*!< [3..3] GPT Module 2 Timer5 Interrupt Status                               */
      __IM  uint8_t T6          : 1;            /*!< [4..4] GPT Module 2Timer6 Interrupt Status                                */
      __IM  uint8_t CR          : 1;            /*!< [5..5] GPT Module 2 Capture Reload Interrupt Status                       */
    } bit;
  } GPT12IRC;
  __IM  uint8_t   RESERVED71[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000164) Timer and Counter Control/Status Clear Register,
                                                                    RESET_TYPE_3                                               */

    struct
    {
      __OM  uint8_t T2C         : 1;            /*!< [0..0] GPT Module 1 Timer 2 Interrupt Status Clear                        */
      __OM  uint8_t T3C         : 1;            /*!< [1..1] GPT Module 1 Timer3 Interrupt Status Clear                         */
      __OM  uint8_t T4C         : 1;            /*!< [2..2] GPT Module 1 Timer4 Interrupt Status Clear                         */
      __OM  uint8_t T5C         : 1;            /*!< [3..3] GPT Module 2 Timer5 Interrupt Status Clear                         */
      __OM  uint8_t T6C         : 1;            /*!< [4..4] GPT Module 2Timer6 Interrupt Status Clear                          */
      __OM  uint8_t CRC         : 1;            /*!< [5..5] GPT Module 2 Capture Reload Interrupt Status Clear                 */
    } bit;
  } GPT12ICLR;
  __IM  uint8_t   RESERVED72[19];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000178) Interrupt Request 1 Clear Register, RESET_TYPE_3           */

    struct
    {
      __OM  uint8_t EIRC        : 1;            /*!< [0..0] Error Interrupt Flag for SSC1 Clear                                */
      __OM  uint8_t TIRC        : 1;            /*!< [1..1] Transmit Interrupt Flag for SSC1 Clear                             */
      __OM  uint8_t RIRC        : 1;            /*!< [2..2] Receive Interrupt Flag for SSC1 Clear                              */
    } bit;
  } IRCON1CLR;
  __IM  uint8_t   RESERVED73[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x0000017C) Interrupt Request 2 Clear Register, RESET_TYPE_3           */

    struct
    {
      __OM  uint8_t EIRC        : 1;            /*!< [0..0] Error Interrupt Flag for SSC2 Clear                                */
      __OM  uint8_t TIRC        : 1;            /*!< [1..1] Transmit Interrupt Flag for SSC2 Clear                             */
      __OM  uint8_t RIRC        : 1;            /*!< [2..2] Receive Interrupt Flag for SSC2 Clear                              */
    } bit;
  } IRCON2CLR;
  __IM  uint8_t   RESERVED74[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000180) DMA Source Selection Register 2, RESET_TYPE_3              */

    struct
    {
      __IOM uint8_t GPT12_DMAEN : 2;            /*!< [1..0] GPT12 T3 DMA muxer, DMA channel 12                                 */
    } bit;
  } DMASRCSEL2;
  __IM  uint8_t   RESERVED75[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000184) DMA Interrupt Control 1 Clear Register, RESET_TYPE_3       */

    struct
    {
      __OM  uint8_t CH1C        : 1;            /*!< [0..0] DMA Channel 4 Interrupt Status Clear (ADC1 Channel 0)              */
      __OM  uint8_t CH2C        : 1;            /*!< [1..1] DMA Channel 5 Interrupt Status Clear (ADC1 Channel 1)              */
      __OM  uint8_t CH3C        : 1;            /*!< [2..2] DMA Channel 6 Interrupt Status Clear (ADC1 Channel 2)              */
      __OM  uint8_t CH4C        : 1;            /*!< [3..3] DMA Channel 7 Interrupt Status Clear (ADC1 Channel 3)              */
      __OM  uint8_t CH5C        : 1;            /*!< [4..4] DMA Channel 8 Interrupt Status Clear (ADC1 Channel 4)              */
      __OM  uint8_t CH6C        : 1;            /*!< [5..5] DMA Channel 9 Interrupt Status Clear (ADC1 Channel 5)              */
      __OM  uint8_t CH7C        : 1;            /*!< [6..6] DMA Channel 10 Interrupt Status Clear (ADC1 Channel 6)             */
      __OM  uint8_t CH8C        : 1;            /*!< [7..7] DMA Channel 11 Interrupt Status Clear (ADC1 Channel 7)             */
    } bit;
  } DMAIRC1CLR;
  __IM  uint8_t   RESERVED76[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000188) ADC1 Interrupt Control 2 Clear Register, RESET_TYPE_3      */

    struct
    {
      __IM  uint8_t             : 1;
      __OM  uint8_t TRSEQ1DYC   : 1;            /*!< [1..1] DMA Channel 0 Interrupt Status Clear (ADC1 Sequence)               */
      __OM  uint8_t TRSEQ2DYC   : 1;            /*!< [2..2] DMA Channel 1 Interrupt Status Clear (ADC1 ESM)                    */
      __OM  uint8_t SSC1C       : 1;            /*!< [3..3] DMA Channel 2 Interrupt Status Clear (SSCx Transmit)               */
      __OM  uint8_t SSC2C       : 1;            /*!< [4..4] DMA Channel 3 Interrupt Status Clear (SSCx Receive)                */
      __OM  uint8_t GPT12C      : 1;            /*!< [5..5] DMA Channel 12 Interrupt Status Clear (GPT12/Timer3)               */
      __OM  uint8_t SDADCC      : 1;            /*!< [6..6] DMA Channel 13 Interrupt Status Clear (SDADC)                      */
    } bit;
  } DMAIRC2CLR;
  __IM  uint8_t   RESERVED77[7];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000190) Interrupt Request 3 Clear Register, RESET_TYPE_3           */

    struct
    {
      __OM  uint8_t CCU6SR0C    : 1;            /*!< [0..0] Interrupt Flag 0 for CCU6 Clear                                    */
      __IM  uint8_t             : 3;
      __OM  uint8_t CCU6SR1C    : 1;            /*!< [4..4] Interrupt Flag 1 for CCU6 Clear                                    */
    } bit;
  } IRCON3CLR;
  __IM  uint8_t   RESERVED78[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000194) Interrupt Request 4 Clear Register, RESET_TYPE_3           */

    struct
    {
      __OM  uint8_t CCU6SR2C    : 1;            /*!< [0..0] Interrupt Flag 2 for CCU6 Clear                                    */
      __IM  uint8_t             : 3;
      __OM  uint8_t CCU6SR3C    : 1;            /*!< [4..4] Interrupt Flag 3 for CCU6 Clear                                    */
    } bit;
  } IRCON4CLR;
  __IM  uint8_t   RESERVED79[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000198) DMA Source Selection Clear Register, RESET_TYPE_3          */

    struct
    {
      __IM  uint8_t             : 5;
      __OM  uint8_t SSCTXC      : 1;            /*!< [5..5] SSC Transmit Request Clear                                         */
      __OM  uint8_t SSCRXC      : 1;            /*!< [6..6] SSC Receive Request Clear                                          */
      __OM  uint8_t GPT12_T3C   : 1;            /*!< [7..7] GPT12 Transmit Request Clear                                       */
    } bit;
  } DMASRCCLR;
} SCU_Type;                                     /*!< Size = 409 (0x199)                                                        */



/* =========================================================================================================================== */
/* ================                                           SCUPM                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief System Control Unit for Power Modules (SCUPM)
  */

typedef struct                                  /*!< (@ 0x50006000) SCUPM Structure                                            */
{

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) Analog Module Clock Frequency Status Register              */

    struct
    {
      __IM  uint32_t AMCLK1_FREQ : 6;           /*!< [5..0] Current frequency of Analog Module Clock System Clock
                                                     (MI_CLK)                                                                  */
      __IM  uint32_t            : 2;
      __IM  uint32_t AMCLK2_FREQ : 6;           /*!< [13..8] Current frequency of Analog Module Clock 2 (TFILT_CLK)            */
    } bit;
  } AMCLK_FREQ_STS;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) Analog Module Clock Control                                */

    struct
    {
      __IOM uint32_t CLKWDT_PD_N : 1;           /*!< [0..0] Clock Watchdog Powerdown                                           */
    } bit;
  } AMCLK_CTRL;
  __IM  uint32_t  RESERVED;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) Analog Module Clock Limit Register                         */

    struct
    {
      __IOM uint32_t AMCLK1_UP_TH : 6;          /*!< [5..0] Analog Module Clock 1 (MI_CLK) Upper Limit Threshold               */
      __IOM uint32_t AMCLK1_UP_HYS : 2;         /*!< [7..6] Analog Module Clock 1 (MI_CLK) Upper Hysteresis                    */
      __IOM uint32_t AMCLK1_LOW_TH : 6;         /*!< [13..8] Analog Module Clock 1 (MI_CLK) Lower Limit Threshold              */
      __IOM uint32_t AMCLK1_LOW_HYS : 2;        /*!< [15..14] Analog Module Clock 1 (MI_CLK) Lower Hysteresis                  */
      __IOM uint32_t AMCLK2_UP_TH : 6;          /*!< [21..16] Analog Module Clock 2 (TFILT_CLK) Upper Limit Threshold          */
      __IOM uint32_t AMCLK2_UP_HYS : 2;         /*!< [23..22] Analog Module Clock 2 (TFILT_CLK) Upper Hysteresis               */
      __IOM uint32_t AMCLK2_LOW_TH : 6;         /*!< [29..24] Analog Module Clock 2 (TFILT_CLK) Lower Limit Threshold          */
      __IOM uint32_t AMCLK2_LOW_HYS : 2;        /*!< [31..30] Analog Module Clock 2 (TFILT_CLK) Lower Hysteresis               */
    } bit;
  } AMCLK_TH_HYS;
  __IM  uint32_t  RESERVED1;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000014) System Interrupt Status Clear                              */

    struct
    {
      __OM  uint32_t LIN_OC_ICLR : 1;           /*!< [0..0] LIN Overcurrent interrupt status                                   */
      __OM  uint32_t LIN_OT_ICLR : 1;           /*!< [1..1] LIN Overtemperature interrupt status                               */
      __OM  uint32_t LIN_TMOUT_ICLR : 1;        /*!< [2..2] LIN TXD timeout                                                    */
      __IM  uint32_t            : 3;
      __OM  uint32_t PMU_OTWARN_ICLR : 1;       /*!< [6..6] PMU Regulator Overtemperature Prewarning (ADC2, Channel
                                                     9) interrupt status                                                       */
      __OM  uint32_t PMU_OT_ICLR : 1;           /*!< [7..7] PMU Regulator Overtemperature Shutdown (ADC2, Channel
                                                     9) interrupt status                                                       */
      __OM  uint32_t SYS_OTWARN_ICLR : 1;       /*!< [8..8] System Overtemperature Prewarning (ADC2, Channel 8) interrupt
                                                     status                                                                    */
      __OM  uint32_t SYS_OT_ICLR : 1;           /*!< [9..9] System Overtemperature Shutdown (ADC2, Channel 8) interrupt
                                                     status                                                                    */
      __OM  uint32_t REFBG_LOTHWARN_ICLR : 1;   /*!< [10..10] 8 Bit ADC2 Reference Undervoltage (ADC2, Channel 5)
                                                     interrupt status                                                          */
      __OM  uint32_t REFBG_UPTHWARN_ICLR : 1;   /*!< [11..11] 8 Bit ADC2 Reference Overvoltage (ADC2, Channel 5)
                                                     interrupt status                                                          */
      __OM  uint32_t VREF5V_LOWTH_ICLR : 1;     /*!< [12..12] VREF5V ADC1 Reference Undervoltage (ADC2, Channel 4)
                                                     Interrupt Status                                                          */
      __OM  uint32_t VREF5V_UPTH_ICLR : 1;      /*!< [13..13] VREF5V ADC1 Reference Overvoltage (ADC2, Channel 4)
                                                     Interrupt Status                                                          */
      __OM  uint32_t VREF5V_OVL_ICLR : 1;       /*!< [14..14] VREF5V Overload Interrupt Status                                 */
      __OM  uint32_t ADC2_ESM_ICLR : 1;         /*!< [15..15] ADC2 Exceptional Sequence Measurement Interrupt Status           */
      __OM  uint32_t PHU_ZCLOW_ICLR : 1;        /*!< [16..16] Phase U Zero Crossing Comperator Low Interrupt Status            */
      __OM  uint32_t PHU_ZCHI_ICLR : 1;         /*!< [17..17] Phase U Zero Crossing Comperator High Interrupt Status           */
      __OM  uint32_t PHV_ZCLOW_ICLR : 1;        /*!< [18..18] Phase V Zero Crossing Comperator Low Interrupt Status            */
      __OM  uint32_t PHV_ZCHI_ICLR : 1;         /*!< [19..19] Phase V Zero Crossing Comperator High Interrupt Status           */
      __OM  uint32_t PHW_ZCLOW_ICLR : 1;        /*!< [20..20] Phase W Zero Crossing Comperator Low Interrupt Status            */
      __OM  uint32_t PHW_ZCHI_ICLR : 1;         /*!< [21..21] Phase W Zero Crossing Comperator High Interrupt Status           */
      __OM  uint32_t ADC3_EOC_ICLR : 1;         /*!< [22..22] ADC3 EOC Interrupt Status                                        */
      __OM  uint32_t ADC4_EOC_ICLR : 1;         /*!< [23..23] ADC4 EOC Interrupt Status                                        */
      __OM  uint32_t PHU_ZCLOW_SCLR : 1;        /*!< [24..24] Phase U Zero Crossing Comperator Low Status                      */
      __OM  uint32_t PHU_ZCHI_SCLR : 1;         /*!< [25..25] Phase U Zero Crossing Comperator High Status                     */
      __OM  uint32_t PHV_ZCLOW_SCLR : 1;        /*!< [26..26] Phase V Zero Crossing Comperator Low Status                      */
      __OM  uint32_t PHV_ZCHI_SCLR : 1;         /*!< [27..27] Phase V Zero Crossing Comperator High Status                     */
      __OM  uint32_t PHW_ZCLOW_SCLR : 1;        /*!< [28..28] Phase W Zero Crossing Comperator Low Status                      */
      __OM  uint32_t PHW_ZCHI_SCLR : 1;         /*!< [29..29] Phase W Zero Crossing Comperator High Status                     */
    } bit;
  } SYS_ISCLR;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000018) System Interrupt Status                                    */

    struct
    {
      __IM  uint32_t LIN_OC_IS  : 1;            /*!< [0..0] LIN Overcurrent interrupt status                                   */
      __IM  uint32_t LIN_OT_IS  : 1;            /*!< [1..1] LIN Overtemperature interrupt status                               */
      __IM  uint32_t LIN_TMOUT_IS : 1;          /*!< [2..2] LIN TXD timeout                                                    */
      __IM  uint32_t            : 3;
      __IM  uint32_t PMU_OTWARN_IS : 1;         /*!< [6..6] PMU Regulator Overtemperature Prewarning (ADC2, Channel
                                                     9) interrupt status                                                       */
      __IM  uint32_t PMU_OT_IS  : 1;            /*!< [7..7] PMU Regulator Overtemperature Shutdown (ADC2, Channel
                                                     9) interrupt status                                                       */
      __IM  uint32_t SYS_OTWARN_IS : 1;         /*!< [8..8] System Overtemperature Prewarning (ADC2, Channel 8) interrupt
                                                     status                                                                    */
      __IM  uint32_t SYS_OT_IS  : 1;            /*!< [9..9] System Overtemperature Shutdown (ADC2, Channel 8) interrupt
                                                     status                                                                    */
      __IM  uint32_t REFBG_LOTHWARN_IS : 1;     /*!< [10..10] 8 Bit ADC2 Reference Undervoltage (ADC2, Channel 5)
                                                     interrupt status                                                          */
      __IM  uint32_t REFBG_UPTHWARN_IS : 1;     /*!< [11..11] 8 Bit ADC2 Reference Overvoltage (ADC2, Channel 5)
                                                     interrupt status                                                          */
      __IM  uint32_t VREF5V_LOWTH_IS : 1;       /*!< [12..12] VREF5V ADC1 Reference Undervoltage (ADC2, Channel 4)
                                                     Interrupt Status                                                          */
      __IM  uint32_t VREF5V_UPTH_IS : 1;        /*!< [13..13] VREF5V ADC1 Reference Overvoltage (ADC2, Channel 4)
                                                     Interrupt Status                                                          */
      __IM  uint32_t VREF5V_OVL_IS : 1;         /*!< [14..14] VREF5V Overload Interrupt Status                                 */
      __IM  uint32_t ADC2_ESM_IS : 1;           /*!< [15..15] ADC2 Exceptional Sequence Measurement Interrupt Status           */
      __IM  uint32_t PHU_ZCLOW_IS : 1;          /*!< [16..16] Phase U Zero Crossing Comperator Low Interrupt Status            */
      __IM  uint32_t PHU_ZCHI_IS : 1;           /*!< [17..17] Phase U Zero Crossing Comperator High Interrupt Status           */
      __IM  uint32_t PHV_ZCLOW_IS : 1;          /*!< [18..18] Phase V Zero Crossing Comperator Low Interrupt Status            */
      __IM  uint32_t PHV_ZCHI_IS : 1;           /*!< [19..19] Phase V Zero Crossing Comperator High Interrupt Status           */
      __IM  uint32_t PHW_ZCLOW_IS : 1;          /*!< [20..20] Phase W Zero Crossing Comperator Low Interrupt Status            */
      __IM  uint32_t PHW_ZCHI_IS : 1;           /*!< [21..21] Phase W Zero Crossing Comperator High Interrupt Status           */
      __IM  uint32_t ADC3_EOC_IS : 1;           /*!< [22..22] ADC3 EOC Interrupt Status                                        */
      __IM  uint32_t ADC4_EOC_IS : 1;           /*!< [23..23] ADC4 EOC Interrupt Status                                        */
      __IM  uint32_t PHU_ZCLOW_STS : 1;         /*!< [24..24] Phase U Zero Crossing Comperator Low Status                      */
      __IM  uint32_t PHU_ZCHI_STS : 1;          /*!< [25..25] Phase U Zero Crossing Comperator High Status                     */
      __IM  uint32_t PHV_ZCLOW_STS : 1;         /*!< [26..26] Phase V Zero Crossing Comperator Low Status                      */
      __IM  uint32_t PHV_ZCHI_STS : 1;          /*!< [27..27] Phase V Zero Crossing Comperator High Status                     */
      __IM  uint32_t PHW_ZCLOW_STS : 1;         /*!< [28..28] Phase W Zero Crossing Comperator Low Status                      */
      __IM  uint32_t PHW_ZCHI_STS : 1;          /*!< [29..29] Phase W Zero Crossing Comperator High Status                     */
    } bit;
  } SYS_IS;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x0000001C) System Supply Interrupt Status                             */

    struct
    {
      __IM  uint32_t MON_UV_IS  : 1;            /*!< [0..0] MON Undervoltage Interrupt Status (ADC2 channel 4)                 */
      __IM  uint32_t VS_UV_IS   : 1;            /*!< [1..1] VS Undervoltage Interrupt Status (ADC2 channel 1)                  */
      __IM  uint32_t VDD5V_UV_IS : 1;           /*!< [2..2] VDDP Undervoltage Interrupt Status (ADC2 channel 2)                */
      __IM  uint32_t VDD1V5_UV_IS : 1;          /*!< [3..3] VDDC Undervoltage Interrupt Status (ADC2 channel 3)                */
      __IM  uint32_t MON_OV_IS  : 1;            /*!< [4..4] MON Overvoltage Interrupt Status (ADC2 channel 4)                  */
      __IM  uint32_t VS_OV_IS   : 1;            /*!< [5..5] VS Overvoltage Interrupt Status (ADC2 channel 1)                   */
      __IM  uint32_t VDD5V_OV_IS : 1;           /*!< [6..6] VDDP Overvoltage Interrupt Status (ADC2 channel 2)                 */
      __IM  uint32_t VDD1V5_OV_IS : 1;          /*!< [7..7] VDDC Overvoltage Interrupt Status (ADC2 channel 3)                 */
      __IM  uint32_t            : 8;
      __IM  uint32_t MON_UV_STS : 1;            /*!< [16..16] MON Undervoltage Status                                          */
      __IM  uint32_t VS_UV_STS  : 1;            /*!< [17..17] VS Undervoltage Status                                           */
      __IM  uint32_t VDD5V_UV_STS : 1;          /*!< [18..18] VDDP Undervoltage Status                                         */
      __IM  uint32_t VDD1V5_UV_STS : 1;         /*!< [19..19] VDDC Undervoltage Status                                         */
      __IM  uint32_t MON_OV_STS : 1;            /*!< [20..20] MON Overvoltage Status                                           */
      __IM  uint32_t VS_OV_STS  : 1;            /*!< [21..21] VS Overvoltage Interrupt Status                                  */
      __IM  uint32_t VDD5V_OV_STS : 1;          /*!< [22..22] VDDP Overvoltage Status                                          */
      __IM  uint32_t VDD1V5_OV_STS : 1;         /*!< [23..23] VDDC Overvoltage Status                                          */
    } bit;
  } SYS_SUPPLY_IRQ_STS;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000020) System Supply Interrupt Control                            */

    struct
    {
      __IOM uint32_t MON_UV_IE  : 1;            /*!< [0..0] MON Undervoltage Interrupt Enable                                  */
      __IOM uint32_t VS_UV_IE   : 1;            /*!< [1..1] VS Undervoltage Interrupt Enable                                   */
      __IOM uint32_t VDD5V_UV_IE : 1;           /*!< [2..2] VDD5V Undervoltage Interrupt Enable                                */
      __IOM uint32_t VDD1V5_UV_IE : 1;          /*!< [3..3] VDD1V5 Undervoltage Interrupt Enable                               */
      __IOM uint32_t MON_OV_IE  : 1;            /*!< [4..4] MON Overvoltage Interrupt Enable                                   */
      __IOM uint32_t VS_OV_IE   : 1;            /*!< [5..5] VS Overvoltage Interrupt Enable                                    */
      __IOM uint32_t VDD5V_OV_IE : 1;           /*!< [6..6] VDD5V Overvoltage Interrupt Enable                                 */
      __IOM uint32_t VDD1V5_OV_IE : 1;          /*!< [7..7] VDD1V5 Overvoltage Interrupt Enable                                */
    } bit;
  } SYS_SUPPLY_IRQ_CTRL;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000024) System Supply Interrupt Status Clear                       */

    struct
    {
      __OM  uint32_t MON_UV_ICLR : 1;           /*!< [0..0] MON Undervoltage Interrupt Status (ADC2 channel 4)                 */
      __OM  uint32_t VS_UV_ICLR : 1;            /*!< [1..1] VS Undervoltage Interrupt Status (ADC2 channel 1)                  */
      __OM  uint32_t VDD5V_UV_ICLR : 1;         /*!< [2..2] VDDP Undervoltage Interrupt Status (ADC2 channel 2)                */
      __OM  uint32_t VDD1V5_UV_ICLR : 1;        /*!< [3..3] VDDC Undervoltage Interrupt Status (ADC2 channel 3)                */
      __OM  uint32_t MON_OV_ICLR : 1;           /*!< [4..4] MON Overvoltage Interrupt Status (ADC2 channel 4)                  */
      __OM  uint32_t VS_OV_ICLR : 1;            /*!< [5..5] VS Overvoltage Interrupt Status (ADC2 channel 1)                   */
      __OM  uint32_t VDD5V_OV_ICLR : 1;         /*!< [6..6] VDDP Overvoltage Interrupt Status (ADC2 channel 2)                 */
      __OM  uint32_t VDD1V5_OV_ICLR : 1;        /*!< [7..7] VDDC Overvoltage Interrupt Status (ADC2 channel 3)                 */
      __IM  uint32_t            : 8;
      __OM  uint32_t MON_UV_SCLR : 1;           /*!< [16..16] MON Undervoltage Status                                          */
      __OM  uint32_t VS_UV_SCLR : 1;            /*!< [17..17] VS Undervoltage Status                                           */
      __OM  uint32_t VDD5V_UV_SCLR : 1;         /*!< [18..18] VDDP Undervoltage Status                                         */
      __OM  uint32_t VDD1V5_UV_SCLR : 1;        /*!< [19..19] VDDC Undervoltage Status                                         */
      __OM  uint32_t MON_OV_SCLR : 1;           /*!< [20..20] MON Overvoltage Status                                           */
      __OM  uint32_t VS_OV_SCLR : 1;            /*!< [21..21] VS Overvoltage Interrupt Status                                  */
      __OM  uint32_t VDD5V_OV_SCLR : 1;         /*!< [22..22] VDDP Overvoltage Status                                          */
      __OM  uint32_t VDD1V5_OV_SCLR : 1;        /*!< [23..23] VDDC Overvoltage Status                                          */
    } bit;
  } SYS_SUPPLY_IRQ_CLR;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000028) System Interrupt Control                                   */

    struct
    {
      __IOM uint32_t LIN_OC_IE  : 1;            /*!< [0..0] LIN Overcurrent Interrupt Enable                                   */
      __IOM uint32_t LIN_OT_IE  : 1;            /*!< [1..1] LIN Overtemperature Interrupt Enable                               */
      __IOM uint32_t LIN_TMOUT_IE : 1;          /*!< [2..2] LIN TXD timeout Interrupt Enable                                   */
      __IM  uint32_t            : 3;
      __IOM uint32_t PMU_OTWARN_IE : 1;         /*!< [6..6] PMU Regulator Overtemperature Warning Interrupt Enable             */
      __IOM uint32_t PMU_OT_IE  : 1;            /*!< [7..7] PMU Regulator Overtemperature Shutdown Interrupt Enable
                                                     (leads to shutdown of System)                                             */
      __IOM uint32_t SYS_OTWARN_IE : 1;         /*!< [8..8] System Overtemperature Warning Interrupt Enable                    */
      __IOM uint32_t SYS_OT_IE  : 1;            /*!< [9..9] System Overtemperature Shutdown Interrupt Enable (leads
                                                     to shutdown of System)                                                    */
      __IOM uint32_t REFBG_LOTHWARN_IE : 1;     /*!< [10..10] Reference Voltage Undervoltage Interrupt Enable                  */
      __IOM uint32_t REFBG_UPTHWARN_IE : 1;     /*!< [11..11] Reference Voltage Overvoltage Interrupt Enable                   */
      __IOM uint32_t VREF5V_LOWTH_IE : 1;       /*!< [12..12] VREF5V ADC1 Reference Undervoltage (ADC2, Channel 4)
                                                     Interrupt Enable                                                          */
      __IOM uint32_t VREF5V_UPTH_IE : 1;        /*!< [13..13] VREF5V ADC1 Reference Overvoltage (ADC2, Channel 4)
                                                     Interrupt Enable                                                          */
      __IOM uint32_t VREF5V_OVL_IE : 1;         /*!< [14..14] VREF5V Overload Interrupt Enable                                 */
      __IOM uint32_t ADC2_ESM_IE : 1;           /*!< [15..15] ADC2 Exceptional Sequence Measurement Interrupt Enable           */
      __IOM uint32_t PHU_ZCLOW_IE : 1;          /*!< [16..16] Phase U Zero Crossing Comperator Low Interrupt Enable            */
      __IOM uint32_t PHU_ZCHI_IE : 1;           /*!< [17..17] Phase U Zero Crossing Comperator High Interrupt Enable           */
      __IOM uint32_t PHV_ZCLOW_IE : 1;          /*!< [18..18] Phase V Zero Crossing Comperator Low Interrupt Enable            */
      __IOM uint32_t PHV_ZCHI_IE : 1;           /*!< [19..19] Phase V Zero Crossing Comperator High Interrupt Enable           */
      __IOM uint32_t PHW_ZCLOW_IE : 1;          /*!< [20..20] Phase W Zero Crossing Comperator Low Interrupt Enable            */
      __IOM uint32_t PHW_ZCHI_IE : 1;           /*!< [21..21] Phase W Zero Crossing Comperator High Interrupt Enable           */
      __IOM uint32_t ADC3_EOC_IE : 1;           /*!< [22..22] ADC3 EOC Interrupt Enable                                        */
      __IOM uint32_t ADC4_EOC_IE : 1;           /*!< [23..23] ADC4 EOC Interrupt Enable                                        */
    } bit;
  } SYS_IRQ_CTRL;
  __IM  uint32_t  RESERVED2;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000030) Power Control Unit Control Status                          */

    struct
    {
      __IM  uint32_t            : 1;
      __IOM uint32_t CLKWDT_SD_DIS : 1;         /*!< [1..1] Power Modules Clock Watchdog Shutdown Disable                      */
      __IM  uint32_t            : 5;
      __IOM uint32_t FAIL_PS_DIS : 1;           /*!< [7..7] Disable LIN, BDRV and CP because of Overtemperature                */
      __IOM uint32_t LIN_VS_UV_SD_DIS : 1;      /*!< [8..8] LIN Module VS Undervoltage Transmitter Shutdown                    */
      __IM  uint32_t            : 5;
      __IOM uint32_t SYS_VSD_OV_SLM_DIS : 1;    /*!< [14..14] VSD Overvoltage Shutdown for Peripherals Disable                 */
      __IM  uint32_t            : 9;
      __IOM uint32_t SYS_OT_PS_DIS : 1;         /*!< [24..24] System Overtemperature Power Switches Shutdown Disable           */
      __IOM uint32_t CLKLOSS_SD_DIS : 1;        /*!< [25..25] Power Switches Loss of Clock Shutdown Disable (AMCLK3)           */
      __IOM uint32_t CLKWDT_RES_SD_DIS : 1;     /*!< [26..26] Clock Watchdog Reset Disable                                     */
    } bit;
  } PCU_CTRL_STS;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000034) WDT1 Watchdog Control                                      */

    struct
    {
      __IOM uint32_t WDP_SEL    : 6;            /*!< [5..0] Watchdog Period Selection and trigger                              */
      __IOM uint32_t SOWCONF    : 2;            /*!< [7..6] Short Open Window Configuration                                    */
    } bit;
  } WDT1_TRIG;
  __IM  uint32_t  RESERVED3[7];

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000054) Bridge Driver Interrrupt Status Clear                      */

    struct
    {
      __OM  uint32_t LS1_DS_ICLR : 1;           /*!< [0..0] Bridge Driver Low Side 1 Pre-Driver short Interrupt Status         */
      __OM  uint32_t LS2_DS_ICLR : 1;           /*!< [1..1] Bridge Driver Low Side 2 Pre-Driver short Interrupt Status         */
      __OM  uint32_t HS1_DS_ICLR : 1;           /*!< [2..2] Bridge Driver High Side 1 Pre-Driver short Interrupt
                                                     Status                                                                    */
      __OM  uint32_t HS2_DS_ICLR : 1;           /*!< [3..3] Bridge Driver High Side 2 Pre-Driver short Interrupt
                                                     Status                                                                    */
      __OM  uint32_t LS3_DS_ICLR : 1;           /*!< [4..4] Bridge Driver Low Side 3 Pre-Driver short Interrupt Status         */
      __OM  uint32_t HS3_DS_ICLR : 1;           /*!< [5..5] Bridge Driver High Side 3 Pre-Driver short Interrupt
                                                     Status                                                                    */
      __IM  uint32_t            : 4;
      __OM  uint32_t LS1_OC_ICLR : 1;           /*!< [10..10] External Low Side 1 FET Over-current Status                      */
      __OM  uint32_t LS2_OC_ICLR : 1;           /*!< [11..11] External Low Side 2 FET Over-current Status                      */
      __OM  uint32_t HS1_OC_ICLR : 1;           /*!< [12..12] External High 1 FET Over-current Status                          */
      __OM  uint32_t HS2_OC_ICLR : 1;           /*!< [13..13] External High Side 2 FET Over-current Status                     */
      __OM  uint32_t LS3_OC_ICLR : 1;           /*!< [14..14] External Low Side 3 FET Over-current Status                      */
      __OM  uint32_t HS3_OC_ICLR : 1;           /*!< [15..15] External High Side 3 FET Over-current Status                     */
      __OM  uint32_t VCP_LOWTH2_ICLR : 1;       /*!< [16..16] Warning for VCP Lower Threshold 2 Measurement (VCP_LOW
                                                     Signal from CP) Interrupt Status                                          */
      __OM  uint32_t VCP_LOWTH1_ICLR : 1;       /*!< [17..17] Warning for VCP Lower Threshold 1 Measurement (ADC2
                                                     channel 7) Interrupt Status                                               */
      __OM  uint32_t VCP_UPTH_ICLR : 1;         /*!< [18..18] Warning for VCP Upper Threshold Measurement (ADC2 channel
                                                     7) Interrupt Status                                                       */
      __OM  uint32_t VSD_LOWTH_ICLR : 1;        /*!< [19..19] Warning for VSD Lower Threshold Measurement (ADC2 channel
                                                     6) Interrupt Status                                                       */
      __OM  uint32_t VSD_UPTH_ICLR : 1;         /*!< [20..20] Warning for VSD Upper Threshold Measurement (ADC2 channel
                                                     6) Interrupt Status                                                       */
      __IM  uint32_t            : 3;
      __OM  uint32_t VCP_LOWTH2_SCLR : 1;       /*!< [24..24] Warning for VCP Lower Threshold 2 Measurement (VCP_LOW
                                                     Signal from CP) Status                                                    */
      __OM  uint32_t VCP_LOWTH1_SCLR : 1;       /*!< [25..25] Warning for VCP Lower Threshold 1 Measurement (ADC2
                                                     channel 7) Status                                                         */
      __OM  uint32_t VCP_UPTH_SCLR : 1;         /*!< [26..26] Warning for VCP Upper Threshold Measurement (ADC2 channel
                                                     7) Status                                                                 */
      __OM  uint32_t VSD_LOWTH_SCLR : 1;        /*!< [27..27] Warning for VSD Lower Threshold Measurement (ADC2 channel
                                                     6) Status                                                                 */
      __OM  uint32_t VSD_UPTH_SCLR : 1;         /*!< [28..28] Warning for VSD Upper Threshold Measurement (ADC2 channel
                                                     6) Status                                                                 */
    } bit;
  } BDRV_ISCLR;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000058) Bridge Driver Interrrupt Status                            */

    struct
    {
      __IM  uint32_t LS1_DS_IS  : 1;            /*!< [0..0] Bridge Driver Low Side 1 Pre-Driver short Interrupt Status         */
      __IM  uint32_t LS2_DS_IS  : 1;            /*!< [1..1] Bridge Driver Low Side 2 Pre-Driver short Interrupt Status         */
      __IM  uint32_t HS1_DS_IS  : 1;            /*!< [2..2] Bridge Driver High Side 1 Pre-Driver short Interrupt
                                                     Status                                                                    */
      __IM  uint32_t HS2_DS_IS  : 1;            /*!< [3..3] Bridge Driver High Side 2 Pre-Driver short Interrupt
                                                     Status                                                                    */
      __IM  uint32_t LS3_DS_IS  : 1;            /*!< [4..4] Bridge Driver Low Side 3 Pre-Driver short Interrupt Status         */
      __IM  uint32_t HS3_DS_IS  : 1;            /*!< [5..5] Bridge Driver High Side 3 Pre-Driver short Interrupt
                                                     Status                                                                    */
      __IM  uint32_t            : 4;
      __IM  uint32_t LS1_OC_IS  : 1;            /*!< [10..10] External Low Side 1 FET Over-current Status                      */
      __IM  uint32_t LS2_OC_IS  : 1;            /*!< [11..11] External Low Side 2 FET Over-current Status                      */
      __IM  uint32_t HS1_OC_IS  : 1;            /*!< [12..12] External High 1 FET Over-current Status                          */
      __IM  uint32_t HS2_OC_IS  : 1;            /*!< [13..13] External High Side 2 FET Over-current Status                     */
      __IM  uint32_t LS3_OC_IS  : 1;            /*!< [14..14] External Low Side 3 FET Over-current Status                      */
      __IM  uint32_t HS3_OC_IS  : 1;            /*!< [15..15] External High Side 3 FET Over-current Status                     */
      __IM  uint32_t VCP_LOWTH2_IS : 1;         /*!< [16..16] Warning for VCP Lower Threshold 2 Measurement (VCP_LOW
                                                     Signal from CP) Interrupt Status                                          */
      __IM  uint32_t VCP_LOWTH1_IS : 1;         /*!< [17..17] Warning for VCP Lower Threshold 1 Measurement (ADC2
                                                     channel 7) Interrupt Status                                               */
      __IM  uint32_t VCP_UPTH_IS : 1;           /*!< [18..18] Warning for VCP Upper Threshold Measurement (ADC2 channel
                                                     7) Interrupt Status                                                       */
      __IM  uint32_t VSD_LOWTH_IS : 1;          /*!< [19..19] Warning for VSD Lower Threshold Measurement (ADC2 channel
                                                     6) Interrupt Status                                                       */
      __IM  uint32_t VSD_UPTH_IS : 1;           /*!< [20..20] Warning for VSD Upper Threshold Measurement (ADC2 channel
                                                     6) Interrupt Status                                                       */
      __IM  uint32_t            : 3;
      __IM  uint32_t VCP_LOWTH2_STS : 1;        /*!< [24..24] Warning for VCP Lower Threshold 2 Measurement (VCP_LOW
                                                     Signal from CP) Status                                                    */
      __IM  uint32_t VCP_LOWTH1_STS : 1;        /*!< [25..25] Warning for VCP Lower Threshold 1 Measurement (ADC2
                                                     channel 7) Status                                                         */
      __IM  uint32_t VCP_UPTH_STS : 1;          /*!< [26..26] Warning for VCP Upper Threshold Measurement (ADC2 channel
                                                     7) Status                                                                 */
      __IM  uint32_t VSD_LOWTH_STS : 1;         /*!< [27..27] Warning for VSD Lower Threshold Measurement (ADC2 channel
                                                     6) Status                                                                 */
      __IM  uint32_t VSD_UPTH_STS : 1;          /*!< [28..28] Warning for VSD Upper Threshold Measurement (ADC2 channel
                                                     6) Status                                                                 */
    } bit;
  } BDRV_IS;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x0000005C) Bridge Driver Interrupt Control                            */

    struct
    {
      __IOM uint32_t LS1_DS_IE  : 1;            /*!< [0..0] Bridge Driver Low Side 1 Pre-Driver Short Interrupt Enable         */
      __IOM uint32_t LS2_DS_IE  : 1;            /*!< [1..1] Bridge Driver Low Side 2 Pre-Driver Short Interrupt Enable         */
      __IOM uint32_t HS1_DS_IE  : 1;            /*!< [2..2] Bridge Driver High Side 1 Pre-Driver Short Interrupt
                                                     Enable                                                                    */
      __IOM uint32_t HS2_DS_IE  : 1;            /*!< [3..3] Bridge Driver High Side 2 Pre-Driver Short Interrupt
                                                     Enable                                                                    */
      __IOM uint32_t LS3_DS_IE  : 1;            /*!< [4..4] Bridge Driver Low Side 3 Pre-Driver Short Interrupt Enable         */
      __IOM uint32_t HS3_DS_IE  : 1;            /*!< [5..5] Bridge Driver High Side 3 Pre-Driver Short Interrupt
                                                     Enable                                                                    */
      __IM  uint32_t            : 4;
      __IOM uint32_t LS1_OC_IE  : 1;            /*!< [10..10] External Low Side 1 FET Over-current Interrupt Enable            */
      __IOM uint32_t LS2_OC_IE  : 1;            /*!< [11..11] External Low Side 2 FET Over-current Interrupt Enable            */
      __IOM uint32_t HS1_OC_IE  : 1;            /*!< [12..12] External High Side 1 FET Over-current Interrupt Enable           */
      __IOM uint32_t HS2_OC_IE  : 1;            /*!< [13..13] External High Side 2 FET Over-current Interrupt Enable           */
      __IOM uint32_t LS3_OC_IE  : 1;            /*!< [14..14] External Low Side 3 FET Over-current Interrupt Enable            */
      __IOM uint32_t HS3_OC_IE  : 1;            /*!< [15..15] External High Side 3 FET Over-current Interrupt Enable           */
      __IOM uint32_t VCP_LOWTH2_IE : 1;         /*!< [16..16] VCP Measurement Lower Threshold 2 Interrupt Enable               */
      __IOM uint32_t VCP_LOWTH1_IE : 1;         /*!< [17..17] VCP Measurement Lower Threshold 1 Interrupt Enable               */
      __IOM uint32_t VCP_UPTH_IE : 1;           /*!< [18..18] VCP Measurement Upper Threshold Interrupt Enable                 */
      __IOM uint32_t VSD_LOWTH_IE : 1;          /*!< [19..19] VSD Measurement Lower Threshold Interrupt Enable                 */
      __IOM uint32_t VSD_UPTH_IE : 1;           /*!< [20..20] VSD Measurement Upper Threshold Interrupt Enable                 */
    } bit;
  } BDRV_IRQ_CTRL;
  __IM  uint32_t  RESERVED4[3];

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x0000006C) System Tick Calibration Register                           */

    struct
    {
      __IOM uint32_t STCALIB    : 26;           /*!< [25..0] System Tick Calibration                                           */
    } bit;
  } STCALIB;
  __IM  uint32_t  RESERVED5[4];

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000080) Bus Fault Status                                           */

    struct
    {
      __IM  uint32_t DBFSTS     : 1;            /*!< [0..0] Data Bus Fault Status Valid Flag                                   */
      __IM  uint32_t SBFSTS     : 1;            /*!< [1..1] System Bus Fault Status Valid Flag                                 */
    } bit;
  } BFSTS;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000084) Data Bus Fault Address Register                            */

    struct
    {
      __IM  uint32_t DBFA       : 32;           /*!< [31..0] Data Bus Fault Address Register                                   */
    } bit;
  } DBFA;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000088) System Bus Fault Address Register                          */

    struct
    {
      __IM  uint32_t SBFA       : 32;           /*!< [31..0] System Bus Fault Address Register                                 */
    } bit;
  } SBFA;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x0000008C) Bus Fault Status Clear Register                            */

    struct
    {
      __OM  uint32_t DBFSTSCLR  : 1;            /*!< [0..0] Data Bus Fault Status Clear Flag                                   */
      __OM  uint32_t SBFSTSCLR  : 1;            /*!< [1..1] System Bus Fault Status Clear Flag                                 */
    } bit;
  } BFSTS_CLR;
} SCUPM_Type;                                   /*!< Size = 144 (0x90)                                                         */



/* =========================================================================================================================== */
/* ================                                           SSC1                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief SSC1 Module (SSC1)
  */

typedef struct                                  /*!< (@ 0x48024000) SSC1 Structure                                             */
{

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000000) Port Input Select Register, RESET_TYPE_3                   */

    struct
    {
      __IOM uint16_t MIS_0      : 1;            /*!< [0..0] Master Mode Receiver Input Select: 0b0=see (SSC1)., 0b1=see
                                                     (SSC1)., 0b0=Receiver input (Port A: P1.2) is selected
                                                     (SSC2)., 0b1=Receiver input (Port B: P2.5) is selected
                                                     (SSC2).,                                                                  */
      __IOM uint16_t SIS        : 1;            /*!< [1..1] Slave Mode Receiver Input Select: 0b0=Receiver input
                                                     (Port A: P0.2) is selected (SSC1)., 0b1=Receiver input
                                                     (Port B: P0.2) is selected (SSC1)., 0b0=Receiver input
                                                     (Port A: P1.1) is selected (SSC2)., 0b1=Receiver input
                                                     (Port B: P1.1) is selected (SSC2).,                                       */
      __IOM uint16_t CIS        : 1;            /*!< [2..2] Slave Mode Clock Input Select: 0b0=Clock input (Port
                                                     A: P0.3) is selected (SSC1)., 0b1=Clock input (Port B:
                                                     P0.3) is selected (SSC1)., 0b0=Clock input (Port A: P1.0)
                                                     is selected (SSC2)., 0b1=Clock input (Port B: P1.0) is
                                                     selected (SSC2).,                                                         */
      __IOM uint16_t MIS_1      : 1;            /*!< [3..3] Master Mode Receiver Input Select: 0b0=see (SSC1)., 0b1=see
                                                     (SSC1)., 0b0=n/a (SSC2)., 0b1=n/a (SSC2).,                                */
    } bit;
  } PISEL;
  __IM  uint16_t  RESERVED;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000004) Control Register                                           */

    struct
    {
      __IM  uint16_t BC         : 4;            /*!< [3..0] Bit Count Field                                                    */
      __IM  uint16_t            : 4;
      __IM  uint16_t TE         : 1;            /*!< [8..8] Transmit Error Flag                                                */
      __IM  uint16_t RE         : 1;            /*!< [9..9] Receive Error Flag                                                 */
      __IM  uint16_t PE         : 1;            /*!< [10..10] Phase Error Flag                                                 */
      __IM  uint16_t BE         : 1;            /*!< [11..11] Baud Rate Error Flag                                             */
      __IM  uint16_t BSY        : 1;            /*!< [12..12] Busy Flag                                                        */
      __IM  uint16_t            : 1;
      __IOM uint16_t MS         : 1;            /*!< [14..14] Master Select Bit                                                */
      __IOM uint16_t EN         : 1;            /*!< [15..15] Enable Bit = 1                                                   */
    } bit;
  } CON;
  __IM  uint16_t  RESERVED1;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000008) Transmitter Buffer Register                                */

    struct
    {
      __IOM uint16_t TB_VALUE   : 16;           /*!< [15..0] Transmit Data Register Value                                      */
    } bit;
  } TB;
  __IM  uint16_t  RESERVED2;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x0000000C) Receiver Buffer Register                                   */

    struct
    {
      __IM  uint16_t RB_VALUE   : 16;           /*!< [15..0] Receive Data Register Value                                       */
    } bit;
  } RB;
  __IM  uint16_t  RESERVED3;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000010) Baud Rate Timer Reload Register                            */

    struct
    {
      __IOM uint16_t BR_VALUE   : 16;           /*!< [15..0] Baud Rate Timer/Reload Register Value                             */
    } bit;
  } BR;
  __IM  uint16_t  RESERVED4;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000014) Interrupt Status Register Clear                            */

    struct
    {
      __IM  uint16_t            : 8;
      __OM  uint16_t TECLR      : 1;            /*!< [8..8] Transmit Error Flag Clear                                          */
      __OM  uint16_t RECLR      : 1;            /*!< [9..9] Receive Error Flag Clear                                           */
      __OM  uint16_t PECLR      : 1;            /*!< [10..10] Phase Error Flag Clear                                           */
      __OM  uint16_t BECLR      : 1;            /*!< [11..11] Baud Rate Error Flag Clear                                       */
    } bit;
  } ISRCLR;
} SSC1_Type;                                    /*!< Size = 22 (0x16)                                                          */



/* =========================================================================================================================== */
/* ================                                           SSC2                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief SSC2 Module (SSC2)
  */

typedef struct                                  /*!< (@ 0x48026000) SSC2 Structure                                             */
{

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000000) Port Input Select Register, RESET_TYPE_3                   */

    struct
    {
      __IOM uint16_t MIS_0      : 1;            /*!< [0..0] Master Mode Receiver Input Select: 0b0=see (SSC1)., 0b1=see
                                                     (SSC1)., 0b0=Receiver input (Port A: P1.2) is selected
                                                     (SSC2)., 0b1=Receiver input (Port B: P2.5) is selected
                                                     (SSC2).,                                                                  */
      __IOM uint16_t SIS        : 1;            /*!< [1..1] Slave Mode Receiver Input Select: 0b0=Receiver input
                                                     (Port A: P0.2) is selected (SSC1)., 0b1=Receiver input
                                                     (Port B: P0.2) is selected (SSC1)., 0b0=Receiver input
                                                     (Port A: P1.1) is selected (SSC2)., 0b1=Receiver input
                                                     (Port B: P1.1) is selected (SSC2).,                                       */
      __IOM uint16_t CIS        : 1;            /*!< [2..2] Slave Mode Clock Input Select: 0b0=Clock input (Port
                                                     A: P0.3) is selected (SSC1)., 0b1=Clock input (Port B:
                                                     P0.3) is selected (SSC1)., 0b0=Clock input (Port A: P1.0)
                                                     is selected (SSC2)., 0b1=Clock input (Port B: P1.0) is
                                                     selected (SSC2).,                                                         */
      __IOM uint16_t MIS_1      : 1;            /*!< [3..3] Master Mode Receiver Input Select: 0b0=see (SSC1)., 0b1=see
                                                     (SSC1)., 0b0=n/a (SSC2)., 0b1=n/a (SSC2).,                                */
    } bit;
  } PISEL;
  __IM  uint16_t  RESERVED;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000004) Control Register                                           */

    struct
    {
      __IM  uint16_t BC         : 4;            /*!< [3..0] Bit Count Field                                                    */
      __IM  uint16_t            : 4;
      __IM  uint16_t TE         : 1;            /*!< [8..8] Transmit Error Flag                                                */
      __IM  uint16_t RE         : 1;            /*!< [9..9] Receive Error Flag                                                 */
      __IM  uint16_t PE         : 1;            /*!< [10..10] Phase Error Flag                                                 */
      __IM  uint16_t BE         : 1;            /*!< [11..11] Baud Rate Error Flag                                             */
      __IM  uint16_t BSY        : 1;            /*!< [12..12] Busy Flag                                                        */
      __IM  uint16_t            : 1;
      __IOM uint16_t MS         : 1;            /*!< [14..14] Master Select Bit                                                */
      __IOM uint16_t EN         : 1;            /*!< [15..15] Enable Bit = 1                                                   */
    } bit;
  } CON;
  __IM  uint16_t  RESERVED1;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000008) Transmitter Buffer Register                                */

    struct
    {
      __IOM uint16_t TB_VALUE   : 16;           /*!< [15..0] Transmit Data Register Value                                      */
    } bit;
  } TB;
  __IM  uint16_t  RESERVED2;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x0000000C) Receiver Buffer Register                                   */

    struct
    {
      __IM  uint16_t RB_VALUE   : 16;           /*!< [15..0] Receive Data Register Value                                       */
    } bit;
  } RB;
  __IM  uint16_t  RESERVED3;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000010) Baud Rate Timer Reload Register                            */

    struct
    {
      __IOM uint16_t BR_VALUE   : 16;           /*!< [15..0] Baud Rate Timer/Reload Register Value                             */
    } bit;
  } BR;
  __IM  uint16_t  RESERVED4;

  union
  {
    __IOM uint16_t reg;                         /*!< (@ 0x00000014) Interrupt Status Register Clear                            */

    struct
    {
      __IM  uint16_t            : 8;
      __OM  uint16_t TECLR      : 1;            /*!< [8..8] Transmit Error Flag Clear                                          */
      __OM  uint16_t RECLR      : 1;            /*!< [9..9] Receive Error Flag Clear                                           */
      __OM  uint16_t PECLR      : 1;            /*!< [10..10] Phase Error Flag Clear                                           */
      __OM  uint16_t BECLR      : 1;            /*!< [11..11] Baud Rate Error Flag Clear                                       */
    } bit;
  } ISRCLR;
} SSC2_Type;                                    /*!< Size = 22 (0x16)                                                          */



/* =========================================================================================================================== */
/* ================                                          TIMER2x                                          ================ */
/* =========================================================================================================================== */


/**
  * @brief TIMER2x Module (TIMER2x)
  */

typedef struct                                  /*!< (@ 0x48004000) TIMER2 Structure, (@ 0x48005000) TIMER21 Structure         */
{

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000000) Timer 2 Control Register                                   */

    struct
    {
      __IOM uint8_t CP_RL2      : 1;            /*!< [0..0] Capture/Reload Select                                              */
      __IOM uint8_t C_T2        : 1;            /*!< [1..1] Timer or Counter Select                                            */
      __IOM uint8_t TR2         : 1;            /*!< [2..2] Timer 2 Start/Stop Control                                         */
      __IOM uint8_t EXEN2       : 1;            /*!< [3..3] Timer 2 External Enable Control                                    */
      __IM  uint8_t             : 2;
      __IM  uint8_t EXF2        : 1;            /*!< [6..6] Timer 2 External Flag                                              */
      __IM  uint8_t TF2         : 1;            /*!< [7..7] Timer 2 Overflow/Underflow Flag                                    */
    } bit;
  } T2CON;
  __IM  uint8_t   RESERVED[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000004) Timer 2 Mode Register                                      */

    struct
    {
      __IOM uint8_t DCEN        : 1;            /*!< [0..0] Up/Down Counter Enable                                             */
      __IOM uint8_t T2PRE       : 3;            /*!< [3..1] Timer 2 Prescaler Bit                                              */
      __IOM uint8_t PREN        : 1;            /*!< [4..4] Prescaler Enable                                                   */
      __IOM uint8_t EDGESEL     : 1;            /*!< [5..5] Edge Select in Capture Mode/Reload Mode                            */
      __IOM uint8_t T2RHEN      : 1;            /*!< [6..6] Timer 2 External Start Enable                                      */
      __IOM uint8_t T2REGS      : 1;            /*!< [7..7] Edge Select for Timer 2 External Start                             */
    } bit;
  } T2MOD;
  __IM  uint8_t   RESERVED1[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000008) Timer 2 Reload/Capture Register, Low Byte                  */

    struct
    {
      __IOM uint8_t RC2         : 8;            /*!< [7..0] Reload/Capture Value                                               */
    } bit;
  } RC2L;
  __IM  uint8_t   RESERVED2[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x0000000C) Timer 2 Reload/Capture Register, High Byte                 */

    struct
    {
      __IOM uint8_t RC2         : 8;            /*!< [7..0] Reload/Capture Value                                               */
    } bit;
  } RC2H;
  __IM  uint8_t   RESERVED3[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000010) Timer 2, Low Byte                                          */

    struct
    {
      __IOM uint8_t T2L         : 8;            /*!< [7..0] Timer 2 Value                                                      */
    } bit;
  } T2L;
  __IM  uint8_t   RESERVED4[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000014) Timer 2, High Byte                                         */

    struct
    {
      __IOM uint8_t T2H         : 8;            /*!< [7..0] Timer 2 Value                                                      */
    } bit;
  } T2H;
  __IM  uint8_t   RESERVED5[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000018) Timer 2 Control Register 1                                 */

    struct
    {
      __IOM uint8_t EXF2EN      : 1;            /*!< [0..0] External Interrupt Enable                                          */
      __IOM uint8_t TF2EN       : 1;            /*!< [1..1] Overflow/Underflow Interrupt Enable                                */
    } bit;
  } T2CON1;
  __IM  uint8_t   RESERVED6[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x0000001C) Timer 2 Interrupt Clear Register                           */

    struct
    {
      __IM  uint8_t             : 6;
      __OM  uint8_t EXF2CLR     : 1;            /*!< [6..6] External Interrupt Clear Flag                                      */
      __OM  uint8_t TF2CLR      : 1;            /*!< [7..7] Overflow/Underflow Interrupt Clear Flag                            */
    } bit;
  } T2ICLR;
} TIMER2x_Type;                                 /*!< Size = 29 (0x1d)                                                          */



/* =========================================================================================================================== */
/* ================                                          TIMER3                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief TIMER3 Module (TIMER3)
  */

typedef struct                                  /*!< (@ 0x48006000) TIMER3 Structure                                           */
{

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) T3 Trigger Control                                         */

    struct
    {
      __IOM uint32_t T3_TRIGG_INP_SEL : 3;      /*!< [2..0] Timer 3 Trigger Input Event Selection (only in mode3b)             */
      __IM  uint32_t            : 1;
      __IOM uint32_t T3_RES_CONF : 2;           /*!< [5..4] Timer 3 Trigger Reset Selection for Mode 1b                        */
      __IOM uint32_t RETRIG     : 1;            /*!< [6..6] Retrigger Condition (in mode 1b) for CCU6-T12 ZM and
                                                     CCU6 PM                                                                   */
    } bit;
  } T3_TRIGG_CTRL;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) Timer 3 Compare Value                                      */

    struct
    {
      __IOM uint32_t LO         : 8;            /*!< [7..0] Timer 3 Compare Value Low Byte                                     */
      __IOM uint32_t HI         : 8;            /*!< [15..8] Timer 3 Compare Value High Byte                                   */
    } bit;
  } CMP;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) Timer 3                                                    */

    struct
    {
      __IOM uint32_t LO         : 8;            /*!< [7..0] Timer 3 Low Register or Preload Value                              */
      __IOM uint32_t HI         : 8;            /*!< [15..8] Timer 3 High Register or Preload Value                            */
    } bit;
  } CNT;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) Timer 3 Control Register                                   */

    struct
    {
      __IOM uint32_t T3_PD_N    : 1;            /*!< [0..0] Timer 3 Power Down                                                 */
      __IOM uint32_t T3_RD_REQ  : 1;            /*!< [1..1] Timer 3 Value Read Request                                         */
      __IOM uint32_t T3_RD_REQ_CONF : 1;        /*!< [2..2] Timer 3 Read Mode                                                  */
      __IOM uint32_t CNT_RDY    : 1;            /*!< [3..3] Timer 3 Count Ready                                                */
      __IOM uint32_t TR3H       : 1;            /*!< [4..4] Timer 3 Run Control (High Byte Timer)                              */
      __IM  uint32_t T3H_OVF_STS : 1;           /*!< [5..5] Timer 3 Overflow Flag (High Byte Timer)                            */
      __IOM uint32_t TR3L       : 1;            /*!< [6..6] Timer 3 Run Control (Low Byte Timer)                               */
      __IM  uint32_t T3L_OVF_STS : 1;           /*!< [7..7] Timer 3 Overflow Flag (Low Byte Timer)                             */
      __IOM uint32_t T3L_OVF_IE : 1;            /*!< [8..8] Timer 3 Overflow Interrupt Enable (Low Byte Timer)                 */
      __IOM uint32_t T3H_OVF_IE : 1;            /*!< [9..9] Timer 3 Overflow Interrupt Enable (High Byte Timer)                */
    } bit;
  } CTRL;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) Timer 3 Mode Configuration Register                        */

    struct
    {
      __IOM uint32_t T3M        : 2;            /*!< [1..0] Mode Select Bits                                                   */
      __IM  uint32_t            : 4;
      __IOM uint32_t T3_SUBM    : 2;            /*!< [7..6] Sub-Mode Select Bits                                               */
    } bit;
  } MODE_CONF;

  union
  {
    __IOM uint32_t reg;                         /*!< (@ 0x00000014) Timer 3 Interrupt Status Clear Register                    */

    struct
    {
      __IM  uint32_t            : 5;
      __OM  uint32_t T3H_OVF_ICLR : 1;          /*!< [5..5] Timer 3 Overflow Flag (High Byte Timer) Interrupt Clear            */
      __IM  uint32_t            : 1;
      __OM  uint32_t T3L_OVF_ICLR : 1;          /*!< [7..7] Timer 3 Overflow Flag (Low Byte Timer) Interrupt Clear             */
    } bit;
  } ISRCLR;
} TIMER3_Type;                                  /*!< Size = 24 (0x18)                                                          */



/* =========================================================================================================================== */
/* ================                                           UARTx                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief UARTx Module (UARTx)
  */

typedef struct                                  /*!< (@ 0x48020000) UART1 Structure, (@ 0x48022000) UART2 Structure            */
{

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000000) Serial Channel Control Register                            */

    struct
    {
      __IOM uint8_t RI          : 1;            /*!< [0..0] Receive Interrupt Flag                                             */
      __IOM uint8_t TI          : 1;            /*!< [1..1] Transmit Interrupt Flag                                            */
      __IOM uint8_t RB8         : 1;            /*!< [2..2] Serial Port Receiver Bit 9                                         */
      __IOM uint8_t TB8         : 1;            /*!< [3..3] Serial Port Transmitter Bit 9                                      */
      __IOM uint8_t REN         : 1;            /*!< [4..4] Enable Receiver of Serial Port                                     */
      __IOM uint8_t SM2         : 1;            /*!< [5..5] Enable Serial Port Multiprocessor Communication in Modes
                                                     2 and 3                                                                   */
      __IOM uint8_t SM1         : 1;            /*!< [6..6] Serial Port Operating Mode Selection                               */
      __IOM uint8_t SM0         : 1;            /*!< [7..7] Serial Port Operating Mode Selection                               */
    } bit;
  } SCON;
  __IM  uint8_t   RESERVED[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000004) Serial Data Buffer                                         */

    struct
    {
      __IOM uint8_t VAL         : 8;            /*!< [7..0] Serial Interface Buffer Register                                   */
    } bit;
  } SBUF;
  __IM  uint8_t   RESERVED1[3];

  union
  {
    __IOM uint8_t reg;                          /*!< (@ 0x00000008) Serial Channel Control Clear Register                      */

    struct
    {
      __OM  uint8_t RICLR       : 1;            /*!< [0..0] Receive Interrupt Clear Flag                                       */
      __OM  uint8_t TICLR       : 1;            /*!< [1..1] Transmit Interrupt Clear Flag                                      */
    } bit;
  } SCONCLR;
} UART_Type;                                    /*!< Size = 9 (0x9)                                                            */




/** @} */ /* End of group Device_Peripheral_peripherals */


/* =========================================================================================================================== */
/* ================                          Device Specific Peripheral Address Map                           ================ */
/* =========================================================================================================================== */


/** @addtogroup Device_Peripheral_peripheralAddr
  * @{
  */

#define ADC1_BASE                   0x40004000UL
#define ADC2_BASE                   0x4801C000UL
#define ADC34_BASE                  0x40008000UL
#define BDRV_BASE                   0x40034000UL
#define CCU6_BASE                   0x4000C000UL
#define CPU_BASE                    0xE000E000UL
#define CSA_BASE                    0x48018000UL
#define DMA_BASE                    0x50014000UL
#define GPT12E_BASE                 0x40010000UL
#define LIN_BASE                    0x4801E000UL
#define MF_BASE                     0x48018000UL
#define MON_BASE                    0x50004000UL
#define PMU_BASE                    0x50004000UL
#define PORT_BASE                   0x48028000UL
#define SCU_BASE                    0x50005000UL
#define SCUPM_BASE                  0x50006000UL
#define SSC1_BASE                   0x48024000UL
#define SSC2_BASE                   0x48026000UL
#define TIMER2_BASE                 0x48004000UL
#define TIMER21_BASE                0x48005000UL
#define TIMER3_BASE                 0x48006000UL
#define UART1_BASE                  0x48020000UL
#define UART2_BASE                  0x48022000UL

/** @} */ /* End of group Device_Peripheral_peripheralAddr */


/* =========================================================================================================================== */
/* ================                                  Peripheral declaration                                   ================ */
/* =========================================================================================================================== */


/** @addtogroup Device_Peripheral_declaration
  * @{
  */
/* Note 923: cast from unsigned long to pointer [MISRA Rule 45] */
/* disable lint warning 923, to accept the conversion of the    */
/* base address into a pointer of the peripheral type.          */
/* This is a preferable exception as it generates the fastest   */
/* code, compared to other solutions which do not require a     */
/* suppressing of this MISRA rule                               */


#ifndef UNIT_TESTING_LV2
#define ADC1    ((ADC1_Type*)    ADC1_BASE)
#define ADC2    ((ADC2_Type*)    ADC2_BASE)
#define ADC34   ((ADC34_Type*)   ADC34_BASE)
#define BDRV    ((BDRV_Type*)    BDRV_BASE)
#define CCU6    ((CCU6_Type*)    CCU6_BASE)
#define CSA     ((CSA_Type*)     CSA_BASE)
#define CPU     ((CPU_Type*)     CPU_BASE)
#define DMA     ((DMA_Type*)     DMA_BASE)
#define GPT12E  ((GPT12E_Type*)  GPT12E_BASE)
#define LIN     ((LIN_Type*)     LIN_BASE)
#define MF      ((MF_Type*)      MF_BASE)
#define MON     ((MON_Type*)     MON_BASE)
#define PMU     ((PMU_Type*)     PMU_BASE)
#define PORT    ((PORT_Type*)    PORT_BASE)
#define SCU     ((SCU_Type*)     SCU_BASE)
#define SCUPM   ((SCUPM_Type*)   SCUPM_BASE)
#define SSC1    ((SSC1_Type*)    SSC1_BASE)
#define SSC2    ((SSC2_Type*)    SSC2_BASE)
#define TIMER2  ((TIMER2x_Type*) TIMER2_BASE)
#define TIMER21 ((TIMER2x_Type*) TIMER21_BASE)
#define TIMER3  ((TIMER3_Type*)  TIMER3_BASE)
#define UART1   ((UART_Type*)    UART1_BASE)
#define UART2   ((UART_Type*)    UART2_BASE)
#else
extern ADC1_Type   *ADC1;
extern ADC2_Type   *ADC2;
extern ADC34_Type  *ADC34;
extern BDRV_Type   *BDRV;
extern CCU6_Type   *CCU6;
extern CSA_Type    *CSA;
extern CPU_Type    *CPU;
extern DMA_Type    *DMA;
extern GPT12E_Type  *GPT12E;
extern LIN_Type    *LIN;
extern MF_Type     *MF;
extern MON_Type    *MON;
extern PMU_Type    *PMU;
extern PORT_Type   *PORT;
extern SCU_Type    *SCU;
extern SCUPM_Type  *SCUPM;
extern SSC1_Type   *SSC1;
extern SSC2_Type   *SSC2;
extern TIMER2x_Type  *TIMER2;
extern TIMER2x_Type  *TIMER21;
extern TIMER3_Type   *TIMER3;
extern UART_Type     *UART1;
extern UART_Type     *UART2;
#endif /* UNIT_TESTING_LV2 */



/** @} */ /* End of group Device_Peripheral_declaration */


/* =========================================================================================================================== */
/* ================                                Pos/Mask Peripheral Section                                ================ */
/* =========================================================================================================================== */


/** @addtogroup PosMask_peripherals
  * @{
  */


/* violation: Identifier clash */
/* =========================================================================================================================== */
/* ================                                           ADC1                                            ================ */
/* =========================================================================================================================== */

/* ========================================================  CHx_EIM  ======================================================== */
#define ADC1_CHx_EIM_TRIG_SEL_Pos         (16UL)                    /*!< ADC1 CHx_EIM: TRIG_SEL (Bit 16)                       */
#define ADC1_CHx_EIM_TRIG_SEL_Msk         (0x70000UL)               /*!< ADC1 CHx_EIM: TRIG_SEL (Bitfield-Mask: 0x07)          */
#define ADC1_CHx_EIM_REP_Pos              (4UL)                     /*!< ADC1 CHx_EIM: REP (Bit 4)                             */
#define ADC1_CHx_EIM_REP_Msk              (0x70UL)                  /*!< ADC1 CHx_EIM: REP (Bitfield-Mask: 0x07)               */
#define ADC1_CHx_EIM_CHx_Pos              (0UL)                     /*!< ADC1 CHx_EIM: CHx (Bit 0)                             */
#define ADC1_CHx_EIM_CHx_Msk              (0x7UL)                   /*!< ADC1 CHx_EIM: CHx (Bitfield-Mask: 0x07)               */
/* ========================================================  CHx_ESM  ======================================================== */
#define ADC1_CHx_ESM_TRIG_SEL_Pos         (16UL)                    /*!< ADC1 CHx_ESM: TRIG_SEL (Bit 16)                       */
#define ADC1_CHx_ESM_TRIG_SEL_Msk         (0x70000UL)               /*!< ADC1 CHx_ESM: TRIG_SEL (Bitfield-Mask: 0x07)          */
#define ADC1_CHx_ESM_ESM_0_Pos            (0UL)                     /*!< ADC1 CHx_ESM: ESM_0 (Bit 0)                           */
#define ADC1_CHx_ESM_ESM_0_Msk            (0xffUL)                  /*!< ADC1 CHx_ESM: ESM_0 (Bitfield-Mask: 0xff)             */
/* =======================================================  CTRL_STS  ======================================================== */
#define ADC1_CTRL_STS_IN_MUX_SEL_Pos      (4UL)                     /*!< ADC1 CTRL_STS: IN_MUX_SEL (Bit 4)                     */
#define ADC1_CTRL_STS_IN_MUX_SEL_Msk      (0x70UL)                  /*!< ADC1 CTRL_STS: IN_MUX_SEL (Bitfield-Mask: 0x07)       */
#define ADC1_CTRL_STS_EOC_Pos             (3UL)                     /*!< ADC1 CTRL_STS: EOC (Bit 3)                            */
#define ADC1_CTRL_STS_EOC_Msk             (0x8UL)                   /*!< ADC1 CTRL_STS: EOC (Bitfield-Mask: 0x01)              */
#define ADC1_CTRL_STS_SOC_Pos             (2UL)                     /*!< ADC1 CTRL_STS: SOC (Bit 2)                            */
#define ADC1_CTRL_STS_SOC_Msk             (0x4UL)                   /*!< ADC1 CTRL_STS: SOC (Bitfield-Mask: 0x01)              */
#define ADC1_CTRL_STS_PD_N_Pos            (0UL)                     /*!< ADC1 CTRL_STS: PD_N (Bit 0)                           */
#define ADC1_CTRL_STS_PD_N_Msk            (0x1UL)                   /*!< ADC1 CTRL_STS: PD_N (Bitfield-Mask: 0x01)             */
/* =========================================================  DWSEL  ========================================================= */
#define ADC1_DWSEL_ch7_Pos                (7UL)                     /*!< ADC1 DWSEL: ch7 (Bit 7)                               */
#define ADC1_DWSEL_ch7_Msk                (0x80UL)                  /*!< ADC1 DWSEL: ch7 (Bitfield-Mask: 0x01)                 */
#define ADC1_DWSEL_ch6_Pos                (6UL)                     /*!< ADC1 DWSEL: ch6 (Bit 6)                               */
#define ADC1_DWSEL_ch6_Msk                (0x40UL)                  /*!< ADC1 DWSEL: ch6 (Bitfield-Mask: 0x01)                 */
#define ADC1_DWSEL_ch5_Pos                (5UL)                     /*!< ADC1 DWSEL: ch5 (Bit 5)                               */
#define ADC1_DWSEL_ch5_Msk                (0x20UL)                  /*!< ADC1 DWSEL: ch5 (Bitfield-Mask: 0x01)                 */
#define ADC1_DWSEL_ch4_Pos                (4UL)                     /*!< ADC1 DWSEL: ch4 (Bit 4)                               */
#define ADC1_DWSEL_ch4_Msk                (0x10UL)                  /*!< ADC1 DWSEL: ch4 (Bitfield-Mask: 0x01)                 */
#define ADC1_DWSEL_ch3_Pos                (3UL)                     /*!< ADC1 DWSEL: ch3 (Bit 3)                               */
#define ADC1_DWSEL_ch3_Msk                (0x8UL)                   /*!< ADC1 DWSEL: ch3 (Bitfield-Mask: 0x01)                 */
#define ADC1_DWSEL_ch2_Pos                (2UL)                     /*!< ADC1 DWSEL: ch2 (Bit 2)                               */
#define ADC1_DWSEL_ch2_Msk                (0x4UL)                   /*!< ADC1 DWSEL: ch2 (Bitfield-Mask: 0x01)                 */
#define ADC1_DWSEL_ch1_Pos                (1UL)                     /*!< ADC1 DWSEL: ch1 (Bit 1)                               */
#define ADC1_DWSEL_ch1_Msk                (0x2UL)                   /*!< ADC1 DWSEL: ch1 (Bitfield-Mask: 0x01)                 */
#define ADC1_DWSEL_ch0_Pos                (0UL)                     /*!< ADC1 DWSEL: ch0 (Bit 0)                               */
#define ADC1_DWSEL_ch0_Msk                (0x1UL)                   /*!< ADC1 DWSEL: ch0 (Bitfield-Mask: 0x01)                 */
/* ========================================================  GLOBCTR  ======================================================== */
#define ADC1_GLOBCTR_ANON_Pos             (8UL)                     /*!< ADC1 GLOBCTR: ANON (Bit 8)                            */
#define ADC1_GLOBCTR_ANON_Msk             (0x300UL)                 /*!< ADC1 GLOBCTR: ANON (Bitfield-Mask: 0x03)              */
#define ADC1_GLOBCTR_DIVA_Pos             (0UL)                     /*!< ADC1 GLOBCTR: DIVA (Bit 0)                            */
#define ADC1_GLOBCTR_DIVA_Msk             (0x3fUL)                  /*!< ADC1 GLOBCTR: DIVA (Bitfield-Mask: 0x3f)              */
/* ========================================================  GLOBSTR  ======================================================== */
#define ADC1_GLOBSTR_ANON_ST_Pos          (8UL)                     /*!< ADC1 GLOBSTR: ANON_ST (Bit 8)                         */
#define ADC1_GLOBSTR_ANON_ST_Msk          (0x300UL)                 /*!< ADC1 GLOBSTR: ANON_ST (Bitfield-Mask: 0x03)           */
#define ADC1_GLOBSTR_CHNR_Pos             (3UL)                     /*!< ADC1 GLOBSTR: CHNR (Bit 3)                            */
#define ADC1_GLOBSTR_CHNR_Msk             (0x38UL)                  /*!< ADC1 GLOBSTR: CHNR (Bitfield-Mask: 0x07)              */
#define ADC1_GLOBSTR_SAMPLE_Pos           (1UL)                     /*!< ADC1 GLOBSTR: SAMPLE (Bit 1)                          */
#define ADC1_GLOBSTR_SAMPLE_Msk           (0x2UL)                   /*!< ADC1 GLOBSTR: SAMPLE (Bitfield-Mask: 0x01)            */
#define ADC1_GLOBSTR_BUSY_Pos             (0UL)                     /*!< ADC1 GLOBSTR: BUSY (Bit 0)                            */
#define ADC1_GLOBSTR_BUSY_Msk             (0x1UL)                   /*!< ADC1 GLOBSTR: BUSY (Bitfield-Mask: 0x01)              */
/* =========================================================  ICLR  ========================================================== */
#define ADC1_ICLR_ESM_ICLR_Pos            (9UL)                     /*!< ADC1 ICLR: ESM_ICLR (Bit 9)                           */
#define ADC1_ICLR_ESM_ICLR_Msk            (0x200UL)                 /*!< ADC1 ICLR: ESM_ICLR (Bitfield-Mask: 0x01)             */
#define ADC1_ICLR_EIM_ICLR_Pos            (8UL)                     /*!< ADC1 ICLR: EIM_ICLR (Bit 8)                           */
#define ADC1_ICLR_EIM_ICLR_Msk            (0x100UL)                 /*!< ADC1 ICLR: EIM_ICLR (Bitfield-Mask: 0x01)             */
#define ADC1_ICLR_CH7_ICLR_Pos            (7UL)                     /*!< ADC1 ICLR: CH7_ICLR (Bit 7)                           */
#define ADC1_ICLR_CH7_ICLR_Msk            (0x80UL)                  /*!< ADC1 ICLR: CH7_ICLR (Bitfield-Mask: 0x01)             */
#define ADC1_ICLR_CH6_ICLR_Pos            (6UL)                     /*!< ADC1 ICLR: CH6_ICLR (Bit 6)                           */
#define ADC1_ICLR_CH6_ICLR_Msk            (0x40UL)                  /*!< ADC1 ICLR: CH6_ICLR (Bitfield-Mask: 0x01)             */
#define ADC1_ICLR_CH5_ICLR_Pos            (5UL)                     /*!< ADC1 ICLR: CH5_ICLR (Bit 5)                           */
#define ADC1_ICLR_CH5_ICLR_Msk            (0x20UL)                  /*!< ADC1 ICLR: CH5_ICLR (Bitfield-Mask: 0x01)             */
#define ADC1_ICLR_CH4_ICLR_Pos            (4UL)                     /*!< ADC1 ICLR: CH4_ICLR (Bit 4)                           */
#define ADC1_ICLR_CH4_ICLR_Msk            (0x10UL)                  /*!< ADC1 ICLR: CH4_ICLR (Bitfield-Mask: 0x01)             */
#define ADC1_ICLR_CH3_ICLR_Pos            (3UL)                     /*!< ADC1 ICLR: CH3_ICLR (Bit 3)                           */
#define ADC1_ICLR_CH3_ICLR_Msk            (0x8UL)                   /*!< ADC1 ICLR: CH3_ICLR (Bitfield-Mask: 0x01)             */
#define ADC1_ICLR_CH2_ICLR_Pos            (2UL)                     /*!< ADC1 ICLR: CH2_ICLR (Bit 2)                           */
#define ADC1_ICLR_CH2_ICLR_Msk            (0x4UL)                   /*!< ADC1 ICLR: CH2_ICLR (Bitfield-Mask: 0x01)             */
#define ADC1_ICLR_CH1_ICLR_Pos            (1UL)                     /*!< ADC1 ICLR: CH1_ICLR (Bit 1)                           */
#define ADC1_ICLR_CH1_ICLR_Msk            (0x2UL)                   /*!< ADC1 ICLR: CH1_ICLR (Bitfield-Mask: 0x01)             */
#define ADC1_ICLR_CH0_ICLR_Pos            (0UL)                     /*!< ADC1 ICLR: CH0_ICLR (Bit 0)                           */
#define ADC1_ICLR_CH0_ICLR_Msk            (0x1UL)                   /*!< ADC1 ICLR: CH0_ICLR (Bitfield-Mask: 0x01)             */
/* ==========================================================  IE  =========================================================== */
#define ADC1_IE_ESM_IE_Pos                (9UL)                     /*!< ADC1 IE: ESM_IE (Bit 9)                               */
#define ADC1_IE_ESM_IE_Msk                (0x200UL)                 /*!< ADC1 IE: ESM_IE (Bitfield-Mask: 0x01)                 */
#define ADC1_IE_EIM_IE_Pos                (8UL)                     /*!< ADC1 IE: EIM_IE (Bit 8)                               */
#define ADC1_IE_EIM_IE_Msk                (0x100UL)                 /*!< ADC1 IE: EIM_IE (Bitfield-Mask: 0x01)                 */
#define ADC1_IE_CH7_IE_Pos                (7UL)                     /*!< ADC1 IE: CH7_IE (Bit 7)                               */
#define ADC1_IE_CH7_IE_Msk                (0x80UL)                  /*!< ADC1 IE: CH7_IE (Bitfield-Mask: 0x01)                 */
#define ADC1_IE_CH6_IE_Pos                (6UL)                     /*!< ADC1 IE: CH6_IE (Bit 6)                               */
#define ADC1_IE_CH6_IE_Msk                (0x40UL)                  /*!< ADC1 IE: CH6_IE (Bitfield-Mask: 0x01)                 */
#define ADC1_IE_CH5_IE_Pos                (5UL)                     /*!< ADC1 IE: CH5_IE (Bit 5)                               */
#define ADC1_IE_CH5_IE_Msk                (0x20UL)                  /*!< ADC1 IE: CH5_IE (Bitfield-Mask: 0x01)                 */
#define ADC1_IE_CH4_IE_Pos                (4UL)                     /*!< ADC1 IE: CH4_IE (Bit 4)                               */
#define ADC1_IE_CH4_IE_Msk                (0x10UL)                  /*!< ADC1 IE: CH4_IE (Bitfield-Mask: 0x01)                 */
#define ADC1_IE_CH3_IE_Pos                (3UL)                     /*!< ADC1 IE: CH3_IE (Bit 3)                               */
#define ADC1_IE_CH3_IE_Msk                (0x8UL)                   /*!< ADC1 IE: CH3_IE (Bitfield-Mask: 0x01)                 */
#define ADC1_IE_CH2_IE_Pos                (2UL)                     /*!< ADC1 IE: CH2_IE (Bit 2)                               */
#define ADC1_IE_CH2_IE_Msk                (0x4UL)                   /*!< ADC1 IE: CH2_IE (Bitfield-Mask: 0x01)                 */
#define ADC1_IE_CH1_IE_Pos                (1UL)                     /*!< ADC1 IE: CH1_IE (Bit 1)                               */
#define ADC1_IE_CH1_IE_Msk                (0x2UL)                   /*!< ADC1 IE: CH1_IE (Bitfield-Mask: 0x01)                 */
#define ADC1_IE_CH0_IE_Pos                (0UL)                     /*!< ADC1 IE: CH0_IE (Bit 0)                               */
#define ADC1_IE_CH0_IE_Msk                (0x1UL)                   /*!< ADC1 IE: CH0_IE (Bitfield-Mask: 0x01)                 */
/* ==========================================================  IS  =========================================================== */
#define ADC1_IS_ESM_STS_Pos               (9UL)                     /*!< ADC1 IS: ESM_STS (Bit 9)                              */
#define ADC1_IS_ESM_STS_Msk               (0x200UL)                 /*!< ADC1 IS: ESM_STS (Bitfield-Mask: 0x01)                */
#define ADC1_IS_EIM_STS_Pos               (8UL)                     /*!< ADC1 IS: EIM_STS (Bit 8)                              */
#define ADC1_IS_EIM_STS_Msk               (0x100UL)                 /*!< ADC1 IS: EIM_STS (Bitfield-Mask: 0x01)                */
#define ADC1_IS_CH7_STS_Pos               (7UL)                     /*!< ADC1 IS: CH7_STS (Bit 7)                              */
#define ADC1_IS_CH7_STS_Msk               (0x80UL)                  /*!< ADC1 IS: CH7_STS (Bitfield-Mask: 0x01)                */
#define ADC1_IS_CH6_STS_Pos               (6UL)                     /*!< ADC1 IS: CH6_STS (Bit 6)                              */
#define ADC1_IS_CH6_STS_Msk               (0x40UL)                  /*!< ADC1 IS: CH6_STS (Bitfield-Mask: 0x01)                */
#define ADC1_IS_CH5_STS_Pos               (5UL)                     /*!< ADC1 IS: CH5_STS (Bit 5)                              */
#define ADC1_IS_CH5_STS_Msk               (0x20UL)                  /*!< ADC1 IS: CH5_STS (Bitfield-Mask: 0x01)                */
#define ADC1_IS_CH4_STS_Pos               (4UL)                     /*!< ADC1 IS: CH4_STS (Bit 4)                              */
#define ADC1_IS_CH4_STS_Msk               (0x10UL)                  /*!< ADC1 IS: CH4_STS (Bitfield-Mask: 0x01)                */
#define ADC1_IS_CH3_STS_Pos               (3UL)                     /*!< ADC1 IS: CH3_STS (Bit 3)                              */
#define ADC1_IS_CH3_STS_Msk               (0x8UL)                   /*!< ADC1 IS: CH3_STS (Bitfield-Mask: 0x01)                */
#define ADC1_IS_CH2_STS_Pos               (2UL)                     /*!< ADC1 IS: CH2_STS (Bit 2)                              */
#define ADC1_IS_CH2_STS_Msk               (0x4UL)                   /*!< ADC1 IS: CH2_STS (Bitfield-Mask: 0x01)                */
#define ADC1_IS_CH1_STS_Pos               (1UL)                     /*!< ADC1 IS: CH1_STS (Bit 1)                              */
#define ADC1_IS_CH1_STS_Msk               (0x2UL)                   /*!< ADC1 IS: CH1_STS (Bitfield-Mask: 0x01)                */
#define ADC1_IS_CH0_STS_Pos               (0UL)                     /*!< ADC1 IS: CH0_STS (Bit 0)                              */
#define ADC1_IS_CH0_STS_Msk               (0x1UL)                   /*!< ADC1 IS: CH0_STS (Bitfield-Mask: 0x01)                */
/* =======================================================  RES_OUT0  ======================================================== */
#define ADC1_RES_OUT0_OF0_Pos             (18UL)                    /*!< ADC1 RES_OUT0: OF0 (Bit 18)                           */
#define ADC1_RES_OUT0_OF0_Msk             (0x40000UL)               /*!< ADC1 RES_OUT0: OF0 (Bitfield-Mask: 0x01)              */
#define ADC1_RES_OUT0_VF0_Pos             (17UL)                    /*!< ADC1 RES_OUT0: VF0 (Bit 17)                           */
#define ADC1_RES_OUT0_VF0_Msk             (0x20000UL)               /*!< ADC1 RES_OUT0: VF0 (Bitfield-Mask: 0x01)              */
#define ADC1_RES_OUT0_WFR0_Pos            (16UL)                    /*!< ADC1 RES_OUT0: WFR0 (Bit 16)                          */
#define ADC1_RES_OUT0_WFR0_Msk            (0x10000UL)               /*!< ADC1 RES_OUT0: WFR0 (Bitfield-Mask: 0x01)             */
#define ADC1_RES_OUT0_OUT_CH0_Pos         (0UL)                     /*!< ADC1 RES_OUT0: OUT_CH0 (Bit 0)                        */
#define ADC1_RES_OUT0_OUT_CH0_Msk         (0xfffUL)                 /*!< ADC1 RES_OUT0: OUT_CH0 (Bitfield-Mask: 0xfff)         */
/* =======================================================  RES_OUT1  ======================================================== */
#define ADC1_RES_OUT1_OF1_Pos             (18UL)                    /*!< ADC1 RES_OUT1: OF1 (Bit 18)                           */
#define ADC1_RES_OUT1_OF1_Msk             (0x40000UL)               /*!< ADC1 RES_OUT1: OF1 (Bitfield-Mask: 0x01)              */
#define ADC1_RES_OUT1_VF1_Pos             (17UL)                    /*!< ADC1 RES_OUT1: VF1 (Bit 17)                           */
#define ADC1_RES_OUT1_VF1_Msk             (0x20000UL)               /*!< ADC1 RES_OUT1: VF1 (Bitfield-Mask: 0x01)              */
#define ADC1_RES_OUT1_WFR1_Pos            (16UL)                    /*!< ADC1 RES_OUT1: WFR1 (Bit 16)                          */
#define ADC1_RES_OUT1_WFR1_Msk            (0x10000UL)               /*!< ADC1 RES_OUT1: WFR1 (Bitfield-Mask: 0x01)             */
#define ADC1_RES_OUT1_OUT_CH1_Pos         (0UL)                     /*!< ADC1 RES_OUT1: OUT_CH1 (Bit 0)                        */
#define ADC1_RES_OUT1_OUT_CH1_Msk         (0xfffUL)                 /*!< ADC1 RES_OUT1: OUT_CH1 (Bitfield-Mask: 0xfff)         */
/* =======================================================  RES_OUT2  ======================================================== */
#define ADC1_RES_OUT2_OF2_Pos             (18UL)                    /*!< ADC1 RES_OUT2: OF2 (Bit 18)                           */
#define ADC1_RES_OUT2_OF2_Msk             (0x40000UL)               /*!< ADC1 RES_OUT2: OF2 (Bitfield-Mask: 0x01)              */
#define ADC1_RES_OUT2_VF2_Pos             (17UL)                    /*!< ADC1 RES_OUT2: VF2 (Bit 17)                           */
#define ADC1_RES_OUT2_VF2_Msk             (0x20000UL)               /*!< ADC1 RES_OUT2: VF2 (Bitfield-Mask: 0x01)              */
#define ADC1_RES_OUT2_WFR2_Pos            (16UL)                    /*!< ADC1 RES_OUT2: WFR2 (Bit 16)                          */
#define ADC1_RES_OUT2_WFR2_Msk            (0x10000UL)               /*!< ADC1 RES_OUT2: WFR2 (Bitfield-Mask: 0x01)             */
#define ADC1_RES_OUT2_OUT_CH2_Pos         (0UL)                     /*!< ADC1 RES_OUT2: OUT_CH2 (Bit 0)                        */
#define ADC1_RES_OUT2_OUT_CH2_Msk         (0xfffUL)                 /*!< ADC1 RES_OUT2: OUT_CH2 (Bitfield-Mask: 0xfff)         */
/* =======================================================  RES_OUT3  ======================================================== */
#define ADC1_RES_OUT3_OF3_Pos             (18UL)                    /*!< ADC1 RES_OUT3: OF3 (Bit 18)                           */
#define ADC1_RES_OUT3_OF3_Msk             (0x40000UL)               /*!< ADC1 RES_OUT3: OF3 (Bitfield-Mask: 0x01)              */
#define ADC1_RES_OUT3_VF3_Pos             (17UL)                    /*!< ADC1 RES_OUT3: VF3 (Bit 17)                           */
#define ADC1_RES_OUT3_VF3_Msk             (0x20000UL)               /*!< ADC1 RES_OUT3: VF3 (Bitfield-Mask: 0x01)              */
#define ADC1_RES_OUT3_WFR3_Pos            (16UL)                    /*!< ADC1 RES_OUT3: WFR3 (Bit 16)                          */
#define ADC1_RES_OUT3_WFR3_Msk            (0x10000UL)               /*!< ADC1 RES_OUT3: WFR3 (Bitfield-Mask: 0x01)             */
#define ADC1_RES_OUT3_OUT_CH3_Pos         (0UL)                     /*!< ADC1 RES_OUT3: OUT_CH3 (Bit 0)                        */
#define ADC1_RES_OUT3_OUT_CH3_Msk         (0xfffUL)                 /*!< ADC1 RES_OUT3: OUT_CH3 (Bitfield-Mask: 0xfff)         */
/* =======================================================  RES_OUT4  ======================================================== */
#define ADC1_RES_OUT4_OF4_Pos             (18UL)                    /*!< ADC1 RES_OUT4: OF4 (Bit 18)                           */
#define ADC1_RES_OUT4_OF4_Msk             (0x40000UL)               /*!< ADC1 RES_OUT4: OF4 (Bitfield-Mask: 0x01)              */
#define ADC1_RES_OUT4_VF4_Pos             (17UL)                    /*!< ADC1 RES_OUT4: VF4 (Bit 17)                           */
#define ADC1_RES_OUT4_VF4_Msk             (0x20000UL)               /*!< ADC1 RES_OUT4: VF4 (Bitfield-Mask: 0x01)              */
#define ADC1_RES_OUT4_WFR4_Pos            (16UL)                    /*!< ADC1 RES_OUT4: WFR4 (Bit 16)                          */
#define ADC1_RES_OUT4_WFR4_Msk            (0x10000UL)               /*!< ADC1 RES_OUT4: WFR4 (Bitfield-Mask: 0x01)             */
#define ADC1_RES_OUT4_OUT_CH4_Pos         (0UL)                     /*!< ADC1 RES_OUT4: OUT_CH4 (Bit 0)                        */
#define ADC1_RES_OUT4_OUT_CH4_Msk         (0xfffUL)                 /*!< ADC1 RES_OUT4: OUT_CH4 (Bitfield-Mask: 0xfff)         */
/* =======================================================  RES_OUT5  ======================================================== */
#define ADC1_RES_OUT5_OF5_Pos             (18UL)                    /*!< ADC1 RES_OUT5: OF5 (Bit 18)                           */
#define ADC1_RES_OUT5_OF5_Msk             (0x40000UL)               /*!< ADC1 RES_OUT5: OF5 (Bitfield-Mask: 0x01)              */
#define ADC1_RES_OUT5_VF5_Pos             (17UL)                    /*!< ADC1 RES_OUT5: VF5 (Bit 17)                           */
#define ADC1_RES_OUT5_VF5_Msk             (0x20000UL)               /*!< ADC1 RES_OUT5: VF5 (Bitfield-Mask: 0x01)              */
#define ADC1_RES_OUT5_WFR5_Pos            (16UL)                    /*!< ADC1 RES_OUT5: WFR5 (Bit 16)                          */
#define ADC1_RES_OUT5_WFR5_Msk            (0x10000UL)               /*!< ADC1 RES_OUT5: WFR5 (Bitfield-Mask: 0x01)             */
#define ADC1_RES_OUT5_OUT_CH5_Pos         (0UL)                     /*!< ADC1 RES_OUT5: OUT_CH5 (Bit 0)                        */
#define ADC1_RES_OUT5_OUT_CH5_Msk         (0xfffUL)                 /*!< ADC1 RES_OUT5: OUT_CH5 (Bitfield-Mask: 0xfff)         */
/* =======================================================  RES_OUT6  ======================================================== */
#define ADC1_RES_OUT6_OF6_Pos             (18UL)                    /*!< ADC1 RES_OUT6: OF6 (Bit 18)                           */
#define ADC1_RES_OUT6_OF6_Msk             (0x40000UL)               /*!< ADC1 RES_OUT6: OF6 (Bitfield-Mask: 0x01)              */
#define ADC1_RES_OUT6_VF6_Pos             (17UL)                    /*!< ADC1 RES_OUT6: VF6 (Bit 17)                           */
#define ADC1_RES_OUT6_VF6_Msk             (0x20000UL)               /*!< ADC1 RES_OUT6: VF6 (Bitfield-Mask: 0x01)              */
#define ADC1_RES_OUT6_WFR6_Pos            (16UL)                    /*!< ADC1 RES_OUT6: WFR6 (Bit 16)                          */
#define ADC1_RES_OUT6_WFR6_Msk            (0x10000UL)               /*!< ADC1 RES_OUT6: WFR6 (Bitfield-Mask: 0x01)             */
#define ADC1_RES_OUT6_OUT_CH6_Pos         (0UL)                     /*!< ADC1 RES_OUT6: OUT_CH6 (Bit 0)                        */
#define ADC1_RES_OUT6_OUT_CH6_Msk         (0xfffUL)                 /*!< ADC1 RES_OUT6: OUT_CH6 (Bitfield-Mask: 0xfff)         */
/* =======================================================  RES_OUT7  ======================================================== */
#define ADC1_RES_OUT7_OF7_Pos             (18UL)                    /*!< ADC1 RES_OUT7: OF7 (Bit 18)                           */
#define ADC1_RES_OUT7_OF7_Msk             (0x40000UL)               /*!< ADC1 RES_OUT7: OF7 (Bitfield-Mask: 0x01)              */
#define ADC1_RES_OUT7_VF7_Pos             (17UL)                    /*!< ADC1 RES_OUT7: VF7 (Bit 17)                           */
#define ADC1_RES_OUT7_VF7_Msk             (0x20000UL)               /*!< ADC1 RES_OUT7: VF7 (Bitfield-Mask: 0x01)              */
#define ADC1_RES_OUT7_WFR7_Pos            (16UL)                    /*!< ADC1 RES_OUT7: WFR7 (Bit 16)                          */
#define ADC1_RES_OUT7_WFR7_Msk            (0x10000UL)               /*!< ADC1 RES_OUT7: WFR7 (Bitfield-Mask: 0x01)             */
#define ADC1_RES_OUT7_OUT_CH7_Pos         (0UL)                     /*!< ADC1 RES_OUT7: OUT_CH7 (Bit 0)                        */
#define ADC1_RES_OUT7_OUT_CH7_Msk         (0xfffUL)                 /*!< ADC1 RES_OUT7: OUT_CH7 (Bitfield-Mask: 0xfff)         */
/* ======================================================  RES_OUT_EIM  ====================================================== */
#define ADC1_RES_OUT_EIM_OF8_Pos          (18UL)                    /*!< ADC1 RES_OUT_EIM: OF8 (Bit 18)                        */
#define ADC1_RES_OUT_EIM_OF8_Msk          (0x40000UL)               /*!< ADC1 RES_OUT_EIM: OF8 (Bitfield-Mask: 0x01)           */
#define ADC1_RES_OUT_EIM_VF8_Pos          (17UL)                    /*!< ADC1 RES_OUT_EIM: VF8 (Bit 17)                        */
#define ADC1_RES_OUT_EIM_VF8_Msk          (0x20000UL)               /*!< ADC1 RES_OUT_EIM: VF8 (Bitfield-Mask: 0x01)           */
#define ADC1_RES_OUT_EIM_WFR8_Pos         (16UL)                    /*!< ADC1 RES_OUT_EIM: WFR8 (Bit 16)                       */
#define ADC1_RES_OUT_EIM_WFR8_Msk         (0x10000UL)               /*!< ADC1 RES_OUT_EIM: WFR8 (Bitfield-Mask: 0x01)          */
#define ADC1_RES_OUT_EIM_OUT_CH_EIM_Pos   (0UL)                     /*!< ADC1 RES_OUT_EIM: OUT_CH_EIM (Bit 0)                  */
#define ADC1_RES_OUT_EIM_OUT_CH_EIM_Msk   (0xfffUL)                 /*!< ADC1 RES_OUT_EIM: OUT_CH_EIM (Bitfield-Mask: 0xfff)   */
/* =========================================================  SQ1_4  ========================================================= */
#define ADC1_SQ1_4_SQ4_Pos                (24UL)                    /*!< ADC1 SQ1_4: SQ4 (Bit 24)                              */
#define ADC1_SQ1_4_SQ4_Msk                (0xff000000UL)            /*!< ADC1 SQ1_4: SQ4 (Bitfield-Mask: 0xff)                 */
#define ADC1_SQ1_4_SQ3_Pos                (16UL)                    /*!< ADC1 SQ1_4: SQ3 (Bit 16)                              */
#define ADC1_SQ1_4_SQ3_Msk                (0xff0000UL)              /*!< ADC1 SQ1_4: SQ3 (Bitfield-Mask: 0xff)                 */
#define ADC1_SQ1_4_SQ2_Pos                (8UL)                     /*!< ADC1 SQ1_4: SQ2 (Bit 8)                               */
#define ADC1_SQ1_4_SQ2_Msk                (0xff00UL)                /*!< ADC1 SQ1_4: SQ2 (Bitfield-Mask: 0xff)                 */
#define ADC1_SQ1_4_SQ1_Pos                (0UL)                     /*!< ADC1 SQ1_4: SQ1 (Bit 0)                               */
#define ADC1_SQ1_4_SQ1_Msk                (0xffUL)                  /*!< ADC1 SQ1_4: SQ1 (Bitfield-Mask: 0xff)                 */
/* =========================================================  SQ5_8  ========================================================= */
#define ADC1_SQ5_8_SQ8_Pos                (24UL)                    /*!< ADC1 SQ5_8: SQ8 (Bit 24)                              */
#define ADC1_SQ5_8_SQ8_Msk                (0xff000000UL)            /*!< ADC1 SQ5_8: SQ8 (Bitfield-Mask: 0xff)                 */
#define ADC1_SQ5_8_SQ7_Pos                (16UL)                    /*!< ADC1 SQ5_8: SQ7 (Bit 16)                              */
#define ADC1_SQ5_8_SQ7_Msk                (0xff0000UL)              /*!< ADC1 SQ5_8: SQ7 (Bitfield-Mask: 0xff)                 */
#define ADC1_SQ5_8_SQ6_Pos                (8UL)                     /*!< ADC1 SQ5_8: SQ6 (Bit 8)                               */
#define ADC1_SQ5_8_SQ6_Msk                (0xff00UL)                /*!< ADC1 SQ5_8: SQ6 (Bitfield-Mask: 0xff)                 */
#define ADC1_SQ5_8_SQ5_Pos                (0UL)                     /*!< ADC1 SQ5_8: SQ5 (Bit 0)                               */
#define ADC1_SQ5_8_SQ5_Msk                (0xffUL)                  /*!< ADC1 SQ5_8: SQ5 (Bitfield-Mask: 0xff)                 */
/* =========================================================  SQ_FB  ========================================================= */
#define ADC1_SQ_FB_CHx_Pos                (16UL)                    /*!< ADC1 SQ_FB: CHx (Bit 16)                              */
#define ADC1_SQ_FB_CHx_Msk                (0x70000UL)               /*!< ADC1 SQ_FB: CHx (Bitfield-Mask: 0x07)                 */
#define ADC1_SQ_FB_SQx_Pos                (11UL)                    /*!< ADC1 SQ_FB: SQx (Bit 11)                              */
#define ADC1_SQ_FB_SQx_Msk                (0x3800UL)                /*!< ADC1 SQ_FB: SQx (Bitfield-Mask: 0x07)                 */
#define ADC1_SQ_FB_ESM_ACTIVE_Pos         (10UL)                    /*!< ADC1 SQ_FB: ESM_ACTIVE (Bit 10)                       */
#define ADC1_SQ_FB_ESM_ACTIVE_Msk         (0x400UL)                 /*!< ADC1 SQ_FB: ESM_ACTIVE (Bitfield-Mask: 0x01)          */
#define ADC1_SQ_FB_EIM_ACTIVE_Pos         (9UL)                     /*!< ADC1 SQ_FB: EIM_ACTIVE (Bit 9)                        */
#define ADC1_SQ_FB_EIM_ACTIVE_Msk         (0x200UL)                 /*!< ADC1 SQ_FB: EIM_ACTIVE (Bitfield-Mask: 0x01)          */
#define ADC1_SQ_FB_SQ_RUN_Pos             (8UL)                     /*!< ADC1 SQ_FB: SQ_RUN (Bit 8)                            */
#define ADC1_SQ_FB_SQ_RUN_Msk             (0x100UL)                 /*!< ADC1 SQ_FB: SQ_RUN (Bitfield-Mask: 0x01)              */
/* ========================================================  STC_0_3  ======================================================== */
#define ADC1_STC_0_3_ch3_Pos              (24UL)                    /*!< ADC1 STC_0_3: ch3 (Bit 24)                            */
#define ADC1_STC_0_3_ch3_Msk              (0xff000000UL)            /*!< ADC1 STC_0_3: ch3 (Bitfield-Mask: 0xff)               */
#define ADC1_STC_0_3_ch2_Pos              (16UL)                    /*!< ADC1 STC_0_3: ch2 (Bit 16)                            */
#define ADC1_STC_0_3_ch2_Msk              (0xff0000UL)              /*!< ADC1 STC_0_3: ch2 (Bitfield-Mask: 0xff)               */
#define ADC1_STC_0_3_ch1_Pos              (8UL)                     /*!< ADC1 STC_0_3: ch1 (Bit 8)                             */
#define ADC1_STC_0_3_ch1_Msk              (0xff00UL)                /*!< ADC1 STC_0_3: ch1 (Bitfield-Mask: 0xff)               */
#define ADC1_STC_0_3_ch0_Pos              (0UL)                     /*!< ADC1 STC_0_3: ch0 (Bit 0)                             */
#define ADC1_STC_0_3_ch0_Msk              (0xffUL)                  /*!< ADC1 STC_0_3: ch0 (Bitfield-Mask: 0xff)               */
/* ========================================================  STC_4_7  ======================================================== */
#define ADC1_STC_4_7_ch7_Pos              (24UL)                    /*!< ADC1 STC_4_7: ch7 (Bit 24)                            */
#define ADC1_STC_4_7_ch7_Msk              (0xff000000UL)            /*!< ADC1 STC_4_7: ch7 (Bitfield-Mask: 0xff)               */
#define ADC1_STC_4_7_ch6_Pos              (16UL)                    /*!< ADC1 STC_4_7: ch6 (Bit 16)                            */
#define ADC1_STC_4_7_ch6_Msk              (0xff0000UL)              /*!< ADC1 STC_4_7: ch6 (Bitfield-Mask: 0xff)               */
#define ADC1_STC_4_7_ch5_Pos              (8UL)                     /*!< ADC1 STC_4_7: ch5 (Bit 8)                             */
#define ADC1_STC_4_7_ch5_Msk              (0xff00UL)                /*!< ADC1 STC_4_7: ch5 (Bitfield-Mask: 0xff)               */
#define ADC1_STC_4_7_ch4_Pos              (0UL)                     /*!< ADC1 STC_4_7: ch4 (Bit 0)                             */
#define ADC1_STC_4_7_ch4_Msk              (0xffUL)                  /*!< ADC1 STC_4_7: ch4 (Bitfield-Mask: 0xff)               */


/* =========================================================================================================================== */
/* ================                                           ADC2                                            ================ */
/* =========================================================================================================================== */

/* =======================================================  CAL_CH0_1  ======================================================= */
#define ADC2_CAL_CH0_1_GAIN_CH1_Pos       (24UL)                    /*!< ADC2 CAL_CH0_1: GAIN_CH1 (Bit 24)                     */
#define ADC2_CAL_CH0_1_GAIN_CH1_Msk       (0xff000000UL)            /*!< ADC2 CAL_CH0_1: GAIN_CH1 (Bitfield-Mask: 0xff)        */
#define ADC2_CAL_CH0_1_OFFS_CH1_Pos       (16UL)                    /*!< ADC2 CAL_CH0_1: OFFS_CH1 (Bit 16)                     */
#define ADC2_CAL_CH0_1_OFFS_CH1_Msk       (0xff0000UL)              /*!< ADC2 CAL_CH0_1: OFFS_CH1 (Bitfield-Mask: 0xff)        */
#define ADC2_CAL_CH0_1_GAIN_CH0_Pos       (8UL)                     /*!< ADC2 CAL_CH0_1: GAIN_CH0 (Bit 8)                      */
#define ADC2_CAL_CH0_1_GAIN_CH0_Msk       (0xff00UL)                /*!< ADC2 CAL_CH0_1: GAIN_CH0 (Bitfield-Mask: 0xff)        */
#define ADC2_CAL_CH0_1_OFFS_CH0_Pos       (0UL)                     /*!< ADC2 CAL_CH0_1: OFFS_CH0 (Bit 0)                      */
#define ADC2_CAL_CH0_1_OFFS_CH0_Msk       (0xffUL)                  /*!< ADC2 CAL_CH0_1: OFFS_CH0 (Bitfield-Mask: 0xff)        */
/* =======================================================  CAL_CH2_3  ======================================================= */
#define ADC2_CAL_CH2_3_GAIN_CH3_Pos       (24UL)                    /*!< ADC2 CAL_CH2_3: GAIN_CH3 (Bit 24)                     */
#define ADC2_CAL_CH2_3_GAIN_CH3_Msk       (0xff000000UL)            /*!< ADC2 CAL_CH2_3: GAIN_CH3 (Bitfield-Mask: 0xff)        */
#define ADC2_CAL_CH2_3_OFFS_CH3_Pos       (16UL)                    /*!< ADC2 CAL_CH2_3: OFFS_CH3 (Bit 16)                     */
#define ADC2_CAL_CH2_3_OFFS_CH3_Msk       (0xff0000UL)              /*!< ADC2 CAL_CH2_3: OFFS_CH3 (Bitfield-Mask: 0xff)        */
#define ADC2_CAL_CH2_3_GAIN_CH2_Pos       (8UL)                     /*!< ADC2 CAL_CH2_3: GAIN_CH2 (Bit 8)                      */
#define ADC2_CAL_CH2_3_GAIN_CH2_Msk       (0xff00UL)                /*!< ADC2 CAL_CH2_3: GAIN_CH2 (Bitfield-Mask: 0xff)        */
#define ADC2_CAL_CH2_3_OFFS_CH2_Pos       (0UL)                     /*!< ADC2 CAL_CH2_3: OFFS_CH2 (Bit 0)                      */
#define ADC2_CAL_CH2_3_OFFS_CH2_Msk       (0xffUL)                  /*!< ADC2 CAL_CH2_3: OFFS_CH2 (Bitfield-Mask: 0xff)        */
/* =======================================================  CAL_CH4_5  ======================================================= */
#define ADC2_CAL_CH4_5_GAIN_CH5_Pos       (24UL)                    /*!< ADC2 CAL_CH4_5: GAIN_CH5 (Bit 24)                     */
#define ADC2_CAL_CH4_5_GAIN_CH5_Msk       (0xff000000UL)            /*!< ADC2 CAL_CH4_5: GAIN_CH5 (Bitfield-Mask: 0xff)        */
#define ADC2_CAL_CH4_5_OFFS_CH5_Pos       (16UL)                    /*!< ADC2 CAL_CH4_5: OFFS_CH5 (Bit 16)                     */
#define ADC2_CAL_CH4_5_OFFS_CH5_Msk       (0xff0000UL)              /*!< ADC2 CAL_CH4_5: OFFS_CH5 (Bitfield-Mask: 0xff)        */
#define ADC2_CAL_CH4_5_GAIN_CH4_Pos       (8UL)                     /*!< ADC2 CAL_CH4_5: GAIN_CH4 (Bit 8)                      */
#define ADC2_CAL_CH4_5_GAIN_CH4_Msk       (0xff00UL)                /*!< ADC2 CAL_CH4_5: GAIN_CH4 (Bitfield-Mask: 0xff)        */
#define ADC2_CAL_CH4_5_OFFS_CH4_Pos       (0UL)                     /*!< ADC2 CAL_CH4_5: OFFS_CH4 (Bit 0)                      */
#define ADC2_CAL_CH4_5_OFFS_CH4_Msk       (0xffUL)                  /*!< ADC2 CAL_CH4_5: OFFS_CH4 (Bitfield-Mask: 0xff)        */
/* =======================================================  CAL_CH6_7  ======================================================= */
#define ADC2_CAL_CH6_7_GAIN_CH7_Pos       (24UL)                    /*!< ADC2 CAL_CH6_7: GAIN_CH7 (Bit 24)                     */
#define ADC2_CAL_CH6_7_GAIN_CH7_Msk       (0xff000000UL)            /*!< ADC2 CAL_CH6_7: GAIN_CH7 (Bitfield-Mask: 0xff)        */
#define ADC2_CAL_CH6_7_OFFS_CH7_Pos       (16UL)                    /*!< ADC2 CAL_CH6_7: OFFS_CH7 (Bit 16)                     */
#define ADC2_CAL_CH6_7_OFFS_CH7_Msk       (0xff0000UL)              /*!< ADC2 CAL_CH6_7: OFFS_CH7 (Bitfield-Mask: 0xff)        */
#define ADC2_CAL_CH6_7_GAIN_CH6_Pos       (8UL)                     /*!< ADC2 CAL_CH6_7: GAIN_CH6 (Bit 8)                      */
#define ADC2_CAL_CH6_7_GAIN_CH6_Msk       (0xff00UL)                /*!< ADC2 CAL_CH6_7: GAIN_CH6 (Bitfield-Mask: 0xff)        */
#define ADC2_CAL_CH6_7_OFFS_CH6_Pos       (0UL)                     /*!< ADC2 CAL_CH6_7: OFFS_CH6 (Bit 0)                      */
#define ADC2_CAL_CH6_7_OFFS_CH6_Msk       (0xffUL)                  /*!< ADC2 CAL_CH6_7: OFFS_CH6 (Bitfield-Mask: 0xff)        */
/* =======================================================  CAL_CH8_9  ======================================================= */
#define ADC2_CAL_CH8_9_GAIN_CH9_Pos       (24UL)                    /*!< ADC2 CAL_CH8_9: GAIN_CH9 (Bit 24)                     */
#define ADC2_CAL_CH8_9_GAIN_CH9_Msk       (0xff000000UL)            /*!< ADC2 CAL_CH8_9: GAIN_CH9 (Bitfield-Mask: 0xff)        */
#define ADC2_CAL_CH8_9_OFFS_CH9_Pos       (16UL)                    /*!< ADC2 CAL_CH8_9: OFFS_CH9 (Bit 16)                     */
#define ADC2_CAL_CH8_9_OFFS_CH9_Msk       (0xff0000UL)              /*!< ADC2 CAL_CH8_9: OFFS_CH9 (Bitfield-Mask: 0xff)        */
#define ADC2_CAL_CH8_9_GAIN_CH8_Pos       (8UL)                     /*!< ADC2 CAL_CH8_9: GAIN_CH8 (Bit 8)                      */
#define ADC2_CAL_CH8_9_GAIN_CH8_Msk       (0xff00UL)                /*!< ADC2 CAL_CH8_9: GAIN_CH8 (Bitfield-Mask: 0xff)        */
#define ADC2_CAL_CH8_9_OFFS_CH8_Pos       (0UL)                     /*!< ADC2 CAL_CH8_9: OFFS_CH8 (Bit 0)                      */
#define ADC2_CAL_CH8_9_OFFS_CH8_Msk       (0xffUL)                  /*!< ADC2 CAL_CH8_9: OFFS_CH8 (Bitfield-Mask: 0xff)        */
/* ========================================================  CHx_EIM  ======================================================== */
#define ADC2_CHx_EIM_SEL_Pos              (12UL)                    /*!< ADC2 CHx_EIM: SEL (Bit 12)                            */
#define ADC2_CHx_EIM_SEL_Msk              (0x1000UL)                /*!< ADC2 CHx_EIM: SEL (Bitfield-Mask: 0x01)               */
#define ADC2_CHx_EIM_EN_Pos               (11UL)                    /*!< ADC2 CHx_EIM: EN (Bit 11)                             */
#define ADC2_CHx_EIM_EN_Msk               (0x800UL)                 /*!< ADC2 CHx_EIM: EN (Bitfield-Mask: 0x01)                */
#define ADC2_CHx_EIM_REP_Pos              (8UL)                     /*!< ADC2 CHx_EIM: REP (Bit 8)                             */
#define ADC2_CHx_EIM_REP_Msk              (0x700UL)                 /*!< ADC2 CHx_EIM: REP (Bitfield-Mask: 0x07)               */
#define ADC2_CHx_EIM_CHx_Pos              (0UL)                     /*!< ADC2 CHx_EIM: CHx (Bit 0)                             */
#define ADC2_CHx_EIM_CHx_Msk              (0x1fUL)                  /*!< ADC2 CHx_EIM: CHx (Bitfield-Mask: 0x1f)               */
/* ========================================================  CHx_ESM  ======================================================== */
#define ADC2_CHx_ESM_STS_Pos              (17UL)                    /*!< ADC2 CHx_ESM: STS (Bit 17)                            */
#define ADC2_CHx_ESM_STS_Msk              (0x20000UL)               /*!< ADC2 CHx_ESM: STS (Bitfield-Mask: 0x01)               */
#define ADC2_CHx_ESM_EN_Pos               (16UL)                    /*!< ADC2 CHx_ESM: EN (Bit 16)                             */
#define ADC2_CHx_ESM_EN_Msk               (0x10000UL)               /*!< ADC2 CHx_ESM: EN (Bitfield-Mask: 0x01)                */
#define ADC2_CHx_ESM_SEL_Pos              (10UL)                    /*!< ADC2 CHx_ESM: SEL (Bit 10)                            */
#define ADC2_CHx_ESM_SEL_Msk              (0x400UL)                 /*!< ADC2 CHx_ESM: SEL (Bitfield-Mask: 0x01)               */
#define ADC2_CHx_ESM_ESM_1_Pos            (6UL)                     /*!< ADC2 CHx_ESM: ESM_1 (Bit 6)                           */
#define ADC2_CHx_ESM_ESM_1_Msk            (0x3c0UL)                 /*!< ADC2 CHx_ESM: ESM_1 (Bitfield-Mask: 0x0f)             */
#define ADC2_CHx_ESM_ESM_0_Pos            (0UL)                     /*!< ADC2 CHx_ESM: ESM_0 (Bit 0)                           */
#define ADC2_CHx_ESM_ESM_0_Msk            (0x3fUL)                  /*!< ADC2 CHx_ESM: ESM_0 (Bitfield-Mask: 0x3f)             */
/* =====================================================  CNT0_3_LOWER  ====================================================== */
#define ADC2_CNT0_3_LOWER_HYST_LO_CH3_Pos (27UL)                    /*!< ADC2 CNT0_3_LOWER: HYST_LO_CH3 (Bit 27)               */
#define ADC2_CNT0_3_LOWER_HYST_LO_CH3_Msk (0x18000000UL)            /*!< ADC2 CNT0_3_LOWER: HYST_LO_CH3 (Bitfield-Mask: 0x03)  */
#define ADC2_CNT0_3_LOWER_CNT_LO_CH3_Pos  (24UL)                    /*!< ADC2 CNT0_3_LOWER: CNT_LO_CH3 (Bit 24)                */
#define ADC2_CNT0_3_LOWER_CNT_LO_CH3_Msk  (0x7000000UL)             /*!< ADC2 CNT0_3_LOWER: CNT_LO_CH3 (Bitfield-Mask: 0x07)   */
#define ADC2_CNT0_3_LOWER_HYST_LO_CH2_Pos (19UL)                    /*!< ADC2 CNT0_3_LOWER: HYST_LO_CH2 (Bit 19)               */
#define ADC2_CNT0_3_LOWER_HYST_LO_CH2_Msk (0x180000UL)              /*!< ADC2 CNT0_3_LOWER: HYST_LO_CH2 (Bitfield-Mask: 0x03)  */
#define ADC2_CNT0_3_LOWER_CNT_LO_CH2_Pos  (16UL)                    /*!< ADC2 CNT0_3_LOWER: CNT_LO_CH2 (Bit 16)                */
#define ADC2_CNT0_3_LOWER_CNT_LO_CH2_Msk  (0x70000UL)               /*!< ADC2 CNT0_3_LOWER: CNT_LO_CH2 (Bitfield-Mask: 0x07)   */
#define ADC2_CNT0_3_LOWER_HYST_LO_CH1_Pos (11UL)                    /*!< ADC2 CNT0_3_LOWER: HYST_LO_CH1 (Bit 11)               */
#define ADC2_CNT0_3_LOWER_HYST_LO_CH1_Msk (0x1800UL)                /*!< ADC2 CNT0_3_LOWER: HYST_LO_CH1 (Bitfield-Mask: 0x03)  */
#define ADC2_CNT0_3_LOWER_CNT_LO_CH1_Pos  (8UL)                     /*!< ADC2 CNT0_3_LOWER: CNT_LO_CH1 (Bit 8)                 */
#define ADC2_CNT0_3_LOWER_CNT_LO_CH1_Msk  (0x700UL)                 /*!< ADC2 CNT0_3_LOWER: CNT_LO_CH1 (Bitfield-Mask: 0x07)   */
#define ADC2_CNT0_3_LOWER_HYST_LO_CH0_Pos (3UL)                     /*!< ADC2 CNT0_3_LOWER: HYST_LO_CH0 (Bit 3)                */
#define ADC2_CNT0_3_LOWER_HYST_LO_CH0_Msk (0x18UL)                  /*!< ADC2 CNT0_3_LOWER: HYST_LO_CH0 (Bitfield-Mask: 0x03)  */
#define ADC2_CNT0_3_LOWER_CNT_LO_CH0_Pos  (0UL)                     /*!< ADC2 CNT0_3_LOWER: CNT_LO_CH0 (Bit 0)                 */
#define ADC2_CNT0_3_LOWER_CNT_LO_CH0_Msk  (0x7UL)                   /*!< ADC2 CNT0_3_LOWER: CNT_LO_CH0 (Bitfield-Mask: 0x07)   */
/* =====================================================  CNT0_3_UPPER  ====================================================== */
#define ADC2_CNT0_3_UPPER_HYST_UP_CH3_Pos (27UL)                    /*!< ADC2 CNT0_3_UPPER: HYST_UP_CH3 (Bit 27)               */
#define ADC2_CNT0_3_UPPER_HYST_UP_CH3_Msk (0x18000000UL)            /*!< ADC2 CNT0_3_UPPER: HYST_UP_CH3 (Bitfield-Mask: 0x03)  */
#define ADC2_CNT0_3_UPPER_CNT_UP_CH3_Pos  (24UL)                    /*!< ADC2 CNT0_3_UPPER: CNT_UP_CH3 (Bit 24)                */
#define ADC2_CNT0_3_UPPER_CNT_UP_CH3_Msk  (0x7000000UL)             /*!< ADC2 CNT0_3_UPPER: CNT_UP_CH3 (Bitfield-Mask: 0x07)   */
#define ADC2_CNT0_3_UPPER_HYST_UP_CH2_Pos (19UL)                    /*!< ADC2 CNT0_3_UPPER: HYST_UP_CH2 (Bit 19)               */
#define ADC2_CNT0_3_UPPER_HYST_UP_CH2_Msk (0x180000UL)              /*!< ADC2 CNT0_3_UPPER: HYST_UP_CH2 (Bitfield-Mask: 0x03)  */
#define ADC2_CNT0_3_UPPER_CNT_UP_CH2_Pos  (16UL)                    /*!< ADC2 CNT0_3_UPPER: CNT_UP_CH2 (Bit 16)                */
#define ADC2_CNT0_3_UPPER_CNT_UP_CH2_Msk  (0x70000UL)               /*!< ADC2 CNT0_3_UPPER: CNT_UP_CH2 (Bitfield-Mask: 0x07)   */
#define ADC2_CNT0_3_UPPER_HYST_UP_CH1_Pos (11UL)                    /*!< ADC2 CNT0_3_UPPER: HYST_UP_CH1 (Bit 11)               */
#define ADC2_CNT0_3_UPPER_HYST_UP_CH1_Msk (0x1800UL)                /*!< ADC2 CNT0_3_UPPER: HYST_UP_CH1 (Bitfield-Mask: 0x03)  */
#define ADC2_CNT0_3_UPPER_CNT_UP_CH1_Pos  (8UL)                     /*!< ADC2 CNT0_3_UPPER: CNT_UP_CH1 (Bit 8)                 */
#define ADC2_CNT0_3_UPPER_CNT_UP_CH1_Msk  (0x700UL)                 /*!< ADC2 CNT0_3_UPPER: CNT_UP_CH1 (Bitfield-Mask: 0x07)   */
#define ADC2_CNT0_3_UPPER_HYST_UP_CH0_Pos (3UL)                     /*!< ADC2 CNT0_3_UPPER: HYST_UP_CH0 (Bit 3)                */
#define ADC2_CNT0_3_UPPER_HYST_UP_CH0_Msk (0x18UL)                  /*!< ADC2 CNT0_3_UPPER: HYST_UP_CH0 (Bitfield-Mask: 0x03)  */
#define ADC2_CNT0_3_UPPER_CNT_UP_CH0_Pos  (0UL)                     /*!< ADC2 CNT0_3_UPPER: CNT_UP_CH0 (Bit 0)                 */
#define ADC2_CNT0_3_UPPER_CNT_UP_CH0_Msk  (0x7UL)                   /*!< ADC2 CNT0_3_UPPER: CNT_UP_CH0 (Bitfield-Mask: 0x07)   */
/* =====================================================  CNT4_5_LOWER  ====================================================== */
#define ADC2_CNT4_5_LOWER_HYST_LO_CH5_Pos (11UL)                    /*!< ADC2 CNT4_5_LOWER: HYST_LO_CH5 (Bit 11)               */
#define ADC2_CNT4_5_LOWER_HYST_LO_CH5_Msk (0x1800UL)                /*!< ADC2 CNT4_5_LOWER: HYST_LO_CH5 (Bitfield-Mask: 0x03)  */
#define ADC2_CNT4_5_LOWER_CNT_LO_CH5_Pos  (8UL)                     /*!< ADC2 CNT4_5_LOWER: CNT_LO_CH5 (Bit 8)                 */
#define ADC2_CNT4_5_LOWER_CNT_LO_CH5_Msk  (0x700UL)                 /*!< ADC2 CNT4_5_LOWER: CNT_LO_CH5 (Bitfield-Mask: 0x07)   */
#define ADC2_CNT4_5_LOWER_HYST_LO_CH4_Pos (3UL)                     /*!< ADC2 CNT4_5_LOWER: HYST_LO_CH4 (Bit 3)                */
#define ADC2_CNT4_5_LOWER_HYST_LO_CH4_Msk (0x18UL)                  /*!< ADC2 CNT4_5_LOWER: HYST_LO_CH4 (Bitfield-Mask: 0x03)  */
#define ADC2_CNT4_5_LOWER_CNT_LO_CH4_Pos  (0UL)                     /*!< ADC2 CNT4_5_LOWER: CNT_LO_CH4 (Bit 0)                 */
#define ADC2_CNT4_5_LOWER_CNT_LO_CH4_Msk  (0x7UL)                   /*!< ADC2 CNT4_5_LOWER: CNT_LO_CH4 (Bitfield-Mask: 0x07)   */
/* =====================================================  CNT4_5_UPPER  ====================================================== */
#define ADC2_CNT4_5_UPPER_HYST_UP_CH5_Pos (11UL)                    /*!< ADC2 CNT4_5_UPPER: HYST_UP_CH5 (Bit 11)               */
#define ADC2_CNT4_5_UPPER_HYST_UP_CH5_Msk (0x1800UL)                /*!< ADC2 CNT4_5_UPPER: HYST_UP_CH5 (Bitfield-Mask: 0x03)  */
#define ADC2_CNT4_5_UPPER_CNT_UP_CH5_Pos  (8UL)                     /*!< ADC2 CNT4_5_UPPER: CNT_UP_CH5 (Bit 8)                 */
#define ADC2_CNT4_5_UPPER_CNT_UP_CH5_Msk  (0x700UL)                 /*!< ADC2 CNT4_5_UPPER: CNT_UP_CH5 (Bitfield-Mask: 0x07)   */
#define ADC2_CNT4_5_UPPER_HYST_UP_CH4_Pos (3UL)                     /*!< ADC2 CNT4_5_UPPER: HYST_UP_CH4 (Bit 3)                */
#define ADC2_CNT4_5_UPPER_HYST_UP_CH4_Msk (0x18UL)                  /*!< ADC2 CNT4_5_UPPER: HYST_UP_CH4 (Bitfield-Mask: 0x03)  */
#define ADC2_CNT4_5_UPPER_CNT_UP_CH4_Pos  (0UL)                     /*!< ADC2 CNT4_5_UPPER: CNT_UP_CH4 (Bit 0)                 */
#define ADC2_CNT4_5_UPPER_CNT_UP_CH4_Msk  (0x7UL)                   /*!< ADC2 CNT4_5_UPPER: CNT_UP_CH4 (Bitfield-Mask: 0x07)   */
/* =====================================================  CNT6_9_LOWER  ====================================================== */
#define ADC2_CNT6_9_LOWER_HYST_LO_CH9_Pos (27UL)                    /*!< ADC2 CNT6_9_LOWER: HYST_LO_CH9 (Bit 27)               */
#define ADC2_CNT6_9_LOWER_HYST_LO_CH9_Msk (0x18000000UL)            /*!< ADC2 CNT6_9_LOWER: HYST_LO_CH9 (Bitfield-Mask: 0x03)  */
#define ADC2_CNT6_9_LOWER_CNT_LO_CH9_Pos  (24UL)                    /*!< ADC2 CNT6_9_LOWER: CNT_LO_CH9 (Bit 24)                */
#define ADC2_CNT6_9_LOWER_CNT_LO_CH9_Msk  (0x7000000UL)             /*!< ADC2 CNT6_9_LOWER: CNT_LO_CH9 (Bitfield-Mask: 0x07)   */
#define ADC2_CNT6_9_LOWER_HYST_LO_CH8_Pos (19UL)                    /*!< ADC2 CNT6_9_LOWER: HYST_LO_CH8 (Bit 19)               */
#define ADC2_CNT6_9_LOWER_HYST_LO_CH8_Msk (0x180000UL)              /*!< ADC2 CNT6_9_LOWER: HYST_LO_CH8 (Bitfield-Mask: 0x03)  */
#define ADC2_CNT6_9_LOWER_CNT_LO_CH8_Pos  (16UL)                    /*!< ADC2 CNT6_9_LOWER: CNT_LO_CH8 (Bit 16)                */
#define ADC2_CNT6_9_LOWER_CNT_LO_CH8_Msk  (0x70000UL)               /*!< ADC2 CNT6_9_LOWER: CNT_LO_CH8 (Bitfield-Mask: 0x07)   */
#define ADC2_CNT6_9_LOWER_HYST_LO_CH7_Pos (11UL)                    /*!< ADC2 CNT6_9_LOWER: HYST_LO_CH7 (Bit 11)               */
#define ADC2_CNT6_9_LOWER_HYST_LO_CH7_Msk (0x1800UL)                /*!< ADC2 CNT6_9_LOWER: HYST_LO_CH7 (Bitfield-Mask: 0x03)  */
#define ADC2_CNT6_9_LOWER_CNT_LO_CH7_Pos  (8UL)                     /*!< ADC2 CNT6_9_LOWER: CNT_LO_CH7 (Bit 8)                 */
#define ADC2_CNT6_9_LOWER_CNT_LO_CH7_Msk  (0x700UL)                 /*!< ADC2 CNT6_9_LOWER: CNT_LO_CH7 (Bitfield-Mask: 0x07)   */
#define ADC2_CNT6_9_LOWER_HYST_LO_CH6_Pos (3UL)                     /*!< ADC2 CNT6_9_LOWER: HYST_LO_CH6 (Bit 3)                */
#define ADC2_CNT6_9_LOWER_HYST_LO_CH6_Msk (0x18UL)                  /*!< ADC2 CNT6_9_LOWER: HYST_LO_CH6 (Bitfield-Mask: 0x03)  */
#define ADC2_CNT6_9_LOWER_CNT_LO_CH6_Pos  (0UL)                     /*!< ADC2 CNT6_9_LOWER: CNT_LO_CH6 (Bit 0)                 */
#define ADC2_CNT6_9_LOWER_CNT_LO_CH6_Msk  (0x7UL)                   /*!< ADC2 CNT6_9_LOWER: CNT_LO_CH6 (Bitfield-Mask: 0x07)   */
/* =====================================================  CNT6_9_UPPER  ====================================================== */
#define ADC2_CNT6_9_UPPER_HYST_UP_CH9_Pos (27UL)                    /*!< ADC2 CNT6_9_UPPER: HYST_UP_CH9 (Bit 27)               */
#define ADC2_CNT6_9_UPPER_HYST_UP_CH9_Msk (0x18000000UL)            /*!< ADC2 CNT6_9_UPPER: HYST_UP_CH9 (Bitfield-Mask: 0x03)  */
#define ADC2_CNT6_9_UPPER_CNT_UP_CH9_Pos  (24UL)                    /*!< ADC2 CNT6_9_UPPER: CNT_UP_CH9 (Bit 24)                */
#define ADC2_CNT6_9_UPPER_CNT_UP_CH9_Msk  (0x7000000UL)             /*!< ADC2 CNT6_9_UPPER: CNT_UP_CH9 (Bitfield-Mask: 0x07)   */
#define ADC2_CNT6_9_UPPER_HYST_UP_CH8_Pos (19UL)                    /*!< ADC2 CNT6_9_UPPER: HYST_UP_CH8 (Bit 19)               */
#define ADC2_CNT6_9_UPPER_HYST_UP_CH8_Msk (0x180000UL)              /*!< ADC2 CNT6_9_UPPER: HYST_UP_CH8 (Bitfield-Mask: 0x03)  */
#define ADC2_CNT6_9_UPPER_CNT_UP_CH8_Pos  (16UL)                    /*!< ADC2 CNT6_9_UPPER: CNT_UP_CH8 (Bit 16)                */
#define ADC2_CNT6_9_UPPER_CNT_UP_CH8_Msk  (0x70000UL)               /*!< ADC2 CNT6_9_UPPER: CNT_UP_CH8 (Bitfield-Mask: 0x07)   */
#define ADC2_CNT6_9_UPPER_HYST_UP_CH7_Pos (11UL)                    /*!< ADC2 CNT6_9_UPPER: HYST_UP_CH7 (Bit 11)               */
#define ADC2_CNT6_9_UPPER_HYST_UP_CH7_Msk (0x1800UL)                /*!< ADC2 CNT6_9_UPPER: HYST_UP_CH7 (Bitfield-Mask: 0x03)  */
#define ADC2_CNT6_9_UPPER_CNT_UP_CH7_Pos  (8UL)                     /*!< ADC2 CNT6_9_UPPER: CNT_UP_CH7 (Bit 8)                 */
#define ADC2_CNT6_9_UPPER_CNT_UP_CH7_Msk  (0x700UL)                 /*!< ADC2 CNT6_9_UPPER: CNT_UP_CH7 (Bitfield-Mask: 0x07)   */
#define ADC2_CNT6_9_UPPER_HYST_UP_CH6_Pos (3UL)                     /*!< ADC2 CNT6_9_UPPER: HYST_UP_CH6 (Bit 3)                */
#define ADC2_CNT6_9_UPPER_HYST_UP_CH6_Msk (0x18UL)                  /*!< ADC2 CNT6_9_UPPER: HYST_UP_CH6 (Bitfield-Mask: 0x03)  */
#define ADC2_CNT6_9_UPPER_CNT_UP_CH6_Pos  (0UL)                     /*!< ADC2 CNT6_9_UPPER: CNT_UP_CH6 (Bit 0)                 */
#define ADC2_CNT6_9_UPPER_CNT_UP_CH6_Msk  (0x7UL)                   /*!< ADC2 CNT6_9_UPPER: CNT_UP_CH6 (Bitfield-Mask: 0x07)   */
/* =========================================================  CTRL1  ========================================================= */
#define ADC2_CTRL1_CALIB_EN_Pos           (0UL)                     /*!< ADC2 CTRL1: CALIB_EN (Bit 0)                          */
#define ADC2_CTRL1_CALIB_EN_Msk           (0x3fUL)                  /*!< ADC2 CTRL1: CALIB_EN (Bitfield-Mask: 0x3f)            */
/* =========================================================  CTRL2  ========================================================= */
#define ADC2_CTRL2_SEL_TS_COUNT_Pos       (16UL)                    /*!< ADC2 CTRL2: SEL_TS_COUNT (Bit 16)                     */
#define ADC2_CTRL2_SEL_TS_COUNT_Msk       (0xf0000UL)               /*!< ADC2 CTRL2: SEL_TS_COUNT (Bitfield-Mask: 0x0f)        */
#define ADC2_CTRL2_SAMPLE_TIME_int_Pos    (8UL)                     /*!< ADC2 CTRL2: SAMPLE_TIME_int (Bit 8)                   */
#define ADC2_CTRL2_SAMPLE_TIME_int_Msk    (0xf00UL)                 /*!< ADC2 CTRL2: SAMPLE_TIME_int (Bitfield-Mask: 0x0f)     */
#define ADC2_CTRL2_MCM_RDY_Pos            (7UL)                     /*!< ADC2 CTRL2: MCM_RDY (Bit 7)                           */
#define ADC2_CTRL2_MCM_RDY_Msk            (0x80UL)                  /*!< ADC2 CTRL2: MCM_RDY (Bitfield-Mask: 0x01)             */
#define ADC2_CTRL2_TSENSE_SD_SEL_Pos      (2UL)                     /*!< ADC2 CTRL2: TSENSE_SD_SEL (Bit 2)                     */
#define ADC2_CTRL2_TSENSE_SD_SEL_Msk      (0x4UL)                   /*!< ADC2 CTRL2: TSENSE_SD_SEL (Bitfield-Mask: 0x01)       */
#define ADC2_CTRL2_TS_SD_SEL_CONF_Pos     (1UL)                     /*!< ADC2 CTRL2: TS_SD_SEL_CONF (Bit 1)                    */
#define ADC2_CTRL2_TS_SD_SEL_CONF_Msk     (0x2UL)                   /*!< ADC2 CTRL2: TS_SD_SEL_CONF (Bitfield-Mask: 0x01)      */
#define ADC2_CTRL2_MCM_PD_N_Pos           (0UL)                     /*!< ADC2 CTRL2: MCM_PD_N (Bit 0)                          */
#define ADC2_CTRL2_MCM_PD_N_Msk           (0x1UL)                   /*!< ADC2 CTRL2: MCM_PD_N (Bitfield-Mask: 0x01)            */
/* =========================================================  CTRL4  ========================================================= */
#define ADC2_CTRL4_FILT_OUT_SEL_9_6_Pos   (8UL)                     /*!< ADC2 CTRL4: FILT_OUT_SEL_9_6 (Bit 8)                  */
#define ADC2_CTRL4_FILT_OUT_SEL_9_6_Msk   (0xf00UL)                 /*!< ADC2 CTRL4: FILT_OUT_SEL_9_6 (Bitfield-Mask: 0x0f)    */
#define ADC2_CTRL4_FILT_OUT_SEL_5_0_Pos   (0UL)                     /*!< ADC2 CTRL4: FILT_OUT_SEL_5_0 (Bit 0)                  */
#define ADC2_CTRL4_FILT_OUT_SEL_5_0_Msk   (0x3fUL)                  /*!< ADC2 CTRL4: FILT_OUT_SEL_5_0 (Bitfield-Mask: 0x3f)    */
/* =======================================================  CTRL_STS  ======================================================== */
#define ADC2_CTRL_STS_VS_RANGE_Pos        (17UL)                    /*!< ADC2 CTRL_STS: VS_RANGE (Bit 17)                      */
#define ADC2_CTRL_STS_VS_RANGE_Msk        (0x20000UL)               /*!< ADC2 CTRL_STS: VS_RANGE (Bitfield-Mask: 0x01)         */
/* =====================================================  FILT_LO_CTRL  ====================================================== */
#define ADC2_FILT_LO_CTRL_Ch5_EN_Pos      (5UL)                     /*!< ADC2 FILT_LO_CTRL: Ch5_EN (Bit 5)                     */
#define ADC2_FILT_LO_CTRL_Ch5_EN_Msk      (0x20UL)                  /*!< ADC2 FILT_LO_CTRL: Ch5_EN (Bitfield-Mask: 0x01)       */
#define ADC2_FILT_LO_CTRL_Ch4_EN_Pos      (4UL)                     /*!< ADC2 FILT_LO_CTRL: Ch4_EN (Bit 4)                     */
#define ADC2_FILT_LO_CTRL_Ch4_EN_Msk      (0x10UL)                  /*!< ADC2 FILT_LO_CTRL: Ch4_EN (Bitfield-Mask: 0x01)       */
#define ADC2_FILT_LO_CTRL_Ch3_EN_Pos      (3UL)                     /*!< ADC2 FILT_LO_CTRL: Ch3_EN (Bit 3)                     */
#define ADC2_FILT_LO_CTRL_Ch3_EN_Msk      (0x8UL)                   /*!< ADC2 FILT_LO_CTRL: Ch3_EN (Bitfield-Mask: 0x01)       */
#define ADC2_FILT_LO_CTRL_Ch2_EN_Pos      (2UL)                     /*!< ADC2 FILT_LO_CTRL: Ch2_EN (Bit 2)                     */
#define ADC2_FILT_LO_CTRL_Ch2_EN_Msk      (0x4UL)                   /*!< ADC2 FILT_LO_CTRL: Ch2_EN (Bitfield-Mask: 0x01)       */
#define ADC2_FILT_LO_CTRL_Ch1_EN_Pos      (1UL)                     /*!< ADC2 FILT_LO_CTRL: Ch1_EN (Bit 1)                     */
#define ADC2_FILT_LO_CTRL_Ch1_EN_Msk      (0x2UL)                   /*!< ADC2 FILT_LO_CTRL: Ch1_EN (Bitfield-Mask: 0x01)       */
#define ADC2_FILT_LO_CTRL_Ch0_EN_Pos      (0UL)                     /*!< ADC2 FILT_LO_CTRL: Ch0_EN (Bit 0)                     */
#define ADC2_FILT_LO_CTRL_Ch0_EN_Msk      (0x1UL)                   /*!< ADC2 FILT_LO_CTRL: Ch0_EN (Bitfield-Mask: 0x01)       */
/* =======================================================  FILT_OUT0  ======================================================= */
#define ADC2_FILT_OUT0_OUT_CH0_Pos        (0UL)                     /*!< ADC2 FILT_OUT0: OUT_CH0 (Bit 0)                       */
#define ADC2_FILT_OUT0_OUT_CH0_Msk        (0x3ffUL)                 /*!< ADC2 FILT_OUT0: OUT_CH0 (Bitfield-Mask: 0x3ff)        */
/* =======================================================  FILT_OUT1  ======================================================= */
#define ADC2_FILT_OUT1_OUT_CH1_Pos        (0UL)                     /*!< ADC2 FILT_OUT1: OUT_CH1 (Bit 0)                       */
#define ADC2_FILT_OUT1_OUT_CH1_Msk        (0x3ffUL)                 /*!< ADC2 FILT_OUT1: OUT_CH1 (Bitfield-Mask: 0x3ff)        */
/* =======================================================  FILT_OUT2  ======================================================= */
#define ADC2_FILT_OUT2_OUT_CH2_Pos        (0UL)                     /*!< ADC2 FILT_OUT2: OUT_CH2 (Bit 0)                       */
#define ADC2_FILT_OUT2_OUT_CH2_Msk        (0x3ffUL)                 /*!< ADC2 FILT_OUT2: OUT_CH2 (Bitfield-Mask: 0x3ff)        */
/* =======================================================  FILT_OUT3  ======================================================= */
#define ADC2_FILT_OUT3_OUT_CH3_Pos        (0UL)                     /*!< ADC2 FILT_OUT3: OUT_CH3 (Bit 0)                       */
#define ADC2_FILT_OUT3_OUT_CH3_Msk        (0x3ffUL)                 /*!< ADC2 FILT_OUT3: OUT_CH3 (Bitfield-Mask: 0x3ff)        */
/* =======================================================  FILT_OUT4  ======================================================= */
#define ADC2_FILT_OUT4_OUT_CH4_Pos        (0UL)                     /*!< ADC2 FILT_OUT4: OUT_CH4 (Bit 0)                       */
#define ADC2_FILT_OUT4_OUT_CH4_Msk        (0x3ffUL)                 /*!< ADC2 FILT_OUT4: OUT_CH4 (Bitfield-Mask: 0x3ff)        */
/* =======================================================  FILT_OUT5  ======================================================= */
#define ADC2_FILT_OUT5_OUT_CH5_Pos        (0UL)                     /*!< ADC2 FILT_OUT5: OUT_CH5 (Bit 0)                       */
#define ADC2_FILT_OUT5_OUT_CH5_Msk        (0x3ffUL)                 /*!< ADC2 FILT_OUT5: OUT_CH5 (Bitfield-Mask: 0x3ff)        */
/* =======================================================  FILT_OUT6  ======================================================= */
#define ADC2_FILT_OUT6_OUT_CH6_Pos        (0UL)                     /*!< ADC2 FILT_OUT6: OUT_CH6 (Bit 0)                       */
#define ADC2_FILT_OUT6_OUT_CH6_Msk        (0x3ffUL)                 /*!< ADC2 FILT_OUT6: OUT_CH6 (Bitfield-Mask: 0x3ff)        */
/* =======================================================  FILT_OUT7  ======================================================= */
#define ADC2_FILT_OUT7_OUT_CH7_Pos        (0UL)                     /*!< ADC2 FILT_OUT7: OUT_CH7 (Bit 0)                       */
#define ADC2_FILT_OUT7_OUT_CH7_Msk        (0x3ffUL)                 /*!< ADC2 FILT_OUT7: OUT_CH7 (Bitfield-Mask: 0x3ff)        */
/* =======================================================  FILT_OUT8  ======================================================= */
#define ADC2_FILT_OUT8_OUT_CH8_Pos        (0UL)                     /*!< ADC2 FILT_OUT8: OUT_CH8 (Bit 0)                       */
#define ADC2_FILT_OUT8_OUT_CH8_Msk        (0x3ffUL)                 /*!< ADC2 FILT_OUT8: OUT_CH8 (Bitfield-Mask: 0x3ff)        */
/* =======================================================  FILT_OUT9  ======================================================= */
#define ADC2_FILT_OUT9_OUT_CH9_Pos        (0UL)                     /*!< ADC2 FILT_OUT9: OUT_CH9 (Bit 0)                       */
#define ADC2_FILT_OUT9_OUT_CH9_Msk        (0x3ffUL)                 /*!< ADC2 FILT_OUT9: OUT_CH9 (Bitfield-Mask: 0x3ff)        */
/* =====================================================  FILT_UP_CTRL  ====================================================== */
#define ADC2_FILT_UP_CTRL_Ch5_EN_Pos      (5UL)                     /*!< ADC2 FILT_UP_CTRL: Ch5_EN (Bit 5)                     */
#define ADC2_FILT_UP_CTRL_Ch5_EN_Msk      (0x20UL)                  /*!< ADC2 FILT_UP_CTRL: Ch5_EN (Bitfield-Mask: 0x01)       */
#define ADC2_FILT_UP_CTRL_Ch4_EN_Pos      (4UL)                     /*!< ADC2 FILT_UP_CTRL: Ch4_EN (Bit 4)                     */
#define ADC2_FILT_UP_CTRL_Ch4_EN_Msk      (0x10UL)                  /*!< ADC2 FILT_UP_CTRL: Ch4_EN (Bitfield-Mask: 0x01)       */
#define ADC2_FILT_UP_CTRL_Ch3_EN_Pos      (3UL)                     /*!< ADC2 FILT_UP_CTRL: Ch3_EN (Bit 3)                     */
#define ADC2_FILT_UP_CTRL_Ch3_EN_Msk      (0x8UL)                   /*!< ADC2 FILT_UP_CTRL: Ch3_EN (Bitfield-Mask: 0x01)       */
#define ADC2_FILT_UP_CTRL_Ch2_EN_Pos      (2UL)                     /*!< ADC2 FILT_UP_CTRL: Ch2_EN (Bit 2)                     */
#define ADC2_FILT_UP_CTRL_Ch2_EN_Msk      (0x4UL)                   /*!< ADC2 FILT_UP_CTRL: Ch2_EN (Bitfield-Mask: 0x01)       */
#define ADC2_FILT_UP_CTRL_Ch1_EN_Pos      (1UL)                     /*!< ADC2 FILT_UP_CTRL: Ch1_EN (Bit 1)                     */
#define ADC2_FILT_UP_CTRL_Ch1_EN_Msk      (0x2UL)                   /*!< ADC2 FILT_UP_CTRL: Ch1_EN (Bitfield-Mask: 0x01)       */
#define ADC2_FILT_UP_CTRL_Ch0_EN_Pos      (0UL)                     /*!< ADC2 FILT_UP_CTRL: Ch0_EN (Bit 0)                     */
#define ADC2_FILT_UP_CTRL_Ch0_EN_Msk      (0x1UL)                   /*!< ADC2 FILT_UP_CTRL: Ch0_EN (Bitfield-Mask: 0x01)       */
/* =====================================================  FILTCOEFF0_5  ====================================================== */
#define ADC2_FILTCOEFF0_5_CH5_Pos         (10UL)                    /*!< ADC2 FILTCOEFF0_5: CH5 (Bit 10)                       */
#define ADC2_FILTCOEFF0_5_CH5_Msk         (0xc00UL)                 /*!< ADC2 FILTCOEFF0_5: CH5 (Bitfield-Mask: 0x03)          */
#define ADC2_FILTCOEFF0_5_CH4_Pos         (8UL)                     /*!< ADC2 FILTCOEFF0_5: CH4 (Bit 8)                        */
#define ADC2_FILTCOEFF0_5_CH4_Msk         (0x300UL)                 /*!< ADC2 FILTCOEFF0_5: CH4 (Bitfield-Mask: 0x03)          */
#define ADC2_FILTCOEFF0_5_CH3_Pos         (6UL)                     /*!< ADC2 FILTCOEFF0_5: CH3 (Bit 6)                        */
#define ADC2_FILTCOEFF0_5_CH3_Msk         (0xc0UL)                  /*!< ADC2 FILTCOEFF0_5: CH3 (Bitfield-Mask: 0x03)          */
#define ADC2_FILTCOEFF0_5_CH2_Pos         (4UL)                     /*!< ADC2 FILTCOEFF0_5: CH2 (Bit 4)                        */
#define ADC2_FILTCOEFF0_5_CH2_Msk         (0x30UL)                  /*!< ADC2 FILTCOEFF0_5: CH2 (Bitfield-Mask: 0x03)          */
#define ADC2_FILTCOEFF0_5_CH1_Pos         (2UL)                     /*!< ADC2 FILTCOEFF0_5: CH1 (Bit 2)                        */
#define ADC2_FILTCOEFF0_5_CH1_Msk         (0xcUL)                   /*!< ADC2 FILTCOEFF0_5: CH1 (Bitfield-Mask: 0x03)          */
#define ADC2_FILTCOEFF0_5_CH0_Pos         (0UL)                     /*!< ADC2 FILTCOEFF0_5: CH0 (Bit 0)                        */
#define ADC2_FILTCOEFF0_5_CH0_Msk         (0x3UL)                   /*!< ADC2 FILTCOEFF0_5: CH0 (Bitfield-Mask: 0x03)          */
/* =====================================================  FILTCOEFF6_9  ====================================================== */
#define ADC2_FILTCOEFF6_9_CH9_Pos         (6UL)                     /*!< ADC2 FILTCOEFF6_9: CH9 (Bit 6)                        */
#define ADC2_FILTCOEFF6_9_CH9_Msk         (0xc0UL)                  /*!< ADC2 FILTCOEFF6_9: CH9 (Bitfield-Mask: 0x03)          */
#define ADC2_FILTCOEFF6_9_CH8_Pos         (4UL)                     /*!< ADC2 FILTCOEFF6_9: CH8 (Bit 4)                        */
#define ADC2_FILTCOEFF6_9_CH8_Msk         (0x30UL)                  /*!< ADC2 FILTCOEFF6_9: CH8 (Bitfield-Mask: 0x03)          */
#define ADC2_FILTCOEFF6_9_CH7_Pos         (2UL)                     /*!< ADC2 FILTCOEFF6_9: CH7 (Bit 2)                        */
#define ADC2_FILTCOEFF6_9_CH7_Msk         (0xcUL)                   /*!< ADC2 FILTCOEFF6_9: CH7 (Bitfield-Mask: 0x03)          */
#define ADC2_FILTCOEFF6_9_CH6_Pos         (0UL)                     /*!< ADC2 FILTCOEFF6_9: CH6 (Bit 0)                        */
#define ADC2_FILTCOEFF6_9_CH6_Msk         (0x3UL)                   /*!< ADC2 FILTCOEFF6_9: CH6 (Bitfield-Mask: 0x03)          */
/* ========================================================  HV_STS  ========================================================= */
#define ADC2_HV_STS_READY_Pos             (1UL)                     /*!< ADC2 HV_STS: READY (Bit 1)                            */
#define ADC2_HV_STS_READY_Msk             (0x2UL)                   /*!< ADC2 HV_STS: READY (Bitfield-Mask: 0x01)              */
/* =======================================================  MMODE0_5  ======================================================== */
#define ADC2_MMODE0_5_Ch5_Pos             (10UL)                    /*!< ADC2 MMODE0_5: Ch5 (Bit 10)                           */
#define ADC2_MMODE0_5_Ch5_Msk             (0xc00UL)                 /*!< ADC2 MMODE0_5: Ch5 (Bitfield-Mask: 0x03)              */
#define ADC2_MMODE0_5_Ch4_Pos             (8UL)                     /*!< ADC2 MMODE0_5: Ch4 (Bit 8)                            */
#define ADC2_MMODE0_5_Ch4_Msk             (0x300UL)                 /*!< ADC2 MMODE0_5: Ch4 (Bitfield-Mask: 0x03)              */
#define ADC2_MMODE0_5_Ch3_Pos             (6UL)                     /*!< ADC2 MMODE0_5: Ch3 (Bit 6)                            */
#define ADC2_MMODE0_5_Ch3_Msk             (0xc0UL)                  /*!< ADC2 MMODE0_5: Ch3 (Bitfield-Mask: 0x03)              */
#define ADC2_MMODE0_5_Ch2_Pos             (4UL)                     /*!< ADC2 MMODE0_5: Ch2 (Bit 4)                            */
#define ADC2_MMODE0_5_Ch2_Msk             (0x30UL)                  /*!< ADC2 MMODE0_5: Ch2 (Bitfield-Mask: 0x03)              */
#define ADC2_MMODE0_5_Ch1_Pos             (2UL)                     /*!< ADC2 MMODE0_5: Ch1 (Bit 2)                            */
#define ADC2_MMODE0_5_Ch1_Msk             (0xcUL)                   /*!< ADC2 MMODE0_5: Ch1 (Bitfield-Mask: 0x03)              */
#define ADC2_MMODE0_5_Ch0_Pos             (0UL)                     /*!< ADC2 MMODE0_5: Ch0 (Bit 0)                            */
#define ADC2_MMODE0_5_Ch0_Msk             (0x3UL)                   /*!< ADC2 MMODE0_5: Ch0 (Bitfield-Mask: 0x03)              */
/* =========================================================  SQ1_4  ========================================================= */
#define ADC2_SQ1_4_SQ4_Pos                (24UL)                    /*!< ADC2 SQ1_4: SQ4 (Bit 24)                              */
#define ADC2_SQ1_4_SQ4_Msk                (0x3f000000UL)            /*!< ADC2 SQ1_4: SQ4 (Bitfield-Mask: 0x3f)                 */
#define ADC2_SQ1_4_SQ3_Pos                (16UL)                    /*!< ADC2 SQ1_4: SQ3 (Bit 16)                              */
#define ADC2_SQ1_4_SQ3_Msk                (0x3f0000UL)              /*!< ADC2 SQ1_4: SQ3 (Bitfield-Mask: 0x3f)                 */
#define ADC2_SQ1_4_SQ2_Pos                (8UL)                     /*!< ADC2 SQ1_4: SQ2 (Bit 8)                               */
#define ADC2_SQ1_4_SQ2_Msk                (0x3f00UL)                /*!< ADC2 SQ1_4: SQ2 (Bitfield-Mask: 0x3f)                 */
#define ADC2_SQ1_4_SQ1_Pos                (0UL)                     /*!< ADC2 SQ1_4: SQ1 (Bit 0)                               */
#define ADC2_SQ1_4_SQ1_Msk                (0x3fUL)                  /*!< ADC2 SQ1_4: SQ1 (Bitfield-Mask: 0x3f)                 */
/* =======================================================  SQ1_8_int  ======================================================= */
#define ADC2_SQ1_8_int_SQ8_int_Pos        (28UL)                    /*!< ADC2 SQ1_8_int: SQ8_int (Bit 28)                      */
#define ADC2_SQ1_8_int_SQ8_int_Msk        (0xf0000000UL)            /*!< ADC2 SQ1_8_int: SQ8_int (Bitfield-Mask: 0x0f)         */
#define ADC2_SQ1_8_int_SQ7_int_Pos        (24UL)                    /*!< ADC2 SQ1_8_int: SQ7_int (Bit 24)                      */
#define ADC2_SQ1_8_int_SQ7_int_Msk        (0xf000000UL)             /*!< ADC2 SQ1_8_int: SQ7_int (Bitfield-Mask: 0x0f)         */
#define ADC2_SQ1_8_int_SQ6_int_Pos        (20UL)                    /*!< ADC2 SQ1_8_int: SQ6_int (Bit 20)                      */
#define ADC2_SQ1_8_int_SQ6_int_Msk        (0xf00000UL)              /*!< ADC2 SQ1_8_int: SQ6_int (Bitfield-Mask: 0x0f)         */
#define ADC2_SQ1_8_int_SQ5_int_Pos        (16UL)                    /*!< ADC2 SQ1_8_int: SQ5_int (Bit 16)                      */
#define ADC2_SQ1_8_int_SQ5_int_Msk        (0xf0000UL)               /*!< ADC2 SQ1_8_int: SQ5_int (Bitfield-Mask: 0x0f)         */
#define ADC2_SQ1_8_int_SQ4_int_Pos        (12UL)                    /*!< ADC2 SQ1_8_int: SQ4_int (Bit 12)                      */
#define ADC2_SQ1_8_int_SQ4_int_Msk        (0xf000UL)                /*!< ADC2 SQ1_8_int: SQ4_int (Bitfield-Mask: 0x0f)         */
#define ADC2_SQ1_8_int_SQ3_int_Pos        (8UL)                     /*!< ADC2 SQ1_8_int: SQ3_int (Bit 8)                       */
#define ADC2_SQ1_8_int_SQ3_int_Msk        (0xf00UL)                 /*!< ADC2 SQ1_8_int: SQ3_int (Bitfield-Mask: 0x0f)         */
#define ADC2_SQ1_8_int_SQ2_int_Pos        (4UL)                     /*!< ADC2 SQ1_8_int: SQ2_int (Bit 4)                       */
#define ADC2_SQ1_8_int_SQ2_int_Msk        (0xf0UL)                  /*!< ADC2 SQ1_8_int: SQ2_int (Bitfield-Mask: 0x0f)         */
#define ADC2_SQ1_8_int_SQ1_int_Pos        (0UL)                     /*!< ADC2 SQ1_8_int: SQ1_int (Bit 0)                       */
#define ADC2_SQ1_8_int_SQ1_int_Msk        (0xfUL)                   /*!< ADC2 SQ1_8_int: SQ1_int (Bitfield-Mask: 0x0f)         */
/* =========================================================  SQ5_8  ========================================================= */
#define ADC2_SQ5_8_SQ8_Pos                (24UL)                    /*!< ADC2 SQ5_8: SQ8 (Bit 24)                              */
#define ADC2_SQ5_8_SQ8_Msk                (0x3f000000UL)            /*!< ADC2 SQ5_8: SQ8 (Bitfield-Mask: 0x3f)                 */
#define ADC2_SQ5_8_SQ7_Pos                (16UL)                    /*!< ADC2 SQ5_8: SQ7 (Bit 16)                              */
#define ADC2_SQ5_8_SQ7_Msk                (0x3f0000UL)              /*!< ADC2 SQ5_8: SQ7 (Bitfield-Mask: 0x3f)                 */
#define ADC2_SQ5_8_SQ6_Pos                (8UL)                     /*!< ADC2 SQ5_8: SQ6 (Bit 8)                               */
#define ADC2_SQ5_8_SQ6_Msk                (0x3f00UL)                /*!< ADC2 SQ5_8: SQ6 (Bitfield-Mask: 0x3f)                 */
#define ADC2_SQ5_8_SQ5_Pos                (0UL)                     /*!< ADC2 SQ5_8: SQ5 (Bit 0)                               */
#define ADC2_SQ5_8_SQ5_Msk                (0x3fUL)                  /*!< ADC2 SQ5_8: SQ5 (Bitfield-Mask: 0x3f)                 */
/* ========================================================  SQ9_10  ========================================================= */
#define ADC2_SQ9_10_SQ10_Pos              (8UL)                     /*!< ADC2 SQ9_10: SQ10 (Bit 8)                             */
#define ADC2_SQ9_10_SQ10_Msk              (0x3f00UL)                /*!< ADC2 SQ9_10: SQ10 (Bitfield-Mask: 0x3f)               */
#define ADC2_SQ9_10_SQ9_Pos               (0UL)                     /*!< ADC2 SQ9_10: SQ9 (Bit 0)                              */
#define ADC2_SQ9_10_SQ9_Msk               (0x3fUL)                  /*!< ADC2 SQ9_10: SQ9 (Bitfield-Mask: 0x3f)                */
/* ======================================================  SQ9_10_int  ======================================================= */
#define ADC2_SQ9_10_int_SQ10_int_Pos      (4UL)                     /*!< ADC2 SQ9_10_int: SQ10_int (Bit 4)                     */
#define ADC2_SQ9_10_int_SQ10_int_Msk      (0xf0UL)                  /*!< ADC2 SQ9_10_int: SQ10_int (Bitfield-Mask: 0x0f)       */
#define ADC2_SQ9_10_int_SQ9_int_Pos       (0UL)                     /*!< ADC2 SQ9_10_int: SQ9_int (Bit 0)                      */
#define ADC2_SQ9_10_int_SQ9_int_Msk       (0xfUL)                   /*!< ADC2 SQ9_10_int: SQ9_int (Bitfield-Mask: 0x0f)        */
/* =========================================================  SQ_FB  ========================================================= */
#define ADC2_SQ_FB_CHx_Pos                (16UL)                    /*!< ADC2 SQ_FB: CHx (Bit 16)                              */
#define ADC2_SQ_FB_CHx_Msk                (0x1f0000UL)              /*!< ADC2 SQ_FB: CHx (Bitfield-Mask: 0x1f)                 */
#define ADC2_SQ_FB_SQx_Pos                (11UL)                    /*!< ADC2 SQ_FB: SQx (Bit 11)                              */
#define ADC2_SQ_FB_SQx_Msk                (0x7800UL)                /*!< ADC2 SQ_FB: SQx (Bitfield-Mask: 0x0f)                 */
#define ADC2_SQ_FB_ESM_ACTIVE_Pos         (10UL)                    /*!< ADC2 SQ_FB: ESM_ACTIVE (Bit 10)                       */
#define ADC2_SQ_FB_ESM_ACTIVE_Msk         (0x400UL)                 /*!< ADC2 SQ_FB: ESM_ACTIVE (Bitfield-Mask: 0x01)          */
#define ADC2_SQ_FB_EIM_ACTIVE_Pos         (9UL)                     /*!< ADC2 SQ_FB: EIM_ACTIVE (Bit 9)                        */
#define ADC2_SQ_FB_EIM_ACTIVE_Msk         (0x200UL)                 /*!< ADC2 SQ_FB: EIM_ACTIVE (Bitfield-Mask: 0x01)          */
#define ADC2_SQ_FB_SQ_STOP_Pos            (8UL)                     /*!< ADC2 SQ_FB: SQ_STOP (Bit 8)                           */
#define ADC2_SQ_FB_SQ_STOP_Msk            (0x100UL)                 /*!< ADC2 SQ_FB: SQ_STOP (Bitfield-Mask: 0x01)             */
#define ADC2_SQ_FB_SQ_FB_Pos              (0UL)                     /*!< ADC2 SQ_FB: SQ_FB (Bit 0)                             */
#define ADC2_SQ_FB_SQ_FB_Msk              (0xfUL)                   /*!< ADC2 SQ_FB: SQ_FB (Bitfield-Mask: 0x0f)               */
/* ======================================================  TH0_3_LOWER  ====================================================== */
#define ADC2_TH0_3_LOWER_CH3_Pos          (24UL)                    /*!< ADC2 TH0_3_LOWER: CH3 (Bit 24)                        */
#define ADC2_TH0_3_LOWER_CH3_Msk          (0xff000000UL)            /*!< ADC2 TH0_3_LOWER: CH3 (Bitfield-Mask: 0xff)           */
#define ADC2_TH0_3_LOWER_CH2_Pos          (16UL)                    /*!< ADC2 TH0_3_LOWER: CH2 (Bit 16)                        */
#define ADC2_TH0_3_LOWER_CH2_Msk          (0xff0000UL)              /*!< ADC2 TH0_3_LOWER: CH2 (Bitfield-Mask: 0xff)           */
#define ADC2_TH0_3_LOWER_CH1_Pos          (8UL)                     /*!< ADC2 TH0_3_LOWER: CH1 (Bit 8)                         */
#define ADC2_TH0_3_LOWER_CH1_Msk          (0xff00UL)                /*!< ADC2 TH0_3_LOWER: CH1 (Bitfield-Mask: 0xff)           */
#define ADC2_TH0_3_LOWER_CH0_Pos          (0UL)                     /*!< ADC2 TH0_3_LOWER: CH0 (Bit 0)                         */
#define ADC2_TH0_3_LOWER_CH0_Msk          (0xffUL)                  /*!< ADC2 TH0_3_LOWER: CH0 (Bitfield-Mask: 0xff)           */
/* ======================================================  TH0_3_UPPER  ====================================================== */
#define ADC2_TH0_3_UPPER_CH3_Pos          (24UL)                    /*!< ADC2 TH0_3_UPPER: CH3 (Bit 24)                        */
#define ADC2_TH0_3_UPPER_CH3_Msk          (0xff000000UL)            /*!< ADC2 TH0_3_UPPER: CH3 (Bitfield-Mask: 0xff)           */
#define ADC2_TH0_3_UPPER_CH2_Pos          (16UL)                    /*!< ADC2 TH0_3_UPPER: CH2 (Bit 16)                        */
#define ADC2_TH0_3_UPPER_CH2_Msk          (0xff0000UL)              /*!< ADC2 TH0_3_UPPER: CH2 (Bitfield-Mask: 0xff)           */
#define ADC2_TH0_3_UPPER_CH1_Pos          (8UL)                     /*!< ADC2 TH0_3_UPPER: CH1 (Bit 8)                         */
#define ADC2_TH0_3_UPPER_CH1_Msk          (0xff00UL)                /*!< ADC2 TH0_3_UPPER: CH1 (Bitfield-Mask: 0xff)           */
#define ADC2_TH0_3_UPPER_CH0_Pos          (0UL)                     /*!< ADC2 TH0_3_UPPER: CH0 (Bit 0)                         */
#define ADC2_TH0_3_UPPER_CH0_Msk          (0xffUL)                  /*!< ADC2 TH0_3_UPPER: CH0 (Bitfield-Mask: 0xff)           */
/* ======================================================  TH4_5_LOWER  ====================================================== */
#define ADC2_TH4_5_LOWER_CH5_Pos          (8UL)                     /*!< ADC2 TH4_5_LOWER: CH5 (Bit 8)                         */
#define ADC2_TH4_5_LOWER_CH5_Msk          (0xff00UL)                /*!< ADC2 TH4_5_LOWER: CH5 (Bitfield-Mask: 0xff)           */
#define ADC2_TH4_5_LOWER_CH4_Pos          (0UL)                     /*!< ADC2 TH4_5_LOWER: CH4 (Bit 0)                         */
#define ADC2_TH4_5_LOWER_CH4_Msk          (0xffUL)                  /*!< ADC2 TH4_5_LOWER: CH4 (Bitfield-Mask: 0xff)           */
/* ======================================================  TH4_5_UPPER  ====================================================== */
#define ADC2_TH4_5_UPPER_CH5_Pos          (8UL)                     /*!< ADC2 TH4_5_UPPER: CH5 (Bit 8)                         */
#define ADC2_TH4_5_UPPER_CH5_Msk          (0xff00UL)                /*!< ADC2 TH4_5_UPPER: CH5 (Bitfield-Mask: 0xff)           */
#define ADC2_TH4_5_UPPER_CH4_Pos          (0UL)                     /*!< ADC2 TH4_5_UPPER: CH4 (Bit 0)                         */
#define ADC2_TH4_5_UPPER_CH4_Msk          (0xffUL)                  /*!< ADC2 TH4_5_UPPER: CH4 (Bitfield-Mask: 0xff)           */
/* ======================================================  TH6_9_LOWER  ====================================================== */
#define ADC2_TH6_9_LOWER_CH9_Pos          (24UL)                    /*!< ADC2 TH6_9_LOWER: CH9 (Bit 24)                        */
#define ADC2_TH6_9_LOWER_CH9_Msk          (0xff000000UL)            /*!< ADC2 TH6_9_LOWER: CH9 (Bitfield-Mask: 0xff)           */
#define ADC2_TH6_9_LOWER_CH8_Pos          (16UL)                    /*!< ADC2 TH6_9_LOWER: CH8 (Bit 16)                        */
#define ADC2_TH6_9_LOWER_CH8_Msk          (0xff0000UL)              /*!< ADC2 TH6_9_LOWER: CH8 (Bitfield-Mask: 0xff)           */
#define ADC2_TH6_9_LOWER_CH7_Pos          (8UL)                     /*!< ADC2 TH6_9_LOWER: CH7 (Bit 8)                         */
#define ADC2_TH6_9_LOWER_CH7_Msk          (0xff00UL)                /*!< ADC2 TH6_9_LOWER: CH7 (Bitfield-Mask: 0xff)           */
#define ADC2_TH6_9_LOWER_CH6_Pos          (0UL)                     /*!< ADC2 TH6_9_LOWER: CH6 (Bit 0)                         */
#define ADC2_TH6_9_LOWER_CH6_Msk          (0xffUL)                  /*!< ADC2 TH6_9_LOWER: CH6 (Bitfield-Mask: 0xff)           */
/* ======================================================  TH6_9_UPPER  ====================================================== */
#define ADC2_TH6_9_UPPER_CH9_Pos          (24UL)                    /*!< ADC2 TH6_9_UPPER: CH9 (Bit 24)                        */
#define ADC2_TH6_9_UPPER_CH9_Msk          (0xff000000UL)            /*!< ADC2 TH6_9_UPPER: CH9 (Bitfield-Mask: 0xff)           */
#define ADC2_TH6_9_UPPER_CH8_Pos          (16UL)                    /*!< ADC2 TH6_9_UPPER: CH8 (Bit 16)                        */
#define ADC2_TH6_9_UPPER_CH8_Msk          (0xff0000UL)              /*!< ADC2 TH6_9_UPPER: CH8 (Bitfield-Mask: 0xff)           */
#define ADC2_TH6_9_UPPER_CH7_Pos          (8UL)                     /*!< ADC2 TH6_9_UPPER: CH7 (Bit 8)                         */
#define ADC2_TH6_9_UPPER_CH7_Msk          (0xff00UL)                /*!< ADC2 TH6_9_UPPER: CH7 (Bitfield-Mask: 0xff)           */
#define ADC2_TH6_9_UPPER_CH6_Pos          (0UL)                     /*!< ADC2 TH6_9_UPPER: CH6 (Bit 0)                         */
#define ADC2_TH6_9_UPPER_CH6_Msk          (0xffUL)                  /*!< ADC2 TH6_9_UPPER: CH6 (Bitfield-Mask: 0xff)           */


/* =========================================================================================================================== */
/* ================                                           ADC34                                           ================ */
/* =========================================================================================================================== */

/* =======================================================  CTRL_STS  ======================================================== */
#define ADC34_CTRL_STS_ADC4_OSR_Pos       (28UL)                    /*!< ADC34 CTRL_STS: ADC4_OSR (Bit 28)                     */
#define ADC34_CTRL_STS_ADC4_OSR_Msk       (0xf0000000UL)            /*!< ADC34 CTRL_STS: ADC4_OSR (Bitfield-Mask: 0x0f)        */
#define ADC34_CTRL_STS_ADC34_DITHVAL_Pos  (24UL)                    /*!< ADC34 CTRL_STS: ADC34_DITHVAL (Bit 24)                */
#define ADC34_CTRL_STS_ADC34_DITHVAL_Msk  (0xf000000UL)             /*!< ADC34 CTRL_STS: ADC34_DITHVAL (Bitfield-Mask: 0x0f)   */
#define ADC34_CTRL_STS_ADC34_DITHEN_Pos   (23UL)                    /*!< ADC34 CTRL_STS: ADC34_DITHEN (Bit 23)                 */
#define ADC34_CTRL_STS_ADC34_DITHEN_Msk   (0x800000UL)              /*!< ADC34 CTRL_STS: ADC34_DITHEN (Bitfield-Mask: 0x01)    */
#define ADC34_CTRL_STS_ADC34_EoC_CNT_Pos  (21UL)                    /*!< ADC34 CTRL_STS: ADC34_EoC_CNT (Bit 21)                */
#define ADC34_CTRL_STS_ADC34_EoC_CNT_Msk  (0x600000UL)              /*!< ADC34 CTRL_STS: ADC34_EoC_CNT (Bitfield-Mask: 0x03)   */
#define ADC34_CTRL_STS_ADC4_EoC_STS_Pos   (20UL)                    /*!< ADC34 CTRL_STS: ADC4_EoC_STS (Bit 20)                 */
#define ADC34_CTRL_STS_ADC4_EoC_STS_Msk   (0x100000UL)              /*!< ADC34 CTRL_STS: ADC4_EoC_STS (Bitfield-Mask: 0x01)    */
#define ADC34_CTRL_STS_ADC4_SOC_Pos       (18UL)                    /*!< ADC34 CTRL_STS: ADC4_SOC (Bit 18)                     */
#define ADC34_CTRL_STS_ADC4_SOC_Msk       (0x40000UL)               /*!< ADC34 CTRL_STS: ADC4_SOC (Bitfield-Mask: 0x01)        */
#define ADC34_CTRL_STS_ADC4_OFS_MEAS_EN_Pos (17UL)                  /*!< ADC34 CTRL_STS: ADC4_OFS_MEAS_EN (Bit 17)             */
#define ADC34_CTRL_STS_ADC4_OFS_MEAS_EN_Msk (0x20000UL)             /*!< ADC34 CTRL_STS: ADC4_OFS_MEAS_EN (Bitfield-Mask: 0x01) */
#define ADC34_CTRL_STS_ADC4_EN_Pos        (16UL)                    /*!< ADC34 CTRL_STS: ADC4_EN (Bit 16)                      */
#define ADC34_CTRL_STS_ADC4_EN_Msk        (0x10000UL)               /*!< ADC34 CTRL_STS: ADC4_EN (Bitfield-Mask: 0x01)         */
#define ADC34_CTRL_STS_ADC3_OSR_Pos       (12UL)                    /*!< ADC34 CTRL_STS: ADC3_OSR (Bit 12)                     */
#define ADC34_CTRL_STS_ADC3_OSR_Msk       (0xf000UL)                /*!< ADC34 CTRL_STS: ADC3_OSR (Bitfield-Mask: 0x0f)        */
#define ADC34_CTRL_STS_ADC34_REF_SEL_Pos  (11UL)                    /*!< ADC34 CTRL_STS: ADC34_REF_SEL (Bit 11)                */
#define ADC34_CTRL_STS_ADC34_REF_SEL_Msk  (0x800UL)                 /*!< ADC34 CTRL_STS: ADC34_REF_SEL (Bitfield-Mask: 0x01)   */
#define ADC34_CTRL_STS_ADC34_DREQ_SEL_Pos (5UL)                     /*!< ADC34 CTRL_STS: ADC34_DREQ_SEL (Bit 5)                */
#define ADC34_CTRL_STS_ADC34_DREQ_SEL_Msk (0x60UL)                  /*!< ADC34 CTRL_STS: ADC34_DREQ_SEL (Bitfield-Mask: 0x03)  */
#define ADC34_CTRL_STS_ADC3_EoC_STS_Pos   (4UL)                     /*!< ADC34 CTRL_STS: ADC3_EoC_STS (Bit 4)                  */
#define ADC34_CTRL_STS_ADC3_EoC_STS_Msk   (0x10UL)                  /*!< ADC34 CTRL_STS: ADC3_EoC_STS (Bitfield-Mask: 0x01)    */
#define ADC34_CTRL_STS_ADC3_SOC_Pos       (2UL)                     /*!< ADC34 CTRL_STS: ADC3_SOC (Bit 2)                      */
#define ADC34_CTRL_STS_ADC3_SOC_Msk       (0x4UL)                   /*!< ADC34 CTRL_STS: ADC3_SOC (Bitfield-Mask: 0x01)        */
#define ADC34_CTRL_STS_ADC3_OFS_MEAS_EN_Pos (1UL)                   /*!< ADC34 CTRL_STS: ADC3_OFS_MEAS_EN (Bit 1)              */
#define ADC34_CTRL_STS_ADC3_OFS_MEAS_EN_Msk (0x2UL)                 /*!< ADC34 CTRL_STS: ADC3_OFS_MEAS_EN (Bitfield-Mask: 0x01) */
#define ADC34_CTRL_STS_ADC3_EN_Pos        (0UL)                     /*!< ADC34 CTRL_STS: ADC3_EN (Bit 0)                       */
#define ADC34_CTRL_STS_ADC3_EN_Msk        (0x1UL)                   /*!< ADC34 CTRL_STS: ADC3_EN (Bitfield-Mask: 0x01)         */
/* =========================================================  RESU  ========================================================== */
#define ADC34_RESU_ADC4_RESU_Pos          (16UL)                    /*!< ADC34 RESU: ADC4_RESU (Bit 16)                        */
#define ADC34_RESU_ADC4_RESU_Msk          (0xffff0000UL)            /*!< ADC34 RESU: ADC4_RESU (Bitfield-Mask: 0xffff)         */
#define ADC34_RESU_ADC3_RESU_Pos          (0UL)                     /*!< ADC34 RESU: ADC3_RESU (Bit 0)                         */
#define ADC34_RESU_ADC3_RESU_Msk          (0xffffUL)                /*!< ADC34 RESU: ADC3_RESU (Bitfield-Mask: 0xffff)         */


/* =========================================================================================================================== */
/* ================                                           BDRV                                            ================ */
/* =========================================================================================================================== */

/* ======================================================  CP_CLK_CTRL  ====================================================== */
#define BDRV_CP_CLK_CTRL_CPCLK_EN_Pos     (15UL)                    /*!< BDRV CP_CLK_CTRL: CPCLK_EN (Bit 15)                   */
#define BDRV_CP_CLK_CTRL_CPCLK_EN_Msk     (0x8000UL)                /*!< BDRV CP_CLK_CTRL: CPCLK_EN (Bitfield-Mask: 0x01)      */
#define BDRV_CP_CLK_CTRL_F_CP_Pos         (13UL)                    /*!< BDRV CP_CLK_CTRL: F_CP (Bit 13)                       */
#define BDRV_CP_CLK_CTRL_F_CP_Msk         (0x6000UL)                /*!< BDRV CP_CLK_CTRL: F_CP (Bitfield-Mask: 0x03)          */
#define BDRV_CP_CLK_CTRL_DITH_UPPER_Pos   (8UL)                     /*!< BDRV CP_CLK_CTRL: DITH_UPPER (Bit 8)                  */
#define BDRV_CP_CLK_CTRL_DITH_UPPER_Msk   (0x1f00UL)                /*!< BDRV CP_CLK_CTRL: DITH_UPPER (Bitfield-Mask: 0x1f)    */
#define BDRV_CP_CLK_CTRL_DITH_LOWER_Pos   (0UL)                     /*!< BDRV CP_CLK_CTRL: DITH_LOWER (Bit 0)                  */
#define BDRV_CP_CLK_CTRL_DITH_LOWER_Msk   (0x1fUL)                  /*!< BDRV CP_CLK_CTRL: DITH_LOWER (Bitfield-Mask: 0x1f)    */
/* ======================================================  CP_CTRL_STS  ====================================================== */
#define BDRV_CP_CTRL_STS_VTHVCP9V_TRIM_Pos (26UL)                   /*!< BDRV CP_CTRL_STS: VTHVCP9V_TRIM (Bit 26)              */
#define BDRV_CP_CTRL_STS_VTHVCP9V_TRIM_Msk (0xc000000UL)            /*!< BDRV CP_CTRL_STS: VTHVCP9V_TRIM (Bitfield-Mask: 0x03) */
#define BDRV_CP_CTRL_STS_VCP9V_SET_Pos    (25UL)                    /*!< BDRV CP_CTRL_STS: VCP9V_SET (Bit 25)                  */
#define BDRV_CP_CTRL_STS_VCP9V_SET_Msk    (0x2000000UL)             /*!< BDRV CP_CTRL_STS: VCP9V_SET (Bitfield-Mask: 0x01)     */
#define BDRV_CP_CTRL_STS_CPLOPWRM_EN_Pos  (24UL)                    /*!< BDRV CP_CTRL_STS: CPLOPWRM_EN (Bit 24)                */
#define BDRV_CP_CTRL_STS_CPLOPWRM_EN_Msk  (0x1000000UL)             /*!< BDRV CP_CTRL_STS: CPLOPWRM_EN (Bitfield-Mask: 0x01)   */
#define BDRV_CP_CTRL_STS_VSD_UPTH_STS_Pos (23UL)                    /*!< BDRV CP_CTRL_STS: VSD_UPTH_STS (Bit 23)               */
#define BDRV_CP_CTRL_STS_VSD_UPTH_STS_Msk (0x800000UL)              /*!< BDRV CP_CTRL_STS: VSD_UPTH_STS (Bitfield-Mask: 0x01)  */
#define BDRV_CP_CTRL_STS_DRVx_VSDUP_DIS_Pos (22UL)                  /*!< BDRV CP_CTRL_STS: DRVx_VSDUP_DIS (Bit 22)             */
#define BDRV_CP_CTRL_STS_DRVx_VSDUP_DIS_Msk (0x400000UL)            /*!< BDRV CP_CTRL_STS: DRVx_VSDUP_DIS (Bitfield-Mask: 0x01) */
#define BDRV_CP_CTRL_STS_VSD_LOTH_STS_Pos (21UL)                    /*!< BDRV CP_CTRL_STS: VSD_LOTH_STS (Bit 21)               */
#define BDRV_CP_CTRL_STS_VSD_LOTH_STS_Msk (0x200000UL)              /*!< BDRV CP_CTRL_STS: VSD_LOTH_STS (Bitfield-Mask: 0x01)  */
#define BDRV_CP_CTRL_STS_DRVx_VSDLO_DIS_Pos (20UL)                  /*!< BDRV CP_CTRL_STS: DRVx_VSDLO_DIS (Bit 20)             */
#define BDRV_CP_CTRL_STS_DRVx_VSDLO_DIS_Msk (0x100000UL)            /*!< BDRV CP_CTRL_STS: DRVx_VSDLO_DIS (Bitfield-Mask: 0x01) */
#define BDRV_CP_CTRL_STS_VCP_UPTH_STS_Pos (19UL)                    /*!< BDRV CP_CTRL_STS: VCP_UPTH_STS (Bit 19)               */
#define BDRV_CP_CTRL_STS_VCP_UPTH_STS_Msk (0x80000UL)               /*!< BDRV CP_CTRL_STS: VCP_UPTH_STS (Bitfield-Mask: 0x01)  */
#define BDRV_CP_CTRL_STS_DRVx_VCPUP_DIS_Pos (18UL)                  /*!< BDRV CP_CTRL_STS: DRVx_VCPUP_DIS (Bit 18)             */
#define BDRV_CP_CTRL_STS_DRVx_VCPUP_DIS_Msk (0x40000UL)             /*!< BDRV CP_CTRL_STS: DRVx_VCPUP_DIS (Bitfield-Mask: 0x01) */
#define BDRV_CP_CTRL_STS_VCP_LOTH1_STS_Pos (17UL)                   /*!< BDRV CP_CTRL_STS: VCP_LOTH1_STS (Bit 17)              */
#define BDRV_CP_CTRL_STS_VCP_LOTH1_STS_Msk (0x20000UL)              /*!< BDRV CP_CTRL_STS: VCP_LOTH1_STS (Bitfield-Mask: 0x01) */
#define BDRV_CP_CTRL_STS_DRVx_VCPLO_DIS_Pos (16UL)                  /*!< BDRV CP_CTRL_STS: DRVx_VCPLO_DIS (Bit 16)             */
#define BDRV_CP_CTRL_STS_DRVx_VCPLO_DIS_Msk (0x10000UL)             /*!< BDRV CP_CTRL_STS: DRVx_VCPLO_DIS (Bitfield-Mask: 0x01) */
#define BDRV_CP_CTRL_STS_VCP_LOWTH2_Pos   (8UL)                     /*!< BDRV CP_CTRL_STS: VCP_LOWTH2 (Bit 8)                  */
#define BDRV_CP_CTRL_STS_VCP_LOWTH2_Msk   (0x700UL)                 /*!< BDRV CP_CTRL_STS: VCP_LOWTH2 (Bitfield-Mask: 0x07)    */
#define BDRV_CP_CTRL_STS_VCP_LOTH2_STS_Pos (5UL)                    /*!< BDRV CP_CTRL_STS: VCP_LOTH2_STS (Bit 5)               */
#define BDRV_CP_CTRL_STS_VCP_LOTH2_STS_Msk (0x20UL)                 /*!< BDRV CP_CTRL_STS: VCP_LOTH2_STS (Bitfield-Mask: 0x01) */
#define BDRV_CP_CTRL_STS_CP_RDY_EN_Pos    (2UL)                     /*!< BDRV CP_CTRL_STS: CP_RDY_EN (Bit 2)                   */
#define BDRV_CP_CTRL_STS_CP_RDY_EN_Msk    (0x4UL)                   /*!< BDRV CP_CTRL_STS: CP_RDY_EN (Bitfield-Mask: 0x01)     */
#define BDRV_CP_CTRL_STS_CP_EN_Pos        (0UL)                     /*!< BDRV CP_CTRL_STS: CP_EN (Bit 0)                       */
#define BDRV_CP_CTRL_STS_CP_EN_Msk        (0x1UL)                   /*!< BDRV CP_CTRL_STS: CP_EN (Bitfield-Mask: 0x01)         */
/* =========================================================  CTRL1  ========================================================= */
#define BDRV_CTRL1_HS2_OC_DIS_Pos         (31UL)                    /*!< BDRV CTRL1: HS2_OC_DIS (Bit 31)                       */
#define BDRV_CTRL1_HS2_OC_DIS_Msk         (0x80000000UL)            /*!< BDRV CTRL1: HS2_OC_DIS (Bitfield-Mask: 0x01)          */
#define BDRV_CTRL1_HS2_OC_STS_Pos         (30UL)                    /*!< BDRV CTRL1: HS2_OC_STS (Bit 30)                       */
#define BDRV_CTRL1_HS2_OC_STS_Msk         (0x40000000UL)            /*!< BDRV CTRL1: HS2_OC_STS (Bitfield-Mask: 0x01)          */
#define BDRV_CTRL1_HS2_SUPERR_STS_Pos     (29UL)                    /*!< BDRV CTRL1: HS2_SUPERR_STS (Bit 29)                   */
#define BDRV_CTRL1_HS2_SUPERR_STS_Msk     (0x20000000UL)            /*!< BDRV CTRL1: HS2_SUPERR_STS (Bitfield-Mask: 0x01)      */
#define BDRV_CTRL1_HS2_DS_STS_Pos         (28UL)                    /*!< BDRV CTRL1: HS2_DS_STS (Bit 28)                       */
#define BDRV_CTRL1_HS2_DS_STS_Msk         (0x10000000UL)            /*!< BDRV CTRL1: HS2_DS_STS (Bitfield-Mask: 0x01)          */
#define BDRV_CTRL1_HS2_DCS_EN_Pos         (27UL)                    /*!< BDRV CTRL1: HS2_DCS_EN (Bit 27)                       */
#define BDRV_CTRL1_HS2_DCS_EN_Msk         (0x8000000UL)             /*!< BDRV CTRL1: HS2_DCS_EN (Bitfield-Mask: 0x01)          */
#define BDRV_CTRL1_HS2_ON_Pos             (26UL)                    /*!< BDRV CTRL1: HS2_ON (Bit 26)                           */
#define BDRV_CTRL1_HS2_ON_Msk             (0x4000000UL)             /*!< BDRV CTRL1: HS2_ON (Bitfield-Mask: 0x01)              */
#define BDRV_CTRL1_HS2_PWM_Pos            (25UL)                    /*!< BDRV CTRL1: HS2_PWM (Bit 25)                          */
#define BDRV_CTRL1_HS2_PWM_Msk            (0x2000000UL)             /*!< BDRV CTRL1: HS2_PWM (Bitfield-Mask: 0x01)             */
#define BDRV_CTRL1_HS2_EN_Pos             (24UL)                    /*!< BDRV CTRL1: HS2_EN (Bit 24)                           */
#define BDRV_CTRL1_HS2_EN_Msk             (0x1000000UL)             /*!< BDRV CTRL1: HS2_EN (Bitfield-Mask: 0x01)              */
#define BDRV_CTRL1_HS1_OC_DIS_Pos         (23UL)                    /*!< BDRV CTRL1: HS1_OC_DIS (Bit 23)                       */
#define BDRV_CTRL1_HS1_OC_DIS_Msk         (0x800000UL)              /*!< BDRV CTRL1: HS1_OC_DIS (Bitfield-Mask: 0x01)          */
#define BDRV_CTRL1_HS1_OC_STS_Pos         (22UL)                    /*!< BDRV CTRL1: HS1_OC_STS (Bit 22)                       */
#define BDRV_CTRL1_HS1_OC_STS_Msk         (0x400000UL)              /*!< BDRV CTRL1: HS1_OC_STS (Bitfield-Mask: 0x01)          */
#define BDRV_CTRL1_HS1_SUPERR_STS_Pos     (21UL)                    /*!< BDRV CTRL1: HS1_SUPERR_STS (Bit 21)                   */
#define BDRV_CTRL1_HS1_SUPERR_STS_Msk     (0x200000UL)              /*!< BDRV CTRL1: HS1_SUPERR_STS (Bitfield-Mask: 0x01)      */
#define BDRV_CTRL1_HS1_DS_STS_Pos         (20UL)                    /*!< BDRV CTRL1: HS1_DS_STS (Bit 20)                       */
#define BDRV_CTRL1_HS1_DS_STS_Msk         (0x100000UL)              /*!< BDRV CTRL1: HS1_DS_STS (Bitfield-Mask: 0x01)          */
#define BDRV_CTRL1_HS1_DCS_EN_Pos         (19UL)                    /*!< BDRV CTRL1: HS1_DCS_EN (Bit 19)                       */
#define BDRV_CTRL1_HS1_DCS_EN_Msk         (0x80000UL)               /*!< BDRV CTRL1: HS1_DCS_EN (Bitfield-Mask: 0x01)          */
#define BDRV_CTRL1_HS1_ON_Pos             (18UL)                    /*!< BDRV CTRL1: HS1_ON (Bit 18)                           */
#define BDRV_CTRL1_HS1_ON_Msk             (0x40000UL)               /*!< BDRV CTRL1: HS1_ON (Bitfield-Mask: 0x01)              */
#define BDRV_CTRL1_HS1_PWM_Pos            (17UL)                    /*!< BDRV CTRL1: HS1_PWM (Bit 17)                          */
#define BDRV_CTRL1_HS1_PWM_Msk            (0x20000UL)               /*!< BDRV CTRL1: HS1_PWM (Bitfield-Mask: 0x01)             */
#define BDRV_CTRL1_HS1_EN_Pos             (16UL)                    /*!< BDRV CTRL1: HS1_EN (Bit 16)                           */
#define BDRV_CTRL1_HS1_EN_Msk             (0x10000UL)               /*!< BDRV CTRL1: HS1_EN (Bitfield-Mask: 0x01)              */
#define BDRV_CTRL1_LS2_OC_DIS_Pos         (15UL)                    /*!< BDRV CTRL1: LS2_OC_DIS (Bit 15)                       */
#define BDRV_CTRL1_LS2_OC_DIS_Msk         (0x8000UL)                /*!< BDRV CTRL1: LS2_OC_DIS (Bitfield-Mask: 0x01)          */
#define BDRV_CTRL1_LS2_OC_STS_Pos         (14UL)                    /*!< BDRV CTRL1: LS2_OC_STS (Bit 14)                       */
#define BDRV_CTRL1_LS2_OC_STS_Msk         (0x4000UL)                /*!< BDRV CTRL1: LS2_OC_STS (Bitfield-Mask: 0x01)          */
#define BDRV_CTRL1_LS2_SUPERR_STS_Pos     (13UL)                    /*!< BDRV CTRL1: LS2_SUPERR_STS (Bit 13)                   */
#define BDRV_CTRL1_LS2_SUPERR_STS_Msk     (0x2000UL)                /*!< BDRV CTRL1: LS2_SUPERR_STS (Bitfield-Mask: 0x01)      */
#define BDRV_CTRL1_LS2_DS_STS_Pos         (12UL)                    /*!< BDRV CTRL1: LS2_DS_STS (Bit 12)                       */
#define BDRV_CTRL1_LS2_DS_STS_Msk         (0x1000UL)                /*!< BDRV CTRL1: LS2_DS_STS (Bitfield-Mask: 0x01)          */
#define BDRV_CTRL1_LS2_DCS_EN_Pos         (11UL)                    /*!< BDRV CTRL1: LS2_DCS_EN (Bit 11)                       */
#define BDRV_CTRL1_LS2_DCS_EN_Msk         (0x800UL)                 /*!< BDRV CTRL1: LS2_DCS_EN (Bitfield-Mask: 0x01)          */
#define BDRV_CTRL1_LS2_ON_Pos             (10UL)                    /*!< BDRV CTRL1: LS2_ON (Bit 10)                           */
#define BDRV_CTRL1_LS2_ON_Msk             (0x400UL)                 /*!< BDRV CTRL1: LS2_ON (Bitfield-Mask: 0x01)              */
#define BDRV_CTRL1_LS2_PWM_Pos            (9UL)                     /*!< BDRV CTRL1: LS2_PWM (Bit 9)                           */
#define BDRV_CTRL1_LS2_PWM_Msk            (0x200UL)                 /*!< BDRV CTRL1: LS2_PWM (Bitfield-Mask: 0x01)             */
#define BDRV_CTRL1_LS2_EN_Pos             (8UL)                     /*!< BDRV CTRL1: LS2_EN (Bit 8)                            */
#define BDRV_CTRL1_LS2_EN_Msk             (0x100UL)                 /*!< BDRV CTRL1: LS2_EN (Bitfield-Mask: 0x01)              */
#define BDRV_CTRL1_LS1_OC_DIS_Pos         (7UL)                     /*!< BDRV CTRL1: LS1_OC_DIS (Bit 7)                        */
#define BDRV_CTRL1_LS1_OC_DIS_Msk         (0x80UL)                  /*!< BDRV CTRL1: LS1_OC_DIS (Bitfield-Mask: 0x01)          */
#define BDRV_CTRL1_LS1_OC_STS_Pos         (6UL)                     /*!< BDRV CTRL1: LS1_OC_STS (Bit 6)                        */
#define BDRV_CTRL1_LS1_OC_STS_Msk         (0x40UL)                  /*!< BDRV CTRL1: LS1_OC_STS (Bitfield-Mask: 0x01)          */
#define BDRV_CTRL1_LS1_SUPERR_STS_Pos     (5UL)                     /*!< BDRV CTRL1: LS1_SUPERR_STS (Bit 5)                    */
#define BDRV_CTRL1_LS1_SUPERR_STS_Msk     (0x20UL)                  /*!< BDRV CTRL1: LS1_SUPERR_STS (Bitfield-Mask: 0x01)      */
#define BDRV_CTRL1_LS1_DS_STS_Pos         (4UL)                     /*!< BDRV CTRL1: LS1_DS_STS (Bit 4)                        */
#define BDRV_CTRL1_LS1_DS_STS_Msk         (0x10UL)                  /*!< BDRV CTRL1: LS1_DS_STS (Bitfield-Mask: 0x01)          */
#define BDRV_CTRL1_LS1_DCS_EN_Pos         (3UL)                     /*!< BDRV CTRL1: LS1_DCS_EN (Bit 3)                        */
#define BDRV_CTRL1_LS1_DCS_EN_Msk         (0x8UL)                   /*!< BDRV CTRL1: LS1_DCS_EN (Bitfield-Mask: 0x01)          */
#define BDRV_CTRL1_LS1_ON_Pos             (2UL)                     /*!< BDRV CTRL1: LS1_ON (Bit 2)                            */
#define BDRV_CTRL1_LS1_ON_Msk             (0x4UL)                   /*!< BDRV CTRL1: LS1_ON (Bitfield-Mask: 0x01)              */
#define BDRV_CTRL1_LS1_PWM_Pos            (1UL)                     /*!< BDRV CTRL1: LS1_PWM (Bit 1)                           */
#define BDRV_CTRL1_LS1_PWM_Msk            (0x2UL)                   /*!< BDRV CTRL1: LS1_PWM (Bitfield-Mask: 0x01)             */
#define BDRV_CTRL1_LS1_EN_Pos             (0UL)                     /*!< BDRV CTRL1: LS1_EN (Bit 0)                            */
#define BDRV_CTRL1_LS1_EN_Msk             (0x1UL)                   /*!< BDRV CTRL1: LS1_EN (Bitfield-Mask: 0x01)              */
/* =========================================================  CTRL2  ========================================================= */
#define BDRV_CTRL2_DLY_DIAG_DIRSEL_Pos    (31UL)                    /*!< BDRV CTRL2: DLY_DIAG_DIRSEL (Bit 31)                  */
#define BDRV_CTRL2_DLY_DIAG_DIRSEL_Msk    (0x80000000UL)            /*!< BDRV CTRL2: DLY_DIAG_DIRSEL (Bitfield-Mask: 0x01)     */
#define BDRV_CTRL2_DLY_DIAG_CHSEL_Pos     (28UL)                    /*!< BDRV CTRL2: DLY_DIAG_CHSEL (Bit 28)                   */
#define BDRV_CTRL2_DLY_DIAG_CHSEL_Msk     (0x70000000UL)            /*!< BDRV CTRL2: DLY_DIAG_CHSEL (Bitfield-Mask: 0x07)      */
#define BDRV_CTRL2_DLY_DIAG_STS_Pos       (27UL)                    /*!< BDRV CTRL2: DLY_DIAG_STS (Bit 27)                     */
#define BDRV_CTRL2_DLY_DIAG_STS_Msk       (0x8000000UL)             /*!< BDRV CTRL2: DLY_DIAG_STS (Bitfield-Mask: 0x01)        */
#define BDRV_CTRL2_DLY_DIAG_SCLR_Pos      (26UL)                    /*!< BDRV CTRL2: DLY_DIAG_SCLR (Bit 26)                    */
#define BDRV_CTRL2_DLY_DIAG_SCLR_Msk      (0x4000000UL)             /*!< BDRV CTRL2: DLY_DIAG_SCLR (Bitfield-Mask: 0x01)       */
#define BDRV_CTRL2_DLY_DIAG_TIM_Pos       (16UL)                    /*!< BDRV CTRL2: DLY_DIAG_TIM (Bit 16)                     */
#define BDRV_CTRL2_DLY_DIAG_TIM_Msk       (0x3ff0000UL)             /*!< BDRV CTRL2: DLY_DIAG_TIM (Bitfield-Mask: 0x3ff)       */
#define BDRV_CTRL2_HS3_OC_DIS_Pos         (15UL)                    /*!< BDRV CTRL2: HS3_OC_DIS (Bit 15)                       */
#define BDRV_CTRL2_HS3_OC_DIS_Msk         (0x8000UL)                /*!< BDRV CTRL2: HS3_OC_DIS (Bitfield-Mask: 0x01)          */
#define BDRV_CTRL2_HS3_OC_STS_Pos         (14UL)                    /*!< BDRV CTRL2: HS3_OC_STS (Bit 14)                       */
#define BDRV_CTRL2_HS3_OC_STS_Msk         (0x4000UL)                /*!< BDRV CTRL2: HS3_OC_STS (Bitfield-Mask: 0x01)          */
#define BDRV_CTRL2_HS3_SUPERR_STS_Pos     (13UL)                    /*!< BDRV CTRL2: HS3_SUPERR_STS (Bit 13)                   */
#define BDRV_CTRL2_HS3_SUPERR_STS_Msk     (0x2000UL)                /*!< BDRV CTRL2: HS3_SUPERR_STS (Bitfield-Mask: 0x01)      */
#define BDRV_CTRL2_HS3_DS_STS_Pos         (12UL)                    /*!< BDRV CTRL2: HS3_DS_STS (Bit 12)                       */
#define BDRV_CTRL2_HS3_DS_STS_Msk         (0x1000UL)                /*!< BDRV CTRL2: HS3_DS_STS (Bitfield-Mask: 0x01)          */
#define BDRV_CTRL2_HS3_DCS_EN_Pos         (11UL)                    /*!< BDRV CTRL2: HS3_DCS_EN (Bit 11)                       */
#define BDRV_CTRL2_HS3_DCS_EN_Msk         (0x800UL)                 /*!< BDRV CTRL2: HS3_DCS_EN (Bitfield-Mask: 0x01)          */
#define BDRV_CTRL2_HS3_ON_Pos             (10UL)                    /*!< BDRV CTRL2: HS3_ON (Bit 10)                           */
#define BDRV_CTRL2_HS3_ON_Msk             (0x400UL)                 /*!< BDRV CTRL2: HS3_ON (Bitfield-Mask: 0x01)              */
#define BDRV_CTRL2_HS3_PWM_Pos            (9UL)                     /*!< BDRV CTRL2: HS3_PWM (Bit 9)                           */
#define BDRV_CTRL2_HS3_PWM_Msk            (0x200UL)                 /*!< BDRV CTRL2: HS3_PWM (Bitfield-Mask: 0x01)             */
#define BDRV_CTRL2_HS3_EN_Pos             (8UL)                     /*!< BDRV CTRL2: HS3_EN (Bit 8)                            */
#define BDRV_CTRL2_HS3_EN_Msk             (0x100UL)                 /*!< BDRV CTRL2: HS3_EN (Bitfield-Mask: 0x01)              */
#define BDRV_CTRL2_LS3_OC_DIS_Pos         (7UL)                     /*!< BDRV CTRL2: LS3_OC_DIS (Bit 7)                        */
#define BDRV_CTRL2_LS3_OC_DIS_Msk         (0x80UL)                  /*!< BDRV CTRL2: LS3_OC_DIS (Bitfield-Mask: 0x01)          */
#define BDRV_CTRL2_LS3_OC_STS_Pos         (6UL)                     /*!< BDRV CTRL2: LS3_OC_STS (Bit 6)                        */
#define BDRV_CTRL2_LS3_OC_STS_Msk         (0x40UL)                  /*!< BDRV CTRL2: LS3_OC_STS (Bitfield-Mask: 0x01)          */
#define BDRV_CTRL2_LS3_SUPERR_STS_Pos     (5UL)                     /*!< BDRV CTRL2: LS3_SUPERR_STS (Bit 5)                    */
#define BDRV_CTRL2_LS3_SUPERR_STS_Msk     (0x20UL)                  /*!< BDRV CTRL2: LS3_SUPERR_STS (Bitfield-Mask: 0x01)      */
#define BDRV_CTRL2_LS3_DS_STS_Pos         (4UL)                     /*!< BDRV CTRL2: LS3_DS_STS (Bit 4)                        */
#define BDRV_CTRL2_LS3_DS_STS_Msk         (0x10UL)                  /*!< BDRV CTRL2: LS3_DS_STS (Bitfield-Mask: 0x01)          */
#define BDRV_CTRL2_LS3_DCS_EN_Pos         (3UL)                     /*!< BDRV CTRL2: LS3_DCS_EN (Bit 3)                        */
#define BDRV_CTRL2_LS3_DCS_EN_Msk         (0x8UL)                   /*!< BDRV CTRL2: LS3_DCS_EN (Bitfield-Mask: 0x01)          */
#define BDRV_CTRL2_LS3_ON_Pos             (2UL)                     /*!< BDRV CTRL2: LS3_ON (Bit 2)                            */
#define BDRV_CTRL2_LS3_ON_Msk             (0x4UL)                   /*!< BDRV CTRL2: LS3_ON (Bitfield-Mask: 0x01)              */
#define BDRV_CTRL2_LS3_PWM_Pos            (1UL)                     /*!< BDRV CTRL2: LS3_PWM (Bit 1)                           */
#define BDRV_CTRL2_LS3_PWM_Msk            (0x2UL)                   /*!< BDRV CTRL2: LS3_PWM (Bitfield-Mask: 0x01)             */
#define BDRV_CTRL2_LS3_EN_Pos             (0UL)                     /*!< BDRV CTRL2: LS3_EN (Bit 0)                            */
#define BDRV_CTRL2_LS3_EN_Msk             (0x1UL)                   /*!< BDRV CTRL2: LS3_EN (Bitfield-Mask: 0x01)              */
/* =========================================================  CTRL3  ========================================================= */
#define BDRV_CTRL3_DRV_CCP_DIS_Pos        (26UL)                    /*!< BDRV CTRL3: DRV_CCP_DIS (Bit 26)                      */
#define BDRV_CTRL3_DRV_CCP_DIS_Msk        (0x4000000UL)             /*!< BDRV CTRL3: DRV_CCP_DIS (Bitfield-Mask: 0x01)         */
#define BDRV_CTRL3_DRV_CCP_TIMSEL_Pos     (24UL)                    /*!< BDRV CTRL3: DRV_CCP_TIMSEL (Bit 24)                   */
#define BDRV_CTRL3_DRV_CCP_TIMSEL_Msk     (0x3000000UL)             /*!< BDRV CTRL3: DRV_CCP_TIMSEL (Bitfield-Mask: 0x03)      */
#define BDRV_CTRL3_DSMONVTH_Pos           (16UL)                    /*!< BDRV CTRL3: DSMONVTH (Bit 16)                         */
#define BDRV_CTRL3_DSMONVTH_Msk           (0x70000UL)               /*!< BDRV CTRL3: DSMONVTH (Bitfield-Mask: 0x07)            */
#define BDRV_CTRL3_OFF_SEQ_EN_Pos         (15UL)                    /*!< BDRV CTRL3: OFF_SEQ_EN (Bit 15)                       */
#define BDRV_CTRL3_OFF_SEQ_EN_Msk         (0x8000UL)                /*!< BDRV CTRL3: OFF_SEQ_EN (Bitfield-Mask: 0x01)          */
#define BDRV_CTRL3_IDISCHARGEDIV2_N_Pos   (14UL)                    /*!< BDRV CTRL3: IDISCHARGEDIV2_N (Bit 14)                 */
#define BDRV_CTRL3_IDISCHARGEDIV2_N_Msk   (0x4000UL)                /*!< BDRV CTRL3: IDISCHARGEDIV2_N (Bitfield-Mask: 0x01)    */
#define BDRV_CTRL3_IDISCHARGE_TRIM_Pos    (8UL)                     /*!< BDRV CTRL3: IDISCHARGE_TRIM (Bit 8)                   */
#define BDRV_CTRL3_IDISCHARGE_TRIM_Msk    (0x1f00UL)                /*!< BDRV CTRL3: IDISCHARGE_TRIM (Bitfield-Mask: 0x1f)     */
#define BDRV_CTRL3_ON_SEQ_EN_Pos          (7UL)                     /*!< BDRV CTRL3: ON_SEQ_EN (Bit 7)                         */
#define BDRV_CTRL3_ON_SEQ_EN_Msk          (0x80UL)                  /*!< BDRV CTRL3: ON_SEQ_EN (Bitfield-Mask: 0x01)           */
#define BDRV_CTRL3_ICHARGEDIV2_N_Pos      (6UL)                     /*!< BDRV CTRL3: ICHARGEDIV2_N (Bit 6)                     */
#define BDRV_CTRL3_ICHARGEDIV2_N_Msk      (0x40UL)                  /*!< BDRV CTRL3: ICHARGEDIV2_N (Bitfield-Mask: 0x01)       */
#define BDRV_CTRL3_ICHARGE_TRIM_Pos       (0UL)                     /*!< BDRV CTRL3: ICHARGE_TRIM (Bit 0)                      */
#define BDRV_CTRL3_ICHARGE_TRIM_Msk       (0x1fUL)                  /*!< BDRV CTRL3: ICHARGE_TRIM (Bitfield-Mask: 0x1f)        */
/* =====================================================  OFF_SEQ_CTRL  ====================================================== */
#define BDRV_OFF_SEQ_CTRL_DRV_OFF_I_1_Pos (27UL)                    /*!< BDRV OFF_SEQ_CTRL: DRV_OFF_I_1 (Bit 27)               */
#define BDRV_OFF_SEQ_CTRL_DRV_OFF_I_1_Msk (0xf8000000UL)            /*!< BDRV OFF_SEQ_CTRL: DRV_OFF_I_1 (Bitfield-Mask: 0x1f)  */
#define BDRV_OFF_SEQ_CTRL_DRV_OFF_t_1_Pos (24UL)                    /*!< BDRV OFF_SEQ_CTRL: DRV_OFF_t_1 (Bit 24)               */
#define BDRV_OFF_SEQ_CTRL_DRV_OFF_t_1_Msk (0x7000000UL)             /*!< BDRV OFF_SEQ_CTRL: DRV_OFF_t_1 (Bitfield-Mask: 0x07)  */
#define BDRV_OFF_SEQ_CTRL_DRV_OFF_I_2_Pos (19UL)                    /*!< BDRV OFF_SEQ_CTRL: DRV_OFF_I_2 (Bit 19)               */
#define BDRV_OFF_SEQ_CTRL_DRV_OFF_I_2_Msk (0xf80000UL)              /*!< BDRV OFF_SEQ_CTRL: DRV_OFF_I_2 (Bitfield-Mask: 0x1f)  */
#define BDRV_OFF_SEQ_CTRL_DRV_OFF_t_2_Pos (16UL)                    /*!< BDRV OFF_SEQ_CTRL: DRV_OFF_t_2 (Bit 16)               */
#define BDRV_OFF_SEQ_CTRL_DRV_OFF_t_2_Msk (0x70000UL)               /*!< BDRV OFF_SEQ_CTRL: DRV_OFF_t_2 (Bitfield-Mask: 0x07)  */
#define BDRV_OFF_SEQ_CTRL_DRV_OFF_I_3_Pos (11UL)                    /*!< BDRV OFF_SEQ_CTRL: DRV_OFF_I_3 (Bit 11)               */
#define BDRV_OFF_SEQ_CTRL_DRV_OFF_I_3_Msk (0xf800UL)                /*!< BDRV OFF_SEQ_CTRL: DRV_OFF_I_3 (Bitfield-Mask: 0x1f)  */
#define BDRV_OFF_SEQ_CTRL_DRV_OFF_t_3_Pos (8UL)                     /*!< BDRV OFF_SEQ_CTRL: DRV_OFF_t_3 (Bit 8)                */
#define BDRV_OFF_SEQ_CTRL_DRV_OFF_t_3_Msk (0x700UL)                 /*!< BDRV OFF_SEQ_CTRL: DRV_OFF_t_3 (Bitfield-Mask: 0x07)  */
#define BDRV_OFF_SEQ_CTRL_DRV_OFF_I_4_Pos (3UL)                     /*!< BDRV OFF_SEQ_CTRL: DRV_OFF_I_4 (Bit 3)                */
#define BDRV_OFF_SEQ_CTRL_DRV_OFF_I_4_Msk (0xf8UL)                  /*!< BDRV OFF_SEQ_CTRL: DRV_OFF_I_4 (Bitfield-Mask: 0x1f)  */
#define BDRV_OFF_SEQ_CTRL_DRV_OFF_t_4_Pos (0UL)                     /*!< BDRV OFF_SEQ_CTRL: DRV_OFF_t_4 (Bit 0)                */
#define BDRV_OFF_SEQ_CTRL_DRV_OFF_t_4_Msk (0x7UL)                   /*!< BDRV OFF_SEQ_CTRL: DRV_OFF_t_4 (Bitfield-Mask: 0x07)  */
/* ======================================================  ON_SEQ_CTRL  ====================================================== */
#define BDRV_ON_SEQ_CTRL_DRV_ON_I_1_Pos   (27UL)                    /*!< BDRV ON_SEQ_CTRL: DRV_ON_I_1 (Bit 27)                 */
#define BDRV_ON_SEQ_CTRL_DRV_ON_I_1_Msk   (0xf8000000UL)            /*!< BDRV ON_SEQ_CTRL: DRV_ON_I_1 (Bitfield-Mask: 0x1f)    */
#define BDRV_ON_SEQ_CTRL_DRV_ON_t_1_Pos   (24UL)                    /*!< BDRV ON_SEQ_CTRL: DRV_ON_t_1 (Bit 24)                 */
#define BDRV_ON_SEQ_CTRL_DRV_ON_t_1_Msk   (0x7000000UL)             /*!< BDRV ON_SEQ_CTRL: DRV_ON_t_1 (Bitfield-Mask: 0x07)    */
#define BDRV_ON_SEQ_CTRL_DRV_ON_I_2_Pos   (19UL)                    /*!< BDRV ON_SEQ_CTRL: DRV_ON_I_2 (Bit 19)                 */
#define BDRV_ON_SEQ_CTRL_DRV_ON_I_2_Msk   (0xf80000UL)              /*!< BDRV ON_SEQ_CTRL: DRV_ON_I_2 (Bitfield-Mask: 0x1f)    */
#define BDRV_ON_SEQ_CTRL_DRV_ON_t_2_Pos   (16UL)                    /*!< BDRV ON_SEQ_CTRL: DRV_ON_t_2 (Bit 16)                 */
#define BDRV_ON_SEQ_CTRL_DRV_ON_t_2_Msk   (0x70000UL)               /*!< BDRV ON_SEQ_CTRL: DRV_ON_t_2 (Bitfield-Mask: 0x07)    */
#define BDRV_ON_SEQ_CTRL_DRV_ON_I_3_Pos   (11UL)                    /*!< BDRV ON_SEQ_CTRL: DRV_ON_I_3 (Bit 11)                 */
#define BDRV_ON_SEQ_CTRL_DRV_ON_I_3_Msk   (0xf800UL)                /*!< BDRV ON_SEQ_CTRL: DRV_ON_I_3 (Bitfield-Mask: 0x1f)    */
#define BDRV_ON_SEQ_CTRL_DRV_ON_t_3_Pos   (8UL)                     /*!< BDRV ON_SEQ_CTRL: DRV_ON_t_3 (Bit 8)                  */
#define BDRV_ON_SEQ_CTRL_DRV_ON_t_3_Msk   (0x700UL)                 /*!< BDRV ON_SEQ_CTRL: DRV_ON_t_3 (Bitfield-Mask: 0x07)    */
#define BDRV_ON_SEQ_CTRL_DRV_ON_I_4_Pos   (3UL)                     /*!< BDRV ON_SEQ_CTRL: DRV_ON_I_4 (Bit 3)                  */
#define BDRV_ON_SEQ_CTRL_DRV_ON_I_4_Msk   (0xf8UL)                  /*!< BDRV ON_SEQ_CTRL: DRV_ON_I_4 (Bitfield-Mask: 0x1f)    */
#define BDRV_ON_SEQ_CTRL_DRV_ON_t_4_Pos   (0UL)                     /*!< BDRV ON_SEQ_CTRL: DRV_ON_t_4 (Bit 0)                  */
#define BDRV_ON_SEQ_CTRL_DRV_ON_t_4_Msk   (0x7UL)                   /*!< BDRV ON_SEQ_CTRL: DRV_ON_t_4 (Bitfield-Mask: 0x07)    */
/* =======================================================  TRIM_DRVx  ======================================================= */
#define BDRV_TRIM_DRVx_CPLOW_TFILT_SEL_Pos (24UL)                   /*!< BDRV TRIM_DRVx: CPLOW_TFILT_SEL (Bit 24)              */
#define BDRV_TRIM_DRVx_CPLOW_TFILT_SEL_Msk (0x3000000UL)            /*!< BDRV TRIM_DRVx: CPLOW_TFILT_SEL (Bitfield-Mask: 0x03) */
#define BDRV_TRIM_DRVx_HS3DRV_OCSDN_DIS_Pos (23UL)                  /*!< BDRV TRIM_DRVx: HS3DRV_OCSDN_DIS (Bit 23)             */
#define BDRV_TRIM_DRVx_HS3DRV_OCSDN_DIS_Msk (0x800000UL)            /*!< BDRV TRIM_DRVx: HS3DRV_OCSDN_DIS (Bitfield-Mask: 0x01) */
#define BDRV_TRIM_DRVx_HS2DRV_OCSDN_DIS_Pos (22UL)                  /*!< BDRV TRIM_DRVx: HS2DRV_OCSDN_DIS (Bit 22)             */
#define BDRV_TRIM_DRVx_HS2DRV_OCSDN_DIS_Msk (0x400000UL)            /*!< BDRV TRIM_DRVx: HS2DRV_OCSDN_DIS (Bitfield-Mask: 0x01) */
#define BDRV_TRIM_DRVx_HS1DRV_OCSDN_DIS_Pos (21UL)                  /*!< BDRV TRIM_DRVx: HS1DRV_OCSDN_DIS (Bit 21)             */
#define BDRV_TRIM_DRVx_HS1DRV_OCSDN_DIS_Msk (0x200000UL)            /*!< BDRV TRIM_DRVx: HS1DRV_OCSDN_DIS (Bitfield-Mask: 0x01) */
#define BDRV_TRIM_DRVx_HS3DRV_FDISCHG_DIS_Pos (20UL)                /*!< BDRV TRIM_DRVx: HS3DRV_FDISCHG_DIS (Bit 20)           */
#define BDRV_TRIM_DRVx_HS3DRV_FDISCHG_DIS_Msk (0x100000UL)          /*!< BDRV TRIM_DRVx: HS3DRV_FDISCHG_DIS (Bitfield-Mask: 0x01) */
#define BDRV_TRIM_DRVx_HS2DRV_FDISCHG_DIS_Pos (19UL)                /*!< BDRV TRIM_DRVx: HS2DRV_FDISCHG_DIS (Bit 19)           */
#define BDRV_TRIM_DRVx_HS2DRV_FDISCHG_DIS_Msk (0x80000UL)           /*!< BDRV TRIM_DRVx: HS2DRV_FDISCHG_DIS (Bitfield-Mask: 0x01) */
#define BDRV_TRIM_DRVx_HS1DRV_FDISCHG_DIS_Pos (18UL)                /*!< BDRV TRIM_DRVx: HS1DRV_FDISCHG_DIS (Bit 18)           */
#define BDRV_TRIM_DRVx_HS1DRV_FDISCHG_DIS_Msk (0x40000UL)           /*!< BDRV TRIM_DRVx: HS1DRV_FDISCHG_DIS (Bitfield-Mask: 0x01) */
#define BDRV_TRIM_DRVx_HSDRV_DS_TFILT_SEL_Pos (16UL)                /*!< BDRV TRIM_DRVx: HSDRV_DS_TFILT_SEL (Bit 16)           */
#define BDRV_TRIM_DRVx_HSDRV_DS_TFILT_SEL_Msk (0x30000UL)           /*!< BDRV TRIM_DRVx: HSDRV_DS_TFILT_SEL (Bitfield-Mask: 0x03) */
#define BDRV_TRIM_DRVx_LS3DRV_OCSDN_DIS_Pos (15UL)                  /*!< BDRV TRIM_DRVx: LS3DRV_OCSDN_DIS (Bit 15)             */
#define BDRV_TRIM_DRVx_LS3DRV_OCSDN_DIS_Msk (0x8000UL)              /*!< BDRV TRIM_DRVx: LS3DRV_OCSDN_DIS (Bitfield-Mask: 0x01) */
#define BDRV_TRIM_DRVx_LS2DRV_OCSDN_DIS_Pos (14UL)                  /*!< BDRV TRIM_DRVx: LS2DRV_OCSDN_DIS (Bit 14)             */
#define BDRV_TRIM_DRVx_LS2DRV_OCSDN_DIS_Msk (0x4000UL)              /*!< BDRV TRIM_DRVx: LS2DRV_OCSDN_DIS (Bitfield-Mask: 0x01) */
#define BDRV_TRIM_DRVx_LS1DRV_OCSDN_DIS_Pos (13UL)                  /*!< BDRV TRIM_DRVx: LS1DRV_OCSDN_DIS (Bit 13)             */
#define BDRV_TRIM_DRVx_LS1DRV_OCSDN_DIS_Msk (0x2000UL)              /*!< BDRV TRIM_DRVx: LS1DRV_OCSDN_DIS (Bitfield-Mask: 0x01) */
#define BDRV_TRIM_DRVx_LS3DRV_FDISCHG_DIS_Pos (12UL)                /*!< BDRV TRIM_DRVx: LS3DRV_FDISCHG_DIS (Bit 12)           */
#define BDRV_TRIM_DRVx_LS3DRV_FDISCHG_DIS_Msk (0x1000UL)            /*!< BDRV TRIM_DRVx: LS3DRV_FDISCHG_DIS (Bitfield-Mask: 0x01) */
#define BDRV_TRIM_DRVx_LS2DRV_FDISCHG_DIS_Pos (11UL)                /*!< BDRV TRIM_DRVx: LS2DRV_FDISCHG_DIS (Bit 11)           */
#define BDRV_TRIM_DRVx_LS2DRV_FDISCHG_DIS_Msk (0x800UL)             /*!< BDRV TRIM_DRVx: LS2DRV_FDISCHG_DIS (Bitfield-Mask: 0x01) */
#define BDRV_TRIM_DRVx_LS1DRV_FDISCHG_DIS_Pos (10UL)                /*!< BDRV TRIM_DRVx: LS1DRV_FDISCHG_DIS (Bit 10)           */
#define BDRV_TRIM_DRVx_LS1DRV_FDISCHG_DIS_Msk (0x400UL)             /*!< BDRV TRIM_DRVx: LS1DRV_FDISCHG_DIS (Bitfield-Mask: 0x01) */
#define BDRV_TRIM_DRVx_LSDRV_DS_TFILT_SEL_Pos (8UL)                 /*!< BDRV TRIM_DRVx: LSDRV_DS_TFILT_SEL (Bit 8)            */
#define BDRV_TRIM_DRVx_LSDRV_DS_TFILT_SEL_Msk (0x300UL)             /*!< BDRV TRIM_DRVx: LSDRV_DS_TFILT_SEL (Bitfield-Mask: 0x03) */
#define BDRV_TRIM_DRVx_DRV_CCPTIMMUL_Pos  (5UL)                     /*!< BDRV TRIM_DRVx: DRV_CCPTIMMUL (Bit 5)                 */
#define BDRV_TRIM_DRVx_DRV_CCPTIMMUL_Msk  (0x60UL)                  /*!< BDRV TRIM_DRVx: DRV_CCPTIMMUL (Bitfield-Mask: 0x03)   */
#define BDRV_TRIM_DRVx_LS_HS_BT_TFILT_SEL_Pos (0UL)                 /*!< BDRV TRIM_DRVx: LS_HS_BT_TFILT_SEL (Bit 0)            */
#define BDRV_TRIM_DRVx_LS_HS_BT_TFILT_SEL_Msk (0x3UL)               /*!< BDRV TRIM_DRVx: LS_HS_BT_TFILT_SEL (Bitfield-Mask: 0x03) */


/* =========================================================================================================================== */
/* ================                                           CCU6                                            ================ */
/* =========================================================================================================================== */

/* =========================================================  CC60R  ========================================================= */
#define CCU6_CC60R_CCV_Pos                (0UL)                     /*!< CCU6 CC60R: CCV (Bit 0)                               */
#define CCU6_CC60R_CCV_Msk                (0xffffUL)                /*!< CCU6 CC60R: CCV (Bitfield-Mask: 0xffff)               */
/* ========================================================  CC60SR  ========================================================= */
#define CCU6_CC60SR_CCS_Pos               (0UL)                     /*!< CCU6 CC60SR: CCS (Bit 0)                              */
#define CCU6_CC60SR_CCS_Msk               (0xffffUL)                /*!< CCU6 CC60SR: CCS (Bitfield-Mask: 0xffff)              */
/* =========================================================  CC61R  ========================================================= */
#define CCU6_CC61R_CCV_Pos                (0UL)                     /*!< CCU6 CC61R: CCV (Bit 0)                               */
#define CCU6_CC61R_CCV_Msk                (0xffffUL)                /*!< CCU6 CC61R: CCV (Bitfield-Mask: 0xffff)               */
/* ========================================================  CC61SR  ========================================================= */
#define CCU6_CC61SR_CCS_Pos               (0UL)                     /*!< CCU6 CC61SR: CCS (Bit 0)                              */
#define CCU6_CC61SR_CCS_Msk               (0xffffUL)                /*!< CCU6 CC61SR: CCS (Bitfield-Mask: 0xffff)              */
/* =========================================================  CC62R  ========================================================= */
#define CCU6_CC62R_CCV_Pos                (0UL)                     /*!< CCU6 CC62R: CCV (Bit 0)                               */
#define CCU6_CC62R_CCV_Msk                (0xffffUL)                /*!< CCU6 CC62R: CCV (Bitfield-Mask: 0xffff)               */
/* ========================================================  CC62SR  ========================================================= */
#define CCU6_CC62SR_CCS_Pos               (0UL)                     /*!< CCU6 CC62SR: CCS (Bit 0)                              */
#define CCU6_CC62SR_CCS_Msk               (0xffffUL)                /*!< CCU6 CC62SR: CCS (Bitfield-Mask: 0xffff)              */
/* =========================================================  CC63R  ========================================================= */
#define CCU6_CC63R_CCV_Pos                (0UL)                     /*!< CCU6 CC63R: CCV (Bit 0)                               */
#define CCU6_CC63R_CCV_Msk                (0xffffUL)                /*!< CCU6 CC63R: CCV (Bitfield-Mask: 0xffff)               */
/* ========================================================  CC63SR  ========================================================= */
#define CCU6_CC63SR_CCS_Pos               (0UL)                     /*!< CCU6 CC63SR: CCS (Bit 0)                              */
#define CCU6_CC63SR_CCS_Msk               (0xffffUL)                /*!< CCU6 CC63SR: CCS (Bitfield-Mask: 0xffff)              */
/* =======================================================  CMPMODIF  ======================================================== */
#define CCU6_CMPMODIF_MCC60S_Pos          (0UL)                     /*!< CCU6 CMPMODIF: MCC60S (Bit 0)                         */
#define CCU6_CMPMODIF_MCC60S_Msk          (0x1UL)                   /*!< CCU6 CMPMODIF: MCC60S (Bitfield-Mask: 0x01)           */
#define CCU6_CMPMODIF_MCC61S_Pos          (1UL)                     /*!< CCU6 CMPMODIF: MCC61S (Bit 1)                         */
#define CCU6_CMPMODIF_MCC61S_Msk          (0x2UL)                   /*!< CCU6 CMPMODIF: MCC61S (Bitfield-Mask: 0x01)           */
#define CCU6_CMPMODIF_MCC62S_Pos          (2UL)                     /*!< CCU6 CMPMODIF: MCC62S (Bit 2)                         */
#define CCU6_CMPMODIF_MCC62S_Msk          (0x4UL)                   /*!< CCU6 CMPMODIF: MCC62S (Bitfield-Mask: 0x01)           */
#define CCU6_CMPMODIF_MCC63S_Pos          (6UL)                     /*!< CCU6 CMPMODIF: MCC63S (Bit 6)                         */
#define CCU6_CMPMODIF_MCC63S_Msk          (0x40UL)                  /*!< CCU6 CMPMODIF: MCC63S (Bitfield-Mask: 0x01)           */
#define CCU6_CMPMODIF_MCC60R_Pos          (8UL)                     /*!< CCU6 CMPMODIF: MCC60R (Bit 8)                         */
#define CCU6_CMPMODIF_MCC60R_Msk          (0x100UL)                 /*!< CCU6 CMPMODIF: MCC60R (Bitfield-Mask: 0x01)           */
#define CCU6_CMPMODIF_MCC61R_Pos          (9UL)                     /*!< CCU6 CMPMODIF: MCC61R (Bit 9)                         */
#define CCU6_CMPMODIF_MCC61R_Msk          (0x200UL)                 /*!< CCU6 CMPMODIF: MCC61R (Bitfield-Mask: 0x01)           */
#define CCU6_CMPMODIF_MCC62R_Pos          (10UL)                    /*!< CCU6 CMPMODIF: MCC62R (Bit 10)                        */
#define CCU6_CMPMODIF_MCC62R_Msk          (0x400UL)                 /*!< CCU6 CMPMODIF: MCC62R (Bitfield-Mask: 0x01)           */
#define CCU6_CMPMODIF_MCC63R_Pos          (14UL)                    /*!< CCU6 CMPMODIF: MCC63R (Bit 14)                        */
#define CCU6_CMPMODIF_MCC63R_Msk          (0x4000UL)                /*!< CCU6 CMPMODIF: MCC63R (Bitfield-Mask: 0x01)           */
/* ========================================================  CMPSTAT  ======================================================== */
#define CCU6_CMPSTAT_CC60ST_Pos           (0UL)                     /*!< CCU6 CMPSTAT: CC60ST (Bit 0)                          */
#define CCU6_CMPSTAT_CC60ST_Msk           (0x1UL)                   /*!< CCU6 CMPSTAT: CC60ST (Bitfield-Mask: 0x01)            */
#define CCU6_CMPSTAT_CC61ST_Pos           (1UL)                     /*!< CCU6 CMPSTAT: CC61ST (Bit 1)                          */
#define CCU6_CMPSTAT_CC61ST_Msk           (0x2UL)                   /*!< CCU6 CMPSTAT: CC61ST (Bitfield-Mask: 0x01)            */
#define CCU6_CMPSTAT_CC62ST_Pos           (2UL)                     /*!< CCU6 CMPSTAT: CC62ST (Bit 2)                          */
#define CCU6_CMPSTAT_CC62ST_Msk           (0x4UL)                   /*!< CCU6 CMPSTAT: CC62ST (Bitfield-Mask: 0x01)            */
#define CCU6_CMPSTAT_CC63ST_Pos           (6UL)                     /*!< CCU6 CMPSTAT: CC63ST (Bit 6)                          */
#define CCU6_CMPSTAT_CC63ST_Msk           (0x40UL)                  /*!< CCU6 CMPSTAT: CC63ST (Bitfield-Mask: 0x01)            */
#define CCU6_CMPSTAT_CCPOS0_Pos           (3UL)                     /*!< CCU6 CMPSTAT: CCPOS0 (Bit 3)                          */
#define CCU6_CMPSTAT_CCPOS0_Msk           (0x8UL)                   /*!< CCU6 CMPSTAT: CCPOS0 (Bitfield-Mask: 0x01)            */
#define CCU6_CMPSTAT_CCPOS1_Pos           (4UL)                     /*!< CCU6 CMPSTAT: CCPOS1 (Bit 4)                          */
#define CCU6_CMPSTAT_CCPOS1_Msk           (0x10UL)                  /*!< CCU6 CMPSTAT: CCPOS1 (Bitfield-Mask: 0x01)            */
#define CCU6_CMPSTAT_CCPOS2_Pos           (5UL)                     /*!< CCU6 CMPSTAT: CCPOS2 (Bit 5)                          */
#define CCU6_CMPSTAT_CCPOS2_Msk           (0x20UL)                  /*!< CCU6 CMPSTAT: CCPOS2 (Bitfield-Mask: 0x01)            */
#define CCU6_CMPSTAT_CC60PS_Pos           (8UL)                     /*!< CCU6 CMPSTAT: CC60PS (Bit 8)                          */
#define CCU6_CMPSTAT_CC60PS_Msk           (0x100UL)                 /*!< CCU6 CMPSTAT: CC60PS (Bitfield-Mask: 0x01)            */
#define CCU6_CMPSTAT_CC61PS_Pos           (10UL)                    /*!< CCU6 CMPSTAT: CC61PS (Bit 10)                         */
#define CCU6_CMPSTAT_CC61PS_Msk           (0x400UL)                 /*!< CCU6 CMPSTAT: CC61PS (Bitfield-Mask: 0x01)            */
#define CCU6_CMPSTAT_CC62PS_Pos           (12UL)                    /*!< CCU6 CMPSTAT: CC62PS (Bit 12)                         */
#define CCU6_CMPSTAT_CC62PS_Msk           (0x1000UL)                /*!< CCU6 CMPSTAT: CC62PS (Bitfield-Mask: 0x01)            */
#define CCU6_CMPSTAT_COUT60PS_Pos         (9UL)                     /*!< CCU6 CMPSTAT: COUT60PS (Bit 9)                        */
#define CCU6_CMPSTAT_COUT60PS_Msk         (0x200UL)                 /*!< CCU6 CMPSTAT: COUT60PS (Bitfield-Mask: 0x01)          */
#define CCU6_CMPSTAT_COUT61PS_Pos         (11UL)                    /*!< CCU6 CMPSTAT: COUT61PS (Bit 11)                       */
#define CCU6_CMPSTAT_COUT61PS_Msk         (0x800UL)                 /*!< CCU6 CMPSTAT: COUT61PS (Bitfield-Mask: 0x01)          */
#define CCU6_CMPSTAT_COUT62PS_Pos         (13UL)                    /*!< CCU6 CMPSTAT: COUT62PS (Bit 13)                       */
#define CCU6_CMPSTAT_COUT62PS_Msk         (0x2000UL)                /*!< CCU6 CMPSTAT: COUT62PS (Bitfield-Mask: 0x01)          */
#define CCU6_CMPSTAT_COUT63PS_Pos         (14UL)                    /*!< CCU6 CMPSTAT: COUT63PS (Bit 14)                       */
#define CCU6_CMPSTAT_COUT63PS_Msk         (0x4000UL)                /*!< CCU6 CMPSTAT: COUT63PS (Bitfield-Mask: 0x01)          */
#define CCU6_CMPSTAT_T13IM_Pos            (15UL)                    /*!< CCU6 CMPSTAT: T13IM (Bit 15)                          */
#define CCU6_CMPSTAT_T13IM_Msk            (0x8000UL)                /*!< CCU6 CMPSTAT: T13IM (Bitfield-Mask: 0x01)             */
/* ==========================================================  IEN  ========================================================== */
#define CCU6_IEN_ENCC60R_Pos              (0UL)                     /*!< CCU6 IEN: ENCC60R (Bit 0)                             */
#define CCU6_IEN_ENCC60R_Msk              (0x1UL)                   /*!< CCU6 IEN: ENCC60R (Bitfield-Mask: 0x01)               */
#define CCU6_IEN_ENCC60F_Pos              (1UL)                     /*!< CCU6 IEN: ENCC60F (Bit 1)                             */
#define CCU6_IEN_ENCC60F_Msk              (0x2UL)                   /*!< CCU6 IEN: ENCC60F (Bitfield-Mask: 0x01)               */
#define CCU6_IEN_ENCC61R_Pos              (2UL)                     /*!< CCU6 IEN: ENCC61R (Bit 2)                             */
#define CCU6_IEN_ENCC61R_Msk              (0x4UL)                   /*!< CCU6 IEN: ENCC61R (Bitfield-Mask: 0x01)               */
#define CCU6_IEN_ENCC61F_Pos              (3UL)                     /*!< CCU6 IEN: ENCC61F (Bit 3)                             */
#define CCU6_IEN_ENCC61F_Msk              (0x8UL)                   /*!< CCU6 IEN: ENCC61F (Bitfield-Mask: 0x01)               */
#define CCU6_IEN_ENCC62R_Pos              (4UL)                     /*!< CCU6 IEN: ENCC62R (Bit 4)                             */
#define CCU6_IEN_ENCC62R_Msk              (0x10UL)                  /*!< CCU6 IEN: ENCC62R (Bitfield-Mask: 0x01)               */
#define CCU6_IEN_ENCC62F_Pos              (5UL)                     /*!< CCU6 IEN: ENCC62F (Bit 5)                             */
#define CCU6_IEN_ENCC62F_Msk              (0x20UL)                  /*!< CCU6 IEN: ENCC62F (Bitfield-Mask: 0x01)               */
#define CCU6_IEN_ENT12OM_Pos              (6UL)                     /*!< CCU6 IEN: ENT12OM (Bit 6)                             */
#define CCU6_IEN_ENT12OM_Msk              (0x40UL)                  /*!< CCU6 IEN: ENT12OM (Bitfield-Mask: 0x01)               */
#define CCU6_IEN_ENT12PM_Pos              (7UL)                     /*!< CCU6 IEN: ENT12PM (Bit 7)                             */
#define CCU6_IEN_ENT12PM_Msk              (0x80UL)                  /*!< CCU6 IEN: ENT12PM (Bitfield-Mask: 0x01)               */
#define CCU6_IEN_ENT13CM_Pos              (8UL)                     /*!< CCU6 IEN: ENT13CM (Bit 8)                             */
#define CCU6_IEN_ENT13CM_Msk              (0x100UL)                 /*!< CCU6 IEN: ENT13CM (Bitfield-Mask: 0x01)               */
#define CCU6_IEN_ENT13PM_Pos              (9UL)                     /*!< CCU6 IEN: ENT13PM (Bit 9)                             */
#define CCU6_IEN_ENT13PM_Msk              (0x200UL)                 /*!< CCU6 IEN: ENT13PM (Bitfield-Mask: 0x01)               */
#define CCU6_IEN_ENTRPF_Pos               (10UL)                    /*!< CCU6 IEN: ENTRPF (Bit 10)                             */
#define CCU6_IEN_ENTRPF_Msk               (0x400UL)                 /*!< CCU6 IEN: ENTRPF (Bitfield-Mask: 0x01)                */
#define CCU6_IEN_ENCHE_Pos                (12UL)                    /*!< CCU6 IEN: ENCHE (Bit 12)                              */
#define CCU6_IEN_ENCHE_Msk                (0x1000UL)                /*!< CCU6 IEN: ENCHE (Bitfield-Mask: 0x01)                 */
#define CCU6_IEN_ENWHE_Pos                (13UL)                    /*!< CCU6 IEN: ENWHE (Bit 13)                              */
#define CCU6_IEN_ENWHE_Msk                (0x2000UL)                /*!< CCU6 IEN: ENWHE (Bitfield-Mask: 0x01)                 */
#define CCU6_IEN_ENIDLE_Pos               (14UL)                    /*!< CCU6 IEN: ENIDLE (Bit 14)                             */
#define CCU6_IEN_ENIDLE_Msk               (0x4000UL)                /*!< CCU6 IEN: ENIDLE (Bitfield-Mask: 0x01)                */
#define CCU6_IEN_ENSTR_Pos                (15UL)                    /*!< CCU6 IEN: ENSTR (Bit 15)                              */
#define CCU6_IEN_ENSTR_Msk                (0x8000UL)                /*!< CCU6 IEN: ENSTR (Bitfield-Mask: 0x01)                 */
/* ==========================================================  INP  ========================================================== */
#define CCU6_INP_INPCC60_Pos              (0UL)                     /*!< CCU6 INP: INPCC60 (Bit 0)                             */
#define CCU6_INP_INPCC60_Msk              (0x3UL)                   /*!< CCU6 INP: INPCC60 (Bitfield-Mask: 0x03)               */
#define CCU6_INP_INPCC61_Pos              (2UL)                     /*!< CCU6 INP: INPCC61 (Bit 2)                             */
#define CCU6_INP_INPCC61_Msk              (0xcUL)                   /*!< CCU6 INP: INPCC61 (Bitfield-Mask: 0x03)               */
#define CCU6_INP_INPCC62_Pos              (4UL)                     /*!< CCU6 INP: INPCC62 (Bit 4)                             */
#define CCU6_INP_INPCC62_Msk              (0x30UL)                  /*!< CCU6 INP: INPCC62 (Bitfield-Mask: 0x03)               */
#define CCU6_INP_INPCHE_Pos               (6UL)                     /*!< CCU6 INP: INPCHE (Bit 6)                              */
#define CCU6_INP_INPCHE_Msk               (0xc0UL)                  /*!< CCU6 INP: INPCHE (Bitfield-Mask: 0x03)                */
#define CCU6_INP_INPERR_Pos               (8UL)                     /*!< CCU6 INP: INPERR (Bit 8)                              */
#define CCU6_INP_INPERR_Msk               (0x300UL)                 /*!< CCU6 INP: INPERR (Bitfield-Mask: 0x03)                */
#define CCU6_INP_INPT12_Pos               (10UL)                    /*!< CCU6 INP: INPT12 (Bit 10)                             */
#define CCU6_INP_INPT12_Msk               (0xc00UL)                 /*!< CCU6 INP: INPT12 (Bitfield-Mask: 0x03)                */
#define CCU6_INP_INPT13_Pos               (12UL)                    /*!< CCU6 INP: INPT13 (Bit 12)                             */
#define CCU6_INP_INPT13_Msk               (0x3000UL)                /*!< CCU6 INP: INPT13 (Bitfield-Mask: 0x03)                */
/* ==========================================================  IS  =========================================================== */
#define CCU6_IS_ICC60R_Pos                (0UL)                     /*!< CCU6 IS: ICC60R (Bit 0)                               */
#define CCU6_IS_ICC60R_Msk                (0x1UL)                   /*!< CCU6 IS: ICC60R (Bitfield-Mask: 0x01)                 */
#define CCU6_IS_ICC61R_Pos                (2UL)                     /*!< CCU6 IS: ICC61R (Bit 2)                               */
#define CCU6_IS_ICC61R_Msk                (0x4UL)                   /*!< CCU6 IS: ICC61R (Bitfield-Mask: 0x01)                 */
#define CCU6_IS_ICC62R_Pos                (4UL)                     /*!< CCU6 IS: ICC62R (Bit 4)                               */
#define CCU6_IS_ICC62R_Msk                (0x10UL)                  /*!< CCU6 IS: ICC62R (Bitfield-Mask: 0x01)                 */
#define CCU6_IS_ICC60F_Pos                (1UL)                     /*!< CCU6 IS: ICC60F (Bit 1)                               */
#define CCU6_IS_ICC60F_Msk                (0x2UL)                   /*!< CCU6 IS: ICC60F (Bitfield-Mask: 0x01)                 */
#define CCU6_IS_ICC61F_Pos                (3UL)                     /*!< CCU6 IS: ICC61F (Bit 3)                               */
#define CCU6_IS_ICC61F_Msk                (0x8UL)                   /*!< CCU6 IS: ICC61F (Bitfield-Mask: 0x01)                 */
#define CCU6_IS_ICC62F_Pos                (5UL)                     /*!< CCU6 IS: ICC62F (Bit 5)                               */
#define CCU6_IS_ICC62F_Msk                (0x20UL)                  /*!< CCU6 IS: ICC62F (Bitfield-Mask: 0x01)                 */
#define CCU6_IS_T12OM_Pos                 (6UL)                     /*!< CCU6 IS: T12OM (Bit 6)                                */
#define CCU6_IS_T12OM_Msk                 (0x40UL)                  /*!< CCU6 IS: T12OM (Bitfield-Mask: 0x01)                  */
#define CCU6_IS_T12PM_Pos                 (7UL)                     /*!< CCU6 IS: T12PM (Bit 7)                                */
#define CCU6_IS_T12PM_Msk                 (0x80UL)                  /*!< CCU6 IS: T12PM (Bitfield-Mask: 0x01)                  */
#define CCU6_IS_T13CM_Pos                 (8UL)                     /*!< CCU6 IS: T13CM (Bit 8)                                */
#define CCU6_IS_T13CM_Msk                 (0x100UL)                 /*!< CCU6 IS: T13CM (Bitfield-Mask: 0x01)                  */
#define CCU6_IS_T13PM_Pos                 (9UL)                     /*!< CCU6 IS: T13PM (Bit 9)                                */
#define CCU6_IS_T13PM_Msk                 (0x200UL)                 /*!< CCU6 IS: T13PM (Bitfield-Mask: 0x01)                  */
#define CCU6_IS_TRPF_Pos                  (10UL)                    /*!< CCU6 IS: TRPF (Bit 10)                                */
#define CCU6_IS_TRPF_Msk                  (0x400UL)                 /*!< CCU6 IS: TRPF (Bitfield-Mask: 0x01)                   */
#define CCU6_IS_TRPS_Pos                  (11UL)                    /*!< CCU6 IS: TRPS (Bit 11)                                */
#define CCU6_IS_TRPS_Msk                  (0x800UL)                 /*!< CCU6 IS: TRPS (Bitfield-Mask: 0x01)                   */
#define CCU6_IS_CHE_Pos                   (12UL)                    /*!< CCU6 IS: CHE (Bit 12)                                 */
#define CCU6_IS_CHE_Msk                   (0x1000UL)                /*!< CCU6 IS: CHE (Bitfield-Mask: 0x01)                    */
#define CCU6_IS_WHE_Pos                   (13UL)                    /*!< CCU6 IS: WHE (Bit 13)                                 */
#define CCU6_IS_WHE_Msk                   (0x2000UL)                /*!< CCU6 IS: WHE (Bitfield-Mask: 0x01)                    */
#define CCU6_IS_IDLE_Pos                  (14UL)                    /*!< CCU6 IS: IDLE (Bit 14)                                */
#define CCU6_IS_IDLE_Msk                  (0x4000UL)                /*!< CCU6 IS: IDLE (Bitfield-Mask: 0x01)                   */
#define CCU6_IS_STR_Pos                   (15UL)                    /*!< CCU6 IS: STR (Bit 15)                                 */
#define CCU6_IS_STR_Msk                   (0x8000UL)                /*!< CCU6 IS: STR (Bitfield-Mask: 0x01)                    */
/* ==========================================================  ISR  ========================================================== */
#define CCU6_ISR_RCC60R_Pos               (0UL)                     /*!< CCU6 ISR: RCC60R (Bit 0)                              */
#define CCU6_ISR_RCC60R_Msk               (0x1UL)                   /*!< CCU6 ISR: RCC60R (Bitfield-Mask: 0x01)                */
#define CCU6_ISR_RCC60F_Pos               (1UL)                     /*!< CCU6 ISR: RCC60F (Bit 1)                              */
#define CCU6_ISR_RCC60F_Msk               (0x2UL)                   /*!< CCU6 ISR: RCC60F (Bitfield-Mask: 0x01)                */
#define CCU6_ISR_RCC61R_Pos               (2UL)                     /*!< CCU6 ISR: RCC61R (Bit 2)                              */
#define CCU6_ISR_RCC61R_Msk               (0x4UL)                   /*!< CCU6 ISR: RCC61R (Bitfield-Mask: 0x01)                */
#define CCU6_ISR_RCC61F_Pos               (3UL)                     /*!< CCU6 ISR: RCC61F (Bit 3)                              */
#define CCU6_ISR_RCC61F_Msk               (0x8UL)                   /*!< CCU6 ISR: RCC61F (Bitfield-Mask: 0x01)                */
#define CCU6_ISR_RCC62R_Pos               (4UL)                     /*!< CCU6 ISR: RCC62R (Bit 4)                              */
#define CCU6_ISR_RCC62R_Msk               (0x10UL)                  /*!< CCU6 ISR: RCC62R (Bitfield-Mask: 0x01)                */
#define CCU6_ISR_RCC62F_Pos               (5UL)                     /*!< CCU6 ISR: RCC62F (Bit 5)                              */
#define CCU6_ISR_RCC62F_Msk               (0x20UL)                  /*!< CCU6 ISR: RCC62F (Bitfield-Mask: 0x01)                */
#define CCU6_ISR_RT12OM_Pos               (6UL)                     /*!< CCU6 ISR: RT12OM (Bit 6)                              */
#define CCU6_ISR_RT12OM_Msk               (0x40UL)                  /*!< CCU6 ISR: RT12OM (Bitfield-Mask: 0x01)                */
#define CCU6_ISR_RT12PM_Pos               (7UL)                     /*!< CCU6 ISR: RT12PM (Bit 7)                              */
#define CCU6_ISR_RT12PM_Msk               (0x80UL)                  /*!< CCU6 ISR: RT12PM (Bitfield-Mask: 0x01)                */
#define CCU6_ISR_RT13CM_Pos               (8UL)                     /*!< CCU6 ISR: RT13CM (Bit 8)                              */
#define CCU6_ISR_RT13CM_Msk               (0x100UL)                 /*!< CCU6 ISR: RT13CM (Bitfield-Mask: 0x01)                */
#define CCU6_ISR_RT13PM_Pos               (9UL)                     /*!< CCU6 ISR: RT13PM (Bit 9)                              */
#define CCU6_ISR_RT13PM_Msk               (0x200UL)                 /*!< CCU6 ISR: RT13PM (Bitfield-Mask: 0x01)                */
#define CCU6_ISR_RTRPF_Pos                (10UL)                    /*!< CCU6 ISR: RTRPF (Bit 10)                              */
#define CCU6_ISR_RTRPF_Msk                (0x400UL)                 /*!< CCU6 ISR: RTRPF (Bitfield-Mask: 0x01)                 */
#define CCU6_ISR_RCHE_Pos                 (12UL)                    /*!< CCU6 ISR: RCHE (Bit 12)                               */
#define CCU6_ISR_RCHE_Msk                 (0x1000UL)                /*!< CCU6 ISR: RCHE (Bitfield-Mask: 0x01)                  */
#define CCU6_ISR_RWHE_Pos                 (13UL)                    /*!< CCU6 ISR: RWHE (Bit 13)                               */
#define CCU6_ISR_RWHE_Msk                 (0x2000UL)                /*!< CCU6 ISR: RWHE (Bitfield-Mask: 0x01)                  */
#define CCU6_ISR_RIDLE_Pos                (14UL)                    /*!< CCU6 ISR: RIDLE (Bit 14)                              */
#define CCU6_ISR_RIDLE_Msk                (0x4000UL)                /*!< CCU6 ISR: RIDLE (Bitfield-Mask: 0x01)                 */
#define CCU6_ISR_RSTR_Pos                 (15UL)                    /*!< CCU6 ISR: RSTR (Bit 15)                               */
#define CCU6_ISR_RSTR_Msk                 (0x8000UL)                /*!< CCU6 ISR: RSTR (Bitfield-Mask: 0x01)                  */
/* ==========================================================  ISS  ========================================================== */
#define CCU6_ISS_SCC60R_Pos               (0UL)                     /*!< CCU6 ISS: SCC60R (Bit 0)                              */
#define CCU6_ISS_SCC60R_Msk               (0x1UL)                   /*!< CCU6 ISS: SCC60R (Bitfield-Mask: 0x01)                */
#define CCU6_ISS_SCC60F_Pos               (1UL)                     /*!< CCU6 ISS: SCC60F (Bit 1)                              */
#define CCU6_ISS_SCC60F_Msk               (0x2UL)                   /*!< CCU6 ISS: SCC60F (Bitfield-Mask: 0x01)                */
#define CCU6_ISS_SCC61R_Pos               (2UL)                     /*!< CCU6 ISS: SCC61R (Bit 2)                              */
#define CCU6_ISS_SCC61R_Msk               (0x4UL)                   /*!< CCU6 ISS: SCC61R (Bitfield-Mask: 0x01)                */
#define CCU6_ISS_SCC61F_Pos               (3UL)                     /*!< CCU6 ISS: SCC61F (Bit 3)                              */
#define CCU6_ISS_SCC61F_Msk               (0x8UL)                   /*!< CCU6 ISS: SCC61F (Bitfield-Mask: 0x01)                */
#define CCU6_ISS_SCC62R_Pos               (4UL)                     /*!< CCU6 ISS: SCC62R (Bit 4)                              */
#define CCU6_ISS_SCC62R_Msk               (0x10UL)                  /*!< CCU6 ISS: SCC62R (Bitfield-Mask: 0x01)                */
#define CCU6_ISS_SCC62F_Pos               (5UL)                     /*!< CCU6 ISS: SCC62F (Bit 5)                              */
#define CCU6_ISS_SCC62F_Msk               (0x20UL)                  /*!< CCU6 ISS: SCC62F (Bitfield-Mask: 0x01)                */
#define CCU6_ISS_ST12OM_Pos               (6UL)                     /*!< CCU6 ISS: ST12OM (Bit 6)                              */
#define CCU6_ISS_ST12OM_Msk               (0x40UL)                  /*!< CCU6 ISS: ST12OM (Bitfield-Mask: 0x01)                */
#define CCU6_ISS_ST12PM_Pos               (7UL)                     /*!< CCU6 ISS: ST12PM (Bit 7)                              */
#define CCU6_ISS_ST12PM_Msk               (0x80UL)                  /*!< CCU6 ISS: ST12PM (Bitfield-Mask: 0x01)                */
#define CCU6_ISS_ST13CM_Pos               (8UL)                     /*!< CCU6 ISS: ST13CM (Bit 8)                              */
#define CCU6_ISS_ST13CM_Msk               (0x100UL)                 /*!< CCU6 ISS: ST13CM (Bitfield-Mask: 0x01)                */
#define CCU6_ISS_ST13PM_Pos               (9UL)                     /*!< CCU6 ISS: ST13PM (Bit 9)                              */
#define CCU6_ISS_ST13PM_Msk               (0x200UL)                 /*!< CCU6 ISS: ST13PM (Bitfield-Mask: 0x01)                */
#define CCU6_ISS_STRPF_Pos                (10UL)                    /*!< CCU6 ISS: STRPF (Bit 10)                              */
#define CCU6_ISS_STRPF_Msk                (0x400UL)                 /*!< CCU6 ISS: STRPF (Bitfield-Mask: 0x01)                 */
#define CCU6_ISS_SWHC_Pos                 (11UL)                    /*!< CCU6 ISS: SWHC (Bit 11)                               */
#define CCU6_ISS_SWHC_Msk                 (0x800UL)                 /*!< CCU6 ISS: SWHC (Bitfield-Mask: 0x01)                  */
#define CCU6_ISS_SCHE_Pos                 (12UL)                    /*!< CCU6 ISS: SCHE (Bit 12)                               */
#define CCU6_ISS_SCHE_Msk                 (0x1000UL)                /*!< CCU6 ISS: SCHE (Bitfield-Mask: 0x01)                  */
#define CCU6_ISS_SWHE_Pos                 (13UL)                    /*!< CCU6 ISS: SWHE (Bit 13)                               */
#define CCU6_ISS_SWHE_Msk                 (0x2000UL)                /*!< CCU6 ISS: SWHE (Bitfield-Mask: 0x01)                  */
#define CCU6_ISS_SIDLE_Pos                (14UL)                    /*!< CCU6 ISS: SIDLE (Bit 14)                              */
#define CCU6_ISS_SIDLE_Msk                (0x4000UL)                /*!< CCU6 ISS: SIDLE (Bitfield-Mask: 0x01)                 */
#define CCU6_ISS_SSTR_Pos                 (15UL)                    /*!< CCU6 ISS: SSTR (Bit 15)                               */
#define CCU6_ISS_SSTR_Msk                 (0x8000UL)                /*!< CCU6 ISS: SSTR (Bitfield-Mask: 0x01)                  */
/* ========================================================  MCMCTR  ========================================================= */
#define CCU6_MCMCTR_SWSEL_Pos             (0UL)                     /*!< CCU6 MCMCTR: SWSEL (Bit 0)                            */
#define CCU6_MCMCTR_SWSEL_Msk             (0x7UL)                   /*!< CCU6 MCMCTR: SWSEL (Bitfield-Mask: 0x07)              */
#define CCU6_MCMCTR_SWSYN_Pos             (4UL)                     /*!< CCU6 MCMCTR: SWSYN (Bit 4)                            */
#define CCU6_MCMCTR_SWSYN_Msk             (0x30UL)                  /*!< CCU6 MCMCTR: SWSYN (Bitfield-Mask: 0x03)              */
#define CCU6_MCMCTR_STE12U_Pos            (8UL)                     /*!< CCU6 MCMCTR: STE12U (Bit 8)                           */
#define CCU6_MCMCTR_STE12U_Msk            (0x100UL)                 /*!< CCU6 MCMCTR: STE12U (Bitfield-Mask: 0x01)             */
#define CCU6_MCMCTR_STE12D_Pos            (9UL)                     /*!< CCU6 MCMCTR: STE12D (Bit 9)                           */
#define CCU6_MCMCTR_STE12D_Msk            (0x200UL)                 /*!< CCU6 MCMCTR: STE12D (Bitfield-Mask: 0x01)             */
#define CCU6_MCMCTR_STE13U_Pos            (10UL)                    /*!< CCU6 MCMCTR: STE13U (Bit 10)                          */
#define CCU6_MCMCTR_STE13U_Msk            (0x400UL)                 /*!< CCU6 MCMCTR: STE13U (Bitfield-Mask: 0x01)             */
/* ========================================================  MCMOUT  ========================================================= */
#define CCU6_MCMOUT_MCMP_Pos              (0UL)                     /*!< CCU6 MCMOUT: MCMP (Bit 0)                             */
#define CCU6_MCMOUT_MCMP_Msk              (0x3fUL)                  /*!< CCU6 MCMOUT: MCMP (Bitfield-Mask: 0x3f)               */
#define CCU6_MCMOUT_R_Pos                 (6UL)                     /*!< CCU6 MCMOUT: R (Bit 6)                                */
#define CCU6_MCMOUT_R_Msk                 (0x40UL)                  /*!< CCU6 MCMOUT: R (Bitfield-Mask: 0x01)                  */
#define CCU6_MCMOUT_EXPH_Pos              (8UL)                     /*!< CCU6 MCMOUT: EXPH (Bit 8)                             */
#define CCU6_MCMOUT_EXPH_Msk              (0x700UL)                 /*!< CCU6 MCMOUT: EXPH (Bitfield-Mask: 0x07)               */
#define CCU6_MCMOUT_CURH_Pos              (11UL)                    /*!< CCU6 MCMOUT: CURH (Bit 11)                            */
#define CCU6_MCMOUT_CURH_Msk              (0x3800UL)                /*!< CCU6 MCMOUT: CURH (Bitfield-Mask: 0x07)               */
/* ========================================================  MCMOUTS  ======================================================== */
#define CCU6_MCMOUTS_MCMPS_Pos            (0UL)                     /*!< CCU6 MCMOUTS: MCMPS (Bit 0)                           */
#define CCU6_MCMOUTS_MCMPS_Msk            (0x3fUL)                  /*!< CCU6 MCMOUTS: MCMPS (Bitfield-Mask: 0x3f)             */
#define CCU6_MCMOUTS_STRMCM_Pos           (7UL)                     /*!< CCU6 MCMOUTS: STRMCM (Bit 7)                          */
#define CCU6_MCMOUTS_STRMCM_Msk           (0x80UL)                  /*!< CCU6 MCMOUTS: STRMCM (Bitfield-Mask: 0x01)            */
#define CCU6_MCMOUTS_EXPHS_Pos            (8UL)                     /*!< CCU6 MCMOUTS: EXPHS (Bit 8)                           */
#define CCU6_MCMOUTS_EXPHS_Msk            (0x700UL)                 /*!< CCU6 MCMOUTS: EXPHS (Bitfield-Mask: 0x07)             */
#define CCU6_MCMOUTS_CURHS_Pos            (11UL)                    /*!< CCU6 MCMOUTS: CURHS (Bit 11)                          */
#define CCU6_MCMOUTS_CURHS_Msk            (0x3800UL)                /*!< CCU6 MCMOUTS: CURHS (Bitfield-Mask: 0x07)             */
#define CCU6_MCMOUTS_STRHP_Pos            (15UL)                    /*!< CCU6 MCMOUTS: STRHP (Bit 15)                          */
#define CCU6_MCMOUTS_STRHP_Msk            (0x8000UL)                /*!< CCU6 MCMOUTS: STRHP (Bitfield-Mask: 0x01)             */
/* ========================================================  MODCTR  ========================================================= */
#define CCU6_MODCTR_T12MODEN_Pos          (0UL)                     /*!< CCU6 MODCTR: T12MODEN (Bit 0)                         */
#define CCU6_MODCTR_T12MODEN_Msk          (0x3fUL)                  /*!< CCU6 MODCTR: T12MODEN (Bitfield-Mask: 0x3f)           */
#define CCU6_MODCTR_MCMEN_Pos             (7UL)                     /*!< CCU6 MODCTR: MCMEN (Bit 7)                            */
#define CCU6_MODCTR_MCMEN_Msk             (0x80UL)                  /*!< CCU6 MODCTR: MCMEN (Bitfield-Mask: 0x01)              */
#define CCU6_MODCTR_T13MODEN_Pos          (8UL)                     /*!< CCU6 MODCTR: T13MODEN (Bit 8)                         */
#define CCU6_MODCTR_T13MODEN_Msk          (0x3f00UL)                /*!< CCU6 MODCTR: T13MODEN (Bitfield-Mask: 0x3f)           */
#define CCU6_MODCTR_ECT13O_Pos            (15UL)                    /*!< CCU6 MODCTR: ECT13O (Bit 15)                          */
#define CCU6_MODCTR_ECT13O_Msk            (0x8000UL)                /*!< CCU6 MODCTR: ECT13O (Bitfield-Mask: 0x01)             */
/* ========================================================  PISEL0  ========================================================= */
#define CCU6_PISEL0_ISCC60_Pos            (0UL)                     /*!< CCU6 PISEL0: ISCC60 (Bit 0)                           */
#define CCU6_PISEL0_ISCC60_Msk            (0x3UL)                   /*!< CCU6 PISEL0: ISCC60 (Bitfield-Mask: 0x03)             */
#define CCU6_PISEL0_ISCC61_Pos            (2UL)                     /*!< CCU6 PISEL0: ISCC61 (Bit 2)                           */
#define CCU6_PISEL0_ISCC61_Msk            (0xcUL)                   /*!< CCU6 PISEL0: ISCC61 (Bitfield-Mask: 0x03)             */
#define CCU6_PISEL0_ISCC62_Pos            (4UL)                     /*!< CCU6 PISEL0: ISCC62 (Bit 4)                           */
#define CCU6_PISEL0_ISCC62_Msk            (0x30UL)                  /*!< CCU6 PISEL0: ISCC62 (Bitfield-Mask: 0x03)             */
#define CCU6_PISEL0_ISTRP_Pos             (6UL)                     /*!< CCU6 PISEL0: ISTRP (Bit 6)                            */
#define CCU6_PISEL0_ISTRP_Msk             (0xc0UL)                  /*!< CCU6 PISEL0: ISTRP (Bitfield-Mask: 0x03)              */
#define CCU6_PISEL0_ISPOS0_Pos            (8UL)                     /*!< CCU6 PISEL0: ISPOS0 (Bit 8)                           */
#define CCU6_PISEL0_ISPOS0_Msk            (0x300UL)                 /*!< CCU6 PISEL0: ISPOS0 (Bitfield-Mask: 0x03)             */
#define CCU6_PISEL0_ISPOS1_Pos            (10UL)                    /*!< CCU6 PISEL0: ISPOS1 (Bit 10)                          */
#define CCU6_PISEL0_ISPOS1_Msk            (0xc00UL)                 /*!< CCU6 PISEL0: ISPOS1 (Bitfield-Mask: 0x03)             */
#define CCU6_PISEL0_ISPOS2_Pos            (12UL)                    /*!< CCU6 PISEL0: ISPOS2 (Bit 12)                          */
#define CCU6_PISEL0_ISPOS2_Msk            (0x3000UL)                /*!< CCU6 PISEL0: ISPOS2 (Bitfield-Mask: 0x03)             */
#define CCU6_PISEL0_IST12HR_Pos           (14UL)                    /*!< CCU6 PISEL0: IST12HR (Bit 14)                         */
#define CCU6_PISEL0_IST12HR_Msk           (0xc000UL)                /*!< CCU6 PISEL0: IST12HR (Bitfield-Mask: 0x03)            */
/* ========================================================  PISEL2  ========================================================= */
#define CCU6_PISEL2_IST13HR_Pos           (0UL)                     /*!< CCU6 PISEL2: IST13HR (Bit 0)                          */
#define CCU6_PISEL2_IST13HR_Msk           (0x3UL)                   /*!< CCU6 PISEL2: IST13HR (Bitfield-Mask: 0x03)            */
#define CCU6_PISEL2_ISCNT12_Pos           (2UL)                     /*!< CCU6 PISEL2: ISCNT12 (Bit 2)                          */
#define CCU6_PISEL2_ISCNT12_Msk           (0xcUL)                   /*!< CCU6 PISEL2: ISCNT12 (Bitfield-Mask: 0x03)            */
#define CCU6_PISEL2_ISCNT13_Pos           (4UL)                     /*!< CCU6 PISEL2: ISCNT13 (Bit 4)                          */
#define CCU6_PISEL2_ISCNT13_Msk           (0x30UL)                  /*!< CCU6 PISEL2: ISCNT13 (Bitfield-Mask: 0x03)            */
#define CCU6_PISEL2_T12EXT_Pos            (6UL)                     /*!< CCU6 PISEL2: T12EXT (Bit 6)                           */
#define CCU6_PISEL2_T12EXT_Msk            (0x40UL)                  /*!< CCU6 PISEL2: T12EXT (Bitfield-Mask: 0x01)             */
#define CCU6_PISEL2_T13EXT_Pos            (7UL)                     /*!< CCU6 PISEL2: T13EXT (Bit 7)                           */
#define CCU6_PISEL2_T13EXT_Msk            (0x80UL)                  /*!< CCU6 PISEL2: T13EXT (Bitfield-Mask: 0x01)             */
/* =========================================================  PSLR  ========================================================== */
#define CCU6_PSLR_PSL_Pos                 (0UL)                     /*!< CCU6 PSLR: PSL (Bit 0)                                */
#define CCU6_PSLR_PSL_Msk                 (0x3fUL)                  /*!< CCU6 PSLR: PSL (Bitfield-Mask: 0x3f)                  */
#define CCU6_PSLR_PSL63_Pos               (7UL)                     /*!< CCU6 PSLR: PSL63 (Bit 7)                              */
#define CCU6_PSLR_PSL63_Msk               (0x80UL)                  /*!< CCU6 PSLR: PSL63 (Bitfield-Mask: 0x01)                */
/* ==========================================================  T12  ========================================================== */
#define CCU6_T12_T12CV_Pos                (0UL)                     /*!< CCU6 T12: T12CV (Bit 0)                               */
#define CCU6_T12_T12CV_Msk                (0xffffUL)                /*!< CCU6 T12: T12CV (Bitfield-Mask: 0xffff)               */
/* ========================================================  T12DTC  ========================================================= */
#define CCU6_T12DTC_DTM_Pos               (0UL)                     /*!< CCU6 T12DTC: DTM (Bit 0)                              */
#define CCU6_T12DTC_DTM_Msk               (0xffUL)                  /*!< CCU6 T12DTC: DTM (Bitfield-Mask: 0xff)                */
#define CCU6_T12DTC_DTE0_Pos              (8UL)                     /*!< CCU6 T12DTC: DTE0 (Bit 8)                             */
#define CCU6_T12DTC_DTE0_Msk              (0x100UL)                 /*!< CCU6 T12DTC: DTE0 (Bitfield-Mask: 0x01)               */
#define CCU6_T12DTC_DTE1_Pos              (9UL)                     /*!< CCU6 T12DTC: DTE1 (Bit 9)                             */
#define CCU6_T12DTC_DTE1_Msk              (0x200UL)                 /*!< CCU6 T12DTC: DTE1 (Bitfield-Mask: 0x01)               */
#define CCU6_T12DTC_DTE2_Pos              (10UL)                    /*!< CCU6 T12DTC: DTE2 (Bit 10)                            */
#define CCU6_T12DTC_DTE2_Msk              (0x400UL)                 /*!< CCU6 T12DTC: DTE2 (Bitfield-Mask: 0x01)               */
#define CCU6_T12DTC_DTR0_Pos              (12UL)                    /*!< CCU6 T12DTC: DTR0 (Bit 12)                            */
#define CCU6_T12DTC_DTR0_Msk              (0x1000UL)                /*!< CCU6 T12DTC: DTR0 (Bitfield-Mask: 0x01)               */
#define CCU6_T12DTC_DTR1_Pos              (13UL)                    /*!< CCU6 T12DTC: DTR1 (Bit 13)                            */
#define CCU6_T12DTC_DTR1_Msk              (0x2000UL)                /*!< CCU6 T12DTC: DTR1 (Bitfield-Mask: 0x01)               */
#define CCU6_T12DTC_DTR2_Pos              (14UL)                    /*!< CCU6 T12DTC: DTR2 (Bit 14)                            */
#define CCU6_T12DTC_DTR2_Msk              (0x4000UL)                /*!< CCU6 T12DTC: DTR2 (Bitfield-Mask: 0x01)               */
/* ========================================================  T12MSEL  ======================================================== */
#define CCU6_T12MSEL_MSEL60_Pos           (0UL)                     /*!< CCU6 T12MSEL: MSEL60 (Bit 0)                          */
#define CCU6_T12MSEL_MSEL60_Msk           (0xfUL)                   /*!< CCU6 T12MSEL: MSEL60 (Bitfield-Mask: 0x0f)            */
#define CCU6_T12MSEL_MSEL61_Pos           (4UL)                     /*!< CCU6 T12MSEL: MSEL61 (Bit 4)                          */
#define CCU6_T12MSEL_MSEL61_Msk           (0xf0UL)                  /*!< CCU6 T12MSEL: MSEL61 (Bitfield-Mask: 0x0f)            */
#define CCU6_T12MSEL_MSEL62_Pos           (8UL)                     /*!< CCU6 T12MSEL: MSEL62 (Bit 8)                          */
#define CCU6_T12MSEL_MSEL62_Msk           (0xf00UL)                 /*!< CCU6 T12MSEL: MSEL62 (Bitfield-Mask: 0x0f)            */
#define CCU6_T12MSEL_HSYNC_Pos            (12UL)                    /*!< CCU6 T12MSEL: HSYNC (Bit 12)                          */
#define CCU6_T12MSEL_HSYNC_Msk            (0x7000UL)                /*!< CCU6 T12MSEL: HSYNC (Bitfield-Mask: 0x07)             */
#define CCU6_T12MSEL_DBYP_Pos             (15UL)                    /*!< CCU6 T12MSEL: DBYP (Bit 15)                           */
#define CCU6_T12MSEL_DBYP_Msk             (0x8000UL)                /*!< CCU6 T12MSEL: DBYP (Bitfield-Mask: 0x01)              */
/* =========================================================  T12PR  ========================================================= */
#define CCU6_T12PR_T12PV_Pos              (0UL)                     /*!< CCU6 T12PR: T12PV (Bit 0)                             */
#define CCU6_T12PR_T12PV_Msk              (0xffffUL)                /*!< CCU6 T12PR: T12PV (Bitfield-Mask: 0xffff)             */
/* ==========================================================  T13  ========================================================== */
#define CCU6_T13_T13CV_Pos                (0UL)                     /*!< CCU6 T13: T13CV (Bit 0)                               */
#define CCU6_T13_T13CV_Msk                (0xffffUL)                /*!< CCU6 T13: T13CV (Bitfield-Mask: 0xffff)               */
/* =========================================================  T13PR  ========================================================= */
#define CCU6_T13PR_T13PV_Pos              (0UL)                     /*!< CCU6 T13PR: T13PV (Bit 0)                             */
#define CCU6_T13PR_T13PV_Msk              (0xffffUL)                /*!< CCU6 T13PR: T13PV (Bitfield-Mask: 0xffff)             */
/* =========================================================  TCTR0  ========================================================= */
#define CCU6_TCTR0_T12CLK_Pos             (0UL)                     /*!< CCU6 TCTR0: T12CLK (Bit 0)                            */
#define CCU6_TCTR0_T12CLK_Msk             (0x7UL)                   /*!< CCU6 TCTR0: T12CLK (Bitfield-Mask: 0x07)              */
#define CCU6_TCTR0_T12PRE_Pos             (3UL)                     /*!< CCU6 TCTR0: T12PRE (Bit 3)                            */
#define CCU6_TCTR0_T12PRE_Msk             (0x8UL)                   /*!< CCU6 TCTR0: T12PRE (Bitfield-Mask: 0x01)              */
#define CCU6_TCTR0_T12R_Pos               (4UL)                     /*!< CCU6 TCTR0: T12R (Bit 4)                              */
#define CCU6_TCTR0_T12R_Msk               (0x10UL)                  /*!< CCU6 TCTR0: T12R (Bitfield-Mask: 0x01)                */
#define CCU6_TCTR0_STE12_Pos              (5UL)                     /*!< CCU6 TCTR0: STE12 (Bit 5)                             */
#define CCU6_TCTR0_STE12_Msk              (0x20UL)                  /*!< CCU6 TCTR0: STE12 (Bitfield-Mask: 0x01)               */
#define CCU6_TCTR0_CDIR_Pos               (6UL)                     /*!< CCU6 TCTR0: CDIR (Bit 6)                              */
#define CCU6_TCTR0_CDIR_Msk               (0x40UL)                  /*!< CCU6 TCTR0: CDIR (Bitfield-Mask: 0x01)                */
#define CCU6_TCTR0_CTM_Pos                (7UL)                     /*!< CCU6 TCTR0: CTM (Bit 7)                               */
#define CCU6_TCTR0_CTM_Msk                (0x80UL)                  /*!< CCU6 TCTR0: CTM (Bitfield-Mask: 0x01)                 */
#define CCU6_TCTR0_T13CLK_Pos             (8UL)                     /*!< CCU6 TCTR0: T13CLK (Bit 8)                            */
#define CCU6_TCTR0_T13CLK_Msk             (0x700UL)                 /*!< CCU6 TCTR0: T13CLK (Bitfield-Mask: 0x07)              */
#define CCU6_TCTR0_T13PRE_Pos             (11UL)                    /*!< CCU6 TCTR0: T13PRE (Bit 11)                           */
#define CCU6_TCTR0_T13PRE_Msk             (0x800UL)                 /*!< CCU6 TCTR0: T13PRE (Bitfield-Mask: 0x01)              */
#define CCU6_TCTR0_T13R_Pos               (12UL)                    /*!< CCU6 TCTR0: T13R (Bit 12)                             */
#define CCU6_TCTR0_T13R_Msk               (0x1000UL)                /*!< CCU6 TCTR0: T13R (Bitfield-Mask: 0x01)                */
#define CCU6_TCTR0_STE13_Pos              (13UL)                    /*!< CCU6 TCTR0: STE13 (Bit 13)                            */
#define CCU6_TCTR0_STE13_Msk              (0x2000UL)                /*!< CCU6 TCTR0: STE13 (Bitfield-Mask: 0x01)               */
/* =========================================================  TCTR2  ========================================================= */
#define CCU6_TCTR2_T12SSC_Pos             (0UL)                     /*!< CCU6 TCTR2: T12SSC (Bit 0)                            */
#define CCU6_TCTR2_T12SSC_Msk             (0x1UL)                   /*!< CCU6 TCTR2: T12SSC (Bitfield-Mask: 0x01)              */
#define CCU6_TCTR2_T13SSC_Pos             (1UL)                     /*!< CCU6 TCTR2: T13SSC (Bit 1)                            */
#define CCU6_TCTR2_T13SSC_Msk             (0x2UL)                   /*!< CCU6 TCTR2: T13SSC (Bitfield-Mask: 0x01)              */
#define CCU6_TCTR2_T13TEC_Pos             (2UL)                     /*!< CCU6 TCTR2: T13TEC (Bit 2)                            */
#define CCU6_TCTR2_T13TEC_Msk             (0x1cUL)                  /*!< CCU6 TCTR2: T13TEC (Bitfield-Mask: 0x07)              */
#define CCU6_TCTR2_T13TED_Pos             (5UL)                     /*!< CCU6 TCTR2: T13TED (Bit 5)                            */
#define CCU6_TCTR2_T13TED_Msk             (0x60UL)                  /*!< CCU6 TCTR2: T13TED (Bitfield-Mask: 0x03)              */
#define CCU6_TCTR2_T12RSEL_Pos            (8UL)                     /*!< CCU6 TCTR2: T12RSEL (Bit 8)                           */
#define CCU6_TCTR2_T12RSEL_Msk            (0x300UL)                 /*!< CCU6 TCTR2: T12RSEL (Bitfield-Mask: 0x03)             */
#define CCU6_TCTR2_T13RSEL_Pos            (10UL)                    /*!< CCU6 TCTR2: T13RSEL (Bit 10)                          */
#define CCU6_TCTR2_T13RSEL_Msk            (0xc00UL)                 /*!< CCU6 TCTR2: T13RSEL (Bitfield-Mask: 0x03)             */
/* =========================================================  TCTR4  ========================================================= */
#define CCU6_TCTR4_T12RR_Pos              (0UL)                     /*!< CCU6 TCTR4: T12RR (Bit 0)                             */
#define CCU6_TCTR4_T12RR_Msk              (0x1UL)                   /*!< CCU6 TCTR4: T12RR (Bitfield-Mask: 0x01)               */
#define CCU6_TCTR4_T12RS_Pos              (1UL)                     /*!< CCU6 TCTR4: T12RS (Bit 1)                             */
#define CCU6_TCTR4_T12RS_Msk              (0x2UL)                   /*!< CCU6 TCTR4: T12RS (Bitfield-Mask: 0x01)               */
#define CCU6_TCTR4_T12RES_Pos             (2UL)                     /*!< CCU6 TCTR4: T12RES (Bit 2)                            */
#define CCU6_TCTR4_T12RES_Msk             (0x4UL)                   /*!< CCU6 TCTR4: T12RES (Bitfield-Mask: 0x01)              */
#define CCU6_TCTR4_DTRES_Pos              (3UL)                     /*!< CCU6 TCTR4: DTRES (Bit 3)                             */
#define CCU6_TCTR4_DTRES_Msk              (0x8UL)                   /*!< CCU6 TCTR4: DTRES (Bitfield-Mask: 0x01)               */
#define CCU6_TCTR4_T12CNT_Pos             (5UL)                     /*!< CCU6 TCTR4: T12CNT (Bit 5)                            */
#define CCU6_TCTR4_T12CNT_Msk             (0x20UL)                  /*!< CCU6 TCTR4: T12CNT (Bitfield-Mask: 0x01)              */
#define CCU6_TCTR4_T12STR_Pos             (6UL)                     /*!< CCU6 TCTR4: T12STR (Bit 6)                            */
#define CCU6_TCTR4_T12STR_Msk             (0x40UL)                  /*!< CCU6 TCTR4: T12STR (Bitfield-Mask: 0x01)              */
#define CCU6_TCTR4_T12STD_Pos             (7UL)                     /*!< CCU6 TCTR4: T12STD (Bit 7)                            */
#define CCU6_TCTR4_T12STD_Msk             (0x80UL)                  /*!< CCU6 TCTR4: T12STD (Bitfield-Mask: 0x01)              */
#define CCU6_TCTR4_T13RR_Pos              (8UL)                     /*!< CCU6 TCTR4: T13RR (Bit 8)                             */
#define CCU6_TCTR4_T13RR_Msk              (0x100UL)                 /*!< CCU6 TCTR4: T13RR (Bitfield-Mask: 0x01)               */
#define CCU6_TCTR4_T13RS_Pos              (9UL)                     /*!< CCU6 TCTR4: T13RS (Bit 9)                             */
#define CCU6_TCTR4_T13RS_Msk              (0x200UL)                 /*!< CCU6 TCTR4: T13RS (Bitfield-Mask: 0x01)               */
#define CCU6_TCTR4_T13RES_Pos             (10UL)                    /*!< CCU6 TCTR4: T13RES (Bit 10)                           */
#define CCU6_TCTR4_T13RES_Msk             (0x400UL)                 /*!< CCU6 TCTR4: T13RES (Bitfield-Mask: 0x01)              */
#define CCU6_TCTR4_T13CNT_Pos             (13UL)                    /*!< CCU6 TCTR4: T13CNT (Bit 13)                           */
#define CCU6_TCTR4_T13CNT_Msk             (0x2000UL)                /*!< CCU6 TCTR4: T13CNT (Bitfield-Mask: 0x01)              */
#define CCU6_TCTR4_T13STR_Pos             (14UL)                    /*!< CCU6 TCTR4: T13STR (Bit 14)                           */
#define CCU6_TCTR4_T13STR_Msk             (0x4000UL)                /*!< CCU6 TCTR4: T13STR (Bitfield-Mask: 0x01)              */
#define CCU6_TCTR4_T13STD_Pos             (15UL)                    /*!< CCU6 TCTR4: T13STD (Bit 15)                           */
#define CCU6_TCTR4_T13STD_Msk             (0x8000UL)                /*!< CCU6 TCTR4: T13STD (Bitfield-Mask: 0x01)              */
/* ========================================================  TRPCTR  ========================================================= */
#define CCU6_TRPCTR_TRPM0_Pos             (0UL)                     /*!< CCU6 TRPCTR: TRPM0 (Bit 0)                            */
#define CCU6_TRPCTR_TRPM0_Msk             (0x1UL)                   /*!< CCU6 TRPCTR: TRPM0 (Bitfield-Mask: 0x01)              */
#define CCU6_TRPCTR_TRPM1_Pos             (1UL)                     /*!< CCU6 TRPCTR: TRPM1 (Bit 1)                            */
#define CCU6_TRPCTR_TRPM1_Msk             (0x2UL)                   /*!< CCU6 TRPCTR: TRPM1 (Bitfield-Mask: 0x01)              */
#define CCU6_TRPCTR_TRPM2_Pos             (2UL)                     /*!< CCU6 TRPCTR: TRPM2 (Bit 2)                            */
#define CCU6_TRPCTR_TRPM2_Msk             (0x4UL)                   /*!< CCU6 TRPCTR: TRPM2 (Bitfield-Mask: 0x01)              */
#define CCU6_TRPCTR_TRPEN_Pos             (8UL)                     /*!< CCU6 TRPCTR: TRPEN (Bit 8)                            */
#define CCU6_TRPCTR_TRPEN_Msk             (0x3f00UL)                /*!< CCU6 TRPCTR: TRPEN (Bitfield-Mask: 0x3f)              */
#define CCU6_TRPCTR_TRPEN13_Pos           (14UL)                    /*!< CCU6 TRPCTR: TRPEN13 (Bit 14)                         */
#define CCU6_TRPCTR_TRPEN13_Msk           (0x4000UL)                /*!< CCU6 TRPCTR: TRPEN13 (Bitfield-Mask: 0x01)            */
#define CCU6_TRPCTR_TRPPEN_Pos            (15UL)                    /*!< CCU6 TRPCTR: TRPPEN (Bit 15)                          */
#define CCU6_TRPCTR_TRPPEN_Msk            (0x8000UL)                /*!< CCU6 TRPCTR: TRPPEN (Bitfield-Mask: 0x01)             */


/* =========================================================================================================================== */
/* ================                                            CPU                                            ================ */
/* =========================================================================================================================== */

/* =========================================================  AFSR  ========================================================== */
#define CPU_AFSR_CP0_Pos                  (0UL)                     /*!< CPU AFSR: CP0 (Bit 0)                                 */
#define CPU_AFSR_CP0_Msk                  (0x3UL)                   /*!< CPU AFSR: CP0 (Bitfield-Mask: 0x03)                   */
#define CPU_AFSR_CP1_Pos                  (2UL)                     /*!< CPU AFSR: CP1 (Bit 2)                                 */
#define CPU_AFSR_CP1_Msk                  (0xcUL)                   /*!< CPU AFSR: CP1 (Bitfield-Mask: 0x03)                   */
#define CPU_AFSR_CP2_Pos                  (4UL)                     /*!< CPU AFSR: CP2 (Bit 4)                                 */
#define CPU_AFSR_CP2_Msk                  (0x30UL)                  /*!< CPU AFSR: CP2 (Bitfield-Mask: 0x03)                   */
#define CPU_AFSR_CP3_Pos                  (6UL)                     /*!< CPU AFSR: CP3 (Bit 6)                                 */
#define CPU_AFSR_CP3_Msk                  (0xc0UL)                  /*!< CPU AFSR: CP3 (Bitfield-Mask: 0x03)                   */
#define CPU_AFSR_CP4_Pos                  (8UL)                     /*!< CPU AFSR: CP4 (Bit 8)                                 */
#define CPU_AFSR_CP4_Msk                  (0x300UL)                 /*!< CPU AFSR: CP4 (Bitfield-Mask: 0x03)                   */
#define CPU_AFSR_CP5_Pos                  (10UL)                    /*!< CPU AFSR: CP5 (Bit 10)                                */
#define CPU_AFSR_CP5_Msk                  (0xc00UL)                 /*!< CPU AFSR: CP5 (Bitfield-Mask: 0x03)                   */
#define CPU_AFSR_CP6_Pos                  (12UL)                    /*!< CPU AFSR: CP6 (Bit 12)                                */
#define CPU_AFSR_CP6_Msk                  (0x3000UL)                /*!< CPU AFSR: CP6 (Bitfield-Mask: 0x03)                   */
#define CPU_AFSR_CP7_Pos                  (14UL)                    /*!< CPU AFSR: CP7 (Bit 14)                                */
#define CPU_AFSR_CP7_Msk                  (0xc000UL)                /*!< CPU AFSR: CP7 (Bitfield-Mask: 0x03)                   */
#define CPU_AFSR_CP10_Pos                 (20UL)                    /*!< CPU AFSR: CP10 (Bit 20)                               */
#define CPU_AFSR_CP10_Msk                 (0x300000UL)              /*!< CPU AFSR: CP10 (Bitfield-Mask: 0x03)                  */
#define CPU_AFSR_CP11_Pos                 (22UL)                    /*!< CPU AFSR: CP11 (Bit 22)                               */
#define CPU_AFSR_CP11_Msk                 (0xc00000UL)              /*!< CPU AFSR: CP11 (Bitfield-Mask: 0x03)                  */
/* =========================================================  AIRCR  ========================================================= */
#define CPU_AIRCR_VECTKEY_Pos             (16UL)                    /*!< CPU AIRCR: VECTKEY (Bit 16)                           */
#define CPU_AIRCR_VECTKEY_Msk             (0xffff0000UL)            /*!< CPU AIRCR: VECTKEY (Bitfield-Mask: 0xffff)            */
#define CPU_AIRCR_ENDIANNESS_Pos          (15UL)                    /*!< CPU AIRCR: ENDIANNESS (Bit 15)                        */
#define CPU_AIRCR_ENDIANNESS_Msk          (0x8000UL)                /*!< CPU AIRCR: ENDIANNESS (Bitfield-Mask: 0x01)           */
#define CPU_AIRCR_PRIGROUP_Pos            (8UL)                     /*!< CPU AIRCR: PRIGROUP (Bit 8)                           */
#define CPU_AIRCR_PRIGROUP_Msk            (0x700UL)                 /*!< CPU AIRCR: PRIGROUP (Bitfield-Mask: 0x07)             */
#define CPU_AIRCR_SYSRESETREQ_Pos         (2UL)                     /*!< CPU AIRCR: SYSRESETREQ (Bit 2)                        */
#define CPU_AIRCR_SYSRESETREQ_Msk         (0x4UL)                   /*!< CPU AIRCR: SYSRESETREQ (Bitfield-Mask: 0x01)          */
#define CPU_AIRCR_VECTCLRACTIVE_Pos       (1UL)                     /*!< CPU AIRCR: VECTCLRACTIVE (Bit 1)                      */
#define CPU_AIRCR_VECTCLRACTIVE_Msk       (0x2UL)                   /*!< CPU AIRCR: VECTCLRACTIVE (Bitfield-Mask: 0x01)        */
#define CPU_AIRCR_VECTRESET_Pos           (0UL)                     /*!< CPU AIRCR: VECTRESET (Bit 0)                          */
#define CPU_AIRCR_VECTRESET_Msk           (0x1UL)                   /*!< CPU AIRCR: VECTRESET (Bitfield-Mask: 0x01)            */
/* =========================================================  BFAR  ========================================================== */
#define CPU_BFAR_ADDRESS_Pos              (0UL)                     /*!< CPU BFAR: ADDRESS (Bit 0)                             */
#define CPU_BFAR_ADDRESS_Msk              (0xffffffffUL)            /*!< CPU BFAR: ADDRESS (Bitfield-Mask: 0xffffffff)         */
/* ==========================================================  CCR  ========================================================== */
#define CPU_CCR_STKALIGN_Pos              (9UL)                     /*!< CPU CCR: STKALIGN (Bit 9)                             */
#define CPU_CCR_STKALIGN_Msk              (0x200UL)                 /*!< CPU CCR: STKALIGN (Bitfield-Mask: 0x01)               */
#define CPU_CCR_BFHFMIGN_Pos              (8UL)                     /*!< CPU CCR: BFHFMIGN (Bit 8)                             */
#define CPU_CCR_BFHFMIGN_Msk              (0x100UL)                 /*!< CPU CCR: BFHFMIGN (Bitfield-Mask: 0x01)               */
#define CPU_CCR_DIV_0_TRP_Pos             (4UL)                     /*!< CPU CCR: DIV_0_TRP (Bit 4)                            */
#define CPU_CCR_DIV_0_TRP_Msk             (0x10UL)                  /*!< CPU CCR: DIV_0_TRP (Bitfield-Mask: 0x01)              */
#define CPU_CCR_UNALIGN_TRP_Pos           (3UL)                     /*!< CPU CCR: UNALIGN_TRP (Bit 3)                          */
#define CPU_CCR_UNALIGN_TRP_Msk           (0x8UL)                   /*!< CPU CCR: UNALIGN_TRP (Bitfield-Mask: 0x01)            */
#define CPU_CCR_USERSETMPEND_Pos          (1UL)                     /*!< CPU CCR: USERSETMPEND (Bit 1)                         */
#define CPU_CCR_USERSETMPEND_Msk          (0x2UL)                   /*!< CPU CCR: USERSETMPEND (Bitfield-Mask: 0x01)           */
#define CPU_CCR_NONBASETHRDENA_Pos        (0UL)                     /*!< CPU CCR: NONBASETHRDENA (Bit 0)                       */
#define CPU_CCR_NONBASETHRDENA_Msk        (0x1UL)                   /*!< CPU CCR: NONBASETHRDENA (Bitfield-Mask: 0x01)         */
/* =========================================================  CFSR  ========================================================== */
#define CPU_CFSR_DIVBYZERO_Pos            (25UL)                    /*!< CPU CFSR: DIVBYZERO (Bit 25)                          */
#define CPU_CFSR_DIVBYZERO_Msk            (0x2000000UL)             /*!< CPU CFSR: DIVBYZERO (Bitfield-Mask: 0x01)             */
#define CPU_CFSR_UNALIGNED_Pos            (24UL)                    /*!< CPU CFSR: UNALIGNED (Bit 24)                          */
#define CPU_CFSR_UNALIGNED_Msk            (0x1000000UL)             /*!< CPU CFSR: UNALIGNED (Bitfield-Mask: 0x01)             */
#define CPU_CFSR_NOCP_Pos                 (19UL)                    /*!< CPU CFSR: NOCP (Bit 19)                               */
#define CPU_CFSR_NOCP_Msk                 (0x80000UL)               /*!< CPU CFSR: NOCP (Bitfield-Mask: 0x01)                  */
#define CPU_CFSR_INVPC_Pos                (18UL)                    /*!< CPU CFSR: INVPC (Bit 18)                              */
#define CPU_CFSR_INVPC_Msk                (0x40000UL)               /*!< CPU CFSR: INVPC (Bitfield-Mask: 0x01)                 */
#define CPU_CFSR_INVSTATE_Pos             (17UL)                    /*!< CPU CFSR: INVSTATE (Bit 17)                           */
#define CPU_CFSR_INVSTATE_Msk             (0x20000UL)               /*!< CPU CFSR: INVSTATE (Bitfield-Mask: 0x01)              */
#define CPU_CFSR_UNDEFINSTR_Pos           (16UL)                    /*!< CPU CFSR: UNDEFINSTR (Bit 16)                         */
#define CPU_CFSR_UNDEFINSTR_Msk           (0x10000UL)               /*!< CPU CFSR: UNDEFINSTR (Bitfield-Mask: 0x01)            */
#define CPU_CFSR_BFARVALID_Pos            (15UL)                    /*!< CPU CFSR: BFARVALID (Bit 15)                          */
#define CPU_CFSR_BFARVALID_Msk            (0x8000UL)                /*!< CPU CFSR: BFARVALID (Bitfield-Mask: 0x01)             */
#define CPU_CFSR_STKERR_Pos               (12UL)                    /*!< CPU CFSR: STKERR (Bit 12)                             */
#define CPU_CFSR_STKERR_Msk               (0x1000UL)                /*!< CPU CFSR: STKERR (Bitfield-Mask: 0x01)                */
#define CPU_CFSR_UNSTKERR_Pos             (11UL)                    /*!< CPU CFSR: UNSTKERR (Bit 11)                           */
#define CPU_CFSR_UNSTKERR_Msk             (0x800UL)                 /*!< CPU CFSR: UNSTKERR (Bitfield-Mask: 0x01)              */
#define CPU_CFSR_IMPRECISERR_Pos          (10UL)                    /*!< CPU CFSR: IMPRECISERR (Bit 10)                        */
#define CPU_CFSR_IMPRECISERR_Msk          (0x400UL)                 /*!< CPU CFSR: IMPRECISERR (Bitfield-Mask: 0x01)           */
#define CPU_CFSR_PRECISERR_Pos            (9UL)                     /*!< CPU CFSR: PRECISERR (Bit 9)                           */
#define CPU_CFSR_PRECISERR_Msk            (0x200UL)                 /*!< CPU CFSR: PRECISERR (Bitfield-Mask: 0x01)             */
#define CPU_CFSR_IBUSERR_Pos              (8UL)                     /*!< CPU CFSR: IBUSERR (Bit 8)                             */
#define CPU_CFSR_IBUSERR_Msk              (0x100UL)                 /*!< CPU CFSR: IBUSERR (Bitfield-Mask: 0x01)               */
#define CPU_CFSR_MMARVALID_Pos            (7UL)                     /*!< CPU CFSR: MMARVALID (Bit 7)                           */
#define CPU_CFSR_MMARVALID_Msk            (0x80UL)                  /*!< CPU CFSR: MMARVALID (Bitfield-Mask: 0x01)             */
#define CPU_CFSR_MSTERR_Pos               (4UL)                     /*!< CPU CFSR: MSTERR (Bit 4)                              */
#define CPU_CFSR_MSTERR_Msk               (0x10UL)                  /*!< CPU CFSR: MSTERR (Bitfield-Mask: 0x01)                */
#define CPU_CFSR_MUNSTKERR_Pos            (3UL)                     /*!< CPU CFSR: MUNSTKERR (Bit 3)                           */
#define CPU_CFSR_MUNSTKERR_Msk            (0x8UL)                   /*!< CPU CFSR: MUNSTKERR (Bitfield-Mask: 0x01)             */
#define CPU_CFSR_DACCVIOL_Pos             (1UL)                     /*!< CPU CFSR: DACCVIOL (Bit 1)                            */
#define CPU_CFSR_DACCVIOL_Msk             (0x2UL)                   /*!< CPU CFSR: DACCVIOL (Bitfield-Mask: 0x01)              */
#define CPU_CFSR_IACCVIOL_Pos             (0UL)                     /*!< CPU CFSR: IACCVIOL (Bit 0)                            */
#define CPU_CFSR_IACCVIOL_Msk             (0x1UL)                   /*!< CPU CFSR: IACCVIOL (Bitfield-Mask: 0x01)              */
/* =========================================================  CPUID  ========================================================= */
#define CPU_CPUID_IMPLEMENTER_Pos         (24UL)                    /*!< CPU CPUID: IMPLEMENTER (Bit 24)                       */
#define CPU_CPUID_IMPLEMENTER_Msk         (0xff000000UL)            /*!< CPU CPUID: IMPLEMENTER (Bitfield-Mask: 0xff)          */
#define CPU_CPUID_VARIANT_Pos             (20UL)                    /*!< CPU CPUID: VARIANT (Bit 20)                           */
#define CPU_CPUID_VARIANT_Msk             (0xf00000UL)              /*!< CPU CPUID: VARIANT (Bitfield-Mask: 0x0f)              */
#define CPU_CPUID_ARCHITECTURE_Pos        (16UL)                    /*!< CPU CPUID: ARCHITECTURE (Bit 16)                      */
#define CPU_CPUID_ARCHITECTURE_Msk        (0xf0000UL)               /*!< CPU CPUID: ARCHITECTURE (Bitfield-Mask: 0x0f)         */
#define CPU_CPUID_PARTNO_Pos              (4UL)                     /*!< CPU CPUID: PARTNO (Bit 4)                             */
#define CPU_CPUID_PARTNO_Msk              (0xfff0UL)                /*!< CPU CPUID: PARTNO (Bitfield-Mask: 0xfff)              */
#define CPU_CPUID_REVISION_Pos            (0UL)                     /*!< CPU CPUID: REVISION (Bit 0)                           */
#define CPU_CPUID_REVISION_Msk            (0xfUL)                   /*!< CPU CPUID: REVISION (Bitfield-Mask: 0x0f)             */
/* =========================================================  DFSR  ========================================================== */
#define CPU_DFSR_EXTERNAL_Pos             (4UL)                     /*!< CPU DFSR: EXTERNAL (Bit 4)                            */
#define CPU_DFSR_EXTERNAL_Msk             (0x10UL)                  /*!< CPU DFSR: EXTERNAL (Bitfield-Mask: 0x01)              */
#define CPU_DFSR_VCATCH_Pos               (3UL)                     /*!< CPU DFSR: VCATCH (Bit 3)                              */
#define CPU_DFSR_VCATCH_Msk               (0x8UL)                   /*!< CPU DFSR: VCATCH (Bitfield-Mask: 0x01)                */
#define CPU_DFSR_DWTTRAP_Pos              (2UL)                     /*!< CPU DFSR: DWTTRAP (Bit 2)                             */
#define CPU_DFSR_DWTTRAP_Msk              (0x4UL)                   /*!< CPU DFSR: DWTTRAP (Bitfield-Mask: 0x01)               */
#define CPU_DFSR_BKPT_Pos                 (1UL)                     /*!< CPU DFSR: BKPT (Bit 1)                                */
#define CPU_DFSR_BKPT_Msk                 (0x2UL)                   /*!< CPU DFSR: BKPT (Bitfield-Mask: 0x01)                  */
#define CPU_DFSR_HALTED_Pos               (0UL)                     /*!< CPU DFSR: HALTED (Bit 0)                              */
#define CPU_DFSR_HALTED_Msk               (0x1UL)                   /*!< CPU DFSR: HALTED (Bitfield-Mask: 0x01)                */
/* =========================================================  HFSR  ========================================================== */
#define CPU_HFSR_DEBUGEVT_Pos             (31UL)                    /*!< CPU HFSR: DEBUGEVT (Bit 31)                           */
#define CPU_HFSR_DEBUGEVT_Msk             (0x80000000UL)            /*!< CPU HFSR: DEBUGEVT (Bitfield-Mask: 0x01)              */
#define CPU_HFSR_FORCED_Pos               (30UL)                    /*!< CPU HFSR: FORCED (Bit 30)                             */
#define CPU_HFSR_FORCED_Msk               (0x40000000UL)            /*!< CPU HFSR: FORCED (Bitfield-Mask: 0x01)                */
#define CPU_HFSR_VECTTBL_Pos              (1UL)                     /*!< CPU HFSR: VECTTBL (Bit 1)                             */
#define CPU_HFSR_VECTTBL_Msk              (0x2UL)                   /*!< CPU HFSR: VECTTBL (Bitfield-Mask: 0x01)               */
/* =========================================================  ICSR  ========================================================== */
#define CPU_ICSR_NMIPENDSET_Pos           (31UL)                    /*!< CPU ICSR: NMIPENDSET (Bit 31)                         */
#define CPU_ICSR_NMIPENDSET_Msk           (0x80000000UL)            /*!< CPU ICSR: NMIPENDSET (Bitfield-Mask: 0x01)            */
#define CPU_ICSR_PENDSVSET_Pos            (28UL)                    /*!< CPU ICSR: PENDSVSET (Bit 28)                          */
#define CPU_ICSR_PENDSVSET_Msk            (0x10000000UL)            /*!< CPU ICSR: PENDSVSET (Bitfield-Mask: 0x01)             */
#define CPU_ICSR_PENDSVCLR_Pos            (27UL)                    /*!< CPU ICSR: PENDSVCLR (Bit 27)                          */
#define CPU_ICSR_PENDSVCLR_Msk            (0x8000000UL)             /*!< CPU ICSR: PENDSVCLR (Bitfield-Mask: 0x01)             */
#define CPU_ICSR_PENDSTSET_Pos            (26UL)                    /*!< CPU ICSR: PENDSTSET (Bit 26)                          */
#define CPU_ICSR_PENDSTSET_Msk            (0x4000000UL)             /*!< CPU ICSR: PENDSTSET (Bitfield-Mask: 0x01)             */
#define CPU_ICSR_PENDSTCLR_Pos            (25UL)                    /*!< CPU ICSR: PENDSTCLR (Bit 25)                          */
#define CPU_ICSR_PENDSTCLR_Msk            (0x2000000UL)             /*!< CPU ICSR: PENDSTCLR (Bitfield-Mask: 0x01)             */
#define CPU_ICSR_ISRPREEMPT_Pos           (23UL)                    /*!< CPU ICSR: ISRPREEMPT (Bit 23)                         */
#define CPU_ICSR_ISRPREEMPT_Msk           (0x800000UL)              /*!< CPU ICSR: ISRPREEMPT (Bitfield-Mask: 0x01)            */
#define CPU_ICSR_ISRPENDING_Pos           (22UL)                    /*!< CPU ICSR: ISRPENDING (Bit 22)                         */
#define CPU_ICSR_ISRPENDING_Msk           (0x400000UL)              /*!< CPU ICSR: ISRPENDING (Bitfield-Mask: 0x01)            */
#define CPU_ICSR_VECTPENDING_Pos          (12UL)                    /*!< CPU ICSR: VECTPENDING (Bit 12)                        */
#define CPU_ICSR_VECTPENDING_Msk          (0x1ff000UL)              /*!< CPU ICSR: VECTPENDING (Bitfield-Mask: 0x1ff)          */
#define CPU_ICSR_RETTOBASE_Pos            (11UL)                    /*!< CPU ICSR: RETTOBASE (Bit 11)                          */
#define CPU_ICSR_RETTOBASE_Msk            (0x800UL)                 /*!< CPU ICSR: RETTOBASE (Bitfield-Mask: 0x01)             */
#define CPU_ICSR_VECTACTIVE_Pos           (0UL)                     /*!< CPU ICSR: VECTACTIVE (Bit 0)                          */
#define CPU_ICSR_VECTACTIVE_Msk           (0x1ffUL)                 /*!< CPU ICSR: VECTACTIVE (Bitfield-Mask: 0x1ff)           */
/* ==========================================================  ICT  ========================================================== */
#define CPU_ICT_INTLINESNUM_Pos           (0UL)                     /*!< CPU ICT: INTLINESNUM (Bit 0)                          */
#define CPU_ICT_INTLINESNUM_Msk           (0x1fUL)                  /*!< CPU ICT: INTLINESNUM (Bitfield-Mask: 0x1f)            */
/* =========================================================  MMFAR  ========================================================= */
#define CPU_MMFAR_ADDRESS_Pos             (0UL)                     /*!< CPU MMFAR: ADDRESS (Bit 0)                            */
#define CPU_MMFAR_ADDRESS_Msk             (0xffffffffUL)            /*!< CPU MMFAR: ADDRESS (Bitfield-Mask: 0xffffffff)        */
/* ======================================================  NVIC_IABR0  ======================================================= */
#define CPU_NVIC_IABR0_Int_DMA_Pos        (15UL)                    /*!< CPU NVIC_IABR0: Int_DMA (Bit 15)                      */
#define CPU_NVIC_IABR0_Int_DMA_Msk        (0x8000UL)                /*!< CPU NVIC_IABR0: Int_DMA (Bitfield-Mask: 0x01)         */
#define CPU_NVIC_IABR0_Int_BDRV_Pos       (14UL)                    /*!< CPU NVIC_IABR0: Int_BDRV (Bit 14)                     */
#define CPU_NVIC_IABR0_Int_BDRV_Msk       (0x4000UL)                /*!< CPU NVIC_IABR0: Int_BDRV (Bitfield-Mask: 0x01)        */
#define CPU_NVIC_IABR0_Int_EXINT1_Pos     (13UL)                    /*!< CPU NVIC_IABR0: Int_EXINT1 (Bit 13)                   */
#define CPU_NVIC_IABR0_Int_EXINT1_Msk     (0x2000UL)                /*!< CPU NVIC_IABR0: Int_EXINT1 (Bitfield-Mask: 0x01)      */
#define CPU_NVIC_IABR0_Int_EXINT0_Pos     (12UL)                    /*!< CPU NVIC_IABR0: Int_EXINT0 (Bit 12)                   */
#define CPU_NVIC_IABR0_Int_EXINT0_Msk     (0x1000UL)                /*!< CPU NVIC_IABR0: Int_EXINT0 (Bitfield-Mask: 0x01)      */
#define CPU_NVIC_IABR0_Int_UART2_Pos      (11UL)                    /*!< CPU NVIC_IABR0: Int_UART2 (Bit 11)                    */
#define CPU_NVIC_IABR0_Int_UART2_Msk      (0x800UL)                 /*!< CPU NVIC_IABR0: Int_UART2 (Bitfield-Mask: 0x01)       */
#define CPU_NVIC_IABR0_Int_UART1_Pos      (10UL)                    /*!< CPU NVIC_IABR0: Int_UART1 (Bit 10)                    */
#define CPU_NVIC_IABR0_Int_UART1_Msk      (0x400UL)                 /*!< CPU NVIC_IABR0: Int_UART1 (Bitfield-Mask: 0x01)       */
#define CPU_NVIC_IABR0_Int_SSC2_Pos       (9UL)                     /*!< CPU NVIC_IABR0: Int_SSC2 (Bit 9)                      */
#define CPU_NVIC_IABR0_Int_SSC2_Msk       (0x200UL)                 /*!< CPU NVIC_IABR0: Int_SSC2 (Bitfield-Mask: 0x01)        */
#define CPU_NVIC_IABR0_Int_SSC1_Pos       (8UL)                     /*!< CPU NVIC_IABR0: Int_SSC1 (Bit 8)                      */
#define CPU_NVIC_IABR0_Int_SSC1_Msk       (0x100UL)                 /*!< CPU NVIC_IABR0: Int_SSC1 (Bitfield-Mask: 0x01)        */
#define CPU_NVIC_IABR0_Int_CCU6SR3_Pos    (7UL)                     /*!< CPU NVIC_IABR0: Int_CCU6SR3 (Bit 7)                   */
#define CPU_NVIC_IABR0_Int_CCU6SR3_Msk    (0x80UL)                  /*!< CPU NVIC_IABR0: Int_CCU6SR3 (Bitfield-Mask: 0x01)     */
#define CPU_NVIC_IABR0_Int_CCU6SR2_Pos    (6UL)                     /*!< CPU NVIC_IABR0: Int_CCU6SR2 (Bit 6)                   */
#define CPU_NVIC_IABR0_Int_CCU6SR2_Msk    (0x40UL)                  /*!< CPU NVIC_IABR0: Int_CCU6SR2 (Bitfield-Mask: 0x01)     */
#define CPU_NVIC_IABR0_Int_CCU6SR1_Pos    (5UL)                     /*!< CPU NVIC_IABR0: Int_CCU6SR1 (Bit 5)                   */
#define CPU_NVIC_IABR0_Int_CCU6SR1_Msk    (0x20UL)                  /*!< CPU NVIC_IABR0: Int_CCU6SR1 (Bitfield-Mask: 0x01)     */
#define CPU_NVIC_IABR0_Int_CCU6SR0_Pos    (4UL)                     /*!< CPU NVIC_IABR0: Int_CCU6SR0 (Bit 4)                   */
#define CPU_NVIC_IABR0_Int_CCU6SR0_Msk    (0x10UL)                  /*!< CPU NVIC_IABR0: Int_CCU6SR0 (Bitfield-Mask: 0x01)     */
#define CPU_NVIC_IABR0_Int_ADC1_Pos       (3UL)                     /*!< CPU NVIC_IABR0: Int_ADC1 (Bit 3)                      */
#define CPU_NVIC_IABR0_Int_ADC1_Msk       (0x8UL)                   /*!< CPU NVIC_IABR0: Int_ADC1 (Bitfield-Mask: 0x01)        */
#define CPU_NVIC_IABR0_Int_ADC2_Pos       (2UL)                     /*!< CPU NVIC_IABR0: Int_ADC2 (Bit 2)                      */
#define CPU_NVIC_IABR0_Int_ADC2_Msk       (0x4UL)                   /*!< CPU NVIC_IABR0: Int_ADC2 (Bitfield-Mask: 0x01)        */
#define CPU_NVIC_IABR0_Int_GPT2_Pos       (1UL)                     /*!< CPU NVIC_IABR0: Int_GPT2 (Bit 1)                      */
#define CPU_NVIC_IABR0_Int_GPT2_Msk       (0x2UL)                   /*!< CPU NVIC_IABR0: Int_GPT2 (Bitfield-Mask: 0x01)        */
#define CPU_NVIC_IABR0_Int_GPT1_Pos       (0UL)                     /*!< CPU NVIC_IABR0: Int_GPT1 (Bit 0)                      */
#define CPU_NVIC_IABR0_Int_GPT1_Msk       (0x1UL)                   /*!< CPU NVIC_IABR0: Int_GPT1 (Bitfield-Mask: 0x01)        */
/* ======================================================  NVIC_ICER0  ======================================================= */
#define CPU_NVIC_ICER0_Int_DMA_Pos        (15UL)                    /*!< CPU NVIC_ICER0: Int_DMA (Bit 15)                      */
#define CPU_NVIC_ICER0_Int_DMA_Msk        (0x8000UL)                /*!< CPU NVIC_ICER0: Int_DMA (Bitfield-Mask: 0x01)         */
#define CPU_NVIC_ICER0_Int_BDRV_Pos       (14UL)                    /*!< CPU NVIC_ICER0: Int_BDRV (Bit 14)                     */
#define CPU_NVIC_ICER0_Int_BDRV_Msk       (0x4000UL)                /*!< CPU NVIC_ICER0: Int_BDRV (Bitfield-Mask: 0x01)        */
#define CPU_NVIC_ICER0_Int_EXINT1_Pos     (13UL)                    /*!< CPU NVIC_ICER0: Int_EXINT1 (Bit 13)                   */
#define CPU_NVIC_ICER0_Int_EXINT1_Msk     (0x2000UL)                /*!< CPU NVIC_ICER0: Int_EXINT1 (Bitfield-Mask: 0x01)      */
#define CPU_NVIC_ICER0_Int_EXINT0_Pos     (12UL)                    /*!< CPU NVIC_ICER0: Int_EXINT0 (Bit 12)                   */
#define CPU_NVIC_ICER0_Int_EXINT0_Msk     (0x1000UL)                /*!< CPU NVIC_ICER0: Int_EXINT0 (Bitfield-Mask: 0x01)      */
#define CPU_NVIC_ICER0_Int_UART2_Pos      (11UL)                    /*!< CPU NVIC_ICER0: Int_UART2 (Bit 11)                    */
#define CPU_NVIC_ICER0_Int_UART2_Msk      (0x800UL)                 /*!< CPU NVIC_ICER0: Int_UART2 (Bitfield-Mask: 0x01)       */
#define CPU_NVIC_ICER0_Int_UART1_Pos      (10UL)                    /*!< CPU NVIC_ICER0: Int_UART1 (Bit 10)                    */
#define CPU_NVIC_ICER0_Int_UART1_Msk      (0x400UL)                 /*!< CPU NVIC_ICER0: Int_UART1 (Bitfield-Mask: 0x01)       */
#define CPU_NVIC_ICER0_Int_SSC2_Pos       (9UL)                     /*!< CPU NVIC_ICER0: Int_SSC2 (Bit 9)                      */
#define CPU_NVIC_ICER0_Int_SSC2_Msk       (0x200UL)                 /*!< CPU NVIC_ICER0: Int_SSC2 (Bitfield-Mask: 0x01)        */
#define CPU_NVIC_ICER0_Int_SSC1_Pos       (8UL)                     /*!< CPU NVIC_ICER0: Int_SSC1 (Bit 8)                      */
#define CPU_NVIC_ICER0_Int_SSC1_Msk       (0x100UL)                 /*!< CPU NVIC_ICER0: Int_SSC1 (Bitfield-Mask: 0x01)        */
#define CPU_NVIC_ICER0_Int_CCU6SR3_Pos    (7UL)                     /*!< CPU NVIC_ICER0: Int_CCU6SR3 (Bit 7)                   */
#define CPU_NVIC_ICER0_Int_CCU6SR3_Msk    (0x80UL)                  /*!< CPU NVIC_ICER0: Int_CCU6SR3 (Bitfield-Mask: 0x01)     */
#define CPU_NVIC_ICER0_Int_CCU6SR2_Pos    (6UL)                     /*!< CPU NVIC_ICER0: Int_CCU6SR2 (Bit 6)                   */
#define CPU_NVIC_ICER0_Int_CCU6SR2_Msk    (0x40UL)                  /*!< CPU NVIC_ICER0: Int_CCU6SR2 (Bitfield-Mask: 0x01)     */
#define CPU_NVIC_ICER0_Int_CCU6SR1_Pos    (5UL)                     /*!< CPU NVIC_ICER0: Int_CCU6SR1 (Bit 5)                   */
#define CPU_NVIC_ICER0_Int_CCU6SR1_Msk    (0x20UL)                  /*!< CPU NVIC_ICER0: Int_CCU6SR1 (Bitfield-Mask: 0x01)     */
#define CPU_NVIC_ICER0_Int_CCU6SR0_Pos    (4UL)                     /*!< CPU NVIC_ICER0: Int_CCU6SR0 (Bit 4)                   */
#define CPU_NVIC_ICER0_Int_CCU6SR0_Msk    (0x10UL)                  /*!< CPU NVIC_ICER0: Int_CCU6SR0 (Bitfield-Mask: 0x01)     */
#define CPU_NVIC_ICER0_Int_ADC1_Pos       (3UL)                     /*!< CPU NVIC_ICER0: Int_ADC1 (Bit 3)                      */
#define CPU_NVIC_ICER0_Int_ADC1_Msk       (0x8UL)                   /*!< CPU NVIC_ICER0: Int_ADC1 (Bitfield-Mask: 0x01)        */
#define CPU_NVIC_ICER0_Int_ADC2_Pos       (2UL)                     /*!< CPU NVIC_ICER0: Int_ADC2 (Bit 2)                      */
#define CPU_NVIC_ICER0_Int_ADC2_Msk       (0x4UL)                   /*!< CPU NVIC_ICER0: Int_ADC2 (Bitfield-Mask: 0x01)        */
#define CPU_NVIC_ICER0_Int_GPT2_Pos       (1UL)                     /*!< CPU NVIC_ICER0: Int_GPT2 (Bit 1)                      */
#define CPU_NVIC_ICER0_Int_GPT2_Msk       (0x2UL)                   /*!< CPU NVIC_ICER0: Int_GPT2 (Bitfield-Mask: 0x01)        */
#define CPU_NVIC_ICER0_Int_GPT1_Pos       (0UL)                     /*!< CPU NVIC_ICER0: Int_GPT1 (Bit 0)                      */
#define CPU_NVIC_ICER0_Int_GPT1_Msk       (0x1UL)                   /*!< CPU NVIC_ICER0: Int_GPT1 (Bitfield-Mask: 0x01)        */
/* ======================================================  NVIC_ICPR0  ======================================================= */
#define CPU_NVIC_ICPR0_Int_DMA_Pos        (15UL)                    /*!< CPU NVIC_ICPR0: Int_DMA (Bit 15)                      */
#define CPU_NVIC_ICPR0_Int_DMA_Msk        (0x8000UL)                /*!< CPU NVIC_ICPR0: Int_DMA (Bitfield-Mask: 0x01)         */
#define CPU_NVIC_ICPR0_Int_BDRV_Pos       (14UL)                    /*!< CPU NVIC_ICPR0: Int_BDRV (Bit 14)                     */
#define CPU_NVIC_ICPR0_Int_BDRV_Msk       (0x4000UL)                /*!< CPU NVIC_ICPR0: Int_BDRV (Bitfield-Mask: 0x01)        */
#define CPU_NVIC_ICPR0_Int_EXINT1_Pos     (13UL)                    /*!< CPU NVIC_ICPR0: Int_EXINT1 (Bit 13)                   */
#define CPU_NVIC_ICPR0_Int_EXINT1_Msk     (0x2000UL)                /*!< CPU NVIC_ICPR0: Int_EXINT1 (Bitfield-Mask: 0x01)      */
#define CPU_NVIC_ICPR0_Int_EXINT0_Pos     (12UL)                    /*!< CPU NVIC_ICPR0: Int_EXINT0 (Bit 12)                   */
#define CPU_NVIC_ICPR0_Int_EXINT0_Msk     (0x1000UL)                /*!< CPU NVIC_ICPR0: Int_EXINT0 (Bitfield-Mask: 0x01)      */
#define CPU_NVIC_ICPR0_Int_UART2_Pos      (11UL)                    /*!< CPU NVIC_ICPR0: Int_UART2 (Bit 11)                    */
#define CPU_NVIC_ICPR0_Int_UART2_Msk      (0x800UL)                 /*!< CPU NVIC_ICPR0: Int_UART2 (Bitfield-Mask: 0x01)       */
#define CPU_NVIC_ICPR0_Int_UART1_Pos      (10UL)                    /*!< CPU NVIC_ICPR0: Int_UART1 (Bit 10)                    */
#define CPU_NVIC_ICPR0_Int_UART1_Msk      (0x400UL)                 /*!< CPU NVIC_ICPR0: Int_UART1 (Bitfield-Mask: 0x01)       */
#define CPU_NVIC_ICPR0_Int_SSC2_Pos       (9UL)                     /*!< CPU NVIC_ICPR0: Int_SSC2 (Bit 9)                      */
#define CPU_NVIC_ICPR0_Int_SSC2_Msk       (0x200UL)                 /*!< CPU NVIC_ICPR0: Int_SSC2 (Bitfield-Mask: 0x01)        */
#define CPU_NVIC_ICPR0_Int_SSC1_Pos       (8UL)                     /*!< CPU NVIC_ICPR0: Int_SSC1 (Bit 8)                      */
#define CPU_NVIC_ICPR0_Int_SSC1_Msk       (0x100UL)                 /*!< CPU NVIC_ICPR0: Int_SSC1 (Bitfield-Mask: 0x01)        */
#define CPU_NVIC_ICPR0_Int_CCU6SR3_Pos    (7UL)                     /*!< CPU NVIC_ICPR0: Int_CCU6SR3 (Bit 7)                   */
#define CPU_NVIC_ICPR0_Int_CCU6SR3_Msk    (0x80UL)                  /*!< CPU NVIC_ICPR0: Int_CCU6SR3 (Bitfield-Mask: 0x01)     */
#define CPU_NVIC_ICPR0_Int_CCU6SR2_Pos    (6UL)                     /*!< CPU NVIC_ICPR0: Int_CCU6SR2 (Bit 6)                   */
#define CPU_NVIC_ICPR0_Int_CCU6SR2_Msk    (0x40UL)                  /*!< CPU NVIC_ICPR0: Int_CCU6SR2 (Bitfield-Mask: 0x01)     */
#define CPU_NVIC_ICPR0_Int_CCU6SR1_Pos    (5UL)                     /*!< CPU NVIC_ICPR0: Int_CCU6SR1 (Bit 5)                   */
#define CPU_NVIC_ICPR0_Int_CCU6SR1_Msk    (0x20UL)                  /*!< CPU NVIC_ICPR0: Int_CCU6SR1 (Bitfield-Mask: 0x01)     */
#define CPU_NVIC_ICPR0_Int_CCU6SR0_Pos    (4UL)                     /*!< CPU NVIC_ICPR0: Int_CCU6SR0 (Bit 4)                   */
#define CPU_NVIC_ICPR0_Int_CCU6SR0_Msk    (0x10UL)                  /*!< CPU NVIC_ICPR0: Int_CCU6SR0 (Bitfield-Mask: 0x01)     */
#define CPU_NVIC_ICPR0_Int_ADC1_Pos       (3UL)                     /*!< CPU NVIC_ICPR0: Int_ADC1 (Bit 3)                      */
#define CPU_NVIC_ICPR0_Int_ADC1_Msk       (0x8UL)                   /*!< CPU NVIC_ICPR0: Int_ADC1 (Bitfield-Mask: 0x01)        */
#define CPU_NVIC_ICPR0_Int_ADC2_Pos       (2UL)                     /*!< CPU NVIC_ICPR0: Int_ADC2 (Bit 2)                      */
#define CPU_NVIC_ICPR0_Int_ADC2_Msk       (0x4UL)                   /*!< CPU NVIC_ICPR0: Int_ADC2 (Bitfield-Mask: 0x01)        */
#define CPU_NVIC_ICPR0_Int_GPT2_Pos       (1UL)                     /*!< CPU NVIC_ICPR0: Int_GPT2 (Bit 1)                      */
#define CPU_NVIC_ICPR0_Int_GPT2_Msk       (0x2UL)                   /*!< CPU NVIC_ICPR0: Int_GPT2 (Bitfield-Mask: 0x01)        */
#define CPU_NVIC_ICPR0_Int_GPT1_Pos       (0UL)                     /*!< CPU NVIC_ICPR0: Int_GPT1 (Bit 0)                      */
#define CPU_NVIC_ICPR0_Int_GPT1_Msk       (0x1UL)                   /*!< CPU NVIC_ICPR0: Int_GPT1 (Bitfield-Mask: 0x01)        */
/* =======================================================  NVIC_IPR0  ======================================================= */
#define CPU_NVIC_IPR0_PRI_ADC1_Pos        (24UL)                    /*!< CPU NVIC_IPR0: PRI_ADC1 (Bit 24)                      */
#define CPU_NVIC_IPR0_PRI_ADC1_Msk        (0xff000000UL)            /*!< CPU NVIC_IPR0: PRI_ADC1 (Bitfield-Mask: 0xff)         */
#define CPU_NVIC_IPR0_PRI_ADC2_Pos        (16UL)                    /*!< CPU NVIC_IPR0: PRI_ADC2 (Bit 16)                      */
#define CPU_NVIC_IPR0_PRI_ADC2_Msk        (0xff0000UL)              /*!< CPU NVIC_IPR0: PRI_ADC2 (Bitfield-Mask: 0xff)         */
#define CPU_NVIC_IPR0_PRI_GPT2_Pos        (8UL)                     /*!< CPU NVIC_IPR0: PRI_GPT2 (Bit 8)                       */
#define CPU_NVIC_IPR0_PRI_GPT2_Msk        (0xff00UL)                /*!< CPU NVIC_IPR0: PRI_GPT2 (Bitfield-Mask: 0xff)         */
#define CPU_NVIC_IPR0_PRI_GPT1_Pos        (0UL)                     /*!< CPU NVIC_IPR0: PRI_GPT1 (Bit 0)                       */
#define CPU_NVIC_IPR0_PRI_GPT1_Msk        (0xffUL)                  /*!< CPU NVIC_IPR0: PRI_GPT1 (Bitfield-Mask: 0xff)         */
/* =======================================================  NVIC_IPR1  ======================================================= */
#define CPU_NVIC_IPR1_PRI_CCU6SR3_Pos     (24UL)                    /*!< CPU NVIC_IPR1: PRI_CCU6SR3 (Bit 24)                   */
#define CPU_NVIC_IPR1_PRI_CCU6SR3_Msk     (0xff000000UL)            /*!< CPU NVIC_IPR1: PRI_CCU6SR3 (Bitfield-Mask: 0xff)      */
#define CPU_NVIC_IPR1_PRI_CCU6SR2_Pos     (16UL)                    /*!< CPU NVIC_IPR1: PRI_CCU6SR2 (Bit 16)                   */
#define CPU_NVIC_IPR1_PRI_CCU6SR2_Msk     (0xff0000UL)              /*!< CPU NVIC_IPR1: PRI_CCU6SR2 (Bitfield-Mask: 0xff)      */
#define CPU_NVIC_IPR1_PRI_CCU6SR1_Pos     (8UL)                     /*!< CPU NVIC_IPR1: PRI_CCU6SR1 (Bit 8)                    */
#define CPU_NVIC_IPR1_PRI_CCU6SR1_Msk     (0xff00UL)                /*!< CPU NVIC_IPR1: PRI_CCU6SR1 (Bitfield-Mask: 0xff)      */
#define CPU_NVIC_IPR1_PRI_CCU6SR0_Pos     (0UL)                     /*!< CPU NVIC_IPR1: PRI_CCU6SR0 (Bit 0)                    */
#define CPU_NVIC_IPR1_PRI_CCU6SR0_Msk     (0xffUL)                  /*!< CPU NVIC_IPR1: PRI_CCU6SR0 (Bitfield-Mask: 0xff)      */
/* =======================================================  NVIC_IPR2  ======================================================= */
#define CPU_NVIC_IPR2_PRI_UART2_Pos       (24UL)                    /*!< CPU NVIC_IPR2: PRI_UART2 (Bit 24)                     */
#define CPU_NVIC_IPR2_PRI_UART2_Msk       (0xff000000UL)            /*!< CPU NVIC_IPR2: PRI_UART2 (Bitfield-Mask: 0xff)        */
#define CPU_NVIC_IPR2_PRI_UART1_Pos       (16UL)                    /*!< CPU NVIC_IPR2: PRI_UART1 (Bit 16)                     */
#define CPU_NVIC_IPR2_PRI_UART1_Msk       (0xff0000UL)              /*!< CPU NVIC_IPR2: PRI_UART1 (Bitfield-Mask: 0xff)        */
#define CPU_NVIC_IPR2_PRI_SSC2_Pos        (8UL)                     /*!< CPU NVIC_IPR2: PRI_SSC2 (Bit 8)                       */
#define CPU_NVIC_IPR2_PRI_SSC2_Msk        (0xff00UL)                /*!< CPU NVIC_IPR2: PRI_SSC2 (Bitfield-Mask: 0xff)         */
#define CPU_NVIC_IPR2_PRI_SSC1_Pos        (0UL)                     /*!< CPU NVIC_IPR2: PRI_SSC1 (Bit 0)                       */
#define CPU_NVIC_IPR2_PRI_SSC1_Msk        (0xffUL)                  /*!< CPU NVIC_IPR2: PRI_SSC1 (Bitfield-Mask: 0xff)         */
/* =======================================================  NVIC_IPR3  ======================================================= */
#define CPU_NVIC_IPR3_PRI_DMA_Pos         (24UL)                    /*!< CPU NVIC_IPR3: PRI_DMA (Bit 24)                       */
#define CPU_NVIC_IPR3_PRI_DMA_Msk         (0xff000000UL)            /*!< CPU NVIC_IPR3: PRI_DMA (Bitfield-Mask: 0xff)          */
#define CPU_NVIC_IPR3_PRI_BDRV_Pos        (16UL)                    /*!< CPU NVIC_IPR3: PRI_BDRV (Bit 16)                      */
#define CPU_NVIC_IPR3_PRI_BDRV_Msk        (0xff0000UL)              /*!< CPU NVIC_IPR3: PRI_BDRV (Bitfield-Mask: 0xff)         */
#define CPU_NVIC_IPR3_PRI_EXINT1_Pos      (8UL)                     /*!< CPU NVIC_IPR3: PRI_EXINT1 (Bit 8)                     */
#define CPU_NVIC_IPR3_PRI_EXINT1_Msk      (0xff00UL)                /*!< CPU NVIC_IPR3: PRI_EXINT1 (Bitfield-Mask: 0xff)       */
#define CPU_NVIC_IPR3_PRI_EXINT0_Pos      (0UL)                     /*!< CPU NVIC_IPR3: PRI_EXINT0 (Bit 0)                     */
#define CPU_NVIC_IPR3_PRI_EXINT0_Msk      (0xffUL)                  /*!< CPU NVIC_IPR3: PRI_EXINT0 (Bitfield-Mask: 0xff)       */
/* ======================================================  NVIC_ISER0  ======================================================= */
#define CPU_NVIC_ISER0_Int_DMA_Pos        (15UL)                    /*!< CPU NVIC_ISER0: Int_DMA (Bit 15)                      */
#define CPU_NVIC_ISER0_Int_DMA_Msk        (0x8000UL)                /*!< CPU NVIC_ISER0: Int_DMA (Bitfield-Mask: 0x01)         */
#define CPU_NVIC_ISER0_Int_BDRV_Pos       (14UL)                    /*!< CPU NVIC_ISER0: Int_BDRV (Bit 14)                     */
#define CPU_NVIC_ISER0_Int_BDRV_Msk       (0x4000UL)                /*!< CPU NVIC_ISER0: Int_BDRV (Bitfield-Mask: 0x01)        */
#define CPU_NVIC_ISER0_Int_EXINT1_Pos     (13UL)                    /*!< CPU NVIC_ISER0: Int_EXINT1 (Bit 13)                   */
#define CPU_NVIC_ISER0_Int_EXINT1_Msk     (0x2000UL)                /*!< CPU NVIC_ISER0: Int_EXINT1 (Bitfield-Mask: 0x01)      */
#define CPU_NVIC_ISER0_Int_EXINT0_Pos     (12UL)                    /*!< CPU NVIC_ISER0: Int_EXINT0 (Bit 12)                   */
#define CPU_NVIC_ISER0_Int_EXINT0_Msk     (0x1000UL)                /*!< CPU NVIC_ISER0: Int_EXINT0 (Bitfield-Mask: 0x01)      */
#define CPU_NVIC_ISER0_Int_UART2_Pos      (11UL)                    /*!< CPU NVIC_ISER0: Int_UART2 (Bit 11)                    */
#define CPU_NVIC_ISER0_Int_UART2_Msk      (0x800UL)                 /*!< CPU NVIC_ISER0: Int_UART2 (Bitfield-Mask: 0x01)       */
#define CPU_NVIC_ISER0_Int_UART1_Pos      (10UL)                    /*!< CPU NVIC_ISER0: Int_UART1 (Bit 10)                    */
#define CPU_NVIC_ISER0_Int_UART1_Msk      (0x400UL)                 /*!< CPU NVIC_ISER0: Int_UART1 (Bitfield-Mask: 0x01)       */
#define CPU_NVIC_ISER0_Int_SSC2_Pos       (9UL)                     /*!< CPU NVIC_ISER0: Int_SSC2 (Bit 9)                      */
#define CPU_NVIC_ISER0_Int_SSC2_Msk       (0x200UL)                 /*!< CPU NVIC_ISER0: Int_SSC2 (Bitfield-Mask: 0x01)        */
#define CPU_NVIC_ISER0_Int_SSC1_Pos       (8UL)                     /*!< CPU NVIC_ISER0: Int_SSC1 (Bit 8)                      */
#define CPU_NVIC_ISER0_Int_SSC1_Msk       (0x100UL)                 /*!< CPU NVIC_ISER0: Int_SSC1 (Bitfield-Mask: 0x01)        */
#define CPU_NVIC_ISER0_Int_CCU6SR3_Pos    (7UL)                     /*!< CPU NVIC_ISER0: Int_CCU6SR3 (Bit 7)                   */
#define CPU_NVIC_ISER0_Int_CCU6SR3_Msk    (0x80UL)                  /*!< CPU NVIC_ISER0: Int_CCU6SR3 (Bitfield-Mask: 0x01)     */
#define CPU_NVIC_ISER0_Int_CCU6SR2_Pos    (6UL)                     /*!< CPU NVIC_ISER0: Int_CCU6SR2 (Bit 6)                   */
#define CPU_NVIC_ISER0_Int_CCU6SR2_Msk    (0x40UL)                  /*!< CPU NVIC_ISER0: Int_CCU6SR2 (Bitfield-Mask: 0x01)     */
#define CPU_NVIC_ISER0_Int_CCU6SR1_Pos    (5UL)                     /*!< CPU NVIC_ISER0: Int_CCU6SR1 (Bit 5)                   */
#define CPU_NVIC_ISER0_Int_CCU6SR1_Msk    (0x20UL)                  /*!< CPU NVIC_ISER0: Int_CCU6SR1 (Bitfield-Mask: 0x01)     */
#define CPU_NVIC_ISER0_Int_CCU6SR0_Pos    (4UL)                     /*!< CPU NVIC_ISER0: Int_CCU6SR0 (Bit 4)                   */
#define CPU_NVIC_ISER0_Int_CCU6SR0_Msk    (0x10UL)                  /*!< CPU NVIC_ISER0: Int_CCU6SR0 (Bitfield-Mask: 0x01)     */
#define CPU_NVIC_ISER0_Int_ADC1_Pos       (3UL)                     /*!< CPU NVIC_ISER0: Int_ADC1 (Bit 3)                      */
#define CPU_NVIC_ISER0_Int_ADC1_Msk       (0x8UL)                   /*!< CPU NVIC_ISER0: Int_ADC1 (Bitfield-Mask: 0x01)        */
#define CPU_NVIC_ISER0_Int_ADC2_Pos       (2UL)                     /*!< CPU NVIC_ISER0: Int_ADC2 (Bit 2)                      */
#define CPU_NVIC_ISER0_Int_ADC2_Msk       (0x4UL)                   /*!< CPU NVIC_ISER0: Int_ADC2 (Bitfield-Mask: 0x01)        */
#define CPU_NVIC_ISER0_Int_GPT2_Pos       (1UL)                     /*!< CPU NVIC_ISER0: Int_GPT2 (Bit 1)                      */
#define CPU_NVIC_ISER0_Int_GPT2_Msk       (0x2UL)                   /*!< CPU NVIC_ISER0: Int_GPT2 (Bitfield-Mask: 0x01)        */
#define CPU_NVIC_ISER0_Int_GPT1_Pos       (0UL)                     /*!< CPU NVIC_ISER0: Int_GPT1 (Bit 0)                      */
#define CPU_NVIC_ISER0_Int_GPT1_Msk       (0x1UL)                   /*!< CPU NVIC_ISER0: Int_GPT1 (Bitfield-Mask: 0x01)        */
/* ======================================================  NVIC_ISPR0  ======================================================= */
#define CPU_NVIC_ISPR0_Int_DMA_Pos        (15UL)                    /*!< CPU NVIC_ISPR0: Int_DMA (Bit 15)                      */
#define CPU_NVIC_ISPR0_Int_DMA_Msk        (0x8000UL)                /*!< CPU NVIC_ISPR0: Int_DMA (Bitfield-Mask: 0x01)         */
#define CPU_NVIC_ISPR0_Int_BDRV_Pos       (14UL)                    /*!< CPU NVIC_ISPR0: Int_BDRV (Bit 14)                     */
#define CPU_NVIC_ISPR0_Int_BDRV_Msk       (0x4000UL)                /*!< CPU NVIC_ISPR0: Int_BDRV (Bitfield-Mask: 0x01)        */
#define CPU_NVIC_ISPR0_Int_EXINT1_Pos     (13UL)                    /*!< CPU NVIC_ISPR0: Int_EXINT1 (Bit 13)                   */
#define CPU_NVIC_ISPR0_Int_EXINT1_Msk     (0x2000UL)                /*!< CPU NVIC_ISPR0: Int_EXINT1 (Bitfield-Mask: 0x01)      */
#define CPU_NVIC_ISPR0_Int_EXINT0_Pos     (12UL)                    /*!< CPU NVIC_ISPR0: Int_EXINT0 (Bit 12)                   */
#define CPU_NVIC_ISPR0_Int_EXINT0_Msk     (0x1000UL)                /*!< CPU NVIC_ISPR0: Int_EXINT0 (Bitfield-Mask: 0x01)      */
#define CPU_NVIC_ISPR0_Int_UART2_Pos      (11UL)                    /*!< CPU NVIC_ISPR0: Int_UART2 (Bit 11)                    */
#define CPU_NVIC_ISPR0_Int_UART2_Msk      (0x800UL)                 /*!< CPU NVIC_ISPR0: Int_UART2 (Bitfield-Mask: 0x01)       */
#define CPU_NVIC_ISPR0_Int_UART1_Pos      (10UL)                    /*!< CPU NVIC_ISPR0: Int_UART1 (Bit 10)                    */
#define CPU_NVIC_ISPR0_Int_UART1_Msk      (0x400UL)                 /*!< CPU NVIC_ISPR0: Int_UART1 (Bitfield-Mask: 0x01)       */
#define CPU_NVIC_ISPR0_Int_SSC2_Pos       (9UL)                     /*!< CPU NVIC_ISPR0: Int_SSC2 (Bit 9)                      */
#define CPU_NVIC_ISPR0_Int_SSC2_Msk       (0x200UL)                 /*!< CPU NVIC_ISPR0: Int_SSC2 (Bitfield-Mask: 0x01)        */
#define CPU_NVIC_ISPR0_Int_SSC1_Pos       (8UL)                     /*!< CPU NVIC_ISPR0: Int_SSC1 (Bit 8)                      */
#define CPU_NVIC_ISPR0_Int_SSC1_Msk       (0x100UL)                 /*!< CPU NVIC_ISPR0: Int_SSC1 (Bitfield-Mask: 0x01)        */
#define CPU_NVIC_ISPR0_Int_CCU6SR3_Pos    (7UL)                     /*!< CPU NVIC_ISPR0: Int_CCU6SR3 (Bit 7)                   */
#define CPU_NVIC_ISPR0_Int_CCU6SR3_Msk    (0x80UL)                  /*!< CPU NVIC_ISPR0: Int_CCU6SR3 (Bitfield-Mask: 0x01)     */
#define CPU_NVIC_ISPR0_Int_CCU6SR2_Pos    (6UL)                     /*!< CPU NVIC_ISPR0: Int_CCU6SR2 (Bit 6)                   */
#define CPU_NVIC_ISPR0_Int_CCU6SR2_Msk    (0x40UL)                  /*!< CPU NVIC_ISPR0: Int_CCU6SR2 (Bitfield-Mask: 0x01)     */
#define CPU_NVIC_ISPR0_Int_CCU6SR1_Pos    (5UL)                     /*!< CPU NVIC_ISPR0: Int_CCU6SR1 (Bit 5)                   */
#define CPU_NVIC_ISPR0_Int_CCU6SR1_Msk    (0x20UL)                  /*!< CPU NVIC_ISPR0: Int_CCU6SR1 (Bitfield-Mask: 0x01)     */
#define CPU_NVIC_ISPR0_Int_CCU6SR0_Pos    (4UL)                     /*!< CPU NVIC_ISPR0: Int_CCU6SR0 (Bit 4)                   */
#define CPU_NVIC_ISPR0_Int_CCU6SR0_Msk    (0x10UL)                  /*!< CPU NVIC_ISPR0: Int_CCU6SR0 (Bitfield-Mask: 0x01)     */
#define CPU_NVIC_ISPR0_Int_ADC1_Pos       (3UL)                     /*!< CPU NVIC_ISPR0: Int_ADC1 (Bit 3)                      */
#define CPU_NVIC_ISPR0_Int_ADC1_Msk       (0x8UL)                   /*!< CPU NVIC_ISPR0: Int_ADC1 (Bitfield-Mask: 0x01)        */
#define CPU_NVIC_ISPR0_Int_ADC2_Pos       (2UL)                     /*!< CPU NVIC_ISPR0: Int_ADC2 (Bit 2)                      */
#define CPU_NVIC_ISPR0_Int_ADC2_Msk       (0x4UL)                   /*!< CPU NVIC_ISPR0: Int_ADC2 (Bitfield-Mask: 0x01)        */
#define CPU_NVIC_ISPR0_Int_GPT2_Pos       (1UL)                     /*!< CPU NVIC_ISPR0: Int_GPT2 (Bit 1)                      */
#define CPU_NVIC_ISPR0_Int_GPT2_Msk       (0x2UL)                   /*!< CPU NVIC_ISPR0: Int_GPT2 (Bitfield-Mask: 0x01)        */
#define CPU_NVIC_ISPR0_Int_GPT1_Pos       (0UL)                     /*!< CPU NVIC_ISPR0: Int_GPT1 (Bit 0)                      */
#define CPU_NVIC_ISPR0_Int_GPT1_Msk       (0x1UL)                   /*!< CPU NVIC_ISPR0: Int_GPT1 (Bitfield-Mask: 0x01)        */
/* ==========================================================  SCR  ========================================================== */
#define CPU_SCR_SEVONPEND_Pos             (4UL)                     /*!< CPU SCR: SEVONPEND (Bit 4)                            */
#define CPU_SCR_SEVONPEND_Msk             (0x10UL)                  /*!< CPU SCR: SEVONPEND (Bitfield-Mask: 0x01)              */
#define CPU_SCR_SLEEPDEEP_Pos             (2UL)                     /*!< CPU SCR: SLEEPDEEP (Bit 2)                            */
#define CPU_SCR_SLEEPDEEP_Msk             (0x4UL)                   /*!< CPU SCR: SLEEPDEEP (Bitfield-Mask: 0x01)              */
#define CPU_SCR_SLEEPONEXIT_Pos           (1UL)                     /*!< CPU SCR: SLEEPONEXIT (Bit 1)                          */
#define CPU_SCR_SLEEPONEXIT_Msk           (0x2UL)                   /*!< CPU SCR: SLEEPONEXIT (Bitfield-Mask: 0x01)            */
/* =========================================================  SHCSR  ========================================================= */
#define CPU_SHCSR_USGFAULTENA_Pos         (18UL)                    /*!< CPU SHCSR: USGFAULTENA (Bit 18)                       */
#define CPU_SHCSR_USGFAULTENA_Msk         (0x40000UL)               /*!< CPU SHCSR: USGFAULTENA (Bitfield-Mask: 0x01)          */
#define CPU_SHCSR_BUSFAULTENA_Pos         (17UL)                    /*!< CPU SHCSR: BUSFAULTENA (Bit 17)                       */
#define CPU_SHCSR_BUSFAULTENA_Msk         (0x20000UL)               /*!< CPU SHCSR: BUSFAULTENA (Bitfield-Mask: 0x01)          */
#define CPU_SHCSR_MEMFAULTENA_Pos         (16UL)                    /*!< CPU SHCSR: MEMFAULTENA (Bit 16)                       */
#define CPU_SHCSR_MEMFAULTENA_Msk         (0x10000UL)               /*!< CPU SHCSR: MEMFAULTENA (Bitfield-Mask: 0x01)          */
#define CPU_SHCSR_SVCALLPENDED_Pos        (15UL)                    /*!< CPU SHCSR: SVCALLPENDED (Bit 15)                      */
#define CPU_SHCSR_SVCALLPENDED_Msk        (0x8000UL)                /*!< CPU SHCSR: SVCALLPENDED (Bitfield-Mask: 0x01)         */
#define CPU_SHCSR_BUSFAULTPENDED_Pos      (14UL)                    /*!< CPU SHCSR: BUSFAULTPENDED (Bit 14)                    */
#define CPU_SHCSR_BUSFAULTPENDED_Msk      (0x4000UL)                /*!< CPU SHCSR: BUSFAULTPENDED (Bitfield-Mask: 0x01)       */
#define CPU_SHCSR_MEMFAULTPENDED_Pos      (13UL)                    /*!< CPU SHCSR: MEMFAULTPENDED (Bit 13)                    */
#define CPU_SHCSR_MEMFAULTPENDED_Msk      (0x2000UL)                /*!< CPU SHCSR: MEMFAULTPENDED (Bitfield-Mask: 0x01)       */
#define CPU_SHCSR_USGFAULTPENDED_Pos      (12UL)                    /*!< CPU SHCSR: USGFAULTPENDED (Bit 12)                    */
#define CPU_SHCSR_USGFAULTPENDED_Msk      (0x1000UL)                /*!< CPU SHCSR: USGFAULTPENDED (Bitfield-Mask: 0x01)       */
#define CPU_SHCSR_SYSTICKACT_Pos          (11UL)                    /*!< CPU SHCSR: SYSTICKACT (Bit 11)                        */
#define CPU_SHCSR_SYSTICKACT_Msk          (0x800UL)                 /*!< CPU SHCSR: SYSTICKACT (Bitfield-Mask: 0x01)           */
#define CPU_SHCSR_PENDSVACT_Pos           (10UL)                    /*!< CPU SHCSR: PENDSVACT (Bit 10)                         */
#define CPU_SHCSR_PENDSVACT_Msk           (0x400UL)                 /*!< CPU SHCSR: PENDSVACT (Bitfield-Mask: 0x01)            */
#define CPU_SHCSR_MONITORACT_Pos          (8UL)                     /*!< CPU SHCSR: MONITORACT (Bit 8)                         */
#define CPU_SHCSR_MONITORACT_Msk          (0x100UL)                 /*!< CPU SHCSR: MONITORACT (Bitfield-Mask: 0x01)           */
#define CPU_SHCSR_SVCALLACT_Pos           (7UL)                     /*!< CPU SHCSR: SVCALLACT (Bit 7)                          */
#define CPU_SHCSR_SVCALLACT_Msk           (0x80UL)                  /*!< CPU SHCSR: SVCALLACT (Bitfield-Mask: 0x01)            */
#define CPU_SHCSR_USGFAULTACT_Pos         (3UL)                     /*!< CPU SHCSR: USGFAULTACT (Bit 3)                        */
#define CPU_SHCSR_USGFAULTACT_Msk         (0x8UL)                   /*!< CPU SHCSR: USGFAULTACT (Bitfield-Mask: 0x01)          */
#define CPU_SHCSR_BUSFAULTACT_Pos         (1UL)                     /*!< CPU SHCSR: BUSFAULTACT (Bit 1)                        */
#define CPU_SHCSR_BUSFAULTACT_Msk         (0x2UL)                   /*!< CPU SHCSR: BUSFAULTACT (Bitfield-Mask: 0x01)          */
#define CPU_SHCSR_MEMFAULTACT_Pos         (0UL)                     /*!< CPU SHCSR: MEMFAULTACT (Bit 0)                        */
#define CPU_SHCSR_MEMFAULTACT_Msk         (0x1UL)                   /*!< CPU SHCSR: MEMFAULTACT (Bitfield-Mask: 0x01)          */
/* =========================================================  SHPR1  ========================================================= */
#define CPU_SHPR1_PRI_7_Pos               (24UL)                    /*!< CPU SHPR1: PRI_7 (Bit 24)                             */
#define CPU_SHPR1_PRI_7_Msk               (0xff000000UL)            /*!< CPU SHPR1: PRI_7 (Bitfield-Mask: 0xff)                */
#define CPU_SHPR1_PRI_6_Pos               (16UL)                    /*!< CPU SHPR1: PRI_6 (Bit 16)                             */
#define CPU_SHPR1_PRI_6_Msk               (0xff0000UL)              /*!< CPU SHPR1: PRI_6 (Bitfield-Mask: 0xff)                */
#define CPU_SHPR1_PRI_5_Pos               (8UL)                     /*!< CPU SHPR1: PRI_5 (Bit 8)                              */
#define CPU_SHPR1_PRI_5_Msk               (0xff00UL)                /*!< CPU SHPR1: PRI_5 (Bitfield-Mask: 0xff)                */
#define CPU_SHPR1_PRI_4_Pos               (0UL)                     /*!< CPU SHPR1: PRI_4 (Bit 0)                              */
#define CPU_SHPR1_PRI_4_Msk               (0xffUL)                  /*!< CPU SHPR1: PRI_4 (Bitfield-Mask: 0xff)                */
/* =========================================================  SHPR2  ========================================================= */
#define CPU_SHPR2_PRI_11_Pos              (24UL)                    /*!< CPU SHPR2: PRI_11 (Bit 24)                            */
#define CPU_SHPR2_PRI_11_Msk              (0xff000000UL)            /*!< CPU SHPR2: PRI_11 (Bitfield-Mask: 0xff)               */
#define CPU_SHPR2_PRI_10_Pos              (16UL)                    /*!< CPU SHPR2: PRI_10 (Bit 16)                            */
#define CPU_SHPR2_PRI_10_Msk              (0xff0000UL)              /*!< CPU SHPR2: PRI_10 (Bitfield-Mask: 0xff)               */
#define CPU_SHPR2_PRI_9_Pos               (8UL)                     /*!< CPU SHPR2: PRI_9 (Bit 8)                              */
#define CPU_SHPR2_PRI_9_Msk               (0xff00UL)                /*!< CPU SHPR2: PRI_9 (Bitfield-Mask: 0xff)                */
#define CPU_SHPR2_PRI_8_Pos               (0UL)                     /*!< CPU SHPR2: PRI_8 (Bit 0)                              */
#define CPU_SHPR2_PRI_8_Msk               (0xffUL)                  /*!< CPU SHPR2: PRI_8 (Bitfield-Mask: 0xff)                */
/* =========================================================  SHPR3  ========================================================= */
#define CPU_SHPR3_PRI_15_Pos              (24UL)                    /*!< CPU SHPR3: PRI_15 (Bit 24)                            */
#define CPU_SHPR3_PRI_15_Msk              (0xff000000UL)            /*!< CPU SHPR3: PRI_15 (Bitfield-Mask: 0xff)               */
#define CPU_SHPR3_PRI_14_Pos              (16UL)                    /*!< CPU SHPR3: PRI_14 (Bit 16)                            */
#define CPU_SHPR3_PRI_14_Msk              (0xff0000UL)              /*!< CPU SHPR3: PRI_14 (Bitfield-Mask: 0xff)               */
#define CPU_SHPR3_PRI_13_Pos              (8UL)                     /*!< CPU SHPR3: PRI_13 (Bit 8)                             */
#define CPU_SHPR3_PRI_13_Msk              (0xff00UL)                /*!< CPU SHPR3: PRI_13 (Bitfield-Mask: 0xff)               */
#define CPU_SHPR3_PRI_12_Pos              (0UL)                     /*!< CPU SHPR3: PRI_12 (Bit 0)                             */
#define CPU_SHPR3_PRI_12_Msk              (0xffUL)                  /*!< CPU SHPR3: PRI_12 (Bitfield-Mask: 0xff)               */
/* ======================================================  SYSTICK_CAL  ====================================================== */
#define CPU_SYSTICK_CAL_NOREF_Pos         (31UL)                    /*!< CPU SYSTICK_CAL: NOREF (Bit 31)                       */
#define CPU_SYSTICK_CAL_NOREF_Msk         (0x80000000UL)            /*!< CPU SYSTICK_CAL: NOREF (Bitfield-Mask: 0x01)          */
#define CPU_SYSTICK_CAL_SKEW_Pos          (30UL)                    /*!< CPU SYSTICK_CAL: SKEW (Bit 30)                        */
#define CPU_SYSTICK_CAL_SKEW_Msk          (0x40000000UL)            /*!< CPU SYSTICK_CAL: SKEW (Bitfield-Mask: 0x01)           */
#define CPU_SYSTICK_CAL_TENMS_Pos         (0UL)                     /*!< CPU SYSTICK_CAL: TENMS (Bit 0)                        */
#define CPU_SYSTICK_CAL_TENMS_Msk         (0xffffffUL)              /*!< CPU SYSTICK_CAL: TENMS (Bitfield-Mask: 0xffffff)      */
/* ======================================================  SYSTICK_CS  ======================================================= */
#define CPU_SYSTICK_CS_COUNTFLAG_Pos      (16UL)                    /*!< CPU SYSTICK_CS: COUNTFLAG (Bit 16)                    */
#define CPU_SYSTICK_CS_COUNTFLAG_Msk      (0x10000UL)               /*!< CPU SYSTICK_CS: COUNTFLAG (Bitfield-Mask: 0x01)       */
#define CPU_SYSTICK_CS_CLKSOURCE_Pos      (2UL)                     /*!< CPU SYSTICK_CS: CLKSOURCE (Bit 2)                     */
#define CPU_SYSTICK_CS_CLKSOURCE_Msk      (0x4UL)                   /*!< CPU SYSTICK_CS: CLKSOURCE (Bitfield-Mask: 0x01)       */
#define CPU_SYSTICK_CS_TICKINT_Pos        (1UL)                     /*!< CPU SYSTICK_CS: TICKINT (Bit 1)                       */
#define CPU_SYSTICK_CS_TICKINT_Msk        (0x2UL)                   /*!< CPU SYSTICK_CS: TICKINT (Bitfield-Mask: 0x01)         */
#define CPU_SYSTICK_CS_ENABLE_Pos         (0UL)                     /*!< CPU SYSTICK_CS: ENABLE (Bit 0)                        */
#define CPU_SYSTICK_CS_ENABLE_Msk         (0x1UL)                   /*!< CPU SYSTICK_CS: ENABLE (Bitfield-Mask: 0x01)          */
/* ======================================================  SYSTICK_CUR  ====================================================== */
#define CPU_SYSTICK_CUR_CURRENT_Pos       (0UL)                     /*!< CPU SYSTICK_CUR: CURRENT (Bit 0)                      */
#define CPU_SYSTICK_CUR_CURRENT_Msk       (0xffffffUL)              /*!< CPU SYSTICK_CUR: CURRENT (Bitfield-Mask: 0xffffff)    */
/* ======================================================  SYSTICK_RL  ======================================================= */
#define CPU_SYSTICK_RL_RELOAD_Pos         (0UL)                     /*!< CPU SYSTICK_RL: RELOAD (Bit 0)                        */
#define CPU_SYSTICK_RL_RELOAD_Msk         (0xffffffUL)              /*!< CPU SYSTICK_RL: RELOAD (Bitfield-Mask: 0xffffff)      */
/* =========================================================  VTOR  ========================================================== */
#define CPU_VTOR_TBLOFF_Pos               (7UL)                     /*!< CPU VTOR: TBLOFF (Bit 7)                              */
#define CPU_VTOR_TBLOFF_Msk               (0xffffff80UL)            /*!< CPU VTOR: TBLOFF (Bitfield-Mask: 0x1ffffff)           */


/* =========================================================================================================================== */
/* ================                                            DMA                                            ================ */
/* =========================================================================================================================== */

/* ===================================================  ALT_CTRL_BASE_PTR  =================================================== */
#define DMA_ALT_CTRL_BASE_PTR_ALT_CTRL_BASE_PTR_Pos (0UL)           /*!< DMA ALT_CTRL_BASE_PTR: ALT_CTRL_BASE_PTR (Bit 0)      */
#define DMA_ALT_CTRL_BASE_PTR_ALT_CTRL_BASE_PTR_Msk (0xffffffffUL)  /*!< DMA ALT_CTRL_BASE_PTR: ALT_CTRL_BASE_PTR (Bitfield-Mask: 0xffffffff) */
/* ==========================================================  CFG  ========================================================== */
#define DMA_CFG_CHN1_PROT_CTRL_Pos        (5UL)                     /*!< DMA CFG: CHN1_PROT_CTRL (Bit 5)                       */
#define DMA_CFG_CHN1_PROT_CTRL_Msk        (0xe0UL)                  /*!< DMA CFG: CHN1_PROT_CTRL (Bitfield-Mask: 0x07)         */
#define DMA_CFG_MASTER_ENABLE_Pos         (0UL)                     /*!< DMA CFG: MASTER_ENABLE (Bit 0)                        */
#define DMA_CFG_MASTER_ENABLE_Msk         (0x1UL)                   /*!< DMA CFG: MASTER_ENABLE (Bitfield-Mask: 0x01)          */
/* ====================================================  CHNL_ENABLE_CLR  ==================================================== */
#define DMA_CHNL_ENABLE_CLR_CHNL_ENABLE_CLR_Pos (0UL)               /*!< DMA CHNL_ENABLE_CLR: CHNL_ENABLE_CLR (Bit 0)          */
#define DMA_CHNL_ENABLE_CLR_CHNL_ENABLE_CLR_Msk (0x3fffUL)          /*!< DMA CHNL_ENABLE_CLR: CHNL_ENABLE_CLR (Bitfield-Mask: 0x3fff) */
/* ====================================================  CHNL_ENABLE_SET  ==================================================== */
#define DMA_CHNL_ENABLE_SET_CHNL_ENABLE_SET_Pos (0UL)               /*!< DMA CHNL_ENABLE_SET: CHNL_ENABLE_SET (Bit 0)          */
#define DMA_CHNL_ENABLE_SET_CHNL_ENABLE_SET_Msk (0x3fffUL)          /*!< DMA CHNL_ENABLE_SET: CHNL_ENABLE_SET (Bitfield-Mask: 0x3fff) */
/* ===================================================  CHNL_PRI_ALT_CLR  ==================================================== */
#define DMA_CHNL_PRI_ALT_CLR_CHNL_PRI_ALT_CLR_Pos (0UL)             /*!< DMA CHNL_PRI_ALT_CLR: CHNL_PRI_ALT_CLR (Bit 0)        */
#define DMA_CHNL_PRI_ALT_CLR_CHNL_PRI_ALT_CLR_Msk (0x3fffUL)        /*!< DMA CHNL_PRI_ALT_CLR: CHNL_PRI_ALT_CLR (Bitfield-Mask: 0x3fff) */
/* ===================================================  CHNL_PRI_ALT_SET  ==================================================== */
#define DMA_CHNL_PRI_ALT_SET_CHNL_PRI_ALT_SET_Pos (0UL)             /*!< DMA CHNL_PRI_ALT_SET: CHNL_PRI_ALT_SET (Bit 0)        */
#define DMA_CHNL_PRI_ALT_SET_CHNL_PRI_ALT_SET_Msk (0x3fffUL)        /*!< DMA CHNL_PRI_ALT_SET: CHNL_PRI_ALT_SET (Bitfield-Mask: 0x3fff) */
/* ===================================================  CHNL_PRIORITY_CLR  =================================================== */
#define DMA_CHNL_PRIORITY_CLR_CHNL_PRIORITY_CLR_Pos (0UL)           /*!< DMA CHNL_PRIORITY_CLR: CHNL_PRIORITY_CLR (Bit 0)      */
#define DMA_CHNL_PRIORITY_CLR_CHNL_PRIORITY_CLR_Msk (0x3fffUL)      /*!< DMA CHNL_PRIORITY_CLR: CHNL_PRIORITY_CLR (Bitfield-Mask: 0x3fff) */
/* ===================================================  CHNL_PRIORITY_SET  =================================================== */
#define DMA_CHNL_PRIORITY_SET_CHNL_PRIORITY_SET_Pos (0UL)           /*!< DMA CHNL_PRIORITY_SET: CHNL_PRIORITY_SET (Bit 0)      */
#define DMA_CHNL_PRIORITY_SET_CHNL_PRIORITY_SET_Msk (0x3fffUL)      /*!< DMA CHNL_PRIORITY_SET: CHNL_PRIORITY_SET (Bitfield-Mask: 0x3fff) */
/* ===================================================  CHNL_REQ_MASK_CLR  =================================================== */
#define DMA_CHNL_REQ_MASK_CLR_CHNL_REQ_MASK_CLR_Pos (0UL)           /*!< DMA CHNL_REQ_MASK_CLR: CHNL_REQ_MASK_CLR (Bit 0)      */
#define DMA_CHNL_REQ_MASK_CLR_CHNL_REQ_MASK_CLR_Msk (0x3fffUL)      /*!< DMA CHNL_REQ_MASK_CLR: CHNL_REQ_MASK_CLR (Bitfield-Mask: 0x3fff) */
/* ===================================================  CHNL_REQ_MASK_SET  =================================================== */
#define DMA_CHNL_REQ_MASK_SET_CHNL_REQ_MASK_SET_Pos (0UL)           /*!< DMA CHNL_REQ_MASK_SET: CHNL_REQ_MASK_SET (Bit 0)      */
#define DMA_CHNL_REQ_MASK_SET_CHNL_REQ_MASK_SET_Msk (0x3fffUL)      /*!< DMA CHNL_REQ_MASK_SET: CHNL_REQ_MASK_SET (Bitfield-Mask: 0x3fff) */
/* ====================================================  CHNL_SW_REQUEST  ==================================================== */
#define DMA_CHNL_SW_REQUEST_CHNL_SW_REQUEST_Pos (0UL)               /*!< DMA CHNL_SW_REQUEST: CHNL_SW_REQUEST (Bit 0)          */
#define DMA_CHNL_SW_REQUEST_CHNL_SW_REQUEST_Msk (0x3fffUL)          /*!< DMA CHNL_SW_REQUEST: CHNL_SW_REQUEST (Bitfield-Mask: 0x3fff) */
/* ===================================================  CHNL_USEBURST_CLR  =================================================== */
#define DMA_CHNL_USEBURST_CLR_CHNL_USEBURST_CLR_Pos (0UL)           /*!< DMA CHNL_USEBURST_CLR: CHNL_USEBURST_CLR (Bit 0)      */
#define DMA_CHNL_USEBURST_CLR_CHNL_USEBURST_CLR_Msk (0x3fffUL)      /*!< DMA CHNL_USEBURST_CLR: CHNL_USEBURST_CLR (Bitfield-Mask: 0x3fff) */
/* ===================================================  CHNL_USEBURST_SET  =================================================== */
#define DMA_CHNL_USEBURST_SET_CHNL_USEBURST_SET_Pos (0UL)           /*!< DMA CHNL_USEBURST_SET: CHNL_USEBURST_SET (Bit 0)      */
#define DMA_CHNL_USEBURST_SET_CHNL_USEBURST_SET_Msk (0x3fffUL)      /*!< DMA CHNL_USEBURST_SET: CHNL_USEBURST_SET (Bitfield-Mask: 0x3fff) */
/* =====================================================  CTRL_BASE_PTR  ===================================================== */
#define DMA_CTRL_BASE_PTR_CTRL_BASE_PTR_Pos (9UL)                   /*!< DMA CTRL_BASE_PTR: CTRL_BASE_PTR (Bit 9)              */
#define DMA_CTRL_BASE_PTR_CTRL_BASE_PTR_Msk (0xfffffe00UL)          /*!< DMA CTRL_BASE_PTR: CTRL_BASE_PTR (Bitfield-Mask: 0x7fffff) */
/* ========================================================  ERR_CLR  ======================================================== */
#define DMA_ERR_CLR_ERR_CLR_Pos           (0UL)                     /*!< DMA ERR_CLR: ERR_CLR (Bit 0)                          */
#define DMA_ERR_CLR_ERR_CLR_Msk           (0x1UL)                   /*!< DMA ERR_CLR: ERR_CLR (Bitfield-Mask: 0x01)            */
/* ========================================================  STATUS  ========================================================= */
#define DMA_STATUS_CHNLS_MINUS1_Pos       (16UL)                    /*!< DMA STATUS: CHNLS_MINUS1 (Bit 16)                     */
#define DMA_STATUS_CHNLS_MINUS1_Msk       (0x1f0000UL)              /*!< DMA STATUS: CHNLS_MINUS1 (Bitfield-Mask: 0x1f)        */
#define DMA_STATUS_STATE_Pos              (4UL)                     /*!< DMA STATUS: STATE (Bit 4)                             */
#define DMA_STATUS_STATE_Msk              (0xf0UL)                  /*!< DMA STATUS: STATE (Bitfield-Mask: 0x0f)               */
#define DMA_STATUS_MASTER_ENABLE_Pos      (0UL)                     /*!< DMA STATUS: MASTER_ENABLE (Bit 0)                     */
#define DMA_STATUS_MASTER_ENABLE_Msk      (0x1UL)                   /*!< DMA STATUS: MASTER_ENABLE (Bitfield-Mask: 0x01)       */
/* ===================================================  WAITONREQ_STATUS  ==================================================== */
#define DMA_WAITONREQ_STATUS_WAITONREQ_STATUS_Pos (0UL)             /*!< DMA WAITONREQ_STATUS: WAITONREQ_STATUS (Bit 0)        */
#define DMA_WAITONREQ_STATUS_WAITONREQ_STATUS_Msk (0x3fffUL)        /*!< DMA WAITONREQ_STATUS: WAITONREQ_STATUS (Bitfield-Mask: 0x3fff) */


/* =========================================================================================================================== */
/* ================                                          GPT12E                                           ================ */
/* =========================================================================================================================== */

/* ========================================================  CAPREL  ========================================================= */
#define GPT12E_CAPREL_CAPREL_Pos          (0UL)                     /*!< GPT12E CAPREL: CAPREL (Bit 0)                         */
#define GPT12E_CAPREL_CAPREL_Msk          (0xffffUL)                /*!< GPT12E CAPREL: CAPREL (Bitfield-Mask: 0xffff)         */
/* ==========================================================  ID  =========================================================== */
#define GPT12E_ID_MOD_REV_Pos             (0UL)                     /*!< GPT12E ID: MOD_REV (Bit 0)                            */
#define GPT12E_ID_MOD_REV_Msk             (0xffUL)                  /*!< GPT12E ID: MOD_REV (Bitfield-Mask: 0xff)              */
#define GPT12E_ID_MOD_TYPE_Pos            (8UL)                     /*!< GPT12E ID: MOD_TYPE (Bit 8)                           */
#define GPT12E_ID_MOD_TYPE_Msk            (0xff00UL)                /*!< GPT12E ID: MOD_TYPE (Bitfield-Mask: 0xff)             */
/* =========================================================  PISEL  ========================================================= */
#define GPT12E_PISEL_IST2IN_Pos           (0UL)                     /*!< GPT12E PISEL: IST2IN (Bit 0)                          */
#define GPT12E_PISEL_IST2IN_Msk           (0x1UL)                   /*!< GPT12E PISEL: IST2IN (Bitfield-Mask: 0x01)            */
#define GPT12E_PISEL_IST2EUD_Pos          (1UL)                     /*!< GPT12E PISEL: IST2EUD (Bit 1)                         */
#define GPT12E_PISEL_IST2EUD_Msk          (0x2UL)                   /*!< GPT12E PISEL: IST2EUD (Bitfield-Mask: 0x01)           */
#define GPT12E_PISEL_IST3IN_Pos           (2UL)                     /*!< GPT12E PISEL: IST3IN (Bit 2)                          */
#define GPT12E_PISEL_IST3IN_Msk           (0xcUL)                   /*!< GPT12E PISEL: IST3IN (Bitfield-Mask: 0x03)            */
#define GPT12E_PISEL_IST3EUD_Pos          (4UL)                     /*!< GPT12E PISEL: IST3EUD (Bit 4)                         */
#define GPT12E_PISEL_IST3EUD_Msk          (0x30UL)                  /*!< GPT12E PISEL: IST3EUD (Bitfield-Mask: 0x03)           */
#define GPT12E_PISEL_IST4IN_Pos           (6UL)                     /*!< GPT12E PISEL: IST4IN (Bit 6)                          */
#define GPT12E_PISEL_IST4IN_Msk           (0xc0UL)                  /*!< GPT12E PISEL: IST4IN (Bitfield-Mask: 0x03)            */
#define GPT12E_PISEL_IST4EUD_Pos          (8UL)                     /*!< GPT12E PISEL: IST4EUD (Bit 8)                         */
#define GPT12E_PISEL_IST4EUD_Msk          (0x300UL)                 /*!< GPT12E PISEL: IST4EUD (Bitfield-Mask: 0x03)           */
#define GPT12E_PISEL_IST5IN_Pos           (10UL)                    /*!< GPT12E PISEL: IST5IN (Bit 10)                         */
#define GPT12E_PISEL_IST5IN_Msk           (0x400UL)                 /*!< GPT12E PISEL: IST5IN (Bitfield-Mask: 0x01)            */
#define GPT12E_PISEL_IST5EUD_Pos          (11UL)                    /*!< GPT12E PISEL: IST5EUD (Bit 11)                        */
#define GPT12E_PISEL_IST5EUD_Msk          (0x800UL)                 /*!< GPT12E PISEL: IST5EUD (Bitfield-Mask: 0x01)           */
#define GPT12E_PISEL_IST6IN_Pos           (12UL)                    /*!< GPT12E PISEL: IST6IN (Bit 12)                         */
#define GPT12E_PISEL_IST6IN_Msk           (0x1000UL)                /*!< GPT12E PISEL: IST6IN (Bitfield-Mask: 0x01)            */
#define GPT12E_PISEL_IST6EUD_Pos          (13UL)                    /*!< GPT12E PISEL: IST6EUD (Bit 13)                        */
#define GPT12E_PISEL_IST6EUD_Msk          (0x2000UL)                /*!< GPT12E PISEL: IST6EUD (Bitfield-Mask: 0x01)           */
#define GPT12E_PISEL_ISCAPIN_Pos          (14UL)                    /*!< GPT12E PISEL: ISCAPIN (Bit 14)                        */
#define GPT12E_PISEL_ISCAPIN_Msk          (0xc000UL)                /*!< GPT12E PISEL: ISCAPIN (Bitfield-Mask: 0x03)           */
/* ==========================================================  T2  =========================================================== */
#define GPT12E_T2_T2_Pos                  (0UL)                     /*!< GPT12E T2: T2 (Bit 0)                                 */
#define GPT12E_T2_T2_Msk                  (0xffffUL)                /*!< GPT12E T2: T2 (Bitfield-Mask: 0xffff)                 */
/* =========================================================  T2CON  ========================================================= */
#define GPT12E_T2CON_T2I_Pos              (0UL)                     /*!< GPT12E T2CON: T2I (Bit 0)                             */
#define GPT12E_T2CON_T2I_Msk              (0x7UL)                   /*!< GPT12E T2CON: T2I (Bitfield-Mask: 0x07)               */
#define GPT12E_T2CON_T2M_Pos              (3UL)                     /*!< GPT12E T2CON: T2M (Bit 3)                             */
#define GPT12E_T2CON_T2M_Msk              (0x38UL)                  /*!< GPT12E T2CON: T2M (Bitfield-Mask: 0x07)               */
#define GPT12E_T2CON_T2R_Pos              (6UL)                     /*!< GPT12E T2CON: T2R (Bit 6)                             */
#define GPT12E_T2CON_T2R_Msk              (0x40UL)                  /*!< GPT12E T2CON: T2R (Bitfield-Mask: 0x01)               */
#define GPT12E_T2CON_T2UD_Pos             (7UL)                     /*!< GPT12E T2CON: T2UD (Bit 7)                            */
#define GPT12E_T2CON_T2UD_Msk             (0x80UL)                  /*!< GPT12E T2CON: T2UD (Bitfield-Mask: 0x01)              */
#define GPT12E_T2CON_T2UDE_Pos            (8UL)                     /*!< GPT12E T2CON: T2UDE (Bit 8)                           */
#define GPT12E_T2CON_T2UDE_Msk            (0x100UL)                 /*!< GPT12E T2CON: T2UDE (Bitfield-Mask: 0x01)             */
#define GPT12E_T2CON_T2RC_Pos             (9UL)                     /*!< GPT12E T2CON: T2RC (Bit 9)                            */
#define GPT12E_T2CON_T2RC_Msk             (0x200UL)                 /*!< GPT12E T2CON: T2RC (Bitfield-Mask: 0x01)              */
#define GPT12E_T2CON_T2IRDIS_Pos          (12UL)                    /*!< GPT12E T2CON: T2IRDIS (Bit 12)                        */
#define GPT12E_T2CON_T2IRDIS_Msk          (0x1000UL)                /*!< GPT12E T2CON: T2IRDIS (Bitfield-Mask: 0x01)           */
#define GPT12E_T2CON_T2EDGE_Pos           (13UL)                    /*!< GPT12E T2CON: T2EDGE (Bit 13)                         */
#define GPT12E_T2CON_T2EDGE_Msk           (0x2000UL)                /*!< GPT12E T2CON: T2EDGE (Bitfield-Mask: 0x01)            */
#define GPT12E_T2CON_T2CHDIR_Pos          (14UL)                    /*!< GPT12E T2CON: T2CHDIR (Bit 14)                        */
#define GPT12E_T2CON_T2CHDIR_Msk          (0x4000UL)                /*!< GPT12E T2CON: T2CHDIR (Bitfield-Mask: 0x01)           */
#define GPT12E_T2CON_T2RDIR_Pos           (15UL)                    /*!< GPT12E T2CON: T2RDIR (Bit 15)                         */
#define GPT12E_T2CON_T2RDIR_Msk           (0x8000UL)                /*!< GPT12E T2CON: T2RDIR (Bitfield-Mask: 0x01)            */
/* ==========================================================  T3  =========================================================== */
#define GPT12E_T3_T3_Pos                  (0UL)                     /*!< GPT12E T3: T3 (Bit 0)                                 */
#define GPT12E_T3_T3_Msk                  (0xffffUL)                /*!< GPT12E T3: T3 (Bitfield-Mask: 0xffff)                 */
/* =========================================================  T3CON  ========================================================= */
#define GPT12E_T3CON_T3I_Pos              (0UL)                     /*!< GPT12E T3CON: T3I (Bit 0)                             */
#define GPT12E_T3CON_T3I_Msk              (0x7UL)                   /*!< GPT12E T3CON: T3I (Bitfield-Mask: 0x07)               */
#define GPT12E_T3CON_T3M_Pos              (3UL)                     /*!< GPT12E T3CON: T3M (Bit 3)                             */
#define GPT12E_T3CON_T3M_Msk              (0x38UL)                  /*!< GPT12E T3CON: T3M (Bitfield-Mask: 0x07)               */
#define GPT12E_T3CON_T3R_Pos              (6UL)                     /*!< GPT12E T3CON: T3R (Bit 6)                             */
#define GPT12E_T3CON_T3R_Msk              (0x40UL)                  /*!< GPT12E T3CON: T3R (Bitfield-Mask: 0x01)               */
#define GPT12E_T3CON_T3UD_Pos             (7UL)                     /*!< GPT12E T3CON: T3UD (Bit 7)                            */
#define GPT12E_T3CON_T3UD_Msk             (0x80UL)                  /*!< GPT12E T3CON: T3UD (Bitfield-Mask: 0x01)              */
#define GPT12E_T3CON_T3UDE_Pos            (8UL)                     /*!< GPT12E T3CON: T3UDE (Bit 8)                           */
#define GPT12E_T3CON_T3UDE_Msk            (0x100UL)                 /*!< GPT12E T3CON: T3UDE (Bitfield-Mask: 0x01)             */
#define GPT12E_T3CON_T3OE_Pos             (9UL)                     /*!< GPT12E T3CON: T3OE (Bit 9)                            */
#define GPT12E_T3CON_T3OE_Msk             (0x200UL)                 /*!< GPT12E T3CON: T3OE (Bitfield-Mask: 0x01)              */
#define GPT12E_T3CON_T3OTL_Pos            (10UL)                    /*!< GPT12E T3CON: T3OTL (Bit 10)                          */
#define GPT12E_T3CON_T3OTL_Msk            (0x400UL)                 /*!< GPT12E T3CON: T3OTL (Bitfield-Mask: 0x01)             */
#define GPT12E_T3CON_BPS1_Pos             (11UL)                    /*!< GPT12E T3CON: BPS1 (Bit 11)                           */
#define GPT12E_T3CON_BPS1_Msk             (0x1800UL)                /*!< GPT12E T3CON: BPS1 (Bitfield-Mask: 0x03)              */
#define GPT12E_T3CON_T3EDGE_Pos           (13UL)                    /*!< GPT12E T3CON: T3EDGE (Bit 13)                         */
#define GPT12E_T3CON_T3EDGE_Msk           (0x2000UL)                /*!< GPT12E T3CON: T3EDGE (Bitfield-Mask: 0x01)            */
#define GPT12E_T3CON_T3CHDIR_Pos          (14UL)                    /*!< GPT12E T3CON: T3CHDIR (Bit 14)                        */
#define GPT12E_T3CON_T3CHDIR_Msk          (0x4000UL)                /*!< GPT12E T3CON: T3CHDIR (Bitfield-Mask: 0x01)           */
#define GPT12E_T3CON_T3RDIR_Pos           (15UL)                    /*!< GPT12E T3CON: T3RDIR (Bit 15)                         */
#define GPT12E_T3CON_T3RDIR_Msk           (0x8000UL)                /*!< GPT12E T3CON: T3RDIR (Bitfield-Mask: 0x01)            */
/* ==========================================================  T4  =========================================================== */
#define GPT12E_T4_T4_Pos                  (0UL)                     /*!< GPT12E T4: T4 (Bit 0)                                 */
#define GPT12E_T4_T4_Msk                  (0xffffUL)                /*!< GPT12E T4: T4 (Bitfield-Mask: 0xffff)                 */
/* =========================================================  T4CON  ========================================================= */
#define GPT12E_T4CON_T4I_Pos              (0UL)                     /*!< GPT12E T4CON: T4I (Bit 0)                             */
#define GPT12E_T4CON_T4I_Msk              (0x7UL)                   /*!< GPT12E T4CON: T4I (Bitfield-Mask: 0x07)               */
#define GPT12E_T4CON_T4M_Pos              (3UL)                     /*!< GPT12E T4CON: T4M (Bit 3)                             */
#define GPT12E_T4CON_T4M_Msk              (0x38UL)                  /*!< GPT12E T4CON: T4M (Bitfield-Mask: 0x07)               */
#define GPT12E_T4CON_T4R_Pos              (6UL)                     /*!< GPT12E T4CON: T4R (Bit 6)                             */
#define GPT12E_T4CON_T4R_Msk              (0x40UL)                  /*!< GPT12E T4CON: T4R (Bitfield-Mask: 0x01)               */
#define GPT12E_T4CON_T4UD_Pos             (7UL)                     /*!< GPT12E T4CON: T4UD (Bit 7)                            */
#define GPT12E_T4CON_T4UD_Msk             (0x80UL)                  /*!< GPT12E T4CON: T4UD (Bitfield-Mask: 0x01)              */
#define GPT12E_T4CON_T4UDE_Pos            (8UL)                     /*!< GPT12E T4CON: T4UDE (Bit 8)                           */
#define GPT12E_T4CON_T4UDE_Msk            (0x100UL)                 /*!< GPT12E T4CON: T4UDE (Bitfield-Mask: 0x01)             */
#define GPT12E_T4CON_T4RC_Pos             (9UL)                     /*!< GPT12E T4CON: T4RC (Bit 9)                            */
#define GPT12E_T4CON_T4RC_Msk             (0x200UL)                 /*!< GPT12E T4CON: T4RC (Bitfield-Mask: 0x01)              */
#define GPT12E_T4CON_CLRT2EN_Pos          (10UL)                    /*!< GPT12E T4CON: CLRT2EN (Bit 10)                        */
#define GPT12E_T4CON_CLRT2EN_Msk          (0x400UL)                 /*!< GPT12E T4CON: CLRT2EN (Bitfield-Mask: 0x01)           */
#define GPT12E_T4CON_CLRT3EN_Pos          (11UL)                    /*!< GPT12E T4CON: CLRT3EN (Bit 11)                        */
#define GPT12E_T4CON_CLRT3EN_Msk          (0x800UL)                 /*!< GPT12E T4CON: CLRT3EN (Bitfield-Mask: 0x01)           */
#define GPT12E_T4CON_T4IRDIS_Pos          (12UL)                    /*!< GPT12E T4CON: T4IRDIS (Bit 12)                        */
#define GPT12E_T4CON_T4IRDIS_Msk          (0x1000UL)                /*!< GPT12E T4CON: T4IRDIS (Bitfield-Mask: 0x01)           */
#define GPT12E_T4CON_T4EDGE_Pos           (13UL)                    /*!< GPT12E T4CON: T4EDGE (Bit 13)                         */
#define GPT12E_T4CON_T4EDGE_Msk           (0x2000UL)                /*!< GPT12E T4CON: T4EDGE (Bitfield-Mask: 0x01)            */
#define GPT12E_T4CON_T4CHDIR_Pos          (14UL)                    /*!< GPT12E T4CON: T4CHDIR (Bit 14)                        */
#define GPT12E_T4CON_T4CHDIR_Msk          (0x4000UL)                /*!< GPT12E T4CON: T4CHDIR (Bitfield-Mask: 0x01)           */
#define GPT12E_T4CON_T4RDIR_Pos           (15UL)                    /*!< GPT12E T4CON: T4RDIR (Bit 15)                         */
#define GPT12E_T4CON_T4RDIR_Msk           (0x8000UL)                /*!< GPT12E T4CON: T4RDIR (Bitfield-Mask: 0x01)            */
/* ==========================================================  T5  =========================================================== */
#define GPT12E_T5_T5_Pos                  (0UL)                     /*!< GPT12E T5: T5 (Bit 0)                                 */
#define GPT12E_T5_T5_Msk                  (0xffffUL)                /*!< GPT12E T5: T5 (Bitfield-Mask: 0xffff)                 */
/* =========================================================  T5CON  ========================================================= */
#define GPT12E_T5CON_T5I_Pos              (0UL)                     /*!< GPT12E T5CON: T5I (Bit 0)                             */
#define GPT12E_T5CON_T5I_Msk              (0x7UL)                   /*!< GPT12E T5CON: T5I (Bitfield-Mask: 0x07)               */
#define GPT12E_T5CON_T5M_Pos              (3UL)                     /*!< GPT12E T5CON: T5M (Bit 3)                             */
#define GPT12E_T5CON_T5M_Msk              (0x18UL)                  /*!< GPT12E T5CON: T5M (Bitfield-Mask: 0x03)               */
#define GPT12E_T5CON_T5R_Pos              (6UL)                     /*!< GPT12E T5CON: T5R (Bit 6)                             */
#define GPT12E_T5CON_T5R_Msk              (0x40UL)                  /*!< GPT12E T5CON: T5R (Bitfield-Mask: 0x01)               */
#define GPT12E_T5CON_T5UD_Pos             (7UL)                     /*!< GPT12E T5CON: T5UD (Bit 7)                            */
#define GPT12E_T5CON_T5UD_Msk             (0x80UL)                  /*!< GPT12E T5CON: T5UD (Bitfield-Mask: 0x01)              */
#define GPT12E_T5CON_T5UDE_Pos            (8UL)                     /*!< GPT12E T5CON: T5UDE (Bit 8)                           */
#define GPT12E_T5CON_T5UDE_Msk            (0x100UL)                 /*!< GPT12E T5CON: T5UDE (Bitfield-Mask: 0x01)             */
#define GPT12E_T5CON_T5RC_Pos             (9UL)                     /*!< GPT12E T5CON: T5RC (Bit 9)                            */
#define GPT12E_T5CON_T5RC_Msk             (0x200UL)                 /*!< GPT12E T5CON: T5RC (Bitfield-Mask: 0x01)              */
#define GPT12E_T5CON_CT3_Pos              (10UL)                    /*!< GPT12E T5CON: CT3 (Bit 10)                            */
#define GPT12E_T5CON_CT3_Msk              (0x400UL)                 /*!< GPT12E T5CON: CT3 (Bitfield-Mask: 0x01)               */
#define GPT12E_T5CON_CI_Pos               (12UL)                    /*!< GPT12E T5CON: CI (Bit 12)                             */
#define GPT12E_T5CON_CI_Msk               (0x3000UL)                /*!< GPT12E T5CON: CI (Bitfield-Mask: 0x03)                */
#define GPT12E_T5CON_T5CLR_Pos            (14UL)                    /*!< GPT12E T5CON: T5CLR (Bit 14)                          */
#define GPT12E_T5CON_T5CLR_Msk            (0x4000UL)                /*!< GPT12E T5CON: T5CLR (Bitfield-Mask: 0x01)             */
#define GPT12E_T5CON_T5SC_Pos             (15UL)                    /*!< GPT12E T5CON: T5SC (Bit 15)                           */
#define GPT12E_T5CON_T5SC_Msk             (0x8000UL)                /*!< GPT12E T5CON: T5SC (Bitfield-Mask: 0x01)              */
/* ==========================================================  T6  =========================================================== */
#define GPT12E_T6_T6_Pos                  (0UL)                     /*!< GPT12E T6: T6 (Bit 0)                                 */
#define GPT12E_T6_T6_Msk                  (0xffffUL)                /*!< GPT12E T6: T6 (Bitfield-Mask: 0xffff)                 */
/* =========================================================  T6CON  ========================================================= */
#define GPT12E_T6CON_T6I_Pos              (0UL)                     /*!< GPT12E T6CON: T6I (Bit 0)                             */
#define GPT12E_T6CON_T6I_Msk              (0x7UL)                   /*!< GPT12E T6CON: T6I (Bitfield-Mask: 0x07)               */
#define GPT12E_T6CON_T6M_Pos              (3UL)                     /*!< GPT12E T6CON: T6M (Bit 3)                             */
#define GPT12E_T6CON_T6M_Msk              (0x38UL)                  /*!< GPT12E T6CON: T6M (Bitfield-Mask: 0x07)               */
#define GPT12E_T6CON_T6R_Pos              (6UL)                     /*!< GPT12E T6CON: T6R (Bit 6)                             */
#define GPT12E_T6CON_T6R_Msk              (0x40UL)                  /*!< GPT12E T6CON: T6R (Bitfield-Mask: 0x01)               */
#define GPT12E_T6CON_T6UD_Pos             (7UL)                     /*!< GPT12E T6CON: T6UD (Bit 7)                            */
#define GPT12E_T6CON_T6UD_Msk             (0x80UL)                  /*!< GPT12E T6CON: T6UD (Bitfield-Mask: 0x01)              */
#define GPT12E_T6CON_T6UDE_Pos            (8UL)                     /*!< GPT12E T6CON: T6UDE (Bit 8)                           */
#define GPT12E_T6CON_T6UDE_Msk            (0x100UL)                 /*!< GPT12E T6CON: T6UDE (Bitfield-Mask: 0x01)             */
#define GPT12E_T6CON_T6OE_Pos             (9UL)                     /*!< GPT12E T6CON: T6OE (Bit 9)                            */
#define GPT12E_T6CON_T6OE_Msk             (0x200UL)                 /*!< GPT12E T6CON: T6OE (Bitfield-Mask: 0x01)              */
#define GPT12E_T6CON_T6OTL_Pos            (10UL)                    /*!< GPT12E T6CON: T6OTL (Bit 10)                          */
#define GPT12E_T6CON_T6OTL_Msk            (0x400UL)                 /*!< GPT12E T6CON: T6OTL (Bitfield-Mask: 0x01)             */
#define GPT12E_T6CON_BPS2_Pos             (11UL)                    /*!< GPT12E T6CON: BPS2 (Bit 11)                           */
#define GPT12E_T6CON_BPS2_Msk             (0x1800UL)                /*!< GPT12E T6CON: BPS2 (Bitfield-Mask: 0x03)              */
#define GPT12E_T6CON_T6CLR_Pos            (14UL)                    /*!< GPT12E T6CON: T6CLR (Bit 14)                          */
#define GPT12E_T6CON_T6CLR_Msk            (0x4000UL)                /*!< GPT12E T6CON: T6CLR (Bitfield-Mask: 0x01)             */
#define GPT12E_T6CON_T6SR_Pos             (15UL)                    /*!< GPT12E T6CON: T6SR (Bit 15)                           */
#define GPT12E_T6CON_T6SR_Msk             (0x8000UL)                /*!< GPT12E T6CON: T6SR (Bitfield-Mask: 0x01)              */


/* =========================================================================================================================== */
/* ================                                            LIN                                            ================ */
/* =========================================================================================================================== */

/* =======================================================  CTRL_STS  ======================================================== */
#define LIN_CTRL_STS_M_SM_ERR_CLR_Pos     (24UL)                    /*!< LIN CTRL_STS: M_SM_ERR_CLR (Bit 24)                   */
#define LIN_CTRL_STS_M_SM_ERR_CLR_Msk     (0x1000000UL)             /*!< LIN CTRL_STS: M_SM_ERR_CLR (Bitfield-Mask: 0x01)      */
#define LIN_CTRL_STS_HV_MODE_Pos          (21UL)                    /*!< LIN CTRL_STS: HV_MODE (Bit 21)                        */
#define LIN_CTRL_STS_HV_MODE_Msk          (0x200000UL)              /*!< LIN CTRL_STS: HV_MODE (Bitfield-Mask: 0x01)           */
#define LIN_CTRL_STS_MODE_FB_Pos          (16UL)                    /*!< LIN CTRL_STS: MODE_FB (Bit 16)                        */
#define LIN_CTRL_STS_MODE_FB_Msk          (0x70000UL)               /*!< LIN CTRL_STS: MODE_FB (Bitfield-Mask: 0x07)           */
#define LIN_CTRL_STS_FB_SM3_Pos           (15UL)                    /*!< LIN CTRL_STS: FB_SM3 (Bit 15)                         */
#define LIN_CTRL_STS_FB_SM3_Msk           (0x8000UL)                /*!< LIN CTRL_STS: FB_SM3 (Bitfield-Mask: 0x01)            */
#define LIN_CTRL_STS_FB_SM2_Pos           (14UL)                    /*!< LIN CTRL_STS: FB_SM2 (Bit 14)                         */
#define LIN_CTRL_STS_FB_SM2_Msk           (0x4000UL)                /*!< LIN CTRL_STS: FB_SM2 (Bitfield-Mask: 0x01)            */
#define LIN_CTRL_STS_FB_SM1_Pos           (13UL)                    /*!< LIN CTRL_STS: FB_SM1 (Bit 13)                         */
#define LIN_CTRL_STS_FB_SM1_Msk           (0x2000UL)                /*!< LIN CTRL_STS: FB_SM1 (Bitfield-Mask: 0x01)            */
#define LIN_CTRL_STS_SM_Pos               (11UL)                    /*!< LIN CTRL_STS: SM (Bit 11)                             */
#define LIN_CTRL_STS_SM_Msk               (0x1800UL)                /*!< LIN CTRL_STS: SM (Bitfield-Mask: 0x03)                */
#define LIN_CTRL_STS_RXD_Pos              (10UL)                    /*!< LIN CTRL_STS: RXD (Bit 10)                            */
#define LIN_CTRL_STS_RXD_Msk              (0x400UL)                 /*!< LIN CTRL_STS: RXD (Bitfield-Mask: 0x01)               */
#define LIN_CTRL_STS_TXD_Pos              (9UL)                     /*!< LIN CTRL_STS: TXD (Bit 9)                             */
#define LIN_CTRL_STS_TXD_Msk              (0x200UL)                 /*!< LIN CTRL_STS: TXD (Bitfield-Mask: 0x01)               */
#define LIN_CTRL_STS_TXD_TMOUT_STS_Pos    (6UL)                     /*!< LIN CTRL_STS: TXD_TMOUT_STS (Bit 6)                   */
#define LIN_CTRL_STS_TXD_TMOUT_STS_Msk    (0x40UL)                  /*!< LIN CTRL_STS: TXD_TMOUT_STS (Bitfield-Mask: 0x01)     */
#define LIN_CTRL_STS_OC_STS_Pos           (5UL)                     /*!< LIN CTRL_STS: OC_STS (Bit 5)                          */
#define LIN_CTRL_STS_OC_STS_Msk           (0x20UL)                  /*!< LIN CTRL_STS: OC_STS (Bitfield-Mask: 0x01)            */
#define LIN_CTRL_STS_OT_STS_Pos           (4UL)                     /*!< LIN CTRL_STS: OT_STS (Bit 4)                          */
#define LIN_CTRL_STS_OT_STS_Msk           (0x10UL)                  /*!< LIN CTRL_STS: OT_STS (Bitfield-Mask: 0x01)            */
#define LIN_CTRL_STS_M_SM_ERR_Pos         (3UL)                     /*!< LIN CTRL_STS: M_SM_ERR (Bit 3)                        */
#define LIN_CTRL_STS_M_SM_ERR_Msk         (0x8UL)                   /*!< LIN CTRL_STS: M_SM_ERR (Bitfield-Mask: 0x01)          */
#define LIN_CTRL_STS_MODE_Pos             (1UL)                     /*!< LIN CTRL_STS: MODE (Bit 1)                            */
#define LIN_CTRL_STS_MODE_Msk             (0x6UL)                   /*!< LIN CTRL_STS: MODE (Bitfield-Mask: 0x03)              */


/* =========================================================================================================================== */
/* ================                                            MF                                             ================ */
/* =========================================================================================================================== */

/* ====================================================  BEMFC_CTRL_STS  ===================================================== */
#define MF_BEMFC_CTRL_STS_PHW_ZC_STS_Pos   (18UL)                   /*!< MF BEMFC_CTRL_STS: PHW_ZC_STS (Bit 18)                */
#define MF_BEMFC_CTRL_STS_PHW_ZC_STS_Msk   (0x40000UL)              /*!< MF BEMFC_CTRL_STS: PHW_ZC_STS (Bitfield-Mask: 0x01)   */
#define MF_BEMFC_CTRL_STS_PHV_ZC_STS_Pos   (17UL)                   /*!< MF BEMFC_CTRL_STS: PHV_ZC_STS (Bit 17)                */
#define MF_BEMFC_CTRL_STS_PHV_ZC_STS_Msk   (0x20000UL)              /*!< MF BEMFC_CTRL_STS: PHV_ZC_STS (Bitfield-Mask: 0x01)   */
#define MF_BEMFC_CTRL_STS_PHU_ZC_STS_Pos   (16UL)                   /*!< MF BEMFC_CTRL_STS: PHU_ZC_STS (Bit 16)                */
#define MF_BEMFC_CTRL_STS_PHU_ZC_STS_Msk   (0x10000UL)              /*!< MF BEMFC_CTRL_STS: PHU_ZC_STS (Bitfield-Mask: 0x01)   */
#define MF_BEMFC_CTRL_STS_CCPOS_INSEL_Pos  (12UL)                   /*!< MF BEMFC_CTRL_STS: CCPOS_INSEL (Bit 12)               */
#define MF_BEMFC_CTRL_STS_CCPOS_INSEL_Msk  (0x1000UL)               /*!< MF BEMFC_CTRL_STS: CCPOS_INSEL (Bitfield-Mask: 0x01)  */
#define MF_BEMFC_CTRL_STS_PHWCOMP_ON_Pos   (10UL)                   /*!< MF BEMFC_CTRL_STS: PHWCOMP_ON (Bit 10)                */
#define MF_BEMFC_CTRL_STS_PHWCOMP_ON_Msk   (0x400UL)                /*!< MF BEMFC_CTRL_STS: PHWCOMP_ON (Bitfield-Mask: 0x01)   */
#define MF_BEMFC_CTRL_STS_PHVCOMP_ON_Pos   (9UL)                    /*!< MF BEMFC_CTRL_STS: PHVCOMP_ON (Bit 9)                 */
#define MF_BEMFC_CTRL_STS_PHVCOMP_ON_Msk   (0x200UL)                /*!< MF BEMFC_CTRL_STS: PHVCOMP_ON (Bitfield-Mask: 0x01)   */
#define MF_BEMFC_CTRL_STS_PHUCOMP_ON_Pos   (8UL)                    /*!< MF BEMFC_CTRL_STS: PHUCOMP_ON (Bit 8)                 */
#define MF_BEMFC_CTRL_STS_PHUCOMP_ON_Msk   (0x100UL)                /*!< MF BEMFC_CTRL_STS: PHUCOMP_ON (Bitfield-Mask: 0x01)   */
#define MF_BEMFC_CTRL_STS_GPT12CAPINSW_Pos (5UL)                    /*!< MF BEMFC_CTRL_STS: GPT12CAPINSW (Bit 5)               */
#define MF_BEMFC_CTRL_STS_GPT12CAPINSW_Msk (0x20UL)                 /*!< MF BEMFC_CTRL_STS: GPT12CAPINSW (Bitfield-Mask: 0x01) */
#define MF_BEMFC_CTRL_STS_FILTBYPS_Pos     (4UL)                    /*!< MF BEMFC_CTRL_STS: FILTBYPS (Bit 4)                   */
#define MF_BEMFC_CTRL_STS_FILTBYPS_Msk     (0x10UL)                 /*!< MF BEMFC_CTRL_STS: FILTBYPS (Bitfield-Mask: 0x01)     */
#define MF_BEMFC_CTRL_STS_DEMGFILTDIS_Pos  (3UL)                    /*!< MF BEMFC_CTRL_STS: DEMGFILTDIS (Bit 3)                */
#define MF_BEMFC_CTRL_STS_DEMGFILTDIS_Msk  (0x8UL)                  /*!< MF BEMFC_CTRL_STS: DEMGFILTDIS (Bitfield-Mask: 0x01)  */
#define MF_BEMFC_CTRL_STS_PHWCOMP_EN_Pos   (2UL)                    /*!< MF BEMFC_CTRL_STS: PHWCOMP_EN (Bit 2)                 */
#define MF_BEMFC_CTRL_STS_PHWCOMP_EN_Msk   (0x4UL)                  /*!< MF BEMFC_CTRL_STS: PHWCOMP_EN (Bitfield-Mask: 0x01)   */
#define MF_BEMFC_CTRL_STS_PHVCOMP_EN_Pos   (1UL)                    /*!< MF BEMFC_CTRL_STS: PHVCOMP_EN (Bit 1)                 */
#define MF_BEMFC_CTRL_STS_PHVCOMP_EN_Msk   (0x2UL)                  /*!< MF BEMFC_CTRL_STS: PHVCOMP_EN (Bitfield-Mask: 0x01)   */
#define MF_BEMFC_CTRL_STS_PHUCOMP_EN_Pos   (0UL)                    /*!< MF BEMFC_CTRL_STS: PHUCOMP_EN (Bit 0)                 */
#define MF_BEMFC_CTRL_STS_PHUCOMP_EN_Msk   (0x1UL)                  /*!< MF BEMFC_CTRL_STS: PHUCOMP_EN (Bitfield-Mask: 0x01)   */
/* =======================================================  CSA_CTRL  ======================================================== */
#define MF_CSA_CTRL_VZERO_Pos             (8UL)                     /*!< MF CSA_CTRL: VZERO (Bit 8)                            */
#define MF_CSA_CTRL_VZERO_Msk             (0x100UL)                 /*!< MF CSA_CTRL: VZERO (Bitfield-Mask: 0x01)              */
#define MF_CSA_CTRL_GAIN_Pos              (1UL)                     /*!< MF CSA_CTRL: GAIN (Bit 1)                             */
#define MF_CSA_CTRL_GAIN_Msk              (0x6UL)                   /*!< MF CSA_CTRL: GAIN (Bitfield-Mask: 0x03)               */
#define MF_CSA_CTRL_EN_Pos                (0UL)                     /*!< MF CSA_CTRL: EN (Bit 0)                               */
#define MF_CSA_CTRL_EN_Msk                (0x1UL)                   /*!< MF CSA_CTRL: EN (Bitfield-Mask: 0x01)                 */
/* ====================================================  P2_ADCSEL_CTRL  ===================================================== */
#define MF_P2_ADCSEL_CTRL_ADC1_CH1_SEL_Pos (10UL)                   /*!< MF P2_ADCSEL_CTRL: ADC1_CH1_SEL (Bit 10)              */
#define MF_P2_ADCSEL_CTRL_ADC1_CH1_SEL_Msk (0x400UL)                /*!< MF P2_ADCSEL_CTRL: ADC1_CH1_SEL (Bitfield-Mask: 0x01) */
#define MF_P2_ADCSEL_CTRL_ADC3_INN_SEL_Pos (9UL)                    /*!< MF P2_ADCSEL_CTRL: ADC3_INN_SEL (Bit 9)               */
#define MF_P2_ADCSEL_CTRL_ADC3_INN_SEL_Msk (0x200UL)                /*!< MF P2_ADCSEL_CTRL: ADC3_INN_SEL (Bitfield-Mask: 0x01) */
#define MF_P2_ADCSEL_CTRL_ADC3_INP_SEL_Pos (8UL)                    /*!< MF P2_ADCSEL_CTRL: ADC3_INP_SEL (Bit 8)               */
#define MF_P2_ADCSEL_CTRL_ADC3_INP_SEL_Msk (0x100UL)                /*!< MF P2_ADCSEL_CTRL: ADC3_INP_SEL (Bitfield-Mask: 0x01) */
#define MF_P2_ADCSEL_CTRL_P2_0_ADC_SEL_Pos (0UL)                    /*!< MF P2_ADCSEL_CTRL: P2_0_ADC_SEL (Bit 0)               */
#define MF_P2_ADCSEL_CTRL_P2_0_ADC_SEL_Msk (0x1UL)                  /*!< MF P2_ADCSEL_CTRL: P2_0_ADC_SEL (Bitfield-Mask: 0x01) */
#define MF_P2_ADCSEL_CTRL_P2_2_ADC_SEL_Pos (1UL)                    /*!< MF P2_ADCSEL_CTRL: P2_2_ADC_SEL (Bit 1)               */
#define MF_P2_ADCSEL_CTRL_P2_2_ADC_SEL_Msk (0x2UL)                  /*!< MF P2_ADCSEL_CTRL: P2_2_ADC_SEL (Bitfield-Mask: 0x01) */
#define MF_P2_ADCSEL_CTRL_P2_3_ADC_SEL_Pos (2UL)                    /*!< MF P2_ADCSEL_CTRL: P2_3_ADC_SEL (Bit 2)               */
#define MF_P2_ADCSEL_CTRL_P2_3_ADC_SEL_Msk (0x4UL)                  /*!< MF P2_ADCSEL_CTRL: P2_3_ADC_SEL (Bitfield-Mask: 0x01) */
#define MF_P2_ADCSEL_CTRL_P2_4_ADC_SEL_Pos (3UL)                    /*!< MF P2_ADCSEL_CTRL: P2_4_ADC_SEL (Bit 3)               */
#define MF_P2_ADCSEL_CTRL_P2_4_ADC_SEL_Msk (0x8UL)                  /*!< MF P2_ADCSEL_CTRL: P2_4_ADC_SEL (Bitfield-Mask: 0x01) */
#define MF_P2_ADCSEL_CTRL_P2_5_ADC_SEL_Pos (4UL)                    /*!< MF P2_ADCSEL_CTRL: P2_5_ADC_SEL (Bit 4)               */
#define MF_P2_ADCSEL_CTRL_P2_5_ADC_SEL_Msk (0x10UL)                 /*!< MF P2_ADCSEL_CTRL: P2_5_ADC_SEL (Bitfield-Mask: 0x01) */
/* =======================================================  REF1_STS  ======================================================== */
#define MF_REF1_STS_REFBG_UPTHWARN_STS_Pos (5UL)                    /*!< MF REF1_STS: REFBG_UPTHWARN_STS (Bit 5)               */
#define MF_REF1_STS_REFBG_UPTHWARN_STS_Msk (0x20UL)                 /*!< MF REF1_STS: REFBG_UPTHWARN_STS (Bitfield-Mask: 0x01) */
#define MF_REF1_STS_REFBG_LOTHWARN_STS_Pos (4UL)                    /*!< MF REF1_STS: REFBG_LOTHWARN_STS (Bit 4)               */
#define MF_REF1_STS_REFBG_LOTHWARN_STS_Msk (0x10UL)                 /*!< MF REF1_STS: REFBG_LOTHWARN_STS (Bitfield-Mask: 0x01) */
/* =======================================================  REF2_CTRL  ======================================================= */
#define MF_REF2_CTRL_VREF5V_OV_STS_Pos    (3UL)                     /*!< MF REF2_CTRL: VREF5V_OV_STS (Bit 3)                   */
#define MF_REF2_CTRL_VREF5V_OV_STS_Msk    (0x8UL)                   /*!< MF REF2_CTRL: VREF5V_OV_STS (Bitfield-Mask: 0x01)     */
#define MF_REF2_CTRL_VREF5V_UV_STS_Pos    (2UL)                     /*!< MF REF2_CTRL: VREF5V_UV_STS (Bit 2)                   */
#define MF_REF2_CTRL_VREF5V_UV_STS_Msk    (0x4UL)                   /*!< MF REF2_CTRL: VREF5V_UV_STS (Bitfield-Mask: 0x01)     */
#define MF_REF2_CTRL_VREF5V_OVL_STS_Pos   (1UL)                     /*!< MF REF2_CTRL: VREF5V_OVL_STS (Bit 1)                  */
#define MF_REF2_CTRL_VREF5V_OVL_STS_Msk   (0x2UL)                   /*!< MF REF2_CTRL: VREF5V_OVL_STS (Bitfield-Mask: 0x01)    */
#define MF_REF2_CTRL_VREF5V_PD_N_Pos      (0UL)                     /*!< MF REF2_CTRL: VREF5V_PD_N (Bit 0)                     */
#define MF_REF2_CTRL_VREF5V_PD_N_Msk      (0x1UL)                   /*!< MF REF2_CTRL: VREF5V_PD_N (Bitfield-Mask: 0x01)       */
/* ====================================================  TEMPSENSE_CTRL  ===================================================== */
#define MF_TEMPSENSE_CTRL_SYS_OT_STS_Pos  (7UL)                     /*!< MF TEMPSENSE_CTRL: SYS_OT_STS (Bit 7)                 */
#define MF_TEMPSENSE_CTRL_SYS_OT_STS_Msk  (0x80UL)                  /*!< MF TEMPSENSE_CTRL: SYS_OT_STS (Bitfield-Mask: 0x01)   */
#define MF_TEMPSENSE_CTRL_SYS_OTWARN_STS_Pos (6UL)                  /*!< MF TEMPSENSE_CTRL: SYS_OTWARN_STS (Bit 6)             */
#define MF_TEMPSENSE_CTRL_SYS_OTWARN_STS_Msk (0x40UL)               /*!< MF TEMPSENSE_CTRL: SYS_OTWARN_STS (Bitfield-Mask: 0x01) */
#define MF_TEMPSENSE_CTRL_PMU_OT_STS_Pos  (5UL)                     /*!< MF TEMPSENSE_CTRL: PMU_OT_STS (Bit 5)                 */
#define MF_TEMPSENSE_CTRL_PMU_OT_STS_Msk  (0x20UL)                  /*!< MF TEMPSENSE_CTRL: PMU_OT_STS (Bitfield-Mask: 0x01)   */
#define MF_TEMPSENSE_CTRL_PMU_OTWARN_STS_Pos (4UL)                  /*!< MF TEMPSENSE_CTRL: PMU_OTWARN_STS (Bit 4)             */
#define MF_TEMPSENSE_CTRL_PMU_OTWARN_STS_Msk (0x10UL)               /*!< MF TEMPSENSE_CTRL: PMU_OTWARN_STS (Bitfield-Mask: 0x01) */
/* ======================================================  TRIM_BEMFx  ======================================================= */
#define MF_TRIM_BEMFx_BEMF_TFILT_SEL_Pos  (8UL)                     /*!< MF TRIM_BEMFx: BEMF_TFILT_SEL (Bit 8)                 */
#define MF_TRIM_BEMFx_BEMF_TFILT_SEL_Msk  (0x300UL)                 /*!< MF TRIM_BEMFx: BEMF_TFILT_SEL (Bitfield-Mask: 0x03)   */
#define MF_TRIM_BEMFx_BEMF_GPT_CAPIN_SEL_Pos (4UL)                  /*!< MF TRIM_BEMFx: BEMF_GPT_CAPIN_SEL (Bit 4)             */
#define MF_TRIM_BEMFx_BEMF_GPT_CAPIN_SEL_Msk (0x30UL)               /*!< MF TRIM_BEMFx: BEMF_GPT_CAPIN_SEL (Bitfield-Mask: 0x03) */
#define MF_TRIM_BEMFx_BEMF_BT_TFILT_SEL_Pos (0UL)                   /*!< MF TRIM_BEMFx: BEMF_BT_TFILT_SEL (Bit 0)              */
#define MF_TRIM_BEMFx_BEMF_BT_TFILT_SEL_Msk (0x7UL)                 /*!< MF TRIM_BEMFx: BEMF_BT_TFILT_SEL (Bitfield-Mask: 0x07) */
/* =====================================================  VMON_SEN_CTRL  ===================================================== */
#define MF_VMON_SEN_CTRL_VMON_SEN_SEL_INRANGE_Pos (5UL)             /*!< MF VMON_SEN_CTRL: VMON_SEN_SEL_INRANGE (Bit 5)        */
#define MF_VMON_SEN_CTRL_VMON_SEN_SEL_INRANGE_Msk (0x20UL)          /*!< MF VMON_SEN_CTRL: VMON_SEN_SEL_INRANGE (Bitfield-Mask: 0x01) */
#define MF_VMON_SEN_CTRL_VMON_SEN_HRESO_5V_Pos (4UL)                /*!< MF VMON_SEN_CTRL: VMON_SEN_HRESO_5V (Bit 4)           */
#define MF_VMON_SEN_CTRL_VMON_SEN_HRESO_5V_Msk (0x10UL)             /*!< MF VMON_SEN_CTRL: VMON_SEN_HRESO_5V (Bitfield-Mask: 0x01) */
#define MF_VMON_SEN_CTRL_VMON_SEN_PD_N_Pos (0UL)                    /*!< MF VMON_SEN_CTRL: VMON_SEN_PD_N (Bit 0)               */
#define MF_VMON_SEN_CTRL_VMON_SEN_PD_N_Msk (0x1UL)                  /*!< MF VMON_SEN_CTRL: VMON_SEN_PD_N (Bitfield-Mask: 0x01) */


/* =========================================================================================================================== */
/* ================                                            PMU                                            ================ */
/* =========================================================================================================================== */

/* ==================================================  CNF_CYC_SAMPLE_DEL  =================================================== */
#define PMU_CNF_CYC_SAMPLE_DEL_M03_Pos    (0UL)                     /*!< PMU CNF_CYC_SAMPLE_DEL: M03 (Bit 0)                   */
#define PMU_CNF_CYC_SAMPLE_DEL_M03_Msk    (0xfUL)                   /*!< PMU CNF_CYC_SAMPLE_DEL: M03 (Bitfield-Mask: 0x0f)     */
/* =====================================================  CNF_CYC_SENSE  ===================================================== */
#define PMU_CNF_CYC_SENSE_OSC_100kHz_EN_Pos (7UL)                   /*!< PMU CNF_CYC_SENSE: OSC_100kHz_EN (Bit 7)              */
#define PMU_CNF_CYC_SENSE_OSC_100kHz_EN_Msk (0x80UL)                /*!< PMU CNF_CYC_SENSE: OSC_100kHz_EN (Bitfield-Mask: 0x01) */
#define PMU_CNF_CYC_SENSE_E01_Pos         (4UL)                     /*!< PMU CNF_CYC_SENSE: E01 (Bit 4)                        */
#define PMU_CNF_CYC_SENSE_E01_Msk         (0x30UL)                  /*!< PMU CNF_CYC_SENSE: E01 (Bitfield-Mask: 0x03)          */
#define PMU_CNF_CYC_SENSE_M03_Pos         (0UL)                     /*!< PMU CNF_CYC_SENSE: M03 (Bit 0)                        */
#define PMU_CNF_CYC_SENSE_M03_Msk         (0xfUL)                   /*!< PMU CNF_CYC_SENSE: M03 (Bitfield-Mask: 0x0f)          */
/* =====================================================  CNF_CYC_WAKE  ====================================================== */
#define PMU_CNF_CYC_WAKE_E01_Pos          (4UL)                     /*!< PMU CNF_CYC_WAKE: E01 (Bit 4)                         */
#define PMU_CNF_CYC_WAKE_E01_Msk          (0x30UL)                  /*!< PMU CNF_CYC_WAKE: E01 (Bitfield-Mask: 0x03)           */
#define PMU_CNF_CYC_WAKE_M03_Pos          (0UL)                     /*!< PMU CNF_CYC_WAKE: M03 (Bit 0)                         */
#define PMU_CNF_CYC_WAKE_M03_Msk          (0xfUL)                   /*!< PMU CNF_CYC_WAKE: M03 (Bitfield-Mask: 0x0f)           */
/* ===================================================  CNF_PMU_SETTINGS  ==================================================== */
#define PMU_CNF_PMU_SETTINGS_EN_VDDEXT_OC_OFF_N_Pos (7UL)           /*!< PMU CNF_PMU_SETTINGS: EN_VDDEXT_OC_OFF_N (Bit 7)      */
#define PMU_CNF_PMU_SETTINGS_EN_VDDEXT_OC_OFF_N_Msk (0x80UL)        /*!< PMU CNF_PMU_SETTINGS: EN_VDDEXT_OC_OFF_N (Bitfield-Mask: 0x01) */
#define PMU_CNF_PMU_SETTINGS_CYC_SENSE_EN_Pos (3UL)                 /*!< PMU CNF_PMU_SETTINGS: CYC_SENSE_EN (Bit 3)            */
#define PMU_CNF_PMU_SETTINGS_CYC_SENSE_EN_Msk (0x8UL)               /*!< PMU CNF_PMU_SETTINGS: CYC_SENSE_EN (Bitfield-Mask: 0x01) */
#define PMU_CNF_PMU_SETTINGS_CYC_WAKE_EN_Pos (2UL)                  /*!< PMU CNF_PMU_SETTINGS: CYC_WAKE_EN (Bit 2)             */
#define PMU_CNF_PMU_SETTINGS_CYC_WAKE_EN_Msk (0x4UL)                /*!< PMU CNF_PMU_SETTINGS: CYC_WAKE_EN (Bitfield-Mask: 0x01) */
#define PMU_CNF_PMU_SETTINGS_EN_0V9_N_Pos (1UL)                     /*!< PMU CNF_PMU_SETTINGS: EN_0V9_N (Bit 1)                */
#define PMU_CNF_PMU_SETTINGS_EN_0V9_N_Msk (0x2UL)                   /*!< PMU CNF_PMU_SETTINGS: EN_0V9_N (Bitfield-Mask: 0x01)  */
#define PMU_CNF_PMU_SETTINGS_WAKE_W_RST_Pos (0UL)                   /*!< PMU CNF_PMU_SETTINGS: WAKE_W_RST (Bit 0)              */
#define PMU_CNF_PMU_SETTINGS_WAKE_W_RST_Msk (0x1UL)                 /*!< PMU CNF_PMU_SETTINGS: WAKE_W_RST (Bitfield-Mask: 0x01) */
/* ======================================================  CNF_RST_TFB  ====================================================== */
#define PMU_CNF_RST_TFB_RST_TFB_Pos       (0UL)                     /*!< PMU CNF_RST_TFB: RST_TFB (Bit 0)                      */
#define PMU_CNF_RST_TFB_RST_TFB_Msk       (0x3UL)                   /*!< PMU CNF_RST_TFB: RST_TFB (Bitfield-Mask: 0x03)        */
/* ====================================================  CNF_WAKE_FILTER  ==================================================== */
#define PMU_CNF_WAKE_FILTER_CNF_GPIO_FT_Pos (2UL)                   /*!< PMU CNF_WAKE_FILTER: CNF_GPIO_FT (Bit 2)              */
#define PMU_CNF_WAKE_FILTER_CNF_GPIO_FT_Msk (0xcUL)                 /*!< PMU CNF_WAKE_FILTER: CNF_GPIO_FT (Bitfield-Mask: 0x03) */
#define PMU_CNF_WAKE_FILTER_CNF_MON_FT_Pos (1UL)                    /*!< PMU CNF_WAKE_FILTER: CNF_MON_FT (Bit 1)               */
#define PMU_CNF_WAKE_FILTER_CNF_MON_FT_Msk (0x2UL)                  /*!< PMU CNF_WAKE_FILTER: CNF_MON_FT (Bitfield-Mask: 0x01) */
#define PMU_CNF_WAKE_FILTER_CNF_LIN_FT_Pos (0UL)                    /*!< PMU CNF_WAKE_FILTER: CNF_LIN_FT (Bit 0)               */
#define PMU_CNF_WAKE_FILTER_CNF_LIN_FT_Msk (0x1UL)                  /*!< PMU CNF_WAKE_FILTER: CNF_LIN_FT (Bitfield-Mask: 0x01) */
/* =======================================================  GPUDATA00  ======================================================= */
#define PMU_GPUDATA00_DATA0_Pos           (0UL)                     /*!< PMU GPUDATA00: DATA0 (Bit 0)                          */
#define PMU_GPUDATA00_DATA0_Msk           (0xffUL)                  /*!< PMU GPUDATA00: DATA0 (Bitfield-Mask: 0xff)            */
/* =======================================================  GPUDATA01  ======================================================= */
#define PMU_GPUDATA01_DATA1_Pos           (0UL)                     /*!< PMU GPUDATA01: DATA1 (Bit 0)                          */
#define PMU_GPUDATA01_DATA1_Msk           (0xffUL)                  /*!< PMU GPUDATA01: DATA1 (Bitfield-Mask: 0xff)            */
/* =======================================================  GPUDATA02  ======================================================= */
#define PMU_GPUDATA02_DATA2_Pos           (0UL)                     /*!< PMU GPUDATA02: DATA2 (Bit 0)                          */
#define PMU_GPUDATA02_DATA2_Msk           (0xffUL)                  /*!< PMU GPUDATA02: DATA2 (Bitfield-Mask: 0xff)            */
/* =======================================================  GPUDATA03  ======================================================= */
#define PMU_GPUDATA03_DATA3_Pos           (0UL)                     /*!< PMU GPUDATA03: DATA3 (Bit 0)                          */
#define PMU_GPUDATA03_DATA3_Msk           (0xffUL)                  /*!< PMU GPUDATA03: DATA3 (Bitfield-Mask: 0xff)            */
/* =======================================================  GPUDATA04  ======================================================= */
#define PMU_GPUDATA04_DATA4_Pos           (0UL)                     /*!< PMU GPUDATA04: DATA4 (Bit 0)                          */
#define PMU_GPUDATA04_DATA4_Msk           (0xffUL)                  /*!< PMU GPUDATA04: DATA4 (Bitfield-Mask: 0xff)            */
/* =======================================================  GPUDATA05  ======================================================= */
#define PMU_GPUDATA05_DATA5_Pos           (0UL)                     /*!< PMU GPUDATA05: DATA5 (Bit 0)                          */
#define PMU_GPUDATA05_DATA5_Msk           (0xffUL)                  /*!< PMU GPUDATA05: DATA5 (Bitfield-Mask: 0xff)            */
/* ======================================================  LIN_WAKE_EN  ====================================================== */
#define PMU_LIN_WAKE_EN_LIN_EN_Pos        (7UL)                     /*!< PMU LIN_WAKE_EN: LIN_EN (Bit 7)                       */
#define PMU_LIN_WAKE_EN_LIN_EN_Msk        (0x80UL)                  /*!< PMU LIN_WAKE_EN: LIN_EN (Bitfield-Mask: 0x01)         */
/* ========================================================  MON_CNF  ======================================================== */
#define PMU_MON_CNF_STS_Pos               (7UL)                     /*!< PMU MON_CNF: STS (Bit 7)                              */
#define PMU_MON_CNF_STS_Msk               (0x80UL)                  /*!< PMU MON_CNF: STS (Bitfield-Mask: 0x01)                */
#define PMU_MON_CNF_PU_Pos                (5UL)                     /*!< PMU MON_CNF: PU (Bit 5)                               */
#define PMU_MON_CNF_PU_Msk                (0x20UL)                  /*!< PMU MON_CNF: PU (Bitfield-Mask: 0x01)                 */
#define PMU_MON_CNF_PD_Pos                (4UL)                     /*!< PMU MON_CNF: PD (Bit 4)                               */
#define PMU_MON_CNF_PD_Msk                (0x10UL)                  /*!< PMU MON_CNF: PD (Bitfield-Mask: 0x01)                 */
#define PMU_MON_CNF_CYC_Pos               (3UL)                     /*!< PMU MON_CNF: CYC (Bit 3)                              */
#define PMU_MON_CNF_CYC_Msk               (0x8UL)                   /*!< PMU MON_CNF: CYC (Bitfield-Mask: 0x01)                */
#define PMU_MON_CNF_RISE_Pos              (2UL)                     /*!< PMU MON_CNF: RISE (Bit 2)                             */
#define PMU_MON_CNF_RISE_Msk              (0x4UL)                   /*!< PMU MON_CNF: RISE (Bitfield-Mask: 0x01)               */
#define PMU_MON_CNF_FALL_Pos              (1UL)                     /*!< PMU MON_CNF: FALL (Bit 1)                             */
#define PMU_MON_CNF_FALL_Msk              (0x2UL)                   /*!< PMU MON_CNF: FALL (Bitfield-Mask: 0x01)               */
#define PMU_MON_CNF_EN_Pos                (0UL)                     /*!< PMU MON_CNF: EN (Bit 0)                               */
#define PMU_MON_CNF_EN_Msk                (0x1UL)                   /*!< PMU MON_CNF: EN (Bitfield-Mask: 0x01)                 */
/* ====================================================  PMU_RESET_STS1  ===================================================== */
#define PMU_PMU_RESET_STS1_PMU_1V5DidPOR_Pos (7UL)                  /*!< PMU PMU_RESET_STS1: PMU_1V5DidPOR (Bit 7)             */
#define PMU_PMU_RESET_STS1_PMU_1V5DidPOR_Msk (0x80UL)               /*!< PMU PMU_RESET_STS1: PMU_1V5DidPOR (Bitfield-Mask: 0x01) */
#define PMU_PMU_RESET_STS1_PMU_PIN_Pos    (6UL)                     /*!< PMU PMU_RESET_STS1: PMU_PIN (Bit 6)                   */
#define PMU_PMU_RESET_STS1_PMU_PIN_Msk    (0x40UL)                  /*!< PMU PMU_RESET_STS1: PMU_PIN (Bitfield-Mask: 0x01)     */
#define PMU_PMU_RESET_STS1_PMU_ExtWDT_Pos (5UL)                     /*!< PMU PMU_RESET_STS1: PMU_ExtWDT (Bit 5)                */
#define PMU_PMU_RESET_STS1_PMU_ExtWDT_Msk (0x20UL)                  /*!< PMU PMU_RESET_STS1: PMU_ExtWDT (Bitfield-Mask: 0x01)  */
#define PMU_PMU_RESET_STS1_PMU_ClkWDT_Pos (4UL)                     /*!< PMU PMU_RESET_STS1: PMU_ClkWDT (Bit 4)                */
#define PMU_PMU_RESET_STS1_PMU_ClkWDT_Msk (0x10UL)                  /*!< PMU PMU_RESET_STS1: PMU_ClkWDT (Bitfield-Mask: 0x01)  */
#define PMU_PMU_RESET_STS1_PMU_LPR_Pos    (3UL)                     /*!< PMU PMU_RESET_STS1: PMU_LPR (Bit 3)                   */
#define PMU_PMU_RESET_STS1_PMU_LPR_Msk    (0x8UL)                   /*!< PMU PMU_RESET_STS1: PMU_LPR (Bitfield-Mask: 0x01)     */
#define PMU_PMU_RESET_STS1_PMU_SleepEX_Pos (2UL)                    /*!< PMU PMU_RESET_STS1: PMU_SleepEX (Bit 2)               */
#define PMU_PMU_RESET_STS1_PMU_SleepEX_Msk (0x4UL)                  /*!< PMU PMU_RESET_STS1: PMU_SleepEX (Bitfield-Mask: 0x01) */
#define PMU_PMU_RESET_STS1_PMU_WAKE_Pos   (1UL)                     /*!< PMU PMU_RESET_STS1: PMU_WAKE (Bit 1)                  */
#define PMU_PMU_RESET_STS1_PMU_WAKE_Msk   (0x2UL)                   /*!< PMU PMU_RESET_STS1: PMU_WAKE (Bitfield-Mask: 0x01)    */
#define PMU_PMU_RESET_STS1_SYS_FAIL_Pos   (0UL)                     /*!< PMU PMU_RESET_STS1: SYS_FAIL (Bit 0)                  */
#define PMU_PMU_RESET_STS1_SYS_FAIL_Msk   (0x1UL)                   /*!< PMU PMU_RESET_STS1: SYS_FAIL (Bitfield-Mask: 0x01)    */
/* ====================================================  PMU_RESET_STS2  ===================================================== */
#define PMU_PMU_RESET_STS2_LOCKUP_Pos     (2UL)                     /*!< PMU PMU_RESET_STS2: LOCKUP (Bit 2)                    */
#define PMU_PMU_RESET_STS2_LOCKUP_Msk     (0x4UL)                   /*!< PMU PMU_RESET_STS2: LOCKUP (Bitfield-Mask: 0x01)      */
#define PMU_PMU_RESET_STS2_PMU_SOFT_Pos   (1UL)                     /*!< PMU PMU_RESET_STS2: PMU_SOFT (Bit 1)                  */
#define PMU_PMU_RESET_STS2_PMU_SOFT_Msk   (0x2UL)                   /*!< PMU PMU_RESET_STS2: PMU_SOFT (Bitfield-Mask: 0x01)    */
#define PMU_PMU_RESET_STS2_PMU_IntWDT_Pos (0UL)                     /*!< PMU PMU_RESET_STS2: PMU_IntWDT (Bit 0)                */
#define PMU_PMU_RESET_STS2_PMU_IntWDT_Msk (0x1UL)                   /*!< PMU PMU_RESET_STS2: PMU_IntWDT (Bitfield-Mask: 0x01)  */
/* ====================================================  PMU_SUPPLY_STS  ===================================================== */
#define PMU_PMU_SUPPLY_STS_PMU_5V_FAIL_EN_Pos (6UL)                 /*!< PMU PMU_SUPPLY_STS: PMU_5V_FAIL_EN (Bit 6)            */
#define PMU_PMU_SUPPLY_STS_PMU_5V_FAIL_EN_Msk (0x40UL)              /*!< PMU PMU_SUPPLY_STS: PMU_5V_FAIL_EN (Bitfield-Mask: 0x01) */
#define PMU_PMU_SUPPLY_STS_PMU_5V_OVERLOAD_Pos (5UL)                /*!< PMU PMU_SUPPLY_STS: PMU_5V_OVERLOAD (Bit 5)           */
#define PMU_PMU_SUPPLY_STS_PMU_5V_OVERLOAD_Msk (0x20UL)             /*!< PMU PMU_SUPPLY_STS: PMU_5V_OVERLOAD (Bitfield-Mask: 0x01) */
#define PMU_PMU_SUPPLY_STS_PMU_5V_OVERVOLT_Pos (4UL)                /*!< PMU PMU_SUPPLY_STS: PMU_5V_OVERVOLT (Bit 4)           */
#define PMU_PMU_SUPPLY_STS_PMU_5V_OVERVOLT_Msk (0x10UL)             /*!< PMU PMU_SUPPLY_STS: PMU_5V_OVERVOLT (Bitfield-Mask: 0x01) */
#define PMU_PMU_SUPPLY_STS_PMU_1V5_FAIL_EN_Pos (2UL)                /*!< PMU PMU_SUPPLY_STS: PMU_1V5_FAIL_EN (Bit 2)           */
#define PMU_PMU_SUPPLY_STS_PMU_1V5_FAIL_EN_Msk (0x4UL)              /*!< PMU PMU_SUPPLY_STS: PMU_1V5_FAIL_EN (Bitfield-Mask: 0x01) */
#define PMU_PMU_SUPPLY_STS_PMU_1V5_OVERLOAD_Pos (1UL)               /*!< PMU PMU_SUPPLY_STS: PMU_1V5_OVERLOAD (Bit 1)          */
#define PMU_PMU_SUPPLY_STS_PMU_1V5_OVERLOAD_Msk (0x2UL)             /*!< PMU PMU_SUPPLY_STS: PMU_1V5_OVERLOAD (Bitfield-Mask: 0x01) */
#define PMU_PMU_SUPPLY_STS_PMU_1V5_OVERVOLT_Pos (0UL)               /*!< PMU PMU_SUPPLY_STS: PMU_1V5_OVERVOLT (Bit 0)          */
#define PMU_PMU_SUPPLY_STS_PMU_1V5_OVERVOLT_Msk (0x1UL)             /*!< PMU PMU_SUPPLY_STS: PMU_1V5_OVERVOLT (Bitfield-Mask: 0x01) */
/* =====================================================  SYS_FAIL_STS  ====================================================== */
#define PMU_SYS_FAIL_STS_WDT1_SEQ_FAIL_Pos (6UL)                    /*!< PMU SYS_FAIL_STS: WDT1_SEQ_FAIL (Bit 6)               */
#define PMU_SYS_FAIL_STS_WDT1_SEQ_FAIL_Msk (0x40UL)                 /*!< PMU SYS_FAIL_STS: WDT1_SEQ_FAIL (Bitfield-Mask: 0x01) */
#define PMU_SYS_FAIL_STS_SYS_OT_Pos       (5UL)                     /*!< PMU SYS_FAIL_STS: SYS_OT (Bit 5)                      */
#define PMU_SYS_FAIL_STS_SYS_OT_Msk       (0x20UL)                  /*!< PMU SYS_FAIL_STS: SYS_OT (Bitfield-Mask: 0x01)        */
#define PMU_SYS_FAIL_STS_PMU_5V_OVL_Pos   (3UL)                     /*!< PMU SYS_FAIL_STS: PMU_5V_OVL (Bit 3)                  */
#define PMU_SYS_FAIL_STS_PMU_5V_OVL_Msk   (0x8UL)                   /*!< PMU SYS_FAIL_STS: PMU_5V_OVL (Bitfield-Mask: 0x01)    */
#define PMU_SYS_FAIL_STS_PMU_1V5_OVL_Pos  (2UL)                     /*!< PMU SYS_FAIL_STS: PMU_1V5_OVL (Bit 2)                 */
#define PMU_SYS_FAIL_STS_PMU_1V5_OVL_Msk  (0x4UL)                   /*!< PMU SYS_FAIL_STS: PMU_1V5_OVL (Bitfield-Mask: 0x01)   */
#define PMU_SYS_FAIL_STS_SUPP_TMOUT_Pos   (1UL)                     /*!< PMU SYS_FAIL_STS: SUPP_TMOUT (Bit 1)                  */
#define PMU_SYS_FAIL_STS_SUPP_TMOUT_Msk   (0x2UL)                   /*!< PMU SYS_FAIL_STS: SUPP_TMOUT (Bitfield-Mask: 0x01)    */
#define PMU_SYS_FAIL_STS_SUPP_SHORT_Pos   (0UL)                     /*!< PMU SYS_FAIL_STS: SUPP_SHORT (Bit 0)                  */
#define PMU_SYS_FAIL_STS_SUPP_SHORT_Msk   (0x1UL)                   /*!< PMU SYS_FAIL_STS: SUPP_SHORT (Bitfield-Mask: 0x01)    */
/* ===================================================  SystemStartConfig  =================================================== */
#define PMU_SystemStartConfig_MBIST_EN_Pos (0UL)                    /*!< PMU SystemStartConfig: MBIST_EN (Bit 0)               */
#define PMU_SystemStartConfig_MBIST_EN_Msk (0x1UL)                  /*!< PMU SystemStartConfig: MBIST_EN (Bitfield-Mask: 0x01) */
/* ======================================================  VDDEXT_CTRL  ====================================================== */
#define PMU_VDDEXT_CTRL_STABLE_Pos        (7UL)                     /*!< PMU VDDEXT_CTRL: STABLE (Bit 7)                       */
#define PMU_VDDEXT_CTRL_STABLE_Msk        (0x80UL)                  /*!< PMU VDDEXT_CTRL: STABLE (Bitfield-Mask: 0x01)         */
#define PMU_VDDEXT_CTRL_OK_Pos            (6UL)                     /*!< PMU VDDEXT_CTRL: OK (Bit 6)                           */
#define PMU_VDDEXT_CTRL_OK_Msk            (0x40UL)                  /*!< PMU VDDEXT_CTRL: OK (Bitfield-Mask: 0x01)             */
#define PMU_VDDEXT_CTRL_OVERLOAD_Pos      (5UL)                     /*!< PMU VDDEXT_CTRL: OVERLOAD (Bit 5)                     */
#define PMU_VDDEXT_CTRL_OVERLOAD_Msk      (0x20UL)                  /*!< PMU VDDEXT_CTRL: OVERLOAD (Bitfield-Mask: 0x01)       */
#define PMU_VDDEXT_CTRL_OVERVOLT_Pos      (4UL)                     /*!< PMU VDDEXT_CTRL: OVERVOLT (Bit 4)                     */
#define PMU_VDDEXT_CTRL_OVERVOLT_Msk      (0x10UL)                  /*!< PMU VDDEXT_CTRL: OVERVOLT (Bitfield-Mask: 0x01)       */
#define PMU_VDDEXT_CTRL_SHORT_Pos         (3UL)                     /*!< PMU VDDEXT_CTRL: SHORT (Bit 3)                        */
#define PMU_VDDEXT_CTRL_SHORT_Msk         (0x8UL)                   /*!< PMU VDDEXT_CTRL: SHORT (Bitfield-Mask: 0x01)          */
#define PMU_VDDEXT_CTRL_FAIL_EN_Pos       (2UL)                     /*!< PMU VDDEXT_CTRL: FAIL_EN (Bit 2)                      */
#define PMU_VDDEXT_CTRL_FAIL_EN_Msk       (0x4UL)                   /*!< PMU VDDEXT_CTRL: FAIL_EN (Bitfield-Mask: 0x01)        */
#define PMU_VDDEXT_CTRL_CYC_EN_Pos        (1UL)                     /*!< PMU VDDEXT_CTRL: CYC_EN (Bit 1)                       */
#define PMU_VDDEXT_CTRL_CYC_EN_Msk        (0x2UL)                   /*!< PMU VDDEXT_CTRL: CYC_EN (Bitfield-Mask: 0x01)         */
#define PMU_VDDEXT_CTRL_ENABLE_Pos        (0UL)                     /*!< PMU VDDEXT_CTRL: ENABLE (Bit 0)                       */
#define PMU_VDDEXT_CTRL_ENABLE_Msk        (0x1UL)                   /*!< PMU VDDEXT_CTRL: ENABLE (Bitfield-Mask: 0x01)         */
/* ==================================================  WAKE_CONF_GPIO0_CYC  ================================================== */
#define PMU_WAKE_CONF_GPIO0_CYC_GPIO0_CYC_4_Pos (4UL)               /*!< PMU WAKE_CONF_GPIO0_CYC: GPIO0_CYC_4 (Bit 4)          */
#define PMU_WAKE_CONF_GPIO0_CYC_GPIO0_CYC_4_Msk (0x10UL)            /*!< PMU WAKE_CONF_GPIO0_CYC: GPIO0_CYC_4 (Bitfield-Mask: 0x01) */
#define PMU_WAKE_CONF_GPIO0_CYC_GPIO0_CYC_3_Pos (3UL)               /*!< PMU WAKE_CONF_GPIO0_CYC: GPIO0_CYC_3 (Bit 3)          */
#define PMU_WAKE_CONF_GPIO0_CYC_GPIO0_CYC_3_Msk (0x8UL)             /*!< PMU WAKE_CONF_GPIO0_CYC: GPIO0_CYC_3 (Bitfield-Mask: 0x01) */
#define PMU_WAKE_CONF_GPIO0_CYC_GPIO0_CYC_2_Pos (2UL)               /*!< PMU WAKE_CONF_GPIO0_CYC: GPIO0_CYC_2 (Bit 2)          */
#define PMU_WAKE_CONF_GPIO0_CYC_GPIO0_CYC_2_Msk (0x4UL)             /*!< PMU WAKE_CONF_GPIO0_CYC: GPIO0_CYC_2 (Bitfield-Mask: 0x01) */
#define PMU_WAKE_CONF_GPIO0_CYC_GPIO0_CYC_1_Pos (1UL)               /*!< PMU WAKE_CONF_GPIO0_CYC: GPIO0_CYC_1 (Bit 1)          */
#define PMU_WAKE_CONF_GPIO0_CYC_GPIO0_CYC_1_Msk (0x2UL)             /*!< PMU WAKE_CONF_GPIO0_CYC: GPIO0_CYC_1 (Bitfield-Mask: 0x01) */
#define PMU_WAKE_CONF_GPIO0_CYC_GPIO0_CYC_0_Pos (0UL)               /*!< PMU WAKE_CONF_GPIO0_CYC: GPIO0_CYC_0 (Bit 0)          */
#define PMU_WAKE_CONF_GPIO0_CYC_GPIO0_CYC_0_Msk (0x1UL)             /*!< PMU WAKE_CONF_GPIO0_CYC: GPIO0_CYC_0 (Bitfield-Mask: 0x01) */
/* =================================================  WAKE_CONF_GPIO0_FALL  ================================================== */
#define PMU_WAKE_CONF_GPIO0_FALL_GPIO0_FA_4_Pos (4UL)               /*!< PMU WAKE_CONF_GPIO0_FALL: GPIO0_FA_4 (Bit 4)          */
#define PMU_WAKE_CONF_GPIO0_FALL_GPIO0_FA_4_Msk (0x10UL)            /*!< PMU WAKE_CONF_GPIO0_FALL: GPIO0_FA_4 (Bitfield-Mask: 0x01) */
#define PMU_WAKE_CONF_GPIO0_FALL_GPIO0_FA_3_Pos (3UL)               /*!< PMU WAKE_CONF_GPIO0_FALL: GPIO0_FA_3 (Bit 3)          */
#define PMU_WAKE_CONF_GPIO0_FALL_GPIO0_FA_3_Msk (0x8UL)             /*!< PMU WAKE_CONF_GPIO0_FALL: GPIO0_FA_3 (Bitfield-Mask: 0x01) */
#define PMU_WAKE_CONF_GPIO0_FALL_GPIO0_FA_2_Pos (2UL)               /*!< PMU WAKE_CONF_GPIO0_FALL: GPIO0_FA_2 (Bit 2)          */
#define PMU_WAKE_CONF_GPIO0_FALL_GPIO0_FA_2_Msk (0x4UL)             /*!< PMU WAKE_CONF_GPIO0_FALL: GPIO0_FA_2 (Bitfield-Mask: 0x01) */
#define PMU_WAKE_CONF_GPIO0_FALL_GPIO0_FA_1_Pos (1UL)               /*!< PMU WAKE_CONF_GPIO0_FALL: GPIO0_FA_1 (Bit 1)          */
#define PMU_WAKE_CONF_GPIO0_FALL_GPIO0_FA_1_Msk (0x2UL)             /*!< PMU WAKE_CONF_GPIO0_FALL: GPIO0_FA_1 (Bitfield-Mask: 0x01) */
#define PMU_WAKE_CONF_GPIO0_FALL_GPIO0_FA_0_Pos (0UL)               /*!< PMU WAKE_CONF_GPIO0_FALL: GPIO0_FA_0 (Bit 0)          */
#define PMU_WAKE_CONF_GPIO0_FALL_GPIO0_FA_0_Msk (0x1UL)             /*!< PMU WAKE_CONF_GPIO0_FALL: GPIO0_FA_0 (Bitfield-Mask: 0x01) */
/* =================================================  WAKE_CONF_GPIO0_RISE  ================================================== */
#define PMU_WAKE_CONF_GPIO0_RISE_GPIO0_RI_4_Pos (4UL)               /*!< PMU WAKE_CONF_GPIO0_RISE: GPIO0_RI_4 (Bit 4)          */
#define PMU_WAKE_CONF_GPIO0_RISE_GPIO0_RI_4_Msk (0x10UL)            /*!< PMU WAKE_CONF_GPIO0_RISE: GPIO0_RI_4 (Bitfield-Mask: 0x01) */
#define PMU_WAKE_CONF_GPIO0_RISE_GPIO0_RI_3_Pos (3UL)               /*!< PMU WAKE_CONF_GPIO0_RISE: GPIO0_RI_3 (Bit 3)          */
#define PMU_WAKE_CONF_GPIO0_RISE_GPIO0_RI_3_Msk (0x8UL)             /*!< PMU WAKE_CONF_GPIO0_RISE: GPIO0_RI_3 (Bitfield-Mask: 0x01) */
#define PMU_WAKE_CONF_GPIO0_RISE_GPIO0_RI_2_Pos (2UL)               /*!< PMU WAKE_CONF_GPIO0_RISE: GPIO0_RI_2 (Bit 2)          */
#define PMU_WAKE_CONF_GPIO0_RISE_GPIO0_RI_2_Msk (0x4UL)             /*!< PMU WAKE_CONF_GPIO0_RISE: GPIO0_RI_2 (Bitfield-Mask: 0x01) */
#define PMU_WAKE_CONF_GPIO0_RISE_GPIO0_RI_1_Pos (1UL)               /*!< PMU WAKE_CONF_GPIO0_RISE: GPIO0_RI_1 (Bit 1)          */
#define PMU_WAKE_CONF_GPIO0_RISE_GPIO0_RI_1_Msk (0x2UL)             /*!< PMU WAKE_CONF_GPIO0_RISE: GPIO0_RI_1 (Bitfield-Mask: 0x01) */
#define PMU_WAKE_CONF_GPIO0_RISE_GPIO0_RI_0_Pos (0UL)               /*!< PMU WAKE_CONF_GPIO0_RISE: GPIO0_RI_0 (Bit 0)          */
#define PMU_WAKE_CONF_GPIO0_RISE_GPIO0_RI_0_Msk (0x1UL)             /*!< PMU WAKE_CONF_GPIO0_RISE: GPIO0_RI_0 (Bitfield-Mask: 0x01) */
/* ==================================================  WAKE_CONF_GPIO1_CYC  ================================================== */
#define PMU_WAKE_CONF_GPIO1_CYC_GPIO1_CYC_4_Pos (4UL)               /*!< PMU WAKE_CONF_GPIO1_CYC: GPIO1_CYC_4 (Bit 4)          */
#define PMU_WAKE_CONF_GPIO1_CYC_GPIO1_CYC_4_Msk (0x10UL)            /*!< PMU WAKE_CONF_GPIO1_CYC: GPIO1_CYC_4 (Bitfield-Mask: 0x01) */
#define PMU_WAKE_CONF_GPIO1_CYC_GPIO1_CYC_3_Pos (3UL)               /*!< PMU WAKE_CONF_GPIO1_CYC: GPIO1_CYC_3 (Bit 3)          */
#define PMU_WAKE_CONF_GPIO1_CYC_GPIO1_CYC_3_Msk (0x8UL)             /*!< PMU WAKE_CONF_GPIO1_CYC: GPIO1_CYC_3 (Bitfield-Mask: 0x01) */
#define PMU_WAKE_CONF_GPIO1_CYC_GPIO1_CYC_2_Pos (2UL)               /*!< PMU WAKE_CONF_GPIO1_CYC: GPIO1_CYC_2 (Bit 2)          */
#define PMU_WAKE_CONF_GPIO1_CYC_GPIO1_CYC_2_Msk (0x4UL)             /*!< PMU WAKE_CONF_GPIO1_CYC: GPIO1_CYC_2 (Bitfield-Mask: 0x01) */
#define PMU_WAKE_CONF_GPIO1_CYC_GPIO1_CYC_1_Pos (1UL)               /*!< PMU WAKE_CONF_GPIO1_CYC: GPIO1_CYC_1 (Bit 1)          */
#define PMU_WAKE_CONF_GPIO1_CYC_GPIO1_CYC_1_Msk (0x2UL)             /*!< PMU WAKE_CONF_GPIO1_CYC: GPIO1_CYC_1 (Bitfield-Mask: 0x01) */
#define PMU_WAKE_CONF_GPIO1_CYC_GPIO1_CYC_0_Pos (0UL)               /*!< PMU WAKE_CONF_GPIO1_CYC: GPIO1_CYC_0 (Bit 0)          */
#define PMU_WAKE_CONF_GPIO1_CYC_GPIO1_CYC_0_Msk (0x1UL)             /*!< PMU WAKE_CONF_GPIO1_CYC: GPIO1_CYC_0 (Bitfield-Mask: 0x01) */
/* =================================================  WAKE_CONF_GPIO1_FALL  ================================================== */
#define PMU_WAKE_CONF_GPIO1_FALL_GPIO1_FA_4_Pos (4UL)               /*!< PMU WAKE_CONF_GPIO1_FALL: GPIO1_FA_4 (Bit 4)          */
#define PMU_WAKE_CONF_GPIO1_FALL_GPIO1_FA_4_Msk (0x10UL)            /*!< PMU WAKE_CONF_GPIO1_FALL: GPIO1_FA_4 (Bitfield-Mask: 0x01) */
#define PMU_WAKE_CONF_GPIO1_FALL_GPIO1_FA_3_Pos (3UL)               /*!< PMU WAKE_CONF_GPIO1_FALL: GPIO1_FA_3 (Bit 3)          */
#define PMU_WAKE_CONF_GPIO1_FALL_GPIO1_FA_3_Msk (0x8UL)             /*!< PMU WAKE_CONF_GPIO1_FALL: GPIO1_FA_3 (Bitfield-Mask: 0x01) */
#define PMU_WAKE_CONF_GPIO1_FALL_GPIO1_FA_2_Pos (2UL)               /*!< PMU WAKE_CONF_GPIO1_FALL: GPIO1_FA_2 (Bit 2)          */
#define PMU_WAKE_CONF_GPIO1_FALL_GPIO1_FA_2_Msk (0x4UL)             /*!< PMU WAKE_CONF_GPIO1_FALL: GPIO1_FA_2 (Bitfield-Mask: 0x01) */
#define PMU_WAKE_CONF_GPIO1_FALL_GPIO1_FA_1_Pos (1UL)               /*!< PMU WAKE_CONF_GPIO1_FALL: GPIO1_FA_1 (Bit 1)          */
#define PMU_WAKE_CONF_GPIO1_FALL_GPIO1_FA_1_Msk (0x2UL)             /*!< PMU WAKE_CONF_GPIO1_FALL: GPIO1_FA_1 (Bitfield-Mask: 0x01) */
#define PMU_WAKE_CONF_GPIO1_FALL_GPIO1_FA_0_Pos (0UL)               /*!< PMU WAKE_CONF_GPIO1_FALL: GPIO1_FA_0 (Bit 0)          */
#define PMU_WAKE_CONF_GPIO1_FALL_GPIO1_FA_0_Msk (0x1UL)             /*!< PMU WAKE_CONF_GPIO1_FALL: GPIO1_FA_0 (Bitfield-Mask: 0x01) */
/* =================================================  WAKE_CONF_GPIO1_RISE  ================================================== */
#define PMU_WAKE_CONF_GPIO1_RISE_GPIO1_RI_4_Pos (4UL)               /*!< PMU WAKE_CONF_GPIO1_RISE: GPIO1_RI_4 (Bit 4)          */
#define PMU_WAKE_CONF_GPIO1_RISE_GPIO1_RI_4_Msk (0x10UL)            /*!< PMU WAKE_CONF_GPIO1_RISE: GPIO1_RI_4 (Bitfield-Mask: 0x01) */
#define PMU_WAKE_CONF_GPIO1_RISE_GPIO1_RI_3_Pos (3UL)               /*!< PMU WAKE_CONF_GPIO1_RISE: GPIO1_RI_3 (Bit 3)          */
#define PMU_WAKE_CONF_GPIO1_RISE_GPIO1_RI_3_Msk (0x8UL)             /*!< PMU WAKE_CONF_GPIO1_RISE: GPIO1_RI_3 (Bitfield-Mask: 0x01) */
#define PMU_WAKE_CONF_GPIO1_RISE_GPIO1_RI_2_Pos (2UL)               /*!< PMU WAKE_CONF_GPIO1_RISE: GPIO1_RI_2 (Bit 2)          */
#define PMU_WAKE_CONF_GPIO1_RISE_GPIO1_RI_2_Msk (0x4UL)             /*!< PMU WAKE_CONF_GPIO1_RISE: GPIO1_RI_2 (Bitfield-Mask: 0x01) */
#define PMU_WAKE_CONF_GPIO1_RISE_GPIO1_RI_1_Pos (1UL)               /*!< PMU WAKE_CONF_GPIO1_RISE: GPIO1_RI_1 (Bit 1)          */
#define PMU_WAKE_CONF_GPIO1_RISE_GPIO1_RI_1_Msk (0x2UL)             /*!< PMU WAKE_CONF_GPIO1_RISE: GPIO1_RI_1 (Bitfield-Mask: 0x01) */
#define PMU_WAKE_CONF_GPIO1_RISE_GPIO1_RI_0_Pos (0UL)               /*!< PMU WAKE_CONF_GPIO1_RISE: GPIO1_RI_0 (Bit 0)          */
#define PMU_WAKE_CONF_GPIO1_RISE_GPIO1_RI_0_Msk (0x1UL)             /*!< PMU WAKE_CONF_GPIO1_RISE: GPIO1_RI_0 (Bitfield-Mask: 0x01) */
/* ======================================================  WAKE_STATUS  ====================================================== */
#define PMU_WAKE_STATUS_FAIL_Pos          (5UL)                     /*!< PMU WAKE_STATUS: FAIL (Bit 5)                         */
#define PMU_WAKE_STATUS_FAIL_Msk          (0x20UL)                  /*!< PMU WAKE_STATUS: FAIL (Bitfield-Mask: 0x01)           */
#define PMU_WAKE_STATUS_CYC_WAKE_Pos      (4UL)                     /*!< PMU WAKE_STATUS: CYC_WAKE (Bit 4)                     */
#define PMU_WAKE_STATUS_CYC_WAKE_Msk      (0x10UL)                  /*!< PMU WAKE_STATUS: CYC_WAKE (Bitfield-Mask: 0x01)       */
#define PMU_WAKE_STATUS_GPIO1_Pos         (3UL)                     /*!< PMU WAKE_STATUS: GPIO1 (Bit 3)                        */
#define PMU_WAKE_STATUS_GPIO1_Msk         (0x8UL)                   /*!< PMU WAKE_STATUS: GPIO1 (Bitfield-Mask: 0x01)          */
#define PMU_WAKE_STATUS_GPIO0_Pos         (2UL)                     /*!< PMU WAKE_STATUS: GPIO0 (Bit 2)                        */
#define PMU_WAKE_STATUS_GPIO0_Msk         (0x4UL)                   /*!< PMU WAKE_STATUS: GPIO0 (Bitfield-Mask: 0x01)          */
#define PMU_WAKE_STATUS_MON_WAKE_Pos      (1UL)                     /*!< PMU WAKE_STATUS: MON_WAKE (Bit 1)                     */
#define PMU_WAKE_STATUS_MON_WAKE_Msk      (0x2UL)                   /*!< PMU WAKE_STATUS: MON_WAKE (Bitfield-Mask: 0x01)       */
#define PMU_WAKE_STATUS_LIN_WAKE_Pos      (0UL)                     /*!< PMU WAKE_STATUS: LIN_WAKE (Bit 0)                     */
#define PMU_WAKE_STATUS_LIN_WAKE_Msk      (0x1UL)                   /*!< PMU WAKE_STATUS: LIN_WAKE (Bitfield-Mask: 0x01)       */
/* =====================================================  WAKE_STS_FAIL  ===================================================== */
#define PMU_WAKE_STS_FAIL_VDDEXTSHORT_Pos (2UL)                     /*!< PMU WAKE_STS_FAIL: VDDEXTSHORT (Bit 2)                */
#define PMU_WAKE_STS_FAIL_VDDEXTSHORT_Msk (0x4UL)                   /*!< PMU WAKE_STS_FAIL: VDDEXTSHORT (Bitfield-Mask: 0x01)  */
#define PMU_WAKE_STS_FAIL_SUPPFAIL_Pos    (0UL)                     /*!< PMU WAKE_STS_FAIL: SUPPFAIL (Bit 0)                   */
#define PMU_WAKE_STS_FAIL_SUPPFAIL_Msk    (0x1UL)                   /*!< PMU WAKE_STS_FAIL: SUPPFAIL (Bitfield-Mask: 0x01)     */
/* ====================================================  WAKE_STS_GPIO0  ===================================================== */
#define PMU_WAKE_STS_GPIO0_GPIO0_STS_4_Pos (4UL)                    /*!< PMU WAKE_STS_GPIO0: GPIO0_STS_4 (Bit 4)               */
#define PMU_WAKE_STS_GPIO0_GPIO0_STS_4_Msk (0x10UL)                 /*!< PMU WAKE_STS_GPIO0: GPIO0_STS_4 (Bitfield-Mask: 0x01) */
#define PMU_WAKE_STS_GPIO0_GPIO0_STS_3_Pos (3UL)                    /*!< PMU WAKE_STS_GPIO0: GPIO0_STS_3 (Bit 3)               */
#define PMU_WAKE_STS_GPIO0_GPIO0_STS_3_Msk (0x8UL)                  /*!< PMU WAKE_STS_GPIO0: GPIO0_STS_3 (Bitfield-Mask: 0x01) */
#define PMU_WAKE_STS_GPIO0_GPIO0_STS_2_Pos (2UL)                    /*!< PMU WAKE_STS_GPIO0: GPIO0_STS_2 (Bit 2)               */
#define PMU_WAKE_STS_GPIO0_GPIO0_STS_2_Msk (0x4UL)                  /*!< PMU WAKE_STS_GPIO0: GPIO0_STS_2 (Bitfield-Mask: 0x01) */
#define PMU_WAKE_STS_GPIO0_GPIO0_STS_1_Pos (1UL)                    /*!< PMU WAKE_STS_GPIO0: GPIO0_STS_1 (Bit 1)               */
#define PMU_WAKE_STS_GPIO0_GPIO0_STS_1_Msk (0x2UL)                  /*!< PMU WAKE_STS_GPIO0: GPIO0_STS_1 (Bitfield-Mask: 0x01) */
#define PMU_WAKE_STS_GPIO0_GPIO0_STS_0_Pos (0UL)                    /*!< PMU WAKE_STS_GPIO0: GPIO0_STS_0 (Bit 0)               */
#define PMU_WAKE_STS_GPIO0_GPIO0_STS_0_Msk (0x1UL)                  /*!< PMU WAKE_STS_GPIO0: GPIO0_STS_0 (Bitfield-Mask: 0x01) */
/* ====================================================  WAKE_STS_GPIO1  ===================================================== */
#define PMU_WAKE_STS_GPIO1_GPIO1_STS_4_Pos (4UL)                    /*!< PMU WAKE_STS_GPIO1: GPIO1_STS_4 (Bit 4)               */
#define PMU_WAKE_STS_GPIO1_GPIO1_STS_4_Msk (0x10UL)                 /*!< PMU WAKE_STS_GPIO1: GPIO1_STS_4 (Bitfield-Mask: 0x01) */
#define PMU_WAKE_STS_GPIO1_GPIO1_STS_3_Pos (3UL)                    /*!< PMU WAKE_STS_GPIO1: GPIO1_STS_3 (Bit 3)               */
#define PMU_WAKE_STS_GPIO1_GPIO1_STS_3_Msk (0x8UL)                  /*!< PMU WAKE_STS_GPIO1: GPIO1_STS_3 (Bitfield-Mask: 0x01) */
#define PMU_WAKE_STS_GPIO1_GPIO1_STS_2_Pos (2UL)                    /*!< PMU WAKE_STS_GPIO1: GPIO1_STS_2 (Bit 2)               */
#define PMU_WAKE_STS_GPIO1_GPIO1_STS_2_Msk (0x4UL)                  /*!< PMU WAKE_STS_GPIO1: GPIO1_STS_2 (Bitfield-Mask: 0x01) */
#define PMU_WAKE_STS_GPIO1_GPIO1_STS_1_Pos (1UL)                    /*!< PMU WAKE_STS_GPIO1: GPIO1_STS_1 (Bit 1)               */
#define PMU_WAKE_STS_GPIO1_GPIO1_STS_1_Msk (0x2UL)                  /*!< PMU WAKE_STS_GPIO1: GPIO1_STS_1 (Bitfield-Mask: 0x01) */
#define PMU_WAKE_STS_GPIO1_GPIO1_STS_0_Pos (0UL)                    /*!< PMU WAKE_STS_GPIO1: GPIO1_STS_0 (Bit 0)               */
#define PMU_WAKE_STS_GPIO1_GPIO1_STS_0_Msk (0x1UL)                  /*!< PMU WAKE_STS_GPIO1: GPIO1_STS_0 (Bitfield-Mask: 0x01) */
/* =====================================================  WAKE_STS_MON  ====================================================== */
#define PMU_WAKE_STS_MON_WAKE_STS_Pos     (0UL)                     /*!< PMU WAKE_STS_MON: WAKE_STS (Bit 0)                    */
#define PMU_WAKE_STS_MON_WAKE_STS_Msk     (0x1UL)                   /*!< PMU WAKE_STS_MON: WAKE_STS (Bitfield-Mask: 0x01)      */


/* =========================================================================================================================== */
/* ================                                           PORT                                            ================ */
/* =========================================================================================================================== */

/* ======================================================  P0_ALTSEL0  ======================================================= */
#define PORT_P0_ALTSEL0_P0_Pos            (0UL)                     /*!< PORT P0_ALTSEL0: P0 (Bit 0)                           */
#define PORT_P0_ALTSEL0_P0_Msk            (0x1UL)                   /*!< PORT P0_ALTSEL0: P0 (Bitfield-Mask: 0x01)             */
#define PORT_P0_ALTSEL0_P1_Pos            (1UL)                     /*!< PORT P0_ALTSEL0: P1 (Bit 1)                           */
#define PORT_P0_ALTSEL0_P1_Msk            (0x2UL)                   /*!< PORT P0_ALTSEL0: P1 (Bitfield-Mask: 0x01)             */
#define PORT_P0_ALTSEL0_P2_Pos            (2UL)                     /*!< PORT P0_ALTSEL0: P2 (Bit 2)                           */
#define PORT_P0_ALTSEL0_P2_Msk            (0x4UL)                   /*!< PORT P0_ALTSEL0: P2 (Bitfield-Mask: 0x01)             */
#define PORT_P0_ALTSEL0_P3_Pos            (3UL)                     /*!< PORT P0_ALTSEL0: P3 (Bit 3)                           */
#define PORT_P0_ALTSEL0_P3_Msk            (0x8UL)                   /*!< PORT P0_ALTSEL0: P3 (Bitfield-Mask: 0x01)             */
#define PORT_P0_ALTSEL0_P4_Pos            (4UL)                     /*!< PORT P0_ALTSEL0: P4 (Bit 4)                           */
#define PORT_P0_ALTSEL0_P4_Msk            (0x10UL)                  /*!< PORT P0_ALTSEL0: P4 (Bitfield-Mask: 0x01)             */
/* ======================================================  P0_ALTSEL1  ======================================================= */
#define PORT_P0_ALTSEL1_P0_Pos            (0UL)                     /*!< PORT P0_ALTSEL1: P0 (Bit 0)                           */
#define PORT_P0_ALTSEL1_P0_Msk            (0x1UL)                   /*!< PORT P0_ALTSEL1: P0 (Bitfield-Mask: 0x01)             */
#define PORT_P0_ALTSEL1_P1_Pos            (1UL)                     /*!< PORT P0_ALTSEL1: P1 (Bit 1)                           */
#define PORT_P0_ALTSEL1_P1_Msk            (0x2UL)                   /*!< PORT P0_ALTSEL1: P1 (Bitfield-Mask: 0x01)             */
#define PORT_P0_ALTSEL1_P2_Pos            (2UL)                     /*!< PORT P0_ALTSEL1: P2 (Bit 2)                           */
#define PORT_P0_ALTSEL1_P2_Msk            (0x4UL)                   /*!< PORT P0_ALTSEL1: P2 (Bitfield-Mask: 0x01)             */
#define PORT_P0_ALTSEL1_P3_Pos            (3UL)                     /*!< PORT P0_ALTSEL1: P3 (Bit 3)                           */
#define PORT_P0_ALTSEL1_P3_Msk            (0x8UL)                   /*!< PORT P0_ALTSEL1: P3 (Bitfield-Mask: 0x01)             */
#define PORT_P0_ALTSEL1_P4_Pos            (4UL)                     /*!< PORT P0_ALTSEL1: P4 (Bit 4)                           */
#define PORT_P0_ALTSEL1_P4_Msk            (0x10UL)                  /*!< PORT P0_ALTSEL1: P4 (Bitfield-Mask: 0x01)             */
/* ========================================================  P0_DATA  ======================================================== */
#define PORT_P0_DATA_P0_Pos               (0UL)                     /*!< PORT P0_DATA: P0 (Bit 0)                              */
#define PORT_P0_DATA_P0_Msk               (0x1UL)                   /*!< PORT P0_DATA: P0 (Bitfield-Mask: 0x01)                */
#define PORT_P0_DATA_P1_Pos               (1UL)                     /*!< PORT P0_DATA: P1 (Bit 1)                              */
#define PORT_P0_DATA_P1_Msk               (0x2UL)                   /*!< PORT P0_DATA: P1 (Bitfield-Mask: 0x01)                */
#define PORT_P0_DATA_P2_Pos               (2UL)                     /*!< PORT P0_DATA: P2 (Bit 2)                              */
#define PORT_P0_DATA_P2_Msk               (0x4UL)                   /*!< PORT P0_DATA: P2 (Bitfield-Mask: 0x01)                */
#define PORT_P0_DATA_P3_Pos               (3UL)                     /*!< PORT P0_DATA: P3 (Bit 3)                              */
#define PORT_P0_DATA_P3_Msk               (0x8UL)                   /*!< PORT P0_DATA: P3 (Bitfield-Mask: 0x01)                */
#define PORT_P0_DATA_P4_Pos               (4UL)                     /*!< PORT P0_DATA: P4 (Bit 4)                              */
#define PORT_P0_DATA_P4_Msk               (0x10UL)                  /*!< PORT P0_DATA: P4 (Bitfield-Mask: 0x01)                */
/* ========================================================  P0_DIR  ========================================================= */
#define PORT_P0_DIR_P0_Pos                (0UL)                     /*!< PORT P0_DIR: P0 (Bit 0)                               */
#define PORT_P0_DIR_P0_Msk                (0x1UL)                   /*!< PORT P0_DIR: P0 (Bitfield-Mask: 0x01)                 */
#define PORT_P0_DIR_P1_Pos                (1UL)                     /*!< PORT P0_DIR: P1 (Bit 1)                               */
#define PORT_P0_DIR_P1_Msk                (0x2UL)                   /*!< PORT P0_DIR: P1 (Bitfield-Mask: 0x01)                 */
#define PORT_P0_DIR_P2_Pos                (2UL)                     /*!< PORT P0_DIR: P2 (Bit 2)                               */
#define PORT_P0_DIR_P2_Msk                (0x4UL)                   /*!< PORT P0_DIR: P2 (Bitfield-Mask: 0x01)                 */
#define PORT_P0_DIR_P3_Pos                (3UL)                     /*!< PORT P0_DIR: P3 (Bit 3)                               */
#define PORT_P0_DIR_P3_Msk                (0x8UL)                   /*!< PORT P0_DIR: P3 (Bitfield-Mask: 0x01)                 */
#define PORT_P0_DIR_P4_Pos                (4UL)                     /*!< PORT P0_DIR: P4 (Bit 4)                               */
#define PORT_P0_DIR_P4_Msk                (0x10UL)                  /*!< PORT P0_DIR: P4 (Bitfield-Mask: 0x01)                 */
/* =========================================================  P0_OD  ========================================================= */
#define PORT_P0_OD_P0_Pos                 (0UL)                     /*!< PORT P0_OD: P0 (Bit 0)                                */
#define PORT_P0_OD_P0_Msk                 (0x1UL)                   /*!< PORT P0_OD: P0 (Bitfield-Mask: 0x01)                  */
#define PORT_P0_OD_P1_Pos                 (1UL)                     /*!< PORT P0_OD: P1 (Bit 1)                                */
#define PORT_P0_OD_P1_Msk                 (0x2UL)                   /*!< PORT P0_OD: P1 (Bitfield-Mask: 0x01)                  */
#define PORT_P0_OD_P2_Pos                 (2UL)                     /*!< PORT P0_OD: P2 (Bit 2)                                */
#define PORT_P0_OD_P2_Msk                 (0x4UL)                   /*!< PORT P0_OD: P2 (Bitfield-Mask: 0x01)                  */
#define PORT_P0_OD_P3_Pos                 (3UL)                     /*!< PORT P0_OD: P3 (Bit 3)                                */
#define PORT_P0_OD_P3_Msk                 (0x8UL)                   /*!< PORT P0_OD: P3 (Bitfield-Mask: 0x01)                  */
#define PORT_P0_OD_P4_Pos                 (4UL)                     /*!< PORT P0_OD: P4 (Bit 4)                                */
#define PORT_P0_OD_P4_Msk                 (0x10UL)                  /*!< PORT P0_OD: P4 (Bitfield-Mask: 0x01)                  */
/* =======================================================  P0_PUDEN  ======================================================== */
#define PORT_P0_PUDEN_P0_Pos              (0UL)                     /*!< PORT P0_PUDEN: P0 (Bit 0)                             */
#define PORT_P0_PUDEN_P0_Msk              (0x1UL)                   /*!< PORT P0_PUDEN: P0 (Bitfield-Mask: 0x01)               */
#define PORT_P0_PUDEN_P1_Pos              (1UL)                     /*!< PORT P0_PUDEN: P1 (Bit 1)                             */
#define PORT_P0_PUDEN_P1_Msk              (0x2UL)                   /*!< PORT P0_PUDEN: P1 (Bitfield-Mask: 0x01)               */
#define PORT_P0_PUDEN_P2_Pos              (2UL)                     /*!< PORT P0_PUDEN: P2 (Bit 2)                             */
#define PORT_P0_PUDEN_P2_Msk              (0x4UL)                   /*!< PORT P0_PUDEN: P2 (Bitfield-Mask: 0x01)               */
#define PORT_P0_PUDEN_P3_Pos              (3UL)                     /*!< PORT P0_PUDEN: P3 (Bit 3)                             */
#define PORT_P0_PUDEN_P3_Msk              (0x8UL)                   /*!< PORT P0_PUDEN: P3 (Bitfield-Mask: 0x01)               */
#define PORT_P0_PUDEN_P4_Pos              (4UL)                     /*!< PORT P0_PUDEN: P4 (Bit 4)                             */
#define PORT_P0_PUDEN_P4_Msk              (0x10UL)                  /*!< PORT P0_PUDEN: P4 (Bitfield-Mask: 0x01)               */
/* =======================================================  P0_PUDSEL  ======================================================= */
#define PORT_P0_PUDSEL_P0_Pos             (0UL)                     /*!< PORT P0_PUDSEL: P0 (Bit 0)                            */
#define PORT_P0_PUDSEL_P0_Msk             (0x1UL)                   /*!< PORT P0_PUDSEL: P0 (Bitfield-Mask: 0x01)              */
#define PORT_P0_PUDSEL_P1_Pos             (1UL)                     /*!< PORT P0_PUDSEL: P1 (Bit 1)                            */
#define PORT_P0_PUDSEL_P1_Msk             (0x2UL)                   /*!< PORT P0_PUDSEL: P1 (Bitfield-Mask: 0x01)              */
#define PORT_P0_PUDSEL_P2_Pos             (2UL)                     /*!< PORT P0_PUDSEL: P2 (Bit 2)                            */
#define PORT_P0_PUDSEL_P2_Msk             (0x4UL)                   /*!< PORT P0_PUDSEL: P2 (Bitfield-Mask: 0x01)              */
#define PORT_P0_PUDSEL_P3_Pos             (3UL)                     /*!< PORT P0_PUDSEL: P3 (Bit 3)                            */
#define PORT_P0_PUDSEL_P3_Msk             (0x8UL)                   /*!< PORT P0_PUDSEL: P3 (Bitfield-Mask: 0x01)              */
#define PORT_P0_PUDSEL_P4_Pos             (4UL)                     /*!< PORT P0_PUDSEL: P4 (Bit 4)                            */
#define PORT_P0_PUDSEL_P4_Msk             (0x10UL)                  /*!< PORT P0_PUDSEL: P4 (Bitfield-Mask: 0x01)              */
/* ======================================================  P1_ALTSEL0  ======================================================= */
#define PORT_P1_ALTSEL0_P0_Pos            (0UL)                     /*!< PORT P1_ALTSEL0: P0 (Bit 0)                           */
#define PORT_P1_ALTSEL0_P0_Msk            (0x1UL)                   /*!< PORT P1_ALTSEL0: P0 (Bitfield-Mask: 0x01)             */
#define PORT_P1_ALTSEL0_P1_Pos            (1UL)                     /*!< PORT P1_ALTSEL0: P1 (Bit 1)                           */
#define PORT_P1_ALTSEL0_P1_Msk            (0x2UL)                   /*!< PORT P1_ALTSEL0: P1 (Bitfield-Mask: 0x01)             */
#define PORT_P1_ALTSEL0_P2_Pos            (2UL)                     /*!< PORT P1_ALTSEL0: P2 (Bit 2)                           */
#define PORT_P1_ALTSEL0_P2_Msk            (0x4UL)                   /*!< PORT P1_ALTSEL0: P2 (Bitfield-Mask: 0x01)             */
#define PORT_P1_ALTSEL0_P3_Pos            (3UL)                     /*!< PORT P1_ALTSEL0: P3 (Bit 3)                           */
#define PORT_P1_ALTSEL0_P3_Msk            (0x8UL)                   /*!< PORT P1_ALTSEL0: P3 (Bitfield-Mask: 0x01)             */
#define PORT_P1_ALTSEL0_P4_Pos            (4UL)                     /*!< PORT P1_ALTSEL0: P4 (Bit 4)                           */
#define PORT_P1_ALTSEL0_P4_Msk            (0x10UL)                  /*!< PORT P1_ALTSEL0: P4 (Bitfield-Mask: 0x01)             */
/* ======================================================  P1_ALTSEL1  ======================================================= */
#define PORT_P1_ALTSEL1_P0_Pos            (0UL)                     /*!< PORT P1_ALTSEL1: P0 (Bit 0)                           */
#define PORT_P1_ALTSEL1_P0_Msk            (0x1UL)                   /*!< PORT P1_ALTSEL1: P0 (Bitfield-Mask: 0x01)             */
#define PORT_P1_ALTSEL1_P1_Pos            (1UL)                     /*!< PORT P1_ALTSEL1: P1 (Bit 1)                           */
#define PORT_P1_ALTSEL1_P1_Msk            (0x2UL)                   /*!< PORT P1_ALTSEL1: P1 (Bitfield-Mask: 0x01)             */
#define PORT_P1_ALTSEL1_P2_Pos            (2UL)                     /*!< PORT P1_ALTSEL1: P2 (Bit 2)                           */
#define PORT_P1_ALTSEL1_P2_Msk            (0x4UL)                   /*!< PORT P1_ALTSEL1: P2 (Bitfield-Mask: 0x01)             */
#define PORT_P1_ALTSEL1_P3_Pos            (3UL)                     /*!< PORT P1_ALTSEL1: P3 (Bit 3)                           */
#define PORT_P1_ALTSEL1_P3_Msk            (0x8UL)                   /*!< PORT P1_ALTSEL1: P3 (Bitfield-Mask: 0x01)             */
#define PORT_P1_ALTSEL1_P4_Pos            (4UL)                     /*!< PORT P1_ALTSEL1: P4 (Bit 4)                           */
#define PORT_P1_ALTSEL1_P4_Msk            (0x10UL)                  /*!< PORT P1_ALTSEL1: P4 (Bitfield-Mask: 0x01)             */
/* ========================================================  P1_DATA  ======================================================== */
#define PORT_P1_DATA_P0_Pos               (0UL)                     /*!< PORT P1_DATA: P0 (Bit 0)                              */
#define PORT_P1_DATA_P0_Msk               (0x1UL)                   /*!< PORT P1_DATA: P0 (Bitfield-Mask: 0x01)                */
#define PORT_P1_DATA_P1_Pos               (1UL)                     /*!< PORT P1_DATA: P1 (Bit 1)                              */
#define PORT_P1_DATA_P1_Msk               (0x2UL)                   /*!< PORT P1_DATA: P1 (Bitfield-Mask: 0x01)                */
#define PORT_P1_DATA_P2_Pos               (2UL)                     /*!< PORT P1_DATA: P2 (Bit 2)                              */
#define PORT_P1_DATA_P2_Msk               (0x4UL)                   /*!< PORT P1_DATA: P2 (Bitfield-Mask: 0x01)                */
#define PORT_P1_DATA_P3_Pos               (3UL)                     /*!< PORT P1_DATA: P3 (Bit 3)                              */
#define PORT_P1_DATA_P3_Msk               (0x8UL)                   /*!< PORT P1_DATA: P3 (Bitfield-Mask: 0x01)                */
#define PORT_P1_DATA_P4_Pos               (4UL)                     /*!< PORT P1_DATA: P4 (Bit 4)                              */
#define PORT_P1_DATA_P4_Msk               (0x10UL)                  /*!< PORT P1_DATA: P4 (Bitfield-Mask: 0x01)                */
/* ========================================================  P1_DIR  ========================================================= */
#define PORT_P1_DIR_P0_Pos                (0UL)                     /*!< PORT P1_DIR: P0 (Bit 0)                               */
#define PORT_P1_DIR_P0_Msk                (0x1UL)                   /*!< PORT P1_DIR: P0 (Bitfield-Mask: 0x01)                 */
#define PORT_P1_DIR_P1_Pos                (1UL)                     /*!< PORT P1_DIR: P1 (Bit 1)                               */
#define PORT_P1_DIR_P1_Msk                (0x2UL)                   /*!< PORT P1_DIR: P1 (Bitfield-Mask: 0x01)                 */
#define PORT_P1_DIR_P2_Pos                (2UL)                     /*!< PORT P1_DIR: P2 (Bit 2)                               */
#define PORT_P1_DIR_P2_Msk                (0x4UL)                   /*!< PORT P1_DIR: P2 (Bitfield-Mask: 0x01)                 */
#define PORT_P1_DIR_P3_Pos                (3UL)                     /*!< PORT P1_DIR: P3 (Bit 3)                               */
#define PORT_P1_DIR_P3_Msk                (0x8UL)                   /*!< PORT P1_DIR: P3 (Bitfield-Mask: 0x01)                 */
#define PORT_P1_DIR_P4_Pos                (4UL)                     /*!< PORT P1_DIR: P4 (Bit 4)                               */
#define PORT_P1_DIR_P4_Msk                (0x10UL)                  /*!< PORT P1_DIR: P4 (Bitfield-Mask: 0x01)                 */
/* =========================================================  P1_OD  ========================================================= */
#define PORT_P1_OD_P0_Pos                 (1UL)                     /*!< PORT P1_OD: P0 (Bit 1)                                */
#define PORT_P1_OD_P0_Msk                 (0x2UL)                   /*!< PORT P1_OD: P0 (Bitfield-Mask: 0x01)                  */
#define PORT_P1_OD_P1_Pos                 (2UL)                     /*!< PORT P1_OD: P1 (Bit 2)                                */
#define PORT_P1_OD_P1_Msk                 (0x4UL)                   /*!< PORT P1_OD: P1 (Bitfield-Mask: 0x01)                  */
#define PORT_P1_OD_P3_P2_Pos              (3UL)                     /*!< PORT P1_OD: P3_P2 (Bit 3)                             */
#define PORT_P1_OD_P3_P2_Msk              (0x8UL)                   /*!< PORT P1_OD: P3_P2 (Bitfield-Mask: 0x01)               */
#define PORT_P1_OD_P4_Pos                 (4UL)                     /*!< PORT P1_OD: P4 (Bit 4)                                */
#define PORT_P1_OD_P4_Msk                 (0x10UL)                  /*!< PORT P1_OD: P4 (Bitfield-Mask: 0x01)                  */
/* =======================================================  P1_PUDEN  ======================================================== */
#define PORT_P1_PUDEN_P0_Pos              (0UL)                     /*!< PORT P1_PUDEN: P0 (Bit 0)                             */
#define PORT_P1_PUDEN_P0_Msk              (0x1UL)                   /*!< PORT P1_PUDEN: P0 (Bitfield-Mask: 0x01)               */
#define PORT_P1_PUDEN_P1_Pos              (1UL)                     /*!< PORT P1_PUDEN: P1 (Bit 1)                             */
#define PORT_P1_PUDEN_P1_Msk              (0x2UL)                   /*!< PORT P1_PUDEN: P1 (Bitfield-Mask: 0x01)               */
#define PORT_P1_PUDEN_P2_Pos              (2UL)                     /*!< PORT P1_PUDEN: P2 (Bit 2)                             */
#define PORT_P1_PUDEN_P2_Msk              (0x4UL)                   /*!< PORT P1_PUDEN: P2 (Bitfield-Mask: 0x01)               */
#define PORT_P1_PUDEN_P3_Pos              (3UL)                     /*!< PORT P1_PUDEN: P3 (Bit 3)                             */
#define PORT_P1_PUDEN_P3_Msk              (0x8UL)                   /*!< PORT P1_PUDEN: P3 (Bitfield-Mask: 0x01)               */
#define PORT_P1_PUDEN_P4_Pos              (4UL)                     /*!< PORT P1_PUDEN: P4 (Bit 4)                             */
#define PORT_P1_PUDEN_P4_Msk              (0x10UL)                  /*!< PORT P1_PUDEN: P4 (Bitfield-Mask: 0x01)               */
/* =======================================================  P1_PUDSEL  ======================================================= */
#define PORT_P1_PUDSEL_P0_Pos             (0UL)                     /*!< PORT P1_PUDSEL: P0 (Bit 0)                            */
#define PORT_P1_PUDSEL_P0_Msk             (0x1UL)                   /*!< PORT P1_PUDSEL: P0 (Bitfield-Mask: 0x01)              */
#define PORT_P1_PUDSEL_P1_Pos             (1UL)                     /*!< PORT P1_PUDSEL: P1 (Bit 1)                            */
#define PORT_P1_PUDSEL_P1_Msk             (0x2UL)                   /*!< PORT P1_PUDSEL: P1 (Bitfield-Mask: 0x01)              */
#define PORT_P1_PUDSEL_P2_Pos             (2UL)                     /*!< PORT P1_PUDSEL: P2 (Bit 2)                            */
#define PORT_P1_PUDSEL_P2_Msk             (0x4UL)                   /*!< PORT P1_PUDSEL: P2 (Bitfield-Mask: 0x01)              */
#define PORT_P1_PUDSEL_P3_Pos             (3UL)                     /*!< PORT P1_PUDSEL: P3 (Bit 3)                            */
#define PORT_P1_PUDSEL_P3_Msk             (0x8UL)                   /*!< PORT P1_PUDSEL: P3 (Bitfield-Mask: 0x01)              */
#define PORT_P1_PUDSEL_P4_Pos             (4UL)                     /*!< PORT P1_PUDSEL: P4 (Bit 4)                            */
#define PORT_P1_PUDSEL_P4_Msk             (0x10UL)                  /*!< PORT P1_PUDSEL: P4 (Bitfield-Mask: 0x01)              */
/* ========================================================  P2_DATA  ======================================================== */
#define PORT_P2_DATA_P0_Pos               (0UL)                     /*!< PORT P2_DATA: P0 (Bit 0)                              */
#define PORT_P2_DATA_P0_Msk               (0x1UL)                   /*!< PORT P2_DATA: P0 (Bitfield-Mask: 0x01)                */
#define PORT_P2_DATA_P2_Pos               (2UL)                     /*!< PORT P2_DATA: P2 (Bit 2)                              */
#define PORT_P2_DATA_P2_Msk               (0x4UL)                   /*!< PORT P2_DATA: P2 (Bitfield-Mask: 0x01)                */
#define PORT_P2_DATA_P3_Pos               (3UL)                     /*!< PORT P2_DATA: P3 (Bit 3)                              */
#define PORT_P2_DATA_P3_Msk               (0x8UL)                   /*!< PORT P2_DATA: P3 (Bitfield-Mask: 0x01)                */
#define PORT_P2_DATA_P4_Pos               (4UL)                     /*!< PORT P2_DATA: P4 (Bit 4)                              */
#define PORT_P2_DATA_P4_Msk               (0x10UL)                  /*!< PORT P2_DATA: P4 (Bitfield-Mask: 0x01)                */
#define PORT_P2_DATA_P5_Pos               (5UL)                     /*!< PORT P2_DATA: P5 (Bit 5)                              */
#define PORT_P2_DATA_P5_Msk               (0x20UL)                  /*!< PORT P2_DATA: P5 (Bitfield-Mask: 0x01)                */
/* ========================================================  P2_DIR  ========================================================= */
#define PORT_P2_DIR_P0_Pos                (0UL)                     /*!< PORT P2_DIR: P0 (Bit 0)                               */
#define PORT_P2_DIR_P0_Msk                (0x1UL)                   /*!< PORT P2_DIR: P0 (Bitfield-Mask: 0x01)                 */
#define PORT_P2_DIR_P2_Pos                (2UL)                     /*!< PORT P2_DIR: P2 (Bit 2)                               */
#define PORT_P2_DIR_P2_Msk                (0x4UL)                   /*!< PORT P2_DIR: P2 (Bitfield-Mask: 0x01)                 */
#define PORT_P2_DIR_P3_Pos                (3UL)                     /*!< PORT P2_DIR: P3 (Bit 3)                               */
#define PORT_P2_DIR_P3_Msk                (0x8UL)                   /*!< PORT P2_DIR: P3 (Bitfield-Mask: 0x01)                 */
#define PORT_P2_DIR_P4_Pos                (4UL)                     /*!< PORT P2_DIR: P4 (Bit 4)                               */
#define PORT_P2_DIR_P4_Msk                (0x10UL)                  /*!< PORT P2_DIR: P4 (Bitfield-Mask: 0x01)                 */
#define PORT_P2_DIR_P5_Pos                (5UL)                     /*!< PORT P2_DIR: P5 (Bit 5)                               */
#define PORT_P2_DIR_P5_Msk                (0x20UL)                  /*!< PORT P2_DIR: P5 (Bitfield-Mask: 0x01)                 */
/* =======================================================  P2_PUDEN  ======================================================== */
#define PORT_P2_PUDEN_P0_Pos              (0UL)                     /*!< PORT P2_PUDEN: P0 (Bit 0)                             */
#define PORT_P2_PUDEN_P0_Msk              (0x1UL)                   /*!< PORT P2_PUDEN: P0 (Bitfield-Mask: 0x01)               */
#define PORT_P2_PUDEN_P2_Pos              (2UL)                     /*!< PORT P2_PUDEN: P2 (Bit 2)                             */
#define PORT_P2_PUDEN_P2_Msk              (0x4UL)                   /*!< PORT P2_PUDEN: P2 (Bitfield-Mask: 0x01)               */
#define PORT_P2_PUDEN_P3_Pos              (3UL)                     /*!< PORT P2_PUDEN: P3 (Bit 3)                             */
#define PORT_P2_PUDEN_P3_Msk              (0x8UL)                   /*!< PORT P2_PUDEN: P3 (Bitfield-Mask: 0x01)               */
#define PORT_P2_PUDEN_P4_Pos              (4UL)                     /*!< PORT P2_PUDEN: P4 (Bit 4)                             */
#define PORT_P2_PUDEN_P4_Msk              (0x10UL)                  /*!< PORT P2_PUDEN: P4 (Bitfield-Mask: 0x01)               */
#define PORT_P2_PUDEN_P5_Pos              (5UL)                     /*!< PORT P2_PUDEN: P5 (Bit 5)                             */
#define PORT_P2_PUDEN_P5_Msk              (0x20UL)                  /*!< PORT P2_PUDEN: P5 (Bitfield-Mask: 0x01)               */
/* =======================================================  P2_PUDSEL  ======================================================= */
#define PORT_P2_PUDSEL_P0_Pos             (0UL)                     /*!< PORT P2_PUDSEL: P0 (Bit 0)                            */
#define PORT_P2_PUDSEL_P0_Msk             (0x1UL)                   /*!< PORT P2_PUDSEL: P0 (Bitfield-Mask: 0x01)              */
#define PORT_P2_PUDSEL_P2_Pos             (2UL)                     /*!< PORT P2_PUDSEL: P2 (Bit 2)                            */
#define PORT_P2_PUDSEL_P2_Msk             (0x4UL)                   /*!< PORT P2_PUDSEL: P2 (Bitfield-Mask: 0x01)              */
#define PORT_P2_PUDSEL_P3_Pos             (3UL)                     /*!< PORT P2_PUDSEL: P3 (Bit 3)                            */
#define PORT_P2_PUDSEL_P3_Msk             (0x8UL)                   /*!< PORT P2_PUDSEL: P3 (Bitfield-Mask: 0x01)              */
#define PORT_P2_PUDSEL_P4_Pos             (4UL)                     /*!< PORT P2_PUDSEL: P4 (Bit 4)                            */
#define PORT_P2_PUDSEL_P4_Msk             (0x10UL)                  /*!< PORT P2_PUDSEL: P4 (Bitfield-Mask: 0x01)              */
#define PORT_P2_PUDSEL_P5_Pos             (5UL)                     /*!< PORT P2_PUDSEL: P5 (Bit 5)                            */
#define PORT_P2_PUDSEL_P5_Msk             (0x20UL)                  /*!< PORT P2_PUDSEL: P5 (Bitfield-Mask: 0x01)              */


/* =========================================================================================================================== */
/* ================                                            SCU                                            ================ */
/* =========================================================================================================================== */

/* ========================================================  APCLK1  ========================================================= */
#define SCU_APCLK1_APCLK3SCLR_Pos         (7UL)                     /*!< SCU APCLK1: APCLK3SCLR (Bit 7)                        */
#define SCU_APCLK1_APCLK3SCLR_Msk         (0x80UL)                  /*!< SCU APCLK1: APCLK3SCLR (Bitfield-Mask: 0x01)          */
#define SCU_APCLK1_APCLK3STS_Pos          (6UL)                     /*!< SCU APCLK1: APCLK3STS (Bit 6)                         */
#define SCU_APCLK1_APCLK3STS_Msk          (0x40UL)                  /*!< SCU APCLK1: APCLK3STS (Bitfield-Mask: 0x01)           */
#define SCU_APCLK1_APCLK1STS_Pos          (4UL)                     /*!< SCU APCLK1: APCLK1STS (Bit 4)                         */
#define SCU_APCLK1_APCLK1STS_Msk          (0x30UL)                  /*!< SCU APCLK1: APCLK1STS (Bitfield-Mask: 0x03)           */
#define SCU_APCLK1_APCLK1SCLR_Pos         (2UL)                     /*!< SCU APCLK1: APCLK1SCLR (Bit 2)                        */
#define SCU_APCLK1_APCLK1SCLR_Msk         (0x4UL)                   /*!< SCU APCLK1: APCLK1SCLR (Bitfield-Mask: 0x01)          */
#define SCU_APCLK1_APCLK1FAC_Pos          (0UL)                     /*!< SCU APCLK1: APCLK1FAC (Bit 0)                         */
#define SCU_APCLK1_APCLK1FAC_Msk          (0x3UL)                   /*!< SCU APCLK1: APCLK1FAC (Bitfield-Mask: 0x03)           */
/* ========================================================  APCLK2  ========================================================= */
#define SCU_APCLK2_APCLK2SCLR_Pos         (7UL)                     /*!< SCU APCLK2: APCLK2SCLR (Bit 7)                        */
#define SCU_APCLK2_APCLK2SCLR_Msk         (0x80UL)                  /*!< SCU APCLK2: APCLK2SCLR (Bitfield-Mask: 0x01)          */
#define SCU_APCLK2_APCLK2STS_Pos          (5UL)                     /*!< SCU APCLK2: APCLK2STS (Bit 5)                         */
#define SCU_APCLK2_APCLK2STS_Msk          (0x60UL)                  /*!< SCU APCLK2: APCLK2STS (Bitfield-Mask: 0x03)           */
#define SCU_APCLK2_APCLK2FAC_Pos          (0UL)                     /*!< SCU APCLK2: APCLK2FAC (Bit 0)                         */
#define SCU_APCLK2_APCLK2FAC_Msk          (0x1fUL)                  /*!< SCU APCLK2: APCLK2FAC (Bitfield-Mask: 0x1f)           */
/* ======================================================  APCLK_CTRL1  ====================================================== */
#define SCU_APCLK_CTRL1_CPCLK_DIV_Pos     (7UL)                     /*!< SCU APCLK_CTRL1: CPCLK_DIV (Bit 7)                    */
#define SCU_APCLK_CTRL1_CPCLK_DIV_Msk     (0x80UL)                  /*!< SCU APCLK_CTRL1: CPCLK_DIV (Bitfield-Mask: 0x01)      */
#define SCU_APCLK_CTRL1_CPCLK_SEL_Pos     (6UL)                     /*!< SCU APCLK_CTRL1: CPCLK_SEL (Bit 6)                    */
#define SCU_APCLK_CTRL1_CPCLK_SEL_Msk     (0x40UL)                  /*!< SCU APCLK_CTRL1: CPCLK_SEL (Bitfield-Mask: 0x01)      */
#define SCU_APCLK_CTRL1_BGCLK_DIV_Pos     (5UL)                     /*!< SCU APCLK_CTRL1: BGCLK_DIV (Bit 5)                    */
#define SCU_APCLK_CTRL1_BGCLK_DIV_Msk     (0x20UL)                  /*!< SCU APCLK_CTRL1: BGCLK_DIV (Bitfield-Mask: 0x01)      */
#define SCU_APCLK_CTRL1_BGCLK_SEL_Pos     (4UL)                     /*!< SCU APCLK_CTRL1: BGCLK_SEL (Bit 4)                    */
#define SCU_APCLK_CTRL1_BGCLK_SEL_Msk     (0x10UL)                  /*!< SCU APCLK_CTRL1: BGCLK_SEL (Bitfield-Mask: 0x01)      */
#define SCU_APCLK_CTRL1_CLKWDT_IE_Pos     (3UL)                     /*!< SCU APCLK_CTRL1: CLKWDT_IE (Bit 3)                    */
#define SCU_APCLK_CTRL1_CLKWDT_IE_Msk     (0x8UL)                   /*!< SCU APCLK_CTRL1: CLKWDT_IE (Bitfield-Mask: 0x01)      */
#define SCU_APCLK_CTRL1_T3CLK_SEL_Pos     (2UL)                     /*!< SCU APCLK_CTRL1: T3CLK_SEL (Bit 2)                    */
#define SCU_APCLK_CTRL1_T3CLK_SEL_Msk     (0x4UL)                   /*!< SCU APCLK_CTRL1: T3CLK_SEL (Bitfield-Mask: 0x01)      */
#define SCU_APCLK_CTRL1_APCLK_SET_Pos     (1UL)                     /*!< SCU APCLK_CTRL1: APCLK_SET (Bit 1)                    */
#define SCU_APCLK_CTRL1_APCLK_SET_Msk     (0x2UL)                   /*!< SCU APCLK_CTRL1: APCLK_SET (Bitfield-Mask: 0x01)      */
#define SCU_APCLK_CTRL1_PLL_LOCK_Pos      (0UL)                     /*!< SCU APCLK_CTRL1: PLL_LOCK (Bit 0)                     */
#define SCU_APCLK_CTRL1_PLL_LOCK_Msk      (0x1UL)                   /*!< SCU APCLK_CTRL1: PLL_LOCK (Bitfield-Mask: 0x01)       */
/* ======================================================  APCLK_CTRL2  ====================================================== */
#define SCU_APCLK_CTRL2_T3CLK_DIV_Pos     (2UL)                     /*!< SCU APCLK_CTRL2: T3CLK_DIV (Bit 2)                    */
#define SCU_APCLK_CTRL2_T3CLK_DIV_Msk     (0xcUL)                   /*!< SCU APCLK_CTRL2: T3CLK_DIV (Bitfield-Mask: 0x03)      */
#define SCU_APCLK_CTRL2_SDADCCLK_DIV_Pos  (0UL)                     /*!< SCU APCLK_CTRL2: SDADCCLK_DIV (Bit 0)                 */
#define SCU_APCLK_CTRL2_SDADCCLK_DIV_Msk  (0x3UL)                   /*!< SCU APCLK_CTRL2: SDADCCLK_DIV (Bitfield-Mask: 0x03)   */
/* =========================================================  BCON1  ========================================================= */
#define SCU_BCON1_R_Pos                   (0UL)                     /*!< SCU BCON1: R (Bit 0)                                  */
#define SCU_BCON1_R_Msk                   (0x1UL)                   /*!< SCU BCON1: R (Bitfield-Mask: 0x01)                    */
#define SCU_BCON1_BRPRE_Pos               (1UL)                     /*!< SCU BCON1: BRPRE (Bit 1)                              */
#define SCU_BCON1_BRPRE_Msk               (0xeUL)                   /*!< SCU BCON1: BRPRE (Bitfield-Mask: 0x07)                */
/* =========================================================  BCON2  ========================================================= */
#define SCU_BCON2_R_Pos                   (0UL)                     /*!< SCU BCON2: R (Bit 0)                                  */
#define SCU_BCON2_R_Msk                   (0x1UL)                   /*!< SCU BCON2: R (Bitfield-Mask: 0x01)                    */
#define SCU_BCON2_BRPRE_Pos               (1UL)                     /*!< SCU BCON2: BRPRE (Bit 1)                              */
#define SCU_BCON2_BRPRE_Msk               (0xeUL)                   /*!< SCU BCON2: BRPRE (Bitfield-Mask: 0x07)                */
/* =========================================================  BGH1  ========================================================== */
#define SCU_BGH1_BR_VALUE_Pos             (0UL)                     /*!< SCU BGH1: BR_VALUE (Bit 0)                            */
#define SCU_BGH1_BR_VALUE_Msk             (0xffUL)                  /*!< SCU BGH1: BR_VALUE (Bitfield-Mask: 0xff)              */
/* =========================================================  BGH2  ========================================================== */
#define SCU_BGH2_BR_VALUE_Pos             (0UL)                     /*!< SCU BGH2: BR_VALUE (Bit 0)                            */
#define SCU_BGH2_BR_VALUE_Msk             (0xffUL)                  /*!< SCU BGH2: BR_VALUE (Bitfield-Mask: 0xff)              */
/* =========================================================  BGL1  ========================================================== */
#define SCU_BGL1_FD_SEL_Pos               (0UL)                     /*!< SCU BGL1: FD_SEL (Bit 0)                              */
#define SCU_BGL1_FD_SEL_Msk               (0x1fUL)                  /*!< SCU BGL1: FD_SEL (Bitfield-Mask: 0x1f)                */
#define SCU_BGL1_BR_VALUE_Pos             (5UL)                     /*!< SCU BGL1: BR_VALUE (Bit 5)                            */
#define SCU_BGL1_BR_VALUE_Msk             (0xe0UL)                  /*!< SCU BGL1: BR_VALUE (Bitfield-Mask: 0x07)              */
/* =========================================================  BGL2  ========================================================== */
#define SCU_BGL2_FD_SEL_Pos               (0UL)                     /*!< SCU BGL2: FD_SEL (Bit 0)                              */
#define SCU_BGL2_FD_SEL_Msk               (0x1fUL)                  /*!< SCU BGL2: FD_SEL (Bitfield-Mask: 0x1f)                */
#define SCU_BGL2_BR_VALUE_Pos             (5UL)                     /*!< SCU BGL2: BR_VALUE (Bit 5)                            */
#define SCU_BGL2_BR_VALUE_Msk             (0xe0UL)                  /*!< SCU BGL2: BR_VALUE (Bitfield-Mask: 0x07)              */
/* ========================================================  CMCON1  ========================================================= */
#define SCU_CMCON1_VCOSEL_Pos             (7UL)                     /*!< SCU CMCON1: VCOSEL (Bit 7)                            */
#define SCU_CMCON1_VCOSEL_Msk             (0x80UL)                  /*!< SCU CMCON1: VCOSEL (Bitfield-Mask: 0x01)              */
#define SCU_CMCON1_K1DIV_Pos              (6UL)                     /*!< SCU CMCON1: K1DIV (Bit 6)                             */
#define SCU_CMCON1_K1DIV_Msk              (0x40UL)                  /*!< SCU CMCON1: K1DIV (Bitfield-Mask: 0x01)               */
#define SCU_CMCON1_K2DIV_Pos              (4UL)                     /*!< SCU CMCON1: K2DIV (Bit 4)                             */
#define SCU_CMCON1_K2DIV_Msk              (0x30UL)                  /*!< SCU CMCON1: K2DIV (Bitfield-Mask: 0x03)               */
#define SCU_CMCON1_CLKREL_Pos             (0UL)                     /*!< SCU CMCON1: CLKREL (Bit 0)                            */
#define SCU_CMCON1_CLKREL_Msk             (0xfUL)                   /*!< SCU CMCON1: CLKREL (Bitfield-Mask: 0x0f)              */
/* ========================================================  CMCON2  ========================================================= */
#define SCU_CMCON2_PBA0CLKREL_Pos         (0UL)                     /*!< SCU CMCON2: PBA0CLKREL (Bit 0)                        */
#define SCU_CMCON2_PBA0CLKREL_Msk         (0x1UL)                   /*!< SCU CMCON2: PBA0CLKREL (Bitfield-Mask: 0x01)          */
/* =========================================================  COCON  ========================================================= */
#define SCU_COCON_EN_Pos                  (7UL)                     /*!< SCU COCON: EN (Bit 7)                                 */
#define SCU_COCON_EN_Msk                  (0x80UL)                  /*!< SCU COCON: EN (Bitfield-Mask: 0x01)                   */
#define SCU_COCON_COUTS1_Pos              (6UL)                     /*!< SCU COCON: COUTS1 (Bit 6)                             */
#define SCU_COCON_COUTS1_Msk              (0x40UL)                  /*!< SCU COCON: COUTS1 (Bitfield-Mask: 0x01)               */
#define SCU_COCON_TLEN_Pos                (5UL)                     /*!< SCU COCON: TLEN (Bit 5)                               */
#define SCU_COCON_TLEN_Msk                (0x20UL)                  /*!< SCU COCON: TLEN (Bitfield-Mask: 0x01)                 */
#define SCU_COCON_COUTS0_Pos              (4UL)                     /*!< SCU COCON: COUTS0 (Bit 4)                             */
#define SCU_COCON_COUTS0_Msk              (0x10UL)                  /*!< SCU COCON: COUTS0 (Bitfield-Mask: 0x01)               */
#define SCU_COCON_COREL_Pos               (0UL)                     /*!< SCU COCON: COREL (Bit 0)                              */
#define SCU_COCON_COREL_Msk               (0xfUL)                   /*!< SCU COCON: COREL (Bitfield-Mask: 0x0f)                */
/* ========================================================  DMAIEN1  ======================================================== */
#define SCU_DMAIEN1_CH8IE_Pos             (7UL)                     /*!< SCU DMAIEN1: CH8IE (Bit 7)                            */
#define SCU_DMAIEN1_CH8IE_Msk             (0x80UL)                  /*!< SCU DMAIEN1: CH8IE (Bitfield-Mask: 0x01)              */
#define SCU_DMAIEN1_CH7IE_Pos             (6UL)                     /*!< SCU DMAIEN1: CH7IE (Bit 6)                            */
#define SCU_DMAIEN1_CH7IE_Msk             (0x40UL)                  /*!< SCU DMAIEN1: CH7IE (Bitfield-Mask: 0x01)              */
#define SCU_DMAIEN1_CH6IE_Pos             (5UL)                     /*!< SCU DMAIEN1: CH6IE (Bit 5)                            */
#define SCU_DMAIEN1_CH6IE_Msk             (0x20UL)                  /*!< SCU DMAIEN1: CH6IE (Bitfield-Mask: 0x01)              */
#define SCU_DMAIEN1_CH5IE_Pos             (4UL)                     /*!< SCU DMAIEN1: CH5IE (Bit 4)                            */
#define SCU_DMAIEN1_CH5IE_Msk             (0x10UL)                  /*!< SCU DMAIEN1: CH5IE (Bitfield-Mask: 0x01)              */
#define SCU_DMAIEN1_CH4IE_Pos             (3UL)                     /*!< SCU DMAIEN1: CH4IE (Bit 3)                            */
#define SCU_DMAIEN1_CH4IE_Msk             (0x8UL)                   /*!< SCU DMAIEN1: CH4IE (Bitfield-Mask: 0x01)              */
#define SCU_DMAIEN1_CH3IE_Pos             (2UL)                     /*!< SCU DMAIEN1: CH3IE (Bit 2)                            */
#define SCU_DMAIEN1_CH3IE_Msk             (0x4UL)                   /*!< SCU DMAIEN1: CH3IE (Bitfield-Mask: 0x01)              */
#define SCU_DMAIEN1_CH2IE_Pos             (1UL)                     /*!< SCU DMAIEN1: CH2IE (Bit 1)                            */
#define SCU_DMAIEN1_CH2IE_Msk             (0x2UL)                   /*!< SCU DMAIEN1: CH2IE (Bitfield-Mask: 0x01)              */
#define SCU_DMAIEN1_CH1IE_Pos             (0UL)                     /*!< SCU DMAIEN1: CH1IE (Bit 0)                            */
#define SCU_DMAIEN1_CH1IE_Msk             (0x1UL)                   /*!< SCU DMAIEN1: CH1IE (Bitfield-Mask: 0x01)              */
/* ========================================================  DMAIEN2  ======================================================== */
#define SCU_DMAIEN2_SDADCIE_Pos           (6UL)                     /*!< SCU DMAIEN2: SDADCIE (Bit 6)                          */
#define SCU_DMAIEN2_SDADCIE_Msk           (0x40UL)                  /*!< SCU DMAIEN2: SDADCIE (Bitfield-Mask: 0x01)            */
#define SCU_DMAIEN2_GPT12IE_Pos           (5UL)                     /*!< SCU DMAIEN2: GPT12IE (Bit 5)                          */
#define SCU_DMAIEN2_GPT12IE_Msk           (0x20UL)                  /*!< SCU DMAIEN2: GPT12IE (Bitfield-Mask: 0x01)            */
#define SCU_DMAIEN2_SSCRXIE_Pos           (4UL)                     /*!< SCU DMAIEN2: SSCRXIE (Bit 4)                          */
#define SCU_DMAIEN2_SSCRXIE_Msk           (0x10UL)                  /*!< SCU DMAIEN2: SSCRXIE (Bitfield-Mask: 0x01)            */
#define SCU_DMAIEN2_SSCTXIE_Pos           (3UL)                     /*!< SCU DMAIEN2: SSCTXIE (Bit 3)                          */
#define SCU_DMAIEN2_SSCTXIE_Msk           (0x8UL)                   /*!< SCU DMAIEN2: SSCTXIE (Bitfield-Mask: 0x01)            */
#define SCU_DMAIEN2_TRSEQ2RDYIE_Pos       (2UL)                     /*!< SCU DMAIEN2: TRSEQ2RDYIE (Bit 2)                      */
#define SCU_DMAIEN2_TRSEQ2RDYIE_Msk       (0x4UL)                   /*!< SCU DMAIEN2: TRSEQ2RDYIE (Bitfield-Mask: 0x01)        */
#define SCU_DMAIEN2_TRSEQ1RDYIE_Pos       (1UL)                     /*!< SCU DMAIEN2: TRSEQ1RDYIE (Bit 1)                      */
#define SCU_DMAIEN2_TRSEQ1RDYIE_Msk       (0x2UL)                   /*!< SCU DMAIEN2: TRSEQ1RDYIE (Bitfield-Mask: 0x01)        */
#define SCU_DMAIEN2_TRERRIE_Pos           (0UL)                     /*!< SCU DMAIEN2: TRERRIE (Bit 0)                          */
#define SCU_DMAIEN2_TRERRIE_Msk           (0x1UL)                   /*!< SCU DMAIEN2: TRERRIE (Bitfield-Mask: 0x01)            */
/* ========================================================  DMAIRC1  ======================================================== */
#define SCU_DMAIRC1_CH8_Pos               (7UL)                     /*!< SCU DMAIRC1: CH8 (Bit 7)                              */
#define SCU_DMAIRC1_CH8_Msk               (0x80UL)                  /*!< SCU DMAIRC1: CH8 (Bitfield-Mask: 0x01)                */
#define SCU_DMAIRC1_CH7_Pos               (6UL)                     /*!< SCU DMAIRC1: CH7 (Bit 6)                              */
#define SCU_DMAIRC1_CH7_Msk               (0x40UL)                  /*!< SCU DMAIRC1: CH7 (Bitfield-Mask: 0x01)                */
#define SCU_DMAIRC1_CH6_Pos               (5UL)                     /*!< SCU DMAIRC1: CH6 (Bit 5)                              */
#define SCU_DMAIRC1_CH6_Msk               (0x20UL)                  /*!< SCU DMAIRC1: CH6 (Bitfield-Mask: 0x01)                */
#define SCU_DMAIRC1_CH5_Pos               (4UL)                     /*!< SCU DMAIRC1: CH5 (Bit 4)                              */
#define SCU_DMAIRC1_CH5_Msk               (0x10UL)                  /*!< SCU DMAIRC1: CH5 (Bitfield-Mask: 0x01)                */
#define SCU_DMAIRC1_CH4_Pos               (3UL)                     /*!< SCU DMAIRC1: CH4 (Bit 3)                              */
#define SCU_DMAIRC1_CH4_Msk               (0x8UL)                   /*!< SCU DMAIRC1: CH4 (Bitfield-Mask: 0x01)                */
#define SCU_DMAIRC1_CH3_Pos               (2UL)                     /*!< SCU DMAIRC1: CH3 (Bit 2)                              */
#define SCU_DMAIRC1_CH3_Msk               (0x4UL)                   /*!< SCU DMAIRC1: CH3 (Bitfield-Mask: 0x01)                */
#define SCU_DMAIRC1_CH2_Pos               (1UL)                     /*!< SCU DMAIRC1: CH2 (Bit 1)                              */
#define SCU_DMAIRC1_CH2_Msk               (0x2UL)                   /*!< SCU DMAIRC1: CH2 (Bitfield-Mask: 0x01)                */
#define SCU_DMAIRC1_CH1_Pos               (0UL)                     /*!< SCU DMAIRC1: CH1 (Bit 0)                              */
#define SCU_DMAIRC1_CH1_Msk               (0x1UL)                   /*!< SCU DMAIRC1: CH1 (Bitfield-Mask: 0x01)                */
/* ======================================================  DMAIRC1CLR  ======================================================= */
#define SCU_DMAIRC1CLR_CH8C_Pos           (7UL)                     /*!< SCU DMAIRC1CLR: CH8C (Bit 7)                          */
#define SCU_DMAIRC1CLR_CH8C_Msk           (0x80UL)                  /*!< SCU DMAIRC1CLR: CH8C (Bitfield-Mask: 0x01)            */
#define SCU_DMAIRC1CLR_CH7C_Pos           (6UL)                     /*!< SCU DMAIRC1CLR: CH7C (Bit 6)                          */
#define SCU_DMAIRC1CLR_CH7C_Msk           (0x40UL)                  /*!< SCU DMAIRC1CLR: CH7C (Bitfield-Mask: 0x01)            */
#define SCU_DMAIRC1CLR_CH6C_Pos           (5UL)                     /*!< SCU DMAIRC1CLR: CH6C (Bit 5)                          */
#define SCU_DMAIRC1CLR_CH6C_Msk           (0x20UL)                  /*!< SCU DMAIRC1CLR: CH6C (Bitfield-Mask: 0x01)            */
#define SCU_DMAIRC1CLR_CH5C_Pos           (4UL)                     /*!< SCU DMAIRC1CLR: CH5C (Bit 4)                          */
#define SCU_DMAIRC1CLR_CH5C_Msk           (0x10UL)                  /*!< SCU DMAIRC1CLR: CH5C (Bitfield-Mask: 0x01)            */
#define SCU_DMAIRC1CLR_CH4C_Pos           (3UL)                     /*!< SCU DMAIRC1CLR: CH4C (Bit 3)                          */
#define SCU_DMAIRC1CLR_CH4C_Msk           (0x8UL)                   /*!< SCU DMAIRC1CLR: CH4C (Bitfield-Mask: 0x01)            */
#define SCU_DMAIRC1CLR_CH3C_Pos           (2UL)                     /*!< SCU DMAIRC1CLR: CH3C (Bit 2)                          */
#define SCU_DMAIRC1CLR_CH3C_Msk           (0x4UL)                   /*!< SCU DMAIRC1CLR: CH3C (Bitfield-Mask: 0x01)            */
#define SCU_DMAIRC1CLR_CH2C_Pos           (1UL)                     /*!< SCU DMAIRC1CLR: CH2C (Bit 1)                          */
#define SCU_DMAIRC1CLR_CH2C_Msk           (0x2UL)                   /*!< SCU DMAIRC1CLR: CH2C (Bitfield-Mask: 0x01)            */
#define SCU_DMAIRC1CLR_CH1C_Pos           (0UL)                     /*!< SCU DMAIRC1CLR: CH1C (Bit 0)                          */
#define SCU_DMAIRC1CLR_CH1C_Msk           (0x1UL)                   /*!< SCU DMAIRC1CLR: CH1C (Bitfield-Mask: 0x01)            */
/* ========================================================  DMAIRC2  ======================================================== */
#define SCU_DMAIRC2_SDADC_Pos             (6UL)                     /*!< SCU DMAIRC2: SDADC (Bit 6)                            */
#define SCU_DMAIRC2_SDADC_Msk             (0x40UL)                  /*!< SCU DMAIRC2: SDADC (Bitfield-Mask: 0x01)              */
#define SCU_DMAIRC2_GPT12_Pos             (5UL)                     /*!< SCU DMAIRC2: GPT12 (Bit 5)                            */
#define SCU_DMAIRC2_GPT12_Msk             (0x20UL)                  /*!< SCU DMAIRC2: GPT12 (Bitfield-Mask: 0x01)              */
#define SCU_DMAIRC2_SSC2RDY_Pos           (4UL)                     /*!< SCU DMAIRC2: SSC2RDY (Bit 4)                          */
#define SCU_DMAIRC2_SSC2RDY_Msk           (0x10UL)                  /*!< SCU DMAIRC2: SSC2RDY (Bitfield-Mask: 0x01)            */
#define SCU_DMAIRC2_SSC1RDY_Pos           (3UL)                     /*!< SCU DMAIRC2: SSC1RDY (Bit 3)                          */
#define SCU_DMAIRC2_SSC1RDY_Msk           (0x8UL)                   /*!< SCU DMAIRC2: SSC1RDY (Bitfield-Mask: 0x01)            */
#define SCU_DMAIRC2_TRSEQ2DY_Pos          (2UL)                     /*!< SCU DMAIRC2: TRSEQ2DY (Bit 2)                         */
#define SCU_DMAIRC2_TRSEQ2DY_Msk          (0x4UL)                   /*!< SCU DMAIRC2: TRSEQ2DY (Bitfield-Mask: 0x01)           */
#define SCU_DMAIRC2_TRSEQ1DY_Pos          (1UL)                     /*!< SCU DMAIRC2: TRSEQ1DY (Bit 1)                         */
#define SCU_DMAIRC2_TRSEQ1DY_Msk          (0x2UL)                   /*!< SCU DMAIRC2: TRSEQ1DY (Bitfield-Mask: 0x01)           */
#define SCU_DMAIRC2_STRDY_Pos             (0UL)                     /*!< SCU DMAIRC2: STRDY (Bit 0)                            */
#define SCU_DMAIRC2_STRDY_Msk             (0x1UL)                   /*!< SCU DMAIRC2: STRDY (Bitfield-Mask: 0x01)              */
/* ======================================================  DMAIRC2CLR  ======================================================= */
#define SCU_DMAIRC2CLR_SDADCC_Pos         (6UL)                     /*!< SCU DMAIRC2CLR: SDADCC (Bit 6)                        */
#define SCU_DMAIRC2CLR_SDADCC_Msk         (0x40UL)                  /*!< SCU DMAIRC2CLR: SDADCC (Bitfield-Mask: 0x01)          */
#define SCU_DMAIRC2CLR_GPT12C_Pos         (5UL)                     /*!< SCU DMAIRC2CLR: GPT12C (Bit 5)                        */
#define SCU_DMAIRC2CLR_GPT12C_Msk         (0x20UL)                  /*!< SCU DMAIRC2CLR: GPT12C (Bitfield-Mask: 0x01)          */
#define SCU_DMAIRC2CLR_SSC2C_Pos          (4UL)                     /*!< SCU DMAIRC2CLR: SSC2C (Bit 4)                         */
#define SCU_DMAIRC2CLR_SSC2C_Msk          (0x10UL)                  /*!< SCU DMAIRC2CLR: SSC2C (Bitfield-Mask: 0x01)           */
#define SCU_DMAIRC2CLR_SSC1C_Pos          (3UL)                     /*!< SCU DMAIRC2CLR: SSC1C (Bit 3)                         */
#define SCU_DMAIRC2CLR_SSC1C_Msk          (0x8UL)                   /*!< SCU DMAIRC2CLR: SSC1C (Bitfield-Mask: 0x01)           */
#define SCU_DMAIRC2CLR_TRSEQ2DYC_Pos      (2UL)                     /*!< SCU DMAIRC2CLR: TRSEQ2DYC (Bit 2)                     */
#define SCU_DMAIRC2CLR_TRSEQ2DYC_Msk      (0x4UL)                   /*!< SCU DMAIRC2CLR: TRSEQ2DYC (Bitfield-Mask: 0x01)       */
#define SCU_DMAIRC2CLR_TRSEQ1DYC_Pos      (1UL)                     /*!< SCU DMAIRC2CLR: TRSEQ1DYC (Bit 1)                     */
#define SCU_DMAIRC2CLR_TRSEQ1DYC_Msk      (0x2UL)                   /*!< SCU DMAIRC2CLR: TRSEQ1DYC (Bitfield-Mask: 0x01)       */
/* =======================================================  DMASRCCLR  ======================================================= */
#define SCU_DMASRCCLR_GPT12_T3C_Pos       (7UL)                     /*!< SCU DMASRCCLR: GPT12_T3C (Bit 7)                      */
#define SCU_DMASRCCLR_GPT12_T3C_Msk       (0x80UL)                  /*!< SCU DMASRCCLR: GPT12_T3C (Bitfield-Mask: 0x01)        */
#define SCU_DMASRCCLR_SSCRXC_Pos          (6UL)                     /*!< SCU DMASRCCLR: SSCRXC (Bit 6)                         */
#define SCU_DMASRCCLR_SSCRXC_Msk          (0x40UL)                  /*!< SCU DMASRCCLR: SSCRXC (Bitfield-Mask: 0x01)           */
#define SCU_DMASRCCLR_SSCTXC_Pos          (5UL)                     /*!< SCU DMASRCCLR: SSCTXC (Bit 5)                         */
#define SCU_DMASRCCLR_SSCTXC_Msk          (0x20UL)                  /*!< SCU DMASRCCLR: SSCTXC (Bitfield-Mask: 0x01)           */
/* =======================================================  DMASRCSEL  ======================================================= */
#define SCU_DMASRCSEL_GPT12_T3_Pos        (7UL)                     /*!< SCU DMASRCSEL: GPT12_T3 (Bit 7)                       */
#define SCU_DMASRCSEL_GPT12_T3_Msk        (0x80UL)                  /*!< SCU DMASRCSEL: GPT12_T3 (Bitfield-Mask: 0x01)         */
#define SCU_DMASRCSEL_SSCRX_Pos           (6UL)                     /*!< SCU DMASRCSEL: SSCRX (Bit 6)                          */
#define SCU_DMASRCSEL_SSCRX_Msk           (0x40UL)                  /*!< SCU DMASRCSEL: SSCRX (Bitfield-Mask: 0x01)            */
#define SCU_DMASRCSEL_SSCTX_Pos           (5UL)                     /*!< SCU DMASRCSEL: SSCTX (Bit 5)                          */
#define SCU_DMASRCSEL_SSCTX_Msk           (0x20UL)                  /*!< SCU DMASRCSEL: SSCTX (Bitfield-Mask: 0x01)            */
#define SCU_DMASRCSEL_T12PM_DMAEN_Pos     (3UL)                     /*!< SCU DMASRCSEL: T12PM_DMAEN (Bit 3)                    */
#define SCU_DMASRCSEL_T12PM_DMAEN_Msk     (0x8UL)                   /*!< SCU DMASRCSEL: T12PM_DMAEN (Bitfield-Mask: 0x01)      */
#define SCU_DMASRCSEL_T12ZM_DMAEN_Pos     (2UL)                     /*!< SCU DMASRCSEL: T12ZM_DMAEN (Bit 2)                    */
#define SCU_DMASRCSEL_T12ZM_DMAEN_Msk     (0x4UL)                   /*!< SCU DMASRCSEL: T12ZM_DMAEN (Bitfield-Mask: 0x01)      */
#define SCU_DMASRCSEL_SSCRXSRCSEL_Pos     (1UL)                     /*!< SCU DMASRCSEL: SSCRXSRCSEL (Bit 1)                    */
#define SCU_DMASRCSEL_SSCRXSRCSEL_Msk     (0x2UL)                   /*!< SCU DMASRCSEL: SSCRXSRCSEL (Bitfield-Mask: 0x01)      */
#define SCU_DMASRCSEL_SSCTXSRCSEL_Pos     (0UL)                     /*!< SCU DMASRCSEL: SSCTXSRCSEL (Bit 0)                    */
#define SCU_DMASRCSEL_SSCTXSRCSEL_Msk     (0x1UL)                   /*!< SCU DMASRCSEL: SSCTXSRCSEL (Bitfield-Mask: 0x01)      */
/* ======================================================  DMASRCSEL2  ======================================================= */
#define SCU_DMASRCSEL2_GPT12_DMAEN_Pos    (0UL)                     /*!< SCU DMASRCSEL2: GPT12_DMAEN (Bit 0)                   */
#define SCU_DMASRCSEL2_GPT12_DMAEN_Msk    (0x3UL)                   /*!< SCU DMASRCSEL2: GPT12_DMAEN (Bitfield-Mask: 0x03)     */
/* ========================================================  EDCCON  ========================================================= */
#define SCU_EDCCON_NVMIE_Pos              (2UL)                     /*!< SCU EDCCON: NVMIE (Bit 2)                             */
#define SCU_EDCCON_NVMIE_Msk              (0x4UL)                   /*!< SCU EDCCON: NVMIE (Bitfield-Mask: 0x01)               */
#define SCU_EDCCON_RIE_Pos                (0UL)                     /*!< SCU EDCCON: RIE (Bit 0)                               */
#define SCU_EDCCON_RIE_Msk                (0x1UL)                   /*!< SCU EDCCON: RIE (Bitfield-Mask: 0x01)                 */
/* ========================================================  EDCSCLR  ======================================================== */
#define SCU_EDCSCLR_RSBEC_Pos             (4UL)                     /*!< SCU EDCSCLR: RSBEC (Bit 4)                            */
#define SCU_EDCSCLR_RSBEC_Msk             (0x10UL)                  /*!< SCU EDCSCLR: RSBEC (Bitfield-Mask: 0x01)              */
#define SCU_EDCSCLR_NVMDBEC_Pos           (2UL)                     /*!< SCU EDCSCLR: NVMDBEC (Bit 2)                          */
#define SCU_EDCSCLR_NVMDBEC_Msk           (0x4UL)                   /*!< SCU EDCSCLR: NVMDBEC (Bitfield-Mask: 0x01)            */
#define SCU_EDCSCLR_RDBEC_Pos             (0UL)                     /*!< SCU EDCSCLR: RDBEC (Bit 0)                            */
#define SCU_EDCSCLR_RDBEC_Msk             (0x1UL)                   /*!< SCU EDCSCLR: RDBEC (Bitfield-Mask: 0x01)              */
/* ========================================================  EDCSTAT  ======================================================== */
#define SCU_EDCSTAT_RSBE_Pos              (4UL)                     /*!< SCU EDCSTAT: RSBE (Bit 4)                             */
#define SCU_EDCSTAT_RSBE_Msk              (0x10UL)                  /*!< SCU EDCSTAT: RSBE (Bitfield-Mask: 0x01)               */
#define SCU_EDCSTAT_NVMDBE_Pos            (2UL)                     /*!< SCU EDCSTAT: NVMDBE (Bit 2)                           */
#define SCU_EDCSTAT_NVMDBE_Msk            (0x4UL)                   /*!< SCU EDCSTAT: NVMDBE (Bitfield-Mask: 0x01)             */
#define SCU_EDCSTAT_RDBE_Pos              (0UL)                     /*!< SCU EDCSTAT: RDBE (Bit 0)                             */
#define SCU_EDCSTAT_RDBE_Msk              (0x1UL)                   /*!< SCU EDCSTAT: RDBE (Bitfield-Mask: 0x01)               */
/* ========================================================  EXICON0  ======================================================== */
#define SCU_EXICON0_MON_Trig_Sel_Pos      (6UL)                     /*!< SCU EXICON0: MON_Trig_Sel (Bit 6)                     */
#define SCU_EXICON0_MON_Trig_Sel_Msk      (0xc0UL)                  /*!< SCU EXICON0: MON_Trig_Sel (Bitfield-Mask: 0x03)       */
#define SCU_EXICON0_EXINT2_Pos            (4UL)                     /*!< SCU EXICON0: EXINT2 (Bit 4)                           */
#define SCU_EXICON0_EXINT2_Msk            (0x30UL)                  /*!< SCU EXICON0: EXINT2 (Bitfield-Mask: 0x03)             */
#define SCU_EXICON0_EXINT1_Pos            (2UL)                     /*!< SCU EXICON0: EXINT1 (Bit 2)                           */
#define SCU_EXICON0_EXINT1_Msk            (0xcUL)                   /*!< SCU EXICON0: EXINT1 (Bitfield-Mask: 0x03)             */
#define SCU_EXICON0_EXINT0_Pos            (0UL)                     /*!< SCU EXICON0: EXINT0 (Bit 0)                           */
#define SCU_EXICON0_EXINT0_Msk            (0x3UL)                   /*!< SCU EXICON0: EXINT0 (Bitfield-Mask: 0x03)             */
/* =======================================================  GPT12ICLR  ======================================================= */
#define SCU_GPT12ICLR_CRC_Pos             (5UL)                     /*!< SCU GPT12ICLR: CRC (Bit 5)                            */
#define SCU_GPT12ICLR_CRC_Msk             (0x20UL)                  /*!< SCU GPT12ICLR: CRC (Bitfield-Mask: 0x01)              */
#define SCU_GPT12ICLR_T6C_Pos             (4UL)                     /*!< SCU GPT12ICLR: T6C (Bit 4)                            */
#define SCU_GPT12ICLR_T6C_Msk             (0x10UL)                  /*!< SCU GPT12ICLR: T6C (Bitfield-Mask: 0x01)              */
#define SCU_GPT12ICLR_T5C_Pos             (3UL)                     /*!< SCU GPT12ICLR: T5C (Bit 3)                            */
#define SCU_GPT12ICLR_T5C_Msk             (0x8UL)                   /*!< SCU GPT12ICLR: T5C (Bitfield-Mask: 0x01)              */
#define SCU_GPT12ICLR_T4C_Pos             (2UL)                     /*!< SCU GPT12ICLR: T4C (Bit 2)                            */
#define SCU_GPT12ICLR_T4C_Msk             (0x4UL)                   /*!< SCU GPT12ICLR: T4C (Bitfield-Mask: 0x01)              */
#define SCU_GPT12ICLR_T3C_Pos             (1UL)                     /*!< SCU GPT12ICLR: T3C (Bit 1)                            */
#define SCU_GPT12ICLR_T3C_Msk             (0x2UL)                   /*!< SCU GPT12ICLR: T3C (Bitfield-Mask: 0x01)              */
#define SCU_GPT12ICLR_T2C_Pos             (0UL)                     /*!< SCU GPT12ICLR: T2C (Bit 0)                            */
#define SCU_GPT12ICLR_T2C_Msk             (0x1UL)                   /*!< SCU GPT12ICLR: T2C (Bitfield-Mask: 0x01)              */
/* =======================================================  GPT12IEN  ======================================================== */
#define SCU_GPT12IEN_CRIE_Pos             (5UL)                     /*!< SCU GPT12IEN: CRIE (Bit 5)                            */
#define SCU_GPT12IEN_CRIE_Msk             (0x20UL)                  /*!< SCU GPT12IEN: CRIE (Bitfield-Mask: 0x01)              */
#define SCU_GPT12IEN_T6IE_Pos             (4UL)                     /*!< SCU GPT12IEN: T6IE (Bit 4)                            */
#define SCU_GPT12IEN_T6IE_Msk             (0x10UL)                  /*!< SCU GPT12IEN: T6IE (Bitfield-Mask: 0x01)              */
#define SCU_GPT12IEN_T5IE_Pos             (3UL)                     /*!< SCU GPT12IEN: T5IE (Bit 3)                            */
#define SCU_GPT12IEN_T5IE_Msk             (0x8UL)                   /*!< SCU GPT12IEN: T5IE (Bitfield-Mask: 0x01)              */
#define SCU_GPT12IEN_T4IE_Pos             (2UL)                     /*!< SCU GPT12IEN: T4IE (Bit 2)                            */
#define SCU_GPT12IEN_T4IE_Msk             (0x4UL)                   /*!< SCU GPT12IEN: T4IE (Bitfield-Mask: 0x01)              */
#define SCU_GPT12IEN_T3IE_Pos             (1UL)                     /*!< SCU GPT12IEN: T3IE (Bit 1)                            */
#define SCU_GPT12IEN_T3IE_Msk             (0x2UL)                   /*!< SCU GPT12IEN: T3IE (Bitfield-Mask: 0x01)              */
#define SCU_GPT12IEN_T2IE_Pos             (0UL)                     /*!< SCU GPT12IEN: T2IE (Bit 0)                            */
#define SCU_GPT12IEN_T2IE_Msk             (0x1UL)                   /*!< SCU GPT12IEN: T2IE (Bitfield-Mask: 0x01)              */
/* =======================================================  GPT12IRC  ======================================================== */
#define SCU_GPT12IRC_CR_Pos               (5UL)                     /*!< SCU GPT12IRC: CR (Bit 5)                              */
#define SCU_GPT12IRC_CR_Msk               (0x20UL)                  /*!< SCU GPT12IRC: CR (Bitfield-Mask: 0x01)                */
#define SCU_GPT12IRC_T6_Pos               (4UL)                     /*!< SCU GPT12IRC: T6 (Bit 4)                              */
#define SCU_GPT12IRC_T6_Msk               (0x10UL)                  /*!< SCU GPT12IRC: T6 (Bitfield-Mask: 0x01)                */
#define SCU_GPT12IRC_T5_Pos               (3UL)                     /*!< SCU GPT12IRC: T5 (Bit 3)                              */
#define SCU_GPT12IRC_T5_Msk               (0x8UL)                   /*!< SCU GPT12IRC: T5 (Bitfield-Mask: 0x01)                */
#define SCU_GPT12IRC_T4_Pos               (2UL)                     /*!< SCU GPT12IRC: T4 (Bit 2)                              */
#define SCU_GPT12IRC_T4_Msk               (0x4UL)                   /*!< SCU GPT12IRC: T4 (Bitfield-Mask: 0x01)                */
#define SCU_GPT12IRC_T3_Pos               (1UL)                     /*!< SCU GPT12IRC: T3 (Bit 1)                              */
#define SCU_GPT12IRC_T3_Msk               (0x2UL)                   /*!< SCU GPT12IRC: T3 (Bitfield-Mask: 0x01)                */
#define SCU_GPT12IRC_T2_Pos               (0UL)                     /*!< SCU GPT12IRC: T2 (Bit 0)                              */
#define SCU_GPT12IRC_T2_Msk               (0x1UL)                   /*!< SCU GPT12IRC: T2 (Bitfield-Mask: 0x01)                */
/* ======================================================  GPT12PISEL  ======================================================= */
#define SCU_GPT12PISEL_T3_GPT12_SEL_Pos   (5UL)                     /*!< SCU GPT12PISEL: T3_GPT12_SEL (Bit 5)                  */
#define SCU_GPT12PISEL_T3_GPT12_SEL_Msk   (0x20UL)                  /*!< SCU GPT12PISEL: T3_GPT12_SEL (Bitfield-Mask: 0x01)    */
#define SCU_GPT12PISEL_TRIG_CONF_Pos      (4UL)                     /*!< SCU GPT12PISEL: TRIG_CONF (Bit 4)                     */
#define SCU_GPT12PISEL_TRIG_CONF_Msk      (0x10UL)                  /*!< SCU GPT12PISEL: TRIG_CONF (Bitfield-Mask: 0x01)       */
#define SCU_GPT12PISEL_GPT12_Pos          (0UL)                     /*!< SCU GPT12PISEL: GPT12 (Bit 0)                         */
#define SCU_GPT12PISEL_GPT12_Msk          (0xfUL)                   /*!< SCU GPT12PISEL: GPT12 (Bitfield-Mask: 0x0f)           */
/* ==========================================================  ID  =========================================================== */
#define SCU_ID_PRODID_Pos                 (3UL)                     /*!< SCU ID: PRODID (Bit 3)                                */
#define SCU_ID_PRODID_Msk                 (0xf8UL)                  /*!< SCU ID: PRODID (Bitfield-Mask: 0x1f)                  */
#define SCU_ID_VERID_Pos                  (0UL)                     /*!< SCU ID: VERID (Bit 0)                                 */
#define SCU_ID_VERID_Msk                  (0x7UL)                   /*!< SCU ID: VERID (Bitfield-Mask: 0x07)                   */
/* =========================================================  IEN0  ========================================================== */
#define SCU_IEN0_EA_Pos                   (7UL)                     /*!< SCU IEN0: EA (Bit 7)                                  */
#define SCU_IEN0_EA_Msk                   (0x80UL)                  /*!< SCU IEN0: EA (Bitfield-Mask: 0x01)                    */
/* ========================================================  IRCON0  ========================================================= */
#define SCU_IRCON0_MONF_Pos               (7UL)                     /*!< SCU IRCON0: MONF (Bit 7)                              */
#define SCU_IRCON0_MONF_Msk               (0x80UL)                  /*!< SCU IRCON0: MONF (Bitfield-Mask: 0x01)                */
#define SCU_IRCON0_MONR_Pos               (6UL)                     /*!< SCU IRCON0: MONR (Bit 6)                              */
#define SCU_IRCON0_MONR_Msk               (0x40UL)                  /*!< SCU IRCON0: MONR (Bitfield-Mask: 0x01)                */
#define SCU_IRCON0_EXINT2F_Pos            (5UL)                     /*!< SCU IRCON0: EXINT2F (Bit 5)                           */
#define SCU_IRCON0_EXINT2F_Msk            (0x20UL)                  /*!< SCU IRCON0: EXINT2F (Bitfield-Mask: 0x01)             */
#define SCU_IRCON0_EXINT2R_Pos            (4UL)                     /*!< SCU IRCON0: EXINT2R (Bit 4)                           */
#define SCU_IRCON0_EXINT2R_Msk            (0x10UL)                  /*!< SCU IRCON0: EXINT2R (Bitfield-Mask: 0x01)             */
#define SCU_IRCON0_EXINT1F_Pos            (3UL)                     /*!< SCU IRCON0: EXINT1F (Bit 3)                           */
#define SCU_IRCON0_EXINT1F_Msk            (0x8UL)                   /*!< SCU IRCON0: EXINT1F (Bitfield-Mask: 0x01)             */
#define SCU_IRCON0_EXINT1R_Pos            (2UL)                     /*!< SCU IRCON0: EXINT1R (Bit 2)                           */
#define SCU_IRCON0_EXINT1R_Msk            (0x4UL)                   /*!< SCU IRCON0: EXINT1R (Bitfield-Mask: 0x01)             */
#define SCU_IRCON0_EXINT0F_Pos            (1UL)                     /*!< SCU IRCON0: EXINT0F (Bit 1)                           */
#define SCU_IRCON0_EXINT0F_Msk            (0x2UL)                   /*!< SCU IRCON0: EXINT0F (Bitfield-Mask: 0x01)             */
#define SCU_IRCON0_EXINT0R_Pos            (0UL)                     /*!< SCU IRCON0: EXINT0R (Bit 0)                           */
#define SCU_IRCON0_EXINT0R_Msk            (0x1UL)                   /*!< SCU IRCON0: EXINT0R (Bitfield-Mask: 0x01)             */
/* =======================================================  IRCON0CLR  ======================================================= */
#define SCU_IRCON0CLR_MONFC_Pos           (7UL)                     /*!< SCU IRCON0CLR: MONFC (Bit 7)                          */
#define SCU_IRCON0CLR_MONFC_Msk           (0x80UL)                  /*!< SCU IRCON0CLR: MONFC (Bitfield-Mask: 0x01)            */
#define SCU_IRCON0CLR_MONRC_Pos           (6UL)                     /*!< SCU IRCON0CLR: MONRC (Bit 6)                          */
#define SCU_IRCON0CLR_MONRC_Msk           (0x40UL)                  /*!< SCU IRCON0CLR: MONRC (Bitfield-Mask: 0x01)            */
#define SCU_IRCON0CLR_EXINT2FC_Pos        (5UL)                     /*!< SCU IRCON0CLR: EXINT2FC (Bit 5)                       */
#define SCU_IRCON0CLR_EXINT2FC_Msk        (0x20UL)                  /*!< SCU IRCON0CLR: EXINT2FC (Bitfield-Mask: 0x01)         */
#define SCU_IRCON0CLR_EXINT2RC_Pos        (4UL)                     /*!< SCU IRCON0CLR: EXINT2RC (Bit 4)                       */
#define SCU_IRCON0CLR_EXINT2RC_Msk        (0x10UL)                  /*!< SCU IRCON0CLR: EXINT2RC (Bitfield-Mask: 0x01)         */
#define SCU_IRCON0CLR_EXINT1FC_Pos        (3UL)                     /*!< SCU IRCON0CLR: EXINT1FC (Bit 3)                       */
#define SCU_IRCON0CLR_EXINT1FC_Msk        (0x8UL)                   /*!< SCU IRCON0CLR: EXINT1FC (Bitfield-Mask: 0x01)         */
#define SCU_IRCON0CLR_EXINT1RC_Pos        (2UL)                     /*!< SCU IRCON0CLR: EXINT1RC (Bit 2)                       */
#define SCU_IRCON0CLR_EXINT1RC_Msk        (0x4UL)                   /*!< SCU IRCON0CLR: EXINT1RC (Bitfield-Mask: 0x01)         */
#define SCU_IRCON0CLR_EXINT0FC_Pos        (1UL)                     /*!< SCU IRCON0CLR: EXINT0FC (Bit 1)                       */
#define SCU_IRCON0CLR_EXINT0FC_Msk        (0x2UL)                   /*!< SCU IRCON0CLR: EXINT0FC (Bitfield-Mask: 0x01)         */
#define SCU_IRCON0CLR_EXINT0RC_Pos        (0UL)                     /*!< SCU IRCON0CLR: EXINT0RC (Bit 0)                       */
#define SCU_IRCON0CLR_EXINT0RC_Msk        (0x1UL)                   /*!< SCU IRCON0CLR: EXINT0RC (Bitfield-Mask: 0x01)         */
/* ========================================================  IRCON1  ========================================================= */
#define SCU_IRCON1_RIR_Pos                (2UL)                     /*!< SCU IRCON1: RIR (Bit 2)                               */
#define SCU_IRCON1_RIR_Msk                (0x4UL)                   /*!< SCU IRCON1: RIR (Bitfield-Mask: 0x01)                 */
#define SCU_IRCON1_TIR_Pos                (1UL)                     /*!< SCU IRCON1: TIR (Bit 1)                               */
#define SCU_IRCON1_TIR_Msk                (0x2UL)                   /*!< SCU IRCON1: TIR (Bitfield-Mask: 0x01)                 */
#define SCU_IRCON1_EIR_Pos                (0UL)                     /*!< SCU IRCON1: EIR (Bit 0)                               */
#define SCU_IRCON1_EIR_Msk                (0x1UL)                   /*!< SCU IRCON1: EIR (Bitfield-Mask: 0x01)                 */
/* =======================================================  IRCON1CLR  ======================================================= */
#define SCU_IRCON1CLR_RIRC_Pos            (2UL)                     /*!< SCU IRCON1CLR: RIRC (Bit 2)                           */
#define SCU_IRCON1CLR_RIRC_Msk            (0x4UL)                   /*!< SCU IRCON1CLR: RIRC (Bitfield-Mask: 0x01)             */
#define SCU_IRCON1CLR_TIRC_Pos            (1UL)                     /*!< SCU IRCON1CLR: TIRC (Bit 1)                           */
#define SCU_IRCON1CLR_TIRC_Msk            (0x2UL)                   /*!< SCU IRCON1CLR: TIRC (Bitfield-Mask: 0x01)             */
#define SCU_IRCON1CLR_EIRC_Pos            (0UL)                     /*!< SCU IRCON1CLR: EIRC (Bit 0)                           */
#define SCU_IRCON1CLR_EIRC_Msk            (0x1UL)                   /*!< SCU IRCON1CLR: EIRC (Bitfield-Mask: 0x01)             */
/* ========================================================  IRCON2  ========================================================= */
#define SCU_IRCON2_RIR_Pos                (2UL)                     /*!< SCU IRCON2: RIR (Bit 2)                               */
#define SCU_IRCON2_RIR_Msk                (0x4UL)                   /*!< SCU IRCON2: RIR (Bitfield-Mask: 0x01)                 */
#define SCU_IRCON2_TIR_Pos                (1UL)                     /*!< SCU IRCON2: TIR (Bit 1)                               */
#define SCU_IRCON2_TIR_Msk                (0x2UL)                   /*!< SCU IRCON2: TIR (Bitfield-Mask: 0x01)                 */
#define SCU_IRCON2_EIR_Pos                (0UL)                     /*!< SCU IRCON2: EIR (Bit 0)                               */
#define SCU_IRCON2_EIR_Msk                (0x1UL)                   /*!< SCU IRCON2: EIR (Bitfield-Mask: 0x01)                 */
/* =======================================================  IRCON2CLR  ======================================================= */
#define SCU_IRCON2CLR_RIRC_Pos            (2UL)                     /*!< SCU IRCON2CLR: RIRC (Bit 2)                           */
#define SCU_IRCON2CLR_RIRC_Msk            (0x4UL)                   /*!< SCU IRCON2CLR: RIRC (Bitfield-Mask: 0x01)             */
#define SCU_IRCON2CLR_TIRC_Pos            (1UL)                     /*!< SCU IRCON2CLR: TIRC (Bit 1)                           */
#define SCU_IRCON2CLR_TIRC_Msk            (0x2UL)                   /*!< SCU IRCON2CLR: TIRC (Bitfield-Mask: 0x01)             */
#define SCU_IRCON2CLR_EIRC_Pos            (0UL)                     /*!< SCU IRCON2CLR: EIRC (Bit 0)                           */
#define SCU_IRCON2CLR_EIRC_Msk            (0x1UL)                   /*!< SCU IRCON2CLR: EIRC (Bitfield-Mask: 0x01)             */
/* ========================================================  IRCON3  ========================================================= */
#define SCU_IRCON3_CCU6SR1_Pos            (4UL)                     /*!< SCU IRCON3: CCU6SR1 (Bit 4)                           */
#define SCU_IRCON3_CCU6SR1_Msk            (0x10UL)                  /*!< SCU IRCON3: CCU6SR1 (Bitfield-Mask: 0x01)             */
#define SCU_IRCON3_CCU6SR0_Pos            (0UL)                     /*!< SCU IRCON3: CCU6SR0 (Bit 0)                           */
#define SCU_IRCON3_CCU6SR0_Msk            (0x1UL)                   /*!< SCU IRCON3: CCU6SR0 (Bitfield-Mask: 0x01)             */
/* =======================================================  IRCON3CLR  ======================================================= */
#define SCU_IRCON3CLR_CCU6SR1C_Pos        (4UL)                     /*!< SCU IRCON3CLR: CCU6SR1C (Bit 4)                       */
#define SCU_IRCON3CLR_CCU6SR1C_Msk        (0x10UL)                  /*!< SCU IRCON3CLR: CCU6SR1C (Bitfield-Mask: 0x01)         */
#define SCU_IRCON3CLR_CCU6SR0C_Pos        (0UL)                     /*!< SCU IRCON3CLR: CCU6SR0C (Bit 0)                       */
#define SCU_IRCON3CLR_CCU6SR0C_Msk        (0x1UL)                   /*!< SCU IRCON3CLR: CCU6SR0C (Bitfield-Mask: 0x01)         */
/* ========================================================  IRCON4  ========================================================= */
#define SCU_IRCON4_CCU6SR3_Pos            (4UL)                     /*!< SCU IRCON4: CCU6SR3 (Bit 4)                           */
#define SCU_IRCON4_CCU6SR3_Msk            (0x10UL)                  /*!< SCU IRCON4: CCU6SR3 (Bitfield-Mask: 0x01)             */
#define SCU_IRCON4_CCU6SR2_Pos            (0UL)                     /*!< SCU IRCON4: CCU6SR2 (Bit 0)                           */
#define SCU_IRCON4_CCU6SR2_Msk            (0x1UL)                   /*!< SCU IRCON4: CCU6SR2 (Bitfield-Mask: 0x01)             */
/* =======================================================  IRCON4CLR  ======================================================= */
#define SCU_IRCON4CLR_CCU6SR3C_Pos        (4UL)                     /*!< SCU IRCON4CLR: CCU6SR3C (Bit 4)                       */
#define SCU_IRCON4CLR_CCU6SR3C_Msk        (0x10UL)                  /*!< SCU IRCON4CLR: CCU6SR3C (Bitfield-Mask: 0x01)         */
#define SCU_IRCON4CLR_CCU6SR2C_Pos        (0UL)                     /*!< SCU IRCON4CLR: CCU6SR2C (Bit 0)                       */
#define SCU_IRCON4CLR_CCU6SR2C_Msk        (0x1UL)                   /*!< SCU IRCON4CLR: CCU6SR2C (Bitfield-Mask: 0x01)         */
/* ========================================================  LINSCLR  ======================================================== */
#define SCU_LINSCLR_BRKC_Pos              (3UL)                     /*!< SCU LINSCLR: BRKC (Bit 3)                             */
#define SCU_LINSCLR_BRKC_Msk              (0x8UL)                   /*!< SCU LINSCLR: BRKC (Bitfield-Mask: 0x01)               */
#define SCU_LINSCLR_EOFSYNC_Pos           (4UL)                     /*!< SCU LINSCLR: EOFSYNC (Bit 4)                          */
#define SCU_LINSCLR_EOFSYNC_Msk           (0x10UL)                  /*!< SCU LINSCLR: EOFSYNC (Bitfield-Mask: 0x01)            */
#define SCU_LINSCLR_ERRSYNC_Pos           (5UL)                     /*!< SCU LINSCLR: ERRSYNC (Bit 5)                          */
#define SCU_LINSCLR_ERRSYNC_Msk           (0x20UL)                  /*!< SCU LINSCLR: ERRSYNC (Bitfield-Mask: 0x01)            */
/* =========================================================  LINST  ========================================================= */
#define SCU_LINST_BRDIS_Pos               (0UL)                     /*!< SCU LINST: BRDIS (Bit 0)                              */
#define SCU_LINST_BRDIS_Msk               (0x1UL)                   /*!< SCU LINST: BRDIS (Bitfield-Mask: 0x01)                */
#define SCU_LINST_BGSEL_Pos               (1UL)                     /*!< SCU LINST: BGSEL (Bit 1)                              */
#define SCU_LINST_BGSEL_Msk               (0x6UL)                   /*!< SCU LINST: BGSEL (Bitfield-Mask: 0x03)                */
#define SCU_LINST_BRK_Pos                 (3UL)                     /*!< SCU LINST: BRK (Bit 3)                                */
#define SCU_LINST_BRK_Msk                 (0x8UL)                   /*!< SCU LINST: BRK (Bitfield-Mask: 0x01)                  */
#define SCU_LINST_EOFSYN_Pos              (4UL)                     /*!< SCU LINST: EOFSYN (Bit 4)                             */
#define SCU_LINST_EOFSYN_Msk              (0x10UL)                  /*!< SCU LINST: EOFSYN (Bitfield-Mask: 0x01)               */
#define SCU_LINST_ERRSYN_Pos              (5UL)                     /*!< SCU LINST: ERRSYN (Bit 5)                             */
#define SCU_LINST_ERRSYN_Msk              (0x20UL)                  /*!< SCU LINST: ERRSYN (Bitfield-Mask: 0x01)               */
#define SCU_LINST_SYNEN_Pos               (6UL)                     /*!< SCU LINST: SYNEN (Bit 6)                              */
#define SCU_LINST_SYNEN_Msk               (0x40UL)                  /*!< SCU LINST: SYNEN (Bitfield-Mask: 0x01)                */
/* ======================================================  MEM_ACC_STS  ====================================================== */
#define SCU_MEM_ACC_STS_RAM_PROT_ERR_Pos  (6UL)                     /*!< SCU MEM_ACC_STS: RAM_PROT_ERR (Bit 6)                 */
#define SCU_MEM_ACC_STS_RAM_PROT_ERR_Msk  (0x40UL)                  /*!< SCU MEM_ACC_STS: RAM_PROT_ERR (Bitfield-Mask: 0x01)   */
#define SCU_MEM_ACC_STS_ROM_ADDR_ERR_Pos  (5UL)                     /*!< SCU MEM_ACC_STS: ROM_ADDR_ERR (Bit 5)                 */
#define SCU_MEM_ACC_STS_ROM_ADDR_ERR_Msk  (0x20UL)                  /*!< SCU MEM_ACC_STS: ROM_ADDR_ERR (Bitfield-Mask: 0x01)   */
#define SCU_MEM_ACC_STS_ROM_PROT_ERR_Pos  (4UL)                     /*!< SCU MEM_ACC_STS: ROM_PROT_ERR (Bit 4)                 */
#define SCU_MEM_ACC_STS_ROM_PROT_ERR_Msk  (0x10UL)                  /*!< SCU MEM_ACC_STS: ROM_PROT_ERR (Bitfield-Mask: 0x01)   */
#define SCU_MEM_ACC_STS_NVM_SFR_ADDR_ERR_Pos (3UL)                  /*!< SCU MEM_ACC_STS: NVM_SFR_ADDR_ERR (Bit 3)             */
#define SCU_MEM_ACC_STS_NVM_SFR_ADDR_ERR_Msk (0x8UL)                /*!< SCU MEM_ACC_STS: NVM_SFR_ADDR_ERR (Bitfield-Mask: 0x01) */
#define SCU_MEM_ACC_STS_NVM_SFR_PROT_ERR_Pos (2UL)                  /*!< SCU MEM_ACC_STS: NVM_SFR_PROT_ERR (Bit 2)             */
#define SCU_MEM_ACC_STS_NVM_SFR_PROT_ERR_Msk (0x4UL)                /*!< SCU MEM_ACC_STS: NVM_SFR_PROT_ERR (Bitfield-Mask: 0x01) */
#define SCU_MEM_ACC_STS_NVM_ADDR_ERR_Pos  (1UL)                     /*!< SCU MEM_ACC_STS: NVM_ADDR_ERR (Bit 1)                 */
#define SCU_MEM_ACC_STS_NVM_ADDR_ERR_Msk  (0x2UL)                   /*!< SCU MEM_ACC_STS: NVM_ADDR_ERR (Bitfield-Mask: 0x01)   */
#define SCU_MEM_ACC_STS_NVM_PROT_ERR_Pos  (0UL)                     /*!< SCU MEM_ACC_STS: NVM_PROT_ERR (Bit 0)                 */
#define SCU_MEM_ACC_STS_NVM_PROT_ERR_Msk  (0x1UL)                   /*!< SCU MEM_ACC_STS: NVM_PROT_ERR (Bitfield-Mask: 0x01)   */
/* ========================================================  MEMSTAT  ======================================================== */
#define SCU_MEMSTAT_SASTATUS_Pos          (6UL)                     /*!< SCU MEMSTAT: SASTATUS (Bit 6)                         */
#define SCU_MEMSTAT_SASTATUS_Msk          (0xc0UL)                  /*!< SCU MEMSTAT: SASTATUS (Bitfield-Mask: 0x03)           */
#define SCU_MEMSTAT_SECTORINFO_Pos        (0UL)                     /*!< SCU MEMSTAT: SECTORINFO (Bit 0)                       */
#define SCU_MEMSTAT_SECTORINFO_Msk        (0x3fUL)                  /*!< SCU MEMSTAT: SECTORINFO (Bitfield-Mask: 0x3f)         */
/* ========================================================  MODIEN1  ======================================================== */
#define SCU_MODIEN1_TIEN1_Pos             (7UL)                     /*!< SCU MODIEN1: TIEN1 (Bit 7)                            */
#define SCU_MODIEN1_TIEN1_Msk             (0x80UL)                  /*!< SCU MODIEN1: TIEN1 (Bitfield-Mask: 0x01)              */
#define SCU_MODIEN1_RIEN1_Pos             (6UL)                     /*!< SCU MODIEN1: RIEN1 (Bit 6)                            */
#define SCU_MODIEN1_RIEN1_Msk             (0x40UL)                  /*!< SCU MODIEN1: RIEN1 (Bitfield-Mask: 0x01)              */
#define SCU_MODIEN1_RIREN1_Pos            (2UL)                     /*!< SCU MODIEN1: RIREN1 (Bit 2)                           */
#define SCU_MODIEN1_RIREN1_Msk            (0x4UL)                   /*!< SCU MODIEN1: RIREN1 (Bitfield-Mask: 0x01)             */
#define SCU_MODIEN1_TIREN1_Pos            (1UL)                     /*!< SCU MODIEN1: TIREN1 (Bit 1)                           */
#define SCU_MODIEN1_TIREN1_Msk            (0x2UL)                   /*!< SCU MODIEN1: TIREN1 (Bitfield-Mask: 0x01)             */
#define SCU_MODIEN1_EIREN1_Pos            (0UL)                     /*!< SCU MODIEN1: EIREN1 (Bit 0)                           */
#define SCU_MODIEN1_EIREN1_Msk            (0x1UL)                   /*!< SCU MODIEN1: EIREN1 (Bitfield-Mask: 0x01)             */
/* ========================================================  MODIEN2  ======================================================== */
#define SCU_MODIEN2_TIEN2_Pos             (7UL)                     /*!< SCU MODIEN2: TIEN2 (Bit 7)                            */
#define SCU_MODIEN2_TIEN2_Msk             (0x80UL)                  /*!< SCU MODIEN2: TIEN2 (Bitfield-Mask: 0x01)              */
#define SCU_MODIEN2_RIEN2_Pos             (6UL)                     /*!< SCU MODIEN2: RIEN2 (Bit 6)                            */
#define SCU_MODIEN2_RIEN2_Msk             (0x40UL)                  /*!< SCU MODIEN2: RIEN2 (Bitfield-Mask: 0x01)              */
#define SCU_MODIEN2_EXINT2_EN_Pos         (5UL)                     /*!< SCU MODIEN2: EXINT2_EN (Bit 5)                        */
#define SCU_MODIEN2_EXINT2_EN_Msk         (0x20UL)                  /*!< SCU MODIEN2: EXINT2_EN (Bitfield-Mask: 0x01)          */
#define SCU_MODIEN2_RIREN2_Pos            (2UL)                     /*!< SCU MODIEN2: RIREN2 (Bit 2)                           */
#define SCU_MODIEN2_RIREN2_Msk            (0x4UL)                   /*!< SCU MODIEN2: RIREN2 (Bitfield-Mask: 0x01)             */
#define SCU_MODIEN2_TIREN2_Pos            (1UL)                     /*!< SCU MODIEN2: TIREN2 (Bit 1)                           */
#define SCU_MODIEN2_TIREN2_Msk            (0x2UL)                   /*!< SCU MODIEN2: TIREN2 (Bitfield-Mask: 0x01)             */
#define SCU_MODIEN2_EIREN2_Pos            (0UL)                     /*!< SCU MODIEN2: EIREN2 (Bit 0)                           */
#define SCU_MODIEN2_EIREN2_Msk            (0x1UL)                   /*!< SCU MODIEN2: EIREN2 (Bitfield-Mask: 0x01)             */
/* ========================================================  MODIEN3  ======================================================== */
#define SCU_MODIEN3_MONSTS_Pos            (5UL)                     /*!< SCU MODIEN3: MONSTS (Bit 5)                           */
#define SCU_MODIEN3_MONSTS_Msk            (0x20UL)                  /*!< SCU MODIEN3: MONSTS (Bitfield-Mask: 0x01)             */
#define SCU_MODIEN3_MONIE_Pos             (4UL)                     /*!< SCU MODIEN3: MONIE (Bit 4)                            */
#define SCU_MODIEN3_MONIE_Msk             (0x10UL)                  /*!< SCU MODIEN3: MONIE (Bitfield-Mask: 0x01)              */
#define SCU_MODIEN3_IE0_Pos               (0UL)                     /*!< SCU MODIEN3: IE0 (Bit 0)                              */
#define SCU_MODIEN3_IE0_Msk               (0x1UL)                   /*!< SCU MODIEN3: IE0 (Bitfield-Mask: 0x01)                */
/* ========================================================  MODIEN4  ======================================================== */
#define SCU_MODIEN4_IE1_Pos               (0UL)                     /*!< SCU MODIEN4: IE1 (Bit 0)                              */
#define SCU_MODIEN4_IE1_Msk               (0x1UL)                   /*!< SCU MODIEN4: IE1 (Bitfield-Mask: 0x01)                */
/* =======================================================  MODPISEL  ======================================================== */
#define SCU_MODPISEL_U_TX_CONDIS_Pos      (7UL)                     /*!< SCU MODPISEL: U_TX_CONDIS (Bit 7)                     */
#define SCU_MODPISEL_U_TX_CONDIS_Msk      (0x80UL)                  /*!< SCU MODPISEL: U_TX_CONDIS (Bitfield-Mask: 0x01)       */
#define SCU_MODPISEL_URIOS1_Pos           (6UL)                     /*!< SCU MODPISEL: URIOS1 (Bit 6)                          */
#define SCU_MODPISEL_URIOS1_Msk           (0x40UL)                  /*!< SCU MODPISEL: URIOS1 (Bitfield-Mask: 0x01)            */
#define SCU_MODPISEL_EXINT2IS_Pos         (4UL)                     /*!< SCU MODPISEL: EXINT2IS (Bit 4)                        */
#define SCU_MODPISEL_EXINT2IS_Msk         (0x30UL)                  /*!< SCU MODPISEL: EXINT2IS (Bitfield-Mask: 0x03)          */
#define SCU_MODPISEL_EXINT1IS_Pos         (2UL)                     /*!< SCU MODPISEL: EXINT1IS (Bit 2)                        */
#define SCU_MODPISEL_EXINT1IS_Msk         (0xcUL)                   /*!< SCU MODPISEL: EXINT1IS (Bitfield-Mask: 0x03)          */
#define SCU_MODPISEL_EXINT0IS_Pos         (0UL)                     /*!< SCU MODPISEL: EXINT0IS (Bit 0)                        */
#define SCU_MODPISEL_EXINT0IS_Msk         (0x3UL)                   /*!< SCU MODPISEL: EXINT0IS (Bitfield-Mask: 0x03)          */
/* =======================================================  MODPISEL1  ======================================================= */
#define SCU_MODPISEL1_T21EXCON_Pos        (7UL)                     /*!< SCU MODPISEL1: T21EXCON (Bit 7)                       */
#define SCU_MODPISEL1_T21EXCON_Msk        (0x80UL)                  /*!< SCU MODPISEL1: T21EXCON (Bitfield-Mask: 0x01)         */
#define SCU_MODPISEL1_T2EXCON_Pos         (6UL)                     /*!< SCU MODPISEL1: T2EXCON (Bit 6)                        */
#define SCU_MODPISEL1_T2EXCON_Msk         (0x40UL)                  /*!< SCU MODPISEL1: T2EXCON (Bitfield-Mask: 0x01)          */
#define SCU_MODPISEL1_GPT12CAPINB_Pos     (0UL)                     /*!< SCU MODPISEL1: GPT12CAPINB (Bit 0)                    */
#define SCU_MODPISEL1_GPT12CAPINB_Msk     (0x1UL)                   /*!< SCU MODPISEL1: GPT12CAPINB (Bitfield-Mask: 0x01)      */
/* =======================================================  MODPISEL2  ======================================================= */
#define SCU_MODPISEL2_T21EXIS_Pos         (6UL)                     /*!< SCU MODPISEL2: T21EXIS (Bit 6)                        */
#define SCU_MODPISEL2_T21EXIS_Msk         (0xc0UL)                  /*!< SCU MODPISEL2: T21EXIS (Bitfield-Mask: 0x03)          */
#define SCU_MODPISEL2_T2EXIS_Pos          (4UL)                     /*!< SCU MODPISEL2: T2EXIS (Bit 4)                         */
#define SCU_MODPISEL2_T2EXIS_Msk          (0x30UL)                  /*!< SCU MODPISEL2: T2EXIS (Bitfield-Mask: 0x03)           */
#define SCU_MODPISEL2_T21IS_Pos           (2UL)                     /*!< SCU MODPISEL2: T21IS (Bit 2)                          */
#define SCU_MODPISEL2_T21IS_Msk           (0xcUL)                   /*!< SCU MODPISEL2: T21IS (Bitfield-Mask: 0x03)            */
#define SCU_MODPISEL2_T2IS_Pos            (0UL)                     /*!< SCU MODPISEL2: T2IS (Bit 0)                           */
#define SCU_MODPISEL2_T2IS_Msk            (0x3UL)                   /*!< SCU MODPISEL2: T2IS (Bitfield-Mask: 0x03)             */
/* =======================================================  MODPISEL3  ======================================================= */
#define SCU_MODPISEL3_URIOS2_Pos          (6UL)                     /*!< SCU MODPISEL3: URIOS2 (Bit 6)                         */
#define SCU_MODPISEL3_URIOS2_Msk          (0x40UL)                  /*!< SCU MODPISEL3: URIOS2 (Bitfield-Mask: 0x01)           */
/* =======================================================  MODSUSP1  ======================================================== */
#define SCU_MODSUSP1_T21_SUSP_Pos         (6UL)                     /*!< SCU MODSUSP1: T21_SUSP (Bit 6)                        */
#define SCU_MODSUSP1_T21_SUSP_Msk         (0x40UL)                  /*!< SCU MODSUSP1: T21_SUSP (Bitfield-Mask: 0x01)          */
#define SCU_MODSUSP1_GPT12_SUSP_Pos       (4UL)                     /*!< SCU MODSUSP1: GPT12_SUSP (Bit 4)                      */
#define SCU_MODSUSP1_GPT12_SUSP_Msk       (0x10UL)                  /*!< SCU MODSUSP1: GPT12_SUSP (Bitfield-Mask: 0x01)        */
#define SCU_MODSUSP1_T2_SUSP_Pos          (3UL)                     /*!< SCU MODSUSP1: T2_SUSP (Bit 3)                         */
#define SCU_MODSUSP1_T2_SUSP_Msk          (0x8UL)                   /*!< SCU MODSUSP1: T2_SUSP (Bitfield-Mask: 0x01)           */
#define SCU_MODSUSP1_T13SUSP_Pos          (2UL)                     /*!< SCU MODSUSP1: T13SUSP (Bit 2)                         */
#define SCU_MODSUSP1_T13SUSP_Msk          (0x4UL)                   /*!< SCU MODSUSP1: T13SUSP (Bitfield-Mask: 0x01)           */
#define SCU_MODSUSP1_T12SUSP_Pos          (1UL)                     /*!< SCU MODSUSP1: T12SUSP (Bit 1)                         */
#define SCU_MODSUSP1_T12SUSP_Msk          (0x2UL)                   /*!< SCU MODSUSP1: T12SUSP (Bitfield-Mask: 0x01)           */
#define SCU_MODSUSP1_WDTSUSP_Pos          (0UL)                     /*!< SCU MODSUSP1: WDTSUSP (Bit 0)                         */
#define SCU_MODSUSP1_WDTSUSP_Msk          (0x1UL)                   /*!< SCU MODSUSP1: WDTSUSP (Bitfield-Mask: 0x01)           */
/* =======================================================  MODSUSP2  ======================================================== */
#define SCU_MODSUSP2_ADC1_SUSP_Pos        (2UL)                     /*!< SCU MODSUSP2: ADC1_SUSP (Bit 2)                       */
#define SCU_MODSUSP2_ADC1_SUSP_Msk        (0x4UL)                   /*!< SCU MODSUSP2: ADC1_SUSP (Bitfield-Mask: 0x01)         */
#define SCU_MODSUSP2_MU_SUSP_Pos          (1UL)                     /*!< SCU MODSUSP2: MU_SUSP (Bit 1)                         */
#define SCU_MODSUSP2_MU_SUSP_Msk          (0x2UL)                   /*!< SCU MODSUSP2: MU_SUSP (Bitfield-Mask: 0x01)           */
#define SCU_MODSUSP2_T3_SUSP_Pos          (0UL)                     /*!< SCU MODSUSP2: T3_SUSP (Bit 0)                         */
#define SCU_MODSUSP2_T3_SUSP_Msk          (0x1UL)                   /*!< SCU MODSUSP2: T3_SUSP (Bitfield-Mask: 0x01)           */
/* ========================================================  NMICLR  ========================================================= */
#define SCU_NMICLR_NMISUPC_Pos            (7UL)                     /*!< SCU NMICLR: NMISUPC (Bit 7)                           */
#define SCU_NMICLR_NMISUPC_Msk            (0x80UL)                  /*!< SCU NMICLR: NMISUPC (Bitfield-Mask: 0x01)             */
#define SCU_NMICLR_NMIECCC_Pos            (6UL)                     /*!< SCU NMICLR: NMIECCC (Bit 6)                           */
#define SCU_NMICLR_NMIECCC_Msk            (0x40UL)                  /*!< SCU NMICLR: NMIECCC (Bitfield-Mask: 0x01)             */
#define SCU_NMICLR_NMIMAPC_Pos            (5UL)                     /*!< SCU NMICLR: NMIMAPC (Bit 5)                           */
#define SCU_NMICLR_NMIMAPC_Msk            (0x20UL)                  /*!< SCU NMICLR: NMIMAPC (Bitfield-Mask: 0x01)             */
#define SCU_NMICLR_NMIOWDC_Pos            (4UL)                     /*!< SCU NMICLR: NMIOWDC (Bit 4)                           */
#define SCU_NMICLR_NMIOWDC_Msk            (0x10UL)                  /*!< SCU NMICLR: NMIOWDC (Bitfield-Mask: 0x01)             */
#define SCU_NMICLR_NMIOTC_Pos             (3UL)                     /*!< SCU NMICLR: NMIOTC (Bit 3)                            */
#define SCU_NMICLR_NMIOTC_Msk             (0x8UL)                   /*!< SCU NMICLR: NMIOTC (Bitfield-Mask: 0x01)              */
#define SCU_NMICLR_NMINVMC_Pos            (2UL)                     /*!< SCU NMICLR: NMINVMC (Bit 2)                           */
#define SCU_NMICLR_NMINVMC_Msk            (0x4UL)                   /*!< SCU NMICLR: NMINVMC (Bitfield-Mask: 0x01)             */
#define SCU_NMICLR_NMIPLLC_Pos            (1UL)                     /*!< SCU NMICLR: NMIPLLC (Bit 1)                           */
#define SCU_NMICLR_NMIPLLC_Msk            (0x2UL)                   /*!< SCU NMICLR: NMIPLLC (Bitfield-Mask: 0x01)             */
#define SCU_NMICLR_NMIWDTC_Pos            (0UL)                     /*!< SCU NMICLR: NMIWDTC (Bit 0)                           */
#define SCU_NMICLR_NMIWDTC_Msk            (0x1UL)                   /*!< SCU NMICLR: NMIWDTC (Bitfield-Mask: 0x01)             */
/* ========================================================  NMICON  ========================================================= */
#define SCU_NMICON_NMISUP_Pos             (7UL)                     /*!< SCU NMICON: NMISUP (Bit 7)                            */
#define SCU_NMICON_NMISUP_Msk             (0x80UL)                  /*!< SCU NMICON: NMISUP (Bitfield-Mask: 0x01)              */
#define SCU_NMICON_NMIECC_Pos             (6UL)                     /*!< SCU NMICON: NMIECC (Bit 6)                            */
#define SCU_NMICON_NMIECC_Msk             (0x40UL)                  /*!< SCU NMICON: NMIECC (Bitfield-Mask: 0x01)              */
#define SCU_NMICON_NMIMAP_Pos             (5UL)                     /*!< SCU NMICON: NMIMAP (Bit 5)                            */
#define SCU_NMICON_NMIMAP_Msk             (0x20UL)                  /*!< SCU NMICON: NMIMAP (Bitfield-Mask: 0x01)              */
#define SCU_NMICON_NMIOWD_Pos             (4UL)                     /*!< SCU NMICON: NMIOWD (Bit 4)                            */
#define SCU_NMICON_NMIOWD_Msk             (0x10UL)                  /*!< SCU NMICON: NMIOWD (Bitfield-Mask: 0x01)              */
#define SCU_NMICON_NMIOT_Pos              (3UL)                     /*!< SCU NMICON: NMIOT (Bit 3)                             */
#define SCU_NMICON_NMIOT_Msk              (0x8UL)                   /*!< SCU NMICON: NMIOT (Bitfield-Mask: 0x01)               */
#define SCU_NMICON_NMINVM_Pos             (2UL)                     /*!< SCU NMICON: NMINVM (Bit 2)                            */
#define SCU_NMICON_NMINVM_Msk             (0x4UL)                   /*!< SCU NMICON: NMINVM (Bitfield-Mask: 0x01)              */
#define SCU_NMICON_NMIPLL_Pos             (1UL)                     /*!< SCU NMICON: NMIPLL (Bit 1)                            */
#define SCU_NMICON_NMIPLL_Msk             (0x2UL)                   /*!< SCU NMICON: NMIPLL (Bitfield-Mask: 0x01)              */
#define SCU_NMICON_NMIWDT_Pos             (0UL)                     /*!< SCU NMICON: NMIWDT (Bit 0)                            */
#define SCU_NMICON_NMIWDT_Msk             (0x1UL)                   /*!< SCU NMICON: NMIWDT (Bitfield-Mask: 0x01)              */
/* =========================================================  NMISR  ========================================================= */
#define SCU_NMISR_FNMISUP_Pos             (7UL)                     /*!< SCU NMISR: FNMISUP (Bit 7)                            */
#define SCU_NMISR_FNMISUP_Msk             (0x80UL)                  /*!< SCU NMISR: FNMISUP (Bitfield-Mask: 0x01)              */
#define SCU_NMISR_FNMIECC_Pos             (6UL)                     /*!< SCU NMISR: FNMIECC (Bit 6)                            */
#define SCU_NMISR_FNMIECC_Msk             (0x40UL)                  /*!< SCU NMISR: FNMIECC (Bitfield-Mask: 0x01)              */
#define SCU_NMISR_FNMIMAP_Pos             (5UL)                     /*!< SCU NMISR: FNMIMAP (Bit 5)                            */
#define SCU_NMISR_FNMIMAP_Msk             (0x20UL)                  /*!< SCU NMISR: FNMIMAP (Bitfield-Mask: 0x01)              */
#define SCU_NMISR_FNMIOWD_Pos             (4UL)                     /*!< SCU NMISR: FNMIOWD (Bit 4)                            */
#define SCU_NMISR_FNMIOWD_Msk             (0x10UL)                  /*!< SCU NMISR: FNMIOWD (Bitfield-Mask: 0x01)              */
#define SCU_NMISR_FNMIOT_Pos              (3UL)                     /*!< SCU NMISR: FNMIOT (Bit 3)                             */
#define SCU_NMISR_FNMIOT_Msk              (0x8UL)                   /*!< SCU NMISR: FNMIOT (Bitfield-Mask: 0x01)               */
#define SCU_NMISR_FNMINVM_Pos             (2UL)                     /*!< SCU NMISR: FNMINVM (Bit 2)                            */
#define SCU_NMISR_FNMINVM_Msk             (0x4UL)                   /*!< SCU NMISR: FNMINVM (Bitfield-Mask: 0x01)              */
#define SCU_NMISR_FNMIPLL_Pos             (1UL)                     /*!< SCU NMISR: FNMIPLL (Bit 1)                            */
#define SCU_NMISR_FNMIPLL_Msk             (0x2UL)                   /*!< SCU NMISR: FNMIPLL (Bitfield-Mask: 0x01)              */
#define SCU_NMISR_FNMIWDT_Pos             (0UL)                     /*!< SCU NMISR: FNMIWDT (Bit 0)                            */
#define SCU_NMISR_FNMIWDT_Msk             (0x1UL)                   /*!< SCU NMISR: FNMIWDT (Bitfield-Mask: 0x01)              */
/* =====================================================  NVM_PROT_STS  ====================================================== */
#define SCU_NVM_PROT_STS_NVMPROTSTSL_3_Pos (3UL)                    /*!< SCU NVM_PROT_STS: NVMPROTSTSL_3 (Bit 3)               */
#define SCU_NVM_PROT_STS_NVMPROTSTSL_3_Msk (0x8UL)                  /*!< SCU NVM_PROT_STS: NVMPROTSTSL_3 (Bitfield-Mask: 0x01) */
#define SCU_NVM_PROT_STS_NVMPROTSTSL_2_Pos (2UL)                    /*!< SCU NVM_PROT_STS: NVMPROTSTSL_2 (Bit 2)               */
#define SCU_NVM_PROT_STS_NVMPROTSTSL_2_Msk (0x4UL)                  /*!< SCU NVM_PROT_STS: NVMPROTSTSL_2 (Bitfield-Mask: 0x01) */
#define SCU_NVM_PROT_STS_NVMPROTSTSL_1_Pos (1UL)                    /*!< SCU NVM_PROT_STS: NVMPROTSTSL_1 (Bit 1)               */
#define SCU_NVM_PROT_STS_NVMPROTSTSL_1_Msk (0x2UL)                  /*!< SCU NVM_PROT_STS: NVMPROTSTSL_1 (Bitfield-Mask: 0x01) */
#define SCU_NVM_PROT_STS_NVMPROTSTSL_0_Pos (0UL)                    /*!< SCU NVM_PROT_STS: NVMPROTSTSL_0 (Bit 0)               */
#define SCU_NVM_PROT_STS_NVMPROTSTSL_0_Msk (0x1UL)                  /*!< SCU NVM_PROT_STS: NVMPROTSTSL_0 (Bitfield-Mask: 0x01) */
/* ========================================================  OSC_CON  ======================================================== */
#define SCU_OSC_CON_OSCTRIM_8_Pos         (7UL)                     /*!< SCU OSC_CON: OSCTRIM_8 (Bit 7)                        */
#define SCU_OSC_CON_OSCTRIM_8_Msk         (0x80UL)                  /*!< SCU OSC_CON: OSCTRIM_8 (Bitfield-Mask: 0x01)          */
#define SCU_OSC_CON_XPD_Pos               (4UL)                     /*!< SCU OSC_CON: XPD (Bit 4)                              */
#define SCU_OSC_CON_XPD_Msk               (0x10UL)                  /*!< SCU OSC_CON: XPD (Bitfield-Mask: 0x01)                */
#define SCU_OSC_CON_OSC2L_Pos             (3UL)                     /*!< SCU OSC_CON: OSC2L (Bit 3)                            */
#define SCU_OSC_CON_OSC2L_Msk             (0x8UL)                   /*!< SCU OSC_CON: OSC2L (Bitfield-Mask: 0x01)              */
#define SCU_OSC_CON_OSCWDTRST_Pos         (2UL)                     /*!< SCU OSC_CON: OSCWDTRST (Bit 2)                        */
#define SCU_OSC_CON_OSCWDTRST_Msk         (0x4UL)                   /*!< SCU OSC_CON: OSCWDTRST (Bitfield-Mask: 0x01)          */
#define SCU_OSC_CON_OSCSS_Pos             (0UL)                     /*!< SCU OSC_CON: OSCSS (Bit 0)                            */
#define SCU_OSC_CON_OSCSS_Msk             (0x3UL)                   /*!< SCU OSC_CON: OSCSS (Bitfield-Mask: 0x03)              */
/* =======================================================  P0_POCON0  ======================================================= */
#define SCU_P0_POCON0_PDM1_Pos            (4UL)                     /*!< SCU P0_POCON0: PDM1 (Bit 4)                           */
#define SCU_P0_POCON0_PDM1_Msk            (0x70UL)                  /*!< SCU P0_POCON0: PDM1 (Bitfield-Mask: 0x07)             */
#define SCU_P0_POCON0_PDM0_Pos            (0UL)                     /*!< SCU P0_POCON0: PDM0 (Bit 0)                           */
#define SCU_P0_POCON0_PDM0_Msk            (0x7UL)                   /*!< SCU P0_POCON0: PDM0 (Bitfield-Mask: 0x07)             */
/* =======================================================  P0_POCON1  ======================================================= */
#define SCU_P0_POCON1_PDM3_Pos            (4UL)                     /*!< SCU P0_POCON1: PDM3 (Bit 4)                           */
#define SCU_P0_POCON1_PDM3_Msk            (0x70UL)                  /*!< SCU P0_POCON1: PDM3 (Bitfield-Mask: 0x07)             */
#define SCU_P0_POCON1_PDM2_Pos            (0UL)                     /*!< SCU P0_POCON1: PDM2 (Bit 0)                           */
#define SCU_P0_POCON1_PDM2_Msk            (0x7UL)                   /*!< SCU P0_POCON1: PDM2 (Bitfield-Mask: 0x07)             */
/* =======================================================  P0_POCON2  ======================================================= */
#define SCU_P0_POCON2_PDM4_Pos            (0UL)                     /*!< SCU P0_POCON2: PDM4 (Bit 0)                           */
#define SCU_P0_POCON2_PDM4_Msk            (0x7UL)                   /*!< SCU P0_POCON2: PDM4 (Bitfield-Mask: 0x07)             */
/* =======================================================  P1_POCON0  ======================================================= */
#define SCU_P1_POCON0_PDM1_Pos            (4UL)                     /*!< SCU P1_POCON0: PDM1 (Bit 4)                           */
#define SCU_P1_POCON0_PDM1_Msk            (0x70UL)                  /*!< SCU P1_POCON0: PDM1 (Bitfield-Mask: 0x07)             */
#define SCU_P1_POCON0_PDM0_Pos            (0UL)                     /*!< SCU P1_POCON0: PDM0 (Bit 0)                           */
#define SCU_P1_POCON0_PDM0_Msk            (0x7UL)                   /*!< SCU P1_POCON0: PDM0 (Bitfield-Mask: 0x07)             */
/* =======================================================  P1_POCON1  ======================================================= */
#define SCU_P1_POCON1_PDM3_Pos            (4UL)                     /*!< SCU P1_POCON1: PDM3 (Bit 4)                           */
#define SCU_P1_POCON1_PDM3_Msk            (0x70UL)                  /*!< SCU P1_POCON1: PDM3 (Bitfield-Mask: 0x07)             */
#define SCU_P1_POCON1_PDM2_Pos            (0UL)                     /*!< SCU P1_POCON1: PDM2 (Bit 0)                           */
#define SCU_P1_POCON1_PDM2_Msk            (0x7UL)                   /*!< SCU P1_POCON1: PDM2 (Bitfield-Mask: 0x07)             */
/* =======================================================  P1_POCON2  ======================================================= */
#define SCU_P1_POCON2_PDM4_Pos            (0UL)                     /*!< SCU P1_POCON2: PDM4 (Bit 0)                           */
#define SCU_P1_POCON2_PDM4_Msk            (0x7UL)                   /*!< SCU P1_POCON2: PDM4 (Bitfield-Mask: 0x07)             */
/* ========================================================  PASSWD  ========================================================= */
#define SCU_PASSWD_PASS_Pos               (3UL)                     /*!< SCU PASSWD: PASS (Bit 3)                              */
#define SCU_PASSWD_PASS_Msk               (0xf8UL)                  /*!< SCU PASSWD: PASS (Bitfield-Mask: 0x1f)                */
#define SCU_PASSWD_PROTECT_S_Pos          (2UL)                     /*!< SCU PASSWD: PROTECT_S (Bit 2)                         */
#define SCU_PASSWD_PROTECT_S_Msk          (0x4UL)                   /*!< SCU PASSWD: PROTECT_S (Bitfield-Mask: 0x01)           */
#define SCU_PASSWD_MODE_Pos               (0UL)                     /*!< SCU PASSWD: MODE (Bit 0)                              */
#define SCU_PASSWD_MODE_Msk               (0x3UL)                   /*!< SCU PASSWD: MODE (Bitfield-Mask: 0x03)                */
/* ========================================================  PLL_CON  ======================================================== */
#define SCU_PLL_CON_NDIV_Pos              (4UL)                     /*!< SCU PLL_CON: NDIV (Bit 4)                             */
#define SCU_PLL_CON_NDIV_Msk              (0xf0UL)                  /*!< SCU PLL_CON: NDIV (Bitfield-Mask: 0x0f)               */
#define SCU_PLL_CON_VCOBYP_Pos            (3UL)                     /*!< SCU PLL_CON: VCOBYP (Bit 3)                           */
#define SCU_PLL_CON_VCOBYP_Msk            (0x8UL)                   /*!< SCU PLL_CON: VCOBYP (Bitfield-Mask: 0x01)             */
#define SCU_PLL_CON_OSCDISC_Pos           (2UL)                     /*!< SCU PLL_CON: OSCDISC (Bit 2)                          */
#define SCU_PLL_CON_OSCDISC_Msk           (0x4UL)                   /*!< SCU PLL_CON: OSCDISC (Bitfield-Mask: 0x01)            */
#define SCU_PLL_CON_RESLD_Pos             (1UL)                     /*!< SCU PLL_CON: RESLD (Bit 1)                            */
#define SCU_PLL_CON_RESLD_Msk             (0x2UL)                   /*!< SCU PLL_CON: RESLD (Bitfield-Mask: 0x01)              */
#define SCU_PLL_CON_LOCK_Pos              (0UL)                     /*!< SCU PLL_CON: LOCK (Bit 0)                             */
#define SCU_PLL_CON_LOCK_Msk              (0x1UL)                   /*!< SCU PLL_CON: LOCK (Bitfield-Mask: 0x01)               */
/* ========================================================  PMCON0  ========================================================= */
#define SCU_PMCON0_SD_Pos                 (3UL)                     /*!< SCU PMCON0: SD (Bit 3)                                */
#define SCU_PMCON0_SD_Msk                 (0x8UL)                   /*!< SCU PMCON0: SD (Bitfield-Mask: 0x01)                  */
#define SCU_PMCON0_PD_Pos                 (2UL)                     /*!< SCU PMCON0: PD (Bit 2)                                */
#define SCU_PMCON0_PD_Msk                 (0x4UL)                   /*!< SCU PMCON0: PD (Bitfield-Mask: 0x01)                  */
#define SCU_PMCON0_SL_Pos                 (1UL)                     /*!< SCU PMCON0: SL (Bit 1)                                */
#define SCU_PMCON0_SL_Msk                 (0x2UL)                   /*!< SCU PMCON0: SL (Bitfield-Mask: 0x01)                  */
#define SCU_PMCON0_XTAL_ON_Pos            (0UL)                     /*!< SCU PMCON0: XTAL_ON (Bit 0)                           */
#define SCU_PMCON0_XTAL_ON_Msk            (0x1UL)                   /*!< SCU PMCON0: XTAL_ON (Bitfield-Mask: 0x01)             */
/* ========================================================  PMCON1  ========================================================= */
#define SCU_PMCON1_GPT12_DIS_Pos          (4UL)                     /*!< SCU PMCON1: GPT12_DIS (Bit 4)                         */
#define SCU_PMCON1_GPT12_DIS_Msk          (0x10UL)                  /*!< SCU PMCON1: GPT12_DIS (Bitfield-Mask: 0x01)           */
#define SCU_PMCON1_T2_DIS_Pos             (3UL)                     /*!< SCU PMCON1: T2_DIS (Bit 3)                            */
#define SCU_PMCON1_T2_DIS_Msk             (0x8UL)                   /*!< SCU PMCON1: T2_DIS (Bitfield-Mask: 0x01)              */
#define SCU_PMCON1_CCU6_DIS_Pos           (2UL)                     /*!< SCU PMCON1: CCU6_DIS (Bit 2)                          */
#define SCU_PMCON1_CCU6_DIS_Msk           (0x4UL)                   /*!< SCU PMCON1: CCU6_DIS (Bitfield-Mask: 0x01)            */
#define SCU_PMCON1_SSC1_DIS_Pos           (1UL)                     /*!< SCU PMCON1: SSC1_DIS (Bit 1)                          */
#define SCU_PMCON1_SSC1_DIS_Msk           (0x2UL)                   /*!< SCU PMCON1: SSC1_DIS (Bitfield-Mask: 0x01)            */
#define SCU_PMCON1_ADC1_DIS_Pos           (0UL)                     /*!< SCU PMCON1: ADC1_DIS (Bit 0)                          */
#define SCU_PMCON1_ADC1_DIS_Msk           (0x1UL)                   /*!< SCU PMCON1: ADC1_DIS (Bitfield-Mask: 0x01)            */
/* ========================================================  PMCON2  ========================================================= */
#define SCU_PMCON2_T3_DIS_Pos             (5UL)                     /*!< SCU PMCON2: T3_DIS (Bit 5)                            */
#define SCU_PMCON2_T3_DIS_Msk             (0x20UL)                  /*!< SCU PMCON2: T3_DIS (Bitfield-Mask: 0x01)              */
#define SCU_PMCON2_T21_DIS_Pos            (3UL)                     /*!< SCU PMCON2: T21_DIS (Bit 3)                           */
#define SCU_PMCON2_T21_DIS_Msk            (0x8UL)                   /*!< SCU PMCON2: T21_DIS (Bitfield-Mask: 0x01)             */
#define SCU_PMCON2_SSC2_DIS_Pos           (1UL)                     /*!< SCU PMCON2: SSC2_DIS (Bit 1)                          */
#define SCU_PMCON2_SSC2_DIS_Msk           (0x2UL)                   /*!< SCU PMCON2: SSC2_DIS (Bitfield-Mask: 0x01)            */
/* ========================================================  RSTCON  ========================================================= */
#define SCU_RSTCON_LOCKUP_EN_Pos          (7UL)                     /*!< SCU RSTCON: LOCKUP_EN (Bit 7)                         */
#define SCU_RSTCON_LOCKUP_EN_Msk          (0x80UL)                  /*!< SCU RSTCON: LOCKUP_EN (Bitfield-Mask: 0x01)           */
#define SCU_RSTCON_LOCKUP_Pos             (0UL)                     /*!< SCU RSTCON: LOCKUP (Bit 0)                            */
#define SCU_RSTCON_LOCKUP_Msk             (0x1UL)                   /*!< SCU RSTCON: LOCKUP (Bitfield-Mask: 0x01)              */
/* ====================================================  SYS_STRTUP_STS  ===================================================== */
#define SCU_SYS_STRTUP_STS_PG100TP_CHKS_ERR_Pos (2UL)               /*!< SCU SYS_STRTUP_STS: PG100TP_CHKS_ERR (Bit 2)          */
#define SCU_SYS_STRTUP_STS_PG100TP_CHKS_ERR_Msk (0x4UL)             /*!< SCU SYS_STRTUP_STS: PG100TP_CHKS_ERR (Bitfield-Mask: 0x01) */
#define SCU_SYS_STRTUP_STS_MRAMINITSTS_Pos (1UL)                    /*!< SCU SYS_STRTUP_STS: MRAMINITSTS (Bit 1)               */
#define SCU_SYS_STRTUP_STS_MRAMINITSTS_Msk (0x2UL)                  /*!< SCU SYS_STRTUP_STS: MRAMINITSTS (Bitfield-Mask: 0x01) */
#define SCU_SYS_STRTUP_STS_INIT_FAIL_Pos  (0UL)                     /*!< SCU SYS_STRTUP_STS: INIT_FAIL (Bit 0)                 */
#define SCU_SYS_STRTUP_STS_INIT_FAIL_Msk  (0x1UL)                   /*!< SCU SYS_STRTUP_STS: INIT_FAIL (Bitfield-Mask: 0x01)   */
/* ========================================================  SYSCON0  ======================================================== */
#define SCU_SYSCON0_SYSCLKSEL_Pos         (6UL)                     /*!< SCU SYSCON0: SYSCLKSEL (Bit 6)                        */
#define SCU_SYSCON0_SYSCLKSEL_Msk         (0xc0UL)                  /*!< SCU SYSCON0: SYSCLKSEL (Bitfield-Mask: 0x03)          */
#define SCU_SYSCON0_NVMCLKFAC_Pos         (4UL)                     /*!< SCU SYSCON0: NVMCLKFAC (Bit 4)                        */
#define SCU_SYSCON0_NVMCLKFAC_Msk         (0x30UL)                  /*!< SCU SYSCON0: NVMCLKFAC (Bitfield-Mask: 0x03)          */
/* =========================================================  TCCR  ========================================================== */
#define SCU_TCCR_TCC_Pos                  (0UL)                     /*!< SCU TCCR: TCC (Bit 0)                                 */
#define SCU_TCCR_TCC_Msk                  (0x3UL)                   /*!< SCU TCCR: TCC (Bitfield-Mask: 0x03)                   */
/* ========================================================  WDTCON  ========================================================= */
#define SCU_WDTCON_WINBEN_Pos             (5UL)                     /*!< SCU WDTCON: WINBEN (Bit 5)                            */
#define SCU_WDTCON_WINBEN_Msk             (0x20UL)                  /*!< SCU WDTCON: WINBEN (Bitfield-Mask: 0x01)              */
#define SCU_WDTCON_WDTPR_Pos              (4UL)                     /*!< SCU WDTCON: WDTPR (Bit 4)                             */
#define SCU_WDTCON_WDTPR_Msk              (0x10UL)                  /*!< SCU WDTCON: WDTPR (Bitfield-Mask: 0x01)               */
#define SCU_WDTCON_WDTEN_Pos              (2UL)                     /*!< SCU WDTCON: WDTEN (Bit 2)                             */
#define SCU_WDTCON_WDTEN_Msk              (0x4UL)                   /*!< SCU WDTCON: WDTEN (Bitfield-Mask: 0x01)               */
#define SCU_WDTCON_WDTRS_Pos              (1UL)                     /*!< SCU WDTCON: WDTRS (Bit 1)                             */
#define SCU_WDTCON_WDTRS_Msk              (0x2UL)                   /*!< SCU WDTCON: WDTRS (Bitfield-Mask: 0x01)               */
#define SCU_WDTCON_WDTIN_Pos              (0UL)                     /*!< SCU WDTCON: WDTIN (Bit 0)                             */
#define SCU_WDTCON_WDTIN_Msk              (0x1UL)                   /*!< SCU WDTCON: WDTIN (Bitfield-Mask: 0x01)               */
/* =========================================================  WDTH  ========================================================== */
#define SCU_WDTH_WDT_Pos                  (0UL)                     /*!< SCU WDTH: WDT (Bit 0)                                 */
#define SCU_WDTH_WDT_Msk                  (0xffUL)                  /*!< SCU WDTH: WDT (Bitfield-Mask: 0xff)                   */
/* =========================================================  WDTL  ========================================================== */
#define SCU_WDTL_WDT_Pos                  (0UL)                     /*!< SCU WDTL: WDT (Bit 0)                                 */
#define SCU_WDTL_WDT_Msk                  (0xffUL)                  /*!< SCU WDTL: WDT (Bitfield-Mask: 0xff)                   */
/* ========================================================  WDTREL  ========================================================= */
#define SCU_WDTREL_WDTREL_Pos             (0UL)                     /*!< SCU WDTREL: WDTREL (Bit 0)                            */
#define SCU_WDTREL_WDTREL_Msk             (0xffUL)                  /*!< SCU WDTREL: WDTREL (Bitfield-Mask: 0xff)              */
/* ========================================================  WDTWINB  ======================================================== */
#define SCU_WDTWINB_WDTWINB_Pos           (0UL)                     /*!< SCU WDTWINB: WDTWINB (Bit 0)                          */
#define SCU_WDTWINB_WDTWINB_Msk           (0xffUL)                  /*!< SCU WDTWINB: WDTWINB (Bitfield-Mask: 0xff)            */


/* =========================================================================================================================== */
/* ================                                           SCUPM                                           ================ */
/* =========================================================================================================================== */

/* ======================================================  AMCLK_CTRL  ======================================================= */
#define SCUPM_AMCLK_CTRL_CLKWDT_PD_N_Pos  (0UL)                     /*!< SCUPM AMCLK_CTRL: CLKWDT_PD_N (Bit 0)                 */
#define SCUPM_AMCLK_CTRL_CLKWDT_PD_N_Msk  (0x1UL)                   /*!< SCUPM AMCLK_CTRL: CLKWDT_PD_N (Bitfield-Mask: 0x01)   */
/* ====================================================  AMCLK_FREQ_STS  ===================================================== */
#define SCUPM_AMCLK_FREQ_STS_AMCLK2_FREQ_Pos (8UL)                  /*!< SCUPM AMCLK_FREQ_STS: AMCLK2_FREQ (Bit 8)             */
#define SCUPM_AMCLK_FREQ_STS_AMCLK2_FREQ_Msk (0x3f00UL)             /*!< SCUPM AMCLK_FREQ_STS: AMCLK2_FREQ (Bitfield-Mask: 0x3f) */
#define SCUPM_AMCLK_FREQ_STS_AMCLK1_FREQ_Pos (0UL)                  /*!< SCUPM AMCLK_FREQ_STS: AMCLK1_FREQ (Bit 0)             */
#define SCUPM_AMCLK_FREQ_STS_AMCLK1_FREQ_Msk (0x3fUL)               /*!< SCUPM AMCLK_FREQ_STS: AMCLK1_FREQ (Bitfield-Mask: 0x3f) */
/* =====================================================  AMCLK_TH_HYS  ====================================================== */
#define SCUPM_AMCLK_TH_HYS_AMCLK2_LOW_HYS_Pos (30UL)                /*!< SCUPM AMCLK_TH_HYS: AMCLK2_LOW_HYS (Bit 30)           */
#define SCUPM_AMCLK_TH_HYS_AMCLK2_LOW_HYS_Msk (0xc0000000UL)        /*!< SCUPM AMCLK_TH_HYS: AMCLK2_LOW_HYS (Bitfield-Mask: 0x03) */
#define SCUPM_AMCLK_TH_HYS_AMCLK2_LOW_TH_Pos (24UL)                 /*!< SCUPM AMCLK_TH_HYS: AMCLK2_LOW_TH (Bit 24)            */
#define SCUPM_AMCLK_TH_HYS_AMCLK2_LOW_TH_Msk (0x3f000000UL)         /*!< SCUPM AMCLK_TH_HYS: AMCLK2_LOW_TH (Bitfield-Mask: 0x3f) */
#define SCUPM_AMCLK_TH_HYS_AMCLK2_UP_HYS_Pos (22UL)                 /*!< SCUPM AMCLK_TH_HYS: AMCLK2_UP_HYS (Bit 22)            */
#define SCUPM_AMCLK_TH_HYS_AMCLK2_UP_HYS_Msk (0xc00000UL)           /*!< SCUPM AMCLK_TH_HYS: AMCLK2_UP_HYS (Bitfield-Mask: 0x03) */
#define SCUPM_AMCLK_TH_HYS_AMCLK2_UP_TH_Pos (16UL)                  /*!< SCUPM AMCLK_TH_HYS: AMCLK2_UP_TH (Bit 16)             */
#define SCUPM_AMCLK_TH_HYS_AMCLK2_UP_TH_Msk (0x3f0000UL)            /*!< SCUPM AMCLK_TH_HYS: AMCLK2_UP_TH (Bitfield-Mask: 0x3f) */
#define SCUPM_AMCLK_TH_HYS_AMCLK1_LOW_HYS_Pos (14UL)                /*!< SCUPM AMCLK_TH_HYS: AMCLK1_LOW_HYS (Bit 14)           */
#define SCUPM_AMCLK_TH_HYS_AMCLK1_LOW_HYS_Msk (0xc000UL)            /*!< SCUPM AMCLK_TH_HYS: AMCLK1_LOW_HYS (Bitfield-Mask: 0x03) */
#define SCUPM_AMCLK_TH_HYS_AMCLK1_LOW_TH_Pos (8UL)                  /*!< SCUPM AMCLK_TH_HYS: AMCLK1_LOW_TH (Bit 8)             */
#define SCUPM_AMCLK_TH_HYS_AMCLK1_LOW_TH_Msk (0x3f00UL)             /*!< SCUPM AMCLK_TH_HYS: AMCLK1_LOW_TH (Bitfield-Mask: 0x3f) */
#define SCUPM_AMCLK_TH_HYS_AMCLK1_UP_HYS_Pos (6UL)                  /*!< SCUPM AMCLK_TH_HYS: AMCLK1_UP_HYS (Bit 6)             */
#define SCUPM_AMCLK_TH_HYS_AMCLK1_UP_HYS_Msk (0xc0UL)               /*!< SCUPM AMCLK_TH_HYS: AMCLK1_UP_HYS (Bitfield-Mask: 0x03) */
#define SCUPM_AMCLK_TH_HYS_AMCLK1_UP_TH_Pos (0UL)                   /*!< SCUPM AMCLK_TH_HYS: AMCLK1_UP_TH (Bit 0)              */
#define SCUPM_AMCLK_TH_HYS_AMCLK1_UP_TH_Msk (0x3fUL)                /*!< SCUPM AMCLK_TH_HYS: AMCLK1_UP_TH (Bitfield-Mask: 0x3f) */
/* =====================================================  BDRV_IRQ_CTRL  ===================================================== */
#define SCUPM_BDRV_IRQ_CTRL_VSD_UPTH_IE_Pos (20UL)                  /*!< SCUPM BDRV_IRQ_CTRL: VSD_UPTH_IE (Bit 20)             */
#define SCUPM_BDRV_IRQ_CTRL_VSD_UPTH_IE_Msk (0x100000UL)            /*!< SCUPM BDRV_IRQ_CTRL: VSD_UPTH_IE (Bitfield-Mask: 0x01) */
#define SCUPM_BDRV_IRQ_CTRL_VSD_LOWTH_IE_Pos (19UL)                 /*!< SCUPM BDRV_IRQ_CTRL: VSD_LOWTH_IE (Bit 19)            */
#define SCUPM_BDRV_IRQ_CTRL_VSD_LOWTH_IE_Msk (0x80000UL)            /*!< SCUPM BDRV_IRQ_CTRL: VSD_LOWTH_IE (Bitfield-Mask: 0x01) */
#define SCUPM_BDRV_IRQ_CTRL_VCP_UPTH_IE_Pos (18UL)                  /*!< SCUPM BDRV_IRQ_CTRL: VCP_UPTH_IE (Bit 18)             */
#define SCUPM_BDRV_IRQ_CTRL_VCP_UPTH_IE_Msk (0x40000UL)             /*!< SCUPM BDRV_IRQ_CTRL: VCP_UPTH_IE (Bitfield-Mask: 0x01) */
#define SCUPM_BDRV_IRQ_CTRL_VCP_LOWTH1_IE_Pos (17UL)                /*!< SCUPM BDRV_IRQ_CTRL: VCP_LOWTH1_IE (Bit 17)           */
#define SCUPM_BDRV_IRQ_CTRL_VCP_LOWTH1_IE_Msk (0x20000UL)           /*!< SCUPM BDRV_IRQ_CTRL: VCP_LOWTH1_IE (Bitfield-Mask: 0x01) */
#define SCUPM_BDRV_IRQ_CTRL_VCP_LOWTH2_IE_Pos (16UL)                /*!< SCUPM BDRV_IRQ_CTRL: VCP_LOWTH2_IE (Bit 16)           */
#define SCUPM_BDRV_IRQ_CTRL_VCP_LOWTH2_IE_Msk (0x10000UL)           /*!< SCUPM BDRV_IRQ_CTRL: VCP_LOWTH2_IE (Bitfield-Mask: 0x01) */
#define SCUPM_BDRV_IRQ_CTRL_HS3_OC_IE_Pos (15UL)                    /*!< SCUPM BDRV_IRQ_CTRL: HS3_OC_IE (Bit 15)               */
#define SCUPM_BDRV_IRQ_CTRL_HS3_OC_IE_Msk (0x8000UL)                /*!< SCUPM BDRV_IRQ_CTRL: HS3_OC_IE (Bitfield-Mask: 0x01)  */
#define SCUPM_BDRV_IRQ_CTRL_LS3_OC_IE_Pos (14UL)                    /*!< SCUPM BDRV_IRQ_CTRL: LS3_OC_IE (Bit 14)               */
#define SCUPM_BDRV_IRQ_CTRL_LS3_OC_IE_Msk (0x4000UL)                /*!< SCUPM BDRV_IRQ_CTRL: LS3_OC_IE (Bitfield-Mask: 0x01)  */
#define SCUPM_BDRV_IRQ_CTRL_HS2_OC_IE_Pos (13UL)                    /*!< SCUPM BDRV_IRQ_CTRL: HS2_OC_IE (Bit 13)               */
#define SCUPM_BDRV_IRQ_CTRL_HS2_OC_IE_Msk (0x2000UL)                /*!< SCUPM BDRV_IRQ_CTRL: HS2_OC_IE (Bitfield-Mask: 0x01)  */
#define SCUPM_BDRV_IRQ_CTRL_HS1_OC_IE_Pos (12UL)                    /*!< SCUPM BDRV_IRQ_CTRL: HS1_OC_IE (Bit 12)               */
#define SCUPM_BDRV_IRQ_CTRL_HS1_OC_IE_Msk (0x1000UL)                /*!< SCUPM BDRV_IRQ_CTRL: HS1_OC_IE (Bitfield-Mask: 0x01)  */
#define SCUPM_BDRV_IRQ_CTRL_LS2_OC_IE_Pos (11UL)                    /*!< SCUPM BDRV_IRQ_CTRL: LS2_OC_IE (Bit 11)               */
#define SCUPM_BDRV_IRQ_CTRL_LS2_OC_IE_Msk (0x800UL)                 /*!< SCUPM BDRV_IRQ_CTRL: LS2_OC_IE (Bitfield-Mask: 0x01)  */
#define SCUPM_BDRV_IRQ_CTRL_LS1_OC_IE_Pos (10UL)                    /*!< SCUPM BDRV_IRQ_CTRL: LS1_OC_IE (Bit 10)               */
#define SCUPM_BDRV_IRQ_CTRL_LS1_OC_IE_Msk (0x400UL)                 /*!< SCUPM BDRV_IRQ_CTRL: LS1_OC_IE (Bitfield-Mask: 0x01)  */
#define SCUPM_BDRV_IRQ_CTRL_HS3_DS_IE_Pos (5UL)                     /*!< SCUPM BDRV_IRQ_CTRL: HS3_DS_IE (Bit 5)                */
#define SCUPM_BDRV_IRQ_CTRL_HS3_DS_IE_Msk (0x20UL)                  /*!< SCUPM BDRV_IRQ_CTRL: HS3_DS_IE (Bitfield-Mask: 0x01)  */
#define SCUPM_BDRV_IRQ_CTRL_LS3_DS_IE_Pos (4UL)                     /*!< SCUPM BDRV_IRQ_CTRL: LS3_DS_IE (Bit 4)                */
#define SCUPM_BDRV_IRQ_CTRL_LS3_DS_IE_Msk (0x10UL)                  /*!< SCUPM BDRV_IRQ_CTRL: LS3_DS_IE (Bitfield-Mask: 0x01)  */
#define SCUPM_BDRV_IRQ_CTRL_HS2_DS_IE_Pos (3UL)                     /*!< SCUPM BDRV_IRQ_CTRL: HS2_DS_IE (Bit 3)                */
#define SCUPM_BDRV_IRQ_CTRL_HS2_DS_IE_Msk (0x8UL)                   /*!< SCUPM BDRV_IRQ_CTRL: HS2_DS_IE (Bitfield-Mask: 0x01)  */
#define SCUPM_BDRV_IRQ_CTRL_HS1_DS_IE_Pos (2UL)                     /*!< SCUPM BDRV_IRQ_CTRL: HS1_DS_IE (Bit 2)                */
#define SCUPM_BDRV_IRQ_CTRL_HS1_DS_IE_Msk (0x4UL)                   /*!< SCUPM BDRV_IRQ_CTRL: HS1_DS_IE (Bitfield-Mask: 0x01)  */
#define SCUPM_BDRV_IRQ_CTRL_LS2_DS_IE_Pos (1UL)                     /*!< SCUPM BDRV_IRQ_CTRL: LS2_DS_IE (Bit 1)                */
#define SCUPM_BDRV_IRQ_CTRL_LS2_DS_IE_Msk (0x2UL)                   /*!< SCUPM BDRV_IRQ_CTRL: LS2_DS_IE (Bitfield-Mask: 0x01)  */
#define SCUPM_BDRV_IRQ_CTRL_LS1_DS_IE_Pos (0UL)                     /*!< SCUPM BDRV_IRQ_CTRL: LS1_DS_IE (Bit 0)                */
#define SCUPM_BDRV_IRQ_CTRL_LS1_DS_IE_Msk (0x1UL)                   /*!< SCUPM BDRV_IRQ_CTRL: LS1_DS_IE (Bitfield-Mask: 0x01)  */
/* ========================================================  BDRV_IS  ======================================================== */
#define SCUPM_BDRV_IS_VSD_UPTH_STS_Pos    (28UL)                    /*!< SCUPM BDRV_IS: VSD_UPTH_STS (Bit 28)                  */
#define SCUPM_BDRV_IS_VSD_UPTH_STS_Msk    (0x10000000UL)            /*!< SCUPM BDRV_IS: VSD_UPTH_STS (Bitfield-Mask: 0x01)     */
#define SCUPM_BDRV_IS_VSD_LOWTH_STS_Pos   (27UL)                    /*!< SCUPM BDRV_IS: VSD_LOWTH_STS (Bit 27)                 */
#define SCUPM_BDRV_IS_VSD_LOWTH_STS_Msk   (0x8000000UL)             /*!< SCUPM BDRV_IS: VSD_LOWTH_STS (Bitfield-Mask: 0x01)    */
#define SCUPM_BDRV_IS_VCP_UPTH_STS_Pos    (26UL)                    /*!< SCUPM BDRV_IS: VCP_UPTH_STS (Bit 26)                  */
#define SCUPM_BDRV_IS_VCP_UPTH_STS_Msk    (0x4000000UL)             /*!< SCUPM BDRV_IS: VCP_UPTH_STS (Bitfield-Mask: 0x01)     */
#define SCUPM_BDRV_IS_VCP_LOWTH1_STS_Pos  (25UL)                    /*!< SCUPM BDRV_IS: VCP_LOWTH1_STS (Bit 25)                */
#define SCUPM_BDRV_IS_VCP_LOWTH1_STS_Msk  (0x2000000UL)             /*!< SCUPM BDRV_IS: VCP_LOWTH1_STS (Bitfield-Mask: 0x01)   */
#define SCUPM_BDRV_IS_VCP_LOWTH2_STS_Pos  (24UL)                    /*!< SCUPM BDRV_IS: VCP_LOWTH2_STS (Bit 24)                */
#define SCUPM_BDRV_IS_VCP_LOWTH2_STS_Msk  (0x1000000UL)             /*!< SCUPM BDRV_IS: VCP_LOWTH2_STS (Bitfield-Mask: 0x01)   */
#define SCUPM_BDRV_IS_VSD_UPTH_IS_Pos     (20UL)                    /*!< SCUPM BDRV_IS: VSD_UPTH_IS (Bit 20)                   */
#define SCUPM_BDRV_IS_VSD_UPTH_IS_Msk     (0x100000UL)              /*!< SCUPM BDRV_IS: VSD_UPTH_IS (Bitfield-Mask: 0x01)      */
#define SCUPM_BDRV_IS_VSD_LOWTH_IS_Pos    (19UL)                    /*!< SCUPM BDRV_IS: VSD_LOWTH_IS (Bit 19)                  */
#define SCUPM_BDRV_IS_VSD_LOWTH_IS_Msk    (0x80000UL)               /*!< SCUPM BDRV_IS: VSD_LOWTH_IS (Bitfield-Mask: 0x01)     */
#define SCUPM_BDRV_IS_VCP_UPTH_IS_Pos     (18UL)                    /*!< SCUPM BDRV_IS: VCP_UPTH_IS (Bit 18)                   */
#define SCUPM_BDRV_IS_VCP_UPTH_IS_Msk     (0x40000UL)               /*!< SCUPM BDRV_IS: VCP_UPTH_IS (Bitfield-Mask: 0x01)      */
#define SCUPM_BDRV_IS_VCP_LOWTH1_IS_Pos   (17UL)                    /*!< SCUPM BDRV_IS: VCP_LOWTH1_IS (Bit 17)                 */
#define SCUPM_BDRV_IS_VCP_LOWTH1_IS_Msk   (0x20000UL)               /*!< SCUPM BDRV_IS: VCP_LOWTH1_IS (Bitfield-Mask: 0x01)    */
#define SCUPM_BDRV_IS_VCP_LOWTH2_IS_Pos   (16UL)                    /*!< SCUPM BDRV_IS: VCP_LOWTH2_IS (Bit 16)                 */
#define SCUPM_BDRV_IS_VCP_LOWTH2_IS_Msk   (0x10000UL)               /*!< SCUPM BDRV_IS: VCP_LOWTH2_IS (Bitfield-Mask: 0x01)    */
#define SCUPM_BDRV_IS_HS3_OC_IS_Pos       (15UL)                    /*!< SCUPM BDRV_IS: HS3_OC_IS (Bit 15)                     */
#define SCUPM_BDRV_IS_HS3_OC_IS_Msk       (0x8000UL)                /*!< SCUPM BDRV_IS: HS3_OC_IS (Bitfield-Mask: 0x01)        */
#define SCUPM_BDRV_IS_LS3_OC_IS_Pos       (14UL)                    /*!< SCUPM BDRV_IS: LS3_OC_IS (Bit 14)                     */
#define SCUPM_BDRV_IS_LS3_OC_IS_Msk       (0x4000UL)                /*!< SCUPM BDRV_IS: LS3_OC_IS (Bitfield-Mask: 0x01)        */
#define SCUPM_BDRV_IS_HS2_OC_IS_Pos       (13UL)                    /*!< SCUPM BDRV_IS: HS2_OC_IS (Bit 13)                     */
#define SCUPM_BDRV_IS_HS2_OC_IS_Msk       (0x2000UL)                /*!< SCUPM BDRV_IS: HS2_OC_IS (Bitfield-Mask: 0x01)        */
#define SCUPM_BDRV_IS_HS1_OC_IS_Pos       (12UL)                    /*!< SCUPM BDRV_IS: HS1_OC_IS (Bit 12)                     */
#define SCUPM_BDRV_IS_HS1_OC_IS_Msk       (0x1000UL)                /*!< SCUPM BDRV_IS: HS1_OC_IS (Bitfield-Mask: 0x01)        */
#define SCUPM_BDRV_IS_LS2_OC_IS_Pos       (11UL)                    /*!< SCUPM BDRV_IS: LS2_OC_IS (Bit 11)                     */
#define SCUPM_BDRV_IS_LS2_OC_IS_Msk       (0x800UL)                 /*!< SCUPM BDRV_IS: LS2_OC_IS (Bitfield-Mask: 0x01)        */
#define SCUPM_BDRV_IS_LS1_OC_IS_Pos       (10UL)                    /*!< SCUPM BDRV_IS: LS1_OC_IS (Bit 10)                     */
#define SCUPM_BDRV_IS_LS1_OC_IS_Msk       (0x400UL)                 /*!< SCUPM BDRV_IS: LS1_OC_IS (Bitfield-Mask: 0x01)        */
#define SCUPM_BDRV_IS_HS3_DS_IS_Pos       (5UL)                     /*!< SCUPM BDRV_IS: HS3_DS_IS (Bit 5)                      */
#define SCUPM_BDRV_IS_HS3_DS_IS_Msk       (0x20UL)                  /*!< SCUPM BDRV_IS: HS3_DS_IS (Bitfield-Mask: 0x01)        */
#define SCUPM_BDRV_IS_LS3_DS_IS_Pos       (4UL)                     /*!< SCUPM BDRV_IS: LS3_DS_IS (Bit 4)                      */
#define SCUPM_BDRV_IS_LS3_DS_IS_Msk       (0x10UL)                  /*!< SCUPM BDRV_IS: LS3_DS_IS (Bitfield-Mask: 0x01)        */
#define SCUPM_BDRV_IS_HS2_DS_IS_Pos       (3UL)                     /*!< SCUPM BDRV_IS: HS2_DS_IS (Bit 3)                      */
#define SCUPM_BDRV_IS_HS2_DS_IS_Msk       (0x8UL)                   /*!< SCUPM BDRV_IS: HS2_DS_IS (Bitfield-Mask: 0x01)        */
#define SCUPM_BDRV_IS_HS1_DS_IS_Pos       (2UL)                     /*!< SCUPM BDRV_IS: HS1_DS_IS (Bit 2)                      */
#define SCUPM_BDRV_IS_HS1_DS_IS_Msk       (0x4UL)                   /*!< SCUPM BDRV_IS: HS1_DS_IS (Bitfield-Mask: 0x01)        */
#define SCUPM_BDRV_IS_LS2_DS_IS_Pos       (1UL)                     /*!< SCUPM BDRV_IS: LS2_DS_IS (Bit 1)                      */
#define SCUPM_BDRV_IS_LS2_DS_IS_Msk       (0x2UL)                   /*!< SCUPM BDRV_IS: LS2_DS_IS (Bitfield-Mask: 0x01)        */
#define SCUPM_BDRV_IS_LS1_DS_IS_Pos       (0UL)                     /*!< SCUPM BDRV_IS: LS1_DS_IS (Bit 0)                      */
#define SCUPM_BDRV_IS_LS1_DS_IS_Msk       (0x1UL)                   /*!< SCUPM BDRV_IS: LS1_DS_IS (Bitfield-Mask: 0x01)        */
/* ======================================================  BDRV_ISCLR  ======================================================= */
#define SCUPM_BDRV_ISCLR_VSD_UPTH_SCLR_Pos (28UL)                   /*!< SCUPM BDRV_ISCLR: VSD_UPTH_SCLR (Bit 28)              */
#define SCUPM_BDRV_ISCLR_VSD_UPTH_SCLR_Msk (0x10000000UL)           /*!< SCUPM BDRV_ISCLR: VSD_UPTH_SCLR (Bitfield-Mask: 0x01) */
#define SCUPM_BDRV_ISCLR_VSD_LOWTH_SCLR_Pos (27UL)                  /*!< SCUPM BDRV_ISCLR: VSD_LOWTH_SCLR (Bit 27)             */
#define SCUPM_BDRV_ISCLR_VSD_LOWTH_SCLR_Msk (0x8000000UL)           /*!< SCUPM BDRV_ISCLR: VSD_LOWTH_SCLR (Bitfield-Mask: 0x01) */
#define SCUPM_BDRV_ISCLR_VCP_UPTH_SCLR_Pos (26UL)                   /*!< SCUPM BDRV_ISCLR: VCP_UPTH_SCLR (Bit 26)              */
#define SCUPM_BDRV_ISCLR_VCP_UPTH_SCLR_Msk (0x4000000UL)            /*!< SCUPM BDRV_ISCLR: VCP_UPTH_SCLR (Bitfield-Mask: 0x01) */
#define SCUPM_BDRV_ISCLR_VCP_LOWTH1_SCLR_Pos (25UL)                 /*!< SCUPM BDRV_ISCLR: VCP_LOWTH1_SCLR (Bit 25)            */
#define SCUPM_BDRV_ISCLR_VCP_LOWTH1_SCLR_Msk (0x2000000UL)          /*!< SCUPM BDRV_ISCLR: VCP_LOWTH1_SCLR (Bitfield-Mask: 0x01) */
#define SCUPM_BDRV_ISCLR_VCP_LOWTH2_SCLR_Pos (24UL)                 /*!< SCUPM BDRV_ISCLR: VCP_LOWTH2_SCLR (Bit 24)            */
#define SCUPM_BDRV_ISCLR_VCP_LOWTH2_SCLR_Msk (0x1000000UL)          /*!< SCUPM BDRV_ISCLR: VCP_LOWTH2_SCLR (Bitfield-Mask: 0x01) */
#define SCUPM_BDRV_ISCLR_VSD_UPTH_ICLR_Pos (20UL)                   /*!< SCUPM BDRV_ISCLR: VSD_UPTH_ICLR (Bit 20)              */
#define SCUPM_BDRV_ISCLR_VSD_UPTH_ICLR_Msk (0x100000UL)             /*!< SCUPM BDRV_ISCLR: VSD_UPTH_ICLR (Bitfield-Mask: 0x01) */
#define SCUPM_BDRV_ISCLR_VSD_LOWTH_ICLR_Pos (19UL)                  /*!< SCUPM BDRV_ISCLR: VSD_LOWTH_ICLR (Bit 19)             */
#define SCUPM_BDRV_ISCLR_VSD_LOWTH_ICLR_Msk (0x80000UL)             /*!< SCUPM BDRV_ISCLR: VSD_LOWTH_ICLR (Bitfield-Mask: 0x01) */
#define SCUPM_BDRV_ISCLR_VCP_UPTH_ICLR_Pos (18UL)                   /*!< SCUPM BDRV_ISCLR: VCP_UPTH_ICLR (Bit 18)              */
#define SCUPM_BDRV_ISCLR_VCP_UPTH_ICLR_Msk (0x40000UL)              /*!< SCUPM BDRV_ISCLR: VCP_UPTH_ICLR (Bitfield-Mask: 0x01) */
#define SCUPM_BDRV_ISCLR_VCP_LOWTH1_ICLR_Pos (17UL)                 /*!< SCUPM BDRV_ISCLR: VCP_LOWTH1_ICLR (Bit 17)            */
#define SCUPM_BDRV_ISCLR_VCP_LOWTH1_ICLR_Msk (0x20000UL)            /*!< SCUPM BDRV_ISCLR: VCP_LOWTH1_ICLR (Bitfield-Mask: 0x01) */
#define SCUPM_BDRV_ISCLR_VCP_LOWTH2_ICLR_Pos (16UL)                 /*!< SCUPM BDRV_ISCLR: VCP_LOWTH2_ICLR (Bit 16)            */
#define SCUPM_BDRV_ISCLR_VCP_LOWTH2_ICLR_Msk (0x10000UL)            /*!< SCUPM BDRV_ISCLR: VCP_LOWTH2_ICLR (Bitfield-Mask: 0x01) */
#define SCUPM_BDRV_ISCLR_HS3_OC_ICLR_Pos  (15UL)                    /*!< SCUPM BDRV_ISCLR: HS3_OC_ICLR (Bit 15)                */
#define SCUPM_BDRV_ISCLR_HS3_OC_ICLR_Msk  (0x8000UL)                /*!< SCUPM BDRV_ISCLR: HS3_OC_ICLR (Bitfield-Mask: 0x01)   */
#define SCUPM_BDRV_ISCLR_LS3_OC_ICLR_Pos  (14UL)                    /*!< SCUPM BDRV_ISCLR: LS3_OC_ICLR (Bit 14)                */
#define SCUPM_BDRV_ISCLR_LS3_OC_ICLR_Msk  (0x4000UL)                /*!< SCUPM BDRV_ISCLR: LS3_OC_ICLR (Bitfield-Mask: 0x01)   */
#define SCUPM_BDRV_ISCLR_HS2_OC_ICLR_Pos  (13UL)                    /*!< SCUPM BDRV_ISCLR: HS2_OC_ICLR (Bit 13)                */
#define SCUPM_BDRV_ISCLR_HS2_OC_ICLR_Msk  (0x2000UL)                /*!< SCUPM BDRV_ISCLR: HS2_OC_ICLR (Bitfield-Mask: 0x01)   */
#define SCUPM_BDRV_ISCLR_HS1_OC_ICLR_Pos  (12UL)                    /*!< SCUPM BDRV_ISCLR: HS1_OC_ICLR (Bit 12)                */
#define SCUPM_BDRV_ISCLR_HS1_OC_ICLR_Msk  (0x1000UL)                /*!< SCUPM BDRV_ISCLR: HS1_OC_ICLR (Bitfield-Mask: 0x01)   */
#define SCUPM_BDRV_ISCLR_LS2_OC_ICLR_Pos  (11UL)                    /*!< SCUPM BDRV_ISCLR: LS2_OC_ICLR (Bit 11)                */
#define SCUPM_BDRV_ISCLR_LS2_OC_ICLR_Msk  (0x800UL)                 /*!< SCUPM BDRV_ISCLR: LS2_OC_ICLR (Bitfield-Mask: 0x01)   */
#define SCUPM_BDRV_ISCLR_LS1_OC_ICLR_Pos  (10UL)                    /*!< SCUPM BDRV_ISCLR: LS1_OC_ICLR (Bit 10)                */
#define SCUPM_BDRV_ISCLR_LS1_OC_ICLR_Msk  (0x400UL)                 /*!< SCUPM BDRV_ISCLR: LS1_OC_ICLR (Bitfield-Mask: 0x01)   */
#define SCUPM_BDRV_ISCLR_HS3_DS_ICLR_Pos  (5UL)                     /*!< SCUPM BDRV_ISCLR: HS3_DS_ICLR (Bit 5)                 */
#define SCUPM_BDRV_ISCLR_HS3_DS_ICLR_Msk  (0x20UL)                  /*!< SCUPM BDRV_ISCLR: HS3_DS_ICLR (Bitfield-Mask: 0x01)   */
#define SCUPM_BDRV_ISCLR_LS3_DS_ICLR_Pos  (4UL)                     /*!< SCUPM BDRV_ISCLR: LS3_DS_ICLR (Bit 4)                 */
#define SCUPM_BDRV_ISCLR_LS3_DS_ICLR_Msk  (0x10UL)                  /*!< SCUPM BDRV_ISCLR: LS3_DS_ICLR (Bitfield-Mask: 0x01)   */
#define SCUPM_BDRV_ISCLR_HS2_DS_ICLR_Pos  (3UL)                     /*!< SCUPM BDRV_ISCLR: HS2_DS_ICLR (Bit 3)                 */
#define SCUPM_BDRV_ISCLR_HS2_DS_ICLR_Msk  (0x8UL)                   /*!< SCUPM BDRV_ISCLR: HS2_DS_ICLR (Bitfield-Mask: 0x01)   */
#define SCUPM_BDRV_ISCLR_HS1_DS_ICLR_Pos  (2UL)                     /*!< SCUPM BDRV_ISCLR: HS1_DS_ICLR (Bit 2)                 */
#define SCUPM_BDRV_ISCLR_HS1_DS_ICLR_Msk  (0x4UL)                   /*!< SCUPM BDRV_ISCLR: HS1_DS_ICLR (Bitfield-Mask: 0x01)   */
#define SCUPM_BDRV_ISCLR_LS2_DS_ICLR_Pos  (1UL)                     /*!< SCUPM BDRV_ISCLR: LS2_DS_ICLR (Bit 1)                 */
#define SCUPM_BDRV_ISCLR_LS2_DS_ICLR_Msk  (0x2UL)                   /*!< SCUPM BDRV_ISCLR: LS2_DS_ICLR (Bitfield-Mask: 0x01)   */
#define SCUPM_BDRV_ISCLR_LS1_DS_ICLR_Pos  (0UL)                     /*!< SCUPM BDRV_ISCLR: LS1_DS_ICLR (Bit 0)                 */
#define SCUPM_BDRV_ISCLR_LS1_DS_ICLR_Msk  (0x1UL)                   /*!< SCUPM BDRV_ISCLR: LS1_DS_ICLR (Bitfield-Mask: 0x01)   */
/* =========================================================  BFSTS  ========================================================= */
#define SCUPM_BFSTS_SBFSTS_Pos            (1UL)                     /*!< SCUPM BFSTS: SBFSTS (Bit 1)                           */
#define SCUPM_BFSTS_SBFSTS_Msk            (0x2UL)                   /*!< SCUPM BFSTS: SBFSTS (Bitfield-Mask: 0x01)             */
#define SCUPM_BFSTS_DBFSTS_Pos            (0UL)                     /*!< SCUPM BFSTS: DBFSTS (Bit 0)                           */
#define SCUPM_BFSTS_DBFSTS_Msk            (0x1UL)                   /*!< SCUPM BFSTS: DBFSTS (Bitfield-Mask: 0x01)             */
/* =======================================================  BFSTS_CLR  ======================================================= */
#define SCUPM_BFSTS_CLR_SBFSTSCLR_Pos     (1UL)                     /*!< SCUPM BFSTS_CLR: SBFSTSCLR (Bit 1)                    */
#define SCUPM_BFSTS_CLR_SBFSTSCLR_Msk     (0x2UL)                   /*!< SCUPM BFSTS_CLR: SBFSTSCLR (Bitfield-Mask: 0x01)      */
#define SCUPM_BFSTS_CLR_DBFSTSCLR_Pos     (0UL)                     /*!< SCUPM BFSTS_CLR: DBFSTSCLR (Bit 0)                    */
#define SCUPM_BFSTS_CLR_DBFSTSCLR_Msk     (0x1UL)                   /*!< SCUPM BFSTS_CLR: DBFSTSCLR (Bitfield-Mask: 0x01)      */
/* =========================================================  DBFA  ========================================================== */
#define SCUPM_DBFA_DBFA_Pos               (0UL)                     /*!< SCUPM DBFA: DBFA (Bit 0)                              */
#define SCUPM_DBFA_DBFA_Msk               (0xffffffffUL)            /*!< SCUPM DBFA: DBFA (Bitfield-Mask: 0xffffffff)          */
/* =====================================================  PCU_CTRL_STS  ====================================================== */
#define SCUPM_PCU_CTRL_STS_CLKWDT_RES_SD_DIS_Pos (26UL)             /*!< SCUPM PCU_CTRL_STS: CLKWDT_RES_SD_DIS (Bit 26)        */
#define SCUPM_PCU_CTRL_STS_CLKWDT_RES_SD_DIS_Msk (0x4000000UL)      /*!< SCUPM PCU_CTRL_STS: CLKWDT_RES_SD_DIS (Bitfield-Mask: 0x01) */
#define SCUPM_PCU_CTRL_STS_CLKLOSS_SD_DIS_Pos (25UL)                /*!< SCUPM PCU_CTRL_STS: CLKLOSS_SD_DIS (Bit 25)           */
#define SCUPM_PCU_CTRL_STS_CLKLOSS_SD_DIS_Msk (0x2000000UL)         /*!< SCUPM PCU_CTRL_STS: CLKLOSS_SD_DIS (Bitfield-Mask: 0x01) */
#define SCUPM_PCU_CTRL_STS_SYS_OT_PS_DIS_Pos (24UL)                 /*!< SCUPM PCU_CTRL_STS: SYS_OT_PS_DIS (Bit 24)            */
#define SCUPM_PCU_CTRL_STS_SYS_OT_PS_DIS_Msk (0x1000000UL)          /*!< SCUPM PCU_CTRL_STS: SYS_OT_PS_DIS (Bitfield-Mask: 0x01) */
#define SCUPM_PCU_CTRL_STS_SYS_VSD_OV_SLM_DIS_Pos (14UL)            /*!< SCUPM PCU_CTRL_STS: SYS_VSD_OV_SLM_DIS (Bit 14)       */
#define SCUPM_PCU_CTRL_STS_SYS_VSD_OV_SLM_DIS_Msk (0x4000UL)        /*!< SCUPM PCU_CTRL_STS: SYS_VSD_OV_SLM_DIS (Bitfield-Mask: 0x01) */
#define SCUPM_PCU_CTRL_STS_LIN_VS_UV_SD_DIS_Pos (8UL)               /*!< SCUPM PCU_CTRL_STS: LIN_VS_UV_SD_DIS (Bit 8)          */
#define SCUPM_PCU_CTRL_STS_LIN_VS_UV_SD_DIS_Msk (0x100UL)           /*!< SCUPM PCU_CTRL_STS: LIN_VS_UV_SD_DIS (Bitfield-Mask: 0x01) */
#define SCUPM_PCU_CTRL_STS_FAIL_PS_DIS_Pos (7UL)                    /*!< SCUPM PCU_CTRL_STS: FAIL_PS_DIS (Bit 7)               */
#define SCUPM_PCU_CTRL_STS_FAIL_PS_DIS_Msk (0x80UL)                 /*!< SCUPM PCU_CTRL_STS: FAIL_PS_DIS (Bitfield-Mask: 0x01) */
#define SCUPM_PCU_CTRL_STS_CLKWDT_SD_DIS_Pos (1UL)                  /*!< SCUPM PCU_CTRL_STS: CLKWDT_SD_DIS (Bit 1)             */
#define SCUPM_PCU_CTRL_STS_CLKWDT_SD_DIS_Msk (0x2UL)                /*!< SCUPM PCU_CTRL_STS: CLKWDT_SD_DIS (Bitfield-Mask: 0x01) */
/* =========================================================  SBFA  ========================================================== */
#define SCUPM_SBFA_SBFA_Pos               (0UL)                     /*!< SCUPM SBFA: SBFA (Bit 0)                              */
#define SCUPM_SBFA_SBFA_Msk               (0xffffffffUL)            /*!< SCUPM SBFA: SBFA (Bitfield-Mask: 0xffffffff)          */
/* ========================================================  STCALIB  ======================================================== */
#define SCUPM_STCALIB_STCALIB_Pos         (0UL)                     /*!< SCUPM STCALIB: STCALIB (Bit 0)                        */
#define SCUPM_STCALIB_STCALIB_Msk         (0x3ffffffUL)             /*!< SCUPM STCALIB: STCALIB (Bitfield-Mask: 0x3ffffff)     */
/* =====================================================  SYS_IRQ_CTRL  ====================================================== */
#define SCUPM_SYS_IRQ_CTRL_ADC4_EOC_IE_Pos (23UL)                   /*!< SCUPM SYS_IRQ_CTRL: ADC4_EOC_IE (Bit 23)              */
#define SCUPM_SYS_IRQ_CTRL_ADC4_EOC_IE_Msk (0x800000UL)             /*!< SCUPM SYS_IRQ_CTRL: ADC4_EOC_IE (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_IRQ_CTRL_ADC3_EOC_IE_Pos (22UL)                   /*!< SCUPM SYS_IRQ_CTRL: ADC3_EOC_IE (Bit 22)              */
#define SCUPM_SYS_IRQ_CTRL_ADC3_EOC_IE_Msk (0x400000UL)             /*!< SCUPM SYS_IRQ_CTRL: ADC3_EOC_IE (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_IRQ_CTRL_PHW_ZCHI_IE_Pos (21UL)                   /*!< SCUPM SYS_IRQ_CTRL: PHW_ZCHI_IE (Bit 21)              */
#define SCUPM_SYS_IRQ_CTRL_PHW_ZCHI_IE_Msk (0x200000UL)             /*!< SCUPM SYS_IRQ_CTRL: PHW_ZCHI_IE (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_IRQ_CTRL_PHW_ZCLOW_IE_Pos (20UL)                  /*!< SCUPM SYS_IRQ_CTRL: PHW_ZCLOW_IE (Bit 20)             */
#define SCUPM_SYS_IRQ_CTRL_PHW_ZCLOW_IE_Msk (0x100000UL)            /*!< SCUPM SYS_IRQ_CTRL: PHW_ZCLOW_IE (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_IRQ_CTRL_PHV_ZCHI_IE_Pos (19UL)                   /*!< SCUPM SYS_IRQ_CTRL: PHV_ZCHI_IE (Bit 19)              */
#define SCUPM_SYS_IRQ_CTRL_PHV_ZCHI_IE_Msk (0x80000UL)              /*!< SCUPM SYS_IRQ_CTRL: PHV_ZCHI_IE (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_IRQ_CTRL_PHV_ZCLOW_IE_Pos (18UL)                  /*!< SCUPM SYS_IRQ_CTRL: PHV_ZCLOW_IE (Bit 18)             */
#define SCUPM_SYS_IRQ_CTRL_PHV_ZCLOW_IE_Msk (0x40000UL)             /*!< SCUPM SYS_IRQ_CTRL: PHV_ZCLOW_IE (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_IRQ_CTRL_PHU_ZCHI_IE_Pos (17UL)                   /*!< SCUPM SYS_IRQ_CTRL: PHU_ZCHI_IE (Bit 17)              */
#define SCUPM_SYS_IRQ_CTRL_PHU_ZCHI_IE_Msk (0x20000UL)              /*!< SCUPM SYS_IRQ_CTRL: PHU_ZCHI_IE (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_IRQ_CTRL_PHU_ZCLOW_IE_Pos (16UL)                  /*!< SCUPM SYS_IRQ_CTRL: PHU_ZCLOW_IE (Bit 16)             */
#define SCUPM_SYS_IRQ_CTRL_PHU_ZCLOW_IE_Msk (0x10000UL)             /*!< SCUPM SYS_IRQ_CTRL: PHU_ZCLOW_IE (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_IRQ_CTRL_ADC2_ESM_IE_Pos (15UL)                   /*!< SCUPM SYS_IRQ_CTRL: ADC2_ESM_IE (Bit 15)              */
#define SCUPM_SYS_IRQ_CTRL_ADC2_ESM_IE_Msk (0x8000UL)               /*!< SCUPM SYS_IRQ_CTRL: ADC2_ESM_IE (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_IRQ_CTRL_VREF5V_OVL_IE_Pos (14UL)                 /*!< SCUPM SYS_IRQ_CTRL: VREF5V_OVL_IE (Bit 14)            */
#define SCUPM_SYS_IRQ_CTRL_VREF5V_OVL_IE_Msk (0x4000UL)             /*!< SCUPM SYS_IRQ_CTRL: VREF5V_OVL_IE (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_IRQ_CTRL_VREF5V_UPTH_IE_Pos (13UL)                /*!< SCUPM SYS_IRQ_CTRL: VREF5V_UPTH_IE (Bit 13)           */
#define SCUPM_SYS_IRQ_CTRL_VREF5V_UPTH_IE_Msk (0x2000UL)            /*!< SCUPM SYS_IRQ_CTRL: VREF5V_UPTH_IE (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_IRQ_CTRL_VREF5V_LOWTH_IE_Pos (12UL)               /*!< SCUPM SYS_IRQ_CTRL: VREF5V_LOWTH_IE (Bit 12)          */
#define SCUPM_SYS_IRQ_CTRL_VREF5V_LOWTH_IE_Msk (0x1000UL)           /*!< SCUPM SYS_IRQ_CTRL: VREF5V_LOWTH_IE (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_IRQ_CTRL_REFBG_UPTHWARN_IE_Pos (11UL)             /*!< SCUPM SYS_IRQ_CTRL: REFBG_UPTHWARN_IE (Bit 11)        */
#define SCUPM_SYS_IRQ_CTRL_REFBG_UPTHWARN_IE_Msk (0x800UL)          /*!< SCUPM SYS_IRQ_CTRL: REFBG_UPTHWARN_IE (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_IRQ_CTRL_REFBG_LOTHWARN_IE_Pos (10UL)             /*!< SCUPM SYS_IRQ_CTRL: REFBG_LOTHWARN_IE (Bit 10)        */
#define SCUPM_SYS_IRQ_CTRL_REFBG_LOTHWARN_IE_Msk (0x400UL)          /*!< SCUPM SYS_IRQ_CTRL: REFBG_LOTHWARN_IE (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_IRQ_CTRL_SYS_OT_IE_Pos  (9UL)                     /*!< SCUPM SYS_IRQ_CTRL: SYS_OT_IE (Bit 9)                 */
#define SCUPM_SYS_IRQ_CTRL_SYS_OT_IE_Msk  (0x200UL)                 /*!< SCUPM SYS_IRQ_CTRL: SYS_OT_IE (Bitfield-Mask: 0x01)   */
#define SCUPM_SYS_IRQ_CTRL_SYS_OTWARN_IE_Pos (8UL)                  /*!< SCUPM SYS_IRQ_CTRL: SYS_OTWARN_IE (Bit 8)             */
#define SCUPM_SYS_IRQ_CTRL_SYS_OTWARN_IE_Msk (0x100UL)              /*!< SCUPM SYS_IRQ_CTRL: SYS_OTWARN_IE (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_IRQ_CTRL_PMU_OT_IE_Pos  (7UL)                     /*!< SCUPM SYS_IRQ_CTRL: PMU_OT_IE (Bit 7)                 */
#define SCUPM_SYS_IRQ_CTRL_PMU_OT_IE_Msk  (0x80UL)                  /*!< SCUPM SYS_IRQ_CTRL: PMU_OT_IE (Bitfield-Mask: 0x01)   */
#define SCUPM_SYS_IRQ_CTRL_PMU_OTWARN_IE_Pos (6UL)                  /*!< SCUPM SYS_IRQ_CTRL: PMU_OTWARN_IE (Bit 6)             */
#define SCUPM_SYS_IRQ_CTRL_PMU_OTWARN_IE_Msk (0x40UL)               /*!< SCUPM SYS_IRQ_CTRL: PMU_OTWARN_IE (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_IRQ_CTRL_LIN_TMOUT_IE_Pos (2UL)                   /*!< SCUPM SYS_IRQ_CTRL: LIN_TMOUT_IE (Bit 2)              */
#define SCUPM_SYS_IRQ_CTRL_LIN_TMOUT_IE_Msk (0x4UL)                 /*!< SCUPM SYS_IRQ_CTRL: LIN_TMOUT_IE (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_IRQ_CTRL_LIN_OT_IE_Pos  (1UL)                     /*!< SCUPM SYS_IRQ_CTRL: LIN_OT_IE (Bit 1)                 */
#define SCUPM_SYS_IRQ_CTRL_LIN_OT_IE_Msk  (0x2UL)                   /*!< SCUPM SYS_IRQ_CTRL: LIN_OT_IE (Bitfield-Mask: 0x01)   */
#define SCUPM_SYS_IRQ_CTRL_LIN_OC_IE_Pos  (0UL)                     /*!< SCUPM SYS_IRQ_CTRL: LIN_OC_IE (Bit 0)                 */
#define SCUPM_SYS_IRQ_CTRL_LIN_OC_IE_Msk  (0x1UL)                   /*!< SCUPM SYS_IRQ_CTRL: LIN_OC_IE (Bitfield-Mask: 0x01)   */
/* ========================================================  SYS_IS  ========================================================= */
#define SCUPM_SYS_IS_PHW_ZCHI_STS_Pos     (29UL)                    /*!< SCUPM SYS_IS: PHW_ZCHI_STS (Bit 29)                   */
#define SCUPM_SYS_IS_PHW_ZCHI_STS_Msk     (0x20000000UL)            /*!< SCUPM SYS_IS: PHW_ZCHI_STS (Bitfield-Mask: 0x01)      */
#define SCUPM_SYS_IS_PHW_ZCLOW_STS_Pos    (28UL)                    /*!< SCUPM SYS_IS: PHW_ZCLOW_STS (Bit 28)                  */
#define SCUPM_SYS_IS_PHW_ZCLOW_STS_Msk    (0x10000000UL)            /*!< SCUPM SYS_IS: PHW_ZCLOW_STS (Bitfield-Mask: 0x01)     */
#define SCUPM_SYS_IS_PHV_ZCHI_STS_Pos     (27UL)                    /*!< SCUPM SYS_IS: PHV_ZCHI_STS (Bit 27)                   */
#define SCUPM_SYS_IS_PHV_ZCHI_STS_Msk     (0x8000000UL)             /*!< SCUPM SYS_IS: PHV_ZCHI_STS (Bitfield-Mask: 0x01)      */
#define SCUPM_SYS_IS_PHV_ZCLOW_STS_Pos    (26UL)                    /*!< SCUPM SYS_IS: PHV_ZCLOW_STS (Bit 26)                  */
#define SCUPM_SYS_IS_PHV_ZCLOW_STS_Msk    (0x4000000UL)             /*!< SCUPM SYS_IS: PHV_ZCLOW_STS (Bitfield-Mask: 0x01)     */
#define SCUPM_SYS_IS_PHU_ZCHI_STS_Pos     (25UL)                    /*!< SCUPM SYS_IS: PHU_ZCHI_STS (Bit 25)                   */
#define SCUPM_SYS_IS_PHU_ZCHI_STS_Msk     (0x2000000UL)             /*!< SCUPM SYS_IS: PHU_ZCHI_STS (Bitfield-Mask: 0x01)      */
#define SCUPM_SYS_IS_PHU_ZCLOW_STS_Pos    (24UL)                    /*!< SCUPM SYS_IS: PHU_ZCLOW_STS (Bit 24)                  */
#define SCUPM_SYS_IS_PHU_ZCLOW_STS_Msk    (0x1000000UL)             /*!< SCUPM SYS_IS: PHU_ZCLOW_STS (Bitfield-Mask: 0x01)     */
#define SCUPM_SYS_IS_ADC4_EOC_IS_Pos      (23UL)                    /*!< SCUPM SYS_IS: ADC4_EOC_IS (Bit 23)                    */
#define SCUPM_SYS_IS_ADC4_EOC_IS_Msk      (0x800000UL)              /*!< SCUPM SYS_IS: ADC4_EOC_IS (Bitfield-Mask: 0x01)       */
#define SCUPM_SYS_IS_ADC3_EOC_IS_Pos      (22UL)                    /*!< SCUPM SYS_IS: ADC3_EOC_IS (Bit 22)                    */
#define SCUPM_SYS_IS_ADC3_EOC_IS_Msk      (0x400000UL)              /*!< SCUPM SYS_IS: ADC3_EOC_IS (Bitfield-Mask: 0x01)       */
#define SCUPM_SYS_IS_PHW_ZCHI_IS_Pos      (21UL)                    /*!< SCUPM SYS_IS: PHW_ZCHI_IS (Bit 21)                    */
#define SCUPM_SYS_IS_PHW_ZCHI_IS_Msk      (0x200000UL)              /*!< SCUPM SYS_IS: PHW_ZCHI_IS (Bitfield-Mask: 0x01)       */
#define SCUPM_SYS_IS_PHW_ZCLOW_IS_Pos     (20UL)                    /*!< SCUPM SYS_IS: PHW_ZCLOW_IS (Bit 20)                   */
#define SCUPM_SYS_IS_PHW_ZCLOW_IS_Msk     (0x100000UL)              /*!< SCUPM SYS_IS: PHW_ZCLOW_IS (Bitfield-Mask: 0x01)      */
#define SCUPM_SYS_IS_PHV_ZCHI_IS_Pos      (19UL)                    /*!< SCUPM SYS_IS: PHV_ZCHI_IS (Bit 19)                    */
#define SCUPM_SYS_IS_PHV_ZCHI_IS_Msk      (0x80000UL)               /*!< SCUPM SYS_IS: PHV_ZCHI_IS (Bitfield-Mask: 0x01)       */
#define SCUPM_SYS_IS_PHV_ZCLOW_IS_Pos     (18UL)                    /*!< SCUPM SYS_IS: PHV_ZCLOW_IS (Bit 18)                   */
#define SCUPM_SYS_IS_PHV_ZCLOW_IS_Msk     (0x40000UL)               /*!< SCUPM SYS_IS: PHV_ZCLOW_IS (Bitfield-Mask: 0x01)      */
#define SCUPM_SYS_IS_PHU_ZCHI_IS_Pos      (17UL)                    /*!< SCUPM SYS_IS: PHU_ZCHI_IS (Bit 17)                    */
#define SCUPM_SYS_IS_PHU_ZCHI_IS_Msk      (0x20000UL)               /*!< SCUPM SYS_IS: PHU_ZCHI_IS (Bitfield-Mask: 0x01)       */
#define SCUPM_SYS_IS_PHU_ZCLOW_IS_Pos     (16UL)                    /*!< SCUPM SYS_IS: PHU_ZCLOW_IS (Bit 16)                   */
#define SCUPM_SYS_IS_PHU_ZCLOW_IS_Msk     (0x10000UL)               /*!< SCUPM SYS_IS: PHU_ZCLOW_IS (Bitfield-Mask: 0x01)      */
#define SCUPM_SYS_IS_ADC2_ESM_IS_Pos      (15UL)                    /*!< SCUPM SYS_IS: ADC2_ESM_IS (Bit 15)                    */
#define SCUPM_SYS_IS_ADC2_ESM_IS_Msk      (0x8000UL)                /*!< SCUPM SYS_IS: ADC2_ESM_IS (Bitfield-Mask: 0x01)       */
#define SCUPM_SYS_IS_VREF5V_OVL_IS_Pos    (14UL)                    /*!< SCUPM SYS_IS: VREF5V_OVL_IS (Bit 14)                  */
#define SCUPM_SYS_IS_VREF5V_OVL_IS_Msk    (0x4000UL)                /*!< SCUPM SYS_IS: VREF5V_OVL_IS (Bitfield-Mask: 0x01)     */
#define SCUPM_SYS_IS_VREF5V_UPTH_IS_Pos   (13UL)                    /*!< SCUPM SYS_IS: VREF5V_UPTH_IS (Bit 13)                 */
#define SCUPM_SYS_IS_VREF5V_UPTH_IS_Msk   (0x2000UL)                /*!< SCUPM SYS_IS: VREF5V_UPTH_IS (Bitfield-Mask: 0x01)    */
#define SCUPM_SYS_IS_VREF5V_LOWTH_IS_Pos  (12UL)                    /*!< SCUPM SYS_IS: VREF5V_LOWTH_IS (Bit 12)                */
#define SCUPM_SYS_IS_VREF5V_LOWTH_IS_Msk  (0x1000UL)                /*!< SCUPM SYS_IS: VREF5V_LOWTH_IS (Bitfield-Mask: 0x01)   */
#define SCUPM_SYS_IS_REFBG_UPTHWARN_IS_Pos (11UL)                   /*!< SCUPM SYS_IS: REFBG_UPTHWARN_IS (Bit 11)              */
#define SCUPM_SYS_IS_REFBG_UPTHWARN_IS_Msk (0x800UL)                /*!< SCUPM SYS_IS: REFBG_UPTHWARN_IS (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_IS_REFBG_LOTHWARN_IS_Pos (10UL)                   /*!< SCUPM SYS_IS: REFBG_LOTHWARN_IS (Bit 10)              */
#define SCUPM_SYS_IS_REFBG_LOTHWARN_IS_Msk (0x400UL)                /*!< SCUPM SYS_IS: REFBG_LOTHWARN_IS (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_IS_SYS_OT_IS_Pos        (9UL)                     /*!< SCUPM SYS_IS: SYS_OT_IS (Bit 9)                       */
#define SCUPM_SYS_IS_SYS_OT_IS_Msk        (0x200UL)                 /*!< SCUPM SYS_IS: SYS_OT_IS (Bitfield-Mask: 0x01)         */
#define SCUPM_SYS_IS_SYS_OTWARN_IS_Pos    (8UL)                     /*!< SCUPM SYS_IS: SYS_OTWARN_IS (Bit 8)                   */
#define SCUPM_SYS_IS_SYS_OTWARN_IS_Msk    (0x100UL)                 /*!< SCUPM SYS_IS: SYS_OTWARN_IS (Bitfield-Mask: 0x01)     */
#define SCUPM_SYS_IS_PMU_OT_IS_Pos        (7UL)                     /*!< SCUPM SYS_IS: PMU_OT_IS (Bit 7)                       */
#define SCUPM_SYS_IS_PMU_OT_IS_Msk        (0x80UL)                  /*!< SCUPM SYS_IS: PMU_OT_IS (Bitfield-Mask: 0x01)         */
#define SCUPM_SYS_IS_PMU_OTWARN_IS_Pos    (6UL)                     /*!< SCUPM SYS_IS: PMU_OTWARN_IS (Bit 6)                   */
#define SCUPM_SYS_IS_PMU_OTWARN_IS_Msk    (0x40UL)                  /*!< SCUPM SYS_IS: PMU_OTWARN_IS (Bitfield-Mask: 0x01)     */
#define SCUPM_SYS_IS_LIN_TMOUT_IS_Pos     (2UL)                     /*!< SCUPM SYS_IS: LIN_TMOUT_IS (Bit 2)                    */
#define SCUPM_SYS_IS_LIN_TMOUT_IS_Msk     (0x4UL)                   /*!< SCUPM SYS_IS: LIN_TMOUT_IS (Bitfield-Mask: 0x01)      */
#define SCUPM_SYS_IS_LIN_OT_IS_Pos        (1UL)                     /*!< SCUPM SYS_IS: LIN_OT_IS (Bit 1)                       */
#define SCUPM_SYS_IS_LIN_OT_IS_Msk        (0x2UL)                   /*!< SCUPM SYS_IS: LIN_OT_IS (Bitfield-Mask: 0x01)         */
#define SCUPM_SYS_IS_LIN_OC_IS_Pos        (0UL)                     /*!< SCUPM SYS_IS: LIN_OC_IS (Bit 0)                       */
#define SCUPM_SYS_IS_LIN_OC_IS_Msk        (0x1UL)                   /*!< SCUPM SYS_IS: LIN_OC_IS (Bitfield-Mask: 0x01)         */
/* =======================================================  SYS_ISCLR  ======================================================= */
#define SCUPM_SYS_ISCLR_PHW_ZCHI_SCLR_Pos (29UL)                    /*!< SCUPM SYS_ISCLR: PHW_ZCHI_SCLR (Bit 29)               */
#define SCUPM_SYS_ISCLR_PHW_ZCHI_SCLR_Msk (0x20000000UL)            /*!< SCUPM SYS_ISCLR: PHW_ZCHI_SCLR (Bitfield-Mask: 0x01)  */
#define SCUPM_SYS_ISCLR_PHW_ZCLOW_SCLR_Pos (28UL)                   /*!< SCUPM SYS_ISCLR: PHW_ZCLOW_SCLR (Bit 28)              */
#define SCUPM_SYS_ISCLR_PHW_ZCLOW_SCLR_Msk (0x10000000UL)           /*!< SCUPM SYS_ISCLR: PHW_ZCLOW_SCLR (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_ISCLR_PHV_ZCHI_SCLR_Pos (27UL)                    /*!< SCUPM SYS_ISCLR: PHV_ZCHI_SCLR (Bit 27)               */
#define SCUPM_SYS_ISCLR_PHV_ZCHI_SCLR_Msk (0x8000000UL)             /*!< SCUPM SYS_ISCLR: PHV_ZCHI_SCLR (Bitfield-Mask: 0x01)  */
#define SCUPM_SYS_ISCLR_PHV_ZCLOW_SCLR_Pos (26UL)                   /*!< SCUPM SYS_ISCLR: PHV_ZCLOW_SCLR (Bit 26)              */
#define SCUPM_SYS_ISCLR_PHV_ZCLOW_SCLR_Msk (0x4000000UL)            /*!< SCUPM SYS_ISCLR: PHV_ZCLOW_SCLR (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_ISCLR_PHU_ZCHI_SCLR_Pos (25UL)                    /*!< SCUPM SYS_ISCLR: PHU_ZCHI_SCLR (Bit 25)               */
#define SCUPM_SYS_ISCLR_PHU_ZCHI_SCLR_Msk (0x2000000UL)             /*!< SCUPM SYS_ISCLR: PHU_ZCHI_SCLR (Bitfield-Mask: 0x01)  */
#define SCUPM_SYS_ISCLR_PHU_ZCLOW_SCLR_Pos (24UL)                   /*!< SCUPM SYS_ISCLR: PHU_ZCLOW_SCLR (Bit 24)              */
#define SCUPM_SYS_ISCLR_PHU_ZCLOW_SCLR_Msk (0x1000000UL)            /*!< SCUPM SYS_ISCLR: PHU_ZCLOW_SCLR (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_ISCLR_ADC4_EOC_ICLR_Pos (23UL)                    /*!< SCUPM SYS_ISCLR: ADC4_EOC_ICLR (Bit 23)               */
#define SCUPM_SYS_ISCLR_ADC4_EOC_ICLR_Msk (0x800000UL)              /*!< SCUPM SYS_ISCLR: ADC4_EOC_ICLR (Bitfield-Mask: 0x01)  */
#define SCUPM_SYS_ISCLR_ADC3_EOC_ICLR_Pos (22UL)                    /*!< SCUPM SYS_ISCLR: ADC3_EOC_ICLR (Bit 22)               */
#define SCUPM_SYS_ISCLR_ADC3_EOC_ICLR_Msk (0x400000UL)              /*!< SCUPM SYS_ISCLR: ADC3_EOC_ICLR (Bitfield-Mask: 0x01)  */
#define SCUPM_SYS_ISCLR_PHW_ZCHI_ICLR_Pos (21UL)                    /*!< SCUPM SYS_ISCLR: PHW_ZCHI_ICLR (Bit 21)               */
#define SCUPM_SYS_ISCLR_PHW_ZCHI_ICLR_Msk (0x200000UL)              /*!< SCUPM SYS_ISCLR: PHW_ZCHI_ICLR (Bitfield-Mask: 0x01)  */
#define SCUPM_SYS_ISCLR_PHW_ZCLOW_ICLR_Pos (20UL)                   /*!< SCUPM SYS_ISCLR: PHW_ZCLOW_ICLR (Bit 20)              */
#define SCUPM_SYS_ISCLR_PHW_ZCLOW_ICLR_Msk (0x100000UL)             /*!< SCUPM SYS_ISCLR: PHW_ZCLOW_ICLR (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_ISCLR_PHV_ZCHI_ICLR_Pos (19UL)                    /*!< SCUPM SYS_ISCLR: PHV_ZCHI_ICLR (Bit 19)               */
#define SCUPM_SYS_ISCLR_PHV_ZCHI_ICLR_Msk (0x80000UL)               /*!< SCUPM SYS_ISCLR: PHV_ZCHI_ICLR (Bitfield-Mask: 0x01)  */
#define SCUPM_SYS_ISCLR_PHV_ZCLOW_ICLR_Pos (18UL)                   /*!< SCUPM SYS_ISCLR: PHV_ZCLOW_ICLR (Bit 18)              */
#define SCUPM_SYS_ISCLR_PHV_ZCLOW_ICLR_Msk (0x40000UL)              /*!< SCUPM SYS_ISCLR: PHV_ZCLOW_ICLR (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_ISCLR_PHU_ZCHI_ICLR_Pos (17UL)                    /*!< SCUPM SYS_ISCLR: PHU_ZCHI_ICLR (Bit 17)               */
#define SCUPM_SYS_ISCLR_PHU_ZCHI_ICLR_Msk (0x20000UL)               /*!< SCUPM SYS_ISCLR: PHU_ZCHI_ICLR (Bitfield-Mask: 0x01)  */
#define SCUPM_SYS_ISCLR_PHU_ZCLOW_ICLR_Pos (16UL)                   /*!< SCUPM SYS_ISCLR: PHU_ZCLOW_ICLR (Bit 16)              */
#define SCUPM_SYS_ISCLR_PHU_ZCLOW_ICLR_Msk (0x10000UL)              /*!< SCUPM SYS_ISCLR: PHU_ZCLOW_ICLR (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_ISCLR_ADC2_ESM_ICLR_Pos (15UL)                    /*!< SCUPM SYS_ISCLR: ADC2_ESM_ICLR (Bit 15)               */
#define SCUPM_SYS_ISCLR_ADC2_ESM_ICLR_Msk (0x8000UL)                /*!< SCUPM SYS_ISCLR: ADC2_ESM_ICLR (Bitfield-Mask: 0x01)  */
#define SCUPM_SYS_ISCLR_VREF5V_OVL_ICLR_Pos (14UL)                  /*!< SCUPM SYS_ISCLR: VREF5V_OVL_ICLR (Bit 14)             */
#define SCUPM_SYS_ISCLR_VREF5V_OVL_ICLR_Msk (0x4000UL)              /*!< SCUPM SYS_ISCLR: VREF5V_OVL_ICLR (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_ISCLR_VREF5V_UPTH_ICLR_Pos (13UL)                 /*!< SCUPM SYS_ISCLR: VREF5V_UPTH_ICLR (Bit 13)            */
#define SCUPM_SYS_ISCLR_VREF5V_UPTH_ICLR_Msk (0x2000UL)             /*!< SCUPM SYS_ISCLR: VREF5V_UPTH_ICLR (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_ISCLR_VREF5V_LOWTH_ICLR_Pos (12UL)                /*!< SCUPM SYS_ISCLR: VREF5V_LOWTH_ICLR (Bit 12)           */
#define SCUPM_SYS_ISCLR_VREF5V_LOWTH_ICLR_Msk (0x1000UL)            /*!< SCUPM SYS_ISCLR: VREF5V_LOWTH_ICLR (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_ISCLR_REFBG_UPTHWARN_ICLR_Pos (11UL)              /*!< SCUPM SYS_ISCLR: REFBG_UPTHWARN_ICLR (Bit 11)         */
#define SCUPM_SYS_ISCLR_REFBG_UPTHWARN_ICLR_Msk (0x800UL)           /*!< SCUPM SYS_ISCLR: REFBG_UPTHWARN_ICLR (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_ISCLR_REFBG_LOTHWARN_ICLR_Pos (10UL)              /*!< SCUPM SYS_ISCLR: REFBG_LOTHWARN_ICLR (Bit 10)         */
#define SCUPM_SYS_ISCLR_REFBG_LOTHWARN_ICLR_Msk (0x400UL)           /*!< SCUPM SYS_ISCLR: REFBG_LOTHWARN_ICLR (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_ISCLR_SYS_OT_ICLR_Pos   (9UL)                     /*!< SCUPM SYS_ISCLR: SYS_OT_ICLR (Bit 9)                  */
#define SCUPM_SYS_ISCLR_SYS_OT_ICLR_Msk   (0x200UL)                 /*!< SCUPM SYS_ISCLR: SYS_OT_ICLR (Bitfield-Mask: 0x01)    */
#define SCUPM_SYS_ISCLR_SYS_OTWARN_ICLR_Pos (8UL)                   /*!< SCUPM SYS_ISCLR: SYS_OTWARN_ICLR (Bit 8)              */
#define SCUPM_SYS_ISCLR_SYS_OTWARN_ICLR_Msk (0x100UL)               /*!< SCUPM SYS_ISCLR: SYS_OTWARN_ICLR (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_ISCLR_PMU_OT_ICLR_Pos   (7UL)                     /*!< SCUPM SYS_ISCLR: PMU_OT_ICLR (Bit 7)                  */
#define SCUPM_SYS_ISCLR_PMU_OT_ICLR_Msk   (0x80UL)                  /*!< SCUPM SYS_ISCLR: PMU_OT_ICLR (Bitfield-Mask: 0x01)    */
#define SCUPM_SYS_ISCLR_PMU_OTWARN_ICLR_Pos (6UL)                   /*!< SCUPM SYS_ISCLR: PMU_OTWARN_ICLR (Bit 6)              */
#define SCUPM_SYS_ISCLR_PMU_OTWARN_ICLR_Msk (0x40UL)                /*!< SCUPM SYS_ISCLR: PMU_OTWARN_ICLR (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_ISCLR_LIN_TMOUT_ICLR_Pos (2UL)                    /*!< SCUPM SYS_ISCLR: LIN_TMOUT_ICLR (Bit 2)               */
#define SCUPM_SYS_ISCLR_LIN_TMOUT_ICLR_Msk (0x4UL)                  /*!< SCUPM SYS_ISCLR: LIN_TMOUT_ICLR (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_ISCLR_LIN_OT_ICLR_Pos   (1UL)                     /*!< SCUPM SYS_ISCLR: LIN_OT_ICLR (Bit 1)                  */
#define SCUPM_SYS_ISCLR_LIN_OT_ICLR_Msk   (0x2UL)                   /*!< SCUPM SYS_ISCLR: LIN_OT_ICLR (Bitfield-Mask: 0x01)    */
#define SCUPM_SYS_ISCLR_LIN_OC_ICLR_Pos   (0UL)                     /*!< SCUPM SYS_ISCLR: LIN_OC_ICLR (Bit 0)                  */
#define SCUPM_SYS_ISCLR_LIN_OC_ICLR_Msk   (0x1UL)                   /*!< SCUPM SYS_ISCLR: LIN_OC_ICLR (Bitfield-Mask: 0x01)    */
/* ==================================================  SYS_SUPPLY_IRQ_CLR  =================================================== */
#define SCUPM_SYS_SUPPLY_IRQ_CLR_VDD1V5_OV_SCLR_Pos (23UL)          /*!< SCUPM SYS_SUPPLY_IRQ_CLR: VDD1V5_OV_SCLR (Bit 23)     */
#define SCUPM_SYS_SUPPLY_IRQ_CLR_VDD1V5_OV_SCLR_Msk (0x800000UL)    /*!< SCUPM SYS_SUPPLY_IRQ_CLR: VDD1V5_OV_SCLR (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_SUPPLY_IRQ_CLR_VDD5V_OV_SCLR_Pos (22UL)           /*!< SCUPM SYS_SUPPLY_IRQ_CLR: VDD5V_OV_SCLR (Bit 22)      */
#define SCUPM_SYS_SUPPLY_IRQ_CLR_VDD5V_OV_SCLR_Msk (0x400000UL)     /*!< SCUPM SYS_SUPPLY_IRQ_CLR: VDD5V_OV_SCLR (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_SUPPLY_IRQ_CLR_VS_OV_SCLR_Pos (21UL)              /*!< SCUPM SYS_SUPPLY_IRQ_CLR: VS_OV_SCLR (Bit 21)         */
#define SCUPM_SYS_SUPPLY_IRQ_CLR_VS_OV_SCLR_Msk (0x200000UL)        /*!< SCUPM SYS_SUPPLY_IRQ_CLR: VS_OV_SCLR (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_SUPPLY_IRQ_CLR_MON_OV_SCLR_Pos (20UL)             /*!< SCUPM SYS_SUPPLY_IRQ_CLR: MON_OV_SCLR (Bit 20)        */
#define SCUPM_SYS_SUPPLY_IRQ_CLR_MON_OV_SCLR_Msk (0x100000UL)       /*!< SCUPM SYS_SUPPLY_IRQ_CLR: MON_OV_SCLR (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_SUPPLY_IRQ_CLR_VDD1V5_UV_SCLR_Pos (19UL)          /*!< SCUPM SYS_SUPPLY_IRQ_CLR: VDD1V5_UV_SCLR (Bit 19)     */
#define SCUPM_SYS_SUPPLY_IRQ_CLR_VDD1V5_UV_SCLR_Msk (0x80000UL)     /*!< SCUPM SYS_SUPPLY_IRQ_CLR: VDD1V5_UV_SCLR (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_SUPPLY_IRQ_CLR_VDD5V_UV_SCLR_Pos (18UL)           /*!< SCUPM SYS_SUPPLY_IRQ_CLR: VDD5V_UV_SCLR (Bit 18)      */
#define SCUPM_SYS_SUPPLY_IRQ_CLR_VDD5V_UV_SCLR_Msk (0x40000UL)      /*!< SCUPM SYS_SUPPLY_IRQ_CLR: VDD5V_UV_SCLR (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_SUPPLY_IRQ_CLR_VS_UV_SCLR_Pos (17UL)              /*!< SCUPM SYS_SUPPLY_IRQ_CLR: VS_UV_SCLR (Bit 17)         */
#define SCUPM_SYS_SUPPLY_IRQ_CLR_VS_UV_SCLR_Msk (0x20000UL)         /*!< SCUPM SYS_SUPPLY_IRQ_CLR: VS_UV_SCLR (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_SUPPLY_IRQ_CLR_MON_UV_SCLR_Pos (16UL)             /*!< SCUPM SYS_SUPPLY_IRQ_CLR: MON_UV_SCLR (Bit 16)        */
#define SCUPM_SYS_SUPPLY_IRQ_CLR_MON_UV_SCLR_Msk (0x10000UL)        /*!< SCUPM SYS_SUPPLY_IRQ_CLR: MON_UV_SCLR (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_SUPPLY_IRQ_CLR_VDD1V5_OV_ICLR_Pos (7UL)           /*!< SCUPM SYS_SUPPLY_IRQ_CLR: VDD1V5_OV_ICLR (Bit 7)      */
#define SCUPM_SYS_SUPPLY_IRQ_CLR_VDD1V5_OV_ICLR_Msk (0x80UL)        /*!< SCUPM SYS_SUPPLY_IRQ_CLR: VDD1V5_OV_ICLR (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_SUPPLY_IRQ_CLR_VDD5V_OV_ICLR_Pos (6UL)            /*!< SCUPM SYS_SUPPLY_IRQ_CLR: VDD5V_OV_ICLR (Bit 6)       */
#define SCUPM_SYS_SUPPLY_IRQ_CLR_VDD5V_OV_ICLR_Msk (0x40UL)         /*!< SCUPM SYS_SUPPLY_IRQ_CLR: VDD5V_OV_ICLR (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_SUPPLY_IRQ_CLR_VS_OV_ICLR_Pos (5UL)               /*!< SCUPM SYS_SUPPLY_IRQ_CLR: VS_OV_ICLR (Bit 5)          */
#define SCUPM_SYS_SUPPLY_IRQ_CLR_VS_OV_ICLR_Msk (0x20UL)            /*!< SCUPM SYS_SUPPLY_IRQ_CLR: VS_OV_ICLR (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_SUPPLY_IRQ_CLR_MON_OV_ICLR_Pos (4UL)              /*!< SCUPM SYS_SUPPLY_IRQ_CLR: MON_OV_ICLR (Bit 4)         */
#define SCUPM_SYS_SUPPLY_IRQ_CLR_MON_OV_ICLR_Msk (0x10UL)           /*!< SCUPM SYS_SUPPLY_IRQ_CLR: MON_OV_ICLR (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_SUPPLY_IRQ_CLR_VDD1V5_UV_ICLR_Pos (3UL)           /*!< SCUPM SYS_SUPPLY_IRQ_CLR: VDD1V5_UV_ICLR (Bit 3)      */
#define SCUPM_SYS_SUPPLY_IRQ_CLR_VDD1V5_UV_ICLR_Msk (0x8UL)         /*!< SCUPM SYS_SUPPLY_IRQ_CLR: VDD1V5_UV_ICLR (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_SUPPLY_IRQ_CLR_VDD5V_UV_ICLR_Pos (2UL)            /*!< SCUPM SYS_SUPPLY_IRQ_CLR: VDD5V_UV_ICLR (Bit 2)       */
#define SCUPM_SYS_SUPPLY_IRQ_CLR_VDD5V_UV_ICLR_Msk (0x4UL)          /*!< SCUPM SYS_SUPPLY_IRQ_CLR: VDD5V_UV_ICLR (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_SUPPLY_IRQ_CLR_VS_UV_ICLR_Pos (1UL)               /*!< SCUPM SYS_SUPPLY_IRQ_CLR: VS_UV_ICLR (Bit 1)          */
#define SCUPM_SYS_SUPPLY_IRQ_CLR_VS_UV_ICLR_Msk (0x2UL)             /*!< SCUPM SYS_SUPPLY_IRQ_CLR: VS_UV_ICLR (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_SUPPLY_IRQ_CLR_MON_UV_ICLR_Pos (0UL)              /*!< SCUPM SYS_SUPPLY_IRQ_CLR: MON_UV_ICLR (Bit 0)         */
#define SCUPM_SYS_SUPPLY_IRQ_CLR_MON_UV_ICLR_Msk (0x1UL)            /*!< SCUPM SYS_SUPPLY_IRQ_CLR: MON_UV_ICLR (Bitfield-Mask: 0x01) */
/* ==================================================  SYS_SUPPLY_IRQ_CTRL  ================================================== */
#define SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD1V5_OV_IE_Pos (7UL)            /*!< SCUPM SYS_SUPPLY_IRQ_CTRL: VDD1V5_OV_IE (Bit 7)       */
#define SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD1V5_OV_IE_Msk (0x80UL)         /*!< SCUPM SYS_SUPPLY_IRQ_CTRL: VDD1V5_OV_IE (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD5V_OV_IE_Pos (6UL)             /*!< SCUPM SYS_SUPPLY_IRQ_CTRL: VDD5V_OV_IE (Bit 6)        */
#define SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD5V_OV_IE_Msk (0x40UL)          /*!< SCUPM SYS_SUPPLY_IRQ_CTRL: VDD5V_OV_IE (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_SUPPLY_IRQ_CTRL_VS_OV_IE_Pos (5UL)                /*!< SCUPM SYS_SUPPLY_IRQ_CTRL: VS_OV_IE (Bit 5)           */
#define SCUPM_SYS_SUPPLY_IRQ_CTRL_VS_OV_IE_Msk (0x20UL)             /*!< SCUPM SYS_SUPPLY_IRQ_CTRL: VS_OV_IE (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_SUPPLY_IRQ_CTRL_MON_OV_IE_Pos (4UL)               /*!< SCUPM SYS_SUPPLY_IRQ_CTRL: MON_OV_IE (Bit 4)          */
#define SCUPM_SYS_SUPPLY_IRQ_CTRL_MON_OV_IE_Msk (0x10UL)            /*!< SCUPM SYS_SUPPLY_IRQ_CTRL: MON_OV_IE (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD1V5_UV_IE_Pos (3UL)            /*!< SCUPM SYS_SUPPLY_IRQ_CTRL: VDD1V5_UV_IE (Bit 3)       */
#define SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD1V5_UV_IE_Msk (0x8UL)          /*!< SCUPM SYS_SUPPLY_IRQ_CTRL: VDD1V5_UV_IE (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD5V_UV_IE_Pos (2UL)             /*!< SCUPM SYS_SUPPLY_IRQ_CTRL: VDD5V_UV_IE (Bit 2)        */
#define SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD5V_UV_IE_Msk (0x4UL)           /*!< SCUPM SYS_SUPPLY_IRQ_CTRL: VDD5V_UV_IE (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_SUPPLY_IRQ_CTRL_VS_UV_IE_Pos (1UL)                /*!< SCUPM SYS_SUPPLY_IRQ_CTRL: VS_UV_IE (Bit 1)           */
#define SCUPM_SYS_SUPPLY_IRQ_CTRL_VS_UV_IE_Msk (0x2UL)              /*!< SCUPM SYS_SUPPLY_IRQ_CTRL: VS_UV_IE (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_SUPPLY_IRQ_CTRL_MON_UV_IE_Pos (0UL)               /*!< SCUPM SYS_SUPPLY_IRQ_CTRL: MON_UV_IE (Bit 0)          */
#define SCUPM_SYS_SUPPLY_IRQ_CTRL_MON_UV_IE_Msk (0x1UL)             /*!< SCUPM SYS_SUPPLY_IRQ_CTRL: MON_UV_IE (Bitfield-Mask: 0x01) */
/* ==================================================  SYS_SUPPLY_IRQ_STS  =================================================== */
#define SCUPM_SYS_SUPPLY_IRQ_STS_VDD1V5_OV_STS_Pos (23UL)           /*!< SCUPM SYS_SUPPLY_IRQ_STS: VDD1V5_OV_STS (Bit 23)      */
#define SCUPM_SYS_SUPPLY_IRQ_STS_VDD1V5_OV_STS_Msk (0x800000UL)     /*!< SCUPM SYS_SUPPLY_IRQ_STS: VDD1V5_OV_STS (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_SUPPLY_IRQ_STS_VDD5V_OV_STS_Pos (22UL)            /*!< SCUPM SYS_SUPPLY_IRQ_STS: VDD5V_OV_STS (Bit 22)       */
#define SCUPM_SYS_SUPPLY_IRQ_STS_VDD5V_OV_STS_Msk (0x400000UL)      /*!< SCUPM SYS_SUPPLY_IRQ_STS: VDD5V_OV_STS (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_SUPPLY_IRQ_STS_VS_OV_STS_Pos (21UL)               /*!< SCUPM SYS_SUPPLY_IRQ_STS: VS_OV_STS (Bit 21)          */
#define SCUPM_SYS_SUPPLY_IRQ_STS_VS_OV_STS_Msk (0x200000UL)         /*!< SCUPM SYS_SUPPLY_IRQ_STS: VS_OV_STS (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_SUPPLY_IRQ_STS_MON_OV_STS_Pos (20UL)              /*!< SCUPM SYS_SUPPLY_IRQ_STS: MON_OV_STS (Bit 20)         */
#define SCUPM_SYS_SUPPLY_IRQ_STS_MON_OV_STS_Msk (0x100000UL)        /*!< SCUPM SYS_SUPPLY_IRQ_STS: MON_OV_STS (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_SUPPLY_IRQ_STS_VDD1V5_UV_STS_Pos (19UL)           /*!< SCUPM SYS_SUPPLY_IRQ_STS: VDD1V5_UV_STS (Bit 19)      */
#define SCUPM_SYS_SUPPLY_IRQ_STS_VDD1V5_UV_STS_Msk (0x80000UL)      /*!< SCUPM SYS_SUPPLY_IRQ_STS: VDD1V5_UV_STS (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_SUPPLY_IRQ_STS_VDD5V_UV_STS_Pos (18UL)            /*!< SCUPM SYS_SUPPLY_IRQ_STS: VDD5V_UV_STS (Bit 18)       */
#define SCUPM_SYS_SUPPLY_IRQ_STS_VDD5V_UV_STS_Msk (0x40000UL)       /*!< SCUPM SYS_SUPPLY_IRQ_STS: VDD5V_UV_STS (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_SUPPLY_IRQ_STS_VS_UV_STS_Pos (17UL)               /*!< SCUPM SYS_SUPPLY_IRQ_STS: VS_UV_STS (Bit 17)          */
#define SCUPM_SYS_SUPPLY_IRQ_STS_VS_UV_STS_Msk (0x20000UL)          /*!< SCUPM SYS_SUPPLY_IRQ_STS: VS_UV_STS (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_SUPPLY_IRQ_STS_MON_UV_STS_Pos (16UL)              /*!< SCUPM SYS_SUPPLY_IRQ_STS: MON_UV_STS (Bit 16)         */
#define SCUPM_SYS_SUPPLY_IRQ_STS_MON_UV_STS_Msk (0x10000UL)         /*!< SCUPM SYS_SUPPLY_IRQ_STS: MON_UV_STS (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_SUPPLY_IRQ_STS_VDD1V5_OV_IS_Pos (7UL)             /*!< SCUPM SYS_SUPPLY_IRQ_STS: VDD1V5_OV_IS (Bit 7)        */
#define SCUPM_SYS_SUPPLY_IRQ_STS_VDD1V5_OV_IS_Msk (0x80UL)          /*!< SCUPM SYS_SUPPLY_IRQ_STS: VDD1V5_OV_IS (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_SUPPLY_IRQ_STS_VDD5V_OV_IS_Pos (6UL)              /*!< SCUPM SYS_SUPPLY_IRQ_STS: VDD5V_OV_IS (Bit 6)         */
#define SCUPM_SYS_SUPPLY_IRQ_STS_VDD5V_OV_IS_Msk (0x40UL)           /*!< SCUPM SYS_SUPPLY_IRQ_STS: VDD5V_OV_IS (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_SUPPLY_IRQ_STS_VS_OV_IS_Pos (5UL)                 /*!< SCUPM SYS_SUPPLY_IRQ_STS: VS_OV_IS (Bit 5)            */
#define SCUPM_SYS_SUPPLY_IRQ_STS_VS_OV_IS_Msk (0x20UL)              /*!< SCUPM SYS_SUPPLY_IRQ_STS: VS_OV_IS (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_SUPPLY_IRQ_STS_MON_OV_IS_Pos (4UL)                /*!< SCUPM SYS_SUPPLY_IRQ_STS: MON_OV_IS (Bit 4)           */
#define SCUPM_SYS_SUPPLY_IRQ_STS_MON_OV_IS_Msk (0x10UL)             /*!< SCUPM SYS_SUPPLY_IRQ_STS: MON_OV_IS (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_SUPPLY_IRQ_STS_VDD1V5_UV_IS_Pos (3UL)             /*!< SCUPM SYS_SUPPLY_IRQ_STS: VDD1V5_UV_IS (Bit 3)        */
#define SCUPM_SYS_SUPPLY_IRQ_STS_VDD1V5_UV_IS_Msk (0x8UL)           /*!< SCUPM SYS_SUPPLY_IRQ_STS: VDD1V5_UV_IS (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_SUPPLY_IRQ_STS_VDD5V_UV_IS_Pos (2UL)              /*!< SCUPM SYS_SUPPLY_IRQ_STS: VDD5V_UV_IS (Bit 2)         */
#define SCUPM_SYS_SUPPLY_IRQ_STS_VDD5V_UV_IS_Msk (0x4UL)            /*!< SCUPM SYS_SUPPLY_IRQ_STS: VDD5V_UV_IS (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_SUPPLY_IRQ_STS_VS_UV_IS_Pos (1UL)                 /*!< SCUPM SYS_SUPPLY_IRQ_STS: VS_UV_IS (Bit 1)            */
#define SCUPM_SYS_SUPPLY_IRQ_STS_VS_UV_IS_Msk (0x2UL)               /*!< SCUPM SYS_SUPPLY_IRQ_STS: VS_UV_IS (Bitfield-Mask: 0x01) */
#define SCUPM_SYS_SUPPLY_IRQ_STS_MON_UV_IS_Pos (0UL)                /*!< SCUPM SYS_SUPPLY_IRQ_STS: MON_UV_IS (Bit 0)           */
#define SCUPM_SYS_SUPPLY_IRQ_STS_MON_UV_IS_Msk (0x1UL)              /*!< SCUPM SYS_SUPPLY_IRQ_STS: MON_UV_IS (Bitfield-Mask: 0x01) */
/* =======================================================  WDT1_TRIG  ======================================================= */
#define SCUPM_WDT1_TRIG_SOWCONF_Pos       (6UL)                     /*!< SCUPM WDT1_TRIG: SOWCONF (Bit 6)                      */
#define SCUPM_WDT1_TRIG_SOWCONF_Msk       (0xc0UL)                  /*!< SCUPM WDT1_TRIG: SOWCONF (Bitfield-Mask: 0x03)        */
#define SCUPM_WDT1_TRIG_WDP_SEL_Pos       (0UL)                     /*!< SCUPM WDT1_TRIG: WDP_SEL (Bit 0)                      */
#define SCUPM_WDT1_TRIG_WDP_SEL_Msk       (0x3fUL)                  /*!< SCUPM WDT1_TRIG: WDP_SEL (Bitfield-Mask: 0x3f)        */


/* =========================================================================================================================== */
/* ================                                           SSC1                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  BR  =========================================================== */
#define SSC1_BR_BR_VALUE_Pos              (0UL)                     /*!< SSC1 BR: BR_VALUE (Bit 0)                             */
#define SSC1_BR_BR_VALUE_Msk              (0xffffUL)                /*!< SSC1 BR: BR_VALUE (Bitfield-Mask: 0xffff)             */
/* ==========================================================  CON  ========================================================== */
#define SSC1_CON_BC_Pos                   (0UL)                     /*!< SSC1 CON: BC (Bit 0)                                  */
#define SSC1_CON_BC_Msk                   (0xfUL)                   /*!< SSC1 CON: BC (Bitfield-Mask: 0x0f)                    */
#define SSC1_CON_TE_Pos                   (8UL)                     /*!< SSC1 CON: TE (Bit 8)                                  */
#define SSC1_CON_TE_Msk                   (0x100UL)                 /*!< SSC1 CON: TE (Bitfield-Mask: 0x01)                    */
#define SSC1_CON_RE_Pos                   (9UL)                     /*!< SSC1 CON: RE (Bit 9)                                  */
#define SSC1_CON_RE_Msk                   (0x200UL)                 /*!< SSC1 CON: RE (Bitfield-Mask: 0x01)                    */
#define SSC1_CON_PE_Pos                   (10UL)                    /*!< SSC1 CON: PE (Bit 10)                                 */
#define SSC1_CON_PE_Msk                   (0x400UL)                 /*!< SSC1 CON: PE (Bitfield-Mask: 0x01)                    */
#define SSC1_CON_BE_Pos                   (11UL)                    /*!< SSC1 CON: BE (Bit 11)                                 */
#define SSC1_CON_BE_Msk                   (0x800UL)                 /*!< SSC1 CON: BE (Bitfield-Mask: 0x01)                    */
#define SSC1_CON_BSY_Pos                  (12UL)                    /*!< SSC1 CON: BSY (Bit 12)                                */
#define SSC1_CON_BSY_Msk                  (0x1000UL)                /*!< SSC1 CON: BSY (Bitfield-Mask: 0x01)                   */
#define SSC1_CON_MS_Pos                   (14UL)                    /*!< SSC1 CON: MS (Bit 14)                                 */
#define SSC1_CON_MS_Msk                   (0x4000UL)                /*!< SSC1 CON: MS (Bitfield-Mask: 0x01)                    */
#define SSC1_CON_EN_Pos                   (15UL)                    /*!< SSC1 CON: EN (Bit 15)                                 */
#define SSC1_CON_EN_Msk                   (0x8000UL)                /*!< SSC1 CON: EN (Bitfield-Mask: 0x01)                    */
/* ========================================================  ISRCLR  ========================================================= */
#define SSC1_ISRCLR_TECLR_Pos             (8UL)                     /*!< SSC1 ISRCLR: TECLR (Bit 8)                            */
#define SSC1_ISRCLR_TECLR_Msk             (0x100UL)                 /*!< SSC1 ISRCLR: TECLR (Bitfield-Mask: 0x01)              */
#define SSC1_ISRCLR_RECLR_Pos             (9UL)                     /*!< SSC1 ISRCLR: RECLR (Bit 9)                            */
#define SSC1_ISRCLR_RECLR_Msk             (0x200UL)                 /*!< SSC1 ISRCLR: RECLR (Bitfield-Mask: 0x01)              */
#define SSC1_ISRCLR_PECLR_Pos             (10UL)                    /*!< SSC1 ISRCLR: PECLR (Bit 10)                           */
#define SSC1_ISRCLR_PECLR_Msk             (0x400UL)                 /*!< SSC1 ISRCLR: PECLR (Bitfield-Mask: 0x01)              */
#define SSC1_ISRCLR_BECLR_Pos             (11UL)                    /*!< SSC1 ISRCLR: BECLR (Bit 11)                           */
#define SSC1_ISRCLR_BECLR_Msk             (0x800UL)                 /*!< SSC1 ISRCLR: BECLR (Bitfield-Mask: 0x01)              */
/* =========================================================  PISEL  ========================================================= */
#define SSC1_PISEL_MIS_0_Pos              (0UL)                     /*!< SSC1 PISEL: MIS_0 (Bit 0)                             */
#define SSC1_PISEL_MIS_0_Msk              (0x1UL)                   /*!< SSC1 PISEL: MIS_0 (Bitfield-Mask: 0x01)               */
#define SSC1_PISEL_SIS_Pos                (1UL)                     /*!< SSC1 PISEL: SIS (Bit 1)                               */
#define SSC1_PISEL_SIS_Msk                (0x2UL)                   /*!< SSC1 PISEL: SIS (Bitfield-Mask: 0x01)                 */
#define SSC1_PISEL_CIS_Pos                (2UL)                     /*!< SSC1 PISEL: CIS (Bit 2)                               */
#define SSC1_PISEL_CIS_Msk                (0x4UL)                   /*!< SSC1 PISEL: CIS (Bitfield-Mask: 0x01)                 */
#define SSC1_PISEL_MIS_1_Pos              (3UL)                     /*!< SSC1 PISEL: MIS_1 (Bit 3)                             */
#define SSC1_PISEL_MIS_1_Msk              (0x8UL)                   /*!< SSC1 PISEL: MIS_1 (Bitfield-Mask: 0x01)               */
/* ==========================================================  RB  =========================================================== */
#define SSC1_RB_RB_VALUE_Pos              (0UL)                     /*!< SSC1 RB: RB_VALUE (Bit 0)                             */
#define SSC1_RB_RB_VALUE_Msk              (0xffffUL)                /*!< SSC1 RB: RB_VALUE (Bitfield-Mask: 0xffff)             */
/* ==========================================================  TB  =========================================================== */
#define SSC1_TB_TB_VALUE_Pos              (0UL)                     /*!< SSC1 TB: TB_VALUE (Bit 0)                             */
#define SSC1_TB_TB_VALUE_Msk              (0xffffUL)                /*!< SSC1 TB: TB_VALUE (Bitfield-Mask: 0xffff)             */


/* =========================================================================================================================== */
/* ================                                           SSC2                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  BR  =========================================================== */
#define SSC2_BR_BR_VALUE_Pos              (0UL)                     /*!< SSC2 BR: BR_VALUE (Bit 0)                             */
#define SSC2_BR_BR_VALUE_Msk              (0xffffUL)                /*!< SSC2 BR: BR_VALUE (Bitfield-Mask: 0xffff)             */
/* ==========================================================  CON  ========================================================== */
#define SSC2_CON_BC_Pos                   (0UL)                     /*!< SSC2 CON: BC (Bit 0)                                  */
#define SSC2_CON_BC_Msk                   (0xfUL)                   /*!< SSC2 CON: BC (Bitfield-Mask: 0x0f)                    */
#define SSC2_CON_TE_Pos                   (8UL)                     /*!< SSC2 CON: TE (Bit 8)                                  */
#define SSC2_CON_TE_Msk                   (0x100UL)                 /*!< SSC2 CON: TE (Bitfield-Mask: 0x01)                    */
#define SSC2_CON_RE_Pos                   (9UL)                     /*!< SSC2 CON: RE (Bit 9)                                  */
#define SSC2_CON_RE_Msk                   (0x200UL)                 /*!< SSC2 CON: RE (Bitfield-Mask: 0x01)                    */
#define SSC2_CON_PE_Pos                   (10UL)                    /*!< SSC2 CON: PE (Bit 10)                                 */
#define SSC2_CON_PE_Msk                   (0x400UL)                 /*!< SSC2 CON: PE (Bitfield-Mask: 0x01)                    */
#define SSC2_CON_BE_Pos                   (11UL)                    /*!< SSC2 CON: BE (Bit 11)                                 */
#define SSC2_CON_BE_Msk                   (0x800UL)                 /*!< SSC2 CON: BE (Bitfield-Mask: 0x01)                    */
#define SSC2_CON_BSY_Pos                  (12UL)                    /*!< SSC2 CON: BSY (Bit 12)                                */
#define SSC2_CON_BSY_Msk                  (0x1000UL)                /*!< SSC2 CON: BSY (Bitfield-Mask: 0x01)                   */
#define SSC2_CON_MS_Pos                   (14UL)                    /*!< SSC2 CON: MS (Bit 14)                                 */
#define SSC2_CON_MS_Msk                   (0x4000UL)                /*!< SSC2 CON: MS (Bitfield-Mask: 0x01)                    */
#define SSC2_CON_EN_Pos                   (15UL)                    /*!< SSC2 CON: EN (Bit 15)                                 */
#define SSC2_CON_EN_Msk                   (0x8000UL)                /*!< SSC2 CON: EN (Bitfield-Mask: 0x01)                    */
/* ========================================================  ISRCLR  ========================================================= */
#define SSC2_ISRCLR_TECLR_Pos             (8UL)                     /*!< SSC2 ISRCLR: TECLR (Bit 8)                            */
#define SSC2_ISRCLR_TECLR_Msk             (0x100UL)                 /*!< SSC2 ISRCLR: TECLR (Bitfield-Mask: 0x01)              */
#define SSC2_ISRCLR_RECLR_Pos             (9UL)                     /*!< SSC2 ISRCLR: RECLR (Bit 9)                            */
#define SSC2_ISRCLR_RECLR_Msk             (0x200UL)                 /*!< SSC2 ISRCLR: RECLR (Bitfield-Mask: 0x01)              */
#define SSC2_ISRCLR_PECLR_Pos             (10UL)                    /*!< SSC2 ISRCLR: PECLR (Bit 10)                           */
#define SSC2_ISRCLR_PECLR_Msk             (0x400UL)                 /*!< SSC2 ISRCLR: PECLR (Bitfield-Mask: 0x01)              */
#define SSC2_ISRCLR_BECLR_Pos             (11UL)                    /*!< SSC2 ISRCLR: BECLR (Bit 11)                           */
#define SSC2_ISRCLR_BECLR_Msk             (0x800UL)                 /*!< SSC2 ISRCLR: BECLR (Bitfield-Mask: 0x01)              */
/* =========================================================  PISEL  ========================================================= */
#define SSC2_PISEL_MIS_0_Pos              (0UL)                     /*!< SSC2 PISEL: MIS_0 (Bit 0)                             */
#define SSC2_PISEL_MIS_0_Msk              (0x1UL)                   /*!< SSC2 PISEL: MIS_0 (Bitfield-Mask: 0x01)               */
#define SSC2_PISEL_SIS_Pos                (1UL)                     /*!< SSC2 PISEL: SIS (Bit 1)                               */
#define SSC2_PISEL_SIS_Msk                (0x2UL)                   /*!< SSC2 PISEL: SIS (Bitfield-Mask: 0x01)                 */
#define SSC2_PISEL_CIS_Pos                (2UL)                     /*!< SSC2 PISEL: CIS (Bit 2)                               */
#define SSC2_PISEL_CIS_Msk                (0x4UL)                   /*!< SSC2 PISEL: CIS (Bitfield-Mask: 0x01)                 */
#define SSC2_PISEL_MIS_1_Pos              (3UL)                     /*!< SSC2 PISEL: MIS_1 (Bit 3)                             */
#define SSC2_PISEL_MIS_1_Msk              (0x8UL)                   /*!< SSC2 PISEL: MIS_1 (Bitfield-Mask: 0x01)               */
/* ==========================================================  RB  =========================================================== */
#define SSC2_RB_RB_VALUE_Pos              (0UL)                     /*!< SSC2 RB: RB_VALUE (Bit 0)                             */
#define SSC2_RB_RB_VALUE_Msk              (0xffffUL)                /*!< SSC2 RB: RB_VALUE (Bitfield-Mask: 0xffff)             */
/* ==========================================================  TB  =========================================================== */
#define SSC2_TB_TB_VALUE_Pos              (0UL)                     /*!< SSC2 TB: TB_VALUE (Bit 0)                             */
#define SSC2_TB_TB_VALUE_Msk              (0xffffUL)                /*!< SSC2 TB: TB_VALUE (Bitfield-Mask: 0xffff)             */


/* =========================================================================================================================== */
/* ================                                          TIMER2                                           ================ */
/* =========================================================================================================================== */

/* =========================================================  RC2H  ========================================================== */
#define TIMER2_RC2H_RC2_Pos               (0UL)                     /*!< TIMER2 RC2H: RC2 (Bit 0)                              */
#define TIMER2_RC2H_RC2_Msk               (0xffUL)                  /*!< TIMER2 RC2H: RC2 (Bitfield-Mask: 0xff)                */
/* =========================================================  RC2L  ========================================================== */
#define TIMER2_RC2L_RC2_Pos               (0UL)                     /*!< TIMER2 RC2L: RC2 (Bit 0)                              */
#define TIMER2_RC2L_RC2_Msk               (0xffUL)                  /*!< TIMER2 RC2L: RC2 (Bitfield-Mask: 0xff)                */
/* =========================================================  T2CON  ========================================================= */
#define TIMER2_T2CON_CP_RL2_Pos           (0UL)                     /*!< TIMER2 T2CON: CP_RL2 (Bit 0)                          */
#define TIMER2_T2CON_CP_RL2_Msk           (0x1UL)                   /*!< TIMER2 T2CON: CP_RL2 (Bitfield-Mask: 0x01)            */
#define TIMER2_T2CON_C_T2_Pos             (1UL)                     /*!< TIMER2 T2CON: C_T2 (Bit 1)                            */
#define TIMER2_T2CON_C_T2_Msk             (0x2UL)                   /*!< TIMER2 T2CON: C_T2 (Bitfield-Mask: 0x01)              */
#define TIMER2_T2CON_TR2_Pos              (2UL)                     /*!< TIMER2 T2CON: TR2 (Bit 2)                             */
#define TIMER2_T2CON_TR2_Msk              (0x4UL)                   /*!< TIMER2 T2CON: TR2 (Bitfield-Mask: 0x01)               */
#define TIMER2_T2CON_EXEN2_Pos            (3UL)                     /*!< TIMER2 T2CON: EXEN2 (Bit 3)                           */
#define TIMER2_T2CON_EXEN2_Msk            (0x8UL)                   /*!< TIMER2 T2CON: EXEN2 (Bitfield-Mask: 0x01)             */
#define TIMER2_T2CON_EXF2_Pos             (6UL)                     /*!< TIMER2 T2CON: EXF2 (Bit 6)                            */
#define TIMER2_T2CON_EXF2_Msk             (0x40UL)                  /*!< TIMER2 T2CON: EXF2 (Bitfield-Mask: 0x01)              */
#define TIMER2_T2CON_TF2_Pos              (7UL)                     /*!< TIMER2 T2CON: TF2 (Bit 7)                             */
#define TIMER2_T2CON_TF2_Msk              (0x80UL)                  /*!< TIMER2 T2CON: TF2 (Bitfield-Mask: 0x01)               */
/* ========================================================  T2CON1  ========================================================= */
#define TIMER2_T2CON1_EXF2EN_Pos          (0UL)                     /*!< TIMER2 T2CON1: EXF2EN (Bit 0)                         */
#define TIMER2_T2CON1_EXF2EN_Msk          (0x1UL)                   /*!< TIMER2 T2CON1: EXF2EN (Bitfield-Mask: 0x01)           */
#define TIMER2_T2CON1_TF2EN_Pos           (1UL)                     /*!< TIMER2 T2CON1: TF2EN (Bit 1)                          */
#define TIMER2_T2CON1_TF2EN_Msk           (0x2UL)                   /*!< TIMER2 T2CON1: TF2EN (Bitfield-Mask: 0x01)            */
/* ==========================================================  T2H  ========================================================== */
#define TIMER2_T2H_T2H_Pos                (0UL)                     /*!< TIMER2 T2H: T2H (Bit 0)                               */
#define TIMER2_T2H_T2H_Msk                (0xffUL)                  /*!< TIMER2 T2H: T2H (Bitfield-Mask: 0xff)                 */
/* ========================================================  T2ICLR  ========================================================= */
#define TIMER2_T2ICLR_EXF2CLR_Pos         (6UL)                     /*!< TIMER2 T2ICLR: EXF2CLR (Bit 6)                        */
#define TIMER2_T2ICLR_EXF2CLR_Msk         (0x40UL)                  /*!< TIMER2 T2ICLR: EXF2CLR (Bitfield-Mask: 0x01)          */
#define TIMER2_T2ICLR_TF2CLR_Pos          (7UL)                     /*!< TIMER2 T2ICLR: TF2CLR (Bit 7)                         */
#define TIMER2_T2ICLR_TF2CLR_Msk          (0x80UL)                  /*!< TIMER2 T2ICLR: TF2CLR (Bitfield-Mask: 0x01)           */
/* ==========================================================  T2L  ========================================================== */
#define TIMER2_T2L_T2L_Pos                (0UL)                     /*!< TIMER2 T2L: T2L (Bit 0)                               */
#define TIMER2_T2L_T2L_Msk                (0xffUL)                  /*!< TIMER2 T2L: T2L (Bitfield-Mask: 0xff)                 */
/* =========================================================  T2MOD  ========================================================= */
#define TIMER2_T2MOD_DCEN_Pos             (0UL)                     /*!< TIMER2 T2MOD: DCEN (Bit 0)                            */
#define TIMER2_T2MOD_DCEN_Msk             (0x1UL)                   /*!< TIMER2 T2MOD: DCEN (Bitfield-Mask: 0x01)              */
#define TIMER2_T2MOD_T2PRE_Pos            (1UL)                     /*!< TIMER2 T2MOD: T2PRE (Bit 1)                           */
#define TIMER2_T2MOD_T2PRE_Msk            (0xeUL)                   /*!< TIMER2 T2MOD: T2PRE (Bitfield-Mask: 0x07)             */
#define TIMER2_T2MOD_PREN_Pos             (4UL)                     /*!< TIMER2 T2MOD: PREN (Bit 4)                            */
#define TIMER2_T2MOD_PREN_Msk             (0x10UL)                  /*!< TIMER2 T2MOD: PREN (Bitfield-Mask: 0x01)              */
#define TIMER2_T2MOD_EDGESEL_Pos          (5UL)                     /*!< TIMER2 T2MOD: EDGESEL (Bit 5)                         */
#define TIMER2_T2MOD_EDGESEL_Msk          (0x20UL)                  /*!< TIMER2 T2MOD: EDGESEL (Bitfield-Mask: 0x01)           */
#define TIMER2_T2MOD_T2RHEN_Pos           (6UL)                     /*!< TIMER2 T2MOD: T2RHEN (Bit 6)                          */
#define TIMER2_T2MOD_T2RHEN_Msk           (0x40UL)                  /*!< TIMER2 T2MOD: T2RHEN (Bitfield-Mask: 0x01)            */
#define TIMER2_T2MOD_T2REGS_Pos           (7UL)                     /*!< TIMER2 T2MOD: T2REGS (Bit 7)                          */
#define TIMER2_T2MOD_T2REGS_Msk           (0x80UL)                  /*!< TIMER2 T2MOD: T2REGS (Bitfield-Mask: 0x01)            */


/* =========================================================================================================================== */
/* ================                                          TIMER21                                          ================ */
/* =========================================================================================================================== */

/* =========================================================  RC2H  ========================================================== */
#define TIMER21_RC2H_RC2_Pos              (0UL)                     /*!< TIMER21 RC2H: RC2 (Bit 0)                             */
#define TIMER21_RC2H_RC2_Msk              (0xffUL)                  /*!< TIMER21 RC2H: RC2 (Bitfield-Mask: 0xff)               */
/* =========================================================  RC2L  ========================================================== */
#define TIMER21_RC2L_RC2_Pos              (0UL)                     /*!< TIMER21 RC2L: RC2 (Bit 0)                             */
#define TIMER21_RC2L_RC2_Msk              (0xffUL)                  /*!< TIMER21 RC2L: RC2 (Bitfield-Mask: 0xff)               */
/* =========================================================  T2CON  ========================================================= */
#define TIMER21_T2CON_CP_RL2_Pos          (0UL)                     /*!< TIMER21 T2CON: CP_RL2 (Bit 0)                         */
#define TIMER21_T2CON_CP_RL2_Msk          (0x1UL)                   /*!< TIMER21 T2CON: CP_RL2 (Bitfield-Mask: 0x01)           */
#define TIMER21_T2CON_C_T2_Pos            (1UL)                     /*!< TIMER21 T2CON: C_T2 (Bit 1)                           */
#define TIMER21_T2CON_C_T2_Msk            (0x2UL)                   /*!< TIMER21 T2CON: C_T2 (Bitfield-Mask: 0x01)             */
#define TIMER21_T2CON_TR2_Pos             (2UL)                     /*!< TIMER21 T2CON: TR2 (Bit 2)                            */
#define TIMER21_T2CON_TR2_Msk             (0x4UL)                   /*!< TIMER21 T2CON: TR2 (Bitfield-Mask: 0x01)              */
#define TIMER21_T2CON_EXEN2_Pos           (3UL)                     /*!< TIMER21 T2CON: EXEN2 (Bit 3)                          */
#define TIMER21_T2CON_EXEN2_Msk           (0x8UL)                   /*!< TIMER21 T2CON: EXEN2 (Bitfield-Mask: 0x01)            */
#define TIMER21_T2CON_EXF2_Pos            (6UL)                     /*!< TIMER21 T2CON: EXF2 (Bit 6)                           */
#define TIMER21_T2CON_EXF2_Msk            (0x40UL)                  /*!< TIMER21 T2CON: EXF2 (Bitfield-Mask: 0x01)             */
#define TIMER21_T2CON_TF2_Pos             (7UL)                     /*!< TIMER21 T2CON: TF2 (Bit 7)                            */
#define TIMER21_T2CON_TF2_Msk             (0x80UL)                  /*!< TIMER21 T2CON: TF2 (Bitfield-Mask: 0x01)              */
/* ========================================================  T2CON1  ========================================================= */
#define TIMER21_T2CON1_EXF2EN_Pos         (0UL)                     /*!< TIMER21 T2CON1: EXF2EN (Bit 0)                        */
#define TIMER21_T2CON1_EXF2EN_Msk         (0x1UL)                   /*!< TIMER21 T2CON1: EXF2EN (Bitfield-Mask: 0x01)          */
#define TIMER21_T2CON1_TF2EN_Pos          (1UL)                     /*!< TIMER21 T2CON1: TF2EN (Bit 1)                         */
#define TIMER21_T2CON1_TF2EN_Msk          (0x2UL)                   /*!< TIMER21 T2CON1: TF2EN (Bitfield-Mask: 0x01)           */
/* ==========================================================  T2H  ========================================================== */
#define TIMER21_T2H_T2H_Pos               (0UL)                     /*!< TIMER21 T2H: T2H (Bit 0)                              */
#define TIMER21_T2H_T2H_Msk               (0xffUL)                  /*!< TIMER21 T2H: T2H (Bitfield-Mask: 0xff)                */
/* ========================================================  T2ICLR  ========================================================= */
#define TIMER21_T2ICLR_EXF2CLR_Pos        (6UL)                     /*!< TIMER21 T2ICLR: EXF2CLR (Bit 6)                       */
#define TIMER21_T2ICLR_EXF2CLR_Msk        (0x40UL)                  /*!< TIMER21 T2ICLR: EXF2CLR (Bitfield-Mask: 0x01)         */
#define TIMER21_T2ICLR_TF2CLR_Pos         (7UL)                     /*!< TIMER21 T2ICLR: TF2CLR (Bit 7)                        */
#define TIMER21_T2ICLR_TF2CLR_Msk         (0x80UL)                  /*!< TIMER21 T2ICLR: TF2CLR (Bitfield-Mask: 0x01)          */
/* ==========================================================  T2L  ========================================================== */
#define TIMER21_T2L_T2L_Pos               (0UL)                     /*!< TIMER21 T2L: T2L (Bit 0)                              */
#define TIMER21_T2L_T2L_Msk               (0xffUL)                  /*!< TIMER21 T2L: T2L (Bitfield-Mask: 0xff)                */
/* =========================================================  T2MOD  ========================================================= */
#define TIMER21_T2MOD_DCEN_Pos            (0UL)                     /*!< TIMER21 T2MOD: DCEN (Bit 0)                           */
#define TIMER21_T2MOD_DCEN_Msk            (0x1UL)                   /*!< TIMER21 T2MOD: DCEN (Bitfield-Mask: 0x01)             */
#define TIMER21_T2MOD_T2PRE_Pos           (1UL)                     /*!< TIMER21 T2MOD: T2PRE (Bit 1)                          */
#define TIMER21_T2MOD_T2PRE_Msk           (0xeUL)                   /*!< TIMER21 T2MOD: T2PRE (Bitfield-Mask: 0x07)            */
#define TIMER21_T2MOD_PREN_Pos            (4UL)                     /*!< TIMER21 T2MOD: PREN (Bit 4)                           */
#define TIMER21_T2MOD_PREN_Msk            (0x10UL)                  /*!< TIMER21 T2MOD: PREN (Bitfield-Mask: 0x01)             */
#define TIMER21_T2MOD_EDGESEL_Pos         (5UL)                     /*!< TIMER21 T2MOD: EDGESEL (Bit 5)                        */
#define TIMER21_T2MOD_EDGESEL_Msk         (0x20UL)                  /*!< TIMER21 T2MOD: EDGESEL (Bitfield-Mask: 0x01)          */
#define TIMER21_T2MOD_T2RHEN_Pos          (6UL)                     /*!< TIMER21 T2MOD: T2RHEN (Bit 6)                         */
#define TIMER21_T2MOD_T2RHEN_Msk          (0x40UL)                  /*!< TIMER21 T2MOD: T2RHEN (Bitfield-Mask: 0x01)           */
#define TIMER21_T2MOD_T2REGS_Pos          (7UL)                     /*!< TIMER21 T2MOD: T2REGS (Bit 7)                         */
#define TIMER21_T2MOD_T2REGS_Msk          (0x80UL)                  /*!< TIMER21 T2MOD: T2REGS (Bitfield-Mask: 0x01)           */


/* =========================================================================================================================== */
/* ================                                          TIMER3                                           ================ */
/* =========================================================================================================================== */

/* ==========================================================  CMP  ========================================================== */
#define TIMER3_CMP_HI_Pos                 (8UL)                     /*!< TIMER3 CMP: HI (Bit 8)                                */
#define TIMER3_CMP_HI_Msk                 (0xff00UL)                /*!< TIMER3 CMP: HI (Bitfield-Mask: 0xff)                  */
#define TIMER3_CMP_LO_Pos                 (0UL)                     /*!< TIMER3 CMP: LO (Bit 0)                                */
#define TIMER3_CMP_LO_Msk                 (0xffUL)                  /*!< TIMER3 CMP: LO (Bitfield-Mask: 0xff)                  */
/* ==========================================================  CNT  ========================================================== */
#define TIMER3_CNT_HI_Pos                 (8UL)                     /*!< TIMER3 CNT: HI (Bit 8)                                */
#define TIMER3_CNT_HI_Msk                 (0xff00UL)                /*!< TIMER3 CNT: HI (Bitfield-Mask: 0xff)                  */
#define TIMER3_CNT_LO_Pos                 (0UL)                     /*!< TIMER3 CNT: LO (Bit 0)                                */
#define TIMER3_CNT_LO_Msk                 (0xffUL)                  /*!< TIMER3 CNT: LO (Bitfield-Mask: 0xff)                  */
/* =========================================================  CTRL  ========================================================== */
#define TIMER3_CTRL_T3H_OVF_IE_Pos        (9UL)                     /*!< TIMER3 CTRL: T3H_OVF_IE (Bit 9)                       */
#define TIMER3_CTRL_T3H_OVF_IE_Msk        (0x200UL)                 /*!< TIMER3 CTRL: T3H_OVF_IE (Bitfield-Mask: 0x01)         */
#define TIMER3_CTRL_T3L_OVF_IE_Pos        (8UL)                     /*!< TIMER3 CTRL: T3L_OVF_IE (Bit 8)                       */
#define TIMER3_CTRL_T3L_OVF_IE_Msk        (0x100UL)                 /*!< TIMER3 CTRL: T3L_OVF_IE (Bitfield-Mask: 0x01)         */
#define TIMER3_CTRL_T3L_OVF_STS_Pos       (7UL)                     /*!< TIMER3 CTRL: T3L_OVF_STS (Bit 7)                      */
#define TIMER3_CTRL_T3L_OVF_STS_Msk       (0x80UL)                  /*!< TIMER3 CTRL: T3L_OVF_STS (Bitfield-Mask: 0x01)        */
#define TIMER3_CTRL_TR3L_Pos              (6UL)                     /*!< TIMER3 CTRL: TR3L (Bit 6)                             */
#define TIMER3_CTRL_TR3L_Msk              (0x40UL)                  /*!< TIMER3 CTRL: TR3L (Bitfield-Mask: 0x01)               */
#define TIMER3_CTRL_T3H_OVF_STS_Pos       (5UL)                     /*!< TIMER3 CTRL: T3H_OVF_STS (Bit 5)                      */
#define TIMER3_CTRL_T3H_OVF_STS_Msk       (0x20UL)                  /*!< TIMER3 CTRL: T3H_OVF_STS (Bitfield-Mask: 0x01)        */
#define TIMER3_CTRL_TR3H_Pos              (4UL)                     /*!< TIMER3 CTRL: TR3H (Bit 4)                             */
#define TIMER3_CTRL_TR3H_Msk              (0x10UL)                  /*!< TIMER3 CTRL: TR3H (Bitfield-Mask: 0x01)               */
#define TIMER3_CTRL_CNT_RDY_Pos           (3UL)                     /*!< TIMER3 CTRL: CNT_RDY (Bit 3)                          */
#define TIMER3_CTRL_CNT_RDY_Msk           (0x8UL)                   /*!< TIMER3 CTRL: CNT_RDY (Bitfield-Mask: 0x01)            */
#define TIMER3_CTRL_T3_RD_REQ_CONF_Pos    (2UL)                     /*!< TIMER3 CTRL: T3_RD_REQ_CONF (Bit 2)                   */
#define TIMER3_CTRL_T3_RD_REQ_CONF_Msk    (0x4UL)                   /*!< TIMER3 CTRL: T3_RD_REQ_CONF (Bitfield-Mask: 0x01)     */
#define TIMER3_CTRL_T3_RD_REQ_Pos         (1UL)                     /*!< TIMER3 CTRL: T3_RD_REQ (Bit 1)                        */
#define TIMER3_CTRL_T3_RD_REQ_Msk         (0x2UL)                   /*!< TIMER3 CTRL: T3_RD_REQ (Bitfield-Mask: 0x01)          */
#define TIMER3_CTRL_T3_PD_N_Pos           (0UL)                     /*!< TIMER3 CTRL: T3_PD_N (Bit 0)                          */
#define TIMER3_CTRL_T3_PD_N_Msk           (0x1UL)                   /*!< TIMER3 CTRL: T3_PD_N (Bitfield-Mask: 0x01)            */
/* ========================================================  ISRCLR  ========================================================= */
#define TIMER3_ISRCLR_T3L_OVF_ICLR_Pos    (7UL)                     /*!< TIMER3 ISRCLR: T3L_OVF_ICLR (Bit 7)                   */
#define TIMER3_ISRCLR_T3L_OVF_ICLR_Msk    (0x80UL)                  /*!< TIMER3 ISRCLR: T3L_OVF_ICLR (Bitfield-Mask: 0x01)     */
#define TIMER3_ISRCLR_T3H_OVF_ICLR_Pos    (5UL)                     /*!< TIMER3 ISRCLR: T3H_OVF_ICLR (Bit 5)                   */
#define TIMER3_ISRCLR_T3H_OVF_ICLR_Msk    (0x20UL)                  /*!< TIMER3 ISRCLR: T3H_OVF_ICLR (Bitfield-Mask: 0x01)     */
/* =======================================================  MODE_CONF  ======================================================= */
#define TIMER3_MODE_CONF_T3_SUBM_Pos      (6UL)                     /*!< TIMER3 MODE_CONF: T3_SUBM (Bit 6)                     */
#define TIMER3_MODE_CONF_T3_SUBM_Msk      (0xc0UL)                  /*!< TIMER3 MODE_CONF: T3_SUBM (Bitfield-Mask: 0x03)       */
#define TIMER3_MODE_CONF_T3M_Pos          (0UL)                     /*!< TIMER3 MODE_CONF: T3M (Bit 0)                         */
#define TIMER3_MODE_CONF_T3M_Msk          (0x3UL)                   /*!< TIMER3 MODE_CONF: T3M (Bitfield-Mask: 0x03)           */
/* =====================================================  T3_TRIGG_CTRL  ===================================================== */
#define TIMER3_T3_TRIGG_CTRL_RETRIG_Pos   (6UL)                     /*!< TIMER3 T3_TRIGG_CTRL: RETRIG (Bit 6)                  */
#define TIMER3_T3_TRIGG_CTRL_RETRIG_Msk   (0x40UL)                  /*!< TIMER3 T3_TRIGG_CTRL: RETRIG (Bitfield-Mask: 0x01)    */
#define TIMER3_T3_TRIGG_CTRL_T3_RES_CONF_Pos (4UL)                  /*!< TIMER3 T3_TRIGG_CTRL: T3_RES_CONF (Bit 4)             */
#define TIMER3_T3_TRIGG_CTRL_T3_RES_CONF_Msk (0x30UL)               /*!< TIMER3 T3_TRIGG_CTRL: T3_RES_CONF (Bitfield-Mask: 0x03) */
#define TIMER3_T3_TRIGG_CTRL_T3_TRIGG_INP_SEL_Pos (0UL)             /*!< TIMER3 T3_TRIGG_CTRL: T3_TRIGG_INP_SEL (Bit 0)        */
#define TIMER3_T3_TRIGG_CTRL_T3_TRIGG_INP_SEL_Msk (0x7UL)           /*!< TIMER3 T3_TRIGG_CTRL: T3_TRIGG_INP_SEL (Bitfield-Mask: 0x07) */


/* =========================================================================================================================== */
/* ================                                           UART1                                           ================ */
/* =========================================================================================================================== */

/* =========================================================  SBUF  ========================================================== */
#define UART1_SBUF_VAL_Pos                (0UL)                     /*!< UART1 SBUF: VAL (Bit 0)                               */
#define UART1_SBUF_VAL_Msk                (0xffUL)                  /*!< UART1 SBUF: VAL (Bitfield-Mask: 0xff)                 */
/* =========================================================  SCON  ========================================================== */
#define UART1_SCON_RI_Pos                 (0UL)                     /*!< UART1 SCON: RI (Bit 0)                                */
#define UART1_SCON_RI_Msk                 (0x1UL)                   /*!< UART1 SCON: RI (Bitfield-Mask: 0x01)                  */
#define UART1_SCON_TI_Pos                 (1UL)                     /*!< UART1 SCON: TI (Bit 1)                                */
#define UART1_SCON_TI_Msk                 (0x2UL)                   /*!< UART1 SCON: TI (Bitfield-Mask: 0x01)                  */
#define UART1_SCON_RB8_Pos                (2UL)                     /*!< UART1 SCON: RB8 (Bit 2)                               */
#define UART1_SCON_RB8_Msk                (0x4UL)                   /*!< UART1 SCON: RB8 (Bitfield-Mask: 0x01)                 */
#define UART1_SCON_TB8_Pos                (3UL)                     /*!< UART1 SCON: TB8 (Bit 3)                               */
#define UART1_SCON_TB8_Msk                (0x8UL)                   /*!< UART1 SCON: TB8 (Bitfield-Mask: 0x01)                 */
#define UART1_SCON_REN_Pos                (4UL)                     /*!< UART1 SCON: REN (Bit 4)                               */
#define UART1_SCON_REN_Msk                (0x10UL)                  /*!< UART1 SCON: REN (Bitfield-Mask: 0x01)                 */
#define UART1_SCON_SM2_Pos                (5UL)                     /*!< UART1 SCON: SM2 (Bit 5)                               */
#define UART1_SCON_SM2_Msk                (0x20UL)                  /*!< UART1 SCON: SM2 (Bitfield-Mask: 0x01)                 */
#define UART1_SCON_SM1_Pos                (6UL)                     /*!< UART1 SCON: SM1 (Bit 6)                               */
#define UART1_SCON_SM1_Msk                (0x40UL)                  /*!< UART1 SCON: SM1 (Bitfield-Mask: 0x01)                 */
#define UART1_SCON_SM0_Pos                (7UL)                     /*!< UART1 SCON: SM0 (Bit 7)                               */
#define UART1_SCON_SM0_Msk                (0x80UL)                  /*!< UART1 SCON: SM0 (Bitfield-Mask: 0x01)                 */
/* ========================================================  SCONCLR  ======================================================== */
#define UART1_SCONCLR_RICLR_Pos           (0UL)                     /*!< UART1 SCONCLR: RICLR (Bit 0)                          */
#define UART1_SCONCLR_RICLR_Msk           (0x1UL)                   /*!< UART1 SCONCLR: RICLR (Bitfield-Mask: 0x01)            */
#define UART1_SCONCLR_TICLR_Pos           (1UL)                     /*!< UART1 SCONCLR: TICLR (Bit 1)                          */
#define UART1_SCONCLR_TICLR_Msk           (0x2UL)                   /*!< UART1 SCONCLR: TICLR (Bitfield-Mask: 0x01)            */


/* =========================================================================================================================== */
/* ================                                           UART2                                           ================ */
/* =========================================================================================================================== */

/* =========================================================  SBUF  ========================================================== */
#define UART2_SBUF_VAL_Pos                (0UL)                     /*!< UART2 SBUF: VAL (Bit 0)                               */
#define UART2_SBUF_VAL_Msk                (0xffUL)                  /*!< UART2 SBUF: VAL (Bitfield-Mask: 0xff)                 */
/* =========================================================  SCON  ========================================================== */
#define UART2_SCON_RI_Pos                 (0UL)                     /*!< UART2 SCON: RI (Bit 0)                                */
#define UART2_SCON_RI_Msk                 (0x1UL)                   /*!< UART2 SCON: RI (Bitfield-Mask: 0x01)                  */
#define UART2_SCON_TI_Pos                 (1UL)                     /*!< UART2 SCON: TI (Bit 1)                                */
#define UART2_SCON_TI_Msk                 (0x2UL)                   /*!< UART2 SCON: TI (Bitfield-Mask: 0x01)                  */
#define UART2_SCON_RB8_Pos                (2UL)                     /*!< UART2 SCON: RB8 (Bit 2)                               */
#define UART2_SCON_RB8_Msk                (0x4UL)                   /*!< UART2 SCON: RB8 (Bitfield-Mask: 0x01)                 */
#define UART2_SCON_TB8_Pos                (3UL)                     /*!< UART2 SCON: TB8 (Bit 3)                               */
#define UART2_SCON_TB8_Msk                (0x8UL)                   /*!< UART2 SCON: TB8 (Bitfield-Mask: 0x01)                 */
#define UART2_SCON_REN_Pos                (4UL)                     /*!< UART2 SCON: REN (Bit 4)                               */
#define UART2_SCON_REN_Msk                (0x10UL)                  /*!< UART2 SCON: REN (Bitfield-Mask: 0x01)                 */
#define UART2_SCON_SM2_Pos                (5UL)                     /*!< UART2 SCON: SM2 (Bit 5)                               */
#define UART2_SCON_SM2_Msk                (0x20UL)                  /*!< UART2 SCON: SM2 (Bitfield-Mask: 0x01)                 */
#define UART2_SCON_SM1_Pos                (6UL)                     /*!< UART1 SCON: SM1 (Bit 6)                               */
#define UART2_SCON_SM1_Msk                (0x40UL)                  /*!< UART1 SCON: SM1 (Bitfield-Mask: 0x01)                 */
#define UART2_SCON_SM0_Pos                (7UL)                     /*!< UART1 SCON: SM0 (Bit 7)                               */
#define UART2_SCON_SM0_Msk                (0x80UL)                  /*!< UART1 SCON: SM0 (Bitfield-Mask: 0x01)                 */
/* ========================================================  SCONCLR  ======================================================== */
#define UART2_SCONCLR_RICLR_Pos           (0UL)                     /*!< UART2 SCONCLR: RICLR (Bit 0)                          */
#define UART2_SCONCLR_RICLR_Msk           (0x1UL)                   /*!< UART2 SCONCLR: RICLR (Bitfield-Mask: 0x01)            */
#define UART2_SCONCLR_TICLR_Pos           (1UL)                     /*!< UART2 SCONCLR: TICLR (Bit 1)                          */
#define UART2_SCONCLR_TICLR_Msk           (0x2UL)                   /*!< UART2 SCONCLR: TICLR (Bitfield-Mask: 0x01)            */

/** @} */ /* End of group PosMask_peripherals */

#ifdef __cplusplus
}
#endif

#endif /* TLE987X_H */


/** @} */ /* End of group TLE987x */

/** @} */ /* End of group Infineon */
