// SPDX-License-Identifier: BSD-3-Clause

use std::fs::File;
use std::io::{BufWriter, Write};

// Structura de date descrisa aici https://infoarena.ro/problema/disjoint.
struct DisjointSet {
    // parent[node] = radacina arborelui din care face parte node.
    // (adica identificatorul componentei conexe curente)
    parent: Vec<usize>,

    // size[node] = numarul de noduri din arborele in care se afla node acum.
    size: Vec<usize>,
}

impl DisjointSet {
    // Se initializeaza n paduri.
    fn new(nodes: usize) -> Self {
        let mut parent = vec![0; nodes + 1];
        let mut size = vec![1; nodes + 1];
        // Fiecare padure contine un nod initial.
        for i in 1..=nodes {
            parent[i] = i;
        }
        Self { parent, size }
    }

    // Returneaza radacina arborelui din care face parte node.
    fn set_of(&mut self, node: usize) -> usize {
        // Daca node este radacina, atunci am gasit raspunsul.
        if node == self.parent[node] {
            return node;
        }

        // Altfel, urcam in sus din "radacina in radacina",
        // actualizand pe parcurs radacinile pentru nodurile atinse.
        self.parent[node] = self.set_of(self.parent[node]);
        self.parent[node]
    }

    // Reuneste arborii lui x si y intr-un singur arbore,
    // folosind euristica de reuniune a drumurilor dupa rank.
    fn union(&mut self, x: usize, y: usize) {
        // Obtinem radacinile celor 2 arbori
        let rx = self.set_of(x);
        let ry = self.set_of(y);

        if rx != ry {
            // Arborele mai mic este atasat la radacina arborelui mai mare.
            if self.size[rx] <= self.size[ry] {
                self.size[ry] += self.size[rx];
                self.parent[rx] = ry;
            } else {
                self.size[rx] += self.size[ry];
                self.parent[ry] = rx;
            }
        }
    }
}

#[derive(Default)]
struct Task {
    // n = numar de noduri, m = numar de muchii
    n: usize,
    m: usize,

    // muchiile din graf: (node, neigh, w) - muchie de la node la neigh de cost w
    edges: Vec<(usize, usize, i32)>,
}

impl Task {
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
        self.kruskal()
    }

    // MST generat cu Kruskal.
    // Complexitate: O(m log m).
    fn kruskal(&mut self) -> (i32, Vec<(usize, usize)>) {
        // Sortam muchiile crescator dupa cost.
        self.edges.sort_by_key(|e| e.2);

        // Initializam padurile.
        let mut ds = DisjointSet::new(self.n);

        // Initializam MST: cost 0, fara muchii
        let mut cost = 0;
        let mut mst = Vec::new();

        // Folosim muchiile in ordine crescatoare a costului.
        let mut used_edges = 0;

        for &(x, y, w) in &self.edges {
            // Aflam radacinile celor 2 arbori in care sunt x si y.
            if ds.set_of(x) != ds.set_of(y) {
                // Reunim arborii.
                ds.union(x, y);

                // Adaugam muchia la MST.
                cost += w;
                mst.push((x, y));

                used_edges += 1;
                if used_edges == self.n - 1 {
                    // Daca am format deja un arbore, ne putem oprim.
                    break;
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
