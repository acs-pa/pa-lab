// SPDX-License-Identifier: BSD-3-Clause

use std::fs;
use std::io::Write;
use std::default::Default;

const MOD: u32 = 1009;
const KMAX: usize = 4;

#[derive(Default)]
struct Task {
    n: u32,
}

impl Task {
    fn solve(&mut self) {
        self.read_input();
        self.write_output(self.get_result());
    }

    fn read_input(&mut self) {
        let input = fs::read_to_string("in").expect("couldn't read input file");
        self.n = input.split_whitespace().next().unwrap().parse().unwrap();
    }

    fn get_result(&self) -> u32 {
        Self::garduri_rapide(self.n)
    }

    // C = A * B (mod MOD)
    fn multiply_matrix(
        a: &[[u32; KMAX]; KMAX],
        b: &[[u32; KMAX]; KMAX],
    ) -> [[u32; KMAX]; KMAX] {
        let mut c = [[0u32; KMAX]; KMAX];
        for i in 0..KMAX {
            for j in 0..KMAX {
                let sum = (0..KMAX).fold(0u64, |acc, k| acc + a[i][k] as u64 * b[k][j] as u64);
                c[i][j] = (sum % (MOD as u64)) as u32;
            }
        }
        c
    }

    // R = C^p (mod MOD)
    fn power_matrix(mut c: [[u32; KMAX]; KMAX], mut p: u32) -> [[u32; KMAX]; KMAX] {
        // tmp = I (matricea identitate)
        let mut tmp = [[0u32; KMAX]; KMAX];
        for i in 0..KMAX {
            tmp[i][i] = 1;
        }

        while p != 1 {
            if p % 2 == 0 {
                c = Self::multiply_matrix(&c, &c);
                p /= 2;
            } else {
                tmp = Self::multiply_matrix(&tmp, &c);
                p -= 1;
            }
        }

        Self::multiply_matrix(&c, &tmp)
    }

    /**
     * Solutia optimizata
     * T(n) = O(log n)
     * S(n) = O(1)
     */
    fn garduri_rapide(n: u32) -> u32 {
        // cazurile de baza
        if n <= 3 {
            return 1;
        }
        if n == 4 {
            return 2;
        }

        // construiesc matricea C
        let c: [[u32; KMAX]; KMAX] = [
            [0, 0, 0, 1],
            [1, 0, 0, 0],
            [0, 1, 0, 0],
            [0, 0, 1, 1],
        ];

        // C = C^(n-4)
        let c = Self::power_matrix(c, n - 4);

        // sol = S_4 * C = dp[n] (ultima coloana din C)
        let sol = 1 * c[0][3] + 1 * c[1][3] + 1 * c[2][3] + 2 * c[3][3];
        sol % MOD
    }

    fn write_output(&self, result: u32) {
        let mut out = fs::File::create("out").expect("Crearea fisierului de output a esuat");
        writeln!(out, "{}", result).unwrap();
    }
}

// [ATENTIE] NU modifica functia main!
fn main() {
    let mut task = Box::new(Task::default());
    task.solve();
}
