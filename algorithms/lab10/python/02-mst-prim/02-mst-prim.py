# SPDX-License-Identifier: BSD-3-Clause

import heapq

class Task:
    def __init__(self) -> None:
        # n = numar de noduri, m = numar de muchii
        self.n = 0
        self.m = 0

        # muchiile din graf: (node, neigh, w) - muchie de la node la neigh de cost w
        self.edges: list[tuple[int, int, int]] = []

        # valoare mai mare decat orice distanta din graf
        self.INF = 1 << 30

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
        return self.prim(self.n, self.edges, 1)

    # MST generat cu Prim, pornind de la un nod radacina ales anterior.
    # Complexitate: O(m log n).
    def prim(self, nodes: int, edges: list[tuple[int, int, int]], source: int) -> tuple[int, list[tuple[int, int]]]:
        # adj[node] = lista de adiacenta a lui node: (neigh, w)
        adj: list[list[tuple[int, int]]] = [[] for _ in range(nodes + 1)]
        for x, y, w in edges:
            adj[x].append((y, w))
            adj[y].append((x, w))

        # d[node] = distanta nodului node fata de MST-ul curent (cel ma apropiat nod din MST)
        # d[node] in aceasta problema va fi mereu egal cu costul unei muchii
        # Initializam vectorul de distante cu distante infinite.
        d = [self.INF] * (nodes + 1)
        # p[node] = parintele lui node (initializat cu 0)
        p = [0] * (nodes + 1)
        used = [0] * (nodes + 1)

        # In loc de un priority_queue<> folosim heapq, cu elemente tupluri de
        # tipul (distanta pana la nod, nod). Heap-ul tine elementele ordonate, deci
        # mereum in varf vom avea tuplul care ii corespunde nodului cu distanta minima.
        pq: list[tuple[int, int]] = []

        # Inseram nodul de plecare in coada si ii actualizam distanta.
        d[source] = 0
        p[source] = 0
        heapq.heappush(pq, (d[source], source))

        # Initializam MST: cost 0, fara muchii
        cost = 0
        mst: list[tuple[int, int]] = []

        # Adaugam fix n noduri la arbore
        while pq:
            # Scoatem un nod din coada.
            w, node = heapq.heappop(pq)

            # In cazul in care nodul e deja in MST, ignoram aceasta intrare.
            if used[node]:
                continue

            # Adaug muchia node - p[node].
            used[node] = 1

            # Nodul radacina este adaugat print-o muchie fictiva,
            # care nu face parte din MST.
            if p[node] != 0:
                cost += d[node]
                mst.append((node, p[node]))

            # Ii parcurgem toti vecinii.
            for neigh, weight in adj[node]:
                # Se imbunatateste distanta?
                if not used[neigh] and weight < d[neigh]:
                    # Actualizam distanta si inseram din nou in set.
                    d[neigh] = weight
                    p[neigh] = node
                    heapq.heappush(pq, (d[neigh], neigh))

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
