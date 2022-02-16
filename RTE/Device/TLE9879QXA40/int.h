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
 * \file     int.h
 *
 * \brief    Interrupt low level access library
 *
 * \version  V0.2.2
 * \date     21. Jul 2020
 */

/*******************************************************************************
**                             Author(s) Identity                             **
********************************************************************************
** Initials     Name                                                          **
** ---------------------------------------------------------------------------**
** DM           Daniel Mysliwitz                                              **
** AP           Adriano Pereira                                               **
** BG           Blandine Guillot                                              **
** JO           Julia Ott                                                     **
*******************************************************************************/

/*******************************************************************************
**                          Revision Control History                          **
********************************************************************************
** V0.1.0: 2014-05-11, DM:   Initial version                                  **
** V0.1.1: 2015-02-10, DM:   Individual header file added                     **
** V0.1.2: 2015-09-17, DM:   SYS_IRQ_CTRL register init added                 **
** V0.1.3: 2015-11-25, DM:   SCU_DMAIENx added, SCU_DMAIRCx clear added       **
** V0.1.4: 2016-10-10, DM:   Interrupt Enable/Disable macros added            **
**                           CPU->SHPR3 init (SysTick Prio) added             **
** V0.1.5: 2017-10-05, DM:   MISRA 2012 compliance, the following PC-Lint     **
**                           rules are globally deactivated:                  **
**                           - Info 793: ANSI/ISO limit of 6 'significant     **
**                             characters in an external identifier           **
**                           - Info 835: A zero has been given as right       **
**                             argument to operator                           **
**                           - Info 845: The left argument to operator '&'    **
**                             is certain to be 0                             **
** V0.1.6: 2018-03-20, DM:   #define NMI_xxx macros modified to meet MISRA2012**
**                           #define EXINTx_xxx macros modified to meet       **
**                           MISRA2012                                        **
**                           Replaced macros by INLINE functions              **
**                           Replaced register accesses within functions by   **
**                           function calls                                   **
**                           Replaced __STATIC_INLINE by INLINE               **
** V0.1.7: 2018-07-04, AP:   Added functions to enable/disable NVIC nodes     **
** V0.1.8: 2018-11-27, JO:   Doxygen update                                   **
**                           Moved revision history from int.c to int.h       **
** V0.1.9: 2019-04-18, JO:   Corrected NVIC_NodeXYZ_En/Dis functions          **
** V0.2.0: 2019-10-14, JO:   Bridge driver interrupts enabled for CW2         **
** V0.2.1: 2020-04-15, BG:   Updated revision history format                  **
** V0.2.2: 2020-07-21, BG:   EP-439: Formatted .h/.c files                    **
*******************************************************************************/

#ifndef INT_H
#define INT_H

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "tle987x.h"
#include "types.h"
#include "tle_variants.h"
#include "sfr_access.h"

/*******************************************************************************
**                          Global Macro Definitions                          **
*******************************************************************************/
/**\brief NMI Flags selection macro, NMI_WDT */
#define NMI_WDT ((uint8)1u << 0u)
/**\brief NMI Flags selection macro, NMI_PLL */
#define NMI_PLL ((uint8)1u << 1u)
/**\brief NMI Flags selection macro, NMI_NVM */
#define NMI_NVM ((uint8)1u << 2u)
/**\brief NMI Flags selection macro, NMI_OT */
#define NMI_OT  ((uint8)1u << 3u)
/**\brief NMI Flags selection macro, NMI_OWT */
#define NMI_OWT ((uint8)1u << 4u)
/**\brief NMI Flags selection macro, NMI_MAP */
#define NMI_MAP ((uint8)1u << 5u)
/**\brief NMI Flags selection macro, NMI_ECC */
#define NMI_ECC ((uint8)1u << 6u)
/**\brief NMI Flags selection macro, NMI_SUP */
#define NMI_SUP ((uint8)1u << 7u)
/**\brief External Interrupt 0 Rising Edge Bit Position */
#define SCU_EXICON0_EXINT0_RE_Pos (0UL)
/**\brief External Interrupt 0 Rising Edge Bit Mask */
#define SCU_EXICON0_EXINT0_RE_Msk (0x01UL)
/**\brief External Interrupt 0 Falling Edge Bit Position */
#define SCU_EXICON0_EXINT0_FE_Pos (1UL)
/**\brief External Interrupt 0 Falling Edge Bit Mask */
#define SCU_EXICON0_EXINT0_FE_Msk (0x02UL)
/**\brief External Interrupt 1 Rising Edge Bit Position */
#define SCU_EXICON0_EXINT1_RE_Pos (2UL)
/**\brief External Interrupt 1 Rising Edge Bit Mask */
#define SCU_EXICON0_EXINT1_RE_Msk (0x04UL)
/**\brief External Interrupt 1 Falling Edge Bit Position */
#define SCU_EXICON0_EXINT1_FE_Pos (3UL)
/**\brief External Interrupt 1 Falling Edge Bit Mask */
#define SCU_EXICON0_EXINT1_FE_Msk (0x08UL)
/**\brief External Interrupt 2 Rising Edge Bit Position */
#define SCU_EXICON0_EXINT2_RE_Pos (4UL)
/**\brief External Interrupt 2 Rising Edge Bit Mask */
#define SCU_EXICON0_EXINT2_RE_Msk (0x10UL)
/**\brief External Interrupt 2 Falling Edge Bit Position */
#define SCU_EXICON0_EXINT2_FE_Pos (5UL)
/**\brief External Interrupt 2 Falling Edge Bit Mask */
#define SCU_EXICON0_EXINT2_FE_Msk (0x20UL)
/**\brief NMI Status Read Bit Position */
#define SCU_NMISR_Pos (0UL)
/**\brief NMI Status Read Bit Mask */
#define SCU_NMISR_Msk (0xFFUL)
/**\brief NMI Clear Bit Position */
#define SCU_NMICLR_Pos (0UL)
/**\brief NMI Clear Bit Mask */
#define SCU_NMICLR_Msk (0xFFUL)


/*******************************************************************************
**                         Inline Function Definitions                        **
*******************************************************************************/
/** \brief enables Global Interrupt (Pending interrupt requests are not blocked from the core).
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Global Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Global_Int_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Global_Int_En(void)
{
  Field_Wrt8(&SCU->IEN0.reg, (uint8)SCU_IEN0_EA_Pos, (uint8)SCU_IEN0_EA_Msk, 1u);
}

/** \brief disables Global Interrupt (All pending interrupt requests,except NMI, are blocked from the core).
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Global Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Global_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Global_Int_Dis(void)
{
  Field_Wrt8(&SCU->IEN0.reg, (uint8)SCU_IEN0_EA_Pos, (uint8)SCU_IEN0_EA_Msk, 0u);
}

/** \brief enables RAM Double Bit ECC Error Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the RAM Double Bit ECC Error Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_ECC_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIECC == (uint8)1)
 *   {
 *     ECC_RAM_DoubleBit_Int_En();
 *     if ((uint8)SCU->EDCSTAT.bit.RDBE == (uint8)1)
 *     {
 *       SCU_ECC_RAM_DB_CALLBACK();
 *       ECC_RAM_DoubleBit_Int_Clr();
 *     }
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void ECC_RAM_DoubleBit_Int_En(void)
{
  Field_Mod8(&SCU->EDCCON.reg, (uint8)SCU_EDCCON_RIE_Pos, (uint8)SCU_EDCCON_RIE_Msk, 1u);
}

/** \brief disables RAM Double Bit ECC Error Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the RAM Double Bit ECC Error Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_ECC_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIECC == (uint8)1)
 *   {
 *     ECC_RAM_DoubleBit_Int_En();
 *     if ((uint8)SCU->EDCSTAT.bit.RDBE == (uint8)1)
 *     {
 *       SCU_ECC_RAM_DB_CALLBACK();
 *       ECC_RAM_DoubleBit_Int_Clr();
 *     }
 *   }
 *   ECC_RAM_DoubleBit_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void ECC_RAM_DoubleBit_Int_Dis(void)
{
  Field_Mod8(&SCU->EDCCON.reg, (uint8)SCU_EDCCON_RIE_Pos, (uint8)SCU_EDCCON_RIE_Msk, 0u);
}

/** \brief enables NVM Double Bit ECC Error Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the NVM Double Bit ECC Error Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_ECC_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIECC == (uint8)1)
 *   {
 *     ECC_NVM_DoubleBit_Int_En();
 *     if ((uint8)SCU->EDCSTAT.bit.NVMDBE == (uint8)1)
 *     {
 *       SCU_ECC_NVM_DB_CALLBACK();
 *       ECC_NVM_DoubleBit_Int_Clr();
 *     }
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void ECC_NVM_DoubleBit_Int_En(void)
{
  Field_Mod8(&SCU->EDCCON.reg, (uint8)SCU_EDCCON_NVMIE_Pos, (uint8)SCU_EDCCON_NVMIE_Msk, 1u);
}

/** \brief disables NVM Double Bit ECC Error Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the NVM Double Bit ECC Error Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_ECC_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIECC == (uint8)1)
 *   {
 *     ECC_NVM_DoubleBit_Int_En();
 *     if ((uint8)SCU->EDCSTAT.bit.NVMDBE == (uint8)1)
 *     {
 *       SCU_ECC_NVM_DB_CALLBACK();
 *       ECC_NVM_DoubleBit_Int_Clr();
 *     }
 *   }
 *   ECC_NVM_DoubleBit_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void ECC_NVM_DoubleBit_Int_Dis(void)
{
  Field_Mod8(&SCU->EDCCON.reg, (uint8)SCU_EDCCON_NVMIE_Pos, (uint8)SCU_EDCCON_NVMIE_Msk, 0u);
}

/** \brief clears RAM Single Bit Error Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example checks the RAM Single Bit Error Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   if ((uint8)SCU->EDCSTAT.bit.RSBE == (uint8)1)
 *   {
 *     ECC_RAM_SingleBit_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void ECC_RAM_SingleBit_Int_Clr(void)
{
  Field_Wrt8(&SCU->EDCSCLR.reg, (uint8)SCU_EDCSCLR_RSBEC_Pos, (uint8)SCU_EDCSCLR_RSBEC_Msk, 1u);
}

/** \brief clears RAM Double Bit ECC Error Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the RAM Double Bit ECC Error Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ECC_RAM_DoubleBit_Int_En();
 *   if ((uint8)SCU->EDCSTAT.bit.RDBE == (uint8)1)
 *   {
 *     SCU_ECC_RAM_DB_CALLBACK();
 *     ECC_RAM_DoubleBit_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void ECC_RAM_DoubleBit_Int_Clr(void)
{
  Field_Wrt8(&SCU->EDCSCLR.reg, (uint8)SCU_EDCSCLR_RDBEC_Pos, (uint8)SCU_EDCSCLR_RDBEC_Msk, 1u);
}

/** \brief clears NVM Double Bit ECC Error Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the NVM Double Bit ECC Error Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ECC_NVM_DoubleBit_Int_En();
 *   if ((uint8)SCU->EDCSTAT.bit.NVMDBE == (uint8)1)
 *   {
 *     SCU_ECC_NVM_DB_CALLBACK();
 *     ECC_NVM_DoubleBit_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void ECC_NVM_DoubleBit_Int_Clr(void)
{
  Field_Wrt8(&SCU->EDCSCLR.reg, (uint8)SCU_EDCSCLR_NVMDBEC_Pos, (uint8)SCU_EDCSCLR_NVMDBEC_Msk, 1u);
}

/** \brief enables Interrupt on rising edge at EXTINT0.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Interrupt 0x on rising edge.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   EXINT0_Rising_Edge_Int_En();
 *   if ((uint8)SCU->IRCON0.bit.EXINT0R == (uint8)1)
 *   {
 *     EXINT0_RISING_CALLBACK();
 *     EXINT0_Rising_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void EXINT0_Rising_Edge_Int_En(void)
{
  Field_Mod8(&SCU->EXICON0.reg, (uint8)SCU_EXICON0_EXINT0_RE_Pos, (uint8)SCU_EXICON0_EXINT0_RE_Msk, 1u);
}

/** \brief disables Interrupt on rising edge at EXTINT0.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Interrupt 0x on rising edge.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   EXINT0_Rising_Edge_Int_En();
 *   if ((uint8)SCU->IRCON0.bit.EXINT0R == (uint8)1)
 *   {
 *     EXINT0_RISING_CALLBACK();
 *     EXINT0_Rising_Edge_Int_Clr();
 *   }
 *   EXINT0_Rising_Edge_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void EXINT0_Rising_Edge_Int_Dis(void)
{
  Field_Mod8(&SCU->EXICON0.reg, (uint8)SCU_EXICON0_EXINT0_RE_Pos, (uint8)SCU_EXICON0_EXINT0_RE_Msk, 0u);
}

/** \brief enables Interrupt on falling edge at EXTINT0.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Interrupt 0x on falling edge.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   EXINT0_Falling_Edge_Int_En();
 *   if ((uint8)SCU->IRCON0.bit.EXINT0F == (uint8)1)
 *   {
 *     EXINT0_FALLING_CALLBACK();
 *     EXINT0_Falling_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void EXINT0_Falling_Edge_Int_En(void)
{
  Field_Mod8(&SCU->EXICON0.reg, (uint8)SCU_EXICON0_EXINT0_FE_Pos, (uint8)SCU_EXICON0_EXINT0_FE_Msk, 1u);
}

/** \brief disables Interrupt on falling edge at EXTINT0.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Interrupt 0x on falling edge.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   EXINT0_Falling_Edge_Int_En();
 *   if ((uint8)SCU->IRCON0.bit.EXINT0F == (uint8)1)
 *   {
 *     EXINT0_FALLING_CALLBACK();
 *     EXINT0_Falling_Edge_Int_Clr();
 *   }
 *   EXINT0_Falling_Edge_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void EXINT0_Falling_Edge_Int_Dis(void)
{
  Field_Mod8(&SCU->EXICON0.reg, (uint8)SCU_EXICON0_EXINT0_FE_Pos, (uint8)SCU_EXICON0_EXINT0_FE_Msk, 0u);
}

/** \brief enables Interrupt on rising edge at EXTINT1.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Interrupt 1x on rising edge.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   EXINT1_Rising_Edge_Int_En();
 *   if ((uint8)SCU->IRCON0.bit.EXINT1R == (uint8)1)
 *   {
 *     EXINT1_RISING_CALLBACK();
 *     EXINT1_Rising_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void EXINT1_Rising_Edge_Int_En(void)
{
  Field_Mod8(&SCU->EXICON0.reg, (uint8)SCU_EXICON0_EXINT1_RE_Pos, (uint8)SCU_EXICON0_EXINT1_RE_Msk, 1u);
}

/** \brief disables Interrupt on rising edge at EXTINT1.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Interrupt 1x on rising edge.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   EXINT1_Rising_Edge_Int_En();
 *   if ((uint8)SCU->IRCON0.bit.EXINT1R == (uint8)1)
 *   {
 *     EXINT1_RISING_CALLBACK();
 *     EXINT1_Rising_Edge_Int_Clr();
 *   }
 *   EXINT1_Rising_Edge_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void EXINT1_Rising_Edge_Int_Dis(void)
{
  Field_Mod8(&SCU->EXICON0.reg, (uint8)SCU_EXICON0_EXINT1_RE_Pos, (uint8)SCU_EXICON0_EXINT1_RE_Msk, 0u);
}

/** \brief enables Interrupt on falling edge at EXTINT1.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Interrupt 1x on falling edge.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   EXINT1_Falling_Edge_Int_En();
 *   if ((uint8)SCU->IRCON0.bit.EXINT1F == (uint8)1)
 *   {
 *     EXINT1_FALLING_CALLBACK();
 *     EXINT1_Falling_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void EXINT1_Falling_Edge_Int_En(void)
{
  Field_Mod8(&SCU->EXICON0.reg, (uint8)SCU_EXICON0_EXINT1_FE_Pos, (uint8)SCU_EXICON0_EXINT1_FE_Msk, 1u);
}

/** \brief disables Interrupt on falling edge at EXTINT1.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Interrupt 1x on falling edge.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   EXINT1_Falling_Edge_Int_En();
 *   if ((uint8)SCU->IRCON0.bit.EXINT1F == (uint8)1)
 *   {
 *     EXINT1_FALLING_CALLBACK();
 *     EXINT1_Falling_Edge_Int_Clr();
 *   }
 *   EXINT1_Falling_Edge_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void EXINT1_Falling_Edge_Int_Dis(void)
{
  Field_Mod8(&SCU->EXICON0.reg, (uint8)SCU_EXICON0_EXINT1_FE_Pos, (uint8)SCU_EXICON0_EXINT1_FE_Msk, 0u);
}

/** \brief enables Interrupt on rising edge at EXTINT2.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Interrupt 2x on rising edge.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   EXINT2_Rising_Edge_Int_En();
 *   if ((uint8)SCU->IRCON0.bit.EXINT2R == (uint8)1)
 *   {
 *     EXINT2_RISING_CALLBACK();
 *     EXINT2_Rising_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void EXINT2_Rising_Edge_Int_En(void)
{
  Field_Mod8(&SCU->EXICON0.reg, (uint8)SCU_EXICON0_EXINT2_RE_Pos, (uint8)SCU_EXICON0_EXINT2_RE_Msk, 1u);
}

/** \brief disables Interrupt on rising edge at EXTINT2.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Interrupt 2x on rising edge.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   EXINT2_Rising_Edge_Int_En();
 *   if ((uint8)SCU->IRCON0.bit.EXINT2R == (uint8)1)
 *   {
 *     EXINT2_RISING_CALLBACK();
 *     EXINT2_Rising_Edge_Int_Clr();
 *   }
 *   EXINT2_Rising_Edge_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void EXINT2_Rising_Edge_Int_Dis(void)
{
  Field_Mod8(&SCU->EXICON0.reg, (uint8)SCU_EXICON0_EXINT2_RE_Pos, (uint8)SCU_EXICON0_EXINT2_RE_Msk, 0u);
}

/** \brief enables Interrupt on falling edge at EXTINT2.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Interrupt 2x on falling edge.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   EXINT2_Falling_Edge_Int_En();
 *   if ((uint8)SCU->IRCON0.bit.EXINT2F == (uint8)1)
 *   {
 *     EXINT2_FALLING_CALLBACK();
 *     EXINT2_Falling_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void EXINT2_Falling_Edge_Int_En(void)
{
  Field_Mod8(&SCU->EXICON0.reg, (uint8)SCU_EXICON0_EXINT2_FE_Pos, (uint8)SCU_EXICON0_EXINT2_FE_Msk, 1u);
}

/** \brief disables Interrupt on falling edge at EXTINT2.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Interrupt 2x on falling edge.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   EXINT2_Falling_Edge_Int_En();
 *   if ((uint8)SCU->IRCON0.bit.EXINT2F == (uint8)1)
 *   {
 *     EXINT2_FALLING_CALLBACK();
 *     EXINT2_Falling_Edge_Int_Clr();
 *   }
 *   EXINT2_Falling_Edge_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void EXINT2_Falling_Edge_Int_Dis(void)
{
  Field_Mod8(&SCU->EXICON0.reg, (uint8)SCU_EXICON0_EXINT2_FE_Pos, (uint8)SCU_EXICON0_EXINT2_FE_Msk, 0u);
}

/** \brief clear Interrupt status on rising edge at EXTINT0.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Interrupt 0x on rising edge.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   EXINT0_Rising_Edge_Int_En();
 *   if ((uint8)SCU->IRCON0.bit.EXINT0R == (uint8)1)
 *   {
 *     EXINT0_RISING_CALLBACK();
 *     EXINT0_Rising_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void EXINT0_Rising_Edge_Int_Clr(void)
{
  Field_Wrt8(&SCU->IRCON0CLR.reg, (uint8)SCU_IRCON0CLR_EXINT0RC_Pos, (uint8)SCU_IRCON0CLR_EXINT0RC_Msk, 1u);
}

/** \brief clear Interrupt status on falling edge at EXTINT0.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Interrupt 0x on falling edge.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   EXINT0_Falling_Edge_Int_En();
 *   if ((uint8)SCU->IRCON0.bit.EXINT0F == (uint8)1)
 *   {
 *     EXINT0_FALLING_CALLBACK();
 *     EXINT0_Falling_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void EXINT0_Falling_Edge_Int_Clr(void)
{
  Field_Wrt8(&SCU->IRCON0CLR.reg, (uint8)SCU_IRCON0CLR_EXINT0FC_Pos, (uint8)SCU_IRCON0CLR_EXINT0FC_Msk, 1u);
}

/** \brief clear Interrupt status on rising edge at EXTINT1.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Interrupt 1x on rising edge.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   EXINT1_Rising_Edge_Int_En();
 *   if ((uint8)SCU->IRCON0.bit.EXINT1R == (uint8)1)
 *   {
 *     EXINT1_RISING_CALLBACK();
 *     EXINT1_Rising_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void EXINT1_Rising_Edge_Int_Clr(void)
{
  Field_Wrt8(&SCU->IRCON0CLR.reg, (uint8)SCU_IRCON0CLR_EXINT1RC_Pos, (uint8)SCU_IRCON0CLR_EXINT1RC_Msk, 1u);
}

/** \brief clear Interrupt status on falling edge at EXTINT1.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Interrupt 1x on falling edge.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   EXINT1_Falling_Edge_Int_En();
 *   if ((uint8)SCU->IRCON0.bit.EXINT1F == (uint8)1)
 *   {
 *     EXINT1_FALLING_CALLBACK();
 *     EXINT1_Falling_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void EXINT1_Falling_Edge_Int_Clr(void)
{
  Field_Wrt8(&SCU->IRCON0CLR.reg, (uint8)SCU_IRCON0CLR_EXINT1FC_Pos, (uint8)SCU_IRCON0CLR_EXINT1FC_Msk, 1u);
}

/** \brief clear Interrupt status on rising edge at EXTINT2.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Interrupt 2x on rising edge.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   EXINT2_Rising_Edge_Int_En();
 *   if ((uint8)SCU->IRCON0.bit.EXINT2R == (uint8)1)
 *   {
 *     EXINT2_RISING_CALLBACK();
 *     EXINT2_Rising_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void EXINT2_Rising_Edge_Int_Clr(void)
{
  Field_Wrt8(&SCU->IRCON0CLR.reg, (uint8)SCU_IRCON0CLR_EXINT2RC_Pos, (uint8)SCU_IRCON0CLR_EXINT2RC_Msk, 1u);
}

/** \brief clear Interrupt status on falling edge at EXTINT2.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Interrupt 2x on falling edge.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   EXINT2_Falling_Edge_Int_En();
 *   if ((uint8)SCU->IRCON0.bit.EXINT2F == (uint8)1)
 *   {
 *     EXINT2_FALLING_CALLBACK();
 *     EXINT2_Falling_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void EXINT2_Falling_Edge_Int_Clr(void)
{
  Field_Wrt8(&SCU->IRCON0CLR.reg, (uint8)SCU_IRCON0CLR_EXINT2FC_Pos, (uint8)SCU_IRCON0CLR_EXINT2FC_Msk, 1u);
}

/** \brief enables Watchdog Timer NMI.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Watchdog Timer NMI.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_WDT_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIWDT == (uint8)1)
 *   {
 *     SCU_NMI_WDT_CALLBACK();
 *     NMI_WDT_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_WDT_Int_En(void)
{
  Field_Mod8(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMIWDT_Pos, (uint8)SCU_NMICON_NMIWDT_Msk, 1u);
}

/** \brief disables Watchdog Timer NMI.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Watchdog Timer NMI.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_WDT_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIWDT == (uint8)1)
 *   {
 *     SCU_NMI_WDT_CALLBACK();
 *     NMI_WDT_Int_Clr();
 *   }
 *   NMI_WDT_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_WDT_Int_Dis(void)
{
  Field_Mod8(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMIWDT_Pos, (uint8)SCU_NMICON_NMIWDT_Msk, 0u);
}

/** \brief enables PLL Loss of Lock NMI.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the PLL Loss of Lock NMI.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_PLL_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIPLL == (uint8)1)
 *   {
 *     SCU_NMI_PLL_CALLBACK();
 *     NMI_PLL_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_PLL_Int_En(void)
{
  Field_Mod8(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMIPLL_Pos, (uint8)SCU_NMICON_NMIPLL_Msk, 1u);
}

/** \brief disables PLL Loss of Lock NMI.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the PLL Loss of Lock NMI.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_PLL_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIPLL == (uint8)1)
 *   {
 *     SCU_NMI_PLL_CALLBACK();
 *     NMI_PLL_Int_Clr();
 *   }
 *   NMI_PLL_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_PLL_Int_Dis(void)
{
  Field_Mod8(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMIPLL_Pos, (uint8)SCU_NMICON_NMIPLL_Msk, 0u);
}

/** \brief enables NVM Operation Complete NMI.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the NVM Operation Complete NMI.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_NVM_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMINVM == (uint8)1)
 *   {
 *     SCU_NMI_NVM_CALLBACK();
 *     NMI_NVM_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_NVM_Int_En(void)
{
  Field_Mod8(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMINVM_Pos, (uint8)SCU_NMICON_NMINVM_Msk, 1u);
}

/** \brief disables NVM Operation Complete NMI.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the NVM Operation Complete NMI.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_NVM_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMINVM == (uint8)1)
 *   {
 *     SCU_NMI_NVM_CALLBACK();
 *     NMI_NVM_Int_Clr();
 *   }
 *   NMI_NVM_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_NVM_Int_Dis(void)
{
  Field_Mod8(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMINVM_Pos, (uint8)SCU_NMICON_NMINVM_Msk, 0u);
}

/** \brief enables ECC Error NMI.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the RAM Double Bit ECC Error Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_ECC_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIECC == (uint8)1)
 *   {
 *     ECC_RAM_DoubleBit_Int_En();
 *     if ((uint8)SCU->EDCSTAT.bit.RDBE == (uint8)1)
 *     {
 *       SCU_ECC_RAM_DB_CALLBACK();
 *       ECC_RAM_DoubleBit_Int_Clr();
 *     }
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_ECC_Int_En(void)
{
  Field_Mod8(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMIECC_Pos, (uint8)SCU_NMICON_NMIECC_Msk, 1u);
}

/** \brief disables ECC Error NMI.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the RAM Double Bit ECC Error Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_ECC_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIECC == (uint8)1)
 *   {
 *     ECC_RAM_DoubleBit_Int_En();
 *     if ((uint8)SCU->EDCSTAT.bit.RDBE == (uint8)1)
 *     {
 *       SCU_ECC_RAM_DB_CALLBACK();
 *       ECC_RAM_DoubleBit_Int_Clr();
 *     }
 *   }
 *   NMI_ECC_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_ECC_Int_Dis(void)
{
  Field_Mod8(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMIECC_Pos, (uint8)SCU_NMICON_NMIECC_Msk, 0u);
}

/** \brief enables NVM Map Error NMI.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the NVM Map Error NMI.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_MAP_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIMAP == (uint8)1)
 *   {
 *     SCU_NMI_MAP_CALLBACK();
 *     NMI_MAP_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_MAP_Int_En(void)
{
  Field_Mod8(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMIMAP_Pos, (uint8)SCU_NMICON_NMIMAP_Msk, 1u);
}

/** \brief disables NVM Map Error NMI.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the NVM Map Error NMI.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_MAP_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIMAP == (uint8)1)
 *   {
 *     SCU_NMI_MAP_CALLBACK();
 *     NMI_MAP_Int_Clr();
 *   }
 *   NMI_MAP_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_MAP_Int_Dis(void)
{
  Field_Mod8(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMIMAP_Pos, (uint8)SCU_NMICON_NMIMAP_Msk, 0u);
}

/** \brief enables Supply Prewarning NMI.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Supply Prewarning NMI.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_SUP_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMISUP == (uint8)1)
 *   {
 *     NMI_SUP_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_SUP_Int_En(void)
{
  Field_Mod8(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMISUP_Pos, (uint8)SCU_NMICON_NMISUP_Msk, 1u);
}

/** \brief disables Supply Prewarning NMI.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Supply Prewarning NMI.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_SUP_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMISUP == (uint8)1)
 *   {
 *     NMI_SUP_Int_Clr();
 *   }
 *   NMI_SUP_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_SUP_Int_Dis(void)
{
  Field_Mod8(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMISUP_Pos, (uint8)SCU_NMICON_NMISUP_Msk, 0u);
}

/** \brief enables Oscillator Watchdog NMI.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Oscillator Watchdog NMI.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_OWD_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIOWD == (uint8)1)
 *   {
 *     SCU_NMI_OWD_CALLBACK();
 *     NMI_OWD_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_OWD_Int_En(void)
{
  Field_Mod8(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMIOWD_Pos, (uint8)SCU_NMICON_NMIOWD_Msk, 1u);
}

/** \brief disables Oscillator Watchdog NMI.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Oscillator Watchdog NMI.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_OWD_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIOWD == (uint8)1)
 *   {
 *     SCU_NMI_OWD_CALLBACK();
 *     NMI_OWD_Int_Clr();
 *   }
 *   NMI_OWD_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_OWD_Int_Dis(void)
{
  Field_Mod8(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMIOWD_Pos, (uint8)SCU_NMICON_NMIOWD_Msk, 0u);
}

/** \brief enables OT NMI.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the NMI OT.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_OT_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIOT == (uint8)1)
 *   {
 *     NMI_OT_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_OT_Int_En(void)
{
  Field_Mod8(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMIOT_Pos, (uint8)SCU_NMICON_NMIOT_Msk, 1u);
}

/** \brief disables OT NMI.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the NMI OT.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_OT_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIOT == (uint8)1)
 *   {
 *     NMI_OT_Int_Clr();
 *   }
 *   NMI_OT_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_OT_Int_Dis(void)
{
  Field_Mod8(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMIOT_Pos, (uint8)SCU_NMICON_NMIOT_Msk, 0u);
}

/** \brief clears Watchdog Timer NMI Flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Watchdog Timer NMI.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_WDT_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIWDT == (uint8)1)
 *   {
 *     SCU_NMI_WDT_CALLBACK();
 *     NMI_WDT_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_WDT_Int_Clr(void)
{
  Field_Wrt8(&SCU->NMICLR.reg, (uint8)SCU_NMICLR_NMIWDTC_Pos, (uint8)SCU_NMICLR_NMIWDTC_Msk, 1u);
}

/** \brief clears PLL Loss of Lock NMI Flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the PLL Loss of Lock NMI.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_PLL_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIPLL == (uint8)1)
 *   {
 *     SCU_NMI_PLL_CALLBACK();
 *     NMI_PLL_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_PLL_Int_Clr(void)
{
  Field_Wrt8(&SCU->NMICLR.reg, (uint8)SCU_NMICLR_NMIPLLC_Pos, (uint8)SCU_NMICLR_NMIPLLC_Msk, 1u);
}

/** \brief clears NVM Operation Complete NMI flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the NVM Operation Complete NMI.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_NVM_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMINVM == (uint8)1)
 *   {
 *     SCU_NMI_NVM_CALLBACK();
 *     NMI_NVM_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_NVM_Int_Clr(void)
{
  Field_Wrt8(&SCU->NMICLR.reg, (uint8)SCU_NMICLR_NMINVMC_Pos, (uint8)SCU_NMICLR_NMINVMC_Msk, 1u);
}

/** \brief clears NMI OT Flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the NMI OT.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_OT_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIOT == (uint8)1)
 *   {
 *     NMI_OT_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_OT_Int_Clr(void)
{
  Field_Wrt8(&SCU->NMICLR.reg, (uint8)SCU_NMICLR_NMIOTC_Pos, (uint8)SCU_NMICLR_NMIOTC_Msk, 1u);
}

/** \brief clears Oscillator Watchdog NMI Flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Oscillator Watchdog NMI.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_OWD_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIOWD == (uint8)1)
 *   {
 *     SCU_NMI_OWD_CALLBACK();
 *     NMI_OWD_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_OWD_Int_Clr(void)
{
  Field_Wrt8(&SCU->NMICLR.reg, (uint8)SCU_NMICLR_NMIOWDC_Pos, (uint8)SCU_NMICLR_NMIOWDC_Msk, 1u);
}

/** \brief clears NVM Map Error NMI Flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the NVM Map Error NMI.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_MAP_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIMAP == (uint8)1)
 *   {
 *     SCU_NMI_MAP_CALLBACK();
 *     NMI_MAP_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_MAP_Int_Clr(void)
{
  Field_Wrt8(&SCU->NMICLR.reg, (uint8)SCU_NMICLR_NMIMAPC_Pos, (uint8)SCU_NMICLR_NMIMAPC_Msk, 1u);
}

/** \brief clears ECC Error NMI Flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ECC Error NMI.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_ECC_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIECC == (uint8)1)
 *   {
 *     NMI_ECC_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_ECC_Int_Clr(void)
{
  Field_Wrt8(&SCU->NMICLR.reg, (uint8)SCU_NMICLR_NMIECCC_Pos, (uint8)SCU_NMICLR_NMIECCC_Msk, 1u);
}

/** \brief clears Supply Prewarning NMI Flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Supply Prewarning NMI.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_SUP_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMISUP == (uint8)1)
 *   {
 *     NMI_SUP_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_SUP_Int_Clr(void)
{
  Field_Wrt8(&SCU->NMICLR.reg, (uint8)SCU_NMICLR_NMISUPC_Pos, (uint8)SCU_NMICLR_NMISUPC_Msk, 1u);
}

/** \brief Enables the NVIC node 0 (Int_GPT1)
 *
 * \ingroup int_api
 */
INLINE void NVIC_Node0_En(void)
{
  Field_Wrt32(&CPU->NVIC_ISER0.reg, (uint32)CPU_NVIC_ISER0_Int_GPT1_Pos, (uint32)CPU_NVIC_ISER0_Int_GPT1_Msk, 1u);
}

/** \brief Disables the NVIC node 0 (Int_GPT1)
 *
 * \ingroup int_api
 */
INLINE void NVIC_Node0_Dis(void)
{
  Field_Wrt32(&CPU->NVIC_ICER0.reg, (uint32)CPU_NVIC_ICER0_Int_GPT1_Pos, (uint32)CPU_NVIC_ICER0_Int_GPT1_Msk, 1u);
}

/** \brief Enables the NVIC node 1 (Int_GPT2)
 *
 * \ingroup int_api
 */
INLINE void NVIC_Node1_En(void)
{
  Field_Wrt32(&CPU->NVIC_ISER0.reg, (uint32)CPU_NVIC_ISER0_Int_GPT2_Pos, (uint32)CPU_NVIC_ISER0_Int_GPT2_Msk, 1u);
}

/** \brief Disables the NVIC node 1 (Int_GPT2)
 *
 * \ingroup int_api
 */
INLINE void NVIC_Node1_Dis(void)
{
  Field_Wrt32(&CPU->NVIC_ICER0.reg, (uint32)CPU_NVIC_ICER0_Int_GPT2_Pos, (uint32)CPU_NVIC_ICER0_Int_GPT2_Msk, 1u);
}

/** \brief Enables the NVIC node 2 (Int_ADC2)
 *
 * \ingroup int_api
 */
INLINE void NVIC_Node2_En(void)
{
  Field_Wrt32(&CPU->NVIC_ISER0.reg, (uint32)CPU_NVIC_ISER0_Int_ADC2_Pos, (uint32)CPU_NVIC_ISER0_Int_ADC2_Msk, 1u);
}

/** \brief Disables the NVIC node 2 (Int_ADC2)
 *
 * \ingroup int_api
 */
INLINE void NVIC_Node2_Dis(void)
{
  Field_Wrt32(&CPU->NVIC_ICER0.reg, (uint32)CPU_NVIC_ICER0_Int_ADC2_Pos, (uint32)CPU_NVIC_ICER0_Int_ADC2_Msk, 1u);
}

/** \brief Enables the NVIC node 3 (Int_ADC1)
 *
 * \ingroup int_api
 */
INLINE void NVIC_Node3_En(void)
{
  Field_Wrt32(&CPU->NVIC_ISER0.reg, (uint32)CPU_NVIC_ISER0_Int_ADC1_Pos, (uint32)CPU_NVIC_ISER0_Int_ADC1_Msk, 1u);
}

/** \brief Disables the NVIC node 3 (Int_ADC1)
 *
 * \ingroup int_api
 */
INLINE void NVIC_Node3_Dis(void)
{
  Field_Wrt32(&CPU->NVIC_ICER0.reg, (uint32)CPU_NVIC_ICER0_Int_ADC1_Pos, (uint32)CPU_NVIC_ICER0_Int_ADC1_Msk, 1u);
}

/** \brief Enables the NVIC node 4 (Int_CCU6SR0)
 *
 * \ingroup int_api
 */
INLINE void NVIC_Node4_En(void)
{
  Field_Wrt32(&CPU->NVIC_ISER0.reg, (uint32)CPU_NVIC_ISER0_Int_CCU6SR0_Pos, (uint32)CPU_NVIC_ISER0_Int_CCU6SR0_Msk, 1u);
}

/** \brief Disables the NVIC node 4 (Int_CCU6SR0)
 *
 * \ingroup int_api
 */
INLINE void NVIC_Node4_Dis(void)
{
  Field_Wrt32(&CPU->NVIC_ICER0.reg, (uint32)CPU_NVIC_ICER0_Int_CCU6SR0_Pos, (uint32)CPU_NVIC_ICER0_Int_CCU6SR0_Msk, 1u);
}

/** \brief Enables the NVIC node 5 (Int_CCU6SR1)
 *
 * \ingroup int_api
 */
INLINE void NVIC_Node5_En(void)
{
  Field_Wrt32(&CPU->NVIC_ISER0.reg, (uint32)CPU_NVIC_ISER0_Int_CCU6SR1_Pos, (uint32)CPU_NVIC_ISER0_Int_CCU6SR1_Msk, 1u);
}

/** \brief Disables the NVIC node 5 (Int_CCU6SR1)
 *
 * \ingroup int_api
 */
INLINE void NVIC_Node5_Dis(void)
{
  Field_Wrt32(&CPU->NVIC_ICER0.reg, (uint32)CPU_NVIC_ICER0_Int_CCU6SR1_Pos, (uint32)CPU_NVIC_ICER0_Int_CCU6SR1_Msk, 1u);
}

/** \brief Enables the NVIC node 6 (Int_CCU6SR2)
 *
 * \ingroup int_api
 */
INLINE void NVIC_Node6_En(void)
{
  Field_Wrt32(&CPU->NVIC_ISER0.reg, (uint32)CPU_NVIC_ISER0_Int_CCU6SR2_Pos, (uint32)CPU_NVIC_ISER0_Int_CCU6SR2_Msk, 1u);
}

/** \brief Disables the NVIC node 6 (Int_CCU6SR2)
 *
 * \ingroup int_api
 */
INLINE void NVIC_Node6_Dis(void)
{
  Field_Wrt32(&CPU->NVIC_ICER0.reg, (uint32)CPU_NVIC_ICER0_Int_CCU6SR2_Pos, (uint32)CPU_NVIC_ICER0_Int_CCU6SR2_Msk, 1u);
}

/** \brief Enables the NVIC node 7 (Int_CCU6SR3)
 *
 * \ingroup int_api
 */
INLINE void NVIC_Node7_En(void)
{
  Field_Wrt32(&CPU->NVIC_ISER0.reg, (uint32)CPU_NVIC_ISER0_Int_CCU6SR3_Pos, (uint32)CPU_NVIC_ISER0_Int_CCU6SR3_Msk, 1u);
}

/** \brief Disables the NVIC node 7 (Int_CCU6SR3)
 *
 * \ingroup int_api
 */
INLINE void NVIC_Node7_Dis(void)
{
  Field_Wrt32(&CPU->NVIC_ICER0.reg, (uint32)CPU_NVIC_ICER0_Int_CCU6SR3_Pos, (uint32)CPU_NVIC_ICER0_Int_CCU6SR3_Msk, 1u);
}

/** \brief Enables the NVIC node 8 (Int_SSC1)
 *
 * \ingroup int_api
 */
INLINE void NVIC_Node8_En(void)
{
  Field_Wrt32(&CPU->NVIC_ISER0.reg, (uint32)CPU_NVIC_ISER0_Int_SSC1_Pos, (uint32)CPU_NVIC_ISER0_Int_SSC1_Msk, 1u);
}

/** \brief Disables the NVIC node 8 (Int_SSC1)
 *
 * \ingroup int_api
 */
INLINE void NVIC_Node8_Dis(void)
{
  Field_Wrt32(&CPU->NVIC_ICER0.reg, (uint32)CPU_NVIC_ICER0_Int_SSC1_Pos, (uint32)CPU_NVIC_ICER0_Int_SSC1_Msk, 1u);
}

/** \brief Enables the NVIC node 9 (Int_SSC2)
 *
 * \ingroup int_api
 */
INLINE void NVIC_Node9_En(void)
{
  Field_Wrt32(&CPU->NVIC_ISER0.reg, (uint32)CPU_NVIC_ISER0_Int_SSC2_Pos, (uint32)CPU_NVIC_ISER0_Int_SSC2_Msk, 1u);
}

/** \brief Disables the NVIC node 9 (Int_SSC2)
 *
 * \ingroup int_api
 */
INLINE void NVIC_Node9_Dis(void)
{
  Field_Wrt32(&CPU->NVIC_ICER0.reg, (uint32)CPU_NVIC_ICER0_Int_SSC2_Pos, (uint32)CPU_NVIC_ICER0_Int_SSC2_Msk, 1u);
}

/** \brief Enables the NVIC node 10 (Int_UART1)
 *
 * \ingroup int_api
 */
INLINE void NVIC_Node10_En(void)
{
  Field_Wrt32(&CPU->NVIC_ISER0.reg, (uint32)CPU_NVIC_ISER0_Int_UART1_Pos, (uint32)CPU_NVIC_ISER0_Int_UART1_Msk, 1u);
}

/** \brief Disables the NVIC node 10 (Int_UART1)
 *
 * \ingroup int_api
 */
INLINE void NVIC_Node10_Dis(void)
{
  Field_Wrt32(&CPU->NVIC_ICER0.reg, (uint32)CPU_NVIC_ICER0_Int_UART1_Pos, (uint32)CPU_NVIC_ICER0_Int_UART1_Msk, 1u);
}

/** \brief Enables the NVIC node 11 (Int_UART2)
 *
 * \ingroup int_api
 */
INLINE void NVIC_Node11_En(void)
{
  Field_Wrt32(&CPU->NVIC_ISER0.reg, (uint32)CPU_NVIC_ISER0_Int_UART2_Pos, (uint32)CPU_NVIC_ISER0_Int_UART2_Msk, 1u);
}

/** \brief Disables the NVIC node 11 (Int_UART2)
 *
 *
 * \ingroup int_api
 */
INLINE void NVIC_Node11_Dis(void)
{
  Field_Wrt32(&CPU->NVIC_ICER0.reg, (uint32)CPU_NVIC_ICER0_Int_UART2_Pos, (uint32)CPU_NVIC_ICER0_Int_UART2_Msk, 1u);
}

/** \brief Enables the NVIC node 12 (Int_EXINT0)
 *
 *
 * \ingroup int_api
 */
INLINE void NVIC_Node12_En(void)
{
  Field_Wrt32(&CPU->NVIC_ISER0.reg, (uint32)CPU_NVIC_ISER0_Int_EXINT0_Pos, (uint32)CPU_NVIC_ISER0_Int_EXINT0_Msk, 1u);
}

/** \brief Disables the NVIC node 12 (Int_EXINT0)
 *
 * \ingroup int_api
 */
INLINE void NVIC_Node12_Dis(void)
{
  Field_Wrt32(&CPU->NVIC_ICER0.reg, (uint32)CPU_NVIC_ICER0_Int_EXINT0_Pos, (uint32)CPU_NVIC_ICER0_Int_EXINT0_Msk, 1u);
}

/** \brief Enables the NVIC node 13 (Int_EXINT1)
 *
 * \ingroup int_api
 */
INLINE void NVIC_Node13_En(void)
{
  Field_Wrt32(&CPU->NVIC_ISER0.reg, (uint32)CPU_NVIC_ISER0_Int_EXINT1_Pos, (uint32)CPU_NVIC_ISER0_Int_EXINT1_Msk, 1u);
}

/** \brief Disables the NVIC node 13 (Int_EXINT1)
 *
 * \ingroup int_api
 */
INLINE void NVIC_Node13_Dis(void)
{
  Field_Wrt32(&CPU->NVIC_ICER0.reg, (uint32)CPU_NVIC_ICER0_Int_EXINT1_Pos, (uint32)CPU_NVIC_ICER0_Int_EXINT1_Msk, 1u);
}

/** \brief Enables the NVIC node 14 (Int_BDRV)
 *
 * \ingroup int_api
 */
INLINE void NVIC_Node14_En(void)
{
  Field_Wrt32(&CPU->NVIC_ISER0.reg, (uint32)CPU_NVIC_ISER0_Int_BDRV_Pos, (uint32)CPU_NVIC_ISER0_Int_BDRV_Msk, 1u);
}

/** \brief Disables the NVIC node 14 (Int_BDRV)
 *
 * \ingroup int_api
 */
INLINE void NVIC_Node14_Dis(void)
{
  Field_Wrt32(&CPU->NVIC_ICER0.reg, (uint32)CPU_NVIC_ICER0_Int_BDRV_Pos, (uint32)CPU_NVIC_ICER0_Int_BDRV_Msk, 1u);
}

/** \brief Enables the NVIC node 15 (Int_DMA)
 *
 * \ingroup int_api
 */
INLINE void NVIC_Node15_En(void)
{
  Field_Wrt32(&CPU->NVIC_ISER0.reg, (uint32)CPU_NVIC_ISER0_Int_DMA_Pos, (uint32)CPU_NVIC_ISER0_Int_DMA_Msk, 1u);
}

/** \brief Disables the NVIC node 15 (Int_DMA)
 *
 * \ingroup int_api
 */
INLINE void NVIC_Node15_Dis(void)
{
  Field_Wrt32(&CPU->NVIC_ICER0.reg, (uint32)CPU_NVIC_ICER0_Int_DMA_Pos, (uint32)CPU_NVIC_ICER0_Int_DMA_Msk, 1u);
}

#if (UC_SERIES == TLE987)
/** \brief enables Phase U Zero Crossing Comparator High Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Phase U Zero Crossing Comparator High Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BEMF_Phase_U_Hi_Int_En();
 *   if (SCUPM->SYS_IS.bit.PHU_ZCHI_IS == 1u)
 *   {
 *     BEMF_U_HI_CALLBACK();
 *     BEMF_Phase_U_Hi_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void BEMF_Phase_U_Hi_Int_En(void)
{
  Field_Mod32(&SCUPM->SYS_IRQ_CTRL.reg, (uint32)SCUPM_SYS_IRQ_CTRL_PHU_ZCHI_IE_Pos, (uint32)SCUPM_SYS_IRQ_CTRL_PHU_ZCHI_IE_Msk, 1u);
}

/** \brief disables Phase U Zero Crossing Comparator High Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Phase U Zero Crossing Comparator High Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BEMF_Phase_U_Hi_Int_En();
 *   if (SCUPM->SYS_IS.bit.PHU_ZCHI_IS == 1u)
 *   {
 *     BEMF_U_HI_CALLBACK();
 *     BEMF_Phase_U_Hi_Int_Clr();
 *   }
 *   BEMF_Phase_U_Hi_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void BEMF_Phase_U_Hi_Int_Dis(void)
{
  Field_Mod32(&SCUPM->SYS_IRQ_CTRL.reg, (uint32)SCUPM_SYS_IRQ_CTRL_PHU_ZCHI_IE_Pos, (uint32)SCUPM_SYS_IRQ_CTRL_PHU_ZCHI_IE_Msk, 0u);
}

/** \brief enables Phase U Zero Crossing Comparator Low Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Phase U Zero Crossing Comparator Low Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BEMF_Phase_U_Lo_Int_En();
 *   if (SCUPM->SYS_IS.bit.PHU_ZCLOW_IS == 1u)
 *   {
 *     BEMF_U_LO_CALLBACK();
 *     BEMF_Phase_U_Lo_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void BEMF_Phase_U_Lo_Int_En(void)
{
  Field_Mod32(&SCUPM->SYS_IRQ_CTRL.reg, (uint32)SCUPM_SYS_IRQ_CTRL_PHU_ZCLOW_IE_Pos, (uint32)SCUPM_SYS_IRQ_CTRL_PHU_ZCLOW_IE_Msk, 1u);
}

/** \brief disables Phase U Zero Crossing Comparator Low Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Phase U Zero Crossing Comparator Low Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BEMF_Phase_U_Lo_Int_En();
 *   if (SCUPM->SYS_IS.bit.PHU_ZCLOW_IS == 1u)
 *   {
 *     BEMF_U_LO_CALLBACK();
 *     BEMF_Phase_U_Lo_Int_Clr();
 *   }
 *   BEMF_Phase_U_Lo_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void BEMF_Phase_U_Lo_Int_Dis(void)
{
  Field_Mod32(&SCUPM->SYS_IRQ_CTRL.reg, (uint32)SCUPM_SYS_IRQ_CTRL_PHU_ZCLOW_IE_Pos, (uint32)SCUPM_SYS_IRQ_CTRL_PHU_ZCLOW_IE_Msk, 0u);
}

/** \brief enables Phase V Zero Crossing Comparator High Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Phase V Zero Crossing Comparator High Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BEMF_Phase_V_Hi_Int_En();
 *   if (SCUPM->SYS_IS.bit.PHV_ZCHI_IS == 1u)
 *   {
 *     BEMF_V_HI_CALLBACK();
 *     BEMF_Phase_V_Hi_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void BEMF_Phase_V_Hi_Int_En(void)
{
  Field_Mod32(&SCUPM->SYS_IRQ_CTRL.reg, (uint32)SCUPM_SYS_IRQ_CTRL_PHV_ZCHI_IE_Pos, (uint32)SCUPM_SYS_IRQ_CTRL_PHV_ZCHI_IE_Msk, 1u);
}

/** \brief disables Phase V Zero Crossing Comparator High Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Phase V Zero Crossing Comparator High Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BEMF_Phase_V_Hi_Int_En();
 *   if (SCUPM->SYS_IS.bit.PHV_ZCHI_IS == 1u)
 *   {
 *     BEMF_V_HI_CALLBACK();
 *     BEMF_Phase_V_Hi_Int_Clr();
 *   }
 *   BEMF_Phase_V_Hi_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void BEMF_Phase_V_Hi_Int_Dis(void)
{
  Field_Mod32(&SCUPM->SYS_IRQ_CTRL.reg, (uint32)SCUPM_SYS_IRQ_CTRL_PHV_ZCHI_IE_Pos, (uint32)SCUPM_SYS_IRQ_CTRL_PHV_ZCHI_IE_Msk, 0u);
}

/** \brief enables Phase V Zero Crossing Comparator Low Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Phase V Zero Crossing Comparator Low Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BEMF_Phase_V_Lo_Int_En();
 *   if (SCUPM->SYS_IS.bit.PHV_ZCLOW_IS == 1u)
 *   {
 *     BEMF_V_LO_CALLBACK();
 *     BEMF_Phase_V_Lo_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void BEMF_Phase_V_Lo_Int_En(void)
{
  Field_Mod32(&SCUPM->SYS_IRQ_CTRL.reg, (uint32)SCUPM_SYS_IRQ_CTRL_PHV_ZCLOW_IE_Pos, (uint32)SCUPM_SYS_IRQ_CTRL_PHV_ZCLOW_IE_Msk, 1u);
}

/** \brief disables Phase V Zero Crossing Comparator Low Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Phase V Zero Crossing Comparator Low Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BEMF_Phase_V_Lo_Int_En();
 *   if (SCUPM->SYS_IS.bit.PHV_ZCLOW_IS == 1u)
 *   {
 *     BEMF_V_LO_CALLBACK();
 *     BEMF_Phase_V_Lo_Int_Clr();
 *   }
 *   BEMF_Phase_V_Lo_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void BEMF_Phase_V_Lo_Int_Dis(void)
{
  Field_Mod32(&SCUPM->SYS_IRQ_CTRL.reg, (uint32)SCUPM_SYS_IRQ_CTRL_PHV_ZCLOW_IE_Pos, (uint32)SCUPM_SYS_IRQ_CTRL_PHV_ZCLOW_IE_Msk, 0u);
}

/** \brief enables Phase W Zero Crossing Comparator High Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Phase W Zero Crossing Comparator High Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BEMF_Phase_W_Hi_Int_En();
 *   if (SCUPM->SYS_IS.bit.PHW_ZCHI_IS == 1u)
 *   {
 *     BEMF_W_HI_CALLBACK();
 *     BEMF_Phase_W_Hi_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void BEMF_Phase_W_Hi_Int_En(void)
{
  Field_Mod32(&SCUPM->SYS_IRQ_CTRL.reg, (uint32)SCUPM_SYS_IRQ_CTRL_PHW_ZCHI_IE_Pos, (uint32)SCUPM_SYS_IRQ_CTRL_PHW_ZCHI_IE_Msk, 1u);
}

/** \brief disables Phase W Zero Crossing Comparator High Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Phase W Zero Crossing Comparator High Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BEMF_Phase_W_Hi_Int_En();
 *   if (SCUPM->SYS_IS.bit.PHW_ZCHI_IS == 1u)
 *   {
 *     BEMF_W_HI_CALLBACK();
 *     BEMF_Phase_W_Hi_Int_Clr();
 *   }
 *   BEMF_Phase_W_Hi_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void BEMF_Phase_W_Hi_Int_Dis(void)
{
  Field_Mod32(&SCUPM->SYS_IRQ_CTRL.reg, (uint32)SCUPM_SYS_IRQ_CTRL_PHW_ZCHI_IE_Pos, (uint32)SCUPM_SYS_IRQ_CTRL_PHW_ZCHI_IE_Msk, 0u);
}

/** \brief enables Phase W Zero Crossing Comparator Low Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Phase W Zero Crossing Comparator Low Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BEMF_Phase_W_Lo_Int_En();
 *   if (SCUPM->SYS_IS.bit.PHW_ZCLOW_IS == 1u)
 *   {
 *     BEMF_W_LO_CALLBACK();
 *     BEMF_Phase_W_Lo_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void BEMF_Phase_W_Lo_Int_En(void)
{
  Field_Mod32(&SCUPM->SYS_IRQ_CTRL.reg, (uint32)SCUPM_SYS_IRQ_CTRL_PHW_ZCLOW_IE_Pos, (uint32)SCUPM_SYS_IRQ_CTRL_PHW_ZCLOW_IE_Msk, 1u);
}

/** \brief disables Phase W Zero Crossing Comparator Low Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Phase W Zero Crossing Comparator Low Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BEMF_Phase_W_Lo_Int_En();
 *   if (SCUPM->SYS_IS.bit.PHW_ZCLOW_IS == 1u)
 *   {
 *     BEMF_W_LO_CALLBACK();
 *     BEMF_Phase_W_Lo_Int_Clr();
 *   }
 *   BEMF_Phase_W_Lo_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void BEMF_Phase_W_Lo_Int_Dis(void)
{
  Field_Mod32(&SCUPM->SYS_IRQ_CTRL.reg, (uint32)SCUPM_SYS_IRQ_CTRL_PHW_ZCLOW_IE_Pos, (uint32)SCUPM_SYS_IRQ_CTRL_PHW_ZCLOW_IE_Msk, 0u);
}

/** \brief clears Phase U Zero Crossing Comparator High Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Phase U Zero Crossing Comparator High Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BEMF_Phase_U_Hi_Int_En();
 *   if (SCUPM->SYS_IS.bit.PHU_ZCHI_IS == 1u)
 *   {
 *     BEMF_U_HI_CALLBACK();
 *     BEMF_Phase_U_Hi_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void BEMF_Phase_U_Hi_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->SYS_ISCLR.reg, (uint32)SCUPM_SYS_ISCLR_PHU_ZCHI_SCLR_Pos, (uint32)SCUPM_SYS_ISCLR_PHU_ZCHI_SCLR_Msk, 1u);
}

/** \brief clears Phase U Zero Crossing Comparator Low Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Phase U Zero Crossing Comparator Low Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BEMF_Phase_U_Lo_Int_En();
 *   if (SCUPM->SYS_IS.bit.PHU_ZCLOW_IS == 1u)
 *   {
 *     BEMF_U_LO_CALLBACK();
 *     BEMF_Phase_U_Lo_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void BEMF_Phase_U_Lo_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->SYS_ISCLR.reg, (uint32)SCUPM_SYS_ISCLR_PHU_ZCLOW_SCLR_Pos, (uint32)SCUPM_SYS_ISCLR_PHU_ZCLOW_SCLR_Msk, 1u);
}

/** \brief clears Phase V Zero Crossing Comparator High Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Phase V Zero Crossing Comparator High Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BEMF_Phase_V_Hi_Int_En();
 *   if (SCUPM->SYS_IS.bit.PHV_ZCHI_IS == 1u)
 *   {
 *     BEMF_V_HI_CALLBACK();
 *     BEMF_Phase_V_Hi_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void BEMF_Phase_V_Hi_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->SYS_ISCLR.reg, (uint32)SCUPM_SYS_ISCLR_PHV_ZCHI_SCLR_Pos, (uint32)SCUPM_SYS_ISCLR_PHV_ZCHI_SCLR_Msk, 1u);
}

/** \brief clears Phase V Zero Crossing Comparator Low Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Phase V Zero Crossing Comparator Low Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BEMF_Phase_V_Lo_Int_En();
 *   if (SCUPM->SYS_IS.bit.PHV_ZCLOW_IS == 1u)
 *   {
 *     BEMF_V_LO_CALLBACK();
 *     BEMF_Phase_V_Lo_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void BEMF_Phase_V_Lo_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->SYS_ISCLR.reg, (uint32)SCUPM_SYS_ISCLR_PHV_ZCLOW_SCLR_Pos, (uint32)SCUPM_SYS_ISCLR_PHV_ZCLOW_SCLR_Msk, 1u);
}

/** \brief clears Phase W Zero Crossing Comparator High Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Phase W Zero Crossing Comparator High Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BEMF_Phase_W_Hi_Int_En();
 *   if (SCUPM->SYS_IS.bit.PHW_ZCHI_IS == 1u)
 *   {
 *     BEMF_W_HI_CALLBACK();
 *     BEMF_Phase_W_Hi_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void BEMF_Phase_W_Hi_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->SYS_ISCLR.reg, (uint32)SCUPM_SYS_ISCLR_PHW_ZCHI_SCLR_Pos, (uint32)SCUPM_SYS_ISCLR_PHW_ZCHI_SCLR_Msk, 1u);
}

/** \brief clears Phase W Zero Crossing Comparator Low Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Phase W Zero Crossing Comparator Low Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BEMF_Phase_W_Lo_Int_En();
 *   if (SCUPM->SYS_IS.bit.PHW_ZCLOW_IS == 1u)
 *   {
 *     BEMF_W_LO_CALLBACK();
 *     BEMF_Phase_W_Lo_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void BEMF_Phase_W_Lo_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->SYS_ISCLR.reg, (uint32)SCUPM_SYS_ISCLR_PHW_ZCLOW_SCLR_Pos, (uint32)SCUPM_SYS_ISCLR_PHW_ZCLOW_SCLR_Msk, 1u);
}
#endif /* (UC_SERIES = TLE987) */

/*******************************************************************************
**                        Global Function Declarations                        **
*******************************************************************************/
INLINE uint8 INT_Get_NMI_Status(void);
INLINE void INT_Clr_NMI_Status(uint8 Flags);
INLINE void INT_Enable_Global_Int(void);
INLINE void INT_Disable_Global_Int(void);

/** \brief Initializes the Interrupt module.
 *
 * \ingroup int_api
 */
void INT_Init(void);

/*******************************************************************************
**                     Global Inline Function Definitions                     **
*******************************************************************************/
/** \brief Reads out the NMI Status
 *
 * \return NMI status flags
 *
 * \brief <b>Example</b><br>
 * \brief This example Reads out the NMI Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   uint8 val;
 *
 *   val = INT_Get_NMI_Status();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE uint8 INT_Get_NMI_Status(void)
{
  return u8_Field_Rd8(&SCU->NMISR.reg, (uint8)SCU_NMISR_Pos, (uint8)SCU_NMISR_Msk);
}

/** \brief Clears the NMI Status flags
 *
 * \param Flags NMI Status bit mask
 *
 * \brief <b>Example</b><br>
 * \brief This example Clears All the NMI Status flags.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   INT_Clr_NMI_Status(0xFF);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void INT_Clr_NMI_Status(uint8 Flags)
{
  Field_Wrt8(&SCU->NMICLR.reg, (uint8)SCU_NMICLR_Pos, (uint8)SCU_NMICLR_Msk, Flags);
}

/** \brief enables the global interrupt IEN0.EA
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Global Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   INT_Enable_Global_Int();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void INT_Enable_Global_Int(void)
{
  Global_Int_En();
}

/** \brief disables the global interrupt IEN0.EA
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Global Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   INT_Disable_Global_Int();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void INT_Disable_Global_Int(void)
{
  Global_Int_Dis();
}

#endif
