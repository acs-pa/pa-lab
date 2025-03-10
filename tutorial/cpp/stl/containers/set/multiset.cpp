// SPDX-License-Identifier: BSD-3-Clause

#include <iostream> // cout
#include <set> // multiset
using namespace std;

int main() {
    multiset<int> ms;
    ms.insert(1);
    ms.insert(2);
    ms.insert(3);
    ms.insert(3);
    ms.insert(2);
    ms.insert(1);

    // iterate a set
    for (const auto& elem : ms) {
        cout << elem << " ";
    }
    cout << "\n";

    return 0;
}

// Compile:
// $ make
//
// Run:
// ./multiset
// 1 1 2 2 3 3
//
