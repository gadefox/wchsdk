#include <stdbool.h>

#include "wchsdk_cfg.h"
#include "wch/hw/exti.h"
#include "wch/sys/init.h"
#include "wch/io/enc.h"
#include "wch/io/pin.h"

static encoder_t enc;

void irq_exti7_0(void) {
  if (EXTI->INTFR & (EXTI_INTF_INTF0 | EXTI_INTF_INTF1)) {
    bool level_a = pin_a_get(0);  // PA0
    bool level_b = pin_a_get(1);  // PA1
    encoder_update(&enc, level_a, level_b);
    EXTI->INTFR = EXTI_INTF_INTF0 | EXTI_INTF_INTF1;
  }
}

int main(void) {
  sys_init();

  // Initialise pins
  pin_a_init();

  pin_a_mode(0, GPIO_CFGLR_IN_PUPD);
  pin_a_exti_cfg(0);

  pin_a_mode(1, GPIO_CFGLR_IN_PUPD);
  pin_a_exti_cfg(1);

  // Initialize exti
  EXTI->INTENR |= EXTI_INTENR_MR0 | EXTI_INTENR_MR1;
  EXTI->RTENR |= EXTI_RTENR_TR0 | EXTI_RTENR_TR1;
  EXTI->FTENR |= EXTI_FTENR_TR0 | EXTI_FTENR_TR1;

  bool level_a = pin_a_get(0);
  bool level_b = pin_a_get(1);
  encoder_init(&enc, level_a, level_b);

  while (true) {
  }

  return 0;
}
