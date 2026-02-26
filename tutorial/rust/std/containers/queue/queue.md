<!-- SPDX-License-Identifier: BSD-3-Clause -->

### queue

* [doc.rust-lang.org/std/collections/struct.VecDeque](https://doc.rust-lang.org/std/collections/struct.VecDeque.html)

Use `VecDeque<T>` for FIFO: `push_back` and `pop_front`.

`VecDeque<T>` API (e.g. `let mut q: VecDeque<i32>`):
* **push_back()**: `q.push_back(x)` — enqueue, O(1)
* **pop_front()**: `q.pop_front()` — dequeue, returns `Option<T>`, O(1)
* **front()**: `q.front()` — peek, `Option<&T>`
* **is_empty()** / **len()**: `q.is_empty()`, `q.len()`

```rust
use std::collections::VecDeque;

let mut q: VecDeque<i32> = VecDeque::new();
q.push_back(1);
q.push_back(2);
q.push_back(3);

while let Some(front) = q.pop_front() {
    println!("{}", front);
}
// print: 1 2 3
```

Runnable example: [queue.rs](queue.rs).
