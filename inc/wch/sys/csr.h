#if SYS_CSR

#pragma once

#include <stdint.h>
#include "wch/sys/def.h"

//------------------------------------------------------------------------------
// Return the Machine Status Register (MSTATUS)

static inline uint32_t csr_get_mstatus(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0, mstatus" : "=r"(result));
  return result; }

//------------------------------------------------------------------------------
// Set the Machine Status Register (MSTATUS)

static inline void csr_set_mstatus(uint32_t value) {
  asm volatile(ZICSR "csrw mstatus, %0" : : "r"(value)); }

//------------------------------------------------------------------------------
// Return the Machine ISA Register (MISA)

static inline uint32_t csr_get_misa(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0, misa" : "=r"(result));
  return result; }

//------------------------------------------------------------------------------
// Set the Machine ISA Register (MISA)

static inline void csr_set_misa(uint32_t value) {
  asm volatile(ZICSR "csrw misa, %0" : : "r"(value)); }

//------------------------------------------------------------------------------
// Return the Machine Trap-Vector Base-Address Register (MTVEC)

static inline uint32_t csr_get_mtvec(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0, mtvec" : "=r"(result));
  return result; }

//------------------------------------------------------------------------------
// Set the Machine Trap-Vector Base-Address Register (MTVEC)

static inline void csr_set_mtvec(uint32_t value) {
  asm volatile(ZICSR "csrw mtvec, %0" ::"r"(value)); }

//------------------------------------------------------------------------------
// Return the Machine Seratch Register (MSCRATCH)

static inline uint32_t csr_get_mscratch(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0, mscratch" : "=r"(result));
  return result; }

//------------------------------------------------------------------------------
// Set the Machine Seratch Register (MSRATCH)

static inline void csr_set_mscratch(uint32_t value) {
  asm volatile(ZICSR "csrw mscratch, %0" : : "r"(value)); }

//------------------------------------------------------------------------------
// Return the Machine Exception Program Register (MEPC)

static inline uint32_t csr_get_mepc(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0, mepc" : "=r"(result));
  return result; }

//------------------------------------------------------------------------------
// Set the Machine Exception Program Register (MEPC)

static inline void csr_set_mepc(uint32_t value) {
  asm volatile(ZICSR "csrw mepc, %0" : : "r"(value)); }

//------------------------------------------------------------------------------
// Return the Machine Cause Register (MCAUSE)

static inline uint32_t csr_get_mcause(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0, mcause" : "=r"(result));
  return result; }

//------------------------------------------------------------------------------
// Set the Machine Cause Register (MCAUSE)

static inline void csr_set_mcause(uint32_t value) {
  asm volatile(ZICSR "csrw mcause, %0" ::"r"(value)); }

//------------------------------------------------------------------------------
// Return the Machine Trap Value Register (MTVAL)

static inline uint32_t csr_get_mtval(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0, mtval" : "=r"(result));
  return result; }

//------------------------------------------------------------------------------
// Set the Machine Trap Value Register (MTVAL)

static inline void csr_set_mtval(uint32_t value) {
  asm volatile(ZICSR "csrw mtval, %0" : : "r"(value)); }

//------------------------------------------------------------------------------
// Return Vendor ID Register (MVENDORID)

static inline uint32_t csr_get_mvendorid(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0, mvendorid" : "=r"(result));
  return result; }

//------------------------------------------------------------------------------
// Return Machine Architecture ID Register (MARCHID)

static inline uint32_t csr_get_marchid(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0, marchid" : "=r"(result));
  return result; }

//------------------------------------------------------------------------------
// Return Machine Implementation ID Register (MIPID)

static inline uint32_t csr_get_mimpid(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0, mimpid" : "=r"(result));
  return result; }

//------------------------------------------------------------------------------
// Return Hart ID Register MHARTID

static inline uint32_t csr_get_mhartid(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0, mhartid" : "=r"(result));
  return result; }

//------------------------------------------------------------------------------
// Return DBGMCU_CR Register value

static inline uint32_t csr_get_dbgcr(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0, 0x7C0" : "=r"(result));
  return result; }

//------------------------------------------------------------------------------
// Set the DBGMCU_CR Register value

static inline void csr_set_dbgcr(uint32_t value) {
  asm volatile(ZICSR "csrw 0x7C0, %0" : : "r"(value)); }

//------------------------------------------------------------------------------
// For reading INTSYSCR, for interrupt nesting + hardware stack enable.

static inline uint32_t csr_get_intsyscr(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0, 0x804" : "=r"(result));
  return result; }

//------------------------------------------------------------------------------
// For setting INTSYSCR, for interrupt nesting + hardware stack enable.

static inline void csr_set_intsyscr(uint32_t value) {
  asm volatile(ZICSR "csrw 0x804, %0" : : "r"(value)); }

//------------------------------------------------------------------------------

#endif  /* SYS_CSR */
