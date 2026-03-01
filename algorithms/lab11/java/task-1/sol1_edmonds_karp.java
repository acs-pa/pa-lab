// SPDX-License-Identifier: BSD-3-Clause

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.lang.Math;
import java.text.CollationElementIterator;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class sol1_edmonds_karp {
    static class Task {
        public static final String INPUT_FILE = "in";
        public static final String OUTPUT_FILE = "out";

        // numarul maxim de noduri
        public static final int NMAX = 1005;

        // valoare mai mare decat maxFlow
        public static final int INF = (int) 10e9;

        // n = numar de noduri, m = numar de muchii
        int n, m;

        // adj[i] = lista de adiacenta a nodului i
        @SuppressWarnings("unchecked")
        ArrayList<Integer> adj[] = new ArrayList[NMAX];

        // cap[i][j] = capacitatea arcului i -> j
        int c[][];

        public class Edge {
            public int node;
            public int neigh;

            Edge(int _node, int _neigh) {
                node = _node;
                neigh = _neigh;
            }

        }

        // structura folosita pentru a stoca daca exista drum de ameliorare
        // si care este acesta.
        public class AugmentedPath {
            boolean hasPath;
            ArrayList<Edge> path;

            AugmentedPath(boolean _hasPath, ArrayList<Edge> _path) {
                hasPath = _hasPath;
                path = _path;
            }
        }

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
                }

                c = new int[n + 1][n + 1];

                for (int i = 1; i <= m; i++) {
                    // x -> y de capacitate c
                    int u, v, capacity;
                    u = sc.nextInt();
                    v = sc.nextInt();
                    capacity = sc.nextInt();
                    adj[u].add(v);
                    adj[v].add(u);

                    // Presupunem existenta mai multor arce x -> y cu capacitati c1, c2, ...
                    // Comprimam intr-un singur arc x -> y cu capacitate
                    // cap[x][y] = c1 + c2 + ...
                    c[u][v] += capacity;
                }
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
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

        private int getResult() {
           //
            // TODO: Calculati fluxul maxim pe graful orientat dat.
            // Sursa este nodul 1.
            // Destinatia este nodul n.
            //
            // In adj este stocat graful neorientat obtinut dupa ce se elimina orientarea
            // arcelor, iar in c sunt stocate capacitatile arcelor.
            // De exemplu, un arc (x, y) de capacitate cap va fi tinut astfel:
            // c[x][y] = cap, adj[x] contine y, adj[y] contine x.
            //
            return getMaxflow(n + 1, adj, 1, n);
        }

        int getMaxflow(int nodes, ArrayList<Integer> adj[], int source, int sink) {
            // Initial nu exista flux in retea.
            int totalFlow = 0;
            AugmentedPath res;

            int f[][] = new int[nodes][nodes];
            for (int u = 1; u < nodes; ++u) {
                for (int v = 1; v < nodes; ++v) {
                    f[u][v] = 0;
                }
            }

            // Cat timp am un drum de ameliorare de la source la sink
            while ((res = bfs(nodes, adj, source, sink, f, c)) != null) {
                var path = res.path;

                int rc = INF;
                // Calculare capacitate reziduala pentru drumul de ameliorare
                for (Edge e : path) {
                    int u = e.node;
                    int v = e.neigh;
                    rc = Math.min(rc, c[u][v] - f[u][v]);
                }

                // pompam fluxul
                totalFlow += rc;

                // actualizez drumul
                for (Edge e : path) {
                    int u = e.node;
                    int v = e.neigh;
                    f[u][v] += rc; // adaug fluxul pe muchia de pe drum
                    f[v][u] -= rc; // scad fluxul in sens invers
                }
            }

            return totalFlow;
        }

        // Se realizeaza o parcugere BFS de la source la sink.
        // Se incearca unui drum de ameliorare.
        // Se poate merge pe un arc i->j doar daca capacitatea reziduala este strict
        // pozitiva
        // a.k.a. cap[i][j] - flow[i][j] > 0, pentru arcul i->j
        // (muchia i->j nu e saturata)
        AugmentedPath bfs(int nodes, ArrayList<Integer> adj[], int source, int sink, int f[][], int c[][]) {

            // initial niciun nod nu are parinte
            int p[] = new int[nodes];
            for (int i = 1; i < nodes; i++) {
                p[i] = -1;
            }

            Queue<Integer> q = new LinkedList<>();

            // sursa este radacina in arborele BFS - singura cu parinte 0
            q.add(source);
            p[source] = 0;

            while (!q.isEmpty()) {
                int node = q.remove();

                for (Integer neigh : adj[node]) {
                    if (p[neigh] == -1 && f[node][neigh] < c[node][neigh]) {
                        p[neigh] = node;
                        q.add(neigh);
                    }
                }
            }

            if (p[sink] == -1) {
                return null;
            }

            // construim un vector cu toate muchiile de pe drumul de ameliorare
            ArrayList<Edge> path = new ArrayList<>();
            int node = sink;
            while (p[node] != 0) {
                path.add(new Edge(p[node], node));
                node = p[node];
            }
            Collections.reverse(path);
            return new AugmentedPath(true, path);
        }
    }

    // [ATENTIE] NU modifica functia main!
    public static void main(String[] args) {
        new Task().solve();
    }
}
