// SPDX-License-Identifier: BSD-3-Clause
// Run: rustc queue.rs && ./queue

use std::collections::VecDeque;

fn main() {
    let mut q: VecDeque<i32> = VecDeque::new();
    for i in 0..5 {
        q.push_back(i);
    }

    while let Some(front) = q.pop_front() {
        print!("{} ", front);
    }
    println!();
    // print: 0 1 2 3 4
}
