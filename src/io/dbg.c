#include "wchsdk_cfg.h"

#if IO_DBG

#include "wch/hw/dbg.h"
#include "wch/hw/stk.h"
#include "wch/sys/def.h"
#include "wch/io/dbg.h"

//------------------------------------------------------------------------------

#if IO_DBG_HARDFAULT

void dbg_print_hex(uint32_t n) {
  while (!debug_buffer_is_empty())
    ;
  // Write out character.
  DBG->DMDATA0 = 0x78302088; //" 0x"

  int shift;
  for (shift = 28; shift >= 0; shift -= 4) {
    while (!debug_buffer_is_empty())
      ;
    int s = (n >> shift) & 0xF;
    s += s < 10 ? '0' : 'a' - 10;
    DBG->DMDATA0 = (s << 8) | 0x85; //" 0x"
  }
}

#endif  /* IO_DBG_HARDFAULT */

//------------------------------------------------------------------------------

static void handle_input(void) {
  int bytes = (DBG->DMDATA0 & 0x3F) - 4;
  if (bytes > 0 && bytes < 16)
   ; // FIXME:
//    handle_debug_input(bytes, DBG->DMDATA0 /*+ 1???*/);
}

//------------------------------------------------------------------------------

void dbg_poll_input(void) {
  if (!debug_buffer_is_empty()) {
    handle_input();
    DBG->DMDATA0 = 0x84;
  }
}

//------------------------------------------------------------------------------
//           MSB .... LSB
// DMDATA0: char3 char2 char1 [status word]
// where [status word] is:
//   bit 7 = is a "printf" waiting?
//   bit 6 = printf has timed out.
//   bit 0..bit 3 = # of bytes in printf (+4).  (5 or higher indicates a print of some kind)
//     note: if b7 is 0 in reply, but b0..b3 have >=4 then we received data from host.
// Special sentinel:
//     status word = 0x80 = default at start
//     status word = 0xcx = timed out.
// declare as weak to allow overriding.

__attribute__((weak))
int dbg_put_str(const char *buf, int size) {
  if ((DBG->DMDATA0 & 0xC0) == 0xC0)
    return 0;

  char buffer[4] = {0};
  int place = 0;
  uint32_t timeout = DEBUG_TIMEOUT; // Give up after ~120ms

  if (size == 0) {
    if (!debug_buffer_is_empty())
      handle_input();
  }

  while (place < size) {
    int tosend = size - place;
    if (tosend > 7)
      tosend = 7;

    while (true) {
      if (!debug_buffer_is_empty())
        break;

      if (timeout-- == 0) {
        DBG->DMDATA0 |= 0xC0;
        return 0;
      }
    }

    // FIXME:
//    if (lastdmd)
      handle_input();

    timeout = DEBUG_TIMEOUT;

    int t = 3;
    while (t < tosend) {
      buffer[t - 3] = buf[t + place];
      t++;
    }
    DBG->DMDATA1 = *(uint32_t *)&buffer[0];
    t = 0;
    while (t < tosend && t < 3) {
      buffer[t + 1] = buf[t + place];
      t++;
    }
    buffer[0] = (tosend + 4) | 0x80;
    DBG->DMDATA0 = *(uint32_t *)&buffer[0];

    // buf += tosend;
    place += tosend;
  }
  return size;
}

//------------------------------------------------------------------------------

// single to debug intf
__attribute__((weak))
bool dbg_put(int c) {
  if ((DBG->DMDATA0 & 0xC0) == 0xC0)
    return false;

  int timeout = DEBUG_TIMEOUT;

  while (true) {
    if (!debug_buffer_is_empty())
      break;

    if (timeout-- == 0) {
      DBG->DMDATA0 |= 0xC0;
      return false;
    }
  }

  // Simply seeking input.
  // FIXME:
//  if (lastdmd)
    handle_input();

  // Write out character.
  DBG->DMDATA0 = 0x85 | ((const char)c << 8);
  return true;
}

//------------------------------------------------------------------------------

void dbg_init(void) {
  // Clear out the sending flag.
  DBG->DMDATA1 = 0x00;
  DBG->DMDATA0 = 0x80;
}

//------------------------------------------------------------------------------

bool dbg_wait_to_attach(int timeout_ms) {
  const uint32_t start = STK->CNT;
  const uint32_t timeout_cycles = ms_to_cycles(timeout_ms);

  // Wait for the sentinel to become zero.
  while (!dbg_is_attached()) {
    if (time_elapsed32(STK->CNT, start) > timeout_cycles)
      return true;
  }
  return false;
}

//------------------------------------------------------------------------------

#endif  /* IO_DBG */
