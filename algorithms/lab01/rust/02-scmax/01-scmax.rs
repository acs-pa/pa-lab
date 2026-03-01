// SPDX-License-Identifier: BSD-3-Clause

use std::fs::File;
use std::io::{BufRead, BufReader, Write};

#[derive(Default)]
struct Task {
    n: usize,
    v: Vec<i32>,
}

impl Task {
    pub fn solve(&mut self) {
        self.read_input();
        let result = self.get_result();
        self.write_output(result);
    }

    fn read_input(&mut self) {
        let fin = File::open("in").expect("in");
        let mut lines = BufReader::new(fin).lines().map(|l| l.unwrap());
        self.n = lines.next().unwrap().parse().unwrap();
        self.v = vec![0]; // index 0 nefolosit; preferăm indexarea de la 1
        let rest: Vec<i32> = lines
            .next()
            .unwrap()
            .split_whitespace()
            .map(|s| s.parse().unwrap())
            .collect();
        self.v.extend(rest);
    }

    fn get_result(&self) -> (usize, Vec<i32>) {
        self.scmax()
    }

    // SCMAX = Subșir Crescător Maximal, implementarea clasică cu DP
    // T = O(n^2)
    // S = O(n)
    fn scmax(&self) -> (usize, Vec<i32>) {
        // dp[i] = lungimea celui mai lung subșir (SCMAX) folosind (doar o parte) din primele i elemente din vectorul v și care se termină pe poziția i
        let mut dp = vec![0; self.n + 1];
        // prev[i] = poziția elementului precedent din SCMAX care se termină pe poziția i
        let mut prev = vec![0; self.n + 1];

        // Caz de bază
        dp[1] = 1;
        prev[1] = 0;

        // Caz general
        for i in 2..=self.n {
            dp[i] = 1;
            prev[i] = 0;
            // Încerc să pun pe v[i] la finalul tuturor soluțiilor disponibile
            // o soluție se termină cu un element v[j].
            for j in 1..i {
                if self.v[j] < self.v[i] && dp[j] + 1 > dp[i] {
                    dp[i] = dp[j] + 1;
                    prev[i] = j;
                }
            }
        }

        // Soluția este maximul din vectorul dp.
        let pos = (1..=self.n).max_by_key(|&i| dp[i]).unwrap();
        let sol = dp[pos];

        // Reconstruim SCMAX: v[pos] este ultimul element, înainte v[prev[pos]], etc.
        let mut sequence = Vec::new();
        let mut i = pos;
        while i != 0 {
            sequence.push(self.v[i]);
            i = prev[i];
        }
        sequence.reverse();
        (sol, sequence)
    }

    fn write_output(&self, result: (usize, Vec<i32>)) {
        let mut fout = File::create("out").expect("out");
        writeln!(fout, "{}", result.0).expect("write");
        for (i, &x) in result.1.iter().enumerate() {
            if i > 0 {
                write!(fout, " ").expect("write");
            }
            write!(fout, "{}", x).expect("write");
        }
        writeln!(fout).expect("write");
    }
}

// [ATENTIE] NU modifica funcția main!
fn main() {
    let mut task = Box::new(Task::default());
    task.solve();
}
