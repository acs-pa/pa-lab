// SPDX-License-Identifier: BSD-3-Clause

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Scanner;

public class Combinari {
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
                        pw.printf("%d%c", arr.get(i), i + 1 == arr.size() ? '\n' : ' ');
                    }
                }
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private ArrayList<ArrayList<Integer>> getResult() {
            ArrayList<ArrayList<Integer>> all = new ArrayList<>();
            solveBKT(all);
            return all;
        }

        void solveBKT(ArrayList<ArrayList<Integer>> all) {
            // Vectorul in care stochez solutia (partiala) curenta
            ArrayList<Integer> current = new ArrayList<Integer>();

            // Construiesc combinarile prin backtracking
            bkt(current, all);
        }

        // Combinari de n luate cate k, implementare cu transmitere prin referinta
        // T = O(n! / (k!*(n-k)!))
        // S = O(n)
        void bkt(ArrayList<Integer> current, ArrayList<ArrayList<Integer>> all) {
            // Daca avem o multime de dimensiune k
            if (current.size() == k) {
                // este implicit si o combinatie prin modul cum a fost generata

                // Adaug la solutie. E nevoie sa copiem current inainte sa il adaugam
                all.add(new ArrayList<>(current));

                // Ma opresc
                return;
            }

            // Daca este primul pas, alegem fiecare element din domeniu ca potential
            // candidat pentru prima pozitie in solutie; altfel, pentru a elimina ramurile
            // in care de exemplu {2, 1} se va genera dupa ce s-a generat {1, 2} (adica
            // ar fi duplicat), vom folosi doar elementele din domeniu care sunt mai mari
            // decat ultimul element adaugat in solutie (solution[step - 1]) */
            for (int i = (current.isEmpty() ? 1 : current.getLast() + 1); i <= n; ++i) {
                // Step 1: ADAUG elementul la solutie
                current.add(i);

                // Step 2: COMPLETEZ recursiv si solutia
                bkt(current, all);

                // Step 3: Scot elementul din solutie, ca sa pot pune altul in locul lui
                current.remove(current.size() - 1);
            }
        }
    }

    // [ATENTIE] NU modifica functia main!
    public static void main(String[] args) {
        new Task().solve();
    }
}
