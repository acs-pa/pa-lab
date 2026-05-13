# SPDX-License-Identifier: BSD-3-Clause

# Structura de date descrisa aici https://infoarena.ro/problema/disjoint.
class DisjointSet:
    def __init__(self, nodes: int) -> None:
        # parent[node] = radacina arborelui din care face parte node.
        # (adica identificatorul componentei conexe curente)
        self.parent = list(range(nodes + 1))
        # size[node] = numarul de noduri din arborele in care se afla node acum.
        self.size = [1] * (nodes + 1)

    # Returneaza radacina arborelui din care face parte node.
    def set_of(self, node: int) -> int:
        # Daca node este radacina, atunci am gasit raspunsul.
        if node == self.parent[node]:
            return node

        # Altfel, urcam in sus din "radacina in radacina",
        # actualizand pe parcurs radacinile pentru nodurile atinse.
        self.parent[node] = self.set_of(self.parent[node])
        return self.parent[node]

    # Reuneste arborii lui x si y intr-un singur arbore,
    # folosind euristica de reuniune a drumurilor dupa rank.
    def union(self, x: int, y: int) -> None:
        # Obtinem radacinile celor 2 arbori
        rx = self.set_of(x)
        ry = self.set_of(y)

        # Arborele mai mic este atasat la radacina arborelui mai mare.
        if self.size[rx] <= self.size[ry]:
            self.size[ry] += self.size[rx]
            self.parent[rx] = ry
        else:
            self.size[rx] += self.size[ry]
            self.parent[ry] = rx


class Task:
    def __init__(self) -> None:
        # n = numar de noduri, m = numar de muchii
        self.n = 0
        self.m = 0

        # muchiile din graf: (node, neigh, w) - muchie de la node la neigh de cost w
        self.edges: list[tuple[int, int, int]] = []

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

            idx = 2
            for _ in range(self.m):
                x = int(tokens[idx])
                y = int(tokens[idx + 1])
                w = int(tokens[idx + 2])
                self.edges.append((x, y, w))
                idx += 3

    def get_result(self) -> tuple[int, list[tuple[int, int]]]:
        return self.kruskal(self.n, self.edges)

    # MST generat cu Kruskal.
    # Complexitate: O(m log m).
    def kruskal(self, nodes: int, edges: list[tuple[int, int, int]]) -> tuple[int, list[tuple[int, int]]]:
        # Sortam muchiile crescator dupa cost.
        edges.sort(key=lambda e: e[2])

        # Initializam padurile.
        disjointset = DisjointSet(nodes)

        # Initializam MST: cost 0, fara muchii
        cost = 0
        mst: list[tuple[int, int]] = []

        # Folosim muchiile in ordine crescatoare a costului.
        used_edges = 0
        for x, y, w in edges:
            # Aflam radacinile celor 2 arbori in care sunt x si y.
            if disjointset.set_of(x) != disjointset.set_of(y):
                # Reunim arborii.
                disjointset.union(x, y)

                # Adaugam muchia la MST.
                cost += w
                mst.append((x, y))

                used_edges += 1
                if used_edges == nodes - 1:
                    # Daca am format deja un arbore, ne putem oprim.
                    break

        return cost, mst

    def write_output(self, res: tuple[int, list[tuple[int, int]]]) -> None:
        cost, mst_edges = res
        with open("out", "w") as fout:
            fout.write(f"{cost}\n")
            for x, y in mst_edges:
                fout.write(f"{x} {y}\n")


def main() -> None:
    task = Task()
    task.solve()

if __name__ == "__main__":
    main()
