#!/usr/bin/env python3
# SPDX-License-Identifier: BSD-3-Clause

import math

class Task:
    def __init__(self):
        self.n = 0                 # numărul de matrici
        self.d: list[int] = []     # dimensiunile matricilor

    def solve(self):
        self.read_input()
        self.write_output(self.get_result())

    def read_input(self):
        with open("in") as fin:
            self.n = int(fin.readline().strip())
            self.d = list(map(int, fin.readline().split()))

    def get_result(self) -> int:
        return self.solve_podm()

    # PODM = Produsul Optim de Matrici, implementarea clasică cu DP
    # T = O(n ^ 3)
    # S = O(n ^ 2) - stocam n x n intregi in tabloul dp
    def solve_podm(self) -> int:
        # dp[i][j] = numarul MINIM inmultiri scalare cu codare poate fi calculat produsul
        #            matricial M_i * M_i+1 * ... * M_j
        dp = [[float('inf')] * (self.n + 1) for _ in range(self.n + 1)]

        # Cazul de baza 1: nu am ce inmulti
        for i in range(1, self.n + 1):
            dp[i][i] = 0

        # Cazul de baza 2: matrice d[i - 1] x d[i] inmultia cu matrice d[i] x d[i + 1]
        # (matrice pe pozitii consecutive)
        for i in range(1, self.n):
            dp[i][i + 1] = self.d[i - 1] * self.d[i] * self.d[i + 1]

        # Cazul general:
        # dp[i][j] = min(dp[i][k] + dp[k + 1][j] + d[i - 1] * d[k] * d[j]), k = i : j - 1
        for length in range(2, self.n + 1): # fixam lungimea intervalului (2, 3, 4, ...)
            for i in range(1, self.n - length + 2): # fixam capatul din stanga: i
                j = i + length - 1 # capatul din dreapta se deduce: j

                # Iteram prin indicii dintre capete, spargand sirul de inmultiri in doua (paranteze).
                for k in range(i, j):
                    # M_i * ... M_j  = (M_i * .. * M_k) * (M_k+1 *... * M_j)
                    new_sol = dp[i][k] + dp[k + 1][j] + self.d[i - 1] * self.d[k] * self.d[j]

                    # actualizam solutia daca este mai buna
                    if new_sol < dp[i][j]:
                        dp[i][j] = new_sol

        # Rezultatul se afla in dp[1][self.n]: Numarul MINIM de inmultiri scalare
        # pe care trebuie sa le facem pentru a obtine produsul M_1 * ... * M_n
        return int(dp[1][self.n])

    def write_output(self, result: int) -> None:
        with open("out", "w") as fout:
            fout.write(f"{result}\n")


def main() -> None:
    task = Task()
    task.solve()


# [ATENTIE] NU modifica blocul de mai jos!
if __name__ == "__main__":
    main()
