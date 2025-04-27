// SPDX-License-Identifier: BSD-3-Clause

#include <algorithm>
#include <fstream>
#include <iostream>
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
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    // n = numar de noduri, m = numar de muchii
    int n, m;

    // muchiile din graf: (node, neigh, w) - muchie de la node la neigh de cost w
    vector<Edge> edges;

    void read_input() {
        ifstream fin("in");
        fin >> n >> m;
        for (int i = 1, x, y, w; i <= m; i++) {
            fin >> x >> y >> w;
            edges.push_back(Edge{x, y, w});
        }
        fin.close();
    }

    MSTResult get_result() {
        //
        // TODO: Calculati costul minim al unui MST folosind Kruskal.
        //
        //
        // Vi se da implementarea DisjointSet. Exemple utilizare:
        //      DisjointSet disjointset(n);
        //      auto setX = disjointset.setOf(x);
        //      ...
        //      disjointset.union(x, y);
        //
        return kruskal(n, edges);
    }

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

    void print_output(const MSTResult& res) {
        ofstream fout("out");
        fout << res.cost << "\n";
        for (const auto& [x, y] : res.edges) {
            fout << x << " " << y << "\n";
        }
        fout.close();
    }
};

// [ATENTIE] NU modifica functia main!
int main() {
    // * se aloca un obiect Task pe heap
    // (se presupune ca e prea mare pentru a fi alocat pe stiva)
    // * se apeleaza metoda solve()
    // (citire, rezolvare, printare)
    // * se distruge obiectul si se elibereaza memoria
    auto* task = new (nothrow) Task(); // hint: cppreference/nothrow
    if (!task) {
        cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
