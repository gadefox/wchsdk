#include "wchsdk_cfg.h"

#if UTIL_POOL

#include "wch/util/pool.h"

//------------------------------------------------------------------------------

static uint8_t free_pool_id;

//------------------------------------------------------------------------------

void pool_init(pool_t *pool, uint8_t *block, uint8_t num_slots, uint16_t slot_size) {
  pool->id = free_pool_id++;
  pool->num_slots = num_slots;
  pool->slot_size = slot_size;
  
  ll_init(&pool->free_list);
  
  // Link all slots into free list
  for (uint32_t i = 0; i < num_slots; i++) {
    slot_t *slot = (slot_t*)block;
    slot_init(slot, pool->id);

    ll_push(&pool->free_list, slot);
    block += slot_size;
  }
}

//------------------------------------------------------------------------------

void* pool_alloc(pool_t *pool) {
  slot_t *slot = (slot_t*)ll_pop(&pool->free_list);
  if (!slot)
    return NULL;
  
  slot->status = SLOT_USED;
  return slot_data(slot);
}

//------------------------------------------------------------------------------

bool pool_free(pool_t *pool, void *data) {
  if (!data)
    return false;
  
  slot_t *slot = slot_from_data(data);
  
  // Validate slot is from this pool
  if (slot->pool != pool->id)
    return false;
  
  // Check for double free
  if (slot->status != SLOT_USED)
    return false;
  
  ll_push(&pool->free_list, slot);
  slot->status = SLOT_FREE;
  return true;
}

//------------------------------------------------------------------------------

#endif  /* UTIL_POOL */
