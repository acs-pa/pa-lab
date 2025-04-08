// SPDX-License-Identifier: BSD-3-Clause

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class sol1_bfs {
    static class Task {
        public static final String INPUT_FILE = "berarii2.in";
        public static final String OUTPUT_FILE = "berari2.out";

        // numarul maxim de noduri
        public static final int NMAX = (int)1e5 + 5; // 10^5 + 5 = 1.000.005

        // n = numar de noduri, m = numar de muchii/arce
        int n, m;

        // p = numarul de taverne
        int p;

        // adj_trans[node] = lista de adiacenta a nodului node in graful transpus
        // exemplu: daca adj_trans[node] = {..., neigh, ...} => exista arcul (node, neigh) in graful transpus
        @SuppressWarnings("unchecked")
        ArrayList<Integer>[] adj_trans = new ArrayList[NMAX];

        // taverns = lista de berarii
        ArrayList<Integer> taverns = new ArrayList<>();

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new BufferedReader(new FileReader(INPUT_FILE)));
                n = sc.nextInt();
                m = sc.nextInt();
                p = sc.nextInt();

                for (int i = 0; i <= n; i++) {
                    adj_trans[i] = new ArrayList<>();
                }

                // Stocam graful transpus, vrem sa vedem intersectiile
                // unde nu putem ajunge pornind din berarii.
                for (int i = 1; i <= m; i++) {
                    int x = sc.nextInt();
                    int y = sc.nextInt();
                    adj_trans[y].add(x);
                }

                for (int i = 0; i < p; i++) {
                    taverns.add(sc.nextInt());
                }

                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        ArrayList<Integer> getResult() {
           return bfs(taverns);
        }

        // Complexitate: O(n + m)
        ArrayList<Integer> bfs(ArrayList<Integer> sources) {
             // visited[node] = retine daca nodul poate fi vizitat pornind
            // dintr-o berarie
            boolean[] visited = new boolean[n + 1];

            // vector care retine nodurile care nu pot fi atinse pornind dintr-o taverna
            ArrayList<Integer> not_reachable = new ArrayList<>();

            // Step 0: declaram o coada in care putem baga noduri
            Queue<Integer> q = new LinkedList<>();

            // Step 1: pasul initial: pun in coada TOATE nodurile din berarii
            for (int tavern : taverns) {
                if (!visited[tavern]) {
                    visited[tavern] = true;
                    q.add(tavern);
                }
            }

            // Step 2: cat timp NU am parcurs toate nodurile
            while (!q.isEmpty()) {
                // Step 2.1: extragem si procesam urmatorul nod din coada
                int node = q.poll();

                // Step 2.2: parcurgem vecinii lui node pe graful transpus
                for (int neighbor : adj_trans[node]) {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        q.add(neighbor);
                    }
                }
            }

            // Step 3: Stochez nodurile la care nu am putut ajunge
            for (int i = 1; i <= n; i++) {
                if (!visited[i]) {
                    not_reachable.add(i);
                }
            }

            return not_reachable;
        }

        private void writeOutput(ArrayList<Integer> not_reachable) {
            try {
                PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(OUTPUT_FILE)));
                pw.println(not_reachable.size());
                for (int node : not_reachable) {
                    pw.println(node);
                }
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
