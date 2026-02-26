// SPDX-License-Identifier: BSD-3-Clause
// Run: rustc set.rs && ./set

use std::collections::BTreeSet;

fn main() {
    let mut s: BTreeSet<i32> = BTreeSet::new();
    s.insert(1);
    s.insert(12);
    s.insert(6);
    s.insert(1);

    for x in &s {
        println!("{}", x);
    }
    // print: 1 6 12
}
