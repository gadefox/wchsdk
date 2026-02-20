#include <stdbool.h>

#include "wchsdk_cfg.h"
#include "wch/sys/exti.h"
#include "wch/sys/init.h"
#include "wch/io/enc.h"
#include "wch/io/pin.h"

#define PIN_A  PA0
#define PIN_B  PA1

static encoder_t enc;

void irq_exti7_0(void) {
  if (exti_pending(EXTI_PIN0 | EXTI_PIN1)) {
    uint32_t pins = port_get(GPIOA);
    encoder_update(&enc, BITR(pins, PIN_NUM(PIN_A)), BITR(pins, PIN_NUM(PIN_B)));
    exti_clear(EXTI_PIN0 | EXTI_PIN1);
  }
}

int main(void) {
  sys_init();

  // Initialise pins
  port_power_on(RCC_IOPAEN);

  port_mask_cfg(GPIOA, PIN_MASK(PIN_A) | PIN_MASK(PIN_B));
  port_set_cfg(GPIOA, PIN_IP(PIN_A) | PIN_IP(PIN_B));

  exti_mask_map(EXTI_MASK(PIN_A) | EXTI_MASK(PIN_B));
  exti_set_map(EXTI_PORTA(PIN_A) | EXTI_PORTA(PIN_B));

  // Initialize exti
  exti_enable(EXTI_PIN0 | EXTI_PIN1);
  exti_rising_on(EXTI_PIN0 | EXTI_PIN1);
  exti_falling_on(EXTI_PIN0 | EXTI_PIN1);

  uint32_t pins = port_get(GPIOA);
  encoder_init(&enc, BITR(pins, PIN_NUM(PIN_A)), BITR(pins, PIN_NUM(PIN_B)));

  while (true) {
    // nop
  }

  return 0;
}
