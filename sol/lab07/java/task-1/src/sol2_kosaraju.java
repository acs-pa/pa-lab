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

public class sol2_kosaraju {
    static class Task {
        public static final String INPUT_FILE = "in";
        public static final String OUTPUT_FILE = "out";

        // numarul maxim de noduri
        public static final int NMAX = (int)1e5 + 5; // 10^5 + 5 = 100.005

        // n = numar de noduri, m = numar de muchii/arce
        int n, m;

        // adj[node] = lista de adiacenta a nodului node
        // exemplu: daca adj[node] = {..., neigh, ...} => exista muchia (node, neigh) in graf
        @SuppressWarnings("unchecked")
        ArrayList<Integer> adj[] = new ArrayList[NMAX];

        // adj_trans[node] = lista de adiacenta a nodului node in graful transpus
        // exemplu: daca adj_trans[node] = {..., neigh, ...} => exista muchia (node, neigh) in graful transpus
        @SuppressWarnings("unchecked")
        ArrayList<Integer> adj_trans[] = new ArrayList[NMAX];

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

                for (int i = 1; i <= n; i++) {
                    adj[i] = new ArrayList<>();
                    adj_trans[i] = new ArrayList<>();
                }
                for (int i = 1; i <= m; i++) {
                    int x, y;
                    x = sc.nextInt();
                    y = sc.nextInt();
                    adj[x].add(y); // arc (x, y)
                    adj_trans[y].add(x); // ar (y, x)
                }
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(ArrayList<ArrayList<Integer>> result) {
            try {
                PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(
                                OUTPUT_FILE)));
                pw.printf("%d\n", result.size());
                for (ArrayList<Integer> ctc : result) {
                    for (int nod : ctc) {
                        pw.printf("%d ", nod);
                    }
                    pw.printf("\n");
                }
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private ArrayList<ArrayList<Integer>> getResult() {
			// TODO: Gasiti componentele tare conexe ale grafului orientat cu n noduri, stocat in adj.
			// Rezultatul se va returna sub forma unui vector, ale carui elemente sunt componentele tare conexe detectate.
			// Nodurile si componentele tare conexe pot fi puse in orice ordine in vector.
			//

            // Aceasta solutia foloseste algoritmul lui Kosaraju.
            // Atentie: graful transpus este stocat in adj_trans.

            ArrayList<ArrayList<Integer>> sol = new ArrayList<>();

            boolean[] visited = new boolean[n + 1];

            // retin nodurile crescator dupa timpul de finalizare
            // Collections.reverse(finish_sort) reprezinta sortarea topologica daca graful ar fi aciclic
            ArrayList<Integer> finish_sort = new ArrayList<>();

            // parcurgere DFS pe graful initial pentru a construi finish_sort
            for (int i = 1; i <= n; ++i)
                if (!visited[i])
                    dfs(i, visited, finish_sort);

            // facem reverse la finish sort intrucat vrem sa parcurgem in ordine inversa
            Collections.reverse(finish_sort);

            // refacem vectorul visited pentru parcurgerea grafului transpus
            for (int i = 1; i <= n; ++i)
                visited[i] = false;

            // parcurgere pe graful transpus pentru a gasi componentele tare conexe
            for (int u: finish_sort) {
                if (!visited[u]) {
                    // construiesc o noua componenta tare conexa
                    ArrayList<Integer> ctc = new ArrayList<>();
                    dfs_t(u, visited, ctc);
                    sol.add(ctc);
                }
            }

            return sol;
        }

        // dfs pe graful normal (folosesc adj)
        void dfs(int node, boolean[] visited, ArrayList<Integer> finish_sort) {
            visited[node] = true;

            for (int v: adj[node])
                if (!visited[v])
                    dfs(v, visited, finish_sort);

            finish_sort.add(node);
        }

        // dfs pe graful transpus (folosesc adj_trans)
        void dfs_t(int node, boolean[] visited, ArrayList<Integer> current_ctc) {
            visited[node] = true;
            current_ctc.add(node);

            for (int v: adj_trans[node])
                if (!visited[v])
                    dfs_t(v, visited, current_ctc);
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
