// SPDX-License-Identifier: BSD-3-Clause

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
        for _ in 0..self.m {
            let line = lines.next().unwrap();
            let mut tok = line.split_whitespace().map(|s| s.parse::<i32>().unwrap());
            let x = tok.next().unwrap();
            let y = tok.next().unwrap();
            // arc (x, y)
            self.adj[x as usize].push(y);
        }
    }

    fn get_result(&self) -> Vec<i32> {
        return self.solve_dfs();
    }

    // Complexitate: O(n + m)
    fn solve_dfs(&self) -> Vec<i32> {
        // vectorul rezultat (in final contine o permutare pentru 1, 2, ..., n)
        let mut topsort: Vec<i32> = vec![];

        // visited[node] = 1 daca node a fost deja vizitat, 0 altfel
        let mut visited = vec![0; (self.n + 1) as usize];

        // pentru fiecare nod
        for node in 1..=self.n {
            // daca nodul este nevizitat, pornim o parcurgere
            if visited[node as usize] == 0 {
                self.dfs(node, &mut visited, &mut topsort);
            }
        }

        // rezultatul a fost obtinut in ordine inversa
        topsort.reverse();

        return topsort;
    }

    // porneste o parcurgere DFS din node
    // foloseste vectorul visited pentru a marca nodurile vizitate
    fn dfs(&self, node: i32, visited: &mut [i32], topsort: &mut Vec<i32>) {
        visited[node as usize] = 1; // marchez nodul ca fiind vizitat

        // parcurg vecinii
        for &neigh in &self.adj[node as usize] {
            if visited[neigh as usize] == 0 {
                self.dfs(neigh, visited, topsort);
            }
        }

        // dupa ce am vizitat recursiv toti vecinii, adaugam
        // nodul la sortare
        topsort.push(node);
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
