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
 * \file     bootrom.h
 *
 * \brief    BootROM low level access library
 *
 * \version  V0.3.0
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
** V0.1.0: 2012-08-31, DM:   Initial version                                  **
** V0.1.1: 2012-11-30, DM:   Implementation of all BOOTROM functions          **
**                           described in the TLE986x AA-Step BootROM UM V0.9 **
** V0.1.2: 2012-12-03, DM:   Defining the function pointers to be const       **
**                           to save unnecessary RAM usage                    **
**                           BootROM_Init() function removed                  **
** V0.1.3: 2013-11-20, DM:   handle WDT1 and Interrupts in ProgramPage()      **
**                           function,                                        **
**                           GetCustomerID() function added                   **
** V0.1.4: 2014-05-14, DM:   Add NVM protect/unprotect functions (BB-step)    **
** V0.1.5: 2014-05-18, DM:   Provide a union/struct for the encoding of the   **
**                           Customer ID                                      **
** V0.1.6: 2014-06-27, TA:   Changed to type definitions from Types.h         **
** V0.1.7: 2014-09-22, DM:   USER_ECC_CHECK modified, parameter added         **
**                           ProgramPage: interrupts disabled over the entire **
**                           NVM programming flow, to prevent from nested     **
**                           NVM operations during assembly buffer filling    **
** V0.1.8: 2015-06-03, DM:   BootROM entry point defines moved into bootrom.h **
** V0.1.9: 2015-07-03, DM:   BE-Step compatible                               **
**                           USER_MAPRAM_INIT function added                  **
** V0.2.0: 2015-07-22, DM:   typedef unions added for various return values   **
** V0.2.1: 2016-04-14, DM:   BF-Step BootROM API extension added              **
** V0.2.2: 2017-09-29, DM:   BootROM functions return values corrected        **
**                           GetCustomerID() parameter changed                **
**                           MISRA 2012 compliance, the following PC-Lint     **
**                           rules are globally deactivated:                  **
**                           - Info 793: ANSI/ISO limit of 6 'significant     **
**                             characters in an external identifier           **
**                           - Info 835: A zero has been given as right       **
**                             argument to operator                           **
**                           - Info 845: The left argument to operator '&'    **
**                             is certain to be 0                             **
**                           The following rules are locally deactivated:     **
**                           - Note 19: Suppressing MISRA 2012 Error 19:      **
**                             Useless Declaration                            **
**                           - Note 970: Suppressing MISRA 2012 MISRA 2012    **
**                             Directive 4.6                                  **
**                           - Note 923: cast from unsigned int to pointer    **
**                            [MISRA Rule 45]                                 **
** V0.2.3: 2018-03-12, DM:   The following rules are locally deactivated:     **
**                           - Note 929: cast from pointer to pointer         **
**                             [MISRA 2012 Rule 11.3, required], [MISRA 2012  **
**                             Rule 11.5, advisory]                           **
**                           - Note 9018: declaration of symbol 'CustID'      **
**                             with union based type 'const TCustomerID *'    **
**                             [MISRA 2012 Rule 19.2, advisory]               **
**                           The following rules are activated:               **
**                           - Note 970: Suppressing MISRA 2012 MISRA 2012    **
**                             Directive 4.6                                  **
** V0.2.4: 2018-11-27, JO:   Doxygen update                                   **
**                           Move revision history from bootrom.c to bootrom.h**
** V0.2.5: 2019-02-11, DM:   Entry points definition reworked to remove       **
**                           MISRA error                                      **
** V0.2.6: 2019-09-10, JO:   Enable interrupts in ProgramPage in case of a    **
**                           NVM error                                        **
** V0.2.7: 2020-04-15, BG:   Updated revision history format                  **
** V0.2.8: 2020-07-15, BG:   Corrected example code                           **
** V0.2.9: 2020-07-14, JO:   EP-431: remove ARMCC v6 Compiler warnings        **
**                           - Added const to parameter CustID in call of     **
**                             function USER_READ_100TP                       **
** V0.3.0: 2020-07-21, BG:   EP-439: Formatted .h/.c files                    **
*******************************************************************************/

#ifndef _BOOTROM_H
#define _BOOTROM_H

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "types.h"
#include "RTE_Components.h"

/*******************************************************************************
**                          Global Macro Definitions                          **
*******************************************************************************/
#define FlashPageSize                   (128U)
#define FlashSectorSize                 (4096U)

/*******************************************************************************
** Entry points into the BootROM                                              **
*******************************************************************************/
#define addr_USER_CFLASH_WR_PROT_EN     (0x3925u)
#define addr_USER_CFLASH_WR_PROT_DIS    (0x391Du)
#define addr_USER_CFLASH_RD_PROT_EN     (0x3915u)
#define addr_USER_CFLASH_RD_PROT_DIS    (0x390Du)
#define addr_USER_DFLASH_WR_PROT_EN     (0x3905u)
#define addr_USER_DFLASH_WR_PROT_DIS    (0x38FDu)
#define addr_USER_DFLASH_RD_PROT_EN     (0x38F5u)
#define addr_USER_DFLASH_RD_PROT_DIS    (0x38EDu)
#define addr_USER_OPENAB                (0x38E5u)
#define addr_USER_PROG                  (0x38DDu)
#define addr_USER_ERASEPG               (0x38D5u)
#define addr_USER_ABORTPROG             (0x38CDu)
#define addr_USER_NVMRDY                (0x38C5u)
#define addr_USER_READ_CAL              (0x38BDu)
#define addr_USER_NVM_CONFIG            (0x38B5u)
#define addr_USER_NVM_ECC2ADDR          (0x38ADu)
#define addr_USER_MAPRAM_INIT           (0x389Du)
#define addr_USER_READ_100TP            (0x3875u)
#define addr_USER_100TP_PROG            (0x386Du)
#define addr_USER_ERASE_SECTOR          (0x3865u)
#define addr_USER_RAM_MBIST_START       (0x384Du)
#define addr_USER_NVM_ECC_CHECK         (0x3845u)
#define addr_USER_ECC_CHECK             (0x383Du)
/* BF-Step BootROM API extension */
#ifdef RTE_DEVICE_BF_STEP
  #define addr_USER_ERASEPG_VERIFY      (0x3885u)
  #define addr_USER_ERASE_SECTOR_VERIFY (0x388Du)
  #define addr_USER_VERIFY_PAGE         (0x3895u)
#endif /* RTE_DEVICE_BF_STEP */

/*******************************************************************************
** Customer ID struct                                                         **
*******************************************************************************/
/** \union TCustomerID
 *  \brief This union defines the return parameter of \link GetCustomerID \endlink
 */
typedef union
{
  uint32 reg;
  struct
  {
    uint32           : 8;  /*!< [0..7]   rfu                                  */
    uint32 Step      : 8;  /*!< [15..8]  design step major/minor number [HEX] */
    uint32 Clock     : 2;  /*!< [17..16] clock frequency                      */
    uint32 Package   : 2;  /*!< [19..18] package code                         */
    uint32 SalesCode : 4;  /*!< [23..20] device sales code [DEC]              */
    uint32 Family    : 8;  /*!< [31..24] family code                          */
  } bit;                   /*!< [32] BitSize                                  */
} TCustomerID;

/*******************************************************************************
** USER_100TP_PROG input struct                                               **
*******************************************************************************/
/** \union T100TP_Data
 *  \brief These structs define the input data structure for \link USER_100TP_PROG \endlink
 */
typedef struct
{
  uint8 offset;
  uint8 date;
} TData;

typedef struct
{
  uint8 count;
  TData data[127];
} T100TP_Data;

/*******************************************************************************
** Function USER_100TP_PROG: return value decoding                            **
*******************************************************************************/
/** \union TUser_100TP_Prog
 *  \brief This union defines the return value of \link USER_100TP_PROG \endlink
 */
typedef union
{
  uint8   reg;
  struct
  {
    uint8 GlobFail  :  1; /**< OR-combination of all fail */
    uint8 OffsetFail:  1; /**< at least one offset witin input struct is out of range */
    uint8 CustIDFail:  1; /**< at least one date addresses the protected CustomerID bytes */
    uint8           :  4;
    uint8 ExecFail  :  1; /**< 100TP pages are write protected, 100x programming reached already */
  } bit;
} TUser_100TP_Prog;

/*******************************************************************************
** Function USER_PROG: type definition of the parameter PROG_FLAG             **
*******************************************************************************/
/** \union TProgFlag
 *  \brief This struct defines the option flag for the \link USER_PROG \endlink function
 */
typedef union
{
  uint8   reg;
  struct
  {
    uint8 RAM_Branch   : 1; /*!< [0] 1 = RAM branch enables, 0 = RAM branch disabled */
    uint8 CorrAct      : 1; /*!< [1] 1 = retry/disturb handling enabled, 0 = retry/disturb handling disabled */
  } bit;
} TProgFlag;

/*******************************************************************************
** Function USER_PROG: return value decoding                                  **
*******************************************************************************/
/** \union TUser_Prog
 *  \brief This union defines the return value of \link USER_PROG \endlink
 */
typedef union
{
  uint8   reg;
  struct
  {
    uint8 GlobFail   :  1; /**< OR-combination of all fail */
    uint8            :  3;
    uint8 VerifyFail :  1; /**< verify has failed */
    uint8 EmergExit  :  1; /**< function was exited because of Emergency Exit */
    uint8 SparePgFail:  1; /**< no new Spare Page was found */
    uint8 ExecFail   :  1; /**< Assembly Buffer not opened */
  } bit;
} TUser_Prog;

/*******************************************************************************
** Function USER_OpenAB: return value decoding                                **
*******************************************************************************/
/** \union TUser_OpenAB
 *  \brief This union defines the return value of \link USER_OPENAB \endlink
 */
typedef union
{
  uint8   reg;
  struct
  {
    uint8 ABFail   :  1; /**< addressed flash page is write protected,<br> or address out of range */
    uint8          :  6;
    uint8 ExecFail :  1; /**< Assembly Buffer already opened,<br> or nested NVM operation */
  } bit;
} TUser_OpenAB;

/*******************************************************************************
** Function USER_MAPRAM_INIT: return value decoding                           **
*******************************************************************************/
/** \union TUser_MAPRAM_Init
 *  \brief This union defines the return value of \link USER_MAPRAM_INIT \endlink
 */
typedef union
{
  uint8   reg;
  struct
  {
    uint8 GlobFail      :  1; /**< OR-combination of all fail */
    uint8               :  4;
    uint8 DoubleMapping :  1; /**< double mapping detected, at least two physical pages are mapped to the same logical page */
    uint8 FaultyPage    :  1; /**< at least one page doesn't have any margin to the user read threshold */
    uint8 ExecFail      :  1; /**< Assembly Buffer is still open, or nested NVM operation */
  } bit;
} TUser_MAPRAM_Init;

/*******************************************************************************
** Function USER_NVM_ECC_CHECK: return value decoding                         **
*******************************************************************************/
/** \union TUser_NVM_ECC_Check
 *  \brief This union defines the return value of \link USER_NVM_ECC_CHECK \endlink
 */
typedef union
{
  uint8   reg;
  struct
  {
    uint8 SBE           :  1; /**< Single Bit Error fail */
    uint8 DBE           :  1; /**< Double Bit Error fail */
    uint8               :  5;
    uint8 ExecFail      :  1; /**< Nested NVM operation */
  } bit;
} TUser_NVM_ECC_Check;

/*******************************************************************************
** Function USER_ECC_CHECK: return value decoding                             **
*******************************************************************************/
/** \union TUser_ECC_Check
 *  \brief This union defines the return value of \link USER_ECC_CHECK \endlink
 */
typedef union
{
  uint8   reg;
  struct
  {
    uint8 SBE           :  1; /**< Single Bit Error fail */
    uint8 DBE           :  1; /**< Double Bit Error fail */
    uint8               :  5;
    uint8 ExecFail      :  1; /**< Nested NVM operation */
  } bit;
} TUser_ECC_Check;

/*******************************************************************************
** Function USER_ERASE_SECTOR_VERIFY: return value decoding                   **
*******************************************************************************/
/** \union TUser_ERASE_SECTOR_VERIFY
 *  \brief BF-Step only: This union defines the return value of \link USER_ERASE_SECTOR_VERIFY \endlink
 */
typedef union
{
  uint8   reg;
  struct
  {
    uint8 GlobFail      :  1; /**< OR-combination of all fail */
    uint8 VerifyFail    :  1; /**< at least one of the 32 pages within the sector is not erased properly */
    uint8               :  4;
    uint8 MapRAMFail    :  1; /**< in case of Data Flash sector only: MAPRAM initialization failed */
    uint8 ExecFail      :  1; /**< Assembly Buffer is still open,<br> or nested NVM operation,<br> or invalid sector address,<br> or sector write proteced*/
  } bit;
} TUser_ERASE_SECTOR_VERIFY;

/*******************************************************************************
** Function USER_ERASEPG_VERIFY: return value decoding                        **
*******************************************************************************/
/** \union TUser_ERASEPG_VERIFY
 *  \brief BF-Step only: This union defines the return value of \link USER_ERASEPG_VERIFY \endlink
 */
typedef union
{
  uint8   reg;
  struct
  {
    uint8 GlobFail      :  1; /**< OR-combination of all fail */
    uint8 VerifyFail    :  1; /**< page not in proper erased state */
    uint8               :  4;
    uint8 MapRAMFail    :  1; /**< MAPRAM initialization failure, invalid SparePage */
    uint8 ExecFail      :  1; /**< Assembly Buffer is still open,<br> or nested NVM operation,<br> or invalid page address,<br> or sector write proteced*/
  } bit;
} TUser_ERASEPG_VERIFY;

/*******************************************************************************
** Function USER_VERIFY_PAGE: return value decoding                           **
*******************************************************************************/
/** \union TUser_VERIFY_PAGE
 *  \brief BF-Step only: This union defines the return value of \link USER_VERIFY_PAGE \endlink
 */
typedef union
{
  uint8   reg;
  struct
  {
    uint8 GlobFail       :  1; /**< OR-combination of all fail */
    uint8 VerifyEraseFail:  1; /**< page verify failed on erased bits */
    uint8 VerifyProgFail :  1; /**< page verify failed on programmed bits */
    uint8                :  4;
    uint8 ExecFail       :  1; /**< Assembly Buffer is still open,<br> or nested NVM operation,<br> or invalid page address,<br> or sector write proteced*/
  } bit;
} TUser_VERIFY_PAGE;

/********************************************************************************
**                         Global Function Definitions                         **
********************************************************************************/

/* In case of unit testing, these functions are stubbed.
 * Unit test is performed with Tessy; tessy doesn't interpret the function definitions
 * which include the pointers to bootROM as functions,
 * so the function definitions are added here for unit testing only */
#ifdef UNIT_TESTING_LV2
  extern bool  USER_CFLASH_WR_PROT_EN   (uint16 cflash_pw);
  extern bool  USER_CFLASH_WR_PROT_DIS  (uint16 cflash_pw);
  extern bool  USER_CFLASH_RD_PROT_EN   (uint16 cflash_pw);
  extern bool  USER_CFLASH_RD_PROT_DIS  (uint16 cflash_pw);
  extern bool  USER_DFLASH_WR_PROT_EN   (uint16 dflash_pw);
  extern bool  USER_DFLASH_WR_PROT_DIS  (uint16 dflash_pw);
  extern bool  USER_DFLASH_RD_PROT_EN   (uint16 dflash_pw);
  extern bool  USER_DFLASH_RD_PROT_DIS  (uint16 dflash_pw);
  extern uint8 USER_OPENAB              (const uint32 NVMPAGEAddr);
  extern uint8 USER_PROG                (const uint8 PROG_FLAG);
  extern uint8 USER_ERASEPG             (const uint32 *NVMPageAddr, const uint8 XRAM_RTNE_BRNCHNG);
  extern bool  USER_ABORTPROG           (void);
  extern bool  USER_NVMRDY              (void);
  extern uint8 USER_READ_CAL            (const uint8 NumOfBytes, const uint8 CSAddr, const uint16 RAMAddr);
  extern bool  USER_NVM_CONFIG          (const uint8 *NVMSize, const uint8 *MapRAMSize);
  extern uint8 USER_NVM_ECC2ADDR        (const uint16 *ecc2addr);
  extern uint8 USER_MAPRAM_INIT         (void);
  extern bool  USER_READ_100TP          (const uint8 OTP_Page_Sel, const uint8 DataOffset, const uint32 *HundredTPData);
  extern uint8 USER_100TP_PROG          (const uint8 OTP_Page_Sel);
  extern uint8 USER_ERASE_SECTOR        (const uint32 NVMSectorAddr);
  extern uint8 USER_RAM_MBIST_START     (const uint16 RAM_MBIST_Stop_Addr, const uint16 RAM_MBIST_Start_addr);
  extern uint8 USER_NVM_ECC_CHECK       (void);
  extern uint8 USER_ECC_CHECK           (const uint32 *ecc2addr);
  extern uint8 USER_ERASE_SECTOR_VERIFY (const uint32 sector_addr);
  extern uint8 USER_ERASEPG_VERIFY      (const uint32 page_addr);
  extern uint8 USER_VERIFY_PAGE         (const uint32 page_addr);
#else

  /** \brief Sets the temporary code flash write protection. The password is compared against the
  * \brief password stored in the 100TP page 1 offset 0x0C. The default password is 0x0000.
  * \note The write protection is recommended to prevent the code flash from being erased/written unintentionally.
  *
  * \param cflash_pw password to validate function execution
  * \retval 0 = pass,
  * \retval 1 = fail, password doesn't match
  *
  * \brief <b>Example</b><br>
  * \brief This example sets the temporary code flash write protection by using the default password.
  * ~~~~~~~~~~~~~~~{.c}
  * void Example_Function(void)
  * {
  *     WDT1_SOW_Service(1u);
  *
  *     if ( USER_CFLASH_WR_PROT_EN(0) == 0)
  *     {
  *         //write protection set
  *     }
  *     else
  *     {
  *         //...careful, protection not set, password did not match
  *     }
  *
  *     (void)WDT1_Service();
  * }
  * ~~~~~~~~~~~~~~~
  * \ingroup bootrom_api
  */
  extern bool  (*const USER_CFLASH_WR_PROT_EN)   (uint16 cflash_pw);

  /** \brief Removes the temporary code flash write protection. The password is compared against the
  * \brief password stored in the 100TP page 1 offset 0x0C. The default password is 0x0000.
  * \note The write protection is recommended to prevent the code flash from being erased/written unintentionally.
  *
  * \param cflash_pw password to validate function execution
  * \retval 0 = pass,
  * \retval 1 = fail, password doesn't match
  *
  * \brief <b>Example</b><br>
  * \brief This example removes the temporary code flash write protection by using the default password.
  * ~~~~~~~~~~~~~~~{.c}
  * void Example_Function(void)
  * {
  *     WDT1_SOW_Service(1u);
  *
  *     if ( USER_CFLASH_WR_PROT_DIS(0) == 0)
  *     {
  *         //code flash no longer write protected
  *     }
  *     else
  *     {
  *         //code flash still write protected, password did not match
  *     }
  *
  *     (void)WDT1_Service();
  * }
  * ~~~~~~~~~~~~~~~
  * \ingroup bootrom_api
  */
  extern bool  (*const USER_CFLASH_WR_PROT_DIS)  (uint16 cflash_pw);

  /** \brief Sets the temporary code flash read protection. The password is compared against the
  * \brief password stored in the 100TP page 1 offset 0x0C. The default password is 0x0000.
  * \note The Read Protection acts as a IP protection, but in order to enable full IP protection use the protection set via BSL mode (permanent) instead.
  *
  * \param cflash_pw password to validate function execution
  * \retval 0 = pass,
  * \retval 1 = fail, password doesn't match
  *
  * \brief <b>Example</b><br>
  * \brief This example sets the temporary code flash read protection by using the default password.
  * ~~~~~~~~~~~~~~~{.c}
  * void Example_Function(void)
  * {
  *     WDT1_SOW_Service(1u);
  *
  *     if ( USER_CFLASH_RD_PROT_EN(0) == 0)
  *     {
  *         //read protection set
  *     }
  *     else
  *     {
  *         //...careful, protection not set, password did not match
  *     }
  *
  *     (void)WDT1_Service();
  * }
  * ~~~~~~~~~~~~~~~
  * \ingroup bootrom_api
  */
  extern bool  (*const USER_CFLASH_RD_PROT_EN)   (uint16 cflash_pw);

  /** \brief Removes the temporary code flash read protection. The password is compared against the
  * \brief password stored in the 100TP page 1 offset 0x0C. The default password is 0x0000.
  * \note The Read Protection acts as a IP protection, but in order to enable full IP protection use the protection set via BSL mode (permanent) instead.
  *
  * \param cflash_pw password to validate function execution
  * \retval 0 = pass,
  * \retval 1 = fail, password doesn't match
  *
  * \brief <b>Example</b><br>
  * \brief This example removes the temporary code flash read protection by using the default password.
  * ~~~~~~~~~~~~~~~{.c}
  * void Example_Function(void)
  * {
  *     WDT1_SOW_Service(1u);
  *
  *     if ( USER_CFLASH_RD_PROT_DIS(0) == 0)
  *     {
  *         //code flash no longer read protected
  *     }
  *     else
  *     {
  *         //code flash still read protected, password did not match
  *     }
  *
  *     (void)WDT1_Service();
  * }
  * ~~~~~~~~~~~~~~~
  * \ingroup bootrom_api
  */
  extern bool  (*const USER_CFLASH_RD_PROT_DIS)  (uint16 cflash_pw);

  /** \brief Sets the temporary data flash write protection. The password is compared against the
  * \brief password stored in the 100TP page 1 offset 0x0E. The default password is 0x0000.
  *
  * \param dflash_pw password to validate function execution
  * \retval 0 = pass,
  * \retval 1 = fail, password doesn't match
  *
  * \brief <b>Example</b><br>
  * \brief This example sets the temporary data flash write protection by using the default password.
  * ~~~~~~~~~~~~~~~{.c}
  * void Example_Function(void)
  * {
  *     WDT1_SOW_Service(1u);
  *
  *     if ( USER_DFLASH_WR_PROT_EN(0) == 0)
  *     {
  *         //write protection set
  *     }
  *     else
  *     {
  *         //...careful, protection not set, password did not match
  *     }
  *
  *     (void)WDT1_Service();
  * }
  * ~~~~~~~~~~~~~~~
  * \ingroup bootrom_api
  */
  extern bool  (*const USER_DFLASH_WR_PROT_EN)   (uint16 dflash_pw);

  /** \brief Removes the temporary data flash write protection. The password is compared against the
  * \brief password stored in the 100TP page 1 offset 0x0E. The default password is 0x0000.
  *
  * \param dflash_pw password to validate function execution
  * \retval 0 = pass,
  * \retval 1 = fail, password doesn't match
  *
  * \brief <b>Example</b><br>
  * \brief This example removes the temporary data flash write protection by using the default password.
  * ~~~~~~~~~~~~~~~{.c}
  * void Example_Function(void)
  * {
  *     WDT1_SOW_Service(1u);
  *
  *     if ( USER_DFLASH_WR_PROT_DIS(0) == 0)
  *     {
  *         //data flash no longer write protected
  *     }
  *     else
  *     {
  *         //data flash still write protected, password did not match
  *     }
  *
  *     (void)WDT1_Service();
  * }
  * ~~~~~~~~~~~~~~~
  * \ingroup bootrom_api
  */
  extern bool  (*const USER_DFLASH_WR_PROT_DIS)  (uint16 dflash_pw);

  /** \brief Sets the temporary data flash read protection. The password is compared against the
  * \brief password stored in the 100TP page 1 offset 0x0E. The default password is 0x0000.
  *
  * \param dflash_pw password to validate function execution
  * \retval 0 = pass,
  * \retval 1 = fail, password doesn't match
  *
  * \brief <b>Example</b><br>
  * \brief This example sets the temporary data flash read protection by using the default password.
  * ~~~~~~~~~~~~~~~{.c}
  * void Example_Function(void)
  * {
  *     WDT1_SOW_Service(1u);
  *
  *     if ( USER_DFLASH_RD_PROT_EN(0) == 0)
  *     {
  *         //write protection set
  *     }
  *     else
  *     {
  *         //...careful, protection not set, password did not match
  *     }
  *
  *     (void)WDT1_Service();
  * }
  * ~~~~~~~~~~~~~~~
  * \ingroup bootrom_api
  */
  extern bool  (*const USER_DFLASH_RD_PROT_EN)   (uint16 dflash_pw);

  /** \brief Removes the temporary data flash read protection. The password is compared against the
  * \brief password stored in the 100TP page 1 offset 0x0E. The default password is 0x0000.
  *
  * \param dflash_pw password to validate function execution
  * \retval 0 = pass,
  * \retval 1 = fail, password doesn't match
  *
  * \brief <b>Example</b><br>
  * \brief This example removes the temporary data flash read protection by using the default password.
  * ~~~~~~~~~~~~~~~{.c}
  * void Example_Function(void)
  * {
  *     WDT1_SOW_Service(1u);
  *
  *     if ( USER_DFLASH_RD_PROT_DIS(0) == 0)
  *     {
  *         //data flash no longer read protected
  *     }
  *     else
  *     {
  *         //data flash still read protected, password did not match
  *     }
  *
  *     (void)WDT1_Service();
  * }
  * ~~~~~~~~~~~~~~~
  * \ingroup bootrom_api
  */
  extern bool  (*const USER_DFLASH_RD_PROT_DIS)  (uint16 dflash_pw);

  /** \brief Opens the assembly buffer for writing to a flash page, for code flash as well as data flash.
  * \brief This function has to be called as a preparation for a flash programming by \link USER_PROG \endlink.
  *
  * \param NVMPAGEAddr logical address to the flash page, the address has to be page aligned (128byte aligned)
  * \return uint8, see \link TUser_OpenAB \endlink
  *
  * \brief <b>Example</b><br>
  * \brief This example performs a page programming to the first data flash page.
  * ~~~~~~~~~~~~~~~{.c}
  * void Example_Function(void)
  * {
  *     TUser_OpenAB openab_res;
  *
  *     WDT1_SOW_Service(1u);
  *
  *     openab_res.reg = USER_OPENAB(DataFlashStart);
  *
  *     (void)WDT1_Service();
  *
  *     if ( openab_res.bit.ExecFail == 1 )
  *     {
  *         //Assembly buffer is already open, or
  *         //nested NVM operation
  *     }
  *     if ( openab_res.bit.ABFail == 1 )
  *     {
  *         //data flash write protected, or
  *         //wrong NVMPAGEAddr address, not within flash range
  *     }
  * }
  * ~~~~~~~~~~~~~~~
  * \ingroup bootrom_api
  */
  extern uint8 (*const USER_OPENAB)              (const uint32 NVMPAGEAddr);

  /** \brief Writes the assembly buffer content to the flash page addressed by \link USER_OPENAB \endlink.
  * \pre The successful execution of \link USER_OPENAB \endlink is required.
  *
  * \param PROG_FLAG options to control the RAM branch and corrective action of the USER_PROG function
  * \return uint8, see \link TUser_Prog \endlink
  *
  * \brief <b>Example</b><br>
  * \brief This example performs a page programming to the first data flash page.
  * ~~~~~~~~~~~~~~~{.c}
  * void Example_Function(void)
  * {
  *     TUser_OpenAB openab_res;
  *     TUser_Prog   prog_res;
  *     TProgFlag    flags;
  *     uint8 i;
  *     uint8 *pAddr;
  *
  *     WDT1_SOW_Service(1u);
  *
  *     openab_res.reg = USER_OPENAB(DataFlashStart);
  *
  *     (void)WDT1_Service();
  *
  *     if ( openab_res.bit.ExecFail == 1 )
  *     {
  *         //Assembly buffer is already open, or
  *         //nested NVM operation
  *     }
  *     else if ( openab_res.bit.ABFail == 1 )
  *     {
  *         //data flash write protected, or
  *         //wrong NVMPAGEAddr address, not within flash range
  *     }
  *     else
  *     {
  *         //assembly buffer successfully opened
  *         pAddr = (uint8*)DataFlashStart;
  *
  *         //fill assembly buffer with new data
  *         for ( i = 0; i < FlashPageSize; i++)
  *         {
  *             pAddr[i] = i;
  *         }
  *
  *         flags.bit.RAM_Branch = 0;
  *         flags.bit.CorrAct = 1;
  *
  *         WDT1_SOW_Service(1u);
  *
  *         prog_res.reg = USER_PROG(flags.reg);
  *
  *         (void)WDT1_Service();
  *
  *         if (prog_res.bit.GlobFail == 1)
  *         {
  *             //handle fails
  *         }
  *     }
  * }
  * ~~~~~~~~~~~~~~~
  * \ingroup bootrom_api
  */
  extern uint8 (*const USER_PROG)                (const uint8 PROG_FLAG);

  /** \brief Erases a flash page, for code flash as well as data flash.
  *
  * \param NVMPageAddr logical address to the flash page, the address has to be page aligned (128byte aligned)
  * \param XRAM_RTNE_BRNCHNG  0 = no RAM branch,<br>
  *                           1 = RAM branch
  * \return uint8
  *
  * \brief <b>Example</b><br>
  * \brief This example performs a page erase of the first data flash page.
  * ~~~~~~~~~~~~~~~{.c}
  * void Example_Function(void)
  * {
  *     uint8 res;
  *
  *     WDT1_SOW_Service(1u);
  *
  *     res = USER_ERASEPG((uint32*)DataFlashStart, 0);
  *
  *     (void)WDT1_Service();
  *
  *     if ( ( res & 1 ) == 1 )
  *     {
  *         //erase failed
  *     }
  * }
  * ~~~~~~~~~~~~~~~
  * \ingroup bootrom_api
  */
  extern uint8 (*const USER_ERASEPG)             (const uint32 *NVMPageAddr, const uint8 XRAM_RTNE_BRNCHNG);

  /** \brief Closes the Assembly Buffer.
  *
  * \retval true = Assembly Buffer closed
  * \retval false = Assembly buffer could not be close, programming already started
  *
  * \brief <b>Example</b><br>
  * \brief This example closes the Assembly Buffer intentionally.
  * ~~~~~~~~~~~~~~~{.c}
  * void Example_Function(void)
  * {
  *     TUser_OpenAB openab_res;
  *
  *     WDT1_SOW_Service(1u);
  *
  *     openab_res.reg = USER_OPENAB(DataFlashStart);
  *
  *     (void)WDT1_Service();
  *
  *     if ( openab_res.bit.ExecFail == 1 )
  *     {
  *         //Assembly buffer is already open, or
  *         //nested NVM operation
  *     }
  *     if ( openab_res.bit.ABFail == 1 )
  *     {
  *         //data flash write protected, or
  *         //wrong NVMPAGEAddr address, not within flash range
  *     }
  *
  *     if ( USER_ABORTPROG() == true)
  *     {
  *         //assembly buffer closed, programming preparation aborted
  *     }
  * }
  * ~~~~~~~~~~~~~~~
  * \ingroup bootrom_api
  */
  extern bool  (*const USER_ABORTPROG)           (void);

  /** \brief Returns the status of the NVM module.
  * \brief This can be used in case of RAM Branch to check whether the NVM module
  * \brief has finished its operation and a jump back to the BootROM should be done,
  * \brief in order to finish the started NVM operation.
  *
  * \retval true = NVM module is ready (not busy)
  * \retval false = NVM module is not yet ready (busy)
  *
  * \brief <b>Example</b><br>
  * \brief This example performs a user action as long as the NVM module is busy.
  * ~~~~~~~~~~~~~~~{.c}
  * void Example_Function(void)
  * {
  *     do
  *     {
  *          ...user code...
  *     }
  *     while ( USER_NVMRDY() == false );
  * }
  * ~~~~~~~~~~~~~~~
  * \note This example makes only sense if it is executed from RAM.
  * \ingroup bootrom_api
  */
  extern bool  (*const USER_NVMRDY)              (void);

  /** \brief Reads the NVM calibration data
  *
  * \param NumOfBytes Number of Bytes to be copied from config sector into the RAM (allowed values are form 01H to 80H).
  * \param CSAddr 100TP page to take data from, 0x11 is page 1, 0x12 is page 2, ..., 0x18 is page 8
  * \param RAMAddr RAM address offset to copy data to (03FFH < RAMAddr < RAMAddr + NumOfBytes < RAM size).
  *
  * \return uint8
  * \return <pre>
  * Bit 0: Pass or Fail
  *        0 = Read is successful
  *        1 = Read is not successful due to invalid input values
  * Bit 7: Execution Pass/Fail status
  *        0 = Pass: Routine was correctly executed
  *        1 = Fail: Routine was not executed</pre>
  *
  * \brief <b>Example</b><br>
  * \brief This example reads 16 bytes from 100TP page 1 at offset 0 and stores them in an array.
  * ~~~~~~~~~~~~~~~{.c}
  * void Example_Function(void)
  * {
  *     uint8 cal_data[0x20] = {0};
  *     uint32 ramaddress = (uint32)cal_data;
  *     uint16 ramoffset = ramaddress - 0x18000000;
  *     USER_READ_CAL(0x10, 0x11, ramoffset);
  * }
  * ~~~~~~~~~~~~~~~
  * \ingroup bootrom_api
  */
  extern uint8 (*const USER_READ_CAL)            (const uint8 NumOfBytes, const uint8 CSAddr, const uint16 RAMAddr);

  /** \brief Reads the total size of code flash and total size of data flash for this device.
  *
  * \param *NVMSize a pointer to a variable where the code flash size will be stored
  * \param *MapRAMSize a pointer to a variable where the data flash size will be stored
  *
  * \retval true = successful
  * \retval false = failed
  *
  * \brief <b>Example</b><br>
  * \brief This example performs read of the NVM configuration.
  * ~~~~~~~~~~~~~~~{.c}
  * void Example_Function(void)
  * {
  *     uint8 code_flash_size;
  *     uint8 data_flash_size;
  *
  *     WDT1_SOW_Service(1u);
  *
  *     if ( USER_NVM_CONFIG( &code_flash_size, &data_flash_size) == true )
  *     {
  *         //code_flash_size and data_flash_size are valid
  *     }
  *
  *     (void)WDT1_Service();
  * }
  * ~~~~~~~~~~~~~~~
  * \ingroup bootrom_api
  */
  extern bool  (*const USER_NVM_CONFIG)          (const uint8 *NVMSize, const uint8 *MapRAMSize);

  /** \brief This function returns the last NVM address causing a double bit ECC failure.
  *
  * \param *ecc2addr a pointer to a variable where the last double bit ECC failing address will be stored
  *
  * \return uint8
  * \return <pre>Bit 0: ECC Double Bit error detection status
  *        0 = no NVM double bit error found
  *        1 = NVM double bit error detected
  * Bit 7: Execution status
  *        0 = pass, routine executed successfully, Bit0 valid
  *        1 = fail, routine failed to execute</pre>
  *
  * \brief <b>Example</b><br>
  * \brief This example performs read of the NVM Double Bit ECC fail location.
  * ~~~~~~~~~~~~~~~{.c}
  * static uint32 ecc_addr;
  *
  * void NMI_Handler(void)
  * {
  *     if ( NMI_ECC_Sts() == 1 )
  *     {
  *         if ( USER_NVM_ECC2ADDR( &ecc_addr ) == 1 )
  *         {
  *             //ecc_addr valid
  *         }
  *     }
  * }
  * ~~~~~~~~~~~~~~~
  * \ingroup bootrom_api
  */
  extern uint8 (*const USER_NVM_ECC2ADDR)        (const uint16 *ecc2addr);

  /** \brief This function performs a MapRAM reinitialization.
  * \brief The MapRAM is the logic to physical address translation for the data flash.
  * \brief This function invalidates the MapRAM content and rebuilds from the data flash content.
  * \brief It furthermore checks the mapping integrity, in case the mapping is not unambiguous an error will be reported.
  * \brief in this case the data flash cannot be used until the error is solved.
  * \brief This function also randomizes the Spare Page newly.
  *
  * \return uint8
  * \return <pre>
  * Bit 0: function status, OR'd all flags
  *        0 = pass, MapRAM initialized, no fails, data flash ready
  *        1 = fail, see bits[5:7] for further details
  * Bit 5: Double Mapping status
  *        0 = pass, no double-mapping found
  *        1 = fail, initialization failed due to double-mapping
  * Bit 6: faulty Page status
  *        0 = pass, no faulty page found
  *        1 = fail, initialization failed due to faulty page
  * Bit 7: Execution status
  *        0 = pass, routine executed successfully
  *        1 = fail, routine failed to execute</pre>
  *
  * \brief <b>Example</b><br>
  * \brief This example performs a MapRAM initialization.
  * ~~~~~~~~~~~~~~~{.c}
  * void main(void)
  * {
  *     TUser_MAPRAM_Init res;
  *
  *     WDT1_SOW_Service(1u);
  *
  *     res.reg = USER_MAPRAM_INIT();
  *
  *     (void)WDT1_Service();
  *
  *     if ( res.bit.GlobFail == 1 )
  *     {
  *         //at least one fail occurred during MapRAM init
  *         if ( ( res.bit.DoubleMapping == 1 ) ||
  *              ( res.bit.FaultyPage    == 1 ) )
  *         {
  *             //restart the device to let ServiceAlgorithm try to fix the issue
  *         }
  *         if ( res.bit.ExecFail == 1 )
  *         {
  *             //ensure that this function is only called if no other NVM operation
  *             //is ongoing. Close the assembly buffer, in case it is open and restart
  *             //the MAPRAM initialization again.
  *         }
  *     }
  * }
  * ~~~~~~~~~~~~~~~
  * \ingroup bootrom_api
  */
  extern uint8 (*const USER_MAPRAM_INIT)         (void);

  /** \brief This function reads four bytes from a selected 100TP page.
  *
  * \param OTP_Page_Sel selects one out of eight 100TP pages, 0x11 is page 1, 0x12 is page 2, ..., 0x18 is page 8
  * \param DataOffset the offset within the selected page, starting from value 0x00 to 0x7F
  * \param *HundredTPData a pointer to a variable where the four bytes from the 100TP will be stored
  *
  * \retval true = pass
  * \retval false = fail
  *
  * \brief <b>Example</b><br>
  * \brief This example performs a complete read of the first 100TP page.
  * ~~~~~~~~~~~~~~~{.c}
  * void Example_Function(void)
  * {
  *     uint32 ui32;
  *     uint8 page_data[128];
  *     uint8 i;
  *
  *     for ( i = 0; i < FlashPageSize; i++ )
  *     {
  *         if ( USER_READ_100TP( 0x11, i, &ui32 ) == true )
  *         {
  *             page_data[i] = ui32 & 0xFF;
  *         }
  *     }
  * }
  * ~~~~~~~~~~~~~~~
  * \ingroup bootrom_api
  */
  extern bool  (*const USER_READ_100TP)          (const uint8 OTP_Page_Sel, const uint8 DataOffset, const uint32 *HundredTPData);

  /** \brief This function writes data to a selected 100TP page.
  * \brief In order to write data to a 100TP page, the data has to be set up in a structure residing in RAM.
  * \brief The structure has the following outline:<br>
  * <table>
  * <caption id="multi_row">RAM preloading for 100 Time Programmable page programming</caption>
  * <tr><th>RAM Address                     <th>Function
  * <tr><td>0x18000400<td>Number of Bytes to be programmed,<br>max. 127
  * <tr><td>0x18000401<td>page offset 1
  * <tr><td>0x18000402<td>page data 1
  * <tr><td>0x18000403<td>page offset 2
  * <tr><td>0x18000404<td>page data 2
  * <tr><td>...<td>...
  * <tr><td>0x18000401 + ((N-1) x 2)<td>page offset N
  * <tr><td>0x18000402 + ((N-1) x 2)<td>page data N
  * </table>
  *
  * \param OTP_Page_Sel selects one out of eight 100TP pages, 0x11 is page 1, 0x12 is page 2, ..., 0x18 is page 8
  *
  * \retval true = pass
  * \retval false = fail
  *
  * \brief <b>Example</b><br>
  * \brief This example writes house numbers to the 2nd 100TP page.
  * ~~~~~~~~~~~~~~~{.c}
  * void Example_Function(void)
  * {
  *   TUser_100TP_Prog res;
  *   //program 100TP page 2
  *   uint8 page = 0x12;
  *   uint8 i;
  *   nvm100tp.count = 127;
  *
  *   for ( i = 0; i < nvm100tp.count; i++ )
  *   {
  *     nvm100tp.data[i].offset = i;
  *     nvm100tp.data[i].date = i;
  *   }
  *
  *   WDT1_SOW_Service(1u);
  *
  *   res.reg = USER_100TP_PROG(page);
  *
  *   (void)WDT1_Service();
  *
  *   if (res.bit.GlobFail == 1)
  *   {
  *     ...any fail has happened
  *   }
  * }
  * ~~~~~~~~~~~~~~~
  * \ingroup bootrom_api
  */
  extern uint8 (*const USER_100TP_PROG)          (const uint8 OTP_Page_Sel);

  /** \brief This function performs a sector erase.
  *
  * \param NVMSectorAddr address of the sector which will be erased
  *
  * \return uint8
  * \return <pre>
  * Bit 0: function status, OR'd all flags
  *        0 = pass, sector erase successful
  *        1 = fail, sector erase failed
  * Bit 7: Execution status
  *        0 = pass, routine executed successfully
  *        1 = fail, routine failed to execute, due to sector protected, or nested call</pre>
  *
  * \brief <b>Example</b><br>
  * \brief This example erases the data flash sector.
  * ~~~~~~~~~~~~~~~{.c}
  * void Example_Function(void)
  * {
  *    uint8 res;
  *
  *    WDT1_SOW_Service(1u);
  *
  *    res = USER_ERASE_SECTOR(DataFlashStart);
  *
  *    (void)WDT1_Service();
  *
  *    if ( res != 0 )
  *    {
  *        ...any fail has happened
  *    }
  * }
  * ~~~~~~~~~~~~~~~
  * \ingroup bootrom_api
  */
  extern uint8 (*const USER_ERASE_SECTOR)        (const uint32 NVMSectorAddr);

  /** \brief This function performs a MBIST on the RAM for a given address range.
  * \brief The RAM interface will be disabled for the duration of the MBIST,
  * \brief accessing the RAM will not be possible for this time.
  * \warning The RAM content for the selected range will be lost after the MBIST,
  * \warning the RAM range will be initialized to '0'.
  *
  * \param RAM_MBIST_Stop_Addr end address for the MBIST, given as offset to RAMStart (0x18000000)
  * \param RAM_MBIST_Start_addr starting address for the MBIST, given as offset to RAMStart (0x18000000)
  *
  * \return uint8
  * \return <pre>
  * Bit 0: function status, OR'd all flags
  *        0 = pass, MBIST ran pass
  *        1 = fail, MBIST failed
  * Bit 1: Address range failed
  *        0 = pass, address range good
  *        1 = fail, address out of range
  * Bit 7: Execution status
  *        0 = pass, routine executed successfully
  *        1 = fail, routine failed to execute, due to nested call</pre>
  *
  * \brief <b>Example</b><br>
  * \brief This example performs a MBIST over the first half of the RAM.
  * ~~~~~~~~~~~~~~~{.c}
  * void Example_Function(void)
  * {
  *    uint8 res;
  *
  *    WDT1_SOW_Service(1u);
  *
  *    res = USER_RAM_MBIST_START((uint16)(RAMSize >> 1u), 0);
  *
  *    (void)WDT1_Service();
  *
  *    if ( res != 0 )
  *    {
  *        ...any fail has happened
  *    }
  * }
  * ~~~~~~~~~~~~~~~
  * \ingroup bootrom_api
  */
  extern uint8 (*const USER_RAM_MBIST_START)     (const uint16 RAM_MBIST_Stop_Addr, const uint16 RAM_MBIST_Start_addr);

  /** \brief This function performs a ECC check on the entire NVM by reading the same.
  * \brief This function does not alter any NVM content.
  *
  * \return uint8
  * \return <pre>
  * Bit 0: single bit errors (SBE)
  *        0 = pass, no SBEs detected
  *        1 = fail, at least one SBE detected
  * Bit 1: Double bit errors (DBE)
  *        0 = pass, no DBEs detected
  *        1 = fail, at least one DBE detected
  * Bit 7: Execution status
  *        0 = pass, routine executed successfully
  *        1 = fail, routine failed to execute, due to nested call</pre>
  *
  * \brief <b>Example</b><br>
  * \brief This example performs a ECC check on the entire flash.
  * ~~~~~~~~~~~~~~~{.c}
  * void Example_Function(void)
  * {
  *    TUser_NVM_ECC_Check res_check;
  *    TUser_ECC_Check res_addr;
  *    uint32 fail_addr;
  *
  *    WDT1_SOW_Service(1u);
  *
  *    res_check.reg = USER_NVM_ECC_CHECK();
  *
  *    (void)WDT1_Service();
  *
  *    if ( res_check.bit.SBE == 1 )
  *    {
  *        //single bit error, will be corrected during runtime
  *    }
  *    else if ( res_check.bit.DBE == 1 )
  *    {
  *        res_addr.reg = USER_ECC_CHECK( &fail_addr );
  *
  *        if ( res_addr.bit.SBE == 1)
  *        {
  *            //fail_addr points to a Single Bit Error
  *        }
  *        else if ( res_addr.bit.DBE == 1)
  *        {
  *            //fail_addr points to a Double Bit Error
  *        }
  *        else if ( res_addr.bit.ExecFail == 1)
  *        {
  *            //fail_addr not valid, function could not be executed
  *        }
  *        else
  *        {
  *            //everything pass?? We should not get here
  *        }
  *    }
  *    else if ( res_check.bit.ExecFail == 1)
  *    {
  *        //ECC check could not be performed
  *    }
  *    else
  *    {
  *        //everything pass
  *    }
  * }
  * ~~~~~~~~~~~~~~~
  * \ingroup bootrom_api
  */
  extern uint8 (*const USER_NVM_ECC_CHECK)       (void);

  /** \brief This function returns the address of the last ECC fail.
  *
  * \return uint8
  * \return <pre>
  * Bit 0: single bit errors (SBE)
  *        0 = pass, no SBEs detected
  *        1 = fail, at least one SBE detected
  * Bit 1: Double bit errors (DBE)
  *        0 = pass, no DBEs detected
  *        1 = fail, at least one DBE detected
  * Bit 7: Execution status
  *        0 = pass, routine executed successfully
  *        1 = fail, routine failed to execute, due to nested call</pre>
  *
  * \brief <b>Example</b><br>
  * \brief This example performs a ECC check on the entire flash.
  * ~~~~~~~~~~~~~~~{.c}
  * void Example_Function(void)
  * {
  *    TUser_NVM_ECC_Check res_check;
  *    TUser_ECC_Check res_addr;
  *    uint32 fail_addr;
  *
  *    WDT1_SOW_Service(1u);
  *
  *    res_check.reg = USER_NVM_ECC_CHECK();
  *
  *    (void)WDT1_Service();
  *
  *    if ( res_check.bit.SBE == 1 )
  *    {
  *        //single bit error, will be corrected during runtime
  *    }
  *    if ( res_check.bit.DBE == 1 )
  *    {
  *        res_addr.reg = USER_ECC_CHECK( &fail_addr );
  *
  *        if ( res_addr.bit.SBE == 1)
  *        {
  *            //fail_addr points to a Single Bit Error
  *        }
  *        if ( res_addr.bit.DBE == 1)
  *        {
  *            //fail_addr points to a Double Bit Error
  *        }
  *        if ( res_addr.bit.ExecFail == 1)
  *        {
  *            //fail_addr not valid, function could not be executed
  *        }
  *    }
  *    if ( res_check.bit.ExecFail == 1)
  *    {
  *        //ECC check could not be performed
  *    }
  * }
  * ~~~~~~~~~~~~~~~
  * \ingroup bootrom_api
  */
  extern uint8 (*const USER_ECC_CHECK)           (const uint32 *ecc2addr);

  /* BF-Step BootROM API extension */
  #ifdef RTE_DEVICE_BF_STEP
    /** \brief This function performs a verify on an erased sector.
    * \brief This function checks if all pages within the sector are in proper erased state.
    * \brief For the data flash sector it checks whether none of the pages are mapped and whether
    * \brief a valid Spare Page is available an in proper erased state.
    * \note  BF-Step only.
    *
    * \param sector_addr address of the sector which will be verified
    *
    * \return uint8 (see \link TUser_ERASE_SECTOR_VERIFY \endlink)
    * \return <pre>
    * Bit 0: GlobFail, function status, OR'd all flags
    *        0 = pass, sector erase verify successful
    *        1 = fail, sector erase verify failed
    * Bit 1: VerifyFail, Erase Verify Status
    *        0 = pass, all pages are in proper erased state
    *        1 = fail, at least one out of the 32 pages is not properly erased
    * Bit 6: MapRAMFail, MapRAM Status, Data Flash sector only
    *        0 = pass, MapRAM and Spare Page pass
    *        1 = fail, mapped pages, or invalid Spare Page, or MapRAM ECC fail
    * Bit 7: ExecFail, Execution status
    *        0 = pass, routine executed successfully
    *        1 = fail, routine failed to execute, due to invalid address, or assembly buffer open, or nested call</pre>
    *
    * \brief <b>Example</b><br>
    * \brief This example verifies the erased state of the data flash sector after bootup.
    * ~~~~~~~~~~~~~~~{.c}
    * void main(void)
    * {
    *    TUser_ERASE_SECTOR_VERIFY res;
    *
    *    WDT1_SOW_Service(1u);
    *
    *    res.reg = USER_ERASE_SECTOR_VERIFY(DataFlashStart);
    *
    *    (void)WDT1_Service();
    *
    *    if ( res.bit.GlobFail != 0 )
    *    {
    *        ...sector is most probably not erased
    *    }
    *    else
    *    {
    *        ...write new data to an erased sector
    *    }
    * }
    * ~~~~~~~~~~~~~~~
    * \ingroup bootrom_api
    */
    extern uint8 (*const USER_ERASE_SECTOR_VERIFY) (const uint32 sector_addr);

    /** \brief This function performs a verify on an erased page.
    * \brief This function checks if a given page is in proper erased state.
    * \brief For the data flash sector it checks whether the Spare Page is in proper erased state,
    * \brief regardless of the provided page address. Because in the Data Flash the Spare Page is
    * \brief the next physical page being used for writing.
    * \note  BF-Step only.
    *
    * \param page_addr address of the page which will be verified
    *
    * \return uint8 (see \link TUser_ERASEPG_VERIFY \endlink)
    * \return <pre>
    * Bit 0: GlobFail, function status, OR'd all flags
    *        0 = pass, sector erase verify successful
    *        1 = fail, sector erase verify failed
    * Bit 1: VerifyFail, Erase Verify Status
    *        0 = pass, all pages are in proper erased state
    *        1 = fail, at least one out of the 32 pages is not properly erased
    * Bit 6: MapRAMFail, MapRAM Status, Data Flash sector only
    *        0 = pass, MapRAM and Spare Page pass
    *        1 = fail, mapped pages, or invalid Spare Page, or MapRAM ECC fail
    * Bit 7: ExecFail, Execution status
    *        0 = pass, routine executed successfully
    *        1 = fail, routine failed to execute, due to invalid address, or assembly buffer open, or nested call</pre>
    *
    * \brief <b>Example</b><br>
    * \brief This example verifies the erased state of the Spare Page of the data flash sector after bootup.
    * ~~~~~~~~~~~~~~~{.c}
    * void main(void)
    * {
    *    TUser_ERASEPG_VERIFY res;
    *
    *    WDT1_SOW_Service(1u);
    *
    *    res.reg = USER_ERASEPG_VERIFY(DataFlashStart);
    *
    *    (void)WDT1_Service();
    *
    *    if ( res.bit.GlobFail != 0 )
    *    {
    *        ...Spare Page not properly erased, perform a device reset to run the ServiceAlgorithm
    *    }
    *    else
    *    {
    *        ...write new data to the data flash
    *    }
    * }
    * ~~~~~~~~~~~~~~~
    * \ingroup bootrom_api
    */
    extern uint8 (*const USER_ERASEPG_VERIFY)      (const uint32 page_addr);

    /** \brief This function performs a verify on a programmed page.
    * \brief This function checks if a given page whether the content has a proper data integrity.
    * \note  BF-Step only.
    *
    * \param page_addr address of the page which will be verified
    *
    * \return uint8 (see \link TUser_VERIFY_PAGE \endlink)
    * \return <pre>
    * Bit 0: GlobFail, function status, OR'd all flags
    *        0 = pass, sector erase verify successful
    *        1 = fail, sector erase verify failed
    * Bit 1: VerifyFail, Erase Verify Status
    *        0 = pass, all pages are in proper erased state
    *        1 = fail, at least one out of the 32 pages is not properly erased
    * Bit 6: MapRAMFail, MapRAM Status, Data Flash sector only
    *        0 = pass, MapRAM and Spare Page pass
    *        1 = fail, mapped pages, or invalid Spare Page, or MapRAM ECC fail
    * Bit 7: ExecFail, Execution status
    *        0 = pass, routine executed successfully
    *        1 = fail, routine failed to execute, due to invalid address, or assembly buffer open, or nested call</pre>
    *
    * \brief <b>Example</b><br>
    * \brief This example verifies the data integrity of the 1st page of the data flash sector after bootup.
    * ~~~~~~~~~~~~~~~{.c}
    * void main(void)
    * {
    *    TUser_VERIFY_PAGE res;
    *
    *    WDT1_SOW_Service(1u);
    *
    *    res.reg = USER_VERIFY_PAGE(DataFlashStart);
    *
    *    (void)WDT1_Service();
    *
    *    if ( res.bit.GlobFail != 0 )
    *    {
    *        ...page was potentially not properly written,
    *        data should be read (if possible), then erase page and
    *        program it again
    *        !!! Ensure that erase/programming will not be interrupted !!!
    *    }
    *    else
    *    {
    *        ... page data integrity given
    *    }
    * }
    * ~~~~~~~~~~~~~~~
    * \ingroup bootrom_api
    */
    extern uint8 (*const USER_VERIFY_PAGE)         (const uint32 page_addr);
  #endif /* RTE_DEVICE_BF_STEP */


  /** \brief Programms a page to NVM
  *  \note This function violates [MISRA Rule 45]
  *
  * \param addr logical address of the page to be programmed
  * \param *buf data buffer containing the data to be programmed, array of 128 bytes
  * \param Branch        0 = no RAM branch,<br>
  *                      1 = RAM branch
  * \param Correct       0 = no corrective actions (retry/disturb handling) on verify fail<br>
  *                      1 = corrective actions (retry/dirsturb handling) enabled
  * \param FailPageErase 0 = enabled, old data is kept,<br>
  *                      1 = disable, old data erased
  * \return 0 = pass,
  * \return 1 = fail
  *
  * \brief <b>Example</b><br>
  * \brief This example fills an array of 128 bytes with house numbers.
  * \brief The page_data array will then be programmed to the first page
  * \brief of the data flash.<br>The page programming is executed with <b>no RAM branch</b>,
  * \brief with <b>corrective actions (retry)</b> and <b>old data is kept</b> in case of fail.
  * ~~~~~~~~~~~~~~~{.c}
  * void Example_Function(void)
  * {
  *     uint8 page_data[128];
  *     uint8 i;
  *
  *     for ( i = 0; i < FlashPageSize; i++)
  *     {
  *         page_data[i] = i;
  *     }
  *
  *     WDT1_SOW_Service(1u);
  *
  *     if ( ProgramPage(DataFlashStart, &page_data, 0, 1, 0) == 1)
  *     {
  *        USER_ERASEPG((uint32*)DataFlashStart, 0);
  *     }
  *
  *     (void)WDT1_Service();
  * }
  * ~~~~~~~~~~~~~~~
  * \ingroup bootrom_api
  */
  uint8 ProgramPage(uint32 addr, const uint8 *buf, uint8 Branch, uint8 Correct, uint8 FailPageErase);

  /** \brief Reads the Customer ID out of the 100TP NVM
  *  \note This function violates [MISRA 2012 Rule 19.2, advisory], [MISRA 2012 Rule 11.3, required], [MISRA 2012 Rule 11.5, advisory]
  *
  * \param *CustID pointer to the struct where the Customer ID will be stored
  * \return 0 = pass
  * \return 1 = fail
  *
  * \brief <b>Example</b><br>
  * \brief This example reads the Customer ID out of the first 100TP page.
  * ~~~~~~~~~~~~~~~{.c}
  * void Example_Function(void)
  * {
  *     TCustomerID custid;
  *
  *     (void)GetCustomerID(&custid);
  * }
  * ~~~~~~~~~~~~~~~
  * \ingroup bootrom_api
  */
  bool GetCustomerID(const TCustomerID *CustID);

#endif
#endif
