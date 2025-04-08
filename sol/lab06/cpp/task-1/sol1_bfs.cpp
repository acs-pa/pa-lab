// SPDX-License-Identifier: BSD-3-Clause

#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    // numarul maxim de noduri
    static constexpr int NMAX = (int)1e5 + 5; // 10^5 + 5 = 100.005

    // distanta maxima in graf
    static constexpr int INF = 1e9; // 10^9 = 1.000.000.000

    // n = numar de noduri, m = numar de muchii/arce
    int n, m;

    // adj[node] = lista de adiacenta a nodului node
    // exemplu: daca adj[node] = {..., neigh, ...} => exista muchia (node, neigh)
    vector<int> adj[NMAX];

    // nodul sursa in parcurgerea BFS
    int source;

    void read_input() {
        ifstream fin("in");
        fin >> n >> m >> source;
        for (int i = 1, x, y; i <= m; i++) {
            // muchie (x, y)
            fin >> x >> y;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        fin.close();
    }

    vector<int> get_result() {
        // TODO: Faceti un BFS care sa construiasca in d valorile cerute:
        // * d[node] = numarul minim de muchii de parcurs de la nodul `source` la nodul `node`
        //      * d[source] = 0
        //      * d[node]   = -1, daca nu exista drum de la source la node
        // *******
        // ATENTIE: nodurile sunt indexate de la 1 la n.
        // *******

        return bfs(source);
    }

    // Complexitate: O(n + m)
    vector<int> bfs(int source) {
        // Step 0: alocare vector de distante
        // d[node] = INF, oricare ar fi node
        vector<int> d(n + 1, INF);

        // Step 1: declaram o coada in care putem baga noduri
        queue<int> q;

        // Step 2: pasul initial: pun in coada TOATE nodurile cu grad intern 0
        q.push(source);
        d[source] = 0;

        // Step 3: cat timp NU am parcurs toate nodurile
        while (!q.empty()) {
            // Step 3.1: extragem si procesam urmatorul nod din coada
            int node = q.front();
            q.pop();

            // Step 3.2: parcurgem vecinii lui node
            for (auto& neigh : adj[node]) {
                // actulizam distanta lui x fata de sursa daca
                // am gasit o solutie mai buna
                if (d[node] + 1 < d[neigh]) {
                    // adauga nodul in coada si actualizeaza distanta pana la el
                    d[neigh] = d[node] + 1;
                    q.push(neigh);
                }
            }
        }

        // Step 4: problema ne cere ca acolo unde nu exista drum sa punem -1
        // inlocuim valorile egale cu INF din d cu -1
        for (auto& value : d) {
            if (value == INF) {
                value = -1;
            }
        }

        return d;
    }

    void print_output(const vector<int>& d) {
        ofstream fout("out");
        for (int node = 1; node <= n; node++) {
            fout << d[node] << (node == n ? '\n' : ' ');
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
