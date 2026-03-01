#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause

set -e

cd "$(realpath "$(dirname "$0")/..")"

error() {
    echo "$1"
    exit 1
}

# Param: algorithms/<lab>/<lang> (ex. algorithms/lab01/cpp). Rulează ./check pentru fiecare sursă.
run_algorithms() {
    local param="$1"
    local base="${param%/*}"   # algorithms/lab01
    local lang="${param##*/}"  # cpp
    if ! [ -d "${lang}" ]; then
        echo "Skipping ${param} (not implemented) ..."
        return 0
    fi
    local ext src_extra_prefix
    case "$lang" in
        cpp)
            ext=cpp
            src_extra_prefix=""
            ;;
        java)
            ext=java
            src_extra_prefix="/src"
            ;;
        rust)
            ext=rs
            src_extra_prefix=""
            ;;
        python)
            ext=py
            src_extra_prefix=""
            ;;
        *)
            error "run_algorithms: unknown lang '${lang}'"
            ;;
    esac
    for alg_dir in "${lang}"/*; do
        [ -d "$alg_dir" ] || continue
        algname="$(basename "$alg_dir")"
        local search_dir="${alg_dir}${src_extra_prefix}"
        [ -d "$search_dir" ] || continue
        for sol in "${search_dir}"/*."${ext}"; do
            [ -f "$sol" ] || continue
            solname="$(basename "$sol")"
            path="${lang}/${algname}${src_extra_prefix}/${solname}"
            full_path="${base}/${path}"
            echo ""
            echo "================================================"
            echo "Testing ${full_path} ..."
            tmpout=$(mktemp)
            set +e
            ./check "$path" > "$tmpout" 2>&1
            exitcode=$?
            set -e
            cat "$tmpout"
            pass=0
            if [[ $exitcode -eq 0 ]] && grep -q "Implementation ${algname} 100% complete." "$tmpout"; then
                pass=1
            fi
            rm -f "$tmpout"
            case "$lang" in
                cpp|rust) rm -f "${alg_dir}/${solname%.*}" ;;
                java)     rm -rf "${alg_dir}/bin" ;;
                python)   : ;;
            esac
            if [[ $pass -ne 1 ]]; then
                echo "Nota: In .err.log se afla si afisarile la stdout si stderr din implementarea voastra."
                error "${full_path}: check failed (exit $exitcode or missing 'Implementation ${algname} 100% complete.')"
            fi
            echo "-> check passed"
        done
    done
}

declare -a labs=(
    "lab01"
    "lab02"
    "lab03"
    "lab04"
    "lab05"
    "lab06"
    "lab07"
    "lab08"
    "lab09"
    "lab10"
    "lab11"
)

TARGET_DIR="algorithms"
for LAB in "${labs[@]}"; do
    pushd "${TARGET_DIR}/${LAB}" 2>&1 1>/dev/null
    run_algorithms "${TARGET_DIR}/${LAB}/cpp"
    run_algorithms "${TARGET_DIR}/${LAB}/java"
    run_algorithms "${TARGET_DIR}/${LAB}/python"
    run_algorithms "${TARGET_DIR}/${LAB}/rust"
    popd 2>&1 1>/dev/null
done

echo "${TARGET_DIR}/* compiled and tested!"
