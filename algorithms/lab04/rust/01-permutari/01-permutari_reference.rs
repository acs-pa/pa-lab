// SPDX-License-Identifier: BSD-3-Clause

use std::fs::File;
use std::io::{BufRead, BufReader, BufWriter, Write};

struct Task {
    n: usize,
}

impl Task {
    pub fn solve(&mut self) {
        self.read_input();
        self.write_output(&self.get_result());
    }

    fn read_input(&mut self) {
        let fin = File::open("in").expect("in");
        let mut lines = BufReader::new(fin).lines().map(|l| l.unwrap());
        self.n = lines.next().unwrap().parse().unwrap();
    }

    fn get_result(&self) -> Vec<Vec<usize>> {
        let mut all = Vec::new();
        self.solve_bkt(&mut all);
        all
    }

    fn solve_bkt(&self, all: &mut Vec<Vec<usize>>) {
        // La începutul generării putem alege din fiecare număr între 1 și n.
        let mut domain: Vec<usize> = (1..=self.n).collect();

        let mut solution = Vec::new();

        // Construim permutările prin backtracking.
        self.bkt(&mut domain, &mut solution, all);
    }

    // Permutări de n elemente, implementare cu referințe.
    // T = O(n * n!)
    // S = O(n)
    fn bkt(&self, domain: &mut Vec<usize>, solution: &mut Vec<usize>, all: &mut Vec<Vec<usize>>) {
        // După ce am folosit toate elementele din domeniu, putem verifica dacă
        // am găsit o soluție.
        if domain.is_empty() {
            if self.check(solution) {
                all.push(solution.clone());
            }
            return;
        }

        // Încercăm să adăugăm în soluție toate valorile din domeniu, pe rând.
        for i in 0..domain.len() {
            let tmp = domain[i];

            // Adaug elementul curent la potențiala soluție.
            solution.push(tmp);
            // Șterg elementul curent ca să nu îl refolosesc.
            domain.remove(i);

            // Continuăm generarea cu noua stare.
            self.bkt(domain, solution, all);

            // Refac domeniul și soluția la modul în care erau înainte de
            // apelarea recursivă a backtracking-ului.
            domain.insert(i, tmp);
            solution.pop();
        }
    }

    // Deoarece numerele sunt șterse din domeniu odată ce sunt folosite, soluția
    // generată este garantată să nu conțină duplicate. Astfel, atunci când
    // domeniul ajunge vid, soluția este intotdeauna corectă.
    fn check(&self, _solution: &[usize]) -> bool {
        true
    }

    fn write_output(&self, result: &[Vec<usize>]) {
        let mut fout = BufWriter::new(File::create("out").expect("out"));
        writeln!(fout, "{}", result.len()).expect("write");
        for perm in result {
            for num in perm {
                write!(fout, "{} ", num).expect("write");
            }
            writeln!(fout).expect("write");
        }
    }
}

// [ATENTIE] NU modifica functia main!
fn main() {
    let mut task = Box::new(Task { n: 0 });
    task.solve();
}
