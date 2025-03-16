// SPDX-License-Identifier: BSD-3-Clause

#include <algorithm>
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

    // T = O(n * DMAX)
    // S = O(DMAX)
    //    n = nr teme
    //    DMAX = deadline-ul maxim
    int plan_homeworks() {
        // sortam descrescator dupa scor
        sort(hws.begin(), hws.end(), [](const Homework& a, const Homework& b) { return a.score > b.score; });

        // aflam deadline-ul maxim
        int max_deadline = 0;
        for (const auto& hw : hws) {
            max_deadline = max(max_deadline, hw.deadline);
        }

        // used[i] = 1, daca in saptamana i am planificata o tema
        //         = 0, daca saptamana inca este libera
        vector<bool> used(max_deadline + 1, false);

        int profit = 0; // cate puncte castigam
        for (const auto& hw : hws) {
            // Incercam sa plasam urmatoarea cea mai bine punctata tema.
            // Unde o plasam?
            //      Incercam sa o plasam in ziua deadline-ului.
            //      Motive:
            //      1. Student lenes.
            //      2. Ne ofera flexibilitate maxima (ex. daca am pune in saptamana 1, toate temele ar putea
            //          fi afectate de aceasta mutare)
            for (int t = hw.deadline; t > 0; --t) { // t = DMAX, DMAX-1, ..., 1
                if (used[t]) { // in saptamana t deja am stabilit ca facem o alta tema mai bine punctata
                    continue;
                }

                // perfect: in saptamana t facem tema hw
                used[t] = true;
                profit += hw.score;
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
