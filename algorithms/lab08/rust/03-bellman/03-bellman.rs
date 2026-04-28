// SPDX-License-Identifier: BSD-3-Clause

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

struct Edge {
    node: i32,
    neigh: i32,
    w: i32,
}

impl Task {
    // numarul maxim de noduri
    const NMAX: usize = 50_005;

    // valoare mai mare decat orice distanta din graf
    const INF: i32 = 1 << 30;

    pub fn solve(&mut self) {
        self.read_input();
        let (has_cycle, d) = self.get_result();
        self.write_output(has_cycle, &d);
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

    fn get_result(&self) -> (bool, Vec<i32>) {
        // Construiesc un vector de muchii.
        let mut edges: Vec<Edge> = vec![];

        for node in 1..=self.n {
            for &(neigh, w) in &self.adj[node as usize] {
                edges.push(Edge { node, neigh, w });
            }
        }

        return self.bellman(self.source, &edges);
    }

    fn bellman(&self, source: i32, edges: &[Edge]) -> (bool, Vec<i32>) {
        // Initializam vectorul de distante cu distante infinite.
        let mut d = vec![Self::INF; (self.n + 1) as usize];

        // Setez sursa la distanta 0.
        d[source as usize] = 0;

        // Fac N - 1 relaxari.
        for _ in 1..self.n {
            // Parcurg toate muchiile:
            for edge in edges {
                // Se imbunatateste distanta?
                if d[edge.node as usize] + edge.w < d[edge.neigh as usize] {
                    // Actualizam distanta.
                    d[edge.neigh as usize] = d[edge.node as usize] + edge.w;
                }
            }
        }

        // Verific daca mai poate fi updatata distanta.
        for edge in edges {
            // Se imbunatateste distanta?
            if d[edge.node as usize] + edge.w < d[edge.neigh as usize] {
                // Am gasit un ciclu de cost negativ.
                return (true, vec![]);
            }
        }

        // Toate nodurile catre care distanta este inca INF nu pot fi atinse din
        // nodul source, deci le setam pe -1.
        for node in 1..=self.n {
            if d[node as usize] == Self::INF {
                d[node as usize] = -1;
            }
        }

        return (false, d);
    }

    fn write_output(&self, has_cycle: bool, d: &[i32]) {
        let mut fout = File::create("out").expect("out");
        if has_cycle {
            writeln!(fout, "Ciclu negativ!").unwrap();
        } else {
            for node in 1..=self.n {
                write!(fout, "{} ", d[node as usize]).unwrap();
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
