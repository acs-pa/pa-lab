#!/usr/bin/env python3
# SPDX-License-Identifier: BSD-3-Clause


class Task:
    def __init__(self):
        self.n = 0

    def solve(self):
        self.read_input()
        self.write_output(self.get_result())

    def read_input(self) -> None:
        with open("in") as fin:
            self.n = int(fin.read())

    def get_result(self) -> list[list[int]]:
        all_res = []
        self.solve_bkt(all_res)
        return all_res

    def solve_bkt(self, all_res: list[list[int]]) -> None:
        # La începutul generării putem alege din fiecare număr între 1 și n.
        domain = list(range(1, self.n + 1))

        solution = []
        visited = set()

        # Construim permutările prin backtracking.
        self.bkt(0, self.n, domain, solution, visited, all_res)

    # Permutări de n elemente, implementare cu pruning.
    # T = O(n * n!)
    # S = O(n)
    def bkt(
        self,
        step: int,
        stop: int,
        domain: list[int],
        solution: list[int],
        visited: set[int],
        all_res: list[list[int]],
    ) -> None:
        # După ce am folosit toate elementele din domeniu, putem verifica dacă
        # am găsit o soluție.
        if step == stop:
            if self.check(solution):
                all_res.append(solution[:])
            return

        # Adaugam in solutie fiecare element din domeniu care *NU* a fost
        # vizitat deja renuntand astfel la nevoia de a verifica duplicatele la
        # final prin functia "check()"
        for i, num in enumerate(domain):
            if num not in visited:
                # Il marcam ca vizitat si taiem eventuale expansiuni nefolositoare viitoare (ex: daca il adaug in
                # solutie pe 3 nu voi mai avea niciodata nevoie sa il mai adaug pe 3 in continuare)
                visited.add(num)
                # Adaugam elementul curent in solutie pe pozitia pasului curent (step)
                solution.append(num)
                # Apelam recursiv backtracking pentru pasul urmator
                self.bkt(step + 1, stop, domain, solution, visited, all_res)
                # Stergem vizitarea elementului curent (ex: pentru N = 3, dupa
                # ce la pasul "step = 0" l-am pus pe 1 pe prima pozitie in
                # solutie si am continuat recursiv pana am ajuns la solutiile
                # {1, 2, 3} si {1, 3, 2}, ne dorim sa il punem pe 2 pe prima
                # pozitie in solutie si sa continuam recursiv pentru a ajunge
                # la solutiile {2, 1, 3} etc.)
                visited.remove(num)
                solution.pop()

    # Deoarece numerele sunt șterse din domeniu odată ce sunt folosite, soluția
    # generată este garantată să nu conțină duplicate. Astfel, atunci când
    # domeniul ajunge vid, soluția este intotdeauna corectă.
    def check(self, solution: list[int]) -> bool:
        return True

    def write_output(self, result: list[list[int]]) -> None:
        with open("out", "w") as fout:
            fout.write(f"{len(result)}\n")
            for perm in result:
                fout.write(" ".join(map(str, perm)) + "\n")


def main() -> None:
    task = Task()
    task.solve()


# [ATENTIE] NU modifica blocul de mai jos
if __name__ == "__main__":
    main()
