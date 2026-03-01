#!/usr/bin/env python3
# SPDX-License-Identifier: BSD-3-Clause


class SSMResult:
    # value = suma subsecvenței de sumă maximă
    # start = poziția de început a subsecvenței de sumă maximă
    # end = poziția de sfârșit a subsecvenței de sumă maximă
    def __init__(self, value: int, start: int, end: int):
        self.value = value
        self.start = start
        self.end = end


class Task:
    def __init__(self):
        self.n = 0
        self.v: list[int] = []

    def solve(self):
        self.read_input()
        self.write_output(self.get_result())

    def read_input(self):
        with open("in") as fin:
            self.n = int(fin.readline().strip())
            self.v = list(map(int, fin.readline().split()))

    def get_result(self) -> SSMResult:
        return self.ssm()

    # SSM = Subsecvența Sumă Maximă, varianta cu O(1) memorie suplimentară
    # Un singur pas: menținem doar suma curentă și cea mai bună secvență.
    # T = O(n)
    # S = O(1) (putem folosi doar variabile locale, nu folosim vectori dp/start)
    def ssm(self) -> SSMResult:
        # Observație: În realitate implementăm aceeași recurență ca în 01-ssm.cpp.
        # dp[i]= suma subsecvenței de sumă maximă (suma SSM) folosind
        # **doar primele i elemente din vectorul v** și care **se termină pe poziția i**

        # Caz de bază
        best_sum = self.v[0]
        best_start = 0
        best_end = 0
        curr_sum = self.v[0]
        curr_start = 0

        # Caz general
        for i in range(1, self.n):
            if curr_sum >= 0:
                # Extinde la dreapta cu v[i].
                curr_sum += self.v[i]
            else:
                # Începe o nouă secvență.
                curr_sum = self.v[i]
                curr_start = i
            curr_end = i
            if curr_sum > best_sum:
                best_sum, best_start, best_end = curr_sum, curr_start, curr_end
            elif curr_sum == best_sum:
                # Conform enunțului: indice de început cel mai mic, la egalitate cea mai scurtă.
                if curr_start < best_start or (curr_start == best_start and curr_end < best_end):
                    best_start, best_end = curr_start, curr_end

        # Soluția este cea reținută în best_*.
        return SSMResult(best_sum, best_start, best_end)

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
