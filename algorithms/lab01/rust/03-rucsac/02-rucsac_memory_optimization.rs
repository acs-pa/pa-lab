// SPDX-License-Identifier: BSD-3-Clause

use std::fs::{self, File};
use std::io::Write;

#[derive(Default)]
struct Task {
    n: usize,       // numărul de obiecte
    w: Vec<i32>,    // greutatea fiecărui obiect
    p: Vec<i32>,    // valoarea fiecărui obiect
    w_cap: i32,     // capacitatea rucsacului
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
        self.w_cap = it.next().unwrap();
        self.w = vec![0];
        self.p = vec![0];
        for _ in 0..self.n {
            self.w.push(it.next().unwrap());
            self.p.push(it.next().unwrap());
        }
    }

    fn get_result(&self) -> i32 {
        self.rucsac()
    }

    // Rucsac = Problema rucsacului, varianta cu 2 linii: dp[i] și dp[i-1].
    // T = O(n * W)
    // S = O(W)
    fn rucsac(&self) -> i32 {
        // Observație: În realitate implementăm aceeași recurență ca în 01-rucsac.rs,
        // dar folosim doar 2 linii de dp.
        // dp[i][cap] = profitul maxim (profit RUCSAC) obținut folosind
        // (doar o parte) din primele i obiecte și având un rucsac de capacitate maximă cap.

        // prev[cap] = profitul maxim folosind primele i-1 obiecte, capacitate cap
        let w = self.w_cap as usize;
        let mut prev: Vec<i32> = vec![0; w + 1];
        // curr[cap] = profitul maxim folosind primele i obiecte, capacitate cap
        let mut curr: Vec<i32> = vec![0; w + 1];

        for i in 1..=self.n {
            for cap in 0..=w {
                curr[cap] = prev[cap];
                if cap as i32 >= self.w[i] {
                    let c = cap - self.w[i] as usize;
                    curr[cap] = curr[cap].max(prev[c] + self.p[i]);
                }
            }
            std::mem::swap(&mut prev, &mut curr);
        }

        // Atenție: în această abordare nu putem reconstitui soluția,
        // deoarece nu păstrăm informațiile despre obiectele care au fost folosite.
        prev[w]
    }

    fn write_output(&self, result: i32) {
        let mut fout = File::create("out").expect("out");
        // Nu se printează obiectele, ci doar valoarea maximă a profitului.
        writeln!(fout, "{}", result).expect("write");
    }
}

// [ATENTIE] NU modifica funcția main!
fn main() {
    let mut task = Box::new(Task::default());
    task.solve();
}
