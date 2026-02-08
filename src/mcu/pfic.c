#include "wchsdk_cfg.h"

#if MCU_PFIC

#include "wch/mcu/pfic.h"

//------------------------------------------------------------------------------
// @fn      SetVTFIRQ
// @brief   Set VTF Interrupt
// @param   addr - VTF interrupt service function base address.
//                  irq - Interrupt Numbers
//                  num - VTF Interrupt Numbers
//                  enalbe -  DISABLE or ENABLE

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

#endif  /* MCU_PFIC */
