# SPDX-License-Identifier: BSD-3-Clause

import heapq


class Task:
    def __init__(self) -> None:
        # valoare mai mare decat orice distanta din graf
        self.INF = 1 << 30

        # n = numar de noduri, m = numar de muchii
        self.n = 0
        self.m = 0

        # adj[node] = lista de adiacenta a nodului node
        # perechea (neigh, w) semnifica arc de la node la neigh de cost w
        self.adj: list[list[list[int, int]]] = []

    def solve(self) -> None:
        self.read_input()
        self.write_output(self.compute())

    def read_input(self) -> None:
        with open("in", "r") as fin:
            tokens = fin.read().split()
            if not tokens:
                return

            self.n = int(tokens[0])
            self.m = int(tokens[1])

            self.adj = [[] for _ in range(self.n + 2)]

            idx = 2
            for _ in range(self.m):
                x = int(tokens[idx])
                y = int(tokens[idx + 1])
                w = int(tokens[idx + 2])
                self.adj[x].append([y, w])
                idx += 3

    def compute(self) -> tuple[bool, list[list[int]]]:
        return self.johnson()

    def compute_h(self) -> tuple[bool, list[int]]:
        # Se adauga un nod suplimentar "fictiv"
        new_n = self.n + 1
        source = self.n + 1

        # Se copiaza vectorul de liste de adiacente
        new_adj: list[list[list[int, int]]] = [list(a) for a in self.adj]
        while len(new_adj) <= new_n:
            new_adj.append([])

        # Se leaga la toate celelalte noduri cu distanta "fictiva" 0
        for node in range(1, self.n + 1):
            new_adj[source].append([node, 0])

        # Construiesc un vector de muchii
        edges: list[tuple[int, int, int]] = []
        for node in range(1, new_n + 1):
            for neigh, w in new_adj[node]:
                edges.append((node, neigh, w))

        # Se aplica algoritmul Bellman-Ford pornind din nodul fictiv
        has_cycle, d = self.bellman(source, new_n, edges)

        if has_cycle:
            return (True, [])

        return (False, d)

    def johnson(self) -> tuple[bool, list[list[int]]]:
        d = [[0] * (self.n + 1) for _ in range(self.n + 1)]

        has_cycle, h = self.compute_h()
        if has_cycle:
            return (True, [])

        # Translatare folosind distantele calculate cu BellmanFord pentru a face
        # toate costurile din graf nenegative.
        for u in range(1, self.n + 1):
            for edge in self.adj[u]:
                edge[1] = edge[1] + (h[u] - h[edge[0]])

        # Se aplica algoritmul lui Dijkstra pornind din fiecare nod al grafului.
        for u in range(1, self.n + 1):
            d_dijkstra = self.dijkstra(u)
            for v in range(1, self.n + 1):
                # daca distanta returnata de Dijkstra este -1, nu exista drum intre
                # nodul u si nodul v si pun distanta 0, conform conventiei.
                if d_dijkstra[v] != -1:
                    # daca exista drum intre u si v, trebuie sa fac si translatarea inversa.
                    d[u][v] = d_dijkstra[v] + (h[v] - h[u])

        return (False, d)

    def dijkstra(self, source: int) -> list[int]:
        d = [self.INF] * (self.n + 1)
        d[source] = 0
        pq: list[tuple[int, int]] = [(0, source)]

        while pq:
            cost, node = heapq.heappop(pq)
            if cost > d[node]:
                continue

            for neigh, w in self.adj[node]:
                if d[node] + w < d[neigh]:
                    d[neigh] = d[node] + w
                    heapq.heappush(pq, (d[neigh], neigh))

        for node in range(1, self.n + 1):
            if d[node] == self.INF:
                d[node] = -1

        return d

    def bellman(self, source: int, nodes: int, edges: list[tuple[int, int, int]]) -> tuple[bool, list[int]]:
        d = [self.INF] * (nodes + 1)
        d[source] = 0

        # Fac N - 1 relaxari.
        for _ in range(1, nodes):
            for node, neigh, w in edges:
                if d[node] + w < d[neigh]:
                    d[neigh] = d[node] + w

        # Verific daca mai poate fi updatata distanta.
        for node, neigh, w in edges:
            if d[node] + w < d[neigh]:
                return (True, [])

        for node in range(1, nodes + 1):
            if d[node] == self.INF:
                d[node] = -1

        return (False, d)

    def write_output(self, result: tuple[bool, list[list[int]]]) -> None:
        has_cycle, d = result
        with open("out", "w") as fout:
            if has_cycle:
                fout.write("Ciclu negativ!\n")
            else:
                for u in range(1, self.n + 1):
                    row = " ".join(str(d[u][v]) for v in range(1, self.n + 1))
                    fout.write(row + " \n")


def main() -> None:
    task = Task()
    task.solve()


# [ATENTIE] NU modifica functia main!
if __name__ == "__main__":
    main()
