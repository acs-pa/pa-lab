// SPDX-License-Identifier: BSD-3-Clause
// Run: create "in" with e.g. "42\n1 2\n3 a hello" then: rustc io.rs && ./io

use std::fs::File;
use std::io::{BufRead, BufReader, Write};

fn main() {
    let fin = File::open("in").expect("in");
    let mut lines = BufReader::new(fin).lines().map(|l| l.unwrap());

    let x: i32 = lines.next().unwrap().parse().unwrap();

    let line2 = lines.next().unwrap();
    let mut tokens = line2.split_whitespace();
    let a: i32 = tokens.next().unwrap().parse().unwrap();
    let b: i32 = tokens.next().unwrap().parse().unwrap();

    let line3 = lines.next().unwrap();
    let mut tokens = line3.split_whitespace();
    let _n: i32 = tokens.next().unwrap().parse().unwrap();
    let c: char = tokens.next().unwrap().parse().unwrap();
    let s: String = tokens.next().unwrap().into();

    let mut fout = File::create("out").expect("out");
    writeln!(fout, "{} {} {} {} {}", x, a, b, c, s).unwrap();
    println!("wrote to out");
}
