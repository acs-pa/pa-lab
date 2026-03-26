// SPDX-License-Identifier: BSD-3-Clause

#include <fstream>
#include <iostream>
#include <memory>
#include <numeric>
#include <vector>
using namespace std;

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

    vector<vector<int>> get_result() {
        vector<vector<int>> all;
        solve_bkt(all);
        return all;
    }

    void solve_bkt(vector<vector<int>>& all) {
        // La începutul generării putem alege din fiecare număr între 1 și n.
        vector<int> domain(n);
        iota(domain.begin(), domain.end(), 1);

        vector<int> solution;

        // Construim permutările prin backtracking.
        bkt(domain, solution, all);
    }

    // Permutări de n elemente, implementare cu referințe.
    // T = O(n * n!)
    // S = O(n)
    void bkt(vector<int>& domain, vector<int>& solution, vector<vector<int>>& all) {
        // După ce am folosit toate elementele din domeniu, putem verifica dacă
        // am găsit o soluție.
        if (domain.size() == 0) {
            if (check(solution)) {
                all.push_back(solution);
            }
            return;
        }

        // Încercăm să adăugăm în soluție toate valorile din domeniu, pe rând.
        for (size_t i = 0; i < domain.size(); i += 1) {
            int tmp = domain[i];

            // Adaug elementul curent la potențiala soluție.
            solution.push_back(tmp);
            // Șterg elementul curent ca să nu îl refolosesc.
            domain.erase(domain.begin() + i);

            // Continuăm generarea cu noua stare.
            bkt(domain, solution, all);

            // Refac domeniul și soluția la modul în care erau înainte de
            // apelarea recursivă a backtracking-ului.
            domain.insert(domain.begin() + i, tmp);
            solution.pop_back();
        }
    }

    // Deoarece numerele sunt șterse din domeniu odată ce sunt folosite, soluția
    // generată este garantată să nu conțină duplicate. Astfel, atunci când
    // domeniul ajunge vid, soluția este intotdeauna corectă.
    bool check(const vector<int>& solution) const { return true; }

    void write_output(const vector<vector<int>>& result) {
        ofstream fout("out");
        fout << result.size() << "\n";
        for (const auto& perm : result) {
            for (const auto& num : perm) {
                fout << num << " ";
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
