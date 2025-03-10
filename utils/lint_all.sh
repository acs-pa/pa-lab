#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause

# Lint C++.
find . -name "*.cpp" -or -name "*.cxx" -or -name "*.h" -or -name "*.hpp" | xargs clang-format -i

# Lint Java.
# TODO

# Lint Python.
find . -name "*.py" -or -name "check_task" | xargs autopep8 -i

# Lint Shell.
# TODO

# Lint Markdown.
# TODO

# Lint YAML.
# TODO
