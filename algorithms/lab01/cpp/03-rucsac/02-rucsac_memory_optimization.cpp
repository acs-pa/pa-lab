// SPDX-License-Identifier: BSD-3-Clause

#include <algorithm> // max
#include <fstream> // ifstream, ofstream
#include <iostream> // cin, cout, cerr
#include <memory> // unique_ptr pentru Task
#include <vector> // vector
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        write_output(get_result());
    }

private:
    int n; // numărul de obiecte
    int W; // capacitatea rucsacului
    vector<int> w; // greutatea fiecărui obiect
    vector<int> p; // valoarea fiecărui obiect

    struct RucsacResult {
        int value; // valoarea maximă a obiectelor care pot fi puse în rucsac
        vector<int> objects; // obiectele care pot fi puse în rucsac
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

    // Rucsac = Problema rucsacului, varianta cu 2 linii: dp[i] și dp[i-1].
    // T = O(n * W)
    // S = O(W)
    RucsacResult rucsac() {
        // Observație: În realitate implementăm aceeași recurență ca în 01-rucsac.cpp,
        // dar folosim doar 2 linii de dp.
        // dp[i][cap] = profitul maxim (profit RUCSAC) obținut folosind
        // (doar o parte) din primele i obiecte și având un rucsac de capacitate maximă cap.

        // prev[cap] = profitul maxim folosind primele i-1 obiecte, capacitate cap
        vector<int> prev(W + 1, 0);
        // curr[cap] = profitul maxim folosind primele i obiecte, capacitate cap
        vector<int> curr(W + 1, 0);

        for (int i = 1; i <= n; ++i) {
            for (int cap = 0; cap <= W; ++cap) {
                curr[cap] = prev[cap];
                if (cap >= w[i]) {
                    curr[cap] = std::max(curr[cap], prev[cap - w[i]] + p[i]);
                }
            }
            std::swap(prev, curr);
        }

        // Atenție: în această abordare nu putem reconstitui soluția,
        // deoarece nu păstrăm informațiile despre obiectele care au fost folosite.
        return RucsacResult{prev[W], {}};
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
