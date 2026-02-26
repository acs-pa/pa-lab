// SPDX-License-Identifier: BSD-3-Clause

#include <functional>
#include <iostream>
#include <set>
using namespace std;

int main() {
    multiset<int, greater<int>> maxheap;
    maxheap.insert(1);
    maxheap.insert(12);
    maxheap.insert(6);
    maxheap.insert(1);

    while (!maxheap.empty()) {
        auto top = *maxheap.begin();
        maxheap.erase(maxheap.begin());
        cout << top << "\n";
    }
    // print: 12 6 1 1
    return 0;
}
