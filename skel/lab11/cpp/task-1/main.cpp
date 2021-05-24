#include <bits/stdc++.h>
using namespace std;

// numarul maxim de noduri
#define NMAX 1005

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

    // cap[i][j] = capacitatea arcului i -> j
    int cap[NMAX][NMAX];

    void read_input() {
        ifstream fin("in");
        fin >> n >> m;
        memset(cap, 0, sizeof cap);
        for (int i = 1, x, y, c; i <= m; i++) {
            // x -> y de capacitate c
            fin >> x >> y >> c;
            adj[x].push_back(y);
            adj[y].push_back(x);

            // Presupunem existenta mai multor arce x -> y cu capacitati c1, c2, ...
            // Comprimam intr-un singur arc x -> y cu capacitate
            // cap[x][y] = c1 + c2 + ...
            cap[x][y] += c;
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
        // De exemplu, un arc (x, y) de capacitate c va fi tinut astfel:
        // cap[x][y] = c, adj[x] contine y, adj[y] contine x.
        //
        int max_flow = 0;

        return max_flow;
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
