// SPDX-License-Identifier: BSD-3-Clause

import java.util.PriorityQueue;

class Solution {
    // Solutie: Folosim un min heap pentru a stoca cele mai mari k elemente.
    // Complexitate: O(nlogk)
    public int findKthLargest(int[] nums, int k) {
        // pq este un min heap.
        PriorityQueue<Integer> pq = new PriorityQueue<>();

        // Insereaza primele k elemente in min heap.
        for (int i = 0; i < k; ++i) {
            pq.add(nums[i]);
        }

        // Insereaza elementele ramase in min heap.
        for (int i = k; i < nums.length; ++i) {
            pq.add(nums[i]);
            pq.poll(); // Elimina cel mai mic element pentru a pastra doar cele mai mari k elemente.
        }

        // Elementul din varful min heap-ului este al k-lea cel mai mare element.
        return pq.peek();
    }
}
