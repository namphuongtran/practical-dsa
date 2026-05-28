# Resources

Curated and opinionated. No fluff, no "100 best DSA resources" listicles — these are the ones that pull their weight.

## Books

### Beginner-friendly (start here)
- **Robert Lafore — _Data Structures & Algorithms in C++_** — gentle pace, great diagrams, perfect for the first time you see each structure.
- **Aditya Bhargava — _Grokking Algorithms_** — picture-heavy, ~250 pages, builds intuition for the big ideas before formal study.

### Reference & intuition
- **Robert Sedgewick & Kevin Wayne — _Algorithms (4th edition)_** — best intuition-building textbook. Examples are in Java but ideas port directly to C++.
- **Steven Skiena — _The Algorithm Design Manual_** — second half is a catalogue: "I have problem X, what algorithm do I use?" Invaluable as a working reference.

### Authoritative (use as a reference, not a tutorial)
- **CLRS — _Introduction to Algorithms_** (Cormen, Leiserson, Rivest, Stein) — *not* a first read. Use it as the canonical reference when you want the rigorous treatment of a topic you already roughly understand.

### Competitive programming (later, if interested)
- **Antti Laaksonen — _Competitive Programmer's Handbook_** — free PDF, excellent. Best concise intro to competitive algorithm tricks.
- **Halim & Halim — _Competitive Programming 4_** — denser, encyclopedic.

## Online problem sets

In rough order of recommended introduction:

1. **CSES Problem Set** ([cses.fi/problemset](https://cses.fi/problemset/)) — curated, well-organized by topic, no clutter. **Best starting point** after each topic in the roadmap.
2. **LeetCode** ([leetcode.com](https://leetcode.com)) — huge problem bank, free tier covers most needs. Filter by topic + difficulty.
3. **Codeforces** ([codeforces.com](https://codeforces.com)) — for when you want timed contest practice. Start with Div 3/4 rounds.
4. **HackerRank — Data Structures & Algorithms track** — gentler intro, useful for the first couple weeks.
5. **AtCoder Beginner Contests** ([atcoder.jp](https://atcoder.jp)) — high-quality problems, generally cleaner than Codeforces at the beginner level.

## Visualizations

- **VisuAlgo** ([visualgo.net](https://visualgo.net)) — animated visualization of every data structure & algorithm. Use it the first time you meet anything.
- **USFCA Algorithm Visualizations** ([cs.usfca.edu/~galles/visualization](https://www.cs.usfca.edu/~galles/visualization/Algorithms.html)) — older but extremely clear step-through animations.
- **algorithm-visualizer.org** — see the code and animation side-by-side.

## Video courses

- **Abdul Bari — Algorithms** (YouTube) — best free lectures for *algorithm intuition*. Watch when a topic feels handwavy.
- **MIT 6.006 — Introduction to Algorithms** (OCW) — Erik Demaine is one of the best teachers of this material alive. Free.
- **Princeton — Algorithms, Part I & II** (Coursera, Sedgewick) — pairs with his book. Pay for the audit if needed; the lectures are gold.
- **William Fiset — Graph Theory series** (YouTube) — clearest free coverage of graph algorithms anywhere.

## Reference cheat-sheets

- **Big-O Cheat Sheet** ([bigocheatsheet.com](https://www.bigocheatsheet.com)) — complexities of every common operation, in one page.
- **CP-Algorithms** ([cp-algorithms.com](https://cp-algorithms.com)) — wiki-style reference for every algorithm with C++ implementations. Excellent.
- **cppreference** ([en.cppreference.com](https://en.cppreference.com)) — when you can't remember an STL method signature.

## Tooling

- **Beej's *Guide to C Programming*** — [beej.us/guide/bgc](https://beej.us/guide/bgc/) — best free C book.
- **Beej's *Quick Guide to GDB*** — [beej.us/guide/bggdb](https://beej.us/guide/bggdb/) — 30-min read, covers 95% of what you'll use.
- **AddressSanitizer wiki** — [github.com/google/sanitizers/wiki/AddressSanitizer](https://github.com/google/sanitizers/wiki/AddressSanitizer) — read once, save days later.
- **lldb cheat-sheet** — [lldb.llvm.org/use/map.html](https://lldb.llvm.org/use/map.html) — gdb↔lldb command translation table.
- **LearnCpp.com** — [learncpp.com](https://www.learncpp.com/) — free, paced C++ tutorial. Skim chapters 1–9 before Week 8.

## Practice strategy

- **Don't grind problems before you've studied the topic.** Always read `notes.md` (or a chapter, or watch the lecture) first.
- **Try each problem for 20–30 minutes before looking at hints.** If you peek too soon, you train pattern-recognition without understanding.
- **After solving, read 2–3 other people's solutions** (LeetCode "Discuss" tab, or Codeforces editorial). You'll often find a cleaner approach or an idea you didn't know.
- **Re-do problems a week later, blind.** The second time is where the learning consolidates.
- **Re-implement core data structures every couple of weeks** from a blank file. Atrophy is real.

## Anti-recommendations

A few things to *not* do:

- Don't start with CLRS. You'll bounce off it. Come back when you have intuition.
- Don't grind LeetCode Hard problems in week 1. You'll discourage yourself for no gain.
- Don't trust YouTube videos that show "the algorithm" without showing the *intuition* for why it works. If you can't explain why an algorithm works, you don't know it yet.
