#include "wchsdk_cfg.h"

#if SYS_STK

#include "wch/hw/stk.h"
#include "wch/sys/stk.h"

//------------------------------------------------------------------------------

uint64_t stk_get64(void) {
  uint32_t base = STK->CNT;

#if SYS_STK_CNTH
  uint32_t high = STK->CNTH;
  uint32_t check = STK->CNT;

  // If and only if check is higher than base can we guarantee high is
  // valid and matches the check else we need a new high.
  if (check < base)
    high = STK->CNTH;

  return PACK64(check, high);
#else

  static uint32_t last_base, high;
  if (last_base > base)
    high++;

  last_base = base;
  return PACK64(base, high);

#endif  /* SYS_STK_CNTH */
}

//------------------------------------------------------------------------------

#endif  /* SYS_STK */
