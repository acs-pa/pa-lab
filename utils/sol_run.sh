#!/usr/bin/env bash
# SPDX-License-Identifier: BSD-3-Clause

set -e

if (($# < 4)); then
    echo "Usage: ${0} <lab> <lang> <sol-name> <task-name>"
    exit 1
fi

LAB="${1}"
LANG="${2}"

SOL_NAME="${3}"
TASK_NAME="${4}"

WORKING_DIR="/tmp/mumu"
rm -rf "${WORKING_DIR}" 2>&1 1>/dev/null
mkdir -p "${WORKING_DIR}" 2>&1 1>/dev/null

# copy skel
SKEL_EXPORT_SCRIPT="$(dirname ${0})/skel_export.sh"
"${SKEL_EXPORT_SCRIPT}" "${LAB}" "${WORKING_DIR}" 2>&1 1>/dev/null

# copy sol
SOL_EXPORT_SCRIPT="$(dirname ${0})/sol_export.sh"
"${SOL_EXPORT_SCRIPT}" "${LAB}" "${LANG}" "${TASK_NAME}" "${SOL_NAME}.${LANG}" "${WORKING_DIR}" 2>&1 1>/dev/null

pushd "${WORKING_DIR}/skel/${LAB}" 2>&1 1>/dev/null

export SOURCE_CPP="${SOL_NAME}.cpp"
export EXE_CPP="${SOL_NAME}"
export SOURCE_JAVA="${SOL_NAME}.java"
export MAIN_CLASS_JAVA="${SOL_NAME}"

./check "${LANG}" ${TASK_NAME}

popd 2>&1 1>/dev/null

rm -rf "${WORKING_DIR}"
