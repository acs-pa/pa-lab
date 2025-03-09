// SPDX-License-Identifier: BSD-3-Clause

#include <iostream>         // cin, cout
#include <fstream>          // ifstream
#include <utility>          // pair
#include <vector>           // vector
using namespace std;

bool check(vector<pair<int, int>>& solution, int walls[100][100]) {
    for (unsigned i = 0; i < solution.size() - 1; ++i) {
        /* line_prev si col_prev reprezinta celula in care se afla soricelul la
        pasul i; line_next si col_next reprezinta celula in care se afla
        la pasul i + 1; trebuie sa fim siguri ca soricelul nu a ajuns pe zid
        si ca urmatoarea celula este sub sau in dreapta celulei curente */
        int line_prev = solution[i].first;
        int line_next = solution[i + 1].first;
        int col_prev = solution[i].second;
        int col_next = solution[i + 1].second;

        /* walls[x][y] == 1 inseamna ca este zid pe linia x, coloana y */
        if (walls[line_prev][col_prev] == 1
            || !((line_next == line_prev + 1 && col_next == col_prev)
                || (line_next == line_prev && col_next == col_prev + 1))) {
            return false;
        }
    }

    return true;
}

void printSolution(vector<pair<int, int>>& solution) {
    for (pair<int, int> s : solution) {
        cout << "(" << s.first << "," << s.second << ")->";
    }
    cout << "\n";
}

void back(
    vector<pair<int, int>>& domain, int walls[100][100], vector<pair<int, int>>& solution, unsigned int max_iter) {
    /* daca am facut "max_iter" pasi ma opresc si verific daca este corecta
    solutia */
    if (solution.size() == max_iter) {
        if (check(solution, walls)) {
            printSolution(solution);
        }
        return;
    }

    /* avand domeniul initializat cu toate celulele din matrice, incercam sa
    adaugam oricare dintre aceste celule la solutie, verificand la final daca
    solutia este buna */
    for (unsigned int i = 0; i < domain.size(); ++i) {
        /* pastram elementul curent pentru a-l readauga in domeniu dupa
        apelarea recursiva */
        pair<int, int> tmp = domain[i];

        /* adaugam elementul curent la solutia candidat */
        solution.push_back(domain[i]);
        /* stergem elementul curent din domeniu */
        domain.erase(domain.begin() + i);

        /* apelam recursiv backtracking */
        back(domain, walls, solution, max_iter);

        /* adaugam elementul sters din domeniu inapoi */
        domain.insert(domain.begin() + i, tmp);
        /* stergem elementul curent din solutia candidat pentru a o forma pe
        urmatoarea */
        solution.pop_back();
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: ./soarece_ref in_file\n";
        exit(1);
    }

    int n, i, j, walls[100][100];
    ifstream fin(argv[1]);
    /* initializam domeniul si solutia ca vectori de perechi de int-uri;
    domeniul va contine initial toate perechile de indici posibile din
    matrice ((0, 0), (0, 1) ... (n - 1, n - 1)), iar solutia va fi initial
    vida */
    vector<pair<int, int>> domain, solution;

    fin >> n;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            /* walls[i][j] == 1 daca pe pozitia (i, j) este zid; 0 altfel */
            fin >> walls[i][j];
            domain.push_back({i, j});
        }
    }

    /* apelam back cu domeniul format initial, cu matricea de ziduri, cu
    solutia vida si cu numarul maxim de iteratii = 2 * n - 1 pentru ca
    mergand doar in dreapta si in jos, in 2 * n - 1 pasi va ajunge din
    (0, 0) in (n - 1, n - 1) */
    back(domain, walls, solution, 2 * n - 1);
}

// Compile:
// $ make
// Run:
// $ ./soarece_ref tests/medium_in
// (0,0)->(0,1)->(0,2)->(1,2)->(2,2)->
// (0,0)->(1,0)->(2,0)->(2,1)->(2,2)->
