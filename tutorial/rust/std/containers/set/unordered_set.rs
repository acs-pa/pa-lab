// SPDX-License-Identifier: BSD-3-Clause
// Run: rustc unordered_set.rs && ./unordered_set

use std::collections::HashSet;

fn main() {
    let mut s: HashSet<i32> = HashSet::new();
    s.insert(1);
    s.insert(12);
    s.insert(6);

    for x in &s {
        println!("{}", x);
    }
}
