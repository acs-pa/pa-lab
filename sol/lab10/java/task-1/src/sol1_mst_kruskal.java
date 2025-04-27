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

public class sol1_mst_kruskal {
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

        // Structura de date descrisa aici https://infoarena.ro/problema/disjoint.
        public class DisjointSet {
            // parent[node] = radacina arborelui din care face parte node.
            // (adica identificatorul componentei conexe curente)
            int [] parent;

            // size[node] = numarul de noduri din arborele in care se afla node acum.
            int [] size;

            // Se initializeaza n paduri.
            DisjointSet(int nodes) {
                parent = new int[nodes + 1];
                size   = new int[nodes + 1];
                // Fiecare padure contine un nod initial.
                for (int node = 1; node <= nodes; ++node) {
                    parent[node] = node;
                    size[node] = 1;
                }
            }

            // Returneaza radacina arborelui din care face parte node.
            int setOf(int node) {
                // Daca node este radacina, atunci am gasit raspunsul.
                if (node == parent[node]) {
                    return node;
                }

                // Altfel, urcam in sus din "radacina in radacina",
                // actualizand pe parcurs radacinile pentru nodurile atinse.
                parent[node] = setOf(parent[node]);
                return parent[node];
            }

            // Reuneste arborii lui x si y intr-un singur arbore,
            // folosind euristica de reuniune a drumurilor dupa rank.
            void union(int x, int y) {
                // Obtinem radacinile celor 2 arbori
                int rx = setOf(x), ry = setOf(y);

                // Arborele mai mic este atasat la radacina arborelui mai mare.
                if (size[rx] <= size[ry]) {
                    size[ry] += size[rx];
                    parent[rx] = ry;
                } else {
                    size[rx] += size[ry];
                    parent[ry] = rx;
                }
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
            //
            // TODO: Calculati costul minim al unui MST folosind Kruskal.
            //
            //
            // Vi se da implementarea DisjointSet. Exemple utilizare:
            //      DisjointSet disjointset = new DisjointSet(n);
            //      int setX = disjointset.setOf(x);
            //      ...
            //      disjointset.union(x, y);
            //

            return kruskal(n, edges);
        }

        // MST generat cu Kruskal.
        // Complexitate: O(m log m).
        MSTResult kruskal(int nodes, ArrayList<Edge> edges) {
            // Sortam muchiile crescator dupa cost.
            Collections.sort(edges, new Comparator<Edge>() {
                public int compare(Edge a, Edge b) {
                        return Integer.compare(a.w, b.w);
                };
            });

            // Initializam padurile.
            DisjointSet disjointset = new DisjointSet(nodes);

            // Initializam MST: cost 0, fara muchii
            int cost = 0;
            ArrayList<Pair> mst = new ArrayList<>();

            // Folosim muchiile in ordine crescatoare a costului.
            int used_edges = 0;
            for (Edge edge : edges) {
                int x = edge.node, y = edge.neigh, w = edge.w;

                // Aflam radacinile celor 2 arbori in care sunt x si y.
                if (disjointset.setOf(x) !=  disjointset.setOf(y)) {
                    // Reunim arborii.
                    disjointset.union(x, y);

                    // Adaugam muchia la MST.
                    cost += w;
                    mst.add(new Pair(x, y));

                    ++used_edges;
                    if (used_edges == nodes - 1) {
                        // Daca am format deja un arbore, ne putem opri.
                        break;
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
