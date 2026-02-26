# SPDX-License-Identifier: BSD-3-Clause

class Solution:
    # Solutie: QuickSelect - partitionare in loc de sortare
    # Python: folosim quickselect echivalent cu nth_element din C++ pentru al k-lea cel mai mare element.
    # Complexitate: O(n) - caz mediu, O(n^2) - caz defavorabil
    @staticmethod
    def findKthLargest(nums: list[int], k: int) -> int:
        # al k-lea cel mai mare (1-based) = index n-k in ordine crescatoare (0-based)
        target = len(nums) - k
        return Solution.quick_select(nums, 0, len(nums) - 1, target)

    @staticmethod
    def quick_select(nums: list[int], left: int, right: int, idx: int) -> int:
        if left == right:
            return nums[left]
        pivot_idx = Solution.partition(nums, left, right)
        if idx == pivot_idx:
            return nums[idx]
        if idx < pivot_idx:
            return Solution.quick_select(nums, left, pivot_idx - 1, idx)
        return Solution.quick_select(nums, pivot_idx + 1, right, idx)

    @staticmethod
    def partition(nums: list[int], left: int, right: int) -> int:
        pivot = nums[right]
        i = left
        for j in range(left, right):
            if nums[j] <= pivot:
                nums[i], nums[j] = nums[j], nums[i]
                i += 1
        nums[i], nums[right] = nums[right], nums[i]
        return i
