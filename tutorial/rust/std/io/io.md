<!-- SPDX-License-Identifier: BSD-3-Clause -->

### IO (file read/write)

* [std::fs::File](https://doc.rust-lang.org/std/fs/struct.File.html)
* [std::io](https://doc.rust-lang.org/std/io/) — `BufRead`, `BufReader`, `Write`

You should use the Rust skel and buffered I/O for PA.

#### Reading

```rust
use std::fs::File;
use std::io::{BufRead, BufReader};

let fin = File::open("in").expect("in");
let mut lines = BufReader::new(fin).lines().map(|l| l.unwrap());

let x: i32 = lines.next().unwrap().parse().unwrap();

let mut tokens = lines.next().unwrap().split_whitespace();
let x: i32 = tokens.next().unwrap().parse().unwrap();
let y: i32 = tokens.next().unwrap().parse().unwrap();

// one line: integer, char, string
let mut tokens = lines.next().unwrap().split_whitespace();
let x: i32 = tokens.next().unwrap().parse().unwrap();
let c: char = tokens.next().unwrap().parse().unwrap();
let s: String = tokens.next().unwrap().into();
```

#### Writing

```rust
use std::fs::File;
use std::io::Write;

let mut fout = File::create("out").expect("out");

let x = 42;
writeln!(fout, "{}", x).unwrap();

let x = 1;
let y = 2;
writeln!(fout, "{} {}", x, y).unwrap();

let x = 1;
let c = 'a';
let s = "hello";
writeln!(fout, "{} {} {}", x, c, s).unwrap();
```

Runnable example: [io.rs](io.rs). From this folder: `make run` (creates sample `in` if missing).
