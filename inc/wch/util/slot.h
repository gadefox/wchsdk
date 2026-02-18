#if UTIL_POOL

#pragma once

#include <stdint.h>

//------------------------------------------------------------------------------
// Slot status: FREE, USED, or PENDING

#define SLOT_FREE     0
#define SLOT_USED     1
#define SLOT_PENDING  2

//------------------------------------------------------------------------------

typedef struct slot {
  struct slot* next;      // must be first
  uint8_t      pool;      // pool id
  uint8_t      status;    // current state
  // user data follows immediately after
} slot_t;

//------------------------------------------------------------------------------
// Get pointer to user data from slot

static inline void* slot_data(slot_t *slot) {
  return (void*)((uint8_t*)slot + sizeof(slot_t)); }

//------------------------------------------------------------------------------
// Get slot header from user data pointer

static inline slot_t* slot_from_data(void *data) {
  return (slot_t*)((uint8_t*)data - sizeof(slot_t)); }

//------------------------------------------------------------------------------
// Initialize a slot (mark as free, link to next)

static inline void slot_init(slot_t *slot, uint8_t pool) {
  slot->next = NULL;
  slot->pool = pool;
  slot->status = SLOT_FREE; }

//------------------------------------------------------------------------------

#endif  /* UTIL_POOL */
