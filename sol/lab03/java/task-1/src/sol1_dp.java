// SPDX-License-Identifier: BSD-3-Clause

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class sol1_dp {
    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        int n, S;
        int[] v;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextInt();
                S = sc.nextInt();
                v = new int[n + 1];
                for (int i = 1; i <= n; i++) {
                    v[i] = sc.nextInt();
                }
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(int result) {
            try {
                PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE));
                pw.printf("%d\n", result);
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private int getResult() {
            // TODO: Aflati numarul minim de monede ce poate fi folosit pentru a
            // obtine suma S. Tipurile monedelor sunt stocate in vectorul v, de
            // dimensiune n.
            return getMinCoins();
        }

        // T = O(n * S)
        // S = O(S)
        private int getMinCoins() {
            final int kInf = (int) 1e9; // presupun ca nu am valori mai mari decat 10^9

            // dp[i] = numarul minim de monede cu care pot forma suma i
            int[] dp = new int[S + 1];

            // cazul de baza: suma 0 nu necesita monede
            dp[0] = 0;

            // cazul general: suma s; s se poate descompune ca s = s1 + s2... cine sunt s1
            // si s2?
            // O varianta simpla: s1 = o moneda (oarecare)
            // s = c + (s - c)
            // 1 coin restul
            // dp[s] = min (1 + dp[s-c]) (minimul se face dupa toate valorile posibile
            // pentru c).
            for (int s = 1; s <= S; ++s) {
                // Initial presupunem ca suma s poate fi obtinuta cu un numar infinit de monede
                // (adica nu poate fi obtinuta).
                dp[s] = kInf;

                for (int c : v) {
                    if (s - c >= 0)
                        dp[s] = Math.min(dp[s], 1 + dp[s - c]);
                }
            }

            // s-a putut forma suma S? (dp[S] != kInf)
            // DA: dp[S] este numarul minim de monede cu care am format pe S
            // NU: ghinion.. nu se poate forma suma S
            return (dp[S] != kInf ? dp[S] : -1);
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
