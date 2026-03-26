// SPDX-License-Identifier: BSD-3-Clause

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Scanner;

public class Soricel {
    static class Task {
        public static final String INPUT_FILE = "in";
        public static final String OUTPUT_FILE = "out";

        private ArrayList<ArrayList<Integer>> mat;

        static class Pair {
            int l;
            int r;

            Pair(int l, int r) {
                this.l = l;
                this.r = r;
            }
        }

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try (Scanner sc = new Scanner(new File(INPUT_FILE))) {
                var n = sc.nextInt();

                mat = new ArrayList<ArrayList<Integer>>();
                mat.ensureCapacity(n);
                for (var i = 0; i < n; i += 1) {
                    mat.add(new ArrayList<>());
                    mat.get(i).ensureCapacity(n);
                    for (var j = 0; j < n; j += 1) {
                        mat.get(i).add(sc.nextInt());
                    }
                }
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private ArrayList<ArrayList<Pair>> getResult() {
            var all = new ArrayList<ArrayList<Pair>>();
            solveBkt(all);
            return all;
        }

        private void solveBkt(ArrayList<ArrayList<Pair>> all) {
            // Adăugăm forțat poziția de start în stivă / soluția parțială.
            var current = new ArrayList<Pair>();
            current.add(new Pair(0, 0));
            bkt(current, all);
        }

        // Problema șoricelului = Generarea drumurilor printr-o matrice cu 2 mișcări.
        // T(n) = O(2^(2n))
        // S(n) = O(n)
        private void bkt(ArrayList<Pair> current, ArrayList<ArrayList<Pair>> all) {
            // Dacă am ajuns la destinație, `current` e un drum complet, nu trebuie extins.
            if (current.getLast().l == mat.size() - 1 && current.getLast().r == mat.size() - 1) {
                all.add(new ArrayList<>(current));
                return;
            }

            // Folosim un vector de direcții pentru mișcările disponibile.
            for (var mod : new Pair[] { new Pair(0, 1), new Pair(1, 0) }) {
                var row = current.getLast().l + mod.l;
                var col = current.getLast().r + mod.r;

                // Putem continua drumul dacă nu ieșim din matrice și nu suntem blocați.
                if (inBounds(row, col) && mat.get(row).get(col) == 0) {
                    current.add(new Pair(row, col)); // Punem pe stivă noua poziție.
                    bkt(current, all); // Generăm continuările recursiv.
                    current.removeLast(); // După revenire, scoatem celula din stivă.
                }
            }
        }

        // Verifică dacă o poziție e în interiorul matricei.
        private boolean inBounds(int row, int col) {
            return 0 <= row && row < mat.size() && 0 <= col && col < mat.get(row).size();
        }

        private void writeOutput(ArrayList<ArrayList<Pair>> result) {
            try (PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE))) {
                pw.printf("%d\n", result.size());
                for (var path : result) {
                    var first = true;
                    for (var pair : path) {
                        if (!first) {
                            pw.print("->");
                        }
                        pw.printf("(%d,%d)", pair.l, pair.r);
                        first = false;
                    }
                    pw.print("\n");
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
