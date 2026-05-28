# Week 8 — C → C++ Transition · Graph Traversal

> Stub — fill in as you study. See `../../templates/notes-template.md`.

## Topics to cover

### Half 1 — "C++ for C devs" cheat-sheet
- [ ] `std::vector<T>` — your dynamic array, for free
- [ ] `std::string`
- [ ] `std::unordered_map<K,V>` — hash table, for free
- [ ] `std::set<T>` / `std::map<K,V>` — balanced BST under the hood
- [ ] `std::priority_queue<T>` — heap, for free
- [ ] Iterators, range-for, `auto`, lambdas — just enough
- [ ] References vs pointers; `&` vs `*`; `nullptr` vs `NULL`

### Half 2 — Graphs
- [ ] Representations: adjacency list, adjacency matrix, edge list — when to use which
- [ ] BFS — generic template; shortest path in unweighted graphs
- [ ] DFS — recursive and iterative (explicit stack)
- [ ] Connected components
- [ ] Topological sort (Kahn's algorithm + DFS-based)
- [ ] Cycle detection — directed (3-color) and undirected (DFS parent check)

## Deliverables
- `impl/cpp_cheatsheet.cpp` — your own C-to-C++ reference snippets
- `impl/bfs.cpp`, `impl/dfs.cpp`, `impl/topo_sort.cpp` (templated, reusable)
- 12 graph problems

## Mental model
> A graph is "anything with relationships." BFS is "rings of distance from the start." DFS is "follow this path as far as it goes, then back up."
