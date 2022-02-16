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
#include "port.h"
#include "port_defines.h"


/*******************************************************************************
**                         Global Function Definitions                        **
*******************************************************************************/

void PORT_Init(void)
{
  /* Initialize all ports */
#if(PORT_XML_VERSION < 10303)
  uint8 Value;
  /* Port 0 */
  PORT->P0_DIR.reg = (uint8) PORT_P0_DIR;
  PORT->P0_OD.reg = (uint8) PORT_P0_OD;
  /*lint complains in case PORT_P0_0_PUD is '0' */
  /* violation: Excessive shift value (precision 0 shifted right by 1) [MISRA Rule 38]*/
  Value  = (uint8) ((PORT_P0_0_PUD & 0x02u) >> 1u);
  Value |= (uint8) ((PORT_P0_1_PUD & 0x02u));
  Value |= (uint8) ((PORT_P0_2_PUD & 0x02u) << 1u);
  Value |= (uint8) ((PORT_P0_3_PUD & 0x02u) << 2u);
  Value |= (uint8) ((PORT_P0_4_PUD & 0x02u) << 3u);
  PORT->P0_PUDEN.reg = Value;
  Value  = (uint8) ((PORT_P0_0_PUD & 0x01u));
  Value |= (uint8) ((PORT_P0_1_PUD & 0x01u) << 1u);
  Value |= (uint8) ((PORT_P0_2_PUD & 0x01u) << 2u);
  Value |= (uint8) ((PORT_P0_3_PUD & 0x01u) << 3u);
  Value |= (uint8) ((PORT_P0_4_PUD & 0x01u) << 4u);
  PORT->P0_PUDSEL.reg = Value;
  Value  = (uint8) ((PORT_P0_0_ALT & 0x01u));
  Value |= (uint8) ((PORT_P0_1_ALT & 0x01u) << 1u);
  Value |= (uint8) ((PORT_P0_2_ALT & 0x01u) << 2u);
  Value |= (uint8) ((PORT_P0_3_ALT & 0x01u) << 3u);
  Value |= (uint8) ((PORT_P0_4_ALT & 0x01u) << 4u);
  PORT->P0_ALTSEL0.reg = Value;
  /*lint complains in case PORT_P0_0_ALT is '0' */
  /* violation: Excessive shift value (precision 0 shifted right by 1) [MISRA Rule 38]*/
  Value  = (uint8) ((PORT_P0_0_ALT & 0x02u) >> 1u);
  Value |= (uint8) ((PORT_P0_1_ALT & 0x02u));
  Value |= (uint8) ((PORT_P0_2_ALT & 0x02u) << 1u);
  Value |= (uint8) ((PORT_P0_3_ALT & 0x02u) << 2u);
  Value |= (uint8) ((PORT_P0_4_ALT & 0x02u) << 3u);
  PORT->P0_ALTSEL1.reg = Value;
  PORT->P0_DATA.reg = (uint8) PORT_P0_DATA;
  /* Port 1 */
  PORT->P1_DIR.reg = (uint8) PORT_P1_DIR;
  PORT->P1_OD.reg = (uint8) PORT_P1_OD;
  /*lint complains in case PORT_P1_0_PUD is '0' */
  /* violation: Excessive shift value (precision 0 shifted right by 1) [MISRA Rule 38]*/
  Value  = (uint8) ((PORT_P1_0_PUD & 0x02u) >> 1u);
  Value |= (uint8) ((PORT_P1_1_PUD & 0x02u));
  Value |= (uint8) ((PORT_P1_2_PUD & 0x02u) << 1u);
  Value |= (uint8) ((PORT_P1_3_PUD & 0x02u) << 2u);
  Value |= (uint8) ((PORT_P1_4_PUD & 0x02u) << 3u);
  PORT->P1_PUDEN.reg = Value;
  Value  = (uint8) ((PORT_P1_0_PUD & 0x01u));
  Value |= (uint8) ((PORT_P1_1_PUD & 0x01u) << 1u);
  Value |= (uint8) ((PORT_P1_2_PUD & 0x01u) << 2u);
  Value |= (uint8) ((PORT_P1_3_PUD & 0x01u) << 3u);
  Value |= (uint8) ((PORT_P1_4_PUD & 0x01u) << 4u);
  PORT->P1_PUDSEL.reg = Value;
  Value  = (uint8) ((PORT_P1_0_ALT & 0x01u));
  Value |= (uint8) ((PORT_P1_1_ALT & 0x01u) << 1u);
  Value |= (uint8) ((PORT_P1_2_ALT & 0x01u) << 2u);
  Value |= (uint8) ((PORT_P1_3_ALT & 0x01u) << 3u);
  Value |= (uint8) ((PORT_P1_4_ALT & 0x01u) << 4u);
  PORT->P1_ALTSEL0.reg = Value;
  /*lint complains in case PORT_P1_0_ALT is '0' */
  /* violation: Excessive shift value (precision 0 shifted right by 1) [MISRA Rule 38]*/
  Value  = (uint8) ((PORT_P1_0_ALT & 0x02u) >> 1u);
  Value |= (uint8) ((PORT_P1_1_ALT & 0x02u));
  Value |= (uint8) ((PORT_P1_2_ALT & 0x02u) << 1u);
  Value |= (uint8) ((PORT_P1_3_ALT & 0x02u) << 2u);
  Value |= (uint8) ((PORT_P1_4_ALT & 0x02u) << 3u);
  PORT->P1_ALTSEL1.reg = Value;
  PORT->P1_DATA.reg = (uint8) PORT_P1_DATA;
  /* Port 2 */
  PORT->P2_DIR.reg = (uint8) PORT_P2_DIR;
  /*lint complains in case PORT_P2_0_PUD is '0' */
  /* violation: Excessive shift value (precision 0 shifted right by 1) [MISRA Rule 38]*/
  Value  = (uint8) ((PORT_P2_0_PUD & 0x02u) >> 1u);
  Value |= (uint8) ((PORT_P2_1_PUD & 0x02u));
  Value |= (uint8) ((PORT_P2_2_PUD & 0x02u) << 1u);
  Value |= (uint8) ((PORT_P2_3_PUD & 0x02u) << 2u);
  Value |= (uint8) ((PORT_P2_4_PUD & 0x02u) << 3u);
  Value |= (uint8) ((PORT_P2_5_PUD & 0x02u) << 4u);
  Value |= (uint8) ((PORT_P2_7_PUD & 0x02u) << 6u);
  PORT->P2_PUDEN.reg = Value;
  Value  = (uint8) ((PORT_P2_0_PUD & 0x01u));
  Value |= (uint8) ((PORT_P2_1_PUD & 0x01u) << 1u);
  Value |= (uint8) ((PORT_P2_2_PUD & 0x01u) << 2u);
  Value |= (uint8) ((PORT_P2_3_PUD & 0x01u) << 3u);
  Value |= (uint8) ((PORT_P2_4_PUD & 0x01u) << 4u);
  Value |= (uint8) ((PORT_P2_5_PUD & 0x01u) << 5u);
  Value |= (uint8) ((PORT_P2_7_PUD & 0x01u) << 7u);
  PORT->P2_PUDSEL.reg = Value;
#else
  /* Port 0 */
  PORT->P0_DIR.reg = (uint8)PORT_P0_DIR;
  PORT->P0_OD.reg = (uint8)PORT_P0_OD;
  PORT->P0_PUDEN.reg = (uint8)PORT_P0_PUDEN;
  PORT->P0_PUDSEL.reg = (uint8)PORT_P0_PUDSEL;
  PORT->P0_ALTSEL0.reg = (uint8)PORT_P0_ALTSEL0;
  PORT->P0_ALTSEL1.reg = (uint8)PORT_P0_ALTSEL1;
  PORT->P0_DATA.reg = (uint8)PORT_P0_DATA;
  /* Port 1 */
  PORT->P1_DIR.reg = (uint8)PORT_P1_DIR;
  PORT->P1_OD.reg = (uint8)PORT_P1_OD;
  PORT->P1_PUDEN.reg = (uint8)PORT_P1_PUDEN;
  PORT->P1_PUDSEL.reg = (uint8)PORT_P1_PUDSEL;
  PORT->P1_ALTSEL0.reg = (uint8)PORT_P1_ALTSEL0;
  PORT->P1_ALTSEL1.reg = (uint8)PORT_P1_ALTSEL1;
  PORT->P1_DATA.reg = (uint8)PORT_P1_DATA;
  /* Port 2 */
  PORT->P2_DIR.reg = (uint8)PORT_P2_DIR;
  PORT->P2_PUDEN.reg = (uint8)PORT_P2_PUDEN;
  PORT->P2_PUDSEL.reg = (uint8)PORT_P2_PUDSEL;
#endif
}


void PORT_ChangePin(uint32 PortPin, uint32 Action)
{
  sint32 int_was_mask;
  volatile uint8 *pSfr;
  uint8 PinMask;
  uint8 PinPos;
  uint32 addr;
  uint16 idx;
  /* Pin pos */
  PinPos = (uint8)(PortPin & 0x7U);
  /* Pin mask = 1 shifted left by pin */
  PinMask = (uint8)(1U << PinPos);
  /* DATA pointer = address of P0_DATA + port * 8 */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45]*/
  addr = (uint32)&PORT->P0_DATA.reg;
  idx = (uint16)((PortPin >> 4U) << 3U);
  addr += idx;
  /* violation: cast from unsigned int to pointer [MISRA Rule 45]*/
  pSfr = (volatile uint8 *) addr;
  /* Change DATA register according to Action */
  int_was_mask = CMSIS_Irq_Dis();

  if (Action == PORT_ACTION_CLEAR)
  {
    Field_Clr8(pSfr, PinMask);
  }
  else if (Action == PORT_ACTION_SET)
  {
    Field_Mod8(pSfr, PinPos, PinMask, 1u);
  }
  else if (Action == PORT_ACTION_TOGGLE)
  {
    Field_Inv8(pSfr, PinMask);
  }
  else if (Action == PORT_ACTION_INPUT)
  {
    /* violation: cast from pointer to unsigned int [MISRA Rule 45]*/
    addr = (uint32)&PORT->P0_DIR.reg;
    idx = (uint16)((PortPin >> 4U) << 3U);
    addr += idx;
    /* violation: cast from unsigned int to pointer [MISRA Rule 45]*/
    pSfr = (volatile uint8 *) addr;
    Field_Clr8(pSfr, PinMask);
  }
  else /* (Action == PORT_ACTION_OUTPUT) */
  {
    /* violation: cast from pointer to unsigned int [MISRA Rule 45]*/
    addr = (uint32)&PORT->P0_DIR.reg;
    idx = (uint16)((PortPin >> 4U) << 3U);
    addr += idx;
    /* violation: cast from unsigned int to pointer [MISRA Rule 45]*/
    pSfr = (volatile uint8 *) addr;
    Field_Mod8(pSfr, PinPos, PinMask, 1u);
  }

  if (int_was_mask == 0)
  {
    CMSIS_Irq_En();
  }
} /* End of PORT_ChangePin */


uint8 PORT_ReadPin(uint32 PortPin)
{
  const volatile uint8 *pSfr;
  uint8 PinMask;
  uint8 PinPos;
  uint32 addr;
  uint16 idx;
  /* Pin pos */
  PinPos = (uint8)(PortPin & 0x7U);
  /* Pin mask = 1 shifted left by pin */
  PinMask = (uint8)(1U << PinPos);
  /* DATA pointer = address of P0_DATA + port * 8 */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45]*/
  addr = (uint32)&PORT->P0_DATA.reg;
  idx = (uint16)((PortPin >> 4U) << 3U);
  addr += idx;
  /* violation: cast from unsigned int to pointer [MISRA Rule 45]*/
  pSfr = (volatile uint8 *) addr;
  /* Read DATA register, shift right by pin and extract bit 0 */
  return (u8_Field_Rd8(pSfr, PinPos, PinMask) );
} /* End of PORT_ReadPin */


uint8 PORT_ReadPort(uint32 Port)
{
  const uint8 PortMsk[3] = {0x1F, 0x1F, 0x3D};
  const volatile uint8 *pSfr;
  uint32 addr;
  uint16 idx;
  /* DATA pointer = address of P0_DATA + port * 8 */
  /*: cast from pointer to unsigned int [MISRA Rule 45]*/
  addr = (uint32)&PORT->P0_DATA.reg;
  idx = (uint16)(Port << 3U);
  addr += idx;
  /* violation: cast from unsigned int to pointer [MISRA Rule 45]*/
  pSfr = (volatile uint8 *) addr;
  /* Read DATA register */
  //return *pSfr;
  return (u8_Field_Rd8(pSfr, 0, PortMsk[Port]));
} /* End of PORT_ReadPort */


void PORT_ChangePinAlt(uint32 PortPin, uint8 AltSel)
{
  sint32 int_was_mask;
  volatile uint8 *pSfr0, *pSfr1;
  uint8 PinMask;
  uint8 PinPos;
  uint32 addr;
  uint16 idx;
  /* Pin pos */
  PinPos = (uint8)(PortPin & 0x7U);
  /* Pin mask = 1 shifted left by pin */
  PinMask = (uint8)(1U << PinPos);
  /* DATA pointer = address of P0_DATA + port * 8 */
  /* violation: cast from pointer to unsigned int [MISRA Rule 45]*/
  addr = (uint32)&PORT->P0_ALTSEL0.reg;
  idx = (uint16)((PortPin >> 4U) << 3U);
  addr += idx;
  /* violation: cast from unsigned int to pointer [MISRA Rule 45]*/
  pSfr0 = (volatile uint8 *) addr;
  /* violation: cast from pointer to unsigned int [MISRA Rule 45]*/
  addr = (uint32)&PORT->P0_ALTSEL1.reg;
  idx = (uint16)((PortPin >> 4U) << 3U);
  addr += idx;
  /* violation: cast from unsigned int to pointer [MISRA Rule 45]*/
  pSfr1 = (volatile uint8 *) addr;
  /* Change DATA register according to Action */
  int_was_mask = CMSIS_Irq_Dis();
  Field_Mod8(pSfr0, PinPos, PinMask, (AltSel & 1u));
  Field_Mod8(pSfr1, PinPos, PinMask, ((AltSel >> 1u) & 1u));

  if (int_was_mask == 0)
  {
    CMSIS_Irq_En();
  }
} /* End of PORT_ChangePinAlt */
