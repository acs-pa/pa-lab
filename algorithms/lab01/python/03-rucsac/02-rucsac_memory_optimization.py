#!/usr/bin/env python3
# SPDX-License-Identifier: BSD-3-Clause


class RucsacResult:
    # value   = valoarea maximă a obiectelor care pot fi puse în rucsac
    # objects = obiectele care pot fi puse în rucsac
    def __init__(self, value: int, objects: list[int]):
        self.value = value
        self.objects = objects


class Task:
    def __init__(self):
        self.n = 0                 # numărul de obiecte
        self.W = 0                 # capacitatea rucsacului
        self.w: list[int] = []     # greutatea fiecărui obiect
        self.p: list[int] = []     # valoarea fiecărui obiect

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

    # Rucsac = Problema rucsacului, varianta cu 2 linii: dp[i] și dp[i-1].
    # T = O(n * W)
    # S = O(W)
    def rucsac(self) -> RucsacResult:
        # Observație: În realitate implementăm aceeași recurență ca în 01-rucsac.cpp,
        # dar folosim doar 2 linii de dp.
        # dp[i][cap] = profitul maxim (profit RUCSAC) obținut folosind
        # (doar o parte) din primele i obiecte și având un rucsac de capacitate maximă cap.

        # prev[cap] = profitul maxim folosind primele i-1 obiecte, capacitate cap
        prev = [0] * (self.W + 1)
        # curr[cap] = profitul maxim folosind primele i obiecte, capacitate cap
        curr = [0] * (self.W + 1)

        for i in range(1, self.n + 1):
            for cap in range(self.W + 1):
                curr[cap] = prev[cap]
                if cap >= self.w[i]:
                    curr[cap] = max(curr[cap], prev[cap - self.w[i]] + self.p[i])
            prev, curr = curr, prev

        # Atenție: în această abordare nu putem reconstitui soluția,
        # deoarece nu păstrăm informațiile despre obiectele care au fost folosite.
        return RucsacResult(prev[self.W], [])

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
