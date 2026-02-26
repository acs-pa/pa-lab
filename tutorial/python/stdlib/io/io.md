<!-- SPDX-License-Identifier: BSD-3-Clause -->

### IO (file read/write)

* [docs.python.org: open](https://docs.python.org/3/library/functions.html#open)
* [docs.python.org: io](https://docs.python.org/3/library/io.html)

You should use the Python skel and file I/O for PA.

#### Reading

```python
def main() -> None:
    with open("in") as fin:
        x = int(fin.readline().strip())
        tokens = fin.readline().split()
        a, b = int(tokens[0]), int(tokens[1])
        line = fin.readline().split()
        n = int(line[0])
        c = line[1][0]
        s = line[2]


if __name__ == "__main__":
    main()
```

#### Writing

```python
def main() -> None:
    with open("out", "w") as fout:
        fout.write(f"{x}\n")
        fout.write(f"{a} {b}\n")
        fout.write(f"{x} {c} {s}\n")


if __name__ == "__main__":
    main()
```

Runnable example: [io.py](io.py). From this folder: `make run` (creates sample `in` if missing).
