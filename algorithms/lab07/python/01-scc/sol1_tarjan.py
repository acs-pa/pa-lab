#!/usr/bin/env python3
# SPDX-License-Identifier: BSD-3-Clause

import sys


sys.setrecursionlimit(1_000_000)


class Task:
    def __init__(self):
        # n = numar de noduri, m = numar de muchii/arce
        self.n = 0
        self.m = 0

        # adj[node] = lista de adiacenta a nodului node
        # exemplu: daca adj[node] = {..., neigh, ...} => exista arcul (node, neigh)
        self.adj = []

        # parent[node] = parent of node in the DFS traversal
        self.parent = []

        # found[node] = the timestamp when node was found (when started to visit its subtree)
        # Note: The global timestamp is incremented everytime a node is found.
        self.found = []

        # the minimum accessible timestamp that node can see/access
        # low_link[node] =  min { found[x] | x is node OR x in ancestors(node) OR x in descendants(node) }
        self.low_link = []

        # visiting stack: nodes are pushed into the stack in visiting order
        self.nodes_stack = []

        # in_stack[node] = true, if node is in stack
        #                  false, otherwise
        self.in_stack = []

    def solve(self) -> None:
        self.read_input()
        self.write_output(self.tarjan_scc())

    def read_input(self) -> None:
        with open("in", "r", encoding="utf-8") as fin:
            self.n, self.m = map(int, fin.readline().split())
            self.adj = [[] for _ in range(self.n + 1)]
            for _ in range(self.m):
                x, y = map(int, fin.readline().split())
                self.adj[x].append(y)

    def tarjan_scc(self) -> list[list[int]]:
        # STEP 1: initialize results
        self.parent = [0] * (self.n + 1)
        self.found = [-1] * (self.n + 1)
        self.low_link = [-1] * (self.n + 1)
        self.in_stack = [False] * (self.n + 1)
        self.nodes_stack = []

        # STEP 2: visit all nodes
        all_sccs: list[list[int]] = []
        timestamp = 0
        for node in range(1, self.n + 1):
            if self.parent[node] == 0:
                # node not visited
                # convention: the parent of the root is actually the root
                self.parent[node] = node

                # STEP 3: start a new DFS traversal this subtree
                timestamp = self.dfs(node, timestamp, all_sccs)

        return all_sccs

    def dfs(self, node: int, timestamp: int, all_sccs: list[list[int]]) -> int:
        # STEP 1: a new node is visited - increment the timestamp
        timestamp += 1
        self.found[node] = timestamp  # the timestamp when node was found
        self.low_link[node] = self.found[node]  # node only knows its timestamp
        self.nodes_stack.append(node)  # add node to the visiting stack
        self.in_stack[node] = True

        # STEP 2: visit each neighbour
        for neigh in self.adj[node]:
            # STEP 3: check if neigh is already visited
            if self.parent[neigh] != 0:
                # STEP 3.1: update low_link[node] with information gained through neigh
                # note: neigh is in the same SCC with node only if it's in the visiting stack;
                # otherwise, neigh is from other SCC, so it should be ignored
                if self.in_stack[neigh]:
                    self.low_link[node] = min(self.low_link[node], self.found[neigh])
                continue

            # STEP 4: save parent
            self.parent[neigh] = node

            # STEP 5: recursively visit the child subtree
            timestamp = self.dfs(neigh, timestamp, all_sccs)

            # STEP 6: update low_link[node] with information gained through neigh
            self.low_link[node] = min(self.low_link[node], self.low_link[neigh])

        # STEP 7: node is root in a SCC if low_link[node] == found[node]
        # (there is no edge from a descendant to an ancestor)
        if self.low_link[node] == self.found[node]:
            # STEP 7.1: pop all elements above node from stack => extract the SCC where node is root
            scc = []
            while True:
                x = self.nodes_stack.pop()
                self.in_stack[x] = False
                scc.append(x)
                if x == node:
                    break

            # STEP 7.2: save SCC
            all_sccs.append(scc)

        return timestamp

    def write_output(self, all_sccs: list[list[int]]) -> None:
        with open("out", "w", encoding="utf-8") as fout:
            fout.write(f"{len(all_sccs)}\n")
            for scc in all_sccs:
                fout.write(" ".join(map(str, scc)) + " \n")


def main() -> None:
    task = Task()
    task.solve()


if __name__ == "__main__":
    main()
