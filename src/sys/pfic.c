#include "wchsdk_cfg.h"

#if SYS_PFIC

#include "wch/sys/pfic.h"

//------------------------------------------------------------------------------
// Set VTF Interrupt: addr - VTF interrupt service function base address.
//  irq - Interrupt Numbers; num - VTF Interrupt Numbers

void pfic_set_vtf(uint32_t addr, irq_t irq, uint8_t num, bool enable) {
  if (num > 1)
    return;

  if (enable) {
    PFIC->VTFIDR[num] = irq;
    PFIC->VTFADDR[num] = ((addr & 0xFFFFFFFE) | 0x1);
  } else {
    PFIC->VTFIDR[num] = irq;
    PFIC->VTFADDR[num] = ((addr & 0xFFFFFFFE) & (~0x1));
  }
}

//------------------------------------------------------------------------------

void pfic_clear_all_irqs_except(uint8_t irq_to_keep) {
  if (irq_to_keep >> 5) { // irq_to_keep < 32
    irq_to_keep >>= 5;
    PFIC->IRER[0] = ~0;
    PFIC->IRER[1] = ~0 & ~(1 << irq_to_keep);
  } else {
    PFIC->IRER[0] = ~0 & ~(1 << irq_to_keep);
    PFIC->IRER[1] = ~0;
  }
}

//------------------------------------------------------------------------------

#endif  /* SYS_PFIC */
