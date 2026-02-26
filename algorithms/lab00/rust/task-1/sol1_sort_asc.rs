// SPDX-License-Identifier: BSD-3-Clause

// Solutie: Sortam vectorul in ordine crescatoare si returnam al k-lea cel mai mare element.
// Complexitate: O(n log n)

impl Solution {
    pub fn find_kth_largest(mut nums: Vec<i32>, k: i32) -> i32 {
        nums.sort();
        let idx = nums.len() - k as usize;
        nums[idx]
    }
}
