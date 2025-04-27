// SPDX-License-Identifier: BSD-3-Clause

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.PriorityQueue;

public class sol2_mst_prim {
    static class Task {
        public static final String INPUT_FILE = "in";
        public static final String OUTPUT_FILE = "out";

        // numarul maxim de noduri
        public static final int NMAX = 200005;

        // valoare mai mare decat orice distanta din graf
        public static final int INF = (1 << 30);

        // n = numar de noduri, m = numar de muchii
        int n, m;

        // adj[node] = lista de adiacenta a nodului node
        // Edge e inseamna ca exista muchie de la e.node la e.neigh de cost e.w
        ArrayList<Edge> edges = new ArrayList<>();

        public class Pair {
            public int x;
            public int y;

            Pair(int _x, int _y) {
                x = _x;
                y = _y;
            }
        }

        public class Edge {
            int node;
            int neigh;
            int w;

            Edge(int _node, int _neigh, int _w) {
                node = _node;
                neigh = _neigh;
                w = _w;
            }
        };

        // structura folosita pentru a stoca MST
        class MSTResult {
            int cost; // costul MST-ului gasit

            ArrayList<Pair> edges; // muchiile din MST-ul gasit (ordinea nu conteaza)

            MSTResult(int _cost,  ArrayList<Pair> _edges) {
                cost = _cost;
                edges = _edges;
            }
        };

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

                for (int i = 1; i <= m; i++) {
                    int x, y, w;
                    x = sc.nextInt();
                    y = sc.nextInt();
                    w = sc.nextInt();
                    edges.add(new Edge(x, y, w));
                }
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(MSTResult result) {
            try {
                PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE));
                pw.printf("%d\n", result.cost);
                for (Pair e : result.edges) {
                    pw.printf("%d %d\n", e.x, e.y);
                }
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private MSTResult getResult() {
            // TODO: Calculati costul minim al unui MST folosind algoritmul lui Prim.
            // Alegem pentru simplitate nodul de start 1.
            return prim(n, edges, 1);
        }

        
        public class PairPrim implements Comparable<PairPrim> {
            public int destination;
            public int cost;

            PairPrim(int _destination, int _cost) {
                destination = _destination;
                cost = _cost;
            }

            public int compareTo(PairPrim rhs) {
                return Integer.compare(cost, rhs.cost);
            }
        }

        // MST generat cu Prim, pornind de la un nod radacina ales anterior.
        // Complexitate: O(m log n).
        private MSTResult prim(int nodes, ArrayList<Edge> edges, int source) {
            // adj[node] = lista de adiacenta a lui node: (neigh, w)
            ArrayList<PairPrim> adj[] = new ArrayList[NMAX];
            for (int node = 1; node <= nodes; ++node) {
                adj[node] = new ArrayList<>();
            }
            for (Edge e : edges) {
                adj[e.node].add(new PairPrim(e.neigh, e.w));
                adj[e.neigh].add(new PairPrim(e.node, e.w));
            }

            // d[node] = distanta nodului node fata de MST-ul curent (cel ma apropiat nod din MST)
            // d[node] in aceasta problema va fi mereu egal cu costul unei muchii
            // Initializam vectorul de distante cu distante infinite.
            int[] d = new int[n + 1];
            // p[node] = parintele lui node (initializat cu 0)
            int[] p = new int[n + 1];
            boolean[] used = new boolean[n + 1];

            // Initializam distantele la infinit.
            for (int node = 0; node <= nodes; node++) {
                d[node] = INF;
                p[node] = 0;
            }

            // Folosim un priority queue de PairPrim, desi elementele noastre nu sunt tocmai muchii.
            // Vom folosi field-ul de cost ca si distanta pana la nodul respectiv.
            // Observati ca am modificat clasa Edge ca sa implementeze interfata Comparable.
            PriorityQueue<PairPrim> pq = new PriorityQueue<>();

            // Inseram nodul de plecare in coada si ii setam distanta pe 0.
            d[source] = 0;
            pq.add(new PairPrim(source, 0));

            // Initializam MST: cost 0, fara muchii
            int cost = 0;
            ArrayList<Pair> mst = new ArrayList<>();

            // Cat timp mai sunt noduri in coada
            while (!pq.isEmpty()) {
                // Scoatem un nod din coada
                int node = pq.poll().destination;
                // In cazul in care nodul e deja in MST, ignoram aceasta intrare.
                if (used[node]) {
                    continue;
                }

                // Adaug muchia node - p[node].
                used[node] = true;
                // Nodul radacina este adaugat print-o muchie fictiva,
                // care nu face parte din MST.
                if (p[node] != 0) {
                    cost += d[node];
                    mst.add(new Pair(node, p[node]));
                }

                // Ii parcurgem toti vecinii.
                for (PairPrim e : adj[node]) {
                    int neigh = e.destination, w = e.cost;

                    // Se imbunatateste distanta?
                    if (!used[neigh] && w < d[neigh]) {
                        // Actualizam distanta si inseram din nou in pq.
                        d[neigh] = w;
                        p[neigh] = node;
                        pq.add(new PairPrim(neigh, d[neigh]));
                    }
                }
            }

            return new MSTResult(cost, mst);
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
