# practical-dsa

> A 12-week, hands-on journey through **Data Structures & Algorithms** in **C and C++** — built to *understand*, not just memorize.

[![Language](https://img.shields.io/badge/language-C%20%7C%20C%2B%2B-blue)](#language-strategy)
[![Status](https://img.shields.io/badge/status-in%20progress-yellow)](docs/progress.md)
[![License](https://img.shields.io/badge/license-MIT-green)](LICENSE)

---

## Why this repo exists

Most DSA resources push you toward two things: memorizing patterns for interviews, or grinding LeetCode for speed. This repo takes a different angle — **deep computer-science understanding first**. You implement every fundamental data structure in C, from raw pointers, before you ever touch an STL container. By the time you switch to C++ for advanced algorithms, you actually know what `std::unordered_map` is doing under the hood. The goal is to internalize DSA so well that it shows up naturally in everything you build afterwards — systems programming, backend services, embedded, anything.

This is a public study log. If you're learning DSA too, fork it, follow along, open an issue to study together, or submit alternative solutions to any problem. See [CONTRIBUTING.md](CONTRIBUTING.md).

---

## Curriculum at a glance

| Phase | Weeks | Focus | Language | Folder |
|-------|-------|-------|----------|--------|
| 0 | (pre-flight) | C/C++ + tooling readiness checklist | — | [docs/prerequisites.md](docs/prerequisites.md) |
| 1 | 1–3 | Foundations & linear data structures | C | [phase-1-foundations](phase-1-foundations/) |
| 2 | 4–5 | Recursion, sorting & searching | C | [phase-2-recursion-sorting](phase-2-recursion-sorting/) |
| 3 | 6–7 | Trees, heaps & hashing | C | [phase-3-trees-heaps-hashing](phase-3-trees-heaps-hashing/) |
| 4 | 8–9 | Graphs & STL transition | C → C++ | [phase-4-graphs-stl](phase-4-graphs-stl/) |
| 5 | 10–11 | Dynamic programming & advanced structures | C++ | [phase-5-advanced](phase-5-advanced/) |
| 6 | 12 | Capstone project & review | C++ | [phase-6-capstone](phase-6-capstone/) |

Each phase ends with a **mini-project** that integrates the structures you just built (text editor, autocomplete engine, route planner, diff tool — see ROADMAP for details).

Full week-by-week breakdown with checkboxes: [ROADMAP.md](ROADMAP.md).
Before starting Week 1, skim the [prerequisites checklist](docs/prerequisites.md) and patch any gaps in pointers/memory/debugger fluency.

**How to actually work a week** (what `notes.md` / `impl/` / `problems/` / `exercises.md` are for, the daily loop, and how to attack each problem): [docs/guidelines.md](docs/guidelines.md).

---

## Language strategy

**C for fundamentals → C++ for advanced.**

- **Weeks 1–7 (C)**: Implementing data structures in C forces you to confront pointers, manual memory management, and what's *actually happening* when a container "grows" or a hash table "collides." There's no library safety net. This is where the deep understanding comes from.
- **Weeks 8–12 (C++)**: Once the internals are second nature, switch to C++ + STL. Now you can think about algorithms (Dijkstra, DP recurrences, segment trees) without re-inventing a `vector` every time.

You're free to revisit problems in the other language any time — re-solving a Week-3 problem in modern C++ later is an excellent exercise.

---

## How to use this repo

```bash
git clone <your-fork-url>
cd practical-dsa

# Each week is self-contained. Compile a C example:
cd phase-1-foundations/week-01-complexity-arrays/impl
gcc -Wall -Wextra -std=c11 dynamic_array.c -o da_test && ./da_test

# Or a C++ example (later weeks):
g++ -Wall -Wextra -std=c++17 <file>.cpp -o out && ./out
```

Inside each weekly folder you'll find:

- **`notes.md`** — theory, complexity tables, common pitfalls
- **`impl/`** — clean reference implementations (`.c` / `.h` or `.cpp`)
- **`problems/`** — solved problems, one file per problem, with header comments
- **`exercises.md`** — the to-do list of problems for that week, with links

Week 1 is fully seeded as an example of the pattern. Every other week starts from a stub you fill in as you progress.

---

## Progress

Live progress log: [docs/progress.md](docs/progress.md).

---

## Contributing / study with me

If you're learning DSA, you're welcome here. Fork the repo, work through the same roadmap on your own branch, submit alternative solutions, suggest better problems for any week, or open a "study buddy" issue. Details: [CONTRIBUTING.md](CONTRIBUTING.md).

---

## Resources

Curated books, video courses, problem sets, and visualizations: [docs/resources.md](docs/resources.md).

---

## Topics / tags

`data-structures` · `algorithms` · `c` · `cpp` · `c-programming` · `cpp-programming` · `dsa` · `dsa-practice` · `learning` · `learning-by-doing` · `computer-science` · `cs-fundamentals` · `study-plan` · `roadmap` · `curriculum` · `self-study` · `practical-dsa` · `interview-preparation` · `competitive-programming` · `leetcode` · `cses` · `from-scratch`

---

## License

MIT — see [LICENSE](LICENSE).
