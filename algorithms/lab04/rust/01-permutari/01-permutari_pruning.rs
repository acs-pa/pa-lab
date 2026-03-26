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

        let mut solution = Vec::new();
        let mut visited = std::collections::HashSet::new();

        // Construim permutările prin backtracking.
        self.bkt(0, self.n, &domain, &mut solution, &mut visited, all);
    }

    // Permutări de n elemente, implementare cu pruning.
    // T = O(n * n!)
    // S = O(n)
    fn bkt(
        &self,
        step: usize,
        stop: usize,
        domain: &[usize],
        solution: &mut Vec<usize>,
        visited: &mut std::collections::HashSet<usize>,
        all: &mut Vec<Vec<usize>>,
    ) {
        // După ce am folosit toate elementele din domeniu, putem verifica dacă
        // am găsit o soluție.
        if step == stop {
            if self.check(solution) {
                all.push(solution.clone());
            }
            return;
        }

        // Adaugam in solutie fiecare element din domeniu care *NU* a fost
        // vizitat deja renuntand astfel la nevoia de a verifica duplicatele la
        // final prin functia "check()"
        for num in domain {
            if !visited.contains(num) {
                // Il marcam ca vizitat si taiem eventuale expansiuni nefolositoare viitoare (ex: daca il adaug in
                // solutie pe 3 nu voi mai avea niciodata nevoie sa il mai adaug pe 3 in continuare)
                visited.insert(*num);
                // Adaugam elementul curent in solutie pe pozitia pasului curent (step)
                solution.push(*num);
                // Apelam recursiv backtracking pentru pasul urmator
                self.bkt(step + 1, stop, domain, solution, visited, all);
                // Stergem vizitarea elementului curent (ex: pentru N = 3, dupa
                // ce la pasul "step = 0" l-am pus pe 1 pe prima pozitie in
                // solutie si am continuat recursiv pana am ajuns la solutiile
                // {1, 2, 3} si {1, 3, 2}, ne dorim sa il punem pe 2 pe prima
                // pozitie in solutie si sa continuam recursiv pentru a ajunge
                // la solutiile {2, 1, 3} etc.)
                visited.remove(num);
                solution.pop();
            }
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
