// SPDX-License-Identifier: BSD-3-Clause

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Gard {
    static class Task {
        public static final String INPUT_FILE = "in";
        public static final String OUTPUT_FILE = "out";

        int n;
        static final int MOD = 1009;
        static final int KMAX = 4;

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

        private int getResult() {
            return garduriRapide(n);
        }

        // C = A * B
        private void multiplyMatrix(int[][] A, int[][] B, int[][] C) {
            int[][] tmp = new int[KMAX][KMAX];

            for (int i = 0; i < KMAX; ++i) {
                for (int j = 0; j < KMAX; ++j) {
                    long sum = 0;

                    for (int k = 0; k < KMAX; ++k) {
                        sum += 1L * A[i][k] * B[k][j];
                    }

                    tmp[i][j] = (int)(sum % MOD);
                }
            }

            for (int i = 0; i < KMAX; ++i) {
                System.arraycopy(tmp[i], 0, C[i], 0, KMAX);
            }
        }

        // R = C^p
        private void powerMatrix(int[][] C, int p, int[][] R) {
            int[][] tmp = new int[KMAX][KMAX];
            for (int i = 0; i < KMAX; ++i) {
                for (int j = 0; j < KMAX; ++j) {
                    tmp[i][j] = (i == j) ? 1 : 0;
                }
            }

            while (p != 1) {
                if (p % 2 == 0) {
                    multiplyMatrix(C, C, C);
                    p /= 2;
                } else {
                    multiplyMatrix(tmp, C, tmp);
                    --p;
                }
            }

            multiplyMatrix(C, tmp, R);
        }

        /**
         * Solutia optimizata
         * T(n) = O(log n)
         * S(n) = O(1)
         */
        private int garduriRapide(int n) {
            if (n <= 3) return 1;
            if (n == 4) return 2;

            int[][] C = {{0, 0, 0, 1}, {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 1}};
            
            powerMatrix(C, n - 4, C);

            int sol = 1 * C[0][3] + 1 * C[1][3] + 1 * C[2][3] + 2 * C[3][3];
            return sol % MOD;
        }

        private void writeOutput(int result) {
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
