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
 * \file     lin.h
 *
 * \brief    LIN low level access library
 *
 * \version  V0.1.9
 * \date     21. Jul 2020
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
** V0.1.0: 2014-06-02, DM:   Initial version                                  **
** V0.1.1: 2014-06-17, DM:   Adding functions to change Trx. Mode and Slope   **
** V0.1.2: 2014-09-22, DM:   LIN_Get_Mode function added                      **
** V0.1.3: 2015-02-10, DM:   Individual header file added                     **
** V0.1.4: 2016-07-07, DM:   Init function corrected to be able to set        **
**                           corrected slope mode                             **
** V0.1.5: 2016-10-12, DM:   LINST initialization added                       **
** V0.1.6: 2017-10-10, DM:   MISRA 2012 compliance, the following PC-Lint     **
**                           rules are globally deactivated:                  **
**                           - Info 793: ANSI/ISO limit of 6 'significant     **
**                             characters in an external identifier           **
**                           - Info 835: A zero has been given as right       **
**                             argument to operator                           **
**                           - Info 845: The left argument to operator '&'    **
**                             is certain to be 0                             **
**                           Replaced macros by INLINE functions              **
**                           Replaced register accesses within functions by   **
**                           function calls                                   **
**                           Replaced __STATIC_INLINE by INLINE               **
** V0.1.7: 2018-11-27, JO:   Doxygen update                                   **
**                           Moved revision history from lin.c to lin.h       **
** V0.1.8: 2020-04-15, BG:   Updated revision history format                  **
** V0.1.9: 2020-07-21, BG:   EP-439: Formatted .h/.c files                    **
*******************************************************************************/

#ifndef LIN_H
#define LIN_H

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "tle987x.h"
#include "types.h"
#include "sfr_access.h"

/*******************************************************************************
**                          Global Macro Definitions                          **
*******************************************************************************/
/**\brief LIN MODE, SLEEP MODE */
#define LIN_MODE_SLEEP        (0u)
/**\brief LIN MODE, RCV ONLY MODE */
#define LIN_MODE_RCV_ONLY     (1u)
/**\brief LIN MODE, NORMAL MODE */
#define LIN_MODE_NORMAL       (3u)

/**\brief LIN MODE READ, SLEEP MODE */
#define LIN_GET_MODE_SLEEP    (1u)
/**\brief LIN MODE READ, RCV ONLY MODE */
#define LIN_GET_MODE_RCV_ONLY (5u)
/**\brief LIN MODE READ, NORMAL MODE */
#define LIN_GET_MODE_NORMAL   (7u)

/**\brief LIN SLOPE MODE, NORMAL SLOPE */
#define LIN_SLOPE_NORMAL      (0u)
/**\brief LIN SLOPE MODE, FAST SLOPE */
#define LIN_SLOPE_FAST        (1u)
/**\brief LIN SLOPE MODE, LOW SLOPE */
#define LIN_SLOPE_LOW         (2u)
/**\brief LIN SLOPE MODE, FLASH SLOPE */
#define LIN_SLOPE_FLASH       (3u)

/*******************************************************************************
**                     Global Inline Function Definitions                     **
*******************************************************************************/
/** \brief reads End of SYN Byte Interrupt Status.
 *
 * \return End of SYN Byte Interrupt Status
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the LIN End of SYN Byte interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   LIN_Sync_Int_En();
 *   if (LIN_End_Of_Sync_Sts() == (uint8)1)
 *   {
 *     LIN_EOF_CALLBACK();
 *     LIN_End_Of_Sync_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE uint8 LIN_End_Of_Sync_Sts(void)
{
  return ( u1_Field_Rd8(&SCU->LINST.reg, (uint8)SCU_LINST_EOFSYN_Pos, (uint8)SCU_LINST_EOFSYN_Msk) );
}

/** \brief reads SYN Byte Error Interrupt Status.
 *
 * \return SYN Byte Error Interrupt Status
 *
 * \brief <b>Example</b><br>
 * \brief This example threats the SYN Byte Error interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   LIN_Sync_Int_En();
 *   if (LIN_Err_In_Sync_Sts() == (uint8)1)
 *   {
 *     LIN_ERR_CALLBACK();
 *     LIN_Err_In_Sync_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE uint8 LIN_Err_In_Sync_Sts(void)
{
  return ( u1_Field_Rd8(&SCU->LINST.reg, (uint8)SCU_LINST_ERRSYN_Pos, (uint8)SCU_LINST_ERRSYN_Msk) );
}

/** \brief reads Break Field Status.
 *
 * \return Break Field Status
 *
 * \brief <b>Example</b><br>
 * \brief This example reads Break Field Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint8 status;
 *
 *    status = LIN_Break_Sts();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE uint8 LIN_Break_Sts(void)
{
  return ( u1_Field_Rd8(&SCU->LINST.reg, (uint8)SCU_LINST_BRK_Pos, (uint8)SCU_LINST_BRK_Msk) );
}

/** \brief enables Baud Rate Detection.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Baud Rate Detection.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     LIN_Break_Detect_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_Break_Detect_En(void)
{
  Field_Mod8(&SCU->LINST.reg, (uint8)SCU_LINST_BRDIS_Pos, (uint8)SCU_LINST_BRDIS_Msk, 0u);
}

/** \brief disables Baud Rate Detection.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Baud Rate Detection.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     LIN_Break_Detect_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_Break_Detect_Dis(void)
{
  Field_Mod8(&SCU->LINST.reg, (uint8)SCU_LINST_BRDIS_Pos, (uint8)SCU_LINST_BRDIS_Msk, 1u);
}

/** \brief selects Baud Rate Detection.
 *
 * \param a BGSEL Value (2 bits)
 *
 * \brief <b>Example</b><br>
 * \brief This example selects the first range of the Baud Rate Detection.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     LIN_BaudRate_Range_Sel(0x00);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_BaudRate_Range_Sel(uint8 a)
{
  Field_Mod8(&SCU->LINST.reg, (uint8)SCU_LINST_BGSEL_Pos, (uint8)SCU_LINST_BGSEL_Msk, a);
}

/** \brief clears LIN Receiver Overcurrent interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the LIN Receiver Overcurrent interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   LIN_Over_Curr_Int_En();
 *   if ((uint8)LIN->CTRL_STS.bit.OC_STS == (uint8)1)
 *   {
 *     LIN_OC_CALLBACK();
 *     LIN_Over_Curr_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_Over_Curr_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->SYS_ISCLR.reg, (uint8)SCUPM_SYS_ISCLR_LIN_OC_ICLR_Pos, (uint8)SCUPM_SYS_ISCLR_LIN_OC_ICLR_Msk, 1u);
}

/** \brief clears LIN Receiver Overtemperature interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the LIN Receiver Overtemperature interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   LIN_Over_Temp_Int_En();
 *   if ((uint8)LIN->CTRL_STS.bit.OT_STS == (uint8)1)
 *   {
 *     LIN_OT_CALLBACK();
 *     LIN_Over_Temp_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_Over_Temp_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->SYS_ISCLR.reg, (uint8)SCUPM_SYS_ISCLR_LIN_OT_ICLR_Pos, (uint8)SCUPM_SYS_ISCLR_LIN_OT_ICLR_Msk, 1u);
}

/** \brief clears LIN TXD time-out interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the LIN TXD time-out interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   LIN_Time_Out_Int_En();
 *   if ((uint8)LIN->CTRL_STS.bit.TXD_TMOUT_STS == (uint8)1)
 *   {
 *     LIN_TMOUT_CALLBACK();
 *     LIN_Time_Out_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_Time_Out_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->SYS_ISCLR.reg, (uint8)SCUPM_SYS_ISCLR_LIN_TMOUT_ICLR_Pos, (uint8)SCUPM_SYS_ISCLR_LIN_TMOUT_ICLR_Msk, 1u);
}

/** \brief clears End of SYN Byte interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the LIN End of SYN Byte interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   LIN_Sync_Int_En();
 *   if (LIN_End_Of_Sync_Sts() == (uint8)1)
 *   {
 *     LIN_EOF_CALLBACK();
 *     LIN_End_Of_Sync_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_End_Of_Sync_Int_Clr(void)
{
  Field_Wrt8(&SCU->LINSCLR.reg, (uint8)SCU_LINSCLR_EOFSYNC_Pos, (uint8)SCU_LINSCLR_EOFSYNC_Msk, 1u);
}

/** \brief clears SYN Byte Error interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example threats the SYN Byte Error interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   LIN_Sync_Int_En();
 *   if (LIN_Err_In_Sync_Sts() == (uint8)1)
 *   {
 *     LIN_ERR_CALLBACK();
 *     LIN_Err_In_Sync_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_Err_In_Sync_Int_Clr(void)
{
  Field_Wrt8(&SCU->LINSCLR.reg, (uint8)SCU_LINSCLR_ERRSYNC_Pos, (uint8)SCU_LINSCLR_ERRSYNC_Msk, 1u);
}

/** \brief clears Break Field flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Break Field flag.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     LIN_Break_Int_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_Break_Int_Clr(void)
{
  Field_Wrt8(&SCU->LINSCLR.reg, (uint8)SCU_LINSCLR_BRKC_Pos, (uint8)SCU_LINSCLR_BRKC_Msk, 1u);
}

/** \brief enables LIN Transceiver Overcurrent interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the LIN Receiver Overcurrent interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   LIN_Over_Curr_Int_En();
 *   if ((uint8)LIN->CTRL_STS.bit.OC_STS == (uint8)1)
 *   {
 *     LIN_OC_CALLBACK();
 *     LIN_Over_Curr_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_Over_Curr_Int_En(void)
{
  Field_Mod32(&SCUPM->SYS_IRQ_CTRL.reg, (uint8)SCUPM_SYS_IRQ_CTRL_LIN_OC_IE_Pos, (uint8)SCUPM_SYS_IRQ_CTRL_LIN_OC_IE_Msk, 1u);
}

/** \brief disables LIN Transceiver Overcurrent interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the LIN Receiver Overcurrent interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   LIN_Over_Curr_Int_En();
 *   if ((uint8)LIN->CTRL_STS.bit.OC_STS == (uint8)1)
 *   {
 *     LIN_OC_CALLBACK();
 *     LIN_Over_Curr_Int_Clr();
 *   }
 *   LIN_Over_Curr_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_Over_Curr_Int_Dis(void)
{
  Field_Mod32(&SCUPM->SYS_IRQ_CTRL.reg, (uint8)SCUPM_SYS_IRQ_CTRL_LIN_OC_IE_Pos, (uint8)SCUPM_SYS_IRQ_CTRL_LIN_OC_IE_Msk, 0u);
}

/** \brief enables LIN Transceiver Overtemperature interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the LIN Receiver Overtemperature interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   LIN_Over_Temp_Int_En();
 *   if ((uint8)LIN->CTRL_STS.bit.OT_STS == (uint8)1)
 *   {
 *     LIN_OT_CALLBACK();
 *     LIN_Over_Temp_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_Over_Temp_Int_En(void)
{
  Field_Mod32(&SCUPM->SYS_IRQ_CTRL.reg, (uint8)SCUPM_SYS_IRQ_CTRL_LIN_OT_IE_Pos, (uint8)SCUPM_SYS_IRQ_CTRL_LIN_OT_IE_Msk, 1u);
}

/** \brief disables LIN Transceiver Overtemperature interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the LIN Receiver Overtemperature interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   LIN_Over_Temp_Int_En();
 *   if ((uint8)LIN->CTRL_STS.bit.OT_STS == (uint8)1)
 *   {
 *     LIN_OT_CALLBACK();
 *     LIN_Over_Temp_Int_Clr();
 *   }
 *   LIN_Over_Temp_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_Over_Temp_Int_Dis(void)
{
  Field_Mod32(&SCUPM->SYS_IRQ_CTRL.reg, (uint8)SCUPM_SYS_IRQ_CTRL_LIN_OT_IE_Pos, (uint8)SCUPM_SYS_IRQ_CTRL_LIN_OT_IE_Msk, 0u);
}

/** \brief enables LIN Transceiver TxD-Timeout interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the LIN TXD time-out interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   LIN_Time_Out_Int_En();
 *   if ((uint8)LIN->CTRL_STS.bit.TXD_TMOUT_STS == (uint8)1)
 *   {
 *     LIN_TMOUT_CALLBACK();
 *     LIN_Time_Out_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_Time_Out_Int_En(void)
{
  Field_Mod32(&SCUPM->SYS_IRQ_CTRL.reg, (uint8)SCUPM_SYS_IRQ_CTRL_LIN_TMOUT_IE_Pos, (uint8)SCUPM_SYS_IRQ_CTRL_LIN_TMOUT_IE_Msk, 1u);
}

/** \brief disables LIN Transceiver TxD-Timeout interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the LIN TXD time-out interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   LIN_Time_Out_Int_En();
 *   if ((uint8)LIN->CTRL_STS.bit.TXD_TMOUT_STS == (uint8)1)
 *   {
 *     LIN_TMOUT_CALLBACK();
 *     LIN_Time_Out_Int_Clr();
 *   }
 *   LIN_Time_Out_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_Time_Out_Int_Dis(void)
{
  Field_Mod32(&SCUPM->SYS_IRQ_CTRL.reg, (uint8)SCUPM_SYS_IRQ_CTRL_LIN_TMOUT_IE_Pos, (uint8)SCUPM_SYS_IRQ_CTRL_LIN_TMOUT_IE_Msk, 0u);
}

/** \brief enables End of SYN Byte and SYN Byte Error interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the LIN End of SYN Byte interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   LIN_Sync_Int_En();
 *   if (LIN_End_Of_Sync_Sts() == (uint8)1)
 *   {
 *     LIN_EOF_CALLBACK();
 *     LIN_End_Of_Sync_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_Sync_Int_En(void)
{
  Field_Mod8(&SCU->LINST.reg, (uint8)SCU_LINST_SYNEN_Pos, (uint8)SCU_LINST_SYNEN_Msk, 1u);
}

/** \brief disables End of SYN Byte and SYN Byte Error interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the LIN End of SYN Byte interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   LIN_Sync_Int_En();
 *   if (LIN_End_Of_Sync_Sts() == (uint8)1)
 *   {
 *     LIN_EOF_CALLBACK();
 *     LIN_End_Of_Sync_Int_Clr();
 *   }
 *   LIN_Sync_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_Sync_Int_Dis(void)
{
  Field_Mod8(&SCU->LINST.reg, (uint8)SCU_LINST_SYNEN_Pos, (uint8)SCU_LINST_SYNEN_Msk, 0u);
}

/*******************************************************************************
**                        Global Function Declarations                        **
*******************************************************************************/
/** \brief Initializes the LIN module.
 *
 * \ingroup lin_api
 */
void LIN_Init(void);

/*******************************************************************************
**                     Global Inline Function Declarations                    **
*******************************************************************************/
INLINE void LIN_Set_Mode(uint8 Mode);
INLINE uint32 LIN_Get_Mode(void);
INLINE void LIN_Set_Slope(uint8 SlopeMode);

/*******************************************************************************
**                     Global Inline Function Definitions                     **
*******************************************************************************/
/** \brief Sets LIN Trx. Mode
 *
 * \param Mode LIN Mode Selection
 *
 * \brief <b>Example</b><br>
 * \brief This example sets LIN Transmitter Sleep Mode as Transceiver power mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     LIN_Set_Mode(0x00);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_Set_Mode(uint8 Mode)
{
  Field_Mod32(&LIN->CTRL_STS.reg, LIN_CTRL_STS_MODE_Pos, LIN_CTRL_STS_MODE_Msk, Mode);
}


/** \brief Gets LIN Trx. Mode
 *
 * \return Lin Trx Mode
 *
 * \brief <b>Example</b><br>
 * \brief This example reads LIN Transmitter Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint32 mode;
 *
 *    mode = LIN_Get_Mode();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE uint32 LIN_Get_Mode(void)
{
  return u32_Field_Rd32(&LIN->CTRL_STS.reg, LIN_CTRL_STS_MODE_FB_Pos, LIN_CTRL_STS_MODE_FB_Msk);
}

/** \brief Sets LIN Trx. Slope Mode
 *
 * \param SlopeMode LIN Trx Slope Mode Selection
 *
 * \brief <b>Example</b><br>
 * \brief This example sets LIN Normal Mode as Transmitter Slope mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     LIN_Set_Slope(0x00);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_Set_Slope(uint8 SlopeMode)
{
  LIN_Set_Mode(LIN_MODE_SLEEP);
  Field_Mod32(&LIN->CTRL_STS.reg, LIN_CTRL_STS_SM_Pos, LIN_CTRL_STS_SM_Msk, SlopeMode);
  LIN_Set_Mode(LIN_MODE_NORMAL);
}

#endif
