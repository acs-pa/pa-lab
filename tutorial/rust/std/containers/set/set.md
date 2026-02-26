<!-- SPDX-License-Identifier: BSD-3-Clause -->

### BTreeSet (ordered set)

* [doc.rust-lang.org/std/collections/struct.BTreeSet](https://doc.rust-lang.org/std/collections/struct.BTreeSet.html)

Set with unique elements, sorted (ascending). Use when you need ordered iteration.

`BTreeSet<T>` API (e.g. `let mut s: BTreeSet<i32>`):
* **insert()**: `s.insert(x)` — returns `bool` (true if new)
* **contains()**: `s.contains(&x)`
* **iter()**: elements in order
* **len()**, **is_empty()**

```rust
use std::collections::BTreeSet;

let mut s: BTreeSet<i32> = BTreeSet::new();
s.insert(1);
s.insert(12);
s.insert(12);
s.insert(6);
s.insert(1);

for x in &s {
    println!("{}", x);
}
// print: 1 6 12
```

Runnable example: [set.rs](set.rs).
