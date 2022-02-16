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
 * \file     system_tle987x.h
 *
 * \brief    System file for TLE987x
 *
 * \version  V0.4.8
 * \date     15. Jun 2021
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
** V0.0.2: 2017-11-10, DM:   Latest system_tle987x.h version                  **
** V0.4.0: 2017-11-10, DM:   Latest system_tle987x.c version                  **
** V0.4.1: 2018-12-05, DM:   system_tle987x.h, system_tle987x.c revisions     **
**                           merged                                           **
** V0.4.2: 2019-02-04, DM:   NAC/NAD pointer modified to be ARMCC v6 compliant**
** V0.4.3: 2019-09-13, JO:   Corrected filename in Revision Control History   **
** V0.4.4: 2020-04-15, BG:   Updated revision history format                  **
** V0.4.5: 2020-07-14, JO:   Added #include "system_tle987x.h" to             **
**                           system_tle987x.c                                 **
** V0.4.6: 2020-07-21, BG:   EP-439: Formatted .h/.c files                    **
** V0.4.7: 2021-05-28, BG:   EP-175: Added compatibility with IAR compiler    **
** V0.4.8: 2021-06-15, JO:   EP-840: Fixed NACNAD placement when using ARMCC  **
**                           v6 and LTO by adding attribute used              **
**                           Added #error Unsupported compiler! in case no    **
**                           supported compiler define is found               **
*******************************************************************************/

#ifndef __SYSTEM_TLE987x_H
#define __SYSTEM_TLE987x_H

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern uint32 SystemFrequency;
extern const uint32 p_NACNAD;

/** \brief Initialize System, clock and watchdog1.
 */
void SystemInit (void);

#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_TLE987x_H */
