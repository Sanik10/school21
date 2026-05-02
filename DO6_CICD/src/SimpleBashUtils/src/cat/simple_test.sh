#!/bin/bash

# cat
flags=("-b" "-e" "-n" "-s" "-t" "-v")

files=("file.txt")

for flag in "${flags[@]}"; do
    echo "Testing flag: $flag"
    
    for file in "${files[@]}"; do
        if [[ -f $file ]]; then
            echo "cat $flag $file:"
            cat $flag "$file"
            echo "------------"
            echo "./s21_cat $flag $file:"
            ./s21_cat $flag "$file"
            echo "=========================="
        else
            echo "File $file not found, skipping..."
        fi
    done
done