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
 * \file     port.h
 *
 * \brief    Port/GPIO low level access library
 *
 * \version  V0.5.7
 * \date     21. Jul 2020
 *
 * \note This file violates [MISRA Rule 38], [MISRA Rule 45]
 */

/*******************************************************************************
**                             Author(s) Identity                             **
********************************************************************************
** Initials     Name                                                          **
** ---------------------------------------------------------------------------**
** SS           Steffen Storandt                                              **
** DM           Daniel Mysliwitz                                              **
** TA           Thomas Albersinger                                            **
** JO           Julia Ott                                                     **
** BG           Blandine Guillot                                              **
*******************************************************************************/

/*******************************************************************************
**                          Revision Control History                          **
********************************************************************************
** V0.1.0: 2012-11-12, SS:   Initial version                                  **
** V0.2.0: 2012-12-13, SS:   New SFR format                                   **
** V0.3.0: 2013-02-10, DM:   Function Port_ChangePin() enhanced by Port Dir   **
**                           adjustment, ne function added PORT_ChangePinAlt  **
**                           to set the alternative settings for a Port Pin at**
**                           runtime                                          **
** V0.4.0: 2013-10-16, DM:   Port configuration changed into header file      **
**                           with Configuration Wizard                        **
**                           Configuration stored into #defines               **
**                           Port_Init() modified                             **
** V0.5.0: 2014-04-25, TA:   Port_Init(): use #defines from IFX Config Wizard **
** V0.5.1: 2015-02-10, DM:   Individual header file added                     **
** V0.5.2: 2017-02-16, DM:   Port prefix changed to capital letters           **
**                           API extended                                     **
** V0.5.3: 2017-10-10, DM:   MISRA 2012 compliance, the following PC-Lint     **
**                           rules are globally deactivated:                  **
**                           - Info 793: ANSI/ISO limit of 6 'significant     **
**                             characters in an external identifier           **
**                           - Info 835: A zero has been given as right       **
**                             argument to operator                           **
**                           - Info 845: The left argument to operator '&'    **
**                             is certain to be 0                             **
**                           The following MISRA rules are deactivated locally**
**                           - Warning 572: Excessive shift value (precision 0**
**                             shifted right by 1) [MISRA Rule 38]            **
** V0.5.4: 2018-03-20, DM:   Double slashes removed to meet MISRA 2012        **
**                           Replaced macros by INLINE functions              **
**                           Replaced register accesses within functions by   **
**                           function calls                                   **
**                           Replaced __STATIC_INLINE by INLINE               **
** V0.5.5: 2018-11-27, JO:   Doxygen update                                   **
**                           Moved revision history from port.c to port.h,    **
**                           Port_Init() uses new defines at PORT_XML_VERSION **
**                           >= 10303                                         **
**                           Replaced __STATIC_INLINE by INLINE               **
** V0.5.6: 2020-04-15, BG:   Updated revision history format                  **
** V0.5.7: 2020-07-21, BG:   EP-439: Formatted .h/.c files                    **
*******************************************************************************/

#ifndef PORT_H
#define PORT_H

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "tle987x.h"
#include "types.h"
#include "cmsis_misra.h"
#include "sfr_access.h"

/*******************************************************************************
**                          Global Macro Definitions                          **
*******************************************************************************/

/**\brief Port indices, Port P0*/
#define PORT_P0 (0U)
/**\brief Port indices, Port P1*/
#define PORT_P1 (1U)
/**\brief Port indices, Port P2*/
#define PORT_P2 (2U)

/**\brief Port actions, clear*/
#define PORT_ACTION_CLEAR  (0U)
/**\brief Port actions, set*/
#define PORT_ACTION_SET    (1U)
/**\brief Port actions, toggle*/
#define PORT_ACTION_TOGGLE (2U)
/**\brief Port actions, input*/
#define PORT_ACTION_INPUT  (3U)
/**\brief Port actions, output*/
#define PORT_ACTION_OUTPUT (4U)

/*******************************************************************************
**                     Global Inline Function Definitions                     **
*******************************************************************************/
/** \brief sets Port P00 to Output.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P00 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P00_Output_Set();
 *     PORT_P00_Output_High_Set();
 *     PORT_P00_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P00_Output_Set(void)
{
  Field_Mod8(&PORT->P0_DIR.reg, (uint8)PORT_P0_DIR_P0_Pos, (uint8)PORT_P0_DIR_P0_Msk, 1u);
}

/** \brief sets Port P00 to Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P00 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P00_Input_Set();
 *     sts = PORT_P00_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P00_Input_Set(void)
{
  Field_Mod8(&PORT->P0_DIR.reg, (uint8)PORT_P0_DIR_P0_Pos, (uint8)PORT_P0_DIR_P0_Msk, 0u);
}

/** \brief sets Port P01 to Output.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P01 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P01_Output_Set();
 *     PORT_P01_Output_High_Set();
 *     PORT_P01_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P01_Output_Set(void)
{
  Field_Mod8(&PORT->P0_DIR.reg, (uint8)PORT_P0_DIR_P1_Pos, (uint8)PORT_P0_DIR_P1_Msk, 1u);
}

/** \brief sets Port P01 to Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P01 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P01_Input_Set();
 *     sts = PORT_P01_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P01_Input_Set(void)
{
  Field_Mod8(&PORT->P0_DIR.reg, (uint8)PORT_P0_DIR_P1_Pos, (uint8)PORT_P0_DIR_P1_Msk, 0u);
}

/** \brief sets Port P02 to Output.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P02 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P02_Output_Set();
 *     PORT_P02_Output_High_Set();
 *     PORT_P02_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P02_Output_Set(void)
{
  Field_Mod8(&PORT->P0_DIR.reg, (uint8)PORT_P0_DIR_P2_Pos, (uint8)PORT_P0_DIR_P2_Msk, 1u);
}

/** \brief sets Port P02 to Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P02 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P02_Input_Set();
 *     sts = PORT_P02_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P02_Input_Set(void)
{
  Field_Mod8(&PORT->P0_DIR.reg, (uint8)PORT_P0_DIR_P2_Pos, (uint8)PORT_P0_DIR_P2_Msk, 0u);
}

/** \brief sets Port P03 to Output.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P03 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P03_Output_Set();
 *     PORT_P03_Output_High_Set();
 *     PORT_P03_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P03_Output_Set(void)
{
  Field_Mod8(&PORT->P0_DIR.reg, (uint8)PORT_P0_DIR_P3_Pos, (uint8)PORT_P0_DIR_P3_Msk, 1u);
}

/** \brief sets Port P03 to Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P03 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P03_Input_Set();
 *     sts = PORT_P03_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P03_Input_Set(void)
{
  Field_Mod8(&PORT->P0_DIR.reg, (uint8)PORT_P0_DIR_P3_Pos, (uint8)PORT_P0_DIR_P3_Msk, 0u);
}

/** \brief sets Port P04 to Output.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P04 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P04_Output_Set();
 *     PORT_P04_Output_High_Set();
 *     PORT_P04_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P04_Output_Set(void)
{
  Field_Mod8(&PORT->P0_DIR.reg, (uint8)PORT_P0_DIR_P4_Pos, (uint8)PORT_P0_DIR_P4_Msk, 1u);
}

/** \brief sets Port P04 to Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P04 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P04_Input_Set();
 *     sts = PORT_P04_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P04_Input_Set(void)
{
  Field_Mod8(&PORT->P0_DIR.reg, (uint8)PORT_P0_DIR_P4_Pos, (uint8)PORT_P0_DIR_P4_Msk, 0u);
}

/** \brief sets Port P00 to High Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P00 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P00_Output_Set();
 *     PORT_P00_Output_High_Set();
 *     PORT_P00_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P00_Output_High_Set(void)
{
  Field_Mod8(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_P0_Pos, (uint8)PORT_P0_DATA_P0_Msk, 1u);
}

/** \brief sets Port P00 to Low Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P00 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P00_Output_Set();
 *     PORT_P00_Output_Low_Set();
 *     PORT_P00_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P00_Output_Low_Set(void)
{
  Field_Mod8(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_P0_Pos, (uint8)PORT_P0_DATA_P0_Msk, 0u);
}

/** \brief sets Port P00 to Toggle Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P00 as output, Toggle and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P00_Output_Set();
 *     PORT_P00_Output_Toggle_Set();
 *     PORT_P00_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P00_Output_Toggle_Set(void)
{
  Field_Inv8(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_P0_Msk);
}

/** \brief sets Port P01 to High Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P01 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P01_Output_Set();
 *     PORT_P01_Output_High_Set();
 *     PORT_P01_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P01_Output_High_Set(void)
{
  Field_Mod8(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_P1_Pos, (uint8)PORT_P0_DATA_P1_Msk, 1u);
}

/** \brief sets Port P01 to Low Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P01 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P01_Output_Set();
 *     PORT_P01_Output_Low_Set();
 *     PORT_P01_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P01_Output_Low_Set(void)
{
  Field_Mod8(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_P1_Pos, (uint8)PORT_P0_DATA_P1_Msk, 0u);
}

/** \brief sets Port P01 to Toggle Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P01 as output, Toggle and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P01_Output_Set();
 *     PORT_P01_Output_Toggle_Set();
 *     PORT_P01_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P01_Output_Toggle_Set(void)
{
  Field_Inv8(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_P1_Msk);
}

/** \brief sets Port P02 to High Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P02 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P02_Output_Set();
 *     PORT_P02_Output_High_Set();
 *     PORT_P02_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P02_Output_High_Set(void)
{
  Field_Mod8(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_P2_Pos, (uint8)PORT_P0_DATA_P2_Msk, 1u);
}

/** \brief sets Port P02 to Low Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P02 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P02_Output_Set();
 *     PORT_P02_Output_Low_Set();
 *     PORT_P02_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P02_Output_Low_Set(void)
{
  Field_Mod8(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_P2_Pos, (uint8)PORT_P0_DATA_P2_Msk, 0u);
}

/** \brief sets Port P02 to Toggle Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P02 as output, Toggle and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P02_Output_Set();
 *     PORT_P02_Output_Toggle_Set();
 *     PORT_P02_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P02_Output_Toggle_Set(void)
{
  Field_Inv8(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_P2_Msk);
}

/** \brief sets Port P03 to High Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P03 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P03_Output_Set();
 *     PORT_P03_Output_High_Set();
 *     PORT_P03_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P03_Output_High_Set(void)
{
  Field_Mod8(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_P3_Pos, (uint8)PORT_P0_DATA_P3_Msk, 1u);
}

/** \brief sets Port P03 to Low Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P03 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P03_Output_Set();
 *     PORT_P03_Output_Low_Set();
 *     PORT_P03_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P03_Output_Low_Set(void)
{
  Field_Mod8(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_P3_Pos, (uint8)PORT_P0_DATA_P3_Msk, 0u);
}

/** \brief sets Port P03 to Toggle Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P03 as output, Toggle and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P03_Output_Set();
 *     PORT_P03_Output_Toggle_Set();
 *     PORT_P03_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P03_Output_Toggle_Set(void)
{
  Field_Inv8(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_P3_Msk);
}

/** \brief sets Port P04 to High Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P04 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P04_Output_Set();
 *     PORT_P04_Output_High_Set();
 *     PORT_P04_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P04_Output_High_Set(void)
{
  Field_Mod8(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_P4_Pos, (uint8)PORT_P0_DATA_P4_Msk, 1u);
}

/** \brief sets Port P04 to Low Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P04 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P04_Output_Set();
 *     PORT_P04_Output_Low_Set();
 *     PORT_P04_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P04_Output_Low_Set(void)
{
  Field_Mod8(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_P4_Pos, (uint8)PORT_P0_DATA_P4_Msk, 0u);
}

/** \brief sets Port P04 to Toggle Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P04 as output, Toggle and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P04_Output_Set();
 *     PORT_P04_Output_Toggle_Set();
 *     PORT_P04_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P04_Output_Toggle_Set(void)
{
  Field_Inv8(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_P4_Msk);
}

/** \brief reads Port P00 Status.
 *
 * \return P00 Status
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P00 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P00_Input_Set();
 *     sts = PORT_P00_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE uint8 PORT_P00_Get(void)
{
  return ( u8_Field_Rd8(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_P0_Pos, (uint8)PORT_P0_DATA_P0_Msk) );
}

/** \brief reads Port P01 Status.
 *
 * \return P01 Status
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P01 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P01_Input_Set();
 *     sts = PORT_P01_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE uint8 PORT_P01_Get(void)
{
  return ( u8_Field_Rd8(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_P1_Pos, (uint8)PORT_P0_DATA_P1_Msk) );
}

/** \brief reads Port P02 Status.
 *
 * \return P02 Status
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P02 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P02_Input_Set();
 *     sts = PORT_P02_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE uint8 PORT_P02_Get(void)
{
  return ( u8_Field_Rd8(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_P2_Pos, (uint8)PORT_P0_DATA_P2_Msk) );
}

/** \brief reads Port P03 Status.
 *
 * \return P03 Status
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P03 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P03_Input_Set();
 *     sts = PORT_P03_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE uint8 PORT_P03_Get(void)
{
  return ( u8_Field_Rd8(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_P3_Pos, (uint8)PORT_P0_DATA_P3_Msk) );
}

/** \brief reads Port P04 Status.
 *
 * \return P04 Status
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P04 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P04_Input_Set();
 *     sts = PORT_P04_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE uint8 PORT_P04_Get(void)
{
  return ( u8_Field_Rd8(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_P4_Pos, (uint8)PORT_P0_DATA_P4_Msk) );
}

/** \brief enables Output OpenDrain for Port P00.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P00 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P00_Output_Set();
 *     PORT_P00_Output_Low_Set();
 *     PORT_P00_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P00_OpenDrain_En(void)
{
  Field_Mod8(&PORT->P0_OD.reg, (uint8)PORT_P0_OD_P0_Pos, (uint8)PORT_P0_OD_P0_Msk, 1u);
}

/** \brief disables Output OpenDrain for Port P00.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P00 as output, Low and Normal Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P00_Output_Set();
 *     PORT_P00_Output_Low_Set();
 *     PORT_P00_OpenDrain_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P00_OpenDrain_Dis(void)
{
  Field_Mod8(&PORT->P0_OD.reg, (uint8)PORT_P0_OD_P0_Pos, (uint8)PORT_P0_OD_P0_Msk, 0u);
}

/** \brief enables Output OpenDrain for Port P01.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P01 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P01_Output_Set();
 *     PORT_P01_Output_Low_Set();
 *     PORT_P01_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P01_OpenDrain_En(void)
{
  Field_Mod8(&PORT->P0_OD.reg, (uint8)PORT_P0_OD_P1_Pos, (uint8)PORT_P0_OD_P1_Msk, 1u);
}

/** \brief disables Output OpenDrain for Port P01.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P01 as output, Low and Normal Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P01_Output_Set();
 *     PORT_P01_Output_Low_Set();
 *     PORT_P01_OpenDrain_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P01_OpenDrain_Dis(void)
{
  Field_Mod8(&PORT->P0_OD.reg, (uint8)PORT_P0_OD_P1_Pos, (uint8)PORT_P0_OD_P1_Msk, 0u);
}

/** \brief enables Output OpenDrain for Port P02.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P02 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P02_Output_Set();
 *     PORT_P02_Output_Low_Set();
 *     PORT_P02_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P02_OpenDrain_En(void)
{
  Field_Mod8(&PORT->P0_OD.reg, (uint8)PORT_P0_OD_P2_Pos, (uint8)PORT_P0_OD_P2_Msk, 1u);
}

/** \brief disables Output OpenDrain for Port P02.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P02 as output, Low and Normal Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P02_Output_Set();
 *     PORT_P02_Output_Low_Set();
 *     PORT_P02_OpenDrain_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P02_OpenDrain_Dis(void)
{
  Field_Mod8(&PORT->P0_OD.reg, (uint8)PORT_P0_OD_P2_Pos, (uint8)PORT_P0_OD_P2_Msk, 0u);
}

/** \brief enables Output OpenDrain for Port P03.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P03 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P03_Output_Set();
 *     PORT_P03_Output_Low_Set();
 *     PORT_P03_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P03_OpenDrain_En(void)
{
  Field_Mod8(&PORT->P0_OD.reg, (uint8)PORT_P0_OD_P3_Pos, (uint8)PORT_P0_OD_P3_Msk, 1u);
}

/** \brief disables Output OpenDrain for Port P03.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P03 as output, Low and Normal Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P03_Output_Set();
 *     PORT_P03_Output_Low_Set();
 *     PORT_P03_OpenDrain_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P03_OpenDrain_Dis(void)
{
  Field_Mod8(&PORT->P0_OD.reg, (uint8)PORT_P0_OD_P3_Pos, (uint8)PORT_P0_OD_P3_Msk, 0u);
}

/** \brief enables Output OpenDrain for Port P04.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P04 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P04_Output_Set();
 *     PORT_P04_Output_Low_Set();
 *     PORT_P04_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P04_OpenDrain_En(void)
{
  Field_Mod8(&PORT->P0_OD.reg, (uint8)PORT_P0_OD_P4_Pos, (uint8)PORT_P0_OD_P4_Msk, 1u);
}

/** \brief disables Output OpenDrain for Port P04.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P04 as output, Low and Normal Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P04_Output_Set();
 *     PORT_P04_Output_Low_Set();
 *     PORT_P04_OpenDrain_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P04_OpenDrain_Dis(void)
{
  Field_Mod8(&PORT->P0_OD.reg, (uint8)PORT_P0_OD_P4_Pos, (uint8)PORT_P0_OD_P4_Msk, 0u);
}

/** \brief enables PullUpDown for Port P00.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullUpDown for Port P00.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P00_PullUpDown_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P00_PullUpDown_En(void)
{
  Field_Mod8(&PORT->P0_PUDEN.reg, (uint8)PORT_P0_PUDEN_P0_Pos, (uint8)PORT_P0_PUDEN_P0_Msk, 1u);
}

/** \brief disables PullUpDown for Port P00.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullUpDown for Port P00.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P00_PullUpDown_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P00_PullUpDown_Dis(void)
{
  Field_Mod8(&PORT->P0_PUDEN.reg, (uint8)PORT_P0_PUDEN_P0_Pos, (uint8)PORT_P0_PUDEN_P0_Msk, 0u);
}

/** \brief enables PullUpDown for Port P01.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullUpDown for Port P01.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P01_PullUpDown_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P01_PullUpDown_En(void)
{
  Field_Mod8(&PORT->P0_PUDEN.reg, (uint8)PORT_P0_PUDEN_P1_Pos, (uint8)PORT_P0_PUDEN_P1_Msk, 1u);
}

/** \brief disables PullUpDown for Port P01.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullUpDown for Port P01.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P01_PullUpDown_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P01_PullUpDown_Dis(void)
{
  Field_Mod8(&PORT->P0_PUDEN.reg, (uint8)PORT_P0_PUDEN_P1_Pos, (uint8)PORT_P0_PUDEN_P1_Msk, 0u);
}

/** \brief enables PullUpDown for Port P02.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullUpDown for Port P02.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P02_PullUpDown_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P02_PullUpDown_En(void)
{
  Field_Mod8(&PORT->P0_PUDEN.reg, (uint8)PORT_P0_PUDEN_P2_Pos, (uint8)PORT_P0_PUDEN_P2_Msk, 1u);
}

/** \brief disables PullUpDown for Port P02.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullUpDown for Port P02.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P02_PullUpDown_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P02_PullUpDown_Dis(void)
{
  Field_Mod8(&PORT->P0_PUDEN.reg, (uint8)PORT_P0_PUDEN_P2_Pos, (uint8)PORT_P0_PUDEN_P2_Msk, 0u);
}

/** \brief enables PullUpDown for Port P03.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullUpDown for Port P03.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P03_PullUpDown_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P03_PullUpDown_En(void)
{
  Field_Mod8(&PORT->P0_PUDEN.reg, (uint8)PORT_P0_PUDEN_P3_Pos, (uint8)PORT_P0_PUDEN_P3_Msk, 1u);
}

/** \brief disables PullUpDown for Port P03.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullUpDown for Port P03.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P03_PullUpDown_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P03_PullUpDown_Dis(void)
{
  Field_Mod8(&PORT->P0_PUDEN.reg, (uint8)PORT_P0_PUDEN_P3_Pos, (uint8)PORT_P0_PUDEN_P3_Msk, 0u);
}

/** \brief enables PullUpDown for Port P04.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullUpDown for Port P04.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P04_PullUpDown_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P04_PullUpDown_En(void)
{
  Field_Mod8(&PORT->P0_PUDEN.reg, (uint8)PORT_P0_PUDEN_P4_Pos, (uint8)PORT_P0_PUDEN_P4_Msk, 1u);
}

/** \brief disables PullUpDown for Port P04.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullUpDown for Port P04.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P04_PullUpDown_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P04_PullUpDown_Dis(void)
{
  Field_Mod8(&PORT->P0_PUDEN.reg, (uint8)PORT_P0_PUDEN_P4_Pos, (uint8)PORT_P0_PUDEN_P4_Msk, 0u);
}

/** \brief sets PullUp for Port P00.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullUp for Port P00.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P00_PullUpDown_En();
 *     PORT_P00_PullUp_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P00_PullUp_Set(void)
{
  Field_Mod8(&PORT->P0_PUDSEL.reg, (uint8)PORT_P0_PUDSEL_P0_Pos, (uint8)PORT_P0_PUDSEL_P0_Msk, 1u);
}

/** \brief sets PullDown for Port P00.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullDown for Port P00.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P00_PullUpDown_En();
 *     PORT_P00_PullDown_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P00_PullDown_Set(void)
{
  Field_Mod8(&PORT->P0_PUDSEL.reg, (uint8)PORT_P0_PUDSEL_P0_Pos, (uint8)PORT_P0_PUDSEL_P0_Msk, 0u);
}

/** \brief sets PullUp for Port P01.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullUp for Port P01.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P01_PullUpDown_En();
 *     PORT_P01_PullUp_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P01_PullUp_Set(void)
{
  Field_Mod8(&PORT->P0_PUDSEL.reg, (uint8)PORT_P0_PUDSEL_P1_Pos, (uint8)PORT_P0_PUDSEL_P1_Msk, 1u);
}

/** \brief sets PullDown for Port P01.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullDown for Port P01.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P01_PullUpDown_En();
 *     PORT_P01_PullDown_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P01_PullDown_Set(void)
{
  Field_Mod8(&PORT->P0_PUDSEL.reg, (uint8)PORT_P0_PUDSEL_P1_Pos, (uint8)PORT_P0_PUDSEL_P1_Msk, 0u);
}

/** \brief sets PullUp for Port P02.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullUp for Port P02.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P02_PullUpDown_En();
 *     PORT_P02_PullUp_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P02_PullUp_Set(void)
{
  Field_Mod8(&PORT->P0_PUDSEL.reg, (uint8)PORT_P0_PUDSEL_P2_Pos, (uint8)PORT_P0_PUDSEL_P2_Msk, 1u);
}

/** \brief sets PullDown for Port P02.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullDown for Port P02.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P02_PullUpDown_En();
 *     PORT_P02_PullDown_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P02_PullDown_Set(void)
{
  Field_Mod8(&PORT->P0_PUDSEL.reg, (uint8)PORT_P0_PUDSEL_P2_Pos, (uint8)PORT_P0_PUDSEL_P2_Msk, 0u);
}

/** \brief sets PullUp for Port P03.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullUp for Port P03.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P03_PullUpDown_En();
 *     PORT_P03_PullUp_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P03_PullUp_Set(void)
{
  Field_Mod8(&PORT->P0_PUDSEL.reg, (uint8)PORT_P0_PUDSEL_P3_Pos, (uint8)PORT_P0_PUDSEL_P3_Msk, 1u);
}

/** \brief sets PullDown for Port P03.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullDown for Port P03.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P03_PullUpDown_En();
 *     PORT_P03_PullDown_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P03_PullDown_Set(void)
{
  Field_Mod8(&PORT->P0_PUDSEL.reg, (uint8)PORT_P0_PUDSEL_P3_Pos, (uint8)PORT_P0_PUDSEL_P3_Msk, 0u);
}

/** \brief sets PullUp for Port P04.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullUp for Port P04.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P04_PullUpDown_En();
 *     PORT_P04_PullUp_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P04_PullUp_Set(void)
{
  Field_Mod8(&PORT->P0_PUDSEL.reg, (uint8)PORT_P0_PUDSEL_P4_Pos, (uint8)PORT_P0_PUDSEL_P4_Msk, 1u);
}

/** \brief sets PullDown for Port P04.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullDown for Port P04.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P04_PullUpDown_En();
 *     PORT_P04_PullDown_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P04_PullDown_Set(void)
{
  Field_Mod8(&PORT->P0_PUDSEL.reg, (uint8)PORT_P0_PUDSEL_P4_Pos, (uint8)PORT_P0_PUDSEL_P4_Msk, 0u);
}

/** \brief sets Port P10 to Output.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P10 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P10_Output_Set();
 *     PORT_P10_Output_High_Set();
 *     PORT_P10_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P10_Output_Set(void)
{
  Field_Mod8(&PORT->P1_DIR.reg, (uint8)PORT_P1_DIR_P0_Pos, (uint8)PORT_P1_DIR_P0_Msk, 1u);
}

/** \brief sets Port P10 to Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P10 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P10_Input_Set();
 *     sts = PORT_P10_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P10_Input_Set(void)
{
  Field_Mod8(&PORT->P1_DIR.reg, (uint8)PORT_P1_DIR_P0_Pos, (uint8)PORT_P1_DIR_P0_Msk, 0u);
}

/** \brief sets Port P11 to Output.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P11 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P11_Output_Set();
 *     PORT_P11_Output_High_Set();
 *     PORT_P11_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P11_Output_Set(void)
{
  Field_Mod8(&PORT->P1_DIR.reg, (uint8)PORT_P1_DIR_P1_Pos, (uint8)PORT_P1_DIR_P1_Msk, 1u);
}

/** \brief sets Port P11 to Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P11 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P11_Input_Set();
 *     sts = PORT_P11_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P11_Input_Set(void)
{
  Field_Mod8(&PORT->P1_DIR.reg, (uint8)PORT_P1_DIR_P1_Pos, (uint8)PORT_P1_DIR_P1_Msk, 0u);
}

/** \brief sets Port P12 to Output.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P12 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P12_Output_Set();
 *     PORT_P12_Output_High_Set();
 *     PORT_P12_P13_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P12_Output_Set(void)
{
  Field_Mod8(&PORT->P1_DIR.reg, (uint8)PORT_P1_DIR_P2_Pos, (uint8)PORT_P1_DIR_P2_Msk, 1u);
}

/** \brief sets Port P12 to Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P12 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P12_Input_Set();
 *     sts = PORT_P12_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P12_Input_Set(void)
{
  Field_Mod8(&PORT->P1_DIR.reg, (uint8)PORT_P1_DIR_P2_Pos, (uint8)PORT_P1_DIR_P2_Msk, 0u);
}

/** \brief sets Port P13 to Output.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P13 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P13_Output_Set();
 *     PORT_P13_Output_High_Set();
 *     PORT_P12_P13_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P13_Output_Set(void)
{
  Field_Mod8(&PORT->P1_DIR.reg, (uint8)PORT_P1_DIR_P3_Pos, (uint8)PORT_P1_DIR_P3_Msk, 1u);
}

/** \brief sets Port P13 to Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P13 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P13_Input_Set();
 *     sts = PORT_P13_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P13_Input_Set(void)
{
  Field_Mod8(&PORT->P1_DIR.reg, (uint8)PORT_P1_DIR_P3_Pos, (uint8)PORT_P1_DIR_P3_Msk, 0u);
}

/** \brief sets Port P14 to Output.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P14 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P14_Output_Set();
 *     PORT_P14_Output_High_Set();
 *     PORT_P14_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P14_Output_Set(void)
{
  Field_Mod8(&PORT->P1_DIR.reg, (uint8)PORT_P1_DIR_P4_Pos, (uint8)PORT_P1_DIR_P4_Msk, 1u);
}

/** \brief sets Port P14 to Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P14 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P14_Input_Set();
 *     sts = PORT_P14_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P14_Input_Set(void)
{
  Field_Mod8(&PORT->P1_DIR.reg, (uint8)PORT_P1_DIR_P4_Pos, (uint8)PORT_P1_DIR_P4_Msk, 0u);
}

/** \brief sets Port P10 to High Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P10 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P10_Output_Set();
 *     PORT_P10_Output_High_Set();
 *     PORT_P10_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P10_Output_High_Set(void)
{
  Field_Mod8(&PORT->P1_DATA.reg, (uint8)PORT_P1_DATA_P0_Pos, (uint8)PORT_P1_DATA_P0_Msk, 1u);
}

/** \brief sets Port P10 to Low Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P10 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P10_Output_Set();
 *     PORT_P10_Output_Low_Set();
 *     PORT_P10_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P10_Output_Low_Set(void)
{
  Field_Mod8(&PORT->P1_DATA.reg, (uint8)PORT_P1_DATA_P0_Pos, (uint8)PORT_P1_DATA_P0_Msk, 0u);
}

/** \brief sets Port P10 to Toggle Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P10 as output, Toggle and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P10_Output_Set();
 *     PORT_P10_Output_Toggle_Set();
 *     PORT_P10_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P10_Output_Toggle_Set(void)
{
  Field_Inv8(&PORT->P1_DATA.reg, (uint8)PORT_P1_DATA_P0_Msk);
}

/** \brief sets Port P11 to High Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P11 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P11_Output_Set();
 *     PORT_P11_Output_High_Set();
 *     PORT_P11_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P11_Output_High_Set(void)
{
  Field_Mod8(&PORT->P1_DATA.reg, (uint8)PORT_P1_DATA_P1_Pos, (uint8)PORT_P1_DATA_P1_Msk, 1u);
}

/** \brief sets Port P11 to Low Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P11 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P11_Output_Set();
 *     PORT_P11_Output_Low_Set();
 *     PORT_P11_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P11_Output_Low_Set(void)
{
  Field_Mod8(&PORT->P1_DATA.reg, (uint8)PORT_P1_DATA_P1_Pos, (uint8)PORT_P1_DATA_P1_Msk, 0u);
}

/** \brief sets Port P11 to Toggle Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P11 as output, Toggle and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P11_Output_Set();
 *     PORT_P11_Output_Toggle_Set();
 *     PORT_P11_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P11_Output_Toggle_Set(void)
{
  Field_Inv8(&PORT->P1_DATA.reg, (uint8)PORT_P1_DATA_P1_Msk);
}

/** \brief sets Port P12 to High Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P12 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P12_Output_Set();
 *     PORT_P12_Output_High_Set();
 *     PORT_P12_P13_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P12_Output_High_Set(void)
{
  Field_Mod8(&PORT->P1_DATA.reg, (uint8)PORT_P1_DATA_P2_Pos, (uint8)PORT_P1_DATA_P2_Msk, 1u);
}

/** \brief sets Port P12 to Low Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P12 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P12_Output_Set();
 *     PORT_P12_Output_Low_Set();
 *     PORT_P12_P13_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P12_Output_Low_Set(void)
{
  Field_Mod8(&PORT->P1_DATA.reg, (uint8)PORT_P1_DATA_P2_Pos, (uint8)PORT_P1_DATA_P2_Msk, 0u);
}

/** \brief sets Port P12 to Toggle Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P12 as output, Toggle and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P12_Output_Set();
 *     PORT_P12_Output_Toggle_Set();
 *     PORT_P12_P13_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P12_Output_Toggle_Set(void)
{
  Field_Inv8(&PORT->P1_DATA.reg, (uint8)PORT_P1_DATA_P2_Msk);
}

/** \brief sets Port P13 to High Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P13 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P13_Output_Set();
 *     PORT_P13_Output_High_Set();
 *     PORT_P12_P13_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P13_Output_High_Set(void)
{
  Field_Mod8(&PORT->P1_DATA.reg, (uint8)PORT_P1_DATA_P3_Pos, (uint8)PORT_P1_DATA_P3_Msk, 1u);
}

/** \brief sets Port P13 to Low Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P13 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P13_Output_Set();
 *     PORT_P13_Output_Low_Set();
 *     PORT_P12_P13_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P13_Output_Low_Set(void)
{
  Field_Mod8(&PORT->P1_DATA.reg, (uint8)PORT_P1_DATA_P3_Pos, (uint8)PORT_P1_DATA_P3_Msk, 0u);
}

/** \brief sets Port P13 to Toggle Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P13 as output, Toggle and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P13_Output_Set();
 *     PORT_P13_Output_Toggle_Set();
 *     PORT_P12_P13_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P13_Output_Toggle_Set(void)
{
  Field_Inv8(&PORT->P1_DATA.reg, (uint8)PORT_P1_DATA_P3_Msk);
}

/** \brief sets Port P14 to High Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P14 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P14_Output_Set();
 *     PORT_P14_Output_High_Set();
 *     PORT_P14_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P14_Output_High_Set(void)
{
  Field_Mod8(&PORT->P1_DATA.reg, (uint8)PORT_P1_DATA_P4_Pos, (uint8)PORT_P1_DATA_P4_Msk, 1u);
}

/** \brief sets Port P14 to Low Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P14 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P14_Output_Set();
 *     PORT_P14_Output_Low_Set();
 *     PORT_P14_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P14_Output_Low_Set(void)
{
  Field_Mod8(&PORT->P1_DATA.reg, (uint8)PORT_P1_DATA_P4_Pos, (uint8)PORT_P1_DATA_P4_Msk, 0u);
}

/** \brief sets Port P14 to Toggle Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P14 as output, Toggle and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P14_Output_Set();
 *     PORT_P14_Output_Toggle_Set();
 *     PORT_P14_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P14_Output_Toggle_Set(void)
{
  Field_Inv8(&PORT->P1_DATA.reg, (uint8)PORT_P1_DATA_P4_Msk);
}

/** \brief reads Port P10 Status.
 *
 * \return P10 Status
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P10 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P10_Input_Set();
 *     sts = PORT_P10_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE uint8 PORT_P10_Get(void)
{
  return ( u8_Field_Rd8(&PORT->P1_DATA.reg, (uint8)PORT_P1_DATA_P0_Pos, (uint8)PORT_P1_DATA_P0_Msk) );
}

/** \brief reads Port P11 Status.
 *
 * \return P11 Status
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P11 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P11_Input_Set();
 *     sts = PORT_P11_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE uint8 PORT_P11_Get(void)
{
  return ( u8_Field_Rd8(&PORT->P1_DATA.reg, (uint8)PORT_P1_DATA_P1_Pos, (uint8)PORT_P1_DATA_P1_Msk) );
}

/** \brief reads Port P12 Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P12 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P12_Input_Set();
 *     sts = PORT_P12_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE uint8 PORT_P12_Get(void)
{
  return ( u8_Field_Rd8(&PORT->P1_DATA.reg, (uint8)PORT_P1_DATA_P2_Pos, (uint8)PORT_P1_DATA_P2_Msk) );
}

/** \brief reads Port P13 Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P13 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P13_Input_Set();
 *     sts = PORT_P13_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE uint8 PORT_P13_Get(void)
{
  return ( u8_Field_Rd8(&PORT->P1_DATA.reg, (uint8)PORT_P1_DATA_P3_Pos, (uint8)PORT_P1_DATA_P3_Msk) );
}

/** \brief reads Port P14 Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P14 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P14_Input_Set();
 *     sts = PORT_P14_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE uint8 PORT_P14_Get(void)
{
  return ( u8_Field_Rd8(&PORT->P1_DATA.reg, (uint8)PORT_P1_DATA_P4_Pos, (uint8)PORT_P1_DATA_P4_Msk) );
}

/** \brief enables Output OpenDrain for Port P10.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P10 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P10_Output_Set();
 *     PORT_P10_Output_Low_Set();
 *     PORT_P10_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P10_OpenDrain_En(void)
{
  Field_Mod8(&PORT->P1_OD.reg, (uint8)PORT_P1_OD_P0_Pos, (uint8)PORT_P1_OD_P0_Msk, 1u);
}

/** \brief disables Output OpenDrain for Port P10.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P10 as output, Low and Normal Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P10_Output_Set();
 *     PORT_P10_Output_Low_Set();
 *     PORT_P10_OpenDrain_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P10_OpenDrain_Dis(void)
{
  Field_Mod8(&PORT->P1_OD.reg, (uint8)PORT_P1_OD_P0_Pos, (uint8)PORT_P1_OD_P0_Msk, 0u);
}

/** \brief enables Output OpenDrain for Port P11.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P11 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P11_Output_Set();
 *     PORT_P11_Output_Low_Set();
 *     PORT_P11_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P11_OpenDrain_En(void)
{
  Field_Mod8(&PORT->P1_OD.reg, (uint8)PORT_P1_OD_P1_Pos, (uint8)PORT_P1_OD_P1_Msk, 1u);
}

/** \brief disables Output OpenDrain for Port P11.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P11 as output, Low and Normal Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P11_Output_Set();
 *     PORT_P11_Output_Low_Set();
 *     PORT_P11_OpenDrain_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P11_OpenDrain_Dis(void)
{
  Field_Mod8(&PORT->P1_OD.reg, (uint8)PORT_P1_OD_P1_Pos, (uint8)PORT_P1_OD_P1_Msk, 0u);
}

/** \brief enables Output OpenDrain for Port P12/P13.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P12 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P12_Output_Set();
 *     PORT_P12_Output_Low_Set();
 *     PORT_P12_P13_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P12_P13_OpenDrain_En(void)
{
  Field_Mod8(&PORT->P1_OD.reg, (uint8)PORT_P1_OD_P3_P2_Pos, (uint8)PORT_P1_OD_P3_P2_Msk, 1u);
}

/** \brief disables Output OpenDrain for Port P12/P13.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P13 as output, Low and Normal Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P13_Output_Set();
 *     PORT_P13_Output_Low_Set();
 *     PORT_P12_P13_OpenDrain_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P12_P13_OpenDrain_Dis(void)
{
  Field_Mod8(&PORT->P1_OD.reg, (uint8)PORT_P1_OD_P3_P2_Pos, (uint8)PORT_P1_OD_P3_P2_Msk, 0u);
}

/** \brief enables Output OpenDrain for Port P14.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P14 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P14_Output_Set();
 *     PORT_P14_Output_Low_Set();
 *     PORT_P14_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P14_OpenDrain_En(void)
{
  Field_Mod8(&PORT->P1_OD.reg, (uint8)PORT_P1_OD_P4_Pos, (uint8)PORT_P1_OD_P4_Msk, 1u);
}

/** \brief disables Output OpenDrain for Port P14.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P14 as output, Low and Normal Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P14_Output_Set();
 *     PORT_P14_Output_Low_Set();
 *     PORT_P14_OpenDrain_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P14_OpenDrain_Dis(void)
{
  Field_Mod8(&PORT->P1_OD.reg, (uint8)PORT_P1_OD_P4_Pos, (uint8)PORT_P1_OD_P4_Msk, 0u);
}

/** \brief enables PullUpDown for Port P10.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullUpDown for Port P10.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P10_PullUpDown_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P10_PullUpDown_En(void)
{
  Field_Mod8(&PORT->P1_PUDEN.reg, (uint8)PORT_P1_PUDEN_P0_Pos, (uint8)PORT_P1_PUDEN_P0_Msk, 1u);
}

/** \brief disables PullUpDown for Port P10.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullUpDown for Port P10.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P10_PullUpDown_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P10_PullUpDown_Dis(void)
{
  Field_Mod8(&PORT->P1_PUDEN.reg, (uint8)PORT_P1_PUDEN_P0_Pos, (uint8)PORT_P1_PUDEN_P0_Msk, 0u);
}

/** \brief enables PullUpDown for Port P11.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullUpDown for Port P11.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P11_PullUpDown_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P11_PullUpDown_En(void)
{
  Field_Mod8(&PORT->P1_PUDEN.reg, (uint8)PORT_P1_PUDEN_P1_Pos, (uint8)PORT_P1_PUDEN_P1_Msk, 1u);
}

/** \brief disables PullUpDown for Port P11.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullUpDown for Port P11.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P11_PullUpDown_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P11_PullUpDown_Dis(void)
{
  Field_Mod8(&PORT->P1_PUDEN.reg, (uint8)PORT_P1_PUDEN_P1_Pos, (uint8)PORT_P1_PUDEN_P1_Msk, 0u);
}

/** \brief enables PullUpDown for Port P12.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullUpDown for Port P12.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P12_PullUpDown_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P12_PullUpDown_En(void)
{
  Field_Mod8(&PORT->P1_PUDEN.reg, (uint8)PORT_P1_PUDEN_P2_Pos, (uint8)PORT_P1_PUDEN_P2_Msk, 1u);
}

/** \brief disables PullUpDown for Port P12.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullUpDown for Port P12.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P12_PullUpDown_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P12_PullUpDown_Dis(void)
{
  Field_Mod8(&PORT->P1_PUDEN.reg, (uint8)PORT_P1_PUDEN_P2_Pos, (uint8)PORT_P1_PUDEN_P2_Msk, 0u);
}

/** \brief enables PullUpDown for Port P13.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullUpDown for Port P13.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P13_PullUpDown_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P13_PullUpDown_En(void)
{
  Field_Mod8(&PORT->P1_PUDEN.reg, (uint8)PORT_P1_PUDEN_P3_Pos, (uint8)PORT_P1_PUDEN_P3_Msk, 1u);
}

/** \brief disables PullUpDown for Port P13.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullUpDown for Port P13.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P13_PullUpDown_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P13_PullUpDown_Dis(void)
{
  Field_Mod8(&PORT->P1_PUDEN.reg, (uint8)PORT_P1_PUDEN_P3_Pos, (uint8)PORT_P1_PUDEN_P3_Msk, 0u);
}

/** \brief enables PullUpDown for Port P14.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullUpDown for Port P14.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P14_PullUpDown_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P14_PullUpDown_En(void)
{
  Field_Mod8(&PORT->P1_PUDEN.reg, (uint8)PORT_P1_PUDEN_P4_Pos, (uint8)PORT_P1_PUDEN_P4_Msk, 1u);
}

/** \brief disables PullUpDown for Port P14.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullUpDown for Port P14.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P14_PullUpDown_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P14_PullUpDown_Dis(void)
{
  Field_Mod8(&PORT->P1_PUDEN.reg, (uint8)PORT_P1_PUDEN_P4_Pos, (uint8)PORT_P1_PUDEN_P4_Msk, 0u);
}

/** \brief sets PullUp for Port P10.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullUp for Port P10.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P10_PullUpDown_En();
 *     PORT_P10_PullUp_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P10_PullUp_Set(void)
{
  Field_Mod8(&PORT->P1_PUDSEL.reg, (uint8)PORT_P1_PUDSEL_P0_Pos, (uint8)PORT_P1_PUDSEL_P0_Msk, 1u);
}

/** \brief sets PullDown for Port P10.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullDown for Port P10.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P10_PullUpDown_En();
 *     PORT_P10_PullDown_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P10_PullDown_Set(void)
{
  Field_Mod8(&PORT->P1_PUDSEL.reg, (uint8)PORT_P1_PUDSEL_P0_Pos, (uint8)PORT_P1_PUDSEL_P0_Msk, 0u);
}

/** \brief sets PullUp for Port P11.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullUp for Port P11.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P11_PullUpDown_En();
 *     PORT_P11_PullUp_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P11_PullUp_Set(void)
{
  Field_Mod8(&PORT->P1_PUDSEL.reg, (uint8)PORT_P1_PUDSEL_P1_Pos, (uint8)PORT_P1_PUDSEL_P1_Msk, 1u);
}

/** \brief sets PullDown for Port P11.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullDown for Port P11.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P11_PullUpDown_En();
 *     PORT_P11_PullDown_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P11_PullDown_Set(void)
{
  Field_Mod8(&PORT->P1_PUDSEL.reg, (uint8)PORT_P1_PUDSEL_P1_Pos, (uint8)PORT_P1_PUDSEL_P1_Msk, 0u);
}

/** \brief sets PullUp for Port P12.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullUp for Port P12.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P12_PullUpDown_En();
 *     PORT_P12_PullUp_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P12_PullUp_Set(void)
{
  Field_Mod8(&PORT->P1_PUDSEL.reg, (uint8)PORT_P1_PUDSEL_P2_Pos, (uint8)PORT_P1_PUDSEL_P2_Msk, 1u);
}

/** \brief sets PullDown for Port P12.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullDown for Port P12.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P12_PullUpDown_En();
 *     PORT_P12_PullDown_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P12_PullDown_Set(void)
{
  Field_Mod8(&PORT->P1_PUDSEL.reg, (uint8)PORT_P1_PUDSEL_P2_Pos, (uint8)PORT_P1_PUDSEL_P2_Msk, 0u);
}

/** \brief sets PullUp for Port P13.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullUp for Port P13.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P13_PullUpDown_En();
 *     PORT_P13_PullUp_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P13_PullUp_Set(void)
{
  Field_Mod8(&PORT->P1_PUDSEL.reg, (uint8)PORT_P1_PUDSEL_P3_Pos, (uint8)PORT_P1_PUDSEL_P3_Msk, 1u);
}

/** \brief sets PullDown for Port P13.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullDown for Port P13.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P13_PullUpDown_En();
 *     PORT_P13_PullDown_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P13_PullDown_Set(void)
{
  Field_Mod8(&PORT->P1_PUDSEL.reg, (uint8)PORT_P1_PUDSEL_P3_Pos, (uint8)PORT_P1_PUDSEL_P3_Msk, 0u);
}

/** \brief sets PullUp for Port P14.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullUp for Port P14.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P14_PullUpDown_En();
 *     PORT_P14_PullUp_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P14_PullUp_Set(void)
{
  Field_Mod8(&PORT->P1_PUDSEL.reg, (uint8)PORT_P1_PUDSEL_P4_Pos, (uint8)PORT_P1_PUDSEL_P4_Msk, 1u);
}

/** \brief sets PullDown for Port P14.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullDown for Port P14.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P14_PullUpDown_En();
 *     PORT_P14_PullDown_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P14_PullDown_Set(void)
{
  Field_Mod8(&PORT->P1_PUDSEL.reg, (uint8)PORT_P1_PUDSEL_P4_Pos, (uint8)PORT_P1_PUDSEL_P4_Msk, 0u);
}

/** \brief sets Port P20 to Disable.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets P20 to disable.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P20_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P20_Dis(void)
{
  Field_Mod8(&PORT->P2_DIR.reg, (uint8)PORT_P2_DIR_P0_Pos, (uint8)PORT_P2_DIR_P0_Msk, 1u);
}

/** \brief sets Port P20 to Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P20 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P20_Input_Set();
 *     sts = PORT_P20_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P20_Input_Set(void)
{
  Field_Mod8(&PORT->P2_DIR.reg, (uint8)PORT_P2_DIR_P0_Pos, (uint8)PORT_P2_DIR_P0_Msk, 0u);
}

/** \brief sets Port P22 to Disable.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets P22 to disable.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P22_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P22_Dis(void)
{
  Field_Mod8(&PORT->P2_DIR.reg, (uint8)PORT_P2_DIR_P2_Pos, (uint8)PORT_P2_DIR_P2_Msk, 1u);
}

/** \brief sets Port P22 to Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P22 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P22_Input_Set();
 *     sts = PORT_P22_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P22_Input_Set(void)
{
  Field_Mod8(&PORT->P2_DIR.reg, (uint8)PORT_P2_DIR_P2_Pos, (uint8)PORT_P2_DIR_P2_Msk, 0u);
}

/** \brief sets Port P23 to Disable.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets P23 to disable.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P23_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P23_Dis(void)
{
  Field_Mod8(&PORT->P2_DIR.reg, (uint8)PORT_P2_DIR_P3_Pos, (uint8)PORT_P2_DIR_P3_Msk, 1u);
}

/** \brief sets Port P23 to Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P23 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P23_Input_Set();
 *     sts = PORT_P23_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P23_Input_Set(void)
{
  Field_Mod8(&PORT->P2_DIR.reg, (uint8)PORT_P2_DIR_P3_Pos, (uint8)PORT_P2_DIR_P3_Msk, 0u);
}

/** \brief sets Port P24 to Disable.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets P24 to disable.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P24_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P24_Dis(void)
{
  Field_Mod8(&PORT->P2_DIR.reg, (uint8)PORT_P2_DIR_P4_Pos, (uint8)PORT_P2_DIR_P4_Msk, 1u);
}

/** \brief sets Port P24 to Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P24 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P24_Input_Set();
 *     sts = PORT_P24_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P24_Input_Set(void)
{
  Field_Mod8(&PORT->P2_DIR.reg, (uint8)PORT_P2_DIR_P4_Pos, (uint8)PORT_P2_DIR_P4_Msk, 0u);
}

/** \brief sets Port P25 to Disable.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets P25 to disable.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P25_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P25_Dis(void)
{
  Field_Mod8(&PORT->P2_DIR.reg, (uint8)PORT_P2_DIR_P5_Pos, (uint8)PORT_P2_DIR_P5_Msk, 1u);
}

/** \brief sets Port P25 to Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P25 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P25_Input_Set();
 *     sts = PORT_P25_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P25_Input_Set(void)
{
  Field_Mod8(&PORT->P2_DIR.reg, (uint8)PORT_P2_DIR_P5_Pos, (uint8)PORT_P2_DIR_P5_Msk, 0u);
}

/** \brief reads Port P20 Status.
 *
 * \return P20 Status
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P20 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P20_Input_Set();
 *     sts = PORT_P20_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE uint8 PORT_P20_Get(void)
{
  return ( u8_Field_Rd8(&PORT->P2_DATA.reg, (uint8)PORT_P2_DATA_P0_Pos, (uint8)PORT_P2_DATA_P0_Msk) );
}

/** \brief reads Port P22 Status.
 *
 * \return P22 Status
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P22 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P22_Input_Set();
 *     sts = PORT_P22_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE uint8 PORT_P22_Get(void)
{
  return ( u8_Field_Rd8(&PORT->P2_DATA.reg, (uint8)PORT_P2_DATA_P2_Pos, (uint8)PORT_P2_DATA_P2_Msk) );
}

/** \brief reads Port P23 Status.
 *
 * \return P23 Status
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P23 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P23_Input_Set();
 *     sts = PORT_P23_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE uint8 PORT_P23_Get(void)
{
  return ( u8_Field_Rd8(&PORT->P2_DATA.reg, (uint8)PORT_P2_DATA_P3_Pos, (uint8)PORT_P2_DATA_P3_Msk) );
}

/** \brief reads Port P24 Status.
 *
 * \return P24 Status
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P24 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P24_Input_Set();
 *     sts = PORT_P24_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE uint8 PORT_P24_Get(void)
{
  return ( u8_Field_Rd8(&PORT->P2_DATA.reg, (uint8)PORT_P2_DATA_P4_Pos, (uint8)PORT_P2_DATA_P4_Msk) );
}

/** \brief reads Port P25 Status.
 *
 * \return P25 Status
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P25 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P25_Input_Set();
 *     sts = PORT_P25_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE uint8 PORT_P25_Get(void)
{
  return ( u8_Field_Rd8(&PORT->P2_DATA.reg, (uint8)PORT_P2_DATA_P5_Pos, (uint8)PORT_P2_DATA_P5_Msk) );
}

/** \brief enables PullUpDown for Port P20.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullUpDown for Port P20.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P20_PullUpDown_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P20_PullUpDown_En(void)
{
  Field_Mod8(&PORT->P2_PUDEN.reg, (uint8)PORT_P2_PUDEN_P0_Pos, (uint8)PORT_P2_PUDEN_P0_Msk, 1u);
}

/** \brief disables PullUpDown for Port P20.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullUpDown for Port P20.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P20_PullUpDown_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P20_PullUpDown_Dis(void)
{
  Field_Mod8(&PORT->P2_PUDEN.reg, (uint8)PORT_P2_PUDEN_P0_Pos, (uint8)PORT_P2_PUDEN_P0_Msk, 0u);
}

/** \brief enables PullUpDown for Port P22.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullUpDown for Port P22.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P22_PullUpDown_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P22_PullUpDown_En(void)
{
  Field_Mod8(&PORT->P2_PUDEN.reg, (uint8)PORT_P2_PUDEN_P2_Pos, (uint8)PORT_P2_PUDEN_P2_Msk, 1u);
}

/** \brief disables PullUpDown for Port P22.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullUpDown for Port P22.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P22_PullUpDown_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P22_PullUpDown_Dis(void)
{
  Field_Mod8(&PORT->P2_PUDEN.reg, (uint8)PORT_P2_PUDEN_P2_Pos, (uint8)PORT_P2_PUDEN_P2_Msk, 0u);
}

/** \brief enables PullUpDown for Port P23.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullUpDown for Port P23.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P23_PullUpDown_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P23_PullUpDown_En(void)
{
  Field_Mod8(&PORT->P2_PUDEN.reg, (uint8)PORT_P2_PUDEN_P3_Pos, (uint8)PORT_P2_PUDEN_P3_Msk, 1u);
}

/** \brief disables PullUpDown for Port P23.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullUpDown for Port P23.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P23_PullUpDown_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P23_PullUpDown_Dis(void)
{
  Field_Mod8(&PORT->P2_PUDEN.reg, (uint8)PORT_P2_PUDEN_P3_Pos, (uint8)PORT_P2_PUDEN_P3_Msk, 0u);
}

/** \brief enables PullUpDown for Port P24.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullUpDown for Port P24.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P24_PullUpDown_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P24_PullUpDown_En(void)
{
  Field_Mod8(&PORT->P2_PUDEN.reg, (uint8)PORT_P2_PUDEN_P4_Pos, (uint8)PORT_P2_PUDEN_P4_Msk, 1u);
}

/** \brief disables PullUpDown for Port P24.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullUpDown for Port P24.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P24_PullUpDown_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P24_PullUpDown_Dis(void)
{
  Field_Mod8(&PORT->P2_PUDEN.reg, (uint8)PORT_P2_PUDEN_P4_Pos, (uint8)PORT_P2_PUDEN_P4_Msk, 0u);
}

/** \brief enables PullUpDown for Port P25.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullUpDown for Port P25.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P25_PullUpDown_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P25_PullUpDown_En(void)
{
  Field_Mod8(&PORT->P2_PUDEN.reg, (uint8)PORT_P2_PUDEN_P5_Pos, (uint8)PORT_P2_PUDEN_P5_Msk, 1u);
}

/** \brief disables PullUpDown for Port P25.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullUpDown for Port P25.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P25_PullUpDown_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P25_PullUpDown_Dis(void)
{
  Field_Mod8(&PORT->P2_PUDEN.reg, (uint8)PORT_P2_PUDEN_P5_Pos, (uint8)PORT_P2_PUDEN_P5_Msk, 0u);
}

/** \brief sets PullUp for Port P20.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullUp for Port P20.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P20_PullUpDown_En();
 *     PORT_P20_PullUp_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P20_PullUp_Set(void)
{
  Field_Mod8(&PORT->P2_PUDSEL.reg, (uint8)PORT_P2_PUDSEL_P0_Pos, (uint8)PORT_P2_PUDSEL_P0_Msk, 1u);
}

/** \brief sets PullDown for Port P20.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullDown for Port P20.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P20_PullUpDown_En();
 *     PORT_P20_PullDown_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P20_PullDown_Set(void)
{
  Field_Mod8(&PORT->P2_PUDSEL.reg, (uint8)PORT_P2_PUDSEL_P0_Pos, (uint8)PORT_P2_PUDSEL_P0_Msk, 0u);
}

/** \brief sets PullUp for Port P22.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullUp for Port P22.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P22_PullUpDown_En();
 *     PORT_P22_PullUp_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P22_PullUp_Set(void)
{
  Field_Mod8(&PORT->P2_PUDSEL.reg, (uint8)PORT_P2_PUDSEL_P2_Pos, (uint8)PORT_P2_PUDSEL_P2_Msk, 1u);
}

/** \brief sets PullDown for Port P22.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullDown for Port P22.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P22_PullUpDown_En();
 *     PORT_P22_PullDown_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P22_PullDown_Set(void)
{
  Field_Mod8(&PORT->P2_PUDSEL.reg, (uint8)PORT_P2_PUDSEL_P2_Pos, (uint8)PORT_P2_PUDSEL_P2_Msk, 0u);
}

/** \brief sets PullUp for Port P23.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullUp for Port P23.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P23_PullUpDown_En();
 *     PORT_P23_PullUp_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P23_PullUp_Set(void)
{
  Field_Mod8(&PORT->P2_PUDSEL.reg, (uint8)PORT_P2_PUDSEL_P3_Pos, (uint8)PORT_P2_PUDSEL_P3_Msk, 1u);
}

/** \brief sets PullDown for Port P23.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullDown for Port P23.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P23_PullUpDown_En();
 *     PORT_P23_PullDown_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P23_PullDown_Set(void)
{
  Field_Mod8(&PORT->P2_PUDSEL.reg, (uint8)PORT_P2_PUDSEL_P3_Pos, (uint8)PORT_P2_PUDSEL_P3_Msk, 0u);
}

/** \brief sets PullUp for Port P24.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullUp for Port P24.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P24_PullUpDown_En();
 *     PORT_P24_PullUp_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P24_PullUp_Set(void)
{
  Field_Mod8(&PORT->P2_PUDSEL.reg, (uint8)PORT_P2_PUDSEL_P4_Pos, (uint8)PORT_P2_PUDSEL_P4_Msk, 1u);
}

/** \brief sets PullDown for Port P24.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullDown for Port P24.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P24_PullUpDown_En();
 *     PORT_P24_PullDown_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P24_PullDown_Set(void)
{
  Field_Mod8(&PORT->P2_PUDSEL.reg, (uint8)PORT_P2_PUDSEL_P4_Pos, (uint8)PORT_P2_PUDSEL_P4_Msk, 0u);
}

/** \brief sets PullUp for Port P25.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullUp for Port P25.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P25_PullUpDown_En();
 *     PORT_P25_PullUp_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P25_PullUp_Set(void)
{
  Field_Mod8(&PORT->P2_PUDSEL.reg, (uint8)PORT_P2_PUDSEL_P5_Pos, (uint8)PORT_P2_PUDSEL_P5_Msk, 1u);
}

/** \brief sets PullDown for Port P25.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullDown for Port P25.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P25_PullUpDown_En();
 *     PORT_P25_PullDown_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P25_PullDown_Set(void)
{
  Field_Mod8(&PORT->P2_PUDSEL.reg, (uint8)PORT_P2_PUDSEL_P5_Pos, (uint8)PORT_P2_PUDSEL_P5_Msk, 0u);
}


/*******************************************************************************
**                        Global Function Declarations                        **
*******************************************************************************/
/** \brief Initializes the ports.
 * \note This function violates [MISRA Rule 38]
 *
 * \ingroup PORT_api
 */
void PORT_Init(void);

/** \brief Sets/clears/toggles a port pin in a safe way, i.e. with interrupt disable.
 * \note This function violates [MISRA Rule 45]
 *
 * \param PortPin Port and pin to change, e.g 0x12U for P1.2
 * \param Action PORT_ACTION_SET, PORT_ACTION_CLEAR or PORT_ACTION_TOGGLE
 *
 * \brief <b>Example</b><br>
 * \brief This example toggles the P1.2 .
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_ChangePin(0x12, PORT_ACTION_TOGGLE);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
void PORT_ChangePin(uint32 PortPin, uint32 Action);

/** \brief Reads a port pin.
 * \note This function violates [MISRA Rule 45]
 *
 * \param PortPin Port and pin to read, e.g 0x12U for P1.2
 * \return Port pin level (0U or 1U)
 *
 * \brief <b>Example</b><br>
 * \brief This example reads the status of P1.2 .
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     sts = PORT_ReadPin(0x12);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
uint8 PORT_ReadPin(uint32 PortPin);

/** \brief Reads a port.
 * \note This function violates [MISRA Rule 45]
 *
 * \param Port Port to read, e.g. 2U for Port 2
 * \return Port data (combination of 0Us and 1Us)
 *
 * \brief <b>Example</b><br>
 * \brief This example reads the status of Port2 .
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     sts = PORT_ReadPort(0x2);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
uint8 PORT_ReadPort(uint32 Port);


/** \brief Change Alternate Settings.
 * \note This function violates [MISRA Rule 45]
 *
 * \param PortPin pin to change AltSel, e.g. 0x01U for Port 0 Pin 1
 * \param AltSel alternate function for the pin (combination of 0Us and 1Us)
 *
 * \brief <b>Example</b><br>
 * \brief This example sets the P1.2 to Output and configures it to Normal GPIO.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P12_Output_Set();
 *     PORT_ChangePinAlt(0x12, 0u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
void PORT_ChangePinAlt(uint32 PortPin, uint8 AltSel);


#endif /* PORT_H */
