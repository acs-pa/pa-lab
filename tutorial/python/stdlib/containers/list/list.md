<!-- SPDX-License-Identifier: BSD-3-Clause -->

### list

* [docs.python.org: list](https://docs.python.org/3/library/stdtypes.html#sequence-types-list-tuple-range)

Resizable array. Use at PA for arrays and matrices.

`list` API (e.g. `v = []`):
* **len(v)**: number of elements
* **v[i]**: access, O(1)
* **v.append(x)**: insert at end, O(1)
* **v.pop()**: remove last, returns element, O(1)
* **v[-1]**, **v[0]**: last / first element

#### Dynamic list

```python
def main() -> None:
    n = int(input())
    v = []
    for _ in range(n):
        x = int(input())
        v.append(x)


if __name__ == "__main__":
    main()
```

#### n elements, 0-indexed

```python
def main() -> None:
    n = int(input())
    v = [0] * n
    for i in range(n):
        v[i] = int(input())


if __name__ == "__main__":
    main()
```

#### n+1 elements, 1-indexed (e.g. DP)

```python
def main() -> None:
    n = int(input())
    v = [0] * (n + 1)
    for i in range(1, n + 1):
        v[i] = int(input())


if __name__ == "__main__":
    main()
```

#### Matrix (1-indexed n×m)

```python
def main() -> None:
    n, m = int(input()), int(input())
    dp = [[0] * (m + 1) for _ in range(n + 1)]
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            # use dp[i][j]
            pass


if __name__ == "__main__":
    main()
```

#### Iteration

```python
def main() -> None:
    for x in v:
        pass
    for i, x in enumerate(v):
        pass


if __name__ == "__main__":
    main()
```

Runnable example: [list.py](list.py).
