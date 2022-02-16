/*
 ***********************************************************************************************************************
 *
 * Copyright (c) 2017, Infineon Technologies AG
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
 * \file     sfr_access.h
 *
 * \brief    SFR low level access library
 *
 * \version  V0.1.2
 * \date     21. Jul 2020
 *
 * \note     This File is MISRA compliant.
 *
 */

/*******************************************************************************
**                             Author(s) Identity                             **
********************************************************************************
** Initials     Name                                                          **
** ---------------------------------------------------------------------------**
** DM           Daniel Mysliwitz                                              **
** BG           Blandine Guillot                                              **
*******************************************************************************/

/*******************************************************************************
**                          Revision Control History                          **
********************************************************************************
** V0.1.0: 2018-11-26, DM:   Initial version                                  **
** V0.1.1: 2020-04-15, BG:   Updated revision history format                  **
** V0.1.2: 2020-07-21, BG:   EP-439: Formatted .h/.c files                    **
*******************************************************************************/

#ifndef sfr_access_h
#define sfr_access_h

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "types.h"

/*******************************************************************************
**                         Prototypes for Unit testing                        **
*******************************************************************************/
#ifdef TESTING
/* macros to access bit fields of a register */
void Field_Wrt8(volatile uint8 *reg, uint8 pos, uint8 msk, uint8 val);
void Field_Wrt8all(volatile uint8 *reg, uint8 val);
void Field_Wrt16(volatile uint16 *reg, uint16 pos, uint16 msk, uint16 val);
void Field_Wrt32(volatile uint32 *reg, uint32 pos, uint32 msk, uint32 val);
void Field_Mod8(volatile uint8 *reg, uint8 pos, uint8 msk, uint8 val);
void Field_Mod16(volatile uint16 *reg, uint16 pos, uint16 msk, uint16 val);
void Field_Mod32(volatile uint32 *reg, uint32 pos, uint32 msk, uint32 val);
void Field_Inv8(volatile uint8 *reg, uint8 msk);
void Field_Inv16(volatile uint16 *reg, uint16 msk);
void Field_Inv32(volatile uint32 *reg, uint32 msk);
void Field_Clr8(volatile uint8 *reg, uint8 msk);
void Field_Clr16(volatile uint16 *reg, uint16 msk);
void Field_Clr32(volatile uint32 *reg, uint32 msk);
uint8 u1_Field_Rd8(const volatile uint8 *reg, uint8 pos, uint8 msk);
uint8 u1_Field_Rd16(const volatile uint16 *reg, uint16 pos, uint16 msk);
uint8 u1_Field_Rd32(const volatile uint32 *reg, uint32 pos, uint32 msk);
uint8 u8_Field_Rd8(const volatile uint8 *reg, uint8 pos, uint8 msk);
uint8 u8_Field_Rd16(const volatile uint16 *reg, uint16 pos, uint16 msk);
uint8 u8_Field_Rd32(const volatile uint32 *reg, uint32 pos, uint32 msk);
uint16 u16_Field_Rd16(const volatile uint16 *reg, uint16 pos, uint16 msk);
uint16 u16_Field_Rd32(const volatile uint32 *reg, uint32 pos, uint32 msk);
uint32 u32_Field_Rd32(const volatile uint32 *reg, uint32 pos, uint32 msk);

#else /* #ifdef TESTING */

/*******************************************************************************
**                                 Prototypes                                 **
*******************************************************************************/
/* macros to access a whole register */
/* set a 8-bit register directly, write (no read-mod-write) */
/** \brief This function writes an 8-bit register directly, no mask/position needed.
 * \note This is a direct write, no read-modify-write.
 *
 * \param reg pointer to an 8-bit register
 * \param val value to be written
 * \ingroup types_api
 */
INLINE void Field_Wrt8all(volatile uint8 *reg, uint8 val);


/* macros to access bit fields of a register */
/* set a bit field directly, write (no read-mod-write) */
/** \brief This function writes a bit field in a 8-bit register.
 * \note This is a direct write, no read-modify-write.
 *
 * \param reg pointer to an 8-bit register
 * \param msk mask of the bit field within the register
 * \param pos bit position of the bit field within the register
 * \param val value to be written to bitfield
 * \ingroup types_api
 */
INLINE void Field_Wrt8(volatile uint8 *reg, uint8 pos, uint8 msk, uint8 val);

/** \brief This function writes a bit field in a 16-bit register.
 * \note This is a direct write, no read-modify-write.
 *
 * \param reg pointer to an 16-bit register
 * \param msk mask of the bit field within the register
 * \param pos bit position of the bit field within the register
 * \param val value to be written to bitfield
 * \ingroup types_api
 */
INLINE void Field_Wrt16(volatile uint16 *reg, uint16 pos, uint16 msk, uint16 val);

/** \brief This function writes a bit field in a 32-bit register.
 * \note This is a direct write, no read-modify-write.
 *
 * \param reg pointer to an 32-bit register
 * \param msk mask of the bit field within the register
 * \param pos bit position of the bit field within the register
 * \param val value to be written to bitfield
 * \ingroup types_api
 */
INLINE void Field_Wrt32(volatile uint32 *reg, uint32 pos, uint32 msk, uint32 val);

/* set a bitfield by using read-mod-write */
/** \brief This function writes a bit field in a 8-bit register.
 * \note This is a read-modify-write access.
 *
 * \param reg pointer to an 8-bit register
 * \param msk mask of the bit field within the register
 * \param pos bit position of the bit field within the register
 * \param val value to be written to bitfield
 * \ingroup types_api
 */
INLINE void Field_Mod8(volatile uint8 *reg, uint8 pos, uint8 msk, uint8 val);

/** \brief This function writes a bit field in a 16-bit register.
 * \note This is a read-modify-write access.
 *
 * \param reg pointer to an 16-bit register
 * \param msk mask of the bit field within the register
 * \param pos bit position of the bit field within the register
 * \param val value to be written to bitfield
 * \ingroup types_api
 */
INLINE void Field_Mod16(volatile uint16 *reg, uint16 pos, uint16 msk, uint16 val);

/** \brief This function writes a bit field in a 32-bit register.
 * \note This is a read-modify-write access.
 *
 * \param reg pointer to an 32-bit register
 * \param msk mask of the bit field within the register
 * \param pos bit position of the bit field within the register
 * \param val value to be written to bitfield
 * \ingroup types_api
 */
INLINE void Field_Mod32(volatile uint32 *reg, uint32 pos, uint32 msk, uint32 val);

/* invert the setting of a bitfield, read-inv-write */
/** \brief This function inverts a bit field in a 8-bit register.
 * \note This is a read-invert-write access.
 *
 * \param reg pointer to an 8-bit register
 * \param msk mask of the bit field within the register
 * \ingroup types_api
 */
INLINE void Field_Inv8(volatile uint8 *reg, uint8 msk);

/** \brief This function inverts a bit field in a 16-bit register.
 * \note This is a read-invert-write access.
 *
 * \param reg pointer to an 16-bit register
 * \param msk mask of the bit field within the register
 * \ingroup types_api
 */
INLINE void Field_Inv16(volatile uint16 *reg, uint16 msk);

/** \brief This function inverts a bit field in a 32-bit register.
 * \note This is a read-invert-write access.
 *
 * \param reg pointer to an 32-bit register
 * \param msk mask of the bit field within the register
 * \ingroup types_api
 */
INLINE void Field_Inv32(volatile uint32 *reg, uint32 msk);

/* write a bitfield to '0', read-write0 */
/** \brief This function clears a bit field in a 8-bit register.
 * \note This is a read-modify-write access.
 *
 * \param reg pointer to an 8-bit register
 * \param msk mask of the bit field within the register
 * \ingroup types_api
 */
INLINE void Field_Clr8(volatile uint8 *reg, uint8 msk);

/* write a bitfield to '0', read-write0 */
/** \brief This function clears a bit field in a 16-bit register.
 * \note This is a read-modify-write access.
 *
 * \param reg pointer to an 16-bit register
 * \param msk mask of the bit field within the register
 * \ingroup types_api
 */
INLINE void Field_Clr16(volatile uint16 *reg, uint16 msk);

/* write a bitfield to '0', read-write0 */
/** \brief This function clears a bit field in a 32-bit register.
 * \note This is a read-modify-write access.
 *
 * \param reg pointer to an 32-bit register
 * \param msk mask of the bit field within the register
 * \ingroup types_api
 */
INLINE void Field_Clr32(volatile uint32 *reg, uint32 msk);

/* read bitffield */

/** \brief This function reads a 1-bit field of a 8-bit register.
 *
 * \param reg pointer to a register
 * \param msk mask of the bit field within the register
 * \param pos bit position of the bit field within the register
 * \return bool
 * \ingroup types_api
 */
INLINE uint8 u1_Field_Rd8(const volatile uint8 *reg, uint8 pos, uint8 msk);

/** \brief This function reads a 1-bit field of a 16-bit register.
 *
 * \param reg pointer to a register
 * \param msk mask of the bit field within the register
 * \param pos bit position of the bit field within the register
 * \return bool
 * \ingroup types_api
 */
INLINE uint8 u1_Field_Rd16(const volatile uint16 *reg, uint16 pos, uint16 msk);

/** \brief This function reads a 1-bit field of a 32-bit register.
 *
 * \param reg pointer to a register
 * \param msk mask of the bit field within the register
 * \param pos bit position of the bit field within the register
 * \return bool
 * \ingroup types_api
 */
INLINE uint8 u1_Field_Rd32(const volatile uint32 *reg, uint32 pos, uint32 msk);

/** \brief This function reads a 8-bit field of a 8-bit register.
 *
 * \param reg pointer to a register
 * \param msk mask of the bit field within the register
 * \param pos bit position of the bit field within the register
 * \return uint8
 * \ingroup types_api
 */
INLINE uint8 u8_Field_Rd8(const volatile uint8 *reg, uint8 pos, uint8 msk);

/** \brief This function reads a 8-bit field of a 16-bit register.
 *
 * \param reg pointer to a register
 * \param msk mask of the bit field within the register
 * \param pos bit position of the bit field within the register
 * \return uint8
 * \ingroup types_api
 */
INLINE uint8 u8_Field_Rd16(const volatile uint16 *reg, uint16 pos, uint16 msk);

/** \brief This function reads a 8-bit field of a 32-bit register.
 *
 * \param reg pointer to a register
 * \param msk mask of the bit field within the register
 * \param pos bit position of the bit field within the register
 * \return uint8
 * \ingroup types_api
 */
INLINE uint8 u8_Field_Rd32(const volatile uint32 *reg, uint32 pos, uint32 msk);

/** \brief This function reads a 16-bit field of a 16-bit register.
 *
 * \param reg pointer to a register
 * \param msk mask of the bit field within the register
 * \param pos bit position of the bit field within the register
 * \return uint16
 * \ingroup types_api
 */
INLINE uint16 u16_Field_Rd16(const volatile uint16 *reg, uint16 pos, uint16 msk);

/** \brief This function reads a 16-bit field of a 32-bit register.
 *
 * \param reg pointer to a register
 * \param msk mask of the bit field within the register
 * \param pos bit position of the bit field within the register
 * \return uint16
 * \ingroup types_api
 */
INLINE uint16 u16_Field_Rd32(const volatile uint32 *reg, uint32 pos, uint32 msk);

/** \brief This function reads a 32-bit field of a 32-bit register.
 *
 * \param reg pointer to a register
 * \param msk mask of the bit field within the register
 * \param pos bit position of the bit field within the register
 * \return uint32
 * \ingroup types_api
 */
INLINE uint32 u32_Field_Rd32(const volatile uint32 *reg, uint32 pos, uint32 msk);

/* Macro function body declarations */

INLINE void Field_Wrt8all(volatile uint8 *reg, uint8 val)
{
  (*reg = val);
}

INLINE void Field_Wrt8(volatile uint8 *reg, uint8 pos, uint8 msk, uint8 val)
{
  (*reg = (uint8)((uint32)val << pos) & (uint8)msk);
}

INLINE void Field_Wrt16(volatile uint16 *reg, uint16 pos, uint16 msk, uint16 val)
{
  (*reg = (uint16)((uint32)val << pos) & (uint16)msk);
}

INLINE void Field_Wrt32(volatile uint32 *reg, uint32 pos, uint32 msk, uint32 val)
{
  (*reg = ((uint32)val << pos) & (uint32)msk);
}

INLINE void Field_Mod8(volatile uint8 *reg, uint8 pos, uint8 msk, uint8 val)
{
  (*reg = (*reg & (uint8)~msk)  | (uint8)(((uint32)val << pos)  & (uint8)msk));
}

INLINE void Field_Mod16(volatile uint16 *reg, uint16 pos, uint16 msk, uint16 val)
{
  (*reg = (*reg & (uint16)~msk) | (uint16)(((uint32)val << pos) & (uint16)msk));
}

INLINE void Field_Mod32(volatile uint32 *reg, uint32 pos, uint32 msk, uint32 val)
{
  (*reg = (*reg & (uint32)~msk) | (uint32)(((uint32)val << pos) & (uint32)msk));
}

INLINE void Field_Inv8(volatile uint8 *reg, uint8 msk)
{
  (*reg = ((uint8) * reg ^ (uint8)msk));
}

INLINE void Field_Inv16(volatile uint16 *reg, uint16 msk)
{
  (*reg = ((uint16) * reg ^ (uint16)msk));
}

INLINE void Field_Inv32(volatile uint32 *reg, uint32 msk)
{
  (*reg = ((uint32) * reg ^ (uint32)msk));
}

INLINE void Field_Clr8(volatile uint8 *reg, uint8 msk)
{
  (*reg = (*reg & (uint8)~msk));
}

INLINE void Field_Clr16(volatile uint16 *reg, uint16 msk)
{
  (*reg = (*reg & (uint16)~msk));
}

INLINE void Field_Clr32(volatile uint32 *reg, uint32 msk)
{
  (*reg = (*reg & (uint32)~msk));
}

INLINE uint8 u1_Field_Rd8(const volatile uint8 *reg, uint8 pos, uint8 msk)
{
  return (((*reg & msk) >> pos) & 1u);
}

INLINE uint8 u1_Field_Rd16(const volatile uint16 *reg, uint16 pos, uint16 msk)
{
  return ((uint8)((*reg & msk) >> pos) & 1u);
}

INLINE uint8 u1_Field_Rd32(const volatile uint32 *reg, uint32 pos, uint32 msk)
{
  return ((uint8)((*reg & msk) >> pos) & 1u);
}

INLINE uint8 u8_Field_Rd8(const volatile uint8 *reg, uint8 pos, uint8 msk)
{
  return ((*reg & msk) >> pos);
}

INLINE uint8 u8_Field_Rd16(const volatile uint16 *reg, uint16 pos, uint16 msk)
{
  return ((uint8)((*reg & msk) >> pos));
}

INLINE uint8 u8_Field_Rd32(const volatile uint32 *reg, uint32 pos, uint32 msk)
{
  return ((uint8)((*reg & msk) >> pos));
}

INLINE uint16 u16_Field_Rd16(const volatile uint16 *reg, uint16 pos, uint16 msk)
{
  return ((*reg & msk) >> pos);
}

INLINE uint16 u16_Field_Rd32(const volatile uint32 *reg, uint32 pos, uint32 msk)
{
  return ((uint16)((*reg & msk) >> pos));
}

INLINE uint32 u32_Field_Rd32(const volatile uint32 *reg, uint32 pos, uint32 msk)
{
  return ((uint32)((*reg & msk) >> pos));
}
#endif /* TESTING */


#endif
