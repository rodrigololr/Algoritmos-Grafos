#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include <string>

using namespace std;

vector<vector<int>> graph, graph_reverse;
vector<bool> seen;
stack<int> finishStack;
vector<int> scc;

void dfs1(int v) {
    seen[v] = true;
    for(int u : graph[v]){
        if(!seen[u]){
            dfs1(u);
        }
    }
    finishStack.push(v);
}

void dfs2(int v) {
    seen[v] = true;
    scc.push_back(v);
    for(int u : graph_reverse[v]){
        if(!seen[u]){
            dfs2(u);
        }
    }
}

int main(int argc, char* argv[]) {
    string inputFile, outputFile;

    for(int i = 1;i < argc; ++i){
        string arg = argv[i];
        if(arg == "-h"){
            cout << "Guia de uso:\n"
                 << "-h: exibe esta ajuda\n"
                 << "-o <arquivo>: define arquivo de saída\n"
                 << "-f <arquivo>: define arquivo de entrada\n";
            return 0;
        }
        else if(arg == "-o" && i < argc - 1){
            outputFile = argv[++i];
        }
        else if(arg == "-f" && i < argc - 1){
            inputFile = argv[++i];
        }
    }

    if(inputFile.empty()){
        cout << "Arquivo de entrada não especificado.\n";
        return 1;
    }

    ifstream fin(inputFile);
    if(!fin){
        cout << "Erro ao abrir o arquivo de entrada.\n";
        return 1;
    }

    int n, m;
    fin >> n >> m;
    graph.resize(n);
    graph_reverse.resize(n);
    seen.resize(n, false);

    for(int i = 0;i < m; ++i){
        int u, v;
        fin >> u >> v;
        u--;
        v--;
        graph[u].push_back(v);
        graph_reverse[v].push_back(u);
    }
    fin.close();

    for(int i = 0;i < n; ++i){
        if(!seen[i]){
            dfs1(i);
        }
    }

    fill(seen.begin(), seen.end(), false);

    ofstream fout;
    if(!outputFile.empty()){
        fout.open(outputFile);
        if(!fout){
            cout << "Erro ao abrir o arquivo de saída.\n";
            return 1;
        }
    }
    ostream &output = outputFile.empty() ? cout : fout;

    while(!finishStack.empty()){
        int v = finishStack.top();
        finishStack.pop();
        if(!seen[v]){
            scc.clear();
            dfs2(v);
            for(int u : scc){
                output << (u + 1) << " ";
            }
            output << endl;
        }
    }

    if(fout.is_open()){
        fout.close();
    }

    return 0;
}