<!-- SPDX-License-Identifier: BSD-3-Clause -->

### minheap

* [docs.oracle.com: PriorityQueue](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/PriorityQueue.html)

`PriorityQueue<T>` is a min-heap by default (natural order). Use `add` (or `offer`) and `poll` (or `remove`).

* **add(T x)** or **offer(T x)**: insert, O(log n)
* **poll()**: remove and return minimum, O(log n)
* **peek()**: minimum without removing, O(1)

```java
import java.util.PriorityQueue;
import java.util.Queue;

Queue<Integer> minheap = new PriorityQueue<>();
minheap.add(1);
minheap.add(12);
minheap.add(6);
minheap.add(1);
while (!minheap.isEmpty()) {
    int top = minheap.poll();
    System.out.println(top);
}
// print: 1 1 6 12
```

Runnable example: [MinHeap.java](MinHeap.java).

### maxheap

Use `PriorityQueue<T>` with a **reverse comparator**: `Comparator.reverseOrder()` (Java 8+).

```java
import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Queue;

Queue<Integer> maxheap = new PriorityQueue<>(Comparator.reverseOrder());
maxheap.add(1);
maxheap.add(12);
maxheap.add(6);
maxheap.add(1);
while (!maxheap.isEmpty()) {
    int top = maxheap.poll();
    System.out.println(top);
}
// print: 12 6 1 1
```

Runnable example: [MaxHeap.java](MaxHeap.java).

In this folder: `make run` runs both; `make run-min` / `make run-max` run one.
