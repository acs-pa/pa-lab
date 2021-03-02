#include <bits/stdc++.h>
using namespace std;

void SSM(int n, vector<int>& v) {
    vector<int> dp(n); // vector cu n elemente
    vector<int> start(n);

    // caz de baza
    dp[0] = v[0];
    start[0] = 0;

    // caz general
    for (int i = 1; i < n; ++i) {
        if (dp[i - 1] >= 0) {
            // extinde la dreapta cu v[i]
            dp[i] = dp[i - 1] + v[i];
            start[i] = start[i - 1];
        } else {
            // incep o noua secventa
            dp[i] = v[i];
            start[i] = i;
        }
    }

    // solutia e maximul din vectorul dp
    int sol = dp[0], pos = 0;
    for (int i = 1; i < n; ++i) {
        if (dp[i] > sol) {
            sol = dp[i];
            pos = i;
        }
    }

    cout << sol << " " << start[pos] + 1 << " " << pos + 1 << "\n";
}

int main() {
    int n;
    vector<int> v;

    // citeste datele
    cin >> n;
    v.resize(n); // redimensioneaza v sa aiba n elememnte
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }

    // afiseaza solutia
    SSM(n, v);

    return 0;
}

// Compile:
// $ make
//
// Run:
// $ ./ssm
// 7
// 5 -6 3 4 -2 3 -3
//
// 8 3 6
//
