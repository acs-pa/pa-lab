// SPDX-License-Identifier: BSD-3-Clause

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class sol2_recursive {
    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        int base;
        int exponent;
        int mod;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                base = sc.nextInt();
                exponent = sc.nextInt();
                mod = sc.nextInt();
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(long result) {
            try {
                PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE));
                pw.printf("%d\n", result);
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private int fastPow(long base, int exponent, int mod) {
            // TODO: Calculati (base^exponent) modulo mod in O(log exponent).

            // base ^ 0 = 1
            if (exponent == 0) {
                return 1;
            }
        
            // Reducem problema la jumatate.
            long half = fastPow(base, exponent / 2, mod);
            long result = (half * half) % mod;
    
            // Pentru exponent impar, mai inmultim odata cu base.
            if (exponent % 2 == 1) {
                result = (result * (base % mod)) % mod;
            }
        
            return (int) result;
        }

        private int getResult() {
            return fastPow(base, exponent, mod);
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
