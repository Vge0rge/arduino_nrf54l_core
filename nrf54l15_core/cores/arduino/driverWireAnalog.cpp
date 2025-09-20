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
#include <hal/nrf_gpio.h>
#include <nrfx_saadc.h>

int analogRead(pin_size_t pinNumber)
{
    nrfx_err_t err;
    const nrfx_saadc_channel_t m_single_channel = NRFX_SAADC_DEFAULT_CHANNEL_SE(pinNumber, 0);
    int16_t sample_value = 0;
    uint32_t channels_mask = 0;

    err = nrfx_saadc_init(NRFX_SAADC_DEFAULT_CONFIG_IRQ_PRIORITY);
    if (err != NRFX_SUCCESS && err != NRFX_ERROR_ALREADY_INITIALIZED)
    {
        DEBUG_PRINT("nrfx_saadc_init failed")
        return 0;
    }

    err = nrfx_saadc_channel_config(&m_single_channel);
    if (err != NRFX_SUCCESS)
    {
        DEBUG_PRINT("nrfx_saadc_channel_config failed")
        return 0;
    }

    channels_mask = nrfx_saadc_channels_configured_get();

    err = nrfx_saadc_simple_mode_set(channels_mask,
                                     NRF_SAADC_RESOLUTION_10BIT,
                                     NRF_SAADC_OVERSAMPLE_DISABLED,
                                     NULL);
    if (err != NRFX_SUCCESS)
    {
        DEBUG_PRINT("nrfx_saadc_simple_mode_set failed")
        return 0;
    }

    err = nrfx_saadc_buffer_set(&sample_value, 1);
    if (err != NRFX_SUCCESS)
    {
        DEBUG_PRINT("nrfx_saadc_buffer_set failed")
        return 0;
    }

    err = nrfx_saadc_offset_calibrate(NULL);
    if (err != NRFX_SUCCESS)
    {
        DEBUG_PRINT("nrfx_saadc_offset_calibrate failed")
        return 0;
    }

    err = nrfx_saadc_mode_trigger();
    if (err != NRFX_SUCCESS)
    {
        DEBUG_PRINT("nrfx_saadc_mode_trigger failed")
        return 0;
    }

    nrfx_saadc_uninit();

    return (sample_value < 0) ? 0 : sample_value;
}

void analogReference(uint8_t mode)
{
    // Nothing to do here, only internal reference is supported which is 0.9V
}

void analogWrite(pin_size_t pinNumber, int value)
{
    // TODO: Use the PWM for this?
}