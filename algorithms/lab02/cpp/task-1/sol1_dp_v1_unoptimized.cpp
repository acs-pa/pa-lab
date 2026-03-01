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

        return solve_dp1_nn();
    }

    // Solutia 1: DP - neoptimizata
    // T = O(n ^ 2)
    // S = O(n)
    int solve_dp1_nn() {
        // dp_even[i] = numarul de subsiruri cu suma PARA folosind v[1..i]
        //              SI care se termina cu v[i]
        // dp_odd[i] = numarul de subsiruri cu suma IMPARA folosind v[1..i]
        //              SI care se termina cu v[i]
        vector<int> dp_even(n + 1);
        vector<int> dp_odd(n + 1);
        // Raspunsul este: suma(dp_even[i])

        // cazuri de baza
        dp_even[0] = 0;
        dp_odd[0] = 0;

        for (int i = 1; i <= n; ++i) {
            if (v[i] % 2 == 0) { // PAR
                dp_even[i] = 1; // v[i] singur
                dp_odd[i] = 0; // v[i] NU poate fi singur

                // v[i] poate fi adaugat la
                // - orice subsir cu suma PARA   => suma PARA
                // - orice subsir cu suma IMPARA => suma IMPARA
                for (int j = 1; j < i; ++j) {
                    dp_even[i] = (dp_even[i] + dp_even[j]) % MOD;
                    dp_odd[i] = (dp_odd[i] + dp_odd[j]) % MOD;
                }
            } else { // IMPAR
                dp_even[i] = 0; // v[i] NU poate fi singur
                dp_odd[i] = 1; // v[i] singur

                // v[i] poate fi adauga la
                // - orice subsir cu suma PARA   => suma IMPARA
                // - orice subsir cu suma IMPARA => suma PARA
                for (int j = 1; j < i; ++j) {
                    dp_even[i] = (dp_even[i] + dp_odd[j]) % MOD;
                    dp_odd[i] = (dp_odd[i] + dp_even[j]) % MOD;
                }
            }
        }

        // raspunsul este R = sum(dp_even[i]), i = 1:n
        // dp_even[1] = numarul de subsiruri cu sumara para care se termina cu v[1]
        // dp_even[2] = numarul de subsiruri cu sumara para care se termina cu v[2]
        // ...
        // dp_even[i] = numarul de subsiruri cu sumara para care se termina cu v[i]
        // ...
        // Numarul total de subsiruri cu suma para se obtine prin insumare

        int sol = 0;
        for (int i = 1; i <= n; ++i) {
            sol = (sol + dp_even[i]) % MOD;
        }

        return sol;
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
