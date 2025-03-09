// SPDX-License-Identifier: BSD-3-Clause

#include <iostream> // cin, cout
#include <fstream> // ifstream, ofstream
#include <iomanip> // setprecision, fixed
#include <cmath> // fabs
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    double n;

    void read_input() {
        ifstream fin("in");
        fin >> n;
        fin.close();
    }

    double get_result() {
        // TODO: Calculati sqrt(n) cu o precizie de 0.001
        // Precizie de 10^-x = |rezultatul vostru - rezultatul corect| <= 10^-x
        const double eps = 1e-3;

        int steps = 30; // limitez prin numarare de pasi

        double left = 0.0;
        double right = (n < 1 ? 1.0 : n);

        while (steps--) {
            double middle = (left + right) * 0.5;
            double diff = n - middle * middle;

            if (fabs(diff) <= eps)
                return middle;

            if (diff > 0) {
                left = middle;
            } else {
                right = middle;
            }
        }

        return 0.0;
    }

    void print_output(double result) {
        ofstream fout("out");
        fout << setprecision(4) << fixed << result;
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
