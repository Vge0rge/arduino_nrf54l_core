/*
 * Copyright (c) 2024, Arm Limited. All rights reserved.
 * Copyright (c) 2023 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "startup.h"

void default_irq_handler(void)
{
	while(1);
}

/*----------------------------------------------------------------------------
  Reset Handler called on controller reset
 *----------------------------------------------------------------------------*/
void Reset_Handler(void)
{
    /* Reset CONTROL register */
    __set_CONTROL(0);

    /* Allow the MSP and PSP stacks to descend to address 0,
     * effectively disabling stack overflow protection.
     */
    __set_MSPLIM(0);
    __set_PSPLIM(0);

    /* Disable MPU */
    ARM_MPU_Disable();

    SCB->VTOR = (uint32_t) &(__VECTOR_TABLE[0]);

    __set_PSP((uint32_t)(&__INITIAL_SP));

    __set_MSPLIM((uint32_t)(&__STACK_LIMIT));
    __set_PSPLIM((uint32_t)(&__STACK_LIMIT));

    __PROGRAM_START();                        /* Enter PreMain (C library entry point) */
}
