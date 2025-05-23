#!/bin/bash

floydWarshall=./floyd-warshall.bin

echo "Testando algoritmo de Floyd-Warshall"
for i in inputs/*.txt
do
    echo -e "\e[33mInstância $i\e[0m"
    $floydWarshall -s -f "$i" > temp
    
    
    numero=$(basename "$i" .txt | grep -o '[0-9]\+')
    j="./gabarito_inputs/gabarito_Grafo_${numero}.txt"
    
    if diff -w temp "$j" > /dev/null; then
        echo -e "\e[32mOK\e[0m"
    else
        echo -e "\e[31mErro\e[0m"
    fi
    rm temp
done