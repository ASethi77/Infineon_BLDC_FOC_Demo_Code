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
 * \file     mon.h
 *
 * \brief    High Voltage Monitor Input low level access library
 *
 * \version  V0.1.6
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
** V0.1.0: 2014-05-12, DM:   Initial version                                  **
** V0.1.1: 2015-02-10, DM:   Individual header file added                     **
** V0.1.2: 2017-04-20, DM:   Macros for configuration and status added        **
** V0.1.3: 2017-10-10, DM:   MISRA 2012 compliance, the following PC-Lint     **
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
** V0.1.4: 2018-11-27, JO:   Doxygen update                                   **
**                           Moved revision history from mon.c to mon.h       **
** V0.1.5: 2020-04-15, BG:   Updated revision history format                  **
** V0.1.6: 2020-07-21, BG:   EP-439: Formatted .h/.c files                    **
*******************************************************************************/

#ifndef MON_H
#define MON_H

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "tle987x.h"
#include "types.h"
#include "sfr_access.h"

/*******************************************************************************
**                          Global Macro Definitions                          **
*******************************************************************************/
/**\brief MON Status Flag mask, MON LOW STATUS*/
#define MON_STATUS_LOW (0U)
/**\brief MON Status Flag mask, MON HIGH STATUS*/
#define MON_STATUS_HIGH (1U)

/*******************************************************************************
**                     Global Inline Function Definitions                     **
*******************************************************************************/
/** \brief clears MON on rising edge interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON on rising edge interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   if ((uint8)SCU->MODIEN3.bit.MONIE == (uint8)1)
 *   {
 *     MON_Rising_Edge_Int_En();
 *     if ((uint8)SCU->IRCON0.bit.MONR == (uint8)1)
 *     {
 *       MON_RISING_CALLBACK();
 *       MON_Rising_Edge_Int_Clr();
 *     }
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON_Rising_Edge_Int_Clr(void)
{
  Field_Wrt8(&SCU->IRCON0CLR.reg, (uint8)SCU_IRCON0CLR_MONRC_Pos, (uint8)SCU_IRCON0CLR_MONRC_Msk, 1u);
}

/** \brief clears MON on falling edge interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON on falling edge interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   if ((uint8)SCU->MODIEN3.bit.MONIE == (uint8)1)
 *   {
 *     MON_Falling_Edge_Int_En();
 *     if ((uint8)SCU->IRCON0.bit.MONF == (uint8)1)
 *     {
 *       MON_FALLING_CALLBACK();
 *       MON_Falling_Edge_Int_Clr();
 *     }
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON_Falling_Edge_Int_Clr(void)
{
  Field_Wrt8(&SCU->IRCON0CLR.reg, (uint8)SCU_IRCON0CLR_MONFC_Pos, (uint8)SCU_IRCON0CLR_MONFC_Msk, 1u);
}

/** \brief enables MON on rising edge interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON on rising edge interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   if ((uint8)SCU->MODIEN3.bit.MONIE == (uint8)1)
 *   {
 *     MON_Rising_Edge_Int_En();
 *     if ((uint8)SCU->IRCON0.bit.MONR == (uint8)1)
 *     {
 *       MON_RISING_CALLBACK();
 *       MON_Rising_Edge_Int_Clr();
 *     }
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON_Rising_Edge_Int_En(void)
{
  Field_Mod8(&SCU->EXICON0.reg, (uint8)6u, (uint8)0x40u, 1u);
}

/** \brief disables MON on rising edge interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON on rising edge interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   if ((uint8)SCU->MODIEN3.bit.MONIE == (uint8)1)
 *   {
 *     MON_Rising_Edge_Int_En();
 *     if ((uint8)SCU->IRCON0.bit.MONR == (uint8)1)
 *     {
 *       MON_RISING_CALLBACK();
 *       MON_Rising_Edge_Int_Clr();
 *     }
 *     MON_Rising_Edge_Int_Dis();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON_Rising_Edge_Int_Dis(void)
{
  Field_Mod8(&SCU->EXICON0.reg, (uint8)6u, (uint8)0x40u, 0u);
}

/** \brief enables MON on falling edge interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON on falling edge interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   if ((uint8)SCU->MODIEN3.bit.MONIE == (uint8)1)
 *   {
 *     MON_Falling_Edge_Int_En();
 *     if ((uint8)SCU->IRCON0.bit.MONF == (uint8)1)
 *     {
 *       MON_FALLING_CALLBACK();
 *       MON_Falling_Edge_Int_Clr();
 *     }
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON_Falling_Edge_Int_En(void)
{
  Field_Mod8(&SCU->EXICON0.reg, (uint8)7u, (uint8)0x80u, 1u);
}

/** \brief disables MON on falling edge interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON on falling edge interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   if ((uint8)SCU->MODIEN3.bit.MONIE == (uint8)1)
 *   {
 *     MON_Falling_Edge_Int_En();
 *     if ((uint8)SCU->IRCON0.bit.MONF == (uint8)1)
 *     {
 *       MON_FALLING_CALLBACK();
 *       MON_Falling_Edge_Int_Clr();
 *     }
 *     MON_Falling_Edge_Int_Dis();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON_Falling_Edge_Int_Dis(void)
{
  Field_Mod8(&SCU->EXICON0.reg, (uint8)7u, (uint8)0x80u, 0u);
}

/** \brief reads MON Status.
 *
 * \return MON Status
 *
 * \brief <b>Example</b><br>
 * \brief This example reads MON Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 status;
 *
 *     status = MON_Sts();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE uint8 MON_Sts(void)
{
  return ( u1_Field_Rd8(&SCU->MODIEN3.reg, (uint8)SCU_MODIEN3_MONSTS_Pos, (uint8)SCU_MODIEN3_MONSTS_Msk) );
}

/** \brief enables PullUp for MON.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullUp for MON.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON_En();
 *     MON_PullUp_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON_PullUp_En(void)
{
  Field_Mod8(&MON->CNF.reg, (uint8)PMU_MON_CNF_PU_Pos, (uint8)PMU_MON_CNF_PU_Msk, 1u);
}

/** \brief disables PullUp for MON.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullUp for MON.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON_En();
 *     MON_PullUp_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON_PullUp_Dis(void)
{
  Field_Mod8(&MON->CNF.reg, (uint8)PMU_MON_CNF_PU_Pos, (uint8)PMU_MON_CNF_PU_Msk, 0u);
}

/** \brief enables PullDown for MON.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullDown for MON.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON_En();
 *     MON_PullDown_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON_PullDown_En(void)
{
  Field_Mod8(&MON->CNF.reg, (uint8)PMU_MON_CNF_PD_Pos, (uint8)PMU_MON_CNF_PD_Msk, 1u);
}

/** \brief disables PullDown for MON.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullDown for MON.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON_En();
 *     MON_PullDown_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON_PullDown_Dis(void)
{
  Field_Mod8(&MON->CNF.reg, (uint8)PMU_MON_CNF_PD_Pos, (uint8)PMU_MON_CNF_PD_Msk, 0u);
}

/** \brief enables Cycle Sense for MON.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Cycle Sense for MON.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON_En();
 *     MON_CycSense_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON_CycSense_En(void)
{
  Field_Mod8(&MON->CNF.reg, (uint8)PMU_MON_CNF_CYC_Pos, (uint8)PMU_MON_CNF_CYC_Msk, 1u);
}

/** \brief disables Cycle Sense for MON.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Cycle Sense for MON.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON_En();
 *     MON_CycSense_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON_CycSense_Dis(void)
{
  Field_Mod8(&MON->CNF.reg, (uint8)PMU_MON_CNF_CYC_Pos, (uint8)PMU_MON_CNF_CYC_Msk, 0u);
}

/** \brief enables Wake-up on Rising Edge for MON.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Wake-up on Rising Edge for MON.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON_En();
 *     MON_WakeOnRise_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON_WakeOnRise_En(void)
{
  Field_Mod8(&MON->CNF.reg, (uint8)PMU_MON_CNF_RISE_Pos, (uint8)PMU_MON_CNF_RISE_Msk, 1u);
}

/** \brief disables Wake-up on Rising Edge for MON.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Wake-up on Rising Edge for MON.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON_En();
 *     MON_WakeOnRise_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON_WakeOnRise_Dis(void)
{
  Field_Mod8(&MON->CNF.reg, (uint8)PMU_MON_CNF_RISE_Pos, (uint8)PMU_MON_CNF_RISE_Msk, 0u);
}

/** \brief enables Wake-up on Falling Edge for MON.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Wake-up on Falling Edge for MON.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON_En();
 *     MON_WakeOnFall_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON_WakeOnFall_En(void)
{
  Field_Mod8(&MON->CNF.reg, (uint8)PMU_MON_CNF_FALL_Pos, (uint8)PMU_MON_CNF_FALL_Msk, 1u);
}

/** \brief disables Wake-up on Falling Edge for MON.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Wake-up on Falling Edge for MON.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON_En();
 *     MON_WakeOnFall_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON_WakeOnFall_Dis(void)
{
  Field_Mod8(&MON->CNF.reg, (uint8)PMU_MON_CNF_FALL_Pos, (uint8)PMU_MON_CNF_FALL_Msk, 0u);
}

/** \brief enables MON.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Wake-up on Falling Edge for MON.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON_En();
 *     MON_WakeOnFall_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON_En(void)
{
  Field_Mod8(&MON->CNF.reg, (uint8)PMU_MON_CNF_EN_Pos, (uint8)PMU_MON_CNF_EN_Msk, 1u);
}

/** \brief disables MON.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables MON.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON_Dis(void)
{
  Field_Mod8(&MON->CNF.reg, (uint8)PMU_MON_CNF_EN_Pos, (uint8)PMU_MON_CNF_EN_Msk, 0u);
}

/*******************************************************************************
**                        Global Function Declarations                        **
*******************************************************************************/
INLINE uint8 MON_Get_Status(void);

/** \brief Initializes the MON module.
 *
 * \ingroup mon_api
 */
void MON_Init(void);

/** \brief Debounces the MON input and reads the logical input value
 *
 * \param MonActiveState expected active state of the MON input
 *
 * \brief <b>Example</b><br>
 * \brief This example Debounces the MON input to Low Level and reads the logical input value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 status;
 *
 *     MON_En();
 *     status = MON_Debounce(0u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
uint8 MON_Debounce(uint8 MonActiveState);

/*******************************************************************************
**                     Global Inline Function Definitions                     **
*******************************************************************************/
/** \brief Reads out the MON Status
 *
 * \return MON status flag
 *
 * \brief <b>Example</b><br>
 * \brief This example reads MON Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 status;
 *
 *     MON_En();
 *     status = MON_Get_Status();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE uint8 MON_Get_Status(void)
{
  return u1_Field_Rd8(&SCU->MODIEN3.reg, (uint8)SCU_MODIEN3_MONSTS_Pos, (uint8)SCU_MODIEN3_MONSTS_Msk);
}

#endif
