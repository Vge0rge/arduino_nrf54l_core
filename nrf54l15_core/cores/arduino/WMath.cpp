 /*
 * Copyright (c) 2026, Georgios Vasilakis
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

#include "Arduino.h"

#ifdef __cplusplus
extern "C"
{
#include <nrfx_cracen.h>
}
#endif

    static long cracenRng(long min, long max)
    {
        nrfx_err_t err = nrfx_cracen_ctr_drbg_init();
        long value;

        if (err != NRFX_SUCCESS && err != NRFX_ERROR_ALREADY)
        {
            DEBUG_PRINT("nrfx_cracen_ctr_drbg_init failed")
            // TODO: Get some clock cycles here?
            return (max == 0) ? 0 : max - 1;
        }

        err = nrfx_cracen_ctr_drbg_random_get((uint8_t *)&value, sizeof(value));
        if (err != NRFX_SUCCESS)
        {
            DEBUG_PRINT("nrfx_cracen_ctr_drbg_random_get failed")
            // TODO: Get some clock cycles here?
            return (max == 0) ? 0 : max - 1;
        }

        // That is just a hobby project so no need for serious security here :)
        while (value < min)
        {
            value <<= 1;
        }

        while (value >= max)
        {
            value >>= 1;
        }

        return value;
    }

    
    long random(long max) {
        return cracenRng(0, max);
    }

    long random(long min, long max) {
         return cracenRng(min, max);
    }
