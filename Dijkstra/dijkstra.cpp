#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <fstream>
#include <string>
#include <climits>

using namespace std;
typedef pair<int, int> distancia_vertice;

vector<int> dijkstra(int num_v, list<distancia_vertice> *arestas, int v_init) {
    vector<int> distances(num_v + 1, INT_MAX);
    distances[v_init] = 0;
    priority_queue<distancia_vertice, vector<distancia_vertice>, greater<distancia_vertice>> queue;
    queue.push(make_pair(0, v_init));

    while(!queue.empty()){
        int dist_atual = queue.top().first;
        int vertice_atual = queue.top().second;
        queue.pop();

        if(dist_atual > distances[vertice_atual]){
            continue;
        }

        for(auto vizinho : arestas[vertice_atual]){
            int proximo_vertice = vizinho.first;
            int peso_aresta = vizinho.second;
            if(distances[vertice_atual] + peso_aresta < distances[proximo_vertice]){
                distances[proximo_vertice] = distances[vertice_atual] + peso_aresta;
                queue.push(make_pair(distances[proximo_vertice], proximo_vertice));
            }
        }
    }

    return distances;
}

int main(int argc, char *argv[]) {
    string inputFile, outputFile;
    int init = 1;

    for(int i = 1;i < argc; ++i){
        string arg = argv[i];
        if(arg == "-h"){
            cout << "Guia de uso:\n"
                 << "-h: exibe esta ajuda\n"
                 << "-o <arquivo>: define arquivo de saída\n"
                 << "-f <arquivo>: define arquivo de entrada\n"
                 << "-i <vertice>: define vértice inicial\n";
            return 0;
        }
        else if(arg == "-o" && i < argc - 1){
            outputFile = argv[++i];
        }
        else if(arg == "-f" && i < argc - 1){
            inputFile = argv[++i];
        }
        else if(arg == "-i" && i < argc - 1){
            init = atoi(argv[++i]);
        }
    }

    if(inputFile.empty()){
        cerr << "Sem input especificado. Use o parametro -f\n";
        return 1;
    }

    ifstream fin(inputFile);
    if(!fin){
        cerr << "Não foi possível abrir o arquivo de entrada: " << inputFile << endl;
        return 1;
    }

    int n, m;
    fin >> n >> m;
    list<pair<int, int>> arestas[n + 1];

    for(int i = 0;i < m; ++i){
        int v1, v2, peso;
        fin >> v1 >> v2 >> peso;
        arestas[v1].push_back(make_pair(v2, peso));
        arestas[v2].push_back(make_pair(v1, peso));
    }
    fin.close();

    vector<int> distances = dijkstra(n, arestas, init);

    if(!outputFile.empty()){
        ofstream fout(outputFile);
        if(!fout){
            cerr << "Não foi possível abrir o arquivo de saída: " << outputFile << endl;
            return 1;
        }
        for(int i = 1;i <= n; ++i){
            if(distances[i] != INT_MAX){
                fout << i << ":" << distances[i] << " ";
            }
            else{
                fout << i << ":" << -1 << " ";
            }
        }
        fout << endl;
        fout.close();
    }

    for(int i = 1;i <= n; ++i){
        if(distances[i] != INT_MAX){
            cout << i << ":" << distances[i] << " ";
        }
        else{
            cout << i << ":" << -1 << " ";
        }
    }
    cout << endl;

    return 0;
}