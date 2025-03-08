#include <algorithm>   // sort
#include <iostream>    // cout
#include <vector>      // vector
using namespace std;

struct greater_comparator {
    template<class T>
    bool operator()(T const& a, T const& b) const {
        return a > b;
    }
};

int minimum_cost(size_t k, vector<int>& costs) {
    // sortam vectorul de preturi in ordine descrescatoare
    sort(costs.begin(), costs.end(), greater_comparator());

    // numarul de flori cumparate de fiecare individ din grup la un moment dat
    int x = 0;
    // o varianta mai putin eficienta spatial ar fi fost sa retinem pt fiecare
    // individ din grup numarul de flori cumparate intr-un hashmap
    // costul total
    int total_cost = 0;

    // parcurgem fiecare pret de floare si o "asignam" unui individ din grup
    // pretul acesteia fiind proportional cu numarul de achizitii facut pana acum
    // de acesta (x)
    for (size_t idx = 0; idx < costs.size(); idx++) {
        size_t customer_idx = idx % k;
        total_cost += (x + 1) * costs[idx];
        // in momentul in care ultimul individ a cumparat o floare din grupul curent
        // incrementam numarul de flori achizitionate de fiecare
        if (customer_idx == k - 1) {
            x += 1;
        }
    }
    return total_cost;
}

int main() {
    size_t n = 3;
    size_t k = 2;

    vector<int> cost(n);
    cost[0] = 2;
    cost[1] = 5;
    cost[2] = 6;

    cout << minimum_cost(k, cost) << "\n";

    return 0;
}

// Compile:
// $ make
//
// Run:
// $ ./florar
// 15
//
