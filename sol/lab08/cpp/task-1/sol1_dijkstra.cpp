// SPDX-License-Identifier: BSD-3-Clause

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <utility>
#include <vector>
using namespace std;

// numarul maxim de noduri
#define NMAX 50005

// valoare mai mare decat orice distanta din graf
#define INF (1 << 30)

// structura folosita pentru a stoca distanta, cat si vectorul de parinti
// folosind algoritmul Dijkstra
struct DijkstraResult {
    vector<int> d;
    vector<int> p;

    DijkstraResult(const vector<int>& d, const vector<int>& p)
        : d(d)
        , p(p) { }
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

    DijkstraResult get_result() {
        //
        // TODO: Gasiti distantele minime de la nodul source la celelalte noduri
        // folosind Dijkstra pe graful orientat cu n noduri, m arce stocat in adj.
        //
        // d[node] = costul minim / lungimea minima a unui drum de la source la nodul node
        //     * d[source] = 0;
        //     * d[node] = -1, daca nu se poate ajunge de la source la node.
        //
        // Atentie:
        // O muchie este tinuta ca o pereche (nod adiacent, cost muchie):
        //     adj[node][i] == (neigh, w) - unde neigh este al i-lea vecin al lui node, iar (node, neigh) are cost w.
        //

        return dijkstra(source, n, adj);
    }

    DijkstraResult dijkstra(int source, int nodes, vector<pair<int, int>> adj[NMAX]) {
        // Initializam vectorul de distante cu distante infinite.
        vector<int> d(nodes + 1, INF);
        vector<int> p(nodes + 1, 0);

        // In loc de un priority_queue<> folosim set<>, cu elemente tupluri de
        // tipul (distanta pana la nod, nod). Setul tine elementele ordonate, deci
        // mereum in pq.begin() vom avea tuplul care ii corespunde nodului cu
        // distanta minima.
        set<pair<int, int>> pq;

        // Inseram nodul de plecare in coada si ii actualizam distanta.
        d[source] = 0;
        pq.insert({d[source], source});

        while (!pq.empty()) {
            // Scoatem top-ul.
            auto top = pq.begin();
            const auto [_, node] = *top;
            pq.erase(top);

            // Ii parcurgem toti vecinii.
            for (const auto& [neigh, w] : adj[node]) {
                // Se imbunatateste distanta?
                if (d[node] + w < d[neigh]) {
                    // Scoatem vechea pereche/distanta din set.
                    pq.erase({d[neigh], neigh});

                    // Actualizam distanta si parintele.
                    d[neigh] = d[node] + w;
                    p[neigh] = node;

                    // Inseram noua distanta.
                    pq.insert({d[neigh], neigh});
                }
            }
        }

        // Toate nodurile catre care distanta este inca INF nu pot fi atinse din
        // nodul source, deci le setam pe -1.
        for (int node = 1; node <= nodes; node++) {
            if (d[node] == INF) {
                d[node] = -1;
            }
        }

        return {d, p};
    }

    void print_output(const DijkstraResult& result) {
        ofstream fout("out");
        const auto& [d, _] = result;
        for (int node = 1; node <= n; node++) {
            fout << d[node] << " ";
        }
        fout << "\n";
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
