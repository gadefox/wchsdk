#if SYS_CORE

#pragma once

#include <stdint.h>

//------------------------------------------------------------------------------
// Return stack pointer register (SP)

static inline uint32_t gpr_get_sp(void) {
  uint32_t result;
  asm volatile("mv %0, sp" : "=r"(result));
  return result; }

//------------------------------------------------------------------------------
// Set stack pointer register (SP)

static inline void gpr_set_sp(uint32_t value) {
  asm volatile("mv sp, %0" : : "r"(value) : "sp"); }

//------------------------------------------------------------------------------
// Initialize stack pointer register (SP)

static inline void gpr_init_sp(void) {
  asm volatile("la sp, _eusrstack"); }

//------------------------------------------------------------------------------
// Return global pointer register (GP)

static inline uint32_t gpr_get_gp(void) {
  uint32_t result;
  asm volatile("mv %0, gp" : "=r"(result));
  return result; }

//------------------------------------------------------------------------------
// Set global pointer register (GP)

static inline void gpr_set_gp(uint32_t value) {
  asm volatile("mv gp, %0" : : "r"(value) : "gp" ); }

//------------------------------------------------------------------------------
// Initialize global pointer register (GP)

static inline void gpr_init_gp(void) {
  asm volatile(
    ".option push               \n"
    ".option norelax            \n"
    "la gp, __global_pointer$   \n"
    ".option pop" : : : "gp"); }

//------------------------------------------------------------------------------

#endif  /* SYS_CORE */
