#include "wchsdk_cfg.h"

#if IO_DMA

#include "wch/mcu/pfic.h"
#include "wch/io/dma.h"

//------------------------------------------------------------------------------

#if !MCU_PFIC
#error "UART requires MCU_PFIC = 1"
#endif  /* MCU_PFIC */

//------------------------------------------------------------------------------

void dma_init_mem2periph(dma_channel_t* ch, uint8_t irq, void* periph) {
  dma_disable(ch);
  dma_set_periph_addr(ch, periph);

  // Set dir to memory -> periph, memory increment, transfer compete interrupt
  ch->CFGR = DMA_CFGR1_DIR | DMA_CFGR1_MINC | DMA_CFGR1_TCIE;
  
  // No enable yet, dma_reload handles that. Enable the interrupt.
  pfic_enable_irq(irq);
}

//------------------------------------------------------------------------------

void dma_init_periph2mem(dma_channel_t* ch, void* periph, void* mem, uint16_t len) {
  dma_disable(ch);
  dma_set_periph_addr(ch, periph);
  dma_set_mem_addr(ch, mem);
  dma_set_count(ch, len);

  // Set dir to memory -> periph, memory increment, circular buf mode
  ch->CFGR = DMA_CFGR1_CIRC | DMA_CFGR1_MINC;
  dma_enable(ch);
}

//------------------------------------------------------------------------------

void dma_reload(dma_channel_t* ch, void* mem, uint16_t len) {
  dma_disable(ch);
  dma_set_mem_addr(ch, mem);
  dma_set_count(ch, len);
  dma_enable(ch);
}
}
//------------------------------------------------------------------------------

void dma_reset(dma_channel_t* ch) {
  dma_disable(ch);
  dma_set_count(ch, 0);
  dma_set_periph_addr(ch, NULL);
  dma_set_mem_addr(ch, NULL);
  ch->CFGR = 0;
  dma_enable(ch);
}

//------------------------------------------------------------------------------

#endif /* IO_DMA */
