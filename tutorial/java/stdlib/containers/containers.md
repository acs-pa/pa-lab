<!-- SPDX-License-Identifier: BSD-3-Clause -->

# containers

Standard library collections ([java.util](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/package-summary.html)).

| Container | Use at PA | Doc |
|-----------|-----------|-----|
| [list](list/list.md) | dynamic array, matrix | [ArrayList](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/ArrayList.html) |
| [stack](stack/stack.md) | LIFO | [Deque](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/Deque.html) (ArrayDeque) |
| [queue](queue/queue.md) | FIFO | [Queue](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/Queue.html) (ArrayDeque) |
| [map](map/map.md) | key-value, unordered | [HashMap](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/HashMap.html) |
| [set](set/set.md) | unordered set | [HashSet](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/HashSet.html) |
| [heap](heap/heap.md) | min-heap, max-heap | [PriorityQueue](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/PriorityQueue.html) |

In each subfolder: `make run` to run the example; `make clean` to remove generated files.
