#include <algorithm>
#include <iostream>
#include <vector>
#include <random>

#define dbg(x) std::cerr << (#x) << ": " << (x) << ", ";
#define dbgln(x) std::cerr << (#x) << ": " << (x) << '\n';
#define dbga(x,n) { std::cerr << (#x) << "[]: "; for(int _ = 0; _ < n; _++) std::cerr << x[_] << ' '; std::cerr<<'\n'; }
#define dbgs(x) { std::cerr << (#x) << "[stl]: "; for(auto _: x) std::cerr << _ << ' '; std::cerr<<'\n'; }
#define dbgp(x) { std::cerr << (#x) << ": " << x.first << ' ' << x.second << '\n'; }
#define dbgs2d(x) { std::cerr << (#x) << "[stl 2d]:\n";  for(const auto& y: x) { for (auto _: y) std::cerr << _ << ' '; std::cerr << '\n'; } std::cerr << "---\n"; }
#define dbgsp(x) { std::cerr << (#x) << "[stl pair]:\n"; for(auto _: x) std::cerr << _.first << ' '<< _.second << '\n'; }

struct TrieNode {
    std::array<TrieNode *, 26> children;
    bool is_leaf;

    TrieNode() {
        std::fill(children.begin(), children.end(), nullptr);
        is_leaf = false;
    }

    bool insert(const std::string& s) {
        TrieNode *now = this;
        for (char ch: s) {
            if (!now->children[ch-'a']) now->children[ch-'a'] = new TrieNode;
            now = now->children[ch-'a'];
        }

        bool is_new = !now->is_leaf;
        now->is_leaf = true;
        return is_new;
    }

    ~TrieNode() {
        for (int i = 0; i < (int)children.size(); i++) {
            if (children[i]) delete children[i];
        }
    }
};

int main() {
    std::string s; std::cin >> s;
    int k; std::cin >> k;
    int n = s.size();

    TrieNode *root = new TrieNode;
    int cnt = 0;
    for (int i = 0; i < n-k+1; i++) {
        cnt += root->insert(s.substr(i, k));
    }

    std::cout << cnt << '\n';
    delete root;

    return 0;
}