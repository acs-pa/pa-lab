#!/usr/bin/env python3
# SPDX-License-Identifier: BSD-3-Clause

import sys


sys.setrecursionlimit(1_000_000)


class Task:
    def __init__(self):
        # n = numar de noduri, m = numar de muchii
        self.n = 0
        self.m = 0

        # adj[i] = lista de adiacenta a nodului i
        self.adj = []

        # ordinea de vizitare
        # found[node] = timpul de start a lui node in parcurgerea DFS
        # in laborator found se numeste idx
        self.found = []

        # low_link[node] = min { found[x] | x este accesibil din node }
        # adica timpul minim al unui nod
        self.low_link = []

        # stiva folosita pentru a reconstrui componentele biconexe
        self.sc: list[tuple[int, int]] = []

        # parent[i] = parintele nodului i
        self.parent = []

        # vector in care retin componentele biconexe
        # all_bccs[i] = componenta biconexa cu indicele i
        self.all_bccs: list[list[int]] = []

    def solve(self) -> None:
        self.read_input()
        self.tarjan()
        self.write_output(self.all_bccs)

    def read_input(self) -> None:
        with open("in", "r", encoding="utf-8") as fin:
            self.n, self.m = map(int, fin.readline().split())
            self.adj = [[] for _ in range(self.n + 1)]
            for _ in range(self.m):
                x, y = map(int, fin.readline().split())
                self.adj[x].append(y)
                self.adj[y].append(x)

    def tarjan(self) -> None:
        self.found = [-1] * (self.n + 1)
        self.low_link = [0] * (self.n + 1)
        self.parent = [0] * (self.n + 1)

        # momentul curent de start
        # pe masura ce vizitam nodurile el va creste (++)
        current_start = 0

        for node in range(1, self.n + 1):
            if self.found[node] == -1:
                # acest nod nu a fost descoperit, deci il putem folosi
                # marcam nodul node ca fiind radacina
                self.parent[node] = 0

                # pornim o noua cautare din nodul respectiv
                current_start = self.dfs(node, current_start)

    def dfs(self, node: int, current_start: int) -> int:
        # incep un nou nod, deci un nou timp de start
        current_start += 1

        # atat found, cat si low_link vor primi valoarea lui current_start
        self.found[node] = current_start
        self.low_link[node] = current_start

        for neigh in self.adj[node]:
            if self.found[neigh] == -1:
                # parintele nodului in care ma duc este chiar nodul curent
                self.parent[neigh] = node

                # retin muchiile de avansare
                self.sc.append((node, neigh))

                # pornesc un nou dfs
                current_start = self.dfs(neigh, current_start)

                # actualizez low_link
                self.low_link[node] = min(self.low_link[node], self.low_link[neigh])

                # daca am gasit un punct de articulatie inseamna ca am descoperit
                # o noua componenta biconexa
                if self.low_link[neigh] >= self.found[node]:
                    self.get_bcc((node, neigh))
            else:
                # !!! graful fiind neorientat trebuie sa ignor muchia catre parinte
                if neigh != self.parent[node]:
                    # am gasit o muchie de intoarcere
                    self.low_link[node] = min(self.low_link[node], self.found[neigh])

        return current_start

    def get_bcc(self, target_edge: tuple[int, int]) -> None:
        # construim o noua componenta biconexa
        current_bcc: list[int] = []

        # extragem muchii din stiva pana am extras muchia target_edge
        while True:
            current_edge = self.sc.pop()

            # adaug capetele muchiei in bcc
            current_bcc.append(current_edge[0])
            current_bcc.append(current_edge[1])

            if current_edge == target_edge:
                break

        # trebuie sa eliminam duplicatele
        current_bcc = sorted(set(current_bcc))

        # current_bcc este o BCC valida
        self.all_bccs.append(current_bcc)

    def write_output(self, result: list[list[int]]) -> None:
        with open("out", "w", encoding="utf-8") as fout:
            fout.write(f"{len(result)}\n")
            for bcc in result:
                fout.write(" ".join(map(str, bcc)) + " \n")


def main() -> None:
    task = Task()
    task.solve()


if __name__ == "__main__":
    main()
