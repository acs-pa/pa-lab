<!-- SPDX-License-Identifier: BSD-3-Clause -->

### HashMap (unordered map)

* [doc.rust-lang.org/std/collections/struct.HashMap](https://doc.rust-lang.org/std/collections/struct.HashMap.html)

Key-value container with unique keys; order not guaranteed.

`HashMap<K, V>` API (e.g. `let mut map: HashMap<String, i32>`):
* **insert()**: `map.insert(k, v)` — insert or overwrite
* **get()**: `map.get(&k)` — `Option<&V>`
* **entry()**: `map.entry(k).or_insert(0)` — get or insert, then modify
* **iter()**: `for (k, v) in &map { }`
* **len()**, **is_empty()**

```rust
use std::collections::HashMap;

let mut frequency: HashMap<String, i32> = HashMap::new();
*frequency.entry("gigel".into()).or_insert(0) += 1;
*frequency.entry("gigel".into()).or_insert(0) += 1;
*frequency.entry("not_gigel".into()).or_insert(0) += 1;

for (name, count) in &frequency {
    println!("{} {}", name, count);
}
```

Runnable example: [hashmap.rs](hashmap.rs).
