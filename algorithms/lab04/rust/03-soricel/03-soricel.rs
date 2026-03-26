// SPDX-License-Identifier: BSD-3-Clause

use std::fs::File;
use std::io::{BufRead, BufReader, Write};

struct Task {
    mat: Vec<Vec<i32>>,
}

impl Task {
    pub fn solve(&mut self) {
        self.read_input();
        self.write_output(&self.get_result());
    }

    fn read_input(&mut self) {
        let fin = File::open("in").expect("in");
        let mut lines = BufReader::new(fin).lines().map(|l| l.unwrap());

        let n: usize = lines.next().unwrap().parse().unwrap();

        self.mat = Vec::new();
        for _ in 0..n {
            let row: Vec<i32> = lines
                .next()
                .unwrap()
                .split_whitespace()
                .map(|s| s.parse().unwrap())
                .collect();
            self.mat.push(row);
        }
    }

    fn get_result(&self) -> Vec<Vec<(usize, usize)>> {
        let mut all = Vec::new();
        self.solve_bkt(&mut all);
        all
    }

    fn solve_bkt(&self, all: &mut Vec<Vec<(usize, usize)>>) {
        // Adăugăm forțat poziția de start în stivă / soluția parțială.
        let mut current = vec![(0, 0)];
        self.bkt(&mut current, all);
    }

    // Problema șoricelului = Generarea drumurilor printr-o matrice cu 2 mișcări.
    // T(n) = O(2^(2n))
    // S(n) = O(n)
    fn bkt(&self, current: &mut Vec<(usize, usize)>, all: &mut Vec<Vec<(usize, usize)>>) {
        // Dacă am ajuns la destinație, `current` e un drum complet, nu trebuie extins.
        if current[current.len() - 1] == (self.mat.len() - 1, self.mat.len() - 1) {
            all.push(current.clone());
            return;
        }

        // Folosim un vector de direcții pentru mișcările disponibile.
        for (mod_r, mod_c) in vec![(0, 1), (1, 0)] {
            let r = current[current.len() - 1].0 + mod_r;
            let c = current[current.len() - 1].1 + mod_c;

            // Putem continua drumul dacă nu ieșim din matrice și nu suntem blocați.
            if self.in_bounds(r, c) && self.mat[r][c] == 0 {
                current.push((r, c)); // Punem pe stivă noua poziție.
                self.bkt(current, all); // Generăm continuările recursiv.
                current.pop(); // După revenire, scoatem celula din stivă.
            }
        }
    }

    // Verifică dacă o poziție e în interiorul matricei.
    fn in_bounds(&self, r: usize, c: usize) -> bool {
        r < self.mat.len() && c < self.mat[r].len()
    }

    fn write_output(&self, result: &[Vec<(usize, usize)>]) {
        let mut fout = File::create("out").expect("out");
        writeln!(fout, "{}", result.len()).expect("write");
        for path in result {
            let mut first = true;
            for (r, c) in path {
                if !first {
                    write!(fout, "->").expect("write");
                }
                write!(fout, "({},{})", r, c).expect("write");
                first = false;
            }
            writeln!(fout).expect("write");
        }
    }
}

// [ATENTIE] NU modifica functia main!
fn main() {
    let mut task = Box::new(Task { mat: Vec::new() });
    task.solve();
}
