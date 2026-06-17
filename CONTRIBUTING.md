# Contributing & Study-With-Me

This repo is a public study log first, a community repo second. If you're learning DSA too, you're welcome here in any of the following ways.

## Ways to participate

### 1. Study buddy — work the curriculum alongside

The roadmap in [ROADMAP.md](ROADMAP.md) is designed to be followable. The simplest path:

1. **Fork** this repo.
2. Work through the weeks at your own pace on your fork.
3. Open an issue here titled `[study-buddy] <your-name>` with a link to your fork and the week you're currently on. Others (and I) can see who's working through the material and where.

### 2. Submit an alternative solution

For any problem under `problems/`, you can submit an alternative solution (different approach, different complexity, C version vs C++ version, etc.).

Folder convention:

```
phase-N-foo/week-MM-bar/problems/<problem-name>/
├── solution.c              ← the canonical solution
└── solutions/              ← alternative solutions
    └── <github-handle>/
        └── solution.cpp    ← your version
```

Open a PR titled `[alt-solution] <problem-name> — <your-handle>`. Briefly describe what's different about your approach.

### 3. Suggest better problems / corrections / clearer notes

PRs welcome for:

- Better problem choices for any week (with links)
- Clearer wording in `notes.md`
- Bug fixes in any reference implementation
- Additional pitfalls / common bugs to add to the notes

Open a PR titled `[improve] <area> — <one-line summary>`.

## Code style

- **C**: C11. Compile clean under `gcc -Wall -Wextra -std=c11`. No warnings.
- **C++**: C++17. Compile clean under `g++ -Wall -Wextra -std=c++17`. No warnings.
- **Header comment required** on every solution file:
  ```c
  /*
   * Problem: <name>
   * Source:  <link>
   * Approach: <one sentence>
   * Time:  O(?)
   * Space: O(?)
   */
  ```
- **Naming**: `snake_case` in C, `snake_case` for functions and `PascalCase` for types in C++. No Hungarian notation.
- **No magic numbers**: use `#define` or `const`.
- **One concept per file** under `impl/` (e.g. `linked_list.c` not `data_structures.c`).

## File placement

Always commit from the **repository root**, so solution files land at paths like
`phase-1-foundations/week-01-complexity-arrays/problems/two-sum.c` — *not*
`practical-dsa/phase-1-foundations/...`. A common mistake is to clone or nest the
repo inside another `practical-dsa/` folder and commit from there, which produces a
duplicated `practical-dsa/` path prefix. CI only checks files under `phase-*/` at the
repo root, so misplaced files are silently skipped (the check appears to pass without
actually testing your solution). Quick sanity check before opening a PR:

```bash
git ls-files | grep -c '^practical-dsa/phase-'   # must print 0
```

## Commit style

Short, imperative present tense. Examples:

- `week-01: add dynamic array reference impl`
- `week-04: solve n-queens with iterative backtracking`
- `roadmap: tick off week 2 milestone`

## Code of conduct

Be kind. Assume good faith. We're all learning. No gatekeeping, no "actually, that's trivial" comments — every concept is hard the first time you meet it.

## Questions

Open an issue. I'd rather answer the same question ten times than have anyone feel stuck.
