# SPDX-License-Identifier: BSD-3-Clause


class Task:
    def __init__(self) -> None:
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

    def get_result(self) -> tuple[bool, list[int]]:
        # Construiesc un vector de muchii.
        edges: list[tuple[int, int, int]] = []

        for node in range(1, self.n + 1):
            for neigh, w in self.adj[node]:
                edges.append((node, neigh, w))

        return self.bellman(self.source, edges)

    def bellman(self, source: int, edges: list[tuple[int, int, int]]) -> tuple[bool, list[int]]:
        # Initializam vectorul de distante cu distante infinite.
        d = [self.INF] * (self.n + 1)
        p = [0] * (self.n + 1)

        # Setez sursa la distanta 0.
        d[source] = 0

        # Fac N - 1 relaxari.
        for _ in range(1, self.n):
            # Parcurg toate muchiile:
            for node, neigh, w in edges:
                # Se imbunatateste distanta?
                if d[node] + w < d[neigh]:
                    # Actualizam distanta si parintele.
                    d[neigh] = d[node] + w
                    p[neigh] = node

        # Verific daca mai poate fi updatata distanta.
        for node, neigh, w in edges:
            # Se imbunatateste distanta?
            if d[node] + w < d[neigh]:
                # Am gasit un ciclu de cost negativ.
                return (True, [])

        # Toate nodurile catre care distanta este inca INF nu pot fi atinse din
        # nodul source, deci le setam pe -1.
        for node in range(1, self.n + 1):
            if d[node] == self.INF:
                d[node] = -1

        return (False, d)

    def write_output(self, result: tuple[bool, list[int]]) -> None:
        has_cycle, d = result
        with open("out", "w") as fout:
            if has_cycle:
                fout.write("Ciclu negativ!\n")
            else:
                out_str = " ".join(str(d[node]) for node in range(1, self.n + 1))
                fout.write(out_str + " \n")


def main() -> None:
    task = Task()
    task.solve()


# [ATENTIE] NU modifica functia main!
if __name__ == "__main__":
    main()
