# SPDX-License-Identifier: BSD-3-Clause

import heapq


class Task:
    def __init__(self) -> None:
        # numarul maxim de noduri
        self.NMAX = 50005

        # valoare mai mare decat orice distanta din graf
        self.INF = 1 << 30

        # n = numar de noduri, m = numar de muchii
        self.n = 0
        self.m = 0

        # adj[node] = lista de adiacenta a nodului node
        # perechea (neigh, w) semnifica arc de la node la neigh de cost w
        self.adj: list[list[tuple[int, int]]] = []

        # nodul sursa
        self.source = 0

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
                y = int(tokens[idx + 1])
                w = int(tokens[idx + 2])
                self.adj[x].append((y, w))
                idx += 3

    def get_result(self) -> list[int]:
        return self.dijkstra(self.source)

    def dijkstra(self, source: int) -> list[int]:
        # Initializam vectorul de distante cu distante infinite.
        d = [self.INF] * (self.n + 1)
        p = [0] * (self.n + 1)

        # Inseram nodul de plecare in coada si ii actualizam distanta.
        d[source] = 0
        pq: list[tuple[int, int]] = [(0, source)]

        while pq:
            # Scoatem top-ul.
            cost, node = heapq.heappop(pq)

            # Daca distanta din coada nu e optima, dam discard.
            if cost > d[node]:
                continue

            # Ii parcurgem toti vecinii.
            for neigh, w in self.adj[node]:
                # Se imbunatateste distanta?
                if d[node] + w < d[neigh]:
                    # Actualizam distanta si parintele.
                    d[neigh] = d[node] + w
                    p[neigh] = node

                    # Inseram noua distanta.
                    heapq.heappush(pq, (d[neigh], neigh))

        # Toate nodurile catre care distanta este inca INF nu pot fi atinse din
        # nodul source, deci le setam pe -1.
        for node in range(1, self.n + 1):
            if d[node] == self.INF:
                d[node] = -1

        return d

    def write_output(self, d: list[int]) -> None:
        with open("out", "w") as fout:
            out_str = " ".join(str(d[node]) for node in range(1, self.n + 1))
            fout.write(out_str + " \n")


def main() -> None:
    task = Task()
    task.solve()


# [ATENTIE] NU modifica functia main!
if __name__ == "__main__":
    main()
