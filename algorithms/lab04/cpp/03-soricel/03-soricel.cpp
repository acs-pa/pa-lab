// SPDX-License-Identifier: BSD-3-Clause

#include <fstream>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        write_output(get_result());
    }

private:
    vector<vector<int>> mat;

    void read_input() {
        ifstream fin("in");

        int n;
        fin >> n;

        mat.resize(n);
        for (auto& row : mat) {
            row.resize(n);
            for (auto& num : row) {
                fin >> num;
            }
        }

        fin.close();
    }

    vector<vector<pair<int, int>>> get_result() {
        vector<vector<pair<int, int>>> all;
        solve_bkt(all);
        return all;
    }

    void solve_bkt(vector<vector<pair<int, int>>>& all) {
        // Adăugăm forțat poziția de start în stivă / soluția parțială.
        vector<pair<int, int>> current = {{0, 0}};
        bkt(current, all);
    }

    // Problema șoricelului = Generarea drumurilor printr-o matrice cu 2 mișcări.
    // T(n) = O(2^(2n))
    // S(n) = O(n)
    void bkt(vector<pair<int, int>>& current, vector<vector<pair<int, int>>>& all) {
        // Dacă am ajuns la destinație, `current` e un drum complet, nu trebuie extins.
        if (current.back() == make_pair<int, int>(mat.size() - 1, mat.size() - 1)) {
            all.push_back(current);
            return;
        }

        // Folosim un vector de direcții pentru mișcările disponibile.
        for (const auto& [mod_r, mod_c] : vector<pair<int, int>>{{0, 1}, {1, 0}}) {
            auto r = get<0>(current.back()) + mod_r;
            auto c = get<1>(current.back()) + mod_c;

            // Putem continua drumul dacă nu ieșim din matrice și nu suntem blocați.
            if (in_bounds(r, c) && mat[r][c] == 0) {
                current.push_back({r, c}); // Punem pe stivă noua poziție.
                bkt(current, all); // Generăm continuările recursiv.
                current.pop_back(); // După revenire, scoatem celula din stivă.
            }
        }
    }

    // Verifică dacă o poziție e în interiorul matricei.
    bool in_bounds(int r, int c) const { return 0 <= r && r < (int)mat.size() && 0 <= c && c < (int)mat[r].size(); }

    void write_output(const vector<vector<pair<int, int>>>& result) {
        ofstream fout("out");
        fout << result.size() << "\n";
        for (const auto& path : result) {
            auto first = true;
            for (const auto& [r, c] : path) {
                if (!first) {
                    fout << "->";
                }
                fout << "(" << r << "," << c << ")";
                first = false;
            }
            fout << "\n";
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
