#!/bin/bash

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
