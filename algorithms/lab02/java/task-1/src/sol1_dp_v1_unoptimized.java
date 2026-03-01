// SPDX-License-Identifier: BSD-3-Clause

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class sol1_dp_v1_unoptimized {
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
            return solveDp1Nn();
        }

        // Solutia 1: DP - neoptimizata
        // T = O(n ^ 2)
        // S = O(n)
        private int solveDp1Nn() {
            // dp_even[i] = numarul de subsiruri cu suma PARA folosind v[1..i]
            //              SI care se termina cu v[i]
            // dp_odd[i] = numarul de subsiruri cu suma IMPARA folosind v[1..i]
            //              SI care se termina cu v[i]

            int[] dp_even = new int[n + 1];
            int[] dp_odd = new int[n + 1];
            // Raspunsul este: suma(dp_even[i])

            // cazuri de baza
            dp_even[0] = 0;
            dp_odd[0] = 0;

            for (int i = 1; i <= n; ++i) {
                if (v[i] % 2 == 0) { // PAR
                    dp_even[i] = 1;  // v[i] singur
                    dp_odd[i]  = 0;  // v[i] NU poate fi singur

                    // v[i] poate fi adaugat la
                    // - orice subsir cu suma PARA   => suma PARA
                    // - orice subsir cu suma IMPARA => suma IMPARA
                    for (int j = 1; j < i; ++j) {
                        dp_even[i] = (dp_even[i] + dp_even[j]) % MOD;
                        dp_odd[i]  = (dp_odd[i] + dp_odd[j]) % MOD;
                    }
                } else {             // IMPAR
                    dp_even[i] = 0;  // v[i] NU poate fi singur
                    dp_odd[i]  = 1;  // v[i] singur

                    // v[i] poate fi adauga la
                    // - orice subsir cu suma PARA   => suma IMPARA
                    // - orice subsir cu suma IMPARA => suma PARA
                    for (int j = 1; j < i; ++j) {
                        dp_even[i] = (dp_even[i] + dp_odd[j]) % MOD;
                        dp_odd[i]  = (dp_odd[i] + dp_even[j]) % MOD;
                    }
                }
            }

            // raspunsul este R = sum(dp_even[i]), i = 1:n
            // dp_even[1] = numarul de subsiruri cu sumara para care se termina cu v[1]
            // dp_even[2] = numarul de subsiruri cu sumara para care se termina cu v[2]
            // ...
            // dp_even[i] = numarul de subsiruri cu sumara para care se termina cu v[i]
            // ...
            // Numarul total de subsiruri cu suma para se obtine prin insumare

            int sol = 0;
            for (int i = 1; i <= n; ++i) {
                sol = (sol + dp_even[i]) % MOD;
            }

            return sol;
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
