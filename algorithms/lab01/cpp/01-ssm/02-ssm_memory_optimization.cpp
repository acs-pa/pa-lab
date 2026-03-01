// SPDX-License-Identifier: BSD-3-Clause

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
    int n;                  // numărul de elemente din vector
    vector<int> v;          // vectorul de elemente pe care se aplică SSM

    struct SSMResult {
        int value;          // suma subsecvenței de sumă maximă
        int start;          // poziția de început a subsecvenței de sumă maximă
        int end;            // poziția de sfârșit a subsecvenței de sumă maximă

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

    // SSM = Subsecvența Sumă Maximă, varianta cu O(1) memorie suplimentară
    // Un singur pas: menținem doar suma curentă și cea mai bună secvență.
    // T = O(n)
    // S = O(1) (putem folosi doar variabile locale, nu folosim vectori dp/start)
    SSMResult ssm() {
        // Observație: În realitate implementăm aceeași recurență ca în 01-ssm.cpp.
        // dp[i] = suma subsecvenței de sumă maximă (suma SSM) folosind
        // **doar primele i elemente din vectorul v** și care **se termină pe poziția i**

        // Caz de bază
        int best_sum = v[0], best_start = 0, best_end = 0;
        int curr_sum = v[0], curr_start = 0;

        // Caz general
        for (int i = 1; i < n; ++i) {
            if (curr_sum >= 0) {
                // Extinde la dreapta cu v[i].
                curr_sum += v[i];
            } else {
                // Începe o nouă secvență.
                curr_sum = v[i];
                curr_start = i;
            }

            int curr_end = i;
            if (curr_sum > best_sum) {
                best_sum = curr_sum;
                best_start = curr_start;
                best_end = curr_end;
            } else if (curr_sum == best_sum) {
                // Conform enunțului: indice de început cel mai mic, la egalitate cea mai scurtă.
                if (curr_start < best_start ||
                    (curr_start == best_start && curr_end < best_end)) {
                    best_start = curr_start;
                    best_end = curr_end;
                }
            }
        }

        // Soluția este cea reținută în best_*.
        return SSMResult{best_sum, best_start, best_end};
    }

    void write_output(const SSMResult& result) {
        ofstream fout("out");
        // Afișăm rezultatul cu indexarea de la 1.
        fout << result.value << " " << result.start + 1 << " " << result.end + 1 << "\n";
        fout.close();
    }
};

// [ATENTIE] NU modifica functia main!
int main() {
    std::unique_ptr<Task> task {new (nothrow) Task()};
    if (!task) {
        std::cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    return 0;
}
