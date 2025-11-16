#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

// Função para calcular a distância Euclidiana
double dist(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

// Heurística do Vizinho Mais Próximo
vector<int> vizinhoMaisProximo(const vector<pair<double,double>>& cidades) {
    int n = cidades.size();
    vector<int> tour;
    vector<bool> visitado(n, false);

    int atual = 0; // começa pela cidade 0
    visitado[0] = true;
    tour.push_back(0);

    for(int step = 1; step < n; step++) {
        double melhorDist = numeric_limits<double>::infinity();
        int prox = -1;

        for(int i = 0; i < n; i++) {
            if(!visitado[i]) {
                double d = dist(cidades[atual].first,
                                cidades[atual].second,
                                cidades[i].first,
                                cidades[i].second);

                if(d < melhorDist) {
                    melhorDist = d;
                    prox = i;
                }
            }
        }

        visitado[prox] = true;
        tour.push_back(prox);
        atual = prox;
    }

    // Fecha o ciclo
    tour.push_back(0);

    return tour;
}

int main() {
    vector<pair<double,double>> cidades = {
        {0,0}, {1,5}, {5,2}, {6,6}, {2,4}
    };

    vector<int> tour = vizinhoMaisProximo(cidades);

    cout << "Rota (Vizinho Mais Proximo): ";
    for(int c : tour) cout << c << " ";
    cout << "\n";

    return 0;
}

