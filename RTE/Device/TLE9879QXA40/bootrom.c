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

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/

#include "bootrom.h"
#include "wdt1.h"
#include "cmsis_misra.h"

/*******************************************************************************
**                         Global Function Definitions                        **
*******************************************************************************/

/*******************************************************************************
** BootROM User Function declaration                                          **
*******************************************************************************/

#ifndef UNIT_TESTING_LV2
  /* violation: Suppressing cast from unsigned int to pointer [MISRA Rule 45] */
  bool  (*const USER_CFLASH_WR_PROT_EN)   (const uint16 cflash_pw)                                                         = (bool  (*)(const uint16)) addr_USER_CFLASH_WR_PROT_EN;
  bool  (*const USER_CFLASH_WR_PROT_DIS)  (const uint16 cflash_pw)                                                         = (bool  (*)(const uint16)) addr_USER_CFLASH_WR_PROT_DIS;
  bool  (*const USER_CFLASH_RD_PROT_EN)   (const uint16 cflash_pw)                                                         = (bool  (*)(const uint16)) addr_USER_CFLASH_RD_PROT_EN;
  bool  (*const USER_CFLASH_RD_PROT_DIS)  (const uint16 cflash_pw)                                                         = (bool  (*)(const uint16)) addr_USER_CFLASH_RD_PROT_DIS;
  bool  (*const USER_DFLASH_WR_PROT_EN)   (const uint16 dflash_pw)                                                         = (bool  (*)(const uint16)) addr_USER_DFLASH_WR_PROT_EN;
  bool  (*const USER_DFLASH_WR_PROT_DIS)  (const uint16 dflash_pw)                                                         = (bool  (*)(const uint16)) addr_USER_DFLASH_WR_PROT_DIS;
  bool  (*const USER_DFLASH_RD_PROT_EN)   (const uint16 dflash_pw)                                                         = (bool  (*)(const uint16)) addr_USER_DFLASH_RD_PROT_EN;
  bool  (*const USER_DFLASH_RD_PROT_DIS)  (const uint16 dflash_pw)                                                         = (bool  (*)(const uint16)) addr_USER_DFLASH_RD_PROT_DIS;
  uint8 (*const USER_OPENAB)              (const uint32 NVMPAGEAddr)                                                       = (uint8 (*)(const uint32)) addr_USER_OPENAB;
  uint8 (*const USER_PROG)                (const uint8 PROG_FLAG)                                                          = (uint8 (*)(const uint8)) addr_USER_PROG;
  uint8 (*const USER_ERASEPG)             (const uint32 *NVMPageAddr, const uint8 XRAM_RTNE_BRNCHNG)                      = (uint8 (*)(const uint32 *, const uint8)) addr_USER_ERASEPG;
  bool  (*const USER_ABORTPROG)           (void)                                                                           = (bool  (*)(void)) addr_USER_ABORTPROG;
  bool  (*const USER_NVMRDY)              (void)                                                                           = (bool  (*)(void)) addr_USER_NVMRDY;
  uint8 (*const USER_READ_CAL)            (const uint8 NumOfBytes, const uint8 CSAddr, const uint16 RAMAddr)               = (uint8 (*)(const uint8, const uint8, const uint16)) addr_USER_READ_CAL;
  bool  (*const USER_NVM_CONFIG)          (const uint8 *NVMSize, const uint8 *MapRAMSize)                                = (bool  (*)(const uint8 *, const uint8 *)) addr_USER_NVM_CONFIG;
  uint8 (*const USER_NVM_ECC2ADDR)        (const uint16 *ecc2addr)                                                        = (uint8 (*)(const uint16 *)) addr_USER_NVM_ECC2ADDR;
  uint8 (*const USER_MAPRAM_INIT)         (void)                                                                           = (uint8 (*)(void)) addr_USER_MAPRAM_INIT;
  bool  (*const USER_READ_100TP)          (const uint8 OTP_Page_Sel, const uint8 DataOffset, const uint32 *HundredTPData) = (bool  (*)(const uint8, const uint8, const uint32 *)) addr_USER_READ_100TP;
  uint8 (*const USER_100TP_PROG)          (const uint8 OTP_Page_Sel)                                                       = (uint8 (*)(const uint8)) addr_USER_100TP_PROG;
  uint8 (*const USER_ERASE_SECTOR)        (const uint32 NVMSectorAddr)                                                     = (uint8 (*)(const uint32)) addr_USER_ERASE_SECTOR;
  uint8 (*const USER_RAM_MBIST_START)     (const uint16 RAM_MBIST_Stop_Addr, const uint16 RAM_MBIST_Start_addr)            = (uint8 (*)(const uint16, const uint16)) addr_USER_RAM_MBIST_START;
  uint8 (*const USER_NVM_ECC_CHECK)       (void)                                                                           = (uint8 (*)(void)) addr_USER_NVM_ECC_CHECK;
  uint8 (*const USER_ECC_CHECK)           (const uint32 *ecc2addr)                                                         = (uint8 (*)(const uint32 *)) addr_USER_ECC_CHECK;
  /* BF-Step BootROM API extension */
  #ifdef RTE_DEVICE_BF_STEP
    uint8 (*const USER_ERASE_SECTOR_VERIFY) (const uint32 sector_addr)                                                       = (uint8 (*)(const uint32)) addr_USER_ERASE_SECTOR_VERIFY;
    uint8 (*const USER_ERASEPG_VERIFY)      (const uint32 page_addr)                                                         = (uint8 (*)(const uint32)) addr_USER_ERASEPG_VERIFY;
    uint8 (*const USER_VERIFY_PAGE)         (const uint32 page_addr)                                                         = (uint8 (*)(const uint32)) addr_USER_VERIFY_PAGE;
  #endif /* RTE_DEVICE_BF_STEP */
#endif /* UNIT_TESTING_LV2 */
/******************************************************************************
** Initialization function to make BootROM functions to be called from C     **
******************************************************************************/

/** \brief Programs a page to NVM
 */
uint8 ProgramPage(uint32 addr, const uint8 *buf, uint8 Branch, uint8 Correct, uint8 FailPageErase)
{
  sint32 int_was_mask;
  uint8 i;
  uint8 res;
  /* violation: cast from unsigned int to pointer [MISRA Rule 45]*/
  uint8 *pc = (uint8 *) addr;
  /* suspend and remember all enabled interrupts */
  int_was_mask = CMSIS_Irq_Dis();
  /* trigger WDT1 Short-Open-Window */
  WDT1_SOW_Service(1u);
  /* open NVM assembly buffer */
  res = USER_OPENAB(addr);
  /* trigger regular WDT1, close SOW */
  (void)WDT1_Service();

  /* check if OpenAB function returned a PASS (== 0) */
  if (res == (uint8)0)
  {
    /* fill up the assembly buffer with new data */
    for (i = 0u; i < (uint8)FlashPageSize; i++)
    {
      pc[i] = buf[i];
    }

    /* trigger WDT1 Short-Open-Window */
    WDT1_SOW_Service(1u);
    /* execute NVM programming function */
    res = USER_PROG((uint8)(((FailPageErase & (uint8)1) << 2u) |
                            ((Correct & (uint8)1) << 1u) | (Branch & (uint8)1)));
    /* trigger regular WDT1, close SOW */
    (void)WDT1_Service();
  }

  /* reenable suspended interrupts */
  if (int_was_mask == 0)
  {
    CMSIS_Irq_En();
  }

  return (res);
}

/** \brief Reads the Customer ID out of the 100TP NVM
 */
/* violation: declaration of symbol 'CustID' with union based type 'const TCustomerID *' [MISRA 2012 Rule 19.2, advisory] */
bool GetCustomerID(const TCustomerID *CustID)
{
  sint32 int_was_mask;
  bool res;
  /* suspend and remember all enabled interrupts */
  int_was_mask = CMSIS_Irq_Dis();
  /* trigger Short-Open-Window */
  WDT1_SOW_Service(1u);
  /* read customer ID out of 100TP page 1, offset 0 */
  /* violation: cast from pointer to pointer [MISRA 2012 Rule 11.3, required], [MISRA 2012 Rule 11.5, advisory] */
  res = USER_READ_100TP((uint8)0x11, (uint8)0, (const uint32 *)CustID);
  /* trigger regular WDT1, close SOW */
  (void)WDT1_Service();

  /* reenable suspended interrupts */
  if (int_was_mask == 0)
  {
    CMSIS_Irq_En();
  }

  /* check if Read_100TP returned a PASS (== true) */
  return (res);
}
