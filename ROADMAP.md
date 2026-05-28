# ROADMAP — 12-Week DSA Curriculum

A living checklist. Tick items off as you finish them. Order matters — each week builds on the previous.

**Total commitment**: ~3 months at 3–4 hours/day (≈ 250–350 hours).

Legend: `- [ ]` not done · `- [x]` done · 🏁 = phase-end milestone · 🛠️ = phase-end mini-project

---

## Phase 0 — Pre-flight (before Week 1)

- [ ] Read [docs/guidelines.md](docs/guidelines.md) — how to actually work a week (the daily loop + the per-problem workflow)
- [ ] Read [docs/prerequisites.md](docs/prerequisites.md) end-to-end
- [ ] Patch any gaps in: pointers, `malloc`/`free`, structs, references
- [ ] Tooling: comfortable with `gcc -Wall -Wextra`, your debugger (gdb or lldb), AddressSanitizer (`-fsanitize=address`)
- [ ] (Optional) Complete the "student manager" warm-up exercise

---

## Phase 1 — Foundations & Linear Structures (Weeks 1–3) · C

### Week 1 · Complexity & Arrays
- [ ] Big-O, Big-Θ, Big-Ω — what they mean, how to derive them
- [ ] Amortized analysis (dynamic array growth as motivating example)
- [ ] Space complexity (auxiliary vs total)
- [ ] Static arrays in C (memory layout, stack vs heap)
- [ ] Dynamic arrays — implement your own `vector` in C
- [ ] C-style strings — null termination, `strlen`, `strcpy` pitfalls
- [ ] 10 array problems (see `phase-1-foundations/week-01-complexity-arrays/exercises.md`)

### Week 2 · Linked Lists
- [ ] Singly linked list — insert head/tail/middle, delete, search, reverse
- [ ] Doubly linked list
- [ ] Circular linked list
- [ ] Pointer-to-pointer technique (`Node **`)
- [ ] Floyd's cycle detection (tortoise & hare)
- [ ] 10 linked-list problems

### Week 3 · Stacks & Queues
- [ ] Stack (array-backed) — `push`, `pop`, `peek`, dynamic resize
- [ ] Stack (linked-list-backed)
- [ ] Queue (array, circular buffer)
- [ ] Queue (linked-list-backed)
- [ ] Deque (double-ended queue)
- [ ] Applications: balanced parentheses, postfix evaluation, sliding-window basics
- [ ] 10 stack/queue problems

> 🏁 **Milestone M1**: From scratch, implement dynamic array, singly linked list, stack, and queue in C. Explain why dynamic-array push is amortized O(1). Solve 30 cumulative problems.

> 🛠️ **Phase 1 mini-project — Mini terminal text editor (C)**
> Build a line-oriented editor that uses your **doubly linked list** for the document and your **stack** for an undo/redo history. Required commands: insert line, delete line, list with line numbers, undo, redo, save to file, load from file. Compiles clean under `-Wall -Wextra -fsanitize=address` with zero leaks. This forces you to combine multiple structures and handle real edge cases (empty doc, undo past beginning, redo after a new edit invalidates the redo stack).

---

## Phase 2 — Recursion, Sorting & Searching (Weeks 4–5) · C

### Week 4 · Recursion & Backtracking
- [ ] Recursion mechanics — call stack, base case, recursive case
- [ ] Recursion tree analysis
- [ ] Tail recursion (and why C compilers may or may not optimize it)
- [ ] Divide & conquer paradigm
- [ ] Master Theorem (apply it to merge sort, binary search)
- [ ] Backtracking template (subsets, permutations, combinations)
- [ ] Solve N-queens, Sudoku, word search
- [ ] 15 recursion / backtracking problems

### Week 5 · Sorting & Searching
- [ ] Bubble, selection, insertion sort — why they exist, when they win
- [ ] Merge sort (top-down + bottom-up)
- [ ] Quicksort — Lomuto and Hoare partitions, worst-case behavior
- [ ] Heap sort (preview of heaps)
- [ ] Counting sort, radix sort — non-comparison sorts
- [ ] Stability — which sorts are stable, why it matters
- [ ] Binary search — exact match, lower_bound, upper_bound
- [ ] Binary search on rotated array, on answer (parametric search)
- [ ] 10 binary-search problems
- [ ] **Stretch**: external sort — sort a file larger than RAM by chunked sort + k-way merge

> 🏁 **Milestone M2**: Implement merge sort and quick sort from scratch. Write a paragraph explaining when each beats the other. Implement binary search and 3+ non-trivial variants.

> 🛠️ **Phase 2 mini-project — Sorting benchmark suite (C)**
> Implement bubble, insertion, merge, quick, and heap sort in one file. Run each on input sizes `n = 10³, 10⁴, 10⁵, 10⁶` with three input shapes (random, sorted, reverse-sorted). Export results as CSV. Plot with a 10-line Python script (`matplotlib`) and commit the resulting PNG to `phase-2-recursion-sorting/week-05-sorting-searching/benchmarks/`. You'll *see* Big-O with your own eyes — quadratic vs n log n becomes viscerally obvious at n = 10⁵.

---

## Phase 3 — Trees, Heaps & Hashing (Weeks 6–7) · C

### Week 6 · Trees & BSTs
- [ ] Binary tree representation (pointer-based, array-based)
- [ ] Traversals: pre-order, in-order, post-order (recursive + iterative)
- [ ] Level-order (BFS) traversal
- [ ] BST — insert, search, delete (including the tricky two-children case)
- [ ] Validate BST, lowest common ancestor (LCA), diameter
- [ ] AVL conceptually (rotations — implement if time)
- [ ] Red-Black tree conceptually (no need to implement yet)
- [ ] 20 tree problems

### Week 7 · Heaps & Hash Tables
- [ ] Binary heap — array-backed min-heap & max-heap
- [ ] `heapify_up`, `heapify_down`, `build_heap` (O(n) construction)
- [ ] Priority queue API on top of a heap
- [ ] Hash function basics (FNV-1a, djb2 — implement one)
- [ ] Hash table with separate chaining
- [ ] Hash table with open addressing (linear probing) + tombstones
- [ ] Load factor, rehashing
- [ ] 15 heap / hash problems (top-K, two-sum, group-anagrams, k-th largest, …)

> 🏁 **Milestone M3**: Implement min-heap and chained hash table in C from scratch with test cases. Explain load factor and when chaining beats open addressing.

> 🛠️ **Phase 3 mini-project — Trie-based autocomplete engine (C)**
> Load a ~100k-word English dictionary (e.g., `/usr/share/dict/words` or a SCOWL list). Build a **trie** for prefix lookup. For each typed prefix, return the **top-K most relevant completions** ranked by word frequency, using your **min-heap** to keep the running top-K. Time it against a naive `O(N * |prefix|)` linear scan over the dictionary — the trie should be 100–1000× faster. Run with `-fsanitize=address` to prove your trie deallocator is correct.

---

## Phase 4 — Graphs & STL Transition (Weeks 8–9) · C++

### Week 8 · C → C++ and Graph Traversal
- [ ] C++ for C devs cheat-sheet (`vector`, `string`, `unordered_map`, `set`, `priority_queue`, iterators, lambdas, range-for, `auto`)
- [ ] Adjacency list vs adjacency matrix — when to use which
- [ ] BFS — generic template, shortest path in unweighted graph
- [ ] DFS — recursive and iterative
- [ ] Connected components
- [ ] Topological sort (Kahn's algorithm + DFS-based)
- [ ] Cycle detection (directed and undirected)
- [ ] 12 graph problems

### Week 9 · Shortest Paths, MST, DSU
- [ ] Dijkstra's algorithm (with `priority_queue`)
- [ ] Bellman-Ford (handles negative weights, detects negative cycles)
- [ ] Floyd-Warshall (all-pairs)
- [ ] Kruskal's MST
- [ ] Prim's MST
- [ ] Union-Find (DSU) with path compression + union by rank
- [ ] 12 problems mixing the above

> 🏁 **Milestone M4**: Implement BFS, DFS, Dijkstra, and Union-Find as reusable C++ templates. Given a graph problem, identify which algorithm to reach for.

> 🛠️ **Phase 4 mini-project — Route planner (C++)**
> Pick one of:
> - **(a)** Read a small **OpenStreetMap** `.osm` extract (one district / city centre). Build an adjacency list, run **Dijkstra** between two named points.
> - **(b)** If `.osm` parsing feels like a yak-shave, generate a synthetic **grid road network** (1000×1000 nodes, random weights, ~5% blocked cells) and route between random source/target pairs.
>
> Report the path, total cost, and number of nodes visited. **Upgrade path**: implement A* with a heuristic and compare nodes visited vs Dijkstra.

---

## Phase 5 — Advanced Algorithms (Weeks 10–11) · C++

### Week 10 · Dynamic Programming
- [ ] DP intuition — overlapping subproblems + optimal substructure
- [ ] Top-down (memoization) vs bottom-up (tabulation)
- [ ] 1D DP: Fibonacci, climbing stairs, house robber, max-subarray (Kadane)
- [ ] 2D DP: LCS, edit distance, unique paths, min path sum
- [ ] Knapsack 0/1 and unbounded
- [ ] Coin change (count + min coins)
- [ ] Interval DP (matrix-chain multiplication intuition)
- [ ] Bitmask DP intro (traveling salesman small-n)
- [ ] Greedy vs DP — when does greedy fail?
- [ ] 20 canonical DP problems

### Week 11 · Tries, Segment Trees, Strings
- [ ] Trie (prefix tree) — insert, search, starts-with
- [ ] Segment tree — point update, range query
- [ ] Segment tree with lazy propagation (range update, range query)
- [ ] Fenwick tree (BIT)
- [ ] KMP string matching
- [ ] Z-function
- [ ] SCC (Kosaraju or Tarjan) — pick one
- [ ] Max-flow conceptually (Ford-Fulkerson)
- [ ] 10 mixed problems

> 🏁 **Milestone M5**: Write a one-page "DP decision flowchart" in your own words. Implement trie + segment tree from scratch. Solve 5 hard DP problems unaided.

> 🛠️ **Phase 5 mini-project — Mini `diff` tool (C++)**
> Implement a line-level diff between two text files, output in unified-diff format (`-`/`+` prefixes, context lines). Core algorithm: **longest common subsequence** via DP, then walk the table to recover the actual edit script. Test against `/usr/bin/diff` on a few real files — your output should match for simple cases.

---

## Phase 6 — Capstone & Synthesis (Week 12) · C++

### Capstone — pick one (or invent your own)
- [ ] **A.** CLI contact book with trie autocomplete + fuzzy search + JSON persistence
- [ ] **B.** Mini text editor using gap buffer or rope
- [ ] **C.** In-memory key-value store: hash table + LRU eviction (doubly linked list)
- [ ] **D.** Maze generator + solver: DFS to generate, BFS / A* to solve, ASCII rendering

### Review week
- [ ] Re-implement one data structure per day from scratch, no references
- [ ] Write `phase-6-capstone/retro.md` — what stuck, what didn't, what to revisit

> 🏁 **Milestone M6 — Final**: Ship the capstone with a README explaining which DSA concepts power which feature. Whiteboard any of the 6 core structures (dynamic array, linked list, hash table, heap, BST, graph w/ BFS/DFS) with complexity analysis in under 10 minutes.

---

## Post-curriculum (optional, week 13+)

- [ ] Advanced graph: Tarjan's SCC, bridges, articulation points, network flow (Ford-Fulkerson, Edmonds-Karp, Dinic's)
- [ ] Advanced strings: suffix array, suffix automaton, Aho-Corasick
- [ ] Computational geometry: convex hull, line sweep
- [ ] Number-theoretic algorithms: sieve, modular exponentiation, CRT
- [ ] Persistent data structures
- [ ] Skip lists
- [ ] **B-trees / B+ trees** — the on-disk index that runs every relational database. Essential if you want the "mini database engine" capstone.
- [ ] **External-memory / out-of-core algorithms** — external sort, external merge, when data doesn't fit in RAM. Pairs well with the Week 5 stretch goal.
- [ ] **Concurrent data structures** (C++) — atomics, memory ordering, lock-free queue (Treiber stack, Michael-Scott queue). For when you want to bridge DSA into systems / multithreading.
- [ ] **Spatial data structures** — quadtree, k-d tree, R-tree. Useful for game engines, GIS, nearest-neighbor problems.
- [ ] Start contributing to an open-source DSA or systems project to apply what you learned
