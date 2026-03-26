#!/usr/bin/env python3
# SPDX-License-Identifier: BSD-3-Clause


class Task:
    def __init__(self):
        self.n = 0

    def solve(self):
        self.read_input()
        self.write_output(self.get_result())

    def read_input(self) -> None:
        with open("in") as fin:
            self.n = int(fin.read())

    def get_result(self) -> list[list[int]]:
        all_res = []
        self.solve_bkt(all_res)
        return all_res

    def solve_bkt(self, all_res: list[list[int]]) -> None:
        # La începutul generării putem alege din fiecare număr între 1 și n.
        domain = list(range(1, self.n + 1))

        solution = []

        # Construim permutările prin backtracking.
        self.bkt(domain, solution, all_res)

    # Permutări de n elemente, implementare cu referințe.
    # T = O(n * n!)
    # S = O(n)
    def bkt(
        self, domain: list[int], solution: list[int], all_res: list[list[int]]
    ) -> None:
        # După ce am folosit toate elementele din domeniu, putem verifica dacă
        # am găsit o soluție.
        if len(domain) == 0:
            if self.check(solution):
                all_res.append(solution[:])
            return

        # Încercăm să adăugăm în soluție toate valorile din domeniu, pe rând.
        for i, num in enumerate(domain):
            tmp = num

            # Adaug elementul curent la potențiala soluție.
            solution.append(tmp)
            # Șterg elementul curent ca să nu îl refolosesc.
            domain.pop(i)

            # Continuăm generarea cu noua stare.
            self.bkt(domain, solution, all_res)

            # Refac domeniul și soluția la modul în care erau înainte de
            # apelarea recursivă a backtracking-ului.
            domain.insert(i, tmp)
            solution.pop()

    # Deoarece numerele sunt șterse din domeniu odată ce sunt folosite, soluția
    # generată este garantată să nu conțină duplicate. Astfel, atunci când
    # domeniul ajunge vid, soluția este intotdeauna corectă.
    def check(self, solution: list[int]) -> bool:
        return True

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
