<!-- SPDX-License-Identifier: BSD-3-Clause -->

### queue

* [docs.oracle.com: Queue](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/Queue.html)
* [docs.oracle.com: ArrayDeque](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/ArrayDeque.html)

Use `Queue<T>` with `ArrayDeque<T>` for FIFO: `add` (or `offer`) / `poll` / `peek`.

* **add(T x)** or **offer(T x)**: enqueue, O(1)
* **poll()**: dequeue and return head, O(1)
* **peek()**: head without removing, O(1)
* **isEmpty()**

```java
import java.util.ArrayDeque;
import java.util.Queue;

Queue<Integer> q = new ArrayDeque<>();
for (int i = 0; i < 5; i++) {
    q.add(i);
}
while (!q.isEmpty()) {
    int front = q.poll();
    System.out.print(front + " ");
}
System.out.println();
// print: 0 1 2 3 4
```

Runnable example: [QueueDemo.java](QueueDemo.java).
