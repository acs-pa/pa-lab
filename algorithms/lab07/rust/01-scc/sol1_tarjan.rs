// SPDX-License-Identifier: BSD-3-Clause

use std::cmp::min;
use std::fs;

#[derive(Default)]
struct Task {
	// n = numar de noduri, m = numar de muchii/arce
	n: usize,

	// adj[node] = lista de adiacenta a nodului node
	// exemplu: daca adj[node] = {..., neigh, ...} => exista arcul (node, neigh)
	adj: Vec<Vec<usize>>,

	// parent[node] = parintele nodului node in parcurgerea DFS
	parent: Vec<usize>,

	// found[node] = momentul cand nodul a fost descoperit (cand a inceput vizitarea subarborelui sau)
	// Observatie: timestamp-ul global creste de fiecare data cand este descoperit un nod.
	found: Vec<i32>,

	// cel mai mic timestamp accesibil pe care il poate vedea/accesa nodul
	// low_link[node] = min { found[x] | x este node SAU x este in stramosii(node) SAU x este in descendentii(node) };
	low_link: Vec<i32>,

	// stiva de vizitare: nodurile sunt puse in stiva in ordinea vizitarii
	nodes_stack: Vec<usize>,

	// in_stack[node] = true, daca nodul este in stiva
	//                  false, altfel
	in_stack: Vec<bool>,
}

impl Task {
	fn solve(&mut self) {
		self.read_input();
		let all_sccs = self.tarjan_scc();
		self.write_output(&all_sccs);
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
		}
	}

	fn tarjan_scc(&mut self) -> Vec<Vec<usize>> {
		// PASUL 1: initializez rezultatele
		self.parent = vec![0; self.n + 1];
		self.found = vec![-1; self.n + 1];
		self.low_link = vec![-1; self.n + 1];
		self.in_stack = vec![false; self.n + 1];
		self.nodes_stack.clear();

		let mut all_sccs = Vec::new();
		let mut timestamp = 0;

		// PASUL 2: vizitez toate nodurile
		for node in 1..=self.n {
			if self.parent[node] == 0 {
				// nod nevizitat
				// conventie: parintele radacinii este chiar radacina
				self.parent[node] = node;

				// PASUL 3: pornesc o noua parcurgere DFS pe acest subarbore
				self.dfs(node, &mut timestamp, &mut all_sccs);
			}
		}

		all_sccs
	}

	fn dfs(&mut self, node: usize, timestamp: &mut i32, all_sccs: &mut Vec<Vec<usize>>) {
		// PASUL 1: un nod nou este vizitat - incrementez timestamp-ul
		*timestamp += 1;
		self.found[node] = *timestamp; // timestamp-ul la care nodul a fost descoperit
		self.low_link[node] = self.found[node]; // nodul cunoaste doar propriul timestamp
		self.nodes_stack.push(node); // adaug nodul in stiva de vizitare
		self.in_stack[node] = true;

		// PASUL 2: vizitez fiecare vecin
		let neighbors = self.adj[node].clone();
		for neigh in neighbors {
			// PASUL 3: verific daca neigh este deja vizitat
			if self.parent[neigh] != 0 {
				// PASUL 3.1: actualizez low_link[node] cu informatiile obtinute prin neigh
				// observatie: neigh este in aceeasi CTC cu node doar daca este in stiva de vizitare;
				// altfel, neigh este din alta CTC, deci trebuie ignorat
				if self.in_stack[neigh] {
					self.low_link[node] = min(self.low_link[node], self.found[neigh]);
				}
				continue;
			}

			// PASUL 4: salvez parintele
			self.parent[neigh] = node;

			// PASUL 5: vizitez recursiv subarborele copilului
			self.dfs(neigh, timestamp, all_sccs);

			// PASUL 6: actualizez low_link[node] cu informatiile obtinute prin neigh
			self.low_link[node] = min(self.low_link[node], self.low_link[neigh]);
		}

		// PASUL 7: nodul este radacina unei CTC daca low_link[node] == found[node]
		// (nu exista muchie de la un descendent la un stramos)
		if self.low_link[node] == self.found[node] {
			// PASUL 7.1: extrag toate elementele de deasupra lui node din stiva => obtin CTC-ul in care node este radacina
			let mut scc = Vec::new();
			loop {
				let x = self.nodes_stack.pop().unwrap();
				self.in_stack[x] = false;
				scc.push(x);
				if x == node {
					break;
				}
			}

			// PASUL 7.2: salvez CTC-ul
			all_sccs.push(scc);
		}
	}

	fn write_output(&self, all_sccs: &[Vec<usize>]) {
		let mut out = String::new();
		out.push_str(&format!("{}\n", all_sccs.len()));
		for scc in all_sccs {
			for &node in scc {
				out.push_str(&format!("{} ", node));
			}
			out.push('\n');
		}
		fs::write("out", out).expect("failed to write output");
	}
}

fn main() {
	let mut task = Box::new(Task::default());
	task.solve();
}
