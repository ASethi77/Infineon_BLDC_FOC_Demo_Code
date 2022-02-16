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
#include "ccu6.h"

/*******************************************************************************
**                         Global Function Definitions                        **
*******************************************************************************/
/** \brief Initializes the CCU6 module.
 *
 * \param None
 * \return None
 *
 * \ingroup drv_api
 */
void CCU6_Init(void)
{
  CCU6->TCTR0.reg = (uint16) CCU6_TCTR0;
  CCU6->T12PR.reg = (uint16) CCU6_T12PR;
  CCU6->T13PR.reg = (uint16) CCU6_T13PR;
  CCU6->T12DTC.reg = (uint16) CCU6_T12DTC;
  CCU6->CC60SR.reg = (uint16) CCU6_CC60SR;
  CCU6->CC61SR.reg = (uint16) CCU6_CC61SR;
  CCU6->CC62SR.reg = (uint16) CCU6_CC62SR;
  CCU6->CC63SR.reg = (uint16) CCU6_CC63SR;
  CCU6->TCTR2.reg = (uint16) CCU6_TCTR2;
  CCU6->TRPCTR.reg = (uint16) CCU6_TRPCTR;
  CCU6->MODCTR.reg = (uint16) CCU6_MODCTR;
  CCU6->MCMCTR.reg = (uint16) CCU6_MCMCTR;
  CCU6->T12MSEL.reg = (uint16) CCU6_T12MSEL;
  CCU6->PSLR.reg = (uint16) CCU6_PSLR;
  CCU6->INP.reg = (uint16) CCU6_INP;
  CCU6->IEN.reg = (uint16) CCU6_IEN;
  CCU6->CMPSTAT.reg = (uint16) CCU6_CMPSTAT;
  CCU6->PISEL0.reg = (uint16) CCU6_PISEL0;
  CCU6->PISEL2.reg = (uint16) CCU6_PISEL2;
  CCU6_T12_Str_En();
  CCU6_T13_Str_En();
}
