<!-- SPDX-License-Identifier: BSD-3-Clause -->

### queue

* [docs.python.org: collections.deque](https://docs.python.org/3/library/collections.html#collections.deque)

Use `collections.deque` for FIFO: `append` and `popleft`.

* **append(x)**: enqueue, O(1)
* **popleft()**: dequeue, returns element, O(1)
* **q[0]**: peek front
* **len(q)**, **not q**

```python
from collections import deque


def main() -> None:
    q = deque()
    q.append(1)
    q.append(2)
    q.append(3)
    while q:
        front = q.popleft()
        print(front)
    # print: 1 2 3


if __name__ == "__main__":
    main()
```

Runnable example: [queue.py](queue.py).
