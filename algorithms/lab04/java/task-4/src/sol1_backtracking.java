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
        char[] caractere;
        int[] freq;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextInt();
                k = sc.nextInt();
                String s = sc.next().trim();
                s = " " + s;
                caractere = s.toCharArray();
                freq = new int[n + 1];
                for (int i = 1; i <= n; i++) {
                    freq[i] = sc.nextInt();
                }
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(ArrayList<ArrayList<Character>> result) {
            try {
                PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE));
                pw.printf("%d\n", result.size());
                for (ArrayList<Character> arr : result) {
                    for (int i = 0; i < arr.size(); i++) {
                        pw.printf("%c", arr.get(i));
                    }
                    pw.printf("\n");
                }
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private ArrayList<ArrayList<Character>> getResult() {
            ArrayList<ArrayList<Character>> all = new ArrayList<>();

            // TODO: Construiti toate sirurile cu caracterele in stringul
            // caractere (indexat de la 1 la n), si frecventele in vectorul freq
            // (indexat de la 1 la n), stiind ca nu pot fi mai mult de K
            // aparitii consecutive ale aceluiasi caracter.
            //
            // Pentru a adauga un nou sir:
            //   ArrayList<Character> sir;
            //   all.add(sir);
            //

            solveGenerate(all);

            return all;
        }

        void solveGenerate(ArrayList<ArrayList<Character>> all) {
            // solutia este un sir (vector) de caractere
            ArrayList<Character> current = new ArrayList<Character>();

            // numarul total de caractere
            int total_count = 0;
            for (int i = 1; i <= n; ++i) {
                total_count += freq[i];
            }

            // generez recursiv pornind de current, avand 0 elemente consecutive la fel
            // in total trebuie sa plasez total_count caractere
            bkt(current, 0, total_count, all);
        }

        void bkt(ArrayList<Character> current,
                 int cons_char,                     // numarul de caractere consecutive la fel
                 int remaining,                     // numarul de caractere inca neplasate
                 ArrayList<ArrayList<Character>> all) {

            // verific daca am pus mai multe aparitii consecutive ale aceluiasi caracter
            if (cons_char > k) {
                return; // nu salvez solutia curenta
            }

            // daca nu mai am de plasat caractere
            if (remaining == 0) {
                // inseamna ca le-am plasat pe toate :D

                // salvez solutia; e nevoie sa o copiem
                all.add(new ArrayList<>(current));
                return;
            }

            // incerc sa extind cu un caracter nefolosit
            for (int i = 1; i <= n; ++i) {
                // daca este epuizat, nu il folosesc din nou
                if (freq[i] == 0) {
                    continue;
                }

                // presupun ca e un caracter nou
                int new_cons_char = 1;

                if (!current.isEmpty() && current.get(current.size() - 1) == caractere[i]) {
                    // am presupus prost, e acelasi caracter
                    new_cons_char = cons_char + 1;
                }

                // Step 1: EXTINDE
                --freq[i];
                current.add(caractere[i]);

                // Step 2: COMPLETEAZA recursiv
                bkt(current, new_cons_char, remaining - 1, all);

                // Step 3: SCOATE elementul din solutie, sa putem pune altceva in locul lui
                ++freq[i];
                current.remove(current.size() - 1);
            }
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
