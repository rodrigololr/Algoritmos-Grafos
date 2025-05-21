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


## Execução de Testes do FloydWarshall

A pasta `BatFloydWarshall` contém os inputs, gabarito dos inputs e a source. Basta copiar o executável `.bin` (gerado após a compilação) para dentro da pasta `BatFloydWarshall`.

Após compilar o `.bin` e caloca-lo na pasta `BatFloydWarshall` rode no terminal (WSL):
```bash
bash floyd.sh
```

Se caso apareça `floyd.sh: line 2: $'\r': command not found` quando for rodar o floyd.sh
isso acontece devido as quebras de linha Windows, rode no terminal:

```bash
sudo apt install dos2unix
dos2unix floyd.sh
> dos2unix: converting file floyd.sh to Unix format...
bash floyd.sh
```

O script irá executar os testes automaticamente e você poderá verificar se os algoritmos retornaram as saídas corretas
