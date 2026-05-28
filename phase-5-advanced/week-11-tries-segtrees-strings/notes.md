# Week 11 — Tries, Segment Trees, String Algorithms

> Stub — fill in as you study. See `../../templates/notes-template.md`.

## Topics to cover
- [ ] Trie (prefix tree) — insert, search, starts-with, autocomplete
- [ ] Segment tree — point update, range query
- [ ] Segment tree with lazy propagation — range update, range query
- [ ] Fenwick tree (BIT) — slicker for prefix-sum-style problems
- [ ] String matching: KMP (failure function)
- [ ] Z-function — alternative pattern-matching tool
- [ ] SCC — pick one of Kosaraju or Tarjan, implement it
- [ ] Max-flow conceptually (Ford-Fulkerson) — no need to implement yet

## Deliverables
- `impl/trie.cpp`
- `impl/segment_tree.cpp` (point + range versions)
- `impl/kmp.cpp`
- 10 mixed problems

## Mental model
> A trie is "shared prefixes share nodes." A segment tree is "I cut the array into a binary tree of summaries so any range query is O(log n)."
