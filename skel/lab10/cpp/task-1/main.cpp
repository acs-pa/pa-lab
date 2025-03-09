// SPDX-License-Identifier: BSD-3-Clause

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

// numarul maxim de noduri
#define NMAX 105

// structura folosita pentru a stoca matricea de distante, matricea
// de parinti folosind algoritmul Roy-Floyd.
struct RoyFloydResult {
    vector<vector<int>> d;
    vector<vector<int>> p;

    RoyFloydResult(const vector<vector<int>>& d, const vector<vector<int>>& p)
        : d(d)
        , p(p) { }
};

class Task {
public:
    void solve() {
        read_input();
        print_output(compute());
    }

private:
    // n = numar de noduri
    int n;

    // w[x]y] = costul muchiei de la x la y: (x, y, w[x][y])
    // (w[x][y] = 0 - muchia lipseste)
    //
    // In aceasta problema, costurile sunt strict pozitive.
    int w[NMAX][NMAX];

    void read_input() {
        ifstream fin("in");
        fin >> n;
        for (int x = 1; x <= n; x++) {
            for (int y = 1; y <= n; y++) {
                fin >> w[x][y];
            }
        }
        fin.close();
    }

    RoyFloydResult compute() {
        //
        // TODO: Gasiti distantele minime intre oricare doua noduri, folosind Roy-Floyd
        // pe graful orientat cu n noduri, m arce stocat in matricea ponderilor w
        // (declarata mai sus).
        //
        // Atentie:
        // O muchie (x, y, w[x][y]) este reprezentata astfel in matricea ponderilor:
        //     w[x][y] este costul muchiei de la x la y
        // Daca nu exista o muchie intre doua noduri x si y, in matricea ponderilor:
        //     w[x][y] = 0;
        //
        // Trebuie sa populati matricea d[][] (declarata mai sus):
        //     d[x][y] = distanta minima intre nodurile x si y, daca exista drum.
        //     d[x][y] = 0 daca nu exista drum intre x si y.
        //          * implicit: d[x][x] = 0 (distanta de la un nod la el insusi).
        //

        vector<vector<int>> d(n + 1, vector<int>(n + 1));
        vector<vector<int>> p(n + 1, vector<int>(n + 1));

        return {d, p};
    }

    void print_output(const RoyFloydResult& res) {
        ofstream fout("out");
        for (int x = 1; x <= n; x++) {
            for (int y = 1; y <= n; y++) {
                fout << res.d[x][y] << ' ';
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
