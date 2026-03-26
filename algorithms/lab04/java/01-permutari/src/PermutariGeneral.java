// SPDX-License-Identifier: BSD-3-Clause

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;
import java.util.ArrayList;

public class PermutariGeneral {
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

        void solveBkt(ArrayList<ArrayList<Integer>> all) {
            var domain = new ArrayList<Integer>();
            for (var i = 1; i <= n; i += 1) {
                domain.add(i);
            }

            bkt(domain, new ArrayList<>(), all);
        }

        void bkt(ArrayList<Integer> domain, ArrayList<Integer> solution,
                ArrayList<ArrayList<Integer>> all) {
            if (domain.size() == 0) {
                if (check(solution)) {
                    all.add(new ArrayList<>(solution));
                }
                return;
            }

            for (var i = 0; i < domain.size(); i += 1) {
                // Creăm o soluție nouă identică cu cea de la pasul curent, și o
                // modificăm.
                var new_solution = new ArrayList<>(solution);
                new_solution.add(domain.get(i));

                // Ștergem elementul ales din domeniu. Creăm o copie a domeniului.
                var new_domain = new ArrayList<>(domain);
                new_domain.remove(i);

                // Continuăm generarea cu noua stare.
                bkt(new_domain, new_solution, all);
            }
        }

        // Deoarece numerele sunt șterse din domeniu odată ce sunt folosite, soluția
        // generată este garantată să nu conțină duplicate. Astfel, atunci când
        // domeniul ajunge vid, soluția este intotdeauna corectă.
        private boolean check(ArrayList<Integer> solution) {
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
