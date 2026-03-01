// SPDX-License-Identifier: BSD-3-Clause

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        write_output(get_result());
    }

private:
    // numarul maxim de noduri
    static constexpr int NMAX = (int)1e5 + 5; // 10^5 + 5 = 100.005

    // n = numar de noduri, m = numar de muchii/arce
    int n, m;

    // adj[node] = lista de adiacenta a nodului node
    // exemplu: daca adj[node] = {..., neigh, ...} => exista arcul (node, neigh)
    vector<int> adj[NMAX];

    void read_input() {
        ifstream fin("in");
        fin >> n >> m;
        for (int i = 1, x, y; i <= m; i++) {
            fin >> x >> y; // arc (x, y)
            adj[x].push_back(y);
        }
        fin.close();
    }

    vector<int> get_result() {
        // TODO: Faceti sortarea topologica a grafului stocat cu liste de adiacenta din adj.
        // *******
        // ATENTIE: nodurile sunt indexate de la 1 la n.
        // *******

        return solve_dfs();
    }

    // Complexitate: O(n + m)
    vector<int> solve_dfs() {
        // vectorul rezultat (in final contine o permutare pentru 1, 2, ..., n)
        vector<int> topsort;

        // visited[node] = 1 daca node a fost deja vizitat, 0 altfel
        vector<int> visited(n + 1, 0);

        // pentru fiecare nod
        for (int node = 1; node <= n; ++node) {
            // daca nodul este nevizitat, pornim o parcurgere
            if (!visited[node]) {
                dfs(node, visited, topsort);
            }
        }

        // rezultatul a fost obtinut in ordine inversa
        reverse(topsort.begin(), topsort.end());

        return topsort;
    }

    // porneste o parcurgere DFS din node
    // foloseste vectorul visited pentru a marca nodurile vizitate
    void dfs(int node, vector<int>& visited, vector<int>& topsort) {
        visited[node] = 1; // marchez nodul ca fiind vizitat

        // parcurg vecinii
        for (auto& neigh : adj[node]) {
            if (!visited[neigh]) {
                dfs(neigh, visited, topsort);
            }
        }

        // dupa ce am vizitat recursiv toti vecinii, adaugam
        // nodul la sortare
        topsort.push_back(node);
    }

    void write_output(const vector<int>& topsort) {
        ofstream fout("out");
        for (auto node : topsort) {
            fout << node << ' ';
        }
        fout << '\n';
        fout.close();
    }
};

// [ATENTIE] NU modifica functia main!
int main() {
    std::unique_ptr<Task> task {new (nothrow) Task()};
    if (!task) {
        std::cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    return 0;
}
