// SPDX-License-Identifier: BSD-3-Clause

#include <iostream> // cin, cout
#include <fstream> // ifstream, ofstream
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    int base, exponent, mod;

    void read_input() {
        ifstream fin("in");
        fin >> base >> exponent >> mod;
        fin.close();
    }

    int fast_pow(long base, int exponent, int mod) {
        // TODO: Calculati (base^exponent) modulo mod in O(log exponent).

        // base ^ 0 = 1
        if (exponent == 0) {
            return 1;
        }

        // Reducem problema la jumatate.
        int half = fast_pow(base, exponent / 2, mod);
        int result = (1LL * half * half) % mod;

        // Pentru exponent impar, mai inmultim odata cu base.
        if (exponent % 2 == 1) {
            result = (1LL * result * base) % mod;
        }

        return result;
    }

    int get_result() { return fast_pow(base, exponent, mod); }

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
