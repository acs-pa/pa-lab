// SPDX-License-Identifier: BSD-3-Clause

// Solutie https://leetcode.com/problems/min-cost-to-connect-all-points/description/
// Class Solution este impusa de LeetCode.
// Class Task este solutia propriu-zisa, conform laboratorului.

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <queue>
#include <set>
#include <utility>
#include <vector>
using namespace std;

// numarul maxim de noduri
#define NMAX 200005

// valoare mai mare decat orice distanta din graf
#define INF (1 << 30)

// Structura de date descrisa aici https://infoarena.ro/problema/disjoint.
class DisjointSet {
private:
    // parent[node] = radacina arborelui din care face parte node.
    // (adica identificatorul componentei conexe curente)
    vector<int> parent;

    // size[node] = numarul de noduri din arborele in care se afla node acum.
    vector<int> size;

public:
    // Se initializeaza n paduri.
    DisjointSet(int nodes)
        : parent(nodes + 1)
        , size(nodes + 1) {
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
    void _union(int x, int y) {
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
};

struct Edge {
    int node;
    int neigh;
    int w;

    Edge() { }
    Edge(int node, int neigh, int w)
        : node(node)
        , neigh(neigh)
        , w(w) { }
};

// structura folosita pentru a stoca MST
struct MSTResult {
    int cost; // costul MST-ului gasit

    vector<pair<int, int>> edges; // muchiile din MST-ul gasit (ordinea nu conteaza)

    MSTResult(int cost, const vector<pair<int, int>>& edges)
        : cost(cost)
        , edges(edges) { }
};

class Task {
public:
    Task(vector<vector<int>>& points)
        : n(points.size())
        { 
            for (int i = 0; i < n; i++) {
                int x_i = points[i][0], y_i = points[i][1];

                for (int j = i + 1; j < n; j++) {
                    int x_j = points[j][0], y_j = points[j][1];

                    // Calculam distanta Manhattan dintre cele 2 puncte.
                    int dist = abs(x_i - x_j) + abs(y_i - y_j);
                    edges.push_back(Edge{i, j, dist});
                    edges.push_back(Edge{j, i, dist});
                }
            }
        }

    // Complexitate: O(m log m) - Kruskal.
    int get_result() {
        return kruskal(n, edges).cost;
    }

private:
    // n = numar de noduri, m = numar de muchii
    int n, m;

    // muchiile din graf: (node, neigh, w) - muchie de la node la neigh de cost w
    vector<Edge> edges;

    // MST generat cu Kruskal.
    // Complexitate: O(m log m).
    MSTResult kruskal(int nodes, vector<Edge>& edges) {
        // Sortam muchiile crescator dupa cost.
        sort(edges.begin(), edges.end(), [](const Edge& e1, const Edge& e2) { return e1.w < e2.w; });

        // Initializam padurile.
        DisjointSet disjointset(nodes);

        // Initializam MST: cost 0, fara muchii
        int cost = 0;
        vector<pair<int, int>> mst;

        // Folosim muchiile in ordine crescatoare a costului.
        int used_edges = 0;
        for (const auto& edge : edges) {
            auto [x, y, w] = edge;

            // Aflam radacinile celor 2 arbori in care sunt x si y.
            if (disjointset.setOf(x) != disjointset.setOf(y)) {
                // Reunim arborii.
                disjointset._union(x, y);

                // Adaugam muchia la MST.
                cost += w;
                mst.push_back({x, y});

                ++used_edges;
                if (used_edges == nodes - 1) {
                    // Daca am format deja un arbore, ne putem oprim.
                    break;
                }
            }
        }

        return {cost, mst};
    }
};

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        Task task(points);
        return task.get_result();
    }
};

// Sterge functia main daca submiti pe LeetCode
// (platforma impune implementarea doar a functiei Solution).
int main() { return 0; }
