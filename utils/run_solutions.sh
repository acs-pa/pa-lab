#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause

set -e

UTILS_PATH="$(realpath $(dirname ${0}))"

error() {
    echo "$1"
    exit 1
}

declare -a solutions=(
    "lab01,cpp"
    "lab01,java"
    "lab02,cpp"
    "lab02,java"
    "lab03,cpp"
    "lab03,java"
    "lab04,cpp"
    "lab04,java"
    "lab05,cpp"
    "lab05,java"
    "lab06,cpp"
    "lab06,java"
    "lab07,cpp"
    "lab07,java"
    "lab08,cpp"
    "lab08,java"
    "lab09,cpp"
    "lab09,java"
    "lab10,cpp"
    "lab10,java"
)

for solution in "${solutions[@]}"; do
    TASK_NAME=""
    IFS=, read LAB LANG <<<"${solution}"

    SOL_PATH="$(realpath ${UTILS_PATH}/..)/sol/${LAB}"

    if [ ! -d "$SOL_PATH" ]; then
        echo "Solution folder for ${LAB} does not exist!"
        exit 1
    fi

    for task in ${SOL_PATH}/${LANG}/*; do
        SOL_PATH=$task
        if [ -e "${task}/src" ]; then
            SOL_PATH=$task/src
        fi

        if [ -d "$task" ]; then
            TASK_NAME=$(basename "$task")
            for sol in $SOL_PATH/*; do
                SOL_FILE=$(basename "$sol") 
                SOL_NAME="${SOL_FILE%.*}"
                printf "running sol/%s: %s/%s %s ...\n" "${LAB}" "${LANG}" "${SOL_NAME}" "${TASK_NAME}"
                ./utils/sol_run.sh "${LAB}" "${LANG}" "${SOL_NAME}" "${TASK_NAME}" || error "${LAB}/${LANG}/${SOL_NAME}/${TASK_NAME} failed!"
                printf "\n\n\n"
            done
        fi
    done
done

echo "sol/* passed!"
