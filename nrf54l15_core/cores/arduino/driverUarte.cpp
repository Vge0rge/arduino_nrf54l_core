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
#include <nrfx_uarte.h>
#include <limits.h>

Uarte::Uarte(nrfx_uarte_t p_instance, uint32_t txd_pin, uint32_t rxd_pin)
{
    this->p_instance = p_instance;
    this->txd_pin = txd_pin;
    this->rxd_pin = rxd_pin;
    this->simple_config = true;
}

Uarte::Uarte(nrfx_uarte_t p_instance, uint32_t txd_pin, uint32_t rxd_pin, uint32_t rts_pin, uint32_t cts_pin, nrf_uarte_hwfc_t hwfc)
{
    this->p_instance = p_instance;
    this->txd_pin = txd_pin;
    this->rxd_pin = rxd_pin;
    this->rts_pin = rts_pin;
    this->cts_pin = cts_pin;
    this->hwfc = hwfc;
    this->simple_config = false;
}

static nrf_uarte_baudrate_t baudrate_to_nrfx_enum(unsigned long baudrate)
{
    switch (baudrate)
    {
    case 1200:
        return NRF_UARTE_BAUDRATE_1200;
    case 2400:
        return NRF_UARTE_BAUDRATE_2400;
    case 4800:
        return NRF_UARTE_BAUDRATE_4800;
    case 9600:
        return NRF_UARTE_BAUDRATE_9600;
    case 14400:
        return NRF_UARTE_BAUDRATE_14400;
    case 19200:
        return NRF_UARTE_BAUDRATE_19200;
    case 28800:
        return NRF_UARTE_BAUDRATE_28800;
    case 31250:
        return NRF_UARTE_BAUDRATE_31250;
    case 38400:
        return NRF_UARTE_BAUDRATE_38400;
    case 56000:
        return NRF_UARTE_BAUDRATE_56000;
    case 57600:
        return NRF_UARTE_BAUDRATE_57600;
    case 76800:
        return NRF_UARTE_BAUDRATE_76800;
    case 115200:
        return NRF_UARTE_BAUDRATE_115200;
    case 230400:
        return NRF_UARTE_BAUDRATE_230400;
    case 250000:
        return NRF_UARTE_BAUDRATE_250000;
    case 460800:
        return NRF_UARTE_BAUDRATE_460800;
    case 921600:
        return NRF_UARTE_BAUDRATE_921600;
    case 1000000:
        return NRF_UARTE_BAUDRATE_1000000;
    default:
        return NRF_UARTE_BAUDRATE_115200;
    }
}

static nrf_uarte_frame_size_t config_to_nrfx_frame_size(uint16_t config){

    switch (config)
    {
    case SERIAL_5N1:
    case SERIAL_5E1:
    case SERIAL_5O1:
    case SERIAL_5N2:
    case SERIAL_5E2:
    case SERIAL_5O2:
        return NRF_UARTE_FRAME_SIZE_5_BIT;
        break;
    case SERIAL_6N1:
    case SERIAL_6E1:
    case SERIAL_6O1:
    case SERIAL_6N2:
    case SERIAL_6E2:
    case SERIAL_6O2:
        return NRF_UARTE_FRAME_SIZE_6_BIT;
        break;
    case SERIAL_7N1:
    case SERIAL_7E1:
    case SERIAL_7O1:
    case SERIAL_7N2:
    case SERIAL_7E2:
    case SERIAL_7O2:
        return NRF_UARTE_FRAME_SIZE_7_BIT;
        break;
    default:
        return NRF_UARTE_FRAME_SIZE_8_BIT;
        break;
    }
}

static bool config_has_parity(uint16_t config){

    switch (config)
    {
    case SERIAL_5N1:
    case SERIAL_5N2:
    case SERIAL_6N1:
    case SERIAL_6N2:
    case SERIAL_7N1:
    case SERIAL_7N2:
    case SERIAL_8N1:
    case SERIAL_8N2:
        return false;
    default:
        return true;
        break;
    }
}

static nrf_uarte_paritytype_t config_to_nrfx_parity_type(uint16_t config){

    switch (config)
    {
    case SERIAL_5O1:
    case SERIAL_5O2:
    case SERIAL_6O1:
    case SERIAL_6O2:
    case SERIAL_7O1:
    case SERIAL_7O2:
    case SERIAL_8O1:
    case SERIAL_8O2:
        return NRF_UARTE_PARITYTYPE_ODD;
        break;
    case SERIAL_5E1:
    case SERIAL_5E2:
    case SERIAL_6E1:
    case SERIAL_6E2:
    case SERIAL_7E1:
    case SERIAL_7E2:
    case SERIAL_8E1:
    case SERIAL_8E2:
    default:
        return NRF_UARTE_PARITYTYPE_EVEN;
        break;
    }
}

static nrf_uarte_stop_t config_to_nrfx_stop_bits(uint16_t config){

    switch (config)
    {
    case SERIAL_5N2:
    case SERIAL_6N2:
    case SERIAL_7N2:
    case SERIAL_8N2:
    case SERIAL_5O2:
    case SERIAL_6O2:
    case SERIAL_7O2:
    case SERIAL_8O2:
    case SERIAL_5E2:
    case SERIAL_6E2:
    case SERIAL_7E2:
    case SERIAL_8E2:
        return NRF_UARTE_STOP_TWO;
        break;
    default:
        return NRF_UARTE_STOP_ONE;
        break;
    }
}

void Uarte::begin(unsigned long baudrate)
{
    nrfx_uarte_config_t uarte_config = NRFX_UARTE_DEFAULT_CONFIG(this->txd_pin, this->rxd_pin);
    uarte_config.baudrate = baudrate_to_nrfx_enum(baudrate);

    if (!this->simple_config)
    {
        uarte_config.rts_pin = this->rts_pin;
        uarte_config.cts_pin = this->cts_pin;
        uarte_config.config.hwfc = this->hwfc;
    }

    nrfx_err_t err = nrfx_uarte_init(&this->p_instance, &uarte_config, NULL);
    if (err != NRFX_SUCCESS && err != NRFX_ERROR_ALREADY)
    {
        DEBUG_PRINT("nrfx_uarte_init failed")
    }
}


void Uarte::begin(unsigned long baudrate, uint16_t config)
{
    nrfx_uarte_config_t uarte_config = NRFX_UARTE_DEFAULT_CONFIG(this->txd_pin, this->rxd_pin);

    if (!this->simple_config)
    {
        uarte_config.rts_pin = this->rts_pin;
        uarte_config.cts_pin = this->cts_pin;
        uarte_config.config.hwfc = this->hwfc;
    }

    uarte_config.baudrate = baudrate_to_nrfx_enum(baudrate);
    uarte_config.config.frame_size= config_to_nrfx_frame_size(config);
    uarte_config.config.stop = config_to_nrfx_stop_bits(config);

    if(config_has_parity(config)){
        uarte_config.config.parity = NRF_UARTE_PARITY_INCLUDED;
        uarte_config.config.paritytype = config_to_nrfx_parity_type(config);
    }


    nrfx_err_t err = nrfx_uarte_init(&this->p_instance, &uarte_config, NULL);
    if (err != NRFX_SUCCESS && err != NRFX_ERROR_ALREADY)
    {
        DEBUG_PRINT("nrfx_uarte_init failed")
    }
}

void Uarte::end()
{
    nrfx_uarte_uninit(&this->p_instance);
}

void Uarte::flush()
{
}

int Uarte::available(void)
{
    size_t rx_bytes;
    nrfx_err_t err = nrfx_uarte_rx_ready(&this->p_instance, &rx_bytes);
    if (err != NRFX_SUCCESS)
    {
        DEBUG_PRINT("nrfx_uarte_rx_ready failed")
        return 0;
    }

    return (rx_bytes > INT_MAX) ? INT_MAX : rx_bytes;
}

int Uarte::peek(void)
{
    /* TODO: Implement this :) */
    return 0;
}

int Uarte::read(void)
{
    int c;
    nrfx_err_t err = nrfx_uarte_rx(&this->p_instance, (uint8_t *)&c, sizeof(c));
    if (err != NRFX_SUCCESS)
    {
        DEBUG_PRINT("nrfx_uarte_rx failed")
    }

    return c;
}

size_t Uarte::write(uint8_t byte)
{
    while (nrfx_uarte_tx_in_progress(&this->p_instance))
    {
    }
    nrfx_err_t err = nrfx_uarte_tx(&this->p_instance, &byte, 1, NRFX_UARTE_TX_BLOCKING);

    if (err != NRFX_SUCCESS)
    {
        DEBUG_PRINT("nrfx_uarte_tx failed")
        return 0;
    }
    
    return 1;
}
