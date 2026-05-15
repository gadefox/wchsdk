#include "wchsdk_cfg.h"

#if SYS_CORE

#include "wch/sys/stk.h"

//------------------------------------------------------------------------------

uint64_t stk_get64(void) {
  uint32_t base = stk_get_count();

#if STK_CNTH
  uint32_t high = stg_get_count_high();
  uint32_t check = stk_get_count();

  // If and only if check is higher than base can we guarantee high is
  // valid and matches the check else we need a new high.
  if (check < base)
    high = STK->CNTH;

  return PACK64(check, high);
#else  /* !HW_STK_CNTH */

  static uint32_t last_base, high;
  if (last_base > base)
    high++;

  last_base = base;
  return PACK64(base, high);

#endif  /* STK_CNTH */
}

//------------------------------------------------------------------------------

#endif  /* SYS_CORE */
