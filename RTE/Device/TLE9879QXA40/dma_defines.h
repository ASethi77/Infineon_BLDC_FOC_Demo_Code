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
#ifndef DMA_DEFINES_H
#define DMA_DEFINES_H

/* XML Version 2.2.3 */
#define DMA_XML_VERSION (20203)

#define DMA_CFG (0x0) /*decimal 0*/

#define DMA_CH0_DST enter destination location

#define DMA_CH0_DST_EXT (0x0) /*decimal 0*/

#define DMA_CH0_DST_PTR_OFFS (0x0) /*decimal 0*/

#define DMA_CH0_INC (0x0) /*decimal 0*/

#define DMA_CH0_NoOfTrans (0x1) /*decimal 1*/

#define DMA_CH0_SIZE (0x1) /*decimal 1*/

#define DMA_CH0_SRC ADC1->RES_OUT0.reg

#define DMA_CH0_SRC_ADC1 (0x0) /*decimal 0*/

#define DMA_CH0_SRC_EXT (0x0) /*decimal 0*/

#define DMA_CH0_SRC_PTR_OFFS (0x0) /*decimal 0*/

#define DMA_CH0_SRC_SEL (0x0) /*decimal 0*/

#define DMA_CH0_TASK_NoOfTasks (0x0) /*decimal 0*/

#define DMA_CH0_TASK_SRC enter source reference

#define DMA_CH0_TRANS_MODE (0x0) /*decimal 0*/

#define DMA_CH10_DST enter destination reference

#define DMA_CH10_DST_EXT (0x0) /*decimal 0*/

#define DMA_CH10_DST_PTR_OFFS (0x0) /*decimal 0*/

#define DMA_CH10_INC (0x0) /*decimal 0*/

#define DMA_CH10_NoOfTrans (0x1) /*decimal 1*/

#define DMA_CH10_SIZE (0x1) /*decimal 1*/

#define DMA_CH10_SRC ADC1->RES_OUT6.reg

#define DMA_CH10_SRC_EXT (0x0) /*decimal 0*/

#define DMA_CH10_SRC_PTR_OFFS (0x0) /*decimal 0*/

#define DMA_CH10_SRC_SEL (0x0) /*decimal 0*/

#define DMA_CH10_TASK_NoOfTasks (0x0) /*decimal 0*/

#define DMA_CH10_TASK_SRC enter source reference

#define DMA_CH10_TRANS_MODE (0x0) /*decimal 0*/

#define DMA_CH11_DST enter destination reference

#define DMA_CH11_DST_EXT (0x0) /*decimal 0*/

#define DMA_CH11_DST_PTR_OFFS (0x0) /*decimal 0*/

#define DMA_CH11_INC (0x0) /*decimal 0*/

#define DMA_CH11_NoOfTrans (0x1) /*decimal 1*/

#define DMA_CH11_SIZE (0x1) /*decimal 1*/

#define DMA_CH11_SRC enter source reference

#define DMA_CH11_SRC_EXT (0x0) /*decimal 0*/

#define DMA_CH11_SRC_PTR_OFFS (0x0) /*decimal 0*/

#define DMA_CH11_TASK_NoOfTasks (0x0) /*decimal 0*/

#define DMA_CH11_TASK_SRC enter source reference

#define DMA_CH11_TRANS_MODE (0x0) /*decimal 0*/

#define DMA_CH12_DST enter destination reference

#define DMA_CH12_DST_EXT (0x0) /*decimal 0*/

#define DMA_CH12_DST_PTR_OFFS (0x0) /*decimal 0*/

#define DMA_CH12_INC (0x0) /*decimal 0*/

#define DMA_CH12_NoOfTrans (0x1) /*decimal 1*/

#define DMA_CH12_SIZE (0x1) /*decimal 1*/

#define DMA_CH12_SRC enter source reference

#define DMA_CH12_SRC_EXT (0x0) /*decimal 0*/

#define DMA_CH12_SRC_PTR_OFFS (0x0) /*decimal 0*/

#define DMA_CH12_TASK_NoOfTasks (0x0) /*decimal 0*/

#define DMA_CH12_TASK_SRC enter source reference

#define DMA_CH12_TRANS_MODE (0x0) /*decimal 0*/

#define DMA_CH1_DST enter destination reference

#define DMA_CH1_DST_EXT (0x0) /*decimal 0*/

#define DMA_CH1_DST_PTR_OFFS (0x0) /*decimal 0*/

#define DMA_CH1_INC (0x0) /*decimal 0*/

#define DMA_CH1_NoOfTrans (0x1) /*decimal 1*/

#define DMA_CH1_SIZE (0x1) /*decimal 1*/

#define DMA_CH1_SRC ADC1->RES_OUT0.reg

#define DMA_CH1_SRC_ADC1 (0x0) /*decimal 0*/

#define DMA_CH1_SRC_EXT (0x0) /*decimal 0*/

#define DMA_CH1_SRC_PTR_OFFS (0x0) /*decimal 0*/

#define DMA_CH1_SRC_SEL (0x0) /*decimal 0*/

#define DMA_CH1_TASK_NoOfTasks (0x0) /*decimal 0*/

#define DMA_CH1_TASK_SRC enter source reference

#define DMA_CH1_TRANS_MODE (0x0) /*decimal 0*/

#define DMA_CH2_DST SSC1->TB.reg

#define DMA_CH2_DST_EXT (0x0) /*decimal 0*/

#define DMA_CH2_DST_PTR_OFFS (0x0) /*decimal 0*/

#define DMA_CH2_DST_SEL (0x0) /*decimal 0*/

#define DMA_CH2_INC (0x0) /*decimal 0*/

#define DMA_CH2_NoOfTrans (0x1) /*decimal 1*/

#define DMA_CH2_SIZE (0x1) /*decimal 1*/

#define DMA_CH2_SRC enter source reference

#define DMA_CH2_SRC_EXT (0x0) /*decimal 0*/

#define DMA_CH2_SRC_PTR_OFFS (0x0) /*decimal 0*/

#define DMA_CH2_TASK_NoOfTasks (0x0) /*decimal 0*/

#define DMA_CH2_TASK_SRC enter source reference

#define DMA_CH2_TRANS_MODE (0x0) /*decimal 0*/

#define DMA_CH3_DST enter destination reference

#define DMA_CH3_DST_EXT (0x0) /*decimal 0*/

#define DMA_CH3_DST_PTR_OFFS (0x0) /*decimal 0*/

#define DMA_CH3_INC (0x0) /*decimal 0*/

#define DMA_CH3_NoOfTrans (0x1) /*decimal 1*/

#define DMA_CH3_SIZE (0x1) /*decimal 1*/

#define DMA_CH3_SRC SSC1->RB.reg

#define DMA_CH3_SRC_EXT (0x0) /*decimal 0*/

#define DMA_CH3_SRC_PTR_OFFS (0x0) /*decimal 0*/

#define DMA_CH3_SRC_SEL (0x0) /*decimal 0*/

#define DMA_CH3_TASK_NoOfTasks (0x0) /*decimal 0*/

#define DMA_CH3_TASK_SRC enter source reference

#define DMA_CH3_TRANS_MODE (0x0) /*decimal 0*/

#define DMA_CH4_DST enter destination reference

#define DMA_CH4_DST_EXT (0x0) /*decimal 0*/

#define DMA_CH4_DST_PTR_OFFS (0x0) /*decimal 0*/

#define DMA_CH4_INC (0x0) /*decimal 0*/

#define DMA_CH4_NoOfTrans (0x1) /*decimal 1*/

#define DMA_CH4_SIZE (0x1) /*decimal 1*/

#define DMA_CH4_SRC ADC1->RES_OUT0.reg

#define DMA_CH4_SRC_EXT (0x0) /*decimal 0*/

#define DMA_CH4_SRC_PTR_OFFS (0x0) /*decimal 0*/

#define DMA_CH4_SRC_SEL (0x0) /*decimal 0*/

#define DMA_CH4_TASK_NoOfTasks (0x0) /*decimal 0*/

#define DMA_CH4_TASK_SRC enter source reference

#define DMA_CH4_TRANS_MODE (0x0) /*decimal 0*/

#define DMA_CH5_DST enter destination reference

#define DMA_CH5_DST_EXT (0x0) /*decimal 0*/

#define DMA_CH5_DST_PTR_OFFS (0x0) /*decimal 0*/

#define DMA_CH5_INC (0x0) /*decimal 0*/

#define DMA_CH5_NoOfTrans (0x1) /*decimal 1*/

#define DMA_CH5_SIZE (0x1) /*decimal 1*/

#define DMA_CH5_SRC ADC1->RES_OUT1.reg

#define DMA_CH5_SRC_EXT (0x0) /*decimal 0*/

#define DMA_CH5_SRC_PTR_OFFS (0x0) /*decimal 0*/

#define DMA_CH5_SRC_SEL (0x0) /*decimal 0*/

#define DMA_CH5_TASK_NoOfTasks (0x0) /*decimal 0*/

#define DMA_CH5_TASK_SRC enter source reference

#define DMA_CH5_TRANS_MODE (0x0) /*decimal 0*/

#define DMA_CH6_DST enter destination reference

#define DMA_CH6_DST_EXT (0x0) /*decimal 0*/

#define DMA_CH6_DST_PTR_OFFS (0x0) /*decimal 0*/

#define DMA_CH6_INC (0x0) /*decimal 0*/

#define DMA_CH6_NoOfTrans (0x1) /*decimal 1*/

#define DMA_CH6_SIZE (0x1) /*decimal 1*/

#define DMA_CH6_SRC ADC1->RES_OUT2.reg

#define DMA_CH6_SRC_EXT (0x0) /*decimal 0*/

#define DMA_CH6_SRC_PTR_OFFS (0x0) /*decimal 0*/

#define DMA_CH6_SRC_SEL (0x0) /*decimal 0*/

#define DMA_CH6_TASK_NoOfTasks (0x0) /*decimal 0*/

#define DMA_CH6_TASK_SRC enter source reference

#define DMA_CH6_TRANS_MODE (0x0) /*decimal 0*/

#define DMA_CH7_DST enter destination reference

#define DMA_CH7_DST_EXT (0x0) /*decimal 0*/

#define DMA_CH7_DST_PTR_OFFS (0x0) /*decimal 0*/

#define DMA_CH7_INC (0x0) /*decimal 0*/

#define DMA_CH7_NoOfTrans (0x1) /*decimal 1*/

#define DMA_CH7_SIZE (0x1) /*decimal 1*/

#define DMA_CH7_SRC ADC1->RES_OUT3.reg

#define DMA_CH7_SRC_EXT (0x0) /*decimal 0*/

#define DMA_CH7_SRC_PTR_OFFS (0x0) /*decimal 0*/

#define DMA_CH7_SRC_SEL (0x0) /*decimal 0*/

#define DMA_CH7_TASK_NoOfTasks (0x0) /*decimal 0*/

#define DMA_CH7_TASK_SRC enter source reference

#define DMA_CH7_TRANS_MODE (0x0) /*decimal 0*/

#define DMA_CH8_DST enter destination reference

#define DMA_CH8_DST_EXT (0x0) /*decimal 0*/

#define DMA_CH8_DST_PTR_OFFS (0x0) /*decimal 0*/

#define DMA_CH8_INC (0x0) /*decimal 0*/

#define DMA_CH8_NoOfTrans (0x1) /*decimal 1*/

#define DMA_CH8_SIZE (0x1) /*decimal 1*/

#define DMA_CH8_SRC ADC1->RES_OUT4.reg

#define DMA_CH8_SRC_EXT (0x0) /*decimal 0*/

#define DMA_CH8_SRC_PTR_OFFS (0x0) /*decimal 0*/

#define DMA_CH8_SRC_SEL (0x0) /*decimal 0*/

#define DMA_CH8_TASK_NoOfTasks (0x0) /*decimal 0*/

#define DMA_CH8_TASK_SRC enter source reference

#define DMA_CH8_TRANS_MODE (0x0) /*decimal 0*/

#define DMA_CH9_DST enter destination reference

#define DMA_CH9_DST_EXT (0x0) /*decimal 0*/

#define DMA_CH9_DST_PTR_OFFS (0x0) /*decimal 0*/

#define DMA_CH9_INC (0x0) /*decimal 0*/

#define DMA_CH9_NoOfTrans (0x1) /*decimal 1*/

#define DMA_CH9_SIZE (0x1) /*decimal 1*/

#define DMA_CH9_SRC ADC1->RES_OUT5.reg

#define DMA_CH9_SRC_EXT (0x0) /*decimal 0*/

#define DMA_CH9_SRC_PTR_OFFS (0x0) /*decimal 0*/

#define DMA_CH9_SRC_SEL (0x0) /*decimal 0*/

#define DMA_CH9_TASK_NoOfTasks (0x0) /*decimal 0*/

#define DMA_CH9_TASK_SRC enter source reference

#define DMA_CH9_TRANS_MODE (0x0) /*decimal 0*/

#define DMA_EN (0x0) /*decimal 0*/

#endif /* DMA_DEFINES_H */
