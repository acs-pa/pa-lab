// SPDX-License-Identifier: BSD-3-Clause

#include <iostream>     // cout
#include <set>          // set
using namespace std;

int main() {
    set<int> s;

    // insert element in set
    for (int i = 0; i < 5; ++i) {
        s.insert(i);
    }

    // erase one element from set
    s.erase(4);

    // add another element to see that elements are sorted
    s.insert(-2);

    // iterate a set
    for (const auto& elem : s) {
        cout << elem << " ";
    }
    cout << "\n";

    return 0;
}
