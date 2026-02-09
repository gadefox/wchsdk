#if IO_DMA

#pragma once

//#include <stdbool.h>
//#include <stdint.h>

//#include "wch/hw/afio.h"
#include "wch/hw/dma.h"
#include "wch/hw/rcc.h"
//#include "wch/mcu/def.h"

//------------------------------------------------------------------------------

void dma_init_mem2periph(dma_channel_t* ch, uint8_t irq, void* periph);
void dma_init_periph2mem(dma_channel_t* ch, void* periph, void* mem, uint16_t len);

void dma_reload(dma_channel_t* ch, void* mem, uint16_t len);

//------------------------------------------------------------------------------
// All configuration functions require channel disabled (EN=0)

static inline void dma_enable(dma_channel_t* ch) {
  ch->CFGR |= DMA_CFGR1_EN; }

static inline void dma_disable(dma_channel_t* ch) {
  ch->CFGR &= ~DMA_CFGR1_EN; }

static inline void dma_power_on(void) {
  RCC->APBPCENR |= RCC_DMA1EN; }

static inline void dma_power_off(void) {
  RCC->APBPCENR &= ~RCC_DMA1EN; }

//------------------------------------------------------------------------------

static inline void dma_set_count(dma_channel_t* ch, uint16_t count) {
  ch->CNTR = count; }

static inline uint16_t dma_get_count(dma_channel_t* ch) {
  return ch->CNTR; }

 static inline void dma_circular(dma_channel_t* ch) {
  ch->CFGR |= DMA_CFGR1_CIRC; }

 static inline void dma_normal(dma_channel_t* ch) {
  ch->CFGR &= ~DMA_CFGR1_CIRC; }

//------------------------------------------------------------------------------

static inline void dma_clear_tc(uint32_t clear_mask) {
  DMA1->INTFCR = clear_mask; }

 static inline void dma_irq_tc(dma_channel_t* ch) {
  ch->CFGR |= DMA_CFGR1_TCIE;
}

 static inline void dma_set_irq_ht(dma_channel_t* ch) {
  ch->CFGR |= DMA_CFGR1_HTIE;
}

 static inline void dma_irq_te(dma_channel_t* ch) {
  ch->CFGR |= DMA_CFGR1_TEIE;
}

//------------------------------------------------------------------------------

static inline void dma_set_mem_addr(dma_channel_t* ch, void* addr) {
  ch->MADDR = (uint32_t)addr; }

 static inline void dma_set_mem_inc(dma_channel_t* ch) {
  ch->CFGR |= DMA_CFGR1_MINC; }

 static inline void dma_set_mem_fixed(dma_channel_t* ch) {
  ch->CFGR &= ~DMA_CFGR1_MINC; }

 static inline void dma_set_mem2periph(dma_channel_t* ch) {
  ch->CFGR |= DMA_CFGR1_DIR; }

//------------------------------------------------------------------------------

static inline void dma_set_periph_addr(dma_channel_t* ch, void* addr) {
  ch->PADDR = (uint32_t)addr; }

 static inline void dma_set_periph_inc(dma_channel_t* ch) {
  ch->CFGR |= DMA_CFGR1_PINC; }

 static inline void dma_set_periph_fixed(dma_channel_t* ch) {
  ch->CFGR &= ~DMA_CFGR1_PINC; }

 static inline void dma_set_periph2mem(dma_channel_t* ch) {
  ch->CFGR &= ~DMA_CFGR1_DIR; }

//------------------------------------------------------------------------------

#endif  /* IO_DMA */
