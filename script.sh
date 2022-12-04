#!/bin/bash

for i in 8 9 10 12 14 16 18 20 22 24 26 28 30 32 34 36
do
    for j in 1 3 5 10 50 100
    do
        ./main -t 50 -f file.txt -T $i -x 400 -y 400 -n $j
        printf "RUN temp: $i colonies: $j\n"
    done
done
