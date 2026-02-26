<!-- SPDX-License-Identifier: BSD-3-Clause -->

### stack

* [docs.oracle.com: Deque](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/Deque.html)

Use `Deque<T>` (e.g. `ArrayDeque<T>`) for a stack: `push` / `pop` / `peek`. Prefer over legacy `Stack<T>`.

* **push(T x)**: push, O(1)
* **pop()**: pop and return top, O(1)
* **peek()**: top without removing, O(1)
* **isEmpty()**

```java
import java.util.ArrayDeque;
import java.util.Deque;

Deque<Integer> st = new ArrayDeque<>();
st.push(1);
st.push(2);
st.push(3);
while (!st.isEmpty()) {
    int top = st.pop();
    System.out.println(top);
}
// print: 3 2 1
```

Runnable example: [StackDemo.java](StackDemo.java).
