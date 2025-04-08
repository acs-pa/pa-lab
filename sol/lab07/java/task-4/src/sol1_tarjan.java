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
import java.util.Stack;

public class sol1_tarjan {
    static class Task {
        class Edge {
            int x, y;

            public Edge(int x, int y) {
                this.x = x;
                this.y = y;
            }

            public boolean equals(Object o) {
                if (o == this) {
                    return true;
                }
                if (!(o instanceof Edge)) {
                    return false;
                }
                Edge other = (Edge)(o);
                return (x == other.x && y == other.y);
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

        // edges stack: (node, neigh) is pushed into stack when traversing the edge
        Stack<Edge> edges_stack = new Stack<>();

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
        private void writeOutput(ArrayList<ArrayList<Integer>> all_bccs) {
            try {
                PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(OUTPUT_FILE)));
                pw.printf("%d\n", all_bccs.size());
                for (ArrayList<Integer> bcc : all_bccs) {
                    for (Integer node : bcc) {
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
            //
            // TODO: Gasiti componentele biconexe (BCC) ale grafului neorientat cu n noduri, stocat in adj.
            //
            // Rezultatul se va returna sub forma unui vector, fiecare element fiind un BCC (adica tot un vector).
            // * nodurile dintr-un BCC pot fi gasite in orice ordine
            // * BCC-urile din graf pot fi gasite in orice ordine
            //
            // Indicatie: Folositi algoritmul lui Tarjan pentru BCC.
            //

            return tarjan_bcc();
        }

        private ArrayList<ArrayList<Integer>> tarjan_bcc() {
            // STEP 1: initialize results
            parent = new int[n + 1];
            found = new int[n + 1];
            low_link = new int[n + 1];

            Arrays.fill(parent, -1);
            Arrays.fill(found, -1);
            Arrays.fill(low_link, -1);

            // STEP 2: visit all nodes
            ArrayList<ArrayList<Integer>> all_bccs = new ArrayList<>();
            timestamp = 0;
            for (int node = 1; node <= n; ++node) {
                if (parent[node] == -1) { // node not visited
                    parent[node] = node; // convention: the parent of the root is actually the root

                    // STEP 3: start a new DFS traversal this subtree
                    dfs(node, all_bccs);
                }
            }

            return all_bccs;
        }

        private void dfs(int node, ArrayList<ArrayList<Integer>> all_bccs) {
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
                edges_stack.add(new Edge(node, neigh));

                // STEP 5: recursively visit the child subree
                dfs(neigh, all_bccs);

                // STEP 6: update low_link[node] with information gained through neigh
                low_link[node] = Math.min(low_link[node], low_link[neigh]);

                // STEP 7: if low_link[neigh] >= found[node], all edges above (node, neigh) from stack are from the same BCC
                if (low_link[neigh] >= found[node]) {
                    all_bccs.add(get_bcc(new Edge(node, neigh)));
                }
            }
        }

        // extract all edges from the stack above stop_edge
        ArrayList<Integer> get_bcc(Edge stop_edge) {
            HashSet<Integer> bcc = new HashSet<>();

            Edge e = new Edge(-1, -1);
            do {
                e = edges_stack.pop();
                bcc.add(e.x);
                bcc.add(e.y);
            } while (!e.equals(stop_edge)); // stop when extracted the stop_edge

            return new ArrayList<>(bcc);
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
