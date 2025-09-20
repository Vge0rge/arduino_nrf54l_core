/*
 * Copyright (c) 2019 Arduino SA
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef PINNAMES_H
#define PINNAMES_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <nrf_gpio.h>
///> define macro producing for example Px_y = NRF_GPIO_PIN_MAP(x, y)
#define PinDef(port_num, pin_num) P##port_num##_##pin_num = NRF_PIN_PORT_TO_PIN_NUMBER(pin_num, port_num)

    typedef enum
    {
        PinDef(0, 0), // P0_0
        PinDef(0, 1),
        PinDef(0, 2),
        PinDef(0, 3),
        PinDef(0, 4),
        PinDef(0, 5),
        PinDef(0, 6),
        PinDef(1, 0), // P1_0
        PinDef(1, 1),
        PinDef(1, 2),
        PinDef(1, 3),
        PinDef(1, 4),
        PinDef(1, 5),
        PinDef(1, 6),
        PinDef(1, 7),
        PinDef(1, 8),
        PinDef(1, 9),
        PinDef(1, 10),
        PinDef(1, 11),
        PinDef(1, 12),
        PinDef(1, 13),
        PinDef(1, 14),
        PinDef(1, 15),
        PinDef(1, 16),
        PinDef(2, 0), // P2_0
        PinDef(2, 1),
        PinDef(2, 2),
        PinDef(2, 3),
        PinDef(2, 4),
        PinDef(2, 5),
        PinDef(2, 6),
        PinDef(2, 7),
        PinDef(2, 8),
        PinDef(2, 9),
        PinDef(2, 10),
        // Not connected
        NC = (int)0xFFFFFFFF,

    } PinName;

#ifdef __cplusplus
}
#endif

#endif
