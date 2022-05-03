#include <bits/stdc++.h>
using namespace std;

// numarul maxim de noduri
#define NMAX 105

class Task {
public:
    void solve() {
        read_input();
        compute();
        print_output();
    }

private:
    // n = numar de noduri
    int n;

    // w[x]y] = costul muchiei de la x la y: (x, y, w[x][y])
    // (w[x][y] = 0 - muchia lipseste)
    int w[NMAX][NMAX];

    // d[x][y] = lungimea drumului minim de la x la y
    int d[NMAX][NMAX];

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

    void compute() {
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
    }

    void print_output() {
        ofstream fout("out");
        for (int x = 1; x <= n; x++) {
            for (int y = 1; y <= n; y++) {
                fout << d[x][y] << ' ';
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
