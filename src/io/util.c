#include "wchsdk_cfg.h"

#if IO_UTIL

#include "wch/sys/def.h"
#include "wch/io/util.h"

//------------------------------------------------------------------------------

uint8_t freq_to_prescaler(uint32_t freq, uint8_t maxprescaler) {
  uint32_t ratio = SYS_FREQ / freq;
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
