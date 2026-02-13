#pragma once

#if UTIL_RING

#include <stdbool.h>
#include <stdint.h>

//------------------------------------------------------------------------------
// NOTE: Size is deliberately limited to a byte. The MCU has just 2 KiB of RAM.

typedef struct {
  uint8_t         *buf;     // pointer to buffer memory
  uint8_t          size;    // buffer size in bytes
  volatile uint8_t head;    // write position
  volatile uint8_t tail;    // read position
} ring_t;

//------------------------------------------------------------------------------

void ring_init(ring_t *ring, uint8_t *buf, uint8_t size);
bool ring_put(ring_t *ring, uint8_t data);
bool ring_get(ring_t *ring, uint8_t *data);

//------------------------------------------------------------------------------
// Returns the number of bytes currently in the ring buffer (ready to read).

static inline uint8_t ring_count(const ring_t *ring) {
  if (ring->head >= ring->tail)
    return ring->head - ring->tail;
  return ring->size - ring->tail + ring->head; }

//------------------------------------------------------------------------------
// Returns the number of free slots left in the ring buffer (available for writing).
// NOTE: We waste one slot to distinguish full vs empty.

static inline uint8_t ring_free_count(const ring_t *ring) {
  return ring->size - ring_count(ring) - 1; }  // -1 because we waste one slot

//------------------------------------------------------------------------------
// Returns number of contiguous bytes available from tail to the end of buffer

static inline uint8_t ring_linear_count(const ring_t *ring) {
  if (ring->head > ring->tail)
    return ring->head - ring->tail;
  return ring->size - ring->tail; }

//------------------------------------------------------------------------------
// Returns number of new bytes written by DMA/producer since last snapshot
// Does not advance tail, just gives a snapshot.

uint8_t ring_snapshot(ring_t *ring, uint8_t count);

//------------------------------------------------------------------------------

static inline uint8_t ring_next_head(const ring_t *ring, uint8_t d) {
  return (ring->head + d) % ring->size; }

static inline void ring_shift_head(ring_t *ring, uint8_t d) {
  ring->head = ring_next_head(ring, d); }

//------------------------------------------------------------------------------

static inline uint8_t ring_next_tail(const ring_t *ring, uint8_t d) {
  return (ring->tail + d) % ring->size; }

static inline void ring_shift_tail(ring_t *ring, uint8_t d) {
  ring->tail = ring_next_tail(ring, d); }

//------------------------------------------------------------------------------

static inline bool ring_is_empty(const ring_t *ring) {
  return ring->head == ring->tail; }

static inline bool ring_is_full(const ring_t *ring) {
  return ring_next_head(ring, 1) == ring->tail; }

//------------------------------------------------------------------------------

static inline uint8_t* ring_head_ptr(const ring_t *ring) {
  return ring->buf + ring->head; }

static inline uint8_t* ring_tail_ptr(const ring_t *ring) {
  return ring->buf + ring->tail; }

static inline uint8_t ring_peek(const ring_t *ring) {
  return ring->buf[ring->tail]; }

//------------------------------------------------------------------------------

static inline void ring_flush(ring_t *ring) {
  ring->head = 0;
  ring->tail = 0; }


//------------------------------------------------------------------------------
uint32_t ring_write(ring_t *ring, const uint8_t *data, uint32_t len);
uint32_t ring_read(ring_t *ring, uint8_t *data, uint32_t len);

//------------------------------------------------------------------------------

#endif  /* UTIL_RING */
