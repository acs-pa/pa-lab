#include <bits/stdc++.h>
using namespace std;

// numarul maxim de noduri
#define NMAX 50005

// valoare mai mare decat orice distanta din graf
#define INF (1 << 30)

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    // n = numar de noduri, m = numar de muchii
    int n, m;
    // adj[x] = lista de adiacenta a nodului x
    // perechea (y, w) semnifica muchie de la x la y de cost w: (x, y, w)
    vector<pair<int, int>> adj[NMAX];
    // nodul sursa
    int source;

    void read_input() {
        ifstream fin("in");
        fin >> n >> m >> source;
        for (int i = 1, x, y, w; i <= m; i++) {
            fin >> x >> y >> w;
            adj[x].push_back({y, w});
        }
        fin.close();
    }

    vector<int> get_result() {
        //
        // TODO: Gasiti distantele minime de la nodul source la celelalte noduri
        // folosind Dijkstra pe graful orientat cu n noduri, m arce stocat in adj.
        //     d[node] = costul minim / lungimea minima a unui drum de la source la nodul
        // node;
        //     d[source] = 0;
        //     d[node] = -1, daca nu se poate ajunge de la source la node.
        //
        // Atentie:
        // O muchie este tinuta ca o pereche (nod adiacent, cost muchie):
        //     adj[x][i] == (y, w) - unde y este al i-lea vecin al lui x, iar (x, y) are cost w: (x, y, w)
        //

        vector<int> d(n + 1, 0);
        return d;
    }

    void print_output(vector<int> result) {
        ofstream fout("out");
        for (int i = 1; i <= n; i++) {
            fout << result[i] << " ";
        }
        fout << "\n";
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
