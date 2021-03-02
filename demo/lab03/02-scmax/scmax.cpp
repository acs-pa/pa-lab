#include <bits/stdc++.h>
using namespace std;

// v   = vectorul dat
// sol = lungimea SCMAX
// pos = pozitia pe care se termina SCMAX gasit pentru problema data
// solutia se termina cu                       v[pos]
// inainte in solutie apare              v[prec[pos]]
//                                v [prec[prec[pos]]]
// si tot asa... in sir avem sol elemente!
// Din cauza ca stim unde se termina solutia, o vom putea reconstrui in ordine inversa
// (de la sfarsit catre inceput). Putem stoca rezultatul intr-un vector si sa il inversam la final.
void rebuild_scmax(vector<int>& v, int sol, int pos, vector<int>& prec) {
    vector<int> scmax; // vectorul cu numerele din scmax

    for (int i = 1; i <= sol; ++i) {
        // v[pos] este ultimul element pe care il stiu din SCMAX
        scmax.push_back(v[pos]);

        // inainte de el era v[prec[pos]] (..., v[ prec[pos] ], v[ pos ])
        pos = prec[pos];
    }

    reverse(scmax.begin(), scmax.end()); // oglindire vector solutie

    for (int i = 0; i < sol; ++i) {
        cout << scmax[i] << " ";
    }
    cout << "\n";
}

void scmax(int n, vector<int>& v) {
    vector<int> dp(n + 1); // in explicatii indexarea incepe de la 1
    vector<int> prec(n + 1); // dp[1], ..., dp[n] | prec[1], ..., prec[n]

    // caz de baza
    dp[1] = 1; // [ v[1] ] este singurul subsir (crescator) care se termina pe 1
    prec[1] = 0; // nu are precedent

    // caz general
    for (int i = 2; i <= n; ++i) {
        dp[i] = 1; // [ v[i] ] - este un subsir (crescator) care se termina pe i
        prec[i] = 0; // nu are precedent (cel putin momentan)

        // incerc sa il pun pe v[i] la finalul tuturor solutiilor disponibile
        // o solutie se termina cu un element v[j]
        for (int j = 1; j < i; ++j) {
            // solutia triviala: v[i]
            if (v[j] < v[i]) {
                // din (..., v[j]) pot obtine (..., v[j], v[i])
                // (caz in care prec[i] = j)

                // voi alege j-ul curent, cand alegerea imi gaseste o solutie mai buna decat ce am deja
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    prec[i] = j;
                }
            }
        }
    }

    // solutia e maximul din vectorul dp
    int sol = dp[1], pos = 1;
    for (int i = 2; i <= n; ++i) {
        if (dp[i] > sol) {
            sol = dp[i];
            pos = i;
        }
    }

    cout << sol << "\n";
    rebuild_scmax(v, sol, pos, prec);
}

int main() {
    int n;
    vector<int> v;

    cin >> n;
    v.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> v[i];
    }

    // afiseaza solutia
    scmax(n, v);

    return 0;
}

// Compile:
// $ make
//
// Run:
// $ ./scmax
// 6
// 100 12 13 -1 15 14
//
// 3
// 12 13 15
//
