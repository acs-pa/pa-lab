// SPDX-License-Identifier: BSD-3-Clause

#include <iostream> // cout
#include <map> // map
#include <string> // string
using namespace std;

int main() {
    map<string, int> grades;
    // insert element in map (keys will be sorted)
    grades["A"] = 10;
    grades["B"] = 8;
    grades["B-"] = 7;
    grades["A-"] = 9;

    // find element in map
    if (grades.find("A") != grades.end()) {
        cout << "A in dict\n";
    }

    if (grades.find("C") == grades.end()) {
        cout << "C not in dict\n";
    }

    // erase element from map
    grades.erase("A");
    if (grades.find("A") == grades.end()) {
        cout << "A not in dict anymore\n";
    }

    // insert another element to see that keys are sorted
    grades["D"] = 5;

    // want to change x in the loop -> use non-const reference
    for (auto& [key, value] : grades) {
        value--;
    }

    // don't want to change x in the loop -> use const reference
    for (const auto& [key, value] : grades) {
        cout << key << " " << value << "\n";
    }

    return 0;
}
