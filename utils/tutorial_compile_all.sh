#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause

make_helper() {
    make -C "$(dirname $1)" $2
    make -C "$(dirname $1)" clean
}

for makefile_path in $(find tutorial/ -name Makefile); do
    make_helper "${makefile_path}" "$1" || exit 1
done
