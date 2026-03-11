// SPDX-License-Identifier: BSD-3-Clause

use std::fs;
use std::io::Write;
use std::default::Default;

const K_INF: u64 = u64::MAX;

#[derive(Default)]
struct Task {
    n: usize,
    d: Vec<u64>,
}

impl Task {
    fn solve(&mut self) {
        self.read_input();
        let result = self.get_result();
        self.write_output(result);
    }

    fn read_input(&mut self) {
        let input = fs::read_to_string("in").expect("couldn't read input file");
        let mut iter = input.split_whitespace();
        self.n = iter.next().unwrap().parse().unwrap();
        self.d = (0..=self.n)
            .map(|_| iter.next().unwrap().parse().unwrap())
            .collect();
    }

    fn get_result(&self) -> u64 {
        self.solve_podm()
    }

    // PODM = Produsul Optim de Matrici, implementarea clasica cu DP
    // T = O(n ^ 3)
    // S = O(n ^ 2) - stocam n x n intregi in tabloul dp
    fn solve_podm(&self) -> u64 {
        let n = self.n;
        // dp[i][j] = numarul MINIM de inmultiri scalare pentru produsul M_i * ... * M_j
        let mut dp = vec![vec![K_INF; n + 1]; n + 1];

        // Cazul de baza 1: nu am ce inmulti
        for i in 1..=n {
            dp[i][i] = 0;
        }

        // Cazul de baza 2: matrice consecutive
        for i in 1..n {
            dp[i][i + 1] = self.d[i - 1] * self.d[i] * self.d[i + 1];
        }

        // Cazul general
        for len in 2..=n {
            for i in 1..=(n - len + 1) {
                let j = i + len - 1;
                for k in i..j {
                    let new_sol = dp[i][k] + dp[k + 1][j] + self.d[i - 1] * self.d[k] * self.d[j];
                    if new_sol < dp[i][j] {
                        dp[i][j] = new_sol;
                    }
                }
            }
        }

        dp[1][n]
    }

    fn write_output(&self, result: u64) {
        let mut out = fs::File::create("out").expect("couldn't create output file");
        writeln!(out, "{}", result).unwrap();
    }
}

// [ATENTIE] NU modifica functia main!
fn main() {
    let mut task = Box::new(Task::default());
    task.solve();
}
