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

#ifdef __cplusplus
extern "C"
{
#endif

  void pinMode(pin_size_t pinNumber, PinMode pinMode)
  {

    switch (pinMode)
    {
    case INPUT:
      nrf_gpio_cfg_input(pinNumber, NRF_GPIO_PIN_NOPULL);
      break;

    case INPUT_PULLUP:
      nrf_gpio_cfg_input(pinNumber, NRF_GPIO_PIN_PULLUP);
      break;

    case INPUT_PULLDOWN:
      nrf_gpio_cfg_input(pinNumber, NRF_GPIO_PIN_PULLDOWN);
      break;

    case OUTPUT:
      nrf_gpio_cfg_output(pinNumber);
      break;

    default:
      break;
    }
  }

  void digitalWrite(pin_size_t pinNumber, PinStatus status)
  {

    switch (status)
    {
    case LOW:
      nrf_gpio_pin_clear(pinNumber);
      break;

    default:
      nrf_gpio_pin_set(pinNumber);
      break;
    }

    return;
  }

  PinStatus digitalRead(pin_size_t pinNumber)
  {
    uint32_t pin_reading = nrf_gpio_pin_out_read(pinNumber);

    return (pin_reading == 0) ? LOW : HIGH;
  }

#ifdef __cplusplus
}
#endif
