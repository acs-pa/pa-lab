// SPDX-License-Identifier: BSD-3-Clause

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.io.PrintWriter;
import java.util.Scanner;

public class PermutariReference {
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
            bkt(domain, solution, all);
        }

        // Permutări de n elemente, implementare cu referințe.
        // T = O(n * n!)
        // S = O(n)
        private void bkt(ArrayList<Integer> domain, ArrayList<Integer> solution,
                ArrayList<ArrayList<Integer>> all) {
            // După ce am folosit toate elementele din domeniu, putem verifica dacă
            // am găsit o soluție.
            if (domain.size() == 0) {
                if (check(solution)) {
                    all.add(new ArrayList<>(solution));
                }
                return;
            }

            // Încercăm să adăugăm în soluție toate valorile din domeniu, pe rând.
            for (var i = 0; i < domain.size(); i += 1) {
                int tmp = domain.get(i);

                // Adaug elementul curent la potențiala soluție.
                solution.add(tmp);
                // Șterg elementul curent ca să nu îl refolosesc.
                domain.remove(i);

                // Continuăm generarea cu noua stare.
                bkt(domain, solution, all);

                // Refac domeniul și soluția la modul în care erau înainte de
                // apelarea recursivă a backtracking-ului.
                domain.add(i, tmp);
                solution.removeLast();
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
