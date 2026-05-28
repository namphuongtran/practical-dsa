# Week 1 — Complexity Analysis & Arrays

> Build the vocabulary you'll use for the next 11 weeks: Big-O, the amortized analysis trick, static vs dynamic arrays, and C-style strings.

---

## 0. Set up your tooling once

Before solving anything, get these working — they pay off across all 12 weeks.

```bash
# Compile with warnings + AddressSanitizer + debug symbols
gcc -Wall -Wextra -std=c11 -g -fsanitize=address foo.c -o foo
./foo                # ASan will catch overflows, leaks, use-after-free

# Step through with a debugger
gdb ./foo            # Linux / cross-platform
lldb ./foo           # macOS default

# A 6-command starter kit (works in both gdb and lldb with minor name differences):
#   break <line> / b <line>           set a breakpoint
#   run / r                           start the program
#   next / n                          step over
#   step / s                          step into
#   print <var> / p <var>             inspect a variable
#   backtrace / bt                    show the call stack
```

If you're on Linux, also install **Valgrind**: `valgrind --leak-check=full ./foo` is the classic memory-leak detector. On macOS, prefer `-fsanitize=address`.

**Habit**: every solution file in this repo should compile cleanly under `-Wall -Wextra -fsanitize=address` with **zero warnings**.

---

## 1. Complexity analysis

### Big-O, Big-Θ, Big-Ω in one breath

For a function `T(n)` describing an algorithm's running time on input size `n`:

| Notation | Meaning (informal) | Meaning (formal) |
|----------|--------------------|------------------|
| `O(f(n))` | upper bound — "no worse than" | ∃ c, n₀ : T(n) ≤ c·f(n) for all n ≥ n₀ |
| `Ω(f(n))` | lower bound — "at least as bad as" | ∃ c, n₀ : T(n) ≥ c·f(n) for all n ≥ n₀ |
| `Θ(f(n))` | tight bound — both O and Ω | T(n) is O(f) **and** Ω(f) |

In practice people say "O" but usually mean Θ. That's fine for now — just know the difference exists.

### Common growth rates, ordered

```
O(1) < O(log n) < O(√n) < O(n) < O(n log n) < O(n²) < O(n³) < O(2ⁿ) < O(n!)
```

Memorize this ordering. Every complexity claim you'll ever make compares against this ladder.

### Drop constants and lower-order terms

`5n² + 100n + 7` → `O(n²)`. Always.

### Amortized analysis — the dynamic-array trick

A dynamic array (Java `ArrayList`, C++ `std::vector`, Python `list`, our `da_t` below) doubles its capacity when full. A single `push` that triggers a doubling does O(n) work copying old → new. So worst case is O(n). But — *averaged across many pushes* — each push pays only O(1).

**Why.** Suppose we push `n` elements starting from capacity 1. The doublings happen at sizes 1, 2, 4, 8, …, n/2. The total copy cost is `1 + 2 + 4 + … + n/2 < n`. So `n` pushes cost less than `2n` work total. Divide by `n`: each push pays **amortized O(1)**.

This is *the* canonical amortized argument. Internalize it.

### Space complexity

- **Total**: all memory the algorithm touches (input + work).
- **Auxiliary**: only the extra memory beyond the input. This is the one people usually mean.

Merge sort has O(n) auxiliary space; in-place quick sort has O(log n) auxiliary (the recursion stack).

---

## 2. Static arrays in C

```c
int  a[10];                  /* stack, fixed size 10, uninitialized */
int  b[5] = {1, 2, 3};       /* {1,2,3,0,0} */
int  c[]  = {1, 2, 3};       /* size inferred = 3 */
```

Layout: 10 `int`s, contiguous in memory, at addresses `&a[0]`, `&a[0]+sizeof(int)`, …

**Key facts**
- Indexing is O(1) — `a[i]` becomes `*(a + i)`, a pointer add + a load.
- Size is *not* stored — `sizeof(a)/sizeof(a[0])` works only inside the scope where the array was declared.
- Passing an array to a function decays it to a pointer; you lose the size. Always pass the size explicitly.

```c
void print(int *arr, size_t n) { for (size_t i = 0; i < n; i++) printf("%d ", arr[i]); }
```

### Stack vs heap

```c
int a[1000];                          /* stack — auto-freed at scope end */
int *b = malloc(1000 * sizeof(int));  /* heap — YOU free it */
free(b);
```

Rule: if size is known at compile-time and modest (< a few KB), stack. Otherwise, heap.

---

## 3. Dynamic arrays in C — your own `vector`

A dynamic array is a struct holding (pointer, length, capacity):

```c
typedef struct {
    int   *data;
    size_t len;
    size_t cap;
} da_t;
```

Operations:

| Op             | Complexity         | Notes |
|----------------|--------------------|-------|
| `da_push(v,x)` | amortized O(1)     | doubles capacity when full |
| `da_pop(v)`    | O(1)               | shrink optional |
| `da_get(v,i)`  | O(1)               | bounds-check in debug builds |
| `da_set(v,i,x)`| O(1)               | bounds-check in debug builds |

See `impl/dynamic_array.h` and `impl/dynamic_array.c`. The test driver in `main()` exercises every operation including a forced resize.

---

## 4. C-style strings (sneak preview — full coverage is implicit through all of Phase 1)

In C, a "string" is just `char *` pointing to a null-terminated (`'\0'`) sequence of bytes.

```c
char  s1[] = "hello";          /* 6 bytes: h e l l o \0 */
char *s2   = "hello";          /* literal — DO NOT modify, undefined behavior */
char  s3[10] = "hi";           /* {h,i,\0, ?,?,?,?,?,?,?} — rest indeterminate */
```

**Gotchas**:
- `strlen` is O(n) — it walks until `\0`. Cache the length if you'll need it repeatedly.
- `strcpy` is famously unsafe: if the destination is too small, it'll happily overrun the buffer. Use `strncpy` (and even that has surprises — it may not null-terminate). Or in modern code, `snprintf`.
- The pattern `for (int i = 0; s[i]; i++) ...` works because of `'\0'` being falsy.

We'll come back to strings in Week 2 (linked list of characters? gap buffer in capstone?) and again in Week 11 (KMP, Z-function).

---

## Common pitfalls (Week 1)

- **Forgetting to free** — every `malloc` needs exactly one `free`. Run under Valgrind / ASan.
- **Off-by-one in `cap` vs `len`** — `len <= cap` is invariant; `len == cap` triggers the resize.
- **Reading past the end** of a static array — silent undefined behavior, not a crash. Use AddressSanitizer (`-fsanitize=address`).
- **Returning a pointer to a local array** — the array is on the stack; it dies when the function returns.
- **Confusing `sizeof(int *)` with `sizeof(int [N])`** — the first is a pointer size (8 on x86-64); the second is `N * sizeof(int)`.

---

## Mental model

> **An array is a contiguous run of identical-sized cells. A dynamic array is "the same, but I'll move it to a bigger room when it gets full." Random access is O(1) because we can multiply our way to any element.**

---

## Problems for this week

See [`exercises.md`](exercises.md). One is fully worked in [`problems/01_two_sum.c`](problems/01_two_sum.c) as an example of the file shape.

---

## Further reading

- *Algorithms 4e* (Sedgewick), §1.4 — Analysis of Algorithms
- *Algorithm Design Manual* (Skiena), §1.3 — RAM Model of Computation
- CP-Algorithms — [Sliding Window Maximum](https://cp-algorithms.com/data_structures/deque.html) (preview of where arrays end and deques begin)
