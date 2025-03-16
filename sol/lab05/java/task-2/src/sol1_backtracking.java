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

            // TODO: Construiti toate submultimele multimii {1, ..., N}.
            //
            // Pentru a adauga o noua submultime:
            //   ArrayList<Integer> submultime;
            //   all.add(submultime);
            //

            solveSets(all);

            return all;
        }

        private void solveSets(ArrayList<ArrayList<Integer>> all) {
            // vectorul in care stochez solutia (partiala) curenta
            ArrayList<Integer> current = new ArrayList<Integer>();

            // construiesc submultimile prin backtracking
            bkt(current, all);
        }

        // Submultimile unei multimi cu n elemente
        void bkt(ArrayList<Integer> current,
                 ArrayList<ArrayList<Integer>> all) {

            // Orice current este implicit si o submultime prin modul cum a fost generat

            // Adaug la solutie. E nevoie sa copiem current inainte sa il adaugam
            all.add(new ArrayList<>(current));

            // ma opresc daca am ajung la lungime maxima
            if (current.size() == n)
                return;

            // current == Submultime
            // incerc sa extind (se genereaza in ordine lexico-grafica)
            int i_min = (current.size() == 0 ? 0 : current.get(current.size() - 1));
            for (int i = i_min + 1; i <= n; ++i) {
                // Step 1: ADAUG elementul la solutie
                current.add(i);

                // Step 2: COMPLETEZ recursiv si solutia
                bkt(current, all);

                // Step 3: Scot elementul din solutie, ca sa pot pune altul in locul lui
                current.remove(current.size() - 1);
            }
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
