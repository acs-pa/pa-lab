<!-- SPDX-License-Identifier: BSD-3-Clause -->

# Rust Tutorial

## TLDR

A short summary for what you need / should use at PA can be found at [PA Rust: TLDR](tldr.md).

## Docs

Links:
* [doc.rust-lang.org](https://doc.rust-lang.org): Rust standard library and book
  * [std](https://doc.rust-lang.org/std/): standard library
  * [std::collections](https://doc.rust-lang.org/std/collections/): containers
  * [std::io](https://doc.rust-lang.org/std/io/): I/O traits and types

This tutorial uses only the **standard library** (`std`). No external crates.

## Rust basics

* Rust is a systems language with ownership, no garbage collector, and a strong type system.
* For PA you only need: structs, `impl` blocks, `Vec`, file I/O, and a few types from `std::collections`.

### Hello Gigel in Rust

```rust
use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut line = String::new();
    stdin.lock().read_line(&mut line).unwrap();
    let x: i32 = line.trim().parse().unwrap();
    println!("Hello, Gigel! I got {} from the PA team!", x);
}
```

* In PA you read/write from files (`std::fs::File`), not stdin — see [std/io](std/io/io.md).

### Struct and impl

* A **struct** holds data; **impl** blocks define methods on that type.
* Methods take `&self` (read), `&mut self` (modify), or `self` (consume).

```rust
struct Task {
    n: usize,
    v: Vec<i32>,
}

impl Task {
    fn get_result(&self) -> i32 {
        self.v.iter().sum()
    }

    fn add(&mut self, x: i32) {
        self.v.push(x);
    }
}
```

### Default and Box

* **Default**: trait for default values; use `#[derive(Default)]` so `Task::default()` works.
* **Box&lt;T&gt;**: allocates `T` on the heap (like C++ `new`). The skeleton uses `Box::new(Task::default())` in `main()`.

```rust
#[derive(Default)]
struct Task {
    n: usize,
}

fn main() {
    let mut task = Box::new(Task::default());
    task.n = 10;
}
```

### Option and unwrap

* **Option&lt;T&gt;**: either `Some(value)` or `None`. Used by `Vec::pop()`, `Iterator::next()`, etc.
* In PA you often use `.unwrap()` or `.expect("msg")` when you assume the value is present.

```rust
let mut v = vec![1, 2, 3];
let last = v.pop();       // Option<i32>
let x = last.unwrap();    // 3
```

## std

Rust’s standard library provides I/O and collections. Continue the tutorial from the `std` tree:

* [std/io](std/io/io.md) — file read/write
* [std/containers](std/containers/containers.md) — Vec, VecDeque, HashMap, sets, heaps
