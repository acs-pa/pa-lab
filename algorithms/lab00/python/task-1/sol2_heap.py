# SPDX-License-Identifier: BSD-3-Clause

import heapq

class Solution:
    # Solutie: Folosim un min heap pentru a stoca cele mai mari k elemente.
    # Complexitate: O(nlogk).
    @staticmethod
    def find_kth_largest(nums: list[int], k: int) -> int:
        # pq este un min heap.
        heap: list[int] = nums[:k]
        heapq.heapify(heap)
        # Insereaza primele k elemente in min heap.
        # Insereaza elementele ramase in min heap.
        for x in nums[k:]:
            heapq.heappushpop(heap, x)
        # Elementul din varful min heap-ului este al k-lea cel mai mare element.
        return heap[0]
