// SPDX-License-Identifier: BSD-3-Clause

// Solutie https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/
// Class Solution este impusa de LeetCode.
// Class Task este solutia propriu-zisa, conform laboratorului.

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;

public class sol1_roy_floyd {
    static class Task {
        // numarul maxim de noduri
        public static final int NMAX = 105;

        // n = numar de noduri
        int n;

        // distanceThreshold = distanta minima
        int distanceThreshold;

        // w[x]y] = constul muchiei de la x la y: (x, y, w[x][y])
        // (w[x][y] = 0 - muchia lipseste)
        //
        // In aceasta problema, costurile sunt strict pozitive.
        int w[][];

        // structura folosita pentru a stoca matricea de distante, matricea
        // de parinti folosind algoritmul RoyFloyd.
        public class RoyFloydResult {
            int d[][];
            int p[][];

            RoyFloydResult(int _d[][], int _p[][]) {
                d = _d;
                p = _p;
            }
        };

        Task(int n, int[][] edges, int distanceThreshold) {
            this.n = n;
            this.distanceThreshold = distanceThreshold;
            w = new int[n + 1][n + 1];
            for (int[] edge : edges) {
                int x = edge[0], y = edge[1], cost = edge[2];
                w[x][y] = cost;
                w[y][x] = cost;
            }
        }

        // Complexitate: O(n^3) - Roy-Floyd
        int getResult() {
            // Calculam distanta minima dintre oricare doua noduri.
            int[][] d = royfloyd().d;

            // Calculam numarul de noduri care se gasesc la distanta minima de nodul curent.
            int min_node = -1, min_count = Integer.MAX_VALUE;
            for (int i = 1; i <= n; i++) {
                int count = 0;
                for (int j = 1; j <= n; j++) {
                    if (i != j && d[i][j] <= distanceThreshold) {
                        count++;
                    }
                }
        
                // Daca numarul de vecini este mai mic decat numarul minim de vecini,
                // sau daca este egal si nodul este mai mare, actualizez minimul.
                if (count <= min_count) {
                    min_count = count;
                    min_node = i;
                }
            }

            return min_node;
        }

        private RoyFloydResult royfloyd() {
            // Initializez matricea de distante cu matricea ponderilor.
            int d[][] = new int[n + 1][n + 1];
            int p[][] = new int[n + 1][n + 1];
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    d[i][j] = w[i][j];
                    p[i][j] = 0;
                }
            }

            // Aplic Roy-Floyd
            for (int k = 1; k <= n; k++) {
                // Fixez nodul intermediar k
                for (int i = 1; i <= n; i++) {
                    for (int j = 1; j <= n; j++) {
                        if (i == j) {
                            continue;
                        }

                        // Daca nu exista drum de la i la k sau de la k la j, sarim peste.
                        if (d[i][k] == 0 || d[k][j] == 0) {
                            continue;
                        }

                        // Fixez cele doua capete ale drumului pe care le updatez (i, j).
                        // Daca nu am drum sau daca obtin un cost mai mic intre i, j,
                        // updatez.
                        if (d[i][j] == 0 || d[i][j] > d[i][k] + d[k][j]) {
                            d[i][j] = d[i][k] + d[k][j];
                            p[i][j] = p[k][j];
                        }
                    }
                }
            }

            return new RoyFloydResult(d, p);
        }
    }
}

class Solution {
    public int findTheCity(int n, int[][] edges, int distanceThreshold) {
        // Modifica indexarea nodurilor pentru a fi 1-based (conform solutie Roy-Floyd laborator).
        for (int[] edge : edges) {
            edge[0]++;
            edge[1]++;
        }

        sol1_roy_floyd.Task task = new sol1_roy_floyd.Task(n, edges, distanceThreshold);
        int min_node = task.getResult();

        // Modifica indexarea nodurilor pentru a fi 0-based (LeetCode).
        return min_node - 1;
    }
}

// Sterge clasa Main daca submiti pe LeetCode
// (platforma impune implementarea doar a clasei Solution).
class Main { public static void main(String[] args) { } }
