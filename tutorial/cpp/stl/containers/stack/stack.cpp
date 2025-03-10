// SPDX-License-Identifier: BSD-3-Clause

#include <iostream> // cout
#include <stack> // stack
using namespace std;

int main() {
    stack<int> st;
    for (int i = 0; i < 5; ++i) {
        st.push(i);
    }

    while (!st.empty()) {
        auto top = st.top(); // get the top element
        st.pop(); // remove the top element
        cout << top << " "; // 4 3 2 1 0
    }
    cout << "\n";

    return 0;
}
