// SPDX-License-Identifier: BSD-3-Clause

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;

public class sol1_dfs {
    static class Task {
        public static final String INPUT_FILE = "in";
        public static final String OUTPUT_FILE = "out";

        // numarul maxim de noduri
        public static final int NMAX = (int)1e5 + 5; // 10^5 + 5 = 100.005

        // n = numar de noduri, m = numar de muchii/arce
        int n, m;

        // adj[node] = lista de adiacenta a nodului node
        // exemplu: daca adj[node] = {..., neigh, ...} => exista arcul (node, neigh)
        @SuppressWarnings("unchecked")
        ArrayList<Integer> adj[] = new ArrayList[NMAX];

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new BufferedReader(new FileReader(
                                INPUT_FILE)));
                n = sc.nextInt();
                m = sc.nextInt();

                for (int node = 1; node <= n; node++) {
                    adj[node] = new ArrayList<>();
                }

                for (int i = 1, x, y; i <= m; i++) {
                    // arc (x, y)
                    x = sc.nextInt();
                    y = sc.nextInt();
                    adj[x].add(y);
                }

                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(ArrayList<Integer> topsort) {
            try {
                PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(
                                OUTPUT_FILE)));
                for (Integer node : topsort) {
                    pw.printf("%d ", node);
                }
                pw.printf("\n");
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private ArrayList<Integer> getResult() {
            // TODO: Faceti sortarea topologica a grafului stocat cu liste de adiacenta din adj.
            // *******
            // ATENTIE: nodurile sunt indexate de la 1 la n.
            // *******

            return solveDfs(); // DFS: O(n + m)
        }

        private ArrayList<Integer> solveDfs() {
            // vectorul rezultat (in final contine o permutare pentru 1, 2, ... n)
            ArrayList<Integer> topsort = new ArrayList<>();

            boolean[] used = new boolean[n + 1];

            // pentru fiecare nod
            for (int node = 1; node <= n; node++) {
                // daca nodul nu a fost vizitat, pornim o parcurgere DFS
                if (!used[node]) {
                    dfs(node, used, topsort);
                }
            }

            // rezultatul a fost obtinut in ordine inversa
            Collections.reverse(topsort);

            return topsort;
        }

        // porneste o parcurgere DFS din node
        // foloseste vectorul used pentru a marca nodurile vizitate
        void dfs(int node, boolean[] used, ArrayList<Integer> topsort) {
            used[node] = true;

            for (Integer neigh : adj[node]) {
                if (!used[neigh]) {
                    dfs(neigh, used, topsort);
                }
            }

            // dupa ce am terminat de vizitat nodul, adaugam nodul in sortarea topologica
            topsort.add(node);
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
