// SPDX-License-Identifier: BSD-3-Clause

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.lang.Math;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Scanner;

public class sol1_sort {
    static class Homework {
        public int deadline;
        public int score;

        public Homework() {
            deadline = 0;
            score = 0;
        }
    }

    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        int n;
        Homework[] hws;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextInt();
                hws = new Homework[n];
                for (int i = 0; i < n; i++) {
                    hws[i] = new Homework();
                    hws[i].deadline = sc.nextInt();
                    hws[i].score = sc.nextInt();
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
            // TODO: Aflati punctajul maxim pe care il puteti obtine
            // planificand optim temele.

            return plan_homeworks();
        }

        // T = O(n * DMAX)
        // S = O(DMAX)
        // n = nr teme
        // DMAX = deadline-ul maxim
        int plan_homeworks() {
            // sortam descrescator dupa scor
            Arrays.sort(hws, new Comparator<Homework>() {
                public int compare(Homework a, Homework b) {
                    return (a.score > b.score ? -1 : +1);
                }
            });

            // aflam deadline-ul maxim
            int max_deadline = 0;
            for (Homework hw : hws) {
                max_deadline = Math.max(max_deadline, hw.deadline);
            }

            // used[i] = 1, daca in saptamana i am planificata o tema
            // = 0, daca saptamana inca este libera
            boolean[] used = new boolean[max_deadline + 1];
            for (int i = 0; i <= max_deadline; ++i) {
                used[i] = false;
            }

            int profit = 0; // cate puncte castigam
            for (Homework hw : hws) {
                // Incercam sa plasam urmatoarea cea mai bine punctata tema.
                // Unde o plasam?
                // Incercam sa o plasam in ziua deadline-ului.
                // Motive:
                // 1. Student lenes.
                // 2. Ne ofera flexibilitate maxima (ex. daca am pune in saptamana 1, toate
                // temele ar putea
                // fi afectate de aceasta mutare)
                for (int t = hw.deadline; t > 0; --t) { // t = DMAX, DMAX-1, ..., 1
                    if (used[t]) { // in saptamana t deja am stabilit ca facem o alta tema mai bine punctata
                        continue;
                    }

                    // perfect: in saptamana t facem tema hw
                    used[t] = true;
                    profit += hw.score;
                    break;
                }
            }

            return profit;
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
