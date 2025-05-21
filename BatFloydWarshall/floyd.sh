#!/bin/bash

floydWarshall=./floyd-warshall.bin

echo "Testando algoritmo de Floyd-Warshall"
for i in inputs/*.txt
do
    echo -e "\e[33mInstância $i\e[0m"
    $floydWarshall -s -f $i > temp
    
    j=./gabarito_inputs/gabarito_$(basename $i)
    if diff -w temp "$j" > /dev/null; then
        echo -e "\e[32mOK\e[0m"
    else
        echo -e "\e[31mErro\e[0m"
    fi
    rm temp
done
