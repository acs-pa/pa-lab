<!-- SPDX-License-Identifier: BSD-3-Clause -->

### set (unordered set)

* [docs.python.org: set](https://docs.python.org/3/library/stdtypes.html#set-types-set-frozenset)

Set with unique elements; order not guaranteed (in practice insertion order in recent CPython).

* **s.add(x)**: insert
* **x in s**: membership, O(1) average
* **for x in s**: iterate
* **len(s)**

```python
def main() -> None:
    s = set()
    s.add(1)
    s.add(12)
    s.add(12)
    s.add(6)
    s.add(1)
    for x in sorted(s):  # sorted for reproducible output
        print(x)
    # print: 1 6 12


if __name__ == "__main__":
    main()
```

Runnable example: [set.py](set.py).
