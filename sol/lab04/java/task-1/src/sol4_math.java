// SPDX-License-Identifier: BSD-3-Clause

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class sol4_math {
    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        int n;
        int[] v;

        private final static int MOD = 1000000007;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextInt();
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
            // TODO: Aflati numarul de subsiruri (ale sirului stocat in v,
            // indexat de la 1 la n), nevide cu suma numerelor para.
            // Rezultatul se va intoarce modulo MOD (1000000007).

            // Sunt prezentate 4 solutii.
            // Oricare dintre dinamici s-au punctat cu 10 la laborator.
            // La teme/test va trebui sa alegeti pe cea care intra in timp!
            // (Daca intra toate, atunci alegeti una. Ideal ar fi sa fie cea mai rapida!)
            return solveMath();
        }

        // Solutia 4: math
        // - daca toate numerele sunt pare: 2^n - 1
        // -                        altfel: 2^(n-1) - 1
        // T = O(n) - tot parcurgem vectorul sa vedem daca toate sunt pare
        // S = O(1) - nu stocam tabloul dp (inputul nu a fost luat in calcul)
        private int solveMath() {
            boolean all_even = true;
            for (int i = 1; i <= n; ++i) {
                all_even = all_even && (v[i] % 2 == 0);
            }

            int sol = (all_even ? logPow(2, n) - 1 : logPow(2, n - 1) - 1);
            sol = (sol + MOD) % MOD; // atentie! am scazut 1, expresia poate fi negativa
                                       // Testele nu surprind acest caz. La teme/test trebuie sa fiti atenti!

            return sol;
        }

        // returneaza base ^ exp % MOD
        int logPow(int base, int exp) {
            if (exp == 0) {
                return 1;
            }

            int tmp = 1;
            while (exp != 1) {
                if (exp % 2 == 0) {
                    base = (int) ((1L * base * base) % MOD);
                    exp /= 2;
                } else {
                    tmp = (int) ((1L * tmp * base) % MOD);
                    exp--;
                }
            }

            return (int) ((1L * tmp * base) % MOD);
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
