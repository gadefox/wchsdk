#if MCU_PFIC

#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "wch/hw/irq.h"
#include "wch/hw/pfic.h"

//------------------------------------------------------------------------------

void pfic_set_vtf(uint32_t addr, irq_t irq, uint8_t num, bool enable);
void pfic_clear_all_irqs_except(uint8_t irq_to_keep);

//------------------------------------------------------------------------------
// Enable Interrupt (by interrupt number)

static inline void pfic_enable_irq(irq_t irq) {
  PFIC->IENR[((uint32_t)irq >> 5)] = (1 << ((uint32_t)irq & 0x1F)); }

//------------------------------------------------------------------------------
// Disable Interrupt (by interrupt number)

static inline void pfic_disable_irq(irq_t irq) {
  PFIC->IRER[((uint32_t)irq >> 5)] = (1 << ((uint32_t)irq & 0x1F)); }

//------------------------------------------------------------------------------
// Get Interrupt Enable State, (by number)
static inline bool pfic_is_irq_enabled(irq_t irq) {
  return (PFIC->ISR[(uint32_t)irq >> 5] & (1 << ((uint32_t)irq & 0x1F))) != 0; }

//------------------------------------------------------------------------------
// Get Interrupt Pending State, (by number), 1 = Pending 0 = Not pending

static inline bool pfic_is_irq_pending(irq_t irq) {
  return (PFIC->IPR[(uint32_t)irq >> 5] & (1 << ((uint32_t)irq & 0x1F))) != 0; }

//------------------------------------------------------------------------------

static inline void pfic_set_pending_irq(irq_t irq) {
  PFIC->IPSR[((uint32_t)irq >> 5)] = (1 << ((uint32_t)irq & 0x1F)); }

//------------------------------------------------------------------------------
// Clear Interrupt Pending

static inline void pfic_clear_pending_irq(irq_t irq) {
  PFIC->IPRR[((uint32_t)irq >> 5)] = (1 << ((uint32_t)irq & 0x1F)); }

//------------------------------------------------------------------------------
// Get Interrupt Active State (returns 1 if active)

static inline bool pfic_get_active(irq_t irq) {
  return (PFIC->IACTR[(uint32_t)irq >> 5] & (1 << ((uint32_t)irq & 0x1F))) != 0; }

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

#endif  /* MCU_PFIC */
