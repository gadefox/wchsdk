#include "wchsdk_cfg.h"

#if UTIL_NUM

#include "wch/util/num.h"

//------------------------------------------------------------------------------

uint8_t log2_pow2(uint32_t x) {
  if (x == 0)
    return 0xFF;
 
  uint8_t r = 0;
  while (!(x & 1)) {
    x >>= 1;
    r++;
  }
  return r;
}

//------------------------------------------------------------------------------

#endif  /* UTIL_NUM */
