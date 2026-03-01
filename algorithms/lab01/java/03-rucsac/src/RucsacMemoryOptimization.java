// SPDX-License-Identifier: BSD-3-Clause

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class RucsacMemoryOptimization {
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

        // Rucsac = Problema rucsacului, varianta cu 2 linii: dp[i] și dp[i-1].
        // T = O(n * W)
        // S = O(W)
        private RucsacResult rucsac() {
            // Observație: În realitate implementăm aceeași recurență ca în 01-rucsac.cpp,
            // dar folosim doar 2 linii de dp.
            // dp[i][cap] = profitul maxim (profit RUCSAC) obținut folosind
            // (doar o parte) din primele i obiecte și având un rucsac de capacitate maximă cap.

            // prev[cap] = profitul maxim folosind primele i-1 obiecte, capacitate cap
            int[] prev = new int[W + 1];
            // curr[cap] = profitul maxim folosind primele i obiecte, capacitate cap
            int[] curr = new int[W + 1];

            for (int i = 1; i <= n; i++) {
                for (int cap = 0; cap <= W; cap++) {
                    curr[cap] = prev[cap];
                    if (cap >= w.get(i)) {
                        curr[cap] = Math.max(curr[cap], prev[cap - w.get(i)] + p.get(i));
                    }
                }
                int[] tmp = prev;
                prev = curr;
                curr = tmp;
            }

            // Atenție: în această abordare nu putem reconstitui soluția,
            // deoarece nu păstrăm informațiile despre obiectele care au fost folosite.
            return new RucsacResult(prev[W], new ArrayList<>());
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
