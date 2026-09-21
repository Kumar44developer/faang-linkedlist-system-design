<div align="center">

# FAANG Linked List System Design

**Six production-grade system design problems, solved in C++ with linked lists at the core.**

Each module is a self-contained, runnable program that shows how pointer-based structures
deliver O(1) insertions, removals and reordering inside real-world systems like caches,
browsers, editors and memory allocators.

![C++](https://img.shields.io/badge/C%2B%2B-14-blue?style=flat-square&logo=cplusplus&logoColor=white)
![Modules](https://img.shields.io/badge/modules-6-brightgreen?style=flat-square)
![Dependencies](https://img.shields.io/badge/dependencies-0-green?style=flat-square)
![Warnings](https://img.shields.io/badge/build%20warnings-0-orange?style=flat-square)
![License](https://img.shields.io/badge/license-MIT-blue?style=flat-square)

</div>

---

## Table of Contents

- [Overview](#overview)
- [Why Linked Lists](#why-linked-lists)
- [Modules](#modules)
- [Complexity](#complexity)
- [Requirements](#requirements)
- [Build and Run](#build-and-run)
- [Example Output](#example-output)
- [Project Structure](#project-structure)
- [Design Notes](#design-notes)
- [Contributing](#contributing)
- [Author](#author)
- [License](#license)

---

## Overview

This repository is a curated collection of FAANG-style system design questions where the
intended data structure is a linked list. Every file in `src/` compiles to its own executable
with a `main` function and a worked example, so each solution can be built, run and studied
independently. The goal is to demonstrate not just that a linked list *can* solve the problem,
but *why* it is the right tool: constant-time reparenting, seamless splicing, and cache-friendly
O(1) lookups when paired with a hash map.

---

## Why Linked Lists

Array-backed containers force O(n) shifts whenever order changes. The systems modelled here all
reorder their elements at runtime, which is exactly where a doubly linked list wins:

- Moving a node to the front of a cache is a constant-time relink, not a copy
- Evicting the least-recent or least-frequent item is a constant-time removal
- Traversing backward and forward through history is pointer walking with no index math
- Free-memory blocks merge and split in place without moving the data they describe

---

## Modules

| File | Problem | Linked List Design |
| --- | --- | --- |
| `src/lru_cache.cpp` | Least Recently Used cache | Doubly linked list with a hash map for O(1) get and put |
| `src/lfu_cache.cpp` | Least Frequently Used cache | Per-frequency doubly linked lists with a minimum-frequency tracker |
| `src/browser_history.cpp` | Back and forward navigation | Doubly linked list with a current pointer |
| `src/playlist_manager.cpp` | Music playlist with wraparound | Circular doubly linked list |
| `src/free_list_allocator.cpp` | Memory allocator | Singly linked free list with block splitting and coalescing |
| `src/undo_redo.cpp` | Undo and redo history | Two linked-list stacks for undo and redo states |

---

## Complexity

| Module | get / access | put / mutation | Space |
| --- | --- | --- | --- |
| LRU Cache | O(1) | O(1) | O(capacity) |
| LFU Cache | O(1) | O(1) | O(capacity) |
| Browser History | O(1) now | O(steps) navigate, O(forward) visit | O(pages) |
| Playlist Manager | O(1) | O(1) | O(songs) |
| Free List Allocator | O(1) metadata | O(blocks) first-fit | O(free blocks) |
| Undo / Redo | O(1) | O(1) | O(states) |

---

## Requirements

- A C++ compiler supporting **C++14 or later** (GCC `g++` or Clang `clang++`)
- No external libraries, package managers or build tools

> The sources include the non-standard `<bits/stdc++.h>` convenience header, so they are built
> with GCC or Clang. They do not target MSVC (`cl.exe`).

---

## Build and Run

Compile any single module from the project root and run it:

```bash
g++ -std=c++14 -O2 -Wall src/lru_cache.cpp -o lru_cache
./lru_cache
```

On Windows, the same command produces `lru_cache.exe`:

```bat
g++ -std=c++14 -O2 -Wall src\lru_cache.cpp -o lru_cache.exe
lru_cache.exe
```

Build every module in one pass on Linux or macOS:

```bash
mkdir -p bin
for file in src/*.cpp; do
  name=$(basename "$file" .cpp)
  g++ -std=c++14 -O2 -Wall "$file" -o "bin/$name"
done
```

Build every module in one pass on Windows:

```bat
mkdir bin
for %f in (src\*.cpp) do g++ -std=c++14 -O2 -Wall "%f" -o "bin\%~nf.exe"
```

Swap in the source file of any module listed in [Modules](#modules) to run a different example.

---

## Example Output

Each program prints a deterministic transcript that walks through its data structure.

### `lru_cache`

```text
10
-1
-1 30 40
```

### `lfu_cache`

```text
10
-1
30
-1 30 40
```

### `browser_history`

```text
facebook.com
google.com
facebook.com
linkedin.com
google.com
leetcode.com
```

### `playlist_manager`

```text
Song A
Song B
Song C
Song A
Song C
```

### `free_list_allocator`

```text
0 30 50
0
```

### `undo_redo`

```text
Hello World
Hello
Hello World
Hello There
Hello World
```

---

## Project Structure

```text
faang-linkedlist-system-design/
├── src/
│   ├── lru_cache.cpp
│   ├── lfu_cache.cpp
│   ├── browser_history.cpp
│   ├── playlist_manager.cpp
│   ├── free_list_allocator.cpp
│   └── undo_redo.cpp
├── .gitignore
├── LICENSE
└── README.md
```

---

## Design Notes

- **Sentinel nodes.** The LRU and LFU lists use head and tail sentinels, which removes the
  null-pointer special cases from every insert and erase and keeps the relink logic branch-free.
- **Ownership.** The LFU cache stores each real node once in a key map and links it inside a
  frequency list; the key map owns the memory and the frequency lists only borrow pointers, so
  there is no double free on teardown.
- **Splicing on visit.** Browser history deletes the forward branch on every new visit, matching
  real browser semantics where a new page discards the redo stack.
- **Coalescing.** The allocator merges adjacent free blocks after every deallocation, keeping the
  free list sorted by offset and preventing fragmentation from neighbouring holes.
- **RAII.** Every module frees its allocations in a destructor, so the examples run clean under a
  leak checker.

---

## Contributing

Contributions are welcome.

1. Fork the project
2. Create your feature branch (`git checkout -b feature/amazing-solution`)
3. Compile with `-Wall` and confirm zero warnings
4. Commit your changes (`git commit -m "Add amazing solution"`)
5. Push to the branch (`git push origin feature/amazing-solution`)
6. Open a Pull Request

---

## Author

Created by **[Kumar44developer](https://github.com/Kumar44developer)**.

---

## License

Distributed under the MIT License. See `LICENSE` for more information.
