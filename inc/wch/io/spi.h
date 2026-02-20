// User-configurable macros (see wchsdk_cfg.h):
//  IO_SPI_TIMEOUT
//  IO_SPI_RX_RING_OVERWRITE  0/1
//   1: Incomming data will overwrite older data in the buffer.
//   0: Incomming data will not be added to the buffer until space is free.

#if IO_SPI

#pragma once

#include <stdbool.h>

#include "wch/hw/afio.h"
#include "wch/hw/rcc.h"
#include "wch/hw/spi.h"

#include "wch/sys/pfic.h"
#include "wch/sys/util.h"

//------------------------------------------------------------------------------

#if !SYS_PFIC
#error "SPI requires SYS_PFIC = 1"
#endif  /* SYS_PFIC */

//------------------------------------------------------------------------------

#if !IO_SPI_TIMEOUT
#define IO_SPI_TIMEOUT  500
#endif  /* IO_SPI_TIMEOUT */

//------------------------------------------------------------------------------

typedef struct {
  uint32_t freq;
  uint8_t  direction;
  uint8_t  *rx_buf;
  uint8_t  rx_size;
  uint8_t  *tx_buf;
  uint8_t  tx_size;
} spi_config_t;

//------------------------------------------------------------------------------

void spi_init(spi_config_t* c);

bool spi_transfer_byte(uint8_t tx, uint8_t *rx);
bool spi_put(uint8_t byte);
bool spi_get(uint8_t *out);

//------------------------------------------------------------------------------
// DFF length can only be set when SPI is disabled

static inline void spi_begin_byte(void) {
  SPI1->CTLR1 &= ~SPI_DFF;
  SPI1->CTLR1 |= SPI_SPE; }

static inline void spi_begin_word(void) {
  SPI1->CTLR1 |= SPI_DFF | SPI_SPE; }

//------------------------------------------------------------------------------

static inline void spi_enable(void) {
  SPI1->CTLR1 |= SPI_CRCEN; }

static inline void spi_disable(void) {
  SPI1->CTLR1 &= ~SPI_CRCEN; }

static inline void spi_power_on(void) {
  RCC->APB2PCENR |= RCC_SPI1EN; }

static inline void spi_power_off(void) {
  RCC->APB2PCENR &= ~RCC_SPI1EN; }

static inline void spi_reset(void) {
  RCC->APB2PRSTR |= RCC_SPI1RST;
  RCC->APB2PRSTR &= ~RCC_SPI1RST; }

static inline void spi_remap(uint32_t pcfr) {
  AFIO->PCFR1 &= ~(AFIO_SWD_OFF | AFIO_SPI1_RM);
  AFIO->PCFR1 |= pcfr; }

//------------------------------------------------------------------------------

static inline bool spi_is_rx_empty(void) {
  return SPI1->STATR & SPI_RXNE; }

//------------------------------------------------------------------------------

static inline bool spi_wait_tx_complete(void) {
  return wait_mask((__IO uint32_t*)&SPI1->STATR, SPI_TXE, true, IO_SPI_TIMEOUT); }

static inline bool spi_wait_rx_available(void) {
  return wait_mask((__IO uint32_t*)&SPI1->STATR, SPI_RXNE, true, IO_SPI_TIMEOUT); }

static inline bool spi_wait_not_busy(void) {
  return wait_mask((__IO uint32_t*)&SPI1->STATR, SPI_BSY, false, IO_SPI_TIMEOUT); }

//------------------------------------------------------------------------------
// PFIC

static inline void spi_enable_irq(void) {
  pfic_enable_irq(IRQ_SPI1); }

static inline void spi_disable_irq(void) {
  pfic_disable_irq(IRQ_SPI1); }

//------------------------------------------------------------------------------

#endif // IO_SPI
