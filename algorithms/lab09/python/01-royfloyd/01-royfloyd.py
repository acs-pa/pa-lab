# SPDX-License-Identifier: BSD-3-Clause


class Task:
    def __init__(self) -> None:
        # numarul maxim de noduri
        self.NMAX = 105

        # n = numar de noduri
        self.n = 0

        # w[x][y] = costul muchiei de la x la y: (x, y, w[x][y])
        # (w[x][y] = 0 - muchia lipseste)
        #
        # In aceasta problema, costurile sunt strict pozitive.
        self.w: list[list[int]] = []

    def solve(self) -> None:
        self.read_input()
        self.write_output(self.compute())

    def read_input(self) -> None:
        with open("in", "r") as fin:
            tokens = fin.read().split()
            if not tokens:
                return

            self.n = int(tokens[0])
            self.w = [[0] * (self.n + 1) for _ in range(self.n + 1)]

            idx = 1
            for x in range(1, self.n + 1):
                for y in range(1, self.n + 1):
                    self.w[x][y] = int(tokens[idx])
                    idx += 1

    def compute(self) -> list[list[int]]:
        return self.royfloyd()

    def royfloyd(self) -> list[list[int]]:
        d = [[0] * (self.n + 1) for _ in range(self.n + 1)]

        # Initializez matricea d folosind matricea w.
        for i in range(1, self.n + 1):
            for j in range(1, self.n + 1):
                d[i][j] = self.w[i][j]

        # Aplic Roy-Floyd:
        for k in range(1, self.n + 1):
            # Fixez nodul intermediar, k.
            for i in range(1, self.n + 1):
                for j in range(1, self.n + 1):
                    if i == j:
                        continue

                    # Daca nu exista drum de la i la k sau de la k la j, sarim peste.
                    if d[i][k] == 0 or d[k][j] == 0:
                        continue

                    # Fixez cele doua capete ale drumului pe care le updatez (i, j).
                    # Daca nu am drum sau daca obtin un cost mai mic intre i, j, updatez.
                    if d[i][j] == 0 or d[i][k] + d[k][j] < d[i][j]:
                        d[i][j] = d[i][k] + d[k][j]

        return d

    def write_output(self, d: list[list[int]]) -> None:
        with open("out", "w") as fout:
            for x in range(1, self.n + 1):
                row = " ".join(str(d[x][y]) for y in range(1, self.n + 1))
                fout.write(row + " \n")


def main() -> None:
    task = Task()
    task.solve()


# [ATENTIE] NU modifica functia main!
if __name__ == "__main__":
    main()
