// SPDX-License-Identifier: BSD-3-Clause

#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

class Solution {
public:
    // Solutie: Folosim un min heap pentru a stoca cele mai mari k elemente.
    // Complexitate: O(nlogk).
    int findKthLargest(vector<int>& nums, int k) {
        // pq este un min heap.
        priority_queue<int, vector<int>, greater<int>> pq;

        // Insereaza primele k elemente in min heap.
        for (int i = 0; i < k; ++i) {
            pq.push(nums[i]);
        }

        // Insereaza elementele ramase in min heap.
        for (int i = k; i < nums.size(); ++i) {
            pq.push(nums[i]);
            pq.pop();
        }

        // Elementul din varful min heap-ului este al k-lea cel mai mare element.
        return pq.top();
    }
};
