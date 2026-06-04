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

if [ "${#files[@]}" -eq 0 ]; then
  echo "No solution files found under phase-*/."
  exit 0
fi

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
