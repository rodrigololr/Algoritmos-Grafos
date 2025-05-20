#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;

class Solucao {
public:
    pair<int, vector<pair<int, int>>> algoritmoPrim(int numVertices, vector<vector<pair<int, int>>> &grafo, int verticeInicial) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> filaPrioridade;
        vector<int> visitado(numVertices, 0);
        vector<int> parent(numVertices, -1);
        filaPrioridade.push(make_pair(0, verticeInicial));

        int totalWeight = 0;
        vector<pair<int, int>> arestasMST;

        while(!filaPrioridade.empty()){
            auto topo = filaPrioridade.top();
            filaPrioridade.pop();
            int verticeAtual = topo.second;
            int pesoAtual = topo.first;

            if(visitado[verticeAtual] == 1){
                continue;
            }
            visitado[verticeAtual] = 1;
            totalWeight += pesoAtual;

            if(verticeAtual != verticeInicial){
                arestasMST.push_back(make_pair(parent[verticeAtual], verticeAtual));
            }

            for(auto vizinho : grafo[verticeAtual]){
                int verticeVizinho = vizinho.first;
                int pesoAresta = vizinho.second;
                if(!visitado[verticeVizinho]){
                    parent[verticeVizinho] = verticeAtual;
                    filaPrioridade.push(make_pair(pesoAresta, verticeVizinho));
                }
            }
        }

        return make_pair(totalWeight, arestasMST);
    }
};

int main(int argc, char *argv[]) {
    string inputFile, outputFile, opcaoSaida = "peso";
    int verticeInicial = 1;

    for(int i = 1;i < argc; ++i){
        string arg = argv[i];
        if(arg == "-h"){
            cout << "Guia de uso:\n"
                 << "-h: exibe o help\n"
                 << "-o <arquivo>: redireciona a saida para o ‘‘arquivo’’\n"
                 << "-f <arquivo>: indica o ‘‘arquivo’’ que contém o grafo de entrada\n"
                 << "-s: mostra a solução\n"
                 << "-i <vertice>: define vértice inicial (1-indexado)\n";
            return 0;
        }
        else if(arg == "-o" && i + 1 < argc){
            outputFile = argv[++i];
            opcaoSaida = "nenhuma";
        }
        else if(arg == "-f" && i + 1 < argc){
            inputFile = argv[++i];
        }
        else if(arg == "-s"){
            opcaoSaida = "arestas";
        }
        else if(arg == "-i" && i + 1 < argc){
            verticeInicial = atoi(argv[++i]) - 1;
        }
    }

    if(inputFile.empty()){
        cout << "Erro: especifique um arquivo de entrada com -f\n";
        return 1;
    }

    ifstream entrada(inputFile);
    if(!entrada){
        cerr << "Não foi possível abrir o arquivo de entrada: " << inputFile << endl;
        return 1;
    }

    int numVertices, numArestas;
    entrada >> numVertices >> numArestas;
    vector<vector<pair<int, int>>> grafo(numVertices);

    for(int i = 0;i < numArestas; ++i){
        int vertice1, vertice2, peso;
        entrada >> vertice1 >> vertice2 >> peso;
        grafo[vertice1 - 1].push_back(make_pair(vertice2 - 1, peso));
        grafo[vertice2 - 1].push_back(make_pair(vertice1 - 1, peso));
    }
    entrada.close();

    Solucao solver;
    auto resultado = solver.algoritmoPrim(numVertices, grafo, verticeInicial);

    if(!outputFile.empty()){
        ofstream saida(outputFile);
        if(!saida){
            cerr << "Não foi possível abrir o arquivo de saída: " << outputFile << endl;
            return 1;
        }
        for(auto &aresta : resultado.second){
            saida << "(" << aresta.first + 1 << ", " << aresta.second + 1 << ") ";
        }
        saida << endl;
        saida.close();
    }

    if(opcaoSaida == "peso"){
        cout << resultado.first << endl;
    }
    else if(opcaoSaida == "arestas"){
        for(auto &aresta : resultado.second){
            cout << "(" << aresta.first + 1 << ", " << aresta.second + 1 << ") ";
        }
        cout << endl;
    }

    return 0;
}