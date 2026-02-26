# SPDX-License-Identifier: BSD-3-Clause

import bisect
from collections import deque

class Solution:
    # Solutie: Folosim un multiset pentru a mentine cele mai mari k elemente.
    # Complexitate: O(nlogk)
    @staticmethod
    def max_sliding_window(nums: list[int], k: int) -> list[int]:
        # sol stocheaza al k-lea cel mai mare element din fiecare fereastra.
        sol: list[int] = []
        # window stocheaza elementele din fereastra curenta.
        window: deque[int] = deque()
        # heap este un multiset care stocheaza cele mai mari k elemente.
        heap: list[int] = []

        for x in nums:
            # Insereaza primele k elemente in multiset.
            if len(window) < k:
                window.append(x)
                bisect.insort(heap, x)
                continue

            # Insereaza al k-lea cel mai mare element in sol.
            sol.append(heap[-1])

            # Elimina cel mai vechi element din fereastra si din multiset.
            old_x = window.popleft()
            pos = bisect.bisect_left(heap, old_x)
            del heap[pos]

            window.append(x)
            bisect.insort(heap, x)
        # Insereaza al k-lea cel mai mare element din ultima fereastra in sol.
        sol.append(heap[-1])
        return sol
