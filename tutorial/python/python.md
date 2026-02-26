<!-- SPDX-License-Identifier: BSD-3-Clause -->

# Python Tutorial

## TLDR

A short summary for what you need / should use at PA can be found at [PA Python: TLDR](tldr.md).

## Docs

Links:
* [docs.python.org](https://docs.python.org/3/): Python documentation
  * [Library Reference](https://docs.python.org/3/library/): standard library
  * [Built-in Types](https://docs.python.org/3/library/stdtypes.html): list, dict, set, etc.
  * [io](https://docs.python.org/3/library/io.html): I/O

This tutorial uses only the **standard library**. No external packages (pip).

## Python basics

* Python is a high-level, interpreted language with dynamic typing.
* For PA you typically use: files (open/read/write), lists, dict, set, and `collections.deque` or `heapq`.

### Hello Gigel in Python

```python
def main() -> None:
    x = int(input())
    print(f"Hello, Gigel! I got {x} from the PA team!")


if __name__ == "__main__":
    main()
```

* In PA you usually read/write from files — see [std/io](std/io/io.md).

### Class and methods

* A **class** holds data and methods; `self` is the instance.

```python
class Task:
    def __init__(self):
        self.n = 0
        self.v = []

    def solve(self):
        self.read_input()
        self.write_output(self.get_result())

    def get_result(self):
        return sum(self.v)


def main() -> None:
    task = Task()
    task.solve()


if __name__ == "__main__":
    main()
```

## stdlib

Python’s standard library provides I/O and built-in types. Continue the tutorial from the `stdlib` tree:

* [stdlib/io](stdlib/io/io.md) — file read/write
* [stdlib/containers](stdlib/containers/containers.md) — list, dict, set, deque, heapq.
