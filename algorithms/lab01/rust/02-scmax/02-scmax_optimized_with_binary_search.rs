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
        self.v = vec![0];
        let rest: Vec<i32> = lines
            .next()
            .unwrap()
            .split_whitespace()
            .map(|s| s.parse().unwrap())
            .collect();
        self.v.extend(rest);
    }

    fn get_result(&self) -> (usize, Vec<i32>) {
        self.scmax_binary_search()
    }

    // SCMAX = Subșir Crescător Maximal, varianta O(n log n) cu binary search
    // Menținem pentru fiecare lungime L cea mai mică valoare finală a unui subșir crescător de lungime L.
    // T = O(n log n)
    // S = O(n)
    fn scmax_binary_search(&self) -> (usize, Vec<i32>) {
        // dp[l] = valoarea minimă a ultimului element dintr-un subșir crescător de lungime l+1
        let mut dp: Vec<i32> = Vec::new();
        // dp_idx[l] = indicele în v al acelui element (pentru reconstrucție)
        let mut dp_idx: Vec<usize> = Vec::new();
        let mut prev = vec![0usize; self.n + 1];

        // Caz de bază: primul element
        dp.push(self.v[1]);
        dp_idx.push(1);
        prev[1] = 0;

        // Caz general: pentru fiecare v[i] căutăm binar unde să extindem sau să înlocuim.
        for i in 2..=self.n {
            let p = dp.binary_search(&self.v[i]).unwrap_or_else(|x| x);
            if p == dp.len() {
                // Extindem: subșir nou de lungime maximă
                dp.push(self.v[i]);
                dp_idx.push(i);
                prev[i] = dp_idx[p - 1];
            } else {
                // Înlocuim: obținem o „coadă” mai mică pentru lungimea p+1
                dp[p] = self.v[i];
                dp_idx[p] = i;
                prev[i] = if p > 0 { dp_idx[p - 1] } else { 0 };
            }
        }

        let sol = dp.len();

        // Reconstruim subșirul: începem de la ultimul element al LIS-ului de lungime maximă
        let mut sequence = Vec::new();
        let mut i = dp_idx[sol - 1];
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
    // Se alocă un obiect Task pe heap pe care se apelează metoda solve().
    let mut task = Box::new(Task::default());
    task.solve();
}
