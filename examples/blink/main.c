#include "wchsdk_cfg.h"
#include "wch/sys/init.h"
#include "wch/sys/stk.h"
#include "wch/io/pin.h"

#define PIN_R  PD0
#define PIN_G  PD4
#define PIN_B  PC0

void set_pins(bool set) {
  if (set) {
    port_set(GPIOD, BITS(PIN_R) | BITS(PIN_G));
    pin_set(GPIOC, PIN_B);
  } else {
    port_reset(GPIOD, BITS(PIN_R) | BITS(PIN_G));
    pin_reset(GPIOC, PIN_B);
  }

  delay_ms(250);
}

int main(void) {
  sys_init();

  // Enable GPIOs
  port_power_on(PORTC | PORTD);

  // Set pins to output mode
  port_cfg(GPIOC, PIN_PP10(PIN_R), PIN_MASK(PIN_R));
  port_cfg(GPIOD, PIN_PP10(PIN_G) | PIN_PP10(PIN_B), PIN_MASK(PIN_G) | PIN_MASK(PIN_B));

  while (true) {
    set_pins(true);
    set_pins(false);
  }
}
