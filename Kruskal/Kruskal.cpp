#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;

class ConjuntoDisjunto {
    vector<int> parent, rank, size;
public:
    ConjuntoDisjunto(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        size.resize(n + 1, 1);
        for(int i = 0;i <= n; ++i){
            parent[i] = i;
        }
    }

    int find(int u) {
        if(u == parent[u]){
            return u;
        }
        return parent[u] = find(parent[u]);
    }

    void mergeByRank(int u, int v) {
        int pu = find(u), pv = find(v);
        if(pu == pv){
            return;
        }
        if(rank[pu] < rank[pv]){
            parent[pu] = pv;
        }
        else if(rank[pu] > rank[pv]){
            parent[pv] = pu;
        }
        else{
            parent[pv] = pu;
            rank[pu]++;
        }
    }

    void mergeBySize(int u, int v) {
        int pu = find(u), pv = find(v);
        if(pu == pv){
            return;
        }
        if(size[pu] < size[pv]){
            parent[pu] = pv;
            size[pv] += size[pu];
        }
        else{
            parent[pv] = pu;
            size[pu] += size[pv];
        }
    }
};

class Graph {
public:
    pair<int, vector<pair<int, int>>> kruskal(int vertices, vector<vector<pair<int, int>>> &adj) {
        vector<pair<int, pair<int, int>>> edges;
        for(int u = 0;u < vertices; ++u){
            for(auto &e : adj[u]){
                int v = e.first, weight = e.second;
                edges.emplace_back(weight, make_pair(u, v));
            }
        }

        sort(edges.begin(), edges.end());
        ConjuntoDisjunto ds(vertices);

        int totalWeight = 0;
        vector<pair<int, int>> mstEdges;

        for(auto &edge : edges){
            int u = edge.second.first;
            int v = edge.second.second;
            if(ds.find(u) != ds.find(v)){
                totalWeight += edge.first;
                mstEdges.emplace_back(u, v);
                ds.mergeByRank(u, v);
            }
        }

        return {totalWeight, mstEdges};
    }
};

int main(int argc, char *argv[]) {
    string inputFile, outputFile, outputType = "resultado";

    for(int i = 1;i < argc; ++i){
        string arg = argv[i];
        if(arg == "-h"){
            cout << "Guia de uso:\n"
                 << "-h: exibe o help\n"
                 << "-o <arquivo>: redireciona a saida para o ‘‘arquivo’’\n"
                 << "-f <arquivo>: indica o ‘‘arquivo’’ que contém o grafo de entrada\n"
                 << "-s: mostra a solução\n";
            return 0;
        }
        else if(arg == "-o" && i + 1 < argc){
            outputFile = argv[++i];
            outputType = "nenhum";
        }
        else if(arg == "-f" && i + 1 < argc){
            inputFile = argv[++i];
        }
        else if(arg == "-s"){
            outputType = "vertices";
        }
    }

    if(inputFile.empty()){
        cout << "Erro: especifique um arquivo de entrada com -f\n";
        return 1;
    }

    ifstream in(inputFile);
    if(!in){
        cerr << "Erro ao abrir o arquivo de entrada: " << inputFile << endl;
        return 1;
    }

    int vertices, edges;
    in >> vertices >> edges;
    vector<vector<pair<int, int>>> adjList(vertices + 1);

    for(int i = 0;i < edges; ++i){
        int u, v, w;
        in >> u >> v >> w;
        adjList[u].emplace_back(v, w);
        adjList[v].emplace_back(u, w);
    }
    in.close();

    Graph solver;
    auto result = solver.kruskal(vertices, adjList);

    if(!outputFile.empty()){
        ofstream out(outputFile);
        if(!out){
            cerr << "Erro ao abrir o arquivo de saída: " << outputFile << endl;
            return 1;
        }
        for(auto &e : result.second){
            out << "(" << e.first << ", " << e.second << ") ";
        }
        out << endl;
        out.close();
    }

    if(outputType == "resultado"){
        cout << result.first << endl;
    }
    else if(outputType == "vertices"){
        for(auto &e : result.second){
            cout << "(" << e.first << ", " << e.second << ") ";
        }
        cout << endl;
    }

    return 0;
}