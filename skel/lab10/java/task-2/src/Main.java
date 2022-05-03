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

public class Main {
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
            int d[][] = new int[n + 1][n + 1];
            int p[][] = new int[n + 1][n + 1];
            for (int u = 1; u <= n; u++) {
                for (int v = 1; v <= n; v++) {
                    d[u][v] = 0;
                    p[u][v] = 0;
                }
            }

            return new JohnsonResult(false, d, p);
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
