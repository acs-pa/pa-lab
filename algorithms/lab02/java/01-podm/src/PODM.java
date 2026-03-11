// SPDX-License-Identifier: BSD-3-Clause

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class PODM {
    static class Task {
        public static final String INPUT_FILE = "in";
        public static final String OUTPUT_FILE = "out";

        int n;                  // numărul de matrici
        int[] d;                // dimensiunile matricilor

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try (Scanner sc = new Scanner(new File(INPUT_FILE))) {
                n = sc.nextInt();
                d = new int[n + 1];
                for (int i = 0; i <= n; i++) {
                    d[i] = sc.nextInt();
                }
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private long getResult() {
            return solvePodm();
        }

        // PODM = Produsul Optim de Matrici, implementarea clasică cu DP
        // T = O(n ^ 3)
        // S = O(n ^ 2) - stocam n x n intregi in tabloul dp
        private long solvePodm() {
            // dp[i][j] = numarul MINIM inmultiri scalare cu codare poate fi calculat produsul
            //            matricial M_i * M_i+1 * ... * M_j
            long[][] dp = new long[n + 1][n + 1];
            
            // Inițializăm tot cu infinit
            for (int i = 0; i <= n; i++) {
                for (int j = 0; j <= n; j++) {
                    dp[i][j] = Long.MAX_VALUE;
                }
            }

            // Cazul de baza 1: nu am ce inmulti
            for (int i = 1; i <= n; ++i) {
                dp[i][i] = 0L;
            }

            // Cazul de baza 2: matrice d[i - 1] x d[i] inmultita cu matrice d[i] x d[i + 1]
            // (matrice pe pozitii consecutive)
            for (int i = 1; i < n; ++i) {
                dp[i][i + 1] = 1L * d[i - 1] * d[i] * d[i + 1];
            }

            // Cazul general:
            // dp[i][j] = min(dp[i][k] + dp[k + 1][j] + d[i - 1] * d[k] * d[j]), k = i : j - 1
            for (int len = 2; len <= n; ++len) { // fixam lungimea intervalului (2, 3, 4, ...)
                for (int i = 1; i + len - 1 <= n; ++i) { // fixam capatul din stanga: i
                    int j = i + len - 1; // capatul din dreapta se deduce: j

                    // Iteram prin indicii dintre capete, spargand sirul de inmultiri in doua (paranteze).
                    for (int k = i; k < j; ++k) {
                        // M_i * ... M_j  = (M_i * .. * M_k) * (M_k+1 *... * M_j)
                        long newSol = dp[i][k] + dp[k + 1][j] + 1L * d[i - 1] * d[k] * d[j];

                        // actualizam solutia daca este mai buna
                        if (newSol < dp[i][j]) {
                            dp[i][j] = newSol;
                        }
                    }
                }
            }

            // Rezultatul se afla in dp[1][n]: Numarul MINIM de inmultiri scalare
            // pe care trebuie sa le facem pentru a obtine produsul M_1 * ... * M_n
            return dp[1][n];
        }

        private void writeOutput(long result) {
            try (PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE))) {
                pw.println(result);
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
