#if SYS_PFIC

#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "wch/hw/irq.h"
#include "wch/hw/pfic.h"

#include "wch/sys/def.h"

//------------------------------------------------------------------------------

static inline uint8_t pfic_reg_num(irq_t irq) {
  return (uint32_t)irq >> 5; }              // irq / 32

static inline uint32_t pfic_irq_mask(irq_t irq) {
  return BITS((uint32_t)irq & 0x1F); }      // bit[irq % 32]

//------------------------------------------------------------------------------
// Enable Interrupt (by interrupt number)

static inline void pfic_enable_irq(irq_t irq) {
  uint8_t num = pfic_reg_num(irq);
  uint32_t mask = pfic_irq_mask(irq);
  PFIC->IENR[num] = mask; }

//------------------------------------------------------------------------------
// Disable Interrupt (by interrupt number)

static inline void pfic_disable_irq(irq_t irq) {
  uint8_t num = pfic_reg_num(irq);
  uint32_t mask = pfic_irq_mask(irq);
  PFIC->IRER[num] = mask; }

//------------------------------------------------------------------------------

void pfic_disable_irqs_except(irq_t irq);

//------------------------------------------------------------------------------
// Get Interrupt Enable State, (by number)
static inline uint32_t pfic_is_irq_enabled(irq_t irq) {
  uint8_t num = pfic_reg_num(irq);
  uint32_t mask = pfic_irq_mask(irq);
  return PFIC->ISR[num] & mask; }

//------------------------------------------------------------------------------
// Get Interrupt Pending State, (by number), 1 = Pending 0 = Not pending

static inline uint32_t pfic_is_irq_pending(irq_t irq) {
  uint8_t num = pfic_reg_num(irq);
  uint32_t mask = pfic_irq_mask(irq);
  return PFIC->IPR[num] & mask; }

//------------------------------------------------------------------------------

static inline void pfic_set_pending_irq(irq_t irq) {
  uint8_t num = pfic_reg_num(irq);
  uint32_t mask = pfic_irq_mask(irq);
  PFIC->IPSR[num] = mask; }

//------------------------------------------------------------------------------
// Clear Interrupt Pending

static inline void pfic_clear_pending_irq(irq_t irq) {
  uint8_t num = pfic_reg_num(irq);
  uint32_t mask = pfic_irq_mask(irq);
  PFIC->IPRR[num] = mask; }

//------------------------------------------------------------------------------
// Get Interrupt Active State (returns 1 if active)

static inline uint32_t pfic_get_active(irq_t irq) {
  uint8_t num = pfic_reg_num(irq);
  uint32_t mask = pfic_irq_mask(irq);
  return PFIC->IACTR[num] & mask; }

//------------------------------------------------------------------------------
// Set Interrupt Priority (priority: bit7: pre-emption priority, bit6: subpriority, bit[5-0]: reserved

static inline void pfic_set_priority(irq_t irq, uint8_t priority) {
  PFIC->IPRIOR[(uint32_t)irq] = priority; }

//------------------------------------------------------------------------------
// SUSPEND ALL INTERRUPTS EXCEPT
// The following 3 functions serve to suspend all interrupts, except for the one
// you momentarily need. The purpose of this is to not disturb the one
// interrupt of interest and let it run unimpeded.
// procedure:
// 1. save the enabled IRQs: uint32_t backup = pfic_get_enabled_irqs();
// 2. disable all IRQs: pfic_clear_all_irqs_except(irqs);
// 3. restore the previously enabled IRQs: pfic_restore_irqs(backup);
//
// bit layout of the IRQ backup
// bit  0 | 1 | 2  |  3  | 4  |  5  | 6  .. 21 | 22 .. 28
// irq  2 | 3 | 12 | res | 14 | res | 16 .. 31 | 32 .. 38
// irq 2 and 3 aren't actually user-settable (see RM).
// Specifying an invalid irq_to_keep like 0 will disable all interrupts.

static inline uint32_t pfic_get_enabled_irqs() {
  return ((PFIC->ISR[0] & (PFIC_ISR1_INTENSTA2 | PFIC_ISR1_INTENSTA3)) >> 2) |
          (PFIC->ISR[0] >> 10) | (PFIC->ISR[1] << 22); }

//------------------------------------------------------------------------------

static inline void pfic_restore_irqs(uint32_t isr) {
  PFIC->IENR[0] = (isr << 10) | ((isr & 0b11) << 2);
  PFIC->IENR[1] = isr >> 22; }

//------------------------------------------------------------------------------
// Initiate a system reset request

static inline void pfic_system_reset(void) {
  PFIC->CFGR = PFIC_CFGR_RESETSYS | PFIC_CFGR_KEY3; }

//------------------------------------------------------------------------------
// WFI - wait for interrupt (like a light sleep)

__attribute__((always_inline))
static inline void pfic_wait_for_irq(void) {
  PFIC->SCTLR &= ~PFIC_SCTLR_WFITOWFE;
  asm volatile("wfi"); }

//------------------------------------------------------------------------------
// NOTE: Hardware workaround for CH32V003 WFI errata

__attribute__((always_inline))
static inline void pfic_wait_for_events(void) {
  uint32_t sctlr = PFIC->SCTLR & PFIC_SCTLR_SETEVENT;
  PFIC->SCTLR |= PFIC_SCTLR_SETEVENT | PFIC_SCTLR_WFITOWFE;
  PFIC->SCTLR &= ~PFIC_SCTLR_SETEVENT;
  PFIC->SCTLR |= sctlr;
  asm volatile("wfi");
  asm volatile("wfi"); }

//------------------------------------------------------------------------------
// Set VTF Interrupt: addr - VTF interrupt service function base address.
// NOTE: addr[31:1], no shift

static inline void pfic_enable_vtf(irq_t irq, void *addr, uint8_t num) {
  PFIC->VTFIDR[num] = irq;
  PFIC->VTFADDR[num] = (uint32_t)addr | PFIC_VTFADDR_EN; }

static inline void pfic_disable_vtf(irq_t irq, uint8_t num) {
  PFIC->VTFIDR[num] = irq;
  PFIC->VTFADDR[num] = 0; }

//------------------------------------------------------------------------------

#endif  /* SYS_PFIC */
