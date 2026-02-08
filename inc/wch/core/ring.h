#pragma once

#if CORE_RING

#include <stdbool.h>
#include <stdint.h>

//------------------------------------------------------------------------------
// Ring Buffer struct

typedef struct {
  uint8_t         *buf;
  uint8_t          size;
  volatile uint8_t head;
  volatile uint8_t tail;
} ring_t;

//------------------------------------------------------------------------------

void ring_init(ring_t *ring, uint8_t *buf, uint8_t size);
bool ring_put(ring_t *ring, uint8_t data);
bool ring_get(ring_t *ring, uint8_t *data);

//------------------------------------------------------------------------------

static inline uint8_t ring_count(const ring_t *ring) {
  if (ring->head >= ring->tail)
    return ring->head - ring->tail;
  return ring->size - ring->tail + ring->head; }

static inline uint8_t ring_free_count(const ring_t *ring) {
  return ring->size - ring_count(ring) - 1; }  // -1 because we waste one slot

static inline bool ring_is_empty(const ring_t *ring) {
  return ring->head == ring->tail; }

static inline uint8_t ring_next_head(const ring_t *ring) {
  return (ring->head + 1) % ring->size; }

static inline bool ring_is_full(const ring_t *ring) {
  return ring_next_head(ring) == ring->tail; }

static inline void ring_flush(ring_t *ring) {
  ring->head = 0;
  ring->tail = 0; }

//------------------------------------------------------------------------------
uint32_t ring_write(ring_t *ring, const uint8_t *data, uint32_t len);
uint32_t ring_read(ring_t *ring, uint8_t *data, uint32_t len);

//------------------------------------------------------------------------------

#endif  /* CORE_RING */
