// SPDX-License-Identifier: BSD-3-Clause
// Run: rustc vec.rs && ./vec

fn main() {
    let mut v: Vec<i32> = Vec::new();
    v.push(5);
    v.push(1);
    v.push(3);
    println!("len = {}", v.len());
    println!("last = {:?}", v.last());
    let last = v.pop();
    println!("pop = {:?}, len = {}", last, v.len());
}
