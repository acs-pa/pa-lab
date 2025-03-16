// SPDX-License-Identifier: BSD-3-Clause

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

struct Homework {
    int deadline;
    int score;

    Homework(int _deadline, int _score)
        : deadline(_deadline)
        , score(_score) { }
};

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    int n;
    vector<Homework> hws;

    void read_input() {
        ifstream fin("in");
        fin >> n;
        for (int i = 0, deadline, score; i < n; i++) {
            fin >> deadline >> score;
            hws.push_back(Homework(deadline, score));
        }
        fin.close();
    }

    int get_result() {
        // TODO: Aflati punctajul maxim pe care il puteti obtine planificand
        // optim temele.

        return plan_homeworks();
    }

    // T = O(n^2)
    // S = O(1)
    // n = nr teme
    int plan_homeworks() {
        int profit = 0; // cate puncte castigam
        while (!hws.empty()) {
            // cautam deadline-ul maxim (daca sunt mai multe punctaj maxim)
            int imax = 0;
            for (int i = 1; i < hws.size(); ++i) {
                if (hws[i].deadline > hws[imax].deadline
                    || (hws[i].deadline == hws[imax].deadline && hws[i].score > hws[imax].score)) {
                    imax = i;
                }
            }

            // folosesc tema cu cel mai mare punctaj
            profit += hws[imax].score;
            int used_deadline = hws[imax].deadline;
            hws.erase(hws.begin() + imax);

            // scad cu 1 deadline-ul temelor cu acelasi deadline
            bool has_valid_homeworks = false;
            for (auto& hw : hws) {
                if (hw.deadline == used_deadline) {
                    --hw.deadline;
                }

                if (hw.deadline > 0) {
                    has_valid_homeworks = true;
                }
            }

            // daca toate temele au deadline negative, nu mai putem face alte teme
            if (!has_valid_homeworks) {
                break;
            }
        }

        return profit;
    }

    void print_output(int result) {
        ofstream fout("out");
        fout << result;
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
