# PR CI Compile + Run + Style Check Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add PR CI that compiles every C/C++ solution with the CONTRIBUTING flags, runs each file's self-test `main`, checks for a header comment, and reports all issues inline on the PR diff — replacing the broken cmake workflow.

**Architecture:** A single portable bash script (`scripts/ci-check.sh`) is the source of truth, runnable identically locally and in CI. A thin GitHub Actions workflow (`.github/workflows/ci.yml`) runs it on PRs and pushes to `main`. The script compiles each file with `gcc/g++ -Wall -Wextra -Werror`, runs the resulting binary when it has `main` (the `assert`s are the tests), syntax-checks headers, verifies a `/* … */` header block, collects all failures, and emits `::error file=…::` annotations in CI.

**Tech Stack:** Bash (portable to macOS bash 3.2), GCC/g++, GitHub Actions.

**Spec:** `docs/superpowers/specs/2026-06-04-pr-ci-compile-check-design.md`

---

### Task 1: Create the check script and verify it passes against the current repo

**Files:**
- Create: `scripts/ci-check.sh`

- [ ] **Step 1: Write the script**

Create `scripts/ci-check.sh` with exactly this content:

```bash
#!/usr/bin/env bash
#
# ci-check.sh — compile, run, and style-check every solution file.
#
# Runs identically locally and in GitHub Actions. From the repo root:
#     bash scripts/ci-check.sh
#
# For each .c/.cpp under phase-*/ : compile clean with the CONTRIBUTING flags,
# then run the binary if it has main() (the asserts are the tests).
# For each .h/.hpp : syntax-check only.
# Every file must begin with a /* ... */ header comment block.
# All failures are collected; in CI they are emitted as ::error annotations.

set -uo pipefail

# Run from the repo root regardless of caller's CWD.
cd "$(dirname "$0")/.." || exit 2

C_STD=c11
CXX_STD=c++17
# Intentionally unquoted at use sites for word-splitting into separate flags.
WARN_FLAGS="-Wall -Wextra -Werror"

GHA="${GITHUB_ACTIONS:-false}"

if [ -t 1 ]; then
  RED=$'\033[31m'; GRN=$'\033[32m'; RST=$'\033[0m'
else
  RED=''; GRN=''; RST=''
fi

failures=0
checked=0

tmpdir="$(mktemp -d)"
trap 'rm -rf "$tmpdir"' EXIT

# report_error <file> <line-or-0> <message>
report_error() {
  local file="$1" line="$2" msg="$3"
  failures=$((failures + 1))
  if [ "$GHA" = "true" ]; then
    if [ "$line" != "0" ]; then
      echo "::error file=${file},line=${line}::${msg}"
    else
      echo "::error file=${file}::${msg}"
    fi
  else
    if [ "$line" != "0" ]; then
      echo "${RED}FAIL${RST} ${file}:${line} — ${msg}"
    else
      echo "${RED}FAIL${RST} ${file} — ${msg}"
    fi
  fi
}

# emit_compiler_log <file> <logfile>: turn the first GCC diagnostic into an
# error report, then echo the full compiler output indented for context.
emit_compiler_log() {
  local file="$1" log="$2" line msg diag
  diag="$(grep -m1 -E ':[0-9]+:[0-9]+: (error|warning):' "$log" || true)"
  if [ -n "$diag" ]; then
    line="$(printf '%s\n' "$diag" | sed -E 's/^[^:]*:([0-9]+):[0-9]+:.*/\1/')"
    msg="$(printf '%s\n' "$diag" | sed -E 's/^[^:]*:[0-9]+:[0-9]+: //')"
  else
    line=0
    msg="compilation failed"
  fi
  report_error "$file" "$line" "$msg"
  sed 's/^/    /' "$log"
}

# style_check <file>: first non-blank line must open a /* block comment.
style_check() {
  local file="$1" first
  first="$(grep -m1 -v '^[[:space:]]*$' "$file" || true)"
  case "$first" in
    /\**) : ;;
    *) report_error "$file" 1 "missing header comment block (file must begin with a /* ... */ comment; see CONTRIBUTING.md)" ;;
  esac
}

# compile_and_run <file> <compiler> <std>
compile_and_run() {
  local file="$1" cc="$2" std="$3" dir obj exe log
  dir="$(dirname "$file")"
  obj="$tmpdir/out.o"; exe="$tmpdir/out.bin"; log="$tmpdir/cc.log"

  # 1. Compile-clean gate (object only; works with or without main()).
  if ! "$cc" -std="$std" $WARN_FLAGS -I"$dir" -c "$file" -o "$obj" 2>"$log"; then
    emit_compiler_log "$file" "$log"
    return
  fi

  # 2. If it links into an executable (has main), run it.
  if "$cc" -std="$std" $WARN_FLAGS -I"$dir" "$file" -o "$exe" 2>/dev/null; then
    if ! "$exe" >"$tmpdir/run.log" 2>&1; then
      report_error "$file" 0 "self-test failed at runtime (exit non-zero): $(tail -n1 "$tmpdir/run.log")"
    fi
  fi
}

# syntax_check <file> <compiler> <std> (headers only)
syntax_check() {
  local file="$1" cc="$2" std="$3" dir log
  dir="$(dirname "$file")"; log="$tmpdir/cc.log"
  if ! "$cc" -std="$std" $WARN_FLAGS -I"$dir" -fsyntax-only "$file" 2>"$log"; then
    emit_compiler_log "$file" "$log"
  fi
}

# Collect files portably (macOS bash 3.2 has no mapfile).
files=()
while IFS= read -r f; do
  files+=("$f")
done < <(find phase-* -type f \( -name '*.c' -o -name '*.cpp' -o -name '*.h' -o -name '*.hpp' \) | sort)

for f in "${files[@]}"; do
  checked=$((checked + 1))
  style_check "$f"
  case "$f" in
    *.c)   compile_and_run "$f" gcc "$C_STD" ;;
    *.cpp) compile_and_run "$f" g++ "$CXX_STD" ;;
    *.h)   syntax_check "$f" gcc "$C_STD" ;;
    *.hpp) syntax_check "$f" g++ "$CXX_STD" ;;
  esac
done

echo
if [ "$failures" -eq 0 ]; then
  echo "${GRN}All ${checked} file(s) passed.${RST}"
  exit 0
else
  echo "${RED}${failures} issue(s) across ${checked} file(s).${RST}"
  exit 1
fi
```

- [ ] **Step 2: Make it executable**

Run: `chmod +x scripts/ci-check.sh`

- [ ] **Step 3: Run against the current repo to verify it passes**

Run: `bash scripts/ci-check.sh`
Expected: exits 0, prints `All 3 file(s) passed.` (the three existing files — `dynamic_array.c`, `dynamic_array.h`, `01_two_sum.c` — compile clean and the two with `main` self-test OK).

If `g++` or `gcc` is missing locally, install them first; on macOS `g++` is typically a clang shim — note that `<bits/stdc++.h>` will not be available locally, but CI uses real GCC. Files in the current repo do not use `<bits/stdc++.h>`, so this step passes locally regardless.

- [ ] **Step 4: Commit**

```bash
git add scripts/ci-check.sh
git commit -m "ci: add compile+run+style check script"
```

---

### Task 2: Verify the script actually catches a bad file (negative test)

**Files:**
- Temporary: `phase-1-foundations/week-01-complexity-arrays/problems/_ci_fixture.c` (created and deleted within this task — never committed)

- [ ] **Step 1: Create a file with a warning (unused variable) and a missing header**

Create `phase-1-foundations/week-01-complexity-arrays/problems/_ci_fixture.c`:

```c
int main(void) {
    int unused;
    return 0;
}
```

(No `/* */` header, and `int unused;` triggers `-Wunused-variable` → error under `-Werror`.)

- [ ] **Step 2: Run the script and confirm it fails on this file**

Run: `bash scripts/ci-check.sh`
Expected: exits non-zero. Output includes a `FAIL …/_ci_fixture.c:1 — missing header comment block` line **and** a `FAIL …/_ci_fixture.c:2 — …unused-variable…` (or similar) line. The summary reads `2 issue(s) …` or more.

- [ ] **Step 3: Confirm CI annotation format**

Run: `GITHUB_ACTIONS=true bash scripts/ci-check.sh`
Expected: output contains lines beginning with `::error file=phase-1-foundations/week-01-complexity-arrays/problems/_ci_fixture.c`.

- [ ] **Step 4: Delete the fixture**

Run: `rm phase-1-foundations/week-01-complexity-arrays/problems/_ci_fixture.c`

- [ ] **Step 5: Re-run to confirm green again**

Run: `bash scripts/ci-check.sh`
Expected: exits 0, `All 3 file(s) passed.`

(No commit — this task only verifies behavior; nothing is left on disk.)

---

### Task 3: Add the workflow and remove the broken cmake workflow

**Files:**
- Create: `.github/workflows/ci.yml`
- Delete: `.github/workflows/cmake-single-platform.yml`

- [ ] **Step 1: Write the workflow**

Create `.github/workflows/ci.yml`:

```yaml
name: CI

on:
  pull_request:
    branches: [ "main" ]
  push:
    branches: [ "main" ]

jobs:
  check:
    name: Compile, run & style-check solutions
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4

      - name: Show compiler versions
        run: |
          gcc --version
          g++ --version

      - name: Run checks
        run: bash scripts/ci-check.sh
```

(`ubuntu-latest` ships `gcc`/`g++` preinstalled, so no install step is needed. The version step makes the toolchain visible in logs.)

- [ ] **Step 2: Delete the broken cmake workflow**

Run: `git rm .github/workflows/cmake-single-platform.yml`

- [ ] **Step 3: Sanity-check the workflow file is valid YAML**

Run: `python3 -c "import yaml,sys; yaml.safe_load(open('.github/workflows/ci.yml')); print('ok')"`
Expected: prints `ok`.

- [ ] **Step 4: Commit**

```bash
git add .github/workflows/ci.yml
git commit -m "ci: run compile+run+style check on PRs; drop broken cmake workflow"
```

---

### Task 4: Open the PR and confirm CI runs

- [ ] **Step 1: Push the branch**

Run: `git push -u origin ci/pr-compile-check`

- [ ] **Step 2: Open the PR**

Run:
```bash
gh pr create --title "ci: compile+run+style check on PRs" \
  --body "Adds scripts/ci-check.sh and .github/workflows/ci.yml; replaces the broken cmake workflow. See docs/superpowers/specs/2026-06-04-pr-ci-compile-check-design.md."
```

- [ ] **Step 3: Confirm the CI check runs on the PR**

Run: `gh pr checks --watch`
Expected: the `CI / Compile, run & style-check solutions` check appears and passes (green).

---

## Notes for the implementer

- **DRY:** the script is the single source of truth; the workflow just calls it. Contributors run the exact same command locally.
- **macOS portability:** no `mapfile` (bash 3.2), uses a `while read` loop. `mktemp -d`, `sed -E`, `grep -m1` all work on BSD and GNU.
- **Why object-compile first:** `-c` is the authoritative compile-clean gate and succeeds whether or not the file has `main`. The separate link step only runs the binary when `main` exists; a header-only or main-less `.c` simply skips the run without failing.
- **Compiler choice:** GCC/g++ only — the C++ problem template uses `<bits/stdc++.h>`, which clang does not provide.
