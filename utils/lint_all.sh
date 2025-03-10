#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause

# Lint C++.
find . -name "*.cpp" -or -name "*.h" | xargs clang-format -i

# Lint Java.
# TODO

# Lint Python.
# TODO

# Lint Shell.
# TODO
