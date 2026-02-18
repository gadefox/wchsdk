#include "wchsdk_cfg.h"

#if IO_ENCODER

#include "wch/hw/stk.h"
#include "wch/sys/exti.h"
#include "wch/sys/stk.h"
#include "wch/io/enc.h"

//------------------------------------------------------------------------------

#if !SYS_EXTI
#error "Encoder requires SYS_EXTI = 1"
#endif  /* SYS_EXTI */

//------------------------------------------------------------------------------

#define IO_ENC_STATE(a, b)  (((a) << 7) | ((b) << 6))

//------------------------------------------------------------------------------

void encoder_init(encoder_t* e, bool level_a, bool level_b) {
  e->state = IO_ENC_STATE(level_a, level_b);
  e->timestamp = 0;

  // Enable the EXTI interrupt
  exti_enable_irq();
}

//------------------------------------------------------------------------------

void encoder_update(encoder_t* e, bool level_a, bool level_b) {
  uint8_t state = IO_ENC_STATE(level_a, level_b);
  uint8_t delta = state ^ (e->state & 0xC0);

  if (delta == 1 || delta == 2) {
    // CW/CCW direction
    uint8_t dir = (e->state >> 7) ^ level_b;
    state |= dir << 4;

    // Update timestamp
    uint32_t now = stk_get_count();
    uint32_t tdiff = time_elapsed(now, e->timestamp);
    e->timestamp = now;

    // Calculate steps
    if (tdiff < 1000)      state |= 8;
    else if (tdiff < 3000) state |= 4;
    else if (tdiff < 8000) state |= 2;
    else                   state |= 1;
  }

  e->state = state;
}

//------------------------------------------------------------------------------

#endif  /* IO_ENCODER */
