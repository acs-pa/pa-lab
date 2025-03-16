// SPDX-License-Identifier: BSD-3-Clause

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

// constanta modulo folosita in aceasta problema
#define MOD ((int)1e9 + 7)
// sau
// #define MOD 100000007
// (varianta 2 e mai ușor de busit, sesizați? :p)

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    int n;
    vector<int> v;

    void read_input() {
        ifstream fin("in");
        fin >> n;
        v.push_back(-1); // adaugare element fictiv - indexare de la 1
        for (int i = 1, e; i <= n; i++) {
            fin >> e;
            v.push_back(e);
        }
        fin.close();
    }

    int get_result() {
        // Calculati numarul de subsiruri ale lui v cu suma numerelor para si
        // returnati restul impartirii numarului la 10^9 + 7 (vezi macro-ul MOD).

        // Sunt prezentate 4 solutii.
        // Oricare dintre dinamici s-a punctat cu 10 la laborator.
        // La teme/test va trebui sa alegeti pe cea care intra in timp!
        // (Daca intra toate, atunci alegeti una. Ideal ar fi sa fie cea mai rapida!)

        return solve_math();
    }

    // Solutia 4: math
    // - daca toate numerele sunt pare: 2^n - 1
    // -                        altfel: 2^(n-1) - 1
    // T = O(n) - tot parcurgem vectorul sa vedem daca toate sunt pare
    // S = O(1) - nu stocam tabloul dp (inputul nu a fost luat in calcul)
    int solve_math() {
        bool all_even = true;
        for (int i = 1; i <= n; ++i) {
            all_even &= (v[i] % 2 == 0);
        }

        int sol = (all_even ? log_pow(2, n) - 1 : log_pow(2, n - 1) - 1);
        sol = (sol + MOD) % MOD; // atentie! am scazut 1, expresia poate fi negativa
                                 // Testele nu surprind acest caz. La teme/test trebuie sa fiti atenti!

        return sol;
    }

    // returneaza base ^ exp % MOD
    int log_pow(int base, int exp) {
        if (!exp) {
            return 1;
        }

        int tmp = 1;
        while (exp != 1) {
            if (exp % 2 == 0) {
                base = (1LL * base * base) % MOD;
                exp /= 2;
            } else {
                tmp = (1LL * tmp * base) % MOD;
                exp--;
            }
        }

        return (1LL * tmp * base) % MOD;
    }

    void print_output(int result) {
        ofstream fout("out");
        fout << result;
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
