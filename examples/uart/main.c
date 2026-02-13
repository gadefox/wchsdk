#include <stdint.h>

#include "wchsdk_cfg.h"
#include "wch/sys/init.h"
#include "wch/iface/uart.h"

uint8_t ring_tx[32];
uint8_t ring_rx[32];

int main(void) {
  sys_init();

  // Initialise the UART
  uart_config_t c;
  c.baud = 9600;
  c.rx_buf = ring_rx;
  c.tx_buf = ring_tx;
  c.buf_size = sizeof(ring_tx);
  uart_init(&c);

  // Simple string printing example - all return uart_err_t error codes
  uart_print("This string will be one line 1");
  uart_print(" -- This string will be on the same line");
  uart_printnl("This string will be on its own line");

  // Loop forever, echoing UART data back to the sender
  while (true) {
    uint8_t byte;
    if (uart_get(&byte))
      uart_put(byte);
  }

  return 0;
}
