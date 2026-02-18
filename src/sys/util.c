#include "wchsdk_cfg.h"

#if SYS_CORE

#include "wch/sys/stk.h"
#include "wch/sys/util.h"

//==============================================================================
// Register functions

bool wait_mask(__IO uint32_t *statr, uint32_t mask, bool want_set, uint32_t timeout) {
  uint32_t deadline = stk_get_count() + timeout;

  while (true) {
    bool is_set = (*statr & mask) != 0;
    if (is_set == want_set)
      return true;

    if (stk_elapsed(deadline))
      return false;
  }
}

//------------------------------------------------------------------------------

bool wait_mask2(__IO uint16_t *statr1, __IO uint16_t *statr2, uint32_t mask,
                bool want_set, uint32_t timeout) {
  uint32_t deadline = stk_get_count() + timeout;

  while (true) {
    uint32_t state = PACK32(*statr1, *statr2);
    bool is_set = (state & mask) != 0;

    if (is_set == want_set)
      return true;

    if (stk_elapsed(deadline))
      return false;
  }
}

//------------------------------------------------------------------------------

#endif // SYS_CORE
