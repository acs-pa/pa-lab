#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause

set -e

error() {
    echo "$1"
    exit 1
}

export COMPILE_ONLY=true

declare -a labs=(
    "lab01"
    "lab02"
    "lab03"
    "lab04"
    "lab05"
    "lab06"
    "lab07"
    "lab09"
    "lab10"
    "lab11"
    "lab12"
)

for LAB in "${labs[@]}"; do
    pushd "skel/${LAB}" 2>&1 1>/dev/null

    echo "compiling skel/${LAB}/cpp ..."
    ./check cpp 2>&1 1>/dev/null || error "skel/${LAB}/cpp doesn't compile!"
    echo "compiling skel/${LAB}/java ..."
    ./check java 2>&1 1>/dev/null || error "skel/${LAB}/java doesn't compile!"
    popd 2>&1 1>/dev/null
done

echo "skel/* compiled!"

export COMPILE_ONLY=
