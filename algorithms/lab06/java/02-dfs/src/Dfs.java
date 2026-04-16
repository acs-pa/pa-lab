// SPDX-License-Identifier: BSD-3-Clause

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;
import java.util.ArrayList;

public class Dfs {
    static class Task {
        public static final String INPUT_FILE = "in";
        public static final String OUTPUT_FILE = "out";

        // numarul maxim de noduri
        public static final int NMAX = (int)1e5 + 5; // 10^5 + 5 = 100.005

        // n = numar de noduri, m = numar de muchii/arce
        int n, m;

        // adj[node] = lista de adiacenta a nodului node
        // exemplu: daca adj[node] = {..., neigh, ...} => exista muchia (node, neigh)
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
                    // muchie (x, y)
                    x = sc.nextInt();
                    y = sc.nextInt();
                    adj[x].add(y);
                    adj[y].add(x);
                }

                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private int getResult() {
            return solveDfs();
        }

        // Complexitate: O(n + m)
        private int solveDfs() {
            int connectedComponents = 0;
            
            // visited[node] = 1 daca node a fost deja vizitat, 0 altfel
            int[] visited = new int[n + 1];

            // pentru fiecare nod
            for (int node = 1; node <= n; node++) {
                // daca nodul este nevizitat, pornim o parcurgere
                if (visited[node] == 0) {
                    connectedComponents++;
                    dfs(node, visited);
                }
            }

            return connectedComponents;
        }

        // porneste o parcurgere DFS din node
        // foloseste vectorul visited pentru a marca nodurile vizitate
        private void dfs(int node, int[] visited) {
            visited[node] = 1; // marchez nodul ca fiind vizitat

            // parcurg vecinii
            for (Integer neigh : adj[node]) {
                if (visited[neigh] == 0) {
                    dfs(neigh, visited);
                }
            }
        }

        private void writeOutput(int result) {
            try {
                PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(
                                OUTPUT_FILE)));
                pw.printf("%d\n", result);
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
    }

    // [ATENTIE] NU modifica functia main!
    public static void main(String[] args) {
        new Task().solve();
    }
}
