// SPDX-License-Identifier: BSD-3-Clause

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;

public class sol1_tarjan {
    static class Task {
        public static final String INPUT_FILE = "in";
        public static final String OUTPUT_FILE = "out";

        // numarul maxim de noduri
        public static final int NMAX = (int) 1e5 + 5; // 10^5 + 5 = 100.005

        // n = numar de noduri, m = numar de muchii/arce
        int n, m;

        // adj[node] = lista de adiacenta a nodului node
        // exemplu: daca adj[node] = {..., neigh, ...} => exista arcul (node, neigh)
        @SuppressWarnings("unchecked")
        ArrayList<Integer> adj[] = new ArrayList[NMAX];

        // parent[node] = parintele nodului node in parcurgerea DFS
        int[] parent;

        // found[node] = momentul cand nodul a fost descoperit (cand a inceput vizitarea subarborelui sau)
        // Observatie: timestamp-ul global creste de fiecare data cand este descoperit un nod.
        int[] found;

        // cel mai mic timestamp accesibil pe care il poate vedea/accesa nodul
        // low_link[node] = min { found[x] | x este node SAU x este in stramosii(node) SAU x este in descendentii(node) };
        int[] low_link;

        // timestamp global
        int timestamp;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new BufferedReader(new FileReader(INPUT_FILE)));
                n = sc.nextInt();
                m = sc.nextInt();

                for (int i = 1; i <= n; i++) {
                    adj[i] = new ArrayList<>();
                }
                for (int i = 1; i <= m; i++) {
                    int x, y;
                    x = sc.nextInt();
                    y = sc.nextInt();
                    // muchie (x, y)
                    adj[x].add(y);
                    adj[y].add(x);
                }
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(ArrayList<Integer>  all_cvs) {
            try {
                PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(OUTPUT_FILE)));
                for (Integer cv : all_cvs) {
                    pw.printf("%d ", cv);
                }
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private ArrayList<Integer> getResult() {
            return tarjan_cv();
        }

        private ArrayList<Integer>  tarjan_cv() {
            // PASUL 1: initializez rezultatele
            parent = new int[n + 1];
            found = new int[n + 1];
            low_link = new int[n + 1];

            Arrays.fill(parent, -1);
            Arrays.fill(found, -1);
            Arrays.fill(low_link, -1);

            // PASUL 2: vizitez toate nodurile
            HashSet<Integer> all_cvs = new HashSet<>();
            timestamp = 0;
            for (int node = 1; node <= n; ++node) {
                if (parent[node] == -1) { // nod nevizitat
                    parent[node] = node; // conventie: parintele radacinii este chiar radacina

                    // PASUL 3: pornesc o noua parcurgere DFS pe acest subarbore
                    dfs(node, all_cvs);
                }
            }

            return new ArrayList<>(all_cvs);
        }

        private void dfs(int node, HashSet<Integer>  all_cvs) {
            // PASUL 1: un nod nou este vizitat - incrementez timestamp-ul
            found[node] = ++timestamp; // timestamp-ul la care nodul a fost descoperit
            low_link[node] = found[node]; // nodul cunoaste doar propriul timestamp

            // PASUL 2: vizitez fiecare vecin
            int children = 0; // numar toti copiii lui node
            for (Integer neigh : adj[node]) {
                // PASUL 3: verific daca neigh este deja vizitat
                if (parent[neigh] != -1) {
                    // PASUL 3.1: actualizez low_link[node] cu informatiile obtinute prin neigh
                    // observatie: pentru ca graful este neorientat, trebuie ignorata muchia catre parinte
                    // (valoarea found a parintelui este mereu mai mica decat valoarea found a lui node)
                    if (neigh != parent[node]) {
                        low_link[node] = Math.min(low_link[node], found[neigh]);
                    }
                    continue;
                }

                // PASUL 4: salvez parintele
                parent[neigh] = node;
                ++children; // numar copilul

                // PASUL 5: vizitez recursiv subarborele copilului
                dfs(neigh, all_cvs);

                // PASUL 6: actualizez low_link[node] cu informatiile obtinute prin neigh
                low_link[node] = Math.min(low_link[node], low_link[neigh]);

                // PASUL 7.1: node este un CV daca i): *) node NU este radacina si **) low_link[neigh] >= found[node]
                if (parent[node] != node && low_link[neigh] >= found[node]) {
                    all_cvs.add(node);
                }
            }

            // PASUL 7.2: node este un CV daca i)): *) node este radacina si **) are cel putin 2 copii
            if (parent[node] == node && children > 1) {
                all_cvs.add(node);
            }
        }
    }

    // [ATENTIE] NU modifica functia main!
    public static void main(String[] args) {
        new Task().solve();
    }
}
