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

        return solve_dp2_n();
    }

    // Solutia 3: DP - alta idee
    // T = O(n)
    // S = O(n)
    int solve_dp2_n() {
        // dp_even[i] = numarul de subsiruri cu suma PARA folosind v[1..i]
        //  dp_odd[i] = numarul de subsiruri cu suma IMPARA folosind v[1..i]
        vector<int> dp_even(n + 1);
        vector<int> dp_odd(n + 1);
        // Observatie: Nu spunem daca acele subsiruri se termina sau nu cu v[i]!
        // Raspunsul este: dp_even[n]

        // cazuri de baza
        dp_even[0] = 0;
        dp_odd[0] = 0;

        for (int i = 1; i <= n; ++i) {
            if (v[i] % 2 == 0) { // elementul curent e par
                // subsirurile cu suma para sunt:
                // - toate subsirutile cu suma para de dinainte (dp_even[i - 1])
                // - toate subsirutile cu suma para de dinainte la care adaugam v[i] (dp_even[i - 1])
                // - subsirul format doar din v[i]
                dp_even[i] = (dp_even[i - 1] + dp_even[i - 1] + 1) % MOD;

                // subsirurile cu suma impara sunt:
                // - toate subsirurile cu suma impara de dinainte (dp_odd[i - 1])
                // - toate subsirurile cu suma impara de dinainte la care adaugam v[i] (dp_odd[i - 1])
                dp_odd[i] = (dp_odd[i - 1] + dp_odd[i - 1]) % MOD;
            } else { // elementul curent e impar
                // subsirurile cu suma para sunt:
                // - toate subsirurile cu suma para de dinainte (dp_even[i - 1])
                // - toate subsirurile cu suma impara de dinainte la care adaugam v[i] (dp_odd[i - 1])
                dp_even[i] = (dp_even[i - 1] + dp_odd[i - 1]) % MOD;

                // subsirurile cu suma impara sunt:
                // - toate subsirurile cu suma impara de dinainte (dp_odd[i - 1])
                // - toate subsirurile cu suma para de dinainte la care adaugam v[i] (dp_even[i - 1])
                // - subsirul format doar din v[i]
                dp_odd[i] = (dp_odd[i - 1] + dp_even[i - 1] + 1) % MOD;
            }
        }

        // numarul de subsiruri cu SUMA PARA folosind v[1..n]
        return dp_even[n];
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
