#!/usr/bin/env python3
# SPDX-License-Identifier: BSD-3-Clause


class Task:
    def __init__(self):
        self.n = 0
        self.k = 0

    def solve(self):
        self.read_input()
        self.write_output(self.get_result())

    def read_input(self) -> None:
        with open("in") as fin:
            self.n, self.k = map(int, fin.read().split())

    def get_result(self) -> list[list[int]]:
        all_res = []
        self.solve_bkt(all_res)
        return all_res

    def solve_bkt(self, all_res: list[list[int]]) -> None:
        # Vectorul in care stochez solutia (partiala) curenta
        current = []

        # construiesc combinarile prin backtracking
        self.bkt(current, all_res)

    # Combinari de n luate cate k, implementare cu transmitere prin referinta
    # T = O(n! / (k!*(n-k)!))
    # S = O(n)
    def bkt(self, current: list[int], all_res: list[list[int]]) -> None:
        # Daca avem o multime de dimensiune k
        if len(current) == self.k:
            # este implicit si o combinatie prin modul cum a fost generata

            # Adaug la solutie
            all_res.append(current[:])

            # Ma opresc
            return

        # Daca este primul pas, alegem fiecare element din domeniu ca potential
        # candidat pentru prima pozitie in solutie; altfel, pentru a elimina ramurile
        # in care de exemplu {2, 1} se va genera dupa ce s-a generat {1, 2} (adica
        # ar fi duplicat), vom folosi doar elementele din domeniu care sunt mai mari
        # decat ultimul element adaugat in solutie (solution[step - 1])
        start = 1 if not current else current[-1] + 1
        for i in range(start, self.n + 1):
            # Step 1: ADAUG elementul la solutie
            current.append(i)

            # Step 2: COMPLETEZ recursiv si solutia
            self.bkt(current, all_res)

            # Step 3: Scot elementul din solutie, ca sa pot pune altul in locul lui
            current.pop()

    def write_output(self, result: list[list[int]]) -> None:
        with open("out", "w") as fout:
            fout.write(f"{len(result)}\n")
            for perm in result:
                fout.write(" ".join(map(str, perm)) + "\n")


def main() -> None:
    task = Task()
    task.solve()


# [ATENTIE] NU modifica blocul de mai jos
if __name__ == "__main__":
    main()
