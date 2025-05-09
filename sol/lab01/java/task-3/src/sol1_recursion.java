// SPDX-License-Identifier: BSD-3-Clause

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class sol1_recursion {
    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        int n, x, y;

        public void solve() {
            readInput();
            writeOutput(getResult(n, x, y));
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextInt();
                x = sc.nextInt();
                y = sc.nextInt();
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(int answer) {
            try {
                PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE));
                pw.printf("%d\n", answer);
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        // (x, y) in dreptunghiul [ (tlx, tly), (drx, dry) ]
        boolean in_rectangle(int x, int y, int tlx, int tly, int drx, int dry) {
            return (tlx <= x && x <= drx) && // x intre cele 2 laturi verticale
                    (tly <= y && y <= dry); // y intre cele 2 laturi orizontale
        }

        // caut ce valoarea am pe (x, y), in patratul de dim D, colt stanga sus dat
        // in acest patrat a fost impratiat recursiv sirul: lower, lower + 1, ..., upper
        int helper(int x, int y, int tlx, int tly, int D, int lower, int upper) {
            if (lower == upper) { // D == 1
                return lower;
            }

            // down right
            int drx = tlx + D - 1;
            int dry = tly + D - 1;

            // middle cell
            int mx = (tlx + drx) >> 1;
            int my = (tly + dry) >> 1;

            // in care subdreptunghi se afla x, y?
            // are dimensiune de 2 ori mai mica => D / 2
            // fiecare sumatrice are 1/4 din sirul de numere
            int new_D = (D >> 1); // D / 2
            int cnt = (upper - lower + 1) >> 2; // (...) / 4

            // 1: este in stanga-sus?
            int new_lower = lower;
            int new_upper = new_lower + cnt - 1;

            // cout << "case 1?\n";
            if (in_rectangle(x, y, tlx, tly, mx, my)) {
                return helper(x, y, tlx, tly, new_D, new_lower, new_upper);
            }

            // 2: este in dreapta-sus?
            new_lower += cnt;
            new_upper += cnt;

            // cout << "case 2?\n";
            if (in_rectangle(x, y, tlx, my + 1, mx, dry)) {
                return helper(x, y, tlx, my + 1, new_D, new_lower, new_upper);
            }

            // 3: este in stanga-jos?
            new_lower += cnt;
            new_upper += cnt;

            // cout << "case 3?\n";
            if (in_rectangle(x, y, mx + 1, tly, drx, my)) {
                return helper(x, y, mx + 1, tly, new_D, new_lower, new_upper);
            }

            // 4: este in dreapta-jos?
            new_lower += cnt;
            new_upper += cnt;

            // cout << "case 4?\n";
            if (in_rectangle(x, y, mx + 1, my + 1, drx, dry)) {
                return helper(x, y, mx + 1, my + 1, new_D, new_lower, new_upper);
            }

            // avem mereu solutie, nu se va ajunge aici
            return -1;
        }

        int solve_rec(int n, int x, int y) {
            int D = (1 << n);
            int lower = 1, upper = D * D;

            return helper(x, y, 1, 1, D, lower, upper);
        }

        private int getResult(int n, int x, int y) {
            // TODO: Calculati valoarea de pe pozitia (x, y) din matricea de dimensiune 2^n * 2^n.
            return solve_rec(n, x, y);
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
