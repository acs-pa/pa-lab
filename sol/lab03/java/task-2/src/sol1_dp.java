// SPDX-License-Identifier: BSD-3-Clause

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

public class sol1_dp {
    static class Result {
        int len; // rezultat pentru cerinta 1
        ArrayList<Integer> subsequence; // rezultat pentru cerinta 2

        public Result() {
            len = 0;
            subsequence = new ArrayList<>();
        }
    }

    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        int n, m;
        int[] v;
        int[] w;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextInt();
                m = sc.nextInt();
                v = new int[n + 1]; // Adaugare element fictiv - indexare de la 1
                for (int i = 1; i <= n; i++) {
                    v[i] = sc.nextInt();
                }

                w = new int[m + 1]; // Adaugare element fictiv - indexare de la 1
                for (int i = 1; i <= m; i++) {
                    w[i] = sc.nextInt();
                }
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(Result result) {
            try {
                PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE));
                pw.printf("%d\n", result.len);
                for (Integer x : result.subsequence) {
                    pw.printf("%d ", x);
                }
                pw.printf("\n");
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private Result getResult() {
            // TODO: Aflati cel mai lung subsir comun intre v (de lungime n)
            // si w (de lungime m).
            // Se puncteaza separat urmatoarele 2 cerinte:
            // 2.1. Lungimea CMLSC. Rezultatul pentru cerinta aceasta se va pune
            // in ``result.len``.
            // 2.2. Reconstructia CMLSC. Se puncteaza orice subsir comun maximal
            // valid. Solutia pentru aceasta cerinta se va pune in
            // ``result.subsequence``.
            return cmlsc();
        }

        // T = O(n*m) (n*m + L; unde L este lungimea solutiei si L <= min(n,m))
        // S = O(n*m) - stocam tabloul dp
        private Result cmlsc() {
            Result result = new Result();

            // deoarece avem doua dimensiuni in input (doi vectori), o solutie cu o
            // dimensiune (dp[i] = ...)
            // nu poate sa stocheze informatia necesara (asemantor cu RUCSAC)

            // dp[i][j] = LUNGIMEA celui mai lung subsir crescator maximal
            // format cu elementele din vectorii v[1..i] si w[1..j]
            int[][] dp = new int[n + 1][m + 1];
            // dp are dimensiunile n x m - indexare de la 1

            // Caz de baza:
            // dp[0][j] = 0 (daca nu luam element din primul vector)
            // dp[i][0] = 0 (daca nu luam element din al doilea vector)
            // P.S. Aceste cazuri au fost tratate deja, intrucat toate valorile din dp sunt
            // initializate cu 0.

            // Cazul general
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= m; ++j) {
                    // (v[i], w[j]) pot extinde cu 1 o solutie care se termina cel mult pe (i-1, j-1)
                    if (v[i] == w[j]) {
                        dp[i][j] = dp[i - 1][j - 1] + 1;
                    } else {
                        // v[i] poate extinde o solutie, caz in care se cupleaza cu un w[k], k < j (k =
                        // 1...j-1)
                        // w[j] poate extinde o solutie, caz in care se cupleaza cu un v[k], k < i (k =
                        // 1...i-1)
                        dp[i][j] = Math.max(dp[i - 1][j], dp[i][j - 1]);
                    }
                }
            }

            // lungimea ceruta se afla in dp[n][m]
            result.len = dp[n][m];

            // daca nu avem ce reconstitui, ne oprim
            if (result.len == 0) {
                return result;
            }

            // vom reconstitui solutia de la sfarsit catre inceput
            int i = n, j = m;
            int crt = result.len - 1; // crt va tine pozitia pe care urmeaza sa punem o valoare in solutie
            while (i > 0 && j > 0) {
                if (v[i] == w[j]) { // v[i], w[j] a extins candva o solutie
                    result.subsequence.add(v[i]); // adaugam elementul v[i] la solutie
                    crt--;

                    --i; // i,j a extins i-1, j-1 (din recurenta)
                    --j;
                    continue;
                }

                if (dp[i][j] == dp[i - 1][j]) {
                    --i; // ori w[j] a extins singur o solutie
                } else {
                    --j; // ori v[i] a extins singur o solutie
                }
            }

            // inversam solutia
            Collections.reverse(result.subsequence);

            return result;
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
