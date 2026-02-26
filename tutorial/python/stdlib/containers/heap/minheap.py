#!/usr/bin/env python3
# SPDX-License-Identifier: BSD-3-Clause

import heapq


def main() -> None:
    minheap: list[int] = []
    heapq.heappush(minheap, 1)
    heapq.heappush(minheap, 12)
    heapq.heappush(minheap, 6)
    heapq.heappush(minheap, 1)
    while minheap:
        top: int = heapq.heappop(minheap)
        print(top)
    # print: 1 1 6 12


if __name__ == "__main__":
    main()
