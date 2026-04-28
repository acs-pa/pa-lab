// SPDX-License-Identifier: BSD-3-Clause

use std::fs::File;
use std::io::{BufRead, BufReader, Write};

#[derive(Default)]
struct Task {
    // n = numar de noduri
    n: i32,

    // parent[node] = parintele nodului node
    // Cazuri particulare:
    //      * parent[source] = -1
    //      * parent[node] = -1, daca node nu este accesibil din nodul sursa.
    parent: Vec<i32>,

    // nodul sursa si nodul destinatie
    // (capetele drumului care trebuie reconstruit)
    source: i32,
    destination: i32,
}

impl Task {
    pub fn solve(&mut self) {
        self.read_input();
        let result = self.get_result();
        self.write_output(&result);
    }

    fn read_input(&mut self) {
        let fin = File::open("in").expect("in");
        let mut lines = BufReader::new(fin).lines().map(|l| l.unwrap());
        let first = lines.next().unwrap();
        let mut tokens = first.split_whitespace().map(|s| s.parse::<i32>().unwrap());
        self.n = tokens.next().unwrap();
        let second = lines.next().unwrap();
        let mut tokens2 = second.split_whitespace().map(|s| s.parse::<i32>().unwrap());
        self.source = tokens2.next().unwrap();
        self.destination = tokens2.next().unwrap();
        self.parent = vec![0; (self.n + 1) as usize];
        let third = lines.next().unwrap();
        let mut ptokens = third.split_whitespace().map(|s| s.parse::<i32>().unwrap());
        for node in 1..=self.n {
            self.parent[node as usize] = ptokens.next().unwrap();
        }
    }

    fn get_result(&self) -> Vec<i32> {
        let mut path: Vec<i32> = vec![];

        // Pornesc de la nodul destinatie si ii caut parintele.
        let mut node = self.destination;

        // Daca parintele lui node este -1, inseamna ca node este chiar source
        // sau node nu este accesibil din nodul source.
        while self.parent[node as usize] != -1 {
            // Daca el exista, atunci poate face dintr-un path valid.
            path.push(node);

            // Se cauta parintele nodului curent.
            node = self.parent[node as usize];
        }

        // Daca node nu este sursa, inseamna ca nu am putut ajunge inapoi
        // la nodul sursa, deci trebuie returnat un vector gol.
        if node != self.source {
            return vec![];
        }

        // Node este sursa, deci se adauga la path.
        path.push(self.source);

        // Se inverseaza ordinea nodurilor, pentru a obtine un drum
        // source - node_1 - node_2 - ... - node_k -  destination,
        // unde un node este parintele vecinului de la dreapta.
        path.reverse();

        return path;
    }

    fn write_output(&self, result: &[i32]) {
        let mut fout = File::create("out").expect("out");
        if result.is_empty() {
            writeln!(fout, "Nu se poate ajunge").unwrap();
        } else {
            for node in result {
                write!(fout, "{} ", node).unwrap();
            }
            writeln!(fout).unwrap();
        }
    }
}

// [ATENTIE] NU modifica functia main!
fn main() {
    let mut task = Box::new(Task::default());
    task.solve();
}
