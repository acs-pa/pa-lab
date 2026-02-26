#!/usr/bin/env python3
# SPDX-License-Identifier: BSD-3-Clause


def main() -> None:
    st: list[int] = []
    st.append(1)
    st.append(2)
    st.append(3)
    while st:
        top: int = st.pop()
        print(top)
    # print: 3 2 1


if __name__ == "__main__":
    main()
