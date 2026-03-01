// SPDX-License-Identifier: BSD-3-Clause

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;

public class SCMAXOptimizedWithBinarySearch {
    static class Task {
        public static final String INPUT_FILE = "in";
        public static final String OUTPUT_FILE = "out";

        int n;                       // numărul de elemente din vector
        List<Integer> v;             // vectorul de elemente pe care se aplică SCMAX

        static class SCMAXResult {
            int length;              // lungimea SCMAX
            List<Integer> sequence;  // secvența SCMAX
            SCMAXResult(int length, List<Integer> sequence) {
                this.length = length;
                this.sequence = sequence;
            }
        }

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try (Scanner sc = new Scanner(new File(INPUT_FILE))) {
                n = sc.nextInt();
                v = new ArrayList<>(n + 1);
                v.add(0);
                for (int i = 0; i < n; i++) {
                    v.add(sc.nextInt());
                }
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private SCMAXResult getResult() {
            return scmaxBinarySearch();
        }

        // SCMAX = Subșir Crescător Maximal, varianta O(n log n) cu binary search
        // Menținem pentru fiecare lungime L cea mai mică valoare finală a unui subșir crescător de lungime L.
        // T = O(n log n)
        // S = O(n)
        private SCMAXResult scmaxBinarySearch() {
            // dp[l] = valoarea minimă a ultimului element dintr-un subșir crescător de lungime l+1
            List<Integer> dp = new ArrayList<>();
            // dp_idx[l] = indicele în v al acelui element (pentru reconstrucție)
            List<Integer> dpIdx = new ArrayList<>();
            int[] prev = new int[n + 1];

            // Caz de bază: primul element
            dp.add(v.get(1));
            dpIdx.add(1);
            prev[1] = 0;

            // Caz general: pentru fiecare v[i] căutăm binar unde să extindem sau să înlocuim.
            for (int i = 2; i <= n; i++) {
                int p = Collections.binarySearch(dp, v.get(i));
                if (p < 0) p = -(p + 1);

                if (p == dp.size()) {
                    // Extindem: subșir nou de lungime maximă
                    dp.add(v.get(i));
                    dpIdx.add(i);
                    prev[i] = dpIdx.get(p - 1);
                } else {
                    // Înlocuim: obținem o „coadă” mai mică pentru lungimea p+1
                    dp.set(p, v.get(i));
                    dpIdx.set(p, i);
                    prev[i] = (p > 0) ? dpIdx.get(p - 1) : 0;
                }
            }

            int sol = dp.size();

            // Reconstruim subșirul: începem de la ultimul element al LIS-ului de lungime maximă
            List<Integer> sequence = new ArrayList<>();
            for (int i = dpIdx.get(sol - 1); i != 0; i = prev[i]) {
                sequence.add(v.get(i));
            }
            Collections.reverse(sequence);
            return new SCMAXResult(sol, sequence);
        }

        private void writeOutput(SCMAXResult result) {
            try (PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE))) {
                pw.println(result.length);
                for (int i = 0; i < result.sequence.size(); i++) {
                    if (i > 0) pw.print(" ");
                    pw.print(result.sequence.get(i));
                }
                pw.println();
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
