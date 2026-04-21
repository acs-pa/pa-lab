// SPDX-License-Identifier: BSD-3-Clause

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <stack>
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

    // parent[node] = parintele nodului node in parcurgerea DFS
    vector<int> parent;

    // found[node] = momentul cand nodul a fost descoperit (cand a inceput vizitarea subarborelui sau)
    // Observatie: timestamp-ul global creste de fiecare data cand este descoperit un nod.
    vector<int> found;

    // cel mai mic timestamp accesibil pe care il poate vedea/accesa nodul
    // low_link[node] = min { found[x] | x este node SAU x este in stramosii(node) SAU x este in descendentii(node) };
    vector<int> low_link;

    // stiva de vizitare: nodurile sunt puse in stiva in ordinea vizitarii
    stack<int> nodes_stack;

    // in_stack[node] = true, daca nodul este in stiva
    //                  false, altfel
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
        return tarjan_scc();
    }

    vector<vector<int>> tarjan_scc() {
        // PASUL 1: initializez rezultatele
        parent = vector<int>(n + 1, -1);
        found = vector<int>(n + 1, -1);
        low_link = vector<int>(n + 1, -1);
        in_stack = vector<bool>(n + 1, false);

        // PASUL 2: vizitez toate nodurile
        vector<vector<int>> all_sccs;
        int timestamp = 0; // timestamp global
        for (int node = 1; node <= n; ++node) {
            if (parent[node] == -1) { // nod nevizitat
                parent[node] = node; // conventie: parintele radacinii este chiar radacina

                // PASUL 3: pornesc o noua parcurgere DFS pe acest subarbore
                dfs(node, timestamp, all_sccs);
            }
        }

        return all_sccs;
    }

    void dfs(int node, int& timestamp, vector<vector<int>>& all_sccs) {
        // PASUL 1: un nod nou este vizitat - incrementez timestamp-ul
        found[node] = ++timestamp; // timestamp-ul la care nodul a fost descoperit
        low_link[node] = found[node]; // nodul cunoaste doar propriul timestamp
        nodes_stack.push(node); // adaug nodul in stiva de vizitare
        in_stack[node] = true;

        // PASUL 2: vizitez fiecare vecin
        for (auto neigh : adj[node]) {
            // PASUL 3: verific daca neigh este deja vizitat
            if (parent[neigh] != -1) {
                // PASUL 3.1: actualizez low_link[node] cu informatiile obtinute prin neigh
                // observatie: neigh este in aceeasi CTC cu node doar daca este in stiva de vizitare;
                // altfel, neigh este din alta CTC, deci trebuie ignorat
                if (in_stack[neigh]) {
                    low_link[node] = min(low_link[node], found[neigh]);
                }
                continue;
            }

            // PASUL 4: salvez parintele
            parent[neigh] = node;

            // PASUL 5: vizitez recursiv subarborele copilului
            dfs(neigh, timestamp, all_sccs);

            // PASUL 6: actualizez low_link[node] cu informatiile obtinute prin neigh
            low_link[node] = min(low_link[node], low_link[neigh]);
        }

        // PASUL 7: nodul este radacina unei CTC daca low_link[node] == found[node]
        // (nu exista muchie de la un descendent la un stramos)
        if (low_link[node] == found[node]) {
            // PASUL 7.1: extrag toate elementele de deasupra lui node din stiva => obtin CTC-ul in care node este radacina
            vector<int> scc;
            do {
                auto x = nodes_stack.top();
                nodes_stack.pop();
                in_stack[x] = false;

                scc.push_back(x);
            } while (scc.back() != node); // ma opresc cand node a fost scos din stiva

            // PASUL 7.2: salvez CTC-ul
            all_sccs.push_back(scc);
        }
    }

    void write_output(const vector<vector<int>>& all_sccs) {
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
    std::unique_ptr<Task> task {new (nothrow) Task()};
    if (!task) {
        std::cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    return 0;
}
