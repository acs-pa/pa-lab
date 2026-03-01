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
    int n;                       // numărul de elemente din vector
    vector<int> v;               // vectorul de elemente pe care se aplică SCMAX

    struct SCMAXResult {
        int length;              // lungimea SCMAX
        vector<int> sequence;    // secvența SCMAX
        SCMAXResult(int length, const vector<int>& sequence) : length(length), sequence(sequence) {}
    };

    void read_input() {
        ifstream fin("in");
        fin >> n;
        v.resize(n + 1);
        for (int i = 1; i <= n; ++i) {
            fin >> v[i];
        }
        fin.close();
    }

    SCMAXResult get_result() {
        return scmax();
    }

    // SCMAX = Subșir Crescător Maximal, implementarea clasica cu DP
    // T = O(n^2)
    // S = O(n)
    SCMAXResult scmax() {
        // dp[i] = lungimea celui mai lung subșir (SCMAX) folosind (doar o parte) din primele i elemente din vectorul v și care se termină pe poziția i
        vector<int> dp(n + 1); // Preferăm indexarea de la 1 pentru a fi mai ușor de implementat.
        
        // prev[i] = poziția elementului precedent din SCMAX care se termină pe poziția i
        vector<int> prev(n + 1);

        // Caz de bază
        dp[1] = 1;
        prev[1] = 0;

        // Caz general
        for (int i = 2; i <= n; ++i) {
            dp[i] = 1;
            prev[i] = 0;

            // Încerc să pun pe v[i] la finalul tuturor soluțiilor disponibile
            // o soluție se termină cu un element v[j].
            for (int j = 1; j < i; ++j) {
                if (v[j] < v[i] && dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    prev[i] = j;
                }
            }
        }

        // Soluția este maximul din vectorul dp.
        int pos = std::max_element(dp.begin(), dp.end()) - dp.begin();
        int sol = dp[pos];

        // Reconstruim SCMAX: v[pos] este ultimul element, înainte v[prev[pos]], etc.
        vector<int> sequence;
        for (int i = pos; i != 0; i = prev[i]) {
            sequence.push_back(v[i]);
        }
        reverse(sequence.begin(), sequence.end());
        return SCMAXResult{sol, sequence};
    }

    void write_output(const SCMAXResult& result) {
        ofstream fout("out");
        fout << result.length << "\n";
        for (size_t i = 0; i < result.sequence.size(); ++i) {
            fout << (i ? " " : "") << result.sequence[i];
        }
        fout << "\n";
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
