// SPDX-License-Identifier: BSD-3-Clause

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class sol3_dp_v2 {
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
            return solveDp2N();   
        }

        // Solutia 3: DP - alta idee
        // T = O(n)
        // S = O(n)
        private int solveDp2N() {
            // dp_even[i] = numarul de subsiruri cu suma PARA folosind v[1..i]
            //  dp_odd[i] = numarul de subsiruri cu suma IMPARA folosind v[1..i]
            int[] dp_even = new int[n + 1];
            int[] dp_odd = new int[n + 1];
            // Observatie: Nu spunem daca acele subsiruri se termina sau nu cu v[i]!
            // Raspunsul este: dp_even[n]

            // cazuri de baza
            dp_even[0] = 0;
            dp_odd[0] = 0;

            for (int i = 1; i <= n; ++i) {
                if  (v[i] % 2 == 0)  {      // elementul curent e par
                    // subsirurile cu suma para sunt:
                    // - toate subsirutile cu suma para de dinainte (dp_even[i - 1])
                    // - toate subsirutile cu suma para de dinainte la care adaugam v[i] (dp_even[i - 1])
                    // - subsirul format doar din v[i]
                    dp_even[i] = (dp_even[i - 1] + dp_even[i - 1] + 1) % MOD;

                    // subsirurile cu suma impara sunt:
                    // - toate subsirurile cu suma impara de dinainte (dp_odd[i - 1])
                    // - toate subsirurile cu suma impara de dinainte la care adaugam v[i] (dp_odd[i - 1])
                    dp_odd[i] = (dp_odd[i - 1] + dp_odd[i - 1]) % MOD;
                } else {                    // elementul curent e impar
                    // subsirurile cu suma para sunt:
                    // - toate subsirurile cu suma para de dinainte (dp_even[i - 1])
                    // - toate subsirurile cu suma impara de dinainte la care adaugam v[i] (dp_odd[i - 1])
                    dp_even[i] = (dp_even[i - 1] + dp_odd[i - 1]) % MOD;

                    // subsirurile cu suma impara sunt:
                    // - toate subsirurile cu suma impara de dinainte (dp_odd[i - 1])
                    // - toate subsirurile cu suma para de dinainte la care adaugam v[i] (dp_even[i - 1])
                    // - subsirul format doar din v[i]
                    dp_odd[i] = (dp_odd[i - 1] + dp_even[i - 1] + 1) % MOD;
                }
            }

            // numarul de subsiruri cu SUMA PARA folosind v[1..n]
            return dp_even[n];
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
