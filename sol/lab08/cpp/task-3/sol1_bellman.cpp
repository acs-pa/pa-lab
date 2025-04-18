// SPDX-License-Identifier: BSD-3-Clause

#include <fstream>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

// numarul maxim de noduri
#define NMAX 50005

// valoare mai mare decat orice distanta din graf
#define INF (1 << 30)

// structura folosita pentru a stoca distanta, vectorul de parinti
// si daca s-a intalnit un ciclu de cost negativ folosind algoritmul
// Bellman-Ford
struct BellmanFordResult {
    bool has_cycle;
    vector<int> d;
    vector<int> p;

    BellmanFordResult(bool has_cycle, const vector<int>& d, const vector<int>& p)
        : has_cycle(has_cycle)
        , d(d)
        , p(p) { }
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

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    // n = numar de noduri, m = numar de muchii
    int n, m;
    // adj[node] = lista de adiacenta a nodului node
    // perechea (neigh, w) semnifica arc de la node la neigh de cost w
    vector<pair<int, int>> adj[NMAX];
    // nodul sursa
    int source;

    void read_input() {
        ifstream fin("in");
        fin >> n >> m >> source;
        for (int i = 1, x, y, w; i <= m; i++) {
            fin >> x >> y >> w;
            adj[x].push_back({y, w});
        }
        fin.close();
    }

    BellmanFordResult get_result() {
        //
        // TODO: Gasiti distantele minime de la nodul source la celelalte noduri
        // folosind Bellman-Ford pe graful orientat cu n noduri, m arce stocat in adj.
        //     d[node] = costul minim / lungimea minima a unui drum de la source la nodul
        // node;
        //     d[source] = 0;
        //     d[node] = -1, daca nu se poate ajunge de la source la node.
        //
        // Atentie:
        // O muchie este tinuta ca o pereche (nod adiacent, cost muchie):
        //     adj[node][i] == (neigh, w) - unde neigh este al i-lea vecin al lui node, iar (node, neigh) are cost w.
        //
        // In cazul in care exista ciclu de cost negativ, returnati un obiect de tipul
        //  BellmanFordResult cu campul has_cycle setat pe true si doi vectori fara elemente;
        //

        // Construiesc un vector de muchii.
        vector<Edge> edges;

        for (int node = 1; node <= n; ++node) {
            for (const auto& [neigh, w] : adj[node]) {
                edges.push_back(Edge(node, neigh, w));
            }
        }

        return bellman(source, n, edges);
    }

    BellmanFordResult bellman(int source, int nodes, vector<Edge>& edges) {
        // Initializam vectorul de distante cu distante infinite.
        vector<int> d(nodes + 1, INF);
        vector<int> p(nodes + 1, 0);

        // Setez sursa la distanta 0.
        d[source] = 0;

        // Fac N - 1 relaxari.
        for (int i = 1; i <= nodes - 1; i++) {
            // Parcurg toate muchiile:
            for (const auto& [node, neigh, w] : edges) {
                // Se imbunatateste distanta?
                if (d[node] + w < d[neigh]) {
                    // Actualizam distanta si parintele.
                    d[neigh] = d[node] + w;
                    p[neigh] = node;
                }
            }
        }

        // Verific daca mai poate fi updatata distanta.
        for (const auto& [node, neigh, w] : edges) {
            // Se imbunatateste distanta?
            if (d[node] + w < d[neigh]) {
                // Am gasit un ciclu de cost negativ.
                return {true, {}, {}};
            }
        }

        // Toate nodurile catre care distanta este inca INF nu pot fi atinse din
        // nodul source, deci le setam pe -1.
        for (int node = 1; node <= nodes; node++) {
            if (d[node] == INF) {
                d[node] = -1;
            }
        }

        return {false, d, p};
    }

    void print_output(const BellmanFordResult& result) {
        ofstream fout("out");
        const auto& [has_cycle, d, p] = result;
        if (has_cycle) {
            fout << "Ciclu negativ!\n";
        } else {
            for (int node = 1; node <= n; node++) {
                fout << d[node] << ' ';
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
