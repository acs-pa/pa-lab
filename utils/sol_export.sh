#!/usr/bin/env bash
# SPDX-License-Identifier: BSD-3-Clause

set -e

if (($# < 4)); then
    echo "Usage: ${0} <lab> <cpp> <sol-name> <export_path>"
    exit 1
fi

LAB="${1}"
LANG="${2}"
SOL_NAME="${3}"
EXPORT_PATH="${4}"
SKEL_PATH="skel/${LAB}/${LANG}"

copy_sol() {
    SOL_FILE="${1}"
    EXPORT_PATH="${2}"

    cp "${SOL_FILE}" "${EXPORT_PATH}/${SOL_FILE}" 2>&1 1>/dev/null
}

export -f copy_sol

find "${SKEL_PATH}/" -regextype posix-extended -regex ".*${SOL_NAME}.${LANG}" -exec bash -c 'copy_sol "${0}" "${1}"' {} "${EXPORT_PATH}" \;
