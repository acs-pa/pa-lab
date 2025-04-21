// SPDX-License-Identifier: BSD-3-Clause

#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

#include "shortest_path.h"

using namespace std;

class Task {
public:
    void solve() {
        read_input();
        print_output(compute());
    }

private:
    // n = numar de noduri, m = numar de muchii
    int n, m;
    // adj[i] = lista de adiacenta a nodului i
    // perechea (j, w) semnifica muchie de la i la j de cost w
    vector<pair<int, int>> adj[NMAX];

    void read_input() {
        ifstream fin("in");
        fin >> n >> m;
        for (int i = 1, x, y, w; i <= m; i++) {
            fin >> x >> y >> w;
            adj[x].push_back({y, w});
        }
        fin.close();
    }

    JohnsonResult compute() {
        //
        // TODO: Gasiti distantele minime intre oricare doua noduri, folosind
        // algoritmul lui Johnson pe graful orientat cu n noduri, m arce stocat in adk.
        //
        // Atentie:
        // O muchie este tinuta ca o pereche (nod adiacent, cost muchie):
        //     adj[node][i] == (neigh, w) - unde neigh este al i-lea vecin al lui node, iar (node, neigh) are cost w.
        //
        //
        // Trebuie sa întoarceți o structură de tipul JohnsonResult, care contine membrii
        //  * has_cycle = true, dacă a fost întâlnit un ciclu de cost negativ
        //  * d = matricea de distante, unde se setează d[u][v] = 0, daca nu a fost gasit
        // un drum de la u la v. d[u][u] = 0
        //  * p = matricea de parinti, unde p[u][v] = parintele nodului v, pornind din nodul u.
        // si p[u][v] = 0, daca v nu se poate atinge din nodul u
        //
        // Verificati "shortest_path.h":
        // * Structuri ajutatoare: Edge, JohnsonResult.
        // * Implementare data Dijkstra, BellmanFord.
        //

        return johnson(n, adj);
    }

    pair<bool, vector<int>> compute_h(int nodes, vector<pair<int, int>> adj[NMAX]) {
        // Se adauga un nod suplimentar "fictiv"
        int new_n = nodes + 1;
        int source = nodes + 1;

        // Se copiaza vectorul de liste de adiacente
        auto new_adj = adj;

        // Se leaga la toate celelalte noduri cu distanta "fictiva" 0
        for (int node = 1; node <= nodes; node++) {
            new_adj[source].push_back({node, 0});
        }

        // Construiesc un vector de muchii
        vector<Edge> edges;
        for (int node = 1; node <= new_n; ++node) {
            for (const auto& [neigh, w] : new_adj[node]) {
                edges.push_back(Edge(node, neigh, w));
            }
        }

        // Se aplica algoritmul Bellman-Ford porning din nodul fictiv
        auto res = bellman(source, new_n, edges);

        // Daca se identifica un ciclu de cost negativ, problema nu are solutie
        if (res.has_cycle) {
            return {true, {}};
        }

        // In caz contrar, se intoarce structura BellmanFordResult, ce contine vectorul de distante
        // si vectorul de parinti
        return {false, res.d};
    }

    JohnsonResult johnson(int nodes, vector<pair<int, int>> adj[NMAX]) {
        vector<vector<int>> d(nodes + 1, vector<int>(nodes + 1, 0)); // initial toate distantele sunt 0
        vector<vector<int>> p(nodes + 1, vector<int>(nodes + 1, 0)); // initial toti parintii sunt 0

        auto [has_cycle, h] = compute_h(nodes, adj);
        if (has_cycle) {
            // Am intalnit un ciclu de cost negativ, problema nu are solutie.
            return {true, {}, {}};
        }

        // Translatare folosind distantele calculate cu BellmanFord pentru a face
        // toate costurile din graf nenegative.
        for (int u = 1; u <= nodes; u++) {
            for (auto& [v, w] : adj[u]) {
                w = w + (h[u] - h[v]);
            }
        }

        // Se aplica algoritmul lui Dijsktra pornind din fiecare nod al grafului.
        for (int u = 1; u <= nodes; u++) {
            const auto& [d_dijkstra, p_dijkstra] = dijkstra(u, nodes, adj);
            for (int v = 1; v <= n; v++) {
                // daca distanta returnata de Dijkstra este -1, nu exista drum intre
                // nodul u si nodul v si pun distanta 0, conform conventiei.
                if (d_dijkstra[v] != -1) {
                    // daca exista drum intre u si v, trebuie sa fac si translatarea inversa.
                    d[u][v] = d_dijkstra[v] + (h[v] - h[u]);
                    p[u][v] = p_dijkstra[v];
                }
            }
        }

        return {false, d, p};
    }

    void print_output(const JohnsonResult& res) {
        ofstream fout("out");
        if (res.has_cycle) {
            fout << "Ciclu negativ!\n";
            return;
        }

        for (int u = 1; u <= n; u++) {
            for (int v = 1; v <= n; v++) {
                fout << res.d[u][v] << ' ';
            }
            fout << '\n';
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
