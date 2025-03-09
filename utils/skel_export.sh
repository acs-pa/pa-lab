#!/usr/bin/env bash
# SPDX-License-Identifier: BSD-3-Clause

set -e

if (($# < 2)); then
    echo "Usage: ${0} <lab> <export_path>"
    exit 1
fi

LAB="${1}"
UTILS_PATH="$(realpath $(dirname ${0}))"
SKEL_PATH="$(realpath ${UTILS_PATH}/..)/skel/${LAB}"

EXPORT_PATH="${2}"
SKEL_EXPORT_PATH="${EXPORT_PATH}/skel/"
UTILS_EXPORT_PATH="${EXPORT_PATH}/utils"

mkdir -p "${SKEL_EXPORT_PATH}/" 2>&1 1>/dev/null
rm -rf "${SKEL_EXPORT_PATH}/${LAB}" 2>&1 1>/dev/null
cp -r "${SKEL_PATH}" "${SKEL_EXPORT_PATH}" 2>&1 1>/dev/null
find "${SKEL_EXPORT_PATH}/" -regextype posix-extended -regex '^.*sol_[0-9]{4}_[a-zA-Z0-9]{2,}.((cpp)|(java))' -exec rm -f {} \;

mkdir -p "${UTILS_EXPORT_PATH}" 2>&1 1>/dev/null
cp -r "${UTILS_PATH}/base_check.sh" "${UTILS_EXPORT_PATH}" 2>&1 1>/dev/null
cp -r "${UTILS_PATH}/default_checker.sh" "${UTILS_EXPORT_PATH}" 2>&1 1>/dev/null
