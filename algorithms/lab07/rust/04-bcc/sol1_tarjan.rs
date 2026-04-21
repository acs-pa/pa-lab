// SPDX-License-Identifier: BSD-3-Clause

use std::cmp::min;
use std::fs;

#[derive(Default)]
struct Task {
	// n = numar de noduri, m = numar de muchii
	n: usize,

	// adj[i] = lista de adiacenta a nodului i
	adj: Vec<Vec<usize>>,

	// ordinea de vizitare
	// found[node] = timpul de start a lui node in parcurgerea DFS
	// in laborator found se numeste idx
	found: Vec<i32>,

	// low_link[node] = min { found[x] | x este accesibil din node }
	// adica timpul minim al unui nod
	low_link: Vec<i32>,

	// parent[i] = parintele nodului i
	parent: Vec<usize>,

	// stiva folosita pentru a reconstrui componentele biconexe
	stack_edges: Vec<(usize, usize)>,

	// vector in care retin componentele biconexe
	// all_bccs[i] = componenta biconexa cu indicele i
	all_bccs: Vec<Vec<usize>>,
}

impl Task {
	fn solve(&mut self) {
		self.read_input();
		self.tarjan();
		self.write_output();
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

	fn tarjan(&mut self) {
		// PASUL 1: initializez rezultatele
		self.found = vec![-1; self.n + 1];
		self.low_link = vec![0; self.n + 1];
		self.parent = vec![0; self.n + 1];
		self.stack_edges.clear();
		self.all_bccs.clear();

		// momentul curent de start
		// pe masura ce vizitam nodurile el va creste (++)
		let mut current_start = 0;
		// PASUL 2: vizitez toate nodurile
		for node in 1..=self.n {
			if self.found[node] == -1 {
				// acest nod nu a fost descoperit, deci il putem folosi
				// marcam nodul node ca fiind radacina
				self.parent[node] = 0;

				// PASUL 3: pornesc o noua parcurgere DFS pe acest subarbore
				self.dfs(node, &mut current_start);
			}
		}
	}

	fn dfs(&mut self, node: usize, current_start: &mut i32) {
		// PASUL 1: un nod nou este vizitat - incrementez timestamp-ul
		*current_start += 1;
		self.found[node] = *current_start;
		self.low_link[node] = *current_start;

		// PASUL 2: vizitez fiecare vecin
		let neighbors = self.adj[node].clone();
		for neigh in neighbors {
			// PASUL 3: verific daca neigh este deja vizitat
			if self.found[neigh] == -1 {
				// PASUL 4: salvez parintele
				self.parent[neigh] = node;

				// retin muchiile de avansare
				self.stack_edges.push((node, neigh));

				// PASUL 5: vizitez recursiv subarborele copilului
				self.dfs(neigh, current_start);

				// PASUL 6: actualizez low_link[node] cu informatiile obtinute prin neigh
				self.low_link[node] = min(self.low_link[node], self.low_link[neigh]);

				// daca am gasit un punct de articulatie inseamna ca am descoperit
				// o noua componenta biconexa
				if self.low_link[neigh] >= self.found[node] {
					self.get_bcc((node, neigh));
				}
			} else if neigh != self.parent[node] {
				// am gasit o muchie de intoarcere
				self.low_link[node] = min(self.low_link[node], self.found[neigh]);
			}
		}
	}

	fn get_bcc(&mut self, target_edge: (usize, usize)) {
		// construim o noua componenta biconexa
		let mut current_bcc = Vec::new();

		// extragem muchii din stiva pana am extras muchia target_edge
		loop {
			let edge = self.stack_edges.pop().unwrap();

			// adaug capetele muchiei in bcc
			current_bcc.push(edge.0);
			current_bcc.push(edge.1);

			if edge == target_edge {
				break;
			}
		}

		// trebuie sa eliminam duplicatele
		current_bcc.sort_unstable();
		current_bcc.dedup();

		// current_bcc este o BCC valida
		self.all_bccs.push(current_bcc);
	}

	fn write_output(&self) {
		let mut out = String::new();
		out.push_str(&format!("{}\n", self.all_bccs.len()));
		for bcc in &self.all_bccs {
			for &node in bcc {
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
