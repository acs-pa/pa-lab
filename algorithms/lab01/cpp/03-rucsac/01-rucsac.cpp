// SPDX-License-Identifier: BSD-3-Clause

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        write_output(get_result());
    }

private:
    int n;                       // numărul de obiecte
    int W;                       // capacitatea rucsacului
    vector<int> w;              // greutatea fiecărui obiect
    vector<int> p;              // valoarea fiecărui obiect

    struct RucsacResult {
        int value;              // valoarea maximă a obiectelor care pot fi puse în rucsac
        vector<int> objects;    // obiectele care pot fi puse în rucsac
        RucsacResult(int value, const vector<int>& objects) : value(value), objects(objects) {}
    };

    void read_input() {
        ifstream fin("in");
        fin >> n >> W;
        p.resize(n + 1);
        w.resize(n + 1);
        for (int i = 1; i <= n; ++i) {
            fin >> w[i] >> p[i];
        }
        fin.close();
    }

    RucsacResult get_result() {
        return rucsac();
    }

    // Rucsac = Problema rucsacului, implementarea clasica cu DP
    // T = O(n * W)
    // S = O(n * W)
    RucsacResult rucsac() {
        // dp[i][cap] = profitul maxim (profit RUCSAC) obținut folosind
        // (doar o parte) din primele i obiecte și având un rucsac de capacitate maximă cap.
        vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

        // Caz de bază
        for (int cap = 0; cap <= W; ++cap) {
            dp[0][cap] = 0;
        }

        // Caz general
        for (int i = 1; i <= n; ++i) {
            for (int cap = 0; cap <= W; ++cap) {
                // Nu folosesc obiectul i => e soluția de la pasul i - 1
                dp[i][cap] = dp[i - 1][cap];

                // Folosesc obiectul i, deci trebuie să rezerv w[i] unități în rucsac.
                // Înseamnă că înainte trebuie să ocup maxim cap - w[i] unități.
                if (cap - w[i] >= 0) {
                    int sol_aux = dp[i - 1][cap - w[i]] + p[i];
                    dp[i][cap] = max(dp[i][cap], sol_aux);
                }
            }
        }
        return RucsacResult{dp[n][W], reconstruct_solution(dp, w, p)};
    }

    // Reconstruim soluția
    vector<int> reconstruct_solution(const vector<vector<int>>& dp, const vector<int>& w, const vector<int>& p) {
        vector<int> objects;
        int cap = W;
        for (int i = n; i > 0; --i) {
            if (dp[i][cap] != dp[i - 1][cap]) {
                objects.push_back(i);
                cap -= w[i];
            }
        }
        return objects;
    }

    void write_output(const RucsacResult& result) {
        ofstream fout("out");
        fout << result.value << "\n";
        // Nu se printează obiectele, ci doar valoarea maximă a profitului.
        fout.close();
    }
};

// [ATENTIE] NU modifica funcția main!
int main() {
    std::unique_ptr<Task> task {new (nothrow) Task()};
    if (!task) {
        std::cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    return 0;
}
