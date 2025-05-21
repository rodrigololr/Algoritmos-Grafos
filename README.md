# Algoritmos de Grafos

Bem-vindo ao repositório **Algoritmos de Grafos**, implementado como projeto da disciplina **Teoria dos Grafos** da **Universidade Federal de Alagoas (UFAL)**. Este projeto contém cinco algoritmos de grafos em C++.

## Equipe

- Antônio Rodrigo Lima de Andrade Tenório (arlat@ic.ufal.br) - 23210707
- Luiz Miguel de Melo Bomfim (lmmb@ic.ufal.br) - 23211918

## Estrutura do Projeto

Cada algoritmo está em sua própria pasta com um `Makefile` para compilação:
- `Kruskal`: Árvore Geradora Mínima (AGM).
- `Prim`: Árvore Geradora Mínima (AGM) com vértice inicial.
- `Dijkstra`: Caminhos mínimos a partir de um vértice.
- `Kosaraju`: Componentes fortemente conexos.
- `Floyd-Warshall`: Caminhos mínimos entre todos os pares.

## Compilação

1. Acesse a pasta do algoritmo desejado:
```bash
cd Dijkstra    (Ou Prim, Kruskal, etc...)
```

2. Compile o `Makefile` com:
```bash
make
```

> Problemas com Recompilação

Se caso já existir um arquivo `.bin` no diretório e ele **não está sendo recompilado corretamente**, utilize uma das opções abaixo para forçar a recompilação:

```bash
make -B
```
ou
```bash
make clean
make
```

3. Um executável .bin será gerado, por exemplo: dijkstra.bin.


## Execução de Testes com Bat1

A pasta `Bat1` contém arquivos de entrada e um script para testar todos os algoritmos. Basta copiar os executáveis `.bin` (gerados após a compilação) para dentro da pasta `Bat1`.


na `Bat1` vamos ter as entradas:
```bash
- `inputs` : testes Floyd-Warshall
- `instances`: testes Kosaraju
- `instances_scc`: testes Dijkstra, Kruskal e Prim
```
e os gabaritos das entradas:
```bash
- `gabarito_inputs` : gabarito Floyd-Warshall
- `scc`: gabarito Kosaraju
- `sp`: gabarito Dijkstra
- `gabarito_agm.txt`: gabarito Kruskal e Prim
-
```

Após compilar todos os `.bin` e colocalos na pasta `Bat1` rode no terminal (WSL):
```bash
bash Bat1.sh
```

O script irá executar os testes automaticamente e você poderá verificar se os algoritmos retornaram as saídas corretas
