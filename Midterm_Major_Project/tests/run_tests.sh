#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT"

rm -rf build bin
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build

run_and_capture() {
  local name="$1"
  local cmd="$2"
  local input="$3"
  local out="results/${name}.out"
  mkdir -p results
  eval "$cmd" < "$input" > "$out"
  printf '%s\n' "$out"
}

assert_contains() {
  local file="$1"
  local expected="$2"
  if ! grep -Fq "$expected" "$file"; then
    echo "Expected to find: $expected" >&2
    echo "In file: $file" >&2
    echo "Actual output:" >&2
    cat "$file" >&2
    exit 1
  fi
}

selection_out=$(run_and_capture selection_sample "./bin/selection" "tests/selection_sample.txt")
assert_contains "$selection_out" "HeapSelect: 3"
assert_contains "$selection_out" "RandomizedSelect: 3"
assert_contains "$selection_out" "MedianOfMediansSelect: 3"
assert_contains "$selection_out" "All algorithms agree: yes"

selection_k1_out=$(run_and_capture selection_k1 "./bin/selection" "tests/selection_k1.txt")
assert_contains "$selection_k1_out" "HeapSelect: 2"
assert_contains "$selection_k1_out" "All algorithms agree: yes"

selection_kn_out=$(run_and_capture selection_kn "./bin/selection" "tests/selection_kn.txt")
assert_contains "$selection_kn_out" "HeapSelect: 9"
assert_contains "$selection_kn_out" "All algorithms agree: yes"

partition_out=$(run_and_capture partition_sample "./bin/partition" "tests/partition_sample.txt")
assert_contains "$partition_out" "BruteForce best difference: 1"
assert_contains "$partition_out" "DynamicProgramming best difference: 1"
assert_contains "$partition_out" "DynamicProgramming pile A sum: 10"
assert_contains "$partition_out" "DynamicProgramming pile B sum: 11"

partition_single_out=$(run_and_capture partition_single "./bin/partition" "tests/partition_single.txt")
assert_contains "$partition_single_out" "DynamicProgramming best difference: 7"
assert_contains "$partition_single_out" "DynamicProgramming pile B sum: 7"

partition_equal_out=$(run_and_capture partition_equal "./bin/partition" "tests/partition_equal.txt")
assert_contains "$partition_equal_out" "DynamicProgramming best difference: 0"

mst_out=$(run_and_capture mst_sample "./bin/mst" "tests/mst_sample.txt")
assert_contains "$mst_out" "Total cost: 15"
assert_contains "$mst_out" "Selected edges: 5"
assert_contains "$mst_out" "1 3 1"
assert_contains "$mst_out" "4 6 2"

if ./bin/mst < tests/mst_disconnected.txt > results/mst_disconnected.out 2>&1; then
  echo "Expected disconnected MST input to fail" >&2
  cat results/mst_disconnected.out >&2
  exit 1
fi
assert_contains results/mst_disconnected.out "Graph is disconnected"

echo "All tests passed."
