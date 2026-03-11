// SPDX-License-Identifier: BSD-3-Clause

#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

#define MOD 1009
#define KMAX 4

class Task {
public:
    void solve() {
        read_input();
        write_output(get_result());
    }

private:
    int n;

    void read_input() {
        ifstream fin("in");
        fin >> n;
        fin.close();
    }

    int get_result() {
        return garduri_rapide(n);
    }

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

    /**
     * Solutia optimizata
     * T(n) = O(log n)
     * S(n) = O(1)
     */
    int garduri_rapide(int n) {
        // cazurile de baza
        if (n <= 3)
            return 1;
        if (n == 4)
            return 2;

        // construiesc matricea C
        int C[KMAX][KMAX] = {{0, 0, 0, 1}, {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 1}};

        // C = C^(n-4)
        power_matrix(C, n - 4, C);

        // sol = S_4 * C = dp[n] (se afla pe ultima pozitie din S_n, deci voi folosi ultima coloana din C)
        int sol = 1 * C[0][3] + 1 * C[1][3] + 1 * C[2][3] + 2 * C[3][3];
        return sol % MOD;
    }

    void write_output(int result) {
        ofstream fout("out");
        fout << result << "\n";
        fout.close();
    }
};

// [ATENTIE] NU modifica funcția main!
int main() {
    // Se alocă un obiect Task pe heap pe care se apelează metoda solve().
    std::unique_ptr<Task> task {new (nothrow) Task()};
    if (!task) {
        std::cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    return 0;
}
