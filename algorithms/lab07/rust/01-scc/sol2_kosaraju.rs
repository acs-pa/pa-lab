// SPDX-License-Identifier: BSD-3-Clause

use std::fs;

#[derive(Default)]
struct Task {
	// n = numar de noduri, m = numar de muchii/arce
	n: usize,

	// adj[node] = lista de adiacenta a nodului node
	// exemplu: daca adj[node] = {..., neigh, ...} => exista arcul (node, neigh) in graf
	adj: Vec<Vec<usize>>,

	// adj_trans[node] = lista de adiacenta a nodului node in graful transpus
	// exemplu: daca adj_trans[node] = {..., neigh, ...} => exista arcul (node, neigh) in graful transpus
	adj_trans: Vec<Vec<usize>>,
}

impl Task {
	fn solve(&mut self) {
		self.read_input();
		let all_sccs = self.ctc_kosaraju();
		self.write_output(&all_sccs);
	}

	fn read_input(&mut self) {
		let data = fs::read_to_string("in").expect("failed to read input");
		let mut it = data.split_whitespace();

		self.n = it.next().unwrap().parse::<usize>().unwrap();
		let m = it.next().unwrap().parse::<usize>().unwrap();
		self.adj = vec![Vec::new(); self.n + 1];
		self.adj_trans = vec![Vec::new(); self.n + 1];

		for _ in 0..m {
			let x = it.next().unwrap().parse::<usize>().unwrap();
			let y = it.next().unwrap().parse::<usize>().unwrap();
			self.adj[x].push(y);
			self.adj_trans[y].push(x);
		}
	}

	fn ctc_kosaraju(&self) -> Vec<Vec<usize>> {
		let mut visited = vec![false; self.n + 1];

		// retin nodurile crescator dupa timpul de finalizare
		// reverse(finish_sort.begin(), finish_sort.end()) reprezinta sortarea topologica
		let mut finish_sort = Vec::with_capacity(self.n);

		// parcurgere pe graful initial
		for node in 1..=self.n {
			if !visited[node] {
				// nevizitat pe adj => visited[node] == false
				self.dfs(node, &mut visited, &mut finish_sort);
			}
		}

		// parcurgere pe graful transpus dat de sortarea topologica
		let mut all_sccs = Vec::new();
		for &node in finish_sort.iter().rev() {
			if visited[node] {
				// nevizitat pe adj_trans => visited[node] == true
				// construiesc o noua ctc
				let mut scc = Vec::new();
				self.dfs_trans(node, &mut visited, &mut scc);

				// o salvez
				all_sccs.push(scc);
			}
		}

		all_sccs
	}

	// dfs pe graful normal (folosesc adj)
	fn dfs(&self, node: usize, visited: &mut [bool], finish_sort: &mut Vec<usize>) {
		visited[node] = true;
		for &neigh in &self.adj[node] {
			if !visited[neigh] {
				self.dfs(neigh, visited, finish_sort);
			}
		}
		// adaug nodul la sortarea topologica
		finish_sort.push(node);
	}

	// dfs pe graful transpus (folosesc adj_trans)
	fn dfs_trans(&self, node: usize, visited: &mut [bool], scc: &mut Vec<usize>) {
		// vizitarea pe graful transpus, inseamna
		visited[node] = false;
		scc.push(node);
		for &neigh in &self.adj_trans[node] {
			if visited[neigh] {
				self.dfs_trans(neigh, visited, scc);
			}
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
