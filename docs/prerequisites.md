# Prerequisites — Phase 0 Checklist

Not a curriculum phase, a **pre-flight checklist**. Skim the list; for each item you're not fluent with, spend an hour or two with the linked refresher before starting Week 1. If you're solid on most of these, you're ready to start tomorrow.

The 3-month intensive plan assumes this baseline. Patching gaps now is much cheaper than getting stuck in Week 2.

---

## C fundamentals

- [ ] **Pointers** — declaration, dereference, address-of, `NULL`. Why `int *p, q;` declares one pointer and one int (and why that's a footgun).
- [ ] **Pointer arithmetic** — `p + 1` advances by `sizeof(*p)`, not by 1 byte.
- [ ] **Pointer-to-pointer** (`int **`) — you'll need this for clean linked-list deletion in Week 2.
- [ ] **`malloc` / `calloc` / `realloc` / `free`** — every `malloc` needs exactly one `free`. Returning a `malloc`'d pointer transfers ownership; document who frees it.
- [ ] **Dangling pointers, double-free, use-after-free** — recognize the symptoms.
- [ ] **`struct`** — declaration, member access (`.` vs `->`), forward declaration for self-referential structs.
- [ ] **`typedef`** — when it helps readability, when it hides too much.
- [ ] **Header files** — include guards (`#ifndef`/`#define`/`#endif` or `#pragma once`). What goes in `.h` vs `.c`.
- [ ] **Function pointers** — used in generic comparators (e.g., `qsort`).
- [ ] **`const` correctness** — what `const char *p` vs `char * const p` mean.

## C++ fundamentals (you'll need these by Week 8)

You don't need C++ for Weeks 1–7 — but glance over these before then.

- [ ] **References** — `T&` and `const T&`. When to prefer them over pointers.
- [ ] **Classes** — constructors, destructors, member functions, access modifiers. RAII as a concept.
- [ ] **`new` / `delete` / `new[]` / `delete[]`** — and why modern C++ prefers `std::unique_ptr` / `std::vector` over raw `new`.
- [ ] **Basic templates** — `template<typename T>`, enough to write a generic stack. We'll deepen in Week 8.
- [ ] **Namespaces** — `std::`, why `using namespace std;` is a code smell in headers.

> If you've never written C++ before, skim a short intro like [LearnCpp.com](https://www.learncpp.com/) chapters 1–9 (skim, don't grind). You don't need to master OOP or modern C++ idioms yet — Week 8 has a "C++ for C devs" cheat-sheet that bridges the gap.

## Tooling fluency

This is what most beginners under-invest in. Be comfortable with these *before* the bugs get hard.

- [ ] **Compile with warnings on**: `gcc -Wall -Wextra -std=c11` and `g++ -Wall -Wextra -std=c++17`. Treat warnings as errors.
- [ ] **A debugger** — pick one and learn 6 commands:
  - **gdb** (Linux, also macOS): `break <line>`, `run`, `next`, `step`, `print <var>`, `backtrace`. [gdb cheat-sheet](https://darkdust.net/files/GDB%20Cheat%20Sheet.pdf).
  - **lldb** (macOS default, Xcode): same idea, different command names — `breakpoint set --line N`, `run`, `next`, `step`, `print`, `bt`.
- [ ] **AddressSanitizer** — compile with `-fsanitize=address -g` and you'll catch buffer overruns and use-after-free at runtime. **This will save you days.**
- [ ] **Valgrind** (Linux, brittle on macOS) — `valgrind --leak-check=full ./your_program` catches memory leaks. ASan is preferable on macOS.
- [ ] **A Makefile or just a build script** — so you don't retype gcc flags every time. A 5-line shell script is fine.
- [ ] **Git basics** — `add`, `commit`, `push`, branches, log. You'll commit after every solved problem.

## CS literacy already assumed

You said you have CS background, so we assume:

- Comfortable on the command line (cd, ls, file paths, env vars)
- Understand basic computer architecture at the "stack vs heap, register vs RAM" level
- Comfortable reading documentation and reading code that isn't yours

If any of these are shaky, address them as they come up — they're not blockers for Week 1.

---

## Optional warm-up (skip if confident)

If you're patching pointer/memory gaps, write this 30-line program before starting Week 1:

> **Student manager** — define a `Student` struct (`char name[64]`, `int id`, `float gpa`). Read N students from stdin into a heap-allocated array (use `malloc` and `realloc` to grow it). Print them sorted by GPA. Free everything. Compile with `-Wall -Wextra -fsanitize=address`. No leaks, no warnings.

If this compiles clean, runs clean, and you understand every line — Phase 0 is done. Go to [ROADMAP.md](../ROADMAP.md) Week 1.

---

## Refresher links

- **C in a nutshell**: Beej's *Guide to C Programming* — [beej.us/guide/bgc](https://beej.us/guide/bgc/)
- **C++ first contact**: [learncpp.com](https://www.learncpp.com/) (free, paced)
- **Debugger crash course**: [Beej's *Quick Guide to GDB*](https://beej.us/guide/bggdb/) — 30 min read
- **ASan introduction**: [Google's AddressSanitizer wiki](https://github.com/google/sanitizers/wiki/AddressSanitizer) — skim
