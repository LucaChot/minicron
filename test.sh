#!/bin/bash
SCRIPT=./minicron
passed=0;

for f in test_cases/config?.txt ; do

    section=0
    > tmp0
    > tmp1
    > tmp2

    while IFS= read -r line; do
        if [ -z "$line" ]; then
            section=$(( section + 1 ))
        else
            tmp=tmp$section
            echo "$line" >> "$tmp"
        fi
    done < "$f"

    result=$(cat tmp0 | $SCRIPT $(cat tmp1) | diff - tmp2)

    if [ ! -z "$result" ]; then
        passed=1
        echo "Test $f failed"
        echo $result
    else
        echo "Passed $f"
    fi
done

rm tmp*

if test $passed; then
    echo "Passed all tests"
fi
