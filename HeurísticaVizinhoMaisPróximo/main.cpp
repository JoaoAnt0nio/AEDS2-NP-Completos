#include <bits/stdc++.h>
using namespace std;

// Heurística do Vizinho Mais Próximo para o Caixeiro Viajante
vector<int> tspVizinhoMaisProximo(const vector<vector<int>>& G, int inicio) {
    int n = G.size();

    vector<bool> visitado(n, false);
    vector<int> caminho;

    int atual = inicio;
    caminho.push_back(atual);
    visitado[atual] = true;

    // Enquanto ainda houver cidades não visitadas
    for (int k = 1; k < n; k++) {
        int proximo = -1;
        int menorDist = INT_MAX;

        // Escolher a cidade não visitada mais próxima
        for (int v = 0; v < n; v++) {
            if (!visitado[v] && G[atual][v] < menorDist) {
                menorDist = G[atual][v];
                proximo = v;
            }
        }

        visitado[proximo] = true;
        caminho.push_back(proximo);
        atual = proximo;
    }

    // Fechar o ciclo voltando à cidade inicial
    caminho.push_back(inicio);

    return caminho;
}

int main() {
    // Exemplo de grafo completo (matriz de adjacência)
    vector<vector<int>> G = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    // Começar da cidade 0
    vector<int> ciclo = tspVizinhoMaisProximo(G, 0);

    cout << "Ciclo pelo Vizinho Mais Proximo: ";
    for (int cidade : ciclo)
        cout << cidade << " ";
    cout << endl;

    return 0;
}
