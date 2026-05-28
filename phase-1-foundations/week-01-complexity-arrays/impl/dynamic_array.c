/*
 * dynamic_array.c — implementation + self-test main().
 *
 * Build:  gcc -Wall -Wextra -std=c11 dynamic_array.c -o da_test
 * Run:    ./da_test
 */
#include "dynamic_array.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAP 4
#define GROWTH      2  /* double on resize */

da_t *da_new(void) {
    da_t *v = malloc(sizeof(*v));
    if (!v) { perror("malloc"); exit(EXIT_FAILURE); }
    v->data = NULL;
    v->len  = 0;
    v->cap  = 0;
    return v;
}

void da_free(da_t *v) {
    if (!v) return;
    free(v->data);
    free(v);
}

size_t da_len(const da_t *v) { return v->len; }
size_t da_cap(const da_t *v) { return v->cap; }

void da_reserve(da_t *v, size_t new_cap) {
    if (new_cap <= v->cap) return;
    int *p = realloc(v->data, new_cap * sizeof(*p));
    if (!p) { perror("realloc"); exit(EXIT_FAILURE); }
    v->data = p;
    v->cap  = new_cap;
}

int da_get(const da_t *v, size_t i) {
    assert(i < v->len);
    return v->data[i];
}

void da_set(da_t *v, size_t i, int x) {
    assert(i < v->len);
    v->data[i] = x;
}

void da_push(da_t *v, int x) {
    if (v->len == v->cap) {
        size_t new_cap = v->cap == 0 ? INITIAL_CAP : v->cap * GROWTH;
        da_reserve(v, new_cap);
    }
    v->data[v->len++] = x;
}

int da_pop(da_t *v) {
    assert(v->len > 0);
    return v->data[--v->len];
}

/* -------------------- self-test driver -------------------- */
#ifndef DA_NO_MAIN
int main(void) {
    da_t *v = da_new();
    assert(da_len(v) == 0);
    assert(da_cap(v) == 0);

    /* push enough to force several doublings: 0 -> 4 -> 8 -> 16 */
    for (int i = 0; i < 10; i++) da_push(v, i * i);
    assert(da_len(v) == 10);
    assert(da_cap(v) >= 10);

    /* random access */
    assert(da_get(v, 0) == 0);
    assert(da_get(v, 3) == 9);
    assert(da_get(v, 9) == 81);

    /* set */
    da_set(v, 5, -42);
    assert(da_get(v, 5) == -42);

    /* pop returns the last */
    assert(da_pop(v) == 81);
    assert(da_len(v) == 9);

    /* reserve doesn't shrink and is idempotent above current cap */
    size_t old_cap = da_cap(v);
    da_reserve(v, old_cap - 1);
    assert(da_cap(v) == old_cap);
    da_reserve(v, 100);
    assert(da_cap(v) >= 100);
    assert(da_len(v) == 9);  /* len unchanged */

    printf("dynamic_array: OK  (len=%zu cap=%zu)\n", da_len(v), da_cap(v));
    da_free(v);
    return 0;
}
#endif
