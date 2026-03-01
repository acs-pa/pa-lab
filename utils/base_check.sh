#!/usr/bin/env bash
# SPDX-License-Identifier: BSD-3-Clause

TMP_FILE="$PWD/.tmp"
LOG_NAME="$PWD/.err.log"

FAILED_TOTAL=0
MAX_SIZE_SHOWN=30

CXX=g++
CXXFLAGS="-std=c++17 -Werror=vla -O3"
JAVAFLAGS="-Xmx128M -Xss128M -server"
RUSTFLAGS="-C opt-level=3"
PYTHONFLAGS="-u"

# timeout for each language
if [ -z "${TIMEOUT_CPP}" ]; then
  TIMEOUT_CPP=1
fi
if [ -z "${TIMEOUT_JAVA}" ]; then
  TIMEOUT_JAVA=2
fi
if [ -z "${TIMEOUT_RUST}" ]; then
  TIMEOUT_RUST=1
fi
if [ -z "${TIMEOUT_PYTHON}" ]; then
  TIMEOUT_PYTHON=1
fi

# Cross-platform timeout (using perl).
timeout() {
  perl -e 'alarm shift; exec @ARGV' "$@"
}


check_prerequisites() {
  for prereq in "$@"; do
    command -v "$prereq" >/dev/null 2>&1 || {
      echo "Eroare: Nu am gasit '${prereq}'. Instaleaza '${prereq}'."
      exit 1
    }
  done
}

check_prerequisites_cpp() {
  check_prerequisites python3 g++
}

check_prerequisites_java() {
  check_prerequisites python3 java javac
}

check_prerequisites_rust() {
  check_prerequisites python3 rustc
}

check_prerequisites_python() {
  check_prerequisites python3
}

show_help() {
  echo "Utilizare: ./check <lang>/<algorithm>/<sursa>"
  echo ""
  echo " (presupune ca directorul curent este radacina laboratorului curent)"
  echo ""
  echo -e "algorithms/lab01 $  ./check cpp/01-ssm/01-ssm.cpp"
  echo -e "algorithms/lab01 $ ./check java/01-ssm/src/ssm.java"
  echo -e "algorithms/lab01 $ ./check rust/01-ssm/01-ssm.rs"
  echo -e "algorithms/lab01 $ ./check python/01-ssm/01-ssm.py"
  exit 1
}

task_index() {
  task_name=$1

  for index in $(seq 0 $(($NUM_TASKS - 1))); do
    if [[ "${TASKS[$index]}" == "$task_name" ]]; then
      echo $index
      return
    fi
  done

  echo -1
}

compile_java() {
  result=0
  local task_dir="$1"
  # Dacă sursa e un path (conține /), compilăm din rădăcina lab-ului, fără a copia sursa.
  if [[ "${SOURCE_JAVA}" == */* ]]; then
    mkdir -p "${task_dir}/bin"
    if [[ ! (-f "${task_dir}/bin/${MAIN_CLASS_JAVA}.class" && "${task_dir}/bin/${MAIN_CLASS_JAVA}.class" -nt "${SOURCE_JAVA}") ]]; then
      echo "Compiling ${SOURCE_JAVA}..." >>"$LOG_NAME" 2>&1
      javac "${SOURCE_JAVA}" -d "${task_dir}/bin" >"$TMP_FILE" 2>&1
      result=$?
      cat "$TMP_FILE" >>"$LOG_NAME"
      head -n 3 "$TMP_FILE"
      echo "========================================" >>"$LOG_NAME" 2>&1
    fi
  else
    command pushd "$task_dir" &>/dev/null
    if [[ ! (-f bin/"${MAIN_CLASS_JAVA}.class" && bin/"${MAIN_CLASS_JAVA}.class" -nt src/"${SOURCE_JAVA}") ]]; then
      mkdir -p bin
      echo "Compiling $task_dir..." >>"$LOG_NAME" 2>&1
      javac src/"${SOURCE_JAVA}" -d bin >"$TMP_FILE" 2>&1
      result=$?
      cat "$TMP_FILE" >>"$LOG_NAME"
      head -n 3 "$TMP_FILE"
      echo "========================================" >>"$LOG_NAME" 2>&1
    fi
    command popd &>/dev/null
  fi
  return $result
}

compile_cpp() {
  result=0
  local task_dir="$1"
  # Dacă sursa e un path (conține /), compilăm din rădăcina lab-ului, fără a copia sursa.
  if [[ "${SOURCE_CPP}" == */* ]]; then
    if [[ ! (-f "${task_dir}/${EXE_CPP}" && "${task_dir}/${EXE_CPP}" -nt "${SOURCE_CPP}") ]]; then
      echo "Compiling ${SOURCE_CPP}..." >>"$LOG_NAME" 2>&1
      ${CXX} ${CXXFLAGS} -o "${task_dir}/${EXE_CPP}" "${SOURCE_CPP}" >"$TMP_FILE" 2>&1
      result=$?
      cat "$TMP_FILE" >>"$LOG_NAME"
      head -n 3 "$TMP_FILE"
      echo "========================================" >>"$LOG_NAME" 2>&1
    fi
  else
    command pushd "$task_dir" &>/dev/null
    if [[ ! (-f "${EXE_CPP}" && "${EXE_CPP}" -nt "${SOURCE_CPP}") ]]; then
      echo "Compiling $task_dir..." >>"$LOG_NAME" 2>&1
      ${CXX} ${CXXFLAGS} -o "${EXE_CPP}" "${SOURCE_CPP}" >"$TMP_FILE" 2>&1
      result=$?
      cat "$TMP_FILE" >>"$LOG_NAME"
      head -n 3 "$TMP_FILE"
      echo "========================================" >>"$LOG_NAME" 2>&1
    fi
    command popd &>/dev/null
  fi
  return $result
}

compile_rust() {
  result=0
  local task_dir="$1"
  # Dacă sursa e un path (conține /), compilăm din rădăcina lab-ului, fără a copia sursa.
  if [[ "${SOURCE_RUST}" == */* ]]; then
    if [[ ! (-f "${task_dir}/${EXE_RUST}" && "${task_dir}/${EXE_RUST}" -nt "${SOURCE_RUST}") ]]; then
      echo "Compiling ${SOURCE_RUST}..." >>"$LOG_NAME" 2>&1
      rustc ${RUSTFLAGS} -o "${task_dir}/${EXE_RUST}" "${SOURCE_RUST}" >"$TMP_FILE" 2>&1
      result=$?
      cat "$TMP_FILE" >>"$LOG_NAME"
      head -n 3 "$TMP_FILE"
      echo "========================================" >>"$LOG_NAME" 2>&1
    fi
  else
    command pushd "$task_dir" &>/dev/null
    if [[ ! (-f "${EXE_RUST}" && "${EXE_RUST}" -nt "${SOURCE_RUST}") ]]; then
      echo "Compiling $task_dir..." >>"$LOG_NAME" 2>&1
      rustc ${RUSTFLAGS} -o "${EXE_RUST}" "${SOURCE_RUST}" >"$TMP_FILE" 2>&1
      result=$?
      cat "$TMP_FILE" >>"$LOG_NAME"
      head -n 3 "$TMP_FILE"
      echo "========================================" >>"$LOG_NAME" 2>&1
    fi
    command popd &>/dev/null
  fi
  return $result
}

run_java() {
  command pushd "$1" &>/dev/null
  echo "Running $1..." >>"$LOG_NAME" 2>&1
  timeout ${TIMEOUT_JAVA} java ${JAVAFLAGS} -cp bin "${MAIN_CLASS_JAVA}" >>"$LOG_NAME" 2>&1
  result=$?
  echo "========================================" >>"$LOG_NAME" 2>&1
  command popd &>/dev/null

  return $result
}

run_cpp() {
  command pushd "$1" &>/dev/null
  echo "Running $1..." >>"$LOG_NAME" 2>&1
  timeout ${TIMEOUT_CPP} ./"${EXE_CPP}" >>"$LOG_NAME" 2>&1
  result=$?
  echo "========================================" >>"$LOG_NAME" 2>&1
  command popd &>/dev/null

  return $result
}

run_rust() {
  command pushd "$1" &>/dev/null
  echo "Running $1..." >>"$LOG_NAME" 2>&1
  timeout ${TIMEOUT_RUST} ./"${EXE_RUST}" >>"$LOG_NAME" 2>&1
  result=$?
  echo "========================================" >>"$LOG_NAME" 2>&1
  command popd &>/dev/null

  return $result
}

cleanup_java() {
  command pushd "$1" &>/dev/null
  rm -rf bin in out
  command popd &>/dev/null
}

cleanup_cpp() {
  command pushd "$1" &>/dev/null
  rm -rf "${EXE_CPP}" in out
  command popd &>/dev/null
}

cleanup_rust() {
  command pushd "$1" &>/dev/null
  rm -rf "${EXE_RUST}" in out
  command popd &>/dev/null
}

compile_python() {
  local task_dir="$1"
  if [[ "${SOURCE_PYTHON}" == */* ]]; then
    [[ -f "${SOURCE_PYTHON}" ]] || { echo "Missing: ${SOURCE_PYTHON}" >>"$LOG_NAME" 2>&1; return 1; }
  else
    [[ -f "${task_dir}/${SOURCE_PYTHON}" ]] || { echo "Missing: ${task_dir}/${SOURCE_PYTHON}" >>"$LOG_NAME" 2>&1; return 1; }
  fi
  return 0
}

run_python() {
  command pushd "$1" &>/dev/null
  echo "Running $1..." >>"$LOG_NAME" 2>&1
  # Rulăm scriptul din directorul task-ului (in/out sunt acolo).
  local script="${SOURCE_PYTHON}"
  [[ "${SOURCE_PYTHON}" == */* ]] && script="$(basename "${SOURCE_PYTHON}")"
  timeout ${TIMEOUT_PYTHON} python3 "${script}" >>"$LOG_NAME" 2>&1
  result=$?
  echo "========================================" >>"$LOG_NAME" 2>&1
  command popd &>/dev/null
  return $result
}

cleanup_python() {
  command pushd "$1" &>/dev/null
  rm -f in out
  command popd &>/dev/null
}

# Returns:
# 1 = COMPILE ERROR
# 2 = RUNTIME ERROR OR TIMEOUT
# 3 = WRONG ANSWER
compile_and_run() {
  lang="$1"
  task="$2"
  num="$3"

  compile_${lang} "${lang}/${task}"
  if [[ $? -ne 0 ]]; then
    return 1
  fi

  if [ ! -z "${COMPILE_ONLY}" ]; then
    return 0
  fi

  cp "tests/${task}/${num}.in" "${lang}/${task}/in"
  result=0
  run_${lang} "${lang}/${task}"
  if [[ $? -ne 0 ]]; then
    result=2
  fi

  if [[ $result -eq 0 ]]; then
   if [[ ! -f "tests/${task}/check_task" || ! -x "tests/${task}/check_task" ]]; then
    echo "No check_task file found for task $task or check_task is not executable"
    exit 1
   fi

   "tests/${task}/check_task" "tests/${task}/${num}.in" "tests/${task}/${num}.ref" "${lang}/${task}/out" >"$TMP_FILE" 2>&1
   checker_result=$?
   cat "$TMP_FILE" >>"$LOG_NAME"
   head -n 3 "$TMP_FILE"
   if [[ $checker_result -ne 0 ]]; then
     result=3
   fi
  fi

  # If not WA, remove in/out files.
  if [[ $result -ne 3 ]]; then
    rm -f "${lang}/${task}/in" "${lang}/${task}/out"
  fi

  return $result
}

run_single_test() {
  lang="$1"
  task="$2"
  num="$3"

  echo -n "Running ${task}, test ${num}, language ${lang}... "

  compile_and_run "$lang" "$task" "$num"
  result=$?

  RUN_STATUS=("OK" "COMPILE ERROR" "RUNTIME/TIMELIMIT" "WRONG ANSWER")
  if [[ $result -ne 0 ]]; then
    FAILED_TOTAL=$(($FAILED_TOTAL + 1))
    echo "Failed with status ${RUN_STATUS[$result]}!"

    # If WA, print diffs.
    if [[ $result -eq 3 ]]; then
      echo -ne "Expected: "
      cat "tests/${task}/${num}.ref" | head -n 2 | grep -Ev "^$" | cut -c 1-${MAX_SIZE_SHOWN}
      echo -ne "Got: "
      cat "${lang}/${task}/out" | head -n 2 | grep -Ev "^$" | cut -c 1-${MAX_SIZE_SHOWN}

      # Clean up in/out now.
      rm -f "${lang}/${task}/in" "${lang}/${task}/out"
    fi
  else
    echo "Successful!"
  fi

  echo ""
  return $result
}

run_task_tests() {
  echo "========================================================================================="
  lang=$1
  task=$2
  # SOURCE_* / EXE_* sunt setate de apelant din path (lang/algorithm/source.ext).

  task_num=$(task_index $task)
  if [[ $task_num -eq -1 ]]; then
    echo "Invalid task name: $task" >&2
    echo "========================================================================================="
    exit 1
  fi

  if [[ ${NUM_TESTS[$task_num]} -eq 0 ]]; then
    echo "No tests are available for $task"
    if [[ -e "${lang}/${task}" ]]; then
      echo "Testing solution for $task"
      compile_${lang} "${lang}/${task}"
      if [[ $? -ne 0 ]]; then
        echo "COMPILATION ERROR"
        exit 1
      fi
    fi
  else
    failed=0
    num=1
    while [[ $num -le ${NUM_TESTS[$task_num]} ]]; do
      run_single_test "$lang" "$task" "$num"
      if [[ $? -ne 0 ]]; then
        failed=$(($failed + 1))
      fi
      num=$(($num + 1))
    done
  fi

  if [[ $failed -eq 0 ]]; then
    echo "Implementation $task 100% complete."
  fi

  # Șterge executabilul (și in/out) după rularea testelor.
  if [[ "$lang" == cpp || "$lang" == java || "$lang" == rust || "$lang" == python ]]; then
    cleanup_${lang} "${lang}/${task}"
  fi
  echo "========================================================================================="
}

# Clear log.
echo >"$LOG_NAME"

if [[ $# -ne 1 ]]; then
  show_help
fi

# Singura optiune: path lang/algorithm/source.ext
if [[ "$1" == */* && ("$1" == *.cpp || "$1" == *.java || "$1" == *.rs || "$1" == *.py) ]]; then
  path_lang="${1%%/*}"
  path_rest="${1#*/}"
  path_task="${path_rest%%/*}"
  if [[ "$path_lang" == cpp || "$path_lang" == java || "$path_lang" == rust || "$path_lang" == python ]]; then
    check_prerequisites_"$path_lang"
    if [[ "$1" == *.cpp ]]; then
      export SOURCE_CPP="$1"
      export EXE_CPP="$(basename "${1%.cpp}")"
    elif [[ "$1" == *.java ]]; then
      export SOURCE_JAVA="$1"
      export MAIN_CLASS_JAVA="$(basename "${1%.java}")"
    elif [[ "$1" == *.rs ]]; then
      export SOURCE_RUST="$1"
      export EXE_RUST="$(basename "${1%.rs}")"
    elif [[ "$1" == *.py ]]; then
      export SOURCE_PYTHON="$1"
      export EXE_PYTHON="$(basename "${1%.py}")"
    fi
    run_task_tests "$path_lang" "$path_task"
  else
    show_help
  fi
else
  show_help
fi

if [[ $FAILED_TOTAL -gt 0 ]]; then
  echo "Rulati urmatoarea comanda pentru a vedea log-ul de compile/run: "
  echo -e "\tless .err.log"
  echo "Nota: In .err.log se afla si afisarile la stdout si stderr din implementarea voastra."
  exit 1
fi
