for filename in ./tests/*.yvr; do
    echo "Running " $(basename "$filename") "..."
    ./youverify "$filename" | python3 tests.py $(basename "$filename" .yvr)
    
done
