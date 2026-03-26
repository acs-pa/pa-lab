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
        let domain: Vec<usize> = (1..=self.n).collect();

        // Construim permutările prin backtracking.
        self.bkt(&domain, &Vec::new(), all);
    }

    // Permutări de n elemente, implementare pe caz general.
    // T = O(n * n!)
    // S = O(n^2)
    fn bkt(&self, domain: &[usize], solution: &[usize], all: &mut Vec<Vec<usize>>) {
        // După ce am folosit toate elementele din domeniu, putem verifica dacă
        // am găsit o soluție.
        if domain.is_empty() {
            if self.check(solution) {
                all.push(solution.to_vec());
            }
            return;
        }

        // Încercăm să adăugăm în soluție toate valorile din domeniu, pe rând.
        for i in 0..domain.len() {
            // Creăm o soluție nouă identică cu cea de la pasul curent, și o
            // modificăm.
            let mut new_solution = solution.to_vec();
            new_solution.push(domain[i]);

            // Ștergem elementul ales din domeniu. Creăm o copie a domeniului.
            let mut new_domain = domain.to_vec();
            new_domain.remove(i);

            // Continuăm generarea cu noua stare.
            self.bkt(&new_domain, &new_solution, all);
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
