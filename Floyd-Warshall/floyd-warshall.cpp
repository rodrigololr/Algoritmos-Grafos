#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <climits>

using namespace std;

void floyd_warshall(int vertices, vector<vector<int>> &distances) {
    for(int k = 0;k < vertices; ++k){
        for(int i = 0;i < vertices; ++i){
            for(int j = 0;j < vertices; ++j){
                if(distances[i][j] > distances[i][k] + distances[k][j] && distances[k][j] != INT_MAX && distances[i][k] != INT_MAX){
                    distances[i][j] = distances[i][k] + distances[k][j];
                }
            }
        }
    }
}

void help() {
    cout << "-h: exibe esta ajuda\n"
         << "-o <arquivo>: define arquivo de saída\n"
         << "-f <arquivo>: define arquivo de entrada\n"
         << "-s: exibe a matriz de caminhos mínimos\n";
}

int main(int argc, char *argv[]) {
    string inputFile, outputFile;
    bool solucao = false;
    ofstream fout;

    for(int i = 1;i < argc; ++i){
        string arg = argv[i];
        if(arg == "-h"){
            help();
            return 0;
        }
        else if(arg == "-o" && i < argc - 1){
            outputFile = argv[++i];
            fout.open(outputFile);
            if(!fout){
                cerr << "Erro ao abrir o arquivo de saída: " << outputFile << endl;
                return 1;
            }
            cout.rdbuf(fout.rdbuf());
        }
        else if(arg == "-f" && i < argc - 1){
            inputFile = argv[++i];
        }
        else if(arg == "-s"){
            solucao = true;
        }
    }

    if(inputFile.empty()){
        cerr << "Erro ao abrir o arquivo de entrada: " << inputFile << endl;
        return 1;
    }

    ifstream fin(inputFile);
    if(!fin){
        cerr << "Erro ao abrir o arquivo de entrada: " << inputFile << endl;
        return 1;
    }

    int vertices, arestas;
    fin >> vertices >> arestas;
    vector<vector<int>> distances(vertices, vector<int>(vertices, INT_MAX));

    for(int i = 0;i < vertices; ++i){
        distances[i][i] = 0;
    }

    for(int i = 0;i < arestas; ++i){
        int u, v, peso;
        fin >> u >> v >> peso;
        u--;
        v--;
        distances[u][v] = peso;
    }
    fin.close();

    floyd_warshall(vertices, distances);

    if(solucao){
        for(int i = 0;i < vertices; ++i){
            for(int j = 0;j < vertices; ++j){
                if(distances[i][j] == INT_MAX){
                    cout << "- ";
                }
                else{
                    cout << distances[i][j] << " ";
                }
            }
            cout << endl;
        }
    }

    if(fout.is_open()){
        fout.close();
    }
    return 0;
}