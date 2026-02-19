#include "wchsdk_cfg.h"
#include "wch/sys/init.h"
#include "wch/sys/stk.h"
#include "wch/io/pin.h"

#define PIN_R  PD5
#define PIN_G  PA0
#define PIN_B  PA1

void set_pins(bool set) {
  if (set) {
    port_set(GPIOA, PIN_BIT(PIN_R) | PIN_BIT(PIN_G));
    pin_set(PIN_R);
  } else {
    port_reset(GPIOA, PIN_BIT(PIN_R) | PIN_BIT(PIN_G));
    pin_reset(PIN_R);
  }

  delay_ms(250);
}

int main(void) {
  sys_init();

  // Enable GPIOs
  port_power_on(RCC_IOPCEN | RCC_IOPDEN);

  // Set pins to output mode
  pin_set_mode(PIN_R, GPIO_CFGO_PP10);

  port_mask_cfg(GPIOA, PIN_MASK(PIN_G) | PIN_MASK(PIN_B));
  port_set_cfg(GPIOA, PIN_PP10(PIN_G) | PIN_PP10(PIN_B));

  while (true) {
    set_pins(true);
    set_pins(false);
  }
}
