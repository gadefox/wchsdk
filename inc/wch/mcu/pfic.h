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
  PFIC->IENR[((uint32_t)irq >> 5)] = (1 << ((uint32_t)irq & 0x1F));
}

//------------------------------------------------------------------------------
// Disable Interrupt (by interrupt number)

static inline void pfic_disable_irq(irq_t irq) {
  PFIC->IRER[((uint32_t)irq >> 5)] = (1 << ((uint32_t)irq & 0x1F));
}

//------------------------------------------------------------------------------
// Get Interrupt Enable State, (by number), 1 = Triggered 0 = Not triggered
static inline uint32_t pfic_get_status_irq(irq_t irq) {
  return ((uint32_t)((PFIC->ISR[(uint32_t)irq >> 5] & (1 << ((uint32_t)irq & 0x1F))) ? 1 : 0));
}

//------------------------------------------------------------------------------
// Get Interrupt Pending State, (by number), 1 = Pending 0 = Not pending

static inline uint32_t pfic_get_pending_irq(irq_t irq) {
  return ((uint32_t)((PFIC->IPR[(uint32_t)irq >> 5] & (1 << ((uint32_t)irq & 0x1F))) ? 1 : 0));
}

//------------------------------------------------------------------------------
// "current number break hang"

static inline void pfic_set_pending_irq(irq_t irq) {
  PFIC->IPSR[((uint32_t)irq >> 5)] = (1 << ((uint32_t)irq & 0x1F));
}

//------------------------------------------------------------------------------
// Clear Interrupt Pending

static inline void pfic_clear_pending_irq(irq_t irq) {
  PFIC->IPRR[((uint32_t)irq >> 5)] = (1 << ((uint32_t)irq & 0x1F));
}

//------------------------------------------------------------------------------
// Get Interrupt Active State (returns 1 if active)

static inline uint32_t pfic_get_active(irq_t irq) {
  return ((uint32_t)((PFIC->IACTR[(uint32_t)irq >> 5] & (1 << ((uint32_t)irq & 0x1F))) ? 1 : 0));
}

//------------------------------------------------------------------------------
// Set Interrupt Priority (priority: bit7: pre-emption priority, bit6: subpriority, bit[5-0]: reserved

static inline void pfic_set_priority(irq_t irq, uint8_t priority) {
  PFIC->IPRIOR[(uint32_t)irq] = priority;
}

//------------------------------------------------------------------------------
// SUSPEND ALL INTERRUPTS EXCEPT
// The following 3 functions serve to suspend all interrupts, except for the one you momentarily need.
// The purpose of this is to not disturb the one interrupt of interest and let it run unimpeded.
// procedure:
// 1. save the enabled IRQs: uint32_t IRQ_backup = pfic_get_enabled_IRQs();
// 2. disable all IRQs: pfic_clear_all_IRQs_except(IRQ_of_interest);
// 3. restore the previously enabled IRQs: pfic_restore_IRQs(IRQ_backup);
//
// bit layout of the IRQ backup
// bit		0 | 1 | 2  |  3  | 4  |  5  | 6  .. 22 | 23 .. 28
// irq		2 | 3 | 12 | res | 14 | res | 16 .. 31 | 32 .. 38
// irq 2 and 3 aren't actually user-settable (see RM).
//
// Specifying an invalid irq_to_keep like 0 will disable all interrupts.

static inline uint32_t pfic_get_enabled_irqs() {
  return (((PFIC->ISR[0] >> 2) & 0b11) | ((PFIC->ISR[0] >> 12) << 2) |
      ((PFIC->ISR[1] & 0b1111111) << 23));
}

//------------------------------------------------------------------------------

static inline void pfic_restore_irqs(uint32_t old_state) {
  PFIC->IENR[0] = (old_state >> 2) << 12;
  PFIC->IENR[1] = old_state >> 23;
}

//------------------------------------------------------------------------------
// Initiate a system reset request

static inline void pfic_system_reset(void) {
  PFIC->CFGR = PFIC_KEY3 | (1 << 7);
}

//------------------------------------------------------------------------------
// WFI - wait for interrupt (like a light sleep)

__attribute__((always_inline))
static inline void pfic_wait_for_irq(void) {
  PFIC->SCTLR &= ~(1 << 3); // wfi
  asm volatile("wfi");
}

//------------------------------------------------------------------------------
// WFE - wait for events (more like a deeper sleep)

__attribute__((always_inline))
static inline void pfic_wait_for_events(void) {
  uint32_t t = PFIC->SCTLR;
  PFIC->SCTLR |= (1 << 3) | (1 << 5); // (wfi->wfe)+(__sev)
  PFIC->SCTLR = (PFIC->SCTLR & ~(1 << 5)) | (t & (1 << 5));
  asm volatile("wfi");
  asm volatile("wfi");
}

//------------------------------------------------------------------------------

#endif  /* MCU_PFIC */
