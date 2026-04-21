// SPDX-License-Identifier: BSD-3-Clause

use std::cmp::min;
use std::fs;

#[derive(Default)]
struct Task {
	// n = numar de noduri, m = numar de muchii/arce
	n: usize,

	// adj[node] = lista de adiacenta a nodului node
	// exemplu: daca adj[node] = {..., neigh, ...} => exista muchia (node, neigh)
	adj: Vec<Vec<usize>>,

	// parent[node] = parintele nodului node in parcurgerea DFS
	parent: Vec<usize>,

	// found[node] = momentul cand nodul a fost descoperit (cand a inceput vizitarea subarborelui sau)
	// Observatie: timestamp-ul global creste de fiecare data cand este descoperit un nod.
	found: Vec<i32>,

	// cel mai mic timestamp accesibil pe care il poate vedea/accesa nodul
	// low_link[node] = min { found[x] | x este node SAU x este in stramosii(node) SAU x este in descendentii(node) };
	low_link: Vec<i32>,

	// is_cv[node] = true daca node este punct de articulatie (nod critic)
	is_cv: Vec<bool>,
}

impl Task {
	fn solve(&mut self) {
		self.read_input();
		let all_cvs = self.tarjan_cv();
		self.write_output(&all_cvs);
	}

	fn read_input(&mut self) {
		let data = fs::read_to_string("in").expect("failed to read input");
		let mut it = data.split_whitespace();

		self.n = it.next().unwrap().parse::<usize>().unwrap();
		let m = it.next().unwrap().parse::<usize>().unwrap();
		self.adj = vec![Vec::new(); self.n + 1];

		for _ in 0..m {
			let x = it.next().unwrap().parse::<usize>().unwrap();
			let y = it.next().unwrap().parse::<usize>().unwrap();
			self.adj[x].push(y);
			self.adj[y].push(x);
		}
	}

	fn tarjan_cv(&mut self) -> Vec<usize> {
		// PASUL 1: initializez rezultatele
		self.parent = vec![0; self.n + 1];
		self.found = vec![-1; self.n + 1];
		self.low_link = vec![-1; self.n + 1];
		self.is_cv = vec![false; self.n + 1];

		// PASUL 2: vizitez toate nodurile
		let mut timestamp = 0;
		for node in 1..=self.n {
			if self.parent[node] == 0 {
				// nod nevizitat
				// conventie: parintele radacinii este chiar radacina
				self.parent[node] = node;

				// PASUL 3: pornesc o noua parcurgere DFS pe acest subarbore
				self.dfs(node, &mut timestamp);
			}
		}

		let mut result = Vec::new();
		for node in 1..=self.n {
			if self.is_cv[node] {
				result.push(node);
			}
		}
		result
	}

	fn dfs(&mut self, node: usize, timestamp: &mut i32) {
		// PASUL 1: un nod nou este vizitat - incrementez timestamp-ul
		*timestamp += 1;
		self.found[node] = *timestamp; // timestamp-ul la care nodul a fost descoperit
		self.low_link[node] = self.found[node]; // nodul cunoaste doar propriul timestamp

		// PASUL 2: vizitez fiecare vecin
		let mut children = 0;
		let neighbors = self.adj[node].clone();
		for neigh in neighbors {
			// PASUL 3: verific daca neigh este deja vizitat
			if self.parent[neigh] != 0 {
				// PASUL 3.1: actualizez low_link[node] cu informatiile obtinute prin neigh
				// observatie: pentru ca graful este neorientat, trebuie ignorata muchia catre parinte
				// (valoarea found a parintelui este mereu mai mica decat valoarea found a lui node)
				if neigh != self.parent[node] {
					self.low_link[node] = min(self.low_link[node], self.found[neigh]);
				}
				continue;
			}

			// PASUL 4: salvez parintele
			self.parent[neigh] = node;
			children += 1; // numar copilul

			// PASUL 5: vizitez recursiv subarborele copilului
			self.dfs(neigh, timestamp);

			// PASUL 6: actualizez low_link[node] cu informatiile obtinute prin neigh
			self.low_link[node] = min(self.low_link[node], self.low_link[neigh]);

			// PASUL 7.1: node este un CV daca i): *) node NU este radacina si **) low_link[neigh] >= found[node]
			if self.parent[node] != node && self.low_link[neigh] >= self.found[node] {
				self.is_cv[node] = true;
			}
		}

		// PASUL 7.2: node este un CV daca i)): *) node este radacina si **) are cel putin 2 copii
		if self.parent[node] == node && children > 1 {
			self.is_cv[node] = true;
		}
	}

	fn write_output(&self, all_cvs: &[usize]) {
		let mut out = String::new();
		for &cv in all_cvs {
			out.push_str(&format!("{} ", cv));
		}
		out.push('\n');
		fs::write("out", out).expect("failed to write output");
	}
}

fn main() {
	let mut task = Box::new(Task::default());
	task.solve();
}
