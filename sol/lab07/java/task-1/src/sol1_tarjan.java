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

        // parent[node] = parent of node in the DFS traversal
        int[] parent;

        // found[node] = the timestamp when node was found (when started to visit its subtree)
        // Note: The global timestamp is incremented everytime a node is found.
        int[] found;

        // the minimum accessible timestamp that node can see/access
        // low_link[node] = min { found[x] | x is node OR x in ancestors(node) OR x in descendants(node) };
        int[] low_link;

        // visiting stack: nodes are pushed into the stack in visiting order
        Stack<Integer> nodes_stack = new Stack<>();

        // in_stack[node] = true, if node is in stack
        //                  false, otherwise
        boolean[] in_stack;

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
            //
            // TODO: Gasiti componentele tare conexe (CTC / SCC) ale grafului orientat cu n
            // noduri, stocat in adj.
            //
            // Rezultatul se va returna sub forma unui vector, fiecare element fiind un SCC
            // (adica tot un vector).
            // * nodurile dintr-un SCC pot fi gasite in orice ordine
            // * SCC-urile din graf pot fi gasite in orice ordine
            //
            // Indicatie: Folositi algoritmul lui Tarjan pentru SCC.
            //

            return tarjan_scc();
        }

        private ArrayList<ArrayList<Integer>> tarjan_scc() {
            // STEP 1: initialize results
            parent = new int[n + 1];
            found = new int[n + 1];
            low_link = new int[n + 1];
            in_stack = new boolean[n + 1];

            Arrays.fill(parent, -1);
            Arrays.fill(found, -1);
            Arrays.fill(low_link, -1);
            Arrays.fill(in_stack, false);

            // STEP 2: visit all nodes
            ArrayList<ArrayList<Integer>> all_sccs = new ArrayList<>();
            timestamp = 0;
            for (int node = 1; node <= n; ++node) {
                if (parent[node] == -1) { // node not visited
                    parent[node] = node; // convention: the parent of the root is actually the root

                    // STEP 3: start a new DFS traversal this subtree
                    dfs(node, all_sccs);
                }
            }

            return all_sccs;
        }

        private void dfs(int node, ArrayList<ArrayList<Integer>> all_sccs) {
            // STEP 1: a new node is visited - increment the timestamp
            found[node] = ++timestamp; // the timestamp when node was found
            low_link[node] = found[node]; // node only knows its timestamp
            nodes_stack.push(node); // add node to the visiting stack
            in_stack[node] = true;

            // STEP 2: visit each neighbour
            for (Integer neigh : adj[node]) {
                // STEP 3: check if neigh is already visited
                if (parent[neigh] != -1) {
                    // STEP 3.1: update low_link[node] with information gained through neigh
                    // note: neigh is in the same SCC with node only if it's in the visiting stack;
                    // otherwise, neigh is from other SCC, so it should be ignored
                    if (in_stack[neigh]) {
                        low_link[node] = Math.min(low_link[node], found[neigh]);
                    }
                    continue;
                }

                // STEP 4: save parent
                parent[neigh] = node;

                // STEP 5: recursively visit the child subree
                dfs(neigh, all_sccs);

                // STEP 6: update low_link[node] with information gained through neigh
                low_link[node] = Math.min(low_link[node], low_link[neigh]);
            }

            // STEP 7: node is root in a SCC if low_link[node] == found[node]
            // (there is no edge from a descendant to an ancestor)
            if (low_link[node] == found[node]) {
                // STEP 7.1: pop all elements above node from stack => extract the SCC where node is root
                ArrayList<Integer> scc = new ArrayList<>();
                do {
                    Integer x = nodes_stack.peek();
                    nodes_stack.pop();
                    in_stack[x] = false;

                    scc.add(x);
                } while (scc.get(scc.size() - 1) != node); // stop when node was popped from the stack

                // STEP 7.2: save SCC
                all_sccs.add(scc);
            }
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
