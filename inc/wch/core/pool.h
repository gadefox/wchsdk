#if CORE_POOL

#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "wch/core/ll.h"
#include "wch/core/slot.h"

#if !CORE_LL
#error "pool requires CORE_LL = 1"
#endif  /* CORE_LL */

#if !CORE_SLOT
#error "pool requires CORE_SLOT = 1"
#endif  /* CORE_SLOT */

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

#endif  /* CORE_POOL */
