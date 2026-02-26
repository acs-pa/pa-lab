<!-- SPDX-License-Identifier: BSD-3-Clause -->

### minheap

* [docs.python.org: heapq](https://docs.python.org/3/library/heapq.html)

`heapq` provides a min-heap: the smallest element is at index 0. Use `heappush` and `heappop`.

* **heappush(heap, x)**: insert
* **heappop(heap)**: extract minimum
* **heap[0]**: peek minimum (without removing)

```python
import heapq


def main() -> None:
    minheap = []
    heapq.heappush(minheap, 1)
    heapq.heappush(minheap, 12)
    heapq.heappush(minheap, 6)
    heapq.heappush(minheap, 1)
    while minheap:
        top = heapq.heappop(minheap)
        print(top)
    # print: 1 1 6 12


if __name__ == "__main__":
    main()
```

Runnable example: [minheap.py](minheap.py).

### maxheap

From **Python 3.14** onward, `heapq` has dedicated max-heap functions (no value negation):

* **heappush_max(heap, x)**: insert
* **heappop_max(heap)**: extract maximum
* **heap[0]**: peek maximum (without removing)

See [heapq (Python 3.14)](https://docs.python.org/3.14/library/heapq.html).

```python
import heapq


def main() -> None:
    maxheap = []
    heapq.heappush_max(maxheap, 1)
    heapq.heappush_max(maxheap, 12)
    heapq.heappush_max(maxheap, 6)
    heapq.heappush_max(maxheap, 1)
    while maxheap:
        top = heapq.heappop_max(maxheap)
        print(top)
    # print: 12 6 1 1


if __name__ == "__main__":
    main()
```

On **Python &lt; 3.14**, `heapq` is min-heap only. Use the negation trick: push `-x`, pop `-heapq.heappop(heap)`.

```python
import heapq


def main() -> None:
    maxheap = []
    for x in (1, 12, 6, 1):
        heapq.heappush(maxheap, -x)
    while maxheap:
        top = -heapq.heappop(maxheap)
        print(top)
    # print: 12 6 1 1


if __name__ == "__main__":
    main()
```

Runnable example: [maxheap.py](maxheap.py) (uses 3.14 API when available, else negation).

In each subfolder: `make run` runs both examples; `make run-min` / `make run-max` run one.
