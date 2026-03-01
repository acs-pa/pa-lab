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

    // SSM = Subsecvența Sumă Maximă, implementarea clasică cu DP
    // T = O(n)
    // S = O(n)
    fn ssm(&self) -> (i32, usize, usize) {
        // dp[i] = suma subsecvenței de sumă maximă (suma SSM) folosind
        // **doar primele i elemente din vectorul v** și care **se termină pe poziția i**
        let mut dp: Vec<i32> = vec![0; self.n];
        // start[i] = poziția de început a subsecvenței de sumă maximă care se termină pe poziția i
        let mut start: Vec<usize> = vec![0; self.n];

        // Caz de bază
        dp[0] = self.v[0];
        start[0] = 0;

        // Caz general
        for i in 1..self.n {
            if dp[i - 1] >= 0 {
                // Extinde la dreapta cu v[i].
                dp[i] = dp[i - 1] + self.v[i];
                start[i] = start[i - 1];
            } else {
                // Începe o nouă secvență.
                dp[i] = self.v[i];
                start[i] = i;
            }
        }

        // Soluția este maximul din vectorul dp.
        let pos = (0..dp.len()).max_by_key(|&i| dp[i]).unwrap();
        (dp[pos], start[pos], pos)
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
