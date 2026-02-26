// SPDX-License-Identifier: BSD-3-Clause
// Run: rustc hashmap.rs && ./hashmap

use std::collections::HashMap;

fn main() {
    let mut frequency: HashMap<String, i32> = HashMap::new();
    *frequency.entry("gigel".into()).or_insert(0) += 1;
    *frequency.entry("gigel".into()).or_insert(0) += 1;
    *frequency.entry("not_gigel".into()).or_insert(0) += 1;

    for (name, count) in &frequency {
        println!("{} {}", name, count);
    }
}
