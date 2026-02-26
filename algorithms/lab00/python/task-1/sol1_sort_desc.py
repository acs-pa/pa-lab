# SPDX-License-Identifier: BSD-3-Clause

class Solution:
    # Solutie: Sortam vectorul in ordine descrescatoare si returnam al k-lea cel mai mare element.
    # Complexitate: O(nlogn)
    @staticmethod
    def findKthLargest(nums: list[int], k: int) -> int:
        nums.sort(reverse=True)
        return nums[k - 1]
