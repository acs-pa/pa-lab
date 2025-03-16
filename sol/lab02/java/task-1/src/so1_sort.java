// SPDX-License-Identifier: BSD-3-Clause

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Scanner;

public class so1_sort {
    static class Obj {
        public int weight;
        public int price;

        public Obj() {
            weight = 0;
            price = 0;
        }
    };

    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        int n, w;
        Obj[] objs;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextInt();
                w = sc.nextInt();
                objs = new Obj[n];
                for (int i = 0; i < n; i++) {
                    objs[i] = new Obj();
                    objs[i].weight = sc.nextInt();
                    objs[i].price = sc.nextInt();
                }
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(double result) {
            try {
                PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE));
                pw.printf("%.4f\n", result);
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private double getResult() {
            // TODO: Aflati profitul maxim care se poate obtine cu
            // obiectele date.
            return knapsack_greedy();
        }

        // T = O(n log n) - sortare
        // S = O(1) - nu am inclus inputul
        double knapsack_greedy() {
            // Sortare crescatoare greutate/pret
            Arrays.sort(objs, new Comparator<Obj>() {
                public int compare(Obj a, Obj b) {
                    return (1.0 * a.weight / a.price < 1.0 * b.weight / b.price ? -1 : +1);
                }
            });

            double sol = 0.0;

            // parcurg lista de obiecte
            for (Obj o : objs) {
                if (w == 0.0) {
                    break; // ghiozdan plin
                }

                // in rucsac pot pune ori tot obiectul, ori o bucata din el (cat mai are loc)
                double weight = (w < o.weight ? w : o.weight);
                w -= weight;
                sol += 1.0 * weight / o.weight * o.price;
            }

            return sol;
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
