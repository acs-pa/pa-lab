# SPDX-License-Identifier: BSD-3-Clause


class Task:
    def __init__(self) -> None:
        # n = numar de noduri
        self.n = 0

        # parent[node] = parintele nodului node
        # Cazuri particulare:
        #      * parent[source] = -1
        #      * parent[node] = -1, daca node nu este accesibil din nodul sursa.
        self.parent: list[int] = []

        # nodul sursa si nodul destinatie
        # (capetele drumului care trebuie reconstruit)
        self.source = 0
        self.destination = 0

    def solve(self) -> None:
        self.read_input()
        self.write_output(self.get_result())

    def read_input(self) -> None:
        with open("in", "r") as fin:
            tokens = fin.read().split()
            if not tokens:
                return

            self.n = int(tokens[0])
            self.source = int(tokens[1])
            self.destination = int(tokens[2])

            self.parent = [0] * (self.n + 1)
            for node in range(1, self.n + 1):
                self.parent[node] = int(tokens[2 + node])

    def get_result(self) -> list[int]:
        path: list[int] = []

        # Pornesc de la nodul destinatie si ii caut parintele.
        node = self.destination

        # Daca parintele lui node este -1, inseamna ca node este chiar source
        # sau node nu este accesibil din nodul source.
        while self.parent[node] != -1:
            # Daca el exista, atunci poate face dintr-un path valid.
            path.append(node)

            # Se cauta parintele nodului curent.
            node = self.parent[node]

        # Daca node nu este sursa, inseamna ca nu am putut ajunge inapoi
        # la nodul sursa, deci trebuie returnat un vector gol.
        if node != self.source:
            return []

        # Node este sursa, deci se adauga la path.
        path.append(self.source)

        # Se inverseaza ordinea nodurilor, pentru a obtine un drum
        # source - node_1 - node_2 - ... - node_k -  destination,
        # unde un node este parintele vecinului de la dreapta.
        path.reverse()

        return path

    def write_output(self, result: list[int]) -> None:
        with open("out", "w") as fout:
            if not result:
                fout.write("Nu se poate ajunge\n")
            else:
                out_str = " ".join(map(str, result))
                fout.write(out_str + " \n")


def main() -> None:
    task = Task()
    task.solve()


# [ATENTIE] NU modifica functia main!
if __name__ == "__main__":
    main()
