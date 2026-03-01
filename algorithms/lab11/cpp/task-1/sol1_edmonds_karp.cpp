// SPDX-License-Identifier: BSD-3-Clause

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <memory> // unique_ptr pentru Task
#include <queue>
#include <utility>
#include <vector>
using namespace std;

// numarul maxim de noduri
#define NMAX 1005

// valoare mai mare decat max_flow
#define INF (1 << 30)

// structura folosita pentru a stoca daca exista drum de ameliorare
// si care este acesta.
struct AugmentedPath {
    bool has_path;
    vector<pair<int, int>> path;
    AugmentedPath(bool has_path, const vector<pair<int, int>>& path)
        : has_path(has_path)
        , path(path) { }

    operator bool() const { return has_path; }
};

class Task {
public:
    void solve() {
        read_input();
        write_output(get_result());
    }

private:
    // n = numar de noduri, m = numar de muchii
    int n, m;

    // adj[i] = lista de adiacenta a nodului i
    vector<int> adj[NMAX];

    // c[i][j] = capacitatea arcului i -> j
    int c[NMAX][NMAX];

    void read_input() {
        ifstream fin("in");
        fin >> n >> m;
        memset(c, 0, sizeof(c));
        for (int i = 1, u, v, capacity; i <= m; i++) {
            // x -> y de capacitate cap
            fin >> u >> v >> capacity;
            adj[u].push_back(v);
            adj[v].push_back(u); // stocam si arcul invers

            // Presupunem existenta mai multor arce u -> v cu capacitati c1, c2, ...
            // Comprimam intr-un singur arc x -> y cu capacitate
            // c[x][y] = c1 + c2 + ...
            c[u][v] += capacity;
        }
        fin.close();
    }

    int get_result() {
        //
        // TODO: Calculati fluxul maxim pe graful orientat dat.
        // Sursa este nodul 1.
        // Destinatia este nodul n.
        //
        // In adj este stocat graful neorientat obtinut dupa ce se elimina orientarea
        // arcelor, iar in cap sunt stocate capacitatile arcelor.
        // De exemplu, un arc (u, v) de capacitate cap va fi tinut astfel:
        // c[u][v] = cap, adj[u] contine v, adj[v] contine u.
        //
        return get_maxflow(n + 1, adj, 1, n);
    }

    int get_maxflow(int nodes, vector<int> adj[NMAX], int source, int sink) {
        // Initial nu exista flux in retea.
        int total_flow = 0;

        int f[NMAX][NMAX];
        for (int u = 1; u <= nodes; ++u) {
            for (int v = 1; v <= nodes; ++v) {
                f[u][v] = 0;
            }
        }

        // Cat timp am un drum de ameliorare de la source la sink
        while (auto res = bfs(nodes, adj, source, sink, f, c)) {
            auto& [_, path] = res;

            int rc = INF;
            // Calculare capacitate reziduala pentru drumul de ameliorare
            for (auto& [u, v] : path) {
                rc = min(rc, c[u][v] - f[u][v]);
            }

            // pompam fluxul
            total_flow += rc;
            //  actualizez drumul
            for (auto& [u, v] : path) {
                f[u][v] += rc; //  adaug fluxul pe muchia de pe drum
                f[v][u] -= rc; //  scad  fluxul in sens invers
            }
        }

        return total_flow;
    }

    // Se realizeaza o parcugere BFS de la source la sink.
    // Se incearca unui drum de ameliorare.
    // Se poate merge pe un arc i->j doar daca capacitatea reziduala este strict
    // pozitiva
    // a.k.a. cap[i][j] - flow[i][j] > 0, pentru arcul i->j
    //         (muchia i->j nu e saturata)

    AugmentedPath bfs(int nodes, vector<int> adj[NMAX], int source, int sink, int f[NMAX][NMAX], int c[NMAX][NMAX]) {

        // initial niciun nod nu are parinte
        vector<int> p(nodes, -1);

        queue<int> q;

        // sursa este radacina in arborele BFS - singura cu parinte 0
        q.push(source);
        p[source] = 0;

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (auto& neigh : adj[node]) {
                // daca x NU are parinte si muchia node->neigh NU este saturata
                if (p[neigh] == -1 && f[node][neigh] < c[node][neigh]) {
                    p[neigh] = node;
                    q.push(neigh);
                }
            }
        }

        // daca p[sink] == -1, nu se poate gasi un drum de ameliorare
        if (p[sink] == -1) {
            return {false, {}};
        }

        // construim un vector cu toate muchiile de pe drumul de ameliorare
        vector<pair<int, int>> path;
        int node = sink;
        while (p[node] != 0) {
            path.push_back({p[node], node});
            node = p[node];
        }
        reverse(path.begin(), path.end());
        return {true, path};
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
