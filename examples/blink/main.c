#include "wchsdk_cfg.h"
#include "wch/sys/init.h"
#include "wch/sys/stk.h"
#include "wch/io/pin.h"

#define PIN_R  PD0
#define PIN_G  PD1
#define PIN_B  PD2

void blink(int pin) {
  for (int i = 0; i < 30; i++) {
    pin_write(pin, true);
    delay_ms(150);
    pin_write(pin, false);
    delay_ms(150);
  }
}

void blink_port(int port) {
  for (int i = 0; i < 8; i++) {
    int pin = GPIO_PIN(port, i);
    blink(pin);
  }
}

int main(void) {
  sys_init();

  // Enable GPIOs
  port_power_on(RCC_IOPAEN | RCC_IOPCEN | RCC_IOPDEN);

  // Set pins to output mode
//  port_mask_cfg(GPIOA, PIN_MASK(PIN_R) | PIN_MASK(PIN_G) | PIN_MASK(PIN_B));
  port_write_cfg(GPIOA, 0x11111111);
  port_write_cfg(GPIOC, 0x11111111);
  port_write_cfg(GPIOD, 0x11111111);

//  uint32_t state = 0;
  while (true) {
    blink_port(GPIO_PORTA);
    blink_port(GPIO_PORTC);
    blink_port(GPIO_PORTD);
/*    pin_write(PIN_R, state == 0);
    pin_write(PIN_G, state == 1);
    pin_write(PIN_B, state == 2);
    delay_ms(500);
    if (++state == 3)
      state = 0;*/
  }
}
