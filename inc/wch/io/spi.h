// User-configurable macros (see wchsdk_cfg.h):
//  IO_SPI_TIMEOUT
//  IO_SPI_RX_RING_OVERWRITE  0/1
//   1: Incomming data will overwrite older data in the buffer.
//   0: Incomming data will not be added to the buffer until space is free.

#if IO_SPI

#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "wch/hw/afio.h"
#include "wch/hw/rcc.h"
#include "wch/hw/spi.h"
#include "wch/mcu/util.h"

#if !MCU_UTIL
#error "SPI requires MCU_UTIL = 1"
#endif  /* MCU_UTIL */

//------------------------------------------------------------------------------

#if !IFACE_SPI_TIMEOUT
#define IFACE_SPI_TIMEOUT  500
#endif  /* IFACE_SPI_TIMEOUT */

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
  SPI1->CTLR1 &= ~SPI_CTLR1_DFF;
  SPI1->CTLR1 |= SPI_CTLR1_SPE; }

static inline void spi_begin_word(void) {
  SPI1->CTLR1 |= SPI_CTLR1_DFF | SPI_CTLR1_SPE; }

//------------------------------------------------------------------------------

static inline void spi_enable(void) {
  SPI1->CTLR1 |= CTLR1_CRCEN_SET; }

static inline void spi_disable(void) {
  SPI1->CTLR1 &= CTLR1_CRCEN_RESET; }

static inline void spi_power_on(void) {
  RCC->APB2PCENR |= RCC_SPI1EN; }

static inline void spi_power_off(void) {
  RCC->APB2PCENR &= ~RCC_SPI1EN; }

static inline void spi_reset(void) {
  RCC->APB2PRSTR |= RCC_SPI1RST;
  RCC->APB2PRSTR &= ~RCC_SPI1RST; }

static inline void spi_remap(uint32_t pcfr) {
  AFIO->PCFR1 &= ~(AFIO_PCFR1_SWCFG_DISABLE | AFIO_PCFR1_SPI1_REMAP);
  AFIO->PCFR1 |= pcfr; }

//------------------------------------------------------------------------------

static inline bool spi_is_rx_empty(void) {
  return SPI1->STATR & SPI_STATR_RXNE; }

//------------------------------------------------------------------------------

static inline bool spi_wait_tx_complete(void) {
  return wait_mask((__IO uint32_t*)&SPI1->STATR, SPI_STATR_TXE, true, IFACE_SPI_TIMEOUT); }

static inline bool spi_wait_rx_available(void) {
  return wait_mask((__IO uint32_t*)&SPI1->STATR, SPI_STATR_RXNE, true, IFACE_SPI_TIMEOUT); }

static inline bool spi_wait_not_busy(void) {
  return wait_mask((__IO uint32_t*)&SPI1->STATR, SPI_STATR_BSY, false, IFACE_SPI_TIMEOUT); }

//------------------------------------------------------------------------------

#endif // IO_SPI
