// SPDX-License-Identifier: BSD-3-Clause

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.lang.Math;
import java.util.Scanner;

public class sol1_binary_search {
    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        double n;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextDouble();
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(double x) {
            try {
                PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE));
                pw.printf("%.4f\n", x);
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private double getResult() {
            // TODO: Calculeaza sqrt(n) cu o precizie de 10^-3.
            // Precizie de 10^(-x) inseamna |valoarea_ta - valoarea_reala| < 10^(-x).
            double eps = 1e-3;

            int steps = 30; // limitez prin numarare de pasi

            double left = 0.0;
            double right = (n < 1 ? 1.0 : n);

            while (steps-- >= 0) {
                double middle = (left + right) * 0.5;
                double diff = n - middle * middle;

                if (Math.abs(diff) <= eps)
                    return middle;

                if (diff > 0) {
                    left = middle;
                } else {
                    right = middle;
                }
            }

            return 0.0;
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
