// SPDX-License-Identifier: BSD-3-Clause

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class sol1_dfs {

    // Clasa generica pair. De exemplu, vom folosi Pair<Integer, Integer> 
    // pentru a reprezenta o muchie catre un nod de un anumit cost.
    private static class Pair<T, U> {
        T first;
        U second;

        Pair(T first, U second) {
            this.first = first;
            this.second = second;
        }
    }

    static class Task {
        // numarul maxim de noduri
        public static final int NMAX = (int)1e5 + 5; // 10^5 + 5 = 100.005

        // n = numar de noduri, m = numar de muchii/arce
        int n, m;

        // adj[node] = lista de adiacenta a nodului node
        // perechea (neigh, w) semnifica arc de la node la neigh de cost w
        // FOLLOW-UP : Se poate o stocare mai eficienta pentru aceasta problema? 
        // Hint: Fiecare nod are exact un vecin (putem folosi un hashtable).
        @SuppressWarnings("unchecked")
        ArrayList<Pair<Integer, Integer>> adj[] = new ArrayList[NMAX];

        // Gradul intern al nodurilor.
        int[] in_degree;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            Scanner sc = new Scanner(System.in);
            n = sc.nextInt();
            m = sc.nextInt();

            in_degree = new int[n + 1];
            
            for (int node = 1; node <= n; node++) {
                adj[node] = new ArrayList<>();
            }

            for (int i = 1, x, y, p; i <= m; i++) {
                // arc (x, y)
                x = sc.nextInt();
                y = sc.nextInt();
                p = sc.nextInt();

                adj[x].add(new Pair<Integer,Integer>(y, p));
                in_degree[y]++;
            }
        }

        private void writeOutput(ArrayList<Pair<ArrayList<Integer>, Integer>> allComponents) {
            System.out.println(allComponents.size());
            for (Pair<ArrayList<Integer>, Integer> component : allComponents) {
                ArrayList<Integer> nodes = component.first;
                int cost = component.second;
                if (nodes.size() != 1) {
                    System.out.println(nodes.get(0) + " " + nodes.get(nodes.size() - 1) + " " + cost);
                } else {
                    System.out.println(nodes.get(0) + " " + nodes.get(0) + " " + cost);
                }
            }
        }

        private ArrayList<Pair<ArrayList<Integer>, Integer>> getResult() {
            return solveDfs();
        }

        // Complexitate: O(n + m + n * log n): parcurgerea DFS - O(n + m), sortare - O(n log n)
        // Observatie: Parcurgerea poate fi inlocuita si cu BFS.
        private ArrayList<Pair<ArrayList<Integer>, Integer>> solveDfs() {
            // vectorul rezultat, contine lanturile si costul minim pentru ele   
            ArrayList<Pair<ArrayList<Integer>, Integer>> all_components = new ArrayList<>();

            // visited[node] = 1 daca node a fost deja vizitat, 0 altfel
            boolean[] visited = new boolean[n + 1];

            // pentru fiecare nod
            for (int node = 1; node <= n; node++) {
                // Incepem un lant nou doar daca nodul
                // nu e vizitat si are gradul intern 0.
                if (!visited[node] && in_degree[node] == 0) {

                    // In Java nu avem transmitere prin referinta pentru int; 
                    // il vom pasa intr-un arrray cu un element.
                    ArrayList<Integer> current_component = new ArrayList<>();
                    int[] minCost = {Integer.MAX_VALUE};
                    dfs(node, visited, current_component, minCost);

                    // O componenta cu un singur nod are costul minim 0
                    if (current_component.size() == 1) {
                        minCost[0] = 0;
                    }
                    all_components.add(new Pair<>(current_component, minCost[0]));
                }
            }

            // Sortare crescatoare dupa start
            all_components.sort((a, b) -> Integer.compare(a.first.get(0), b.first.get(0)));

            return all_components;
        }

        // porneste o parcurgere DFS din node
        // foloseste vectorul visited pentru a marca nodurile vizitate
        void dfs(int node, boolean[] visited, ArrayList<Integer> current_component, int[] min_cost) {
            visited[node] = true;
            current_component.add(node);

            // parcurg vecinii
            for (Pair<Integer, Integer> neigh : adj[node]) {
                if (!visited[neigh.first]) {
                    min_cost[0] = Math.min(min_cost[0], neigh.second);
                    dfs(neigh.first, visited, current_component, min_cost);
                }
            }
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
