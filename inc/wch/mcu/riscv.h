#if MCU_RISCV

#pragma once

#include <stdint.h>
#include "wch/mcu/def.h"

//------------------------------------------------------------------------------

// Add a certain number of nops.  Note: These are usually executed in pairs
// and take two cycles, so you typically would use 0, 2, 4, etc.
#define RISCV_NOPS(n)  asm volatile(\
   ".rept " #n "\n \
    c.nop       \n \
    .endr");

//------------------------------------------------------------------------------

// Get stack pointer (returns the stack pointer)
static inline uint32_t riscv_get_cpu_sp(void) {
  uint32_t result;
  asm volatile(ZICSR "mv %0, sp" : "=r"(result));
  return result;
}

// nop
static inline void riscv_nop(void) {
  asm volatile("nop");
}

// For reading INTSYSCR, for interrupt nesting + hardware stack enable.
static inline uint32_t riscv_get_INTSYSCR(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0, 0x804" : "=r"(result));
  return result;
}

// For setting INTSYSCR, for interrupt nesting + hardware stack enable.
static inline void riscv_set_INTSYSCR(uint32_t value) {
  asm volatile(ZICSR "csrw 0x804, %0" : : "r"(value));
}

// Return the Machine Status Register (MSTATUS)
static inline uint32_t riscv_get_MSTATUS(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0, mstatus" : "=r"(result));
  return (result);
}

// Set the Machine Status Register (MSTATUS)
static inline void riscv_set_MSTATUS(uint32_t value) {
  asm volatile(ZICSR "csrw mstatus, %0" : : "r"(value));
}

// Return the Machine ISA Register (MISA)
static inline uint32_t riscv_get_MISA(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0, misa" : "=r"(result));
  return (result);
}

// Set the Machine ISA Register (MISA)
static inline void riscv_set_MISA(uint32_t value) {
  asm volatile(ZICSR "csrw misa, %0" : : "r"(value));
}

// Return the Machine Trap-Vector Base-Address Register (MTVEC)
static inline uint32_t riscv_get_MTVEC(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0,"
                     "mtvec" : "=r"(result));
  return (result);
}

//  * @brief   Set the Machine Trap-Vector Base-Address Register (MTVEC)
static inline void riscv_set_MTVEC(uint32_t value) {
  asm volatile(ZICSR "csrw mtvec, %0" ::"r"(value));
}

// Return the Machine Seratch Register (MSCRATCH)
static inline uint32_t riscv_get_MSCRATCH(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0,"
                                "mscratch" : "=r"(result));
  return (result);
}

// Set the Machine Seratch Register (MSRATCH)
static inline void riscv_set_MSCRATCH(uint32_t value) {
  asm volatile(ZICSR "csrw mscratch, %0" : : "r"(value));
}

// Return the Machine Exception Program Register (MEPC)
static inline uint32_t riscv_get_MEPC(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0,"
                     "mepc" : "=r"(result));
  return (result);
}

// Set the Machine Exception Program Register (MEPC)
static inline void riscv_set_MEPC(uint32_t value) {
  asm volatile(ZICSR "csrw mepc, %0" : : "r"(value));
}

// Return the Machine Cause Register (MCAUSE)
static inline uint32_t riscv_get_MCAUSE(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0,"
                     "mcause" : "=r"(result));
  return (result);
}

// Set the Machine Cause Register (MCAUSE)
static inline void riscv_set_MCAUSE(uint32_t value) {
  asm volatile(ZICSR "csrw mcause, %0" ::"r"(value));
}

// Return the Machine Trap Value Register (MTVAL)
static inline uint32_t riscv_get_MTVAL(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0,"
                     "mtval" : "=r"(result));
  return (result);
}

// Set the Machine Trap Value Register (MTVAL)
static inline void riscv_set_MTVAL(uint32_t value) {
  asm volatile(ZICSR "csrw mtval, %0" : : "r"(value));
}

// Return Vendor ID Register (MVENDORID)
static inline uint32_t riscv_get_MVENDORID(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0, mvendorid" : "=r"(result));
  return (result);
}

// Return Machine Architecture ID Register (MARCHID)
static inline uint32_t riscv_get_MARCHID(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0, marchid" : "=r"(result));
  return (result);
}

// Return Machine Implementation ID Register (MIPID)
static inline uint32_t riscv_get_MIMPID(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0, mimpid" : "=r"(result));
  return (result);
}

// Return Hart ID Register MHARTID
static inline uint32_t riscv_get_MHARTID(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0, mhartid" : "=r"(result));
  return (result);
}

// Return stack pointer register (SP)
static inline uint32_t riscv_get_SP(void) {
  uint32_t result;
  asm volatile("mv %0,"
               "sp" : "=r"(result) :);
  return (result);
}

// Return DBGMCU_CR Register value
static inline uint32_t riscv_get_DEBUG_CR(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0, 0x7C0" : "=r"(result));
  return (result);
}

// Set the DBGMCU_CR Register value
static inline void riscv_set_DEBUG_CR(uint32_t value) {
  asm volatile(ZICSR "csrw 0x7C0, %0" : : "r"(value));
}

//------------------------------------------------------------------------------

#endif  /* MCU_RISCV */
