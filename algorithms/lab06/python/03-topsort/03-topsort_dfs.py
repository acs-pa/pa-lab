# SPDX-License-Identifier: BSD-3-Clause

import sys

sys.setrecursionlimit(10**6)

class Task:
    def __init__(self) -> None:
        # n = numar de noduri, m = numar de muchii/arce
        self.n = 0
        self.m = 0

        # adj[node] = lista de adiacenta a nodului node
        # exemplu: daca adj[node] = [..., neigh, ...] => exista arcul (node, neigh)
        self.adj = []

    def solve(self) -> None:
        self.read_input()
        self.write_output(self.get_result())

    def read_input(self) -> None:
        with open("in", "r") as fin:
            tokens = fin.read().split()
            if not tokens:
                return

            self.n = int(tokens[0])
            self.m = int(tokens[1])

            self.adj = [[] for _ in range(self.n + 1)]

            idx = 2
            for _ in range(self.m):
                x = int(tokens[idx])
                y = int(tokens[idx+1])
                self.adj[x].append(y)
                idx += 2

    def get_result(self) -> list[int]:
        return self.solve_dfs()

    # Complexitate: O(n + m)
    def solve_dfs(self) -> list[int]:
        # vectorul rezultat (in final contine o permutare pentru 1, 2, ..., n)
        topsort = []

        # visited[node] = 1 daca node a fost deja vizitat, 0 altfel
        visited = [0] * (self.n + 1)

        # pentru fiecare nod
        for node in range(1, self.n + 1):
            # daca nodul este nevizitat, pornim o parcurgere
            if visited[node] == 0:
                self.dfs(node, visited, topsort)

        # rezultatul a fost obtinut in ordine inversa
        topsort.reverse()

        return topsort

    # porneste o parcurgere DFS din node
    # foloseste vectorul visited pentru a marca nodurile vizitate
    def dfs(self, node: int, visited: list[int], topsort: list[int]) -> None:
        visited[node] = 1 # marchez nodul ca fiind vizitat

        # parcurg vecinii
        for neigh in self.adj[node]:
            if visited[neigh] == 0:
                self.dfs(neigh, visited, topsort)

        # dupa ce am vizitat recursiv toti vecinii, adaugam
        # nodul la sortare
        topsort.append(node)

    def write_output(self, topsort: list[int]) -> None:
        with open("out", "w") as fout:
            out_str = " ".join(map(str, topsort))
            fout.write(out_str + "\n")

def main() -> None:
    task = Task()
    task.solve()

# [ATENTIE] NU modifica functia main!
if __name__ == "__main__":
    main()
