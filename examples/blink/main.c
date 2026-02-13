// Coppied from Ch32v003 blink example

#include "wchsdk_cfg.h"
#include "wch/sys/init.h"
#include "wch/sys/stk.h"
#include "wch/io/pin.h"

// use defines to make more meaningful names for our GPIO pins
#define PIND_1      0
#define PIND_K      4
#define PIND_BOB    6
#define PINC_KEVIN  0

void pin_set_all(bool set) {
  if (set) {
    pin_d_set(PIND_1);
    pin_d_set(PIND_K);
    pin_d_set(PIND_BOB);
    pin_c_set(PINC_KEVIN);
  } else {
    pin_d_reset(PIND_1);
    pin_d_reset(PIND_K);
    pin_d_reset(PIND_BOB);
    pin_c_reset(PINC_KEVIN);
  }

  delay_ms(250);
}

int main(void) {
  sys_init();
  pin_init_all(); // Enable GPIOs

  // Set pins to output mode
  pin_d_mode(PIND_1, GPIO_CFGLR_OUT_10_PP);
  pin_d_mode(PIND_K, GPIO_CFGLR_OUT_10_PP);
  pin_d_mode(PIND_BOB, GPIO_CFGLR_OUT_10_PP);
  pin_c_mode(PINC_KEVIN, GPIO_CFGLR_OUT_10_PP);

  while (true) {
    pin_set_all(true);
    pin_set_all(false);
  }
}
