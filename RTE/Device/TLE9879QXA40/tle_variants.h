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
 * \file     tle_variants.h
 *
 * \brief    Device specific memory layout defines
 *
 * \version  V0.2.1
 * \date     24. Feb 2021
 */

/*******************************************************************************
**                             Author(s) Identity                             **
********************************************************************************
** Initials     Name                                                          **
** ---------------------------------------------------------------------------**
** DM           Daniel Mysliwitz                                              **
** JO           Julia Ott                                                     **
** BG           Blandine Guillot                                              **
*******************************************************************************/

/*******************************************************************************
**                          Revision Control History                          **
********************************************************************************
** V0.1.0: 2018-12-10, JO:   Initial version                                  **
** V0.1.1: 2019-02-04, DM:   sNADStart defined to be ARMCC v6 compliant       **
** V0.1.2: 2020-04-15, BG:   Updated revision history format                  **
** V0.1.3: 2020-07-21, BG:   EP-439: Formatted .h/.c files                    **
** V0.2.0: 2020-10-05, JO:   EP-437: Added support for devices TLE9877QTW40,  **
**                           TLE9879QTW40, TLE9872QXA40, TLE9872QTW40,        **
**                           and TLE9872-2QXA40                               **
** V0.2.1: 2021-02-24, BG:   EP-175: Added missing RTE_DEVICE_BF_STEP for     **
**                           TLE9872QTW40, TLE9872QXA40, TLE9872_2QXA40,      **
**                           TLE9877QTW40, TLE9879QTW40                       **
*******************************************************************************/

#ifndef _TLE_VARIANTS_H
#define _TLE_VARIANTS_H

/* Family definitions  */
#define TLE98      (98)

/* Series definitions  */
#define TLE984     (984)
#define TLE985     (985)
#define TLE986     (986)
#define TLE987     (987)

/* Device definitions  */
#define TLE9871    (9871)
#define TLE9873    (9873)
#define TLE9877    (9877)
#define TLE9879    (9879)

/* Package definitions */
#define BGA144     (1)
#define LQFP144    (2)
#define LQFP100    (3)
#define BGA64      (4)
#define LQFP64     (5)
#define VQFN48     (6)
#define TSSOP38    (7)
#define TSSOP28    (8)
#define TSSOP16    (9)
#define VQFN24     (10)
#define VQFN40     (11)
#define TQFP48     (12)


#if defined(TLE9871QXA20)
  #define UC_FAMILY       TLE98
  #define UC_SERIES       TLE987
  #define UC_DEVICE       TLE9871
  #define UC_PACKAGE      VQFN48
  #define UC_FLASH        (36UL)
  #define ProgFlashSize   (0x8000U)
  #define RAMSize         (0xC00U)
  #define sNADStart       ".ARM.__at_0x11007FFC"

#elif defined(TLE9872QTW40)
  #define UC_FAMILY       TLE98
  #define UC_SERIES       TLE987
  #define UC_DEVICE       TLE9879
  #define UC_PACKAGE      TQFP48
  #define UC_FLASH        (256UL)
  #define ProgFlashSize   (0x3F000U)
  #define RAMSize         (0x2000U)
  #define sNADStart       ".ARM.__at_0x1103EFFC"
  #define RTE_DEVICE_BF_STEP

#elif defined(TLE9872QXA40)
  #define UC_FAMILY       TLE98
  #define UC_SERIES       TLE987
  #define UC_DEVICE       TLE9879
  #define UC_PACKAGE      VQFN48
  #define UC_FLASH        (256UL)
  #define ProgFlashSize   (0x3F000U)
  #define RAMSize         (0x2000U)
  #define sNADStart       ".ARM.__at_0x1103EFFC"
  #define RTE_DEVICE_BF_STEP

#elif defined(TLE9872_2QXA40)
  #define UC_FAMILY       TLE98
  #define UC_SERIES       TLE987
  #define UC_DEVICE       TLE9879
  #define UC_PACKAGE      VQFN48
  #define UC_FLASH        (256UL)
  #define ProgFlashSize   (0x3F000U)
  #define RAMSize         (0x2000U)
  #define sNADStart       ".ARM.__at_0x1103EFFC"
  #define RTE_DEVICE_BF_STEP

#elif defined(TLE9873QXW40)
  #define UC_FAMILY       TLE98
  #define UC_SERIES       TLE987
  #define UC_DEVICE       TLE9873
  #define UC_PACKAGE      VQFN48
  #define UC_FLASH        (48UL)
  #define ProgFlashSize   (0xB000U)
  #define RAMSize         (0xC00U)
  #define sNADStart       ".ARM.__at_0x1100AFFC"
  #define RTE_DEVICE_BF_STEP

#elif defined(TLE9877QTW40)
  #define UC_FAMILY       TLE98
  #define UC_SERIES       TLE987
  #define UC_DEVICE       TLE9877
  #define UC_PACKAGE      TQFP48
  #define UC_FLASH        (64UL)
  #define ProgFlashSize   (0xF000U)
  #define RAMSize         (0x1800U)
  #define sNADStart       ".ARM.__at_0x1100EFFC"
  #define RTE_DEVICE_BF_STEP

#elif defined(TLE9877QXA20)
  #define UC_FAMILY       TLE98
  #define UC_SERIES       TLE987
  #define UC_DEVICE       TLE9877
  #define UC_PACKAGE      VQFN48
  #define UC_FLASH        (64UL)
  #define ProgFlashSize   (0xF000U)
  #define RAMSize         (0x1800U)
  #define sNADStart       ".ARM.__at_0x1100EFFC"

#elif defined(TLE9877QXA40)
  #define UC_FAMILY       TLE98
  #define UC_SERIES       TLE987
  #define UC_DEVICE       TLE9877
  #define UC_PACKAGE      VQFN48
  #define UC_FLASH        (64UL)
  #define ProgFlashSize   (0xF000U)
  #define RAMSize         (0x1800U)
  #define sNADStart       ".ARM.__at_0x1100EFFC"

#elif defined(TLE9877QXW40)
  #define UC_FAMILY       TLE98
  #define UC_SERIES       TLE987
  #define UC_DEVICE       TLE9877
  #define UC_PACKAGE      VQFN48
  #define UC_FLASH        (64UL)
  #define ProgFlashSize   (0xF000U)
  #define RAMSize         (0x1800U)
  #define sNADStart       ".ARM.__at_0x1100EFFC"
  #define RTE_DEVICE_BF_STEP

#elif defined(TLE9879QTW40)
  #define UC_FAMILY       TLE98
  #define UC_SERIES       TLE987
  #define UC_DEVICE       TLE9879
  #define UC_PACKAGE      TQFP48
  #define UC_FLASH        (128UL)
  #define ProgFlashSize   (0x1F000U)
  #define RAMSize         (0x1800U)
  #define sNADStart       ".ARM.__at_0x1101EFFC"
  #define RTE_DEVICE_BF_STEP

#elif defined(TLE9879QXA20)
  #define UC_FAMILY       TLE98
  #define UC_SERIES       TLE987
  #define UC_DEVICE       TLE9879
  #define UC_PACKAGE      VQFN48
  #define UC_FLASH        (128UL)
  #define ProgFlashSize   (0x1F000U)
  #define RAMSize         (0x1800U)
  #define sNADStart       ".ARM.__at_0x1101EFFC"

#elif defined(TLE9879QXA40)
  #define UC_FAMILY       TLE98
  #define UC_SERIES       TLE987
  #define UC_DEVICE       TLE9879
  #define UC_PACKAGE      VQFN48
  #define UC_FLASH        (128UL)
  #define ProgFlashSize   (0x1F000U)
  #define RAMSize         (0x1800U)
  #define sNADStart       ".ARM.__at_0x1101EFFC"

#elif defined(TLE9879QXW40)
  #define UC_FAMILY       TLE98
  #define UC_SERIES       TLE987
  #define UC_DEVICE       TLE9879
  #define UC_PACKAGE      VQFN48
  #define UC_FLASH        (128UL)
  #define ProgFlashSize   (0x1F000U)
  #define RAMSize         (0x1800U)
  #define sNADStart       ".ARM.__at_0x1101EFFC"
  #define RTE_DEVICE_BF_STEP

#elif defined(TLE9879_2QXA40)
  #define UC_FAMILY       TLE98
  #define UC_SERIES       TLE987
  #define UC_DEVICE       TLE9879
  #define UC_PACKAGE      VQFN48
  #define UC_FLASH        (128UL)
  #define ProgFlashSize   (0x1F000U)
  #define RAMSize         (0x1800U)
  #define sNADStart       ".ARM.__at_0x1101EFFC"
  #define RTE_DEVICE_BF_STEP

#else
  #error "tle_device.h: device not supported"
#endif
/*----------------------------------------------------------------------------
  Define Memory
 *----------------------------------------------------------------------------*/
#define ProgFlashStart  (0x11000000U)      /* Start Address of the flash      */
#define DataFlashStart  (ProgFlashStart + ProgFlashSize)
#define DataFlashSize   (0x1000U)          /* 4KB Data Flash                  */
#define NACStart        (DataFlashStart - 4U)
#define NADStart        (DataFlashStart - 2U)
#define RAMStart        (0x18000000UL)     /* Start Address of the SRAM       */

#if (UC_SERIES == 987)
  #include "tle987x.h"
#endif

#endif
