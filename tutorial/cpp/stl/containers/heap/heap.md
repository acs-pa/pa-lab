<!-- SPDX-License-Identifier: BSD-3-Clause -->

### minheap

Use `multiset<T>` for a min-heap: smallest at `*begin()`, remove with `erase(begin())`.

* **insert(x)**: insert, O(log n)
* **erase(begin())**: extract minimum, O(log n)
* **begin()**: iterator to minimum

Runnable example: [minheap.cpp](minheap.cpp).

### maxheap

Use `multiset<T, greater<T>>` for a max-heap.

Runnable example: [maxheap.cpp](maxheap.cpp).

In this folder: `make run` runs both; `make run-min` / `make run-max` run one.
