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
 * \file     pmu.h
 *
 * \brief    Power Management Unit low level access library
 *
 * \version  V0.2.0
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
** V0.1.2: 2017-07-06, DM:   PMU_VDDEXT_On() function updated to satisfy      **
**                           the EPN for BE-Step                              **
** V0.1.3: 2017-07-20, DM:   PMU_VDDEXT_On() workaround reworked to work      **
**                           for fSYS=40MHz as well                           **
** V0.1.4: 2017-10-10, DM:   MISRA 2012 compliance, the following PC-Lint     **
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
** V0.1.5: 2018-03-20, DM:   PMU_VDDEXT_On() return value handling modified   **
**                           to meet MISRA 2012                               **
** V0.1.6: 2018-07-06, BG:   PMU_Clear_Reset_Status(), PMU_VDDEXT_Off(),      **
**                           PMU_Get_Reset_Status, PMU_VDDEXT_Error_Clear(u8),**
**                           PMU_VDDEXT_Set(uint8) rewritten                  **
** V0.1.7: 2018-10-16, JO:   PMU_VDDEXT_Error_Clear renamed to                **
**                           PMU_VDDEXT_Short_Clr, parameter removed          **
**                           Corrected mask in PMU_Get_Reset_Status and       **
**                           PMU_Set_Reset_Status                             **
**                           Field_Mod8 instead of Field_Wrt8 in              **
**                           PMU_VDDEXT_On BF-step                            **
** V0.1.8: 2018-11-27, JO:   Doxygen update                                   **
**                           Moved revision history from pmu.c to pmu.h       **
** V0.1.9: 2020-04-15, BG:   Updated revision history format                  **
** V0.2.0: 2020-07-21, BG:   EP-439: Formatted .h/.c files                    **
*******************************************************************************/

#ifndef PMU_H
#define PMU_H

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "tle987x.h"
#include "types.h"
#include "sfr_access.h"

/*******************************************************************************
**                          Global Macro Definitions                          **
*******************************************************************************/
/**\brief PMU Reset Status Flag Mask, Power-On Reset Flag*/
#define PMU_RESET_STS_POR      (0x80u)
/**\brief PMU Reset Status Flag Mask, PIN-Reset Flag*/
#define PMU_RESET_STS_PIN      (0x40u)
/**\brief PMU Reset Status Flag Mask, External Watchdog (WDT1) Reset Flag*/
#define PMU_RESET_STS_WDT1     (0x20u)
/**\brief PMU Reset Status Flag Mask, Clock Watchdog (CLKWDT) Reset Flag*/
#define PMU_RESET_STS_ClkWDT   (0x10u)
/**\brief PMU Reset Status Flag Mask, Low Priority Resets*/
#define PMU_RESET_STS_LPR      (0x08u)
/**\brief PMU Reset Status Flag Mask, Flag which indicates a reset caused by Sleep-Exit*/
#define PMU_RESET_STS_SLEEP    (0x04u)
/**\brief PMU Reset Status Flag Mask, Flag which indicates a reset caused by Stop-Exit*/
#define PMU_RESET_STS_WAKE     (0x02u)
/**\brief PMU Reset Status Flag Mask, Flag which indicates a reset caused by a System Fail reported in the corresponding Fail Register*/
#define PMU_RESET_STS_SYS_FAIL (0x01u)

/**\brief PMU VDDEXT Status Flag Mask, VDDEXT Supply works inside its specified range 1*/
#define PMU_VDDEXT_STABLE       (0x80u)
/**\brief PMU VDDEXT Status Flag Mask, VDDEXT Supply works inside its specified range 2*/
#define PMU_VDDEXT_OK           (0x40u)
/**\brief PMU VDDEXT Status Flag Mask, VDDEXT Supply Overload*/
#define PMU_VDDEXT_OVERLOAD     (0x20u)
/**\brief PMU VDDEXT Status Flag Mask, VDDEXT Supply Overvoltage*/
#define PMU_VDDEXT_OVERVOLT     (0x10u)
/**\brief PMU VDDEXT Status Flag Mask, VDDEXT Shorted Output*/
#define PMU_VDDEXT_SHORT        (0x08u)
/**\brief PMU VDDEXT Status Flag Mask, Enabling of VDDEXT Supply status information as interrupt source*/
#define PMU_VDDEXT_IE           (0x04u)
/**\brief PMU VDDEXT Status Flag Mask, VDDEXT Supply for Cyclic Sense Enable*/
#define PMU_VDDEXT_CYC_EN       (0x02u)
/**\brief PMU VDDEXT Status Flag Mask, VDDEXT Supply Enable*/
#define PMU_VDDEXT_ENABLE       (0x01u)

/*******************************************************************************
**                     Global Inline Function Definitions                     **
*******************************************************************************/
/** \brief enables VDDEXT Supply status information as interrupt source (enable Fail Interrupt).
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VDDEXT Supply OverLoad interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PMU_VDDEXT_Int_En();
 *   if ((uint8)PMU->VDDEXT_CTRL.bit.OVERLOAD == (uint8)1)
 *   {
 *     PMU_VDDEXT_OL_CALLBACK();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PMU_VDDEXT_Int_En(void)
{
  Field_Mod8(&PMU->VDDEXT_CTRL.reg, (uint8)PMU_VDDEXT_CTRL_FAIL_EN_Pos, (uint8)PMU_VDDEXT_CTRL_FAIL_EN_Msk, 1u);
}

/** \brief disables VDDEXT Supply status information as interrupt source (disable Fail Interrupt).
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VDDEXT Supply OverLoad interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PMU_VDDEXT_Int_En();
 *   if ((uint8)PMU->VDDEXT_CTRL.bit.OVERLOAD == (uint8)1)
 *   {
 *     PMU_VDDEXT_OL_CALLBACK();
 *   }
 *   PMU_VDDEXT_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PMU_VDDEXT_Int_Dis(void)
{
  Field_Mod8(&PMU->VDDEXT_CTRL.reg, (uint8)PMU_VDDEXT_CTRL_FAIL_EN_Pos, (uint8)PMU_VDDEXT_CTRL_FAIL_EN_Msk, 0u);
}

/** \brief enables VDDC status information as interrupt source.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Overvoltage at VDDC regulator interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PMU_VDDC_Int_En();
 *   if ((uint8)PMU->PMU_SUPPLY_STS.bit.PMU_1V5_OVERVOLT == (uint8)1)
 *   {
 *     PMU_VDDC_OV_CALLBACK();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PMU_VDDC_Int_En(void)
{
  Field_Mod8(&PMU->PMU_SUPPLY_STS.reg, (uint8)PMU_PMU_SUPPLY_STS_PMU_1V5_FAIL_EN_Pos, (uint8)PMU_PMU_SUPPLY_STS_PMU_1V5_FAIL_EN_Msk, 1u);
}

/** \brief disables VDDC status information as interrupt source.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Overvoltage at VDDC regulator interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PMU_VDDC_Int_En();
 *   if ((uint8)PMU->PMU_SUPPLY_STS.bit.PMU_1V5_OVERVOLT == (uint8)1)
 *   {
 *     PMU_VDDC_OV_CALLBACK();
 *   }
 *   PMU_VDDC_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PMU_VDDC_Int_Dis(void)
{
  Field_Mod8(&PMU->PMU_SUPPLY_STS.reg, (uint8)PMU_PMU_SUPPLY_STS_PMU_1V5_FAIL_EN_Pos, (uint8)PMU_PMU_SUPPLY_STS_PMU_1V5_FAIL_EN_Msk, 0u);
}

/** \brief enables VDDP status information as interrupt source.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Overvoltage at VDDP regulator interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PMU_VDDP_Int_En();
 *   if ((uint8)PMU->PMU_SUPPLY_STS.bit.PMU_5V_OVERVOLT == (uint8)1)
 *   {
 *     PMU_VDDP_OV_CALLBACK();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PMU_VDDP_Int_En(void)
{
  Field_Mod8(&PMU->PMU_SUPPLY_STS.reg, (uint8)PMU_PMU_SUPPLY_STS_PMU_5V_FAIL_EN_Pos, (uint8)PMU_PMU_SUPPLY_STS_PMU_5V_FAIL_EN_Msk, 1u);
}

/** \brief disables VDDP status information as interrupt source.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Overvoltage at VDDP regulator interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PMU_VDDP_Int_En();
 *   if ((uint8)PMU->PMU_SUPPLY_STS.bit.PMU_5V_OVERVOLT == (uint8)1)
 *   {
 *     PMU_VDDP_OV_CALLBACK();
 *   }
 *   PMU_VDDP_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PMU_VDDP_Int_Dis(void)
{
  Field_Mod8(&PMU->PMU_SUPPLY_STS.reg, (uint8)PMU_PMU_SUPPLY_STS_PMU_5V_FAIL_EN_Pos, (uint8)PMU_PMU_SUPPLY_STS_PMU_5V_FAIL_EN_Msk, 0u);
}

/*******************************************************************************
**                        Global Function Declarations                        **
*******************************************************************************/
/** \brief Initializes the PMU module.
 *
 * \ingroup pmu_api
 */
void PMU_Init(void);

/** \brief Turns VDDEXT on.
 * \brief Different implementations for BE/BF-Step
 *
 * \retval TRUE VDDEXT was turned on
 * \retval FALSE VDDEXT is off, was not turned on
 *
 * \brief <b>Example</b><br>
 * \brief This example switches VDDEXT on and waits until VDDEXT is in stable condition.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   while (PMU_VDDEXT_On() == false)
 *   {
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
bool PMU_VDDEXT_On(void);

/*******************************************************************************
**                        Inline Function Declarations                        **
*******************************************************************************/
INLINE uint8 PMU_Get_Reset_Status(void);
INLINE void PMU_Clear_Reset_Status(void);
INLINE uint8 PMU_VDDEXT_Off(void);
INLINE void PMU_VDDEXT_Short_Clr(void);
INLINE void PMU_VDDEXT_Set(uint8 FlagMask);

/*******************************************************************************
**                         Inline Function Definitions                        **
*******************************************************************************/
/** \brief Reads out the Reset Status Hard Register (PMU->PMU_RESET_STS1)
 *
 * \return combination of reset status bits
 *
 * \brief <b>Example</b><br>
 * \brief This example checks and clears Reset Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   if (PMU_Get_Reset_Status() != (uint8)0)
 *   {
 *     PMU_Clear_Reset_Status();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE uint8 PMU_Get_Reset_Status(void)
{
  return u8_Field_Rd8(&PMU->PMU_RESET_STS1.reg, 0u, 0xFFu);
}

/** \brief Clears the Reset Status Hard Register (PMU->PMU_RESET_STS1)
 *
 * \brief <b>Example</b><br>
 * \brief This example checks and clears Reset Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   if (PMU_Get_Reset_Status() != (uint8)0)
 *   {
 *     PMU_Clear_Reset_Status();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PMU_Clear_Reset_Status(void)
{
  Field_Wrt8all(&PMU->PMU_RESET_STS1.reg, 0u);
}

/** \brief Switches off (disables) VDDEXT
 * and returns the stable state of VDDEXT (VDDEXT Supply works inside its specified range)
 *
 * \return status of VDDEXT
 *
 * \brief <b>Example</b><br>
 * \brief This example switches VDDEXT off and waits until VDDEXT is in stable condition.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   while (PMU_VDDEXT_Off() == (uint8)0)
 *   {
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE uint8 PMU_VDDEXT_Off(void)
{
  Field_Mod8(&PMU->VDDEXT_CTRL.reg, (uint8)PMU_VDDEXT_CTRL_ENABLE_Pos, (uint8)PMU_VDDEXT_CTRL_ENABLE_Msk, 0u);
  return u1_Field_Rd8(&PMU->VDDEXT_CTRL.reg, (uint8)PMU_VDDEXT_CTRL_STABLE_Pos, (uint8)PMU_VDDEXT_CTRL_STABLE_Msk);
}

/** \brief Clear VDDEXT Short Error Flag
 *
 * \brief <b>Example</b><br>
 * \brief This example clears VDDEXT Supply Shorted Output flag.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PMU_VDDEXT_Short_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PMU_VDDEXT_Short_Clr(void)
{
  Field_Clr8(&PMU->VDDEXT_CTRL.reg, 0x08);
}

/** \brief Set the given bits in the PMU->VDDEXT_CTRL register
 *
 * \param FlagMask VDDEXT Flags Mask
 *
 * \brief <b>Example</b><br>
 * \brief This example enables VVDDEXT Supply status information as interrupt source.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PMU_VDDEXT_Set(PMU_VDDEXT_ENABLE);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PMU_VDDEXT_Set(uint8 FlagMask)
{
  Field_Mod8(&PMU->VDDEXT_CTRL.reg, 0u, (uint8)FlagMask, 0xFFu);
}

#endif
