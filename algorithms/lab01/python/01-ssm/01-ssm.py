#!/usr/bin/env python3
# SPDX-License-Identifier: BSD-3-Clause


class SSMResult:
    # value = suma subsecvenței de sumă maximă
    # start = poziția de început a subsecvenței de sumă maximă
    # end   = poziția de sfârșit a subsecvenței de sumă maximă
    def __init__(self, value: int, start: int, end: int):
        self.value = value
        self.start = start
        self.end = end


class Task:
    def __init__(self):
        self.n = 0                 # numărul de elemente din vector
        self.v: list[int] = []     # vectorul de elemente pe care se aplică SSM

    def solve(self):
        self.read_input()
        self.write_output(self.get_result())

    def read_input(self):
        with open("in") as fin:
            self.n = int(fin.readline().strip())
            self.v = list(map(int, fin.readline().split()))

    def get_result(self) -> SSMResult:
        return self.ssm()

    # SSM = Subsecvența Sumă Maximă, implementarea clasică cu DP
    # T = O(n)
    # S = O(n)
    def ssm(self) -> SSMResult:
        # dp[i] = suma subsecvenței de sumă maximă (suma SSM) folosind
        # **doar primele i elemente din vectorul v** și care **se termină pe poziția i**
        dp = [0] * self.n
        # start[i] = poziția de început a subsecvenței de sumă maximă care se termină pe poziția i
        start = [0] * self.n

        # Caz de bază
        dp[0] = self.v[0]
        start[0] = 0

        # Caz general
        for i in range(1, self.n):
            if dp[i - 1] >= 0:
                # Extinde la dreapta cu v[i].
                dp[i] = dp[i - 1] + self.v[i]
                start[i] = start[i - 1]
            else:
                # Începe o nouă secvență.
                dp[i] = self.v[i]
                start[i] = i

        # Soluția este maximul din vectorul dp.
        pos = max(range(self.n), key=lambda i: dp[i])
        return SSMResult(dp[pos], start[pos], pos)

    def write_output(self, result: SSMResult) -> None:
        with open("out", "w") as fout:
            # Afișăm rezultatul cu indexarea de la 1.
            fout.write(f"{result.value} {result.start + 1} {result.end + 1}\n")


def main() -> None:
    task = Task()
    task.solve()


# [ATENTIE] NU modifica blocul de mai jos!
if __name__ == "__main__":
    main()
