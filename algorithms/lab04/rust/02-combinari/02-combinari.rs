// SPDX-License-Identifier: BSD-3-Clause

use std::fs::File;
use std::io::{BufRead, BufReader, Write};

struct Task {
    n: usize,
    k: usize,
}

impl Task {
    pub fn solve(&mut self) {
        self.read_input();
        self.write_output(&self.get_result());
    }

    fn read_input(&mut self) {
        let fin = File::open("in").expect("in");
        let mut lines = BufReader::new(fin).lines().map(|l| l.unwrap());
        let nums: Vec<usize> = lines
            .next()
            .unwrap()
            .split_whitespace()
            .map(|l| l.parse().unwrap())
            .collect();
        self.n = nums[0];
        self.k = nums[1];
    }

    fn get_result(&self) -> Vec<Vec<usize>> {
        let mut all = Vec::new();
        self.solve_bkt(&mut all);
        all
    }

    fn solve_bkt(&self, all: &mut Vec<Vec<usize>>) {
        // Vectorul in care stochez solutia (partiala) curenta
        let mut current = Vec::new();

        // construiesc combinarile prin backtracking
        self.bkt(&mut current, all);
    }

    // Combinari de n luate cate k, implementare cu transmitere prin referinta
    // T = O(n! / (k!*(n-k)!))
    // S = O(n)
    fn bkt(&self, current: &mut Vec<usize>, all: &mut Vec<Vec<usize>>) {
        // Daca avem o multime de dimensiune k
        if current.len() == self.k {
            // este implicit si o combinatie prin modul cum a fost generata

            // Adaug la solutie
            all.push(current.clone());

            // Ma opresc
            return;
        }

        // Daca este primul pas, alegem fiecare element din domeniu ca potential
        // candidat pentru prima pozitie in solutie; altfel, pentru a elimina ramurile
        // in care de exemplu {2, 1} se va genera dupa ce s-a generat {1, 2} (adica
        // ar fi duplicat), vom folosi doar elementele din domeniu care sunt mai mari
        // decat ultimul element adaugat in solutie (solution[step - 1])
        let start = if current.is_empty() {
            1
        } else {
            current[current.len() - 1] + 1
        };
        for i in start..=self.n {
            // Step 1: ADAUG elementul la solutie
            current.push(i);

            // Step 2: COMPLETEZ recursiv si solutia
            self.bkt(current, all);

            // Step 3: Scot elementul din solutie, ca sa pot pune altul in locul lui
            current.pop();
        }
    }

    fn write_output(&self, result: &[Vec<usize>]) {
        let mut fout = File::create("out").expect("out");
        writeln!(fout, "{}", result.len()).expect("write");
        for perm in result {
            for num in perm.iter() {
                write!(fout, "{} ", num).expect("write");
            }
            write!(fout, "\n").expect("write");
        }
    }
}

// [ATENTIE] NU modifica functia main!
fn main() {
    let mut task = Box::new(Task { n: 0, k: 0 });
    task.solve();
}
