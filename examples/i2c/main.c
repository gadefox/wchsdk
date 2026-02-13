#include <stdint.h>

#include "wchsdk_cfg.h"
#include "wch/sys/init.h"
#include "wch/io/i2c.h"

uint8_t ring_tx[32];
uint8_t ring_rx[32];

int main(void) {
  sys_init();

  // Initialise the UART
  i2c_config_t c;
  c.rx_buf = ring_rx;
  c.rx_size = sizeof(ring_rx);
  c.tx_buf = ring_tx;
  c.tx_size = sizeof(ring_tx);
  i2c_init(&c);

  // Loop forever, echoing UART data back to the sender
  while (true) {
    uint8_t byte;
    if (i2c_get(&byte))
      i2c_put(byte);
  }

  return 0;
}
