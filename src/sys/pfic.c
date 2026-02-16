#include "wchsdk_cfg.h"

#if SYS_PFIC

#include "wch/sys/pfic.h"

//------------------------------------------------------------------------------

void pfic_disable_irqs_except(irq_t irq) {
  uint8_t index = pfic_reg_num(irq);
  uint32_t mask = pfic_irq_mask(irq);

  if (index) {
    PFIC->IRER[0] = ~0;
    PFIC->IRER[1] = ~mask;
  } else {
    PFIC->IRER[0] = ~mask;
    PFIC->IRER[1] = ~0;
  }
}

//------------------------------------------------------------------------------

#endif  /* SYS_PFIC */
