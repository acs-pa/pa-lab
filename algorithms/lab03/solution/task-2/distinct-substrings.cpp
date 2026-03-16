#include <algorithm>
#include <iostream>
#include <vector>
#include <random>

int main() {
    const int mod = 1'000'000'007;

    std::random_device rd;
    std::mt19937 mt(rd());
    int base = std::uniform_int_distribution<int>(27, mod - 1)(mt);

    std::string s; std::cin >> s;
    int k; std::cin >> k;
    int n = s.size();

    int base_k1 = 1;
    for (int i = 1; i < k; i++) base_k1 = (long)base_k1 * base % mod;

    std::vector<int> hhs(n-k+1);
    for (int i = 0; i < k; i++) hhs[0] = ((long)hhs[0] * base + s[i] - 'a') % mod;

    for (int i = 1; i < n-k+1; i++) {
        hhs[i] = ((hhs[i-1] - (long)base_k1 * (s[i-1] - 'a') % mod + mod) * base + s[k+i-1] - 'a') % mod;
    }

    std::sort(hhs.begin(), hhs.end());
    hhs.resize(std::unique(hhs.begin(), hhs.end()) - hhs.begin());

    std::cout << hhs.size() << '\n';

    return 0;
}