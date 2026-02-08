#include "wchsdk_cfg.h"

#if CORE_RING

#include "wch/core/ring.h"

//------------------------------------------------------------------------------

void ring_init(ring_t *ring, uint8_t *buf, uint8_t size) {
  ring->buf = buf;
  ring->size = size;
  ring_flush(ring);
}

//------------------------------------------------------------------------------

bool ring_put(ring_t *ring, uint8_t data) {
  uint32_t next_head = ring_next_head(ring);
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
  
  *data = ring->buf[ring->tail];
  ring->tail = ring->tail % ring->size;
  return true;
}

//------------------------------------------------------------------------------

uint32_t ring_write(ring_t *ring, const uint8_t *data, uint32_t len) {
  uint32_t written = 0;
  while (written < len && ring_put(ring, data[written]))
    written++;
  return written;
}

uint32_t ring_read(ring_t *ring, uint8_t *data, uint32_t len) {
  uint32_t read = 0;
  while (read < len && ring_get(ring, &data[read]))
    read++;
  return read;
}

//------------------------------------------------------------------------------

#endif  /* CORE_RING */
