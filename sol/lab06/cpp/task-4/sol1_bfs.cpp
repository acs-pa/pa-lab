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
    static constexpr int NMAX = (int)1e6 + 5; // 10^6 + 5 = 1.000.005

    // n = numar de noduri, m = numar de muchii/arce
    int n, m;

    // p = numarul de taverne
    int p;

    // adj_trans[node] = lista de adiacenta a nodului node in graful transpus
    // exemplu: daca adj_trans[node] = {..., neigh, ...} => exista arcul (node, neigh) in graful transpus
    vector<int> adj_trans[NMAX];

    // vector ce reține nodurile din taverne
    vector<int> taverns;

    void read_input() {
        ifstream fin("berarii2.in");
        fin >> n >> m >> p;

        // Stocam graful transpus, vrem sa vedem intersectiile
        // unde nu putem ajunge pornind din berarii.
        for (int i = 1, x, y; i <= m; i++) {
            fin >> x >> y;
            adj_trans[y].push_back(x);
        }

        taverns.resize(p);
        for (int i = 0; i < p; ++i) {
            fin >> taverns[i];
        }

        fin.close();
    }

    vector<int> get_result() { return bfs(taverns); }

    // Complexitate: O(n + m)
    vector<int> bfs(std::vector<int>& sources) {
        // visited[node] = retine daca nodul poate fi vizitat pornind
        // dintr-o berarie
        vector<int> visited(n + 1, 0);

        // vector care retine nodurile care nu pot fi atinse pornind dintr-o taverna
        vector<int> not_reachable;

        // Step 0: declaram o coada in care putem baga noduri
        queue<int> q;

        // Step 1: pasul initial: pun in coada TOATE nodurile din berarii
        for (int tavern : taverns) {
            q.push(tavern);
            visited[tavern] = true;
        }

        // Step 2: cat timp NU am parcurs toate nodurile
        while (!q.empty()) {
            // Step 2.1: extragem si procesam urmatorul nod din coada
            int node = q.front();
            q.pop();

            // Step 2.2: parcurgem vecinii lui node pe graful transpus
            for (int adj : adj_trans[node]) {
                if (!visited[adj]) {
                    visited[adj] = true;
                    q.push(adj);
                }
            }
        }

        // Step 3: Stochez nodurile la care nu am putut ajunge
        for (int i = 1; i <= n; ++i) {
            if (!visited[i]) {
                not_reachable.push_back(i);
            }
        }

        return not_reachable;
    }

    void print_output(const vector<int>& not_reachable) {
        ofstream fout("berarii2.out");
        fout << not_reachable.size() << "\n";
        for (int node : not_reachable) {
            fout << node << "\n";
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
