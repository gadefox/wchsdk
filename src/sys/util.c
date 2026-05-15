#include "wchsdk_cfg.h"

#if SYS_CORE

#include "wch/sys/stk.h"
#include "wch/sys/util.h"

//==============================================================================
// Register functions

bool wait_mask(__IO uint32_t *statr, uint32_t mask, uint32_t value, uint16_t delay) {
  for (int i = 0; i < 200; i++) {
    if ((*statr & mask) == value)
      return true;

    delay_us(delay);
  }
  return false;
}

//------------------------------------------------------------------------------

bool wait_mask2(__IO uint16_t *statr1, __IO uint16_t *statr2, uint32_t mask,
                uint32_t value, uint16_t delay) {
  for (int i = 0; i < 200; i++) {
    uint32_t state = PACK32(*statr1, *statr2);
    if ((state & mask) == value)
      return true;

    delay_us(delay);
  }
  return false;
}

//------------------------------------------------------------------------------

#endif // SYS_CORE
