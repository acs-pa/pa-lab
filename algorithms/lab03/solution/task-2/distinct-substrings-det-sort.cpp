#include <algorithm>
#include <iostream>
#include <vector>
#include <random>

int main() {
    std::string s; std::cin >> s;
    int k; std::cin >> k;
    int n = s.size();

    std::vector<int> inds(n-k+1);
    std::iota(inds.begin(), inds.end(), 0);

    std::sort(inds.begin(), inds.end(), [&s, &k](int i, int j) { return s.substr(i, k) < s.substr(j, k); });

    int cnt = 1;
    for (int i = 1; i < n-k+1; i++) {
        if (s.substr(inds[i], k) != s.substr(inds[i-1], k)) cnt++;
    }

    std::cout << cnt << '\n';

    return 0;
}