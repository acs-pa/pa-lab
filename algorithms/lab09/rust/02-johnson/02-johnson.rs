// SPDX-License-Identifier: BSD-3-Clause

use std::collections::BinaryHeap;
use std::cmp::Reverse;
use std::fs::File;
use std::io::{BufWriter, Read, Write};

#[derive(Default)]
struct Task {
    // n = numar de noduri, m = numar de muchii
    n: usize,
    m: usize,

    // adj[node] = lista de adiacenta a nodului node
    // perechea (neigh, w) semnifica arc de la node la neigh de cost w
    adj: Vec<Vec<(usize, i64)>>,
}

impl Task {
    const INF: i64 = 1 << 50;

    pub fn solve(&mut self) {
        self.read_input();
        let (has_cycle, d) = self.compute();
        self.write_output(has_cycle, &d);
    }

    fn read_input(&mut self) {
        let mut input = String::new();
        File::open("in").expect("in").read_to_string(&mut input).unwrap();
        let mut it = input.split_ascii_whitespace();
        self.n = it.next().unwrap().parse().unwrap();
        self.m = it.next().unwrap().parse().unwrap();
        self.adj = vec![vec![]; self.n + 2];
        for _ in 0..self.m {
            let x: usize = it.next().unwrap().parse().unwrap();
            let y: usize = it.next().unwrap().parse().unwrap();
            let w: i64 = it.next().unwrap().parse().unwrap();
            self.adj[x].push((y, w));
        }
    }

    fn compute(&mut self) -> (bool, Vec<Vec<i64>>) {
        return self.johnson();
    }

    fn compute_h(&self) -> (bool, Vec<i64>) {
        // Se adauga un nod suplimentar "fictiv"
        let new_n = self.n + 1;
        let source = self.n + 1;

        let mut new_adj = self.adj.clone();
        while new_adj.len() <= new_n {
            new_adj.push(vec![]);
        }

        // Se leaga la toate celelalte noduri cu distanta "fictiva" 0
        for node in 1..=self.n {
            new_adj[source].push((node, 0));
        }

        // Construiesc un vector de muchii
        let mut edges: Vec<(usize, usize, i64)> = Vec::new();
        for node in 1..=new_n {
            for &(neigh, w) in &new_adj[node] {
                edges.push((node, neigh, w));
            }
        }

        // Se aplica algoritmul Bellman-Ford pornind din nodul fictiv
        return Self::bellman(source, new_n, &edges);
    }

    fn johnson(&mut self) -> (bool, Vec<Vec<i64>>) {
        let mut d = vec![vec![0i64; self.n + 1]; self.n + 1];

        let (has_cycle, h) = self.compute_h();
        if has_cycle {
            return (true, vec![]);
        }

        // Translatare folosind distantele calculate cu BellmanFord pentru a face
        // toate costurile din graf nenegative.
        for u in 1..=self.n {
            for edge in self.adj[u].iter_mut() {
                edge.1 = edge.1 + (h[u] - h[edge.0]);
            }
        }

        // Se aplica algoritmul lui Dijkstra pornind din fiecare nod al grafului.
        for u in 1..=self.n {
            let d_dijkstra = self.dijkstra(u);
            for v in 1..=self.n {
                // daca distanta returnata de Dijkstra este -1, nu exista drum intre
                // nodul u si nodul v si pun distanta 0, conform conventiei.
                if d_dijkstra[v] != -1 {
                    // daca exista drum intre u si v, trebuie sa fac si translatarea inversa.
                    d[u][v] = d_dijkstra[v] + (h[v] - h[u]);
                }
            }
        }

        return (false, d);
    }

    fn dijkstra(&self, source: usize) -> Vec<i64> {
        let mut d = vec![Self::INF; self.n + 1];
        d[source] = 0;
        let mut pq = BinaryHeap::new();
        pq.push(Reverse((0i64, source)));

        while let Some(Reverse((cost, node))) = pq.pop() {
            if cost > d[node] {
                continue;
            }
            for &(neigh, w) in &self.adj[node] {
                if d[node] + w < d[neigh] {
                    d[neigh] = d[node] + w;
                    pq.push(Reverse((d[neigh], neigh)));
                }
            }
        }

        for node in 1..=self.n {
            if d[node] == Self::INF {
                d[node] = -1;
            }
        }

        return d;
    }

    fn bellman(source: usize, nodes: usize, edges: &[(usize, usize, i64)]) -> (bool, Vec<i64>) {
        let mut d = vec![Self::INF; nodes + 1];
        d[source] = 0;

        // Fac N - 1 relaxari.
        for _ in 1..nodes {
            let mut updated = false;
            for &(node, neigh, w) in edges {
                if d[node] != Self::INF && d[node] + w < d[neigh] {
                    d[neigh] = d[node] + w;
                    updated = true;
                }
            }
            if !updated {
                break;
            }
        }

        // Verific daca mai poate fi updatata distanta.
        for &(node, neigh, w) in edges {
            if d[node] != Self::INF && d[node] + w < d[neigh] {
                return (true, vec![]);
            }
        }

        for node in 1..=nodes {
            if d[node] == Self::INF {
                d[node] = -1;
            }
        }

        return (false, d);
    }

    fn write_output(&self, has_cycle: bool, d: &[Vec<i64>]) {
        let fout = File::create("out").expect("out");
        let mut fout = BufWriter::new(fout);
        if has_cycle {
            writeln!(fout, "Ciclu negativ!").unwrap();
        } else {
            for u in 1..=self.n {
                for v in 1..=self.n {
                    write!(fout, "{} ", d[u][v]).unwrap();
                }
                writeln!(fout).unwrap();
            }
        }
    }
}

// [ATENTIE] NU modifica functia main!
fn main() {
    let mut task = Box::new(Task::default());
    task.solve();
}
