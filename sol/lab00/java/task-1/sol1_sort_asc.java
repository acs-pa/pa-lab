// SPDX-License-Identifier: BSD-3-Clause

import java.util.Arrays;

class Solution {
    // Solutie: Sortam vectorul in ordine crescatoare si returnam al k-lea cel mai mare element.
    // Complexitate: O(nlogn)
    public int findKthLargest(int[] nums, int k) {
        Arrays.sort(nums);
        return nums[nums.length - k];
    }
}
