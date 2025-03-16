// SPDX-License-Identifier: BSD-3-Clause

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Scanner;

public class sol1_backtracking {
    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        int n;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextInt();
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(ArrayList<Integer> result) {
            try {
                PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE));
                for (int i = 1; i <= n; i++) {
                    pw.printf("%d%c", result.get(i), i == n ? '\n' : ' ');
                }
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private ArrayList<Integer> getResult() {
            ArrayList<Integer> sol = new ArrayList<Integer>();
            for (int i = 0; i <= n; i++)
                sol.add(0);

            // TODO: Gasiti o solutie pentru problema damelor pe o tabla de
            // dimensiune n x n.
            //
            // Pentru a plasa o dama pe randul i, coloana j:
            //     sol[i] = j.
            // Randurile si coloanele se indexeaza de la 1 la n.
            //

            // De exemplu, configuratia (n = 5)
            // X----
            // --X--
            // ----X
            // -X---
            // ---X-
            // se va reprezenta prin sol[1..5] = {1, 3, 5, 2, 4}.

            solveQueens(sol);

            return sol;
        }

        void solveQueens(ArrayList<Integer> sol) {
            // used[i] = true, daca coloana i e luata
            boolean[] used = new boolean[n + 1];

            bkt(1, used, sol);
        }

        // functia intoarce true daca a gasit o solutie
        boolean bkt(int i,                      // linia curenta de completat
                    boolean[] used,             // evidenta coloanelor folosite
                    ArrayList<Integer> sol) {   // solutia gasita

            // daca am gasit o solutie
            if (i == n + 1) {
                // marcam faptul ca am gasit solutia
                return true;
            }

            // incercam sa extindem solutia curenta, punand o dama pe orice coloana libera
            for (int j = 1; j <= n; ++j) {
                // pe coloana j deja mai am o dama pusa
                if (used[j]) {
                    continue;
                }

                // Pana acum avem satisfacute urmatoare conditii:
                // - 1. NU se ataca pe rand, deoarece sol[i] are valoare unica
                // - 2. NU se ataca pe coloana, deoarece avem grija ca in sol sa punem valori unice

                // ramane sa verificam conditia 3
                // - 3. Se ataca pe diagonala?

                boolean attacked = false; // solutie OK, adica presupun ca nu se ataca

                for (int row = 1; row < i; ++row) {
                    // Doua dame cu coordonatele (x1, y1) si (x2, y2) se ataca pe
                    // diagonala <==> abs(x1 - x2) == abs(y1 - y2).

                    // In cazul nostru, damele sunt (row, sol[row]) si cea pe care
                    // vrem sa o punem acum: (i, j).
                    if (Math.abs(i - row) == Math.abs(j - sol.get(row))) {
                        attacked = true;
                        break;
                    }
                }

                // Se ataca pe diagonala
                if (attacked) {
                    continue; // trec mai departe
                }

                // Step 1: PUNE o dama pe coloana j
                sol.set(i, j);
                used[j] = true;

                // Step 2: INCERCAM sa construim recursiv solutia
                boolean success = bkt(i + 1, used, sol);
                if (success) {
                    // am gasit solutie, ne intoarcem din recursivitate
                    return true;
                }

                // Step 3: SCOATE dama de pe coloana j
                sol.set(i, 0);
                used[j] = false;
            }

            // DACA se ajunge aici, atunci nu am reusit sa contruim o solutie
            return false;
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
