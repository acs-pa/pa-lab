// SPDX-License-Identifier: BSD-3-Clause

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;

public class SCMAX {
    static class Task {
        public static final String INPUT_FILE = "in";
        public static final String OUTPUT_FILE = "out";

        int n;
        List<Integer> v;

        static class SCMAXResult {
            int length; // lungimea SCMAX
            List<Integer> sequence; // secvența SCMAX
            SCMAXResult(int length, List<Integer> sequence) {
                this.length = length;
                this.sequence = sequence;
            }
        }

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try (Scanner sc = new Scanner(new File(INPUT_FILE))) {
                n = sc.nextInt();
                v = new ArrayList<>(n + 1);
                v.add(0); // index 0 nefolosit; preferăm indexarea de la 1
                for (int i = 0; i < n; i++) {
                    v.add(sc.nextInt());
                }
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private SCMAXResult getResult() {
            return scmax();
        }

        // SCMAX = Subșir Crescător Maximal, implementarea clasică cu DP
        // T = O(n^2)
        // S = O(n)
        private SCMAXResult scmax() {
            // dp[i] = lungimea celui mai lung subșir (SCMAX) folosind (doar o parte) din primele i elemente din vectorul v și care se termină pe poziția i
            int[] dp = new int[n + 1];
            // prev[i] = poziția elementului precedent din SCMAX care se termină pe poziția i
            int[] prev = new int[n + 1];

            // Caz de bază
            dp[1] = 1;
            prev[1] = 0;

            // Caz general
            for (int i = 2; i <= n; i++) {
                dp[i] = 1;
                prev[i] = 0;
                // Încerc să pun pe v[i] la finalul tuturor soluțiilor disponibile
                // o soluție se termină cu un element v[j].
                for (int j = 1; j < i; j++) {
                    if (v.get(j) < v.get(i) && dp[j] + 1 > dp[i]) {
                        dp[i] = dp[j] + 1;
                        prev[i] = j;
                    }
                }
            }

            // Soluția este maximul din vectorul dp.
            int pos = 1;
            for (int i = 2; i <= n; i++) {
                if (dp[i] > dp[pos]) pos = i;
            }
            int sol = dp[pos];

            // Reconstruim SCMAX: v[pos] este ultimul element, înainte v[prev[pos]], etc.
            List<Integer> sequence = new ArrayList<>();
            for (int i = pos; i != 0; i = prev[i]) {
                sequence.add(v.get(i));
            }
            Collections.reverse(sequence);
            return new SCMAXResult(sol, sequence);
        }

        private void writeOutput(SCMAXResult result) {
            try (PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE))) {
                pw.println(result.length);
                for (int i = 0; i < result.sequence.size(); i++) {
                    if (i > 0) pw.print(" ");
                    pw.print(result.sequence.get(i));
                }
                pw.println();
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
