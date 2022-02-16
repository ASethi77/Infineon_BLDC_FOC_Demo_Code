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
 * \file     gpt12e.h
 *
 * \brief    General Purpose Timer 12 Encoder low level access library
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
** V0.1.0: 2014-05-13, DM:   Initial version                                  **
** V0.1.1: 2015-01-20, DM:   GPT12E timer stop API added                      **
** V0.1.2: 2015-02-10, DM:   Individual header file added                     **
** V0.1.3: 2015-08-27, DM:   Timer readout functions added                    **
** V0.1.4: 2017-05-26, DM:   API extended                                     **
** V0.1.5: 2017-09-29, DM:   MISRA 2012 compliance, the following PC-Lint     **
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
** V0.1.6: 2018-03-14, DM:   GPT12E_T5_Capture_Trig_Rising_CapIn_En(),        **
**                           GPT12E_T5_Capture_Trig_Rising_CapIn_Dis(),       **
**                           GPT12E_T5_Capture_Trig_Falling_CapIn_En(),       **
**                           GPT12E_T5_Capture_Trig_Falling_CapIn_Dis(),      **
**                           GPT12E_T5_Capture_Trig_Any_T3In_En(),            **
**                           GPT12E_T5_Capture_Trig_Any_T3In_Dis(),           **
**                           GPT12E_T5_Capture_Trig_Any_T3EUD_En(),           **
**                           GPT12E_T5_Capture_Trig_Any_T3EUD_Dis()           **
**                           modified for MISRA 2012                          **
** V0.1.7: 2018-07-05, BG:   Values for GPT12E_T4_Start_by_T3_En() and        **
**                           GPT12E_T4_Start_by_T3_Dis()                      **
**                           corrected in gpt12e.h                            **
** V0.1.8: 2018-11-27, JO:   Doxygen update                                   **
**                           Moved revision history from gpt12e.c to gpt12e.h **
** V0.1.9: 2020-04-15, BG:   Updated revision history format                  **
** V0.2.0: 2020-07-21, BG:   EP-439: Formatted .h/.c files                    **
*******************************************************************************/

#ifndef GPT12E_H
#define GPT12E_H

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "tle987x.h"
#include "types.h"
#include "sfr_access.h"
#include "gpt12e_defines.h"

/*******************************************************************************
**                           Global Type Definitions                          **
*******************************************************************************/
/** \enum TGPT1_Clk_Prescaler
 *  \brief This enum lists the GPT1 Mode Timer Prescaler.
 */
typedef enum
{
  GPT1_fSYS_Div_4  = 1u, /**< GPT1 Timer Input Clock Select: fGPT/4 */
  GPT1_fSYS_Div_8  = 0u, /**< GPT1 Timer Input Clock Select: fGPT/8 */
  GPT1_fSYS_Div_16 = 3u, /**< GPT1 Timer Input Clock Select: fGPT/16 */
  GPT1_fSYS_Div_32 = 2u  /**< GPT1 Timer Input Clock Select: fGPT/32 */
} TGPT1_Clk_Prescaler;

/** \enum TGPT12E_CCU6_SEL
 *  \brief This enum lists the GPT12E CCU6 Selection.
 */
typedef enum
{
  GPT12E_CCU6_CH0        = 0u,  /**< GPT12 TIN3B/TIN4D Input Select: CC60 */
  GPT12E_CCU6_CH1        = 1u,  /**< GPT12 TIN3B/TIN4D Input Select: CC61 */
  GPT12E_CCU6_CH2        = 2u,  /**< GPT12 TIN3B/TIN4D Input Select: CC62 */
  GPT12E_CCU6_T12_ZM     = 3u,  /**< GPT12 TIN3B/TIN4D Input Select: T12 ZM */
  GPT12E_CCU6_T12_PM     = 4u,  /**< GPT12 TIN3B/TIN4D Input Select: T12 PM */
  GPT12E_CCU6_T12_CM_CH0 = 5u,  /**< GPT12 TIN3B/TIN4D Input Select: T12 CM0 */
  GPT12E_CCU6_T12_CM_CH1 = 6u,  /**< GPT12 TIN3B/TIN4D Input Select: T12 CM1 */
  GPT12E_CCU6_T12_CM_CH2 = 7u,  /**< GPT12 TIN3B/TIN4D Input Select: T12 CM2 */
  GPT12E_CCU6_T13_PM     = 8u,  /**< GPT12 TIN3B/TIN4D Input Select: T13 PM */
  GPT12E_CCU6_T13_ZM     = 9u,  /**< GPT12 TIN3B/TIN4D Input Select: T13 ZM */
  GPT12E_CCU6_T13_CM     = 10u, /**< GPT12 TIN3B/TIN4D Input Select: T13 CM */
  GPT12E_CCU6_ANY_CHx    = 11u  /**< GPT12 TIN3B/TIN4D Input Select: Any Edge on CC60/61/62 */
} TGPT12E_CCU6_SEL;

/** \enum TGPT12E_T2IN
 *  \brief This enum lists the GPT12E T2INx Inputs.
 */
typedef enum
{
  GPT12E_T2INA_P12  = 0u, /**< The input pin for T2INA */
  GPT12E_T2INB_P14  = 1u  /**< The input pin for T2INB */
} TGPT12E_T2IN;

/** \enum TGPT12E_T2EUD
 *  \brief This enum lists the GPT12E T2EUDx Inputs.
 */
typedef enum
{
  GPT12E_T2EUDA_P02 = 0u, /**< The input pin for T2EUDA */
  GPT12E_T2EUDB_P24 = 1u  /**< The input pin for T2EUDB */
} TGPT12E_T2EUD;

/** \enum TGPT12E_T3IN
 *  \brief This enum lists the GPT12E T3INx Inputs.
 */
typedef enum
{
  GPT12E_T3INA_CCU6_CH0 = 0u, /**< The input pin for T3INA */
  GPT12E_T3INB_CCU6_SEL = 1u, /**< The input pin for T3INB */
  GPT12E_T3INC_P10      = 2u, /**< The input pin for T3INC */
  GPT12E_T3IND_MON      = 3u  /**< The input pin for T3IND */
} TGPT12E_T3IN;

/** \enum TGPT12E_T3EUD
 *  \brief This enum lists the GPT12E T3EUDx Inputs.
 */
typedef enum
{
  GPT12E_T3EUDA_P04     = 0u, /**< The input pin for T3EUDA */
  GPT12E_T3EUDB_P25     = 1u  /**< The input pin for T3EUDB */
} TGPT12E_T3EUD;

/** \enum TGPT12E_T4IN
 *  \brief This enum lists the GPT12E T4INx Inputs.
 */
typedef enum
{
  GPT12E_T4INA_P00      = 0u, /**< The input pin for T4INA */
  GPT12E_T4INB_CCU6_CH0 = 1u, /**< The input pin for T4INB */
  GPT12E_T4INC_P01      = 2u, /**< The input pin for T4INC */
  GPT12E_T4IND_CCU6_SEL = 3u  /**< The input pin for T4IND */
} TGPT12E_T4IN;

/** \enum TGPT12E_T4EUD
 *  \brief This enum lists the GPT12E T4EUDx Inputs.
 */
typedef enum
{
  GPT12E_T4EUDA_P03     = 0u, /**< The input pin for T4EUDA */
  GPT12E_T4EUDB_P10     = 1u  /**< The input pin for T4EUDB */
} TGPT12E_T4EUD;

/** \enum TGPT2_Clk_Prescaler
 *  \brief This enum lists the GPT2 Mode Timer Prescaler.
 */
typedef enum
{
  GPT2_fSYS_Div_2  = 1u, /**< GPT2 Timer Input Clock Select: fGPT/2 */
  GPT2_fSYS_Div_4  = 0u, /**< GPT2 Timer Input Clock Select: fGPT/4 */
  GPT2_fSYS_Div_8  = 3u, /**< GPT2 Timer Input Clock Select: fGPT/8 */
  GPT2_fSYS_Div_16 = 2u  /**< GPT2 Timer Input Clock Select: fGPT/16 */
} TGPT2_Clk_Prescaler;

/** \enum TGPT12E_T5IN
 *  \brief This enum lists the GPT12E T5INx Inputs.
 */
typedef enum
{
  GPT12E_T5INA_P03 = 0u, /**< The input pin for T5INA */
  GPT12E_T5INB_P20 = 1u  /**< The input pin for T5INB */
} TGPT12E_T5IN;

/** \enum TGPT12E_T5EUD
 *  \brief This enum lists the GPT12E T5EUDx Inputs.
 */
typedef enum
{
  GPT12E_T5EUDA_P14 = 0u, /**< The input pin for T5EUDA */
  GPT12E_T5EUDB_P20 = 1u  /**< The input pin for T5EUDB */
} TGPT12E_T5EUD;

/** \enum TGPT12E_T6IN
 *  \brief This enum lists the GPT12E T6INx Inputs.
 */
typedef enum
{
  GPT12E_T6INA_P02 = 0u, /**< The input pin for T6INA */
  GPT12E_T6INB_P13 = 1u  /**< The input pin for T6INB */
} TGPT12E_T6IN;

/** \enum TGPT12E_T6EUD
 *  \brief This enum lists the GPT12E T6EUDx Inputs.
 */
typedef enum
{
  GPT12E_T6EUDA_P11 = 0u, /**< The input pin for T6EUDA */
  GPT12E_T6EUDB_P13 = 1u  /**< The input pin for T6EUDB */
} TGPT12E_T6EUD;

/** \enum TGPT12E_CAPIN
 *  \brief This enum lists the GPT12E CAPINx Inputs.
 */
typedef enum
{
  GPT12E_CAPINA_P01           = 0u, /**< The input pin for CAPINA */
  GPT12E_CAPINB_P03           = 1u, /**< The input pin for CAPINB */
  GPT12E_CAPINC_T3_READ       = 2u, /**< The input pin for CAPINC */
  GPT12E_CAPIND_T2_T3_T4_READ = 3u  /**< The input pin for CAPIND */
} TGPT12E_CAPIN;

/** \enum TGPT12E_Mode_Timer_Prescaler
 *  \brief This enum lists the GPT12E Mode Timer Prescaler.
 */
typedef enum
{
  GPT_Clk_Div_1   = 0, /**< GPT12E Timer Input Clock Select: fCCU */
  GPT_Clk_Div_2   = 1, /**< GPT12E Timer Input Clock Select: fCCU/2 */
  GPT_Clk_Div_4   = 2, /**< GPT12E Timer Input Clock Select: fCCU/4 */
  GPT_Clk_Div_8   = 3, /**< GPT12E Timer Input Clock Select: fCCU/8 */
  GPT_Clk_Div_16  = 4, /**< GPT12E Timer Input Clock Select: fCCU/16 */
  GPT_Clk_Div_32  = 5, /**< GPT12E Timer Input Clock Select: fCCU/32 */
  GPT_Clk_Div_64  = 6, /**< GPT12E Timer Input Clock Select: fCCU/64 */
  GPT_Clk_Div_128 = 7  /**< GPT12E Timer Input Clock Select: fCCU/128 */
} TGPT12E_Mode_Timer_Prescaler;


/*******************************************************************************
**                     Global Inline Function Definitions                     **
*******************************************************************************/
/** \brief selects GPT1 Clock Prescaler.
 *
 * \param bps1 GPT1 clock prescaler
 *
 * \brief <b>Example</b><br>
 * \brief This example sets clock for block GPT1 to fGPT/4.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     GPT12E_GPT1_Clk_Prescaler_Sel(0x0001);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_GPT1_Clk_Prescaler_Sel(uint16 bps1)
{
  Field_Mod16(&GPT12E->T3CON.reg, (uint16)GPT12E_T3CON_BPS1_Pos, (uint16)GPT12E_T3CON_BPS1_Msk, (bps1 ^ (uint16)1));
}

/** \brief reads GPT1 Clock Prescaler.
 *
 * \return GPT1 clock prescaler
 *
 * \brief <b>Example</b><br>
 * \brief This example reads clock for block GPT1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint16 pres;
 *
 *    pres =  GPT12E_GPT1_Clk_Prescaler_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE uint16 GPT12E_GPT1_Clk_Prescaler_Get(void)
{
  return ( u16_Field_Rd16(&GPT12E->T3CON.reg, (uint16)GPT12E_T3CON_BPS1_Pos, (uint16)GPT12E_T3CON_BPS1_Msk) ^ (uint16)1 );
}

/** \brief selects GPT12 TIN3B/TIN4D Input.
 *
 * \param gpt GPT12 TIN3B/TIN4D Input Sel
 *
 * \brief <b>Example</b><br>
 * \brief This example sets T12 ZM as GPT12 TIN3B/TIN4D Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T3_T4_CCU6_Sel(0x03);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T3_T4_CCU6_Sel(uint8 gpt)
{
  Field_Mod8(&SCU->GPT12PISEL.reg, (uint8)SCU_GPT12PISEL_GPT12_Pos, (uint8)SCU_GPT12PISEL_GPT12_Msk, gpt);
}

/****************************************************************************/
/* Timer2 *******************************************************************/
/****************************************************************************/
/** \brief selects T2 Timer Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T2 Timer Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_Timer_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_Timer_Sel(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, (uint16)GPT12E_T2CON_T2M_Pos, (uint16)GPT12E_T2CON_T2M_Msk, 0u);
}

/** \brief selects T2 Counter Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T2 Counter Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_Counter_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_Counter_Sel(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, (uint16)GPT12E_T2CON_T2M_Pos, (uint16)GPT12E_T2CON_T2M_Msk, 1u);
}

/** \brief selects T2 Gated low Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T2 Gated Timer Mode with gate active low.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_Gated_Timer_Low_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_Gated_Timer_Low_Sel(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, (uint16)GPT12E_T2CON_T2M_Pos, (uint16)GPT12E_T2CON_T2M_Msk, 2u);
}

/** \brief selects T2 Gated high Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T2 Gated Timer Mode with gate active high.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_Gated_Timer_High_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_Gated_Timer_High_Sel(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, (uint16)GPT12E_T2CON_T2M_Pos, (uint16)GPT12E_T2CON_T2M_Msk, 3u);
}

/** \brief selects T2 Reload Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T2 Reload Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_Reload_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_Reload_Sel(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, (uint16)GPT12E_T2CON_T2M_Pos, (uint16)GPT12E_T2CON_T2M_Msk, 4u);
}

/** \brief selects T2 Capture Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T2 Capture Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_Capture_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_Capture_Sel(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, (uint16)GPT12E_T2CON_T2M_Pos, (uint16)GPT12E_T2CON_T2M_Msk, 5u);
}

/** \brief selects T2 Incremental Interface -Rotation Detection- Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T2 Incremental Interface -Rotation Detection-  Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_IncEnc_Rot_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_IncEnc_Rot_Sel(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, (uint16)GPT12E_T2CON_T2M_Pos, (uint16)GPT12E_T2CON_T2M_Msk, 6u);
}

/** \brief selects T2 Incremental Interface -Edge Detection- Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T2 Incremental Interface -Edge Detection-  Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_IncEnc_Edge_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_IncEnc_Edge_Sel(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, (uint16)GPT12E_T2CON_T2M_Pos, (uint16)GPT12E_T2CON_T2M_Msk, 7u);
}

/** \brief selects T2 Timer Mode Parameter.
 *
 * \param t2i T2 Input Parameter Sel
 *
 * \brief <b>Example</b><br>
 * \brief This example sets T2 Timer Mode Parameter to 0x01.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_Timer_Sel();
 *    GPT12E_T2_Mode_Timer_Clk_Prescaler_Sel(0x01);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_Timer_Clk_Prescaler_Sel(uint16 t2i)
{
  Field_Mod16(&GPT12E->T2CON.reg, (uint16)GPT12E_T2CON_T2I_Pos, (uint16)GPT12E_T2CON_T2I_Msk, t2i);
}

/** \brief selects T2 Gated Timer Mode Parameter.
 *
 * \param t2i T2 Input Parameter Sel
 *
 * \brief <b>Example</b><br>
 * \brief This example sets selects T2 Gated Timer Mode Parameter to 0x01.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_Gated_Timer_High_Sel();
 *    GPT12E_T2_Mode_Gated_Timer_Clk_Prescaler_Sel(0x01);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_Gated_Timer_Clk_Prescaler_Sel(uint16 t2i)
{
  Field_Mod16(&GPT12E->T2CON.reg, (uint16)GPT12E_T2CON_T2I_Pos, (uint16)GPT12E_T2CON_T2I_Msk, t2i);
}

/** \brief selects T2In as T2 Counter Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T2In as T2 Counter Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_Counter_Sel();
 *    GPT12E_T2_Mode_Counter_Input_T2In_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_Counter_Input_T2In_Sel(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, 2u, 4u, 0u);
}

/** \brief enables Rising Edge on T2In as T2 Counter Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Rising Edge on T2In as T2 Counter Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_Counter_Sel();
 *    GPT12E_T2_Mode_Counter_Input_Rising_T2In_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_Counter_Input_Rising_T2In_En(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, 0u, 1u, 1u);
}

/** \brief disables Rising Edge on T2In as T2 Counter Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Rising Edge on T2In as T2 Counter Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_Counter_Sel();
 *    GPT12E_T2_Mode_Counter_Input_Rising_T2In_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_Counter_Input_Rising_T2In_Dis(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, 0u, 1u, 0u);
}

/** \brief enables Falling Edge on T2In as T2 Counter Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Falling Edge on T2In as T2 Counter Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_Counter_Sel();
 *    GPT12E_T2_Mode_Counter_Input_Falling_T2In_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_Counter_Input_Falling_T2In_En(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, 1u, 2u, 1u);
}

/** \brief disables Falling Edge on T2In as T2 Counter Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Falling Edge on T2In as T2 Counter Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_Counter_Sel();
 *    GPT12E_T2_Mode_Counter_Input_Falling_T2In_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_Counter_Input_Falling_T2In_Dis(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, 1u, 2u, 0u);
}

/** \brief selects T3OTL as T2 Counter Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T3OTL as T2 Counter Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_Counter_Sel();
 *    GPT12E_T2_Mode_Counter_Input_T3Out_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_Counter_Input_T3Out_Sel(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, 2u, 4u, 1u);
}

/** \brief enables Rising Edge on T3OTL as T2 Counter Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Rising Edge on T3OTL as T2 Counter Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_Counter_Sel();
 *    GPT12E_T2_Mode_Counter_Input_Rising_T3Out_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_Counter_Input_Rising_T3Out_En(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, 0u, 1u, 1u);
}

/** \brief disables Rising Edge on T3OTL as T2 Counter Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Rising Edge on T3OTL as T2 Counter Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_Counter_Sel();
 *    GPT12E_T2_Mode_Counter_Input_Rising_T3Out_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_Counter_Input_Rising_T3Out_Dis(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, 0u, 1u, 0u);
}

/** \brief enables Falling Edge on T3OTL as T2 Counter Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Falling Edge on T3OTL as T2 Counter Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_Counter_Sel();
 *    GPT12E_T2_Mode_Counter_Input_Falling_T3Out_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_Counter_Input_Falling_T3Out_En(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, 1u, 2u, 1u);
}

/** \brief disables Falling Edge on T3OTL as T2 Counter Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Falling Edge on T3OTL as T2 Counter Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_Counter_Sel();
 *    GPT12E_T2_Mode_Counter_Input_Falling_T3Out_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_Counter_Input_Falling_T3Out_Dis(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, 1u, 2u, 0u);
}

/** \brief selects T2In as T2 Capture Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T2In as T2 Capture Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_Capture_Sel();
 *    GPT12E_T2_Mode_Capture_Input_T2In_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_Capture_Input_T2In_Sel(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, 2u, 4u, 0u);
}

/** \brief enables Rising Edge on T2In as T2 Capture Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Rising Edge on T2In as T2 Capture Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_Capture_Sel();
 *    GPT12E_T2_Mode_Capture_Input_Rising_T2In_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_Capture_Input_Rising_T2In_En(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, 0u, 1u, 1u);
}

/** \brief disables Rising Edge on T2In as T2 Capture Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Rising Edge on T2In as T2 Capture Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_Capture_Sel();
 *    GPT12E_T2_Mode_Capture_Input_Rising_T2In_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_Capture_Input_Rising_T2In_Dis(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, 0u, 1u, 0u);
}

/** \brief enables Falling Edge on T2In as T2 Capture Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Falling Edge on T2In as T2 Capture Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_Capture_Sel();
 *    GPT12E_T2_Mode_Capture_Input_Falling_T2In_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_Capture_Input_Falling_T2In_En(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, 1u, 2u, 1u);
}

/** \brief disables Falling Edge on T2In as T2 Capture Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Falling Edge on T2In as T2 Capture Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_Capture_Sel();
 *    GPT12E_T2_Mode_Capture_Input_Falling_T2In_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_Capture_Input_Falling_T2In_Dis(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, 1u, 2u, 0u);
}

/** \brief selects T2In as T2 Reload Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T2In as T2 Reload Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_Reload_Sel();
 *    GPT12E_T2_Mode_Reload_Input_T2In_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_Reload_Input_T2In_Sel(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, 2u, 4u, 0u);
}

/** \brief enables Rising Edge on T2In as T2 Reload Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Rising Edge on T2In as T2 Reload Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_Reload_Sel();
 *    GPT12E_T2_Mode_Reload_Input_Rising_T2In_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_Reload_Input_Rising_T2In_En(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, 0u, 1u, 1u);
}

/** \brief disables Rising Edge on T2In as T2 Reload Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Rising Edge on T2In as T2 Reload Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_Reload_Sel();
 *    GPT12E_T2_Mode_Reload_Input_Rising_T2In_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_Reload_Input_Rising_T2In_Dis(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, 0u, 1u, 0u);
}

/** \brief enables Falling Edge on T2In as T2 Reload Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Falling Edge on T2In as T2 Reload Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_Reload_Sel();
 *    GPT12E_T2_Mode_Reload_Input_Falling_T2In_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_Reload_Input_Falling_T2In_En(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, 1u, 2u, 1u);
}

/** \brief disables Falling Edge on T2In as T2 Reload Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Falling Edge on T2In as T2 Reload Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_Reload_Sel();
 *    GPT12E_T2_Mode_Reload_Input_Falling_T2In_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_Reload_Input_Falling_T2In_Dis(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, 1u, 2u, 0u);
}

/** \brief selects T3OTL as T2 Reload Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T3OTL as T2 Reload Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_Reload_Sel();
 *    GPT12E_T2_Mode_Reload_Input_T3Out_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_Reload_Input_T3Out_Sel(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, 2u, 4u, 1u);
}

/** \brief enables Rising Edge on T3OTL as T2 Reload Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Rising Edge on T3OTL as T2 Reload Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_Reload_Sel();
 *    GPT12E_T2_Mode_Reload_Input_Rising_T3Out_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_Reload_Input_Rising_T3Out_En(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, 0u, 1u, 1u);
}

/** \brief disables Rising Edge on T3OTL as T2 Reload Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Rising Edge on T3OTL as T2 Reload Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_Reload_Sel();
 *    GPT12E_T2_Mode_Reload_Input_Rising_T3Out_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_Reload_Input_Rising_T3Out_Dis(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, 0u, 1u, 0u);
}

/** \brief enables Falling Edge on T3OTL as T2 Reload Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Falling Edge on T3OTL as T2 Reload Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_Reload_Sel();
 *    GPT12E_T2_Mode_Reload_Input_Falling_T3Out_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_Reload_Input_Falling_T3Out_En(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, 1u, 2u, 1u);
}

/** \brief disables Falling Edge on T3OTL as T2 Reload Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Falling Edge on T3OTL as T2 Reload Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_Reload_Sel();
 *    GPT12E_T2_Mode_Reload_Input_Falling_T3Out_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_Reload_Input_Falling_T3Out_Dis(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, 1u, 2u, 0u);
}

/** \brief selects T2 Incremental Interface Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T2 Incremental Interface Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_IncEnc_Edge_Sel();
 *    GPT12E_T2_Mode_IncEnc_Input_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_IncEnc_Input_Sel(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, 2u, 4u, 0u);
}

/** \brief enables Rising or Falling Edge on T3In as T2 Incremental Interface Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Rising or Falling Edge on T3In as T2 Incremental Interface Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_IncEnc_Edge_Sel();
 *    GPT12E_T2_Mode_IncEnc_Any_T3In_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_IncEnc_Any_T3In_En(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, 0u, 1u, 1u);
}

/** \brief disables Rising or Falling Edge on T3In as T2 Incremental Interface Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Rising or Falling Edge on T3In as T2 Incremental Interface Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_IncEnc_Edge_Sel();
 *    GPT12E_T2_Mode_IncEnc_Any_T3In_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_IncEnc_Any_T3In_Dis(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, 0u, 1u, 0u);
}

/** \brief enables Falling or Falling Edge on T3EUD as T2 Incremental Interface Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Falling or Falling Edge on T3EUD as T2 Incremental Interface Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_IncEnc_Edge_Sel();
 *    GPT12E_T2_Mode_IncEnc_Any_T3EUD_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_IncEnc_Any_T3EUD_En(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, 1u, 2u, 1u);
}

/** \brief disables Falling or Falling Edge on T3EUD as T2 Incremental Interface Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Falling or Falling Edge on T3EUD as T2 Incremental Interface Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_IncEnc_Edge_Sel();
 *    GPT12E_T2_Mode_IncEnc_Any_T3EUD_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_IncEnc_Any_T3EUD_Dis(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, 1u, 2u, 0u);
}

/** \brief starts Timer T2.
 *
 * \brief <b>Example</b><br>
 * \brief This example starts Timer T2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Start_by_T3_Dis();
 *    GPT12E_T2_Start();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Start(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, (uint16)GPT12E_T2CON_T2R_Pos, (uint16)GPT12E_T2CON_T2R_Msk,  1u);
}

/** \brief stops Timer T2.
 *
 * \brief <b>Example</b><br>
 * \brief This example stops Timer T2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Start_by_T3_Dis();
 *    GPT12E_T2_Stop();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Stop(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, (uint16)GPT12E_T2CON_T2R_Pos, (uint16)GPT12E_T2CON_T2R_Msk,  0u);
}

/** \brief enables controlling Timer T2 by the run bit T3R of core timer T3.
 *
 * \brief <b>Example</b><br>
 * \brief This example starts Timer T2 by setting T3R.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Start_by_T3_En();
 *    GPT12E_T3_Start();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Start_by_T3_En(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, (uint16)GPT12E_T2CON_T2RC_Pos, (uint16)GPT12E_T2CON_T2RC_Msk, 1u);
}

/** \brief disables controlling Timer T2 by the run bit T3R of core timer T3.
 *
 * \brief <b>Example</b><br>
 * \brief This example starts Timer T2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Start_by_T3_Dis();
 *    GPT12E_T2_Start();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Start_by_T3_Dis(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, (uint16)GPT12E_T2CON_T2RC_Pos, (uint16)GPT12E_T2CON_T2RC_Msk, 0u);
}

/** \brief selects Timer T2 counts down.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Timer T2 counts down (internally).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_UpDownCount_Ext_Dis();
 *    GPT12E_T2_DownCount_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_DownCount_Sel(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, (uint16)GPT12E_T2CON_T2UD_Pos, (uint16)GPT12E_T2CON_T2UD_Msk, 1u);
}

/** \brief selects Timer T2 counts up.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Timer T2 counts up (internally).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_UpDownCount_Ext_Dis();
 *    GPT12E_T2_UpCount_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_UpCount_Sel(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, (uint16)GPT12E_T2CON_T2UD_Pos, (uint16)GPT12E_T2CON_T2UD_Msk, 0u);
}

/** \brief enables controlling Count direction by external input (T2EUD).
 *
 * \brief <b>Example</b><br>
 * \brief This example enables controlling Count direction by external input (T2EUD).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_UpDownCount_Ext_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_UpDownCount_Ext_En(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, (uint16)GPT12E_T2CON_T2UDE_Pos, (uint16)GPT12E_T2CON_T2UDE_Msk,  1u);
}

/** \brief disables controlling Count direction by external input (T2EUD).
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Timer T2 counts up (internally).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_UpDownCount_Ext_Dis();
 *    GPT12E_T2_UpCount_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_UpDownCount_Ext_Dis(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, (uint16)GPT12E_T2CON_T2UDE_Pos, (uint16)GPT12E_T2CON_T2UDE_Msk,  0u);
}

/** \brief selects Timer T2 Incremental Interface Rotation Detection Mode counts down.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Timer T2 Incremental Interface Rotation Detection Mode counts down.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_IncEnc_Rot_Sel();
 *    GPT12E_T2_Mode_IncEnc_DownCount_RotDir_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_IncEnc_DownCount_RotDir_Sel(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, (uint16)GPT12E_T2CON_T2RDIR_Pos, (uint16)GPT12E_T2CON_T2RDIR_Msk, 1u);
}

/** \brief selects Timer T2 Incremental Interface Rotation Detection Mode counts up.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Timer T2 Incremental Interface Rotation Detection Mode counts up.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_IncEnc_Rot_Sel();
 *    GPT12E_T2_Mode_IncEnc_UpCount_RotDir_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_IncEnc_UpCount_RotDir_Sel(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, (uint16)GPT12E_T2CON_T2RDIR_Pos, (uint16)GPT12E_T2CON_T2RDIR_Msk, 0u);
}

/** \brief reads Timer T2 Incremental Interface Edge Detection Counting.
 *
 * \return Count Edge Detection
 *
 * \brief <b>Example</b><br>
 * \brief This example clears counting of Timer T2 Incremental Interface Edge if it's detected.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_IncEnc_Edge_Sel();
 *    if (GPT12E_T2_Mode_IncEnc_Edge_Detect_Sts() == (uint8)1u)
 *     {
 *       GPT12E_T2_Mode_IncEnc_Edge_Detect_Clr();
 *    }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE uint8 GPT12E_T2_Mode_IncEnc_Edge_Detect_Sts(void)
{
  return ( u1_Field_Rd16(&GPT12E->T2CON.reg, (uint16)GPT12E_T2CON_T2EDGE_Pos, (uint16)GPT12E_T2CON_T2EDGE_Msk) );
}

/** \brief clears Timer T2 Incremental Interface Edge Detection Counting.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears counting of Timer T2 Incremental Interface Edge if it's detected.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_IncEnc_Edge_Sel();
 *    if (GPT12E_T2_Mode_IncEnc_Edge_Detect_Sts() == (uint8)1u)
 *     {
 *       GPT12E_T2_Mode_IncEnc_Edge_Detect_Clr();
 *    }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_IncEnc_Edge_Detect_Clr(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, (uint16)GPT12E_T2CON_T2EDGE_Pos, (uint16)GPT12E_T2CON_T2EDGE_Msk, 0u);
}

/** \brief reads Timer T2 Incremental Interface Direction Change.
 *
 * \return Direction Change
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Direction Change of Timer T2 Incremental Interface if it's detected.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_IncEnc_Edge_Sel();
 *    if (GPT12E_T2_Mode_IncEnc_Dir_Change_Sts() == (uint8)1u)
 *     {
 *       GPT12E_T2_Mode_IncEnc_Dir_Change_Clr();
 *    }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE uint8 GPT12E_T2_Mode_IncEnc_Dir_Change_Sts(void)
{
  return ( u1_Field_Rd16(&GPT12E->T2CON.reg, (uint16)GPT12E_T2CON_T2CHDIR_Pos, (uint16)GPT12E_T2CON_T2CHDIR_Msk) );
}

/** \brief clears Timer T2 Incremental Interface Direction Change.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Direction Change of Timer T2 Incremental Interface if it's detected.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_IncEnc_Edge_Sel();
 *    if (GPT12E_T2_Mode_IncEnc_Dir_Change_Sts() == (uint8)1u)
 *     {
 *       GPT12E_T2_Mode_IncEnc_Dir_Change_Clr();
 *    }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Mode_IncEnc_Dir_Change_Clr(void)
{
  Field_Mod16(&GPT12E->T2CON.reg, (uint16)GPT12E_T2CON_T2CHDIR_Pos, (uint16)GPT12E_T2CON_T2CHDIR_Msk, 0u);
}

/** \brief reads Timer T2 Value.
 *
 * \return T2 Value
 *
 * \brief <b>Example</b><br>
 * \brief This example reads Timer T2 Value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint16 timer;
 *
 *    timer = GPT12E_T2_Value_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE uint16 GPT12E_T2_Value_Get(void)
{
  return ( u16_Field_Rd16(&GPT12E->T2.reg, (uint16)GPT12E_T2_T2_Pos, (uint16)GPT12E_T2_T2_Msk) );
}

/** \brief sets Timer T2 Value.
 *
 * \param t2 T2 Value
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Timer T2 Value to 5000.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Value_Set(0x1388);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Value_Set(uint16 t2)
{
  Field_Wrt16(&GPT12E->T2.reg, (uint16)GPT12E_T2_T2_Pos, (uint16)GPT12E_T2_T2_Msk, t2);
}

/** \brief selects Input for T2IN.
 *
 * \param ist2in Input Select for T2IN
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Rising Edge Counter Mode on T2INB Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_Mode_Counter_Sel();
 *    GPT12E_T2_Mode_Counter_Input_Rising_T2In_En();
 *    GPT12E_T2_T2In_Sel(1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_T2In_Sel(uint16 ist2in)
{
  Field_Mod16(&GPT12E->PISEL.reg, (uint16)GPT12E_PISEL_IST2IN_Pos, (uint16)GPT12E_PISEL_IST2IN_Msk, ist2in);
}

/** \brief selects Input for T2EUD.
 *
 * \param ist2eud Input Select for T2EUD
 *
 * \brief <b>Example</b><br>
 * \brief This example enables controlling Count direction by the external input T2EUDB.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T2_UpDownCount_Ext_En();
 *    GPT12E_T2_T2EUD_Sel(1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_T2EUD_Sel(uint16 ist2eud)
{
  Field_Mod16(&GPT12E->PISEL.reg, (uint16)GPT12E_PISEL_IST2EUD_Pos, (uint16)GPT12E_PISEL_IST2EUD_Msk, ist2eud);
}

/****************************************************************************/
/* Timer3 * Core Timer ******************************************************/
/****************************************************************************/
/** \brief selects T3 Timer Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T3 Timer Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T3_Mode_Timer_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T3_Mode_Timer_Sel(void)
{
  Field_Mod16(&GPT12E->T3CON.reg, (uint16)GPT12E_T3CON_T3M_Pos, (uint16)GPT12E_T3CON_T3M_Msk, 0u);
}

/** \brief selects T3 Counter Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T3 Counter Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T3_Mode_Counter_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T3_Mode_Counter_Sel(void)
{
  Field_Mod16(&GPT12E->T3CON.reg, (uint16)GPT12E_T3CON_T3M_Pos, (uint16)GPT12E_T3CON_T3M_Msk, 1u);
}

/** \brief selects T3 Gated low Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T3 Gated Timer Mode with gate active low.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T3_Mode_Gated_Timer_Low_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T3_Mode_Gated_Timer_Low_Sel(void)
{
  Field_Mod16(&GPT12E->T3CON.reg, (uint16)GPT12E_T3CON_T3M_Pos, (uint16)GPT12E_T3CON_T3M_Msk, 2u);
}

/** \brief selects T3 Gated high Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T3 Gated Timer Mode with gate active high.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T3_Mode_Gated_Timer_High_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T3_Mode_Gated_Timer_High_Sel(void)
{
  Field_Mod16(&GPT12E->T3CON.reg, (uint16)GPT12E_T3CON_T3M_Pos, (uint16)GPT12E_T3CON_T3M_Msk, 3u);
}

/** \brief selects T3 Incremental Interface -Rotation Detection- Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T3 Incremental Interface -Rotation Detection-  Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T3_Mode_IncEnc_Rot_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T3_Mode_IncEnc_Rot_Sel(void)
{
  Field_Mod16(&GPT12E->T3CON.reg, (uint16)GPT12E_T3CON_T3M_Pos, (uint16)GPT12E_T3CON_T3M_Msk, 6u);
}

/** \brief selects T3 Incremental Interface -Edge Detection- Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T3 Incremental Interface -Edge Detection-  Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T3_Mode_IncEnc_Edge_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T3_Mode_IncEnc_Edge_Sel(void)
{
  Field_Mod16(&GPT12E->T3CON.reg, (uint16)GPT12E_T3CON_T3M_Pos, (uint16)GPT12E_T3CON_T3M_Msk, 7u);
}

/** \brief selects T3 Timer Mode Parameter.
 *
 * \param t3i T3 Input Parameter Sel
 *
 * \brief <b>Example</b><br>
 * \brief This example sets T3 Timer Mode Parameter to 0x01.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T3_Mode_Timer_Sel();
 *    GPT12E_T3_Mode_Timer_Clk_Prescaler_Sel(0x01);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T3_Mode_Timer_Clk_Prescaler_Sel(uint16 t3i)
{
  Field_Mod16(&GPT12E->T3CON.reg, (uint16)GPT12E_T3CON_T3I_Pos, (uint16)GPT12E_T3CON_T3I_Msk, t3i);
}

/** \brief selects T3 Gated Timer Mode Parameter.
 *
 * \param t3i T3 Input Parameter Sel
 *
 * \brief <b>Example</b><br>
 * \brief This example sets selects T3 Gated Timer Mode Parameter to 0x01.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T3_Mode_Gated_Timer_High_Sel();
 *    GPT12E_T3_Mode_Gated_Timer_Clk_Prescaler_Sel(0x01);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T3_Mode_Gated_Timer_Clk_Prescaler_Sel(uint16 t3i)
{
  Field_Mod16(&GPT12E->T3CON.reg, (uint16)GPT12E_T3CON_T3I_Pos, (uint16)GPT12E_T3CON_T3I_Msk, t3i);
}

/** \brief enables Rising Edge on T3In as T3 Counter Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Rising Edge on T3In as T3 Counter Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T3_Mode_Counter_Sel();
 *    GPT12E_T3_Mode_Counter_Input_Rising_T3In_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T3_Mode_Counter_Input_Rising_T3In_En(void)
{
  Field_Mod16(&GPT12E->T3CON.reg, 0u, 1u, 1u);
}

/** \brief disables Rising Edge on T3In as T3 Counter Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Rising Edge on T3In as T3 Counter Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T3_Mode_Counter_Sel();
 *    GPT12E_T3_Mode_Counter_Input_Rising_T3In_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T3_Mode_Counter_Input_Rising_T3In_Dis(void)
{
  Field_Mod16(&GPT12E->T3CON.reg, 0u, 1u, 0u);
}

/** \brief enables Falling Edge on T3In as T3 Counter Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Falling Edge on T3In as T3 Counter Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T3_Mode_Counter_Sel();
 *    GPT12E_T3_Mode_Counter_Input_Falling_T3In_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T3_Mode_Counter_Input_Falling_T3In_En(void)
{
  Field_Mod16(&GPT12E->T3CON.reg, 1u, 2u, 1u);
}

/** \brief disables Falling Edge on T3In as T3 Counter Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Falling Edge on T3In as T3 Counter Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T3_Mode_Counter_Sel();
 *    GPT12E_T3_Mode_Counter_Input_Falling_T3In_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T3_Mode_Counter_Input_Falling_T3In_Dis(void)
{
  Field_Mod16(&GPT12E->T3CON.reg, 1u, 2u, 0u);
}

/** \brief enables Rising or Falling Edge on T3In as T3 Incremental Interface Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Rising or Falling Edge on T3In as T3 Incremental Interface Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T3_Mode_IncEnc_Edge_Sel();
 *    GPT12E_T3_Mode_IncEnc_Any_T3In_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T3_Mode_IncEnc_Any_T3In_En(void)
{
  Field_Mod16(&GPT12E->T3CON.reg, 0u, 1u, 1u);
}

/** \brief disables Rising or Falling Edge on T3In as T3 Incremental Interface Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Rising or Falling Edge on T3In as T3 Incremental Interface Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T3_Mode_IncEnc_Edge_Sel();
 *    GPT12E_T3_Mode_IncEnc_Any_T3In_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T3_Mode_IncEnc_Any_T3In_Dis(void)
{
  Field_Mod16(&GPT12E->T3CON.reg, 0u, 1u, 0u);
}

/** \brief enables Falling or Falling Edge on T3EUD as T3 Incremental Interface Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Falling or Falling Edge on T3EUD as T3 Incremental Interface Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T3_Mode_IncEnc_Edge_Sel();
 *    GPT12E_T3_Mode_IncEnc_Any_T3EUD_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T3_Mode_IncEnc_Any_T3EUD_En(void)
{
  Field_Mod16(&GPT12E->T3CON.reg, 1u, 2u, 1u);
}

/** \brief disables Falling or Falling Edge on T3EUD as T3 Incremental Interface Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Falling or Falling Edge on T3EUD as T3 Incremental Interface Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T3_Mode_IncEnc_Edge_Sel();
 *    GPT12E_T3_Mode_IncEnc_Any_T3EUD_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T3_Mode_IncEnc_Any_T3EUD_Dis(void)
{
  Field_Mod16(&GPT12E->T3CON.reg, 1u, 2u, 0u);
}

/** \brief starts Timer T3.
 *
 * \brief <b>Example</b><br>
 * \brief This example starts Timer T3.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T3_Start();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T3_Start(void)
{
  Field_Mod16(&GPT12E->T3CON.reg, (uint16)GPT12E_T3CON_T3R_Pos, (uint16)GPT12E_T3CON_T3R_Msk, 1u);
}

/** \brief stops Timer T3.
 *
 * \brief <b>Example</b><br>
 * \brief This example stops Timer T3.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T3_Stop();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T3_Stop(void)
{
  Field_Mod16(&GPT12E->T3CON.reg, (uint16)GPT12E_T3CON_T3R_Pos, (uint16)GPT12E_T3CON_T3R_Msk, 0u);
}

/** \brief enables Timer T3 Overflow/Underflow Output.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Timer T3 Overflow/Underflow Output.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T3_Output_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T3_Output_En(void)
{
  Field_Mod16(&GPT12E->T3CON.reg, (uint16)GPT12E_T3CON_T3OE_Pos, (uint16)GPT12E_T3CON_T3OE_Msk,  1u);
}

/** \brief disables Timer T3 Overflow/Underflow Output.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Timer T3 Overflow/Underflow Output.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T3_Output_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T3_Output_Dis(void)
{
  Field_Mod16(&GPT12E->T3CON.reg, (uint16)GPT12E_T3CON_T3OE_Pos, (uint16)GPT12E_T3CON_T3OE_Msk,  0u);
}

/** \brief sets Timer T3 Overflow Toggle Latch.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Timer T3 Overflow Toggle Latch.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T3_Output_En();
 *    GPT12E_T3_Output_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T3_Output_Set(void)
{
  Field_Mod16(&GPT12E->T3CON.reg, (uint16)GPT12E_T3CON_T3OTL_Pos, (uint16)GPT12E_T3CON_T3OTL_Msk, 1u);
}

/** \brief clears Timer T3 Overflow Toggle Latch.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Timer T3 Overflow Toggle Latch.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T3_Output_En();
 *    GPT12E_T3_Output_Rst();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T3_Output_Rst(void)
{
  Field_Mod16(&GPT12E->T3CON.reg, (uint16)GPT12E_T3CON_T3OTL_Pos, (uint16)GPT12E_T3CON_T3OTL_Msk, 0u);
}

/** \brief selects Timer T3 counts down.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Timer T3 counts down (internally).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T3_UpDownCount_Ext_Dis();
 *    GPT12E_T3_DownCount_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T3_DownCount_Sel(void)
{
  Field_Mod16(&GPT12E->T3CON.reg, (uint16)GPT12E_T3CON_T3UD_Pos, (uint16)GPT12E_T3CON_T3UD_Msk,   1u);
}

/** \brief selects Timer T3 counts up.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Timer T3 counts up (internally).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T3_UpDownCount_Ext_Dis();
 *    GPT12E_T3_UpCount_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T3_UpCount_Sel(void)
{
  Field_Mod16(&GPT12E->T3CON.reg, (uint16)GPT12E_T3CON_T3UD_Pos, (uint16)GPT12E_T3CON_T3UD_Msk,   0u);
}

/** \brief enables controlling Count direction by external input (T3EUD).
 *
 * \brief <b>Example</b><br>
 * \brief This example enables controlling Count direction by external input (T3EUD).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T3_UpDownCount_Ext_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T3_UpDownCount_Ext_En(void)
{
  Field_Mod16(&GPT12E->T3CON.reg, (uint16)GPT12E_T3CON_T3UDE_Pos, (uint16)GPT12E_T3CON_T3UDE_Msk,  1u);
}

/** \brief disables controlling Count direction by external input (T3EUD).
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Timer T3 counts up (internally).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T3_UpDownCount_Ext_Dis();
 *    GPT12E_T3_UpCount_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T3_UpDownCount_Ext_Dis(void)
{
  Field_Mod16(&GPT12E->T3CON.reg, (uint16)GPT12E_T3CON_T3UDE_Pos, (uint16)GPT12E_T3CON_T3UDE_Msk,  0u);
}

/** \brief selects Timer T3 Incremental Interface Rotation Detection Mode counts down.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Timer T3 Incremental Interface Rotation Detection Mode counts down.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T3_Mode_IncEnc_Rot_Sel();
 *    GPT12E_T3_Mode_IncEnc_DownCount_RotDir_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T3_Mode_IncEnc_DownCount_RotDir_Sel(void)
{
  Field_Mod16(&GPT12E->T3CON.reg, (uint16)GPT12E_T3CON_T3RDIR_Pos, (uint16)GPT12E_T3CON_T3RDIR_Msk, 1u);
}

/** \brief selects Timer T3 Incremental Interface Rotation Detection Mode counts up.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Timer T3 Incremental Interface Rotation Detection Mode counts up.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T3_Mode_IncEnc_Rot_Sel();
 *    GPT12E_T3_Mode_IncEnc_UpCount_RotDir_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T3_Mode_IncEnc_UpCount_RotDir_Sel(void)
{
  Field_Mod16(&GPT12E->T3CON.reg, (uint16)GPT12E_T3CON_T3RDIR_Pos, (uint16)GPT12E_T3CON_T3RDIR_Msk, 0u);
}

/** \brief reads Timer T3 Incremental Interface Edge Detection Counting.
 *
 * \return Count Edge Detection
 *
 * \brief <b>Example</b><br>
 * \brief This example clears counting of Timer T3 Incremental Interface Edge if it's detected.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T3_Mode_IncEnc_Edge_Sel();
 *    if (GPT12E_T3_Mode_IncEnc_Edge_Detect_Sts() == (uint8)1u)
 *     {
 *       GPT12E_T3_Mode_IncEnc_Edge_Detect_Clr();
 *    }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE uint8 GPT12E_T3_Mode_IncEnc_Edge_Detect_Sts(void)
{
  return ( u1_Field_Rd16(&GPT12E->T3CON.reg, (uint16)GPT12E_T3CON_T3EDGE_Pos, (uint16)GPT12E_T3CON_T3EDGE_Msk) );
}

/** \brief clears Timer T3 Incremental Interface Edge Detection Counting.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears counting of Timer T3 Incremental Interface Edge if it's detected.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T3_Mode_IncEnc_Edge_Sel();
 *    if (GPT12E_T3_Mode_IncEnc_Edge_Detect_Sts() == (uint8)1u)
 *     {
 *       GPT12E_T3_Mode_IncEnc_Edge_Detect_Clr();
 *    }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T3_Mode_IncEnc_Edge_Detect_Clr(void)
{
  Field_Mod16(&GPT12E->T3CON.reg, (uint16)GPT12E_T3CON_T3EDGE_Pos, (uint16)GPT12E_T3CON_T3EDGE_Msk, 0u);
}

/** \brief reads Timer T3 Incremental Interface Direction Change.
 *
 * \return Direction Change
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Direction Change of Timer T3 Incremental Interface if it's detected.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T3_Mode_IncEnc_Edge_Sel();
 *    if (GPT12E_T3_Mode_IncEnc_Dir_Change_Sts() == (uint8)1u)
 *     {
 *       GPT12E_T3_Mode_IncEnc_Dir_Change_Clr();
 *    }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE uint8 GPT12E_T3_Mode_IncEnc_Dir_Change_Sts(void)
{
  return ( u1_Field_Rd16(&GPT12E->T3CON.reg, (uint16)GPT12E_T3CON_T3CHDIR_Pos, (uint16)GPT12E_T3CON_T3CHDIR_Msk) );
}

/** \brief clears Timer T3 Incremental Interface Direction Change.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Direction Change of Timer T3 Incremental Interface if it's detected.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T3_Mode_IncEnc_Edge_Sel();
 *    if (GPT12E_T3_Mode_IncEnc_Dir_Change_Sts() == (uint8)1u)
 *     {
 *       GPT12E_T3_Mode_IncEnc_Dir_Change_Clr();
 *    }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T3_Mode_IncEnc_Dir_Change_Clr(void)
{
  Field_Mod16(&GPT12E->T3CON.reg, (uint16)GPT12E_T3CON_T3CHDIR_Pos, (uint16)GPT12E_T3CON_T3CHDIR_Msk, 0u);
}

/** \brief reads Timer T3 Value.
 *
 * \return T3 Value
 *
 * \brief <b>Example</b><br>
 * \brief This example reads Timer T3 Value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint16 timer;
 *
 *    timer = GPT12E_T3_Value_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE uint16 GPT12E_T3_Value_Get(void)
{
  return ( u16_Field_Rd16(&GPT12E->T3.reg, (uint16)GPT12E_T3_T3_Pos, (uint16)GPT12E_T3_T3_Msk) );
}

/** \brief sets Timer T3 Value.
 *
 * \param t3 T3 Value
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Timer T3 Value to 5000.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T3_Value_Set(0x1388);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T3_Value_Set(uint16 t3)
{
  Field_Wrt16(&GPT12E->T3.reg, (uint16)GPT12E_T3_T3_Pos, (uint16)GPT12E_T3_T3_Msk, t3);
}

/** \brief selects Input for T3IN.
 *
 * \param ist3in Input Select for T3IN
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Rising Edge Counter Mode on T3INB Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T3_Mode_Counter_Sel();
 *    GPT12E_T3_Mode_Counter_Input_Rising_T3In_En();
 *    GPT12E_T3_T3In_Sel(1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T3_T3In_Sel(uint16 ist3in)
{
  Field_Mod16(&GPT12E->PISEL.reg, (uint16)GPT12E_PISEL_IST3IN_Pos, (uint16)GPT12E_PISEL_IST3IN_Msk,  ist3in);
}

/** \brief selects Input for T3EUD.
 *
 * \param ist3eud Input Select for T3EUD
 *
 * \brief <b>Example</b><br>
 * \brief This example enables controlling Count direction by the external input T3EUDB.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T3_UpDownCount_Ext_En();
 *    GPT12E_T3_T3EUD_Sel(1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T3_T3EUD_Sel(uint16 ist3eud)
{
  Field_Mod16(&GPT12E->PISEL.reg, (uint16)GPT12E_PISEL_IST3EUD_Pos, (uint16)GPT12E_PISEL_IST3EUD_Msk, ist3eud);
}

/****************************************************************************/
/* Timer4 *******************************************************************/
/****************************************************************************/
/** \brief selects T4 Timer Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T4 Timer Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_Timer_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_Timer_Sel(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, (uint16)GPT12E_T4CON_T4M_Pos, (uint16)GPT12E_T4CON_T4M_Msk, 0u);
}

/** \brief selects T4 Counter Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T4 Counter Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_Counter_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_Counter_Sel(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, (uint16)GPT12E_T4CON_T4M_Pos, (uint16)GPT12E_T4CON_T4M_Msk, 1u);
}

/** \brief selects T4 Gated low Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T4 Gated Timer Mode with gate active low.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_Gated_Timer_Low_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_Gated_Timer_Low_Sel(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, (uint16)GPT12E_T4CON_T4M_Pos, (uint16)GPT12E_T4CON_T4M_Msk, 2u);
}

/** \brief selects T4 Gated high Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T4 Gated Timer Mode with gate active high.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_Gated_Timer_High_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_Gated_Timer_High_Sel(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, (uint16)GPT12E_T4CON_T4M_Pos, (uint16)GPT12E_T4CON_T4M_Msk, 3u);
}

/** \brief selects T4 Reload Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T4 Reload Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_Reload_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_Reload_Sel(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, (uint16)GPT12E_T4CON_T4M_Pos, (uint16)GPT12E_T4CON_T4M_Msk, 4u);
}

/** \brief selects T4 Capture Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T4 Capture Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_Capture_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_Capture_Sel(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, (uint16)GPT12E_T4CON_T4M_Pos, (uint16)GPT12E_T4CON_T4M_Msk, 5u);
}

/** \brief selects T4 Incremental Interface -Rotation Detection- Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T4 Incremental Interface -Rotation Detection-  Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_IncEnc_Rot_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_IncEnc_Rot_Sel(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, (uint16)GPT12E_T4CON_T4M_Pos, (uint16)GPT12E_T4CON_T4M_Msk, 6u);
}

/** \brief selects T4 Incremental Interface -Edge Detection- Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T4 Incremental Interface -Edge Detection-  Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_IncEnc_Edge_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_IncEnc_Edge_Sel(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, (uint16)GPT12E_T4CON_T4M_Pos, (uint16)GPT12E_T4CON_T4M_Msk, 7u);
}

/** \brief selects T4 Timer Mode Parameter.
 *
 * \param t4i T4 Input Parameter Sel
 *
 * \brief <b>Example</b><br>
 * \brief This example sets T4 Timer Mode Parameter to 0x01.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_Timer_Sel();
 *    GPT12E_T4_Mode_Timer_Clk_Prescaler_Sel(0x01);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_Timer_Clk_Prescaler_Sel(uint16 t4i)
{
  Field_Mod16(&GPT12E->T4CON.reg, (uint16)GPT12E_T4CON_T4I_Pos, (uint16)GPT12E_T4CON_T4I_Msk, t4i);
}

/** \brief selects T4 Gated Timer Mode Parameter.
 *
 * \param t4i T4 Input Parameter Sel
 *
 * \brief <b>Example</b><br>
 * \brief This example sets selects T4 Gated Timer Mode Parameter to 0x01.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_Gated_Timer_High_Sel();
 *    GPT12E_T4_Mode_Gated_Timer_Clk_Prescaler_Sel(0x01);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_Gated_Timer_Clk_Prescaler_Sel(uint16 t4i)
{
  Field_Mod16(&GPT12E->T4CON.reg, (uint16)GPT12E_T4CON_T4I_Pos, (uint16)GPT12E_T4CON_T4I_Msk, t4i);
}

/** \brief selects T4In as T4 Counter Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T4In as T4 Counter Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_Counter_Sel();
 *    GPT12E_T4_Mode_Counter_Input_T4In_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_Counter_Input_T4In_Sel(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, 2u, 4u, 0u);
}

/** \brief enables Rising Edge on T4In as T4 Counter Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Rising Edge on T4In as T4 Counter Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_Counter_Sel();
 *    GPT12E_T4_Mode_Counter_Input_Rising_T4In_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_Counter_Input_Rising_T4In_En(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, 0u, 1u, 1u);
}

/** \brief disables Rising Edge on T4In as T4 Counter Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Rising Edge on T4In as T4 Counter Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_Counter_Sel();
 *    GPT12E_T4_Mode_Counter_Input_Rising_T4In_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_Counter_Input_Rising_T4In_Dis(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, 0u, 1u, 0u);
}

/** \brief enables Falling Edge on T4In as T4 Counter Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Falling Edge on T4In as T4 Counter Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_Counter_Sel();
 *    GPT12E_T4_Mode_Counter_Input_Falling_T4In_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_Counter_Input_Falling_T4In_En(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, 1u, 2u, 1u);
}

/** \brief disables Falling Edge on T4In as T4 Counter Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Falling Edge on T4In as T4 Counter Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_Counter_Sel();
 *    GPT12E_T4_Mode_Counter_Input_Falling_T4In_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_Counter_Input_Falling_T4In_Dis(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, 1u, 2u, 0u);
}

/** \brief selects T3OTL as T4 Counter Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T3OTL as T4 Counter Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_Counter_Sel();
 *    GPT12E_T4_Mode_Counter_Input_T3Out_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_Counter_Input_T3Out_Sel(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, 2u, 4u, 1u);
}

/** \brief enables Rising Edge on T3OTL as T4 Counter Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Rising Edge on T3OTL as T4 Counter Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_Counter_Sel();
 *    GPT12E_T4_Mode_Counter_Input_Rising_T3Out_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_Counter_Input_Rising_T3Out_En(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, 0u, 1u, 1u);
}

/** \brief disables Rising Edge on T3OTL as T4 Counter Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Rising Edge on T3OTL as T4 Counter Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_Counter_Sel();
 *    GPT12E_T4_Mode_Counter_Input_Rising_T3Out_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_Counter_Input_Rising_T3Out_Dis(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, 0u, 1u, 0u);
}

/** \brief enables Falling Edge on T3OTL as T4 Counter Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Falling Edge on T3OTL as T4 Counter Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_Counter_Sel();
 *    GPT12E_T4_Mode_Counter_Input_Falling_T3Out_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_Counter_Input_Falling_T3Out_En(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, 1u, 2u, 1u);
}

/** \brief disables Falling Edge on T3OTL as T4 Counter Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Falling Edge on T3OTL as T4 Counter Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_Counter_Sel();
 *    GPT12E_T4_Mode_Counter_Input_Falling_T3Out_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_Counter_Input_Falling_T3Out_Dis(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, 1u, 2u, 0u);
}

/** \brief selects T4In as T4 Capture Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T4In as T4 Capture Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_Capture_Sel();
 *    GPT12E_T4_Mode_Capture_Input_T4In_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_Capture_Input_T4In_Sel(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, 2u, 4u, 0u);
}

/** \brief enables Rising Edge on T4In as T4 Capture Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Rising Edge on T4In as T4 Capture Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_Capture_Sel();
 *    GPT12E_T4_Mode_Capture_Input_Rising_T4In_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_Capture_Input_Rising_T4In_En(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, 0u, 1u, 1u);
}

/** \brief disables Rising Edge on T4In as T4 Capture Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Rising Edge on T4In as T4 Capture Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_Capture_Sel();
 *    GPT12E_T4_Mode_Capture_Input_Rising_T4In_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_Capture_Input_Rising_T4In_Dis(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, 0u, 1u, 0u);
}

/** \brief enables Falling Edge on T4In as T4 Capture Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Falling Edge on T4In as T4 Capture Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_Capture_Sel();
 *    GPT12E_T4_Mode_Capture_Input_Falling_T4In_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_Capture_Input_Falling_T4In_En(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, 1u, 2u, 1u);
}

/** \brief disables Falling Edge on T4In as T4 Capture Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Falling Edge on T4In as T4 Capture Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_Capture_Sel();
 *    GPT12E_T4_Mode_Capture_Input_Falling_T4In_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_Capture_Input_Falling_T4In_Dis(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, 1u, 2u, 0u);
}

/** \brief selects T4In as T4 Reload Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T4n as T4 Reload Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_Reload_Sel();
 *    GPT12E_T4_Mode_Reload_Input_T4In_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_Reload_Input_T4In_Sel(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, 2u, 4u, 0u);
}

/** \brief enables Rising Edge on T4In as T4 Reload Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Rising Edge on T4In as T4 Reload Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_Reload_Sel();
 *    GPT12E_T4_Mode_Reload_Input_Rising_T4In_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_Reload_Input_Rising_T4In_En(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, 0u, 1u, 1u);
}

/** \brief disables Rising Edge on T4In as T4 Reload Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Rising Edge on T4In as T4 Reload Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_Reload_Sel();
 *    GPT12E_T4_Mode_Reload_Input_Rising_T4In_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_Reload_Input_Rising_T4In_Dis(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, 0u, 1u, 0u);
}

/** \brief enables Falling Edge on T4In as T4 Reload Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Falling Edge on T4In as T4 Reload Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_Reload_Sel();
 *    GPT12E_T4_Mode_Reload_Input_Falling_T4In_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_Reload_Input_Falling_T4In_En(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, 1u, 2u, 1u);
}

/** \brief disables Falling Edge on T4In as T4 Reload Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Falling Edge on T4In as T4 Reload Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_Reload_Sel();
 *    GPT12E_T4_Mode_Reload_Input_Falling_T4In_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_Reload_Input_Falling_T4In_Dis(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, 1u, 2u, 0u);
}

/** \brief selects T3OTL as T4 Reload Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T3OTL as T4 Reload Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_Reload_Sel();
 *    GPT12E_T4_Mode_Reload_Input_T3Out_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_Reload_Input_T3Out_Sel(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, 2u, 4u, 1u);
}

/** \brief enables Rising Edge on T3OTL as T4 Reload Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Rising Edge on T3OTL as T4 Reload Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_Reload_Sel();
 *    GPT12E_T4_Mode_Reload_Input_Rising_T3Out_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_Reload_Input_Rising_T3Out_En(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, 0u, 1u, 1u);
}

/** \brief disables Rising Edge on T3OTL as T4 Reload Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Rising Edge on T3OTL as T4 Reload Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_Reload_Sel();
 *    GPT12E_T4_Mode_Reload_Input_Rising_T3Out_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_Reload_Input_Rising_T3Out_Dis(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, 0u, 1u, 0u);
}

/** \brief enables Falling Edge on T3OTL as T4 Reload Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Falling Edge on T3OTL as T4 Reload Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_Reload_Sel();
 *    GPT12E_T4_Mode_Reload_Input_Falling_T3Out_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_Reload_Input_Falling_T3Out_En(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, 1u, 2u, 1u);
}

/** \brief disables Falling Edge on T3OTL as T4 Reload Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Falling Edge on T3OTL as T4 Reload Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_Reload_Sel();
 *    GPT12E_T4_Mode_Reload_Input_Falling_T3Out_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_Reload_Input_Falling_T3Out_Dis(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, 1u, 2u, 0u);
}

/** \brief enables Rising or Falling Edge on T3In as T4 Incremental Interface Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Rising or Falling Edge on T3In as T4 Incremental Interface Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_IncEnc_Edge_Sel();
 *    GPT12E_T4_Mode_IncEnc_Any_T3In_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_IncEnc_Any_T3In_En(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, 0u, 1u, 1u);
}

/** \brief disables Rising or Falling Edge on T3In as T4 Incremental Interface Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Rising or Falling Edge on T3In as T4 Incremental Interface Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_IncEnc_Edge_Sel();
 *    GPT12E_T4_Mode_IncEnc_Any_T3In_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_IncEnc_Any_T3In_Dis(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, 0u, 1u, 0u);
}

/** \brief enables Falling or Falling Edge on T3EUD as T4 Incremental Interface Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Falling or Falling Edge on T3EUD as T4 Incremental Interface Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_IncEnc_Edge_Sel();
 *    GPT12E_T4_Mode_IncEnc_Any_T3EUD_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_IncEnc_Any_T3EUD_En(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, 1u, 2u, 1u);
}

/** \brief disables Falling or Falling Edge on T3EUD as T4 Incremental Interface Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Falling or Falling Edge on T3EUD as T4 Incremental Interface Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_IncEnc_Edge_Sel();
 *    GPT12E_T4_Mode_IncEnc_Any_T3EUD_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_IncEnc_Any_T3EUD_Dis(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, 1u, 2u, 0u);
}

/** \brief starts Timer T4.
 *
 * \brief <b>Example</b><br>
 * \brief This example starts Timer T4.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Start_by_T3_Dis();
 *    GPT12E_T4_Start();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Start(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, (uint16)GPT12E_T4CON_T4R_Pos, (uint16)GPT12E_T4CON_T4R_Msk,  1u);
}

/** \brief stops Timer T4.
 *
 * \brief <b>Example</b><br>
 * \brief This example stops Timer T4.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Start_by_T3_Dis();
 *    GPT12E_T4_Stop();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Stop(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, (uint16)GPT12E_T4CON_T4R_Pos, (uint16)GPT12E_T4CON_T4R_Msk,  0u);
}

/** \brief enables controlling Timer T4 by the run bit T3R of core timer T3.
 *
 * \brief <b>Example</b><br>
 * \brief This example starts Timer T4 by setting T3R.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Start_by_T3_En();
 *    GPT12E_T3_Start();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Start_by_T3_En(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, (uint16)GPT12E_T4CON_T4RC_Pos, (uint16)GPT12E_T4CON_T4RC_Msk, 1u);
}

/** \brief disables controlling Timer T4 by the run bit T3R of core timer T3.
 *
 * \brief <b>Example</b><br>
 * \brief This example starts Timer T4.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Start_by_T3_Dis();
 *    GPT12E_T4_Start();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Start_by_T3_Dis(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, (uint16)GPT12E_T4CON_T4RC_Pos, (uint16)GPT12E_T4CON_T4RC_Msk, 0u);
}

/** \brief selects Timer T4 counts down.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Timer T4 counts down (internally).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_UpDownCount_Ext_Dis();
 *    GPT12E_T4_DownCount_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_DownCount_Sel(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, (uint16)GPT12E_T4CON_T4UD_Pos, (uint16)GPT12E_T4CON_T4UD_Msk,  1u);
}

/** \brief selects Timer T4 counts up.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Timer T4 counts up (internally).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_UpDownCount_Ext_Dis();
 *    GPT12E_T4_UpCount_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_UpCount_Sel(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, (uint16)GPT12E_T4CON_T4UD_Pos, (uint16)GPT12E_T4CON_T4UD_Msk,  0u);
}

/** \brief enables controlling Count direction by external input (T4EUD).
 *
 * \brief <b>Example</b><br>
 * \brief This example enables controlling Count direction by external input (T4EUD).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_UpDownCount_Ext_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_UpDownCount_Ext_En(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, (uint16)GPT12E_T4CON_T4UDE_Pos, (uint16)GPT12E_T4CON_T4UDE_Msk, 1u);
}

/** \brief disables controlling Count direction by external input (T4EUD).
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Timer T4 counts up (internally).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_UpDownCount_Ext_Dis();
 *    GPT12E_T4_UpCount_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_UpDownCount_Ext_Dis(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, (uint16)GPT12E_T4CON_T4UDE_Pos, (uint16)GPT12E_T4CON_T4UDE_Msk, 0u);
}

/** \brief selects Timer T4 Incremental Interface Rotation Detection Mode counts down.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Timer T4 Incremental Interface Rotation Detection Mode counts down.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_IncEnc_Rot_Sel();
 *    GPT12E_T4_Mode_IncEnc_DownCount_RotDir_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_IncEnc_DownCount_RotDir_Sel(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, (uint16)GPT12E_T4CON_T4RDIR_Pos, (uint16)GPT12E_T4CON_T4RDIR_Msk, 1u);
}

/** \brief selects Timer T4 Incremental Interface Rotation Detection Mode counts up.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Timer T4 Incremental Interface Rotation Detection Mode counts up.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_IncEnc_Rot_Sel();
 *    GPT12E_T4_Mode_IncEnc_UpCount_RotDir_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_IncEnc_UpCount_RotDir_Sel(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, (uint16)GPT12E_T4CON_T4RDIR_Pos, (uint16)GPT12E_T4CON_T4RDIR_Msk, 0u);
}

/** \brief Enables the automatic clearing of timer T2 upon a falling edge of the selected T4EUD input.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables the automatic clearing of timer T2 upon a falling edge of the selected T4EUD input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_UpDownCount_Ext_En();
 *    GPT12E_T4_T4EUD_Sel(1u);
 *    GPT12E_T4_Clr_T2_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Clr_T2_En(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, (uint16)GPT12E_T4CON_CLRT2EN_Pos, (uint16)GPT12E_T4CON_CLRT2EN_Msk,  1u);
}

/** \brief Disables the automatic clearing of timer T2 upon a falling edge of the selected T4EUD input.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables the automatic clearing of timer T2 upon a falling edge of the selected T4EUD input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Clr_T2_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Clr_T2_Dis(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, (uint16)GPT12E_T4CON_CLRT2EN_Pos, (uint16)GPT12E_T4CON_CLRT2EN_Msk,  0u);
}

/** \brief Enables the automatic clearing of timer T3 upon a falling edge of the selected T4EUD input.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables the automatic clearing of timer T3 upon a falling edge of the selected T4EUD input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_UpDownCount_Ext_En();
 *    GPT12E_T4_T4EUD_Sel(1u);
 *    GPT12E_T4_Clr_T3_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Clr_T3_En(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, (uint16)GPT12E_T4CON_CLRT3EN_Pos, (uint16)GPT12E_T4CON_CLRT3EN_Msk,  1u);
}

/** \brief Disables the automatic clearing of timer T3 upon a falling edge of the selected T4EUD input.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables the automatic clearing of timer T3 upon a falling edge of the selected T4EUD input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Clr_T3_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Clr_T3_Dis(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, (uint16)GPT12E_T4CON_CLRT3EN_Pos, (uint16)GPT12E_T4CON_CLRT3EN_Msk,  0u);
}

/** \brief reads Timer T4 Incremental Interface Edge Detection Counting.
 *
 * \return Count Edge Detection
 *
 * \brief <b>Example</b><br>
 * \brief This example clears counting of Timer T4 Incremental Interface Edge if it's detected.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_IncEnc_Edge_Sel();
 *    if (GPT12E_T4_Mode_IncEnc_Edge_Detect_Sts() == (uint8)1u)
 *     {
 *       GPT12E_T4_Mode_IncEnc_Edge_Detect_Clr();
 *    }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE uint8 GPT12E_T4_Mode_IncEnc_Edge_Detect_Sts(void)
{
  return ( u1_Field_Rd16(&GPT12E->T4CON.reg, (uint16)GPT12E_T4CON_T4EDGE_Pos, (uint16)GPT12E_T4CON_T4EDGE_Msk) );
}

/** \brief clears Timer T4 Incremental Interface Edge Detection Counting.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears counting of Timer T4 Incremental Interface Edge if it's detected.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_IncEnc_Edge_Sel();
 *    if (GPT12E_T4_Mode_IncEnc_Edge_Detect_Sts() == (uint8)1u)
 *     {
 *       GPT12E_T4_Mode_IncEnc_Edge_Detect_Clr();
 *    }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_IncEnc_Edge_Detect_Clr(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, (uint16)GPT12E_T4CON_T4EDGE_Pos, (uint16)GPT12E_T4CON_T4EDGE_Msk, 0u);
}

/** \brief reads Timer T4 Incremental Interface Direction Change.
 *
 * \return Direction Change
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Direction Change of Timer T4 Incremental Interface if it's detected.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_IncEnc_Edge_Sel();
 *    if (GPT12E_T4_Mode_IncEnc_Dir_Change_Sts() == (uint8)1u)
 *     {
 *       GPT12E_T4_Mode_IncEnc_Dir_Change_Clr();
 *    }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE uint8 GPT12E_T4_Mode_IncEnc_Dir_Change_Sts(void)
{
  return ( u1_Field_Rd16(&GPT12E->T4CON.reg, (uint16)GPT12E_T4CON_T4CHDIR_Pos, (uint16)GPT12E_T4CON_T4CHDIR_Msk) );
}

/** \brief clears Timer T4 Incremental Interface Direction Change.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Direction Change of Timer T4 Incremental Interface if it's detected.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_IncEnc_Edge_Sel();
 *    if (GPT12E_T4_Mode_IncEnc_Dir_Change_Sts() == (uint8)1u)
 *     {
 *       GPT12E_T4_Mode_IncEnc_Dir_Change_Clr();
 *    }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Mode_IncEnc_Dir_Change_Clr(void)
{
  Field_Mod16(&GPT12E->T4CON.reg, (uint16)GPT12E_T4CON_T4CHDIR_Pos, (uint16)GPT12E_T4CON_T4CHDIR_Msk, 0u);
}

/** \brief reads Timer T4 Value.
 *
 * \return T4 Value
 *
 * \brief <b>Example</b><br>
 * \brief This example reads Timer T4 Value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint16 timer;
 *
 *    timer = GPT12E_T4_Value_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE uint16 GPT12E_T4_Value_Get(void)
{
  return ( u16_Field_Rd16(&GPT12E->T4.reg, (uint16)GPT12E_T4_T4_Pos, (uint16)GPT12E_T4_T4_Msk) );
}

/** \brief sets Timer T4 Value.
 *
 * \param t4 T4 Value
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Timer T4 Value to 5000.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Value_Set(0x1388);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Value_Set(uint16 t4)
{
  Field_Wrt16(&GPT12E->T4.reg, (uint16)GPT12E_T4_T4_Pos, (uint16)GPT12E_T4_T4_Msk, t4);
}

/** \brief selects Input for T4IN.
 *
 * \param ist4in Input Select for T4IN
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Rising Edge Counter Mode on T4INB Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_Mode_Counter_Sel();
 *    GPT12E_T4_Mode_Counter_Input_Rising_T4In_En();
 *    GPT12E_T4_T4In_Sel(1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_T4In_Sel(uint16 ist4in)
{
  Field_Mod16(&GPT12E->PISEL.reg, (uint16)GPT12E_PISEL_IST4IN_Pos, (uint16)GPT12E_PISEL_IST4IN_Msk,  ist4in);
}

/** \brief selects Input for T4EUD.
 *
 * \param ist4eud Input Select for T4EUD.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables controlling Count direction by the external input T4EUDB.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T4_UpDownCount_Ext_En();
 *    GPT12E_T4_T4EUD_Sel(1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_T4EUD_Sel(uint16 ist4eud)
{
  Field_Mod16(&GPT12E->PISEL.reg, (uint16)GPT12E_PISEL_IST4EUD_Pos, (uint16)GPT12E_PISEL_IST4EUD_Msk, ist4eud);
}

/****************************************************************************/
/* GPT2   *******************************************************************/
/****************************************************************************/
/** \brief selects GPT2 Block Prescaler.
 *
 * \param bps2 GPT2 Clock Prescaler
 *
 * \brief <b>Example</b><br>
 * \brief This example sets clock for block GPT2 to fGPT/2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     GPT12E_GPT2_Clk_Prescaler_Sel(0x0001);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_GPT2_Clk_Prescaler_Sel(uint16 bps2)
{
  Field_Mod16(&GPT12E->T6CON.reg, (uint16)GPT12E_T6CON_BPS2_Pos, (uint16)GPT12E_T6CON_BPS2_Msk, (bps2 ^ (uint16)1));
}

/** \brief reads GPT2 Block Prescaler.
 *
 * \return GPT2 Block Prescaler
 *
 * \brief <b>Example</b><br>
 * \brief This example reads clock for block GPT2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint16 pres;
 *
 *    pres =  GPT12E_GPT2_Clk_Prescaler_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE uint16 GPT12E_GPT2_Clk_Prescaler_Get(void)
{
  return ( u16_Field_Rd16(&GPT12E->T6CON.reg, (uint16)GPT12E_T6CON_BPS2_Pos, (uint16)GPT12E_T6CON_BPS2_Msk) ^ (uint16)1 );
}

/****************************************************************************/
/* Timer5 *******************************************************************/
/****************************************************************************/
/** \brief selects T5 Timer Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T5 Timer Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_Mode_Timer_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_Mode_Timer_Sel(void)
{
  Field_Mod16(&GPT12E->T5CON.reg, (uint16)GPT12E_T5CON_T5M_Pos, (uint16)GPT12E_T5CON_T5M_Msk, 0u);
}

/** \brief selects T5 Counter Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T5 Counter Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_Mode_Counter_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_Mode_Counter_Sel(void)
{
  Field_Mod16(&GPT12E->T5CON.reg, (uint16)GPT12E_T5CON_T5M_Pos, (uint16)GPT12E_T5CON_T5M_Msk, 1u);
}

/** \brief selects T5 Gated low Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T5 Gated Timer Mode with gate active low.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_Mode_Gated_Timer_Low_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_Mode_Gated_Timer_Low_Sel(void)
{
  Field_Mod16(&GPT12E->T5CON.reg, (uint16)GPT12E_T5CON_T5M_Pos, (uint16)GPT12E_T5CON_T5M_Msk, 2u);
}

/** \brief selects T5 Gated high Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T5 Gated Timer Mode with gate active high.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_Mode_Gated_Timer_High_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_Mode_Gated_Timer_High_Sel(void)
{
  Field_Mod16(&GPT12E->T5CON.reg, (uint16)GPT12E_T5CON_T5M_Pos, (uint16)GPT12E_T5CON_T5M_Msk, 3u);
}

/** \brief selects T5 Timer Mode Parameter.
 *
 * \param t5i T5 Input Parameter Sel
 *
 * \brief <b>Example</b><br>
 * \brief This example sets T5 Timer Mode Parameter to 0x01.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_Mode_Timer_Sel();
 *    GPT12E_T5_Mode_Timer_Clk_Prescaler_Sel(0x01);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_Mode_Timer_Clk_Prescaler_Sel(uint16 t5i)
{
  Field_Mod16(&GPT12E->T5CON.reg, (uint16)GPT12E_T5CON_T5I_Pos, (uint16)GPT12E_T5CON_T5I_Msk, t5i);
}

/** \brief selects T5 Gated Timer Mode Parameter.
 *
 * \param t5i T5 Input Parameter Sel
 *
 * \brief <b>Example</b><br>
 * \brief This example sets selects T5 Gated Timer Mode Parameter to 0x01.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_Mode_Gated_Timer_High_Sel();
 *    GPT12E_T5_Mode_Gated_Timer_Clk_Prescaler_Sel(0x01);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_Mode_Gated_Timer_Clk_Prescaler_Sel(uint16 t5i)
{
  Field_Mod16(&GPT12E->T5CON.reg, (uint16)GPT12E_T5CON_T5I_Pos, (uint16)GPT12E_T5CON_T5I_Msk, t5i);
}

/** \brief selects T5In as T5 Counter Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T5In as T5 Counter Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_Mode_Counter_Sel();
 *    GPT12E_T5_Mode_Counter_Input_T5In_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_Mode_Counter_Input_T5In_Sel(void)
{
  Field_Mod16(&GPT12E->T5CON.reg, 2u, 4u, 0u);
}

/** \brief selects Rising Edge on T5In as T5 Counter Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Rising Edge on T5In as T5 Counter Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_Mode_Counter_Sel();
 *    GPT12E_T5_Mode_Counter_Input_Rising_T5In_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_Mode_Counter_Input_Rising_T5In_Sel(void)
{
  Field_Mod16(&GPT12E->T5CON.reg, 0u, 1u, 1u);
}

/** \brief selects Falling Edge on T5In as T5 Counter Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Falling Edge on T5In as T5 Counter Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_Mode_Counter_Sel();
 *    GPT12E_T5_Mode_Counter_Input_Falling_T5In_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_Mode_Counter_Input_Falling_T5In_Sel(void)
{
  Field_Mod16(&GPT12E->T5CON.reg, 1u, 2u, 1u);
}

/** \brief selects Any Edge on T5In as T5 Counter Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Any Edge on T5In as T5 Counter Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_Mode_Counter_Sel();
 *    GPT12E_T5_Mode_Counter_Input_Any_T5In_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_Mode_Counter_Input_Any_T5In_Sel(void)
{
  Field_Mod16(&GPT12E->T5CON.reg, 0u, 3u, 3u);
}

/** \brief selects T6OTL as T5 Counter Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T6OTL as T5 Counter Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_Mode_Counter_Sel();
 *    GPT12E_T5_Mode_Counter_Input_T6Out_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_Mode_Counter_Input_T6Out_Sel(void)
{
  Field_Mod16(&GPT12E->T5CON.reg, 2u, 4u, 1u);
}

/** \brief enables Rising Edge on T6OTL as T5 Counter Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Rising Edge on T6OTL as T5 Counter Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_Mode_Counter_Sel();
 *    GPT12E_T5_Mode_Counter_Input_Rising_T6Out_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_Mode_Counter_Input_Rising_T6Out_En(void)
{
  Field_Mod16(&GPT12E->T5CON.reg, 0u, 1u, 1u);
}

/** \brief disables Rising Edge on T6OTL as T5 Counter Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Rising Edge on T6OTL as T5 Counter Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_Mode_Counter_Sel();
 *    GPT12E_T5_Mode_Counter_Input_Rising_T6Out_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_Mode_Counter_Input_Rising_T6Out_Dis(void)
{
  Field_Mod16(&GPT12E->T5CON.reg, 0u, 1u, 0u);
}

/** \brief enables Falling Edge on T6OTL as T5 Counter Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Falling Edge on T6OTL as T5 Counter Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_Mode_Counter_Sel();
 *    GPT12E_T5_Mode_Counter_Input_Falling_T6Out_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_Mode_Counter_Input_Falling_T6Out_En(void)
{
  Field_Mod16(&GPT12E->T5CON.reg, 1u, 2u, 1u);
}

/** \brief disables Falling Edge on T6OTL as T5 Counter Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Falling Edge on T6OTL as T5 Counter Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_Mode_Counter_Sel();
 *    GPT12E_T5_Mode_Counter_Input_Falling_T6Out_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_Mode_Counter_Input_Falling_T6Out_Dis(void)
{
  Field_Mod16(&GPT12E->T5CON.reg, 1u, 2u, 0u);
}

/** \brief enables T5 Capture Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables T5 Capture Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_Capture_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_Capture_En(void)
{
  Field_Mod16(&GPT12E->T5CON.reg, (uint16)GPT12E_T5CON_T5SC_Pos, (uint16)GPT12E_T5CON_T5SC_Msk, 1u);
}

/** \brief disables T5 Capture Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables T5 Capture Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_Capture_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_Capture_Dis(void)
{
  Field_Mod16(&GPT12E->T5CON.reg, (uint16)GPT12E_T5CON_T5SC_Pos, (uint16)GPT12E_T5CON_T5SC_Msk, 0u);
}

/** \brief selects CapIn as T5 Capture Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects CapIn as T5 Capture Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_Capture_En();
 *    GPT12E_T5_Capture_Trig_CapIn_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_Capture_Trig_CapIn_Sel(void)
{
  Field_Mod16(&GPT12E->T5CON.reg, (uint16)GPT12E_T5CON_CT3_Pos, (uint16)GPT12E_T5CON_CT3_Msk, 1u);
}

/** \brief enables Rising Edge on CapIn as T5 Capture Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Rising Edge on CapIn as T5 Capture Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_Capture_En();
 *    GPT12E_T5_Capture_Trig_CapIn_Sel();
 *    GPT12E_T5_Capture_Trig_Rising_CapIn_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_Capture_Trig_Rising_CapIn_En(void)
{
  Field_Mod16(&GPT12E->T5CON.reg, 12u, ((uint16)1u << 12u), 1u);
}

/** \brief disables Rising Edge on CapIn as T5 Capture Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Rising Edge on CapIn as T5 Capture Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_Capture_En();
 *    GPT12E_T5_Capture_Trig_CapIn_Sel();
 *    GPT12E_T5_Capture_Trig_Rising_CapIn_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_Capture_Trig_Rising_CapIn_Dis(void)
{
  Field_Mod16(&GPT12E->T5CON.reg, 12u, ((uint16)1u << 12u), 0u);
}

/** \brief enables Falling Edge on CapIn as T5 Capture Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Falling Edge on CapIn as T5 Capture Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_Capture_En();
 *    GPT12E_T5_Capture_Trig_CapIn_Sel();
 *    GPT12E_T5_Capture_Trig_Falling_CapIn_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_Capture_Trig_Falling_CapIn_En(void)
{
  Field_Mod16(&GPT12E->T5CON.reg, 13u, ((uint16)1u << 13u), 1u);
}

/** \brief disables Falling Edge on CapIn as T5 Capture Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Falling Edge on CapIn as T5 Capture Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_Capture_En();
 *    GPT12E_T5_Capture_Trig_CapIn_Sel();
 *    GPT12E_T5_Capture_Trig_Falling_CapIn_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_Capture_Trig_Falling_CapIn_Dis(void)
{
  Field_Mod16(&GPT12E->T5CON.reg, 13u, ((uint16)1u << 13u), 0u);
}

/** \brief selects T3In and/or T3EUD as T5 Capture Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T3In and/or T3EUD as T5 Capture Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_Capture_En();
 *    GPT12E_T5_Capture_Trig_T3In_T3EUD_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_Capture_Trig_T3In_T3EUD_Sel(void)
{
  Field_Mod16(&GPT12E->T5CON.reg, (uint16)GPT12E_T5CON_CT3_Pos, (uint16)GPT12E_T5CON_CT3_Msk, 0u);
}

/** \brief enables Any Edge on T3In as T5 Capture Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Any Edge on T3In as T5 Capture Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_Capture_En();
 *    GPT12E_T5_Capture_Trig_T3In_T3EUD_Sel();
 *    GPT12E_T5_Capture_Trig_Any_T3In_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_Capture_Trig_Any_T3In_En(void)
{
  Field_Mod16(&GPT12E->T5CON.reg, 12u, ((uint16)1u << 12u), 1u);
}

/** \brief disables Any Edge on T3In as T5 Capture Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Any Edge on T3In as T5 Capture Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_Capture_En();
 *    GPT12E_T5_Capture_Trig_T3In_T3EUD_Sel();
 *    GPT12E_T5_Capture_Trig_Any_T3In_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_Capture_Trig_Any_T3In_Dis(void)
{
  Field_Mod16(&GPT12E->T5CON.reg, 12u, ((uint16)1u << 12u), 0u);
}

/** \brief enables Any Edge on T3EUD as T5 Capture Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Any Edge on T3EUD as T5 Capture Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_Capture_En();
 *    GPT12E_T5_Capture_Trig_T3In_T3EUD_Sel();
 *    GPT12E_T5_Capture_Trig_Any_T3EUD_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_Capture_Trig_Any_T3EUD_En(void)
{
  Field_Mod16(&GPT12E->T5CON.reg, 13u, ((uint16)1u << 13u), 1u);
}

/** \brief disables Any Edge on T3EUD as T5 Capture Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Any Edge on T3EUD as T5 Capture Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_Capture_En();
 *    GPT12E_T5_Capture_Trig_T3In_T3EUD_Sel();
 *    GPT12E_T5_Capture_Trig_Any_T3EUD_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_Capture_Trig_Any_T3EUD_Dis(void)
{
  Field_Mod16(&GPT12E->T5CON.reg, 13u, ((uint16)1u << 13u), 0u);
}

/** \brief enables clearing T5 on a Capture Event.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables clearing T5 on a Capture Event.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_Capture_En();
 *    GPT12E_T5_Cleared_On_Capture_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_Cleared_On_Capture_En(void)
{
  Field_Mod16(&GPT12E->T5CON.reg, (uint16)GPT12E_T5CON_T5CLR_Pos, (uint16)GPT12E_T5CON_T5CLR_Msk, 1u);
}

/** \brief disables clearing T5 on a Capture Event.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables clearing T5 on a Capture Event.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_Capture_En();
 *    GPT12E_T5_Cleared_On_Capture_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_Cleared_On_Capture_Dis(void)
{
  Field_Mod16(&GPT12E->T5CON.reg, (uint16)GPT12E_T5CON_T5CLR_Pos, (uint16)GPT12E_T5CON_T5CLR_Msk, 0u);
}

/** \brief reads Current T5 Capture Value.
 *
 * \return T5 Capture Value
 *
 * \brief <b>Example</b><br>
 * \brief This example reads Current T5 Capture Value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint16 cap;
 *
 *    GPT12E_T5_Capture_En();
 *    cap = GPT12E_T5_Capture_Value_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE uint16 GPT12E_T5_Capture_Value_Get(void)
{
  return ( u16_Field_Rd16(&GPT12E->CAPREL.reg, (uint16)GPT12E_CAPREL_CAPREL_Pos, (uint16)GPT12E_CAPREL_CAPREL_Msk) );
}

/** \brief starts Timer T5.
 *
 * \brief <b>Example</b><br>
 * \brief This example starts Timer T5.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_Start_by_T6_Dis();
 *    GPT12E_T5_Start();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_Start(void)
{
  Field_Mod16(&GPT12E->T5CON.reg, (uint16)GPT12E_T5CON_T5R_Pos, (uint16)GPT12E_T5CON_T5R_Msk,  1u);
}

/** \brief stops Timer T5.
 *
 * \brief <b>Example</b><br>
 * \brief This example stops Timer T5.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_Start_by_T6_Dis();
 *    GPT12E_T5_Stop();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_Stop(void)
{
  Field_Mod16(&GPT12E->T5CON.reg, (uint16)GPT12E_T5CON_T5R_Pos, (uint16)GPT12E_T5CON_T5R_Msk,  0u);
}

/** \brief disables controlling Timer T5 by the run bit T6R of core timer T6.
 *
 * \brief <b>Example</b><br>
 * \brief This example starts Timer T5.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_Start_by_T6_Dis();
 *    GPT12E_T5_Start();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_Start_by_T6_Dis(void)
{
  Field_Mod16(&GPT12E->T5CON.reg, (uint16)GPT12E_T5CON_T5RC_Pos, (uint16)GPT12E_T5CON_T5RC_Msk, 0u);
}

/** \brief enables controlling Timer T5 by the run bit T6R of core timer T6.
 *
 * \brief <b>Example</b><br>
 * \brief This example starts Timer T5 by setting T6R.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_Start_by_T6_En();
 *    GPT12E_T6_Start();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_Start_by_T6_En(void)
{
  Field_Mod16(&GPT12E->T5CON.reg, (uint16)GPT12E_T5CON_T5RC_Pos, (uint16)GPT12E_T5CON_T5RC_Msk, 1u);
}

/** \brief selects Timer T5 counts down.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Timer T5 counts down (internally).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_UpDownCount_Ext_Dis();
 *    GPT12E_T5_DownCount_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_DownCount_Sel(void)
{
  Field_Mod16(&GPT12E->T5CON.reg, (uint16)GPT12E_T5CON_T5UD_Pos, (uint16)GPT12E_T5CON_T5UD_Msk,  1u);
}

/** \brief selects Timer T5 counts up.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Timer T5 counts up (internally).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_UpDownCount_Ext_Dis();
 *    GPT12E_T5_UpCount_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_UpCount_Sel(void)
{
  Field_Mod16(&GPT12E->T5CON.reg, (uint16)GPT12E_T5CON_T5UD_Pos, (uint16)GPT12E_T5CON_T5UD_Msk,  0u);
}

/** \brief enables controlling Count direction by external input (T5EUD).
 *
 * \brief <b>Example</b><br>
 * \brief This example enables controlling Count direction by external input (T5EUD).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_UpDownCount_Ext_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_UpDownCount_Ext_En(void)
{
  Field_Mod16(&GPT12E->T5CON.reg, (uint16)GPT12E_T5CON_T5UDE_Pos, (uint16)GPT12E_T5CON_T5UDE_Msk, 1u);
}

/** \brief disables controlling Count direction by external input (T5EUD).
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Timer T5 counts up (internally).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_UpDownCount_Ext_Dis();
 *    GPT12E_T5_UpCount_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_UpDownCount_Ext_Dis(void)
{
  Field_Mod16(&GPT12E->T5CON.reg, (uint16)GPT12E_T5CON_T5UDE_Pos, (uint16)GPT12E_T5CON_T5UDE_Msk, 0u);
}

/** \brief reads Timer T5 Value.
 *
 * \return T5 Value
 *
 * \brief <b>Example</b><br>
 * \brief This example reads Timer T5 Value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint16 timer;
 *
 *    timer = GPT12E_T5_Value_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE uint16 GPT12E_T5_Value_Get(void)
{
  return ( u16_Field_Rd16(&GPT12E->T5.reg, (uint16)GPT12E_T5_T5_Pos, (uint16)GPT12E_T5_T5_Msk) );
}

/** \brief sets Timer T5 Value.
 *
 * \param t5 T5 Value
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Timer T5 Value to 5000.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_Value_Set(0x1388);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_Value_Set(uint16 t5)
{
  Field_Wrt16(&GPT12E->T5.reg, (uint16)GPT12E_T5_T5_Pos, (uint16)GPT12E_T5_T5_Msk, t5);
}

/** \brief selects Input for T2IN.
 *
 * \param ist5in Input Select for T2IN
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Rising Edge Counter Mode on T2INB Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_Mode_Counter_Sel();
 *    GPT12E_T5_Mode_Counter_Input_Any_T5In_Sel();
 *    GPT12E_T5_T5In_Sel(1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_T5In_Sel(uint16 ist5in)
{
  Field_Mod16(&GPT12E->PISEL.reg, (uint16)GPT12E_PISEL_IST5IN_Pos, (uint16)GPT12E_PISEL_IST5IN_Msk, ist5in  );
}

/** \brief selects Input for T5EUD.
 *
 * \param ist5eud Input Select for T5EUD
 *
 * \brief <b>Example</b><br>
 * \brief This example enables controlling Count direction by the external input T5EUDB.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_UpDownCount_Ext_En();
 *    GPT12E_T5_T5EUD_Sel(1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_T5EUD_Sel(uint16 ist5eud)
{
  Field_Mod16(&GPT12E->PISEL.reg, (uint16)GPT12E_PISEL_IST5EUD_Pos, (uint16)GPT12E_PISEL_IST5EUD_Msk, ist5eud);
}

/****************************************************************************/
/* Timer6 *******************************************************************/
/****************************************************************************/
/** \brief selects T6 Timer Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T6 Timer Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T6_Mode_Timer_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T6_Mode_Timer_Sel(void)
{
  Field_Mod16(&GPT12E->T6CON.reg, (uint16)GPT12E_T6CON_T6M_Pos, (uint16)GPT12E_T6CON_T6M_Msk, 0u);
}

/** \brief selects T6 Counter Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T6 Counter Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T6_Mode_Counter_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T6_Mode_Counter_Sel(void)
{
  Field_Mod16(&GPT12E->T6CON.reg, (uint16)GPT12E_T6CON_T6M_Pos, (uint16)GPT12E_T6CON_T6M_Msk, 1u);
}

/** \brief selects T6 Gated low Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T6 Gated Timer Mode with gate active low.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T6_Mode_Gated_Timer_Low_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T6_Mode_Gated_Timer_Low_Sel(void)
{
  Field_Mod16(&GPT12E->T6CON.reg, (uint16)GPT12E_T6CON_T6M_Pos, (uint16)GPT12E_T6CON_T6M_Msk, 2u);
}

/** \brief selects T6 Gated high Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T6 Gated Timer Mode with gate active high.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T6_Mode_Gated_Timer_High_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T6_Mode_Gated_Timer_High_Sel(void)
{
  Field_Mod16(&GPT12E->T6CON.reg, (uint16)GPT12E_T6CON_T6M_Pos, (uint16)GPT12E_T6CON_T6M_Msk, 3u);
}

/** \brief selects T6 Timer Mode Parameter.
 *
 * \param t6i T6 Input Parameter Sel
 *
 * \brief <b>Example</b><br>
 * \brief This example sets T6 Timer Mode Parameter to 0x01.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T6_Mode_Timer_Sel();
 *    GPT12E_T6_Mode_Timer_Clk_Prescaler_Sel(0x01);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T6_Mode_Timer_Clk_Prescaler_Sel(uint16 t6i)
{
  Field_Mod16(&GPT12E->T6CON.reg, (uint16)GPT12E_T6CON_T6I_Pos, (uint16)GPT12E_T6CON_T6I_Msk, t6i);
}

/** \brief selects T6 Gated Timer Mode Parameter.
 *
 * \param t6i T6 Input Parameter Sel
 *
 * \brief <b>Example</b><br>
 * \brief This example sets selects T6 Gated Timer Mode Parameter to 0x01.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T6_Mode_Gated_Timer_High_Sel();
 *    GPT12E_T6_Mode_Gated_Timer_Clk_Prescaler_Sel(0x01);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T6_Mode_Gated_Timer_Clk_Prescaler_Sel(uint16 t6i)
{
  Field_Mod16(&GPT12E->T6CON.reg, (uint16)GPT12E_T6CON_T6I_Pos, (uint16)GPT12E_T6CON_T6I_Msk, t6i);
}

/** \brief selects T6In as T6 Counter Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T6In as T6 Counter Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T6_Mode_Counter_Sel();
 *    GPT12E_T6_Mode_Counter_Input_T6In_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T6_Mode_Counter_Input_T6In_Sel(void)
{
  Field_Mod16(&GPT12E->T6CON.reg, (uint16)2u, (uint16)4u, 0u);
}

/** \brief selects Rising Edge on T6In as T6 Counter Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Rising Edge on T6n as T6 Counter Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T6_Mode_Counter_Sel();
 *    GPT12E_T6_Mode_Counter_Input_Rising_T6In_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T6_Mode_Counter_Input_Rising_T6In_Sel(void)
{
  Field_Mod16(&GPT12E->T6CON.reg, (uint16)0u, (uint16)1u, 1u);
}

/** \brief selects Falling Edge on T6In as T6 Counter Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Falling Edge on T6In as T6 Counter Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T6_Mode_Counter_Sel();
 *    GPT12E_T6_Mode_Counter_Input_Falling_T6In_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T6_Mode_Counter_Input_Falling_T6In_Sel(void)
{
  Field_Mod16(&GPT12E->T6CON.reg, (uint16)1u, (uint16)2u, 1u);
}

/** \brief selects Any Edge on T6In as T6 Counter Mode Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Any Edge on T6In as T6 Counter Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T6_Mode_Counter_Sel();
 *    GPT12E_T6_Mode_Counter_Input_Any_T6In_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T6_Mode_Counter_Input_Any_T6In_Sel(void)
{
  Field_Mod16(&GPT12E->T6CON.reg, (uint16)0u, (uint16)3u, 3u);
}

/** \brief enables T6 Reload Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables T6 Reload Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T6_Reload_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T6_Reload_En(void)
{
  Field_Mod16(&GPT12E->T6CON.reg,  (uint16)GPT12E_T6CON_T6SR_Pos, (uint16)GPT12E_T6CON_T6SR_Msk,    1u);
}

/** \brief disables T6 Reload Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables T6 Reload Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T6_Reload_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T6_Reload_Dis(void)
{
  Field_Mod16(&GPT12E->T6CON.reg,  (uint16)GPT12E_T6CON_T6SR_Pos, (uint16)GPT12E_T6CON_T6SR_Msk,    0u);
}

/** \brief sets Current T6 Reload Value.
 *
 * \param rl T6 Reload Value
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Current T6 Reload Value to 5000.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T6_Reload_En();
 *    GPT12E_T6_Reload_Value_Set(0x1388);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T6_Reload_Value_Set(uint16 rl)
{
  Field_Mod16(&GPT12E->CAPREL.reg, (uint16)GPT12E_CAPREL_CAPREL_Pos, (uint16)GPT12E_CAPREL_CAPREL_Msk, rl);
}

/** \brief enables clearing T6 on a Capture Event.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables clearing T6 on a Capture Event.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T6_Reload_En();
 *    GPT12E_T6_On_Capture_Cleared_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T6_On_Capture_Cleared_En(void)
{
  Field_Mod16(&GPT12E->T6CON.reg, (uint16)GPT12E_T6CON_T6CLR_Pos, (uint16)GPT12E_T6CON_T6CLR_Msk, 1u);
}

/** \brief disables clearing T6 on a Capture Event.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables clearing T6 on a Capture Event.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T6_Reload_En();
 *    GPT12E_T6_On_Capture_Cleared_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T6_On_Capture_Cleared_Dis(void)
{
  Field_Mod16(&GPT12E->T6CON.reg, (uint16)GPT12E_T6CON_T6CLR_Pos, (uint16)GPT12E_T6CON_T6CLR_Msk, 0u);
}

/** \brief starts Timer T6.
 *
 * \brief <b>Example</b><br>
 * \brief This example starts Timer T6.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T6_Start();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T6_Start(void)
{
  Field_Mod16(&GPT12E->T6CON.reg, (uint16)GPT12E_T6CON_T6R_Pos, (uint16)GPT12E_T6CON_T6R_Msk,    1u);
}

/** \brief stops Timer T6.
 *
 * \brief <b>Example</b><br>
 * \brief This example stops Timer T6.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T6_Stop();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T6_Stop(void)
{
  Field_Mod16(&GPT12E->T6CON.reg, (uint16)GPT12E_T6CON_T6R_Pos, (uint16)GPT12E_T6CON_T6R_Msk,    0u);
}

/** \brief enables Timer T6 Overflow/Underflow Output.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Timer T6 Overflow/Underflow Output.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T6_Output_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T6_Output_En(void)
{
  Field_Mod16(&GPT12E->T6CON.reg, (uint16)GPT12E_T6CON_T6OE_Pos, (uint16)GPT12E_T6CON_T6OE_Msk,  1u);
}

/** \brief disables Timer T6 Overflow/Underflow Output.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Timer T6 Overflow/Underflow Output.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T6_Output_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T6_Output_Dis(void)
{
  Field_Mod16(&GPT12E->T6CON.reg, (uint16)GPT12E_T6CON_T6OE_Pos, (uint16)GPT12E_T6CON_T6OE_Msk,  0u);
}

/** \brief sets Timer T6 Overflow Toggle Latch.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Timer T6 Overflow Toggle Latch.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T6_Output_En();
 *    GPT12E_T6_Output_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T6_Output_Set(void)
{
  Field_Mod16(&GPT12E->T6CON.reg, (uint16)GPT12E_T6CON_T6OTL_Pos, (uint16)GPT12E_T6CON_T6OTL_Msk, 1u);
}

/** \brief clears Timer T6 Overflow Toggle Latch.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Timer T6 Overflow Toggle Latch.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T6_Output_En();
 *    GPT12E_T6_Output_Rst();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T6_Output_Rst(void)
{
  Field_Mod16(&GPT12E->T6CON.reg, (uint16)GPT12E_T6CON_T6OTL_Pos, (uint16)GPT12E_T6CON_T6OTL_Msk, 0u);
}

/** \brief selects Timer T6 counts down.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Timer T6 counts down (internally).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T6_UpDownCount_Ext_Dis();
 *    GPT12E_T6_DownCount_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T6_DownCount_Sel(void)
{
  Field_Mod16(&GPT12E->T6CON.reg, (uint16)GPT12E_T6CON_T6UD_Pos, (uint16)GPT12E_T6CON_T6UD_Msk,  1u);
}

/** \brief selects Timer T6 counts up.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Timer T6 counts up (internally).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T6_UpDownCount_Ext_Dis();
 *    GPT12E_T6_UpCount_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T6_UpCount_Sel(void)
{
  Field_Mod16(&GPT12E->T6CON.reg, (uint16)GPT12E_T6CON_T6UD_Pos, (uint16)GPT12E_T6CON_T6UD_Msk,  0u);
}

/** \brief enables controlling Count direction by external input (T6EUD).
 *
 * \brief <b>Example</b><br>
 * \brief This example enables controlling Count direction by external input (T6EUD).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T6_UpDownCount_Ext_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T6_UpDownCount_Ext_En(void)
{
  Field_Mod16(&GPT12E->T6CON.reg, (uint16)GPT12E_T6CON_T6UDE_Pos, (uint16)GPT12E_T6CON_T6UDE_Msk, 1u);
}

/** \brief disables controlling Count direction by external input (T6EUD).
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Timer T6 counts up (internally).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T6_UpDownCount_Ext_Dis();
 *    GPT12E_T6_UpCount_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T6_UpDownCount_Ext_Dis(void)
{
  Field_Mod16(&GPT12E->T6CON.reg, (uint16)GPT12E_T6CON_T6UDE_Pos, (uint16)GPT12E_T6CON_T6UDE_Msk, 0u);
}

/** \brief reads Timer T6 Value.
 *
 * \return T6 Value
 *
 * \brief <b>Example</b><br>
 * \brief This example reads Timer T6 Value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint16 timer;
 *
 *    timer = GPT12E_T6_Value_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE uint16 GPT12E_T6_Value_Get(void)
{
  return ( u16_Field_Rd16(&GPT12E->T6.reg, (uint16)GPT12E_T6_T6_Pos, (uint16)GPT12E_T6_T6_Msk) );
}

/** \brief sets Timer T6 Value.
 *
 * \param t6 T6 Value
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Timer T6 Value to 5000.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T6_Value_Set(0x1388);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T6_Value_Set(uint16 t6)
{
  Field_Wrt16(&GPT12E->T6.reg, (uint16)GPT12E_T6_T6_Pos, (uint16)GPT12E_T6_T6_Msk, t6);
}

/** \brief selects Input for T6IN.
 *
 * \param ist6in Input Select for T6IN
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Rising Edge Counter Mode on T6INB Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T6_Mode_Counter_Sel();
 *    GPT12E_T6_Mode_Counter_Input_Any_T6In_Sel();
 *    GPT12E_T6_T6In_Sel(1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T6_T6In_Sel(uint16 ist6in)
{
  Field_Mod16(&GPT12E->PISEL.reg, (uint16)GPT12E_PISEL_IST6IN_Pos, (uint16)GPT12E_PISEL_IST6IN_Msk,  ist6in );
}

/** \brief selects Input for T6EUD.
 *
 * \param ist6eud Input Select for T6EUD
 *
 * \brief <b>Example</b><br>
 * \brief This example enables controlling Count direction by the external input T6EUDB.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T6_UpDownCount_Ext_En();
 *    GPT12E_T6_T6EUD_Sel(1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T6_T6EUD_Sel(uint16 ist6eud)
{
  Field_Mod16(&GPT12E->PISEL.reg, (uint16)GPT12E_PISEL_IST6EUD_Pos, (uint16)GPT12E_PISEL_IST6EUD_Msk, ist6eud);
}

/****************************************************************************/
/* CAPREL *******************************************************************/
/****************************************************************************/
/** \brief selects CAPIN.
 *
 * \param iscapin Input Select for CAPIN
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Falling Edge on CAPINB as T5 Capture Mode Input.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    GPT12E_T5_Capture_En();
 *    GPT12E_T5_Capture_Trig_CapIn_Sel();
 *    GPT12E_T5_Capture_Trig_Falling_CapIn_En();
 *    GPT12E_CapRel_CAPIn_Sel(1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_CapRel_CAPIn_Sel(uint16 iscapin)
{
  Field_Mod16(&GPT12E->PISEL.reg, (uint16)GPT12E_PISEL_ISCAPIN_Pos, (uint16)GPT12E_PISEL_ISCAPIN_Msk, iscapin);
}

/****************************************************************************/
/* Interrupt ****************************************************************/
/****************************************************************************/
/** \brief reads GPT Module 1 Timer 2 interrupt Status.
 *
 * \return T2 interrupt Status
 *
 * \brief <b>Example</b><br>
 * \brief This example checks the GPT Module 1 Timer 2 interrupt Status and clears it.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     GPT12E_T2_Int_En();
 *     if (GPT12E_T2_Int_Sts() == (uint8)1)
 *     {
 *         GPT12E_T2_Int_Clr();
 *     }
 *     GPT12E_T2_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE uint8 GPT12E_T2_Int_Sts(void)
{
  return ( u1_Field_Rd8(&SCU->GPT12IRC.reg, (uint8)SCU_GPT12IRC_T2_Pos, (uint8)SCU_GPT12IRC_T2_Msk) );
}

/** \brief reads GPT Module 1 Timer 3 interrupt Status.
 *
 * \return T3 interrupt Status
 *
 * \brief <b>Example</b><br>
 * \brief This example checks the GPT Module 1 Timer 3 interrupt Status and clears it.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     GPT12E_T3_Int_En();
 *     if (GPT12E_T3_Int_Sts() == (uint8)1)
 *     {
 *         GPT12E_T3_Int_Clr();
 *     }
 *     GPT12E_T3_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE uint8 GPT12E_T3_Int_Sts(void)
{
  return ( u1_Field_Rd8(&SCU->GPT12IRC.reg, (uint8)SCU_GPT12IRC_T3_Pos, (uint8)SCU_GPT12IRC_T3_Msk) );
}

/** \brief reads GPT Module 1 Timer 4 interrupt Status.
 *
 * \return T4 interrupt Status
 *
 * \brief <b>Example</b><br>
 * \brief This example checks the GPT Module 1 Timer 4 interrupt Status and clears it.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     GPT12E_T4_Int_En();
 *     if (GPT12E_T4_Int_Sts() == (uint8)1)
 *     {
 *         GPT12E_T4_Int_Clr();
 *     }
 *     GPT12E_T4_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE uint8 GPT12E_T4_Int_Sts(void)
{
  return ( u1_Field_Rd8(&SCU->GPT12IRC.reg, (uint8)SCU_GPT12IRC_T4_Pos, (uint8)SCU_GPT12IRC_T4_Msk) );
}

/** \brief reads GPT Module 2 Timer 5 interrupt Status.
 *
 * \return T5 interrupt Status
 *
 * \brief <b>Example</b><br>
 * \brief This example checks the GPT Module 2 Timer 5 interrupt Status and clears it.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     GPT12E_T5_Int_En();
 *     if (GPT12E_T5_Int_Sts() == (uint8)1)
 *     {
 *         GPT12E_T5_Int_Clr();
 *     }
 *     GPT12E_T5_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE uint8 GPT12E_T5_Int_Sts(void)
{
  return ( u1_Field_Rd8(&SCU->GPT12IRC.reg, (uint8)SCU_GPT12IRC_T5_Pos, (uint8)SCU_GPT12IRC_T5_Msk) );
}

/** \brief reads GPT Module 2 Timer 6 interrupt Status.
 *
 * \return T6 interrupt Status
 *
 * \brief <b>Example</b><br>
 * \brief This example checks the GPT Module 2 Timer 6 interrupt Status and clears it.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     GPT12E_T6_Int_En();
 *     if (GPT12E_T6_Int_Sts() == (uint8)1)
 *     {
 *         GPT12E_T6_Int_Clr();
 *     }
 *     GPT12E_T6_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE uint8 GPT12E_T6_Int_Sts(void)
{
  return ( u1_Field_Rd8(&SCU->GPT12IRC.reg, (uint8)SCU_GPT12IRC_T6_Pos, (uint8)SCU_GPT12IRC_T6_Msk) );
}

/** \brief reads GPT Module 1 Capture Reload interrupt Status.
 *
 * \return Capture Reload interrupt Status
 *
 * \brief <b>Example</b><br>
 * \brief This example checks the GPT Module 1 Capture Reload interrupt Status and clears it.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     GPT12E_CapRel_Int_En();
 *     if (GPT12E_CapRel_Int_Sts() == (uint8)1)
 *     {
 *         GPT12E_CapRel_Int_Clr();
 *     }
 *     GPT12E_CapRel_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE uint8 GPT12E_CapRel_Int_Sts(void)
{
  return ( u1_Field_Rd8(&SCU->GPT12IRC.reg, (uint8)SCU_GPT12IRC_CR_Pos, (uint8)SCU_GPT12IRC_CR_Msk) );
}

/* GPT12E Interrupt Clear Macros */
/** \brief clears GPT Module 1 Timer 2 interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the GPT Module 1 Timer 2 interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     GPT12E_T2_Int_En();
 *     if (GPT12E_T2_Int_Sts() == (uint8)1)
 *     {
 *         GPT1_T2_CALLBACK();
 *         GPT12E_T2_Int_Clr();
 *     }
 *     GPT12E_T2_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Int_Clr(void)
{
  Field_Wrt8(&SCU->GPT12ICLR.reg, (uint8)SCU_GPT12ICLR_T2C_Pos, (uint8)SCU_GPT12ICLR_T2C_Msk, 1u);
}

/** \brief clears GPT Module 1 Timer 3 interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the GPT Module 1 Timer 3 interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     GPT12E_T3_Int_En();
 *     if (GPT12E_T3_Int_Sts() == (uint8)1)
 *     {
 *         GPT1_T3_CALLBACK();
 *         GPT12E_T3_Int_Clr();
 *     }
 *     GPT12E_T3_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T3_Int_Clr(void)
{
  Field_Wrt8(&SCU->GPT12ICLR.reg, (uint8)SCU_GPT12ICLR_T3C_Pos, (uint8)SCU_GPT12ICLR_T3C_Msk, 1u);
}

/** \brief clears GPT Module 1 Timer 4 interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the GPT Module 1 Timer 4 interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     GPT12E_T4_Int_En();
 *     if (GPT12E_T4_Int_Sts() == (uint8)1)
 *     {
 *         GPT1_T4_CALLBACK();
 *         GPT12E_T4_Int_Clr();
 *     }
 *     GPT12E_T4_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Int_Clr(void)
{
  Field_Wrt8(&SCU->GPT12ICLR.reg, (uint8)SCU_GPT12ICLR_T4C_Pos, (uint8)SCU_GPT12ICLR_T4C_Msk, 1u);
}

/** \brief clears GPT Module 2 Timer 5 interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the GPT Module 2 Timer 5 interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     GPT12E_T5_Int_En();
 *     if (GPT12E_T5_Int_Sts() == (uint8)1)
 *     {
 *         GPT2_T5_CALLBACK();
 *         GPT12E_T5_Int_Clr();
 *     }
 *     GPT12E_T5_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_Int_Clr(void)
{
  Field_Wrt8(&SCU->GPT12ICLR.reg, (uint8)SCU_GPT12ICLR_T5C_Pos, (uint8)SCU_GPT12ICLR_T5C_Msk, 1u);
}

/** \brief clears GPT Module 2 Timer 6 interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the GPT Module 2 Timer 6 interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     GPT12E_T6_Int_En();
 *     if (GPT12E_T6_Int_Sts() == (uint8)1)
 *     {
 *         GPT2_T6_CALLBACK();
 *         GPT12E_T6_Int_Clr();
 *     }
 *     GPT12E_T6_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T6_Int_Clr(void)
{
  Field_Wrt8(&SCU->GPT12ICLR.reg, (uint8)SCU_GPT12ICLR_T6C_Pos, (uint8)SCU_GPT12ICLR_T6C_Msk, 1u);
}

/** \brief clears GPT Module 1 Capture Reload interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the GPT Module 1 Capture Reload interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     GPT12E_CapRel_Int_En();
 *     if (GPT12E_CapRel_Int_Sts() == (uint8)1)
 *     {
 *         GPT2_CAPREL_CALLBACK();
 *         GPT12E_CapRel_Int_Clr();
 *     }
 *     GPT12E_CapRel_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_CapRel_Int_Clr(void)
{
  Field_Wrt8(&SCU->GPT12ICLR.reg, (uint8)SCU_GPT12ICLR_CRC_Pos, (uint8)SCU_GPT12ICLR_CRC_Msk, 1u);
}

/** \brief enables GPT Module 1 Timer 2 interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the GPT Module 1 Timer 2 interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     GPT12E_T2_Int_En();
 *     if (GPT12E_T2_Int_Sts() == (uint8)1)
 *     {
 *         GPT1_T2_CALLBACK();
 *         GPT12E_T2_Int_Clr();
 *     }
 *     GPT12E_T2_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Int_En(void)
{
  Field_Mod8(&SCU->GPT12IEN.reg, (uint8)SCU_GPT12IEN_T2IE_Pos, (uint8)SCU_GPT12IEN_T2IE_Msk, 1u);
}

/** \brief disables GPT Module 1 Timer 2 interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the GPT Module 1 Timer 2 interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     GPT12E_T2_Int_En();
 *     if (GPT12E_T2_Int_Sts() == (uint8)1)
 *     {
 *         GPT1_T2_CALLBACK();
 *         GPT12E_T2_Int_Clr();
 *     }
 *     GPT12E_T2_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T2_Int_Dis(void)
{
  Field_Mod8(&SCU->GPT12IEN.reg, (uint8)SCU_GPT12IEN_T2IE_Pos, (uint8)SCU_GPT12IEN_T2IE_Msk, 0u);
}

/** \brief enables GPT Module 1 Timer 3 interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the GPT Module 1 Timer 3 interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     GPT12E_T3_Int_En();
 *     if (GPT12E_T3_Int_Sts() == (uint8)1)
 *     {
 *         GPT1_T3_CALLBACK();
 *         GPT12E_T3_Int_Clr();
 *     }
 *     GPT12E_T3_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T3_Int_En(void)
{
  Field_Mod8(&SCU->GPT12IEN.reg, (uint8)SCU_GPT12IEN_T3IE_Pos, (uint8)SCU_GPT12IEN_T3IE_Msk, 1u);
}

/** \brief disables GPT Module 1 Timer 3 interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the GPT Module 1 Timer 3 interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     GPT12E_T3_Int_En();
 *     if (GPT12E_T3_Int_Sts() == (uint8)1)
 *     {
 *         GPT1_T3_CALLBACK();
 *         GPT12E_T3_Int_Clr();
 *     }
 *     GPT12E_T3_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T3_Int_Dis(void)
{
  Field_Mod8(&SCU->GPT12IEN.reg, (uint8)SCU_GPT12IEN_T3IE_Pos, (uint8)SCU_GPT12IEN_T3IE_Msk, 0u);
}

/** \brief enables GPT Module 1 Timer 4 interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the GPT Module 1 Timer 4 interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     GPT12E_T4_Int_En();
 *     if (GPT12E_T4_Int_Sts() == (uint8)1)
 *     {
 *         GPT1_T4_CALLBACK();
 *         GPT12E_T4_Int_Clr();
 *     }
 *     GPT12E_T4_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Int_En(void)
{
  Field_Mod8(&SCU->GPT12IEN.reg, (uint8)SCU_GPT12IEN_T4IE_Pos, (uint8)SCU_GPT12IEN_T4IE_Msk, 1u);
}

/** \brief enables GPT Module 1 Timer 4 interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the GPT Module 1 Timer 4 interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     GPT12E_T4_Int_En();
 *     if (GPT12E_T4_Int_Sts() == (uint8)1)
 *     {
 *         GPT1_T4_CALLBACK();
 *         GPT12E_T4_Int_Clr();
 *     }
 *     GPT12E_T4_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T4_Int_Dis(void)
{
  Field_Mod8(&SCU->GPT12IEN.reg, (uint8)SCU_GPT12IEN_T4IE_Pos, (uint8)SCU_GPT12IEN_T4IE_Msk, 0u);
}

/** \brief enables GPT Module 2 Timer 5 interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the GPT Module 2 Timer 5 interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     GPT12E_T5_Int_En();
 *     if (GPT12E_T5_Int_Sts() == (uint8)1)
 *     {
 *         GPT2_T5_CALLBACK();
 *         GPT12E_T5_Int_Clr();
 *     }
 *     GPT12E_T5_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_Int_En(void)
{
  Field_Mod8(&SCU->GPT12IEN.reg, (uint8)SCU_GPT12IEN_T5IE_Pos, (uint8)SCU_GPT12IEN_T5IE_Msk, 1u);
}

/** \brief disables GPT Module 2 Timer 5 interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the GPT Module 2 Timer 5 interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     GPT12E_T5_Int_En();
 *     if (GPT12E_T5_Int_Sts() == (uint8)1)
 *     {
 *         GPT2_T5_CALLBACK();
 *         GPT12E_T5_Int_Clr();
 *     }
 *     GPT12E_T5_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T5_Int_Dis(void)
{
  Field_Mod8(&SCU->GPT12IEN.reg, (uint8)SCU_GPT12IEN_T5IE_Pos, (uint8)SCU_GPT12IEN_T5IE_Msk, 0u);
}

/** \brief enables GPT Module 2 Timer 6 interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the GPT Module 2 Timer 6 interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     GPT12E_T6_Int_En();
 *     if (GPT12E_T6_Int_Sts() == (uint8)1)
 *     {
 *         GPT2_T6_CALLBACK();
 *         GPT12E_T6_Int_Clr();
 *     }
 *     GPT12E_T6_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T6_Int_En(void)
{
  Field_Mod8(&SCU->GPT12IEN.reg, (uint8)SCU_GPT12IEN_T6IE_Pos, (uint8)SCU_GPT12IEN_T6IE_Msk, 1u);
}

/** \brief disables GPT Module 2 Timer 6 interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the GPT Module 2 Timer 6 interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     GPT12E_T6_Int_En();
 *     if (GPT12E_T6_Int_Sts() == (uint8)1)
 *     {
 *         GPT2_T6_CALLBACK();
 *         GPT12E_T6_Int_Clr();
 *     }
 *     GPT12E_T6_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_T6_Int_Dis(void)
{
  Field_Mod8(&SCU->GPT12IEN.reg, (uint8)SCU_GPT12IEN_T6IE_Pos, (uint8)SCU_GPT12IEN_T6IE_Msk, 0u);
}

/** \brief enables GPT Module 1 Capture Reload interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the GPT Module 1 Capture Reload interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     GPT12E_CapRel_Int_En();
 *     if (GPT12E_CapRel_Int_Sts() == (uint8)1)
 *     {
 *         GPT2_CAPREL_CALLBACK();
 *         GPT12E_CapRel_Int_Clr();
 *     }
 *     GPT12E_CapRel_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_CapRel_Int_En(void)
{
  Field_Mod8(&SCU->GPT12IEN.reg, (uint8)SCU_GPT12IEN_CRIE_Pos, (uint8)SCU_GPT12IEN_CRIE_Msk, 1u);
}

/** \brief disables GPT Module 1 Capture Reload interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the GPT Module 1 Capture Reload interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     GPT12E_CapRel_Int_En();
 *     if (GPT12E_CapRel_Int_Sts() == (uint8)1)
 *     {
 *         GPT2_CAPREL_CALLBACK();
 *         GPT12E_CapRel_Int_Clr();
 *     }
 *     GPT12E_CapRel_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
INLINE void GPT12E_CapRel_Int_Dis(void)
{
  Field_Mod8(&SCU->GPT12IEN.reg, (uint8)SCU_GPT12IEN_CRIE_Pos, (uint8)SCU_GPT12IEN_CRIE_Msk, 0u);
}

/*******************************************************************************
**                        Global Function Declarations                        **
*******************************************************************************/
/** \brief Initializes the GPT12E module.
 *
 * \ingroup gpt12e_api
 */
void GPT12E_Init(void);

/** \brief Initializes the T3 to be reloaded by T2
 *
 * \param timer_interval_us timer interval in microseconds
 * \retval TRUE setup done
 * \retval FALSE setup failed
 *
 * \brief <b>Example</b><br>
 * \brief This example initializes the T3 to be reloaded by T2 with a timer interval equals to 5000 us.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     bool sts;
 *
 *     sts = GPT12E_T3_Interval_Timer_Setup(0x1388);
 *     return(sts);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
bool GPT12E_T3_Interval_Timer_Setup(uint32 timer_interval_us);

/** \brief Initializes the T6 to be reloaded by CAPREL
 *
 * \param timer_interval_us timer interval in microseconds
 *
 * \brief <b>Example</b><br>
 * \brief This example initializes the T6 to be reloaded by CAPREL with a timer interval equals to 5000 us.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     bool sts;
 *
 *     sts = GPT12E_T6_Interval_Timer_Setup(0x1388);
 *     return(sts);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup gpt12e_api
 */
bool GPT12E_T6_Interval_Timer_Setup(uint32 timer_interval_us);

#endif
