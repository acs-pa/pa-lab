// SPDX-License-Identifier: BSD-3-Clause

use std::collections::VecDeque;
use std::fs::File;
use std::io::{BufRead, BufReader, Write};

#[derive(Default)]
struct Task {
    // n = numar de noduri, m = numar de muchii/arce
    n: i32,
    m: i32,

    // adj[node] = lista de adiacenta a nodului node
    // exemplu: daca adj[node] = {..., neigh, ...} => exista arcul (node, neigh)
    adj: Vec<Vec<i32>>,

    // in_degree[node] = gradul intern al nodului node
    in_degree: Vec<i32>,
}

impl Task {
    // numarul maxim de noduri
    const NMAX: usize = 100_005; // 10^5 + 5

    pub fn solve(&mut self) {
        self.read_input();
        self.write_output(&self.get_result());
    }

    fn read_input(&mut self) {
        let fin = File::open("in").expect("in");
        let mut lines = BufReader::new(fin).lines().map(|l| l.unwrap());
        let first = lines.next().unwrap();
        let mut tokens = first.split_whitespace().map(|s| s.parse::<i32>().unwrap());
        self.n = tokens.next().unwrap();
        self.m = tokens.next().unwrap();

        self.adj = vec![vec![]; Self::NMAX];
        // grad intern 0 pentru toate nodurile... momentan
        self.in_degree = vec![0; (self.n + 1) as usize];

        for _ in 0..self.m {
            let line = lines.next().unwrap();
            let mut tok = line.split_whitespace().map(|s| s.parse::<i32>().unwrap());
            let x = tok.next().unwrap();
            let y = tok.next().unwrap();
            self.adj[x as usize].push(y); // arc (x, y)
            self.in_degree[y as usize] += 1; // numar inca o muchie care intra in y
        }
    }

    fn get_result(&self) -> Vec<i32> {
        return self.solve_bfs();
    }

    // Complexitate: O(n + m)
    fn solve_bfs(&self) -> Vec<i32> {
        // Step 0: initializare topsort - permutare vida initial
        let mut topsort: Vec<i32> = vec![];

        // Step 1: declaram o coada in care putem baga noduri
        let mut q = VecDeque::new();

        // Step 2: pasul initial: pun in coada TOATE nodurile cu grad intern 0
        for node in 1..=self.n {
            if self.in_degree[node as usize] == 0 {
                q.push_back(node);
            }
        }

        // in_degree il modificam, deci trebuie mutabil
        let mut in_degree = self.in_degree.clone();

        // Step 3: parcurg in latime graful
        while let Some(node) = q.pop_front() {
            // 3.1: SCOT primul nod din coada
            // adaug la solutie elementul scos
            topsort.push(node);

            // 3.2 Ii parcurg toti vecinii
            for &neigh in &self.adj[node as usize] {
                // sterg muchia node->neigh
                // obs1. NU e nevoie sa o sterg la propriu
                //       Daca nu am cicluri, nu se va ajunge aici
                // obs2. Simulez stergerea prin scaderea gradului intern a lui neigh
                in_degree[neigh as usize] -= 1;

                // daca neigh a ajuns nod cu grad intern 0, atunci este adaugat in coada
                if in_degree[neigh as usize] == 0 {
                    q.push_back(neigh);
                }
            }
        }

        // Step 4: verifica ca topsort chiar reprezinta o sortare topologica valida
        // Ce inseamna asta? S-au sters toate muchiile din graf.
        // Daca nu s-a sters tot, atunci graful este ciclic!
        let is_valid = in_degree[1usize..=self.n as usize].iter().all(|&d| d == 0);
        if is_valid {
            return topsort; // sortarea topologica obtinuta
        } else {
            return vec![]; // vector gol == nu se poate face o sortare topologica
        }
    }

    fn write_output(&self, topsort: &[i32]) {
        let mut fout = File::create("out").expect("out");
        for node in topsort {
            write!(fout, "{} ", node).unwrap();
        }
        writeln!(fout).unwrap();
    }
}

// [ATENTIE] NU modifica functia main!
fn main() {
    let mut task = Box::new(Task::default());
    task.solve();
}
