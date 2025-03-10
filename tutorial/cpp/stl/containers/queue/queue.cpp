// SPDX-License-Identifier: BSD-3-Clause

#include <iostream> // cout
#include <queue> // queue
using namespace std;

int main() {
    queue<int> q;
    for (int i = 0; i < 5; ++i) {
        q.push(i);
    }

    while (!q.empty()) {
        auto front = q.front();
        q.pop();
        cout << front << " "; // 0 1 2 3 4
    }
    cout << "\n";
    return 0;
}
