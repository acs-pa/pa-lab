#!/usr/bin/env python3
# SPDX-License-Identifier: BSD-3-Clause


class SCMAXResult:
    # length = lungimea SCMAX
    # sequence = secvența SCMAX
    def __init__(self, length: int, sequence: list[int]):
        self.length = length
        self.sequence = sequence


class Task:
    def __init__(self):
        self.n = 0
        self.v: list[int] = []  # index 0 nefolosit; preferăm indexarea de la 1

    def solve(self):
        self.read_input()
        self.write_output(self.get_result())

    def read_input(self):
        with open("in") as fin:
            self.n = int(fin.readline().strip())
            self.v = [0] + list(map(int, fin.readline().split()))

    def get_result(self) -> SCMAXResult:
        return self.scmax()

    # SCMAX = Subșir Crescător Maximal, implementarea clasică cu DP
    # T = O(n^2)
    # S = O(n)
    def scmax(self) -> SCMAXResult:
        # dp[i] = lungimea celui mai lung subșir (SCMAX) folosind (doar o parte) din primele i elemente din vectorul v și care se termină pe poziția i
        dp = [0] * (self.n + 1)  # Preferăm indexarea de la 1 pentru a fi mai ușor de implementat.
        # prev[i] = poziția elementului precedent din SCMAX care se termină pe poziția i
        prev = [0] * (self.n + 1)

        # Caz de bază
        dp[1] = 1
        prev[1] = 0

        # Caz general
        for i in range(2, self.n + 1):
            dp[i] = 1
            prev[i] = 0
            # Încerc să pun pe v[i] la finalul tuturor soluțiilor disponibile
            # o soluție se termină cu un element v[j].
            for j in range(1, i):
                if self.v[j] < self.v[i] and dp[j] + 1 > dp[i]:
                    dp[i] = dp[j] + 1
                    prev[i] = j

        # Soluția este maximul din vectorul dp.
        pos = max(range(1, self.n + 1), key=lambda i: dp[i])
        sol = dp[pos]

        # Reconstruim SCMAX: v[pos] este ultimul element, înainte v[prev[pos]], etc.
        sequence = []
        i = pos
        while i != 0:
            sequence.append(self.v[i])
            i = prev[i]
        sequence.reverse()
        return SCMAXResult(sol, sequence)

    def write_output(self, result: SCMAXResult) -> None:
        with open("out", "w") as fout:
            fout.write(f"{result.length}\n")
            fout.write(" ".join(map(str, result.sequence)) + "\n")


def main() -> None:
    task = Task()
    task.solve()


# [ATENTIE] NU modifica blocul de mai jos!
if __name__ == "__main__":
    main()
