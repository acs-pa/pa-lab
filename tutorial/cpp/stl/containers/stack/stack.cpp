#include <bits/stdc++.h>

int main() {
    std::stack<int> s;
    for (int i = 0; i < 5; ++i) {
        s.push(i);
    }

    while (!s.empty()) {
        int top = s.top(); // get the top element
        s.pop(); // remove the top element
        std::cout << top << " "; // 4 3 2 1 0
    }
    std::cout << "\n";
    
    return 0;
}
