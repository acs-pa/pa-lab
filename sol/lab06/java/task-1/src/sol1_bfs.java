// SPDX-License-Identifier: BSD-3-Clause

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Scanner;
import java.util.Queue;

public class sol1_bfs {
    static class Task {
        public static final String INPUT_FILE = "in";
        public static final String OUTPUT_FILE = "out";

        // numarul maxim de noduri
        public static final int NMAX = (int)1e5 + 5; // 10^5 + 5 = 100.005

        // distanta maxima in graf
        public static final int INF = (int)1e9; // 10^9 = 1.000.000.000

        // n = numar de noduri, m = numar de muchii/arce
        int n, m;

        // adj[node] = lista de adiacenta a nodului node
        // exemplu: daca adj[node] = {..., neigh, ...} => exista muchia (node, neigh)
        @SuppressWarnings("unchecked")
        ArrayList<Integer> adj[] = new ArrayList[NMAX];

        // nodul sursa in parcurgerea BFS
        int source;

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

                for (int node = 1; node <= n; node++) {
                    adj[node] = new ArrayList<>();
                }

                for (int i = 1, x, y; i <= m; i++) {
                    // muchie (x, y)
                    x = sc.nextInt();
                    y = sc.nextInt();
                    adj[x].add(y);
                    adj[y].add(x);
                }

                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
 
        private int[] getResult() {
            // TODO: Faceti un BFS care sa construiasca in d valorile:
            // * d[node] = numarul minim de muchii de parcurs de la nodul `source` la nodul `node`
            //      * d[source] = 0
            //      * d[node]   = -1, daca nu exista drum de la source la node
            // *******
            // ATENTIE: nodurile sunt indexate de la 1 la n.
            // *******
            return bfs(source);
        }

        // Complexitate: O(n + m)
        private int[] bfs(int source) {
            // Step 0: alocare vector de distante
            // d[node] = INF, oricare ar fi node
            int d[] = new int[n + 1];
            Arrays.fill(d, INF);

            // Step 1: declaram o coada in care putem baga noduri
            Queue<Integer> q = new LinkedList<>();

            // Step 2: pasul initial: pun in coada TOATE nodurile cu grad intern 0
            q.add(source);
            d[source] = 0;

            // Step 3: cat timp NU am parcurs toate nodurile
            while (!q.isEmpty()) {
                // Step 3.1: extragem si procesam urmatorul nod din coada
                int node = q.poll();

                // Step 3.2: parcurgem vecinii lui node
                for (Integer neigh : adj[node]) {
                    // actulizam distanta lui x fata de sursa daca
                    // am gasit o solutie mai buna
                    if (d[node] + 1 < d[neigh]) {
                        // adauga nodul in coada si actualizeaza distanta pana la el
                        d[neigh] = d[node] + 1;
                        q.add(neigh);
                    }
                }
            }

            // Step 4: problema ne cere ca acolo unde nu exista drum sa punem -1
            // inlocuim valorile egale cu INF din d cu -1
            for (int node = 1; node <= n; node++) {
                if (d[node] == INF) {
                    d[node] = -1;
                }
            }

            return d;
        }

        private void writeOutput(int[] d) {
            try {
                PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(
                                OUTPUT_FILE)));
                for (int node = 1; node <= n; node++) {
                    pw.printf("%d%c", d[node], node == n ? '\n' : ' ');
                }
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
