// SPDX-License-Identifier: BSD-3-Clause

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.PriorityQueue;
import java.util.List;

public class sol1_dijkstra {
    static class Task {
        public static final String INPUT_FILE = "in";
        public static final String OUTPUT_FILE = "out";

        // numarul maxim de noduri
        public static final int NMAX = 50005;

        // valoare mai mare decat orice distanta din graf
        public static final int INF = (int) 1e9;

        // n = numar de noduri, m = numar de muchii
        int n, m;
        // nodul sursa
        int source;

        // structura folosita pentru a stoca distanta, cat si vectorul de parinti
        // folosind algoritmul Dijkstra
        public class DijkstraResult {
            List<Integer> d;
            List<Integer> p;

            DijkstraResult(List<Integer> _d, List<Integer> _p) {
                d = _d;
                p = _p;
            }
        };

        public class Pair implements Comparable<Pair> {
            public int destination;
            public int cost;

            Pair(int _destination, int _cost) {
                destination = _destination;
                cost = _cost;
            }

            public int compareTo(Pair rhs) {
                return Integer.compare(cost, rhs.cost);
            }
        }

        // adj[node] = lista de adiacenta a nodului node
        // perechea (neigh, w) semnifica arc de la node la neigh de cost w
        @SuppressWarnings("unchecked")
        ArrayList<Pair> adj[] = new ArrayList[NMAX];

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
                source = sc.nextInt();

                for (int i = 1; i <= n; i++) {
                    adj[i] = new ArrayList<>();
                }
                for (int i = 1; i <= m; i++) {
                    int x, y, w;
                    x = sc.nextInt();
                    y = sc.nextInt();
                    w = sc.nextInt();
                    adj[x].add(new Pair(y, w));
                }
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(DijkstraResult result) {
            try {
                BufferedWriter bw = new BufferedWriter(new FileWriter(
                        OUTPUT_FILE));
                StringBuilder sb = new StringBuilder();
                for (int i = 1; i <= n; i++) {
                    sb.append(result.d.get(i)).append(' ');
                }
                sb.append('\n');
                bw.write(sb.toString());
                bw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private DijkstraResult getResult() {
            //
            // TODO: Gasiti distantele minime de la nodul source la celelalte noduri
            // folosind Dijkstra pe graful orientat cu n noduri, m arce stocat in adj.
            //
            // d[node] = costul minim / lungimea minima a unui drum de la source la nodul
            // node
            // * d[source] = 0;
            // * d[node] = -1, daca nu se poate ajunge de la source la node.
            //
            // Atentie:
            // O muchie este tinuta ca o pereche (nod adiacent, cost muchie):
            // adj[node][i] == (neigh, w) - unde neigh este al i-lea vecin al lui node, iar
            // (node, neigh) are cost w.
            //
            return dijkstra(source, n, adj);

        }

        private DijkstraResult dijkstra(int source, int nodes, ArrayList<Pair> adj[]) {
            List<Integer> d = new ArrayList<>();
            List<Integer> p = new ArrayList<>();

            // Initializam distantele la infinit
            for (int node = 0; node <= nodes; node++) {
                d.add(INF);
                p.add(0);
            }

            // Folosim un priority queue de Pair, desi elementele noastre nu sunt tocmai
            // muchii.
            // Vom folosi field-ul de cost ca si distanta pana la nodul respectiv.
            // Observati ca am modificat clasa Pair ca sa implementeze interfata Comparable.
            PriorityQueue<Pair> pq = new PriorityQueue<>();

            // Inseram nodul de plecare in pq si ii setam distanta la 0.
            d.set(source, 0);
            pq.add(new Pair(source, 0));

            // Cat timp inca avem noduri de procesat
            while (!pq.isEmpty()) {
                // Scoatem head-ul cozii
                int cost = pq.peek().cost;
                int node = pq.poll().destination;

                // In cazul in care un nod e introdus in coada cu mai multe distante (pentru ca
                // distanta pana la el se imbunatateste in timp), vrem sa procesam doar
                // versiunea sa cu distanta minima. Astfel, dam discard la intrarile din coada
                // care nu au distanta optima.
                if (cost > d.get(node)) {
                    continue;
                }

                // Ii parcurgem toti vecinii.
                for (var e : adj[node]) {
                    int neigh = e.destination;
                    int w = e.cost;

                    // Se imbunatateste distanta?
                    if (d.get(node) + w < d.get(neigh)) {
                        // Actualizam distanta si parintele.
                        d.set(neigh, d.get(node) + w);
                        p.set(neigh, node);
                        pq.add(new Pair(neigh, d.get(neigh)));
                    }
                }
            }

            // Toate nodurile ce au distanta INF nu pot fi atinse din sursa, asa ca setam
            // distantele
            // pe -1.
            for (int i = 1; i <= n; i++)
                if (d.get(i) == INF)
                    d.set(i, -1);

            return new DijkstraResult(d, p);
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
