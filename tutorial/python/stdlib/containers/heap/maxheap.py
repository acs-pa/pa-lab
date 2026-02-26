#!/usr/bin/env python3
# SPDX-License-Identifier: BSD-3-Clause

import heapq

# Python 3.14+ has heappush_max / heappop_max; older versions use the negation hack.
_HAS_HEAP_MAX = hasattr(heapq, "heappush_max")


def main() -> None:
    if _HAS_HEAP_MAX:
        maxheap: list[int] = []
        heapq.heappush_max(maxheap, 1)
        heapq.heappush_max(maxheap, 12)
        heapq.heappush_max(maxheap, 6)
        heapq.heappush_max(maxheap, 1)
        while maxheap:
            top: int = heapq.heappop_max(maxheap)
            print(top)
    else:
        # Fallback for Python < 3.14: negate values in a min-heap.
        maxheap_neg: list[int] = []
        for x in (1, 12, 6, 1):
            heapq.heappush(maxheap_neg, -x)
        while maxheap_neg:
            top = -heapq.heappop(maxheap_neg)
            print(top)
    # print: 12 6 1 1


if __name__ == "__main__":
    main()
