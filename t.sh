#!/bin/bash
set -e

rm -f 1 2

./dummy c book1 1
./dummy d 1 2

echo "--- md5sums ---"
md5sum 1 book1.ppm 2 book1

echo "--- comparing 1 and book1.ppm ---"
if cmp -s 1 book1.ppm; then
  echo "PASS: 1 == book1.ppm"
else
  echo "FAIL: 1 != book1.ppm"
  exit 1
fi

echo "--- comparing 2 and book1 ---"
if cmp -s 2 book1; then
  echo "PASS: 2 == book1"
else
  echo "FAIL: 2 != book1"
  exit 1
fi
