#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

// Distância Euclidiana
double dist(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

// Calcula a árvore geradora mínima usando o algoritmo de Prim
vector<vector<int>> construirMST(const vector<pair<double,double>>& cidades) {
    int n = cidades.size();

    vector<bool> inMST(n, false);
    vector<double> chave(n, numeric_limits<double>::infinity());
    vector<int> parent(n, -1);

    chave[0] = 0; // começa pela cidade 0

    for(int i = 0; i < n-1; i++) {
        // Escolhe o vértice com menor chave
        double menor = numeric_limits<double>::infinity();
        int u = -1;

        for(int v = 0; v < n; v++)
            if(!inMST[v] && chave[v] < menor) {
                menor = chave[v];
                u = v;
            }

        inMST[u] = true;

        // Atualiza chaves
        for(int v = 0; v < n; v++) {
            double d = dist(cidades[u].first, cidades[u].second,
                            cidades[v].first, cidades[v].second);

            if(!inMST[v] && d < chave[v]) {
                chave[v] = d;
                parent[v] = u;
            }
        }
    }

    // Cria lista de adjacência da árvore geradora mínima
    vector<vector<int>> adj(n);
    for(int v = 1; v < n; v++) {
        adj[v].push_back(parent[v]);
        adj[parent[v]].push_back(v);
    }

    return adj;
}

// DFS para gerar ordem do caixeiro viajante aproximado
void dfs(int u, vector<bool>& vis, vector<int>& ordem, const vector<vector<int>>& adj) {
    vis[u] = true;
    ordem.push_back(u);

    for(int v : adj[u])
        if(!vis[v])
            dfs(v, vis, ordem, adj);
}

vector<int> tspAproxMST(const vector<pair<double,double>>& cidades) {
    auto adj = construirMST(cidades);

    vector<bool> vis(cidades.size(), false);
    vector<int> ordem;

    dfs(0, vis, ordem, adj);

    // Fecha o ciclo
    ordem.push_back(0);
    return ordem;
}

int main() {
    vector<pair<double,double>> cidades = {
        {0,0}, {1,5}, {5,2}, {6,6}, {2,4}
    };

    vector<int> tour = tspAproxMST(cidades);

    cout << "Rota (Aproximativo via Árvore Geradora Mínima): ";
    for(int c : tour) cout << c << " ";
    cout << "\n";

    return 0;
}

