// SPDX-License-Identifier: BSD-3-Clause

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

struct Result {
    int len; // rezultat pentru cerinta 1
    vector<int> subsequence; // rezultat pentru cerinta 2
};

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    int n, m;
    vector<int> v;
    vector<int> w;

    void read_input() {
        ifstream fin("in");
        fin >> n >> m;

        v.push_back(-1); // adaugare element fictiv - indexare de la 1
        for (int i = 1, e; i <= n; i++) {
            fin >> e;
            v.push_back(e);
        }

        w.push_back(-1); // adaugare element fictiv - indexare de la 1
        for (int i = 1, e; i <= m; i++) {
            fin >> e;
            w.push_back(e);
        }

        fin.close();
    }

    Result get_result() {
        // TODO: Aflati cel mai lung subsir comun intre v (de lungime n)
        // si w (de lungime m).
        // Se puncteaza separat urmatoarele 2 cerinte:
        // 2.1. Lungimea CMLSC. Rezultatul pentru cerinta aceasta se va pune in
        // ``result.len``.
        // 2.2. Reconstructia CMLSC. Se puncteaza orice subsir comun maximal valid.
        // Solutia pentru aceasta cerinta se va pune in ``result.subsequence``.

        return cmlsc();
    }

    // T = O(n *m) (n*m + L; unde L este lungimea solutiei si L <= min(n,m))
    // S = O(n *m) - stocam tabloul dp
    Result cmlsc() {
        Result result;
        result.len = 0;

        // deoarece avem doua dimensiuni in input (doi vectori), o solutie cu o dimensiune (dp[i] = ...)
        // nu poate sa stocheze informatia necesara (asemantor cu RUCSAC)

        // dp[i][j] = LUNGIMEA celui mai lung subsir crescator maximal
        //            format cu elementele din vectorii v[1..i] si w[1..j]
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        // dp are dimensiunile n x m - indexare de la 1
        //			Obs. Si aici am numit recurenta pornind de la ce ni se cera in enunt!

        // Caz de baza:
        // dp[0][j] = 0 (daca nu luam element din primul vector)
        // dp[i][0] = 0 (daca nu luam element din al doilea vector)
        // P.S. Aceste cazuri au fost tratate prin initializarea lui dp. (Sesizati? :p)

        // Cazul general
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (v[i] == w[j]) { // (v[i], w[j]) pot extinde cu 1 o solutie care se termina cel mult pe (i-1, j-1)
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else { // v[i], w[j] nu pot extinde impreuna o solutie
                    // v[i] poate extinde o solutie, caz in care se cupleaza cu un w[k], k < j (k = 1...j-1)
                    // w[j] poate extinde o solutie, caz in care se cupleaza cu un v[k], k < i (k = 1...i-1)
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        // lungimea ceruta se afla in dp[n][m]
        result.len = dp[n][m];

        // daca nu avem ce reconstitui, ne oprim
        if (result.len == 0) {
            return result;
        }

        // vom reconstitui solutia de la sfarsit catre inceput
        int i = n, j = m;
        while (i > 0 && j > 0) {
            if (v[i] == w[j]) { // v[i], w[j] a extins candva o solutie
                result.subsequence.push_back(v[i]); // adaugam elementul v[i] la solutie

                --i; // i,j a extins i-1, j-1 (din recurenta)
                --j;
                continue;
            }

            if (dp[i][j] == dp[i - 1][j]) {
                --i; // ori w[j] a extins singur o solutie
            } else {
                --j; // ori v[i] a extins singur o solutie
            }
        }

        // inversam solutia
        reverse(result.subsequence.begin(), result.subsequence.end());

        return result;
    }

    void print_output(Result result) {
        ofstream fout("out");
        fout << result.len << '\n';
        for (int x : result.subsequence) {
            fout << x << ' ';
        }
        fout << '\n';
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
