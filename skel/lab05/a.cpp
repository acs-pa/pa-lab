#include <bits/stdc++.h>
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        get_result();
        // print_output(get_result());
    }

private:
    int n, k;

    void read_input() {
        std::cin >> n >> k;
        // ifstream fin("in");
        // fin >> n >> k;
        // fin.close();
    }

    void back(int stop, std::unordered_set<int> &domain, std::vector<int> &sol, std::vector<int> &used)
    {
        if (sol.size() == stop) { // domain.size() == 0
            for (auto x : sol) {
                std::cout << x << ' ';
            }
            std::cout << '\n';
            return;
        }

        for (auto x : domain) {
            if (used[x])
                continue;

            // DO
            sol.push_back(x);
            used[x] = 1;

            // RECURSION
            back(k, domain, sol, used);

            // UNDO
            sol.pop_back();
            used[x] = 0;
        }
    }

    void get_result() {
        std::unordered_set<int> domain;
        for (int i = 0; i < n; ++i) {
            domain.insert(i + 1);
        }

        std::vector<int> sol;

        std::vector<int> used(n + 1, 0);
        // used[i] = 1 - i a fost deja adaugat la solutie
        // used[i] = 0 - opus

        back(k, domain, sol, used);
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
