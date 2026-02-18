#include "wchsdk_cfg.h"
#include "wch/sys/init.h"
#include "wch/sys/stk.h"
#include "wch/io/pin.h"

#define PIN_R  PD0
#define PIN_G  PD4
#define PIN_B  PC0

void set_pins(bool set) {
  if (set) {
    port_set(GPIOD, PIN_BIT(PIN_R) | PIN_BIT(PIN_G));
    pin_set(PIN_B);
  } else {
    port_reset(GPIOD, PIN_BIT(PIN_R) | PIN_BIT(PIN_G));
    pin_reset(PIN_B);
  }

  delay_ms(250);
}

int main(void) {
  sys_init();

  // Enable GPIOs
  port_power_on(RCC_IOPCEN | RCC_IOPDEN);

  // Set pins to output mode
  pin_set_mode(PIN_R, GPIO_CFGO_PP10);

  port_mask_cfg(GPIOD, PIN_MASK(PIN_G) | PIN_MASK(PIN_B));
  port_set_cfg(GPIOD, PIN_PP10(PIN_G) | PIN_PP10(PIN_B));

  while (true) {
    set_pins(true);
    set_pins(false);
  }
}
