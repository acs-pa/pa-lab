// SPDX-License-Identifier: BSD-3-Clause

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class SSM {
    static class Task {
        public static final String INPUT_FILE = "in";
        public static final String OUTPUT_FILE = "out";

        int n; // numărul de elemente din vector
        List<Integer> v; // vectorul de elemente pe care se aplică SSM

        static class SSMResult {
            int value;  // suma subsecvenței de sumă maximă
            int start;  // poziția de început a subsecvenței de sumă maximă
            int end;    // poziția de sfârșit a subsecvenței de sumă maximă
            SSMResult(int value, int start, int end) {
                this.value = value;
                this.start = start;
                this.end = end;
            }
        }

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try (Scanner sc = new Scanner(new File(INPUT_FILE))) {
                n = sc.nextInt();
                v = new ArrayList<>(n);
                for (int i = 0; i < n; i++) {
                    v.add(sc.nextInt());
                }
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private SSMResult getResult() {
            return ssm();
        }

        // SSM = Subsecvența Sumă Maximă, implementarea clasică cu DP
        // T = O(n)
        // S = O(n)
        private SSMResult ssm() {
            // dp[i]= suma subsecvenței de sumă maximă (suma SSM) folosind
            // **doar primele i elemente din vectorul v** și care **se termină pe poziția i**
            int[] dp = new int[n];
            // start[i] = poziția de început a subsecvenței de sumă maximă care se termină pe poziția i
            int[] start = new int[n];

            // Caz de bază
            dp[0] = v.get(0);
            start[0] = 0;

            // Caz general
            for (int i = 1; i < n; i++) {
                if (dp[i - 1] >= 0) {
                    // Extinde la dreapta cu v[i].
                    dp[i] = dp[i - 1] + v.get(i);
                    start[i] = start[i - 1];
                } else {
                    // Începe o nouă secvență.
                    dp[i] = v.get(i);
                    start[i] = i;
                }
            }

            // Soluția este maximul din vectorul dp.
            int pos = 0;
            for (int i = 1; i < n; i++) {
                if (dp[i] > dp[pos]) pos = i;
            }
            return new SSMResult(dp[pos], start[pos], pos);
        }

        private void writeOutput(SSMResult result) {
            try (PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE))) {
                // Afișăm rezultatul cu indexarea de la 1.
                pw.println(result.value + " " + (result.start + 1) + " " + (result.end + 1));
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
