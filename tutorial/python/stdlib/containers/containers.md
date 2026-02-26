<!-- SPDX-License-Identifier: BSD-3-Clause -->

# containers

Standard library and built-in types ([Library Reference](https://docs.python.org/3/library/)).

| Container | Use at PA | Doc |
|-----------|-----------|-----|
| [list](list/list.md) | dynamic array, matrix | [Built-in Types: list](https://docs.python.org/3/library/stdtypes.html#sequence-types-list-tuple-range) |
| [stack](stack/stack.md) | LIFO (list append/pop) | — |
| [queue](queue/queue.md) | FIFO | [collections.deque](https://docs.python.org/3/library/collections.html#collections.deque) |
| [dict](map/dict.md) | key-value, unordered | [Mapping Types: dict](https://docs.python.org/3/library/stdtypes.html#mapping-types-dict) |
| [set](set/set.md) | unordered set | [Set Types: set](https://docs.python.org/3/library/stdtypes.html#set-types-set-frozenset) |
| [heap](heap/heap.md) | min-heap, max-heap (3.14+ or negation) | [heapq](https://docs.python.org/3/library/heapq.html) |

In each subfolder: `make run` to run the example; `make clean` to remove generated files.
