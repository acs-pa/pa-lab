// SPDX-License-Identifier: BSD-3-Clause

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stack>
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

    // visiting stack: nodes are pushed into the stack in visiting order
    stack<int> nodes_stack;

    // in_stack[node] = true, if node is in stack
    //                  false, otherwise
    vector<bool> in_stack;

    void read_input() {
        ifstream fin("in");
        fin >> n >> m;
        for (int i = 1, x, y; i <= m; i++) {
            fin >> x >> y;
            adj[x].push_back(y); // arc (x, y)
        }
        fin.close();
    }

    vector<vector<int>> get_result() {
        //
        // TODO: Găsiți componentele tare conexe  (CTC / SCC) ale grafului orientat cu n noduri, stocat în adj.
        //
        // Rezultatul se va returna sub forma unui vector, fiecare element fiind un SCC (adică tot un vector).
        // * nodurile dintr-un SCC pot fi găsite în orice ordine
        // * SCC-urile din graf pot fi găsite în orice ordine
        //
        // Indicație: Folosiți algoritmul lui Tarjan pentru SCC.
        //

        return tarjan_scc();
    }

    vector<vector<int>> tarjan_scc() {
        // STEP 1: initialize results
        parent = vector<int>(n + 1, -1);
        found = vector<int>(n + 1, -1);
        low_link = vector<int>(n + 1, -1);
        in_stack = vector<bool>(n + 1, false);

        // STEP 2: visit all nodes
        vector<vector<int>> all_sccs;
        int timestamp = 0; // global timestamp
        for (int node = 1; node <= n; ++node) {
            if (parent[node] == -1) { // node not visited
                parent[node] = node; // convention: the parent of the root is actually the root

                // STEP 3: start a new DFS traversal this subtree
                dfs(node, timestamp, all_sccs);
            }
        }

        return all_sccs;
    }

    void dfs(int node, int& timestamp, vector<vector<int>>& all_sccs) {
        // STEP 1: a new node is visited - increment the timestamp
        found[node] = ++timestamp; // the timestamp when node was found
        low_link[node] = found[node]; // node only knows its timestamp
        nodes_stack.push(node); // add node to the visiting stack
        in_stack[node] = true;

        // STEP 2: visit each neighbour
        for (auto neigh : adj[node]) {
            // STEP 3: check if neigh is already visited
            if (parent[neigh] != -1) {
                // STEP 3.1: update low_link[node] with information gained through neigh
                // note: neigh is in the same SCC with node only if it's in the visiting stack;
                // otherwise, neigh is from other SCC, so it should be ignored
                if (in_stack[neigh]) {
                    low_link[node] = min(low_link[node], found[neigh]);
                }
                continue;
            }

            // STEP 4: save parent
            parent[neigh] = node;

            // STEP 5: recursively visit the child subree
            dfs(neigh, timestamp, all_sccs);

            // STEP 6: update low_link[node] with information gained through neigh
            low_link[node] = min(low_link[node], low_link[neigh]);
        }

        // STEP 7: node is root in a SCC if low_link[node] == found[node]
        // (there is no edge from a descendant to an ancestor)
        if (low_link[node] == found[node]) {
            // STEP 7.1: pop all elements above node from stack => extract the SCC where node is root
            vector<int> scc;
            do {
                auto x = nodes_stack.top();
                nodes_stack.pop();
                in_stack[x] = false;

                scc.push_back(x);
            } while (scc.back() != node); // stop when node was popped from the stack

            // STEP 7.2: save SCC
            all_sccs.push_back(scc);
        }
    }

    void print_output(const vector<vector<int>>& all_sccs) {
        ofstream fout("out");
        fout << all_sccs.size() << '\n';
        for (const auto& scc : all_sccs) {
            for (auto node : scc) {
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
