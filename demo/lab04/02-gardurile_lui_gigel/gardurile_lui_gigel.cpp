// SPDX-License-Identifier: BSD-3-Clause

#include <cstring> // memcpy
#include <iostream> // cin, cout
#include <vector> // vector
using namespace std;

#define MOD 1009
int gardurile_lui_Gigel(int n) {
    // cazurile de baza
    if (n <= 3)
        return 1;
    if (n == 4)
        return 2;

    vector<int> dp(n + 1); // pastrez indexarea de la 1 ca in explicatii

    // cazurile de baza
    dp[1] = dp[2] = dp[3] = 1;
    dp[4] = 2;

    // cazul general
    for (int i = 5; i <= n; ++i) {
        dp[i] = (dp[i - 1] + dp[i - 4]) % MOD;
    }

    return dp[n];
}

#define MOD 1009
#define KMAX 4

// C = A * B
void multiply_matrix(int A[KMAX][KMAX], int B[KMAX][KMAX], int C[KMAX][KMAX]) {
    int tmp[KMAX][KMAX];

    // tmp = A * B
    for (int i = 0; i < KMAX; ++i) {
        for (int j = 0; j < KMAX; ++j) {
            unsigned long long sum = 0; // presupun ca o suma intermediara incape pe 64 de biti

            for (int k = 0; k < KMAX; ++k) {
                sum += 1LL * A[i][k] * B[k][j];
            }

            tmp[i][j] = sum % MOD;
        }
    }

    //  C = tmp
    memcpy(C, tmp, sizeof(tmp));
}

// R = C^p
void power_matrix(int C[KMAX][KMAX], int p, int R[KMAX][KMAX]) {
    // tmp = I
    int tmp[KMAX][KMAX];
    for (int i = 0; i < KMAX; ++i) {
        for (int j = 0; j < KMAX; ++j) {
            tmp[i][j] = (i == j) ? 1 : 0;
        }
    }

    while (p != 1) {
        if (p % 2 == 0) {
            multiply_matrix(C, C, C); // C = C*C
            p /= 2; // ramane de calculat C^(p/2)
        } else {
            // reduc la cazul anterior:
            multiply_matrix(tmp, C, tmp); // tmp = tmp*C
            --p; // ramane de calculat C^(p-1)
        }
    }

    // avem o parte din rezultat in C si o parte in tmp
    multiply_matrix(C, tmp, R); // rezultat = tmp * C
}

void print_matrix(int A[KMAX][KMAX]) {
    for (int i = 0; i < KMAX; ++i) {
        for (int j = 0; j < KMAX; ++j) {
            cout << A[i][j] << " ";
        }
        cout << "\n";
    }
}
/*
k = 4
dp[i] = dp[i-1] + dp[i-4] = 1 * dp[i-1] + 0 * dp[i-2] + 0 * dp[i-3] + 1 * dp[i-4]

s_4   = (1, 1, 1, 2)
s_i-1 = (dp[i-4], dp[i-3], dp[i-2], dp[i-1])
C     = (0 0 0 1
         1 0 0 0
         0 1 0 0
         0 0 1 1)
s_i = s_i-1 * C
s_i   = (dp[i-3], dp[i-2], dp[i-1], dp[i])

*/
int garduri_rapide(int n) {
    // cazurile de baza
    if (n <= 3)
        return 1;
    if (n == 4)
        return 2;

    // construiesc matricea C
    int C[KMAX][KMAX] = {{0, 0, 0, 1}, {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 1}};
    // vreau sa aplic formula S_n = S_4 * C^(n-4)

    // C = C^(n-4)
    power_matrix(C, n - 4, C);

    // sol = S_4 * C = dp[n] (se afla pe ultima pozitie din S_n, deci voi folosi ultima coloana din C)
    int sol = 1 * C[0][3] + 1 * C[1][3] + 1 * C[2][3] + 2 * C[3][3];
    return sol % MOD;
}

bool verifica_algoritmi() {
    int n = 1000; // testez daca pentru toate valorile 1, 2, ...,1000 cei 2 algoritmi gasesc aceeasi solutie

    for (int i = 1; i <= n; ++i) {
        int sol1 = gardurile_lui_Gigel(i), sol2 = garduri_rapide(i);
        if (sol1 != sol2) {
            cout << "Am pus-o! " << i << ":" << sol1 << " vs " << sol2 << "\n";
            return false;
        }
    }

    return true;
}

void benchmark(int n, string name, int (*func)(int)) {
    int start = clock();
    int sol = func(n);
    int end = clock();

    double duration = 1.0 * (end - start) / CLOCKS_PER_SEC; // durata in secunde

    cout.precision(6);
    cout << "test case: " << name << "\n";
    cout << "n = " << n << " sol = " << sol << "; time = " << fixed << duration << "\n";
}

void benchmark_set(int n) {
    benchmark(n, "varianta simpla", gardurile_lui_Gigel);
    benchmark(n, "varianta rapida", garduri_rapide);
}

int main() {
    if (verifica_algoritmi() == true) {
        benchmark_set(100000000); // n = 10^8
        benchmark_set(1000000000); // n = 10^9
    } else {
        cout << "Mai incearca! (cei 2 algoritmi nu obtine aceleasi rezultate\n";
    }

    return 0;
}

// Compile:
// $ make
// Run:
// $ ./gardurile_lui_gigel
// test case: varianta simpla
// n = 100000000 sol = 119; time = 0.566617
// test case: varianta rapida
// n = 100000000 sol = 119; time = 0.000005
// test case: varianta simpla
// n = 1000000000 sol = 812; time = 5.547222
// test case: varianta rapida
// n = 1000000000 sol = 812; time = 0.000004
