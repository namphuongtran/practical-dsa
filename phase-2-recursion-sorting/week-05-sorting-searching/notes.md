# Week 5 — Sorting & Searching

> Stub — fill in as you study. See `../../templates/notes-template.md`.

## Topics to cover
- [ ] Comparison sorts: bubble, selection, insertion (and *why* they still exist)
- [ ] Merge sort — top-down recursive + bottom-up iterative
- [ ] Quicksort — Lomuto partition, Hoare partition, median-of-three pivot
- [ ] Heap sort (preview of Week 7's heap)
- [ ] Non-comparison sorts: counting sort, radix sort — beat the Ω(n log n) lower bound by exploiting structure
- [ ] Stability: which sorts are stable, when stability matters (multi-key sorting)
- [ ] Binary search — exact, lower_bound, upper_bound
- [ ] Binary search on rotated array
- [ ] Binary search on the answer (parametric search) — Aggressive Cows, Capacity to Ship Packages

## Deliverables
- `impl/sorting.c` with all algorithms benchmarked side-by-side
- `impl/binary_search.c` (the variants matter as much as the basic version)
- 10 binary-search problems

## Mental model
> Sorting is "what work can I do once so all my future queries become trivial?" Binary search is "every guess halves the remaining space."
