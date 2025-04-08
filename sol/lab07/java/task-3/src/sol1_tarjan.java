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
        class Edge {
            int x, y;

            public Edge(int x, int y) {
                this.x = x;
                this.y = y;
            }
        }

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

        // parent[node] = parent of node in the DFS traversal
        int[] parent;

        // found[node] = the timestamp when node was found (when started to visit its subtree)
        // Note: The global timestamp is incremented everytime a node is found.
        int[] found;

        // the minimum accessible timestamp that node can see/access
        // low_link[node] = min { found[x] | x is node OR x in ancestors(node) OR x in descendants(node) };
        int[] low_link;

        // global timestamp
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

        private void writeOutput(ArrayList<Edge>  all_ces) {
            try {
                PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(OUTPUT_FILE)));
                pw.printf("%d\n", all_ces.size());
                for (Edge ce : all_ces) {
                    pw.printf("%d %d\n", ce.x, ce.y);
                }
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private ArrayList<Edge> getResult() {
            //
            // TODO: Gasiti toate muchiile critice ale grafului neorientat stocat cu liste de adiacenta in adj.
            // Rezultatul se va returna sub forma unui vector cu toate muchiile critice (ordinea nu conteaza).
            //
            // Indicatie: Folositi algoritmul lui Tarjan pentru CE.
            //

            return tarjan_ce();
        }

        private ArrayList<Edge>  tarjan_ce() {
            // STEP 1: initialize results
            parent = new int[n + 1];
            found = new int[n + 1];
            low_link = new int[n + 1];

            Arrays.fill(parent, -1);
            Arrays.fill(found, -1);
            Arrays.fill(low_link, -1);

            // STEP 2: visit all nodes
            ArrayList<Edge> all_ces = new ArrayList<>();
            timestamp = 0;
            for (int node = 1; node <= n; ++node) {
                if (parent[node] == -1) { // node not visited
                    parent[node] = node; // convention: the parent of the root is actually the root

                    // STEP 3: start a new DFS traversal this subtree
                    dfs(node, all_ces);
                }
            }

            return all_ces;
        }

        private void dfs(int node, ArrayList<Edge> all_ces) {
            // STEP 1: a new node is visited - increment the timestamp
            found[node] = ++timestamp; // the timestamp when node was found
            low_link[node] = found[node]; // node only knows its timestamp

            // STEP 2: visit each neighbour
            for (Integer neigh : adj[node]) {
                // STEP 3: check if neigh is already visited
                if (parent[neigh] != -1) {
                    // STEP 3.1: update low_link[node] with information gained through neigh
                    // note: because it's an undirected graf, we should ignore the edge to the parent
                    // (the found value of the parent is always less than found value of node)
                    if (neigh != parent[node]) {
                        low_link[node] = Math.min(low_link[node], found[neigh]);
                    }
                    continue;
                }

                // STEP 4: save parent
                parent[neigh] = node;

                // STEP 5: recursively visit the child subree
                dfs(neigh, all_ces);

                // STEP 6: update low_link[node] with information gained through neigh
                low_link[node] = Math.min(low_link[node], low_link[neigh]);

                // STEP 7: (node, neigh) is a CE if low_link[neigh] > found[node] where neigh in adj[node]
                if (low_link[neigh] > found[node]) {
                    all_ces.add(new Edge(node, neigh));
                }
            }
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
