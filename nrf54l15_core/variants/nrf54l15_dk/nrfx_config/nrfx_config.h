/*
 * Copyright (c) 2019 - 2025, Nordic Semiconductor ASA
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef NRFX_CONFIG_H__
#define NRFX_CONFIG_H__

#include <nrfx_config_common.h>

/* Place your configuration here */

// Enabled peripherals
#define NRFX_UARTE_ENABLED 1
#define NRFX_UARTE30_ENABLED 1
#define NRFX_SAADC_ENABLED 1
#define NRFX_CRACEN_ENABLED 1

// The following were defined to silence build issues in nrfx.
// The issues are probably a side effect from the fact that Arduino will
// try to build eveery single source file.
#ifndef NRFX_DPPI00_INST_IDX
#define NRFX_DPPI00_INST_IDX 0
#endif

#ifndef NRFX_DPPI10_INST_IDX
#define NRFX_DPPI10_INST_IDX 0
#endif

#ifndef NRFX_DPPI20_INST_IDX
#define NRFX_DPPI20_INST_IDX 0
#endif

#ifndef NRFX_DPPI30_INST_IDX
#define NRFX_DPPI30_INST_IDX 0
#endif

#ifndef NRFX_PPIB_INTERCONNECT_00_10_INST_IDX 
#define NRFX_PPIB_INTERCONNECT_00_10_INST_IDX 0
#endif

#ifndef NRFX_PPIB_INTERCONNECT_11_21_INST_IDX 
#define NRFX_PPIB_INTERCONNECT_11_21_INST_IDX 0
#endif

#ifndef NRFX_PPIB_INTERCONNECT_22_30_INST_IDX 
#define NRFX_PPIB_INTERCONNECT_22_30_INST_IDX 0
#endif

#ifndef NRFX_PPIB_INTERCONNECT_01_20_INST_IDX 
#define NRFX_PPIB_INTERCONNECT_01_20_INST_IDX 0
#endif

#include <nrfx_config_nrf54l15_application.h>

#endif // NRFX_CONFIG_H__
