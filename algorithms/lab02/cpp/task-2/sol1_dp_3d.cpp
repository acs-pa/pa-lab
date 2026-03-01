// SPDX-License-Identifier: BSD-3-Clause

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// constanta modulo folosita in aceasta problema
#define MOD ((int)1e9 + 7)
// sau
// #define MOD 100000007
// (varianta 2 e mai ușor de busit, sesizați? :p)

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    int n;
    string expr;

    void read_input() {
        ifstream fin("in");
        fin >> n >> expr;
        expr = " " + expr; // adaugare caracter fictiv - indexare de la 1
        fin.close();
    }

    int get_result() {
        // Calculati numarul de parantezari ale expresiei date astfel incat
        // rezultatul sa dea true si returnati restul impartirii numarului
        // la 10^9 + 7 (vezi macro-ul MOD).

        return bool_expression();
    }

    bool is_operator(char op) { return op == '&' || op == '|' || op == '^'; }

    bool is_operand(char op) { return op == 'T' || op == 'F'; }

    bool evaluate(char op, int L, int R) {
        if (op == '&')
            return L & R;
        if (op == '|')
            return L | R;
        if (op == '^')
            return L ^ R;

        // valoare default pentru evitare warnings
        return false;
    }

    // T = O(n ^ 3)
    // S = O(n ^ 2) - stocam n x n x 2 numere intregi in tabloul dp
    //          Obs. Chiar daca dp are 3 dimensiuni, o dimensiune este foarte mica! (sesizati? :p)
    int bool_expression() {
        //      Problema seamna cu PODM, coincidenta tot vorba de parantezari...
        //      La PODM avem o dinamica de forma dp[i][j] = ..., ceea ce ar avea foarte mult sens si aici,
        // intrucat [i,j] ar reprezenta o subexpresie!
        //      Este suficient sa avem doua dimensiuni?
        //          - ar suna asa:
        //              dp[i][j] = numarul de moduri de a paranteza expr[i...j] pentru a obtine valoarea 1 (True)
        //          - privind tabela de adevar a celor 3 operatori, observam ca avem nevoie sa stim si valorile
        //              de 0 (False).
        //              Ex. La xor se obtine 1 pentru operatorii 1, 0 sau 0, 1.
        //          - din motivele mentionate anterior, vom calcula raspunsul si pentru a obtine expresia cu valoarea
        //              1, dar si pentru a obtine expresia cu valoarea 0.

        // dp[i][j][v] = numarul de moduri de a paranteza expresia expr[i...j] pentru a obtine valoarea v
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(n + 1, vector<int>(2, 0)));
        // dp are dimensiunile n x n x 2 (daca nu va place acest oneliner,
        // puteti sa alocati fiecare dimensiune pas cu pas)

        // Asemanator problemei PODM, dorim sa plecam de la intervale cat mai mici si sa ne extindem.
        // Adica daca cunoastem parantezari pentru subexpresii, cum rezolvam expresii mai mari.

        // Cazul de baza: intervalele de forma [i, i], care nu necesita paranteze.
        // Pentru expresii de forma  "expr[i]", valorea expresiei e chiar valoarea operandului.
        for (int i = 1; i <= n; i += 2) {
            dp[i][i][0] = (expr[i] == 'F');
            dp[i][i][1] = (expr[i] == 'T');
        }

        //      Fie o expresie [i, j], care este de forma: expr[i] expr[i + 1] ... expr[j]
        //      Ce inseamna a paranteza aceasta expresie?
        // Obtinem o expresie de forma: (expr[i] ... expr[k - 1]) expr[k] (expr[k + 1] ... expr[j])
        //      Obs. expr[k] este un operator!
        //      Notam cu E toata expresia, L (left) si R (right) cele 2 subexpresii, cu op operatorul
        // Obtinem: E = L op R
        //      Daca am sti toate modurile de parantezare pentru L si R,
        // atunci E o sa fie o combinatie.
        //
        //      Ex. Daca avem X moduri in stanga, Y moduri in
        // dreapta, atunci se vor obtine X * Y moduri noi de a paranteza
        // subsecventa [i, j], deoarece parantezele din stanga si din
        // dreapta sunt independente.

        //      Deoarece pentru expresii mai mari avem nevoie de expresii mai mici (de lungime mai mica),
        // vom procesa intervalele in ordinea lungimii (lungime 1, 2, 3, ...)
        //      Obs. In for-ul aneterior am calculat deja intervalele de lungime 1 ([i, i])

        //      Pentru a afla solutia pentru un interval [i, j] (o expresie), avem mai multe moduri de a
        // paranteza.
        //      Fiecare parantezare inseamna separarea lui [i,j] in [i, k - 1] op [k + 1, j]
        // (observatie: pe pozitia k este un operator, care aplica o operatie intre valorile celor doua subexpresii)

        for (int len = 2; len <= n; ++len) { // fixam lungimea intervalului (2, 3, 4, ...)
            for (int i = 1; i + len - 1 <= n; ++i) { // fixam capatul din stanga: i
                int j = i + len - 1; // capatul din dreapta se deduce: j

                // Iteram prin indicii dintre capete, cautand un loc unde
                // subsecventa poate fi "sparta" in 2 de un operator.
                for (int k = i + 1; k < j; ++k) { // k este OPERATOR intre i si j
                    if (!is_operator(expr[k])) {
                        continue;
                    }
                    char op = expr[k]; // am extras OPERATORUL

                    // lv rv        (lv = left value, rv = right value)
                    // 0  0
                    // 0  1
                    // 1  0
                    // 1  1
                    for (int lv = 0; lv <= 1; ++lv) {
                        for (int rv = 0; rv <= 1; ++rv) {
                            //   v = lv op rv               (v = value)
                            bool v = evaluate(op, lv, rv);

                            // X = moduri de parantezare pentru expresia de la stanga  ([i  , k-1])
                            // Y = moduri de parantezare pentru expresia de la dreapta ([k+1, j])
                            // numar moduri =     X           *      Y
                            int add = (1LL * dp[i][k - 1][lv] * dp[k + 1][j][rv]) % MOD;

                            // Trebuie sa il adaugam la rezultatul pentru [i,j] si valoare v
                            dp[i][j][v] = (dp[i][j][v] + add) % MOD;
                        }
                    }
                }
            }
        }

        // Rezultatul se afla in dp[1][n][1]: Numarul de parantezari pentru
        // intreg sirul cu valoarea de adevar 1 (TRUE).
        return dp[1][n][1];
    }

    void print_output(int result) {
        ofstream fout("out");
        fout << result << '\n';
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
