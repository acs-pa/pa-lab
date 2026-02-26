<!-- SPDX-License-Identifier: BSD-3-Clause -->

### dict (unordered map)

* [docs.python.org: dict](https://docs.python.org/3/library/stdtypes.html#mapping-types-dict)

Key-value container with unique keys; order guaranteed insertion order (Python 3.7+).

* **d[key] = value**: insert or overwrite
* **d.get(key)**: returns value or None
* **d[key]**: get (KeyError if missing)
* **for k, v in d.items()**: iterate

```python
def main() -> None:
    frequency = {}
    frequency["gigel"] = frequency.get("gigel", 0) + 1
    frequency["gigel"] = frequency.get("gigel", 0) + 1
    frequency["not_gigel"] = frequency.get("not_gigel", 0) + 1
    for name, count in frequency.items():
        print(name, count)


if __name__ == "__main__":
    main()
```

Runnable example: [dict.py](dict.py).
