#!/usr/bin/env python3
# SPDX-License-Identifier: BSD-3-Clause


class Task:
    def __init__(self):
        self.mat = []

    def solve(self):
        self.read_input()
        self.write_output(self.get_result())

    def read_input(self) -> None:
        with open("in") as fin:
            n = int(fin.readline())
            self.mat = []
            for _ in range(n):
                row = list(map(int, fin.readline().split()))
                self.mat.append(row)

    def get_result(self) -> list[list[tuple[int, int]]]:
        all_res = []
        self.solve_bkt(all_res)
        return all_res

    def solve_bkt(self, all_res: list[list[tuple[int, int]]]) -> None:
        # Adăugăm forțat poziția de start în stivă / soluția parțială.
        current = [(0, 0)]
        self.bkt(current, all_res)

    # Problema șoricelului = Generarea drumurilor printr-o matrice cu 2 mișcări.
    # T(n) = O(2^(2n))
    # S(n) = O(n)
    def bkt(
        self, current: list[tuple[int, int]], all_res: list[list[tuple[int, int]]]
    ) -> None:
        # Dacă am ajuns la destinație, `current` e un drum complet, nu trebuie extins.
        if current[-1] == (len(self.mat) - 1, len(self.mat) - 1):
            all_res.append(current[:])
            return

        # Folosim un vector de direcții pentru mișcările disponibile.
        for mod_r, mod_c in [(0, 1), (1, 0)]:
            r = current[-1][0] + mod_r
            c = current[-1][1] + mod_c

            # Putem continua drumul dacă nu ieșim din matrice și nu suntem blocați.
            if self.in_bounds(r, c) and self.mat[r][c] == 0:
                current.append((r, c))  # Punem pe stivă noua poziție.
                self.bkt(current, all_res)  # Generăm continuările recursiv.
                current.pop()  # După revenire, scoatem celula din stivă.

    # Verifică dacă o poziție e în interiorul matricei.
    def in_bounds(self, r: int, c: int) -> bool:
        return 0 <= r < len(self.mat) and 0 <= c < len(self.mat[r])

    def write_output(self, result: list[list[tuple[int, int]]]) -> None:
        with open("out", "w") as fout:
            fout.write(f"{len(result)}\n")
            for path in result:
                fout.write("->".join(f"({r},{c})" for r, c in path) + "\n")


def main() -> None:
    task = Task()
    task.solve()


# [ATENTIE] NU modifica blocul de mai jos
if __name__ == "__main__":
    main()
