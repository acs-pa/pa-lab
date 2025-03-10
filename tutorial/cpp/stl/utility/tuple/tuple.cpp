// SPDX-License-Identifier: BSD-3-Clause

#include <iostream> // cout
#include <string> // string
#include <utility> // tuple
using namespace std;

int main() {
    tuple<int, int> t1 = {1, 2};
    tuple<int, int, int> t2 = {1, 2, 3};
    tuple<int, char, bool, string, int> t3 = {1, '2', false, "gigel", -1};

    // example: a 3D position -> tuple of coordinates (e.g. integer coordinates)
    auto [x, y, z]
        = t2; // unpack a tuple into 3 variables: x is the 1st member, y is the 2nd member, z is the 3rd member
    cout << x << " " << y << " " << z << "\n";
    return 0;
}
// the members from a tuple can also be accessed via get
// cout << get<0>(position) << " " << get<1>(position) << " " << get<2>(position) << "\n";
// we encourage you to use the structure binding pattern
