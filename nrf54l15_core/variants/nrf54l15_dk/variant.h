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

#pragma once
#include <stdint.h>
#include <nrfx.h>
#include <driverUarte.h>
// #include <macros.h>

#ifndef __PINS_ARDUINO__
#define __PINS_ARDUINO__

#define BOARD_VENDORID 0x1111
#define BOARD_PRODUCTID 0x1111
#define BOARD_NAME "nrf54l15_dk"

// Frequency of the board main oscillator
#define VARIANT_MAINOSC (32768ul)

// Master clock frequency
#define VARIANT_MCK (128000000ul)
#define ANALOG_CONFIG

// Pins
// ----

// The DK has the QFN48 package so 31 pins are available
#define PINS_COUNT (31u)
#define NUM_DIGITAL_PINS (31u)

// UART PINS
#define PIN_UART_TX P0_0
#define PIN_UART_RX P0_1

// LEDs
// ----
#define PIN_LED0 P2_9
#define PIN_LED1 P1_10
#define PIN_LED2 P2_7
#define PIN_LED3 P1_14

#define LED_BUILTIN PIN_LED0

// BUTTONs
// ----
#define PIN_BUTTON0 P1_13
#define PIN_BUTTON1 P1_9
#define PIN_BUTTON2 P1_8
#define PIN_BUTTON3 P0_4

// Digital pins
// -----------
#define D0 P2_0
#define D1 P2_1
#define D2 P2_2
#define D3 P2_3
#define D4 P2_4
#define D5 P2_5
#define D6 P2_6

// Analog pins
// -----------
#define A0 P1_0
#define A1 P1_1
#define A2 P1_4
#define A3 P1_5
#define A4 P1_6
#define A5 P1_8

// The QFN48 gives us P0 0-4, P1 0-14, P2 0-10/
// P0_0 and P0_1 for the UART
// P0_4 for the button 3
// P1_0 to P1_7  seem to be free

// Analog input can be
// p1.0, p1.1, p1.4, p1.5, p1.6, p1.8

/*
 * Serial interfaces
 */
extern Uarte Serial;
extern Uarte Serial1;

#endif //__PINS_ARDUINO__
