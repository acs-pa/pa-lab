// SPDX-License-Identifier: BSD-3-Clause

// Solutie: QuickSelect - partitionare in loc de sortare.
// Rust: select_nth_unstable pentru a gasi al k-lea cel mai mare element.
// Complexitate: O(n) caz mediu, O(n^2) caz defavorabil

impl Solution {
    pub fn find_kth_largest(mut nums: Vec<i32>, k: i32) -> i32 {
        let n = nums.len();
        let idx = n - k as usize; // al k-lea cel mai mare
        let (_, mid, _) = nums.select_nth_unstable(idx);
        *mid
    }
}
