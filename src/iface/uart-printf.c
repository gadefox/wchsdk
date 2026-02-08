#include "wchsdk_cfg.h"

#if USE_PRINTF_UART

#include "wch/hw/gpio.h"
#include "wch/hw/rcc.h"
#include "wch/hw/uart.h"
#include "wch/util/fmt.h"
#include "wch/iface/uart-printf.h"

//------------------------------------------------------------------------------

void uart_setup(int uartBRR) {
  // Enable GPIOD and UART.
  RCC->APB2PCENR |= RCC_APB2PERIPH_GPIOD | RCC_APB2PERIPH_USART1;

  // Push-Pull, 10MHz Output, GPIO D5, with AutoFunction
  GPIOD->CFGLR &= ~(0xF << (4 * 5));
  GPIOD->CFGLR |= (GPIO_SPEED_10MHZ | GPIO_CNF_OUT_PP_AF) << (4 * 5);

  // USART1 configuration: 115200 8N1 TX only
  USART1->CTLR1 = USART_WORDLENGTH_8B | USART_PARITY_NO | USART_MODE_TX;
  USART1->CTLR2 = USART_STOPBITS_1;
  USART1->CTLR3 = USART_HWFLOW_CONTROL_NONE;

  // Baudrate register
  USART1->BRR = uartBRR;

  // Enable USART
  USART1->CTLR1 |= CTLR1_UE_SET;
}

//------------------------------------------------------------------------------

static int uart_puts(char *s, int len, void *buf) {
  uart_write(s, len);
  return len;
}

//------------------------------------------------------------------------------

__attribute__((weak))
int uart_printf(const char *format, ...) {
  va_list args;
  va_start(args, format);
  int ret_status = vpprintf(uart_puts, 0, format, args);
  va_end(args);
  return ret_status;
}

//------------------------------------------------------------------------------

__attribute__((weak))
int uart_vprintf(const char *format, va_list args) {
  return vpprintf(uart_puts, 0, format, args);
}

//------------------------------------------------------------------------------

// For debug writing to the UART.
__attribute__((weak))
void uart_write(const char *buf, int size) {
  for (int i = 0; i < size; i++) {
    while (!(USART1->STATR & USART_FLAG_TC))
      ;
    USART1->DATAR = *buf++;
  }
}
//------------------------------------------------------------------------------

// single char to UART
__attribute__((weak))
void uart_putchar(int c) {
  while (!(USART1->STATR & USART_FLAG_TC))
    ;
  USART1->DATAR = (const char)c;
}

//------------------------------------------------------------------------------

#endif  /* USE_PRINTF_UART */
