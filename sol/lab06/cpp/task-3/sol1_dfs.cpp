// SPDX-License-Identifier: BSD-3-Clause

#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <limits>
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
    // perechea (neigh, w) semnifica arc de la node la neigh de cost w
    // FOLLOW-UP : Se poate o stocare mai eficienta pentru aceasta problema?
    // Hint: Fiecare nod are exact un vecin (putem folosi un hashtable).
    vector<pair<int, int>> adj[NMAX];

    // Stocare noduri care nu au gradul intern 0
    vector<bool> not_start;

    void read_input() {
        cin >> n >> m;

        not_start.resize(n + 1);
        for (int i = 0; i < m; ++i) {
            int x, y, p;
            cin >> x >> y >> p;
            adj[x].push_back({y, p});
            not_start[y] = true;
        }
    }

    vector<pair<vector<int>, int>> get_result() {
        return solve_dfs();
    }

    // Complexitate: O(n + m + n * log n): parcurgerea DFS - O(n + m), sortare - O(n log n)
    vector<pair<vector<int>, int>> solve_dfs() {
        // vectorul rezultat, contine lanturile si costul minim pentru ele
        vector<pair<vector<int>, int>> all_components;

        // visited[node] = 1 daca node a fost deja vizitat, 0 altfel
        vector<int> visited(n + 1, 0);

        // pentru fiecare nod
        for (int node = 1; node <= n; ++node) {
            // Incepem un lant nou doar daca nodul
            // nu e vizitat si e la inceputul unei lant.
            if (!visited[node] && !not_start[node]) {
                vector<int> current_component;

                int min_cost = numeric_limits<int>::max();
                dfs(node, visited, current_component, min_cost);

                // O componenta cu un singur nod are costul minim 0
                if (current_component.size() == 1) {
                    min_cost = 0;
                }
                all_components.push_back({current_component, min_cost});
            }
        }

        // Sortare crescatoare dupa start
        sort(all_components.begin(), all_components.end(), 
            [](auto &a, auto &b) { return a.first[0] < b.first[0]; });

        return all_components;
    }

    // porneste o parcurgere DFS din node
    // foloseste vectorul visited pentru a marca nodurile vizitate
    void dfs(int node, vector<int>& visited, vector<int>& current_component, int& min_cost) {
        visited[node] = 1; // marcheze nodul ca fiind vizitat
        current_component.push_back(node); // adaug nodul la componenta curenta

        // parcurg vecinii
        for (auto& [neigh, cost] : adj[node]) {
            if (!visited[neigh]) {
                min_cost = min(min_cost, cost);
                dfs(neigh, visited, current_component, min_cost);
            }
        }
    }

    void print_output(vector<pair<vector<int>, int>>&& all_components) {
        cout << all_components.size() << "\n";
        for (const auto& [nodes, cost] : all_components) {
            if (nodes.size() != 1) {
                cout << nodes.front() << " " << nodes.back() << " " << cost << "\n";
            } else {
                cout << nodes[0] << " " << nodes[0] << " " << cost << "\n";
            }
        }
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
