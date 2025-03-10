// SPDX-License-Identifier: BSD-3-Clause

#include <cstdlib> // atoi
#include <iostream> // cin, cout
#include <vector> // vector
using namespace std;

bool check(vector<int>& solution) {
    return true;
}

void printSolution(vector<int>& solution, vector<int>& domain, int stop) {
    for (auto i = 0; i < stop; ++i) {
        cout << domain[solution[i]] << " ";
    }
    cout << "\n";
}

void back(int step, int stop, vector<int>& domain, vector<int>& solution) {
    /* vom verifica o solutie atunci cand am adaugat deja K elemente in solutie,
    adica step == stop */
    if (step == stop) {
        /* deoarece am avut grija sa se adauge elementele doar in ordine
        crescatoare, "check()" va returna intotdeauna "true" */
        if (check(solution)) {
            printSolution(solution, domain, stop);
        }
        return;
    }

    /* daca este primul pas, alegem fiecare element din domeniu ca potential
    candidat pentru prima pozitie in solutie; altfel, pentru a elimina ramurile
    in care de exemplu {2, 1} se va genera dupa ce s-a generat {1, 2} (adica
    ar fi duplicat), vom folosi doar elementele din domeniu care sunt mai mari
    decat ultimul element adaugat in solutie (solution[step - 1]) */
    unsigned i = step > 0 ? solution[step - 1] + 1 : 0;
    for (; i < domain.size(); ++i) {
        solution[step] = i;
        back(step + 1, stop, domain, solution);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: ./combs n k\n";
        exit(1);
    }

    int n = atoi(argv[1]), k = atoi(argv[2]);
    /* dupa ce citim n si k initializam domeniul cu valorile de la 1 la n,
    iar solutia este initializata cu un vector de k elemente (fiindca o
    combinare de "n luate cate k" are k elemente) */
    vector<int> domain(n), solution(k);
    for (int i = 0; i < n; ++i) {
        domain[i] = i + 1;
    }

    back(0, k, domain, solution);
}

// Compile:
// $ make
// Run:
// $ ./combs 5 3
// 1 2 3
// 1 2 4
// 1 2 5
// 1 3 4
// 1 3 5
// 1 4 5
// 2 3 4
// 2 3 5
// 2 4 5
// 3 4 5
