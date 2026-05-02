#!/usr/bin/env bash
set -euo pipefail

export LC_ALL=C
export LANG=C

ROOT_DIR="$(cd "$(dirname "$0")/../.." && pwd)"
BIN_DIR="$ROOT_DIR/artifacts/bin"

S21_CAT="$BIN_DIR/s21_cat"
S21_GREP="$BIN_DIR/s21_grep"

CAT_REF="$(command -v cat)"
GREP_REF="$(command -v grep)"

fail() {
  echo "INTEGRATION TESTS: FAILED"
  echo "$1"
  exit 1
}

require() {
  [[ -e "$1" ]] || fail "Not found: $1"
}

run_case() {
  local title="$1"
  local ref_cmd="$2"
  local s21_cmd="$3"

  echo "=== $title ==="

  local ref_out ref_err s21_out s21_err
  ref_out="$(mktemp)"; ref_err="$(mktemp)"
  s21_out="$(mktemp)"; s21_err="$(mktemp)"

  set +e
  bash -c "$ref_cmd" >"$ref_out" 2>"$ref_err"
  ref_code=$?
  bash -c "$s21_cmd" >"$s21_out" 2>"$s21_err"
  s21_code=$?
  set -e

  if [[ $ref_code -ne $s21_code ]]; then
    echo "Return code mismatch: ref=$ref_code s21=$s21_code"
    echo "--- ref stderr ---"; cat "$ref_err"
    echo "--- s21 stderr ---"; cat "$s21_err"
    fail "$title"
  fi

  diff -u "$ref_out" "$s21_out" || fail "$title (stdout differs)"
  diff -u "$ref_err" "$s21_err" || fail "$title (stderr differs)"

  rm -f "$ref_out" "$ref_err" "$s21_out" "$s21_err"
  echo "OK"
}

# входные данные из репо
CAT_FILE="$ROOT_DIR/src/SimpleBashUtils/src/cat/file.txt"
GREP_FILE1="$ROOT_DIR/src/SimpleBashUtils/src/grep/file1.txt"

require "$S21_CAT"
require "$S21_GREP"
require "$CAT_FILE"
require "$GREP_FILE1"

for f in "-b" "-e" "-n" "-s" "-t" "-v"; do
  run_case "cat $f" \
    "$CAT_REF $f '$CAT_FILE'" \
    "$S21_CAT $f '$CAT_FILE'"
done
run_case "cat -s -n" \
  "$CAT_REF -s -n '$CAT_FILE'" \
  "$S21_CAT -s -n '$CAT_FILE'"

run_case "grep basic" \
  "$GREP_REF 'Lorem' '$GREP_FILE1'" \
  "$S21_GREP 'Lorem' '$GREP_FILE1'"

for f in "-i" "-v" "-c" "-n" "-o"; do
  run_case "grep $f" \
    "$GREP_REF $f 'Lorem' '$GREP_FILE1'" \
    "$S21_GREP $f 'Lorem' '$GREP_FILE1'"
done

run_case "grep -e multi" \
  "$GREP_REF -e 'Lorem' -e 'ipsum' '$GREP_FILE1'" \
  "$S21_GREP -e 'Lorem' -e 'ipsum' '$GREP_FILE1'"

echo "INTEGRATION TESTS: PASSED"
