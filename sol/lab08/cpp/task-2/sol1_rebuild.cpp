// SPDX-License-Identifier: BSD-3-Clause

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    // n = numar de noduri
    int n;

    //
    // parent[node] = parintele nodului node
    // Cazuri particulare:
    //      * parent[source] = -1
    //      * parent[node] = -1, daca node nu este accesibil din nodul sursa.
    //
    vector<int> parent;

    // nodul sursa si nodul destinatie
    // (captele drumului care trebuie reconstruit)
    int source, destination;

    void read_input() {
        ifstream fin("in");
        fin >> n >> source >> destination;
        parent.resize(n + 1);
        for (int node = 1; node <= n; node++) {
            fin >> parent[node];
        }

        fin.close();
    }

    vector<int> get_result() {
        //
        // TODO: Reconstituiti drumul de cost minim de la nodul source la nodul destination
        // folosind vectorul de parinti parent.
        //
        // In cazul in care exista nu exista un drum de la sursa la destinatie, returnati
        // un vector gol (a.k.a. return {};).
        //
        vector<int> path;

        // Pornesc de la nodul destinatie si ii caut parintele.
        int node = destination;

        // Daca parintele lui node este -1, inseamna ca node este chiar source
        // sau node nu este accesibil din nodul source.
        while (parent[node] != -1) {
            // Daca el exista, atunci poate face dintr-un path valid.
            path.push_back(node);

            // Se cauta parintele nodului curent.
            node = parent[node];
        }

        // Daca node nu este sursa, inseamna ca nu am putut ajunge inapoi
        // la nodul sursa, deci trebuie returnat un vector gol.
        if (node != source) {
            return {};
        }

        // Node este sursa, deci se adauga la path.
        path.push_back(source);

        // Se inverseaza ordinea nodurilor, pentru a obtine un drum
        // source - node_1 - node_2 - ... - node_k -  destination,
        // unde un node este parintele vecinului de la dreapta.
        reverse(path.begin(), path.end());

        return path;
    }

    void print_output(const vector<int>& result) {
        ofstream fout("out");

        if (result.empty()) {
            fout << "Nu se poate ajunge\n";
            return;
        }

        for (auto& node : result) {
            fout << node << " ";
        }
        fout << "\n";
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
