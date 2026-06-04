# PR CI: compile + run + style check — design

**Date:** 2026-06-04
**Status:** Approved (pending spec review)

## Problem

The repo is a 12-week DSA study curriculum (C → C++). Contributions arrive as
PRs adding self-contained `.c` / `.cpp` solution files (and occasional `.h`
headers) under `phase-*/week-*/{impl,problems,solutions}/`.

There is no build system and no test framework. The only existing workflow,
`.github/workflows/cmake-single-platform.yml`, runs `cmake -B build` + `ctest`,
but **no `CMakeLists.txt` exists anywhere** — so it fails on every push and PR
today.

`CONTRIBUTING.md` defines the real quality bar:

- **C**: clean under `gcc -Wall -Wextra -std=c11` (no warnings)
- **C++**: clean under `g++ -Wall -Wextra -std=c++17` (no warnings)
- A `/* … */` header comment block on every solution file
- `snake_case` / `PascalCase` naming, no magic numbers

We want CI that, when a PR is opened, verifies a contribution compiles clean and
follows the conventions — and points the issues out **inline on the PR diff**.

## Key observation

Every solution file is **self-contained**: it has its own `main()` that runs
`assert`-based self-tests and prints `OK`. So CI needs no test framework — it can
**compile each file with the exact CONTRIBUTING flags and then run it**. The
asserts *are* the tests. Header files (`.h` / `.hpp`) have no `main` and just
need a syntax check.

Note: the C++ template uses `#include <bits/stdc++.h>`, which is GCC-only — the
runner must use `g++`, not clang.

## Decisions

| Decision | Choice |
|---|---|
| CI scope | Compile **and** run each file + lightweight style check |
| File scope | **All** solution files under `phase-*/` on every PR (repo is small; no fragile git-diff logic; catches rot anywhere) |
| Existing workflow | **Replace** — delete `cmake-single-platform.yml` |
| Structure | Standalone script + thin workflow (also runnable locally) |
| Compiler | GCC / g++ only (single platform), to support `<bits/stdc++.h>` |
| Warnings | Treated as errors (`-Werror`), matching "no warnings" |

## Architecture

Two artifacts:

### 1. `.github/workflows/ci.yml`

- **Triggers:** `pull_request` and `push` to `main`.
- **Job:** single job on `ubuntu-latest`.
- **Steps:** checkout → ensure `gcc` / `g++` present → run `scripts/ci-check.sh`.
- The job goes red if the script exits non-zero.

### 2. `scripts/ci-check.sh`

The single source of truth for the check, runnable identically in CI and
locally (`bash scripts/ci-check.sh` from the repo root).

**Discovery:** find every `.c .cpp .h .hpp` under `phase-*/`. Exclude
`templates/` (placeholder headers, not real solutions).

**Per-file checks:**

| File type | Action | Pass condition |
|---|---|---|
| `.c` | `gcc -std=c11 -Wall -Wextra -Werror -c file` → object. Then build an executable; if it links (has `main`), **run it**. | compiles clean **and**, if it has `main`, the binary exits 0 |
| `.cpp` | same with `g++ -std=c++17` | same |
| `.h` / `.hpp` | `gcc/g++ -fsyntax-only` (pick compiler by sibling files / extension; default `.h`→C, `.hpp`→C++) | compiles clean |

The file's own directory is placed on the include path (`-I<dir>`) so local
`#include "foo.h"` resolves. Each file is compiled standalone (every file is
self-contained today).

Distinguishing "no `main`" from a real link error: the object compile (`-c`) is
the authoritative compile-clean gate and always runs regardless of `main`. The
run step only executes when the executable links successfully; a file with no
`main` simply skips the run step without failing.

**Style check (per file):** the first non-whitespace content must be a
`/* … */` block comment (the universal header-comment convention). Lenient on
the block's contents so both the `impl/` style and the `problems/` style pass.
Stricter field checks (Problem / Source / Time / Space) are deferred — noted as a
possible later layer.

## Reporting

The script **does not stop at the first failure.** It collects all problems
across all files, then at the end emits GitHub Actions annotations:

```
::error file=<path>,line=<n>::<message>
```

These render **inline on the PR diff** and in the run summary, so the author
sees every compile warning, failed assertion, and missing-header issue in a
single run. Locally, the same failures print as plain colored output.

The script exits non-zero if any file failed any check, turning the PR check
red.

## Error handling

- A compile failure, a non-zero run exit, or a missing header block each record
  a failure for that file and continue to the next file.
- Compiler stderr is captured and surfaced (mapped to the file, and to a line
  when GCC reports one) rather than swallowed.
- Build artifacts (objects, executables) are written to a temp dir and not left
  in the tree.

## Testing / verification

- Run `scripts/ci-check.sh` against the current repo — it must pass clean (the
  existing files compile and self-test today).
- Introduce a deliberate warning in a throwaway file and confirm the script
  fails and annotates it; then remove it.
- Confirm a `.h`-only change is syntax-checked and passes.

## Out of scope (YAGNI)

- CMake / ctest build system and per-week `CMakeLists.txt`.
- Multi-compiler / multi-platform matrix (clang, Windows, macOS).
- `clang-format` / `clang-tidy` enforcement.
- Strict header-field validation (Problem/Source/Time/Space).
- Changed-files-only diffing.

These can be layered on later without reworking the structure above.
