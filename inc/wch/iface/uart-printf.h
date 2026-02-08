// FIXME:not completed!!!
#if IFACE_PRINTF_UART

#pragma once

#include <stdarg.h>
#include "wch/mcu/def.h"

//------------------------------------------------------------------------------

#ifndef UART_BAUD_RATE
#define UART_BAUD_RATE  115200
#endif  /* UART_BAUD_RATE */

//------------------------------------------------------------------------------
// Put an output debug UART on Pin D5.
// You can write to this with printf(...) or puts(...)

void uart_setup(int uartBRR);

//------------------------------------------------------------------------------

void uart_write(const char *buf, int size);
void uart_putchar(int c);

//------------------------------------------------------------------------------

int uart_printf(const char *format, ...);
int uart_vprintf(const char *format, va_list args);

//------------------------------------------------------------------------------

#endif  /* IFACE_PRINTF_UART */
