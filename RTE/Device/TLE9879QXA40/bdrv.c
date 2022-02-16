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
#include "bdrv.h"
#include "cmsis_misra.h"
#include "bdrv_defines.h"
#include "RTE_Components.h"

/*******************************************************************************
**                           Global Type Definitions                          **
*******************************************************************************/
#define SCUPM_BDRV_ISCLR_Pos (0UL)
#define SCUPM_BDRV_ISCLR_Msk (0xFFFFFFFFUL)

#define BDRV_CTRL1_LS1_Cfg_Pos BDRV_CTRL1_LS1_EN_Pos
#define BDRV_CTRL1_LS2_Cfg_Pos BDRV_CTRL1_LS2_EN_Pos
#define BDRV_CTRL1_HS1_Cfg_Pos BDRV_CTRL1_HS1_EN_Pos
#define BDRV_CTRL1_HS2_Cfg_Pos BDRV_CTRL1_HS2_EN_Pos
#if (UC_SERIES == TLE987)
  #define BDRV_CTRL2_LS3_Cfg_Pos BDRV_CTRL2_LS3_EN_Pos
  #define BDRV_CTRL2_HS3_Cfg_Pos BDRV_CTRL2_HS3_EN_Pos
#endif

#define BDRV_CTRL1_LS1_Cfg_Msk (BDRV_CTRL1_LS1_EN_Msk | BDRV_CTRL1_LS1_PWM_Msk | BDRV_CTRL1_LS1_ON_Msk | BDRV_CTRL1_LS1_DCS_EN_Msk)
#define BDRV_CTRL1_LS2_Cfg_Msk (BDRV_CTRL1_LS2_EN_Msk | BDRV_CTRL1_LS2_PWM_Msk | BDRV_CTRL1_LS2_ON_Msk | BDRV_CTRL1_LS2_DCS_EN_Msk)
#define BDRV_CTRL1_HS1_Cfg_Msk (BDRV_CTRL1_HS1_EN_Msk | BDRV_CTRL1_HS1_PWM_Msk | BDRV_CTRL1_HS1_ON_Msk | BDRV_CTRL1_HS1_DCS_EN_Msk)
#define BDRV_CTRL1_HS2_Cfg_Msk (BDRV_CTRL1_HS2_EN_Msk | BDRV_CTRL1_HS2_PWM_Msk | BDRV_CTRL1_HS2_ON_Msk | BDRV_CTRL1_HS2_DCS_EN_Msk)
#if (UC_SERIES == TLE987)
  #define BDRV_CTRL2_LS3_Cfg_Msk (BDRV_CTRL2_LS3_EN_Msk | BDRV_CTRL2_LS3_PWM_Msk | BDRV_CTRL2_LS3_ON_Msk | BDRV_CTRL2_LS3_DCS_EN_Msk)
  #define BDRV_CTRL2_HS3_Cfg_Msk (BDRV_CTRL2_HS3_EN_Msk | BDRV_CTRL2_HS3_PWM_Msk | BDRV_CTRL2_HS3_ON_Msk | BDRV_CTRL2_HS3_DCS_EN_Msk)
#endif

/*******************************************************************************
**                         Global Function Definitions                        **
*******************************************************************************/

void BDRV_Init(void)
{
  sint32 int_was_mask;
  /* Set charge pump clock */
  BDRV->CP_CLK_CTRL.reg = (uint32) BDRV_CP_CLK_CTRL;
  /* Set charge pump control, clear status bits */
  BDRV->CP_CTRL_STS.reg = (uint32) BDRV_CP_CTRL_STS;
  /* Set trimming register */
  int_was_mask = CMSIS_Irq_Dis();
  SCU_OpenPASSWD();
  BDRV->TRIM_DRVx.reg = (uint32) BDRV_TRIM_DRVx;
  SCU_ClosePASSWD();

  if (int_was_mask == 0)
  {
    CMSIS_Irq_En();
  }

  /* Set bridge driver control 1/2/3 */
  BDRV->CTRL1.reg = (uint32) BDRV_CTRL1;
  BDRV->CTRL2.reg = (uint32) BDRV_CTRL2;
  BDRV->CTRL3.reg = (uint32) BDRV_CTRL3;
#if (CONFIGWIZARD == 1)
  BDRV->OFF_SEQ_CTRL.reg = (uint32) BDRV_OFF_SEQ;
  BDRV->ON_SEQ_CTRL.reg = (uint32) BDRV_ON_SEQ;
#else /* (CONFIGWIZARD == 2) */
  BDRV->OFF_SEQ_CTRL.reg = (uint32) BDRV_OFF_SEQ_CTRL;
  BDRV->ON_SEQ_CTRL.reg = (uint32) BDRV_ON_SEQ_CTRL;
#endif
#if (UC_SERIES == TLE987)
  MF->BEMFC_CTRL_STS.reg = (uint32) MF_BEMFC_CTRL_STS;
  MF->TRIM_BEMFx.reg = (uint32) MF_TRIM_BEMFx;
#endif
} /* End of BDRV_Init */


#if (UC_SERIES == TLE987)
void BDRV_Set_Bridge(TBdrv_Ch_Cfg LS1_Cfg, TBdrv_Ch_Cfg HS1_Cfg,
                     TBdrv_Ch_Cfg LS2_Cfg, TBdrv_Ch_Cfg HS2_Cfg, TBdrv_Ch_Cfg LS3_Cfg,
                     TBdrv_Ch_Cfg HS3_Cfg)
{
  Field_Mod32(&BDRV->CTRL1.reg, BDRV_CTRL1_LS1_Cfg_Pos, BDRV_CTRL1_LS1_Cfg_Msk, (uint32)LS1_Cfg);
  Field_Mod32(&BDRV->CTRL1.reg, BDRV_CTRL1_HS1_Cfg_Pos, BDRV_CTRL1_HS1_Cfg_Msk, (uint32)HS1_Cfg);
  Field_Mod32(&BDRV->CTRL1.reg, BDRV_CTRL1_LS2_Cfg_Pos, BDRV_CTRL1_LS2_Cfg_Msk, (uint32)LS2_Cfg);
  Field_Mod32(&BDRV->CTRL1.reg, BDRV_CTRL1_HS2_Cfg_Pos, BDRV_CTRL1_HS2_Cfg_Msk, (uint32)HS2_Cfg);
  Field_Mod32(&BDRV->CTRL2.reg, BDRV_CTRL2_LS3_Cfg_Pos, BDRV_CTRL2_LS3_Cfg_Msk, (uint32)LS3_Cfg);
  Field_Mod32(&BDRV->CTRL2.reg, BDRV_CTRL2_HS3_Cfg_Pos, BDRV_CTRL2_HS3_Cfg_Msk, (uint32)HS3_Cfg);
}
#else
void BDRV_Set_Bridge(TBdrv_Ch_Cfg LS1_Cfg, TBdrv_Ch_Cfg HS1_Cfg,
                     TBdrv_Ch_Cfg LS2_Cfg, TBdrv_Ch_Cfg HS2_Cfg)
{
  Field_Mod32(&BDRV->CTRL1.reg, BDRV_CTRL1_LS1_Cfg_Pos, BDRV_CTRL1_LS1_Cfg_Msk, (uint32)LS1_Cfg);
  Field_Mod32(&BDRV->CTRL1.reg, BDRV_CTRL1_HS1_Cfg_Pos, BDRV_CTRL1_HS1_Cfg_Msk, (uint32)HS1_Cfg);
  Field_Mod32(&BDRV->CTRL1.reg, BDRV_CTRL1_LS2_Cfg_Pos, BDRV_CTRL1_LS2_Cfg_Msk, (uint32)LS2_Cfg);
  Field_Mod32(&BDRV->CTRL1.reg, BDRV_CTRL1_HS2_Cfg_Pos, BDRV_CTRL1_HS2_Cfg_Msk, (uint32)HS2_Cfg);
}
#endif


void BDRV_Clr_Sts(uint32 Sts_Bit)
{
  Field_Wrt32(&SCUPM->BDRV_ISCLR.reg, SCUPM_BDRV_ISCLR_Pos, SCUPM_BDRV_ISCLR_Msk, Sts_Bit);
  /* add an extra clear access in order to ensure the clear of           */
  /* the status flags is executed before the status flags are read again */
  Field_Wrt32(&SCUPM->BDRV_ISCLR.reg, SCUPM_BDRV_ISCLR_Pos, SCUPM_BDRV_ISCLR_Msk, Sts_Bit);
}


void BDRV_Set_Channel(TBdrv_Ch BDRV_Ch, TBdrv_Ch_Cfg Ch_Cfg)
{
#if (UC_SERIES == TLE987)

  if (BDRV_Ch < LS3)
  {
    Field_Mod32(&BDRV->CTRL1.reg, ((uint32)BDRV_Ch << 3u), (uint32)0x0F << ((uint32)BDRV_Ch << 3u), (uint32)Ch_Cfg);
  }
  else
  {
    Field_Mod32(&BDRV->CTRL2.reg, (((uint32)BDRV_Ch - 4u) << 3u), (uint32)0x0F << (((uint32)BDRV_Ch - 4u) << 3u), (uint32)Ch_Cfg);
  }

#else
  Field_Mod32(&BDRV->CTRL1.reg, ((uint32)BDRV_Ch << 3u), (uint32)0x0F << ((uint32)BDRV_Ch << 3u), (uint32)Ch_Cfg);
#endif
}


void BDRV_Set_Int_Channel(TBdrv_Ch BDRV_Ch, TBdrv_Ch_Int Ch_Int)
{
  /* set DS_Int (DS_Int bitfields start at LS1_DS_IE)*/
  Field_Mod32(&SCUPM->BDRV_IRQ_CTRL.reg, (uint32)BDRV_Ch, ((uint32)SCUPM_BDRV_IRQ_CTRL_LS1_DS_IE_Msk << (uint32)BDRV_Ch), (uint32)Ch_Int);
  /* set OC_Int (OC_Int bitfields start at LS1_OC_IE) */
  Field_Mod32(&SCUPM->BDRV_IRQ_CTRL.reg, (uint32)BDRV_Ch + SCUPM_BDRV_IRQ_CTRL_LS1_OC_IE_Pos, (SCUPM_BDRV_IRQ_CTRL_LS1_OC_IE_Msk << (uint32)BDRV_Ch), (uint32)Ch_Int >> 1u);

  /* enable BDRV interrupt node */
  if ((SCUPM->BDRV_IRQ_CTRL.reg & (uint32)BDRV_IRQ_BITS) != 0u)
  {
    NVIC_Node14_En();
  }
}


void BDRV_Set_DSM_Threshold(TBdrv_DSM_Threshold BDRV_Threshold)
{
  Field_Mod32(&BDRV->CTRL3.reg, BDRV_CTRL3_DSMONVTH_Pos, BDRV_CTRL3_DSMONVTH_Msk, (uint32)BDRV_Threshold);
}


TBDRV_Curr BDRV_getChrgCurrent_mA(void)
{
  uint8 u8_range;
  uint8 u8_current;
	
  u8_range = BDRV->CTRL3.bit.ICHARGEDIV2_N;
  u8_current = BDRV->CTRL3.bit.ICHARGE_TRIM;
  
  return (TBDRV_Curr)((u8_range << TBDRV_Curr_RANGE_POS) | u8_current);
}


void BDRV_setChrgCurrent_mA(TBDRV_Curr BDRV_Current)
{
  uint8 u8_range;
  uint8 u8_current;
	
  u8_range = (uint8)BDRV_Current >> TBDRV_Curr_RANGE_POS;
  u8_current = (uint8)BDRV_Current & TBDRV_Curr_CURRENT_MASK;

  BDRV->CTRL3.bit.ICHARGEDIV2_N = u8_range;
  BDRV->CTRL3.bit.ICHARGE_TRIM = u8_current;
}


TBDRV_Curr BDRV_getDischrgCurrent_mA(void)
{
  uint8 u8_range;
  uint8 u8_current;
  
  u8_range = BDRV->CTRL3.bit.IDISCHARGEDIV2_N;
  u8_current = BDRV->CTRL3.bit.IDISCHARGE_TRIM;
  
  return (TBDRV_Curr)((u8_range << TBDRV_Curr_RANGE_POS) | u8_current);
}


void BDRV_setDischrgCurrent_mA(TBDRV_Curr BDRV_Current)
{
  uint8 u8_range;
  uint8 u8_current;
	
  u8_range = (uint8)BDRV_Current >> TBDRV_Curr_RANGE_POS;
  u8_current = (uint8)BDRV_Current & TBDRV_Curr_CURRENT_MASK;

  BDRV->CTRL3.bit.IDISCHARGEDIV2_N = u8_range;
  BDRV->CTRL3.bit.IDISCHARGE_TRIM = u8_current;
}


#if (UC_SERIES == TLE986)
bool BDRV_Diag_OpenLoad(void)
{
  /* HSx_OC/LSx_OC and HSx_DS/LSx/DS bits */
  uint8 iBDRV_Int_En;
  bool bOpenLoad;
  uint32 lCTRL3;
  bOpenLoad = false;
  /* save bridge driver interrupt enable */
  iBDRV_Int_En = CPU->NVIC_ISER0.bit.Int_BDRV;
  /* disable bridge driver interrupt */
  NVIC_Node14_Dis();
  /* save CTRL3 register */
  lCTRL3 = BDRV->CTRL3.reg;
  /* set IDISCHARGE = 1, set DSMONVTH = 7 (2.25V) */
  BDRV_Set_DSM_Threshold(Threshold_2_00_V);
  BDRV->CTRL3.bit.IDISCHARGEDIV2_N = 0;
  BDRV_Set_Discharge_Current(Current_Min);
  /* check Phase 1 and 2 */
  BDRV_Set_Channel(LS1, Ch_En);
  BDRV_Set_Channel(LS2, Ch_En);
  BDRV_Set_Channel(HS1, Ch_En);
  BDRV_Set_Channel(HS2, Ch_En);
  /* enable HS1 DS-Current Source */
  BDRV_Set_Channel(HS1, Ch_DCS);
  /* Delay, give the DS-Current source some time to settle *
   * delay time depends on the attached motor              */
  Delay_us(800u);
  /* clear status flags */
  BDRV_Clr_Sts(BDRV_ISCLR_DS);

  /* check status flags */
  if ((SCUPM->BDRV_IS.reg & (uint32)BDRV_IRQ_BITS) != 0u)
  {
    bOpenLoad = true;
  }

  /* switch off all drivers */
  BDRV->CTRL1.reg = (uint32) 0;
  /* restore CTRL3 register */
  BDRV->CTRL3.reg = lCTRL3;

  /* restore interrupt */
  if (iBDRV_Int_En == (uint8)1)
  {
    NVIC_Node14_En();
  }

  return (bOpenLoad);
}
#endif

#if (UC_SERIES == TLE987)
bool BDRV_Diag_OpenLoad(void)
{
  uint8 bBDRV_Int_En;
  bool bOpenLoad;
  uint32 lCTRL3;
  bOpenLoad = false;
  /* save bridge driver interrupt enable */
  bBDRV_Int_En = CPU->NVIC_ISER0.bit.Int_BDRV;
  /* disable bridge driver interrupt */
  NVIC_Node14_Dis();
  /* save CTRL3 register */
  lCTRL3 = BDRV->CTRL3.reg;
  /* set IDISCHARGE = 1, set DSMONVTH = 7 (2.00V) */
  BDRV_Set_DSM_Threshold(Threshold_2_00_V);
  BDRV_setDischrgCurrent_mA(BDRV_Curr_HR_Min);
  /**********************************/
  /********* check Phase 1 **********/
  /* enable HS2/3 DS-Current Source */
  /**********************************/
  BDRV_Set_Bridge(Ch_En, Ch_En, Ch_En, Ch_DCS, Ch_En, Ch_DCS);
  /* Delay, give the DS-Current source some time to settle *
   * delay time depends on the attached motor              */
  Delay_us(800u);
  Delay_us(800u);
  /* clear status flags */
  BDRV_Clr_Sts(BDRV_ISCLR_DS);

  /* check status flags */
  if (BDRV_HS1_DS_Int_Sts() == 1u)
  {
    bOpenLoad = true;
  }

  /**********************************/
  /********* check Phase 2 **********/
  /* enable HS1/3 DS-Current Source */
  /**********************************/
  BDRV_Set_Bridge(Ch_En, Ch_DCS, Ch_En, Ch_En, Ch_En, Ch_DCS);
  /* Delay, give the DS-Current source some time to settle *
   * delay time depends on the attached motor              */
  Delay_us(800u);
  Delay_us(800u);
  /* clear status flags */
  BDRV_Clr_Sts(BDRV_ISCLR_DS);

  if (BDRV_HS2_DS_Int_Sts() == 1u)
  {
    bOpenLoad = true;
  }

  /**********************************/
  /********* check Phase 3 **********/
  /* enable HS1/2 DS-Current Source */
  /**********************************/
  BDRV_Set_Bridge(Ch_En, Ch_DCS, Ch_En, Ch_DCS, Ch_En, Ch_En);
  /* Delay, give the DS-Current source some time to settle *
   * delay time depends on the attached motor              */
  Delay_us(800u);
  Delay_us(800u);
  /* clear status flags */
  BDRV_Clr_Sts(BDRV_ISCLR_DS);

  if (BDRV_HS3_DS_Int_Sts() == 1u)
  {
    bOpenLoad = true;
  }

  /* switch off all drivers */
  BDRV->CTRL1.reg = (uint32)0;
  BDRV->CTRL2.reg = (uint32)0;
  /* restore CTRL3 register */
  BDRV->CTRL3.reg = lCTRL3;

  /* restore interrupt */
  if (bBDRV_Int_En == (uint8)1)
  {
    NVIC_Node14_En();
  }

  return (bOpenLoad);
}
#endif


#if (UC_SERIES == TLE986)
TBDRV_Off_Diag BDRV_Off_Diagnosis(void)
{
  TBDRV_Off_Diag res;
  uint8 iBDRV_Int_En;
  uint32 lCTRL3;
  res.GlobFailSts = false;
  res.Phase1 = Ch_Ok;
  res.Phase2 = Ch_Ok;
  /* save bridge driver interrupt enable */
  iBDRV_Int_En = CPU->NVIC_ISER0.bit.Int_BDRV;
  /* disable bridge driver interrupt */
  NVIC_Node14_Dis();
  /* save CTRL3 register */
  lCTRL3 = BDRV->CTRL3.reg;
  BDRV_Set_Bridge(Ch_En, Ch_En, Ch_En, Ch_En);
  /* set IDISCHARGE = 1, set DSMONVTH = 0 (0.25V) */
  BDRV_Set_DSM_Threshold(Threshold_0_25_V);
  BDRV->CTRL3.bit.IDISCHARGEDIV2_N = 0;
  BDRV_Set_Discharge_Current(Current_Min);
  /* enable diagnostic current source on all four drivers */
  BDRV_Set_Bridge(Ch_DCS, Ch_DCS, Ch_DCS, Ch_DCS);
  /* Delay, give the DS-Current source some time to settle *
   * delay time depends on the attached motor              */
  Delay_us(800u);
  /* clear status flags */
  BDRV_Clr_Sts(BDRV_IRQ_BITS);

  /* check status flags */
  if ((SCUPM->BDRV_IS.reg & (uint32)BDRV_DS_STS_BITS) != 0u)
  {
    res.GlobFailSts = true;

    if (BDRV_HS1_DS_Int_Sts() == 1u)
    {
      res.Phase1 = Ch_Short_to_VBat;
    }

    if (BDRV_LS1_DS_Int_Sts() == 1u)
    {
      res.Phase1 = Ch_Short_to_Gnd;
    }

    if (BDRV_HS2_DS_Int_Sts() == 1u)
    {
      res.Phase2 = Ch_Short_to_VBat;
    }

    if (BDRV_LS2_DS_Int_Sts() == 1u)
    {
      res.Phase2 = Ch_Short_to_Gnd;
    }
  }

  /* switch off all drivers */
  BDRV->CTRL1.reg = (uint32) 0;
  /* restore CTRL3 register */
  BDRV->CTRL3.reg = lCTRL3;

  /* restore interrupt */
  if (iBDRV_Int_En == (uint8)1)
  {
    NVIC_Node14_En();
  }

  return (res);
}
#endif

#if (UC_SERIES == TLE987)
TBDRV_Off_Diag BDRV_Off_Diagnosis(void)
{
  TBDRV_Off_Diag res;
  uint8 iBDRV_Int_En;
  uint32 lCTRL3;
  res.GlobFailSts = false;
  res.Phase1 = Ch_Ok;
  res.Phase2 = Ch_Ok;
  res.Phase3 = Ch_Ok;
  /* save bridge driver interrupt enable */
  iBDRV_Int_En = CPU->NVIC_ISER0.bit.Int_BDRV;
  /* disable bridge driver interrupt */
  NVIC_Node14_Dis();
  /* save CTRL3 register */
  lCTRL3 = BDRV->CTRL3.reg;
  BDRV_Set_Bridge(Ch_En, Ch_En, Ch_En, Ch_En, Ch_En, Ch_En);
  /* set IDISCHARGE = 1, set DSMONVTH = 0 (0.25V) */
  BDRV_Set_DSM_Threshold(Threshold_0_25_V);
  BDRV_setDischrgCurrent_mA(BDRV_Curr_HR_Min);
  /* enable diagnostic current source on all four drivers */
  BDRV_Set_Bridge(Ch_DCS, Ch_DCS, Ch_DCS, Ch_DCS, Ch_DCS, Ch_DCS);
  /* Delay, give the DS-Current source some time to settle *
   * delay time depends on the attached motor              */
  Delay_us(800u);
  /* clear status flags */
  BDRV_Clr_Sts(BDRV_DS_STS_BITS);

  /* check status flags */
  if ((SCUPM->BDRV_IS.reg & (uint32)BDRV_DS_STS_BITS) != 0u)
  {
    res.GlobFailSts = true;

    if (BDRV_HS1_DS_Int_Sts() == 1u)
    {
      res.Phase1 = Ch_Short_to_VBat;
    }

    if (BDRV_LS1_DS_Int_Sts() == 1u)
    {
      res.Phase1 = Ch_Short_to_Gnd;
    }

    if (BDRV_HS2_DS_Int_Sts() == 1u)
    {
      res.Phase2 = Ch_Short_to_VBat;
    }

    if (BDRV_LS2_DS_Int_Sts() == 1u)
    {
      res.Phase2 = Ch_Short_to_Gnd;
    }

    if (BDRV_HS3_DS_Int_Sts() == 1u)
    {
      res.Phase3 = Ch_Short_to_VBat;
    }

    if (BDRV_LS3_DS_Int_Sts() == 1u)
    {
      res.Phase3 = Ch_Short_to_Gnd;
    }
  }

  /* switch off all drivers */
  BDRV->CTRL1.reg = (uint32) 0;
  /* restore CTRL3 register */
  BDRV->CTRL3.reg = lCTRL3;

  /* restore interrupt */
  if (iBDRV_Int_En == (uint8)1)
  {
    NVIC_Node14_En();
  }

  return (res);
}
#endif
