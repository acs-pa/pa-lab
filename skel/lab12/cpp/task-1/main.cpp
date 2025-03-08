#include <cstring>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

// numarul maxim de noduri
#define NMAX 1005

// valoare mai mare decat max_flow
#define INF (1 << 30)

// structura folosita pentru a stoca daca exista drum de ameliorare
// si care este acesta.
struct AugmentedBFS {
    bool has_path;
    vector<pair<int, int>> path;
    AugmentedBFS(bool has_path, const vector<pair<int, int>>& path)
        : has_path(has_path)
        , path(path) { }

    operator bool() const { return has_path; }
};

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
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
        int total_flow = 0;
        return total_flow;
    }

    void print_output(int result) {
        ofstream fout("out");
        fout << result << '\n';
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
