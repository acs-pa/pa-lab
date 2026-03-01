// SPDX-License-Identifier: BSD-3-Clause

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class SSMMemoryOptimization {
    static class Task {
        public static final String INPUT_FILE = "in";
        public static final String OUTPUT_FILE = "out";

        int n;
        List<Integer> v;

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

        // SSM = Subsecvența Sumă Maximă, varianta cu O(1) memorie suplimentară
        // Un singur pas: menținem doar suma curentă și cea mai bună secvență.
        // T = O(n)
        // S = O(1) (putem folosi doar variabile locale, nu folosim vectori dp/start)
        private SSMResult ssm() {
            // Observație: În realitate implementăm aceeași recurență ca în 01-ssm.cpp.
            // dp[i]= suma subsecvenței de sumă maximă (suma SSM) folosind
            // **doar primele i elemente din vectorul v** și care **se termină pe poziția i**

            // Caz de bază
            int bestSum = v.get(0), bestStart = 0, bestEnd = 0;
            int currSum = v.get(0), currStart = 0;

            // Caz general
            for (int i = 1; i < n; i++) {
                if (currSum >= 0) {
                    // Extinde la dreapta cu v[i].
                    currSum += v.get(i);
                } else {
                    // Începe o nouă secvență.
                    currSum = v.get(i);
                    currStart = i;
                }
                int currEnd = i;
                if (currSum > bestSum) {
                    bestSum = currSum;
                    bestStart = currStart;
                    bestEnd = currEnd;
                } else if (currSum == bestSum) {
                    // Conform enunțului: indice de început cel mai mic, la egalitate cea mai scurtă.
                    if (currStart < bestStart
                            || (currStart == bestStart && currEnd < bestEnd)) {
                        bestStart = currStart;
                        bestEnd = currEnd;
                    }
                }
            }

            // Soluția este cea reținută în best_*.
            return new SSMResult(bestSum, bestStart, bestEnd);
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
