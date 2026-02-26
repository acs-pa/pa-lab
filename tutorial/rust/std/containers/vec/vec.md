<!-- SPDX-License-Identifier: BSD-3-Clause -->

### Vec

* [doc.rust-lang.org/std/vec/struct.Vec](https://doc.rust-lang.org/std/vec/struct.Vec.html)

Resizable array. Use at PA for arrays and matrices.

`Vec<T>` API (e.g. `let mut v: Vec<i32>`):
* **len()**: `v.len()` — number of elements
* **operator[]**: `v[i]` — access, O(1)
* **push()**: `v.push(x)` — insert at end, O(1)
* **pop()**: `v.pop()` — remove last, returns `Option<T>`, O(1)
* **front/back**: `v.first()`, `v.last()` — `Option<&T>`

#### Dynamic vector

```rust
let mut v: Vec<i32> = Vec::new();
for _ in 0..n {
    let x: i32 = lines.next().unwrap().parse().unwrap();
    v.push(x);
}
```

#### n elements, 0-indexed

```rust
let mut v = vec![0; n];
for i in 0..n {
    let x: i32 = lines.next().unwrap().parse().unwrap();
    v[i] = x;
}
```

#### n+1 elements, 1-indexed (e.g. DP)

```rust
let mut v = vec![0; n + 1];
for i in 1..=n {
    let x: i32 = lines.next().unwrap().parse().unwrap();
    v[i] = x;
}
```

#### Matrix (1-indexed n×m)

```rust
let mut dp = vec![vec![0; m + 1]; n + 1];
for i in 1..=n {
    for j in 1..=m {
        // use dp[i][j]
    }
}
```

#### Iteration

```rust
for x in &v { }           // borrow, no change
for x in &mut v { }       // mutable borrow
for (i, x) in v.iter().enumerate() { }  // with index
```

Runnable example: [vec.rs](vec.rs).
