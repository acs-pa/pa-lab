#include <iostream>
#include <vector>
#include <random>
#include <array>

constexpr int cnt_pivots = 7;

void qsort(std::vector<int>::iterator begin, std::vector<int>::iterator end, std::mt19937& mt, int& max_depth, int depth) {
    max_depth = std::max(max_depth, depth);

    if (begin + 1 >= end) return;

    int n = std::distance(begin, end);
    
    std::array<int, cnt_pivots> pivs;
    for (int i = 0; i < cnt_pivots; i++) pivs[i] = std::uniform_int_distribution<int>(0, n-1)(mt);

    for (int i = 0; i < cnt_pivots; i++) {
        for (int j = i+1; j < cnt_pivots; j++) {
            if (*(begin + pivs[i]) > *(begin + pivs[j])) std::swap(pivs[i], pivs[j]);
        }
    }

    int piv = pivs[cnt_pivots / 2], piv_val = *(begin + piv);

    std::vector<int> lower, higher, equal;
    for (auto it = begin; it < end; it++) {
        if (*it < piv_val) lower.push_back(*it);
        else if (*it > piv_val) higher.push_back(*it);
        else equal.push_back(*it);
    }

    qsort(lower.begin(), lower.end(), mt, max_depth, depth+1);
    qsort(higher.begin(), higher.end(), mt, max_depth, depth+1);

    std::copy(lower.begin(), lower.end(), begin);
    std::copy(equal.begin(), equal.end(), begin + lower.size());
    std::copy(higher.begin(), higher.end(), begin + lower.size() + equal.size());
}

int main() {
    int n; std::cin >> n;

    std::vector<int> v(n);
    for (int i = 0; i < n; i++) std::cin >> v[i];

    std::random_device rd;
    std::mt19937 mt(rd());

    int max_depth = 0;
    qsort(v.begin(), v.end(), mt, max_depth, 0);

    for (int i = 0; i < n; i++) std::cout << v[i] << ' ';
    std::cout << '\n' << max_depth << '\n';

    return 0;
}
