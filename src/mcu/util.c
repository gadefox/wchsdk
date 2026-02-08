
#include "wchsdk_cfg.h"

#if MCU_UTIL

#include "wch/hw/stk.h"
#include "wch/mcu/def.h"
#include "wch/mcu/util.h"

//==============================================================================
// Register functions

bool reg_wait_mask(__IO uint32_t *statr, uint32_t mask, bool want_set, uint32_t timeout) {
  uint32_t deadline = STK->CNT + timeout;

  while (true) {
    uint32_t state = *statr;
    if ((state & mask) == want_set)
      return true;

    if (stk_elapsed(deadline))
      return false;
  }
}

bool reg_wait_mask2(__IO uint16_t *statr1, __IO uint16_t *statr2, uint32_t mask,
                    bool want_set, uint32_t timeout) {
  uint32_t deadline = STK->CNT + timeout;

  while (true) {
    uint32_t state = PACK32(*statr1, *statr2);
    if ((state & mask) == want_set)
      return true;

    if (stk_elapsed(deadline))
      return false;
  }
}

//------------------------------------------------------------------------------

#endif // MCU_UTIL
