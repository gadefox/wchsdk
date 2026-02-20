#include "wchsdk_cfg.h"
#include "wch/sys/init.h"
#include "wch/sys/stk.h"
#include "wch/io/pin.h"

#define PIN_R  PD5
#define PIN_G  PA0
#define PIN_B  PA1

void pins_on(void) {
  pin_set(PIN_R);
  port_set(GPIOA, PIN_BIT(PIN_G) | PIN_BIT(PIN_B));
}

void pins_off(void) {
  pin_reset(PIN_R);
  port_reset(GPIOA, PIN_BIT(PIN_G) | PIN_BIT(PIN_B));
}

int main(void) {
  sys_init();

  // Enable GPIOs
  port_power_on(RCC_IOPAEN | RCC_IOPDEN);

  // Set pins to output mode
  pin_set_mode(PIN_R, GPIO_PP10);
  port_mask_cfg(GPIOA, PIN_MASK(PIN_G) | PIN_MASK(PIN_B));
  port_set_cfg(GPIOA, PIN_PP10(PIN_G) | PIN_PP10(PIN_B));

  while (true) {
    pins_on();
    delay_ms(1000);
    pins_off();
    delay_ms(1000);
  }
}
