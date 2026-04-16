// SPDX-License-Identifier: BSD-3-Clause

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
    // exemplu: daca adj[node] = {..., neigh, ...} => exista muchia (node, neigh)
    vector<int> adj[NMAX];

    void read_input() {
        ifstream fin("in");
        fin >> n >> m;
        for (int i = 1, x, y; i <= m; i++) {
            // muchie (x, y)
            fin >> x >> y;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        fin.close();
    }

    int get_result() {
        return solve_dfs();
    }

    // Complexitate: O(n + m)
    int solve_dfs() {
        int connected_components = 0;
        vector<int> visited(n + 1, 0);

        // pentru fiecare nod
        for (int node = 1; node <= n; node++) {
            // daca nodul este nevizitat, pornim o parcurgere
            if (visited[node] == 0) {
                connected_components++;
                dfs(node, visited);
            }
        }

        return connected_components;
    }

    // porneste o parcurgere DFS din node
    // foloseste vectorul visited pentru a marca nodurile vizitate
    void dfs(int node, vector<int>& visited) {
        visited[node] = 1; // marchez nodul ca fiind vizitat

        // parcurg vecinii
        for (auto& neigh : adj[node]) {
            if (visited[neigh] == 0) {
                dfs(neigh, visited);
            }
        }
    }

    void write_output(int result) {
        ofstream fout("out");
        fout << result << '\n';
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
