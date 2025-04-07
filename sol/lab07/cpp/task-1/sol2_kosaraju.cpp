// SPDX-License-Identifier: BSD-3-Clause

#include <algorithm>
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
    // exemplu: daca adj[node] = {..., neigh, ...} => exista arcul (node, neigh) in graf
    vector<int> adj[NMAX];

    // adj_trans[node] = lista de adiacenta a nodului node in graful transpus
    // exemplu: daca adj_trans[node] = {..., neigh, ...} => exista arcul (node, neigh) in graful transpus
    vector<int> adj_trans[NMAX];

    void read_input() {
        ifstream fin("in");
        fin >> n >> m;
        for (int i = 1, x, y; i <= m; i++) {
            fin >> x >> y;
            adj[x].push_back(y); // arc (x, y)
            adj_trans[y].push_back(x); // arc (y, x)
        }
        fin.close();
    }

    vector<vector<int>> get_result() {
        // TODO: Gasiti componentele tare conexe ale grafului orientat cu n noduri, stocat in adj.
        // Rezultatul se va returna sub forma unui vector, ale carui elemente sunt componentele tare conexe detectate.
        // Nodurile si componentele tare conexe pot fi puse in orice ordine in vector.
        //

        // Aceasta solutia foloseste algoritmul lui Kosaraju.
        // Atentie: graful transpus este stocat in adj_trans.
        return ctc_kosaraju();
    }

    vector<vector<int>> ctc_kosaraju() {
        vector<vector<int>> all_ctc;

        // visited[node] = retine daca nodul a fost vizitat sau nu
        // initial visited[node] = 0
        // - cand fac DFS pe graful normal, marchez cu 1 nodurile vizitate
        // - obtin toate nodurile vizitate
        // - cand fac DFS pe graful transpus, le am deja marcate cu 1,
        //   cand vizitez un nod il marchez cu 0
        vector<int> visited(n + 1, 0);

        // retin nodurile crescator dupa timpul de finalizare
        // reverse(finish_sort.begin(), finish_sort.end()) reprezinta sortarea topologica
        vector<int> finish_sort;

        finish_sort.push_back(-1); // indexare de la 1
        // parcugere pe graful initial
        for (int node = 1; node <= n; ++node) {
            if (!visited[node]) { // nevizitat pe adj => visited[node] == 0
                dfs(node, visited, finish_sort);
            }
        }

        // parcurgere pe graful transpus dat de sortarea topologica
        for (int node = n; node >= 1; --node) {
            if (visited[finish_sort[node]]) { // nevizitat pe adj => visited[node] == 1
                // construiesc o noua ctc
                vector<int> ctc;
                dfs_trans(finish_sort[node], visited, ctc);

                // o salvez
                all_ctc.push_back(ctc);
            }
        }

        return all_ctc;
    }

    // dfs pe graful normal (folosesc adj)
    void dfs(int node, vector<int>& visited, vector<int>& finish_sort) {
        visited[node] = 1;

        for (auto& neigh : adj[node]) {
            if (!visited[neigh]) {
                dfs(neigh, visited, finish_sort);
            }
        }

        // adaug nodul la sortarea topologica
        finish_sort.push_back(node);
    }

    // dfs pe graful transpus (folosesc adj_trans)
    void dfs_trans(int node, vector<int>& visited, vector<int>& ctc) {
        // vizitarea pe graful transpus, inseamna
        visited[node] = 0;
        ctc.push_back(node);

        for (auto& neigh : adj_trans[node]) {
            if (visited[neigh]) {
                dfs_trans(neigh, visited, ctc);
            }
        }
    }

    void print_output(const vector<vector<int>>& result) {
        ofstream fout("out");
        fout << result.size() << '\n';
        for (const auto& ctc : result) {
            for (auto node : ctc) {
                fout << node << ' ';
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
