#!/usr/bin/env python3
# SPDX-License-Identifier: BSD-3-Clause


def main() -> None:
    v: list[int] = []
    v.append(5)
    v.append(1)
    v.append(3)
    print("len =", len(v))
    print("last =", v[-1])
    last: int = v.pop()
    print("pop =", last, "len =", len(v))


if __name__ == "__main__":
    main()
