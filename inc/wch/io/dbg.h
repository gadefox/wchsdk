#pragma once

#if IO_DBG

#include <stdbool.h>
#include <stdint.h>

//------------------------------------------------------------------------------

#ifndef IO_DBG_TIMEOUT
#define IO_DBG_TIMEOUT  0x100000
#endif

//------------------------------------------------------------------------------

// Returns 1 if a debugger has activated the debug module.
#define dbg_is_attached()      (!DBG->DMSTATUS)
#define dbg_buffer_is_empty()  (!(DBG->DMDATA0 & 0x80))

//------------------------------------------------------------------------------

void dbg_init(void);
void dbg_poll_input(void);

//------------------------------------------------------------------------------

#if IO_DBG_HARDFAULT

// Print a hexadecimal value to the debug depending on configuration.
void dbg_print_hex(uint32_t n);

#endif  /* IFACE_DBG_HARDFAULT */

//------------------------------------------------------------------------------

__attribute__((weak)) int dbg_put_str(const char *buf, int size);
__attribute__((weak)) bool dbg_put(int c);

//------------------------------------------------------------------------------
// Returns 1 if timeout reached, 0 otherwise.

bool dbg_wait_to_attach(int timeout_ms);

//------------------------------------------------------------------------------

#endif  /* IO_DBG */
