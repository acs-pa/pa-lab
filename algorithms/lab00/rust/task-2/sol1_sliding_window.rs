// SPDX-License-Identifier: BSD-3-Clause

use std::collections::btree_map::Entry;
use std::collections::{BTreeMap, VecDeque};

// Solutie: Folosim un BTreeMap pentru a mentine cele mai mari k elemente din fereastra.
// BTreeMap e ordonat dupa cheie; maximul = last_key_value().
// Complexitate: O(n log k)

impl Solution {
    pub fn max_sliding_window(nums: Vec<i32>, k: i32) -> Vec<i32> {
        let k = k as usize;
        let mut sol: Vec<i32> = Vec::new();
        let mut window: VecDeque<i32> = VecDeque::new();
        // heap: multiset (element -> count) ordonat dupa cheie; maximul = ultima cheie
        let mut heap: BTreeMap<i32, usize> = BTreeMap::new();

        for x in nums {
            if window.len() < k {
                window.push_back(x);
                *heap.entry(x).or_insert(0) += 1;
                continue;
            }

            // Insereaza maximul din fereastra curenta in sol.
            let max_key = *heap.keys().next_back().unwrap();
            sol.push(max_key);

            // Elimina cel mai vechi element din fereastra si din multiset.
            let old_x = window.pop_front().unwrap();
            if let Entry::Occupied(mut e) = heap.entry(old_x) {
                *e.get_mut() -= 1;
                if *e.get() == 0 {
                    e.remove_entry();
                }
            }

            window.push_back(x);
            *heap.entry(x).or_insert(0) += 1;
        }
        // Ultima fereastra: maximul
        let max_key = *heap.keys().next_back().unwrap();
        sol.push(max_key);

        sol
    }
}
