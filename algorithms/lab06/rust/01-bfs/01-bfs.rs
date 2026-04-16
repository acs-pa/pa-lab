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
    // exemplu: daca adj[node] = {..., neigh, ...} => exista muchia (node, neigh)
    adj: Vec<Vec<i32>>,

    // nodul sursa in parcurgerea BFS
    source: i32,
}

impl Task {
    // numarul maxim de noduri
    const NMAX: usize = 100_005; // 10^5 + 5

    // distanta maxima in graf
    const INF: i32 = 1_000_000_000; // 10^9

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
        self.source = tokens.next().unwrap();
        self.adj = vec![vec![]; Self::NMAX];
        for _ in 0..self.m {
            let line = lines.next().unwrap();
            let mut tok = line.split_whitespace().map(|s| s.parse::<i32>().unwrap());
            let x = tok.next().unwrap();
            let y = tok.next().unwrap();
            // muchie (x, y)
            self.adj[x as usize].push(y);
            self.adj[y as usize].push(x);
        }
    }

    fn get_result(&self) -> Vec<i32> {
        return self.bfs(self.source);
    }

    // Complexitate: O(n + m)
    fn bfs(&self, source: i32) -> Vec<i32> {
        // Step 0: alocare vector de distante
        // d[node] = INF, oricare ar fi node
        let mut d = vec![Self::INF; (self.n + 1) as usize];

        // Step 1: declaram o coada in care putem baga noduri
        let mut q = VecDeque::new();

        // Step 2: pasul initial: pun in coada TOATE nodurile cu grad intern 0
        q.push_back(source);
        d[source as usize] = 0;

        // Step 3: cat timp NU am parcurs toate nodurile
        while let Some(node) = q.pop_front() {
            // Step 3.1: extragem si procesam urmatorul nod din coada
            // Step 3.2: parcurgem vecinii lui node
            for &neigh in &self.adj[node as usize] {
                // actualizam distanta lui neigh fata de sursa daca
                // am gasit o solutie mai buna
                if d[node as usize] + 1 < d[neigh as usize] {
                    // adauga nodul in coada si actualizeaza distanta pana la el
                    d[neigh as usize] = d[node as usize] + 1;
                    q.push_back(neigh);
                }
            }
        }

        // Step 4: problema ne cere ca acolo unde nu exista drum sa punem -1
        // inlocuim valorile egale cu INF din d cu -1
        for value in &mut d {
            if *value == Self::INF {
                *value = -1;
            }
        }

        return d;
    }

    fn write_output(&self, d: &[i32]) {
        let mut fout = File::create("out").expect("out");
        for node in 1..=self.n {
            let idx = node as usize;
            if node == self.n {
                writeln!(fout, "{}", d[idx]).unwrap();
            } else {
                write!(fout, "{} ", d[idx]).unwrap();
            }
        }
    }
}

// [ATENTIE] NU modifica functia main!
fn main() {
    let mut task = Box::new(Task::default());
    task.solve();
}
