// SPDX-License-Identifier: BSD-3-Clause

// Solutie https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/
// Class Solution este impusa de LeetCode.
// Class Task este solutia propriu-zisa, conform laboratorului.

#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

// numarul maxim de noduri
#define NMAX 105

// structura folosita pentru a stoca matricea de distante, matricea
// de parinti folosind algoritmul Roy-Floyd.
struct RoyFloydResult {
    vector<vector<int>> d;
    vector<vector<int>> p;

    RoyFloydResult(const vector<vector<int>>& d, const vector<vector<int>>& p)
        : d(d)
        , p(p) { }
};

class Task {
public:
    // n = numar de noduri, edges = lista de muchii, distanceThreshold = distanta minima
    // edges[i] = [x, y, w] - muchia de la x la y cu costul w
    Task(int n, vector<vector<int>>& edges, int distanceThreshold)
        : n(n)
        , distanceThreshold(distanceThreshold) {
        memset(w, 0, sizeof(w));
        for (auto edge : edges) {
            int x = edge[0], y = edge[1], cost = edge[2];
            w[x][y] = cost;
            w[y][x] = cost;
        }
    }

    // Complexitate: O(n^3) - Roy-Floyd
    int get_result() {
        // Calculam distanta minima dintre oricare doua noduri.
        const auto& [d, p] = royfloyd();
        
        // Calculam numarul de noduri care se gasesc la distanta minima de nodul curent.
        int min_node = -1, min_count = std::numeric_limits<int>::max();
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

private:
    // n = numar de noduri
    int n;

    // w[x]y] = costul muchiei de la x la y: (x, y, w[x][y])
    // (w[x][y] = 0 - muchia lipseste)
    //
    // In aceasta problema, costurile sunt strict pozitive.
    int w[NMAX][NMAX];

    // Distanta threshold
    int distanceThreshold;

    RoyFloydResult royfloyd() {
        vector<vector<int>> d(n + 1, vector<int>(n + 1));
        vector<vector<int>> p(n + 1, vector<int>(n + 1));

        // Initializez matricea d folosind matricea w.
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                d[i][j] = w[i][j];
            }
        }

        // Aplic Roy-Floyd:
        for (int k = 1; k <= n; k++) {
            // Fixez nodul intermediar, k.
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    if (i == j) {
                        continue;
                    }

                    // Daca nu exista drum de la i la k sau de la k la j, sarim peste.
                    if (!d[i][k] || !d[k][j]) {
                        continue;
                    }

                    // Fixez cele doua capete ale drumului pe care le updatez (i, j).
                    // Daca nu am drum sau daca obtin un cost mai mic intre i, j, updatez.
                    if (!d[i][j] || d[i][k] + d[k][j] < d[i][j]) {
                        d[i][j] = d[i][k] + d[k][j];
                        p[i][j] = p[k][j];
                    }
                }
            }
        }

        return {d, p};
    }
};

class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        // Modifica indexarea nodurilor pentru a fi 1-based (conform solutie Roy-Floyd laborator).
        for (auto& edge : edges) {
            edge[0]++;
            edge[1]++;
        }

        Task task(n, edges, distanceThreshold);
        auto min_node = task.get_result();

        // Modifica indexarea nodurilor pentru a fi 0-based (LeetCode).
        return min_node - 1;
    }
};

// Sterge functia main daca submiti pe LeetCode
// (platforma impune implementarea doar a functiei Solution).
int main() { return 0; }
