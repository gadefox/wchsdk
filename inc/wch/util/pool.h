#if UTIL_POOL

#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "wch/util/ll.h"
#include "wch/util/slot.h"

//------------------------------------------------------------------------------

#if !UTIL_LL
#error "pool requires UTIL_LL = 1"
#endif  /* UTIL_LL */

//------------------------------------------------------------------------------

typedef struct {
  uint8_t   id;
  ll_list_t free_list;       // linked list of free slots
  uint8_t   num_slots;       // total number of slots
  uint16_t  slot_size;       // slot size including user data
} pool_t;

//------------------------------------------------------------------------------
// Initialize pool with pre-allocated memory
// NOTE: memory for blocks must be at least:
//  num_slots * (sizeof(slot_t) + slot_size)

void pool_init(pool_t *pool, uint8_t *block, uint8_t num_slots, uint16_t slot_size);

//------------------------------------------------------------------------------
// Allocate a slot from pool (returns user data pointer)

void* pool_alloc(pool_t *pool);

//------------------------------------------------------------------------------
// Free a slot back to pool (takes user data pointer)

bool pool_free(pool_t *pool, void *data);

//------------------------------------------------------------------------------
// Helper functions

static inline uint32_t pool_used(const pool_t *pool) {
  return pool->num_slots - pool->free_list.count; }

static inline bool pool_is_empty(const pool_t *pool) {
  return pool->free_list.count == pool->num_slots; }

//------------------------------------------------------------------------------

#endif  /* UTIL_POOL */
