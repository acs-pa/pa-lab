// SPDX-License-Identifier: BSD-3-Clause

#include <algorithm>
#include <queue>
#include <set>
#include <vector>
using namespace std;

class Solution {
public:
    // Solutie: Folosim un multiset pentru a mentine cele mai mari k elemente.
    // Complexitate: O(nlogk)
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        // sol stocheaza al k-lea cel mai mare element din fiecare fereastra.
        vector<int> sol;

        // window stocheaza elementele din fereastra curenta.
        queue<int> window;

        // heap este un multiset care stocheaza cele mai mari k elemente.
        multiset<int, greater<int>> heap;

        for (auto& x : nums) {
            // Insereaza primele k elemente in multiset.
            if (window.size() < k) {
                window.push(x);
                heap.insert(x);
                continue;
            }

            // Insereaza al k-lea cel mai mare element in sol.
            sol.push_back(*heap.begin());

            // Elimina cel mai vechi element din fereastra si din multiset.
            auto old_x = window.front();
            window.pop();
            heap.erase(heap.find(old_x));

            window.push(x);
            heap.insert(x);
        }
        // Insereaza al k-lea cel mai mare element din ultima fereastra in sol.
        sol.push_back(*heap.begin());

        return sol;
    }
};
