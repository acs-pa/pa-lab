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
    int n, k;

    void read_input() {
        ifstream fin("in");
        fin >> n >> k;
        fin.close();
    }

    vector<vector<int>> get_result() {
        vector<vector<int>> all;
        solve_bkt(all);
        return all;
    }

    void solve_bkt(vector<vector<int>>& all) {
        // Vectorul in care stochez solutia (partiala) curenta
        vector<int> current;

        // construiesc combinarile prin backtracking
        bkt(current, all);
    }

    // Combinari de n luate cate k, implementare cu transmitere prin referinta
    // T = O(n! / (k!*(n-k)!))
    // S = O(n)
    void bkt(vector<int>& current, vector<vector<int>>& all) {
        // Daca avem o multime de dimensiune k
        if (current.size() == k) {
            // este implicit si o combinatie prin modul cum a fost generata

            // Adaug la solutie
            all.push_back(current);

            // Ma opresc
            return;
        }

        // Daca este primul pas, alegem fiecare element din domeniu ca potential
        // candidat pentru prima pozitie in solutie; altfel, pentru a elimina ramurile
        // in care de exemplu {2, 1} se va genera dupa ce s-a generat {1, 2} (adica
        // ar fi duplicat), vom folosi doar elementele din domeniu care sunt mai mari
        // decat ultimul element adaugat in solutie (solution[step - 1]) */
        for (int i = (current.empty() ? 1 : current.back() + 1); i <= n; ++i) {
            // Step 1: ADAUG elementul la solutie
            current.push_back(i);

            // Step 2: COMPLETEZ recursiv si solutia
            bkt(current, all);

            // Step 3: Scot elementul din solutie, ca sa pot pune altul in locul lui
            current.pop_back();
        }
    }

    void write_output(const vector<vector<int>>& result) {
        ofstream fout("out");
        fout << result.size() << '\n';
        for (size_t i = 0; i < result.size(); i++) {
            for (size_t j = 0; j < result[i].size(); j++) {
                fout << result[i][j] << (j + 1 != result[i].size() ? ' ' : '\n');
            }
        }
        fout.close();
    }
};

// [ATENTIE] NU modifica functia main!
int main() {
    std::unique_ptr<Task> task{new (nothrow) Task()};
    if (!task) {
        std::cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    return 0;
}
