# SPDX-License-Identifier: BSD-3-Clause

import sys
from collections import deque

class Task:
    def __init__(self) -> None:
        # n = numar de noduri, m = numar de muchii/arce
        self.n = 0
        self.m = 0

        # adj[node] = lista de adiacenta a nodului node
        # exemplu: daca adj[node] = [..., neigh, ...] => exista arcul (node, neigh)
        self.adj = []

        # in_degree[node] = gradul intern al nodului node
        self.in_degree = []

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
            # grad intern 0 pentru toate nodurile... momentan
            self.in_degree = [0] * (self.n + 1)

            idx = 2
            for _ in range(self.m):
                x = int(tokens[idx])
                y = int(tokens[idx+1])
                self.adj[x].append(y) # arc (x, y)
                self.in_degree[y] += 1 # numar inca o muchie care intra in y
                idx += 2

    def get_result(self) -> list[int]:
        return self.solve_bfs()

    # Complexitate: O(n + m)
    def solve_bfs(self) -> list[int]:
        # Step 0: initializare topsort - permutare vida initial
        topsort = []

        # Step 1: declaram o coada in care putem baga noduri
        q = deque()

        # Step 2: pasul initial: pun in coada TOATE nodurile cu grad intern 0
        for node in range(1, self.n + 1):
            if self.in_degree[node] == 0:
                q.append(node)

        # in_degree il modificam, deci facem o copie
        in_degree = list(self.in_degree)

        # Step 3: parcurg in latime graful
        while q:
            # 3.1: SCOT primul nod din coada
            # adaug la solutie elementul scos
            node = q.popleft()
            topsort.append(node)

            # 3.2 Ii parcurg toti vecinii
            for neigh in self.adj[node]:
                # sterg muchia node->neigh
                # obs1. NU e nevoie sa o sterg la propriu
                #       Daca nu am cicluri, nu se va ajunge aici
                # obs2. Simulez stergerea prin scaderea gradului intern a lui neigh
                in_degree[neigh] -= 1

                # daca neigh a ajuns nod cu grad intern 0, atunci este adaugat in coada
                if in_degree[neigh] == 0:
                    q.append(neigh)

        # Step 4: verifica ca topsort chiar reprezinta o sortare topologica valida
        # Ce inseamna asta? S-au sters toate muchiile din graf.
        # Daca nu s-a sters tot, atunci graful este ciclic!
        is_valid = all(d == 0 for d in in_degree[1:self.n+1])
        if is_valid:
            return topsort # sortarea topologica obtinuta
        else:
            return [] # vector gol == nu se poate face o sortare topologica

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
