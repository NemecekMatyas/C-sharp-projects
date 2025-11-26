#!/bin/bash

echo "Compiling flows.c ..."
gcc -std=c11 -Wall -Wextra flows.c -o flows -lm || { echo "Compilation failed"; exit 1; }
echo "Compilation OK"

# helper function
run_test() {
    input="$1"
    expected="$2"
    shift 2

    printf "%s" "$input" >input.tmp
    printf "%s" "$expected" >expected.tmp

    ./flows "$@" <input.tmp >output.tmp 2>&1
    diff -iBw expected.tmp output.tmp >/dev/null

    if [ $? -eq 0 ]; then
        echo "OK"
    else
        echo "FAIL"
        echo "INPUT:"
        cat input.tmp
        echo "OUTPUT:"
        cat output.tmp
        echo "EXPECTED:"
        cat expected.tmp
    fi

    rm input.tmp expected.tmp output.tmp
}

echo
echo "Running tests..."

# 1) missing arguments
run_test "" "Chybne parametry." data.txt

# 2) missing file
run_test "" "Soubor se nepodarilo otevrit." xxxxx.txt 1.0 1.0 1.0 1.0

# 3) count=0
run_test "count=0" "Clusters:" file.txt 1.0 1.0 1.0 1.0

# 4) one flow
run_test "count=1
10 A B 100 5 10 0.1" "Clusters:
cluster 0: 10 " file.txt 1.0 1.0 1.0 1.0

echo "Done."
