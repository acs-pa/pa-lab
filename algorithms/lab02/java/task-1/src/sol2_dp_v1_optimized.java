// SPDX-License-Identifier: BSD-3-Clause

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class sol2_dp_v1_optimized {
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
            return solveDp1N();
        }

        // Solutia 2: DP - optimizata
        // T = O(n)
        // S = O(n)
        // Observam ca in fiecare for cu j, noi extindem o suma
        // Ex. La pasul i - 1 am calculat S1 = dp[1] + .. + dp[i - 2]
        //     La pasul i     am calculat S2 = dp[1] + ...+ dp[i - 2] + dp[i -1]
        // Insa nu am folosit faptul ca S2 = S1 + dp[i - 1]
        // Putem sa folosim sume partiale sa facem o IMPLEMENTARE eficienta
        // cu ACEEASI IDEE!
        private int solveDp1N() {
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

            // sume partiale
            int sum_even = 0; // dp_even[1] + dp_even[2] + ...
            int sum_odd  = 0; //  dp_odd[1] +  dp_odd[2] + ...

            for (int i = 1; i <= n; ++i) {
                if (v[i] % 2 == 0) { // PAR
                    dp_even[i] = 1;  // v[i] singur
                    dp_odd[i]  = 0;  // v[i] NU poate fi singur

                    // v[i] poate fi adauga la
                    // - orice subsir cu suma PARA   => suma PARA
                    // - orice subsir cu suma IMPARA => suma IMPARA

                    dp_even[i] = (dp_even[i] + sum_even) % MOD;
                    dp_odd[i]  = (dp_odd[i] + sum_odd) % MOD;
                } else {             // IMPAR
                    dp_even[i] = 0;  // v[i] NU poate fi singur
                    dp_odd[i]  = 1;  // v[i] singur

                    // v[i] poate fi adauga la
                    // - orice subsir cu suma PARA   => suma IMPARA
                    // - orice subsir cu suma IMPARA => suma PARA
                    dp_even[i] = (dp_even[i] + sum_odd) % MOD;
                    dp_odd[i]  = (dp_odd[i] + sum_even) % MOD;
                }

                // reactulizez sumele partiale
                sum_even = (sum_even + dp_even[i]) % MOD;
                sum_odd  = (sum_odd +  dp_odd[i]) % MOD;
            }

            // raspunsul este R = sum(dp_even[i]), i = 1:n
            // Dar stai.. este in sum_even aceasta suma!
            return sum_even;
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
