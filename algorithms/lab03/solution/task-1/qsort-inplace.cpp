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

    int piv = pivs[cnt_pivots / 2], piv_val = *(begin + piv), piv_pos = 0;
    for (auto it = begin; it < end; it++) piv_pos += *it < piv_val;

    std::iter_swap(begin + piv, begin + piv_pos);

    int l = 0, r = n-1;
    while (l < piv_pos) {
        while (l < piv_pos && *(begin + l) < piv_val) l++;
        while (r > piv_pos && *(begin + r) >= piv_val) r--;
        if (l < piv_pos) {
            std::iter_swap(begin + l, begin + r);
            l++; r--;
        }
    }

    qsort(begin, begin + piv_pos, mt, max_depth, depth+1);
    qsort(begin + piv_pos+1, end, mt, max_depth, depth+1);
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
