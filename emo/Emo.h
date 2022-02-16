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

#ifndef EMO_CFG_H
#define EMO_CFG_H

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "tle_device.h"

/*******************************************************************************
**                   Global Macro Definitions to be changed                   **
*******************************************************************************/
/* CTRAP enable
 * Range: 0=disabled, 1=enabled */
#define EMO_CFG_CTRAP_ENABLED (0)

/* Scaling constant for FOC sinus table */
#define EMO_CFG_FOC_TABLE_SCALE (0.117553711)


/*******************************************************************************
**             Derived Global Macro Definitions not to be changed             **
*******************************************************************************/
/** \ingroup emo_type_definitions
 *  \brief TEmo_Status
 *  Types involved in the interrupt loop are placed here.
 */
typedef struct
{
  uint8 MotorState;               /**< \brief Motor state */
  uint16 MotorStartError;         /**<\brief Start Error bits */
} TEmo_Status;

extern TEmo_Status Emo_Status;

uint32 Emo_GetSpeed(void);
uint32 Emo_Init(void);
void Emo_SetRefSpeed(sint16 RefSpeed);
uint32 Emo_StartMotor(uint32 EnableBridge);
extern uint32 Emo_StopMotor(void);
void Emo_lInitFocPar(void);
void Emo_lInitFocVar(void);
__STATIC_INLINE uint32 Emo_GetMotorState(void);

/** \brief Returns the motor state.
 *
 * \param None
 * \return Motor state
 *
 * \ingroup emo_api
 */
__STATIC_INLINE uint32 Emo_GetMotorState(void)
{
  return (uint32)Emo_Status.MotorState;
}

#endif  /* EMO_CFG_H */


