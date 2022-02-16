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
#include "pmu.h"
#include "wdt1.h"
#include "cmsis_misra.h"
#include "pmu_defines.h"
#include "RTE_Components.h"

/*******************************************************************************
**                         Global Function Definitions                        **
*******************************************************************************/

void PMU_Init(void)
{
#ifndef RTE_DEVICE_BF_STEP
#if ((PMU_VDDEXT_CTRL & 1u) == 1u)
  /* turn VDDEXT on using the workaround, for BE-Step and earlier */
  (void)PMU_VDDEXT_On();
  /* in addition write all the other control bits of VDDEXT       */
  PMU->VDDEXT_CTRL.reg = (uint8) PMU_VDDEXT_CTRL;
#else
  /* VDDEXT is not supposed to be enabled now, so write the other **
  ** control bits only                                            */
  PMU->VDDEXT_CTRL.reg = (uint8) PMU_VDDEXT_CTRL;
#endif /* ((PMU_VDDEXT_CTRL & 1u) == 1u) */
#else /* BF-Step */
  /* for BF-Step the register can be written directly             */
  PMU->VDDEXT_CTRL.reg = (uint8) PMU_VDDEXT_CTRL;
#endif /* RTE_DEVICE_BF_STEP */
  PMU->CNF_CYC_SENSE.reg = (uint8) PMU_CNF_CYC_SENSE;
  PMU->CNF_CYC_SAMPLE_DEL.reg = (uint8) PMU_CNF_CYC_SAMPLE_DEL;
  PMU->CNF_CYC_WAKE.reg = (uint8) PMU_CNF_CYC_WAKE;
#if (CONFIGWIZARD == 1)
  PMU->CNF_PMU_SETTINGS.reg = (uint8) PMU_CNF_PMU_SETTING;
#else /* (CONFIGWIZARD == 2) */
  PMU->CNF_PMU_SETTINGS.reg = (uint8) PMU_CNF_PMU_SETTINGS;
#endif
  PMU->PMU_SUPPLY_STS.reg = (uint8) PMU_PMU_SUPPLY_STS;
  PMU->LIN_WAKE_EN.reg = (uint8) PMU_LIN_WAKE_EN;
  PMU->WAKE_CONF_GPIO0_CYC.reg = (uint8) PMU_WAKE_CONF_GPIO0_CYC;
  PMU->WAKE_CONF_GPIO0_FALL.reg = (uint8) PMU_WAKE_CONF_GPIO0_FALL;
  PMU->WAKE_CONF_GPIO0_RISE.reg = (uint8) PMU_WAKE_CONF_GPIO0_RISE;
  PMU->WAKE_CONF_GPIO1_CYC.reg = (uint8) PMU_WAKE_CONF_GPIO1_CYC;
  PMU->WAKE_CONF_GPIO1_FALL.reg = (uint8) PMU_WAKE_CONF_GPIO1_FALL;
  PMU->WAKE_CONF_GPIO1_RISE.reg = (uint8) PMU_WAKE_CONF_GPIO1_RISE;
  PMU->CNF_RST_TFB.reg = (uint8) PMU_CNF_RST_TFB;
  PMU->CNF_WAKE_FILTER.reg = (uint8) PMU_CNF_WAKE_FILTER;
}

#ifdef RTE_DEVICE_BF_STEP
/** \brief Turns VDDEXT on.
 * \brief BF-Step implementation
 *
 * \retval TRUE VDDEXT was turned on
 * \retval FALSE VDDEXT is off, was not turned on
 *
 * \ingroup drv_api
 */
bool PMU_VDDEXT_On(void)
{
  bool bRet = false;
  Field_Mod8(&PMU->VDDEXT_CTRL.reg, (uint8)PMU_VDDEXT_CTRL_ENABLE_Pos, (uint8)PMU_VDDEXT_CTRL_ENABLE_Msk, 1u);
  /* delay 200us, to give VDDEXT some time to ramp up */
  Delay_us(200u);

  /* return the status of VDDEXT_CTRL.STABLE */
  if (u1_Field_Rd8(&PMU->VDDEXT_CTRL.reg, (uint8)PMU_VDDEXT_CTRL_STABLE_Pos, (uint8)PMU_VDDEXT_CTRL_STABLE_Msk) == 1u)
  {
    bRet = true;
  }

  return (bRet) ;
}
#else /* BE-Step or earlier */
/** \brief Turns VDDEXT on.
 * \brief to satify the EPN for BE-Step.
 * Excluded from unit test due to EPN distribution.
 *
 * \retval TRUE VDDEXT was turned on
 * \retval FALSE VDDEXT is off, was not turned on
 *
 * \ingroup drv_api
 */
bool PMU_VDDEXT_On(void)
{
  bool result;
  result = false;
  /* disable all interrupts to ensure toggle timing 0.1us < on/off-time < 2.5us */
  CMSIS_Irq_Dis();
  /* toggle VDDEXT.CTRL.ENABLE eight times */
  /* VDDEXT Enable #1 */
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 1u;
  /* VDDEXT Disable #1 */
  PMU->VDDEXT_CTRL.reg = 0u;
  PMU->VDDEXT_CTRL.reg = 0u;
  PMU->VDDEXT_CTRL.reg = 0u;
  /* VDDEXT Enable #2 */
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 1u;
  /* VDDEXT Disable #2 */
  PMU->VDDEXT_CTRL.reg = 0u;
  PMU->VDDEXT_CTRL.reg = 0u;
  PMU->VDDEXT_CTRL.reg = 0u;
  /* VDDEXT Enable #3 */
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 1u;
  /* VDDEXT Disable #3 */
  PMU->VDDEXT_CTRL.reg = 0u;
  PMU->VDDEXT_CTRL.reg = 0u;
  PMU->VDDEXT_CTRL.reg = 0u;
  /* VDDEXT Enable #4 */
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 1u;
  /* VDDEXT Disable #4 */
  PMU->VDDEXT_CTRL.reg = 0u;
  PMU->VDDEXT_CTRL.reg = 0u;
  PMU->VDDEXT_CTRL.reg = 0u;
  /* VDDEXT Enable #5 */
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 1u;
  /* VDDEXT Disable #5 */
  PMU->VDDEXT_CTRL.reg = 0u;
  PMU->VDDEXT_CTRL.reg = 0u;
  PMU->VDDEXT_CTRL.reg = 0u;
  /* VDDEXT Enable #6 */
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 1u;
  /* VDDEXT Disable #6 */
  PMU->VDDEXT_CTRL.reg = 0u;
  PMU->VDDEXT_CTRL.reg = 0u;
  PMU->VDDEXT_CTRL.reg = 0u;
  /* VDDEXT Enable #7 */
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 1u;
  /* VDDEXT Disable #7 */
  PMU->VDDEXT_CTRL.reg = 0u;
  PMU->VDDEXT_CTRL.reg = 0u;
  PMU->VDDEXT_CTRL.reg = 0u;
  /* VDDEXT Enable #8 */
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 1u;
  /* enable irqs */
  CMSIS_Irq_En();
  /* delay 200us, to give VDDEXT some time to ramp up */
  Delay_us(200u);

  /* return the status of VDDEXT_CTRL.STABLE */
  if ((PMU->VDDEXT_CTRL.reg & (uint8)PMU_VDDEXT_STABLE) == (uint8)PMU_VDDEXT_STABLE)
  {
    result = true;
  }

  return (result);
}
#endif /* RTE_DEVICE_BF_STEP */
