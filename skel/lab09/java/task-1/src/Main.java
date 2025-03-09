// SPDX-License-Identifier: BSD-3-Clause

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.List;

public class Main {
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
            List<Integer> d = new ArrayList<>();
            List<Integer> p = new ArrayList<>();

            for (int i = 0; i <= n; i++) {
                d.add(0);
                p.add(0);
            }

            return new DijkstraResult(d, p);

        }

    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
