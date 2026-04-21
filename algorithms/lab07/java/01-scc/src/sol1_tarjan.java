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
import java.util.Stack;

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

        // stiva de vizitare: nodurile sunt puse in stiva in ordinea vizitarii
        Stack<Integer> nodes_stack = new Stack<>();

        // in_stack[node] = true, daca nodul este in stiva
        //                  false, altfel
        boolean[] in_stack;

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
                    adj[x].add(y); // arc (x, y)
                }
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(ArrayList<ArrayList<Integer>> all_sccs) {
            try {
                PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(OUTPUT_FILE)));
                pw.printf("%d\n", all_sccs.size());
                for (ArrayList<Integer> scc : all_sccs) {
                    for (Integer node : scc) {
                        pw.printf("%d ", node);
                    }
                    pw.printf("\n");
                }
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private ArrayList<ArrayList<Integer>> getResult() {
            return tarjan_scc();
        }

        private ArrayList<ArrayList<Integer>> tarjan_scc() {
            // PASUL 1: initializez rezultatele
            parent = new int[n + 1];
            found = new int[n + 1];
            low_link = new int[n + 1];
            in_stack = new boolean[n + 1];

            Arrays.fill(parent, -1);
            Arrays.fill(found, -1);
            Arrays.fill(low_link, -1);
            Arrays.fill(in_stack, false);

            // PASUL 2: vizitez toate nodurile
            ArrayList<ArrayList<Integer>> all_sccs = new ArrayList<>();
            timestamp = 0;
            for (int node = 1; node <= n; ++node) {
                if (parent[node] == -1) { // nod nevizitat
                    parent[node] = node; // conventie: parintele radacinii este chiar radacina

                    // PASUL 3: pornesc o noua parcurgere DFS pe acest subarbore
                    dfs(node, all_sccs);
                }
            }

            return all_sccs;
        }

        private void dfs(int node, ArrayList<ArrayList<Integer>> all_sccs) {
            // PASUL 1: un nod nou este vizitat - incrementez timestamp-ul
            found[node] = ++timestamp; // timestamp-ul la care nodul a fost descoperit
            low_link[node] = found[node]; // nodul cunoaste doar propriul timestamp
            nodes_stack.push(node); // adaug nodul in stiva de vizitare
            in_stack[node] = true;

            // PASUL 2: vizitez fiecare vecin
            for (Integer neigh : adj[node]) {
                // PASUL 3: verific daca neigh este deja vizitat
                if (parent[neigh] != -1) {
                    // PASUL 3.1: actualizez low_link[node] cu informatiile obtinute prin neigh
                    // observatie: neigh este in aceeasi CTC cu node doar daca este in stiva de vizitare;
                    // altfel, neigh este din alta CTC, deci trebuie ignorat
                    if (in_stack[neigh]) {
                        low_link[node] = Math.min(low_link[node], found[neigh]);
                    }
                    continue;
                }

                // PASUL 4: salvez parintele
                parent[neigh] = node;

                // PASUL 5: vizitez recursiv subarborele copilului
                dfs(neigh, all_sccs);

                // PASUL 6: actualizez low_link[node] cu informatiile obtinute prin neigh
                low_link[node] = Math.min(low_link[node], low_link[neigh]);
            }

            // PASUL 7: nodul este radacina unei CTC daca low_link[node] == found[node]
            // (nu exista muchie de la un descendent la un stramos)
            if (low_link[node] == found[node]) {
                // PASUL 7.1: extrag toate elementele de deasupra lui node din stiva => obtin CTC-ul in care node este radacina
                ArrayList<Integer> scc = new ArrayList<>();
                do {
                    Integer x = nodes_stack.peek();
                    nodes_stack.pop();
                    in_stack[x] = false;

                    scc.add(x);
                } while (scc.get(scc.size() - 1) != node); // ma opresc cand node a fost scos din stiva

                // PASUL 7.2: salvez CTC-ul
                all_sccs.add(scc);
            }
        }
    }

    // [ATENTIE] NU modifica functia main!
    public static void main(String[] args) {
        new Task().solve();
    }
}
