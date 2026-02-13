#include "wchsdk_cfg.h"

#if UTIL_RING

#include "wch/core/ring.h"

//------------------------------------------------------------------------------

void ring_init(ring_t *ring, uint8_t *buf, uint8_t size) {
  ring->buf = buf;
  ring->size = size;
  ring_flush(ring);
}

//------------------------------------------------------------------------------

bool ring_put(ring_t *ring, uint8_t data) {
  uint32_t next_head = ring_next_head(ring, 1);
  if (next_head == ring->tail)
    return false; // Full

  ring->buf[ring->head] = data;
  ring->head = next_head;
  return true;
}

//------------------------------------------------------------------------------

bool ring_get(ring_t *ring, uint8_t *data) {
  if (ring_is_empty(ring))
    return false; // Empty
  
  *data = ring_peek(ring);
  ring->tail = ring_next_tail(ring, 1);
  return true;
}

//------------------------------------------------------------------------------

uint32_t ring_write(ring_t *ring, const uint8_t *data, uint32_t len) {
  uint32_t written = 0;
  while (written < len && ring_put(ring, data[written]))
    written++;
  return written;
}

//------------------------------------------------------------------------------

uint32_t ring_read(ring_t *ring, uint8_t *data, uint32_t len) {
  uint32_t read = 0;
  while (read < len && ring_get(ring, &data[read]))
    read++;
  return read;
}

//------------------------------------------------------------------------------

uint8_t ring_snapshot(ring_t *ring, uint8_t count) {
  uint8_t new_head = (ring->size - count) % ring->size;
  uint8_t new_count;

  if (new_head >= ring->head)
    new_count = new_head - ring->head;               // no wrap
  else
    new_count = ring->size - ring->head + new_head;  // wrapped around

  ring->head = new_head;
  return new_count;
}

//------------------------------------------------------------------------------

#endif  /* UTIL_RING */
