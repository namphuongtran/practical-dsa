# Week 9 — Shortest Paths, MST, Union-Find

> Stub — fill in as you study. See `../../templates/notes-template.md`.

## Topics to cover
- [ ] Dijkstra's algorithm — with `std::priority_queue`
- [ ] Why Dijkstra fails on negative edges
- [ ] Bellman-Ford — handles negative edges, detects negative cycles
- [ ] Floyd-Warshall — all-pairs shortest paths in O(V³)
- [ ] MST: Kruskal's algorithm (sort edges + DSU)
- [ ] MST: Prim's algorithm (priority queue from a starting vertex)
- [ ] Union-Find (DSU) with path compression + union by rank — near-O(1) amortized

## Deliverables
- `impl/dsu.cpp` — Union-Find with both optimizations + test main
- `impl/dijkstra.cpp`
- `impl/kruskal.cpp`
- 12 problems

## Mental model
> Dijkstra greedily settles the closest unsettled node. Bellman-Ford relaxes every edge n−1 times because pessimism. Union-Find is "two groups merge by pointing one root at the other."
