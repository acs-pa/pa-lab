// SPDX-License-Identifier: BSD-3-Clause

#include <algorithm>        // max
#include <iostream>         // cin, cout
#include <vector>           // vector
using namespace std;

int rucsac(int n, int W, vector<int>& w, vector<int>& p) {
    // dp este o matrice de dimensiune (n + 1)x(W+1)
    // pentru ca folosim dp[0][*] pentru multimea vida
    //                   dp[*][0] pentru situatia in care ghiozdanul are capacitate 0
    vector<vector<int>> dp(n + 1);
    for (int i = 0; i <= n; ++i) {
        dp[i].resize(W + 1);
    }

    // cazul de baza
    for (int cap = 0; cap <= W; ++cap) {
        dp[0][cap] = 0;
    }

    // cazul general
    for (int i = 1; i <= n; ++i) {
        for (int cap = 0; cap <= W; ++cap) {
            // nu folosesc obiectu i => e solutia de la pasul i - 1
            dp[i][cap] = dp[i - 1][cap];

            // folosesc obiectul i, deci trebuie sa rezerv w[i] unitati in rucsac
            // inseamna ca inainte trebuie sa ocup maxim cap - w[i] unitati
            if (cap - w[i] >= 0) {
                int sol_aux = dp[i - 1][cap - w[i]] + p[i];

                dp[i][cap] = max(dp[i][cap], sol_aux);
            }
        }
    }

    return dp[n][W];
}

int main() {
    int n, W;
    vector<int> p, w;

    // citeste datele
    cin >> n >> W;
    p.resize(n + 1); // redimensioneaza v sa aiba n elememnte
    w.resize(n + 1); // redimensioneaza v sa aiba n elememnte

    for (int i = 1; i <= n; ++i) {
        cin >> w[i] >> p[i];
    }

    // afiseaza solutia
    cout << rucsac(n, W, w, p) << "\n";

    return 0;
}

// Compile:
// $ make
// Run:
// $ ./rucsac
// 5 3
// 3 6
// 3 3
// 1 2
// 1 8
// 2 5
//
// 13
