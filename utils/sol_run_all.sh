#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause

set -e

error() {
    echo "$1"
    exit 1
}

declare -a solutions=(
    "lab01,cpp,sol_2020_dn"
    "lab01,java,sol_2020_dn"
    "lab02,cpp,sol_2020_dn"
    "lab02,cpp,sol_2020_dn2,task-3"
    "lab02,java,sol_2020_dn"
    "lab03,cpp,sol_2020_dn"
    "lab03,java,sol_2020_sp"
    "lab04,cpp,sol_2020_dn"
    "lab04,cpp,sol_2020_dn2,task-1"
    "lab04,cpp,sol_2020_dn3,task-1"
    "lab04,cpp,sol_2020_dn4,task-1"
    "lab04,java,sol_2020_sp"
    "lab05,cpp,sol_2020_dn"
    "lab05,java,sol_2020_sp"
    "lab07,cpp,sol_2020_dn"
    "lab07,cpp,sol_2020_dn2,task-2"
    "lab07,java,sol_2020_sp"
    "lab07,java,sol_2020_sp2,task-2"
    "lab08,cpp,sol_2020_dn"
    "lab08,cpp,sol_2020_dn2,task-1"
    "lab08,cpp,sol_2021_rn,task-4"
    "lab08,java,sol_2021_rn"
    "lab08,java,sol_2020_sp,task-1"
    "lab08,java,sol_2020_sp,task-2"
    "lab08,java,sol_2020_sp,task-3"
    "lab09,cpp,sol_2022_rn"
    "lab09,java,sol_2022_rn"
    "lab10,cpp,sol_2022_rn"
    "lab10,java,sol_2022_rn"
    "lab11,cpp,sol_2022_dn"
    "lab11,java,sol_2022_dn"
    "lab12,cpp,sol_2022_dn"
    "lab12,java,sol_2022_dn"
)

for solution in "${solutions[@]}"; do
    TASK_NAME=
    IFS=, read LAB LANG SOL_NAME TASK_NAME <<<"${solution}"

    printf "running sol/%s: %s/%s %s ...\n" "${LAB}" "${LANG}" "${SOL_NAME}" "${TASK_NAME}"
    ./utils/sol_run.sh "${LAB}" "${LANG}" "${SOL_NAME}" "${TASK_NAME}" || error "${LAB}/${LANG}/${SOL_NAME}/${TASK_NAME} failed!"
    printf "\n\n\n"
done

echo "sol/* passed!"
