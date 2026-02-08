#include "wchsdk_cfg.h"
#include "wch/core/pool.h"
#include "wch/sys/init.h"

typedef struct {
  slot_t   slot;
  uint16_t year;
  uint32_t data;
} data_t;

#define NUM_SLOTS  4

// Aligned memory buffer for the pool
static uint8_t block[NUM_SLOTS * sizeof(data_t)];

int main(void) {
  pool_t pool;

  sys_init();

  // Initialize the pool
  pool_init(&pool, block, NUM_SLOTS, sizeof(slot_t));

//  printf("INIT: free=%lu used=%lu\n", pool_available(&pool), pool_used(&pool));

  void *ptr[NUM_SLOTS + 1];

  // Allocate all slots
  for (int i = 0; i < NUM_SLOTS; i++) {
    ptr[i] = pool_alloc(&pool);
//    printf("ALLOC %d -> %p\n", i, ptr[i]);
  }

//  printf("AFTER FULL: free=%lu used=%lu\n", pool_available(&pool), pool_used(&pool));

  // Attempt to allocate one more (should fail)
  ptr[NUM_SLOTS] = pool_alloc(&pool);
//  printf("OVERALLOC -> %p (should be NULL)\n", ptr[NUM_SLOTS]);

  // Free all slots
  for (int i = 0; i < NUM_SLOTS; i++) {
    bool ok = pool_free(&pool, ptr[i]);
//    printf("FREE %d -> %s\n", i, ok ? "OK" : "FAIL");
  }

//  printf("AFTER FREE: free=%lu used=%lu\n", pool_available(&pool), pool_used(&pool));

  // Double free test
  bool df = pool_free(&pool, ptr[0]);
//  printf("DOUBLE FREE -> %s (should be FAIL)\n", df ? "OK" : "FAIL");

  // Pointer check for something not in pool
  int dummy;
//  printf("IS FROM POOL (dummy) -> %s\n", pool_is_from_pool(&pool, &dummy) ? "YES" : "NO");
//
  return 0;
}
