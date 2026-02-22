#include "wchsdk_cfg.h"
#include "wch/sys/init.h"
#include "wch/sys/stk.h"
#include "wch/io/pin.h"

#define PIN_R  PD5
#define PIN_G  PA0
#define PIN_B  PA1

int main(void) {
  sys_init();

  // Enable GPIOs
  port_power_on(RCC_IOPAEN | RCC_IOPDEN);

  // Set pins to output mode
  pin_mode(PIN_R, GPIO_PP10);
  port_mask_cfg(GPIOA, PIN_MASK(PIN_G) | PIN_MASK(PIN_B));
  port_write_cfg(GPIOA, PIN_PP10(PIN_G) | PIN_PP10(PIN_B));

  uint32_t state = 0;
  while (true) {
    pin_write(PIN_R, state % 4);
    pin_write(PIN_G, state % 5);
    pin_write(PIN_B, state % 6);
    delay_ms(500);
    state++;
  }
}
