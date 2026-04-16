# SPDX-License-Identifier: BSD-3-Clause

import sys
from collections import deque

class Task:
    def __init__(self) -> None:
        # n = numar de noduri, m = numar de muchii/arce
        self.n = 0
        self.m = 0
        
        # adj[node] = lista de adiacenta a nodului node
        # exemplu: daca adj[node] = [..., neigh, ...] => exista muchia (node, neigh)
        self.adj = []
        
        # nodul sursa in parcurgerea BFS
        self.source = 0

        # distanta maxima in graf
        self.INF = int(1e9) # 10^9 = 1.000.000.000

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
            self.source = int(tokens[2])
            
            self.adj = [[] for _ in range(self.n + 1)]
            
            idx = 3
            for _ in range(self.m):
                x = int(tokens[idx])
                y = int(tokens[idx+1])
                idx += 2
                self.adj[x].append(y)
                self.adj[y].append(x)

    def get_result(self) -> list[int]:
        return self.bfs(self.source)

    # Complexitate: O(n + m)
    def bfs(self, source: int) -> list[int]:
        # Step 0: alocare vector de distante
        # d[node] = INF, oricare ar fi node
        d = [self.INF] * (self.n + 1)

        # Step 1: declaram o coada in care putem baga noduri
        q = deque()

        # Step 2: pasul initial: pun in coada TOATE nodurile cu grad intern 0
        q.append(source)
        d[source] = 0

        # Step 3: cat timp NU am parcurs toate nodurile
        while q:
            # Step 3.1: extragem si procesam urmatorul nod din coada
            node = q.popleft()

            # Step 3.2: parcurgem vecinii lui node
            for neigh in self.adj[node]:
                # actulizam distanta lui x fata de sursa daca
                # am gasit o solutie mai buna
                if d[node] + 1 < d[neigh]:
                    # adauga nodul in coada si actualizeaza distanta pana la el
                    d[neigh] = d[node] + 1
                    q.append(neigh)

        # Step 4: problema ne cere ca acolo unde nu exista drum sa punem -1
        # inlocuim valorile egale cu INF din d cu -1
        for i in range(1, self.n + 1):
            if d[i] == self.INF:
                d[i] = -1

        return d

    def write_output(self, d: list[int]) -> None:
        with open("out", "w") as fout:
            out_str = " ".join(map(str, d[1:self.n+1]))
            fout.write(out_str + "\n")

def main() -> None:
    task = Task()
    task.solve()

# [ATENTIE] NU modifica functia main!
if __name__ == "__main__":
    main()
