// SPDX-License-Identifier: BSD-3-Clause

import java.io.BufferedWriter;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    static class Task {
        public static final String INPUT_FILE = "in";
        public static final String OUTPUT_FILE = "out";

        // n = numar de noduri
        int n;

        //
        // parent[node] = parintele nodului node
        // Cazuri particulare:
        //      * parent[source] = -1
        //      * parent[node] = -1, daca node nu este accesibil din nodul sursa.
        //
        int[] parent;

        // nodul sursa si nodul destinatie
        // (captele drumului care trebuie reconstruit)
        int source, destination;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new BufferedReader(new FileReader(
                                INPUT_FILE)));
                n = sc.nextInt();
                source = sc.nextInt();
                destination = sc.nextInt();
                parent = new int[n + 1];

                for (int node = 1; node <= n; node++) {
                    parent[node] = sc.nextInt();
                }
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(ArrayList<Integer> result) {
            try {
                BufferedWriter bw = new BufferedWriter(new FileWriter(
                                OUTPUT_FILE));
                StringBuilder sb = new StringBuilder();

                if (result.isEmpty()) {
                    sb.append("Nu se poate ajunge");
                } else {
                    for (var node : result) {
                        sb.append(node).append(' ');
                    }
                }
                sb.append('\n');
                bw.write(sb.toString());
                bw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private ArrayList<Integer> getResult() {
            //
            // TODO: Reconstituiti drumul de cost minim de la nodul source la nodul destination
            // folosind vectorul de parinti parent.
            //
            // In cazul in care exista nu exista un drum de la sursa la destinatie, returnati
            // un vector gol (a.k.a. return new ArrayList<>();).
            //
            ArrayList<Integer> path = new ArrayList<>();
            return path;
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
