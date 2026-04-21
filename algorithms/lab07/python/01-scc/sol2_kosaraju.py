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
        # exemplu: daca adj[node] = {..., neigh, ...} => exista arcul (node, neigh) in graf
        self.adj = []

        # adj_trans[node] = lista de adiacenta a nodului node in graful transpus
        # exemplu: daca adj_trans[node] = {..., neigh, ...} => exista arcul (node, neigh) in graful transpus
        self.adj_trans = []

    def solve(self) -> None:
        self.read_input()
        self.write_output(self.ctc_kosaraju())

    def read_input(self) -> None:
        with open("in", "r", encoding="utf-8") as fin:
            self.n, self.m = map(int, fin.readline().split())
            self.adj = [[] for _ in range(self.n + 1)]
            self.adj_trans = [[] for _ in range(self.n + 1)]
            for _ in range(self.m):
                x, y = map(int, fin.readline().split())
                self.adj[x].append(y)
                self.adj_trans[y].append(x)

    def ctc_kosaraju(self) -> list[list[int]]:
        all_ctc: list[list[int]] = []

        # visited[node] = retine daca nodul a fost vizitat sau nu
        # initial visited[node] = 0
        # - cand fac DFS pe graful normal, marchez cu 1 nodurile vizitate
        # - obtin toate nodurile vizitate
        # - cand fac DFS pe graful transpus, le am deja marcate cu 1,
        #   cand vizitez un nod il marchez cu 0
        visited = [0] * (self.n + 1)

        # retin nodurile crescator dupa timpul de finalizare
        # reverse(finish_sort.begin(), finish_sort.end()) reprezinta sortarea topologica
        finish_sort = []

        # parcugere pe graful initial
        for node in range(1, self.n + 1):
            if not visited[node]:
                # nevizitat pe adj => visited[node] == 0
                self.dfs(node, visited, finish_sort)

        # parcurgere pe graful transpus dat de sortarea topologica
        for node in reversed(finish_sort):
            if visited[node]:
                # nevizitat pe adj_trans => visited[node] == 1
                # construiesc o noua ctc
                ctc = []
                self.dfs_trans(node, visited, ctc)

                # o salvez
                all_ctc.append(ctc)

        return all_ctc

    # dfs pe graful normal (folosesc adj)
    def dfs(self, node: int, visited: list[int], finish_sort: list[int]) -> None:
        visited[node] = 1

        for neigh in self.adj[node]:
            if not visited[neigh]:
                self.dfs(neigh, visited, finish_sort)

        # adaug nodul la sortarea topologica
        finish_sort.append(node)

    # dfs pe graful transpus (folosesc adj_trans)
    def dfs_trans(self, node: int, visited: list[int], ctc: list[int]) -> None:
        # vizitarea pe graful transpus, inseamna
        visited[node] = 0
        ctc.append(node)

        for neigh in self.adj_trans[node]:
            if visited[neigh]:
                self.dfs_trans(neigh, visited, ctc)

    def write_output(self, all_ctc: list[list[int]]) -> None:
        with open("out", "w", encoding="utf-8") as fout:
            fout.write(f"{len(all_ctc)}\n")
            for ctc in all_ctc:
                fout.write(" ".join(map(str, ctc)) + " \n")


def main() -> None:
    task = Task()
    task.solve()


if __name__ == "__main__":
    main()
