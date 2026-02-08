#if IO_DMA

#pragma once

//#include <stdbool.h>
//#include <stdint.h>

//#include "wch/hw/afio.h"
//#include "wch/hw/uart.h"
//#include "wch/hw/rcc.h"
//#include "wch/mcu/def.h"

//------------------------------------------------------------------------------

typedef struct {
  uint32_t baud;
  uint8_t *rx_buf;
  uint32_t rx_size;
  uint8_t *tx_buf;
  uint32_t tx_size;
} uart_config_t;

//------------------------------------------------------------------------------
// CTLR3 options
//  USART_CTLR3_CTSE
//  USART_CTLR3_RTSE
//  (USART_CTLR3_CTSE | USART_CTLR3_RTSE)

//------------------------------------------------------------------------------
// Initiliase the UART peripheral with the passed configuratiion.

void uart_init(uart_config_t* c);

//------------------------------------------------------------------------------
// Prints one byte to the UART

bool uart_put(uint8_t byte);

//------------------------------------------------------------------------------
// Reads one bytes from the RX Ring Buffer.

bool uart_get(uint8_t *out);

//------------------------------------------------------------------------------
// Prints a string to the UART, without any added ternination

void uart_print(const char *s);

//------------------------------------------------------------------------------
// Write the terminating characters

static inline void uart_printnl(const char *s) {
  uart_print(s);
  uart_put('\r');
  uart_put('\n'); }

//------------------------------------------------------------------------------

static inline bool uart_is_rx_empty(void) {
  return USART1->STATR & USART_STATR_RXNE; }

//------------------------------------------------------------------------------

static inline void uart_enable(void) {
  USART1->CTLR1 |= CTLR1_UE_SET; }

static inline void uart_disable(void) {
  USART1->CTLR1 &= CTLR1_UE_RESET; }

static inline void uart_power_on(void) {
  RCC->APB2PCENR |= RCC_USART1EN; }

static inline void uart_power_off(void) {
  RCC->APB2PCENR &= ~RCC_USART1EN; }

static inline void uart_reset(void) {
  RCC->APB2PRSTR |= RCC_USART1RST;
  RCC->APB2PRSTR &= ~RCC_USART1RST; }

static inline void usart_remap(uint32_t pcfr) {
  AFIO->PCFR1 &= ~(AFIO_PCFR1_SWCFG_DISABLE | AFIO_PCFR1_USART1_REMAP |
      AFIO_PCFR1_USART1_REMAP_1);
  AFIO->PCFR1 |= pcfr; }

//------------------------------------------------------------------------------

#endif  /* IO_DMA */
