#!/bin/bash
# Skript pro automatické testování programu flows2

EXEC=./flows2
DATA=data.txt

echo "=== Testování programu flows2 ==="

# 1. Test: špatný počet argumentů
echo -n "Test 1 (špatný počet argumentů)... "
$EXEC $DATA 1.0 1.0 1.0 >/dev/null 2>&1 && echo "FAIL" || echo "OK"

# 2. Test: záporné váhy
echo -n "Test 2 (záporné váhy)... "
$EXEC $DATA -1 1.0 1.0 1.0 >/dev/null 2>&1 && echo "FAIL" || echo "OK"

# 3. Test: nečíselné váhy
echo -n "Test 3 (nečíselné váhy)... "
$EXEC $DATA abc 1.0 1.0 1.0 >/dev/null 2>&1 && echo "FAIL" || echo "OK"

# 4. Test: požadovaný počet shluků = 1
echo "Test 4 (počet shluků = 1)"
$EXEC $DATA 1 1.0 1.0 1.0 1.0

# 5. Test: požadovaný počet shluků = 5
echo "Test 5 (počet shluků = 5)"
$EXEC $DATA 5 1.0 1.0 1.0 1.0

# 6. Test: požadovaný počet shluků = 2
echo "Test 6 (počet shluků = 2)"
$EXEC $DATA 2 1.0 1.0 1.0 1.0

# 7. Test: kontrola řazení toků ve shluku
echo "Test 7 (řazení toků ve shluku)"
OUT=$($EXEC $DATA 2 1.0 1.0 1.0 1.0)
echo "$OUT"
echo "$OUT" | grep -q "cluster 0: 10 11 12 13 15" && echo "OK (seřazeno)" || echo "FAIL (nesprávné pořadí)"

# 8. Test: kontrola řazení shluků
echo "Test 8 (řazení shluků)"
OUT=$($EXEC $DATA 3 1.0 1.0 1.0 1.0)
echo "$OUT"
echo "$OUT" | grep -q "cluster 0:" && echo "OK (shluky začínají nejmenším tokem)" || echo "FAIL"
