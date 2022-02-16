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
**                             Author(s) Identity                             **
********************************************************************************
** Initials     Name                                                          **
** ---------------------------------------------------------------------------**
** BG           Blandine Guillot                                              **
*******************************************************************************/

/*******************************************************************************
**                          Revision Control History                          **
********************************************************************************
** V1.0.0: 2020-04-15, BG:   Initial version of revision history              **
*******************************************************************************/

#include "Emo_RAM.h"
#include "foc_defines.h"

/*******************************************************************************
**                 Global Constant Definitions to be changed                  **
*******************************************************************************/

const TEmo_Focpar_Cfg Emo_Focpar_Cfg =
{
  /* Rshunt */
  (float) FOC_R_SHUNT,
  /* NominalCurrent A*/
  (float) FOC_NOM_CUR,
  /* PWM_Frequency */
  (float) FOC_PWM_FREQ,
  /* PhaseRes - Phase resistance Ohm */
  (float) FOC_R_PHASE,
  /* PhaseInd - Phase inductance H*/
  (float) (FOC_L_PHASE),
  /* Speedcontroller Kp */
  (uint16) FOC_SPEED_KP,
  /* Speedcontroller Ki */
  (uint16) FOC_SPEED_KI,
  /* MaxRefCurr in A*/
  (float) FOC_MAX_POS_REF_CUR,
  /* MinRefCurr in A*/
  (float) FOC_MAX_NEG_REF_CUR,
  /* MaxRefStartCurr in A*/
  (float) FOC_MIN_POS_REF_CUR,
  /* MinRefStartCurr in A*/
  (float) FOC_MIN_NEG_REF_CUR,
  /*Speedlevel for MaxStartCurrent*/
  (float) FOC_MAX_CUR_SPEED,
  /*Speedlevel for MinStartCurrent*/
  (float) FOC_MIN_CUR_SPEED,
  /* Time constant for speed filter in s*/
  (float) FOC_SPEED_FILT_TIME,
  /* reserved */
  (float) FOC_ESTFLUX_FILT_TIME,
  /* reserved */
  (uint16)0,
  /* Polpaarzahl  */
  /* Range: 1..32 */
  (uint16)FOC_POLE_PAIRS,
  /*Start Voltage in V */
  //(float) FOC_START_VOLT,
  /* Start Current in A */
  (float) FOC_START_CUR,
  /*Time for Speed zero in s */
  (float) FOC_ZERO_VEC_TIME,
  /* Max Speed for Start in 1/rpm */
  (float) FOC_END_START_SPEED,
  /* Start Speed SlewRate in 1/rpm/s */
  (float) FOC_START_ACCEL,
  /*Enable Start width Frequenz=0 */
  (uint16) FOC_START_FREQ_ZERO,
  /*Speed level switch on */
  (float) FOC_SWITCH_ON_SPEED,
  /*AdjustmCurrentControl  0.1 .. 1.0 */
  (float) FOC_CUR_ADJUST,
  /* Maximum Speed */
  (float) FOC_MAX_SPEED,
};/* End of Emo_Focpar_Cfg */

