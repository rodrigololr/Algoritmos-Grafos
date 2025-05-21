#!/bin/bash

floydWarshall=./floyd-warshall.bin

echo -e "\n\n";

echo "Testando algoritmo de Floyd-Warshall\n"
for i in inputs/*.txt
do

    echo -e "\e[33mInstância $i\e[0m"
    $floydWarshall -s -f $i > temp


    j=./gabarito_inputs/gabarito_$(basename $i)

    # Compara o arquivo temporário com o gabarito
    if diff -w temp "$j" > /dev/null; then
        # Mostra OK em verde
        echo -e "\e[32mOK\e[0m"
    else
        # Mostra ERRO em vermelho
        echo -e "\e[31mErro\e[0m"
    fi

    # Remove o arquivo temporário
    rm temp

done
