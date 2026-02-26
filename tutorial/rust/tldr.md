<!-- SPDX-License-Identifier: BSD-3-Clause -->

# PA Rust - TLDR

## PA skel
During the PA laboratories, you'll receive a skeleton for each task.

NOTE: `should` on this page means tips & tricks for PA (may not apply elsewhere).

Everything below uses only the **standard library** (`std`). No external crates.

```rust
// std::fs::File — https://doc.rust-lang.org/std/fs/struct.File.html
// std::io (BufRead, BufReader, Write) — https://doc.rust-lang.org/std/io/
use std::fs::File;
use std::io::{BufRead, BufReader, Write};

// std::default::Default — https://doc.rust-lang.org/std/default/trait.Default.html
#[derive(Default)]
struct Task {
    // TODO: define fields
}

impl Task {
    pub fn solve(&mut self) {
        self.read_input();
        self.write_output(self.get_result());
    }

    fn read_input(&mut self) {
        let fin = File::open("in").expect("in");
        let mut lines = BufReader::new(fin).lines().map(|l| l.unwrap());
        // TODO: read input from lines
    }

    fn get_result(&self) -> i32 {
        // TODO: implement the solution
        return 0;
    }

    fn write_output(&self, result: i32) {
        let mut fout = File::create("out").expect("out");
        // TODO: write result
        writeln!(fout, "{}", result).expect("write");
    }
}

// [ATENTIE] NU modifica functia main!
fn main() {
    // obiect Task pe heap (analog C++: new Task)
    let mut task = Box::new(Task::default());
    task.solve();
}
```

Notes:
* Use only types and modules from `std` (no external crates).
* You `don't` need to ever change the `main()` function!
* You `need` to complete the `Task` struct and its methods.
  * Reading/writing must use `std::fs::File` and `std::io` for performance.
  * Usually the skeleton already implements `read_input()` and `write_output()`.
  * You implement `get_result()` and any helpers.
* The `check` command compiles and runs the tasks.
  ```bash
  ./check rust
  ./check rust task-1
  ./check rust task-1 1
  ```

## Rust tweaks (std only)

Details and runnable examples are in the `std` tree. Quick reference:

| Topic        | Rust std              | See |
|-------------|------------------------|-----|
| **IO**      | `File`, `BufReader`, `Write`, `writeln!` | [std/io/io.md](std/io/io.md) |
| **arrays**  | `Vec<T>`              | [std/containers/vec/vec.md](std/containers/vec/vec.md) |
| **matrix**  | `Vec<Vec<T>>`         | [std/containers/vec/vec.md](std/containers/vec/vec.md) |
| **stack**   | `Vec` (push / pop)    | [std/containers/stack/stack.md](std/containers/stack/stack.md) |
| **queue**   | `VecDeque<T>`         | [std/containers/queue/queue.md](std/containers/queue/queue.md) |
| **hashtable** | `HashMap<K, V>`     | [std/containers/map/hashmap.md](std/containers/map/hashmap.md) |
| **ordered set** | `BTreeSet<T>`    | [std/containers/set/set.md](std/containers/set/set.md) |
| **unordered set** | `HashSet<T>`   | [std/containers/set/unordered_set.md](std/containers/set/unordered_set.md) |
| **minheap** | `BinaryHeap<Reverse<T>>` | [std/containers/binary_heap/minheap.md](std/containers/binary_heap/minheap.md) |
| **maxheap** | `BinaryHeap<T>`      | [std/containers/binary_heap/maxheap.md](std/containers/binary_heap/maxheap.md) |

Containers index: [std/containers/containers.md](std/containers/containers.md).
