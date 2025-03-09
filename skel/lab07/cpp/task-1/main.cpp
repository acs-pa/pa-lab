// SPDX-License-Identifier: BSD-3-Clause

#include <fstream>
#include <iostream>
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
            fin >> x >> y; // muchie (x, y)
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

        vector<int> d(n + 1);
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
