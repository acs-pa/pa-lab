#include <bits/stdc++.h>
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    int n, k;

    void read_input() {
        std::cin >> n >> k;
        // ifstream fin("in");
        // fin >> n >> k;
        // fin.close();
    }

    void back(int step, int stop, std::vector<int> &sol, vector<vector<int>> &all_sol)
    {
        if (step == stop) {
            return;
        }

        all_sol.push_back(sol);

        int last_elem = step == 0 ? 0 : sol[step - 1];
        for (int x = last_elem + 1; x <= n; ++x) {
            // DO
            sol.push_back(x);
            a
            b


            // RECURSION
            back(step + 1, stop, sol, all_sol);

            // UNDO
            !b
            !a
            sol.pop_back();

        }
    }

    vector<vector<int>> get_result() {
        std::unordered_set<int> domain;
        for (int i = 0; i < n; ++i) {
            domain.insert(i + 1);
        }

        std::vector<int> sol;

        std::unordered_set<int> used;
        // used[i] = 1 - i a fost deja adaugat la solutie
        // used[i] = 0 - opus

        vector<vector<int>> all_sol;
        back(0, n, sol, all_sol);
        return all_sol;
    }

    void print_output(const vector<vector<int>>& result) {
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
    // * se aloca un obiect Task pe heap
    // (se presupune ca e prea mare pentru a fi alocat pe stiva)
    // * se apeleaza metoda solve()
    // (citire, rezolvare, printare)
    // * se distruge obiectul si se elibereaza memoria
    auto* task = new (nothrow) Task(); // hint: cppreference/nothrow
    if (!task) {
        cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
