#if UTIL_LL

#pragma once

#include <stddef.h>

//------------------------------------------------------------------------------

typedef void* ll_node_t;

typedef struct {
  ll_node_t head;
  uint8_t   count;
} ll_list_t;

//------------------------------------------------------------------------------

static inline void ll_init(ll_list_t *list) {
  list->head = NULL;
  list->count = 0;
}

//------------------------------------------------------------------------------

static inline void ll_push(ll_list_t *list, ll_node_t node) {
  *(void**)node = list->head;
  list->head = node;
  list->count++;
}

//------------------------------------------------------------------------------

static inline ll_node_t ll_pop(ll_list_t *list) {
  ll_node_t node = list->head;
  if (!node)
    return NULL;

  list->head = *(void**)node;
  list->count--;
  return node;
}

//------------------------------------------------------------------------------

static inline ll_node_t ll_peek(const ll_list_t *list) {
  return list->head; }

//------------------------------------------------------------------------------

static inline bool ll_is_empty(const ll_list_t *list) {
  return !list->head; }

//------------------------------------------------------------------------------

#endif  /* UTIL_LL */
