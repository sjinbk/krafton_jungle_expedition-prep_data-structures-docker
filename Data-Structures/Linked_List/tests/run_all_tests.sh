#!/usr/bin/env bash

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$SCRIPT_DIR/build"
MODE="run"
SUITE=""

ALL_SUITES=(
  Q1_A_LL_test
  Q2_A_LL_test
  Q3_A_LL_test
  Q4_A_LL_test
  Q5_A_LL_test
  Q6_A_LL_test
  Q7_A_LL_test
)

usage() {
  cat <<'EOF'
Usage:
  ./run_all_tests.sh
  ./run_all_tests.sh --suite Q3_A_LL_test
  ./run_all_tests.sh --mode run
  ./run_all_tests.sh --mode valgrind --suite Q1_A_LL_test

Options:
  --suite NAME   Run one suite from Q1_A_LL_test to Q7_A_LL_test.
  --mode MODE    'run' or 'valgrind'. Default: run.
  -h, --help     Show this help message.
EOF
}

is_valid_suite() {
  local candidate="$1"
  local suite
  for suite in "${ALL_SUITES[@]}"; do
    if [[ "$suite" == "$candidate" ]]; then
      return 0
    fi
  done
  return 1
}

while [[ $# -gt 0 ]]; do
  case "$1" in
    --suite)
      [[ $# -ge 2 ]] || { echo "Missing value for --suite." >&2; usage; exit 1; }
      SUITE="$2"
      shift 2
      ;;
    --mode)
      [[ $# -ge 2 ]] || { echo "Missing value for --mode." >&2; usage; exit 1; }
      MODE="$2"
      shift 2
      ;;
    -h|--help)
      usage
      exit 0
      ;;
    *)
      echo "Unknown argument: $1" >&2
      usage
      exit 1
      ;;
  esac
done

if [[ "$MODE" != "run" && "$MODE" != "valgrind" ]]; then
  echo "Unsupported mode: $MODE" >&2
  usage
  exit 1
fi

if [[ -n "$SUITE" ]] && ! is_valid_suite "$SUITE"; then
  echo "Unknown suite: $SUITE" >&2
  usage
  exit 1
fi

if ! command -v gcc >/dev/null 2>&1; then
  echo "gcc is required to build the C test suites." >&2
  exit 1
fi

if [[ "$MODE" == "valgrind" ]] && ! command -v valgrind >/dev/null 2>&1; then
  echo "valgrind mode was requested, but valgrind is not installed." >&2
  exit 1
fi

mkdir -p "$BUILD_DIR"

if [[ -n "$SUITE" ]]; then
  SUITES_TO_RUN=("$SUITE")
else
  SUITES_TO_RUN=("${ALL_SUITES[@]}")
fi

compile_suite() {
  local suite_name="$1"
  local source_file="$SCRIPT_DIR/${suite_name}.c"
  local output_file="$BUILD_DIR/${suite_name}.out"

  echo
  echo "==> Building ${suite_name}"
  gcc -std=c11 -Wall -Wextra -g "$source_file" -o "$output_file"
}

run_suite() {
  local suite_name="$1"
  local output_file="$BUILD_DIR/${suite_name}.out"

  echo "==> Running ${suite_name}"
  if [[ "$MODE" == "valgrind" ]]; then
    valgrind --leak-check=full --error-exitcode=1 "$output_file"
  else
    "$output_file"
  fi
}

for suite_name in "${SUITES_TO_RUN[@]}"; do
  compile_suite "$suite_name"
  run_suite "$suite_name"
done

echo
echo "All requested suites completed successfully."
