// SPDX-License-Identifier: BSD-3-Clause

impl Solution {
    // Solutie: Sortam vectorul in ordine descrescatoare si returnam al k-lea cel mai mare element.
    // Complexitate: O(nlogn)
    pub fn find_kth_largest(mut nums: Vec<i32>, k: i32) -> i32 {
        nums.sort_unstable_by(|a, b| b.cmp(a));
        nums[(k - 1) as usize]
    }
}