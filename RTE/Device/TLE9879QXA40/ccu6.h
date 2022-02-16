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
 * \file     ccu6.h
 *
 * \brief    Capture/Compare Unit 6 low level access library
 *
 * \version  V0.3.2
 * \date     21. Jul 2020
 */

/*******************************************************************************
**                             Author(s) Identity                             **
********************************************************************************
** Initials     Name                                                          **
** ---------------------------------------------------------------------------**
** DM           Daniel Mysliwitz                                              **
** TA           Thomas Albersinger                                            **
** BG           Blandine Guillot                                              **
** JO           Julia Ott                                                     **
*******************************************************************************/

/*******************************************************************************
**                          Revision Control History                          **
********************************************************************************
** V0.2.0: 2014-04-25, TA:   CCU6_Init(): use #defines from IFX Config Wizard **
** V0.2.1: 2015-02-10, DM:   Individual header file added                     **
** V0.2.2: 2015-08-27, DM:   new API functions added to ccu6.h                **
** V0.2.3: 2017-04-11, DM:   Macros for interrupt set/reset/clear added       **
** V0.2.4: 2017-11-08, DM:   CCU6_T12_Modulation_En() fixed                   **
**                           CCU6_T13_Modulation_En() fixed                   **
** V0.2.5: 2017-11-14, DM:   MISRA 2012 compliance, the following PC-Lint     **
**                           rules are globally deactivated:                  **
**                           - Info 793: ANSI/ISO limit of 6 'significant     **
**                             characters in an external identifier           **
**                           - Info 835: A zero has been given as right       **
**                             argument to operator                           **
**                           - Info 845: The left argument to operator '&'    **
**                             is certain to be 0                             **
**                           CCU6_Init(): one CCU6_T12_Str_En() replaced by   **
**                           CCU6_T13_Str_En()                                **
**                           Replaced macros by INLINE functions              **
**                           Replaced register accesses within functions by   **
**                           function calls                                   **
**                           Replaced __STATIC_INLINE by INLINE               **
** V0.2.6: 2018-03-14, DM:   CCU6_Ch0_Deadtime_Sts(), CCU6_Ch1_Deadtime_Sts(),**
**                           CCU6_Ch2_Deadtime_Sts() the register access      **
**                           macro changed to Field_Rd1()                     **
**                           CCU6_MASK_CC6x and CCU6_MASK_COUT6x changed due  **
**                           to MISRA 2012                                    **
** V0.2.7: 2018-12-04, JO:   Doxygen update                                   **
**                           Moved revision history from ccu6.c to ccu6.h     **
**                           CCU6_Passive_State_After_Compare_Sel() added     **
**                           CCU6_Ch*t_Passive_State_After_Compare_Sel and    **
**                           CCU6_Ch*t_Passive_State_Before_Compare_Sel       **
**                           removed                                          **
** V0.2.8: 2019-01-29, DM:   CCU6_ReadHallReg() fixed                         **
** V0.2.9: 2019-02-27, JO:   CCU6_SetT13Compare() changed (added range check, **
**                           +1 instead of +10)                               **
** V0.3.0: 2020-04-15, BG:   Updated revision history format                  **
** V0.3.1: 2020-07-13, JO:   EP-431: remove ARMCC v6 Compiler warnings        **
**                           - Added typecasts to remove 'implicit typecast'  **
**                             warning                                        **
** V0.3.2: 2020-07-21, BG:   EP-439: Formatted .h/.c files                    **
*******************************************************************************/

#ifndef _CCU6_H
#define _CCU6_H

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "tle987x.h"
#include "types.h"
#include "ccu6_defines.h"
#include "sfr_access.h"
#include "tle_variants.h"

/*******************************************************************************
**                          Global Macro Definitions                          **
*******************************************************************************/
/**\brief CCU6 TCTR4 MASK Macro, T12 STOP */
#define CCU6_MASK_TCTR4_STOP_T12       (CCU6_TCTR4_T12RR_Msk)
/**\brief CCU6 TCTR4 MASK Macro, T12 START */
#define CCU6_MASK_TCTR4_START_T12      (CCU6_TCTR4_T12RS_Msk)
/**\brief CCU6 TCTR4 MASK Macro, T12 RESET */
#define CCU6_MASK_TCTR4_RESET_T12      (CCU6_TCTR4_T12RES_Msk)
/**\brief CCU6 TCTR4 MASK Macro, T12 SHADOW */
#define CCU6_MASK_TCTR4_SHADOW_T12     (CCU6_TCTR4_T12STR_Msk)
/**\brief CCU6 TCTR4 MASK Macro, T13 STOP */
#define CCU6_MASK_TCTR4_STOP_T13       (CCU6_TCTR4_T13RR_Msk)
/**\brief CCU6 TCTR4 MASK Macro, T13 START */
#define CCU6_MASK_TCTR4_START_T13      (CCU6_TCTR4_T13RS_Msk)
/**\brief CCU6 TCTR4 MASK Macro, T13 RESET */
#define CCU6_MASK_TCTR4_RESET_T13      (CCU6_TCTR4_T13RES_Msk)
/**\brief CCU6 TCTR4 MASK Macro, T13 SHADOW */
#define CCU6_MASK_TCTR4_SHADOW_T13     (CCU6_TCTR4_T13STR_Msk)

/**\brief CCU6 MCMOUTS Constants Macro, SHADOW HALL */
#define CCU6_MASK_MCMOUTS_SHADOW_HALL  (CCU6_MCMOUTS_STRHP_Msk)
/**\brief CCU6 MCMOUTS Constants Macro, SHADOW OUT */
#define CCU6_MASK_MCMOUTS_SHADOW_OUT   (CCU6_MCMOUTS_STRMCM_Msk)

/**\brief CCU6 channel Input/Output selection macro, CC60 */
#define CCU6_MASK_CC60                 ((uint16)1u << 0u)
/**\brief CCU6 channel Input/Output selection macro, COUT60 */
#define CCU6_MASK_COUT60               ((uint16)1u << 1u)
/**\brief CCU6 channel Input/Output selection macro, CC61 */
#define CCU6_MASK_CC61                 ((uint16)1u << 2u)
/**\brief CCU6 channel Input/Output selection macro, COUT61 */
#define CCU6_MASK_COUT61               ((uint16)1u << 3u)
/**\brief CCU6 channel Input/Output selection macro, CC62 */
#define CCU6_MASK_CC62                 ((uint16)1u << 4u)
/**\brief CCU6 channel Input/Output selection macro, COUT62 */
#define CCU6_MASK_COUT62               ((uint16)1u << 5u)

/**\brief CCU6 channel Input/Output selection macro, CC60 */
#define CCU6_MASK_Ch0t                 CCU6_MASK_CC60
/**\brief CCU6 channel Input/Output selection macro, COUT60 */
#define CCU6_MASK_Ch0c                 CCU6_MASK_COUT60
/**\brief CCU6 channel Input/Output selection macro, CC61 */
#define CCU6_MASK_Ch1t                 CCU6_MASK_CC61
/**\brief CCU6 channel Input/Output selection macro, COUT61 */
#define CCU6_MASK_Ch1c                 CCU6_MASK_COUT61
/**\brief CCU6 channel Input/Output selection macro, CC62 */
#define CCU6_MASK_Ch2t                 CCU6_MASK_CC62
/**\brief CCU6 channel Input/Output selection macro, COUT62 */
#define CCU6_MASK_Ch2c                 CCU6_MASK_COUT62

/*******************************************************************************
**                           Global Type Definitions                          **
*******************************************************************************/
/** \enum TCCU6_Ch0_Input
 *  \brief This enum lists the CCU6 channel 0 Inputs.
 */
typedef enum
{
  CCU6_CC60_0_P04  = 0u, /**< The input pin for CC60_0 */
  CCU6_CC60_1_P23  = 1u  /**< The input pin for CC60_1 */
} TCCU6_Ch0_Input;

/** \enum TCCU6_Ch1_Input
 *  \brief This enum lists the CCU6 channel 1 Inputs.
 */
typedef enum
{
  CCU6_CC61_0_P10  = 0u /**< The input pin for CC61_0 */
} TCCU6_Ch1_Input;

/** \enum TCCU6_Ch2_Input
 *  \brief This enum lists the CCU6 channel 2 Inputs.
 */
typedef enum
{
  CCU6_CC62_0_P13  = 0u, /**< The input pin for CC62_0 */
  CCU6_CC62_2_P22  = 2u  /**< The input pin for CC62_1 */
} TCCU6_Ch2_Input;

/** \enum TCCU6_Trap_Input
 *  \brief This enum lists the CCU6 Trap Inputs.
 */
typedef enum
{
  CCU6_CTRAP_0_P24  = 0u, /**< The input pin for CTRAP_0 */
  CCU6_CTRAP_1_P23  = 1u  /**< The input pin for CTRAP_1 */
} TCCU6_Trap_Input;

/** \enum TCCU6_Pos0_Input
 *  \brief This enum lists the CCU6 ISPOS0 Inputs.
 */
typedef enum
{
  CCU6_CCPOS0_1_P03  = 1u, /**< The input pin for CCPOS0_1 */
  CCU6_CCPOS0_2_P13  = 2u, /**< The input pin for CCPOS0_2 */
  CCU6_CCPOS0_3_P20  = 3u  /**< The input pin for CCPOS0_3 */
#if (UC_SERIES == TLE987)
  ,
  CCU6_CCPOS0_BEMF   = 3u
#endif /* (UC_SERIES == TLE987) */
} TCCU6_Pos0_Input;

/** \enum TCCU6_Pos1_Input
 *  \brief This enum lists the CCU6 ISPOS1 Inputs.
 */
typedef enum
{
  CCU6_CCPOS1_0_P23  = 0u, /**< The input pin for CCPOS1_0 */
  CCU6_CCPOS1_1_P04  = 1u, /**< The input pin for CCPOS1_1 */
  CCU6_CCPOS1_2_P14  = 2u  /**< The input pin for CCPOS1_2 */
#if (UC_SERIES == TLE987)
  ,
  CCU6_CCPOS1_BEMF   = 3u
#endif /* (UC_SERIES == TLE987) */
} TCCU6_Pos1_Input;

/** \enum TCCU6_Pos2_Input
 *  \brief This enum lists the CCU6 ISPOS2 Inputs.
 */
typedef enum
{
  CCU6_CCPOS2_1_P02  = 1u, /**< The input pin for CCPOS2_1 */
  CCU6_CCPOS2_2_P12  = 2u, /**< The input pin for CCPOS2_2 */
  CCU6_CCPOS2_3_P22  = 3u  /**< The input pin for CCPOS2_3 */
#if (UC_SERIES == TLE987)
  ,
  CCU6_CCPOS2_BEMF   = 3u
#endif /* (UC_SERIES == TLE987) */
} TCCU6_Pos2_Input;

/** \enum TCCU6_T12HR_Input
 *  \brief This enum lists the CCU6 T12HR Inputs.
 */
typedef enum
{
  CCU6_T12HR_0_P00  = 0u, /**< The input pin for T12HR_0 */
  CCU6_T12HR_2_P20  = 2u  /**< The input pin for T12HR_2 */
} TCCU6_T12HR_Input;

/** \enum TCCU6_T13HR_Input
 *  \brief This enum lists the CCU6 T13HR Inputs.
 */
typedef enum
{
  CCU6_T13HR_0_P01  = 0u, /**< The input pin for T13HR_0 */
  CCU6_T13HR_2_P22  = 2u  /**< The input pin for T13HR_2 */
} TCCU6_T13HR_Input;

/** \enum TCCU6_T12_Cnt_Input
 *  \brief This enum lists the CCU6 ISCNT12 Inputs.
 */
typedef enum
{
  CCU6_T12_Prescaler      = 0u, /**< The input event T12 prescaler for T12 Counting */
  CCU6_TCTR4_T12CNT       = 1u, /**< The input event TCTR4.T12CNT for T12 Counting */
  CCU6_T12HR_Rising_Edge  = 2u, /**< The input event T12HR Rising edge for T12 Counting */
  CCU6_T12HR_Falling_Edge = 3u  /**< The input event T12HR Falling edge for T12 Counting */
} TCCU6_T12_Cnt_Input;

/** \enum TCCU6_T13_Cnt_Input
 *  \brief This enum lists the CCU6 ISCNT13 Inputs.
 */
typedef enum
{
  CCU6_T13_Prescaler      = 0u, /**< The input event T13 prescaler for T13 Counting */
  CCU6_TCTR4_T13CNT       = 1u, /**< The input event TCTR4.T13CNT for T13 Counting */
  CCU6_T13HR_Rising_Edge  = 2u, /**< The input event T13HR Rising edge for T13 Counting */
  CCU6_T13HR_Falling_Edge = 3u  /**< The input event T13HR Falling edge for T13 Counting */
} TCCU6_T13_Cnt_Input;

/** \enum TCCU6_T12_Ext_Input
 *  \brief This enum lists the CCU6 T12EXT Inputs.
 */
typedef enum
{
  CCU6_T12HR_D_A      = 0u, /**< The input signal T12HR[D:A] for T12HR */
  CCU6_T12HR_H_E      = 1u  /**< The input signal T12HR[H:E] for T12HR */
} TCCU6_T12_Ext_Input;

/** \enum TCCU6_T13_Ext_Input
 *  \brief This enum lists the CCU6 T13EXT Inputs.
 */
typedef enum
{
  CCU6_T13HR_D_A      = 0u, /**< The input signal T13HR[D:A] for T13HR */
  CCU6_T13HR_H_E      = 1u  /**< The input signal T13HR[H:E] for T13HR */
} TCCU6_T13_Ext_Input;

/** \enum TCCU6_HSYNC
 *  \brief This enum lists the CCU6 Hall Synch Configuration.
 */
typedef enum
{
  CCU6_CCPOS0x_Any_Edge     = 0u, /**< Hall Synchronization Event: Any edge at one of the inputs CCPOSx */
  CCU6_T13_CM               = 1u, /**< Hall Synchronization Event: T13 compare-match */
  CCU6_T13_PM               = 2u, /**< Hall Synchronization Event: T13 period-match */
  CCU6_HW_Hall_Sampling_Off = 3u, /**< Hall Synchronization Event: Hall */
  CCU6_T12_PM               = 4u, /**< Hall Synchronization Event: T12 period-match */
  CCU6_T12_OM               = 5u, /**< Hall Synchronization Event: T12 one-match */
  CCU6_T12_CM_Ch1_up        = 6u, /**< Hall Synchronization Event: T12 compare-match UP */
  CCU6_T12_CM_Ch1_down      = 7u  /**< Hall Synchronization Event: T12 compare-match DOWN */
} TCCU6_HSYNC;

/** \enum TCCU6_Clk_Prescaler
 *  \brief This enum lists the CCU6 T12/T13 Clock Prescaler divider.
 */
typedef enum
{
  CCU6_Clk_Div_1   = 0, /**< Timer T12/T13 Input Clock Select: fCCU */
  CCU6_Clk_Div_2   = 1, /**< Timer T12/T13 Input Clock Select: fCCU/2 */
  CCU6_Clk_Div_4   = 2, /**< Timer T12/T13 Input Clock Select: fCCU/4 */
  CCU6_Clk_Div_8   = 3, /**< Timer T12/T13 Input Clock Select: fCCU/8 */
  CCU6_Clk_Div_16  = 4, /**< Timer T12/T13 Input Clock Select: fCCU/16 */
  CCU6_Clk_Div_32  = 5, /**< Timer T12/T13 Input Clock Select: fCCU/32 */
  CCU6_Clk_Div_64  = 6, /**< Timer T12/T13 Input Clock Select: fCCU/64 */
  CCU6_Clk_Div_128 = 7  /**< Timer T12/T13 Input Clock Select: fCCU/128 */
} TCCU6_Clk_Prescaler;

/** \enum TCCU6_T13TEC
 *  \brief This enum lists the CCU6 T13 Trigger Event Control.
 */
typedef enum
{
  CCU6_T13TEC_No_Trigger = 0, /**< T13 Trigger Event Control: No Action */
  CCU6_T13TEC_T12_CM_Ch0 = 1, /**< T13 Trigger Event Control: Channel 0 */
  CCU6_T13TEC_T12_CM_Ch1 = 2, /**< T13 Trigger Event Control: Channel 1 */
  CCU6_T13TEC_T12_CM_Ch2 = 3, /**< T13 Trigger Event Control: Channel 2 */
  CCU6_T13TEC_T12_CM_Chx = 4, /**< T13 Trigger Event Control: Channels 0,1,2 */
  CCU6_T13TEC_T12_PM     = 5, /**< T13 Trigger Event Control: Period-match */
  CCU6_T13TEC_T12_ZM     = 6, /**< T13 Trigger Event Control: Zero-match */
  CCU6_T13TEC_CCPOSx     = 7  /**< T13 Trigger Event Control: CCPOSx */
} TCCU6_T13TEC;

/** \enum TCCU6_T13ED
 *  \brief This enum lists the CCU6 T13 Trigger Event Direction.
 */
typedef enum
{
  CCU6_T13ED_No_Action   = 0, /**< T13 Trigger Event Direction: No Action */
  CCU6_T13ED_T12_Up      = 1, /**< T13 Trigger Event Direction: T12 is counting Up */
  CCU6_T13ED_T12_Down    = 2, /**< T13 Trigger Event Direction: T12 is counting Down */
  CCU6_T13ED_T12_UpDown  = 3  /**< T13 Trigger Event Direction: Independent direction of T12 */
} TCCU6_T13ED;

/** \enum TCCU6_T12RSEL
 *  \brief This enum lists the CCU6 T12 Run Select.
 */
typedef enum
{
  CCU6_T12RSEL_Dis        = 0, /**< T12 External Run: T12R Disabled */
  CCU6_T12RSEL_T12HR_Rise = 1, /**< T12 External Run: T12HR Rising edge */
  CCU6_T12RSEL_T12HR_Fall = 2, /**< T12 External Run: T12HR Falling edge */
  CCU6_T12RSEL_T12HR_Any  = 3  /**< T12 External Run: T12HR Edge */
} TCCU6_T12RSEL;

/** \enum TCCU6_T13RSEL
 *  \brief This enum lists the CCU6 T13 Run Select.
 */
typedef enum
{
  CCU6_T13RSEL_Dis        = 0, /**< T12 External Run: T13R Disabled */
  CCU6_T13RSEL_T13HR_Rise = 1, /**< T12 External Run: T13HR Rising edge */
  CCU6_T13RSEL_T13HR_Fall = 2, /**< T12 External Run: T13HR Falling edge */
  CCU6_T13RSEL_T13HR_Any  = 3  /**< T12 External Run: T13HR Edge */
} TCCU6_T13RSEL;

/** \enum TCCU6_PSL63
 *  \brief This enum lists the CCU6 COUT63 Passive Level.
 */
typedef enum
{
  CCU6_PSL63_Low  = 0, /**< Passive Low State of Output COUT63 */
  CCU6_PSL63_High = 1  /**< Passive High State of Output COUT63 */
} TCCU6_PSL63;

/** \enum TCCU6_MCM_SWSEL
 *  \brief This enum lists the CCU6 Multi Channel Mode Switching Selection.
 */
typedef enum
{
  CCU6_SWSEL_No_Action    = 0, /**< The trigger request sources for Switching Selection: No request */
  CCU6_SWSEL_Correct_Hall = 1, /**< The trigger request sources for Switching Selection: Correct pattern */
  CCU6_SWSEL_T13_PM       = 2, /**< The trigger request sources for Switching Selection: T13 period-match */
  CCU6_SWSEL_T12_OM       = 3, /**< The trigger request sources for Switching Selection: T12 one-match */
  CCU6_SWSEL_T12_Ch1_CM   = 4, /**< The trigger request sources for Switching Selection: T12 channel 1 compare-match */
  CCU6_SWSEL_T12_PM       = 5  /**< The trigger request sources for Switching Selection: T12 period-match */
} TCCU6_MCM_SWSEL;

/** \enum TCCU6_Node_Sel
 *  \brief This enum lists the CCU6 Interrupt Node Select.
 */
typedef enum
{
  CCU6_Node0 = 0, /**< The CCU6 Interrupt Node: Node 0 */
  CCU6_Node1 = 1, /**< The CCU6 Interrupt Node: Node 1 */
  CCU6_Node2 = 2, /**< The CCU6 Interrupt Node: Node 2 */
  CCU6_Node3 = 3  /**< The CCU6 Interrupt Node: Node 3 */
} TCCU6_Node_Sel;



/** \enum TCCU6_PWMMode
 *  \brief This enum lists the CCU6 modulation modes for T12.
 */
typedef enum
{
  CCU6_T12_ActiveLeftAligned  = 0x15, /**< Active signal is left aligned */
  CCU6_T12_ActiveRightAligned  = 0x2A,  /**< Active signal is right aligned */
  CCU6_T12_ActiveCenterAligned  = 0x2A,  /**< Active signal is center aligned */
  CCU6_T12_ActiveCenterAlignedInverted  = 0x15  /**< Active signal is center aligned inverted */
} TCCU6_PWMMode;


/*******************************************************************************
**                     Global Inline Function Definitions                     **
*******************************************************************************/
/** \brief stops CCU6 T12.
 *
 * \brief <b>Example</b><br>
 * \brief This example stops CCU6 T12.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T12_Stop();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T12_Stop(void)
{
  Field_Wrt16(&CCU6->TCTR4.reg, (uint16)CCU6_TCTR4_T12RR_Pos, (uint16)CCU6_TCTR4_T12RR_Msk, 1u);
}

/** \brief starts CCU6 T12.
 *
 * \brief <b>Example</b><br>
 * \brief This example starts CCU6 T12.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T12_Start();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T12_Start(void)
{
  Field_Wrt16(&CCU6->TCTR4.reg, (uint16)CCU6_TCTR4_T12RS_Pos, (uint16)CCU6_TCTR4_T12RS_Msk, 1u);
}

/** \brief resets CCU6 T12.
 *
 * \brief <b>Example</b><br>
 * \brief This example resets CCU6 T12.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T12_Rst();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T12_Rst(void)
{
  Field_Wrt16(&CCU6->TCTR4.reg, (uint16)CCU6_TCTR4_T12RES_Pos, (uint16)CCU6_TCTR4_T12RES_Msk, 1u);
}

/** \brief resets CCU6 T12 Dead-Time Counter.
 *
 * \brief <b>Example</b><br>
 * \brief This example resets CCU6 T12 Dead-Time Counter.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Deadtime_Rst();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Deadtime_Rst(void)
{
  Field_Wrt16(&CCU6->TCTR4.reg, (uint16)CCU6_TCTR4_DTRES_Pos, (uint16)CCU6_TCTR4_DTRES_Msk, 1u);
}

/** \brief counts 1 step for CCU6 T12 Event.
 *
 * \brief <b>Example</b><br>
 * \brief This example counts 1 step for CCU6 T12 Event (PISEL2 enabled).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T12_Start();
 *    CCU6_T12_Cnt_Input_Sel(1u);
 *    CCU6_T12_Cnt();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T12_Cnt(void)
{
  Field_Wrt16(&CCU6->TCTR4.reg, (uint16)CCU6_TCTR4_T12CNT_Pos, (uint16)CCU6_TCTR4_T12CNT_Msk, 1u);
}

/** \brief enables T12 Shadow Transfer.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables T12 Shadow Transfer.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T12_Str_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T12_Str_En(void)
{
  Field_Wrt16(&CCU6->TCTR4.reg, (uint16)CCU6_TCTR4_T12STR_Pos, (uint16)CCU6_TCTR4_T12STR_Msk, 1u);
}

/** \brief disables T12 Shadow Transfer.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables T12 Shadow Transfer.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T12_Str_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T12_Str_Dis(void)
{
  Field_Wrt16(&CCU6->TCTR4.reg, (uint16)CCU6_TCTR4_T12STD_Pos, (uint16)CCU6_TCTR4_T12STD_Msk, 1u);
}

/** \brief stops CCU6 T13.
 *
 * \brief <b>Example</b><br>
 * \brief This example stops CCU6 T13.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T13_Stop();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T13_Stop(void)
{
  Field_Wrt16(&CCU6->TCTR4.reg, (uint16)CCU6_TCTR4_T13RR_Pos, (uint16)CCU6_TCTR4_T13RR_Msk, 1u);
}

/** \brief starts CCU6 T13.
 *
 * \brief <b>Example</b><br>
 * \brief This example starts CCU6 T13.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T13_Start();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T13_Start(void)
{
  Field_Wrt16(&CCU6->TCTR4.reg, (uint16)CCU6_TCTR4_T13RS_Pos, (uint16)CCU6_TCTR4_T13RS_Msk, 1u);
}

/** \brief resets CCU6 T13.
 *
 * \brief <b>Example</b><br>
 * \brief This example resets CCU6 T13.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T13_Rst();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T13_Rst(void)
{
  Field_Wrt16(&CCU6->TCTR4.reg, (uint16)CCU6_TCTR4_T13RES_Pos, (uint16)CCU6_TCTR4_T13RES_Msk, 1u);
}

/** \brief counts 1 step for CCU6 T13 Event.
 *
 * \brief <b>Example</b><br>
 * \brief This example counts 1 step for CCU6 T13 Event (PISEL2 enabled).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T13_Start();
 *    CCU6_T13_Cnt_Input_Sel(1u);
 *    CCU6_T13_Cnt();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T13_Cnt(void)
{
  Field_Wrt16(&CCU6->TCTR4.reg, (uint16)CCU6_TCTR4_T13CNT_Pos, (uint16)CCU6_TCTR4_T13CNT_Msk, 1u);
}

/** \brief enables T13 Shadow Transfer.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables T13 Shadow Transfer.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T13_Str_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T13_Str_En(void)
{
  Field_Wrt16(&CCU6->TCTR4.reg, (uint16)CCU6_TCTR4_T13STR_Pos, (uint16)CCU6_TCTR4_T13STR_Msk, 1u);
}

/** \brief disables T13 Shadow Transfer.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables T13 Shadow Transfer.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T13_Str_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T13_Str_Dis(void)
{
  Field_Wrt16(&CCU6->TCTR4.reg, (uint16)CCU6_TCTR4_T13STD_Pos, (uint16)CCU6_TCTR4_T13STD_Msk, 1u);
}

/** \brief selects Input for CC60.
 *
 * \param iscc60 input for CC60
 *
 * \brief <b>Example</b><br>
 * \brief This example selects CC60_1 as Input for CC60.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Ch0_Input_Sel(1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch0_Input_Sel(uint16 iscc60)
{
  Field_Mod16(&CCU6->PISEL0.reg, (uint16)CCU6_PISEL0_ISCC60_Pos, (uint16)CCU6_PISEL0_ISCC60_Msk, iscc60);
}

/** \brief selects Input for CC61.
 *
 * \param iscc61 input for CC61
 *
 * \brief <b>Example</b><br>
 * \brief This example selects CC61_1 as Input for CC61.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Ch1_Input_Sel(1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch1_Input_Sel(uint16 iscc61)
{
  Field_Mod16(&CCU6->PISEL0.reg, (uint16)CCU6_PISEL0_ISCC61_Pos, (uint16)CCU6_PISEL0_ISCC61_Msk, iscc61);
}

/** \brief selects Input for CC62.
 *
 * \param iscc62 input for CC62
 *
 * \brief <b>Example</b><br>
 * \brief This example selects CC62_1 as Input for CC62.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Ch2_Input_Sel(1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch2_Input_Sel(uint16 iscc62)
{
  Field_Mod16(&CCU6->PISEL0.reg, (uint16)CCU6_PISEL0_ISCC62_Pos, (uint16)CCU6_PISEL0_ISCC62_Msk, iscc62);
}

/** \brief selects Input for CTRAP.
 *
 * \param istrp input for CTRAP
 *
 * \brief <b>Example</b><br>
 * \brief This example selects CTRAP_1 as Input for CTRAP.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Trap_Input_Sel(1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Trap_Input_Sel(uint16 istrp)
{
  Field_Mod16(&CCU6->PISEL0.reg, (uint16)CCU6_PISEL0_ISTRP_Pos, (uint16)CCU6_PISEL0_ISTRP_Msk, istrp);
}

/** \brief selects Input for CCPOS0.
 *
 * \param ispos0 input for CCPOS0
 *
 * \brief <b>Example</b><br>
 * \brief This example selects CCPOS0_1 as Input for CCPOS0.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_CCPOS0_Input_Sel(1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_CCPOS0_Input_Sel(uint16 ispos0)
{
  Field_Mod16(&CCU6->PISEL0.reg, (uint16)CCU6_PISEL0_ISPOS0_Pos, (uint16)CCU6_PISEL0_ISPOS0_Msk, ispos0);
}

/** \brief selects Input for CCPOS1.
 *
 * \param ispos1 input for CCPOS1
 *
 * \brief <b>Example</b><br>
 * \brief This example selects CCPOS1_1 as Input for CCPOS1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_CCPOS1_Input_Sel(1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_CCPOS1_Input_Sel(uint16 ispos1)
{
  Field_Mod16(&CCU6->PISEL0.reg, (uint16)CCU6_PISEL0_ISPOS1_Pos, (uint16)CCU6_PISEL0_ISPOS1_Msk, ispos1);
}

/** \brief selects Input for CCPOS2.
 *
 * \param ispos2 input for CCPOS2
 *
 * \brief <b>Example</b><br>
 * \brief This example selects CCPOS2_1 as Input for CCPOS2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_CCPOS2_Input_Sel(1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_CCPOS2_Input_Sel(uint16 ispos2)
{
  Field_Mod16(&CCU6->PISEL0.reg, (uint16)CCU6_PISEL0_ISPOS2_Pos, (uint16)CCU6_PISEL0_ISPOS2_Msk, ispos2);
}

/** \brief selects Input for T12HR.
 *
 * \param ist12hr input for T12HR
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T12HR_B as Input for T12HR.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T12_Ext_Input_Sel(0u);
 *    CCU6_T12HR_Input_Sel(1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T12HR_Input_Sel(uint16 ist12hr)
{
  Field_Mod16(&CCU6->PISEL0.reg, (uint16)CCU6_PISEL0_IST12HR_Pos, (uint16)CCU6_PISEL0_IST12HR_Msk, ist12hr);
}

/** \brief selects Input for T13HR.
 *
 * \param ist13hr input for T13HR
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T13HR_B as Input for T13HR.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T13_Ext_Input_Sel(0u);
 *    CCU6_T13HR_Input_Sel(1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T13HR_Input_Sel(uint16 ist13hr)
{
  Field_Mod16(&CCU6->PISEL2.reg, (uint16)CCU6_PISEL2_IST13HR_Pos, (uint16)CCU6_PISEL2_IST13HR_Msk, ist13hr);
}

/** \brief selects Input for T12 Counting.
 *
 * \param iscnt12 input for T12 Counting
 *
 * \brief <b>Example</b><br>
 * \brief This example counts 1 step for CCU6 T12 Event (T12CNT selected).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T12_Start();
 *    CCU6_T12_Cnt_Input_Sel(1u);
 *    CCU6_T12_Cnt();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T12_Cnt_Input_Sel(uint16 iscnt12)
{
  Field_Mod16(&CCU6->PISEL2.reg, (uint16)CCU6_PISEL2_ISCNT12_Pos, (uint16)CCU6_PISEL2_ISCNT12_Msk, iscnt12);
}

/** \brief selects Input for T13 Counting.
 *
 * \param iscnt13 input for T13 Counting
 *
 * \brief <b>Example</b><br>
 * \brief This example counts 1 step for CCU6 T13 Event (T13CNT enabled).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T13_Start();
 *    CCU6_T13_Cnt_Input_Sel(1u);
 *    CCU6_T13_Cnt();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T13_Cnt_Input_Sel(uint16 iscnt13)
{
  Field_Mod16(&CCU6->PISEL2.reg, (uint16)CCU6_PISEL2_ISCNT13_Pos, (uint16)CCU6_PISEL2_ISCNT13_Msk, iscnt13);
}

/** \brief selects Input of Extension for T12HR.
 *
 * \param t12ext input of Extension for T12HR
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T12HR_B as Input for T12HR.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T12_Ext_Input_Sel(0u);
 *    CCU6_T12HR_Input_Sel(1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T12_Ext_Input_Sel(uint16 t12ext)
{
  Field_Mod16(&CCU6->PISEL2.reg, (uint16)CCU6_PISEL2_T12EXT_Pos, (uint16)CCU6_PISEL2_T12EXT_Msk, t12ext);
}

/** \brief selects Input of Extension for T13HR.
 *
 * \param t13ext input of Extension for T13HR
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T13HR_B as Input for T13HR.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T13_Ext_Input_Sel(0u);
 *    CCU6_T13HR_Input_Sel(1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T13_Ext_Input_Sel(uint16 t13ext)
{
  Field_Mod16(&CCU6->PISEL2.reg, (uint16)CCU6_PISEL2_T13EXT_Pos, (uint16)CCU6_PISEL2_T13EXT_Msk, t13ext);
}

/** \brief enables Hall Delay Bypass.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Hall Delay Bypass.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Hall_Delay_Bypass_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Hall_Delay_Bypass_En(void)
{
  Field_Mod16(&CCU6->T12MSEL.reg, (uint16)CCU6_T12MSEL_DBYP_Pos, (uint16)CCU6_T12MSEL_DBYP_Msk, 1u);
}

/** \brief disables Hall Delay Bypass.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Hall Delay Bypass.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Hall_Delay_Bypass_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Hall_Delay_Bypass_Dis(void)
{
  Field_Mod16(&CCU6->T12MSEL.reg, (uint16)CCU6_T12MSEL_DBYP_Pos, (uint16)CCU6_T12MSEL_DBYP_Msk, 0u);
}

/** \brief selects Hall Synchronization.
 *
 * \param hsync Hall Synchronization
 *
 * \brief <b>Example</b><br>
 * \brief This example selects T13 CM as Hall Synchronization.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Hall_Synchronizaion_Sel(1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Hall_Synchronizaion_Sel(uint16 hsync)
{
  Field_Mod16(&CCU6->T12MSEL.reg, (uint16)CCU6_T12MSEL_HSYNC_Pos, (uint16)CCU6_T12MSEL_HSYNC_Msk, hsync);
}

/** \brief selects CCU6 T12 CH2 Capture/Compare Mode.
 *
 * \param msel62 CCU6 T12 CH2 Capture/Compare Mode
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Compare outputs disabled as CCU6 T12 CH2 Capture/Compare Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Ch2_CapCom_Mode_Sel(0u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch2_CapCom_Mode_Sel(uint16 msel62)
{
  Field_Mod16(&CCU6->T12MSEL.reg, (uint16)CCU6_T12MSEL_MSEL62_Pos, (uint16)CCU6_T12MSEL_MSEL62_Msk, msel62);
}

/** \brief selects CCU6 T12 CH1 Capture/Compare Mode.
 *
 * \param msel61 CCU6 T12 CH1 Capture/Compare Mode
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Compare outputs disabled as CCU6 T12 CH1 Capture/Compare Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Ch1_CapCom_Mode_Sel(0u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch1_CapCom_Mode_Sel(uint16 msel61)
{
  Field_Mod16(&CCU6->T12MSEL.reg, (uint16)CCU6_T12MSEL_MSEL61_Pos, (uint16)CCU6_T12MSEL_MSEL61_Msk, msel61);
}

/** \brief selects CCU6 T12 CH0 Capture/Compare Mode.
 *
 * \param msel60 CCU6 T12 CH0 Capture/Compare Mode
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Compare outputs disabled as CCU6 T12 CH0 Capture/Compare Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Ch0_CapCom_Mode_Sel(0u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch0_CapCom_Mode_Sel(uint16 msel60)
{
  Field_Mod16(&CCU6->T12MSEL.reg, (uint16)CCU6_T12MSEL_MSEL60_Pos, (uint16)CCU6_T12MSEL_MSEL60_Msk, msel60);
}

/** \brief reads Timer T12 Counter Value.
 *
 * \return T12 Counter Value
 *
 * \brief <b>Example</b><br>
 * \brief This example reads Timer T12 Counter Value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint16 val;
 *
 *    val = CCU6_T12_Count_Value_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint16 CCU6_T12_Count_Value_Get(void)
{
  return ( u16_Field_Rd16(&CCU6->T12.reg, (uint16)CCU6_T12_T12CV_Pos, (uint16)CCU6_T12_T12CV_Msk) );
}

/** \brief sets Timer T12 Counter Value.
 *
 * \param t12cv T12 Counter Value
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Timer T12 Counter Value to 5000.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T12_Start();
 *    CCU6_T12_Count_Value_Set(0x1388);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T12_Count_Value_Set(uint16 t12cv)
{
  Field_Wrt16(&CCU6->T12.reg, (uint16)CCU6_T12_T12CV_Pos, (uint16)CCU6_T12_T12CV_Msk, t12cv);
}

/** \brief reads Timer T12 Period Value.
 *
 * \return T12 Period Value
 *
 * \brief <b>Example</b><br>
 * \brief This example reads Timer T12 Period Value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint16 val;
 *
 *    CCU6_T12_Start();
 *    val = CCU6_T12_Period_Value_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint16 CCU6_T12_Period_Value_Get(void)
{
  return ( u16_Field_Rd16(&CCU6->T12PR.reg, (uint16)CCU6_T12PR_T12PV_Pos, (uint16)CCU6_T12PR_T12PV_Msk) );
}

/** \brief sets Timer T12 Period Value.
 *
 * \param t12pr T12 Period Value
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Timer T12 Period Value to 5000.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T12_Start();
 *    CCU6_T12_Period_Value_Set(0x1388);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T12_Period_Value_Set(uint16 t12pr)
{
  Field_Wrt16(&CCU6->T12PR.reg, (uint16)CCU6_T12PR_T12PV_Pos, (uint16)CCU6_T12PR_T12PV_Msk, t12pr);
}

/** \brief reads Channel 0 Capture/Compare Value.
 *
 * \return Channel 0 Capture/Compare Value
 *
 * \brief <b>Example</b><br>
 * \brief This example reads Channel 0 Capture/Compare Value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint16 val;
 *
 *    val = CCU6_Ch0_Value_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint16 CCU6_Ch0_Value_Get(void)
{
  return ( u16_Field_Rd16(&CCU6->CC60R.reg, (uint16)CCU6_CC60R_CCV_Pos, (uint16)CCU6_CC60R_CCV_Msk) );
}

/** \brief sets Channel 0 Capture/Compare Value.
 *
 * \param cc60sr Channel 0 Capture/Compare Value
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Channel 0 Capture/Compare Value to 5000.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Ch0_Value_Set(0x1388);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch0_Value_Set(uint16 cc60sr)
{
  Field_Wrt16(&CCU6->CC60SR.reg, (uint16)CCU6_CC60R_CCV_Pos, (uint16)CCU6_CC60R_CCV_Msk, cc60sr);
}

/** \brief reads Channel 1 Capture/Compare Value.
 *
 * \return Channel 1 Capture/Compare Value
 *
 * \brief <b>Example</b><br>
 * \brief This example reads Channel 1 Capture/Compare Value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint16 val;
 *
 *    val = CCU6_Ch1_Value_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint16 CCU6_Ch1_Value_Get(void)
{
  return ( u16_Field_Rd16(&CCU6->CC61R.reg, (uint16)CCU6_CC61R_CCV_Pos, (uint16)CCU6_CC61R_CCV_Msk) );
}

/** \brief sets Channel 1 Capture/Compare Value.
 *
 * \param cc61sr Channel 1 Capture/Compare Value
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Channel 1 Capture/Compare Value to 5000.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Ch1_Value_Set(0x1388);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch1_Value_Set(uint16 cc61sr)
{
  Field_Wrt16(&CCU6->CC61SR.reg, (uint16)CCU6_CC61R_CCV_Pos, (uint16)CCU6_CC61R_CCV_Msk, cc61sr);
}

/** \brief reads Channel 2 Capture/Compare Value.
 *
 * \return Channel 2 Capture/Compare Value
 *
 * \brief <b>Example</b><br>
 * \brief This example reads Channel 2 Capture/Compare Value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint16 val;
 *
 *    val = CCU6_Ch2_Value_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint16 CCU6_Ch2_Value_Get(void)
{
  return ( u16_Field_Rd16(&CCU6->CC62R.reg, (uint16)CCU6_CC62R_CCV_Pos, (uint16)CCU6_CC62R_CCV_Msk) );
}

/** \brief sets Channel 2 Capture/Compare Value.
 *
 * \param cc62sr Channel 2 Capture/Compare Value
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Channel 2 Capture/Compare Value to 5000.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Ch2_Value_Set(0x1388);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch2_Value_Set(uint16 cc62sr)
{
  Field_Wrt16(&CCU6->CC62SR.reg, (uint16)CCU6_CC62R_CCV_Pos, (uint16)CCU6_CC62R_CCV_Msk, cc62sr);
}

/** \brief reads CCU6 Timer T12 Deadtime.
 *
 * \return CCU6 Timer T12 Deadtime
 *
 * \brief <b>Example</b><br>
 * \brief This example reads CCU6 Timer T12 Deadtime.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint16 val;
 *
 *    val = CCU6_Deadtime_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint8 CCU6_Deadtime_Get(void)
{
  return ( u8_Field_Rd16(&CCU6->T12DTC.reg, (uint16)CCU6_T12DTC_DTM_Pos, (uint16)CCU6_T12DTC_DTM_Msk) );
}

/** \brief sets CCU6 Timer T12 Deadtime.
 *
 * \param dtm CCU6 Timer T12 Deadtime
 *
 * \brief <b>Example</b><br>
 * \brief This example sets CCU6 Timer T12 Deadtime to 50.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Deadtime_Set(0x32);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Deadtime_Set(uint16 dtm)
{
  Field_Mod16(&CCU6->T12DTC.reg, (uint16)CCU6_T12DTC_DTM_Pos, (uint16)CCU6_T12DTC_DTM_Msk, dtm);
}

/** \brief enables CCU6 Timer T12 Channel 0 Deadtime.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables CCU6 Timer T12 Channel 0 Deadtime.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Ch0_Deadtime_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch0_Deadtime_En(void)
{
  Field_Mod16(&CCU6->T12DTC.reg, (uint16)CCU6_T12DTC_DTE0_Pos, (uint16)CCU6_T12DTC_DTE0_Msk, 1u);
}

/** \brief enables CCU6 Timer T12 Channel 1 Deadtime.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables CCU6 Timer T12 Channel 1 Deadtime.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Ch1_Deadtime_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch1_Deadtime_En(void)
{
  Field_Mod16(&CCU6->T12DTC.reg, (uint16)CCU6_T12DTC_DTE1_Pos, (uint16)CCU6_T12DTC_DTE1_Msk, 1u);
}

/** \brief enables CCU6 Timer T12 Channel 2 Deadtime.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables CCU6 Timer T12 Channel 2 Deadtime.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Ch2_Deadtime_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch2_Deadtime_En(void)
{
  Field_Mod16(&CCU6->T12DTC.reg, (uint16)CCU6_T12DTC_DTE2_Pos, (uint16)CCU6_T12DTC_DTE2_Msk, 1u);
}

/** \brief disables CCU6 Timer T12 Channel 0 Deadtime.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables CCU6 Timer T12 Channel 0 Deadtime.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Ch0_Deadtime_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch0_Deadtime_Dis(void)
{
  Field_Mod16(&CCU6->T12DTC.reg, (uint16)CCU6_T12DTC_DTE0_Pos, (uint16)CCU6_T12DTC_DTE0_Msk, 0u);
}

/** \brief disables CCU6 Timer T12 Channel 1 Deadtime.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables CCU6 Timer T12 Channel 1 Deadtime.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Ch1_Deadtime_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch1_Deadtime_Dis(void)
{
  Field_Mod16(&CCU6->T12DTC.reg, (uint16)CCU6_T12DTC_DTE1_Pos, (uint16)CCU6_T12DTC_DTE1_Msk, 0u);
}

/** \brief disables CCU6 Timer T12 Channel 2 Deadtime.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables CCU6 Timer T12 Channel 2 Deadtime.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Ch2_Deadtime_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch2_Deadtime_Dis(void)
{
  Field_Mod16(&CCU6->T12DTC.reg, (uint16)CCU6_T12DTC_DTE2_Pos, (uint16)CCU6_T12DTC_DTE2_Msk, 0u);
}

/** \brief reads CCU6 Timer T12 Channel 0 Deadtime Status.
 *
 * \return CCU6 Timer T12 Channel 0 Deadtime Status
 *
 * \brief <b>Example</b><br>
 * \brief This example reads CCU6 Timer T12 Channel 0 Deadtime Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint8 sts;
 *
 *    CCU6_Ch0_Deadtime_En();
 *    sts = CCU6_Ch0_Deadtime_Sts();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint8 CCU6_Ch0_Deadtime_Sts(void)
{
  return ( u1_Field_Rd16(&CCU6->T12DTC.reg, (uint8)CCU6_T12DTC_DTR0_Pos, (uint16)CCU6_T12DTC_DTR0_Msk) );
}

/** \brief reads CCU6 Timer T12 Channel 1 Deadtime Status.
 *
 * \return CCU6 Timer T12 Channel 1 Deadtime Status
 *
 * \brief <b>Example</b><br>
 * \brief This example reads CCU6 Timer T12 Channel 1 Deadtime Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint8 sts;
 *
 *    CCU6_Ch1_Deadtime_En();
 *    sts = CCU6_Ch1_Deadtime_Sts();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint8 CCU6_Ch1_Deadtime_Sts(void)
{
  return ( u1_Field_Rd16(&CCU6->T12DTC.reg, (uint16)CCU6_T12DTC_DTR1_Pos, (uint16)CCU6_T12DTC_DTR1_Msk) );
}

/** \brief reads CCU6 Timer T12 Channel 2 Deadtime Status.
 *
 * \return CCU6 Timer T12 Channel 2 Deadtime Status
 *
 * \brief <b>Example</b><br>
 * \brief This example reads CCU6 Timer T12 Channel 2 Deadtime Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint8 sts;
 *
 *    CCU6_Ch2_Deadtime_En();
 *    sts = CCU6_Ch2_Deadtime_Sts();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint8 CCU6_Ch2_Deadtime_Sts(void)
{
  return ( u1_Field_Rd16(&CCU6->T12DTC.reg, (uint16)CCU6_T12DTC_DTR2_Pos, (uint16)CCU6_T12DTC_DTR2_Msk) );
}

/** \brief reads Timer T13 Counter Value.
 *
 * \return T13 Counter Value
 *
 * \brief <b>Example</b><br>
 * \brief This example reads Timer T13 Counter Value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint16 val;
 *
 *    val = CCU6_T13_Count_Value_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint16 CCU6_T13_Count_Value_Get(void)
{
  return ( u16_Field_Rd16(&CCU6->T13.reg, (uint16)CCU6_T13_T13CV_Pos, (uint16)CCU6_T13_T13CV_Msk) );
}

/** \brief sets Timer T13 Counter Value.
 *
 * \param t13cv T13 Counter Value
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Timer T13 Counter Value to 5000.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T13_Count_Value_Set(0x1388);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T13_Count_Value_Set(uint16 t13cv)
{
  Field_Wrt16(&CCU6->T13.reg, (uint16)CCU6_T13_T13CV_Pos, (uint16)CCU6_T13_T13CV_Msk, t13cv);
}

/** \brief reads Timer T13 Period Value.
 *
 * \return T13 Period Value
 *
 * \brief <b>Example</b><br>
 * \brief This example reads Timer T13 Period Value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint16 val;
 *
 *    val = CCU6_T13_Period_Value_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint16 CCU6_T13_Period_Value_Get(void)
{
  return ( u16_Field_Rd16(&CCU6->T13PR.reg, (uint16)CCU6_T13PR_T13PV_Pos, (uint16)CCU6_T13PR_T13PV_Msk) );
}

/** \brief sets Timer T13 Period Value.
 *
 * \param t13pr T13 Period Value
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Timer T13 Period Value to 5000.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T13_Period_Value_Set(0x1388);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T13_Period_Value_Set(uint16 t13pr)
{
  Field_Wrt16(&CCU6->T13PR.reg, (uint16)CCU6_T13PR_T13PV_Pos, (uint16)CCU6_T13PR_T13PV_Msk, t13pr);
}

/** \brief reads Channel CC63 Compare Value.
 *
 * \return Channel CC63 Compare Value
 *
 * \brief <b>Example</b><br>
 * \brief This example reads Channel CC63 Compare Value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint16 val;
 *
 *    val = CCU6_Ch3_Value_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint16 CCU6_Ch3_Value_Get(void)
{
  return ( u16_Field_Rd16(&CCU6->CC63R.reg, (uint16)CCU6_CC63R_CCV_Pos, (uint16)CCU6_CC63R_CCV_Msk) );
}

/** \brief sets Channel CC63 Compare Value.
 *
 * \param cc63sr Channel CC63 Compare Value
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Channel CC63 Compare Value to 5000.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Ch3_Value_Set(0x1388);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch3_Value_Set(uint16 cc63sr)
{
  Field_Wrt16(&CCU6->CC63SR.reg, (uint16)CCU6_CC63R_CCV_Pos, (uint16)CCU6_CC63R_CCV_Msk, cc63sr);
}

/** \brief reads CC60 Capture/Compare State.
 *
 * \retval 0 if the timer count is less than the compare value
 * \retval 1 if the timer count is greater than the compare value
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Passive state for COUT60.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    while(CCU6_Ch0_CompState_Sts() == (uint8)0)
 *    {
 *       CCU6_Ch0c_Passive_State_Before_Compare_Set();
 *    }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint8 CCU6_Ch0_CompState_Sts(void)
{
  return ( u1_Field_Rd16(&CCU6->CMPSTAT.reg, (uint16)CCU6_CMPSTAT_CC60ST_Pos, (uint16)CCU6_CMPSTAT_CC60ST_Msk) );
}

/** \brief reads CC61 Capture/Compare State.
 *
 * \retval 0 if the timer count is less than the compare value
 * \retval 1 if the timer count is greater than the compare value
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Passive state for COUT61.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    while(CCU6_Ch1_CompState_Sts() == (uint8)0)
 *    {
 *       CCU6_Ch1c_Passive_State_Before_Compare_Set();
 *    }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint8 CCU6_Ch1_CompState_Sts(void)
{
  return ( u1_Field_Rd16(&CCU6->CMPSTAT.reg, (uint16)CCU6_CMPSTAT_CC61ST_Pos, (uint16)CCU6_CMPSTAT_CC61ST_Msk) );
}

/** \brief reads CC62 Capture/Compare State.
 *
 * \retval 0 if the timer count is less than the compare value
 * \retval 1 if the timer count is greater than the compare value
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Passive state for COUT62.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    while(CCU6_Ch2_CompState_Sts() == (uint8)0)
 *    {
 *       CCU6_Ch2c_Passive_State_Before_Compare_Set();
 *    }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint8 CCU6_Ch2_CompState_Sts(void)
{
  return ( u1_Field_Rd16(&CCU6->CMPSTAT.reg, (uint16)CCU6_CMPSTAT_CC62ST_Pos, (uint16)CCU6_CMPSTAT_CC62ST_Msk) );
}

/** \brief reads CC63 Capture/Compare State.
 *
 * \retval 0 if the timer count is less than the compare value
 * \retval 1 if the timer count is greater than the compare value
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Passive state for COUT63.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    while(CCU6_Ch3_CompState_Sts() == (uint8)0)
 *    {
 *       CCU6_Ch3c_Passive_State_Before_Compare_Set();
 *    }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint8 CCU6_Ch3_CompState_Sts(void)
{
  return ( u1_Field_Rd16(&CCU6->CMPSTAT.reg, (uint16)CCU6_CMPSTAT_CC63ST_Pos, (uint16)CCU6_CMPSTAT_CC63ST_Msk) );
}

/** \brief reads Sampled Hall Pattern Bit 0.
 *
 * \retval 0 if the input CCPOS0 has been sampled as 0.
 * \retval 1 if the input CCPOS0 has been sampled as 1.
 *
 * \brief <b>Example</b><br>
 * \brief This example reads Sampled Hall Pattern Bit 0.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint8 data;
 *
 *    data = CCU6_Hall_Ch0_Sts();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint8 CCU6_Hall_Ch0_Sts(void)
{
  return ( u1_Field_Rd16(&CCU6->CMPSTAT.reg, (uint16)CCU6_CMPSTAT_CCPOS0_Pos, (uint16)CCU6_CMPSTAT_CCPOS0_Msk) );
}

/** \brief reads Sampled Hall Pattern Bit 1.
 *
 * \retval 0 if the input CCPOS1 has been sampled as 0.
 * \retval 1 if the input CCPOS1 has been sampled as 1.
 *
 * \brief <b>Example</b><br>
 * \brief This example reads Sampled Hall Pattern Bit 1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint8 data;
 *
 *    data = CCU6_Hall_Ch1_Sts();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint8 CCU6_Hall_Ch1_Sts(void)
{
  return ( u1_Field_Rd16(&CCU6->CMPSTAT.reg, (uint16)CCU6_CMPSTAT_CCPOS1_Pos, (uint16)CCU6_CMPSTAT_CCPOS1_Msk) );
}

/** \brief reads Sampled Hall Pattern Bit 2.
 *
 * \retval 0 if the input CCPOS2 has been sampled as 0.
 * \retval 1 if the input CCPOS2 has been sampled as 1.
 *
 * \brief <b>Example</b><br>
 * \brief This example reads Sampled Hall Pattern Bit 2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint8 data;
 *
 *    data = CCU6_Hall_Ch2_Sts();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint8 CCU6_Hall_Ch2_Sts(void)
{
  return ( u1_Field_Rd16(&CCU6->CMPSTAT.reg, (uint16)CCU6_CMPSTAT_CCPOS2_Pos, (uint16)CCU6_CMPSTAT_CCPOS2_Msk) );
}

/** \brief sets mode of PWM signal for Channel0/1/2 and COUT0/1/2.
 *
 * \param mode possible mode that is set to all channels that can be modulated by Timer12
 *
 * \ingroup ccu6_api
 */
INLINE void CCU6_T12_PWMMode_Set(TCCU6_PWMMode mode)
{
  Field_Mod16(&CCU6->CMPSTAT.reg, (uint16)CCU6_CMPSTAT_CC60PS_Pos, (uint16)0x3F00, (uint16_t)mode);
  CCU6_T12_Str_En();
}


/** \brief sets Passive state for COUT63 after Compare.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Passive state for COUT63.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    while(CCU6_Ch3_CompState_Sts() == (uint8)1)
 *    {
 *       CCU6_Ch3c_Passive_State_After_Compare_Set();
 *    }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch3c_Passive_State_After_Compare_Set(void)
{
  Field_Mod16(&CCU6->CMPSTAT.reg, (uint16)CCU6_CMPSTAT_COUT63PS_Pos, (uint16)CCU6_CMPSTAT_COUT63PS_Msk, 1u);
  CCU6_T13_Str_En();
}

/** \brief sets Passive state for COUT63 Before Compare.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Passive state for COUT63.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    while(CCU6_Ch3_CompState_Sts() == (uint8)0)
 *    {
 *       CCU6_Ch3c_Passive_State_Before_Compare_Set();
 *    }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch3c_Passive_State_Before_Compare_Set(void)
{
  Field_Mod16(&CCU6->CMPSTAT.reg, (uint16)CCU6_CMPSTAT_COUT63PS_Pos, (uint16)CCU6_CMPSTAT_COUT63PS_Msk, 0u);
  CCU6_T13_Str_En();
}

/** \brief enables T13 inversion for further modulation.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables T13 inversion.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T13_Inv_Mod_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T13_Inv_Mod_En(void)
{
  Field_Mod16(&CCU6->CMPSTAT.reg, (uint16)CCU6_CMPSTAT_T13IM_Pos, (uint16)CCU6_CMPSTAT_T13IM_Msk, 1u);
  CCU6_T13_Str_En();
}

/** \brief disables T13 inversion for further modulation.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables T13 inversion.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T13_Inv_Mod_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T13_Inv_Mod_Dis(void)
{
  Field_Mod16(&CCU6->CMPSTAT.reg, (uint16)CCU6_CMPSTAT_T13IM_Pos, (uint16)CCU6_CMPSTAT_T13IM_Msk, 0u);
  CCU6_T13_Str_En();
}

/** \brief sets Capture/Compare Status Modification Bit 0 for (CC60ST) by Software.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets CC60ST.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Ch0_CompState_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch0_CompState_Set(void)
{
  Field_Wrt16(&CCU6->CMPMODIF.reg, (uint16)CCU6_CMPMODIF_MCC60S_Pos, (uint16)CCU6_CMPMODIF_MCC60S_Msk, 1u);
}

/** \brief sets Capture/Compare Status Modification Bit 1 for (CC61ST) by Software.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets CC61ST.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Ch1_CompState_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch1_CompState_Set(void)
{
  Field_Wrt16(&CCU6->CMPMODIF.reg, (uint16)CCU6_CMPMODIF_MCC61S_Pos, (uint16)CCU6_CMPMODIF_MCC61S_Msk, 1u);
}

/** \brief sets Capture/Compare Status Modification Bit 2 for (CC62ST) by Software.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets CC62ST.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Ch2_CompState_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch2_CompState_Set(void)
{
  Field_Wrt16(&CCU6->CMPMODIF.reg, (uint16)CCU6_CMPMODIF_MCC62S_Pos, (uint16)CCU6_CMPMODIF_MCC62S_Msk, 1u);
}

/** \brief sets Capture/Compare Status Modification Bit 3 for (CC63ST) by Software.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets CC63ST.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Ch3_CompState_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch3_CompState_Set(void)
{
  Field_Wrt16(&CCU6->CMPMODIF.reg, (uint16)CCU6_CMPMODIF_MCC63S_Pos, (uint16)CCU6_CMPMODIF_MCC63S_Msk, 1u);
}

/** \brief resets Capture/Compare Status Modification Bit 0 for CC60ST by Software.
 *
 * \brief <b>Example</b><br>
 * \brief This example resets CC60ST.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Ch0_CompState_Rst();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch0_CompState_Rst(void)
{
  Field_Wrt16(&CCU6->CMPMODIF.reg, (uint16)CCU6_CMPMODIF_MCC60R_Pos, (uint16)CCU6_CMPMODIF_MCC60R_Msk, 1u);
}

/** \brief resets Capture/Compare Status Modification Bit 1 for CC61ST by Software.
 *
 * \brief <b>Example</b><br>
 * \brief This example resets CC61ST.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Ch1_CompState_Rst();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch1_CompState_Rst(void)
{
  Field_Wrt16(&CCU6->CMPMODIF.reg, (uint16)CCU6_CMPMODIF_MCC61R_Pos, (uint16)CCU6_CMPMODIF_MCC61R_Msk, 1u);
}

/** \brief resets Capture/Compare Status Modification Bit 2 (CC62ST) by Software.
 *
 * \brief <b>Example</b><br>
 * \brief This example resets CC62ST.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Ch2_CompState_Rst();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch2_CompState_Rst(void)
{
  Field_Wrt16(&CCU6->CMPMODIF.reg, (uint16)CCU6_CMPMODIF_MCC62R_Pos, (uint16)CCU6_CMPMODIF_MCC62R_Msk, 1u);
}

/** \brief resets Capture/Compare Status Modification Bit 3 (CC63ST) by Software.
 *
 * \brief <b>Example</b><br>
 * \brief This example resets CC63ST.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Ch3_CompState_Rst();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch3_CompState_Rst(void)
{
  Field_Wrt16(&CCU6->CMPMODIF.reg, (uint16)CCU6_CMPMODIF_MCC63R_Pos, (uint16)CCU6_CMPMODIF_MCC63R_Msk, 1u);
}

/** \brief enables T12 Operating Edge-aligned Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables T12 Operating Edge-aligned Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T12_Edge_Aligned_Mode_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T12_Edge_Aligned_Mode_En(void)
{
  Field_Mod16(&CCU6->TCTR0.reg, (uint16)CCU6_TCTR0_CTM_Pos, (uint16)CCU6_TCTR0_CTM_Msk, 0u);
}

/** \brief enables T12 Operating Center-aligned Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables T12 Operating Center-aligned Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T12_Center_Aligned_Mode_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T12_Center_Aligned_Mode_En(void)
{
  Field_Mod16(&CCU6->TCTR0.reg, (uint16)CCU6_TCTR0_CTM_Pos, (uint16)CCU6_TCTR0_CTM_Msk, 1u);
}

/** \brief selects Timer T12 Input Clock.
 *
 * \param t12clk Timer T12 Input Clock
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Timer T12 Input Clock to fccu/2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T12_Start();
 *    CCU6_T12_Clk_Sel(1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T12_Clk_Sel(uint16 t12clk)
{
  Field_Mod16(&CCU6->TCTR0.reg, (uint16)CCU6_TCTR0_T12CLK_Pos, (uint16)CCU6_TCTR0_T12CLK_Msk, t12clk);
}

/** \brief selects Timer T13 Input Clock.
 *
 * \param t13clk Timer T13 Input Clock
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Timer T13 Input Clock to fccu/4.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T13_Start();
 *    CCU6_T13_Clk_Sel(2u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T13_Clk_Sel(uint16 t13clk)
{
  Field_Mod16(&CCU6->TCTR0.reg, (uint16)CCU6_TCTR0_T13CLK_Pos, (uint16)CCU6_TCTR0_T13CLK_Msk, t13clk);
}

/** \brief enables additional prescaler for Timer T12.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables additional prescaler for Timer T12.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T12_Prescaler_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T12_Prescaler_En(void)
{
  Field_Mod16(&CCU6->TCTR0.reg, (uint16)CCU6_TCTR0_T12PRE_Pos, (uint16)CCU6_TCTR0_T12PRE_Msk, 1u);
}

/** \brief disables additional prescaler for Timer T12.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables additional prescaler for Timer T12.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T12_Prescaler_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T12_Prescaler_Dis(void)
{
  Field_Mod16(&CCU6->TCTR0.reg, (uint16)CCU6_TCTR0_T12PRE_Pos, (uint16)CCU6_TCTR0_T12PRE_Msk, 0u);
}

/** \brief enables additional prescaler for Timer T13.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables additional prescaler for Timer T13.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T13_Prescaler_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T13_Prescaler_En(void)
{
  Field_Mod16(&CCU6->TCTR0.reg, (uint16)CCU6_TCTR0_T13PRE_Pos, (uint16)CCU6_TCTR0_T13PRE_Msk, 1u);
}

/** \brief disables additional prescaler for Timer T13.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables additional prescaler for Timer T13.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T13_Prescaler_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T13_Prescaler_Dis(void)
{
  Field_Mod16(&CCU6->TCTR0.reg, (uint16)CCU6_TCTR0_T13PRE_Pos, (uint16)CCU6_TCTR0_T13PRE_Msk, 0u);
}

/** \brief reads Timer T12 Run Bit.
 *
 * \retval 0 if Timer T12 is stopped.
 * \retval 1 if Timer T12 is running.
 *
 * \brief <b>Example</b><br>
 * \brief This example reads Timer T12 Run Bit.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint8 data;
 *
 *    data = CCU6_T12_Run_Sts();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint8 CCU6_T12_Run_Sts(void)
{
  return ( u1_Field_Rd16(&CCU6->TCTR0.reg, (uint16)CCU6_TCTR0_T12R_Pos, (uint16)CCU6_TCTR0_T12R_Msk) );
}

/** \brief reads Timer T12 Shadow Transfer Enable Bit.
 *
 * \retval 0 if The shadow register transfer is disabled.
 * \retval 1 if The shadow register transfer is enabled.
 *
 * \brief <b>Example</b><br>
 * \brief This example reads Timer T12 Shadow Transfer Enable Bit.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint8 data;
 *
 *    data = CCU6_T12_Str_Sts();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint8 CCU6_T12_Str_Sts(void)
{
  return ( u1_Field_Rd16(&CCU6->TCTR0.reg, (uint16)CCU6_TCTR0_STE12_Pos, (uint16)CCU6_TCTR0_STE12_Msk) );
}

/** \brief reads Count Direction of Timer T12 Bit.
 *
 * \retval 0 if T12 counts up.
 * \retval 1 if T12 counts down.
 *
 * \brief <b>Example</b><br>
 * \brief This example reads Count Direction of Timer T12 Bit.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint8 data;
 *
 *    data = CCU6_T12_Count_Dir_Sts();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint8 CCU6_T12_Count_Dir_Sts(void)
{
  return ( u1_Field_Rd16(&CCU6->TCTR0.reg, (uint16)CCU6_TCTR0_CDIR_Pos, (uint16)CCU6_TCTR0_CDIR_Msk) );
}

/** \brief reads Timer T13 Run Bit.
 *
 * \retval 0 if Timer T13 is stopped.
 * \retval 1 if Timer T13 is running.
 *
 * \brief <b>Example</b><br>
 * \brief This example reads Timer T13 Run Bit.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint8 data;
 *
 *    data = CCU6_T13_Run_Sts();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint8 CCU6_T13_Run_Sts(void)
{
  return ( u1_Field_Rd16(&CCU6->TCTR0.reg, (uint16)CCU6_TCTR0_T13R_Pos, (uint16)CCU6_TCTR0_T13R_Msk) );
}

/** \brief reads Timer T13 Shadow Transfer Enable Bit.
 *
 * \retval 0 if The shadow register transfer is disabled.
 * \retval 1 if The shadow register transfer is enabled.
 *
 * \brief <b>Example</b><br>
 * \brief This example reads Timer T13 Shadow Transfer Enable Bit.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint8 data;
 *
 *    data = CCU6_T13_Str_Sts();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint8 CCU6_T13_Str_Sts(void)
{
  return ( u1_Field_Rd16(&CCU6->TCTR0.reg, (uint16)CCU6_TCTR0_STE13_Pos, (uint16)CCU6_TCTR0_STE13_Msk) );
}

/** \brief enables Timer T12 Single Shot.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Timer T12 Single Shot.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T12_Single_Shot_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T12_Single_Shot_En(void)
{
  Field_Mod16(&CCU6->TCTR2.reg, (uint16)CCU6_TCTR2_T12SSC_Pos, (uint16)CCU6_TCTR2_T12SSC_Msk, 1u);
}

/** \brief disables Timer T12 Single Shot.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Timer T12 Single Shot.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T12_Single_Shot_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T12_Single_Shot_Dis(void)
{
  Field_Mod16(&CCU6->TCTR2.reg, (uint16)CCU6_TCTR2_T12SSC_Pos, (uint16)CCU6_TCTR2_T12SSC_Msk, 0u);
}

/** \brief selects Timer T13 Trigger Event Control.
 *
 * \param t13tec Timer T13 Trigger Event Control
 *
 * \brief <b>Example</b><br>
 * \brief This example sets T13R upon a period-match of T12.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T13_Trig_Event_Sel(5u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T13_Trig_Event_Sel(uint16 t13tec)
{
  Field_Mod16(&CCU6->TCTR2.reg, (uint16)CCU6_TCTR2_T13TEC_Pos, (uint16)CCU6_TCTR2_T13TEC_Msk, t13tec);
}

/** \brief selects Timer T13 Trigger Event Direction.
 *
 * \param t13ted Timer T13 Trigger Event Direction
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Timer T13 Trigger Event Direction to Up.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T13_Trig_Event_Dir_Sel(1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T13_Trig_Event_Dir_Sel(uint16 t13ted)
{
  Field_Mod16(&CCU6->TCTR2.reg, (uint16)CCU6_TCTR2_T13TED_Pos, (uint16)CCU6_TCTR2_T13TED_Msk, t13ted);
}

/** \brief selects Timer T12 External Run.
 *
 * \param t12rsel Timer T12 External Run
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Timer T12 External Run to Rising edge.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T12_Ext_Run_Sel(1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T12_Ext_Run_Sel(uint16 t12rsel)
{
  Field_Mod16(&CCU6->TCTR2.reg, (uint16)CCU6_TCTR2_T12RSEL_Pos, (uint16)CCU6_TCTR2_T12RSEL_Msk, t12rsel);
}

/** \brief selects Timer T13 External Run.
 *
 * \param t13rsel Timer T13 External Run
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Timer T13 External Run to Rising edge.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T13_Ext_Run_Sel(1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T13_Ext_Run_Sel(uint16 t13rsel)
{
  Field_Mod16(&CCU6->TCTR2.reg, (uint16)CCU6_TCTR2_T13RSEL_Pos, (uint16)CCU6_TCTR2_T13RSEL_Msk, t13rsel);
}

/** \brief enables Timer T12 Modulation Configuration
 *
 * \param ccu6_mask Timer T12 Modulation Configuration
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Timer T12 Modulation of CC60.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T12_Modulation_En(1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T12_Modulation_En(uint16 ccu6_mask)
{
  Field_Mod16(&CCU6->MODCTR.reg, (uint16)CCU6_MODCTR_T12MODEN_Pos, (uint16)CCU6_MODCTR_T12MODEN_Msk, (ccu6_mask));
}

/** \brief disables Timer T12 Modulation Configuration
 *
 * \param ccu6_mask Timer T12 Modulation Configuration
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Timer T12 Modulation of CC60.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T12_Modulation_Dis(1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T12_Modulation_Dis(uint16 ccu6_mask)
{
  Field_Mod16(&CCU6->MODCTR.reg, (uint16)CCU6_MODCTR_T12MODEN_Pos, (uint16)((ccu6_mask << (uint16)CCU6_MODCTR_T12MODEN_Pos) & (uint16)CCU6_MODCTR_T12MODEN_Msk), 0);
}

/** \brief enables Timer T13 Modulation Configuration
 *
 * \param ccu6_mask Timer T13 Modulation Configuration
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Timer T13 Modulation of CC60.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T13_Modulation_En(1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T13_Modulation_En(uint16 ccu6_mask)
{
  Field_Mod16(&CCU6->MODCTR.reg, (uint16)CCU6_MODCTR_T13MODEN_Pos, (uint16)CCU6_MODCTR_T13MODEN_Msk, (ccu6_mask));
}

/** \brief disables Timer T13 Modulation Configuration
 *
 * \param ccu6_mask Timer T13 Modulation Configuration
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Timer T13 Modulation of CC60.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T13_Modulation_Dis(1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T13_Modulation_Dis(uint16 ccu6_mask)
{
  Field_Mod16(&CCU6->MODCTR.reg, (uint16)CCU6_MODCTR_T13MODEN_Pos, (uint16)((ccu6_mask << (uint16)CCU6_MODCTR_T13MODEN_Pos) & (uint16)CCU6_MODCTR_T13MODEN_Msk), 0);
}

/** \brief enables Multi-Channel Mode
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Multi-Channel Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Multi_Ch_Mode_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Multi_Ch_Mode_En(void)
{
  Field_Mod16(&CCU6->MODCTR.reg, (uint16)CCU6_MODCTR_MCMEN_Pos, (uint16)CCU6_MODCTR_MCMEN_Msk, 1u);
}

/** \brief disables Multi-Channel Mode
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Multi-Channel Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Multi_Ch_Mode_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Multi_Ch_Mode_Dis(void)
{
  Field_Mod16(&CCU6->MODCTR.reg, (uint16)CCU6_MODCTR_MCMEN_Pos, (uint16)CCU6_MODCTR_MCMEN_Msk, 0u);
}

/** \brief enables Compare Timer T13 Output
 *
 * \brief <b>Example</b><br>
 * \brief This example enables The alternate output function COUT63.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T13_Compare_Out_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T13_Compare_Out_En(void)
{
  Field_Mod16(&CCU6->MODCTR.reg, (uint16)CCU6_MODCTR_ECT13O_Pos, (uint16)CCU6_MODCTR_ECT13O_Msk, 1u);
}

/** \brief disables Compare Timer T13 Output
 *
 * \brief <b>Example</b><br>
 * \brief This example disables The alternate output function COUT63.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T13_Compare_Out_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T13_Compare_Out_Dis(void)
{
  Field_Mod16(&CCU6->MODCTR.reg, (uint16)CCU6_MODCTR_ECT13O_Pos, (uint16)CCU6_MODCTR_ECT13O_Msk, 0u);
}

/** \brief enables T12 zero-match Trap Mode
 *
 * \brief <b>Example</b><br>
 * \brief This example enables T12 zero-match Trap Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Trap_T12_ZM_Exit_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Trap_T12_ZM_Exit_En(void)
{
  Field_Mod16(&CCU6->TRPCTR.reg, (uint16)CCU6_TRPCTR_TRPM0_Pos, (uint16)(CCU6_TRPCTR_TRPM0_Msk | CCU6_TRPCTR_TRPM1_Msk), 0u);
}

/** \brief enables T13 zero-match Trap Mode
 *
 * \brief <b>Example</b><br>
 * \brief This example enables T13 zero-match Trap Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Trap_T13_ZM_Exit_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Trap_T13_ZM_Exit_En(void)
{
  Field_Mod16(&CCU6->TRPCTR.reg, (uint16)CCU6_TRPCTR_TRPM0_Pos, (uint16)(CCU6_TRPCTR_TRPM0_Msk | CCU6_TRPCTR_TRPM1_Msk), 1u);
}

/** \brief enables Trap Immediately without any synchronization to T12 or T13.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Trap Immediately.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Trap_Asynch_Exit_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Trap_Asynch_Exit_En(void)
{
  Field_Mod16(&CCU6->TRPCTR.reg, (uint16)CCU6_TRPCTR_TRPM0_Pos, (uint16)(CCU6_TRPCTR_TRPM0_Msk | CCU6_TRPCTR_TRPM1_Msk), 3u);
}

/** \brief enables Hardware reset of the Trap Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Hardware reset of the Trap Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Trap_HW_Clr_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Trap_HW_Clr_En(void)
{
  Field_Mod16(&CCU6->TRPCTR.reg, (uint16)CCU6_TRPCTR_TRPM2_Pos, (uint16)CCU6_TRPCTR_TRPM2_Msk, 0u);
}

/** \brief enables Software reset of the Trap Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Software reset of the Trap Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Trap_SW_Clr_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Trap_SW_Clr_En(void)
{
  Field_Mod16(&CCU6->TRPCTR.reg, (uint16)CCU6_TRPCTR_TRPM2_Pos, (uint16)CCU6_TRPCTR_TRPM2_Msk, 1u);
}

/** \brief enables the trap functionality for T13.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables the trap functionality for T13.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Trap_T13_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Trap_T13_En(void)
{
  Field_Mod16(&CCU6->TRPCTR.reg, (uint16)CCU6_TRPCTR_TRPEN13_Pos, (uint16)CCU6_TRPCTR_TRPEN13_Msk, 1u);
}

/** \brief disables The trap functionality for T13.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables the trap functionality for T13.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Trap_T13_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Trap_T13_Dis(void)
{
  Field_Mod16(&CCU6->TRPCTR.reg, (uint16)CCU6_TRPCTR_TRPEN13_Pos, (uint16)CCU6_TRPCTR_TRPEN13_Msk, 0u);
}

/** \brief enables the trap functionality based on the input pin CTRAP.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables the trap functionality based on the input pin CTRAP.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Trap_Pin_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Trap_Pin_En(void)
{
  Field_Mod16(&CCU6->TRPCTR.reg, (uint16)CCU6_TRPCTR_TRPPEN_Pos, (uint16)CCU6_TRPCTR_TRPPEN_Msk, 1u);
}

/** \brief disables the trap functionality based on the input pin CTRAP.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables the trap functionality based on the input pin CTRAP.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Trap_Pin_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Trap_Pin_Dis(void)
{
  Field_Mod16(&CCU6->TRPCTR.reg, (uint16)CCU6_TRPCTR_TRPPEN_Pos, (uint16)CCU6_TRPCTR_TRPPEN_Msk, 0u);
}

/** \brief enables the trap functionality of a corresponding output.
 *
 * \param ccu6_mask corresponding output signals
 *
 * \brief <b>Example</b><br>
 * \brief This example enables the trap functionality of COUT60.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Trap_Channel_En(2u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Trap_Channel_En(uint16 ccu6_mask)
{
  Field_Mod16(&CCU6->TRPCTR.reg, (uint16)CCU6_TRPCTR_TRPEN_Pos, (uint16)CCU6_TRPCTR_TRPEN_Msk, ccu6_mask);
}

/** \brief Sets the passive state to "after" the compare value
 *
 * \param ccu6_mask sets the passive state relative to the compare value for Channel 2..0
 * <table>
 * <caption id="multi_row2">bit encoding of ccu6_mask</caption>
 * <tr><th>5<th>4<th>3<th>2<th>1<th>0
 * <tr><td>Ch2c<td>Ch2t<td>Ch1c<td>Ch1t<td>Ch0c<td>Ch0t
 * </table>
 *        1 = passive state after compare<br>
 *        0 = passive state before compare
 *
 *
 * \brief <b>Example</b><br>
 * \brief This example sets
 *        - Ch0t = passive state before compare
 *        - Ch0c = passive state after compare
 *        - Ch1t = passive state before compare
 *        - Ch1c = passive state after compare
 *        - Ch2t = passive state before compare
 *        - Ch2c = passive state after compare
 *
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Passive_State_After_Compare_Sel(0x2A);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Passive_State_After_Compare_Sel(uint16 ccu6_mask)
{
  Field_Mod16(&CCU6->CMPSTAT.reg, (uint16)CCU6_CMPSTAT_CC60PS_Pos, (uint16)0x3F00, ccu6_mask);
  CCU6_T12_Str_En();
}

/** \brief sets Passive High Level of CC60.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Passive High Level of CC60.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Ch0t_Passive_Level_High_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch0t_Passive_Level_High_Set(void)
{
  Field_Mod16(&CCU6->PSLR.reg, 0u, 0x01u, 1u);
}

/** \brief sets Passive Low Level of CC60.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Passive Low Level of CC60.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Ch0t_Passive_Level_Low_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch0t_Passive_Level_Low_Set(void)
{
  Field_Mod16(&CCU6->PSLR.reg, 0u, 0x01u, 0u);
}

/** \brief sets Passive High Level of COUT60.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Passive High Level of COUT60.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Ch0c_Passive_Level_High_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch0c_Passive_Level_High_Set(void)
{
  Field_Mod16(&CCU6->PSLR.reg, 1u, 0x02u, 1u);
}

/** \brief sets Passive Low Level of COUT60.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Passive Low Level of COUT60.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Ch0c_Passive_Level_Low_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch0c_Passive_Level_Low_Set(void)
{
  Field_Mod16(&CCU6->PSLR.reg, 1u, 0x02u, 0u);
}

/** \brief sets Passive High Level of CC61.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Passive High Level of CC61.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Ch1t_Passive_Level_High_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch1t_Passive_Level_High_Set(void)
{
  Field_Mod16(&CCU6->PSLR.reg, 2u, 0x04u, 1u);
}

/** \brief sets Passive Low Level of CC61.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Passive Low Level of CC61.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Ch1t_Passive_Level_Low_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch1t_Passive_Level_Low_Set(void)
{
  Field_Mod16(&CCU6->PSLR.reg, 2u, 0x04u, 0u);
}

/** \brief sets Passive High Level of COUT61.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Passive High Level of COUT61.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Ch1c_Passive_Level_High_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch1c_Passive_Level_High_Set(void)
{
  Field_Mod16(&CCU6->PSLR.reg, 3u, 0x08u, 1u);
}

/** \brief sets Passive Low Level of COUT61.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Passive Low Level of COUT61.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Ch1c_Passive_Level_Low_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch1c_Passive_Level_Low_Set(void)
{
  Field_Mod16(&CCU6->PSLR.reg, 3u, 0x08u, 0u);
}

/** \brief sets Passive High Level of CC62.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Passive High Level of CC62.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Ch2t_Passive_Level_High_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch2t_Passive_Level_High_Set(void)
{
  Field_Mod16(&CCU6->PSLR.reg, 4u, 0x10u, 1u);
}

/** \brief sets Passive Low Level of CC62.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Passive Low Level of CC62.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Ch2t_Passive_Level_Low_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch2t_Passive_Level_Low_Set(void)
{
  Field_Mod16(&CCU6->PSLR.reg, 4u, 0x10u, 0u);
}

/** \brief sets Passive High Level of COUT62.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Passive High Level of COUT62.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Ch2c_Passive_Level_High_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch2c_Passive_Level_High_Set(void)
{
  Field_Mod16(&CCU6->PSLR.reg, 5u, 0x20u, 1u);
}

/** \brief sets Passive Low Level of COUT62.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Passive Low Level of COUT62.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Ch2c_Passive_Level_Low_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch2c_Passive_Level_Low_Set(void)
{
  Field_Mod16(&CCU6->PSLR.reg, 5u, 0x20u, 0u);
}

/** \brief sets Compare Corresponding Outputs Passive High Level.
 *
 * \param ccu6_mask sets the passive state level for Channel 2..0
 * <table>
 * <caption id="multi_row3">bit encoding of ccu6_mask</caption>
 * <tr><th>5<th>4<th>3<th>2<th>1<th>0
 * <tr><td>Ch2c<td>Ch2t<td>Ch1c<td>Ch1t<td>Ch0c<td>Ch0t
 * </table>
 *        1 = passive state high level<br>
 *        0 = passive state low level
 *
 * \brief <b>Example</b><br>
 * \brief This example sets
 *        - Ch0t = passive state low level
 *        - Ch0c = passive state low level
 *        - Ch1t = passive state low level
 *        - Ch1c = passive state low level
 *        - Ch2t = passive state low level
 *        - Ch2c = passive state high level
 *
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Passive_Level_High_Sel(32u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Passive_Level_High_Sel(uint16 ccu6_mask)
{
  Field_Mod16(&CCU6->PSLR.reg, (uint16)CCU6_PSLR_PSL_Pos, (uint16)CCU6_PSLR_PSL_Msk, ccu6_mask);
}

/** \brief sets Passive State Level of Output COUT63.
 *
 * \param lvl Passive State Level of COUT63
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Passive High Level of Output COUT63.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Passiv_Level_Ch3_Sel(1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Passiv_Level_Ch3_Sel(uint16 lvl)
{
  Field_Mod16(&CCU6->PSLR.reg, (uint16)CCU6_PSLR_PSL63_Pos, (uint16)CCU6_PSLR_PSL63_Msk, lvl);
}

/** \brief sets Multi-Channel PWM Pattern Shadow.
 *
 * \param ccu6_mask PWM Pattern Shadow Mask
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PWM Pattern Shadow for output CC60.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_Multi_Ch_PWM_Shadow_Reg_Load(0u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Multi_Ch_PWM_Shadow_Reg_Load(uint16 ccu6_mask)
{
  Field_Mod16(&CCU6->MCMOUTS.reg, (uint16)CCU6_MCMOUTS_MCMPS_Pos, (uint16)CCU6_MCMOUTS_MCMPS_Msk, ccu6_mask);
}

/** \brief enables Shadow Transfer Request for MCMPS by Software.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Shadow Transfer Request for MCMPS by Software.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_MCM_PWM_Str_SW_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_MCM_PWM_Str_SW_En(void)
{
  Field_Mod16(&CCU6->MCMOUTS.reg, (uint16)CCU6_MCMOUTS_STRMCM_Pos, (uint16)CCU6_MCMOUTS_STRMCM_Msk, 1u);
}

/** \brief enables Shadow Transfer Request for MCMPS by Hardware.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Shadow Transfer Request for MCMPS by Hardware.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_MCM_PWM_Str_HW_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_MCM_PWM_Str_HW_En(void)
{
  Field_Mod16(&CCU6->MCMOUTS.reg, (uint16)CCU6_MCMOUTS_STRMCM_Pos, (uint16)CCU6_MCMOUTS_STRMCM_Msk, 0u);
}

/** \brief sets Expected Hall Pattern Shadow of CCPOSx.
 *
 * \param mcm_mask_ccpos Expected Hall Pattern Shadow Mask
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Expected Hall Pattern Shadow of CCPOS0.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_MCM_Expected_Hall_Shadow_Reg_Load(1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_MCM_Expected_Hall_Shadow_Reg_Load(uint16 mcm_mask_ccpos)
{
  Field_Mod16(&CCU6->MCMOUTS.reg, (uint16)CCU6_MCMOUTS_EXPHS_Pos, (uint16)CCU6_MCMOUTS_EXPHS_Msk, mcm_mask_ccpos);
}

/** \brief sets Current Hall Pattern Shadow of CCPOSx.
 *
 * \param mcm_mask_ccpos Current Hall Pattern Shadow Mask
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Current Hall Pattern Shadow of CCPOS0.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_MCM_Current_Hall_Shadow_Reg_Load(1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_MCM_Current_Hall_Shadow_Reg_Load(uint16 mcm_mask_ccpos)
{
  Field_Mod16(&CCU6->MCMOUTS.reg, (uint16)CCU6_MCMOUTS_CURHS_Pos, (uint16)CCU6_MCMOUTS_CURHS_Msk, mcm_mask_ccpos);
}

/** \brief enables Shadow Transfer Request for the Hall Pattern by Software.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Shadow Transfer Request for the Hall Pattern by Software.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_MCM_Hall_Str_SW_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_MCM_Hall_Str_SW_En(void)
{
  Field_Mod16(&CCU6->MCMOUTS.reg, (uint16)CCU6_MCMOUTS_STRHP_Pos, (uint16)CCU6_MCMOUTS_STRHP_Msk, 1u);
}

/** \brief enables Shadow Transfer Request for the Hall Pattern by Hardware.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Shadow Transfer Request for the Hall Pattern by Hardware.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_MCM_Hall_Str_HW_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_MCM_Hall_Str_HW_En(void)
{
  Field_Mod16(&CCU6->MCMOUTS.reg, (uint16)CCU6_MCMOUTS_STRHP_Pos, (uint16)CCU6_MCMOUTS_STRHP_Msk, 0u);
}

/** \brief reads Multi-Channel PWM Pattern.
 *
 * \return mask of output which can deliver the PWM generated by T12 or T13, values between 0..5
 *
 * \brief <b>Example</b><br>
 * \brief This example reads Multi-Channel PWM Pattern.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint8 data;
 *
 *    data = CCU6_MCM_PWM_Pattern_Sts();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint8 CCU6_MCM_PWM_Pattern_Sts(void)
{
  return ( u8_Field_Rd16(&CCU6->MCMOUT.reg, (uint16)CCU6_MCMOUT_MCMP_Pos, (uint16)CCU6_MCMOUT_MCMP_Msk) );
}

/** \brief reads Reminder Flag Status.
 *
 * \retval 0 if No shadow transfer.
 * \retval 1 if Shadow transfer.
 *
 * \brief <b>Example</b><br>
 * \brief This example reads Reminder Flag Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint8 data;
 *
 *    data = CCU6_MCM_PWM_Str_Req_Sts();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint8 CCU6_MCM_PWM_Str_Req_Sts(void)
{
  return ( u8_Field_Rd16(&CCU6->MCMOUT.reg, (uint16)CCU6_MCMOUT_R_Pos, (uint16)CCU6_MCMOUT_R_Msk) );
}

/** \brief reads Expected Hall Pattern of CCPOSx.
 *
 * \return Expected Hall Pattern Mask, values between 0..2
 *
 * \brief <b>Example</b><br>
 * \brief This example reads Expected Hall Pattern of CCPOSx.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint8 data;
 *
 *    data = CCU6_MCM_Expected_Hall_Sts();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint8 CCU6_MCM_Expected_Hall_Sts(void)
{
  return ( u8_Field_Rd16(&CCU6->MCMOUT.reg, (uint16)CCU6_MCMOUT_EXPH_Pos, (uint16)CCU6_MCMOUT_EXPH_Msk) );
}

/** \brief reads Current Hall Pattern of CCPOSx.
 *
 * \return Current Hall Pattern Mask, values between 0..2
 *
 * \brief <b>Example</b><br>
 * \brief This example reads Current Hall Pattern of CCPOSx.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint8 data;
 *
 *    data = CCU6_MCM_Current_Hall_Sts();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint8 CCU6_MCM_Current_Hall_Sts(void)
{
  return ( u8_Field_Rd16(&CCU6->MCMOUT.reg, (uint16)CCU6_MCMOUT_CURH_Pos, (uint16)CCU6_MCMOUT_CURH_Msk) );
}

/** \brief selects Switching Mode.
 *
 * \param swsel Switching Mode
 *
 * \brief <b>Example</b><br>
 * \brief This example sets T13 period-match Switching Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_MCM_Switch_Sel(2u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_MCM_Switch_Sel(uint16 swsel)
{
  Field_Mod16(&CCU6->MCMCTR.reg, (uint16)CCU6_MCMCTR_SWSEL_Pos, (uint16)CCU6_MCMCTR_SWSEL_Msk, swsel);
}

/** \brief sets No Trigger Switching Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets No Trigger Switching Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_MCM_Switch_NoTrigger_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_MCM_Switch_NoTrigger_Set(void)
{
  Field_Mod16(&CCU6->MCMCTR.reg, (uint16)CCU6_MCMCTR_SWSEL_Pos, (uint16)CCU6_MCMCTR_SWSEL_Msk, 0u);
}

/** \brief sets Correct Hall Switching Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Correct Hall Switching Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_MCM_Switch_CorrectHall_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_MCM_Switch_CorrectHall_Set(void)
{
  Field_Mod16(&CCU6->MCMCTR.reg, (uint16)CCU6_MCMCTR_SWSEL_Pos, (uint16)CCU6_MCMCTR_SWSEL_Msk, 1u);
}

/** \brief sets T13 period-match Switching Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets T13 period-match Switching Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_MCM_Switch_T13_PM_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_MCM_Switch_T13_PM_Set(void)
{
  Field_Mod16(&CCU6->MCMCTR.reg, (uint16)CCU6_MCMCTR_SWSEL_Pos, (uint16)CCU6_MCMCTR_SWSEL_Msk, 2u);
}

/** \brief sets T12 one-match Switching Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets T12 one-match Switching Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_MCM_Switch_T12_ON_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_MCM_Switch_T12_ON_Set(void)
{
  Field_Mod16(&CCU6->MCMCTR.reg, (uint16)CCU6_MCMCTR_SWSEL_Pos, (uint16)CCU6_MCMCTR_SWSEL_Msk, 3u);
}

/** \brief sets T12 channel1 compare-match Switching Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets T12 channel1 compare-match Switching Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_MCM_Switch_T12_Ch1_CM_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_MCM_Switch_T12_Ch1_CM_Set(void)
{
  Field_Mod16(&CCU6->MCMCTR.reg, (uint16)CCU6_MCMCTR_SWSEL_Pos, (uint16)CCU6_MCMCTR_SWSEL_Msk, 4u);
}

/** \brief sets T12 period-match Switching Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets T12 period-match Switching Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_MCM_Switch_T12_PM_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_MCM_Switch_T12_PM_Set(void)
{
  Field_Mod16(&CCU6->MCMCTR.reg, (uint16)CCU6_MCMCTR_SWSEL_Pos, (uint16)CCU6_MCMCTR_SWSEL_Msk, 5u);
}

/** \brief sets Direct Switching Synchronization.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Direct Switching Synchronization.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_MCM_Switch_Sync_direct_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_MCM_Switch_Sync_direct_Sel(void)
{
  Field_Mod16(&CCU6->MCMCTR.reg, (uint16)CCU6_MCMCTR_SWSYN_Pos, (uint16)CCU6_MCMCTR_SWSYN_Msk, 0u);
}

/** \brief sets T13 zero-match Switching Synchronization.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets T13 zero-match Switching Synchronization.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_MCM_Switch_Sync_T13_ZM_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_MCM_Switch_Sync_T13_ZM_Sel(void)
{
  Field_Mod16(&CCU6->MCMCTR.reg, (uint16)CCU6_MCMCTR_SWSYN_Pos, (uint16)CCU6_MCMCTR_SWSYN_Msk, 1u);
}

/** \brief sets T12 zero-match Switching Synchronization.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets T12 zero-match Switching Synchronization.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_MCM_Switch_Sync_T12_ZM_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_MCM_Switch_Sync_T12_ZM_Sel(void)
{
  Field_Mod16(&CCU6->MCMCTR.reg, (uint16)CCU6_MCMCTR_SWSYN_Pos, (uint16)CCU6_MCMCTR_SWSYN_Msk, 2u);
}

/** \brief enables Shadow Transfer for T12 Upcounting.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Shadow Transfer for T12 Upcounting.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_MCM_Str_T12_Up_Cnt_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_MCM_Str_T12_Up_Cnt_En(void)
{
  Field_Mod16(&CCU6->MCMCTR.reg, (uint16)CCU6_MCMCTR_STE12U_Pos, (uint16)CCU6_MCMCTR_STE12U_Msk, 1u);
}

/** \brief disables Shadow Transfer for T12 Upcounting.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Shadow Transfer for T12 Upcounting.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_MCM_Str_T12_Up_Cnt_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_MCM_Str_T12_Up_Cnt_Dis(void)
{
  Field_Mod16(&CCU6->MCMCTR.reg, (uint16)CCU6_MCMCTR_STE12U_Pos, (uint16)CCU6_MCMCTR_STE12U_Msk, 0u);
}

/** \brief enables Shadow Transfer for T12 Downcounting.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Shadow Transfer for T12 Downcounting.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_MCM_Str_T12_Down_Cnt_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_MCM_Str_T12_Down_Cnt_En(void)
{
  Field_Mod16(&CCU6->MCMCTR.reg, (uint16)CCU6_MCMCTR_STE12D_Pos, (uint16)CCU6_MCMCTR_STE12D_Msk, 1u);
}

/** \brief disables Shadow Transfer for T12 Downcounting.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Shadow Transfer for T12 Downcounting.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_MCM_Str_T12_Down_Cnt_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_MCM_Str_T12_Down_Cnt_Dis(void)
{
  Field_Mod16(&CCU6->MCMCTR.reg, (uint16)CCU6_MCMCTR_STE12D_Pos, (uint16)CCU6_MCMCTR_STE12D_Msk, 0u);
}

/** \brief enables Shadow Transfer for T13 Upcounting.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Shadow Transfer for T13 Upcounting.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_MCM_Str_T13_Up_Cnt_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_MCM_Str_T13_Up_Cnt_En(void)
{
  Field_Mod16(&CCU6->MCMCTR.reg, (uint16)CCU6_MCMCTR_STE13U_Pos, (uint16)CCU6_MCMCTR_STE13U_Msk, 1u);
}

/** \brief disables Shadow Transfer for T13 Upcounting.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Shadow Transfer for T13 Upcounting.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_MCM_Str_T13_Up_Cnt_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_MCM_Str_T13_Up_Cnt_Dis(void)
{
  Field_Mod16(&CCU6->MCMCTR.reg, (uint16)CCU6_MCMCTR_STE13U_Pos, (uint16)CCU6_MCMCTR_STE13U_Msk, 0u);
}

/** \brief reads Capture, Compare-Match Rising Edge Flag Status for Channel 0.
 *
 * \return Capture, Compare-Match Rising Edge Flag Status for Channel 0
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Capture, Compare-Match Rising Edge Interrupt for Channel 0.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_CH0_CM_R_Int_En();
 *   if (CCU6_T12_CM_CC60_Int_Rise_Sts() == (uint8)1)
 *   {
 *     CCU6_CH0_CM_R_CALLBACK();
 *     CCU6_CH0_CM_R_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint8 CCU6_T12_CM_CC60_Int_Rise_Sts(void)
{
  return ( u1_Field_Rd16(&CCU6->IS.reg, (uint16)CCU6_IS_ICC60R_Pos, (uint16)CCU6_IS_ICC60R_Msk) );
}

/** \brief reads Capture, Compare-Match Rising Edge Flag Status for Channel 1.
 *
 * \return Capture, Compare-Match Rising Edge Flag Status for Channel 1
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Capture, Compare-Match Rising Edge Interrupt for Channel 1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_CH1_CM_R_Int_En();
 *   if (CCU6_T12_CM_CC61_Int_Rise_Sts() == (uint8)1)
 *   {
 *     CCU6_CH1_CM_R_CALLBACK();
 *     CCU6_CH1_CM_R_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint8 CCU6_T12_CM_CC61_Int_Rise_Sts(void)
{
  return ( u1_Field_Rd16(&CCU6->IS.reg, (uint16)CCU6_IS_ICC61R_Pos, (uint16)CCU6_IS_ICC61R_Msk) );
}

/** \brief reads Capture, Compare-Match Rising Edge Flag Status for Channel 2.
 *
 * \return Capture, Compare-Match Rising Edge Flag Status for Channel 2
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Capture, Compare-Match Rising Edge Interrupt for Channel 2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_CH2_CM_R_Int_En();
 *   if (CCU6_T12_CM_CC62_Int_Rise_Sts() == (uint8)1)
 *   {
 *     CCU6_CH2_CM_R_CALLBACK();
 *     CCU6_CH2_CM_R_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint8 CCU6_T12_CM_CC62_Int_Rise_Sts(void)
{
  return ( u1_Field_Rd16(&CCU6->IS.reg, (uint16)CCU6_IS_ICC62R_Pos, (uint16)CCU6_IS_ICC62R_Msk) );
}

/** \brief reads Capture, Compare-Match Falling Edge Flag Status for Channel 0.
 *
 * \return Capture, Compare-Match Falling Edge Flag Status for Channel 0
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Capture, Compare-Match Falling Edge Interrupt for Channel 0.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_CH0_CM_F_Int_En();
 *   if (CCU6_T12_CM_CC60_Int_Fall_Sts() == (uint8)1)
 *   {
 *     CCU6_CH0_CM_F_CALLBACK();
 *     CCU6_CH0_CM_F_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint8 CCU6_T12_CM_CC60_Int_Fall_Sts(void)
{
  return ( u1_Field_Rd16(&CCU6->IS.reg, (uint16)CCU6_IS_ICC60F_Pos, (uint16)CCU6_IS_ICC60F_Msk) );
}

/** \brief reads Capture, Compare-Match Falling Edge Flag Status for Channel 1.
 *
 * \return Capture, Compare-Match Falling Edge Flag Status for Channel 1
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Capture, Compare-Match Falling Edge Interrupt for Channel 1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_CH1_CM_F_Int_En();
 *   if (CCU6_T12_CM_CC61_Int_Fall_Sts() == (uint8)1)
 *   {
 *     CCU6_CH1_CM_F_CALLBACK();
 *     CCU6_CH1_CM_F_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint8 CCU6_T12_CM_CC61_Int_Fall_Sts(void)
{
  return ( u1_Field_Rd16(&CCU6->IS.reg, (uint16)CCU6_IS_ICC61F_Pos, (uint16)CCU6_IS_ICC61F_Msk) );
}

/** \brief reads Capture, Compare-Match Falling Edge Flag Status for Channel 2.
 *
 * \return Capture, Compare-Match Falling Edge Flag Status for Channel 2
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Capture, Compare-Match Falling Edge Interrupt for Channel 2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_CH2_CM_F_Int_En();
 *   if (CCU6_T12_CM_CC62_Int_Fall_Sts() == (uint8)1)
 *   {
 *     CCU6_CH2_CM_F_CALLBACK();
 *     CCU6_CH2_CM_F_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint8 CCU6_T12_CM_CC62_Int_Fall_Sts(void)
{
  return ( u1_Field_Rd16(&CCU6->IS.reg, (uint16)CCU6_IS_ICC62F_Pos, (uint16)CCU6_IS_ICC62F_Msk) );
}

/** \brief reads Timer T12 One-Match Flag Status.
 *
 * \return Timer T12 One-Match Flag Status
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Interrupt for T12 One-Match.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_T12_OM_Int_En();
 *   if (CCU6_T12_OM_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_T12_OM_CALLBACK();
 *     CCU6_T12_OM_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint8 CCU6_T12_OM_Int_Sts(void)
{
  return ( u1_Field_Rd16(&CCU6->IS.reg, (uint16)CCU6_IS_T12OM_Pos, (uint16)CCU6_IS_T12OM_Msk) );
}

/** \brief reads Timer T12 Period-Match Flag Status.
 *
 * \return Timer T12 Period-Match Flag Status
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Interrupt for T12 Period-Match.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_T12_PM_Int_En();
 *   if (CCU6_T12_PM_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_T12_PM_CALLBACK();
 *     CCU6_T12_PM_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint8 CCU6_T12_PM_Int_Sts(void)
{
  return ( u1_Field_Rd16(&CCU6->IS.reg, (uint16)CCU6_IS_T12PM_Pos, (uint16)CCU6_IS_T12PM_Msk) );
}

/** \brief reads Timer T13 Compare-Match Flag Status.
 *
 * \return Timer T13 Compare-Match Flag Status
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Interrupt for T13 Compare-Match.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_T13_CM_Int_En();
 *   if (CCU6_T13_CM_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_T13_CM_CALLBACK();
 *     CCU6_T13_CM_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint8 CCU6_T13_CM_Int_Sts(void)
{
  return ( u1_Field_Rd16(&CCU6->IS.reg, (uint16)CCU6_IS_T13CM_Pos, (uint16)CCU6_IS_T13CM_Msk) );
}

/** \brief reads Timer T13 Period-Match Flag Status.
 *
 * \return Timer T13 Period-Match Flag Status
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Interrupt for T13 Period-Match.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_T13_PM_Int_En();
 *   if (CCU6_T13_PM_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_T13_PM_CALLBACK();
 *     CCU6_T13_PM_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint8 CCU6_T13_PM_Int_Sts(void)
{
  return ( u1_Field_Rd16(&CCU6->IS.reg, (uint16)CCU6_IS_T13PM_Pos, (uint16)CCU6_IS_T13PM_Msk) );
}

/** \brief reads Trap Flag Status.
 *
 * \return Trap Flag Status
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Interrupt for Trap Flag.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_TRAP_Int_En();
 *   if (CCU6_Trap_Flag_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_TRAP_CALLBACK();
 *     CCU6_TRAP_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint8 CCU6_Trap_Flag_Int_Sts(void)
{
  return ( u1_Field_Rd16(&CCU6->IS.reg, (uint16)CCU6_IS_TRPF_Pos, (uint16)CCU6_IS_TRPF_Msk) );
}

/** \brief reads Trap Status.
 *
 * \return Trap Flag Status
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Interrupt for Trap Flag.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_TRAP_Int_En();
 *   if ((CCU6_Trap_Flag_Int_Sts() == (uint8)1) && (CCU6_Trap_State_Int_Sts() == (uint8)1)))
 *   {
 *     CCU6_TRAP_CALLBACK();
 *     CCU6_TRAP_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint8 CCU6_Trap_State_Int_Sts(void)
{
  return ( u1_Field_Rd16(&CCU6->IS.reg, (uint16)CCU6_IS_TRPS_Pos, (uint16)CCU6_IS_TRPS_Msk) );
}

/** \brief reads Correct Hall Event Status.
 *
 * \return Correct Hall Event Status
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Interrupt for Correct Hall Event.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_CHE_Int_En();
 *   if (CCU6_Hall_Correct_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_CORRECT_HALL_CALLBACK();
 *     CCU6_CHE_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint8 CCU6_Hall_Correct_Int_Sts(void)
{
  return ( u1_Field_Rd16(&CCU6->IS.reg, (uint16)CCU6_IS_CHE_Pos, (uint16)CCU6_IS_CHE_Msk) );
}

/** \brief reads Wrong Hall Event Status.
 *
 * \return Wrong Hall Event Status
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Interrupt for Wrong Hall Event.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_WHE_Int_En();
 *   if (CCU6_Hall_Wrong_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_WRONG_HALL_CALLBACK();
 *     CCU6_WHE_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint8 CCU6_Hall_Wrong_Int_Sts(void)
{
  return ( u1_Field_Rd16(&CCU6->IS.reg, (uint16)CCU6_IS_WHE_Pos, (uint16)CCU6_IS_WHE_Msk) );
}

/** \brief reads IDLE Status.
 *
 * \return IDLE Status
 *
 * \brief <b>Example</b><br>
 * \brief This example sets the Interrupt for IDLE Event and reads IDLE Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   uint8 sts;
 *
 *   CCU6_MCM_Idle_Int_Set();
 *   sts = CCU6_MCM_Idle_Int_Sts();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint8 CCU6_MCM_Idle_Int_Sts(void)
{
  return ( u1_Field_Rd16(&CCU6->IS.reg, (uint16)CCU6_IS_IDLE_Pos, (uint16)CCU6_IS_IDLE_Msk) );
}

/** \brief reads Multi-Channel Mode Shadow Transfer Request Status.
 *
 * \return Multi-Channel Mode Shadow Transfer Request Status
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Multi-Channel Mode Shadow Transfer Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_STR_Int_En();
 *   if (CCU6_MCM_Str_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_MCM_STR_CALLBACK();
 *     CCU6_STR_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint8 CCU6_MCM_Str_Int_Sts(void)
{
  return ( u1_Field_Rd16(&CCU6->IS.reg, (uint16)CCU6_IS_STR_Pos, (uint16)CCU6_IS_STR_Msk) );
}

/** \brief sets Capture, Compare-Match Rising Edge Interrupt flag for Channel 0.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Capture, Compare-Match Rising Edge Interrupt for Channel 0.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_CH0_CM_R_Int_En();
 *   CCU6_T12_CM_CC60_Int_Rise_Set();
 *   if (CCU6_T12_CM_CC60_Int_Rise_Sts() == (uint8)1)
 *   {
 *     CCU6_CH0_CM_R_CALLBACK();
 *     CCU6_CH0_CM_R_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T12_CM_CC60_Int_Rise_Set(void)
{
  Field_Wrt16(&CCU6->ISS.reg, (uint16)CCU6_ISS_SCC60R_Pos, (uint16)CCU6_ISS_SCC60R_Msk, 1u);
}

/** \brief sets Capture, Compare-Match Rising Edge Interrupt flag for Channel 1.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Capture, Compare-Match Rising Edge Interrupt for Channel 1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_CH1_CM_R_Int_En();
 *   CCU6_T12_CM_CC61_Int_Rise_Set();
 *   if (CCU6_T12_CM_CC61_Int_Rise_Sts() == (uint8)1)
 *   {
 *     CCU6_CH1_CM_R_CALLBACK();
 *     CCU6_CH1_CM_R_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T12_CM_CC61_Int_Rise_Set(void)
{
  Field_Wrt16(&CCU6->ISS.reg, (uint16)CCU6_ISS_SCC61R_Pos, (uint16)CCU6_ISS_SCC61R_Msk, 1u);
}

/** \brief sets Capture, Compare-Match Rising Edge Interrupt flag for Channel 2.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Capture, Compare-Match Rising Edge Interrupt for Channel 2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_CH2_CM_R_Int_En();
 *   CCU6_T12_CM_CC62_Int_Rise_Set();
 *   if (CCU6_T12_CM_CC62_Int_Rise_Sts() == (uint8)1)
 *   {
 *     CCU6_CH2_CM_R_CALLBACK();
 *     CCU6_CH2_CM_R_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T12_CM_CC62_Int_Rise_Set(void)
{
  Field_Wrt16(&CCU6->ISS.reg, (uint16)CCU6_ISS_SCC62R_Pos, (uint16)CCU6_ISS_SCC62R_Msk, 1u);
}

/** \brief sets Capture, Compare-Match Falling Edge Interrupt flag for Channel 0.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Capture, Compare-Match Falling Edge Interrupt for Channel 0.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_CH0_CM_F_Int_En();
 *   CCU6_T12_CM_CC60_Int_Fall_Set();
 *   if (CCU6_T12_CM_CC60_Int_Fall_Sts() == (uint8)1)
 *   {
 *     CCU6_CH0_CM_F_CALLBACK();
 *     CCU6_CH0_CM_F_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T12_CM_CC60_Int_Fall_Set(void)
{
  Field_Wrt16(&CCU6->ISS.reg, (uint16)CCU6_ISS_SCC60F_Pos, (uint16)CCU6_ISS_SCC60F_Msk, 1u);
}

/** \brief sets Capture, Compare-Match Falling Edge Interrupt flag for Channel 1.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Capture, Compare-Match Falling Edge Interrupt for Channel 1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_CH1_CM_F_Int_En();
 *   CCU6_T12_CM_CC61_Int_Fall_Set();
 *   if (CCU6_T12_CM_CC61_Int_Fall_Sts() == (uint8)1)
 *   {
 *     CCU6_CH1_CM_F_CALLBACK();
 *     CCU6_CH1_CM_F_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T12_CM_CC61_Int_Fall_Set(void)
{
  Field_Wrt16(&CCU6->ISS.reg, (uint16)CCU6_ISS_SCC61F_Pos, (uint16)CCU6_ISS_SCC61F_Msk, 1u);
}

/** \brief sets Capture, Compare-Match Falling Edge Interrupt flag for Channel 2.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Capture, Compare-Match Falling Edge Interrupt for Channel 2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_CH2_CM_F_Int_En();
 *   CCU6_T12_CM_CC62_Int_Fall_Set();
 *   if (CCU6_T12_CM_CC62_Int_Fall_Sts() == (uint8)1)
 *   {
 *     CCU6_CH2_CM_F_CALLBACK();
 *     CCU6_CH2_CM_F_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T12_CM_CC62_Int_Fall_Set(void)
{
  Field_Wrt16(&CCU6->ISS.reg, (uint16)CCU6_ISS_SCC62F_Pos, (uint16)CCU6_ISS_SCC62F_Msk, 1u);
}

/** \brief sets Interrupt for T12 One-Match Flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Interrupt for T12 One-Match.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_T12_OM_Int_En();
 *   CCU6_T12_OM_Int_Set();
 *   if (CCU6_T12_OM_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_T12_OM_CALLBACK();
 *     CCU6_T12_OM_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T12_OM_Int_Set(void)
{
  Field_Wrt16(&CCU6->ISS.reg, (uint16)CCU6_ISS_ST12OM_Pos, (uint16)CCU6_ISS_ST12OM_Msk, 1u);
}

/** \brief sets Interrupt for T12 Period-Match Flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Interrupt for T12 Period-Match.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_T12_PM_Int_En();
 *   CCU6_T12_PM_Int_Set();
 *   if (CCU6_T12_PM_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_T12_PM_CALLBACK();
 *     CCU6_T12_PM_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T12_PM_Int_Set(void)
{
  Field_Wrt16(&CCU6->ISS.reg, (uint16)CCU6_ISS_ST12PM_Pos, (uint16)CCU6_ISS_ST12PM_Msk, 1u);
}

/** \brief sets Interrupt for T13 Compare-Match Flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Interrupt for T13 Compare-Match.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_T13_CM_Int_En();
 *   CCU6_T13_CM_Int_Set();
 *   if (CCU6_T13_CM_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_T13_CM_CALLBACK();
 *     CCU6_T13_CM_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T13_CM_Int_Set(void)
{
  Field_Wrt16(&CCU6->ISS.reg, (uint16)CCU6_ISS_ST13CM_Pos, (uint16)CCU6_ISS_ST13CM_Msk, 1u);
}

/** \brief sets Interrupt for T13 Period-Match Flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Interrupt for T13 Period-Match.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_T13_PM_Int_En();
 *   CCU6_T13_PM_Int_Set();
 *   if (CCU6_T13_PM_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_T13_PM_CALLBACK();
 *     CCU6_T13_PM_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T13_PM_Int_Set(void)
{
  Field_Wrt16(&CCU6->ISS.reg, (uint16)CCU6_ISS_ST13PM_Pos, (uint16)CCU6_ISS_ST13PM_Msk, 1u);
}

/** \brief sets Trap Flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Interrupt for Trap Flag.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_TRAP_Int_En();
 *   CCU6_Trap_Flag_Int_Set();
 *   if (CCU6_Trap_Flag_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_TRAP_CALLBACK();
 *     CCU6_TRAP_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Trap_Flag_Int_Set(void)
{
  Field_Wrt16(&CCU6->ISS.reg, (uint16)CCU6_ISS_STRPF_Pos, (uint16)CCU6_ISS_STRPF_Msk, 1u);
}

/** \brief sets Interrupt for Trap SW Hall Event flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Interrupt for Trap SW Hall Event.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_Trap_SW_Hall_Int_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Trap_SW_Hall_Int_Set(void)
{
  Field_Wrt16(&CCU6->ISS.reg, (uint16)CCU6_ISS_SWHC_Pos, (uint16)CCU6_ISS_SWHC_Msk, 1u);
}

/** \brief sets Interrupt for Correct Hall Event flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Interrupt for Correct Hall Event.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_CHE_Int_En();
 *   CCU6_Hall_Correct_Int_Set();
 *   if (CCU6_Hall_Correct_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_CORRECT_HALL_CALLBACK();
 *     CCU6_CHE_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Hall_Correct_Int_Set(void)
{
  Field_Wrt16(&CCU6->ISS.reg, (uint16)CCU6_ISS_SCHE_Pos, (uint16)CCU6_ISS_SCHE_Msk, 1u);
}

/** \brief sets Interrupt for Wrong Hall Event flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Interrupt for Wrong Hall Event.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_WHE_Int_En();
 *   CCU6_Hall_Wrong_Int_Set();
 *   if (CCU6_Hall_Wrong_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_WRONG_HALL_CALLBACK();
 *     CCU6_WHE_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Hall_Wrong_Int_Set(void)
{
  Field_Wrt16(&CCU6->ISS.reg, (uint16)CCU6_ISS_SWHE_Pos, (uint16)CCU6_ISS_SWHE_Msk, 1u);
}

/** \brief sets Interrupt for IDLE flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets the Interrupt for IDLE Event and reads IDLE Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   uint8 sts;
 *
 *   CCU6_MCM_Idle_Int_Set();
 *   sts = CCU6_MCM_Idle_Int_Sts();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_MCM_Idle_Int_Set(void)
{
  Field_Wrt16(&CCU6->ISS.reg, (uint16)CCU6_ISS_SIDLE_Pos, (uint16)CCU6_ISS_SIDLE_Msk, 1u);
}

/** \brief sets Multi-Channel Mode Shadow Transfer Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Multi-Channel Mode Shadow Transfer Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_STR_Int_En();
 *   CCU6_MCM_Str_Int_Set();
 *   if (CCU6_MCM_Str_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_MCM_STR_CALLBACK();
 *     CCU6_STR_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_MCM_Str_Int_Set(void)
{
  Field_Wrt16(&CCU6->ISS.reg, (uint16)CCU6_ISS_SSTR_Pos, (uint16)CCU6_ISS_SSTR_Msk, 1u);
}

/** \brief selects Interrupt Node Pointer for Channel 0 Interrupts.
 *
 * \param srx Interrupt Node Pointer for Channel 0 Interrupts, values 0..3
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Interrupt output line SR0 for CC60R and treats the Capture, Compare-Match Rising Edge Interrupt for Channel 0.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_Ch0_Int_Node_Sel(0u);
 *   CCU6_CH0_CM_R_Int_En();
 *   if (CCU6_T12_CM_CC60_Int_Rise_Sts() == (uint8)1)
 *   {
 *     CCU6_CH0_CM_R_CALLBACK();
 *     CCU6_CH0_CM_R_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch0_Int_Node_Sel(uint16 srx)
{
  Field_Mod16(&CCU6->INP.reg, (uint16)CCU6_INP_INPCC60_Pos, (uint16)CCU6_INP_INPCC60_Msk, srx);
}

/** \brief selects Interrupt Node Pointer for Channel 1 Interrupts.
 *
 * \param srx Interrupt Node Pointer for Channel 1 Interrupts, values 0..3
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Interrupt output line SR0 for CC61R and treats the Capture, Compare-Match Rising Edge Interrupt for Channel 1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_Ch1_Int_Node_Sel(0u);
 *   CCU6_CH1_CM_R_Int_En();
 *   if (CCU6_T12_CM_CC61_Int_Rise_Sts() == (uint8)1)
 *   {
 *     CCU6_CH1_CM_R_CALLBACK();
 *     CCU6_CH1_CM_R_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch1_Int_Node_Sel(uint16 srx)
{
  Field_Mod16(&CCU6->INP.reg, (uint16)CCU6_INP_INPCC61_Pos, (uint16)CCU6_INP_INPCC61_Msk, srx);
}

/** \brief selects Interrupt Node Pointer for Channel 2 Interrupts.
 *
 * \param srx Interrupt Node Pointer for Channel 2 Interrupts, values 0..3
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Interrupt output line SR0 for CC62R and treats the Capture, Compare-Match Rising Edge Interrupt for Channel 2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_Ch2_Int_Node_Sel(0u);
 *   CCU6_CH2_CM_R_Int_En();
 *   if (CCU6_T12_CM_CC62_Int_Rise_Sts() == (uint8)1)
 *   {
 *     CCU6_CH2_CM_R_CALLBACK();
 *     CCU6_CH2_CM_R_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Ch2_Int_Node_Sel(uint16 srx)
{
  Field_Mod16(&CCU6->INP.reg, (uint16)CCU6_INP_INPCC62_Pos, (uint16)CCU6_INP_INPCC62_Msk, srx);
}

/** \brief selects Interrupt Node Pointer for Error Interrupts.
 *
 * \param srx Interrupt Node Pointer for Error Interrupts, values 0..3
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Interrupt output line SR0 for TRPF and treats the Interrupt for Trap Flag.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_Error_Int_Node_Sel(0u);
 *   CCU6_TRAP_Int_En();
 *   if (CCU6_Trap_Flag_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_TRAP_CALLBACK();
 *     CCU6_TRAP_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Error_Int_Node_Sel(uint16 srx)
{
  Field_Mod16(&CCU6->INP.reg, (uint16)CCU6_INP_INPERR_Pos, (uint16)CCU6_INP_INPERR_Msk, srx);
}

/** \brief selects Interrupt Node Pointer for Timer T12 Interrupts.
 *
 * \param srx Interrupt Node Pointer for Timer T12 Interrupts, values 0..3
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Interrupt output line SR0 for T12OM and treats the Interrupt for T12 One-Match.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_T12_Int_Node_Sel(0u);
 *   CCU6_T12_OM_Int_En();
 *   if (CCU6_T12_OM_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_T12_OM_CALLBACK();
 *     CCU6_T12_OM_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T12_Int_Node_Sel(uint16 srx)
{
  Field_Mod16(&CCU6->INP.reg, (uint16)CCU6_INP_INPT12_Pos, (uint16)CCU6_INP_INPT12_Msk, srx);
}

/** \brief selects Interrupt Node Pointer for Timer T13 Interrupts.
 *
 * \param srx Interrupt Node Pointer for Timer T13 Interrupts, values 0..3
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Interrupt output line SR0 for T13CM and treats the Interrupt for T13 Compare-Match.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_T13_Int_Node_Sel(0u);
 *   CCU6_T13_CM_Int_En();
 *   if (CCU6_T13_CM_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_T13_CM_CALLBACK();
 *     CCU6_T13_CM_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T13_Int_Node_Sel(uint16 srx)
{
  Field_Mod16(&CCU6->INP.reg, (uint16)CCU6_INP_INPT13_Pos, (uint16)CCU6_INP_INPT13_Msk, srx);
}

/** \brief selects Interrupt Node Pointer for CHE Interrupts.
 *
 * \param srx Interrupt Node Pointer for CHE Interrupts, values 0..3
 *
 * \brief <b>Example</b><br>
 * \brief This example selects Interrupt output line SR0 for CHE and treats the Interrupt for Correct Hall Event.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_Hall_Correct_Int_Node_Sel(0u);
 *   CCU6_CHE_Int_En();
 *   if (CCU6_Hall_Correct_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_CORRECT_HALL_CALLBACK();
 *     CCU6_CHE_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_Hall_Correct_Int_Node_Sel(uint16 srx)
{
  Field_Mod16(&CCU6->INP.reg, (uint16)CCU6_INP_INPCHE_Pos, (uint16)CCU6_INP_INPCHE_Msk, srx);
}

/** \brief clears Capture, Compare-Match Rising Edge Interrupt flag for Channel 0.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Capture, Compare-Match Rising Edge Interrupt for Channel 0.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_CH0_CM_R_Int_En();
 *   if (CCU6_T12_CM_CC60_Int_Rise_Sts() == (uint8)1)
 *   {
 *     CCU6_CH0_CM_R_CALLBACK();
 *     CCU6_CH0_CM_R_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_CH0_CM_R_Int_Clr(void)
{
  Field_Wrt16(&CCU6->ISR.reg, (uint16)CCU6_ISR_RCC60R_Pos, (uint16)CCU6_ISR_RCC60R_Msk, 1u);
}

/** \brief clears Capture, Compare-Match Falling Edge Interrupt flag for Channel 0.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Capture, Compare-Match Falling Edge Interrupt for Channel 0.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_CH0_CM_F_Int_En();
 *   if (CCU6_T12_CM_CC60_Int_Fall_Sts() == (uint8)1)
 *   {
 *     CCU6_CH0_CM_F_CALLBACK();
 *     CCU6_CH0_CM_F_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_CH0_CM_F_Int_Clr(void)
{
  Field_Wrt16(&CCU6->ISR.reg, (uint16)CCU6_ISR_RCC60F_Pos, (uint16)CCU6_ISR_RCC60F_Msk, 1u);
}

/** \brief clears Capture, Compare-Match Rising Edge Interrupt flag for Channel 1.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Capture, Compare-Match Rising Edge Interrupt for Channel 1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_CH1_CM_R_Int_En();
 *   if (CCU6_T12_CM_CC61_Int_Rise_Sts() == (uint8)1)
 *   {
 *     CCU6_CH1_CM_R_CALLBACK();
 *     CCU6_CH1_CM_R_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_CH1_CM_R_Int_Clr(void)
{
  Field_Wrt16(&CCU6->ISR.reg, (uint16)CCU6_ISR_RCC61R_Pos, (uint16)CCU6_ISR_RCC61R_Msk, 1u);
}

/** \brief clears Capture, Compare-Match Falling Edge Interrupt flag for Channel 1.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Capture, Compare-Match Falling Edge Interrupt for Channel 1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_CH1_CM_F_Int_En();
 *   if (CCU6_T12_CM_CC61_Int_Fall_Sts() == (uint8)1)
 *   {
 *     CCU6_CH1_CM_F_CALLBACK();
 *     CCU6_CH1_CM_F_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_CH1_CM_F_Int_Clr(void)
{
  Field_Wrt16(&CCU6->ISR.reg, (uint16)CCU6_ISR_RCC61F_Pos, (uint16)CCU6_ISR_RCC61F_Msk, 1u);
}

/** \brief clears Capture, Compare-Match Rising Edge Interrupt flag for Channel 2.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Capture, Compare-Match Rising Edge Interrupt for Channel 2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_CH2_CM_R_Int_En();
 *   if (CCU6_T12_CM_CC62_Int_Rise_Sts() == (uint8)1)
 *   {
 *     CCU6_CH2_CM_R_CALLBACK();
 *     CCU6_CH2_CM_R_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_CH2_CM_R_Int_Clr(void)
{
  Field_Wrt16(&CCU6->ISR.reg, (uint16)CCU6_ISR_RCC62R_Pos, (uint16)CCU6_ISR_RCC62R_Msk, 1u);
}

/** \brief clears Capture, Compare-Match Falling Edge Interrupt flag for Channel 2.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Capture, Compare-Match Falling Edge Interrupt for Channel 2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_CH2_CM_F_Int_En();
 *   if (CCU6_T12_CM_CC62_Int_Fall_Sts() == (uint8)1)
 *   {
 *     CCU6_CH2_CM_F_CALLBACK();
 *     CCU6_CH2_CM_F_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_CH2_CM_F_Int_Clr(void)
{
  Field_Wrt16(&CCU6->ISR.reg, (uint16)CCU6_ISR_RCC62F_Pos, (uint16)CCU6_ISR_RCC62F_Msk, 1u);
}

/** \brief clears Interrupt for T12 One-Match Flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Interrupt for T12 One-Match.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_T12_OM_Int_En();
 *   if (CCU6_T12_OM_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_T12_OM_CALLBACK();
 *     CCU6_T12_OM_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T12_OM_Int_Clr(void)
{
  Field_Wrt16(&CCU6->ISR.reg, (uint16)CCU6_ISR_RT12OM_Pos, (uint16)CCU6_ISR_RT12OM_Msk, 1u);
}

/** \brief clears Interrupt for T12 Period-Match Flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Interrupt for T12 Period-Match.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_T12_PM_Int_En();
 *   if (CCU6_T12_PM_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_T12_PM_CALLBACK();
 *     CCU6_T12_PM_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T12_PM_Int_Clr(void)
{
  Field_Wrt16(&CCU6->ISR.reg, (uint16)CCU6_ISR_RT12PM_Pos, (uint16)CCU6_ISR_RT12PM_Msk, 1u);
}

/** \brief clears Interrupt for T13 Compare-Match Flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Interrupt for T13 Compare-Match.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_T13_CM_Int_En();
 *   if (CCU6_T13_CM_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_T13_CM_CALLBACK();
 *     CCU6_T13_CM_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T13_CM_Int_Clr(void)
{
  Field_Wrt16(&CCU6->ISR.reg, (uint16)CCU6_ISR_RT13CM_Pos, (uint16)CCU6_ISR_RT13CM_Msk, 1u);
}

/** \brief clears Interrupt for T13 Period-Match Flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Interrupt for T13 Period-Match.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_T13_PM_Int_En();
 *   if (CCU6_T13_PM_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_T13_PM_CALLBACK();
 *     CCU6_T13_PM_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T13_PM_Int_Clr(void)
{
  Field_Wrt16(&CCU6->ISR.reg, (uint16)CCU6_ISR_RT13PM_Pos, (uint16)CCU6_ISR_RT13PM_Msk, 1u);
}

/** \brief clears Trap Flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Interrupt for Trap Flag.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_TRAP_Int_En();
 *   if (CCU6_Trap_Flag_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_TRAP_CALLBACK();
 *     CCU6_TRAP_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_TRAP_Int_Clr(void)
{
  Field_Wrt16(&CCU6->ISR.reg, (uint16)CCU6_ISR_RTRPF_Pos, (uint16)CCU6_ISR_RTRPF_Msk, 1u);
}

/** \brief clears Interrupt for Correct Hall Event flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Interrupt for Correct Hall Event.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_CHE_Int_En();
 *   if (CCU6_Hall_Correct_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_CORRECT_HALL_CALLBACK();
 *     CCU6_CHE_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_CHE_Int_Clr(void)
{
  Field_Wrt16(&CCU6->ISR.reg, (uint16)CCU6_ISR_RCHE_Pos, (uint16)CCU6_ISR_RCHE_Msk, 1u);
}

/** \brief clears Interrupt for Wrong Hall Event flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Interrupt for Wrong Hall Event.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_WHE_Int_En();
 *   if (CCU6_Hall_Wrong_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_WRONG_HALL_CALLBACK();
 *     CCU6_WHE_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_WHE_Int_Clr(void)
{
  Field_Wrt16(&CCU6->ISR.reg, (uint16)CCU6_ISR_RWHE_Pos, (uint16)CCU6_ISR_RWHE_Msk, 1u);
}

/** \brief clears Multi-Channel Mode Shadow Transfer Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Multi-Channel Mode Shadow Transfer Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_STR_Int_En();
 *   if (CCU6_MCM_Str_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_MCM_STR_CALLBACK();
 *     CCU6_STR_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_STR_Int_Clr(void)
{
  Field_Wrt16(&CCU6->ISR.reg, (uint16)CCU6_ISR_RSTR_Pos, (uint16)CCU6_ISR_RSTR_Msk, 1u);
}

/** \brief enables Capture, Compare-Match Rising Edge Interrupt for Channel 0.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Capture, Compare-Match Rising Edge Interrupt for Channel 0.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_CH0_CM_R_Int_En();
 *   if (CCU6_T12_CM_CC60_Int_Rise_Sts() == (uint8)1)
 *   {
 *     CCU6_CH0_CM_R_CALLBACK();
 *     CCU6_CH0_CM_R_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_CH0_CM_R_Int_En(void)
{
  Field_Mod16(&CCU6->IEN.reg, (uint16)CCU6_IEN_ENCC60R_Pos, (uint16)CCU6_IEN_ENCC60R_Msk, 1u);
}

/** \brief disables Capture, Compare-Match Rising Edge Interrupt for Channel 0.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Capture, Compare-Match Rising Edge Interrupt for Channel 0.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_CH0_CM_R_Int_En();
 *   if (CCU6_T12_CM_CC60_Int_Rise_Sts() == (uint8)1)
 *   {
 *     CCU6_CH0_CM_R_CALLBACK();
 *     CCU6_CH0_CM_R_Int_Clr();
 *   }
 *   CCU6_CH0_CM_R_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_CH0_CM_R_Int_Dis(void)
{
  Field_Mod16(&CCU6->IEN.reg, (uint16)CCU6_IEN_ENCC60R_Pos, (uint16)CCU6_IEN_ENCC60R_Msk, 0u);
}

/** \brief enables Capture, Compare-Match Falling Edge Interrupt for Channel 0.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Capture, Compare-Match Falling Edge Interrupt for Channel 0.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_CH0_CM_F_Int_En();
 *   if (CCU6_T12_CM_CC60_Int_Fall_Sts() == (uint8)1)
 *   {
 *     CCU6_CH0_CM_F_CALLBACK();
 *     CCU6_CH0_CM_F_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_CH0_CM_F_Int_En(void)
{
  Field_Mod16(&CCU6->IEN.reg, (uint16)CCU6_IEN_ENCC60F_Pos, (uint16)CCU6_IEN_ENCC60F_Msk, 1u);
}

/** \brief disables Capture, Compare-Match Falling Edge Interrupt for Channel 0.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Capture, Compare-Match Falling Edge Interrupt for Channel 0.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_CH0_CM_F_Int_En();
 *   if (CCU6_T12_CM_CC60_Int_Fall_Sts() == (uint8)1)
 *   {
 *     CCU6_CH0_CM_F_CALLBACK();
 *     CCU6_CH0_CM_F_Int_Clr();
 *   }
 *   CCU6_CH0_CM_F_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_CH0_CM_F_Int_Dis(void)
{
  Field_Mod16(&CCU6->IEN.reg, (uint16)CCU6_IEN_ENCC60F_Pos, (uint16)CCU6_IEN_ENCC60F_Msk, 0u);
}

/** \brief enables Capture, Compare-Match Rising Edge Interrupt for Channel 1.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Capture, Compare-Match Rising Edge Interrupt for Channel 1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_CH1_CM_R_Int_En();
 *   if (CCU6_T12_CM_CC61_Int_Rise_Sts() == (uint8)1)
 *   {
 *     CCU6_CH1_CM_R_CALLBACK();
 *     CCU6_CH1_CM_R_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_CH1_CM_R_Int_En(void)
{
  Field_Mod16(&CCU6->IEN.reg, (uint16)CCU6_IEN_ENCC61R_Pos, (uint16)CCU6_IEN_ENCC61R_Msk, 1u);
}

/** \brief disables Capture, Compare-Match Rising Edge Interrupt for Channel 1.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Capture, Compare-Match Rising Edge Interrupt for Channel 1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_CH1_CM_R_Int_En();
 *   if (CCU6_T12_CM_CC61_Int_Rise_Sts() == (uint8)1)
 *   {
 *     CCU6_CH1_CM_R_CALLBACK();
 *     CCU6_CH1_CM_R_Int_Clr();
 *   }
 *   CCU6_CH1_CM_R_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_CH1_CM_R_Int_Dis(void)
{
  Field_Mod16(&CCU6->IEN.reg, (uint16)CCU6_IEN_ENCC61R_Pos, (uint16)CCU6_IEN_ENCC61R_Msk, 0u);
}

/** \brief enables Capture, Compare-Match Falling Edge Interrupt for Channel 1.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Capture, Compare-Match Falling Edge Interrupt for Channel 1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_CH1_CM_F_Int_En();
 *   if (CCU6_T12_CM_CC61_Int_Fall_Sts() == (uint8)1)
 *   {
 *     CCU6_CH1_CM_F_CALLBACK();
 *     CCU6_CH1_CM_F_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_CH1_CM_F_Int_En(void)
{
  Field_Mod16(&CCU6->IEN.reg, (uint16)CCU6_IEN_ENCC61F_Pos, (uint16)CCU6_IEN_ENCC61F_Msk, 1u);
}

/** \brief disables Capture, Compare-Match Falling Edge Interrupt for Channel 1.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Capture, Compare-Match Falling Edge Interrupt for Channel 1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_CH1_CM_F_Int_En();
 *   if (CCU6_T12_CM_CC61_Int_Fall_Sts() == (uint8)1)
 *   {
 *     CCU6_CH1_CM_F_CALLBACK();
 *     CCU6_CH1_CM_F_Int_Clr();
 *   }
 *   CCU6_CH1_CM_F_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_CH1_CM_F_Int_Dis(void)
{
  Field_Mod16(&CCU6->IEN.reg, (uint16)CCU6_IEN_ENCC61F_Pos, (uint16)CCU6_IEN_ENCC61F_Msk, 0u);
}

/** \brief enables Capture, Compare-Match Rising Edge Interrupt for Channel 2.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Capture, Compare-Match Rising Edge Interrupt for Channel 2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_CH2_CM_R_Int_En();
 *   if (CCU6_T12_CM_CC62_Int_Rise_Sts() == (uint8)1)
 *   {
 *     CCU6_CH2_CM_R_CALLBACK();
 *     CCU6_CH2_CM_R_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_CH2_CM_R_Int_En(void)
{
  Field_Mod16(&CCU6->IEN.reg, (uint16)CCU6_IEN_ENCC62R_Pos, (uint16)CCU6_IEN_ENCC62R_Msk, 1u);
}

/** \brief disables Capture, Compare-Match Rising Edge Interrupt for Channel 2.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Capture, Compare-Match Rising Edge Interrupt for Channel 2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_CH2_CM_R_Int_En();
 *   if (CCU6_T12_CM_CC62_Int_Rise_Sts() == (uint8)1)
 *   {
 *     CCU6_CH2_CM_R_CALLBACK();
 *     CCU6_CH2_CM_R_Int_Clr();
 *   }
 *   CCU6_CH2_CM_R_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_CH2_CM_R_Int_Dis(void)
{
  Field_Mod16(&CCU6->IEN.reg, (uint16)CCU6_IEN_ENCC62R_Pos, (uint16)CCU6_IEN_ENCC62R_Msk, 0u);
}

/** \brief enables Capture, Compare-Match Falling Edge Interrupt for Channel 2.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Capture, Compare-Match Falling Edge Interrupt for Channel 2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_CH2_CM_F_Int_En();
 *   if (CCU6_T12_CM_CC62_Int_Fall_Sts() == (uint8)1)
 *   {
 *     CCU6_CH2_CM_F_CALLBACK();
 *     CCU6_CH2_CM_F_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_CH2_CM_F_Int_En(void)
{
  Field_Mod16(&CCU6->IEN.reg, (uint16)CCU6_IEN_ENCC62F_Pos, (uint16)CCU6_IEN_ENCC62F_Msk, 1u);
}

/** \brief disables Capture, Compare-Match Falling Edge Interrupt for Channel 2.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Capture, Compare-Match Falling Edge Interrupt for Channel 2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_CH2_CM_F_Int_En();
 *   if (CCU6_T12_CM_CC62_Int_Fall_Sts() == (uint8)1)
 *   {
 *     CCU6_CH2_CM_F_CALLBACK();
 *     CCU6_CH2_CM_F_Int_Clr();
 *   }
 *   CCU6_CH2_CM_F_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_CH2_CM_F_Int_Dis(void)
{
  Field_Mod16(&CCU6->IEN.reg, (uint16)CCU6_IEN_ENCC62F_Pos, (uint16)CCU6_IEN_ENCC62F_Msk, 0u);
}

/** \brief enables Interrupt for T12 One-Match.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Interrupt for T12 One-Match.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_T12_OM_Int_En();
 *   if (CCU6_T12_OM_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_T12_OM_CALLBACK();
 *     CCU6_T12_OM_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T12_OM_Int_En(void)
{
  Field_Mod16(&CCU6->IEN.reg, (uint16)CCU6_IEN_ENT12OM_Pos, (uint16)CCU6_IEN_ENT12OM_Msk, 1u);
}

/** \brief disables Interrupt for T12 One-Match.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Interrupt for T12 One-Match.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_T12_OM_Int_En();
 *   if (CCU6_T12_OM_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_T12_OM_CALLBACK();
 *     CCU6_T12_OM_Int_Clr();
 *   }
 *   CCU6_T12_OM_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T12_OM_Int_Dis(void)
{
  Field_Mod16(&CCU6->IEN.reg, (uint16)CCU6_IEN_ENT12OM_Pos, (uint16)CCU6_IEN_ENT12OM_Msk, 0u);
}

/** \brief enables Interrupt for T12 Period-Match.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Interrupt for T12 Period-Match.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_T12_PM_Int_En();
 *   if (CCU6_T12_PM_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_T12_PM_CALLBACK();
 *     CCU6_T12_PM_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T12_PM_Int_En(void)
{
  Field_Mod16(&CCU6->IEN.reg, (uint16)CCU6_IEN_ENT12PM_Pos, (uint16)CCU6_IEN_ENT12PM_Msk, 1u);
}

/** \brief disables Interrupt for T12 Period-Match.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Interrupt for T12 Period-Match.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_T12_PM_Int_En();
 *   if (CCU6_T12_PM_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_T12_PM_CALLBACK();
 *     CCU6_T12_PM_Int_Clr();
 *   }
 *   CCU6_T12_PM_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T12_PM_Int_Dis(void)
{
  Field_Mod16(&CCU6->IEN.reg, (uint16)CCU6_IEN_ENT12PM_Pos, (uint16)CCU6_IEN_ENT12PM_Msk, 0u);
}

/** \brief enables Interrupt for T13 Compare-Match.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Interrupt for T13 Compare-Match.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_T13_CM_Int_En();
 *   if (CCU6_T13_CM_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_T13_CM_CALLBACK();
 *     CCU6_T13_CM_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T13_CM_Int_En(void)
{
  Field_Mod16(&CCU6->IEN.reg, (uint16)CCU6_IEN_ENT13CM_Pos, (uint16)CCU6_IEN_ENT13CM_Msk, 1u);
}

/** \brief disables Interrupt for T13 Compare-Match.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Interrupt for T13 Compare-Match.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_T13_CM_Int_En();
 *   if (CCU6_T13_CM_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_T13_CM_CALLBACK();
 *     CCU6_T13_CM_Int_Clr();
 *   }
 *   CCU6_T13_CM_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T13_CM_Int_Dis(void)
{
  Field_Mod16(&CCU6->IEN.reg, (uint16)CCU6_IEN_ENT13CM_Pos, (uint16)CCU6_IEN_ENT13CM_Msk, 0u);
}

/** \brief enables Interrupt for T13 Period-Match.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Interrupt for T13 Period-Match.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_T13_PM_Int_En();
 *   if (CCU6_T13_PM_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_T13_PM_CALLBACK();
 *     CCU6_T13_PM_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T13_PM_Int_En(void)
{
  Field_Mod16(&CCU6->IEN.reg, (uint16)CCU6_IEN_ENT13PM_Pos, (uint16)CCU6_IEN_ENT13PM_Msk, 1u);
}

/** \brief disables Interrupt for T13 Period-Match.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Interrupt for T13 Period-Match.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_T13_PM_Int_En();
 *   if (CCU6_T13_PM_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_T13_PM_CALLBACK();
 *     CCU6_T13_PM_Int_Clr();
 *   }
 *   CCU6_T13_PM_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_T13_PM_Int_Dis(void)
{
  Field_Mod16(&CCU6->IEN.reg, (uint16)CCU6_IEN_ENT13PM_Pos, (uint16)CCU6_IEN_ENT13PM_Msk, 0u);
}

/** \brief enables Interrupt for Trap Flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Interrupt for Trap Flag.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_TRAP_Int_En();
 *   if (CCU6_Trap_Flag_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_TRAP_CALLBACK();
 *     CCU6_TRAP_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_TRAP_Int_En(void)
{
  Field_Mod16(&CCU6->IEN.reg, (uint16)CCU6_IEN_ENTRPF_Pos, (uint16)CCU6_IEN_ENTRPF_Msk, 1u);
}

/** \brief disables Interrupt for Trap Flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Interrupt for Trap Flag.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_TRAP_Int_En();
 *   if (CCU6_Trap_Flag_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_TRAP_CALLBACK();
 *     CCU6_TRAP_Int_Clr();
 *   }
 *   CCU6_TRAP_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_TRAP_Int_Dis(void)
{
  Field_Mod16(&CCU6->IEN.reg, (uint16)CCU6_IEN_ENTRPF_Pos, (uint16)CCU6_IEN_ENTRPF_Msk, 0u);
}

/** \brief enables Interrupt for Correct Hall Event.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Interrupt for Correct Hall Event.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_CHE_Int_En();
 *   if (CCU6_Hall_Correct_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_CORRECT_HALL_CALLBACK();
 *     CCU6_CHE_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_CHE_Int_En(void)
{
  Field_Mod16(&CCU6->IEN.reg, (uint16)CCU6_IEN_ENCHE_Pos, (uint16)CCU6_IEN_ENCHE_Msk, 1u);
}

/** \brief disables Interrupt for Correct Hall Event.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Interrupt for Correct Hall Event.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_CHE_Int_En();
 *   if (CCU6_Hall_Correct_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_CORRECT_HALL_CALLBACK();
 *     CCU6_CHE_Int_Clr();
 *   }
 *   CCU6_CHE_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_CHE_Int_Dis(void)
{
  Field_Mod16(&CCU6->IEN.reg, (uint16)CCU6_IEN_ENCHE_Pos, (uint16)CCU6_IEN_ENCHE_Msk, 0u);
}

/** \brief enables Interrupt for Wrong Hall Event.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Interrupt for Wrong Hall Event.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_WHE_Int_En();
 *   if (CCU6_Hall_Wrong_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_WRONG_HALL_CALLBACK();
 *     CCU6_WHE_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_WHE_Int_En(void)
{
  Field_Mod16(&CCU6->IEN.reg, (uint16)CCU6_IEN_ENWHE_Pos, (uint16)CCU6_IEN_ENWHE_Msk, 1u);
}

/** \brief disables Interrupt for Wrong Hall Event.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Interrupt for Wrong Hall Event.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_WHE_Int_En();
 *   if (CCU6_Hall_Wrong_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_WRONG_HALL_CALLBACK();
 *     CCU6_WHE_Int_Clr();
 *   }
 *   CCU6_WHE_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_WHE_Int_Dis(void)
{
  Field_Mod16(&CCU6->IEN.reg, (uint16)CCU6_IEN_ENWHE_Pos, (uint16)CCU6_IEN_ENWHE_Msk, 0u);
}

/** \brief enables Multi-Channel Mode Shadow Transfer Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Multi-Channel Mode Shadow Transfer Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_STR_Int_En();
 *   if (CCU6_MCM_Str_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_MCM_STR_CALLBACK();
 *     CCU6_STR_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_STR_Int_En(void)
{
  Field_Mod16(&CCU6->IEN.reg, (uint16)CCU6_IEN_ENSTR_Pos, (uint16)CCU6_IEN_ENSTR_Msk, 1u);
}

/** \brief disables Multi-Channel Mode Shadow Transfer Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Multi-Channel Mode Shadow Transfer Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CCU6_STR_Int_En();
 *   if (CCU6_MCM_Str_Int_Sts() == (uint8)1)
 *   {
 *     CCU6_MCM_STR_CALLBACK();
 *     CCU6_STR_Int_Clr();
 *   }
 *   CCU6_STR_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_STR_Int_Dis(void)
{
  Field_Mod16(&CCU6->IEN.reg, (uint16)CCU6_IEN_ENSTR_Pos, (uint16)CCU6_IEN_ENSTR_Msk, 0u);
}

/*******************************************************************************
**                        Global Function Declarations                        **
*******************************************************************************/
/** \brief Initializes the CCU6 module.
 *
 * \ingroup ccu6_api
 */
void CCU6_Init(void);

INLINE void CCU6_StartTmr_T12(void);
INLINE void CCU6_StartTmr_T13(void);
INLINE void CCU6_StopTmr_T12(void);
INLINE void CCU6_StopTmr_T13(void);
INLINE void CCU6_EnableST_T12(void);
INLINE void CCU6_EnableST_T13(void);
INLINE void CCU6_LoadShadowRegister_CC60(uint16 tick);
INLINE void CCU6_LoadShadowRegister_CC61(uint16 tick);
INLINE void CCU6_LoadShadowRegister_CC62(uint16 tick);
INLINE void CCU6_LoadShadowRegister_CC63(uint16 tick);
INLINE void CCU6_LoadPeriodRegister_T13_Time(uint32 us);
INLINE void CCU6_LoadPeriodRegister_T13_Tick(uint16 tick);
INLINE bool CCU6_IsT13Running(void);
INLINE void CCU6_SetT13Trigger(uint16 Mask);
INLINE void CCU6_SetT13Compare(uint16 Compare);
INLINE void CCU6_SetT12T13ControlBits(uint16 Mask);
INLINE uint32 CCU6_ReadHallReg(void);
INLINE uint16 CCU6_ReadMultichannelPatterns(void);
INLINE void CCU6_WriteMultichannelPatterns(uint16 Patterns);
INLINE void CCU6_ConfigureMultichannelModulation(uint16 Mode);
INLINE void CCU6_ConfigureGlobalModulation(uint16 Mode);
INLINE void CCU6_EnableInt(uint16 Mask);
INLINE void CCU6_ClearIntStatus(uint16 Mask);

/*******************************************************************************
**                     Global Inline Function Definitions                     **
*******************************************************************************/
/** \brief Start CCU6 Timer T12
 *
 * \brief <b>Example</b><br>
 * \brief This example starts CCU6 Timer T12.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_StartTmr_T12();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_StartTmr_T12(void)
{
  CCU6_T12_Start();
}

/** \brief Start CCU6 Timer T13
 *
 * \brief <b>Example</b><br>
 * \brief This example starts CCU6 Timer T13.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_StartTmr_T13();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_StartTmr_T13(void)
{
  CCU6_T13_Start();
}

/** \brief Stop CCU6 Timer T12
 *
 * \brief <b>Example</b><br>
 * \brief This example stops CCU6 Timer T12.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_StopTmr_T12();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_StopTmr_T12(void)
{
  CCU6_T12_Stop();
}

/** \brief Stops CCU6 Timer T13
 *
 * \brief <b>Example</b><br>
 * \brief This example stops CCU6 Timer T13.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_StopTmr_T13();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_StopTmr_T13(void)
{
  CCU6_T13_Stop();
}

/** \brief Enable T12 Shadow Transfer
 *
 * \brief <b>Example</b><br>
 * \brief This example enables T12 Shadow Transfer.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_EnableST_T12();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_EnableST_T12(void)
{
  CCU6_T12_Str_En();
}

/** \brief Enable T13 Shadow Transfer
 *
 * \brief <b>Example</b><br>
 * \brief This example enables T13 Shadow Transfer.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_EnableST_T13();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_EnableST_T13(void)
{
  CCU6_T13_Str_En();
}

/** \brief Load Channel 0 compare value to the shadow register
 *
 * \param tick Channel 0 compare value in clock ticks
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Channel 0 Compare Value to 5000.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_LoadShadowRegister_CC60(0x1388);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_LoadShadowRegister_CC60(uint16 tick)
{
  CCU6_Ch0_Value_Set(tick);
}

/** \brief Load Channel 1 compare value to the shadow register
 *
 * \param tick Channel 1 compare value in clock ticks
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Channel 1 Compare Value to 5000.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_LoadShadowRegister_CC61(0x1388);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_LoadShadowRegister_CC61(uint16 tick)
{
  CCU6_Ch1_Value_Set(tick);
}

/** \brief Load Channel 2 compare value to the shadow register
 *
 * \param tick Channel 2 compare value in clock ticks
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Channel 2 Compare Value to 5000.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_LoadShadowRegister_CC62(0x1388);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_LoadShadowRegister_CC62(uint16 tick)
{
  CCU6_Ch2_Value_Set(tick);
}

/** \brief Load Channel 3 compare value to the shadow register
 *
 * \param tick Channel 3 compare value in clock ticks
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Channel 3 Compare Value to 5000.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_LoadShadowRegister_CC63(0x1388);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_LoadShadowRegister_CC63(uint16 tick)
{
  CCU6_Ch3_Value_Set(tick);
}

/** \brief Load Timer13 Period Register as Time Value
 *
 * \param us Period in Time [us]
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Timer13 Period Register Time Value to 5000 us.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_LoadPeriodRegister_T13_Time(0x1388);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_LoadPeriodRegister_T13_Time(uint32 us)
{
  CCU6_T13_Period_Value_Set((uint16)((uint32)CCU6_T13_CLK * us));
}

/** \brief Load Timer13 Period Register as Time Value
 *
 * \param tick Period in clock ticks
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Timer13 Period Register Time Value to 5000 ticks.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_LoadPeriodRegister_T13_Tick(0x1388);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_LoadPeriodRegister_T13_Tick(uint16 tick)
{
  CCU6_T13_Period_Value_Set(tick);
}

/** \brief reads Timer T13 Run Bit.
 *
 * \retval false if Timer T13 is stopped.
 * \retval true if Timer T13 is running.
 *
 * \brief <b>Example</b><br>
 * \brief This example checks if Timer T13 is running.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_T13_Start();
 *    while (CCU6_IsT13Running())
 *    {
 *    }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE bool CCU6_IsT13Running(void)
{
  bool res = false;

  if (CCU6_T13_Run_Sts() == (uint8)1)
  {
    res = true;
  }

  return (res);
}

/** \brief Sets trigger event for the T13 timer.
 *
 * \param Mask Trigger mask
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Timer T13 Single Shot Control.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_SetT13Trigger(2u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_SetT13Trigger(uint16 Mask)
{
  /* Set trigger mask */
  Field_Wrt16(&CCU6->TCTR2.reg, 0, (uint16)0xFFFF, Mask);
}

/** \brief Sets compare value for the T13 timer.
 *
 * \param Compare Compare value
 *
 * \brief <b>Example</b><br>
 * \brief This example sets T13 Compare to 5000.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_SetT13Compare(0x1388);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_SetT13Compare(uint16 Compare)
{
  if (Compare < CCU6_T13_Period_Value_Get())
  {
    /* Set only the requested compare value if no period change is needed */
    CCU6_Ch3_Value_Set(Compare);
  }
  else
  {
    /* Period value < compare value ? --> increase the period value */
    if (Compare <= (uint16)0xFFFE)
    {
      /* Set requested compare value */
      CCU6_Ch3_Value_Set(Compare);
      /* increase period value to ensure the compare match */
      CCU6_T13_Period_Value_Set((Compare + 1u));
    }
    else
    {
      /* Requested value is not possible */
      /* Set the highest possible values that ensure a compare match*/
      CCU6_Ch3_Value_Set((uint16)0xFFFE);
      CCU6_T13_Period_Value_Set((uint16)0xFFFF);
    }
  }

  /* Enable shadow transfer */
  CCU6_T13_Str_En();
}

/** \brief Sets write-only control bits for T12 and/or T13 timer.
 *
 * \param Mask Control bit mask
 *
 * \brief <b>Example</b><br>
 * \brief This example resets Timer T12 Run.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_SetT12T13ControlBits(1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_SetT12T13ControlBits(uint16 Mask)
{
  Field_Wrt16(&CCU6->TCTR4.reg, 0, (uint16)0xFFFF, Mask);
}

/** \brief Reads sampled Hall pattern from CCU6 CMPSTAT register.
 *
 * \return Sampled Hall pattern
 *
 * \brief <b>Example</b><br>
 * \brief This example Reads sampled Hall pattern from CCU6 CMPSTAT register.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint16 val;
 *
 *    val = CCU6_ReadHallReg();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint32 CCU6_ReadHallReg(void)
{
  return (uint32)u16_Field_Rd16(&CCU6->CMPSTAT.reg, (uint8)CCU6_CMPSTAT_CCPOS0_Pos, 0x38u);
}

/** \brief Reads actual Hall and PWM patterns for Multi-Channel Mode.
 *
 * \return Hall and PWM patterns
 *
 * \brief <b>Example</b><br>
 * \brief This example Reads actual Hall and PWM patterns for Multi-Channel Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint16 val;
 *
 *    val = CCU6_ReadMultichannelPatterns();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE uint16 CCU6_ReadMultichannelPatterns(void)
{
  return u16_Field_Rd16(&CCU6->MCMOUT.reg, 0, (uint16)0xFFFF);
}

/** \brief Writes Hall and/or PWM patterns for Multi-Channel Mode to shadow register.
 *
 * \param Patterns Hall and/or PWM patterns
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Multi-Channel PWM Pattern Shadow.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_WriteMultichannelPatterns(0u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_WriteMultichannelPatterns(uint16 Patterns)
{
  Field_Wrt16(&CCU6->MCMOUTS.reg, 0, (uint16)0xFFFF, Patterns);
}

/** \brief Sets Multi-Channel Mode control register.
 *
 * \param Mode Multi-Channel mode control bits
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Correct pattern Switching Selection.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_ConfigureMultichannelModulation(1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_ConfigureMultichannelModulation(uint16 Mode)
{
  Field_Wrt16(&CCU6->MCMCTR.reg, 0, (uint16)0xFFFF, Mode);
}

/** \brief Sets global modulation control register.
 *
 * \param Mode Global modulation control bits
 *
 * \brief <b>Example</b><br>
 * \brief This example enables T12 modulation of CC60.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_ConfigureGlobalModulation(1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_ConfigureGlobalModulation(uint16 Mode)
{
  Field_Wrt16(&CCU6->MODCTR.reg, 0, (uint16)0xFFFF, Mode);
}

/** \brief Enables/disables interrupt(s).
 *
 * \param Mask for interrupt(s) to be enabled.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables all CCU6 interrupts.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_EnableInt(0xF7FF);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_EnableInt(uint16 Mask)
{
  Field_Wrt16(&CCU6->IEN.reg, 0, (uint16)0xFFFF, Mask);
}

/** \brief Clears interrupt status bit(s).
 *
 * \param Mask for interrupt status bit(s) to be cleared.
 *
 * \brief <b>Example</b><br>
 * \brief This example Clears all CCU6 interrupt flags.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    CCU6_ClearIntStatus(0xF7FF);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ccu6_api
 */
INLINE void CCU6_ClearIntStatus(uint16 Mask)
{
  Field_Wrt16(&CCU6->ISR.reg, 0, (uint16)0xFFFF, Mask);
}

#endif
