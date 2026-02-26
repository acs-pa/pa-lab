// SPDX-License-Identifier: BSD-3-Clause

#include <iostream>
#include <set>
using namespace std;

int main() {
    multiset<int> minheap;
    minheap.insert(1);
    minheap.insert(12);
    minheap.insert(6);
    minheap.insert(1);

    while (!minheap.empty()) {
        auto top = *minheap.begin();
        minheap.erase(minheap.begin());
        cout << top << "\n";
    }
    // print: 1 1 6 12
    return 0;
}
