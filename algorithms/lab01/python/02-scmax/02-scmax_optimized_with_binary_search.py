#!/usr/bin/env python3
# SPDX-License-Identifier: BSD-3-Clause

import bisect


class SCMAXResult:
    # length = lungimea SCMAX
    # sequence = secvența SCMAX
    def __init__(self, length: int, sequence: list[int]):
        self.length = length
        self.sequence = sequence


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
            self.v = [0] + list(map(int, fin.readline().split()))

    def get_result(self) -> SCMAXResult:
        return self.scmax_binary_search()

    # SCMAX = Subșir Crescător Maximal, varianta O(n log n) cu binary search
    # Menținem pentru fiecare lungime L cea mai mică valoare finală a unui subșir crescător de lungime L.
    # T = O(n log n)
    # S = O(n)
    def scmax_binary_search(self) -> SCMAXResult:
        # dp[l] = valoarea minimă a ultimului element dintr-un subșir crescător de lungime l+1
        dp: list[int] = []
        # dp_idx[l] = indicele în v al acelui element (pentru reconstrucție)
        dp_idx: list[int] = []
        prev = [0] * (self.n + 1)

        # Caz de bază: primul element
        dp.append(self.v[1])
        dp_idx.append(1)
        prev[1] = 0

        # Caz general: pentru fiecare v[i] căutăm binar unde să extindem sau să înlocuim.
        for i in range(2, self.n + 1):
            p = bisect.bisect_left(dp, self.v[i])
            if p == len(dp):
                # Extindem: subșir nou de lungime maximă
                dp.append(self.v[i])
                dp_idx.append(i)
                prev[i] = dp_idx[p - 1]
            else:
                # Înlocuim: obținem o „coadă” mai mică pentru lungimea p+1
                dp[p] = self.v[i]
                dp_idx[p] = i
                prev[i] = dp_idx[p - 1] if p > 0 else 0

        sol = len(dp)
        # Reconstruim subșirul: începem de la ultimul element al LIS-ului de lungime maximă
        sequence = []
        i = dp_idx[sol - 1]
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
