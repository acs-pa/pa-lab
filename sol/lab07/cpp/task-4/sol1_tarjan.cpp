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
    struct Edge {
        int x;
        int y;

        Edge() { }
        Edge(int x, int y)
            : x(x)
            , y(y) { }
    };

    // numarul maxim de noduri
    static constexpr int NMAX = (int)1e5 + 5; // 10^5 + 5 = 100.005

    // n = numar de noduri, m = numar de muchii
    int n, m;
    // adj[i] = lista de adiacenta a nodului i
    vector<int> adj[NMAX];

    // ordinea de vizitare
    // found[node] = timpul de start a lui node in parcurgerea DFS
    // in laborator found se numeste idx
    vector<int> found;

    // low_link[node] = min { found[x] | x este accesibil din node }
    // adica timpul minim al unui nou
    vector<int> low_link;

    // stiva folosita pentru a reconstrui componentele biconexe
    stack<Edge> sc;

    // parent[i] = parintele nodului i
    vector<int> parent;

    // vector in care retin componentele biconexe
    // all_bccs[i] = componenta biconexa cu indicele i
    vector<vector<int>> all_bccs;

    void read_input() {
        ifstream fin("in");
        fin >> n >> m;
        for (int i = 1, x, y; i <= m; i++) {
            fin >> x >> y;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        fin.close();
    }

    vector<vector<int>> get_result() {
        // TODO: Gasiti componentele biconexe ale grafului neorientat stocat cu liste
        // de adiacenta in adj.

        tarjan();
        return all_bccs;
    }

    void tarjan() {
        found = vector<int>(n + 1, -1);
        low_link = vector<int>(n + 1, 0);
        parent = vector<int>(n + 1, 0);

        // momentul curent de start
        // pe masura ce vizita nodurile el va creste (++)
        int current_start = 0;

        for (int i = 1; i <= n; ++i) {
            if (found[i] == -1) {
                // acest nod nu a fost descoperit, deci il putem folosi
                // marcam nodul i ca fiind radacina
                parent[i] = 0;

                // pornim o noua cautare din nodul respectiv
                dfs(i, current_start);
            }
        }
    }

    void dfs(int node, int& current_start) {
        // incep un nou nod, deci un nod timp de start
        ++current_start;

        // atat found, cat si low_link vor primi valoarea lui current_start
        found[node] = current_start;
        low_link[node] = current_start;

        // initializez numarul de copii al nodului curent cu 0
        int children = 0;

        for (auto& neigh : adj[node]) {
            if (found[neigh] == -1) { // deci il pot vizita
                // parintele nodului in care ma duc este chiar nodul curent
                parent[neigh] = node;

                // retin muchiile de avansare
                sc.push(Edge(node, neigh));

                // cresc numarul de copii
                ++children;

                // pornesc un nou dfs
                dfs(neigh, current_start);

                // actualizez low_link:
                // - low_link[node]  = timpul de start cel mai mic pe care NODE  il
                // cunoaste
                // - low_link[neigh] = timpul de start cel mai mic pe care neigh il
                // cunoaste
                // Tot ce acceseaza neigh (Ex. neigh - ... - x) poate accesa si node
                // (ex. node - neigh - ... - x)
                low_link[node] = min(low_link[node], low_link[neigh]);

                // daca nu au exista muchii de intoarcere spre un STRAMOS al lui nde
                // inseamna ca nodul curent este punct de articulatie
                // adica neigh nu a putut sa sara inapoi in arbore PESTE node

                // daca am gasit un punct de articulatie inseamna ca am descoperit
                // o noua componenta biconexa
                if (low_link[neigh] >= found[node]) {
                    get_bcc(Edge(node, neigh));
                }
            } else {
                // !!!graful fiind neorientat as updata fiecare copil in functie de
                // parintele sau - trebuie sa am grija sa nu fac asta
                if (neigh != parent[node]) {
                    // am gasit o muchie de intoarcere
                    low_link[node] = min(low_link[node], found[neigh]);
                }
            }
        }
    }

    void get_bcc(Edge target_edge) {
        // construim o noua componenta biconexa
        vector<int> current_bcc;

        // extragem muchii din stiva pana am extras muchia E
        Edge current_edge = Edge(-1, -1);

        // cat timp nu am extras muchia dorita
        while (!((current_edge.x == target_edge.x) && (current_edge.y == target_edge.y))) {
            current_edge = sc.top();
            sc.pop();

            // adaug capetele muchiei in bcc
            current_bcc.push_back(current_edge.x);
            current_bcc.push_back(current_edge.y);
        }

        // trebuie sa eliminam duplicatele
        // vom sorta vectorul si vom folosi functia unique
        // pentru detalii, vezi: http://en.cppreference.com/w/cpp/algorithm/unique
        sort(current_bcc.begin(), current_bcc.end());
        auto it = unique(current_bcc.begin(), current_bcc.end());
        current_bcc.erase(it, current_bcc.end());

        // current_bcc este o BCC valida
        all_bccs.push_back(current_bcc);
    }

    void print_output(const vector<vector<int>>& result) {
        ofstream fout("out");
        fout << result.size() << '\n';
        for (auto& bcc : result) {
            for (auto node : bcc) {
                fout << node << " ";
            }
            fout << "\n";
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
