// SPDX-License-Identifier: BSD-3-Clause

#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    // Solutie: QuickSelect - partitionare in loc de sortare
    // C++ STL: Folosim functia nth_element pentru a gasi al k-lea cel mai mare element.
    // Complexitate: O(n) - caz mediu, O(n^2) - caz defavorabil
    int findKthLargest(vector<int>& nums, int k) {
        nth_element(nums.begin(), nums.begin() + (nums.size() - k), nums.end());
        return nums[nums.size() - k];
    }
};
