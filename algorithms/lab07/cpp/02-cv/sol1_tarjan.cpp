// SPDX-License-Identifier: BSD-3-Clause

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <unordered_set>
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
        return tarjan_cv();
    }

    vector<int> tarjan_cv() {
        // PASUL 1: initializez rezultatele
        parent = vector<int>(n + 1, -1);
        found = vector<int>(n + 1, -1);
        low_link = vector<int>(n + 1, -1);

        // PASUL 2: vizitez toate nodurile
        unordered_set<int> all_cvs;
        int timestamp = 0; // timestamp global
        for (int node = 1; node <= n; ++node) {
            if (parent[node] == -1) { // nod nevizitat
                parent[node] = node; // conventie: parintele radacinii este chiar radacina

                // PASUL 3: pornesc o noua parcurgere DFS pe acest subarbore
                dfs(node, timestamp, all_cvs);
            }
        }

        return {all_cvs.begin(), all_cvs.end()};
    }

    void dfs(int node, int& timestamp, unordered_set<int>& all_cvs) {
        // PASUL 1: un nod nou este vizitat - incrementez timestamp-ul
        found[node] = ++timestamp; // timestamp-ul la care nodul a fost descoperit
        low_link[node] = found[node]; // nodul cunoaste doar propriul timestamp

        // PASUL 2: vizitez fiecare vecin
        int children = 0; // numar toti copiii lui node
        for (auto neigh : adj[node]) {
            // PASUL 3: verific daca neigh este deja vizitat
            if (parent[neigh] != -1) {
                // PASUL 3.1: actualizez low_link[node] cu informatiile obtinute prin neigh
                // observatie: pentru ca graful este neorientat, trebuie ignorata muchia catre parinte
                // (valoarea found a parintelui este mereu mai mica decat valoarea found a lui node)
                if (neigh != parent[node]) {
                    low_link[node] = min(low_link[node], found[neigh]);
                }
                continue;
            }

            // PASUL 4: salvez parintele
            parent[neigh] = node;
            ++children; // numar copilul

            // PASUL 5: vizitez recursiv subarborele copilului
            dfs(neigh, timestamp, all_cvs);

            // PASUL 6: actualizez low_link[node] cu informatiile obtinute prin neigh
            low_link[node] = min(low_link[node], low_link[neigh]);

            // PASUL 7.1: node este un CV daca i): *) node NU este radacina si **) low_link[neigh] >= found[node]
            if (parent[node] != node && low_link[neigh] >= found[node]) {
                all_cvs.insert(node);
            }
        }

        // PASUL 7.2: node este un CV daca i)): *) node este radacina si **) are cel putin 2 copii
        if (parent[node] == node && children > 1) {
            all_cvs.insert(node);
        }
    }

    void write_output(const vector<int>& all_cvs) {
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
    std::unique_ptr<Task> task {new (nothrow) Task()};
    if (!task) {
        std::cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    return 0;
}
