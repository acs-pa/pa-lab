// SPDX-License-Identifier: BSD-3-Clause

#include <algorithm> // lower_bound, reverse
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
    int n;
    vector<int> v;

    struct SCMAXResult {
        int length;
        vector<int> sequence;
        SCMAXResult(int length, const vector<int>& sequence)
            : length(length), sequence(sequence) {}
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
        return scmax_binary_search();
    }

    // SCMAX = Subșir Crescător Maximal, varianta O(n log n) cu binary search
    // Menținem pentru fiecare lungime L cea mai mică valoare finală a unui subșir crescător de lungime L.
    // T = O(n log n)
    // S = O(n)
    SCMAXResult scmax_binary_search() {
        // dp[l] = valoarea minimă a ultimului element dintr-un subșir crescător de lungime l+1
        vector<int> dp;
        // dp_idx[l] = indicele în v al acelui element (pentru reconstrucție)
        vector<int> dp_idx;
        vector<int> prev(n + 1, 0);

        // Caz de bază: primul element
        dp.push_back(v[1]);
        dp_idx.push_back(1);
        prev[1] = 0;

        // Caz general: pentru fiecare v[i] căutăm binar unde să extindem sau să înlocuim.
        for (int i = 2; i <= n; ++i) {
            auto it = std::lower_bound(dp.begin(), dp.end(), v[i]);
            int p = (int)(it - dp.begin());

            if (p == (int)dp.size()) {
                // Extindem: subșir nou de lungime maximă
                dp.push_back(v[i]);
                dp_idx.push_back(i);
                prev[i] = dp_idx[p - 1];
            } else {
                // Înlocuim: obținem o „coadă” mai mică pentru lungimea p+1
                dp[p] = v[i];
                dp_idx[p] = i;
                prev[i] = (p > 0) ? dp_idx[p - 1] : 0;
            }
        }

        int sol = (int)dp.size();

        // Reconstruim subșirul: începem de la ultimul element al LIS-ului de lungime maximă
        vector<int> sequence;
        for (int i = dp_idx[sol - 1]; i != 0; i = prev[i]) {
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
