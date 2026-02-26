<!-- SPDX-License-Identifier: BSD-3-Clause -->

# containers

Standard library containers ([std::collections](https://doc.rust-lang.org/std/collections/)).

| Container | Use at PA | Doc |
|-----------|-----------|-----|
| [Vec](vec/vec.md) | dynamic array, matrix | [std::vec::Vec](https://doc.rust-lang.org/std/vec/struct.Vec.html) |
| [stack](stack/stack.md) | LIFO (Vec push/pop) | — |
| [queue](queue/queue.md) | FIFO | [std::collections::VecDeque](https://doc.rust-lang.org/std/collections/struct.VecDeque.html) |
| [HashMap](map/hashmap.md) | key-value, unordered | [std::collections::HashMap](https://doc.rust-lang.org/std/collections/struct.HashMap.html) |
| [BTreeSet](set/set.md) | ordered set | [std::collections::BTreeSet](https://doc.rust-lang.org/std/collections/struct.BTreeSet.html) |
| [HashSet](set/unordered_set.md) | unordered set | [std::collections::HashSet](https://doc.rust-lang.org/std/collections/struct.HashSet.html) |
| [BinaryHeap (min)](binary_heap/minheap.md) | min-heap | [std::collections::BinaryHeap](https://doc.rust-lang.org/std/collections/struct.BinaryHeap.html), [Reverse](https://doc.rust-lang.org/std/cmp/struct.Reverse.html) |
| [BinaryHeap (max)](binary_heap/maxheap.md) | max-heap | [std::collections::BinaryHeap](https://doc.rust-lang.org/std/collections/struct.BinaryHeap.html) |

In each subfolder: `make run` to build and run the example(s); `make clean` to remove binaries.
