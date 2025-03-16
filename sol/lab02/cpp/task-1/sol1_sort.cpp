// SPDX-License-Identifier: BSD-3-Clause

#include <algorithm>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

// ATENTIE! In aceasta sursa sunt prezentate 4 metode corecte de a folosi sort.
// Alegeti una!

struct Object {
    int weight;
    int price;

    Object(int _weight, int _price)
        : weight(_weight)
        , price(_price) { }

    // Metoda 1: comparare cu operator<
    bool operator<(const Object& a) const { return 1.0 * this->weight / this->price < 1.0 * a.weight / a.price; }
};

// Metoda 2: functie libera
bool cmp(Object& a, Object& b) {
    return 1.0 * a.weight / a.price < 1.0 * b.weight / b.price;
}

// Metoda 3: comparator
struct Comparator {
    bool operator()(const Object& a, const Object& b) const {
        return 1.0 * a.weight / a.price < 1.0 * b.weight / b.price;
    }
};

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    int n, w;
    vector<Object> objs;

    void read_input() {
        ifstream fin("in");
        fin >> n >> w;
        for (int i = 0, weight, price; i < n; i++) {
            fin >> weight >> price;
            objs.push_back(Object(weight, price));
        }
        fin.close();
    }

    double get_result() {
        // TODO: Aflati profitul maxim care se poate obtine cu obiectele date.
        // metode de sortare:
        // 1. sort(objs.begin(), objs.end());
        // 2. sort(objs.begin(), objs.end(), cmp);
        // 3. sort(objs.begin(), objs.end(), Comparator());

        return knapsack_greedy();
    }

    // T = O(n log n) - sortare
    // S = O(1)       - nu am inclus inputul
    double knapsack_greedy() {
        // Sortare crescatoare greutate/pret
        // Metoda 4: lambda function
        sort(objs.begin(), objs.end(),
            [](const Object& a, const Object& b) { return 1.0 * a.weight / a.price < 1.0 * b.weight / b.price; });

        double sol = 0.0;

        // parcurg lista de obiecte
        for (const auto& o : objs) {
            if (w == 0.0) {
                break; // ghiozdan plin
            }

            // in rucsac pot pune ori tot obiectul, ori o bucata din el (cat mai are loc)
            double weight = min<double>(w, o.weight);
            w -= weight;
            sol += 1.0 * weight / o.weight * o.price;
        }

        return sol;
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
