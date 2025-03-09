#!/usr/bin/env bash
# SPDX-License-Identifier: BSD-3-Clause

set -e

if (($# != 4)); then
    echo "Usage: ${0} <lab> <lang> <sol_name> <task>"
    exit 1
fi

LAB="${1}"
LANG="${2}"
SOL_NAME="${3}"
TASK_NAME="${4}"

SOURCE_DIR="$(realpath "$(dirname "${0}")"/..)/skel/${LAB}/${LANG}/${TASK_NAME}"
if [[ "${LANG}" = "cpp" ]]; then
    SKEL_NAME="main.cpp"
    SOL_NAME="${SOL_NAME}.cpp"
else
    SKEL_NAME="src/Main.java"
    SOL_NAME="src/${SOL_NAME}.java"
fi

diff -y "${SOURCE_DIR}/${SKEL_NAME}" "${SOURCE_DIR}/${SOL_NAME}"
