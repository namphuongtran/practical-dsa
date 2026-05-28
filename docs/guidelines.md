# Study Guidelines — How to Work a Week in This Repo

This is the *how* of the curriculum. The [ROADMAP](../ROADMAP.md) tells you **what** to study each week; this file tells you **how** to actually do it — what each file in a weekly folder is for, the order to work in, and how to attack each problem so you actually learn.

Read this once, refer back whenever a habit slips.

---

## The four pieces in every weekly folder

Every week (`phase-N-foo/week-MM-bar/`) has the same shape:

```
week-MM-bar/
├── notes.md          ← your theory file
├── impl/             ← reference data-structure implementations
├── problems/         ← solved problems, one file per problem
└── exercises.md      ← the to-do list of problems for the week
```

### `notes.md` — the *theory* file (you write it as you learn)

- **What it is**: your written explanation of the week's topic in *your own words*. Definitions, complexity tables, a small ASCII diagram, common pitfalls, and the one-line mental model.
- **Why it matters**: writing forces you to confront what you don't actually understand. If you can't explain `heapify_up` in one paragraph, you don't know it yet.
- **When you write it**: incrementally, *while* you study — not after. Add a paragraph after a lecture, add a complexity to the table after you derive it, add a pitfall the moment you fall in one.
- **Starts as a stub**: every week (except Week 1, which is fully seeded as an example) starts with a topic checklist from `templates/notes-template.md`. You fill it in.

### `impl/` — the *reference implementations* folder

- **What it is**: clean, working, test-driven implementations of the data structure(s) the week introduces. One concept per file (`linked_list.c`, not `data_structures.c`).
- **Why it matters**: these are the canonical pieces you'll **reuse** when solving problems later in the week (and beyond). If you've built `heap.c` in Week 7, you don't re-derive a heap in Week 9's Dijkstra — you reuse it.
- **What's in a good `impl/` file**:
  - A header comment describing invariants (e.g., "0 ≤ len ≤ cap; data != NULL iff cap > 0").
  - The public API as functions (or as a class in C++).
  - **A `main()` that tests itself** with `assert()`. Compile + run = visible OK.
  - Compiles clean under `-Wall -Wextra -fsanitize=address`.
- **Example**: `phase-1-foundations/week-01-complexity-arrays/impl/dynamic_array.c` is the seeded reference for the shape.

### `problems/` — the *solved problems* folder

- **What it is**: your solutions to the exercises, one file per problem.
- **File naming**: `01_two_sum.c`, `02_remove_duplicates.c`, … — the leading number matches `exercises.md`.
- **Required header comment** on every solution:
  ```c
  /*
   * Problem: <name>
   * Source:  <link>
   * Approach: <one paragraph in plain English>
   * Time:  O(?)
   * Space: O(?)
   * Notes:  <gotchas, alternative approaches considered, what surprised you>
   */
  ```
- **Why the header matters**: it forces you to articulate your approach *before* the code, and it makes the folder useful as a revision deck later. Skim 50 problem headers in 10 minutes; you can't skim 50 raw solutions.

### `exercises.md` — the *to-do list*

- **What it is**: the curated list of problems for the week, with links to the source (LeetCode, CSES, etc.), tagged by difficulty.
- **Why it's separate from `problems/`**: `problems/` is *what you've done*; `exercises.md` is *what's queued*. You tick boxes in `exercises.md` as you ship solutions to `problems/`.
- **Week 1's `exercises.md` is fully populated** as a model. For Weeks 2–11, you write this file at the start of the week — pick 10–15 problems, add links, set difficulty mix (50% easy, 40% medium, 10% bonus hard).

---

## Order of operations within a week (~7 days, 3–4 hrs/day)

A week breaks down roughly like this. Adjust to fit your real rhythm.

### Day 1 — Theory pass
- Read external sources first: VisuAlgo animation, an Abdul Bari video, the relevant chapter from Sedgewick or Skiena.
- Open `notes.md`. Start filling it in — even badly. The goal of day 1 is "scaffolded understanding," not polished notes.
- Output: `notes.md` has at least the "What it is", "Why it exists", and "Operations & complexities" sections filled.

### Day 2 — Build the impl
- Build the reference implementation(s) in `impl/`. From scratch. No copy-paste.
- Write the `main()` test driver as you go — `assert` every operation including edge cases (empty, single element, after-resize, after-clear).
- Compile clean under `gcc -Wall -Wextra -std=c11 -g -fsanitize=address` (or `g++ -std=c++17` from Week 8). Zero warnings, ASan green.
- If it doesn't compile clean: stop, fix, then move on. Don't accumulate warning debt.
- Output: `impl/<thing>.c` runs and prints `OK`.

### Days 3–5 — Solve problems (the bulk of the week)
- Pick the next unchecked problem from `exercises.md`.
- Apply the per-problem workflow below.
- Aim for 2–4 problems per day, depending on difficulty.
- Tick the box in `exercises.md` and commit.

### Day 6 — Hard problems + reflection
- Tackle the 1–2 hardest problems on the list.
- Update `notes.md` with anything you learned during the problem grind:
  - new pitfalls
  - patterns you noticed
  - things you got wrong the first time
- Write the day's `docs/progress.md` journal entry.

### Day 7 — Milestone check + buffer
- Open the milestone for the phase (e.g., 🏁 M1 at the end of Week 3).
- Can you do it without looking? If yes, commit and move on. If no, list what's shaky and spend the day patching it.
- Days 7 is also your buffer for life. Don't skip the milestone check.

---

## The per-problem workflow (use this every single time)

This is the most important section in this file. Memorize it.

```
1. READ        — understand the problem
2. CONSTRAIN   — what does n tell you about the target complexity?
3. PLAN        — write the approach in English first
4. CODE        — implement, test against examples
5. EDGE CASES  — empty, single element, max n, negatives, duplicates
6. ANALYZE     — annotate time/space in the header
7. REFLECT     — what was hard, what's the clean version?
```

### 1. READ — restate the problem in your own words

Before you touch the keyboard, **rewrite the problem in one sentence in a comment**. If you can't, you haven't read it carefully enough. Re-read it.

```c
// Problem in my words: given an array of integers and a target sum,
// return the two indices whose values add up to the target. Exactly
// one valid pair is guaranteed; i < j.
```

### 2. CONSTRAIN — read the constraints, derive the target complexity

This is the skill that separates DSA-fluent people from everyone else. Constraints tell you what complexity is *allowed*:

| If `n` is up to … | Target time complexity |
|-------------------|------------------------|
| 10⁸ or higher     | O(n) or O(log n)       |
| 10⁷               | O(n) or O(n log log n) |
| 10⁶               | O(n log n)             |
| 10⁵               | O(n log n) or O(n √n)  |
| 10⁴               | O(n²)                  |
| 500               | O(n³)                  |
| 20                | O(2ⁿ) acceptable       |
| 10                | O(n!) acceptable       |

If `n ≤ 10⁵` and the problem says "find pairs," you know an O(n²) brute force is too slow → you need a hashing or sorting trick. **Pinning the target complexity before you code prevents you from spending an hour on the wrong algorithm.**

### 3. PLAN — write the approach in English BEFORE code

Open your `.c` file. Write the approach as a comment paragraph. No code yet.

```c
/*
 * Approach: Walk i from 0 to n-1; for each i, walk j from i+1 to n-1
 * checking if nums[i] + nums[j] == target. Return the first match.
 *
 * Why this is correct: every pair (i, j) with i < j is examined exactly
 * once.
 *
 * Complexity: nested loop = O(n^2) time, O(1) space.
 *
 * Better approach (saved for after Week 7): hash table from value → index.
 * For each i, query for (target - nums[i]) in O(1). Total O(n) time, O(n)
 * space.
 */
```

If this paragraph doesn't write itself, **you don't know how to solve the problem yet — keep thinking; don't start coding**. Coding without a plan is how you end up with 80 lines of nested branches that don't work.

### 4. CODE — implement and test

- Write the function.
- Write a `main()` that asserts the given examples produce the expected output.
- Compile clean under your sanitizer-enabled command. **No warnings.**

### 5. EDGE CASES — be paranoid

Before you call it done, add asserts for at least:
- The smallest possible input (n=0, n=1)
- The largest case you can construct quickly (n = 10⁵ with all duplicates, etc.)
- Negative numbers / empty strings / `NULL` pointers as applicable
- Whatever the problem's *adversarial* case is (already-sorted for quick-sort, all-duplicates for hash, etc.)

You'll catch ~30% of bugs with edge cases alone.

### 6. ANALYZE — write the final time/space in the header

Fill in the header banner's `Time:` and `Space:` lines with the **actual** complexity of what you wrote, not what you intended. If the actual is worse than the target you set in step 2 — you have a problem to investigate.

### 7. REFLECT — what would you do differently?

In the file's `Notes:` field or in `docs/progress.md`, jot one or two sentences:
- "I initially tried X and it was wrong because Y."
- "The clean version uses Z; mine works but is verbose."
- "I want to come back and solve this with a hash table after Week 7."

This is where learning consolidates.

---

## The 30-minute rule

When you're stuck:

- **First 30 minutes**: think alone. No Google, no hints. Draw the problem on paper. Try a small example by hand. Trace through your idea step-by-step.
- **Then**: check your `notes.md`, the relevant chapter, or a related solved problem in `problems/`.
- **Last resort, after ≥30 min struggling**: read a hint (LeetCode "Hints" tab, or the first paragraph of an editorial). Apply the hint and finish the solution yourself.
- **Avoid**: reading the full solution before solving. You'll "understand" it and forget it within a week. The struggle *is* the learning.

---

## Definition of done — for a problem, a week, a phase

### A *problem* is done when
- ✅ The solution file compiles clean under `-Wall -Wextra -fsanitize=address`
- ✅ Asserts pass on the given examples + your own edge cases
- ✅ The header banner is filled in (problem, source, approach, time, space, notes)
- ✅ The checkbox in `exercises.md` is ticked
- ✅ A git commit exists for it

### A *week* is done when
- ✅ `notes.md` is filled in (not just stub)
- ✅ The `impl/` files compile clean and self-test
- ✅ At least 80% of `exercises.md` is ticked
- ✅ A `docs/progress.md` entry exists for at least 3 days that week

### A *phase* is done when
- ✅ All weeks in the phase are done
- ✅ The phase milestone (🏁 M*N*) is hit — verified by attempting it *without notes*
- ✅ The phase mini-project (🛠️) is shipped, with its own short README

---

## Habits worth forming

- **Commit after every problem.** Tiny commits. Message style: `week-01: solve two-sum (O(n^2) array version)`. You'll thank yourself when you want to see your trajectory in two months.
- **Compile with warnings + ASan every time.** Never `gcc foo.c`. Always `gcc -Wall -Wextra -std=c11 -g -fsanitize=address foo.c`. Make it a shell alias.
- **Update `notes.md` the moment you learn something.** Not "I'll do it later." Later never comes.
- **Re-solve old problems weekly.** Pick 1 problem from 2 weeks ago, blank-file it. Took 30 min last time? Should be 5 now. If it's not, the topic isn't sticking — schedule a revisit.
- **Talk through a solution out loud once a week** — to a rubber duck, a friend, or just yourself. If you can explain it cleanly, you own it.

---

## Anti-patterns to avoid

- ❌ **Copy-pasting from Stack Overflow / LeetCode discuss.** You're paying for fake progress.
- ❌ **Skipping the `notes.md` because "I already get it."** You don't. Write it.
- ❌ **Watching DSA YouTube as your primary study activity.** Watching is not learning. Writing is.
- ❌ **Doing only easy problems** because they feel productive. Force at least 2 medium-or-harder per week.
- ❌ **Doing only hard problems** because they feel impressive. Easy problems internalize the fundamentals.
- ❌ **Solving without a header comment** "to save time." You'll lose the time back trying to remember what the file does in 4 weeks.
- ❌ **Letting compiler warnings accumulate.** Warnings are bugs you haven't found yet.

---

## When you fall behind (you will)

It will happen. Some weeks will eat 6 hours instead of 3. Some weeks you'll get sick or busy. Don't reset the curriculum — **truncate the current week instead**:

- Drop bonus problems first.
- Drop one medium problem next.
- Never drop the milestone — it's the load-bearing piece. If you only do 4 problems but you hit M1, you're still ready for Week 4.
- Move what you skipped into a "to-revisit" section in `docs/progress.md`. You can come back during Phase 6's review week.

Progress is *cumulative*, not synchronous. A 13-week version of this curriculum is still excellent.

---

## TL;DR — the loop, every day

1. Open today's week folder.
2. Update `notes.md` with whatever's still fuzzy.
3. Open the next problem in `exercises.md`.
4. Apply the 7-step per-problem workflow.
5. Tick the box, commit, journal in `docs/progress.md`.
6. Repeat.

That's the entire job. The structure is here to keep you honest; the learning is in the loop.
