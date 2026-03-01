// SPDX-License-Identifier: BSD-3-Clause

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

// constanta modulo folosita in aceasta problema
#define INF ((int)1e9)
// sau
// #define MOD 100000000
// (varianta 2 e mai ușor de busit, sesizați? :p)

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    int n, S;
    vector<int> v;

    void read_input() {
        ifstream fin("in");
        fin >> n >> S;
        v.push_back(-1); // adaugare element fictiv - indexare de la 1
        for (int i = 1, e; i <= n; i++) {
            fin >> e;
            v.push_back(e);
        }
        fin.close();
    }

    int get_result() {
        // TODO: Aflati numarul minim de monede ce poate fi folosit pentru a obtine
        // suma S. Tipurile monedelor sunt stocate in vectorul v, de dimensiune n.

        return coing_change();
    }

    // T = O(n * S)
    // S = O(S)
    int coing_change() {
        // dp[i] = numarul minim de monede cu care pot forma suma i
        vector<int> dp(S + 1, INF);
        // initial am valori foarte mari in dinamica (presupun ca nu se poate forma suma S)
        // in definirea recurentei am spus practic ce mi se cerea in enunt
        // Sesizati? :p

        // cazul de baza: suma 0 nu necesita monede
        dp[0] = 0;

        // cazul general: suma s; s se poate descompune ca s = s1 + s2... cine sunt s1 si s2?
        // 		O varianta simpla: s1 = o moneda (oarecare)
        // s     = c      + (s - c)
        //        1 coin     restul
        // dp[s] =  1     + dp[s-c]
        // 		Revenind la notatii:  i  =     v[j]     + (i - v[j])
        //                         dp[i] = min( 1       + dp[i - v[j]]), j = 1:n
        for (int i = 1; i <= S; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (v[j] <= i) {
                    dp[i] = min(dp[i], dp[i - v[j]] + 1);
                }
            }
        }

        // s-a putut forma suma S? (dp[S] != INF)
        // DA: dp[S] este numarul minim de monede cu care am format pe S
        // NU: ghinion... nu se poate forma suma S
        return (dp[S] != INF ? dp[S] : -1);
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
