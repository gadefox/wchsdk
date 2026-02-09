// User-configurable macros (see wchsdk_cfg.h):
//  IFACE_UART_RX_RING_OVERWRITE  0/1
//   1: Incomming data will overwrite older data in the buffer.
//   0: Incomming data will not be added to the buffer until space is free.

#if IFACE_UART

#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "wch/hw/afio.h"
#include "wch/hw/rcc.h"
#include "wch/hw/uart.h"
#include "wch/mcu/def.h"

//------------------------------------------------------------------------------
// Baud

#define UART_BAUD_TO_BRR(b)  ((MCU_SYS_FREQ + ((b) / 2)) / (b))

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

bool uart_put(uint8_t byte);
bool uart_get(uint8_t *out);

//------------------------------------------------------------------------------
// Prints a string to the UART, without any added ternination

void uart_print(const char *s);
void uart_printnl(const char *s);

//------------------------------------------------------------------------------

 static inline bool uart_is_rx_empty(void) {
  return USART1->STATR & USART_STATR_RXNE; }

//------------------------------------------------------------------------------

 static inline void uart_set_baud(uint32_t baud) {
  USART1->BRR = UART_BAUD_TO_BRR(baud); }

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

#endif  /* IFACE_UART */
