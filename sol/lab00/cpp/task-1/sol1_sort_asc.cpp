// SPDX-License-Identifier: BSD-3-Clause

#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    // Solutie: Sortam vectorul in ordine crescatoare si returnam al k-lea cel mai mare element.
    // Complexitate: O(nlogn)
    int findKthLargest(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        return nums[nums.size() - k];
    }
};
