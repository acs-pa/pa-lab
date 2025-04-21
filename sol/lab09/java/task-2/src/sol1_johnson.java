// SPDX-License-Identifier: BSD-3-Clause

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.PriorityQueue;

public class sol1_johnson {
    static class Task {
        public static final String INPUT_FILE = "in";
        public static final String OUTPUT_FILE = "out";

        // numarul maxim de noduri
        public static final int NMAX = 1005;

        // valoare mai mare decat orice distanta din graf
        public static final int INF = (int) 1e9;

        // n = numar de noduri, m = numar de muchii
        int n, m;

        // structura folosita pentru a stoca distanta, vectorul de parinti
        // si daca s-a intalnit un ciclu de cost negativ folosind algoritmul
        // Bellman-Ford
        public class BellmanFordResult {
            List<Integer> d;
            List<Integer> p;
            boolean hasCycle;

            BellmanFordResult(boolean _hasCycle, List<Integer> _d, List<Integer> _p) {
                hasCycle = _hasCycle;
                d = _d;
                p = _p;
            }
        };

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

        // structura folosita pentru a stoca matricea de distante, matricea
        // de parinti si daca s-a intalnit un ciclu de cost negativ
        // folosind algoritmul lui Johnson.
        public class JohnsonResult {
            int d[][];
            int p[][];
            boolean hasCycle;

            JohnsonResult(boolean _hasCycle, int _d[][], int _p[][]) {
                hasCycle = _hasCycle;
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

                for (int i = 1; i <= n; i++)
                    adj[i] = new ArrayList<>();
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

        private void writeOutput(JohnsonResult result) {
            try {
                BufferedWriter bw = new BufferedWriter(new FileWriter(
                        OUTPUT_FILE));
                StringBuilder sb = new StringBuilder();
                if (result.hasCycle) {
                    sb.append("Ciclu negativ!\n");
                } else {
                    for (int x = 1; x <= n; x++) {
                        for (int y = 1; y <= n; y++) {
                            sb.append(result.d[x][y]).append(' ');
                        }
                        sb.append('\n');
                    }
                }
                bw.write(sb.toString());
                bw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private JohnsonResult getResult() {
            //
            // TODO: Gasiti distantele minime intre oricare doua noduri, folosind
            // algoritmul lui Johnson pe graful orientat cu n noduri, m arce stocat in adk.
            //
            // Atentie:
            // O muchie este tinuta ca o pereche (nod adiacent, cost muchie):
            //     adj[node][i] == (neigh, w) - unde neigh este al i-lea vecin al lui node, iar (node, neigh) are cost w.
            //
            //
            // Trebuie sa intoarceti o structura de tipul JohnsonResult, care contine membrii
            //  * has_cycle = true, daca a fost intalnit un ciclu de cost negativ
            //  * d = matricea de distante, unde se seteaza d[u][v] = 0, daca nu a fost gasit
            // un drum de la u la v. d[u][u] = 0
            //  * p = matricea de parinti, unde p[u][v] = parintele nodului v, pornind din nodul u.
            // si p[u][v] = 0, daca v nu se poate atinge din nodul u
            return johnson(n, adj);
        }

        BellmanFordResult computeH(int nodes, ArrayList<Pair> adj[]) {
            // Se adauga un nod suplimentar "fictiv"
            int new_n = n + 1;
            int source = n + 1;

            @SuppressWarnings("unchecked")
            ArrayList<Pair> new_adj[] = new ArrayList[NMAX];

            // Se copiaza vectorul de liste de adiacente
            for (int node = 1; node <= n; node++) {
                new_adj[node] = new ArrayList<>();
                for (Pair e : adj[node]) {
                    new_adj[node].add(e);
                }
            }

            // Se leaga la toate celelalte noduri cu distanta "fictiva" 0
            new_adj[source] = new ArrayList<>();
            for (int node = 1; node <= n; node++) {
                new_adj[source].add(new Pair(node, 0));
            }

            // Construiesc un vector de muchii.
            List<Edge> edges = new ArrayList<>();
            for (int node = 1; node <= new_n; ++node) {
                for (Pair e : new_adj[node]) {
                    int neigh = e.destination;
                    int w = e.cost;
                    edges.add(new Edge(node, neigh, w));
                }
            }

            // Se aplica algoritmul Bellman-Ford porning din nodul fictiv
            BellmanFordResult res = bellman(source, new_n, edges);

            // Daca se identifica un ciclu de cost negativ, problema nu are solutie
            if (res.hasCycle) {
                return new BellmanFordResult(true, new ArrayList<>(), new ArrayList<>());
            }

            // In caz contrar, se intoarce structura BellmanFordResult, ce contine vectorul de distante
            // si vectorul de parinti
            return res;
        }

        private JohnsonResult johnson(int nodes, ArrayList<Pair> adj[]) {
            BellmanFordResult res = computeH(nodes, adj);
            // Am intalnit un ciclu de cost negativ, problema nu are solutie.
            if (res.hasCycle) {
                return new JohnsonResult(true, null, null);
            }
            List<Integer> h = res.d;

            int d[][] = new int[nodes + 1][nodes + 1];
            int p[][] = new int[nodes + 1][nodes + 1];
            for (int u = 1; u <= nodes; u++) {
                for (int v = 1; v <= nodes; v++) {
                    d[u][v] = 0;
                    p[u][v] = 0;
                }
            }

            // Translatare folosind distantele calculate cu BellmanFord pentru a face
            // toate costurile din graf nenegative.
            for (int u = 1; u <= nodes; u++) {
                for (int i = 0; i < adj[u].size(); i++) {
                    int v = adj[u].get(i).destination;
                    int w = adj[u].get(i).cost;
                    adj[u].set(i, new Pair(v, w + (h.get(u) - h.get(v))));
                }
            }

            // Se aplica algoritmul lui Dijsktra pornind din fiecare nod al grafului.
            for (int u = 1; u <= nodes; u++) {
                DijkstraResult dijkstra = dijkstra(u, nodes, adj);
                for (int v = 1; v <= nodes; v++) {
                    // daca distanta returnata de Dijkstra este -1, nu exista drum intre
                    // nodul u si nodul v si pun distanta 0, conform conventiei.
                    if (dijkstra.d.get(v) != -1) {
                        // daca exista drum intre u si v, trebuie sa fac si translatarea inversa.
                        d[u][v] = dijkstra.d.get(v) + (h.get(v) - h.get(u));
                        p[u][v] = dijkstra.p.get(v);
                    }
                }
            }

            return new JohnsonResult(false, d, p);
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
                for (Pair e : adj[node]) {
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
            for (int i = 1; i <= nodes; i++)
                if (d.get(i) == INF)
                    d.set(i, -1);

            return new DijkstraResult(d, p);
        }

        private BellmanFordResult bellman(int source, int nodes, List<Edge> edges) {
            // Initializam distantele catre toate nodurile cu infinit

            List<Integer> d = new ArrayList<>();
            List<Integer> p = new ArrayList<>();

            // Initializam distantele la infinit
            for (int node = 0; node <= nodes; node++) {
                d.add(INF);
                p.add(0);
            }

            // Setez sursa la distanta 0.
            d.set(source, 0);

            // Fac N - 1 relaxari.
            for (int i = 1; i <= nodes - 1; i++) {
                // Parcurg toate muchiile:
                for (Edge edge : edges) {
                    int node = edge.node;
                    int neigh = edge.neigh;
                    int w = edge.w;
                    // Se imbunatateste distanta?
                    if (d.get(node) + w < d.get(neigh)) {
                        // Actualizam distanta si parintele.
                        d.set(neigh, d.get(node) + w);
                        p.set(neigh, node);
                    }
                }
            }

            // Verific daca mai poate fi updatata distanta.
            for (Edge edge : edges) {
                int node = edge.node;
                int neigh = edge.neigh;
                int w = edge.w;
                // Se imbunatateste distanta?
                if (d.get(node) + w < d.get(neigh)) {
                    // Am gasit un ciclu de cost negativ.
                    return new BellmanFordResult(true, new ArrayList<>(), new ArrayList<>());
                }
            }

            // Toate nodurile catre care distanta este inca INF nu pot fi atinse din
            // nodul source, deci le setam pe -1.
            for (int node = 1; node <= nodes; node++) {
                if (d.get(node) == INF) {
                    d.set(node, -1);
                }
            }

            return new BellmanFordResult(false, d, p);
        }

    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
