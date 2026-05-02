#!/bin/bash

# grep
FILES=("file1.txt")
PATTERNS=("Lorem" "текст" "Строка")

FLAGS=("" "-e" "-i" "-v" "-c" "-l" "-n" "-h" "-s" "-o")

for flag in "${FLAGS[@]}"; do
  for pattern in "${PATTERNS[@]}"; do
    for file in "${FILES[@]}"; do
      echo "Тест: grep $flag $pattern $file"
      grep $flag "$pattern" "$file"
      echo "Тест: ./s21_grep $flag $pattern $file"
      ./s21_grep $flag "$pattern" "$file"
      echo "-----------------------------"
    done
  done
done