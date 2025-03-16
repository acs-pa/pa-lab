// SPDX-License-Identifier: BSD-3-Clause

#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    int n;

    void read_input() {
        ifstream fin("in");
        fin >> n;
        fin.close();
    }

    vector<int> get_result() {
        vector<int> sol(n + 1, 0);

        // TODO: Gasiti o solutie pentru problema damelor pe o tabla de dimensiune
        // n x n.
        //
        // Pentru a plasa o dama pe randul i, coloana j:
        //     sol[i] = j.
        // Randurile si coloanele se indexeaza de la 1 la n.
        //
        // De exemplu, configuratia (n = 5)
        // X----
        // --X--
        // ----X
        // -X---
        // ---X-
        // se va reprezenta prin sol[1..5] = {1, 3, 5, 2, 4}.

        solve_queens(sol);

        return sol;
    }

    void solve_queens(vector<int>& sol) {
        // used[i] = 1, daca coloana i e luata
        vector<bool> used(n + 1, false);

        bkt(1, used, sol);
    }

    // functia intoarce true daca a gasit o solutie
    bool bkt(int i, // linia curenta de completat
        vector<bool>& used, // evidenta coloanelor folosite
        vector<int>& sol) { // solutia gasita

        // daca am gasit o solutie
        if (i == n + 1) {
            // marcam faptul ca am gasit solutia
            return true;
        }

        // incercam sa extindem solutia curenta, punand o dama pe orice coloana libera
        for (int j = 1; j <= n; ++j) {
            // pe coloana j deja mai am o dama pusa
            if (used[j]) {
                continue;
            }

            // Pana acum avem satisfacute urmatoare conditii:
            // - 1. NU se ataca pe rand, deoarece sol[i] are valoare unica
            // - 2. NU se ataca pe coloana, deoarece avem grija ca in sol sa punem valori unice

            // ramane sa verificam conditia 3
            // - 3. Se ataca pe diagonala?

            bool attacked = false; // solutie OK, adica presupun ca nu se ataca

            for (int row = 1; row < i; ++row) {
                // Doua dame cu coordonatele (x1, y1) si (x2, y2) se ataca pe
                // diagonala <==> abs(x1 - x2) == abs(y1 - y2).

                // In cazul nostru, damele sunt (row, sol[row]) si cea pe care
                // vrem sa o punem acum: (i, j).
                if (abs(i - row) == abs(j - sol[row])) {
                    attacked = true;
                    break;
                }
            }

            // Se ataca pe diagonala
            if (attacked) {
                continue; // trec mai departe
            }

            // Step 1: PUNE o dama pe coloana j
            sol[i] = j;
            used[j] = true;

            // Step 2: INCERCAM sa construim recursiv solutia
            bool success = bkt(i + 1, used, sol);
            if (success) {
                // am gasit solutie, ne intoarcem din recursivitate
                // pwp, PA!
                return true;
            }

            // Step 3: SCOATE dama de pe coloana j
            sol[i] = 0;
            used[j] = false;
        }

        // DACA se ajunge aici, atunci nu am reusit sa contruim o solutie
        return false;
    }

    void print_output(const vector<int>& result) {
        ofstream fout("out");
        for (int i = 1; i <= n; i++) {
            fout << result[i] << (i != n ? ' ' : '\n');
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
