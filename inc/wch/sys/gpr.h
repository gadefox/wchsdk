#if SYS_GPR

#pragma once

#include <stdint.h>

//------------------------------------------------------------------------------
// Return stack pointer register (SP)

static inline uint32_t gpr_get_sp(void) {
  uint32_t result;
  asm volatile("mv %0, sp" : "=r"(result));
  return result; }

//------------------------------------------------------------------------------

#endif  /* SYS_GPR */
