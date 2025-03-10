// SPDX-License-Identifier: BSD-3-Clause

#include <iostream> // cin, cout
#include <fstream> // ifstream
#include <utility> // pair
#include <vector> // vector
using namespace std;

bool check(vector<pair<int, int>>& solution) {
    return true;
}

void printSolution(vector<pair<int, int>>& solution) {
    for (pair<int, int> s : solution) {
        cout << "(" << s.first << "," << s.second << ")->";
    }
    cout << "\n";
}

void back(int step, int stop, int walls[100][100], vector<pair<int, int>>& solution, int line_moves[2],
    int col_moves[2]) {
    /* ne oprim dupa ce am ajuns la pasul "stop" si verificam daca solutia este
    corecta */
    if (step == stop) {
        /* deoarece am eliminat ramurile nefolositoare am ajuns la o solutie care
        sigur este corecta */
        if (check(solution)) {
            printSolution(solution);
        }
        return;
    }

    /* daca este primul pas stiu ca soricelul este in pozitia (0, 0) */
    if (step == 0) {
        /* adaugam (0, 0) la solutia candidat */
        solution.push_back({0, 0});

        /* apelam backtracking recursiv la pasul urmator */
        back(step + 1, stop, walls, solution, line_moves, col_moves);

        /* scoatem (0, 0) din solutie */
        solution.pop_back();
        return;
    }

    /* sunt doar doua mutari pe care le pot face intr-un pas: dreapta si jos;
    acestea sunt encodate prin vectorii de directii line_moves[2] = {0, 1} si
    col_moves[2] = {1, 0} care reprezinta la indicele 0 miscarea in dreapta, iar
    la indicele 1 miscarea in jos */
    for (unsigned int i = 0; i < 2; ++i) {
        /* cream noua linie si noua coloana cu ajutorul vectorilor de directii */
        int new_line = solution.back().first + line_moves[i];
        int new_col = solution.back().second + col_moves[i];
        int n = (stop + 1) / 2;

        /* daca linia si coloana sunt valide (nu ies din matrice) si nu este
        zid pe pozitia lor, putem continua pe acea celula */
        if (new_line < n && new_col < n && walls[new_line][new_col] == 0) {
            /* adaugam noua celula in solutia candidat;
            NOTE: {new_line, new_col} este echivalent cu
            pair<int, int>(new_line, new_col) si se numeste "initializer
            list", feature in C++11 */
            solution.push_back({new_line, new_col});

            /* apelam backtracking recursiv la pasul urmator */
            back(step + 1, stop, walls, solution, line_moves, col_moves);

            /* scoatem celula adaugata din solutie */
            solution.pop_back();
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: ./soarece_ref in_file\n";
        exit(1);
    }

    int n, i, j, walls[100][100], line_moves[2] = {0, 1}, col_moves[2] = {1, 0};
    ifstream fin(argv[1]);
    /* initializam solutia ca vector de perechi de int-uri */
    vector<pair<int, int>> solution;

    fin >> n;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            /* citim matricea zidurilor; 1 pentru zid, 0 altfel */
            fin >> walls[i][j];
        }
    }

    /* apelam back cu step = 0, stop = 2 * n - 1 deoarece in 2 * n - 1
    pasi soricelul va ajunge la branza, vectorul de ziduri, vectorul in
    care vom stoca solutia, vectorii de directii line_moves[2] = {0, 1} si
    col_moves[2] = {1, 0}; nu avem nevoie de domeniu deoarece folosind
    vectorii de directii vom sti din ultima pozitie pusa in solutie cele
    doua solutii in care putem merge, astfel domeniul nostru va fi alcatuit
    din doua solutii la fiecare pas (daca ultima pozitie din solutie a fost
    (5, 7) => domeniul pasului curent = {(5 + 0, 7 + 1) si (5 + 1, 7 + 0)}
    care este egal cu {(5, 8), (6, 7)}. */
    back(0, 2 * n - 1, walls, solution, line_moves, col_moves);
}

// Compile:
// $ make
// Run:
// $ ./soarece tests/medium_in
// (0,0)->(0,1)->(0,2)->(1,2)->(2,2)->
// (0,0)->(1,0)->(2,0)->(2,1)->(2,2)->
