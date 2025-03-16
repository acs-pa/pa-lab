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

        int n, k;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextInt();
                k = sc.nextInt();
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(ArrayList<ArrayList<Integer>> result) {
            try {
                PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE));
                pw.printf("%d\n", result.size());
                for (ArrayList<Integer> arr : result) {
                    for (int i = 0; i < arr.size(); i++) {
                        pw.printf("%d%c", arr.get(i), i + 1 == arr.size() ?
                                '\n' : ' ');
                    }
                }
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private ArrayList<ArrayList<Integer>> getResult() {
            ArrayList<ArrayList<Integer>> all = new ArrayList<>();

            // TODO: Construiti toate aranjamentele de N luate cate K ale
            // multimii {1, ..., N}.
            //
            // Pentru a adauga un nou aranjament:
            //   ArrayList<Integer> aranjament;
            //   all.add(aranjament);
            //

            solveBKT(all);

            return all;
        }

        void solveBKT(ArrayList<ArrayList<Integer>> all) {
            // vectorul in care stochez solutia (partiala) curenta
            ArrayList<Integer> current = new ArrayList<Integer>();

            // used[i] = true, daca si numai daca i este deja in solutia curenta
            boolean[] used = new boolean[n + 1];

            // construiesc aranjamentele prin backtracking
            bkt(current, used, all);
        }

        void bkt(ArrayList<Integer> current, boolean[] used, ArrayList<ArrayList<Integer>> all) {
            // daca avem o multime de dimensiune k
            if (current.size() == k) {
                // este implicit si un aranjament prin modul cum a fost generata

                // Adaug la solutie. E nevoie sa copiem current inainte sa il adaugam
                all.add(new ArrayList<>(current));

                // ma opresc
                return;
            }

            // current == Aranjament de n luate cate p (p == current.size(), p < k)
            // incerc sa extind (se genereaza in ordine lexico-grafica)
            for (int i = 1; i <= n; ++i) {
                // daca i a fost deja adaugat, il sar
                if (used[i]) {
                    continue;
                }

                // Step 1: ADAUG elementul la solutie
                current.add(i);
                used[i] = true;

                // Step 2: COMPLETEZ recursiv si solutia
                bkt(current, used, all);

                // Step 3: Scot elementul din solutie, ca sa pot pune altul in locul lui
                current.remove(current.size() - 1);
                used[i] = false;
            }
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
