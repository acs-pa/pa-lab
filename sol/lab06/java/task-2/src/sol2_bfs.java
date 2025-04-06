// SPDX-License-Identifier: BSD-3-Clause

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;
import java.util.Arrays;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Queue;
import java.util.LinkedList;

public class sol2_bfs {
    static class Task {
        public static final String INPUT_FILE = "in";
        public static final String OUTPUT_FILE = "out";

        // numarul maxim de noduri
        public static final int NMAX = (int)1e5 + 5; // 10^5 + 5 = 100.005

        // n = numar de noduri, m = numar de muchii/arce
        int n, m;

        // adj[node] = lista de adiacenta a nodului node
        // exemplu: daca adj[node] = {..., neigh, ...} => exista arcul (node, neigh)
        @SuppressWarnings("unchecked")
        ArrayList<Integer> adj[] = new ArrayList[NMAX];

        // in_degree[node] = gradul intern al nodului node
        int[] in_degree;

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

                for (int node = 1; node <= n; node++) {
                    adj[node] = new ArrayList<>();
                }

                in_degree = new int[n + 1];
                Arrays.fill(in_degree, 0);

                for (int i = 1, x, y; i <= m; i++) {
                    // arc (x, y)
                    x = sc.nextInt();
                    y = sc.nextInt();
                    adj[x].add(y);
                    ++in_degree[y];
                }

                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(ArrayList<Integer> topsort) {
            try {
                PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(
                                OUTPUT_FILE)));
                for (Integer node : topsort) {
                    pw.printf("%d ", node);
                }
                pw.printf("\n");
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private ArrayList<Integer> getResult() {
            // TODO: Faceti sortarea topologica a grafului stocat cu liste de adiacenta din adj.
            // *******
            // ATENTIE: nodurile sunt indexate de la 1 la n.
            // *******

            return solve_bfs(); // BFS: O(n + m)
        }

        private ArrayList<Integer> solve_bfs() {
            // Declaram o coada ce va contine toate nodurile care nu mai au dependente
            // si pe care le putem adauga apoi in topsort.
            Queue<Integer> q = new LinkedList<>();
            ArrayList<Integer> topsort = new ArrayList<>();

            // Initial adaugam in coada toate nodurile cu grad intern 0 (fara dependente)
            for (int node = 1; node <= n; node++) {
                if (in_degree[node] == 0) {
                    q.add(node);
                }
            }

            // Cat timp mai sunt noduri in coada
            while (!q.isEmpty()) {
                // Scot primul nod din coada si il adaug la solutie
                int node = q.poll();
                topsort.add(node);

                // Parcurg toti vecinii nodului si sterg arcele catre acestia
                for (Integer neigh : adj[node]) {
                    // Obs: nu e nevoie sa sterg efectiv arcul, ci pot simula asta prin scaderea gradului intern
                    --in_degree[neigh];

                    // daca gradul intern al lui neigh a ajuns la 0 (nu mai are dependente), il adaug in coada
                    if (in_degree[neigh] == 0) {
                        q.add(neigh);
                    }
                }
            }

            // Daca topsort nu contine toate nodurile, atunci graful este ciclic, deci nu are o sortare topologica
            if (topsort.size() < n) {
                return new ArrayList<>();
            }

            return topsort;
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
