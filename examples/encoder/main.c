#include <stdbool.h>

#include "wchsdk_cfg.h"
#include "wch/sys/exti.h"
#include "wch/sys/init.h"
#include "wch/io/enc.h"
#include "wch/io/pin.h"

#define EXTI_LINES  0b11

#define PIN_A  0
#define PIN_B  1

static encoder_t enc;

void irq_exti7_0(void) {
  if (exti_pending(EXTI_LINES)) {        // EXTI_INTF_INTF0 | EXTI_INTF_INTF1
    uint32_t pins = port_get(GPIOA);
    encoder_init(&enc, BITR(pins, PIN_A), BITR(pins, PIN_B));
    exti_clear(EXTI_LINES);              // EXTI_INTF_INTF0 | EXTI_INTF_INTF1
  }
}

int main(void) {
  sys_init();

  // Initialise pins
  port_power_on(PORTA);

  port_clear_cfg(GPIOA, PIN_MASK(PIN_A) | PIN_MASK(PIN_B));
  port_set_cfg(GPIOA, PIN_IP(PIN_A) | PIN_IP(PIN_B));

  exti_clear_map(EXTI_MASK(PIN_A) | EXTI_MASK(PIN_B));
  exti_set_map(EXTI_PORTA(PIN_A) | EXTI_PORTA(PIN_B));

  // Initialize exti
  exti_enable(EXTI_LINES);               // EXTI_INTENR_MR0 | EXTI_INTENR_MR1
  exti_rising_on(EXTI_LINES);            // EXTI_RTENR_TR0 | EXTI_RTENR_TR1
  exti_falling_on(EXTI_LINES);           // EXTI_FTENR_TR0 | EXTI_FTENR_TR1

  uint32_t pins = port_get(GPIOA);
  encoder_init(&enc, BITR(pins, PIN_A), BITR(pins, PIN_B));

  while (true) {
    // nop
  }

  return 0;
}
