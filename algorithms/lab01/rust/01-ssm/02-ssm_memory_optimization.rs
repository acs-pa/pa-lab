// SPDX-License-Identifier: BSD-3-Clause

use std::fs::{self, File};
use std::io::Write;

#[derive(Default)]
struct Task {
    n: usize,       // numărul de elemente din vector
    v: Vec<i32>,    // vectorul de elemente pe care se aplică SSM
}

impl Task {
    pub fn solve(&mut self) {
        self.read_input();
        let result = self.get_result();
        self.write_output(result);
    }

    fn read_input(&mut self) {
        let s = fs::read_to_string("in").expect("in");
        let mut it = s.split_whitespace().map(|s| s.parse::<i32>().unwrap());
        self.n = it.next().unwrap() as usize;
        self.v = it.take(self.n).collect();
    }

    fn get_result(&self) -> (i32, usize, usize) {
        self.ssm()
    }

    // SSM = Subsecvența Sumă Maximă, varianta cu O(1) memorie suplimentară
    // Un singur pas: menținem doar suma curentă și cea mai bună secvență.
    // T = O(n)
    // S = O(1) (putem folosi doar variabile locale, nu folosim vectori dp/start)
    fn ssm(&self) -> (i32, usize, usize) {
        // Observație: În realitate implementăm aceeași recurență ca în 01-ssm.rs.
        // dp[i] = suma subsecvenței de sumă maximă (suma SSM) folosind
        // **doar primele i elemente din vectorul v** și care **se termină pe poziția i**

        // Caz de bază
        let mut best_sum = self.v[0];
        let mut best_start = 0;
        let mut best_end = 0;
        let mut curr_sum = self.v[0];
        let mut curr_start = 0;

        // Caz general
        for i in 1..self.n {
            if curr_sum >= 0 {
                // Extinde la dreapta cu v[i].
                curr_sum += self.v[i];
            } else {
                // Începe o nouă secvență.
                curr_sum = self.v[i];
                curr_start = i;
            }
            let curr_end = i;
            if curr_sum > best_sum {
                best_sum = curr_sum;
                best_start = curr_start;
                best_end = curr_end;
            } else if curr_sum == best_sum {
                // Conform enunțului: indice de început cel mai mic, la egalitate cea mai scurtă.
                if curr_start < best_start
                    || (curr_start == best_start && curr_end < best_end)
                {
                    best_start = curr_start;
                    best_end = curr_end;
                }
            }
        }

        // Soluția este cea reținută în best_*.
        (best_sum, best_start, best_end)
    }

    fn write_output(&self, result: (i32, usize, usize)) {
        let mut fout = File::create("out").expect("out");
        // Afișăm rezultatul cu indexarea de la 1.
        writeln!(fout, "{} {} {}", result.0, result.1 + 1, result.2 + 1).expect("write");
    }
}

// [ATENTIE] NU modifica funcția main!
fn main() {
    let mut task = Box::new(Task::default());
    task.solve();
}
