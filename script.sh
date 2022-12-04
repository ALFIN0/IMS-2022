#!/bin/bash

for i in 8 9 10 12 14 16 18 20 22 24 26 28 30 32 34
do
    for j in 1 3 5 10
    do
        for k in 1 2 3
        do
            test -d stats || mkdir stats
            test -f stats/stats.csv || echo "weeks;colonieslow;coloniesmed;colonieshigh;treeshea;treesatt;treedec;fields;temp;begincolonies" >> stats/stats.csv
            ./main -t 50 -f stats/file.txt -S stats/stats.csv -T $i -x 400 -y 400 -n $j
            printf "RUN temp: $i colonies: $j\n"
        done
    done
done
