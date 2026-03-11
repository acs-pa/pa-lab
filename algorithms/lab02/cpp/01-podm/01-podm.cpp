// SPDX-License-Identifier: BSD-3-Clause

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <vector>
using namespace std;

// kInf este valoarea maxima - "infinitul" nostru
const unsigned long long kInf = numeric_limits<unsigned long long>::max();

class Task {
public:
    void solve() {
        read_input();
        write_output(get_result());
    }

private:
    int n;                  // numărul de matrici
    vector<int> d;          // dimensiunile matricilor

    void read_input() {
        ifstream fin("in");
        fin >> n;
        d.resize(n + 1);
        for (int i = 0; i <= n; ++i) {
            fin >> d[i];
        }
        fin.close();
    }

    unsigned long long get_result() {
        return solve_podm();
    }

    // PODM = Produsul Optim de Matrici, implementarea clasică cu DP
    // T = O(n ^ 3)
    // S = O(n ^ 2) - stocam n x n intregi in tabloul dp
    unsigned long long solve_podm() {
        // dp[i][j] = numarul MINIM inmultiri scalare cu codare poate fi calculat produsul
        //            matricial M_i * M_i+1 * ... * M_j
        vector<vector<unsigned long long>> dp(n + 1, vector<unsigned long long>(n + 1, kInf));

        // Cazul de baza 1: nu am ce inmulti
        for (int i = 1; i <= n; ++i) {
            dp[i][i] = 0ULL; // 0 pe unsigned long long (voi folosi mai incolo si 1ULL)
        }

        // Cazul de baza 2: matrice d[i - 1] x d[i] inmultia cu matrice d[i] x d[i + 1]
        // (matrice pe pozitii consecutive)
        for (int i = 1; i < n; ++i) {
            dp[i][i + 1] = 1ULL * d[i - 1] * d[i] * d[i + 1];
        }

        // Cazul general:
        // dp[i][j] = min(dp[i][k] + dp[k + 1][j] + d[i - 1] * d[k] * d[j]), k = i : j - 1
        for (int len = 2; len <= n; ++len) { // fixam lungimea intervalului (2, 3, 4, ...)
            for (int i = 1; i + len - 1 <= n; ++i) { // fixam capatul din stanga: i
                int j = i + len - 1; // capatul din dreapta se deduce: j

                // Iteram prin indicii dintre capete, spargand sirul de inmultiri in doua (paranteze).
                for (int k = i; k < j; ++k) {
                    // M_i * ... M_j  = (M_i * .. * M_k) * (M_k+1 *... * M_j)
                    unsigned long long new_sol = dp[i][k] + dp[k + 1][j] + 1ULL * d[i - 1] * d[k] * d[j];

                    // actualizam solutia daca este mai buna
                    dp[i][j] = min(dp[i][j], new_sol);
                }
            }
        }

        // Rezultatul se afla in dp[1][n]: Numarul MINIM de inmultiri scalare
        // pe care trebuie sa le facem pentru a obtine produsul M_1 * ... * M_n
        return dp[1][n];
    }

    void write_output(unsigned long long result) {
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
