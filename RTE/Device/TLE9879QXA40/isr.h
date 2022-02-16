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
 * \file     isr.h
 *
 * \brief    Interrupt Service Routines low level access library
 *
 * \version  V0.2.8
 * \date     31. Jul 2020
 *
 *  \note This file violates [MISRA Rule 27], [MISRA 2012 Rule 8.5, required], [MISRA 2012 Rule 2.2, required], [MISRA 2012 Rule 10.7, required], [MISRA 2012 Rule 12.2, required]
 */

/*******************************************************************************
**                             Author(s) Identity                             **
********************************************************************************
** Initials     Name                                                          **
** ---------------------------------------------------------------------------**
** DM           Daniel Mysliwitz                                              **
** BG           Blandine Guillot                                              **
** JO           Julia Ott                                                     **
*******************************************************************************/

/*******************************************************************************
**                          Revision Control History                          **
********************************************************************************
** V0.1.0: 2014-07-01, DM:   Initial version                                  **
** V0.1.1: 2014-07-24, DM:   DMA ISRs, interrupt flags now cleared after      **
**                           call of Callback function                        **
** V0.1.2: 2014-10-31, DM:   EXINTx decoding corrected                        **
** V0.1.3: 2015-02-10, DM:   Individual header file added                     **
** V0.1.4: 2015-07-15, DM:   #define DEVICE replaced by #define UC_SERIES     **
**                           BEMF callbacks added                             **
** V0.1.5: 2015-09-10, DM:   BEMF interrupt status flags naming corrected     **
** V0.1.6: 2016-07-06, DM:   EXTINTx and MON corrected                        **
** V0.1.7: 2016-08-04, DM:   ADC2.MON interrupt handling added (TLE987x)      **
** V0.1.8: 2016-10-07, DM:   all ISRs: interrupt enable checked at runtime    **
** V0.1.9: 2017-02-24, DM:   UART2 callbacks fixed                            **
** V0.2.0: 2017-04-04, DM:   NMI ISR: ECC enable defines added                **
** V0.2.1: 2017-11-09, DM:   ADC34 ISR handling added                         **
**                           VDDEXT fail interrupt handling fixed             **
** V0.2.2: 2017-11-15, DM:   MISRA 2012 compliance, the following PC-Lint     **
**                           rules are globally deactivated:                  **
**                           - Info 793: ANSI/ISO limit of 6 'significant     **
**                             characters in an external identifier           **
**                           - Info 835: A zero has been given as right       **
**                             argument to operator                           **
**                           - Info 845: The left argument to operator '&'    **
**                             is certain to be 0                             **
**                           The following rules are locally disabled:        **
**                           - Info 762: Redundantly declared symbol '...'    **
**                             previous declaration ...                       **
**                           - Note 961: Violates MISRA 1998 Advisory Rule 27,**
**                             object/function previously declared: '...'     **
**                           - Warning 522: Highest operation, function '...',**
**                             lacks side-effects [MISRA Rule 53],            **
**                             [MISRA Rule 85]                                **
**                           - Note 960: Violates MISRA 1998 Required Rule 115**
**                             Re-use of C90 identifier pattern               **
** V0.2.3: 2018-03-12, DM:   The following rules are locally disabled:        **
**                           - Note 9032: Composite expression with smaller   **
**                             essential type than other operand [MISRA 2012  **
**                             Rule 10.7, required]                           **
**                           - Note 9053: the shift value is at least the     **
**                             precision of the essential type of the left    **
**                             hand side [MISRA 2012 Rule 12.2, required]     **
**                           The following rules are activated again:         **
**                           - Note 961: Violates MISRA 1998 Advisory Rule 27,**
**                             object/function previously declared: '...'     **
**                           - Warning 522: Highest operation, function '...',**
**                             lacks side-effects [MISRA Rule 53],            **
**                             [MISRA Rule 85]                                **
**                           - Note 960: Violates MISRA 1998 Required Rule 115**
**                             Re-use of C90 identifier pattern               **
** V0.2.4: 2018-11-27, JO:   Doxygen update                                   **
**                           Moved revision history from isr.c to isr.h       **
** V0.2.5: 2019-02-23, DM:   SDADC interrupt handling put into TLE9879-2/     **
**                           TLE9872-2 preprocessor block                     **
** V0.2.6: 2020-04-15, BG:   Updated revision history format                  **
** V0.2.7: 2020-07-21, BG:   EP-439: Formatted .h/.c files                    **
** V0.2.8: 2020-07-31, DM:   define CCU6_INP to 0 if CCU6 is not added to     **
**                           project                                          **
*******************************************************************************/

#ifndef ISR_H
#define ISR_H

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
/** \brief The GPT1_IRQHandler checks which interrupt caused the call of the node handler
 * (interrupt enabled and status bit indicates that this interrupt occurred).
 * Then it calls the corresponding interrupt handler and clears the interrupt status bit.
 * GPT1_IRQHandler is responsible for:
 * GPT1 T2 INT, GPT1 T3 INT, GPT1 T4 INT
 *
 * \ingroup isr_api
 */
void GPT1_IRQHandler(void);


/** \brief The GPT2_IRQHandler checks which interrupt caused the call of the node handler
 * (interrupt enabled and status bit indicates that this interrupt occurred).
 * Then it calls the corresponding interrupt handler and clears the interrupt status bit.
 * GPT2_IRQHandler is responsible for:
 * GPT2 T5 INT, GPT2 T6 INT, GPT2 CAPREL INT
 *
 * \ingroup isr_api
 */
void GPT2_IRQHandler(void);


/** \brief The ADC2_IRQHandler checks which interrupt caused the call of the node handler
 * (interrupt enabled and status bit indicates that this interrupt occurred).
 * Then it calls the corresponding interrupt handler and clears the interrupt status bit.
 * ADC2_IRQHandler is responsible for:
 * TIMER3 HB INT, TIMER3 LB INT, ADC2 VBG UP INT, ADC2 VBG LO INT,
 * BEMF U HI INT, BEMF U LO INT, BEMF V HI INT, BEMF V LO INT, BEMF W HI INT, BEMF W LO INT,
 * ADC34 ADC3 INT, ADC34 ADC4 INT
 *
 * \ingroup isr_api
 */
void ADC2_IRQHandler(void);


/** \brief The ADC1_IRQHandler checks which interrupt caused the call of the node handler
 * (interrupt enabled and status bit indicates that this interrupt occurred).
 * Then it calls the corresponding interrupt handler and clears the interrupt status bit.
 * ADC1_IRQHandler is responsible for:
 * ADC1 CH0 INT, ADC1 CH1 INT, ADC1 CH2 INT, ADC1 CH3 INT,
 * ADC1 CH4 INT, ADC1 CH5 INT, ADC1 CH6 INT, ADC1 CH7 INT,
 * ADC1 EIM INT, ADC1 ESM INT,
 * ADC2 VAREF UP INT, ADC2 VAREF LO INT, ADC2 VAREF OL INT
 *
 * \ingroup isr_api
 */
void ADC1_IRQHandler(void);


/** \brief The SSU6SR0_IRQHandler checks which interrupt caused the call of the node handler
* (interrupt enabled and status bit indicates that this interrupt occurred).
* Then it calls the corresponding interrupt handler and clears the interrupt status bit.
* SSU6SR0_IRQHandler is responsible for:
* CCU6_CH0_CM_R_INT_EN, CCU6_CH0_CM_F_INT_EN
* CCU6_CH1_CM_R_INT_EN, CCU6_CH1_CM_F_INT_EN
* CCU6_CH2_CM_R_INT_EN, CCU6_CH2_CM_F_INT_EN
* CCU6_T12_OM_INT_EN, CCU6_T12_PM_INT_EN
* CCU6_T13_CM_INT_EN, CCU6_T13_PM_INT_EN
* CCU6_TRAP_INT_EN, CCU6_WHE_INT_EN, CCU6_CHE_INT_EN, CCU6_MCM_STR_INT_EN
*
* \ingroup isr_api
*/
void CCU6SR0_IRQHandler(void);


/** \brief The SSU6SR1_IRQHandler checks which interrupt caused the call of the node handler
* (interrupt enabled and status bit indicates that this interrupt occurred).
* Then it calls the corresponding interrupt handler and clears the interrupt status bit.
* SSU6SR1_IRQHandler is responsible for:
* CCU6_CH0_CM_R_INT_EN, CCU6_CH0_CM_F_INT_EN
* CCU6_CH1_CM_R_INT_EN, CCU6_CH1_CM_F_INT_EN
* CCU6_CH2_CM_R_INT_EN, CCU6_CH2_CM_F_INT_EN
* CCU6_T12_OM_INT_EN, CCU6_T12_PM_INT_EN
* CCU6_T13_CM_INT_EN, CCU6_T13_PM_INT_EN
* CCU6_TRAP_INT_EN, CCU6_WHE_INT_EN, CCU6_CHE_INT_EN, CCU6_MCM_STR_INT_EN
*
* \ingroup isr_api
*/
void CCU6SR1_IRQHandler(void);


/** \brief The SSU6SR2_IRQHandler checks which interrupt caused the call of the node handler
* (interrupt enabled and status bit indicates that this interrupt occurred).
* Then it calls the corresponding interrupt handler and clears the interrupt status bit.
* SSU6SR2_IRQHandler is responsible for:
* CCU6_CH0_CM_R_INT_EN, CCU6_CH0_CM_F_INT_EN
* CCU6_CH1_CM_R_INT_EN, CCU6_CH1_CM_F_INT_EN
* CCU6_CH2_CM_R_INT_EN, CCU6_CH2_CM_F_INT_EN
* CCU6_T12_OM_INT_EN, CCU6_T12_PM_INT_EN
* CCU6_T13_CM_INT_EN, CCU6_T13_PM_INT_EN
* CCU6_TRAP_INT_EN, CCU6_WHE_INT_EN, CCU6_CHE_INT_EN, CCU6_MCM_STR_INT_EN
*
* \ingroup isr_api
*/
void CCU6SR2_IRQHandler(void);


/** \brief The SSU6SR3_IRQHandler checks which interrupt caused the call of the node handler
* (interrupt enabled and status bit indicates that this interrupt occurred).
* Then it calls the corresponding interrupt handler and clears the interrupt status bit.
* SSU6SR3_IRQHandler is responsible for:
* CCU6_CH0_CM_R_INT_EN, CCU6_CH0_CM_F_INT_EN
* CCU6_CH1_CM_R_INT_EN, CCU6_CH1_CM_F_INT_EN
* CCU6_CH2_CM_R_INT_EN, CCU6_CH2_CM_F_INT_EN
* CCU6_T12_OM_INT_EN, CCU6_T12_PM_INT_EN
* CCU6_T13_CM_INT_EN, CCU6_T13_PM_INT_EN
* CCU6_TRAP_INT_EN, CCU6_WHE_INT_EN, CCU6_CHE_INT_EN, CCU6_MCM_STR_INT_EN
*
* \ingroup isr_api
*/
void CCU6SR3_IRQHandler(void);


/** \brief The SSC1_IRQHandler checks which interrupt caused the call of the node handler
* (interrupt enabled and status bit indicates that this interrupt occurred).
* Then it calls the corresponding interrupt handler and clears the interrupt status bit.
* SSC1_IRQHandler is responsible for:
* SSC1 RX INT, SSC1 TX INT, SSC1 ERR INT
*
* \ingroup isr_api
*/
void SSC1_IRQHandler(void);


/** \brief The SSC2_IRQHandler checks which interrupt caused the call of the node handler
* (interrupt enabled and status bit indicates that this interrupt occurred).
* Then it calls the corresponding interrupt handler and clears the interrupt status bit.
* SSC2_IRQHandler is responsible for:
* SSC2 RX INT, SSC2 TX INT, SSC2 ERR INT
*
* \ingroup isr_api
*/
void SSC2_IRQHandler(void);


/** \brief The UART1_IRQHandler checks which interrupt caused the call of the node handler
 * (interrupt enabled and status bit indicates that this interrupt occurred).
 * Then it calls the corresponding interrupt handler and clears the interrupt status bit.
 * UART1_IRQHandler is responsible for:
 * UART1 RX INT, UART1 TX INT,
 * TIMER2 EXF2 INT, TIMER2 TF2 INT,
 * LIN EOF INT, LIN ERR INT, LIN OC INT, LIN OT INT, LIN TMOUT INT
 *
 * \ingroup isr_api
 */
void UART1_IRQHandler(void);


/** \brief The UART2_IRQHandler checks which interrupt caused the call of the node handler
* (interrupt enabled and status bit indicates that this interrupt occurred).
* Then it calls the corresponding interrupt handler and clears the interrupt status bit.
* UART2_IRQHandler is responsible for:
* UART2 RX INT, UART2 TX INT,
* TIMER21 EXF2 INT, TIMER21 TF2 INT,
* SCU EXINT2 RISING INT, SCU EXINT2 FALLING INT
*
* \ingroup isr_api
*/
void UART2_IRQHandler(void);


/** \brief The EXINT0_IRQHandler checks which interrupt caused the call of the node handler
 * (interrupt enabled and status bit indicates that this interrupt occurred).
 * Then it calls the corresponding interrupt handler and clears the interrupt status bit.
 * EXINT0_IRQHandler is responsible for:
 * SCU EXINT0 RISING INT, SCU EXINT0 FALLING INT,
 * MON RISING INT, MON FALLING INT
 *
 * \ingroup isr_api
 */
void EXINT0_IRQHandler(void);


/** \brief The EXINT1_IRQHandler checks which interrupt caused the call of the node handler
 * (interrupt enabled and status bit indicates that this interrupt occurred).
 * Then it calls the corresponding interrupt handler and clears the interrupt status bit.
 * EXINT1_IRQHandler is responsible for:
 * SCU EXINT1 RISING INT, SCU EXINT1 FALLING INT,
 *
 * \ingroup isr_api
 */
void EXINT1_IRQHandler(void);


/** \brief The BDRV_IRQHandler checks which interrupt caused the call of the node handler
 * (interrupt enabled and status bit indicates that this interrupt occurred).
 * Then it calls the corresponding interrupt handler and clears the interrupt status bit.
 * BDRV_IRQHandler is responsible for:
 * BDRV HS1 OC INT, BDRV LS1 OC INT,
 * BDRV HS2 OC INT, BDRV LS2 OC INT,
 * BDRV HS3 OC INT, BDRV LS3 OC INT,
 * BDRV HS1 DS INT, BDRV LS1 DS INT,
 * BDRV HS2 DS INT, BDRV LS2 DS INT,
 * BDRV HS3 DS INT, BDRV LS3 DS INT,
 * ADC2 VSD UP INT, ADC2 VSD LO INT,
 * BDRV VCP LO2 INT,
 * ADC2 VCP UP INT, ADC2 VCP LO INT
 *
 * \ingroup isr_api
 */
void BDRV_IRQHandler(void);


/** \brief The DMA_IRQHandler checks which interrupt caused the call of the node handler
 * (interrupt enabled and status bit indicates that this interrupt occurred).
 * Then it calls the corresponding interrupt handler and clears the interrupt status bit.
 * DMA_IRQHandler is responsible for:
 * DMA_SQ1_RDY_INT, DMA_SQ2_RDY_INT,
 * DMA_SSC_TX_INT, DMA_SSC_RX_INT,
 * DMA_CH1_INT, DMA_CH2_INT, DMA_CH3_INT_EN, DMA_CH4_INT,
 * DMA_CH5_INT, DMA_CH6_INT, DMA_CH7_INT, DMA_CH8_INT_EN,
 * DMA_GPT12E_INT
 *
 * \ingroup isr_api
 */
void DMA_IRQHandler(void);


/** \brief The NMI_Handler checks which interrupt caused the call of the node handler
 * (interrupt enabled and status bit indicates that this interrupt occurred).
 * Then it calls the corresponding interrupt handler and clears the interrupt status bit.
 * NMI_Handler is responsible for:
 * SCU_NMI_WDT_INT, SCU_NMI_PLL_INT, SCU_NMI_NVM_INT,
 * SCU_NMI_OWD_INT, SCU_NMI_MAP_INT,
 * SCU_ECC_RAM_DB_INT_EN, SCU_ECC_NVM_DB_INT_EN,
 * ADC2_SYS_TEMP_UP_INT, ADC2_SYS_TEMP_LO_INT,
 * ADC2_PMU_TEMP_UP_INT, ADC2_PMU_TEMP_LO_INT,
 * ADC2_VS_UP_INT, ADC2_VS_LO_INT,
 * ADC2_VBAT_UP_INT, ADC2_VBAT_LO_INT,
 * ADC2_VDDC_UP_INT, ADC2_VDDC_LO_INT,
 * ADC2_VDDP_UP_INT, ADC2_VDDP_LO_INT,
 * ADC2_MON_UP_INT, ADC2_MON_LO_INT,
 * PMU_VDDEXT_SHORT_INT, PMU_VDDEXT_OV_INT, PMU_VDDEXT_OL_INT,
 * PMU_VDDC_OV_INT, PMU_VDDC_OL_INT,
 * PMU_VDDP_OV_INT, PMU_VDDP_OL_INT
 *
 * \ingroup isr_api
 */
void NMI_Handler(void);


/** \brief The HardFault_Handler handles the HardFault exception
 *
 * \ingroup isr_api
 */
void HardFault_Handler(void);


/** \brief The MemManage_Handler handles the MemManage exception
 *
 * \ingroup isr_api
 */
void MemManage_Handler(void);


/** \brief The BusFault_Handler handles the BusFault exception
 *
 * \ingroup isr_api
 */
void BusFault_Handler(void);


/** \brief The UsageFault_Handler handles the UsageFault exception
 *
 * \ingroup isr_api
 */
void UsageFault_Handler(void);


/** \brief The SysTick_Handler handles the SysTick exception
 *
 * \ingroup isr_api
 */
void SysTick_Handler(void);


#endif
