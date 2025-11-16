#include <bits/stdc++.h>
using namespace std;

// Construção da Árvore Geradora Mínima usando Prim
vector<vector<pair<int,int>>> primMST(const vector<vector<int>>& G) {
    int n = G.size();
    vector<int> key(n, INT_MAX);
    vector<bool> inMST(n, false);
    vector<int> parent(n, -1);

    key[0] = 0; // começa pelo vértice 0

    for (int i = 0; i < n - 1; i++) {
        int u = -1;

        // encontra o vértice não incluído na Árvore Geradora Mínima com menor chave
        for (int v = 0; v < n; v++)
            if (!inMST[v] && (u == -1 || key[v] < key[u]))
                u = v;

        inMST[u] = true;

        // atualiza vizinhos
        for (int v = 0; v < n; v++) {
            if (G[u][v] && !inMST[v] && G[u][v] < key[v]) {
                key[v] = G[u][v];
                parent[v] = u;
            }
        }
    }

    // monta lista de adjacência da Árvore Geradora Mínima
    vector<vector<pair<int,int>>> T(n);
    for (int v = 1; v < n; v++) {
        int u = parent[v];
        T[u].push_back({v, G[u][v]});
        T[v].push_back({u, G[u][v]});
    }

    return T;
}

// DFS para registrar ordem de visita na árvore
void dfs(int u, vector<bool>& visited,
         vector<int>& ordem,
         const vector<vector<pair<int,int>>>& T)
{
    visited[u] = true;
    ordem.push_back(u);

    for (auto& [v, w] : T[u])
        if (!visited[v])
            dfs(v, visited, ordem, T);
}

// Algoritmo Aproximativo do Caixeiro Viajante via Árvore Geradora Mínima
vector<int> tspAproximadoAGM(const vector<vector<int>>& G) {
    int n = G.size();

    // 1. Construir Árvore Geradora Mínima
    auto T = primMST(G);

    // 2. DFS na Árvore Geradora Mínima
    vector<bool> visited(n, false);
    vector<int> ordem;
    dfs(0, visited, ordem, T);

    // 3. Construir o ciclo aproximado
    vector<int> ciclo = ordem;
    ciclo.push_back(ordem[0]); // volta ao início

    return ciclo;
}

int main() {
    // Exemplo de uso com grafo completo (matriz de adjacência)
    vector<vector<int>> G = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    vector<int> ciclo = tspAproximadoAGM(G);

    cout << "Ciclo aproximado: ";
    for (int v : ciclo)
        cout << v << " ";
    cout << "\n";

    return 0;
}
