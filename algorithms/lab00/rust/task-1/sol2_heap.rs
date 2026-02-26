// SPDX-License-Identifier: BSD-3-Clause

use std::cmp::Reverse;
use std::collections::BinaryHeap;

// Solutie: Folosim un min heap pentru a stoca cele mai mari k elemente.
// Complexitate: O(n log k)

impl Solution {
    pub fn find_kth_largest(nums: &[i32], k: i32) -> i32 {
        let k = k as usize;
        let mut heap: BinaryHeap<Reverse<i32>> = BinaryHeap::with_capacity(k);

        for num in nums {
            heap.push(Reverse(num));
            if heap.len() > k {
                heap.pop(); // scoate cel mai mic dintre cele k+1
            }
        }

        heap.peek().unwrap().0
    }
}
