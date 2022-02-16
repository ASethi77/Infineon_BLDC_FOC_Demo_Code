/**
 * @cond
 ***********************************************************************************************************************
 *
 * Copyright (c) 2018, Infineon Technologies AG
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
#ifndef GPT12E_DEFINES_H
#define GPT12E_DEFINES_H

/* XML Version 2.2.3 */
#define GPT12E_XML_VERSION (20203)

#define GPT12E_CAPREL (0xFFF2) /*decimal 65522*/

#define GPT12E_CAPREL_TICK (0x0) /*decimal 0*/

#define GPT12E_CAPREL_TIME (5.50)

#define GPT12E_PISEL (0x885E) /*decimal 34910*/

#define GPT12E_PISEL_ISCAPIN (0x2) /*decimal 2*/

#define GPT12E_T2 (0x4787) /*decimal 18311*/

#define GPT12E_T2CON (0x0) /*decimal 0*/

#define GPT12E_T2CON_T2I_CAPTURE (0x0) /*decimal 0*/

#define GPT12E_T2CON_T2I_COUNTER (0x0) /*decimal 0*/

#define GPT12E_T2CON_T2I_GATED_TIMER_HIGH (0x0) /*decimal 0*/

#define GPT12E_T2CON_T2I_GATED_TIMER_LOW (0x0) /*decimal 0*/

#define GPT12E_T2CON_T2I_INC_EDGE (0x0) /*decimal 0*/

#define GPT12E_T2CON_T2I_INC_ROT (0x0) /*decimal 0*/

#define GPT12E_T2CON_T2I_RELOAD (0x0) /*decimal 0*/

#define GPT12E_T2CON_T2I_TIMER (0x0) /*decimal 0*/

#define GPT12E_T2_TICK (0xB879) /*decimal 47225*/

#define GPT12E_T2_TIME (0.00)

#define GPT12E_T3 (0xFFFF) /*decimal 65535*/

#define GPT12E_T3CON (0x800) /*decimal 2048*/

#define GPT12E_T3CON_T3I_COUNTER (0x0) /*decimal 0*/

#define GPT12E_T3CON_T3I_GATED_TIMER_HIGH (0x0) /*decimal 0*/

#define GPT12E_T3CON_T3I_GATED_TIMER_LOW (0x0) /*decimal 0*/

#define GPT12E_T3CON_T3I_INC_EDGE (0x0) /*decimal 0*/

#define GPT12E_T3CON_T3I_INC_ROT (0x0) /*decimal 0*/

#define GPT12E_T3CON_T3I_TIMER (0x0) /*decimal 0*/

#define GPT12E_T3_TICK (0x1) /*decimal 1*/

#define GPT12E_T3_TIME (0.00)

#define GPT12E_T4 (0xD8F0) /*decimal 55536*/

#define GPT12E_T4CON (0x0) /*decimal 0*/

#define GPT12E_T4CON_T4I_CAPTURE (0x0) /*decimal 0*/

#define GPT12E_T4CON_T4I_COUNTER (0x0) /*decimal 0*/

#define GPT12E_T4CON_T4I_GATED_TIMER_HIGH (0x0) /*decimal 0*/

#define GPT12E_T4CON_T4I_GATED_TIMER_LOW (0x0) /*decimal 0*/

#define GPT12E_T4CON_T4I_INC_EDGE (0x0) /*decimal 0*/

#define GPT12E_T4CON_T4I_INC_ROT (0x0) /*decimal 0*/

#define GPT12E_T4CON_T4I_RELOAD (0x0) /*decimal 0*/

#define GPT12E_T4CON_T4I_TIMER (0x0) /*decimal 0*/

#define GPT12E_T4_TICK (0x0) /*decimal 0*/

#define GPT12E_T4_TIME (1000.00)

#define GPT12E_T5 (0x24) /*decimal 36*/

#define GPT12E_T5CON (0x0) /*decimal 0*/

#define GPT12E_T5CON_T5I_COUNTER (0x0) /*decimal 0*/

#define GPT12E_T5CON_T5I_GATED_TIMER_HIGH (0x0) /*decimal 0*/

#define GPT12E_T5CON_T5I_GATED_TIMER_LOW (0x0) /*decimal 0*/

#define GPT12E_T5CON_T5I_TIMER (0x0) /*decimal 0*/

#define GPT12E_T5IN_SEL (0x0) /*decimal 0*/

#define GPT12E_T5_TICK (0x0) /*decimal 0*/

#define GPT12E_T5_TIME (26200.00)

#define GPT12E_T6 (0xFFFF) /*decimal 65535*/

#define GPT12E_T6CON (0x1000) /*decimal 4096*/

#define GPT12E_T6CON_T6I_COUNTER (0x0) /*decimal 0*/

#define GPT12E_T6CON_T6I_GATED_TIMER_HIGH (0x0) /*decimal 0*/

#define GPT12E_T6CON_T6I_GATED_TIMER_LOW (0x0) /*decimal 0*/

#define GPT12E_T6CON_T6I_TIMER (0x0) /*decimal 0*/

#define GPT12E_T6_TICK (0x1) /*decimal 1*/

#define GPT12E_T6_TIME (0.00)

#define GPT12E_TEMP_CAPREL_SEL (0x1) /*decimal 1*/

#define GPT12E_TEMP_T2_PISEL (0x0) /*decimal 0*/

#define GPT12E_TEMP_T2_SEL (0x0) /*decimal 0*/

#define GPT12E_TEMP_T3OUT (0x0) /*decimal 0*/

#define GPT12E_TEMP_T3_PISEL (0x0) /*decimal 0*/

#define GPT12E_TEMP_T3_SEL (0x0) /*decimal 0*/

#define GPT12E_TEMP_T4_PISEL (0x0) /*decimal 0*/

#define GPT12E_TEMP_T4_SEL (0x1) /*decimal 1*/

#define GPT12E_TEMP_T5_SEL (0x1) /*decimal 1*/

#define GPT12E_TEMP_T6OUT (0x0) /*decimal 0*/

#define GPT12E_TEMP_T6_PISEL (0x0) /*decimal 0*/

#define GPT12E_TEMP_T6_SEL (0x0) /*decimal 0*/

#define GPT1_BASE_CLK (0xA) /*decimal 10*/

#define GPT1_T2_CLK (0xA) /*decimal 10*/

#define GPT1_T3_CLK (0xA) /*decimal 10*/

#define GPT1_T4_CLK (0xA) /*decimal 10*/

#define GPT2_BASE_CLK (2.5)

#define GPT2_T5_CLK (2.5)

#define GPT2_T6_CLK (2.5)

#endif /* GPT12E_DEFINES_H */
