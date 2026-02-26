#!/usr/bin/env python3
# SPDX-License-Identifier: BSD-3-Clause

from collections import deque


def main() -> None:
    q: deque[int] = deque()
    for i in range(5):
        q.append(i)
    while q:
        front: int = q.popleft()
        print(front, end=" ")
    print()
    # print: 0 1 2 3 4


if __name__ == "__main__":
    main()
