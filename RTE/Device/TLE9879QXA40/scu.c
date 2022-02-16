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
#include "scu.h"
#include "wdt1.h"
#include "lin.h"
#include "bootrom.h"
#include "pmu_defines.h"
#include "cmsis_misra.h"
#include "RTE_Components.h"

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wself-assign"
#endif

/*******************************************************************************
**                         Global Variable Definitions                        **
*******************************************************************************/
uint32 SystemFrequency = (uint32)SCU_FSYS;


/*******************************************************************************
**                         Private Function Definitions                       **
*******************************************************************************/
/** \brief Sets the SYCLKSEL multiplexer (fSYS) to LP_CLK
 *
 * \ingroup scu_api
 */
INLINE void PLL_setfSYStoLPCLK(void)
{
  uint8 u8_loc_syscon0;
  u8_loc_syscon0 = SCU->SYSCON0.reg;
  /* set SYSCLKSEL = 3 (LP_CLK) */
  Field_Mod8(&u8_loc_syscon0, (uint8)SCU_SYSCON0_SYSCLKSEL_Pos, (uint8)SCU_SYSCON0_SYSCLKSEL_Msk, 3u);
  SCU_OpenPASSWD();
  SCU->SYSCON0.reg = u8_loc_syscon0;
  SCU_ClosePASSWD();
}

/** \brief Sets the SYCLKSEL multiplexer (fSYS) to fPLL
 *
 * \ingroup scu_api
 */
INLINE void PLL_setfSYStofPLL(void)
{
  uint8 u8_loc_syscon0;
  u8_loc_syscon0 = SCU->SYSCON0.reg;
  /* set SYSCLKSEL = 0 (fPLL) */
  Field_Mod8(&u8_loc_syscon0, (uint8)SCU_SYSCON0_SYSCLKSEL_Pos, (uint8)SCU_SYSCON0_SYSCLKSEL_Msk, 0u);
  SCU_OpenPASSWD();
  SCU->SYSCON0.reg = u8_loc_syscon0;
  SCU_ClosePASSWD();
}

/** \brief Sets the K1DIV to 1.
 * \brief The K1DIV becomes relevant if the Prescaler Mode is selected.
 * \brief To ensure a fPLL of >= 5 MHz, K1DIV is set to divide fR by 1
 *
 * \ingroup scu_api
 */
INLINE void PLL_setK1divToOne(void)
{
  uint8 u8_loc_cmcon1;
  u8_loc_cmcon1 = SCU->CMCON1.reg;
  /* set K1 = 1 */
  Field_Mod8(&u8_loc_cmcon1, (uint8)SCU_CMCON1_K1DIV_Pos, (uint8)SCU_CMCON1_K1DIV_Msk, 1u);
  SCU_OpenPASSWD();
  SCU->CMCON1.reg = u8_loc_cmcon1;
  SCU_ClosePASSWD();
}

#if (SCU_XTAL_EN == 1)
/** \brief Sets the oscillator source select multiplexer to internal oscillator (sync.)
 * \brief This function is only used if an external XTAL is used.
 *
 * \ingroup scu_api
 */
INLINE void PLL_setClkSrcToIntOscSync(void)
{
  uint8 u8_loc_osc_con;
  u8_loc_osc_con = SCU->OSC_CON.reg;
  /* set OSCSS = 0 (int. osc, sync) */
  Field_Mod8(&u8_loc_osc_con, (uint8)SCU_OSC_CON_OSCSS_Pos, (uint8)SCU_OSC_CON_OSCSS_Msk, 0);
  SCU_OpenPASSWD();
  SCU->OSC_CON.reg = u8_loc_osc_con;
  SCU_ClosePASSWD();
}

/** \brief Sets the oscillator source select multiplexer to XTAL (HP_OSC)
 * \brief This function is only used if an external XTAL is used.
 *
 * \ingroup scu_api
 */
INLINE void PLL_setClkSrcToXtal(void)
{
  uint8 u8_loc_osc_con;
  u8_loc_osc_con = SCU->OSC_CON.reg;
  /* set OSCSS = 1 (XTAL) */
  Field_Mod8(&u8_loc_osc_con, (uint8)SCU_OSC_CON_OSCSS_Pos, (uint8)SCU_OSC_CON_OSCSS_Msk, 1);
  SCU_OpenPASSWD();
  SCU->OSC_CON.reg = u8_loc_osc_con;
  SCU_ClosePASSWD();
}

/** \brief Enabled the high precision oscillator (XTAL)
 * \brief This function is only used if an external XTAL is used.
 *
 * \ingroup scu_api
 */
INLINE void PLL_enableXTAL(void)
{
  uint8 u8_loc_osc_con;
  u8_loc_osc_con = SCU->OSC_CON.reg;
  /* set XPD = 0 */
  Field_Mod8(&u8_loc_osc_con, (uint8)SCU_OSC_CON_XPD_Pos, (uint8)SCU_OSC_CON_XPD_Msk, 0);
  SCU_OpenPASSWD();
  SCU->OSC_CON.reg = u8_loc_osc_con;
  SCU_ClosePASSWD();
}

/** \brief Resets the oscillator watchdog
 * \brief This function is only used if an external XTAL is used.
 *
 * \ingroup scu_api
 */
INLINE void PLL_resetOscWDT(void)
{
  /* set OSCWDTRST = 1 */
  Field_Mod8(&SCU->OSC_CON.reg, (uint8)SCU_OSC_CON_OSCWDTRST_Pos, (uint8)SCU_OSC_CON_OSCWDTRST_Msk, 1);
}

/** \brief Waits for the oscillator watchdog to reset the OSC2L flag
 * \brief This function is only used if an external XTAL is used.
 *
 * \ingroup scu_api
 */
INLINE void PLL_waitForOSC2L(void)
{
  /* wait for OSC2L = 0 */
  while (u1_Field_Rd8(&SCU->OSC_CON.reg, (uint8)SCU_OSC_CON_OSC2L_Pos, (uint8)SCU_OSC_CON_OSC2L_Msk) == (uint8)1)
  {
  }
}
#else /* SCU_XTAL_EN == 0 */
/** \brief Sets the OSCTRIM_8 bit and BIT5 in OSC_CON
 * \brief This function is only used if the internal 5 MHz oscillator is used.
 *
 * \ingroup scu_api
 */
INLINE void PLL_setOscTrim(void)
{
  uint8 u8_loc_osc_con;
  u8_loc_osc_con = SCU->OSC_CON.reg;
  /* set OSCTRIM_8 */
  Field_Mod8(&u8_loc_osc_con, (uint8)SCU_OSC_CON_OSCTRIM_8_Pos, (uint8)SCU_OSC_CON_OSCTRIM_8_Msk, 1);
  /* set reserved Bit5 to '1' always */
  u8_loc_osc_con |= (1u << 5u);
  SCU_OpenPASSWD();
  SCU->OSC_CON.reg = u8_loc_osc_con;
  SCU_ClosePASSWD();
}
#endif /* SCU_XTAL_EN == 1 */

/** \brief Sets the NDIV according to the Config Wizard setting
 *
 * \ingroup scu_api
 */
INLINE void PLL_setNdivFromConfigWizard(void)
{
  uint8 u8_loc_pll_con;
  u8_loc_pll_con = SCU->PLL_CON.reg;
  /* clear NDIV bits */
  u8_loc_pll_con &= (uint8)~SCU_PLL_CON_NDIV_Msk;
  /* set NDIV according to Config Wizard settings */
  u8_loc_pll_con = u8_loc_pll_con | (uint8)((uint8)SCU_PLL_CON & (uint8)SCU_PLL_CON_NDIV_Msk);
  SCU_OpenPASSWD();
  SCU->PLL_CON.reg = u8_loc_pll_con;
  SCU_ClosePASSWD();
}

/** \brief Sets the VCOSEL and K2DIV according to the Config Wizard setting
 *
 * \ingroup scu_api
 */
INLINE void PLL_setVcoselK2divFromConfigWizard(void)
{
  /* set VCOSEL and K2DIV according to Config Wizard settings, ensure K1 remains set to '1' */
  SCU_OpenPASSWD();
  SCU->CMCON1.reg = (uint8)SCU_CMCON1 | (uint8)SCU_CMCON1_K1DIV_Msk;
  SCU_ClosePASSWD();
}

/** \brief Resets the PLL lock detection
 *
 * \ingroup scu_api
 */
INLINE void PLL_resetPllLockDetection(void)
{
  /* set RESLD = 1 */
  Field_Mod8(&SCU->PLL_CON.reg, (uint8)SCU_PLL_CON_RESLD_Pos, (uint8)SCU_PLL_CON_RESLD_Msk, 1u);
}

/** \brief Waits for the PLL to lock
 *
 * \ingroup scu_api
 */
INLINE void PLL_waitForPllLock(void)
{
  /* wait for LOCK == 1 */
  while (u1_Field_Rd8(&SCU->PLL_CON.reg, (uint8)SCU_PLL_CON_LOCK_Pos, (uint8)SCU_PLL_CON_LOCK_Msk) == (uint8)0)
  {
  }
}

/** \brief Sets PLL into Prescaler Mode
 *
 * \ingroup scu_api
 */
INLINE void PLL_setPrescalerMode(void)
{
  /* set VCOBYP = 1 */
  Field_Mod8(&SCU->PLL_CON.reg, (uint8)SCU_PLL_CON_VCOBYP_Pos, (uint8)SCU_PLL_CON_VCOBYP_Msk, 1u);
}

/** \brief Sets PLL into Normal Mode
 *
 * \ingroup scu_api
 */
INLINE void PLL_setNormalMode(void)
{
  /* set VCOBYP = 0 */
  Field_Mod8(&SCU->PLL_CON.reg, (uint8)SCU_PLL_CON_VCOBYP_Pos, (uint8)SCU_PLL_CON_VCOBYP_Msk, 0u);
}

/** \brief Toggles the APCLK_SET bit to take over APCLK settings
 *
 * \ingroup scu_api
 */
INLINE void SCU_toggleAPCLK_SET(void)
{
  uint8 u8_loc_apclk_ctrl1;
  u8_loc_apclk_ctrl1 = SCU->APCLK_CTRL1.reg;
  Field_Mod8(&u8_loc_apclk_ctrl1, (uint8)SCU_APCLK_CTRL1_APCLK_SET_Pos, (uint8)SCU_APCLK_CTRL1_APCLK_SET_Msk, 1u);
  SCU_OpenPASSWD();
  SCU->APCLK_CTRL1.reg = u8_loc_apclk_ctrl1;
  SCU_ClosePASSWD();
  CMSIS_NOP();
  Field_Mod8(&u8_loc_apclk_ctrl1, (uint8)SCU_APCLK_CTRL1_APCLK_SET_Pos, (uint8)SCU_APCLK_CTRL1_APCLK_SET_Msk, 0u);
  SCU_OpenPASSWD();
  SCU->APCLK_CTRL1.reg = u8_loc_apclk_ctrl1;
  SCU_ClosePASSWD();
}

/*******************************************************************************
**                         Global Function Definitions                        **
*******************************************************************************/
void SCU_ClkInit(void)
{
  sint32 int_was_mask;
  /* disable all interrupts                */
  int_was_mask = CMSIS_Irq_Dis();
  /***************************************************************************
   ** NVM Protection Control                                                **
   **************************************************************************/
#if (SCU_CFLASH_WPROT == 1)
  (void)USER_CFLASH_WR_PROT_EN((uint16) SCU_CFLASH_WPROT_PW);
#endif
#if (SCU_DFLASH_WPROT == 1)
  (void)USER_DFLASH_WR_PROT_EN((uint16) SCU_DFLASH_WPROT_PW);
#endif
  /***************************************************************************
   ** PLL/SYSCLK Control                                                    **
   **************************************************************************/
  /* step 1: disable PLL loss of lock NMI */
  Field_Mod8(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMIPLL_Pos, (uint8)SCU_NMICON_NMIPLL_Msk, 0);
  /* disable oscillator WDT NMI */
  Field_Mod8(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMIWDT_Pos, (uint8)SCU_NMICON_NMIWDT_Msk, 0);
  /* step 1.5: select LP_CLK as fSYS, this step is optional */
  PLL_setfSYStoLPCLK();
  /* step 2: sets CMCON1.K1DIV = 1, fPLL = fR / 1 */
  PLL_setK1divToOne();
  /* step 3: enable PLL Prescaler Mode, PLL_CON.VCOBYP = 1, hardware forces PLL_CON.OSCDISC to '0' */
  PLL_setPrescalerMode();
#if (SCU_XTAL_EN == 1)

  /* these are additional steps needed for XTAL usage */
  /* switch to int. osc */
  if (SCU->OSC_CON.bit.OSCSS == 1)
  {
    /* switch to int. osc */
    PLL_setClkSrcToIntOscSync();
  }

  /* enable the HP_OSC */
  PLL_enableXTAL();
  /* reset the osc. watchdog */
  PLL_resetOscWDT();
  /* wait for osc. freq. not too low anymore */
  PLL_waitForOSC2L();
  /* switch to XTAL as PLL input */
  PLL_setClkSrcToXtal();
#else /* SCU_XTAL_EN == 0 */
  /* step 4: OSC_CON.OSCTRIM_8 = 1 **
  ** step 5: OSC_CON.Bit5 = 1      */
  PLL_setOscTrim();
#endif /* SCU_XTAL_EN == 1 */
  /* step 6: set PLL_CON.NDIV, ensure that VCOBYP remains set */
  PLL_setNdivFromConfigWizard();
  /* step 7: set CMCON1.VCOSEL, CMCON1.K2DIV and ensure K1DIV remains '1' */
  PLL_setVcoselK2divFromConfigWizard();
  /* step 8: restart PLL lock detection */
  PLL_resetPllLockDetection();
  /* step 9: wait for PLL being locked */
  PLL_waitForPllLock();
  /* step 10: enable PLL Normal Mode, PLL_CON.VCOBYP = 0 */
  PLL_setNormalMode();
  /* step 10.5: select fPLL as fSYS, optional, goes along with step 1.5 (see above) */
  PLL_setfSYStofPLL();
  /* step 11: clear PLL loss of lock NMI status, NMI will be enabled later */
  Field_Mod8(&SCU->NMICLR.reg, (uint8)SCU_NMICLR_NMIPLLC_Pos, (uint8)SCU_NMICLR_NMIPLLC_Msk, 1u);
  Field_Mod8(&SCU->NMICLR.reg, (uint8)SCU_NMICLR_NMIOWDC_Pos, (uint8)SCU_NMICLR_NMIOWDC_Msk, 1u);
  /***************************************************************************
   ** Analog Clock Control                                                  **
   **************************************************************************/
  /* set factor for MI_CLK */
  Field_Wrt8all(&SCU->APCLK1.reg, SCU_APCLK1);
  /* apply setting by toggling APCLK_SET */
  SCU_toggleAPCLK_SET();
  /* set factor for Filt_CLK */
  Field_Wrt8all(&SCU->APCLK2.reg, SCU_APCLK2);
  /* apply setting by toggling APCLK_SET */
  SCU_toggleAPCLK_SET();
#ifdef SCU_APCLK_CTRL1
  SCU_OpenPASSWD();
  SCU->APCLK_CTRL1.reg = (uint8)SCU_APCLK_CTRL1;
  SCU_ClosePASSWD();
#endif
#ifdef SCU_APCLK_CTRL2
  SCU_OpenPASSWD();
  SCU->APCLK_CTRL2.reg = (uint8)SCU_APCLK_CTRL2;
  SCU_ClosePASSWD();
#endif
  /* apply setting by toggling APCLK_SET */
  SCU_toggleAPCLK_SET();

  /* enable interrupts                     */
  if (int_was_mask == 0)
  {
    CMSIS_Irq_En();
  }
}

void SCU_Init(void)
{
  /***************************************************************************
   ** System Clock Output Control                                           **
   **************************************************************************/
  SCU->COCON.reg = (uint8) (SCU_COCON);
  /***************************************************************************
   ** Watchdog Control (internal)                                           **
   **************************************************************************/
#if (CONFIGWIZARD == 1)
  SCU->WDTREL.reg = (uint8) SCU_WDTRL;
#else /* (CONFIGWIZARD == 2) */
  SCU->WDTREL.reg = (uint8) SCU_WDTREL;
#endif
  SCU->WDTWINB.reg = (uint8) SCU_WDTWINB;
  SCU->WDTCON.reg = (uint8) SCU_WDTCON;
  /***************************************************************************
   ** Module Pin Select                                                     **
   **************************************************************************/
#ifdef SCU_MODPISEL
  SCU->MODPISEL.reg = (uint8) SCU_MODPISEL;
#endif
#ifdef SCU_MODPISEL1
  SCU->MODPISEL1.reg = (uint8) SCU_MODPISEL1;
#endif
#ifdef SCU_MODPISEL2
  SCU->MODPISEL2.reg = (uint8) SCU_MODPISEL2;
#endif
#ifdef SCU_MODPISEL3
  SCU->MODPISEL3.reg = (uint8) SCU_MODPISEL3;
#endif
  SCU->GPT12PISEL.reg = (uint8) SCU_GPT12PISEL;
  /***************************************************************************
   ** DMA Source Select                                                     **
   **************************************************************************/
#if (SCU_XML_VERSION >= 10109)
#ifdef SCU_DMASRCSEL
  SCU->DMASRCSEL.reg = (uint8) SCU_DMASRCSEL;
#endif
#ifdef SCU_DMASRCSEL2
  SCU->DMASRCSEL2.reg = (uint8) SCU_DMASRCSEL2;
#endif
#endif
}


#if (PMU_SLEEP_MODE == 1)
/* violation: Last value assigned to variable 'dummy' (defined at line 282) not used [MISRA 2012 Rule 2.2, required] */
#ifndef UNIT_TESTING_LV2
  void __attribute__((noreturn)) SCU_EnterSleepMode(void)
#else
  void SCU_EnterSleepMode(void)
#endif
{
  uint8 u8_loc_pmcon0;
  /* violation: Previously assigned value to variable 'dummy' has not been used */
  /* This function assumes the desired     *
   * wake up sources are enabled already   */
  uint8 dummy;
  /* to remove compiler warning of unused  *
   * dummy variable                        */
  dummy = 0;
  dummy = dummy;
  /* set LIN Trx into Sleep Mode           */
  LIN_Set_Mode(LIN_MODE_SLEEP);

  /* wait until LIN Trx switched           *
   * into Sleep Mode                       */
  while (LIN_Get_Mode() != LIN_GET_MODE_SLEEP)
  {
  }

  /* wait approx. 100µs in order to pass   *
   * the filter time + margin inside the   *
   * LIN Trx. to avoid a false wake up     */
  Delay_us(100u);
  /* dummy read to clr wake up status      *
   * to prevent the device from wakeing up *
   * immediately because of still set      *
   * wake up flags                         */
  dummy = u8_Field_Rd8(&PMU->WAKE_STATUS.reg, 0, 0xFF);
  /* dummy read to clr MON wake up status  */
  dummy = u8_Field_Rd8(&PMU->WAKE_STS_MON.reg, 0, 0xFF);
  /* stop WDT1 (SysTick) to prevent any    *
   * SysTick interrupt to disturb the      *
   * Sleep Mode Entry sequence             */
  WDT1_Stop();
  /* Trigger a ShortOpenWindow on WDT1     *
   * to prevent an unserviced WDT1 by      *
   * accident                              */
  WDT1_SOW_Service(1u);
  /* disable all interrupts                */
  (void)CMSIS_Irq_Dis();
  /* read current PMCON0 content           */
  u8_loc_pmcon0 = SCU->PMCON0.reg;
  /* set SleepMode flag in PMCON0          */
  Field_Mod8(&u8_loc_pmcon0, (uint8)SCU_PMCON0_SL_Pos, (uint8)SCU_PMCON0_SL_Msk, 1U);
  /* open passwd to access PMCON0 register */
  SCU_OpenPASSWD();
  SCU->PMCON0.reg = u8_loc_pmcon0;
  CMSIS_WFE();
  CMSIS_WFE();
  /* dont do anything anymore            *
   * device is in SleepMode              */
#ifndef UNIT_TESTING_LV2

  for (;;)
  {
  }

#endif
  /* device is in Sleep Mode now          *
   * wake up performs RESET               */
}
#endif


#if (PMU_STOP_MODE == 1)
/** \brief Sets the oscillator source select multiplexer to internal oscillator (async.)
 *
 * \ingroup scu_api
 */
INLINE void PLL_setClkSrcToIntOscAsync(void)
{
  uint8 u8_loc_osc_con;
  u8_loc_osc_con = SCU->OSC_CON.reg;
  /* set OSCSS = 0 (int. osc, async) */
  Field_Mod8(&u8_loc_osc_con, (uint8)SCU_OSC_CON_OSCSS_Pos, (uint8)SCU_OSC_CON_OSCSS_Msk, 3u);
  SCU_OpenPASSWD();
  SCU->OSC_CON.reg = u8_loc_osc_con;
  SCU_ClosePASSWD();
}

/* violation: Last value assigned to variable 'dummy' (defined at line 346) not used [MISRA 2012 Rule 2.2, required] */
void SCU_EnterStopMode(void)
{
  uint8 u8_loc_pmcon0;
  sint32 int_was_mask;
  /* violation: Previously assigned value to variable 'dummy' has not been used */
  uint8 dummy;
  /* to remove compiler warning of unused  *
   * dummy variable                        */
  dummy = 0;
  dummy = dummy;
  /* dummy read to clr wake up status      *
   * to prevent the device from wakeing up *
   * immediately because of still set      *
   * wake up flags                         */
  dummy = u8_Field_Rd8(&PMU->WAKE_STATUS.reg, 0, 0xFF);
  /* dummy read to clr MON wake up status  */
  dummy = u8_Field_Rd8(&PMU->WAKE_STS_MON.reg, 0, 0xFF);
  /* dummy read to clr GPIO wake up status */
  dummy = u8_Field_Rd8(&PMU->WAKE_STS_GPIO0.reg, 0, 0xFF);
  dummy = u8_Field_Rd8(&PMU->WAKE_STS_GPIO1.reg, 0, 0xFF);
  /* stop WDT1 (SysTick) to prevent any    *
   * SysTick interrupt to disturb the      *
   * Sleep Mode Entry sequence             */
  WDT1_Stop();
  /* Trigger a ShortOpenWindow on WDT1     *
   * to prevent an unserviced WDT1 by      *
   * accident                              */
  WDT1_SOW_Service(1u);
  /* disable all interrupts                */
  int_was_mask = CMSIS_Irq_Dis();
  /* open access to SYSCLKSEL register     */
  PLL_setfSYStoLPCLK();
  /* open access to OSC_CON register       */
  PLL_setClkSrcToIntOscAsync();
  /* read current PMCON0 content           */
  u8_loc_pmcon0 = SCU->PMCON0.reg;
  /* set PowerDown flag in PMCON0          */
  Field_Mod8(&u8_loc_pmcon0, (uint8)SCU_PMCON0_PD_Pos, (uint8)SCU_PMCON0_PD_Msk, 1U);
  /* open passwd to access PMCON0 register */
  SCU_OpenPASSWD();
  SCU->PMCON0.reg = u8_loc_pmcon0;
  CMSIS_SEV();
  CMSIS_WFE();
  CMSIS_WFE();
  CMSIS_NOP();
  CMSIS_NOP();
  CMSIS_NOP();
  /* dont do anything anymore            *
   * device is in PowerDown Mode         */
  /***************************************/
  /********* DEVICE IN STOP MODE *********/
  /***************************************/
  /* Device has been woken up            */
  /* reset PLL locking                   */
  /* restart PLL lock detection */
  PLL_resetPllLockDetection();
  /* wait for PLL being locked           */
  PLL_waitForPllLock();
  /* enable PLL Normal Mode, PLL_CON.VCOBYP = 0 */
  PLL_setNormalMode();
  /* select fPLL as fSYS, optional, goes along with step 1.5 (see above) */
  PLL_setfSYStofPLL();

  /* enable interrupts                     */
  if (int_was_mask == 0)
  {
    CMSIS_Irq_En();
  }

  /* Init SysTick                          */
  SysTick_Init();
  /* Init and service WDT1                 */
  WDT1_Init();
}
#endif


void SCU_EnterSlowMode(uint8 divider_scaled)
{
  uint8 u8_loc_pmcon0;
  sint32 int_was_mask;
  uint16 divider[16] = {1, 2, 3, 4, 8, 16, 24, 32, 48, 64, 96, 128, 192, 256, 384, 512};
  uint32 reload_value;
  uint8 divider_scaled_local = divider_scaled;

  if (divider_scaled_local > (uint8)0x0F)
  {
    divider_scaled_local = 0x0F;
  }

  /* set the Clock Output Divider */
  Field_Mod8(&SCU->CMCON1.reg, (uint8)SCU_CMCON1_CLKREL_Pos, (uint8)SCU_CMCON1_CLKREL_Msk, divider_scaled_local);
  /* stop WDT1 (SysTick) to prevent any    *
   * SysTick interrupt to disturb the      *
   * Sleep Mode Entry sequence             */
  WDT1_Stop();
  /* Trigger a ShortOpenWindow on WDT1     *
   * to prevent an unserviced WDT1 by      *
   * accident                              */
  WDT1_SOW_Service(3u);
  /* disable all interrupts                */
  int_was_mask = CMSIS_Irq_Dis();
  /* read current PMCON0 content           */
  u8_loc_pmcon0 = SCU->PMCON0.reg;
  /* set SlowDown flag in PMCON0           */
  Field_Mod8(&u8_loc_pmcon0, (uint8)SCU_PMCON0_SD_Pos, (uint8)SCU_PMCON0_SD_Msk, 1U);
  /* open passwd to access PMCON0 register */
  SCU_OpenPASSWD();
  SCU->PMCON0.reg = u8_loc_pmcon0;
  SCU_ClosePASSWD();

  /***************************************/
  /********* DEVICE IN SLOW MODE *********/
  /***************************************/
  /* enable interrupts                     */
  if (int_was_mask == 0)
  {
    CMSIS_Irq_En();
  }

  /* set reload value of systick           */
  reload_value = ((uint32)SCU_FSYS /  divider[divider_scaled_local]) / SysTickFreq;
  /* program SysTick Timer */
  SysTick_ReloadValue_Set(reload_value);
  /* Enable SysTick                        */
  CPU->SYSTICK_CS.bit.ENABLE = 1;
  /* Init and service WDT1                 */
  WDT1_Init();
}


void SCU_ExitSlowMode(void)
{
  uint8 u8_loc_pmcon0;
  sint32 int_was_mask;
  /* stop WDT1 (SysTick) to prevent any    *
   * SysTick interrupt to disturb the      *
   * Slow Mode Exit sequence               */
  WDT1_Stop();
  /* Trigger a ShortOpenWindow on WDT1     *
   * to prevent an unserviced WDT1 by      *
   * accident                              */
  WDT1_SOW_Service(3);
  /* disable all interrupts                */
  int_was_mask = CMSIS_Irq_Dis();
  /* read current PMCON0 content           */
  u8_loc_pmcon0 = SCU->PMCON0.reg;
  /* reset SlowDown flag in PMCON0         */
  Field_Mod8(&u8_loc_pmcon0, (uint8)SCU_PMCON0_SD_Pos, (uint8)SCU_PMCON0_SD_Msk, 0U);
  /* open passwd to access PMCON0 register */
  SCU_OpenPASSWD();
  SCU->PMCON0.reg = u8_loc_pmcon0;
  SCU_ClosePASSWD();

  /***************************************/
  /***** DEVICE back in NORMAL MODE ******/
  /***************************************/
  /* enable interrupts                     */
  if (int_was_mask == 0)
  {
    CMSIS_Irq_En();
  }

  /* Init SysTick                          */
  SysTick_Init();
  /* Init and service WDT1                 */
  WDT1_Init();
}

bool SCU_ChangeNVMProtection(uint32 mode, uint32 action)
{
  bool result;
  result = true;

  if (action == PROTECTION_CLEAR)
  {
    if (mode == NVM_DATA_WRITE)
    {
      result = USER_DFLASH_WR_PROT_DIS((uint16) SCU_DFLASH_WPROT_PW);
    }
    else if (mode == NVM_CODE_WRITE)
    {
      result = USER_CFLASH_WR_PROT_DIS((uint16) SCU_CFLASH_WPROT_PW);
    }
    else if (mode == NVM_DATA_READ)
    {
      result = USER_DFLASH_RD_PROT_DIS((uint16) SCU_DFLASH_WPROT_PW);
    }
    else if (mode == NVM_CODE_READ)
    {
      result = USER_CFLASH_RD_PROT_DIS((uint16) SCU_CFLASH_WPROT_PW);
    }
    else
    {
    }
  }
  else
  {
    if (mode == NVM_DATA_WRITE)
    {
      result = USER_DFLASH_WR_PROT_EN((uint16) SCU_DFLASH_WPROT_PW);
    }
    else if (mode == NVM_CODE_WRITE)
    {
      result = USER_CFLASH_WR_PROT_EN((uint16) SCU_CFLASH_WPROT_PW);
    }
    else if (mode == NVM_DATA_READ)
    {
      result = USER_DFLASH_RD_PROT_EN((uint16) SCU_DFLASH_WPROT_PW);
    }
    else if (mode == NVM_CODE_READ)
    {
      result = USER_CFLASH_RD_PROT_EN((uint16) SCU_CFLASH_WPROT_PW);
    }
    else
    {
    }
  }

  return (result);
}

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
  #pragma clang diagnostic pop
#endif
