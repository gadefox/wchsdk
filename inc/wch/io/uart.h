// User-configurable macros (see wchsdk_cfg.h):
//  IO_UART_RX_RING_OVERWRITE  0/1
//   1: Incomming data will overwrite older data in the buffer.
//   0: Incomming data will not be added to the buffer until space is free.

#if IO_UART

#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "wch/hw/afio.h"
#include "wch/hw/rcc.h"
#include "wch/hw/uart.h"
#include "wch/sys/def.h"
#include "wch/sys/pfic.h"

//------------------------------------------------------------------------------

#if !SYS_PFIC
#error "UART requires SYS_PFIC = 1"
#endif  /* SYS_PFIC */

//------------------------------------------------------------------------------
// Baud

#define UART_BAUD_TO_BRR(b)  ((SYSCLK + ((b) / 2)) / (b))

//------------------------------------------------------------------------------

typedef struct {
  uint32_t baud;
  uint8_t *usb_buf;
  uint8_t *rx_buf;
  uint8_t *tx_buf;
  uint8_t  buf_size;
} uart_config_t;

//------------------------------------------------------------------------------
// Initiliase the UART peripheral with the passed configuration.

void uart_init(uart_config_t* c);

//------------------------------------------------------------------------------

uint8_t uart_rx_snapshot(void);
bool uart_rx_get(uint8_t *out);
bool uart_tx_put(uint8_t byte);

//------------------------------------------------------------------------------
// Prints a string to the UART, without any added ternination

void uart_print(const char *s);
void uart_printnl(const char *s);

//------------------------------------------------------------------------------
static inline void uart_set_baud(uint32_t baud) {
  UART1->BRR = UART_BAUD_TO_BRR(baud); }

//------------------------------------------------------------------------------

static inline bool uart_is_tx_empty(void) {
  return UART1->STATR & UART_STATR_TXE; }

static inline bool uart_is_rx_ready(void) {
  return UART1->STATR & UART_STATR_RXNE; }

//------------------------------------------------------------------------------

static inline void uart_disable_txe(void) {
  UART1->CTLR1 &= ~UART_CTLR1_TXEIE; }

static inline void uart_enable_txe(void) {
  UART1->CTLR1 |= UART_CTLR1_TXEIE; }

static inline void uart_disable_idle(void) {
  UART1->CTLR1 &= ~UART_CTLR1_IDLEIE; }

static inline void uart_enable_idle(void) {
  UART1->CTLR1 |= UART_CTLR1_IDLEIE; }

//------------------------------------------------------------------------------

static inline void uart_enable(void) {
  UART1->CTLR1 |= CTLR1_UE_SET; }

static inline void uart_disable(void) {
  UART1->CTLR1 &= CTLR1_UE_RESET; }

static inline void uart_power_on(void) {
  RCC->APB2PCENR |= RCC_UART1EN; }

static inline void uart_power_off(void) {
  RCC->APB2PCENR &= ~RCC_UART1EN; }

static inline void uart_reset(void) {
  RCC->APB2PRSTR |= RCC_UART1RST;
  RCC->APB2PRSTR &= ~RCC_UART1RST; }

//------------------------------------------------------------------------------

static inline void uart_remap(uint32_t pcfr) {
  AFIO->PCFR1 &= ~(AFIO_PCFR1_SWCFG_DISABLE | AFIO_PCFR1_UART1_REMAP |
      AFIO_PCFR1_UART1_REMAP_1);
  AFIO->PCFR1 |= pcfr; }

//------------------------------------------------------------------------------
// PFIC

static inline void uart_enable_irq(void) {
  pfic_enable_irq(IRQ_UART1); }

static inline void uart_disable_irq(void) {
  pfic_disable_irq(IRQ_UART1); }

//------------------------------------------------------------------------------

#endif  /* IO_UART */
