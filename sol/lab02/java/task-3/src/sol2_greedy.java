// SPDX-License-Identifier: BSD-3-Clause

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.lang.Math;
import java.time.LocalTime;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Scanner;
import java.util.stream.IntStream;

public class sol2_greedy {
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

        // T = O(n^2)
        // S = O(1)
        // n = nr teme
        int plan_homeworks() {
        int profit = 0; // cate puncte castigam
            while (hws.length != 0) {
                // cautam deadline-ul maxim (daca sunt mai multe punctaj maxim)
                int imax = 0;
                for (int i = 1; i < hws.length; ++i) {
                    if (hws[i].deadline > hws[imax].deadline
                        || (hws[i].deadline == hws[imax].deadline && hws[i].score > hws[imax].score)) {
                        imax = i;
                    }
                }

                // folosesc tema cu cel mai mare punctaj
                profit += hws[imax].score;
                int used_deadline = hws[imax].deadline;
                
                final int indexToRemove = imax;
                hws = IntStream.range(0, hws.length)
                .filter(i -> i != indexToRemove)
                .mapToObj(i -> hws[i]) 
                .toArray(Homework[]::new);

                // scad cu 1 deadline-ul temelor cu acelasi deadline
                boolean has_valid_homeworks = false;
                for (var hw : hws) {
                    if (hw.deadline == used_deadline) {
                        --hw.deadline;
                    }

                    if (hw.deadline > 0) {
                        has_valid_homeworks = true;
                    }
                }

                // daca toate temele au deadline negative, nu mai putem face alte teme
                if (!has_valid_homeworks) {
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
