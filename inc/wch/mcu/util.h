#if MCU_UTIL

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "wch/hw/def.h"

//------------------------------------------------------------------------------

static inline void delay_tiny(uint32_t n) {
  asm volatile(
   "mv     a5, %[n]                             \n\
 1: c.addi a5, -1                               \n\
    c.bnez a5, 1b" : : [n]"r"(n) : "a5"); }

//------------------------------------------------------------------------------
// Register utility functions

bool reg_wait(__IO uint32_t *statr, uint32_t mask, bool want_set, uint32_t timeout);
bool reg_wait2(__IO uint16_t *statr1, __IO uint16_t *statr2, uint32_t mask,
               bool want_set, uint32_t timeout);

//------------------------------------------------------------------------------

#endif  /* MCU_UTIL */
