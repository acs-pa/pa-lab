#!/usr/bin/env python3
# SPDX-License-Identifier: BSD-3-Clause


def main() -> None:
    s: set[int] = set()
    s.add(1)
    s.add(12)
    s.add(6)
    s.add(1)
    for x in sorted(s):
        print(x)
    # print: 1 6 12


if __name__ == "__main__":
    main()
