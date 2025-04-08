#!/usr/bin/env bash
# SPDX-License-Identifier: BSD-3-Clause

set -e

if (($# < 4)); then
    echo "Usage: ${0} <lab> <lang> <task> <sol-name> <export_path>"
    exit 1
fi

LAB="${1}"
LANG="${2}"
TASK="${3}"
SOL_NAME="${4}"
EXPORT_PATH="${5}"
SOL_PATH="sol/${LAB}/${LANG}/${TASK}"

copy_sol() {
    SOL_FILE="${1}"
    SKEL_PATH=$(echo "${1}" | sed 's|sol/|skel/|1')
    EXPORT_PATH="${2}"

    if [[ ! -f "${EXPORT_PATH}/${SKEL_PATH}" ]]; then
        # Task doesn't have a skel, we need to create intermediary paths
        mkdir -p "${EXPORT_PATH}"/"$(dirname "${SKEL_PATH}")"
    fi
    cp "${SOL_FILE}" "${EXPORT_PATH}/${SKEL_PATH}" 2>&1 1>/dev/null

}

export -f copy_sol

find "${SOL_PATH}" -regextype posix-extended -regex ".*${SOL_NAME}" -exec bash -c 'copy_sol "${0}" "${1}"' {} "${EXPORT_PATH}" \;
