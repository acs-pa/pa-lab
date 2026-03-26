// SPDX-License-Identifier: BSD-3-Clause

#include <fstream>
#include <iostream>
#include <memory>
#include <numeric>
#include <unordered_set>
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
        unordered_set<int> visited;

        // Construim permutările prin backtracking.
        bkt(0, n, domain, solution, visited, all);
    }

    // Permutări de n elemente, implementare cu pruning.
    // T = O(n * n!)
    // S = O(n)
    void bkt(int step, int stop, vector<int>& domain, vector<int>& solution, unordered_set<int>& visited,
        vector<vector<int>>& all) {
        // După ce am folosit toate elementele din domeniu, putem verifica dacă
        // am găsit o soluție.
        if (step == stop) {
            if (check(solution)) {
                all.push_back(solution);
            }
            return;
        }

        // Adaugam in solutie fiecare element din domeniu care *NU* a fost
        // vizitat deja renuntand astfel la nevoia de a verifica duplicatele la
        // final prin functia "check()"
        for (size_t i = 0; i < domain.size(); i += 1) {
            if (!visited.count(domain[i])) {
                // Il marcam ca vizitat si taiem eventuale expansiuni nefolositoare viitoare (ex: daca il adaug in
                // solutie pe 3 nu voi mai avea niciodata nevoie sa il mai adaug pe 3 in continuare)
                visited.insert(domain[i]);
                // Adaugam elementul curent in solutie pe pozitia pasului curent (step)
                solution.push_back(domain[i]);
                // Apelam recursiv backtracking pentru pasul urmator
                bkt(step + 1, stop, domain, solution, visited, all);
                // Stergem vizitarea elementului curent (ex: pentru N = 3, dupa
                // ce la pasul "step = 0" l-am pus pe 1 pe prima pozitie in
                // solutie si am continuat recursiv pana am ajuns la solutiile
                // {1, 2, 3} si {1, 3, 2}, ne dorim sa il punem pe 2 pe prima
                // pozitie in solutie si sa continuam recursiv pentru a ajunge
                // la solutiile {2, 1, 3} etc.)
                visited.erase(domain[i]);
                solution.pop_back();
            }
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
