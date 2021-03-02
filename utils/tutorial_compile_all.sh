#!/bin/bash

make_helper() {
    make -C "$(dirname $1)" $2
}

for makefile_path in $(find tutorial/ -name Makefile); do
    make_helper "${makefile_path}" "$1" || exit 1
done
