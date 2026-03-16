#include <iostream>
#include <vector>
#include <random>
#include <array>

constexpr int cnt_pivots = 1;

int main() {
    int n; std::cin >> n;

    std::vector<int> v(n);
    for (int i = 0; i < n; i++) std::cin >> v[i];

    ///TODO. faceti cate un executabil pentru fiecare valoare de cnt_pivots.

    for (int i = 0; i < n; i++) std::cout << v[i] << ' ';
    // std::cout << '\n' << max_depth << '\n';

    return 0;
}
