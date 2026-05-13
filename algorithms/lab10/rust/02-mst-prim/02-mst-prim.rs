// SPDX-License-Identifier: BSD-3-Clause

use std::cmp::Reverse;
use std::collections::BinaryHeap;
use std::fs::File;
use std::io::{BufWriter, Write};

#[derive(Default)]
struct Task {
    // n = numar de noduri, m = numar de muchii
    n: usize,
    m: usize,

    // muchiile din graf: (node, neigh, w) - muchie de la node la neigh de cost w
    edges: Vec<(usize, usize, i32)>,
}

impl Task {
    const INF: i32 = 1 << 30;

    pub fn solve(&mut self) {
        self.read_input();
        let result = self.get_result();
        self.write_output(&result);
    }

    fn read_input(&mut self) {
        let mut input = String::new();
        std::io::Read::read_to_string(&mut File::open("in").unwrap(), &mut input).unwrap();
        let mut tokens = input.split_whitespace();
        if let Some(n_str) = tokens.next() {
            self.n = n_str.parse().unwrap();
            self.m = tokens.next().unwrap().parse().unwrap();
            for _ in 0..self.m {
                let x = tokens.next().unwrap().parse().unwrap();
                let y = tokens.next().unwrap().parse().unwrap();
                let w = tokens.next().unwrap().parse().unwrap();
                self.edges.push((x, y, w));
            }
        }
    }

    fn get_result(&mut self) -> (i32, Vec<(usize, usize)>) {
        self.prim(1)
    }

    // MST generat cu Prim, pornind de la un nod radacina ales anterior.
    // Complexitate: O(m log n).
    fn prim(&self, source: usize) -> (i32, Vec<(usize, usize)>) {
        // adj[node] = lista de adiacenta a lui node: (neigh, w)
        let mut adj = vec![vec![]; self.n + 1];
        for &(x, y, w) in &self.edges {
            adj[x].push((y, w));
            adj[y].push((x, w));
        }

        // d[node] = distanta nodului node fata de MST-ul curent (cel ma apropiat nod din MST)
        // d[node] in aceasta problema va fi mereu egal cu costul unei muchii
        // Initializam vectorul de distante cu distante infinite.
        let mut d = vec![Self::INF; self.n + 1];
        // p[node] = parintele lui node (initializat cu 0)
        let mut p = vec![0; self.n + 1];
        let mut used = vec![false; self.n + 1];

        // In loc de un priority_queue<> folosim BinaryHeap, cu elemente tupluri de
        // tipul (distanta pana la nod, nod). Heap-ul tine elementele ordonate.
        // Folosim Reverse pentru ca vrem un min-heap dupa distanta minima.
        let mut pq = BinaryHeap::new();

        // Inseram nodul de plecare in coada si ii actualizam distanta.
        d[source] = 0;
        pq.push(Reverse((0, source)));

        // Initializam MST: cost 0, fara muchii
        let mut cost = 0;
        let mut mst = Vec::new();

        // Adaugam fix n noduri la arbore
        while let Some(Reverse((_, node))) = pq.pop() {
            // In cazul in care nodul e deja in MST, ignoram aceasta intrare.
            if used[node] {
                continue;
            }

            // Adaug muchia node - p[node].
            used[node] = true;

            // Nodul radacina este adaugat print-o muchie fictiva,
            // care nu face parte din MST.
            if p[node] != 0 {
                cost += d[node];
                mst.push((node, p[node]));
            }

            // Ii parcurgem toti vecinii.
            for &(neigh, w) in &adj[node] {
                // Se imbunatateste distanta?
                if (!used[neigh]) && (w < d[neigh]) {
                    // Actualizam distanta si inseram din nou in set.
                    d[neigh] = w;
                    p[neigh] = node;
                    pq.push(Reverse((d[neigh], neigh)));
                }
            }
        }

        (cost, mst)
    }

    fn write_output(&self, result: &(i32, Vec<(usize, usize)>)) {
        let fout = File::create("out").expect("out");
        let mut writer = BufWriter::new(fout);
        writeln!(writer, "{}", result.0).unwrap();
        for &(x, y) in &result.1 {
            writeln!(writer, "{} {}", x, y).unwrap();
        }
    }
}

fn main() {
    let mut task = Box::new(Task::default());
    task.solve();
}
