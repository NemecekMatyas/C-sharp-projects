#!/bin/bash

echo "Compiling flows.c ..."
gcc -std=c11 -Wall -Wextra flows.c -o flows -lm || { echo "Compilation failed"; exit 1; }
echo "Compilation OK"


run_test() {
    input="$1"
    expected="$2"
    shift 2

    printf "%s" "$input" >input.tmp
    printf "%s" "$expected" >expected.tmp

    ./flows "$@" <input.tmp >output.tmp 2>&1
    diff -iBw expected.tmp output.tmp >/dev/null

    if [ $? -eq 0 ]; then
        echo "OK - $desc"
    else
        echo "FAIL - $desc"
        echo "INPUT:"
        sed 's/^/    /' input.tmp
        echo "OUTPUT:"
        sed 's/^/    /' output.tmp
        echo "EXPECTED:"
        sed 's/^/    /' expected.tmp
    fi

    rm input.tmp expected.tmp output.tmp
}


echo
echo "Running tests..."

##############################################
# 1) WRONG ARGUMENTS
##############################################

desc="No arguments"
run_test "" "Chybne parametry."    

desc="Only file given"
run_test "" "Chybne parametry." data.txt

desc="Missing weights"
run_test "" "Chybne parametry." data.txt 1.0 1.0 1.0

desc="Too many arguments"
run_test "" "Chybne parametry." data.txt 1.0 1.0 1.0 1.0 1.0 1.0


##############################################
# 2) FILE ERRORS
##############################################

desc="File does not exist"
run_test "" "Soubor se nepodarilo otevrit." xxxxx.txt 1.0 1.0 1.0 1.0


##############################################
# 3) INPUT FORMAT TESTS
##############################################

desc="count=0"
run_test "count=0" "Clusters:" file.txt 1.0 1.0 1.0 1.0

desc="count with extra spaces"
run_test "  count=1  \n10 A B 100 5 10 0.1" "Clusters:
cluster 0: 10 " file.txt 1.0 1.0 1.0 1.0

desc="Non-numeric count"
run_test "count=x\n10 A B 100 5 10 0.1" "Clusters:" file.txt 1.0 1.0 1.0 1.0

desc="Missing flow fields"
run_test "count=1\n10 A B 100 5" "Clusters:
cluster 0: 10 " file.txt 1.0 1.0 1.0 1.0

desc="Extra spaces between fields"
run_test "count=1\n10   A      B     100   5    10    0.1" "Clusters:
cluster 0: 10 " file.txt 1.0 1.0 1.0 1.0


##############################################
# 4) BASIC CLUSTER OUTPUTS
##############################################

desc="1 flow, no N"
run_test "count=1
10 A B 100 5 10 0.1" "Clusters:
cluster 0: 10 " file.txt 1.0 1.0 1.0 1.0

desc="2 flows, no N"
run_test "count=2
10 A B 100 5 10 0.1
11 X Y 200 7 20 0.2" \
"Clusters:
cluster 0: 10
cluster 1: 11 " \
file.txt 1.0 1.0 1.0 1.0


##############################################
# 5) CLUSTERING TESTS (SINGLE-LINKAGE)
##############################################

# simplest case: 2 flows, N=1
desc="2 flows join"
run_test "count=2
10 A B 100 5 10 0.1
11 C D 101 5 10 0.1" \
"Clusters:
cluster 0: 10 11 " \
file.txt 1 1.0 1.0 1.0 1.0

# 4 flows, known grouping
desc="4 flows grouping"
run_test "count=4
10 A B 100 5 10 0.1
11 A B 101 5 11 0.1
12 C D 300 10 30 0.3
13 C D 301 10 31 0.31" \
"Clusters:
cluster 0: 10 11 
cluster 1: 12 13 " \
file.txt 2 1.0 1.0 1.0 1.0


##############################################
# 6) EDGE CASES
##############################################

desc="Zero packet_count (division by zero)"
run_test "count=1
10 A B 100 5 0 0.1" \
"Clusters:
cluster 0: 10 " \
file.txt 1.0 1.0 1.0 1.0

desc="Zero total_bytes"
run_test "count=1
10 A B 0 5 10 0.1" \
"Clusters:
cluster 0: 10 " \
file.txt 1.0 1.0 1.0 1.0

desc="Large numbers"
run_test "count=1
10 A B 9999999 9999 999 9.99" \
"Clusters:
cluster 0: 10 " \
file.txt 1.0 1.0 1.0 1.0

desc="Negative values"
run_test "count=1
10 A B -100 -5 -10 -0.1" \
"Clusters:
cluster 0: 10 " \
file.txt 1.0 1.0 1.0 1.0


##############################################
echo "Done."
##############################################
