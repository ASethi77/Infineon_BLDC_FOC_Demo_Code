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
 * \file     bdrv.h
 *
 * \brief    Bridge Driver low level access library
 *
 * \version  V0.4.8
 * \date     26. May 2021
 */

/*******************************************************************************
**                             Author(s) Identity                             **
********************************************************************************
** Initials     Name                                                          **
** ---------------------------------------------------------------------------**
** DM           Daniel Mysliwitz                                              **
** TA           Thomas Albersinger                                            **
** AP           Adriano Pereira                                               **
** BG           Blandine Guillot                                              **
** JO           Julia Ott                                                     **
*******************************************************************************/

/*******************************************************************************
**                          Revision Control History                          **
********************************************************************************
** V0.1.0: 2013-02-10, DM:   Initial version                                  **
** V0.1.1: 2013-05-24, DM:   Bdrv_Diag functions removed                      **
**                           Bdrv_Clr_Sts changed, to be robust against       **
**                           unintended flag clearing                         **
**                           Open-Load detection function added               **
** V0.2.0: 2013-09-20, DM:   Function and settings adapted to B-Step device   **
** V0.3.0: 2014-04-25, TA:   Bdrv_Init(): use #defines from IFX Config Wizard **
** V0.3.1: 2015-02-10, DM:   Individual header file added                     **
** V0.3.2: 2015-07-15, DM:   BEMF register init added                         **
** V0.3.3: 2015-11-12, DM:   Disabled interrupts before writing TRIM_DRVx     **
** V0.3.4: 2016-07-28, DM:   OpenLoad detection for 3-phase motors added      **
** V0.3.5: 2016-09-23, DM:   OpenLoad detection current set to 1              **
** V0.3.6: 2017-02-16, DM:   Bdrv prefix changed to capital letter            **
** V0.3.7: 2017-07-25, DM:   A nop was added after each status flag clear     **
** V0.3.8: 2017-09-26, DM:   MISRA 2012 compliance, the following PC-Lint     **
**                           rules are globally deactivated:                  **
**                           - Info 793: ANSI/ISO limit of 6 'significant     **
**                             characters in an external identifier           **
**                           - Info 835: A zero has been given as right       **
**                             argument to operator                           **
**                           - Info 845: The left argument to operator '&'    **
**                             is certain to be 0                             **
** V0.3.9: 2018-02-02, DM:   BDRV_Off_Diagnosis() function added              **
** V0.4.0: 2018-03-14, DM:   BDRV_Clr_Sts() type of parameter changed to      **
**                           (uint32) due to MISRA 2012                       **
**                           typedef TBdrv_Sts replaced by #define macros     **
**                           due to MISRA 2012                                **
**                           Replaced macros by INLINE functions              **
**                           Replaced register accesses within functions by   **
**                           function calls                                   **
** V0.4.1: 2018-07-04, AP:   Updated BDRV_Set_Bridge(), BDRV_Clr_Sts(),       **
**                           BDRV_Set_Channel() to use API functions (instead **
**                           of direct access to registers)                   **
**                           Fixed BDRV_Set_Int_Channel() to allow interrupt  **
**                           disabling                                        **
** V0.4.2: 2018-07-30, AP:   Added functions to get BDRV interrupt status     **
**                           Added BDRV_Set_DSM_Threshold() and               **
**                           BDRV_Set_Discharge_Current()                     **
**                           Updated BDRV_Diag_OpenLoad() and                 **
**                           BDRV_Off_Diagnosis to use new APIs               **
** V0.4.3: 2018-11-27, JO:   Doxygen update                                   **
**                           Moved revision history from bdrv.c to bdrv.h     **
** V0.4.4: 2020-04-15, BG:   Updated revision history format                  **
** V0.4.5: 2020-07-21, BG:   EP-439: Formatted .h/.c files                    **
** V0.4.6: 2021-02-26, JO:   EP-715: Removed type TBdrv_Disch_Curr (not used  **
**                           anymore), added type TBDRV_Curr                  **
**                           Removed function BDRV_Set_Discharge_Current      **
**                           Added functions to get/set the Chrg/Dischrg      **
**                           current and current range in mA via TBDRV_Curr   **
**                           (BDRV_getChrgCurrent_mA, BDRV_setChrgCurrent_mA, **
**                           BDRV_getDischrgCurrent_mA,                       **
**                           BDRV_setDischrgCurrent_mA)                       **
**                           Added functions to get/set the Chrg/Dischrg      **
**                           current and current range (digital value)        **
** V0.4.7: 2021-04-23, BG:   EP-726: Corrected MISRA 2012 violations          **
** V0.4.8: 2021-05-26, BG:   EP-827: Corrected initialization of CTRL1 and    **
**                           CTRL2 registers with the CW defines              **
*******************************************************************************/

#ifndef _BDR_H
#define _BDR_H

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "tle_variants.h"
#include "sfr_access.h"
#include "scu.h"
#include "int.h"
#include "wdt1.h"

/*******************************************************************************
**                          Global Macro Definitions                          **
*******************************************************************************/
#define TBDRV_Curr_RANGE_POS 5u
#define TBDRV_Curr_CURRENT_MASK 0x3Fu

/*******************************************************************************
**                           Global Type Definitions                          **
*******************************************************************************/

/** \enum TBdrv_Ch_Cfg
 *  \brief This enum lists the Bridge Driver High Side channel configuration.
 */
typedef enum _TBdrv_Ch_Cfg
{
  Ch_Off = 0u,  /**< \brief channel disabled                           */
  Ch_En  = 1u,  /**< \brief channel enabled                            */
  Ch_PWM = 3u,  /**< \brief channel enabled with PWM (CCU6 connection) */
  Ch_On  = 5u,  /**< \brief channel enabled and static on              */
  Ch_DCS = 9u   /**< \brief channel enabled with Diag.-Current Source  */
} TBdrv_Ch_Cfg;

/** \enum TBdrv_Ch
 *  \brief This enum lists the Bridge Driver channel configuration.
 */
typedef enum _TBdrv_Ch
{
  LS1 = 0u, /**< \brief Phase1 Low Side MOSFET */
  LS2 = 1u, /**< \brief Phase2 Low Side MOSFET */
  HS1 = 2u, /**< \brief Phase1 High Side MOSFET */
  HS2 = 3u  /**< \brief Phase2 High Side MOSFET */
#if (UC_SERIES == TLE987)
  ,
  LS3 = 4u, /**< \brief Phase3 Low Side MOSFET */
  HS3 = 5u  /**< \brief Phase3 High Side MOSFET */
#endif
} TBdrv_Ch;

/** \brief this enum lists the bit masks for the BridgeDriver status flags */
#define LS1_DS SCUPM_BDRV_ISCLR_LS1_DS_ICLR_Msk /**< \brief Phase1 Low Side MOSFET mask for Off-Diagnosis */
#define LS2_DS SCUPM_BDRV_ISCLR_LS2_DS_ICLR_Msk /**< \brief Phase2 Low Side MOSFET mask for Off-Diagnosis */
#define HS1_DS SCUPM_BDRV_ISCLR_HS1_DS_ICLR_Msk /**< \brief Phase1 High Side MOSFET mask for Off-Diagnosis */
#define HS2_DS SCUPM_BDRV_ISCLR_HS2_DS_ICLR_Msk /**< \brief Phase2 High Side MOSFET mask for Off-Diagnosis */
#define LS1_OC SCUPM_BDRV_ISCLR_LS1_OC_ICLR_Msk /**< \brief Phase1 Low Side MOSFET mask for On-Diagnosis */
#define LS2_OC SCUPM_BDRV_ISCLR_LS2_OC_ICLR_Msk /**< \brief Phase2 Low Side MOSFET mask for On-Diagnosis */
#define HS1_OC SCUPM_BDRV_ISCLR_HS1_OC_ICLR_Msk /**< \brief Phase1 High Side MOSFET mask for On-Diagnosis */
#define HS2_OC SCUPM_BDRV_ISCLR_HS2_OC_ICLR_Msk /**< \brief Phase2 High Side MOSFET mask for On-Diagnosis */
#if (UC_SERIES == TLE987)
  #define LS3_DS SCUPM_BDRV_ISCLR_LS3_DS_ICLR_Msk /**< \brief Phase3 Low Side MOSFET mask for Off-Diagnosis */
  #define HS3_DS SCUPM_BDRV_ISCLR_HS3_DS_ICLR_Msk /**< \brief Phase3 High Side MOSFET mask for Off-Diagnosis */
  #define LS3_OC SCUPM_BDRV_ISCLR_LS3_OC_ICLR_Msk /**< \brief Phase3 Low Side MOSFET mask for On-Diagnosis */
  #define HS3_OC SCUPM_BDRV_ISCLR_HS3_OC_ICLR_Msk /**< \brief Phase3 High Side MOSFET mask for On-Diagnosis */
#endif

/** \enum TBDRV_Off_Diag_Sts
 *  \brief This enum lists the Bridge Driver Off Diagnosis Status configuration.
 */
typedef enum _TBDRV_Off_Diag_Sts
{
  Ch_Ok = 0u,
  Ch_Short_to_Gnd = 1u,
  Ch_Short_to_VBat = 2u
} TBDRV_Off_Diag_Sts;

/** \struct TBDRV_Off_Diag
 *  \brief This struct lists the Bridge Driver Off Diagnosis Status Phases configuration.
 */
typedef struct
{
  bool GlobFailSts;
  TBDRV_Off_Diag_Sts Phase1;
  TBDRV_Off_Diag_Sts Phase2;
#if (UC_SERIES == TLE987)
  TBDRV_Off_Diag_Sts Phase3;
#endif
} TBDRV_Off_Diag;

/** \enum TBdrv_Ch_Int
 *  \brief This enum lists the Bridge Driver channel Interrupt configuration.
 */
typedef enum _TBdrv_Ch_Int
{
  Int_Off = 0U,  /**< \brief all interrupts disable                         */
  Int_DS = 1U,   /**< \brief Drain-Source interrupt enable (Off-Diagnosis)  */
  Int_OC = 2U,   /**< \brief Over-Current interrupt enable (On-Diagnosis)   */
  Int_DS_OC = 3U /**< \brief Drain-Source and Over-Current interrupt enable */
} TBdrv_Ch_Int;

/** \enum TBdrv_DSM_Threshold
 *  \brief This enum lists the possible threshold settings for Drain-Source monitoring
 */
typedef enum _TBdrv_DSM_Threshold
{
  Threshold_0_25_V = 0U, /**< \brief Threshold 0 for VDS at 0.25 V */
  Threshold_0_50_V = 1U, /**< \brief Threshold 1 for VDS at 0.50 V */
  Threshold_0_75_V = 2U, /**< \brief Threshold 2 for VDS at 0.75 V */
  Threshold_1_00_V = 3U, /**< \brief Threshold 3 for VDS at 1.00 V */
  Threshold_1_25_V = 4U, /**< \brief Threshold 4 for VDS at 1.25 V */
  Threshold_1_50_V = 5U, /**< \brief Threshold 5 for VDS at 1.50 V */
  Threshold_1_75_V = 6U, /**< \brief Threshold 6 for VDS at 1.75 V */
  Threshold_2_00_V = 7U  /**< \brief Threshold 7 for VDS at 2.00 V */
} TBdrv_DSM_Threshold;

/** \enum TBDRV_Curr
 *  \brief This enum lists the possible current settings for the BDRV Charge and Discharge currents, 
 *  for half range (BDRV_Curr_HR_*) and for full range (BDRV_Curr_FR_*)
 */
typedef enum _TBDRV_Curr
{
  /* Half Range */
  BDRV_Curr_HR_Disabled = 0U,  /**< \brief (HiZ) Slew Rate Control is inactive */
  BDRV_Curr_HR_Min = 1U,       /**< \brief (min discharge current) lowest gate discharge current */
  BDRV_Curr_HR_10mA = 2U,      /**< \brief typ. current ~10 mA */
  BDRV_Curr_HR_15mA = 3U,      /**< \brief typ. current ~15 mA */
  BDRV_Curr_HR_20mA = 4U,      /**< \brief typ. current ~20 mA */
  BDRV_Curr_HR_25mA = 5U,      /**< \brief typ. current ~25 mA */
  BDRV_Curr_HR_30mA = 6U,      /**< \brief typ. current ~30 mA */
  BDRV_Curr_HR_35mA = 7U,      /**< \brief typ. current ~35 mA */
  BDRV_Curr_HR_40mA = 8U,      /**< \brief typ. current ~40 mA */
  BDRV_Curr_HR_45mA = 9U,      /**< \brief typ. current ~45 mA */
  BDRV_Curr_HR_50mA = 10U,     /**< \brief typ. current ~50 mA */
  BDRV_Curr_HR_55mA = 11U,     /**< \brief typ. current ~55 mA */
  BDRV_Curr_HR_60mA = 12U,     /**< \brief typ. current ~60 mA */
  BDRV_Curr_HR_65mA = 13U,     /**< \brief typ. current ~65 mA */
  BDRV_Curr_HR_70mA = 14U,     /**< \brief typ. current ~70 mA */
  BDRV_Curr_HR_75mA = 15U,     /**< \brief typ. current ~75 mA */
  BDRV_Curr_HR_80mA = 16U,     /**< \brief typ. current ~80 mA */
  BDRV_Curr_HR_85mA = 17U,     /**< \brief typ. current ~85 mA */
  BDRV_Curr_HR_90mA = 18U,     /**< \brief typ. current ~90 mA */
  BDRV_Curr_HR_95mA = 19U,     /**< \brief typ. current ~95 mA */
  BDRV_Curr_HR_100mA = 20U,    /**< \brief typ. current ~100 mA */
  BDRV_Curr_HR_105mA = 21U,    /**< \brief typ. current ~105 mA */
  BDRV_Curr_HR_110mA = 22U,    /**< \brief typ. current ~110 mA */
  BDRV_Curr_HR_115mA = 23U,    /**< \brief typ. current ~115 mA */
  BDRV_Curr_HR_120mA = 24U,    /**< \brief typ. current ~120 mA */
  BDRV_Curr_HR_125mA = 25U,    /**< \brief typ. current ~125 mA */
  BDRV_Curr_HR_130mA = 26U,    /**< \brief typ. current ~130 mA */
  BDRV_Curr_HR_135mA = 27U,    /**< \brief typ. current ~135 mA */
  BDRV_Curr_HR_140mA = 28U,    /**< \brief typ. current ~140 mA */
  BDRV_Curr_HR_145mA = 29U,    /**< \brief typ. current ~145 mA */
  BDRV_Curr_HR_150mA = 30U,    /**< \brief typ. current ~150 mA */
  BDRV_Curr_HR_155mA = 31U,    /**< \brief typ. current ~155 mA  */
  /* Full Range */
  BDRV_Curr_FR_Disabled = 32U, /**< \brief (HiZ) Slew Rate Control is inactive */
  BDRV_Curr_FR_Min =  33U,     /**< \brief (min discharge current) lowest gate discharge current */
  BDRV_Curr_FR_20mA = 43U,     /**< \brief typ. current ~20 mA */
  BDRV_Curr_FR_30mA = 35U,     /**< \brief typ. current ~30 mA */
  BDRV_Curr_FR_40mA = 36U,     /**< \brief typ. current ~40 mA */
  BDRV_Curr_FR_50mA = 37U,     /**< \brief typ. current ~50 mA */
  BDRV_Curr_FR_60mA = 38U,     /**< \brief typ. current ~60 mA */
  BDRV_Curr_FR_70mA = 39U,     /**< \brief typ. current ~70 mA */
  BDRV_Curr_FR_80mA = 40U,     /**< \brief typ. current ~80 mA */
  BDRV_Curr_FR_90mA = 41U,     /**< \brief typ. current ~90 mA */
  BDRV_Curr_FR_100mA = 42U,    /**< \brief typ. current ~100 mA */
  BDRV_Curr_FR_110mA = 43U,    /**< \brief typ. current ~110 mA */
  BDRV_Curr_FR_120mA = 44U,    /**< \brief typ. current ~120 mA */
  BDRV_Curr_FR_130mA = 45U,    /**< \brief typ. current ~130 mA */
  BDRV_Curr_FR_140mA = 46U,    /**< \brief typ. current ~140 mA */
  BDRV_Curr_FR_150mA = 47U,    /**< \brief typ. current ~150 mA */
  BDRV_Curr_FR_160mA = 48U,    /**< \brief typ. current ~160 mA */
  BDRV_Curr_FR_170mA = 49U,    /**< \brief typ. current ~170 mA */
  BDRV_Curr_FR_180mA = 50U,    /**< \brief typ. current ~180 mA */
  BDRV_Curr_FR_190mA = 51U,    /**< \brief typ. current ~190 mA */
  BDRV_Curr_FR_200mA = 52U,    /**< \brief typ. current ~200 mA */
  BDRV_Curr_FR_210mA = 53U,    /**< \brief typ. current ~210 mA */
  BDRV_Curr_FR_220mA = 54U,    /**< \brief typ. current ~220 mA */
  BDRV_Curr_FR_230mA = 55U,    /**< \brief typ. current ~230 mA */
  BDRV_Curr_FR_240mA = 56U,    /**< \brief typ. current ~240 mA */
  BDRV_Curr_FR_250mA = 57U,    /**< \brief typ. current ~250 mA */
  BDRV_Curr_FR_260mA = 58U,    /**< \brief typ. current ~260 mA */
  BDRV_Curr_FR_270mA = 59U,    /**< \brief typ. current ~270 mA */
  BDRV_Curr_FR_280mA = 60U,    /**< \brief typ. current ~280 mA */
  BDRV_Curr_FR_290mA = 61U,    /**< \brief typ. current ~290 mA */
  BDRV_Curr_FR_300mA = 62U,    /**< \brief typ. current ~300 mA */
  BDRV_Curr_FR_310mA = 63U     /**< \brief typ. current ~310 mA  */
} TBDRV_Curr;

#if (UC_SERIES == TLE987)
  #define BDRV_ISCLR_OC    (LS1_OC | HS1_OC | LS2_OC | HS2_OC | LS3_OC | HS3_OC)
  #define BDRV_ISCLR_DS    (LS1_DS | HS1_DS | LS2_DS | HS2_DS | LS3_DS | HS3_DS)
#else
  #define BDRV_ISCLR_OC    (LS1_OC | HS1_OC | LS2_OC | HS2_OC)
  #define BDRV_ISCLR_DS    (LS1_DS | HS1_DS | LS2_DS | HS2_DS)
#endif
#define BDRV_IRQ_BITS     (BDRV_ISCLR_OC | BDRV_ISCLR_DS)
#define BDRV_DS_STS_BITS   BDRV_ISCLR_DS

/*******************************************************************************
**                     Global Inline Function Definitions                     **
*******************************************************************************/
/** \brief clears External High Side 1 FET Over-current interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External High Side 1 FET Over-current interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_HS1_OC_Int_En();
 *   if (SCUPM->BDRV_IS.bit.HS1_OC_IS == 1u)
 *   {
 *     BDRV_HS1_OC_CALLBACK();
 *     BDRV_HS1_OC_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_HS1_OC_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->BDRV_ISCLR.reg, SCUPM_BDRV_ISCLR_HS1_OC_ICLR_Pos, SCUPM_BDRV_ISCLR_HS1_OC_ICLR_Msk, 1u);
}

/** \brief clears External Low Side 1 FET Over-current interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Low Side 1 FET Over-current interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_LS1_OC_Int_En();
 *   if (SCUPM->BDRV_IS.bit.LS1_OC_IS == 1u)
 *   {
 *     BDRV_LS1_OC_CALLBACK();
 *     BDRV_LS1_OC_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_LS1_OC_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->BDRV_ISCLR.reg, SCUPM_BDRV_ISCLR_LS1_OC_ICLR_Pos, SCUPM_BDRV_ISCLR_LS1_OC_ICLR_Msk, 1u);
}

/** \brief clears External High Side 2 FET Over-current interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External High Side 2 FET Over-current interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_HS2_OC_Int_En();
 *   if (SCUPM->BDRV_IS.bit.HS2_OC_IS == 1u)
 *   {
 *     BDRV_HS2_OC_CALLBACK();
 *     BDRV_HS2_OC_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_HS2_OC_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->BDRV_ISCLR.reg, SCUPM_BDRV_ISCLR_HS2_OC_ICLR_Pos, SCUPM_BDRV_ISCLR_HS2_OC_ICLR_Msk, 1u);
}

/** \brief clears External Low Side 2 FET Over-current interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Low Side 2 FET Over-current interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_LS2_OC_Int_En();
 *   if (SCUPM->BDRV_IS.bit.LS2_OC_IS == 1u)
 *   {
 *     BDRV_LS2_OC_CALLBACK();
 *     BDRV_LS2_OC_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_LS2_OC_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->BDRV_ISCLR.reg, SCUPM_BDRV_ISCLR_LS2_OC_ICLR_Pos, SCUPM_BDRV_ISCLR_LS2_OC_ICLR_Msk, 1u);
}

#if (UC_SERIES == TLE987)
/** \brief clears External High Side 3 FET Over-current interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External High Side 3 FET Over-current interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_HS3_OC_Int_En();
 *   if (SCUPM->BDRV_IS.bit.HS3_OC_IS == 1u)
 *   {
 *     BDRV_HS3_OC_CALLBACK();
 *     BDRV_HS3_OC_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_HS3_OC_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->BDRV_ISCLR.reg, SCUPM_BDRV_ISCLR_HS3_OC_ICLR_Pos, SCUPM_BDRV_ISCLR_HS3_OC_ICLR_Msk, 1u);
}
#endif

#if (UC_SERIES == TLE987)
/** \brief clears External Low Side 3 FET Over-current interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Low Side 3 FET Over-current interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_LS3_OC_Int_En();
 *   if (SCUPM->BDRV_IS.bit.LS3_OC_IS == 1u)
 *   {
 *     BDRV_LS3_OC_CALLBACK();
 *     BDRV_LS3_OC_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_LS3_OC_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->BDRV_ISCLR.reg, SCUPM_BDRV_ISCLR_LS3_OC_ICLR_Pos, SCUPM_BDRV_ISCLR_LS3_OC_ICLR_Msk, 1u);
}
#endif

/** \brief enables High Side Driver 1 Drain Source Monitoring interrupt in OFF-State.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the High Side Driver 1 Drain Source Monitoring interrupt in OFF-State.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_HS1_DS_Int_En();
 *   if (SCUPM->BDRV_IS.bit.HS1_DS_IS == 1u)
 *   {
 *     BDRV_HS1_DS_CALLBACK();
 *     BDRV_HS1_DS_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_HS1_DS_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->BDRV_ISCLR.reg, SCUPM_BDRV_ISCLR_HS1_DS_ICLR_Pos, SCUPM_BDRV_ISCLR_HS1_DS_ICLR_Msk, 1u);
}

/** \brief clears Low Side Driver 1 Drain Source Monitoring interrupt flag in OFF-State.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Low Side Driver 1 Drain Source Monitoring interrupt in OFF-State.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_LS1_DS_Int_En();
 *   if (SCUPM->BDRV_IS.bit.LS1_DS_IS == 1u)
 *   {
 *     BDRV_LS1_DS_CALLBACK();
 *     BDRV_LS1_DS_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_LS1_DS_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->BDRV_ISCLR.reg, SCUPM_BDRV_ISCLR_LS1_DS_ICLR_Pos, SCUPM_BDRV_ISCLR_LS1_DS_ICLR_Msk, 1u);
}

/** \brief clears High Side Driver 2 Drain Source Monitoring interrupt flag in OFF-State.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the High Side Driver 2 Drain Source Monitoring interrupt in OFF-State.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_HS2_DS_Int_En();
 *   if (SCUPM->BDRV_IS.bit.HS2_DS_IS == 1u)
 *   {
 *     BDRV_HS2_DS_CALLBACK();
 *     BDRV_HS2_DS_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_HS2_DS_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->BDRV_ISCLR.reg, SCUPM_BDRV_ISCLR_HS2_DS_ICLR_Pos, SCUPM_BDRV_ISCLR_HS2_DS_ICLR_Msk, 1u);
}

/** \brief clears Low Side Driver 2 Drain Source Monitoring interrupt flag in OFF-State.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Low Side Driver 2 Drain Source Monitoring interrupt in OFF-State.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_LS2_DS_Int_En();
 *   if (SCUPM->BDRV_IS.bit.LS2_DS_IS == 1u)
 *   {
 *     BDRV_LS2_DS_CALLBACK();
 *     BDRV_LS2_DS_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_LS2_DS_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->BDRV_ISCLR.reg, SCUPM_BDRV_ISCLR_LS2_DS_ICLR_Pos, SCUPM_BDRV_ISCLR_LS2_DS_ICLR_Msk, 1u);
}

#if (UC_SERIES == TLE987)
/** \brief clears High Side Driver 3 Drain Source Monitoring interrupt flag in OFF-State.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the High Side Driver 3 Drain Source Monitoring interrupt in OFF-State.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_HS3_DS_Int_En();
 *   if (SCUPM->BDRV_IS.bit.HS3_DS_IS == 1u)
 *   {
 *     BDRV_HS3_DS_CALLBACK();
 *     BDRV_HS3_DS_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_HS3_DS_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->BDRV_ISCLR.reg, SCUPM_BDRV_ISCLR_HS3_DS_ICLR_Pos, SCUPM_BDRV_ISCLR_HS3_DS_ICLR_Msk, 1u);
}
#endif

#if (UC_SERIES == TLE987)
/** \brief clears Low Side Driver 3 Drain Source Monitoring interrupt flag in OFF-State.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Low Side Driver 3 Drain Source Monitoring interrupt in OFF-State.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_LS3_DS_Int_En();
 *   if (SCUPM->BDRV_IS.bit.LS3_DS_IS == 1u)
 *   {
 *     BDRV_LS3_DS_CALLBACK();
 *     BDRV_LS3_DS_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_LS3_DS_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->BDRV_ISCLR.reg, SCUPM_BDRV_ISCLR_LS3_DS_ICLR_Pos, SCUPM_BDRV_ISCLR_LS3_DS_ICLR_Msk, 1u);
}
#endif

/** \brief clears Charge Pump Low interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Charge Pump Low interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_VCP_LO_Int_En();
 *   if (SCUPM->BDRV_IS.bit.VCP_LOWTH2_IS == 1u)
 *   {
 *     BDRV_VCP_LO_CALLBACK();
 *     BDRV_VCP_LO_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_VCP_LO_Int_Clr(void)
{
  Field_Wrt32(&SCUPM->BDRV_ISCLR.reg, SCUPM_BDRV_ISCLR_VCP_LOWTH2_ICLR_Pos, SCUPM_BDRV_ISCLR_VCP_LOWTH2_ICLR_Msk, 1u);
}

/** \brief enables External High Side 1 FET Over-current interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External High Side 1 FET Over-current interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_HS1_OC_Int_En();
 *   if (SCUPM->BDRV_IS.bit.HS1_OC_IS == 1u)
 *   {
 *     BDRV_HS1_OC_CALLBACK();
 *     BDRV_HS1_OC_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_HS1_OC_Int_En(void)
{
  Field_Mod32(&SCUPM->BDRV_IRQ_CTRL.reg, SCUPM_BDRV_IRQ_CTRL_HS1_OC_IE_Pos, SCUPM_BDRV_IRQ_CTRL_HS1_OC_IE_Msk, 1u);
}

/** \brief disables External High Side 1 FET Over-current interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External High Side 1 FET Over-current interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_HS1_OC_Int_En();
 *   if (SCUPM->BDRV_IS.bit.HS1_OC_IS == 1u)
 *   {
 *     BDRV_HS1_OC_CALLBACK();
 *     BDRV_HS1_OC_Int_Clr();
 *   }
 *   BDRV_HS1_OC_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_HS1_OC_Int_Dis(void)
{
  Field_Mod32(&SCUPM->BDRV_IRQ_CTRL.reg, SCUPM_BDRV_IRQ_CTRL_HS1_OC_IE_Pos, SCUPM_BDRV_IRQ_CTRL_HS1_OC_IE_Msk, 0u);
}

/** \brief enables External Low Side 1 FET Over-current interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Low Side 1 FET Over-current interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_LS1_OC_Int_En();
 *   if (SCUPM->BDRV_IS.bit.LS1_OC_IS == 1u)
 *   {
 *     BDRV_LS1_OC_CALLBACK();
 *     BDRV_LS1_OC_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_LS1_OC_Int_En(void)
{
  Field_Mod32(&SCUPM->BDRV_IRQ_CTRL.reg, SCUPM_BDRV_IRQ_CTRL_LS1_OC_IE_Pos, SCUPM_BDRV_IRQ_CTRL_LS1_OC_IE_Msk, 1u);
}

/** \brief disables External Low Side 1 FET Over-current interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Low Side 1 FET Over-current interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_LS1_OC_Int_En();
 *   if (SCUPM->BDRV_IS.bit.LS1_OC_IS == 1u)
 *   {
 *     BDRV_LS1_OC_CALLBACK();
 *     BDRV_LS1_OC_Int_Clr();
 *   }
 *   BDRV_LS1_OC_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_LS1_OC_Int_Dis(void)
{
  Field_Mod32(&SCUPM->BDRV_IRQ_CTRL.reg, SCUPM_BDRV_IRQ_CTRL_LS1_OC_IE_Pos, SCUPM_BDRV_IRQ_CTRL_LS1_OC_IE_Msk, 0u);
}

/** \brief enables External High Side 2 FET Over-current interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External High Side 2 FET Over-current interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_HS2_OC_Int_En();
 *   if (SCUPM->BDRV_IS.bit.HS2_OC_IS == 1u)
 *   {
 *     BDRV_HS2_OC_CALLBACK();
 *     BDRV_HS2_OC_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_HS2_OC_Int_En(void)
{
  Field_Mod32(&SCUPM->BDRV_IRQ_CTRL.reg, SCUPM_BDRV_IRQ_CTRL_HS2_OC_IE_Pos, SCUPM_BDRV_IRQ_CTRL_HS2_OC_IE_Msk, 1u);
}

/** \brief disables External High Side 2 FET Over-current interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External High Side 2 FET Over-current interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_HS2_OC_Int_En();
 *   if (SCUPM->BDRV_IS.bit.HS2_OC_IS == 1u)
 *   {
 *     BDRV_HS2_OC_CALLBACK();
 *     BDRV_HS2_OC_Int_Clr();
 *   }
 *   BDRV_HS2_OC_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_HS2_OC_Int_Dis(void)
{
  Field_Mod32(&SCUPM->BDRV_IRQ_CTRL.reg, SCUPM_BDRV_IRQ_CTRL_HS2_OC_IE_Pos, SCUPM_BDRV_IRQ_CTRL_HS2_OC_IE_Msk, 0u);
}

/** \brief enables External Low Side 2 FET Over-current interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Low Side 2 FET Over-current interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_LS2_OC_Int_En();
 *   if (SCUPM->BDRV_IS.bit.LS2_OC_IS == 1u)
 *   {
 *     BDRV_LS2_OC_CALLBACK();
 *     BDRV_LS2_OC_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_LS2_OC_Int_En(void)
{
  Field_Mod32(&SCUPM->BDRV_IRQ_CTRL.reg, SCUPM_BDRV_IRQ_CTRL_LS2_OC_IE_Pos, SCUPM_BDRV_IRQ_CTRL_LS2_OC_IE_Msk, 1u);
}

/** \brief disables External Low Side 2 FET Over-current interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Low Side 2 FET Over-current interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_LS2_OC_Int_En();
 *   if (SCUPM->BDRV_IS.bit.LS2_OC_IS == 1u)
 *   {
 *     BDRV_LS2_OC_CALLBACK();
 *     BDRV_LS2_OC_Int_Clr();
 *   }
 *   BDRV_LS2_OC_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_LS2_OC_Int_Dis(void)
{
  Field_Mod32(&SCUPM->BDRV_IRQ_CTRL.reg, SCUPM_BDRV_IRQ_CTRL_LS2_OC_IE_Pos, SCUPM_BDRV_IRQ_CTRL_LS2_OC_IE_Msk, 0u);
}

#if (UC_SERIES == TLE987)
/** \brief enables External High Side 3 FET Over-current interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External High Side 3 FET Over-current interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_HS3_OC_Int_En();
 *   if (SCUPM->BDRV_IS.bit.HS3_OC_IS == 1u)
 *   {
 *     BDRV_HS3_OC_CALLBACK();
 *     BDRV_HS3_OC_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_HS3_OC_Int_En(void)
{
  Field_Mod32(&SCUPM->BDRV_IRQ_CTRL.reg, SCUPM_BDRV_IRQ_CTRL_HS3_OC_IE_Pos, SCUPM_BDRV_IRQ_CTRL_HS3_OC_IE_Msk, 1u);
}
#endif

#if (UC_SERIES == TLE987)
/** \brief disables External High Side 3 FET Over-current interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External High Side 3 FET Over-current interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_HS3_OC_Int_En();
 *   if (SCUPM->BDRV_IS.bit.HS3_OC_IS == 1u)
 *   {
 *     BDRV_HS3_OC_CALLBACK();
 *     BDRV_HS3_OC_Int_Clr();
 *   }
 *   BDRV_HS3_OC_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_HS3_OC_Int_Dis(void)
{
  Field_Mod32(&SCUPM->BDRV_IRQ_CTRL.reg, SCUPM_BDRV_IRQ_CTRL_HS3_OC_IE_Pos, SCUPM_BDRV_IRQ_CTRL_HS3_OC_IE_Msk, 0u);
}
#endif

#if (UC_SERIES == TLE987)
/** \brief enables External Low Side 3 FET Over-current interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Low Side 3 FET Over-current interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_LS3_OC_Int_En();
 *   if (SCUPM->BDRV_IS.bit.LS3_OC_IS == 1u)
 *   {
 *     BDRV_LS3_OC_CALLBACK();
 *     BDRV_LS3_OC_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_LS3_OC_Int_En(void)
{
  Field_Mod32(&SCUPM->BDRV_IRQ_CTRL.reg, SCUPM_BDRV_IRQ_CTRL_LS3_OC_IE_Pos, SCUPM_BDRV_IRQ_CTRL_LS3_OC_IE_Msk, 1u);
}
#endif

#if (UC_SERIES == TLE987)
/** \brief disables External Low Side 3 FET Over-current interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Low Side 3 FET Over-current interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_LS3_OC_Int_En();
 *   if (SCUPM->BDRV_IS.bit.LS3_OC_IS == 1u)
 *   {
 *     BDRV_LS3_OC_CALLBACK();
 *     BDRV_LS3_OC_Int_Clr();
 *   }
 *   BDRV_LS3_OC_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_LS3_OC_Int_Dis(void)
{
  Field_Mod32(&SCUPM->BDRV_IRQ_CTRL.reg, SCUPM_BDRV_IRQ_CTRL_LS3_OC_IE_Pos, SCUPM_BDRV_IRQ_CTRL_LS3_OC_IE_Msk, 0u);
}
#endif

/** \brief enables High Side Driver 1 Drain Source Monitoring interrupt in OFF-State.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the High Side Driver 1 Drain Source Monitoring interrupt in OFF-State.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_HS1_DS_Int_En();
 *   if (SCUPM->BDRV_IS.bit.HS1_DS_IS == 1u)
 *   {
 *     BDRV_HS1_DS_CALLBACK();
 *     BDRV_HS1_DS_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_HS1_DS_Int_En(void)
{
  Field_Mod32(&SCUPM->BDRV_IRQ_CTRL.reg, SCUPM_BDRV_IRQ_CTRL_HS1_DS_IE_Pos, SCUPM_BDRV_IRQ_CTRL_HS1_DS_IE_Msk, 1u);
}

/** \brief disables High Side Driver 1 Drain Source Monitoring interrupt in OFF-State.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the High Side Driver 1 Drain Source Monitoring interrupt in OFF-State.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_HS1_DS_Int_En();
 *   if (SCUPM->BDRV_IS.bit.HS1_DS_IS == 1u)
 *   {
 *     BDRV_HS1_DS_CALLBACK();
 *     BDRV_HS1_DS_Int_Clr();
 *   }
 *   BDRV_HS1_DS_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_HS1_DS_Int_Dis(void)
{
  Field_Mod32(&SCUPM->BDRV_IRQ_CTRL.reg, SCUPM_BDRV_IRQ_CTRL_HS1_DS_IE_Pos, SCUPM_BDRV_IRQ_CTRL_HS1_DS_IE_Msk, 0u);
}

/** \brief enables Low Side Driver 1 Drain Source Monitoring interrupt in OFF-State.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Low Side Driver 1 Drain Source Monitoring interrupt in OFF-State.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_LS1_DS_Int_En();
 *   if (SCUPM->BDRV_IS.bit.LS1_DS_IS == 1u)
 *   {
 *     BDRV_LS1_DS_CALLBACK();
 *     BDRV_LS1_DS_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_LS1_DS_Int_En(void)
{
  Field_Mod32(&SCUPM->BDRV_IRQ_CTRL.reg, SCUPM_BDRV_IRQ_CTRL_LS1_DS_IE_Pos, SCUPM_BDRV_IRQ_CTRL_LS1_DS_IE_Msk, 1u);
}

/** \brief disables Low Side Driver 1 Drain Source Monitoring interrupt in OFF-State.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Low Side Driver 1 Drain Source Monitoring interrupt in OFF-State.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_LS1_DS_Int_En();
 *   if (SCUPM->BDRV_IS.bit.LS1_DS_IS == 1u)
 *   {
 *     BDRV_LS1_DS_CALLBACK();
 *     BDRV_LS1_DS_Int_Clr();
 *   }
 *   BDRV_LS1_DS_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_LS1_DS_Int_Dis(void)
{
  Field_Mod32(&SCUPM->BDRV_IRQ_CTRL.reg, SCUPM_BDRV_IRQ_CTRL_LS1_DS_IE_Pos, SCUPM_BDRV_IRQ_CTRL_LS1_DS_IE_Msk, 0u);
}

/** \brief enables High Side Driver 2 Drain Source Monitoring interrupt in OFF-State.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the High Side Driver 2 Drain Source Monitoring interrupt in OFF-State.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_HS2_DS_Int_En();
 *   if (SCUPM->BDRV_IS.bit.HS2_DS_IS == 1u)
 *   {
 *     BDRV_HS2_DS_CALLBACK();
 *     BDRV_HS2_DS_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_HS2_DS_Int_En(void)
{
  Field_Mod32(&SCUPM->BDRV_IRQ_CTRL.reg, SCUPM_BDRV_IRQ_CTRL_HS2_DS_IE_Pos, SCUPM_BDRV_IRQ_CTRL_HS2_DS_IE_Msk, 1u);
}

/** \brief disables High Side Driver 2 Drain Source Monitoring interrupt in OFF-State.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the High Side Driver 2 Drain Source Monitoring interrupt in OFF-State.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_HS2_DS_Int_En();
 *   if (SCUPM->BDRV_IS.bit.HS2_DS_IS == 1u)
 *   {
 *     BDRV_HS2_DS_CALLBACK();
 *     BDRV_HS2_DS_Int_Clr();
 *   }
 *   BDRV_HS2_DS_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_HS2_DS_Int_Dis(void)
{
  Field_Mod32(&SCUPM->BDRV_IRQ_CTRL.reg, SCUPM_BDRV_IRQ_CTRL_HS2_DS_IE_Pos, SCUPM_BDRV_IRQ_CTRL_HS2_DS_IE_Msk, 0u);
}

/** \brief enables Low Side Driver 2 Drain Source Monitoring interrupt in OFF-State.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Low Side Driver 2 Drain Source Monitoring interrupt in OFF-State.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_LS2_DS_Int_En();
 *   if (SCUPM->BDRV_IS.bit.LS2_DS_IS == 1u)
 *   {
 *     BDRV_LS2_DS_CALLBACK();
 *     BDRV_LS2_DS_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_LS2_DS_Int_En(void)
{
  Field_Mod32(&SCUPM->BDRV_IRQ_CTRL.reg, SCUPM_BDRV_IRQ_CTRL_LS2_DS_IE_Pos, SCUPM_BDRV_IRQ_CTRL_LS2_DS_IE_Msk, 1u);
}

/** \brief disables Low Side Driver 2 Drain Source Monitoring interrupt in OFF-State.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Low Side Driver 2 Drain Source Monitoring interrupt in OFF-State.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_LS2_DS_Int_En();
 *   if (SCUPM->BDRV_IS.bit.LS2_DS_IS == 1u)
 *   {
 *     BDRV_LS2_DS_CALLBACK();
 *     BDRV_LS2_DS_Int_Clr();
 *   }
 *   BDRV_LS2_DS_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_LS2_DS_Int_Dis(void)
{
  Field_Mod32(&SCUPM->BDRV_IRQ_CTRL.reg, SCUPM_BDRV_IRQ_CTRL_LS2_DS_IE_Pos, SCUPM_BDRV_IRQ_CTRL_LS2_DS_IE_Msk, 0u);
}

#if (UC_SERIES == TLE987)
/** \brief enables High Side Driver 3 Drain Source Monitoring interrupt in OFF-State.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the High Side Driver 3 Drain Source Monitoring interrupt in OFF-State.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_HS3_DS_Int_En();
 *   if (SCUPM->BDRV_IS.bit.HS3_DS_IS == 1u)
 *   {
 *     BDRV_HS3_DS_CALLBACK();
 *     BDRV_HS3_DS_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_HS3_DS_Int_En(void)
{
  Field_Mod32(&SCUPM->BDRV_IRQ_CTRL.reg, SCUPM_BDRV_IRQ_CTRL_HS3_DS_IE_Pos, SCUPM_BDRV_IRQ_CTRL_HS3_DS_IE_Msk, 1u);
}
#endif

#if (UC_SERIES == TLE987)
/** \brief disables High Side Driver 3 Drain Source Monitoring interrupt in OFF-State.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the High Side Driver 3 Drain Source Monitoring interrupt in OFF-State.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_HS3_DS_Int_En();
 *   if (SCUPM->BDRV_IS.bit.HS3_DS_IS == 1u)
 *   {
 *     BDRV_HS3_DS_CALLBACK();
 *     BDRV_HS3_DS_Int_Clr();
 *   }
 *   BDRV_HS3_DS_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_HS3_DS_Int_Dis(void)
{
  Field_Mod32(&SCUPM->BDRV_IRQ_CTRL.reg, SCUPM_BDRV_IRQ_CTRL_HS3_DS_IE_Pos, SCUPM_BDRV_IRQ_CTRL_HS3_DS_IE_Msk, 0u);
}
#endif

#if (UC_SERIES == TLE987)
/** \brief enables Low Side Driver 3 Drain Source Monitoring interrupt in OFF-State.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Low Side Driver 3 Drain Source Monitoring interrupt in OFF-State.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_LS3_DS_Int_En();
 *   if (SCUPM->BDRV_IS.bit.LS3_DS_IS == 1u)
 *   {
 *     BDRV_LS3_DS_CALLBACK();
 *     BDRV_LS3_DS_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_LS3_DS_Int_En(void)
{
  Field_Mod32(&SCUPM->BDRV_IRQ_CTRL.reg, SCUPM_BDRV_IRQ_CTRL_LS3_DS_IE_Pos, SCUPM_BDRV_IRQ_CTRL_LS3_DS_IE_Msk, 1u);
}
#endif

#if (UC_SERIES == TLE987)
/** \brief disables Low Side Driver 3 Drain Source Monitoring interrupt in OFF-State.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Low Side Driver 3 Drain Source Monitoring interrupt in OFF-State.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_LS3_DS_Int_En();
 *   if (SCUPM->BDRV_IS.bit.LS3_DS_IS == 1u)
 *   {
 *     BDRV_LS3_DS_CALLBACK();
 *     BDRV_LS3_DS_Int_Clr();
 *   }
 *   BDRV_LS3_DS_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_LS3_DS_Int_Dis(void)
{
  Field_Mod32(&SCUPM->BDRV_IRQ_CTRL.reg, SCUPM_BDRV_IRQ_CTRL_LS3_DS_IE_Pos, SCUPM_BDRV_IRQ_CTRL_LS3_DS_IE_Msk, 0u);
}
#endif

/** \brief enables Charge Pump Low interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Charge Pump Low interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_VCP_LO_Int_En();
 *   if (SCUPM->BDRV_IS.bit.VCP_LOWTH2_IS == 1u)
 *   {
 *     BDRV_VCP_LO_CALLBACK();
 *     BDRV_VCP_LO_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_VCP_LO_Int_En(void)
{
  Field_Mod32(&SCUPM->BDRV_IRQ_CTRL.reg, SCUPM_BDRV_IRQ_CTRL_VCP_LOWTH2_IE_Pos, SCUPM_BDRV_IRQ_CTRL_VCP_LOWTH2_IE_Msk, 1u);
}

/** \brief disables Charge Pump Low interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Charge Pump Low interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_VCP_LO_Int_En();
 *   if (SCUPM->BDRV_IS.bit.VCP_LOWTH2_IS == 1u)
 *   {
 *     BDRV_VCP_LO_CALLBACK();
 *     BDRV_VCP_LO_Int_Clr();
 *   }
 *   BDRV_VCP_LO_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_VCP_LO_Int_Dis(void)
{
  Field_Mod32(&SCUPM->BDRV_IRQ_CTRL.reg, SCUPM_BDRV_IRQ_CTRL_VCP_LOWTH2_IE_Pos, SCUPM_BDRV_IRQ_CTRL_VCP_LOWTH2_IE_Msk, 0u);
}

/** \brief Reads the Bridge Driver High-Side 1 Over-Current Status Flag
*
* \return uint8 Status Flag
*/
INLINE uint8 BDRV_HS1_OC_Int_Sts(void)
{
  return u1_Field_Rd32(&SCUPM->BDRV_IS.reg, SCUPM_BDRV_IS_HS1_OC_IS_Pos, SCUPM_BDRV_IS_HS1_OC_IS_Msk);
}

/** \brief Reads the Bridge Driver Low-Side 1 Over-Current Status Flag
*
* \return uint8 Status Flag
*/
INLINE uint8 BDRV_LS1_OC_Int_Sts(void)
{
  return u1_Field_Rd32(&SCUPM->BDRV_IS.reg, SCUPM_BDRV_IS_LS1_OC_IS_Pos, SCUPM_BDRV_IS_LS1_OC_IS_Msk);
}

/** \brief Reads the Bridge Driver High-Side 2 Over-Current Status Flag
*
* \return uint8 Status Flag
*/
INLINE uint8 BDRV_HS2_OC_Int_Sts(void)
{
  return u1_Field_Rd32(&SCUPM->BDRV_IS.reg, SCUPM_BDRV_IS_HS2_OC_IS_Pos, SCUPM_BDRV_IS_HS2_OC_IS_Msk);
}

/** \brief Reads the Bridge Driver Low-Side 2 Over-Current Status Flag
*
* \return uint8 Status Flag
*/
INLINE uint8 BDRV_LS2_OC_Int_Sts(void)
{
  return u1_Field_Rd32(&SCUPM->BDRV_IS.reg, SCUPM_BDRV_IS_LS2_OC_IS_Pos, SCUPM_BDRV_IS_LS2_OC_IS_Msk);
}

#if (UC_SERIES == TLE987)
/** \brief Reads the Bridge Driver High-Side 3 Over-Current Status Flag
*
* \return uint8 Status Flag
*/
INLINE uint8 BDRV_HS3_OC_Int_Sts(void)
{
  return u1_Field_Rd32(&SCUPM->BDRV_IS.reg, SCUPM_BDRV_IS_HS3_OC_IS_Pos, SCUPM_BDRV_IS_HS3_OC_IS_Msk);
}
#endif

#if (UC_SERIES == TLE987)
/** \brief Reads the Bridge Driver Low-Side 3 Over-Current Status Flag
*
* \return uint8 Status Flag
*/
INLINE uint8 BDRV_LS3_OC_Int_Sts(void)
{
  return u1_Field_Rd32(&SCUPM->BDRV_IS.reg, SCUPM_BDRV_IS_LS3_OC_IS_Pos, SCUPM_BDRV_IS_LS3_OC_IS_Msk);
}
#endif

/** \brief Reads the Bridge Driver High-Side 1 Pre-Driver Short Status Flag
*
* \return uint8 Status Flag
*/
INLINE uint8 BDRV_HS1_DS_Int_Sts(void)
{
  return u1_Field_Rd32(&SCUPM->BDRV_IS.reg, SCUPM_BDRV_IS_HS1_DS_IS_Pos, SCUPM_BDRV_IS_HS1_DS_IS_Msk);
}

/** \brief Reads the Bridge Driver Low-Side 1 Pre-Driver Short Status Flag
*
* \return uint8 Status Flag
*/
INLINE uint8 BDRV_LS1_DS_Int_Sts(void)
{
  return u1_Field_Rd32(&SCUPM->BDRV_IS.reg, SCUPM_BDRV_IS_LS1_DS_IS_Pos, SCUPM_BDRV_IS_LS1_DS_IS_Msk);
}

/** \brief Reads the Bridge Driver High-Side 2 Pre-Driver Short Status Flag
*
* \return uint8 Status Flag
*/
INLINE uint8 BDRV_HS2_DS_Int_Sts(void)
{
  return u1_Field_Rd32(&SCUPM->BDRV_IS.reg, SCUPM_BDRV_IS_HS2_DS_IS_Pos, SCUPM_BDRV_IS_HS2_DS_IS_Msk);
}

/** \brief Reads the Bridge Driver Low-Side 2 Pre-Driver Short Status Flag
*
* \return uint8 Status Flag
*/
INLINE uint8 BDRV_LS2_DS_Int_Sts(void)
{
  return u1_Field_Rd32(&SCUPM->BDRV_IS.reg, SCUPM_BDRV_IS_LS2_DS_IS_Pos, SCUPM_BDRV_IS_LS2_DS_IS_Msk);
}

#if (UC_SERIES == TLE987)
/** \brief Reads the Bridge Driver High-Side 3 Pre-Driver Short Status Flag
*
* \return uint8 Status Flag
*/
INLINE uint8 BDRV_HS3_DS_Int_Sts(void)
{
  return u1_Field_Rd32(&SCUPM->BDRV_IS.reg, SCUPM_BDRV_IS_HS3_DS_IS_Pos, SCUPM_BDRV_IS_HS3_DS_IS_Msk);
}
#endif

#if (UC_SERIES == TLE987)
/** \brief Reads the Bridge Driver Low-Side 3 Pre-Driver Short Status Flag
*
* \return uint8 Status Flag
*/
INLINE uint8 BDRV_LS3_DS_Int_Sts(void)
{
  return u1_Field_Rd32(&SCUPM->BDRV_IS.reg, SCUPM_BDRV_IS_LS3_DS_IS_Pos, SCUPM_BDRV_IS_LS3_DS_IS_Msk);
}
#endif

/** \brief Reads the Bridge Driver VCP Lower Threshold 2 Measurement Status Flag
*
* \return uint8 Status Flag
*/
INLINE uint8 BDRV_VCP_LO_Int_Sts(void)
{
  return u1_Field_Rd32(&SCUPM->BDRV_IS.reg, SCUPM_BDRV_IS_VCP_LOWTH2_IS_Pos, SCUPM_BDRV_IS_VCP_LOWTH2_IS_Msk);
}

/** \brief Returns the Trimming of the internal driver charge current (Digital value)
*
* \return Trimming of the internal driver charge current
*/
INLINE uint8 BDRV_getChrgCurrent_dig(void)
{
  return BDRV->CTRL3.bit.ICHARGE_TRIM;
}

/** \brief Sets the Trimming of the internal driver charge current (Digital value)
* \brief For setting the Charge Current in mA please use function \link BDRV_setChrgCurrent_mA \endlink
* 
* \param u8_cur_dig Trimming of the internal driver charge current
*/
INLINE void BDRV_setChrgCurrent_dig(uint8 u8_cur_dig)
{
  BDRV->CTRL3.bit.ICHARGE_TRIM = u8_cur_dig;
}

/** \brief Returns the Charge current range select (Digital value)
*
* \return Charge current range select (0: Half Range, 1: Full Range)
*/
INLINE uint8 BDRV_getChrgCurrentRange_dig(void)
{
  return BDRV->CTRL3.bit.ICHARGEDIV2_N;
}

/** \brief Sets the Charge current range select (Digital value)
* \brief For setting the Charge Current in mA please use function \link BDRV_setChrgCurrent_mA \endlink
*
* \param u8_cur_range_dig Charge current range select (0: Half Range, 1: Full Range)
*/
INLINE void BDRV_setChrgCurrentRange_dig(uint8 u8_cur_range_dig)
{
  BDRV->CTRL3.bit.ICHARGEDIV2_N = u8_cur_range_dig;
}

/** \brief Returns the Trimming of the internal driver dis-charge current (Digital value)
*
* \return Trimming of the internal driver dis-charge current
*/
INLINE uint8 BDRV_getDischrgCurrent_dig(void)
{
  return BDRV->CTRL3.bit.IDISCHARGE_TRIM;
}

/** \brief Sets the Trimming of the internal driver dis-charge current (Digital value)
* \brief For setting the Dircharge Current in mA please use function \link BDRV_setDischrgCurrent_mA \endlink
*
* \param u8_cur_dig Trimming of the internal driver dis-charge current
*/
INLINE void BDRV_setDischrgCurrent_dig(uint8 u8_cur_dig)
{
  BDRV->CTRL3.bit.IDISCHARGE_TRIM = u8_cur_dig;
}

/** \brief Returns the Discharge current range select (Digital value)
*
* \return Discharge current range select
*/
INLINE uint8 BDRV_getDischrgCurrentRange_dig(void)
{
  return BDRV->CTRL3.bit.IDISCHARGEDIV2_N;
}

/** \brief Sets the Discharge current range select (Digital value)
* \brief For setting the Dircharge Current in mA please use function \link BDRV_setDischrgCurrent_mA \endlink
*
* \param u8_cur_range_dig Discharge current range select
*/
INLINE void BDRV_setDischrgCurrentRange_dig(uint8 u8_cur_range_dig)
{
  BDRV->CTRL3.bit.IDISCHARGEDIV2_N = u8_cur_range_dig;
}

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/
/** \brief Initializes the BridgeDriver based on the IFXConfigWizard configuration
 *
 * \ingroup bdrv_api
 */
void BDRV_Init(void);

#if (UC_SERIES == TLE987)
/** \brief Sets the bridge in the desired state. For each of the six drivers the state can be defined.
 * \brief In order to operate a 3phase motor all the six driver stages have to be configured to Ch_PWM.
 * \brief See \link TBdrv_Ch_Cfg \endlink
 *
 * \param LS1_Cfg sets the desired mode for LS MOSFET of phase1
 * \param HS1_Cfg sets the desired mode for HS MOSFET of phase1
 * \param LS2_Cfg sets the desired mode for LS MOSFET of phase2
 * \param HS2_Cfg sets the desired mode for HS MOSFET of phase2
 * \param LS3_Cfg sets the desired mode for LS MOSFET of phase3
 * \param HS3_Cfg sets the desired mode for HS MOSFET of phase3
 *
 * \brief <b>Example</b><br>
 * \brief This example configures BDRV Bridge channels HS1, HS2, LS1, LS2, LS3 and HS3 to be enabled with PWM.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     BDRV_Set_Bridge(Ch_PWM, Ch_PWM, Ch_PWM, Ch_PWM, Ch_PWM, Ch_PWM);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
void BDRV_Set_Bridge(TBdrv_Ch_Cfg LS1_Cfg,
                     TBdrv_Ch_Cfg HS1_Cfg,
                     TBdrv_Ch_Cfg LS2_Cfg,
                     TBdrv_Ch_Cfg HS2_Cfg,
                     TBdrv_Ch_Cfg LS3_Cfg,
                     TBdrv_Ch_Cfg HS3_Cfg);
#else
/** \brief Sets the bridge in the desired state. For each of the four drivers the state can be defined.
 * \brief See \link TBdrv_Ch_Cfg \endlink
 *
 * \param LS1_Cfg sets the desired mode for LS MOSFET of phase1
 * \param HS1_Cfg sets the desired mode for HS MOSFET of phase1
 * \param LS2_Cfg sets the desired mode for LS MOSFET of phase2
 * \param HS2_Cfg sets the desired mode for HS MOSFET of phase2
 *
 * \brief <b>Example</b><br>
 * \brief This example configures BDRV Bridge channels HS1, HS2, LS1 and LS2 to be enabled with PWM.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     BDRV_Set_Bridge(Ch_PWM, Ch_PWM, Ch_PWM, Ch_PWM);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
void BDRV_Set_Bridge(TBdrv_Ch_Cfg LS1_Cfg,
                     TBdrv_Ch_Cfg HS1_Cfg,
                     TBdrv_Ch_Cfg LS2_Cfg,
                     TBdrv_Ch_Cfg HS2_Cfg);
#endif

/** \brief sets an individual driver of the BridgeDriver in the desired state
 *
 * \param BDRV_Ch selects the channel for which the configuration should be set, see \link TBdrv_Ch \endlink
 * \param Ch_Cfg selects the mode of operation for that channel, see \link TBdrv_Ch_Cfg \endlink
 *
 * \brief <b>Example</b><br>
 * \brief This example configures BDRV Bridge channel HS1 to be enabled with PWM.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     BDRV_Set_Channel(HS1, Ch_PWM);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
void BDRV_Set_Channel(TBdrv_Ch BDRV_Ch, TBdrv_Ch_Cfg Ch_Cfg);

/** \brief clears individual status flags and interrupt status flags of the BridgeDriver
 *
 * \param Sts_Bit status bit(s) to be cleared
 *
 * \brief <b>Example</b>
 * \brief This example enables BDRV LS1, LS2, HS1 and HS2 Over-Current Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     BDRV_Clr_Sts(LS1_OC | LS2_OC | LS3_OC | HS1_OC | HS2_OC | HS3_OC);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
void BDRV_Clr_Sts(uint32 Sts_Bit);

/** \brief sets Interrupt Enable for the individual MOSFETs (channels)
 *
 * \param BDRV_Ch Channel selection, see \link TBdrv_Ch \endlink
 * \param Ch_Int selection for the desired interrupt to be enabled, see \link TBdrv_Ch_Int \endlink
 *
 * \brief <b>Example</b><br>
 * \brief This example enables BDRV HS1 Over-Current Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     BDRV_Set_Int_Channel(HS1, Int_OC);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
void BDRV_Set_Int_Channel(TBdrv_Ch BDRV_Ch, TBdrv_Ch_Int Ch_Int);

/** \brief Open Load detection, detects whether a motor is connected
 *
 * \retval true no motor detected,
 * \retval false motor connected
 *
 * \brief <b>Example</b><br>
 * \brief This example disables all BDRV channels when Open Load is detected.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     if (BDRV_Diag_OpenLoad() == true)
 *     {
 *         BDRV_Set_Channel(LS1, Ch_Off);
 *         BDRV_Set_Channel(LS2, Ch_Off);
 *         BDRV_Set_Channel(HS1, Ch_Off);
 *         BDRV_Set_Channel(HS2, Ch_Off);
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
bool BDRV_Diag_OpenLoad(void);

/** \brief Off-diagnosis
 * \brief Detects a short of the phases either to Gnd or to Vbat
 *
 * \retval true any short detected
 * \retval false no short
 *
 * \ingroup bdrv_api
 */
TBDRV_Off_Diag BDRV_Off_Diagnosis(void);


/** \brief Sets the Voltage Threshold for Drain-Source Monitoring of external FETs
 *
 * \param BDRV_Threshold selection for the desired voltage threshold, see \link TBdrv_DSM_Threshold \endlink
 *
 * \ingroup bdrv_api
 */
void BDRV_Set_DSM_Threshold(TBdrv_DSM_Threshold BDRV_Threshold);

/** \brief Returns the BDRV charge current
 * \brief This function considers BDRV->CTRL3.bit.ICHARGE_TRIM as well as BDRV->CTRL3.bit.ICHARGEDIV2_N
 *
 * \return BDRV_Current selection for the desired charge current, see \link TBDRV_Curr \endlink
 *
 * \ingroup bdrv_api
 */
TBDRV_Curr BDRV_getChrgCurrent_mA(void);

/** \brief Sets the BDRV charge current
 * \brief This function sets BDRV->CTRL3.bit.ICHARGE_TRIM as well as BDRV->CTRL3.bit.ICHARGEDIV2_N
 *
 * \param BDRV_Current selection for the desired charge current, see \link TBDRV_Curr \endlink
 *
 * \ingroup bdrv_api
 */
void BDRV_setChrgCurrent_mA(TBDRV_Curr BDRV_Current);

/** \brief Returns BDRV discharge current
 * \brief This function considers BDRV->CTRL3.bit.IDISCHARGE_TRIM as well as BDRV->CTRL3.bit.IDISCHARGEDIV2_N
 *
 * \return BDRV_Current selection for the desired discharge current, see \link TBDRV_Curr \endlink
 *
 * \ingroup bdrv_api
 */
TBDRV_Curr BDRV_getDischrgCurrent_mA(void);

/** \brief Sets the BDRV discharge current
 * \brief This function sets BDRV->CTRL3.bit.IDISCHARGE_TRIM as well as BDRV->CTRL3.bit.IDISCHARGEDIV2_N
 *
 * \param BDRV_Current selection for the desired discharge current, see \link TBDRV_Curr \endlink
 *
 * \ingroup bdrv_api
 */
void BDRV_setDischrgCurrent_mA(TBDRV_Curr BDRV_Current);


#endif
