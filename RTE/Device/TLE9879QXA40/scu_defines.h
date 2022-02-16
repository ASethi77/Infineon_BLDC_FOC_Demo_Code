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
#ifndef SCU_DEFINES_H
#define SCU_DEFINES_H

/* XML Version 2.2.3 */
#define SCU_XML_VERSION (20203)

#define SCUPM_WDT1_PERIOD (0x3F0) /*decimal 1008*/

#define SCUPM_WDT1_PERIOD_EDIT (0x3F0) /*decimal 1008*/

#define SCUPM_WDT1_TRIG (0x3F) /*decimal 63*/

#define SCUPM_WDT1_TRIGGER (0x2BB) /*decimal 699*/

#define SCU_APCLK1 (0x1) /*decimal 1*/

#define SCU_APCLK2 (0x13) /*decimal 19*/

#define SCU_APCLK_BG_CLK (0x14) /*decimal 20*/

#define SCU_APCLK_CTRL1 (0x14) /*decimal 20*/

#define SCU_APCLK_CTRL2 (0x0) /*decimal 0*/

#define SCU_APCLK_FILT_CLK (0x2) /*decimal 2*/

#define SCU_APCLK_MI_CLK (0x14) /*decimal 20*/

#define SCU_AUTO_FSYS (0x2625A00) /*decimal 40000000*/

#define SCU_AUTO_FSYS_SEL (0x0) /*decimal 0*/

#define SCU_BCON1 (0x0) /*decimal 0*/

#define SCU_BCON2 (0x1) /*decimal 1*/

#define SCU_CFLASH_WPROT (0x1) /*decimal 1*/

#define SCU_CFLASH_WPROT_PW (0x0) /*decimal 0*/

#define SCU_CKOUT_FREQ (0.5)

#define SCU_CMCON1 (0x0) /*decimal 0*/

#define SCU_COCON (0x7F) /*decimal 127*/

#define SCU_DFLASH_WPROT (0x0) /*decimal 0*/

#define SCU_DFLASH_WPROT_PW (0x0) /*decimal 0*/

#define SCU_DMASRCSEL (0x0) /*decimal 0*/

#define SCU_DMASRCSEL2 (0x0) /*decimal 0*/

#define SCU_EXINT1_FALLING_INT_EN (0x0) /*decimal 0*/

#define SCU_EXINT1_RISING_INT_EN (0x0) /*decimal 0*/

#define SCU_EXINT2_FALLING_INT_EN (0x0) /*decimal 0*/

#define SCU_EXINT2_RISING_INT_EN (0x0) /*decimal 0*/

#define SCU_FSYS (0x2625A00) /*decimal 40000000*/

#define SCU_GPT12PISEL (0x0) /*decimal 0*/

#define SCU_IEN0 (0x80) /*decimal 128*/

#define SCU_MODIEN3 (0x0) /*decimal 0*/

#define SCU_MODIEN4 (0x0) /*decimal 0*/

#define SCU_MODPISEL (0x5) /*decimal 5*/

#define SCU_MODPISEL1 (0x0) /*decimal 0*/

#define SCU_MODPISEL2 (0x81) /*decimal 129*/

#define SCU_MODPISEL3 (0x0) /*decimal 0*/

#define SCU_OSC_CON (0xB0) /*decimal 176*/

#define SCU_PINSEL (0x0) /*decimal 0*/

#define SCU_PLL_CON (0x60) /*decimal 96*/

#define SCU_PLL_fPLL (0x28) /*decimal 40*/

#define SCU_WDTCON (0x0) /*decimal 0*/

#define SCU_WDTREL (0x1) /*decimal 1*/

#define SCU_WDTWINB (0x80) /*decimal 128*/

#define SCU_WDT_TIME_SEL (0x0) /*decimal 0*/

#define SCU_WDT_TIME_TICK (0x1) /*decimal 1*/

#define SCU_WDT_TIME_TIME (1.00)

#define SCU_XTAL_EN (0x0) /*decimal 0*/

#define SCU_XTAL_FREQ (5.00)

#define VCO_range (0x0) /*decimal 0*/

#define check_fsys (0x0) /*decimal 0*/

#define fVCO (0x50) /*decimal 80*/

#endif /* SCU_DEFINES_H */
