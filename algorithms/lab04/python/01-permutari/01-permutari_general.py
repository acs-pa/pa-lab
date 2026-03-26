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

        # Construim permutările prin backtracking.
        self.bkt(domain, [], all_res)

    # Permutări de n elemente, implementare pe caz general.
    # T = O(n * n!)
    # S = O(n^2)
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
            # Creăm o soluție nouă identică cu cea de la pasul curent, și o
            # modificăm.
            new_solution = solution[:] + [num]

            # Ștergem elementul ales din domeniu. Creăm o copie a domeniului.
            new_domain = domain[:i] + domain[i + 1 :]

            # Continuăm generarea cu noua stare.
            self.bkt(new_domain, new_solution, all_res)

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
