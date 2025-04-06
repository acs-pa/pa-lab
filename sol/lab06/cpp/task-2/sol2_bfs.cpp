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
    static constexpr int NMAX = (int)1e5 + 5; // 10^5 + 5 = 100.005

    // n = numar de noduri, m = numar de muchii/arce
    int n, m;

    // adj[node] = lista de adiacenta a nodului node
    // exemplu: daca adj[node] = {..., neigh, ...} => exista arcul (node, neigh)
    vector<int> adj[NMAX];

    // in_degree[node] = gradul intern al nodului node
    vector<int> in_degree;

    void read_input() {
        ifstream fin("in");
        fin >> n >> m;

        // grad intern 0 pentru toate nodurile... momentan
        in_degree = vector<int>(n + 1, 0);

        for (int i = 1, x, y; i <= m; i++) {
            fin >> x >> y;
            adj[x].push_back(y); // arc (x, y)
            ++in_degree[y]; // numar inca o muchie care intra in y
        }
        fin.close();
    }

    vector<int> get_result() {
        // TODO: Faceti sortarea topologica a grafului stocat cu liste de adiacenta din adj.
        // *******
        // ATENTIE: nodurile sunt indexate de la 1 la n.
        // *******

        return solve_bfs(); // BFS: O(n + m);
    }

    vector<int> solve_bfs() {
        // Step 0: initializare topsort - permutare vida initial
        vector<int> topsort;

        // Step 1: declaram o coada in care putem baga noduri
        queue<int> q;

        // Step 2: pasul initial: pun in coada TOATE nodurile cu grad intern 0
        for (int node = 1; node <= n; ++node) {
            if (in_degree[node] == 0) {
                q.push(node);
            }
        }

        // Step 3: parcurg in latime graful
        while (!q.empty()) {
            // 3.1: SCOT primul nod din coada
            int node = q.front();
            q.pop();

            // adaug la solutie elementul scos
            topsort.push_back(node);

            // 3.2 Ii parcurg toti vecinii
            for (auto neigh : adj[node]) {
                // sterg muchia node->neigh
                // obs1. NU e nevoie sa o sterg la propriu
                //       Daca nu am cicluri, nu se va ajunge aici
                // obs2. Simulez stergerea prin scaderea gradului intern a lui neigh
                --in_degree[neigh];

                // daca neigh a ajuns nod cu grad intern 0, atunci este adaugat in coada
                if (in_degree[neigh] == 0) {
                    q.push(neigh);
                }
            }
        }

        // Step 4: verifica ca topsort chiar reprezinta o sortare topologica valida
        // Ce inseamna asta? S-au sters toate muchiile din graf.
        // Daca nu s-a sters tot, atunci graful este ciclic!
        bool is_valid = true;
        for (int node = 1; node <= n; ++node) {
            if (in_degree[node] > 0) {
                is_valid = false;
                break;
            }
        }

        if (is_valid) {
            return topsort; // sortarea topologica obtinuta
        } else {
            return {}; // vector gol == nu se poate face o sortare topologica
        }
    }

    void print_output(const vector<int>& topsort) {
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
