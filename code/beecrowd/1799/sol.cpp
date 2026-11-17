#include <bits/stdc++.h>
using namespace std;

vector<int> bfs(const vector<vector<int>>& grafo, int origem){
    vector<int> dist(grafo.size(), -1);
    queue<int> fila;

    dist[origem] = 0;
    fila.push(origem);

    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();

        for (int v : grafo[u]) {
            if (dist[v] != -1) continue;

            dist[v] = dist[u] + 1;
            fila.push(v);
        }
    }

    return dist;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int pontos, ligacoes;
    while (cin >> pontos >> ligacoes) {
        map<string, int> id;
        vector<vector<int>> grafo;

        auto pegaId = [&](const string& nome) -> int {
            auto it = id.find(nome);
            if (it != id.end()) return it->second;

            int novo = grafo.size();
            id[nome] = novo;
            grafo.emplace_back();
            return novo;
        };

        for (int i = 0; i < ligacoes; i++) {
            string a, b;
            cin >> a >> b;

            int u = pegaId(a);
            int v = pegaId(b);
            grafo[u].push_back(v);
            grafo[v].push_back(u);
        }

        int entrada = pegaId("Entrada");
        int queijo = pegaId("*");
        int saida = pegaId("Saida");

        // o melhor caminho que passa pelo queijo e a soma de dois caminhos minimos independentes
        vector<int> daEntrada = bfs(grafo, entrada);
        vector<int> doQueijo = bfs(grafo, queijo);

        cout << daEntrada[queijo] + doQueijo[saida] << "\n";
    }

    return 0;
}
