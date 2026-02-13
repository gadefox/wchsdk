#include "wchsdk_cfg.h"

#if IO_UTIL

#include "wch/mcu/def.h"
#include "wch/iface/util.h"

//------------------------------------------------------------------------------

uint8_t freq_to_prescaler(uint32_t freq, uint8_t maxprescaler) {
  uint32_t ratio = MCU_SYS_FREQ / freq;
  uint32_t power2 = 1;
  uint8_t prescaler = 0;

  while (power2 < ratio && prescaler <= maxprescaler) {
    power2 <<= 1;
    prescaler += 8;
  }
  return prescaler;
}

//------------------------------------------------------------------------------

#endif  /* IO_UTIL */
