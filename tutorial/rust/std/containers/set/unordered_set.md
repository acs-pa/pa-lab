<!-- SPDX-License-Identifier: BSD-3-Clause -->

### HashSet (unordered set)

* [doc.rust-lang.org/std/collections/struct.HashSet](https://doc.rust-lang.org/std/collections/struct.HashSet.html)

Set with unique elements; order not guaranteed. Use when order does not matter.

`HashSet<T>` API (e.g. `let mut s: HashSet<i32>`):
* **insert()**: `s.insert(x)` — returns `bool` (true if new)
* **contains()**: `s.contains(&x)`
* **iter()**: arbitrary order
* **len()**, **is_empty()**

```rust
use std::collections::HashSet;

let mut s: HashSet<i32> = HashSet::new();
s.insert(1);
s.insert(12);
s.insert(6);

for x in &s {
    println!("{}", x);
}
```

Runnable example: [unordered_set.rs](unordered_set.rs).
