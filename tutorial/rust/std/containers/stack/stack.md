<!-- SPDX-License-Identifier: BSD-3-Clause -->

### stack

Use `Vec<T>` with `push` and `pop` (LIFO).

* **push()**: `st.push(x)` — O(1)
* **pop()**: `st.pop()` — returns `Option<T>`, O(1)
* **last()**: `st.last()` — peek top, `Option<&T>`
* **is_empty()** / **len()**: `st.is_empty()`, `st.len()`

```rust
let mut st: Vec<i32> = Vec::new();
st.push(1);
st.push(2);
st.push(3);

while let Some(top) = st.pop() {
    println!("{}", top);
}
// print: 3 2 1
```

Runnable example: [stack.rs](stack.rs).
