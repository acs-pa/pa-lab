#!/usr/bin/env python3
# SPDX-License-Identifier: BSD-3-Clause


def main() -> None:
    frequency: dict[str, int] = {}
    frequency["gigel"] = frequency.get("gigel", 0) + 1
    frequency["gigel"] = frequency.get("gigel", 0) + 1
    frequency["not_gigel"] = frequency.get("not_gigel", 0) + 1
    for name, count in frequency.items():
        print(name, count)


if __name__ == "__main__":
    main()
