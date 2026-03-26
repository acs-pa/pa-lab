// SPDX-License-Identifier: BSD-3-Clause

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashSet;
import java.io.PrintWriter;
import java.util.Scanner;

public class PermutariPruning {
    static class Task {
        public static final String INPUT_FILE = "in";
        public static final String OUTPUT_FILE = "out";

        int n;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try (Scanner sc = new Scanner(new File(INPUT_FILE))) {
                n = sc.nextInt();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private ArrayList<ArrayList<Integer>> getResult() {
            var all = new ArrayList<ArrayList<Integer>>();
            solveBkt(all);
            return all;
        }

        private void solveBkt(ArrayList<ArrayList<Integer>> all) {
            // La începutul generării putem alege din fiecare număr între 1 și n.
            var domain = new ArrayList<Integer>();
            for (var i = 1; i <= n; i += 1) {
                domain.add(i);
            }

            var solution = new ArrayList<Integer>();

            // Construim permutările prin backtracking.
            bkt(0, n, domain, solution, new HashSet<>(), all);
        }

        // Permutări de n elemente, implementare cu pruning.
        // T = O(n * n!)
        // S = O(n)
        private void bkt(int step, int stop, ArrayList<Integer> domain, ArrayList<Integer> solution,
                HashSet<Integer> visited,
                ArrayList<ArrayList<Integer>> all) {
            // După ce am folosit toate elementele din domeniu, putem verifica dacă
            // am găsit o soluție.
            if (step == stop) {
                if (check(solution)) {
                    all.add(new ArrayList<>(solution));
                }
                return;
            }

            // Adaugam in solutie fiecare element din domeniu care *NU* a fost
            // vizitat deja renuntand astfel la nevoia de a verifica duplicatele la
            // final prin functia "check()"
            for (var i = 0; i < domain.size(); i += 1) {
                if (!visited.contains(domain.get(i))) {
                    // Il marcam ca vizitat si taiem eventuale expansiuni
                    // nefolositoare viitoare (ex: daca il adaug in solutie pe 3
                    // nu voi mai avea niciodata nevoie sa il mai adaug pe 3 in
                    // continuare)
                    visited.add(domain.get(i));
                    // Adaugam elementul curent in solutie pe pozitia pasului
                    // curent (step)
                    solution.add(domain.get(i));
                    // Apelam recursiv backtracking pentru pasul urmator
                    bkt(step + 1, stop, domain, solution, visited, all);
                    // Stergem vizitarea elementului curent (ex: pentru N = 3,
                    // dupa ce la pasul "step = 0" l-am pus pe 1 pe prima
                    // pozitie in solutie si am continuat recursiv pana am ajuns
                    // la solutiile {1, 2, 3} si {1, 3, 2}, ne dorim sa il punem
                    // pe 2 pe prima pozitie in solutie si sa continuam recursiv
                    // pentru a ajunge la solutiile {2, 1, 3} etc.)
                    visited.remove(domain.get(i));
                    solution.removeLast();
                }
            }
        }

        // Deoarece numerele sunt șterse din domeniu odată ce sunt folosite, soluția
        // generată este garantată să nu conțină duplicate. Astfel, atunci când
        // domeniul ajunge vid, soluția este intotdeauna corectă.
        boolean check(ArrayList<Integer> solution) {
            return true;
        }

        private void writeOutput(ArrayList<ArrayList<Integer>> result) {
            try (PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE))) {
                pw.printf("%d\n", result.size());
                for (var perm : result) {
                    for (var num : perm) {
                        pw.printf("%d ", num);
                    }
                    pw.printf("\n");
                }
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
    }

    // [ATENTIE] NU modifica functia main!
    public static void main(String[] args) {
        new Task().solve();
    }
}
