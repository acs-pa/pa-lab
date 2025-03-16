// SPDX-License-Identifier: BSD-3-Clause

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class sol1_greedy {
    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        int n, m;
        int[] dist;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextInt();
                m = sc.nextInt();
                dist = new int[n + 1];
                dist[0] = 0;
                for (int i = 1; i <= n; i++) {
                    dist[i] = sc.nextInt();
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
            // TODO: Aflati numarul minim de opriri necesare pentru
            // a ajunge la destinatie.
            return gas_station();
        }

        // T = O(n)
        // S = O(1)
        int gas_station() {
            int sol = 0; // numar minim de opriri
            int fuel = m; // fuel este cantitatea curenta de combustibil din rezervor (a.k.a cat a ramas)

            for (int i = 1; i <= n; ++i) {
                fuel -= (dist[i] - dist[i - 1]); // ma deplasez de la locatia anterioara la cea curenta
                                                 // intotdeauna cand ajung intr-o benzinarie ma asigur am suficient
                                                 // combustibil sa ajung la urmatoarea - initial pot sa ajung de la A la
                                                 // dist[1]

                // daca nu am ajuns in ultima benziarie
                // verifica daca trebuie sa reincarc (rezervor gol sau cantitate insuficienta
                // pentru a ajunge la benzinaria urmatoare)
                if (i < n && (fuel == 0 || dist[i + 1] - dist[i] > fuel)) {
                    ++sol;
                    fuel = m;
                }
            }

            return sol;
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
