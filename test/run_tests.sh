#!/usr/bin/env bash
for filename in ./tests/*.yvr; do
    echo "Running " $(basename "$filename") "..."
    ../build/youverify "$filename" | python3 tests.py $(basename "$filename" .yvr)
done
