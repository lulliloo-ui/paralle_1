#!/bin/bash
echo "threads time_ms" > results.txt
for threads in 1 2 4 8 16 32 64 128 256 512 1024
do
  for run in 1 2 3 4 5
  do
    result=$(./a.out $threads)
    echo "$threads $result" >> results.txt
  done
done
