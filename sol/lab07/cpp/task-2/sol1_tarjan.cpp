// SPDX-License-Identifier: BSD-3-Clause

#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_set>
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
    // exemplu: daca adj[node] = {..., neigh, ...} => exista arcul (node, neigh)
    vector<int> adj[NMAX];

    // parent[node] = parent of node in the DFS traversal
    vector<int> parent;

    // found[node] = the timestamp when node was found (when started to visit its subtree)
    // Note: The global timestamp is incremented everytime a node is found.
    vector<int> found;

    // the minimum accessible timestamp that node can see/access
    // low_link[node] =  min { found[x] | x is node OR x in ancestors(node) OR x in descendants(node) };
    vector<int> low_link;

    void read_input() {
        ifstream fin("in");
        fin >> n >> m;
        for (int i = 1, x, y; i <= m; i++) {
            fin >> x >> y; // muchia (x, y)
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        fin.close();
    }

    vector<int> get_result() {
        //
        // TODO: Gasiti toate nodurile critice ale grafului neorientat stocat cu liste de adiacenta in adj.
        // Rezultatul se va returna sub forma unui vector cu toate punctele critice (ordinea nu conteaza).
        //
        // Indicație: Folosiți algoritmul lui Tarjan pentru CV.
        //

        return tarjan_cv();
    }

    vector<int> tarjan_cv() {
        // STEP 1: initialize results
        parent = vector<int>(n + 1, -1);
        found = vector<int>(n + 1, -1);
        low_link = vector<int>(n + 1, -1);

        // STEP 2: visit all nodes
        unordered_set<int> all_cvs;
        int timestamp = 0; // global timestamp
        for (int node = 1; node <= n; ++node) {
            if (parent[node] == -1) { // node not visited
                parent[node] = node; // convention: the parent of the root is actually the root

                // STEP 3: start a new DFS traversal this subtree
                dfs(node, timestamp, all_cvs);
            }
        }

        return {all_cvs.begin(), all_cvs.end()};
    }

    void dfs(int node, int& timestamp, unordered_set<int>& all_cvs) {
        // STEP 1: a new node is visited - increment the timestamp
        found[node] = ++timestamp; // the timestamp when node was found
        low_link[node] = found[node]; // node only knows its timestamp

        // STEP 2: visit each neighbour
        int children = 0; // count all children for node
        for (auto neigh : adj[node]) {
            // STEP 3: check if neigh is already visited
            if (parent[neigh] != -1) {
                // STEP 3.1: update low_link[node] with information gained through neigh
                // note: because it's an undirected graf, we should ignore the edge to the parent
                // (the found value of the parent is always less than found value of node)
                if (neigh != parent[node]) {
                    low_link[node] = min(low_link[node], found[neigh]);
                }
                continue;
            }

            // STEP 4: save parent
            parent[neigh] = node;
            ++children; // count child

            // STEP 5: recursively visit the child subree
            dfs(neigh, timestamp, all_cvs);

            // STEP 6: update low_link[node] with information gained through neigh
            low_link[node] = min(low_link[node], low_link[neigh]);

            // STEP 7.1: node is a CV if i): *) node is NOT root and **) low_link[neigh] >= found[node]
            if (parent[node] != node && low_link[neigh] >= found[node]) {
                all_cvs.insert(node);
            }
        }

        // STEP 7.2: node is a CV if i)): *) node is root and **) it hase at leat 2 children
        if (parent[node] == node && children > 1) {
            all_cvs.insert(node);
        }
    }

    void print_output(const vector<int>& all_cvs) {
        ofstream fout("out");
        for (auto cv : all_cvs) {
            fout << cv << ' ';
        }
        fout << '\n';
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
