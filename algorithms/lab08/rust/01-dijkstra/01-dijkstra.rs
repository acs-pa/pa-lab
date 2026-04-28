// SPDX-License-Identifier: BSD-3-Clause

use std::collections::BinaryHeap;
use std::cmp::Reverse;
use std::fs::File;
use std::io::{BufRead, BufReader, Write};

#[derive(Default)]
struct Task {
    // n = numar de noduri, m = numar de muchii
    n: i32,
    m: i32,

    // adj[node] = lista de adiacenta a nodului node
    // perechea (neigh, w) semnifica arc de la node la neigh de cost w
    adj: Vec<Vec<(i32, i32)>>,

    // nodul sursa
    source: i32,
}

impl Task {
    // numarul maxim de noduri
    const NMAX: usize = 50_005;

    // valoare mai mare decat orice distanta din graf
    const INF: i32 = 1 << 30;

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
        self.m = tokens.next().unwrap();
        self.source = tokens.next().unwrap();
        self.adj = vec![vec![]; Self::NMAX];
        for _ in 0..self.m {
            let line = lines.next().unwrap();
            let mut tok = line.split_whitespace().map(|s| s.parse::<i32>().unwrap());
            let x = tok.next().unwrap();
            let y = tok.next().unwrap();
            let w = tok.next().unwrap();
            self.adj[x as usize].push((y, w));
        }
    }

    fn get_result(&self) -> Vec<i32> {
        return self.dijkstra(self.source);
    }

    fn dijkstra(&self, source: i32) -> Vec<i32> {
        // Initializam vectorul de distante cu distante infinite.
        let mut d = vec![Self::INF; (self.n + 1) as usize];

        // Folosim un BinaryHeap cu Reverse pentru a obtine un min-heap.
        let mut pq = BinaryHeap::new();

        // Inseram nodul de plecare in coada si ii actualizam distanta.
        d[source as usize] = 0;
        pq.push(Reverse((0, source)));

        while let Some(Reverse((cost, node))) = pq.pop() {
            // Daca distanta din coada nu e optima, dam discard.
            if cost > d[node as usize] {
                continue;
            }

            // Ii parcurgem toti vecinii.
            for &(neigh, w) in &self.adj[node as usize] {
                // Se imbunatateste distanta?
                if d[node as usize] + w < d[neigh as usize] {
                    // Actualizam distanta.
                    d[neigh as usize] = d[node as usize] + w;

                    // Inseram noua distanta.
                    pq.push(Reverse((d[neigh as usize], neigh)));
                }
            }
        }

        // Toate nodurile catre care distanta este inca INF nu pot fi atinse din
        // nodul source, deci le setam pe -1.
        for node in 1..=self.n {
            if d[node as usize] == Self::INF {
                d[node as usize] = -1;
            }
        }

        return d;
    }

    fn write_output(&self, d: &[i32]) {
        let mut fout = File::create("out").expect("out");
        for node in 1..=self.n {
            write!(fout, "{} ", d[node as usize]).unwrap();
        }
        writeln!(fout).unwrap();
    }
}

// [ATENTIE] NU modifica functia main!
fn main() {
    let mut task = Box::new(Task::default());
    task.solve();
}
