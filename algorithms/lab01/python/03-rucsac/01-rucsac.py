#!/usr/bin/env python3
# SPDX-License-Identifier: BSD-3-Clause


class RucsacResult:
    # value = valoarea maximă a obiectelor care pot fi puse în rucsac
    # objects = obiectele care pot fi puse în rucsac
    def __init__(self, value: int, objects: list[int]):
        self.value = value
        self.objects = objects


class Task:
    def __init__(self):
        self.n = 0  # numărul de obiecte
        self.W = 0  # capacitatea rucsacului
        self.w: list[int] = []  # greutatea fiecărui obiect
        self.p: list[int] = []  # valoarea fiecărui obiect

    def solve(self):
        self.read_input()
        self.write_output(self.get_result())

    def read_input(self):
        with open("in") as fin:
            line = fin.readline().split()
            self.n = int(line[0])
            self.W = int(line[1])
            self.w = [0]
            self.p = [0]
            for _ in range(self.n):
                line = fin.readline().split()
                self.w.append(int(line[0]))
                self.p.append(int(line[1]))

    def get_result(self) -> RucsacResult:
        return self.rucsac()

    # Rucsac = Problema rucsacului, implementarea clasică cu DP
    # T = O(n * W)
    # S = O(n * W)
    def rucsac(self) -> RucsacResult:
        # dp[i][cap] = profitul maxim (profit RUCSAC) obținut folosind
        # (doar o parte) din primele i obiecte și având un rucsac de capacitate maximă cap.
        dp = [[0] * (self.W + 1) for _ in range(self.n + 1)]
        # Caz de bază
        for cap in range(self.W + 1):
            dp[0][cap] = 0
        # Caz general
        for i in range(1, self.n + 1):
            for cap in range(self.W + 1):
                # Nu folosesc obiectul i => e soluția de la pasul i - 1
                dp[i][cap] = dp[i - 1][cap]
                # Folosesc obiectul i, deci trebuie să rezerv w[i] unități în rucsac.
                # Înseamnă că înainte trebuie să ocup maxim cap - w[i] unități.
                if cap >= self.w[i]:
                    sol_aux = dp[i - 1][cap - self.w[i]] + self.p[i]
                    dp[i][cap] = max(dp[i][cap], sol_aux)
        return RucsacResult(dp[self.n][self.W], self.reconstruct_solution(dp))

    # Reconstruim soluția
    def reconstruct_solution(self, dp: list[list[int]]) -> list[int]:
        objects = []
        cap = self.W
        for i in range(self.n, 0, -1):
            if dp[i][cap] != dp[i - 1][cap]:
                objects.append(i)
                cap -= self.w[i]
        return objects

    def write_output(self, result: RucsacResult) -> None:
        with open("out", "w") as fout:
            fout.write(f"{result.value}\n")
            # Nu se printează obiectele, ci doar valoarea maximă a profitului.


def main() -> None:
    task = Task()
    task.solve()


# [ATENTIE] NU modifica blocul de mai jos!
if __name__ == "__main__":
    main()
