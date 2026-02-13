#include "wchsdk_cfg.h"

#if IO_DMA

#include <stddef.h>

#include "wch/sys/pfic.h"
#include "wch/io/dma.h"

//------------------------------------------------------------------------------

#if !SYS_PFIC
#error "UART requires SYS_PFIC = 1"
#endif  /* SYS_PFIC */

//------------------------------------------------------------------------------

void dma_init_mem2periph(dma_channel_t* ch, uint8_t irq, void* paddr) {
  dma_disable(ch);
  dma_set_periph_addr(ch, paddr);

  // Enable the interrupt.
  pfic_enable_irq(irq);

  // Set dir to memory -> periph, memory increment, transfer compete interrupt
  ch->CFGR = DMA_CFGR1_DIR | DMA_CFGR1_MINC | DMA_CFGR1_TCIE;
  dma_enable(ch);
}

//------------------------------------------------------------------------------

void dma_init_periph2mem(dma_channel_t* ch, void* paddr, void* maddr, uint16_t count) {
  dma_disable(ch);
  dma_set_periph_addr(ch, paddr);
  dma_set_mem_addr(ch, maddr);
  dma_set_count(ch, count);

  // Set dir to periph -> memory, memory increment, circular buf mode
  ch->CFGR = DMA_CFGR1_MINC | DMA_CFGR1_CIRC;
  dma_enable(ch);
}

//------------------------------------------------------------------------------

void dma_reload(dma_channel_t* ch, void* mem, uint16_t len) {
  dma_disable(ch);
  dma_set_mem_addr(ch, mem);
  dma_set_count(ch, len);
  dma_enable(ch);
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
