# Week 7 — Heaps & Hash Tables

> Stub — fill in as you study. See `../../templates/notes-template.md`.

## Topics to cover
- [ ] Binary heap — array-backed min-heap and max-heap
- [ ] `heapify_up`, `heapify_down`, `build_heap` in O(n) (not O(n log n)!)
- [ ] Priority queue API on top of a heap
- [ ] Hash function basics — pick one to implement (FNV-1a or djb2)
- [ ] Hash table with separate chaining (linked list per bucket)
- [ ] Hash table with open addressing (linear probing + tombstones)
- [ ] Load factor, rehashing (the "amortized O(1)" trick again — same idea as Week 1's dynamic array)
- [ ] When chaining beats open addressing (and vice versa)

## Deliverables
- `impl/heap.c` — min-heap, with test main
- `impl/hashtable_chaining.c`
- `impl/hashtable_open.c`
- 15 problems (top-K via heap, two-sum via hash, group anagrams, k-th largest, …)

## Mental model
> A heap is "I don't care about full ordering, I just want the extremum fast." A hash table is "I bought O(1) lookup with the cost of a good hash function and some collision pain."
