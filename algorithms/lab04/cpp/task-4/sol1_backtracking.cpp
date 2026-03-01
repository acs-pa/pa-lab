// SPDX-License-Identifier: BSD-3-Clause

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    int n, k;
    string caractere;
    vector<int> freq;

    void read_input() {
        ifstream fin("in");
        fin >> n >> k;
        fin >> caractere;
        caractere = " " + caractere; // Adaugare element fictiv -
                                     // indexare de la 1.
        freq.push_back(-1); // Adaugare element fictiv - indexare de la 1.
        for (int i = 1, f; i <= n; i++) {
            fin >> f;
            freq.push_back(f);
        }
        fin.close();
    }

    vector<vector<char>> get_result() {
        vector<vector<char>> all;

        // TODO: Construiti toate sirurile cu caracterele in stringul caractere
        // (indexat de la 1 la n), si frecventele in vectorul freq (indexat de la 1 la n),
        // stiind ca nu pot fi mai mult de K aparitii consecutive ale
        // aceluiasi caracter.
        //
        // Pentru a adauga un nou sir:
        //     vector<char> sir;
        //     all.push_back(sir);
        //

        solve_generate(all);

        return all;
    }

    void solve_generate(vector<vector<char>>& all) {
        // solutia este un sir (vector) de caractere
        vector<char> current;

        // numarul total de caractere
        int total_count = 0;
        for (int i = 1; i <= n; ++i) {
            total_count += freq[i];
        }

        // generez recursiv pornind de current, avand 0 elemente consecutive la fel
        // in total trebuie sa plasez total_count caractere
        bkt(current, 0, total_count, all);
    }

    void bkt(vector<char>& current,
        int cons_char, // numarul de caractere consecutive la fel
        int remaining, // numarul de caractere inca neplasate
        vector<vector<char>>& all) {

        // verific daca am pus mai multe aparitii consecutive ale aceluiasi caracter
        if (cons_char > k) {
            return; // nu salvez solutia curenta
        }

        // daca nu mai am de plasat caractere
        if (remaining == 0) {
            // inseamna ca le-am plasat pe toate :D

            // salvez solutia
            all.push_back(current);
            return;
        }

        // incerc sa extind cu un caracter nefolosit
        for (int i = 1; i <= n; ++i) {
            // daca este epuizat, nu il folosesc din nou
            if (freq[i] == 0) {
                continue;
            }

            // presupun ca e un caracter nou
            int new_cons_char = 1;

            if (!current.empty() && current.back() == caractere[i]) {
                // am presupus prost, e acelasi caracter
                new_cons_char = cons_char + 1;
            }

            // Step 1: EXTINDE
            --freq[i];
            current.push_back(caractere[i]);

            // Step 2: COMPLETEAZA recursiv
            bkt(current, new_cons_char, remaining - 1, all);

            // Step 3: SCOATE elementul din solutie, sa putem pune altceva in locul lui
            ++freq[i];
            current.pop_back();
        }
    }

    void print_output(const vector<vector<char>>& result) {
        ofstream fout("out");
        fout << result.size() << '\n';
        for (size_t i = 0; i < result.size(); i++) {
            for (size_t j = 0; j < result[i].size(); j++) {
                fout << result[i][j];
            }
            fout << '\n';
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
