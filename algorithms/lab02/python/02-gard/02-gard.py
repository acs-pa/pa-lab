#!/usr/bin/env python3
# SPDX-License-Identifier: BSD-3-Clause

class Task:
    MOD = 1009
    KMAX = 4

    def __init__(self):
        self.n = 0

    def solve(self):
        self.read_input()
        self.write_output(self.get_result())

    def read_input(self):
        with open("in") as fin:
            self.n = int(fin.readline().strip())

    def get_result(self) -> int:
        return self.garduri_rapide(self.n)

    # C = A * B
    def multiply_matrix(self, A: list[list[int]], B: list[list[int]], C: list[list[int]]) -> None:
        tmp = [[0] * self.KMAX for _ in range(self.KMAX)]

        for i in range(self.KMAX):
            for j in range(self.KMAX):
                total_sum = 0
                for k in range(self.KMAX):
                    total_sum += A[i][k] * B[k][j]
                tmp[i][j] = total_sum % self.MOD

        for i in range(self.KMAX):
            for j in range(self.KMAX):
                C[i][j] = tmp[i][j]

    # R = C^p
    def power_matrix(self, C: list[list[int]], p: int, R: list[list[int]]) -> None:
        tmp = [[0] * self.KMAX for _ in range(self.KMAX)]
        for i in range(self.KMAX):
            tmp[i][i] = 1

        while p != 1:
            if p % 2 == 0:
                self.multiply_matrix(C, C, C)
                p //= 2
            else:
                self.multiply_matrix(tmp, C, tmp)
                p -= 1

        self.multiply_matrix(C, tmp, R)

    # Solutia optimizata
    # T(n) = O(log n)
    # S(n) = O(1)
    def garduri_rapide(self, n: int) -> int:
        if n <= 3:
            return 1
        if n == 4:
            return 2

        C = [[0, 0, 0, 1],
             [1, 0, 0, 0],
             [0, 1, 0, 0],
             [0, 0, 1, 1]]

        self.power_matrix(C, n - 4, C)

        sol = 1 * C[0][3] + 1 * C[1][3] + 1 * C[2][3] + 2 * C[3][3]
        return sol % self.MOD

    def write_output(self, result: int) -> None:
        with open("out", "w") as fout:
            fout.write(f"{result}\n")


def main() -> None:
    task = Task()
    task.solve()


# [ATENTIE] NU modifica blocul de mai jos!
if __name__ == "__main__":
    main()
