#include <bits/stdc++.h>
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

        return 0;
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
