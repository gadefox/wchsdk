// User-configurable macros (see wchsdk_cfg.h):

#pragma once

#if IO_ENCODER

#include <stdbool.h>
#include <stdint.h>

//------------------------------------------------------------------------------

#define IO_ENC_STEP(s)  ((s) & 0x0F)  // bit 0–3 = step
#define IO_ENC_CW(s)    ((s) & 0x10)  // bit 4 = CW direction

//------------------------------------------------------------------------------

typedef struct {
  uint8_t state;
  uint32_t timestamp;
} encoder_t;

//------------------------------------------------------------------------------

void encoder_init(encoder_t* e, bool level_a, bool level_b);
void encoder_update(encoder_t* e, bool level_a, bool level_b);

//------------------------------------------------------------------------------

#endif  /* IO_ENCODER */
