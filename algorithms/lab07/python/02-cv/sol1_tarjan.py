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
        # exemplu: daca adj[node] = {..., neigh, ...} => exista muchia (node, neigh)
        self.adj = []

        # parent[node] = parent of node in the DFS traversal
        self.parent = []

        # found[node] = the timestamp when node was found (when started to visit its subtree)
        # Note: The global timestamp is incremented everytime a node is found.
        self.found = []

        # the minimum accessible timestamp that node can see/access
        # low_link[node] =  min { found[x] | x is node OR x in ancestors(node) OR x in descendants(node) }
        self.low_link = []

    def solve(self) -> None:
        self.read_input()
        self.write_output(self.tarjan_cv())

    def read_input(self) -> None:
        with open("in", "r", encoding="utf-8") as fin:
            self.n, self.m = map(int, fin.readline().split())
            self.adj = [[] for _ in range(self.n + 1)]
            for _ in range(self.m):
                x, y = map(int, fin.readline().split())
                self.adj[x].append(y)
                self.adj[y].append(x)

    def tarjan_cv(self) -> list[int]:
        # STEP 1: initialize results
        self.parent = [0] * (self.n + 1)
        self.found = [-1] * (self.n + 1)
        self.low_link = [-1] * (self.n + 1)

        # STEP 2: visit all nodes
        all_cvs = set()
        timestamp = 0
        for node in range(1, self.n + 1):
            if self.parent[node] == 0:
                # node not visited
                # convention: the parent of the root is actually the root
                self.parent[node] = node

                # STEP 3: start a new DFS traversal this subtree
                timestamp = self.dfs(node, timestamp, all_cvs)

        return list(all_cvs)

    def dfs(self, node: int, timestamp: int, all_cvs: set[int]) -> int:
        # STEP 1: a new node is visited - increment the timestamp
        timestamp += 1
        self.found[node] = timestamp  # the timestamp when node was found
        self.low_link[node] = self.found[node]  # node only knows its timestamp

        # STEP 2: visit each neighbour
        children = 0  # count all children for node
        for neigh in self.adj[node]:
            # STEP 3: check if neigh is already visited
            if self.parent[neigh] != 0:
                # STEP 3.1: update low_link[node] with information gained through neigh
                # note: because it's an undirected graph, we should ignore the edge to the parent
                # (the found value of the parent is always less than found value of node)
                if neigh != self.parent[node]:
                    self.low_link[node] = min(self.low_link[node], self.found[neigh])
                continue

            # STEP 4: save parent
            self.parent[neigh] = node
            children += 1  # count child

            # STEP 5: recursively visit the child subtree
            timestamp = self.dfs(neigh, timestamp, all_cvs)

            # STEP 6: update low_link[node] with information gained through neigh
            self.low_link[node] = min(self.low_link[node], self.low_link[neigh])

            # STEP 7.1: node is a CV if i): *) node is NOT root and **) low_link[neigh] >= found[node]
            if self.parent[node] != node and self.low_link[neigh] >= self.found[node]:
                all_cvs.add(node)

        # STEP 7.2: node is a CV if i)): *) node is root and **) it has at least 2 children
        if self.parent[node] == node and children > 1:
            all_cvs.add(node)

        return timestamp

    def write_output(self, all_cvs: list[int]) -> None:
        with open("out", "w", encoding="utf-8") as fout:
            fout.write(" ".join(map(str, all_cvs)) + " \n")


def main() -> None:
    task = Task()
    task.solve()


if __name__ == "__main__":
    main()
