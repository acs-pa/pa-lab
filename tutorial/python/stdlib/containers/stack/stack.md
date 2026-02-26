<!-- SPDX-License-Identifier: BSD-3-Clause -->

### stack

Use `list` with `append` and `pop` (LIFO).

* **append(x)**: push, O(1)
* **pop()**: pop, returns element, O(1)
* **st[-1]**: peek top
* **len(st)**, **not st**

```python
def main() -> None:
    st = []
    st.append(1)
    st.append(2)
    st.append(3)
    while st:
        top = st.pop()
        print(top)
    # print: 3 2 1


if __name__ == "__main__":
    main()
```

Runnable example: [stack.py](stack.py).
