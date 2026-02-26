#!/usr/bin/env python3
# SPDX-License-Identifier: BSD-3-Clause


def main() -> None:
    with open("in") as fin:
        x: int = int(fin.readline().strip())
        tokens: list[str] = fin.readline().split()
        a: int = int(tokens[0])
        b: int = int(tokens[1])
        line: list[str] = fin.readline().split()
        n: int = int(line[0])
        c: str = line[1][0]
        s: str = line[2]

    with open("out", "w") as fout:
        fout.write(f"{x} {a} {b} {c} {s}\n")
    print("wrote to out")


if __name__ == "__main__":
    main()
