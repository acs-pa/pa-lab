// SPDX-License-Identifier: BSD-3-Clause

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Rucsac {
    static class Task {
        public static final String INPUT_FILE = "in";
        public static final String OUTPUT_FILE = "out";

        int n; // numărul de obiecte
        int W; // capacitatea rucsacului
        List<Integer> w; // greutatea fiecărui obiect
        List<Integer> p; // valoarea fiecărui obiect

        static class RucsacResult {
            int value; // valoarea maximă a obiectelor care pot fi puse în rucsac
            List<Integer> objects; // obiectele care pot fi puse în rucsac
            RucsacResult(int value, List<Integer> objects) {
                this.value = value;
                this.objects = objects;
            }
        }

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try (Scanner sc = new Scanner(new File(INPUT_FILE))) {
                n = sc.nextInt();
                W = sc.nextInt();
                w = new ArrayList<>(n + 1);
                p = new ArrayList<>(n + 1);
                w.add(0);
                p.add(0);
                for (int i = 0; i < n; i++) {
                    w.add(sc.nextInt());
                    p.add(sc.nextInt());
                }
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private RucsacResult getResult() {
            return rucsac();
        }

        // Rucsac = Problema rucsacului, implementarea clasică cu DP
        // T = O(n * W)
        // S = O(n * W)
        private RucsacResult rucsac() {
            // dp[i][cap] = profitul maxim (profit RUCSAC) obținut folosind
            // (doar o parte) din primele i obiecte și având un rucsac de capacitate maximă cap.
            int[][] dp = new int[n + 1][W + 1];

            // Caz de bază (implicit dp[0][cap] = 0)

            // Caz general
            for (int i = 1; i <= n; i++) {
                for (int cap = 0; cap <= W; cap++) {
                    // Nu folosesc obiectul i => e soluția de la pasul i - 1
                    dp[i][cap] = dp[i - 1][cap];
                    // Folosesc obiectul i, deci trebuie să rezerv w[i] unități în rucsac.
                    // Înseamnă că înainte trebuie să ocup maxim cap - w[i] unități.
                    if (cap >= w.get(i)) {
                        int solAux = dp[i - 1][cap - w.get(i)] + p.get(i);
                        dp[i][cap] = Math.max(dp[i][cap], solAux);
                    }
                }
            }
            return new RucsacResult(dp[n][W], reconstructSolution(dp));
        }

        // Reconstruim soluția
        private List<Integer> reconstructSolution(int[][] dp) {
            List<Integer> objects = new ArrayList<>();
            int cap = W;
            for (int i = n; i > 0; i--) {
                if (dp[i][cap] != dp[i - 1][cap]) {
                    objects.add(i);
                    cap -= w.get(i);
                }
            }
            return objects;
        }

        private void writeOutput(RucsacResult result) {
            try (PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE))) {
                pw.println(result.value);
                // Nu se printează obiectele, ci doar valoarea maximă a profitului.
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
    }

    // [ATENTIE] NU modifica funcția main!
    public static void main(String[] args) {
        new Task().solve();
    }
}
