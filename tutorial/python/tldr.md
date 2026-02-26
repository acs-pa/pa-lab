<!-- SPDX-License-Identifier: BSD-3-Clause -->

# PA Python - TLDR

## PA skel
During the PA laboratories, you'll receive a skeleton for each task.

NOTE: `should` on this page means tips & tricks for PA (may not apply elsewhere).

Everything below uses only the **standard library**. No pip packages.

```python
class Task:
    def __init__(self):
        # TODO: define attributes
        pass

    def solve(self):
        self.read_input()
        self.write_output(self.get_result())

    def read_input(self):
        with open("in") as fin:
            # TODO: read input from fin
            pass

    def get_result(self):
        # TODO: implement the solution
        return 0

    def write_output(self, result):
        with open("out", "w") as fout:
            fout.write(f"{result}\n")


def main() -> None:
    task = Task()
    task.solve()


# [ATENTIE] NU modifica blocul de mai jos!
if __name__ == "__main__":
    main()
```

Notes:
* Use only the standard library (no pip).
* You `don't` need to ever change the `main()` call or the `if __name__ == "__main__"` block!
* You `need` to complete the `Task` class and its methods.
* The `check` command runs the tasks (if Python is supported).

## Python tweaks (stdlib only)

Details and runnable examples are in the `std` tree. Quick reference:

| Topic        | Python std              | See |
|-------------|--------------------------|-----|
| **IO**      | `open()`, `read()`, `write()` | [std/io/io.md](std/io/io.md) |
| **arrays**  | `list`                   | [std/containers/list/list.md](std/containers/list/list.md) |
| **matrix**  | `list` of `list`         | [std/containers/list/list.md](std/containers/list/list.md) |
| **stack**   | `list` (append / pop)    | [std/containers/stack/stack.md](std/containers/stack/stack.md) |
| **queue**   | `collections.deque`      | [std/containers/queue/queue.md](std/containers/queue/queue.md) |
| **hashtable** | `dict`                 | [std/containers/map/dict.md](std/containers/map/dict.md) |
| **set**     | `set` (unordered)        | [std/containers/set/set.md](std/containers/set/set.md) |
| **minheap** | `heapq`                  | [std/containers/heap/heap.md](std/containers/heap/heap.md) |

Containers index: [std/containers/containers.md](std/containers/containers.md).

In each subfolder: `make run` to run the example; `make clean` to remove generated files.
