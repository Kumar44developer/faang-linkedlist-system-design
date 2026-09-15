# FAANG Linked List System Design

A collection of FAANG-style system design problems implemented in C++ using linked lists as the core data structure. Each module is self-contained with its own `main` function and a runnable example, showing how pointer-based structures power real systems.

## Overview

Every solution favors linked lists over array-backed containers to demonstrate constant-time insertion, removal, and reordering. The examples range from classic cache eviction policies to memory management and editor state, each built around a tailored linked-list design.

## Modules

| File | Problem | Linked List Design |
| --- | --- | --- |
| src/lru_cache.cpp | Least Recently Used cache | Doubly linked list with a hash map for O(1) get and put |
| src/lfu_cache.cpp | Least Frequently Used cache | Per-frequency doubly linked lists with a minimum-frequency tracker |
| src/browser_history.cpp | Back and forward navigation | Doubly linked list with a current pointer |
| src/playlist_manager.cpp | Music playlist with wraparound | Circular doubly linked list |
| src/free_list_allocator.cpp | Memory allocator | Singly linked free list with block splitting and coalescing |
| src/undo_redo.cpp | Undo and redo history | Two linked-list stacks for undo and redo states |

## Requirements

- A C++ compiler supporting C++14 or later, such as g++ (GCC) or Clang

## Build and Run

Compile and run any module from the project root:

```bash
g++ -std=c++14 src/lru_cache.cpp -o lru_cache
./lru_cache
```

On Windows, run the generated `lru_cache.exe`.

## Example Output

| Module | Output |
| --- | --- |
| lru_cache | `10` / `-1` / `-1 30 40` |
| lfu_cache | `10` / `-1` / `30` / `-1 30 40` |
| browser_history | `facebook.com` then `google.com`, `facebook.com`, `linkedin.com`, `google.com`, `leetcode.com` |
| playlist_manager | `Song A`, `Song B`, `Song C`, `Song A`, `Song C` |
| free_list_allocator | `0 30 50` then `0` |
| undo_redo | `Hello World`, `Hello`, `Hello World`, `Hello There`, `Hello World` |

## Author

Created by [Kumar44developer](https://github.com/Kumar44developer).
