// SPDX-License-Identifier: BSD-3-Clause

#include <algorithm> // max_element
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
    int n; // numărul de elemente din vector
    vector<int> v; // vectorul de elemente pe care se aplică SSM

    struct SSMResult {
        int value; // suma subsecvenței de sumă maximă
        int start; // poziția de început a subsecvenței de sumă maximă
        int end; // poziția de sfârșit a subsecvenței de sumă maximă

        SSMResult(int value, int start, int end) : value(value), start(start), end(end) {}
    };

    void read_input() {
        ifstream fin("in");
        fin >> n;
        v.resize(n);
        for (int i = 0; i < n; ++i) {
            fin >> v[i];
        }
        fin.close();
    }

    SSMResult get_result() {
        return ssm();
    }

    // SSM = Subsecvența Sumă Maximă, implementarea clasică cu DP
    // T = O(n)
    // S = O(n)
    SSMResult ssm() {
        // dp[i]= suma subsecvenței de sumă maximă (suma SSM) folosind
        // **doar primele i elemente din vectorul v** și care **se termină pe poziția i**
        vector<int> dp(n);
        
        // start[i] = poziția de început a subsecvenței de sumă maximă care se termină pe poziția i
        vector<int> start(n);

        // Caz de bază
        dp[0] = v[0];
        start[0] = 0;

        // Caz general
        for (int i = 1; i < n; ++i) {
            if (dp[i - 1] >= 0) {
                // Extinde la dreapta cu v[i].
                dp[i] = dp[i - 1] + v[i];
                start[i] = start[i - 1];
            } else {
                // Începe o nouă secvență.
                dp[i] = v[i];
                start[i] = i;
            }
        }

        // Soluția este maximul din vectorul dp.
        int pos = std::max_element(dp.begin(), dp.end()) - dp.begin();
        return SSMResult{dp[pos], start[pos], pos};
    }

    void write_output(const SSMResult& result) {
        ofstream fout("out");
        // Afișăm rezultatul cu indexarea de la 1.
        fout << result.value << " " << result.start + 1 << " " << result.end + 1 << "\n";
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
