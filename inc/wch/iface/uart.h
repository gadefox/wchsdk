#if IFACE_UART

// User-configurable macros (see wchsdk_cfg.h):
//  IFACE_UART_RX_RING_OVERWRITE  0/1
//   1: Incomming data will overwrite older data in the buffer.
//   0: Incomming data will not be added to the buffer until space is free.

#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "wch/hw/afio.h"
#include "wch/hw/uart.h"
#include "wch/hw/rcc.h"
#include "wch/mcu/def.h"

//------------------------------------------------------------------------------
// Baud

#define UART_BAUD_TO_BRR(b)  ((MCU_SYS_FREQ + ((b) / 2)) / (b))

//------------------------------------------------------------------------------
// CTLR1 options

#define UART_WORDLENGTH_9  USART_CTLR1_M

#define UART_PARITY_EVEN  USART_CTLR1_PCE
#define UART_PARITY_ODD   (USART_CTLR1_PCE | USART_CTLR1_PS)

//------------------------------------------------------------------------------
// CTLR2 options

#define UART_STOPBITS_HALF      USART_CTLR2_STOP_0
#define UART_STOPBITS_TWO       USART_CTLR2_STOP_1
#define UART_STOPBITS_ONE_HALF  USART_CTLR2_STOP

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
  USART1->CTLR1 |= USART_CTLR1_UE; }

static inline void uart_disable(void) {
  USART1->CTLR1 &= ~USART_CTLR1_UE; }

static inline void uart_power_on(void) {
  RCC->APB2PCENR |= RCC_APB2PERIPH_USART1; }

static inline void uart_power_off(void) {
  RCC->APB2PCENR &= ~RCC_APB2PERIPH_USART1; }

static inline void uart_reset(void) {
  RCC->APB2PRSTR |= RCC_APB2PERIPH_USART1;
  RCC->APB2PRSTR &= ~RCC_APB2PERIPH_USART1; }

static inline void usart_remap(uint32_t pcfr) {
  AFIO->PCFR1 &= ~(AFIO_PCFR1_SWCFG_DISABLE | AFIO_PCFR1_USART1_REMAP |
      AFIO_PCFR1_USART1_REMAP_1);
  AFIO->PCFR1 |= pcfr; }

//------------------------------------------------------------------------------

#endif  /* IFACE_UART */
