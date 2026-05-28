/*
 * dynamic_array.h — a minimal vector<int> in C.
 *
 * Invariant: 0 <= len <= cap.  data != NULL iff cap > 0.
 *
 * All operations on a NULL pointer are undefined behavior — callers must
 * pass a valid da_t* (typically from da_new).
 */
#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stddef.h>

typedef struct {
    int   *data;
    size_t len;
    size_t cap;
} da_t;

/* Construct / destruct. */
da_t  *da_new(void);                 /* allocate empty da on the heap */
void   da_free(da_t *v);             /* free internal buffer + struct */

/* Capacity. */
size_t da_len(const da_t *v);
size_t da_cap(const da_t *v);
void   da_reserve(da_t *v, size_t new_cap);   /* grow cap to at least new_cap */

/* Element access — no bounds check in release; assert in debug. */
int    da_get(const da_t *v, size_t i);
void   da_set(da_t *v, size_t i, int x);

/* Mutation. */
void   da_push(da_t *v, int x);     /* amortized O(1) */
int    da_pop(da_t *v);             /* O(1); UB if empty */

#endif /* DYNAMIC_ARRAY_H */
