#if SYS_CORE

#pragma once

#include <stdint.h>
#include "wch/sys/def.h"

//==============================================================================
// RISC-V Standard CSRs

//------------------------------------------------------------------------------
// Get Status register (0x300)

#define MSTATUS_MPP_POS  11

typedef enum {
  MSTATUS_MIE   = 1 << 3,                   // Machine Interrupt Enable
  MSTATUS_MPIE  = 1 << 7,                   // Machine Previous Interrupt Enable
  MSTATUS_MPP_M = 0b11 << MSTATUS_MPP_POS,  // Machine Previous Privilege = Machine
  MSTATUS_MPOP  = 1 << 23,                  // Whether the current active interrupt needs to come out of the stack
  MSTATUS_MPPOP = 1 << 24                   // Whether the current subactive interrupt needs to come out of the stack
} mstatus_t;

static inline mstatus_t csr_get_mstatus(void) {
  mstatus_t result;
  asm volatile(ZICSR "csrr %0, mstatus" : "=r"(result) : : "memory");
  return result; }

//------------------------------------------------------------------------------
// Write/Set/Clear Status register (0x300)

static inline void csr_write_mstatus(mstatus_t value) {
  asm volatile(ZICSR "csrw mstatus, %0" : : "r"(value) : "memory"); }

static inline void csr_set_mstatus(mstatus_t mask) {
  asm volatile(ZICSR "csrs mstatus, %0" : : "r"(mask) : "memory"); }

static inline void csr_clear_mstatus(mstatus_t mask) {
  asm volatile(ZICSR "csrc mstatus, %0" : : "r"(mask) : "memory"); }

//------------------------------------------------------------------------------
// Get HW instruction set register (0x301)

#define MISA_MXL_POS  30
#define MISA_MXL(x)   ((x) >> MISA_MXL_POS)

typedef enum {
  MISA_MXL_32  = 1,     // 32-bit CPU
  MISA_MXL_64  = 2,     // 64-bit CPU
  MISA_MXL_128 = 3      // 128-bit CPU
} misa_mxl_t;

typedef enum {
  MISA_EXT_A = 1 << 0,   // Atomic extension
  MISA_EXT_C = 1 << 2,   // Compressed instructions
  MISA_EXT_D = 1 << 3,   // Double-precision FPU
  MISA_EXT_E = 1 << 4,   // RV32E base ISA (reduced registers)
  MISA_EXT_F = 1 << 5,   // Single-precision FPU
  MISA_EXT_G = 1 << 6,   // Additional standard extensions
  MISA_EXT_H = 1 << 7,   // Hypervisor extension
  MISA_EXT_I = 1 << 8,   // Base integer ISA (RV32I/RV64I/RV128I)
  MISA_EXT_M = 1 << 12,  // Multiply/Divide extension
  MISA_EXT_N = 1 << 13,  // User-level interrupts
  MISA_EXT_Q = 1 << 16,  // Quad-precision FPU
  MISA_EXT_S = 1 << 18,  // Supervisor mode implemented
  MISA_EXT_U = 1 << 20,  // User mode implemented
  MISA_EXT_X = 1 << 23   // Non-standard extensions present
} misa_ext_t;

static inline uint32_t csr_get_misa(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0, misa" : "=r"(result));
  return result; }

//------------------------------------------------------------------------------
// Get Exception base address register (0x305)
// NOTE: Address bits [31:2] (no shift, 1KB aligned required)

typedef enum {
  MTVEC_IVT = 1 << 0,       // offset = IVT[interrupt number]
  MTVEC_ABS  = 1 << 1       // identification by absolute address
} mtvec_t;

static inline uint32_t csr_get_mtvec(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0, mtvec" : "=r"(result));
  return result; }

//------------------------------------------------------------------------------
// Set Exception base address register (0x305)

static inline void csr_write_mtvec(uint32_t value) {
  asm volatile(ZICSR "csrw mtvec, %0" ::"r"(value) : "memory"); }

//------------------------------------------------------------------------------
// Get temporary data storage register (0x340)

static inline uint32_t csr_get_mscratch(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0, mscratch" : "=r"(result));
  return result; }

//------------------------------------------------------------------------------
// Set temporary data storage register (0x340)

static inline void csr_write_mscratch(uint32_t value) {
  asm volatile(ZICSR "csrw mscratch, %0" : : "r"(value) : "memory"); }

//------------------------------------------------------------------------------
// Get Exception program pointer register (0x341)

static inline uintptr_t csr_get_mepc(void) {
  uintptr_t value;
  asm volatile(ZICSR "csrr %0, mepc" : "=r"(value));
  return value; }

//------------------------------------------------------------------------------
// Set Exception program pointer register (0x341)

static inline void csr_write_mepc(uint32_t value) {
  asm volatile(ZICSR "csrw mepc, %0" : : "r"(value) : "memory"); }

//------------------------------------------------------------------------------
// Get Exception cause register (0x342)

#define MCAUSE_IRQ  (1 << 31)

static inline uint32_t csr_get_mcause(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0, mcause" : "=r"(result));
  return result; }

//------------------------------------------------------------------------------
// Set Exception cause register (0x342)

static inline void csr_write_mcause(uint32_t value) {
  asm volatile(ZICSR "csrw mcause, %0" ::"r"(value) : "memory"); }

//------------------------------------------------------------------------------
// Get Architecture number register (0xF11)

#define MVID_JEDEC_ID   0x0000007F
#define MVID_JEDEC_BANK 0xFFFFFF80

#define MCHID_JEDEC_ID_POS   0
#define MCHID_JEDEC_BANK_POS 7

static inline uint32_t csr_get_mvendorid(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0, mvendorid" : "=r"(result));
  return result; }


//------------------------------------------------------------------------------
// Get Architecture number register (0xF12)

#define MCHID_VENDOR0 0x7C000000
#define MCHID_VENDOR1 0x03E00000
#define MCHID_VENDOR2 0x001F0000
#define MCHID_ARCH    0x00007C00
#define MCHID_SERIAL  0x000003E0
#define MCHID_VERSION 0x0000001F

#define MCHID_VERSION_POS 0
#define MCHID_SERIAL_POS  5
#define MCHID_ARCH_POS    10
#define MCHID_VENDOR2_POS 16
#define MCHID_VENDOR1_POS 21
#define MCHID_VENDOR0_POS 26

static inline uint32_t csr_get_marchid(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0, marchid" : "=r"(result));
  return result; }

//------------------------------------------------------------------------------
// Get Hardware implementation numbering register (0xF13)

#define MPID_VENDOR0 0x7C000000
#define MPID_VENDOR1 0x03E00000
#define MPID_VENDOR2 0x001F0000

#define MPID_VENDOR2_POS 16
#define MPID_VENDOR1_POS 21
#define MPID_VENDOR0_POS 26

static inline uint32_t csr_get_mimpid(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0, mimpid" : "=r"(result));
  return result; }

//==============================================================================
// Debug CSRs

//------------------------------------------------------------------------------
// Get Debug control and status registers (0x7B0)

static inline uint32_t csr_get_dcsr(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0, 0x7B0" : "=r"(result));
  return result; }

//------------------------------------------------------------------------------
// Set Debug control and status registers (0x7B0)

static inline void csr_write_dcsr(uint32_t value) {
  asm volatile(ZICSR "csrw 0x7B0, %0" : : "r"(value)); }

//------------------------------------------------------------------------------
// Get Debug mode program pointer register (0x7B3)

static inline uint32_t csr_get_dpc(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0, 0x7B1" : "=r"(result));
  return result; }

//------------------------------------------------------------------------------
// Set Debug mode program pointer register (0x7B1)

static inline void csr_write_dpc(uint32_t value) {
  asm volatile(ZICSR "csrw 0x7B1, %0" : : "r"(value)); }

//------------------------------------------------------------------------------
// Get Debug mode staging register 0 (0x7B2)

static inline uint32_t csr_get_dscratch0(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0, 0x7B2" : "=r"(result));
  return result; }

//------------------------------------------------------------------------------
// Set Debug mode staging register 0 (0x7B2)

static inline void csr_write_dscratch0(uint32_t value) {
  asm volatile(ZICSR "csrw 0x7B2, %0" : : "r"(value)); }

//------------------------------------------------------------------------------
// Get Debug mode staging register 1 (0x7B3)

static inline uint32_t csr_get_dscratch1(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0, 0x7B3" : "=r"(result));
  return result; }

//------------------------------------------------------------------------------
// Set Debug mode staging register 1 (0x7B3)

static inline void csr_write_dscratch1(uint32_t value) {
  asm volatile(ZICSR "csrw 0x7B3, %0" : : "r"(value)); }

//------------------------------------------------------------------------------
// Get Debug MCU Configuration Register (0x7C0)

static inline uint32_t csr_get_dbgmcu_cr(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0, 0x7C0" : "=r"(result));
  return result; }

//------------------------------------------------------------------------------
// Set Debug MCU Configuration Register (0x7C0)

static inline void csr_write_dbgmcu_cr(uint32_t value) {
  asm volatile(ZICSR "csrw 0x7C0, %0" : : "r"(value)); }

//==============================================================================
// Vendor-defined CSRs

//------------------------------------------------------------------------------
// Get INTSYSCR register (0x804)

typedef enum {
  INTSYSCR_HWSTK = 1 << 0,      // Hardware Stack Enable
  INTSYSCR_INEST = 1 << 1,      // Interrupt Nesting Enable
  INTSYSCR_EABI  = 1 << 2       // EABI Enable
} intsyscr_t;

static inline intsyscr_t csr_get_intsyscr(void) {
  intsyscr_t result;
  asm volatile(ZICSR "csrr %0, 0x804" : "=r"(result));
  return result; }

//------------------------------------------------------------------------------
// Set INTSYSCR register (<Up>)

static inline void csr_write_intsyscr(intsyscr_t value) {
  asm volatile(ZICSR "csrw 0x804, %0" : : "r"(value) : "memory"); }

//------------------------------------------------------------------------------

#endif  /* SYS_CORE */
