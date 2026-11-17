#include <bits/stdc++.h>
using namespace std;

const int MAXC = 100000;

vector<int> vizinhos(int u){
    vector<int> v = {u + 1, u - 1, u * 2, u * 3};
    if (u % 2 == 0) v.push_back(u / 2);
    return v;
}

int bfs(int origem, int destino, const vector<int>& proibidos){
    vector<int> dist(MAXC + 1, -1);
    // canal proibido entra como "ja visitado": o BFS nunca o enfileira
    for (int p : proibidos) {
        if (p >= 1 && p <= MAXC) dist[p] = -2;
    }

    queue<int> fila;
    dist[origem] = 0;
    fila.push(origem);

    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();

        if (u == destino) return dist[u];

        for (int v : vizinhos(u)) {
            if (v < 1 || v > MAXC || dist[v] != -1) continue;

            dist[v] = dist[u] + 1;
            fila.push(v);
        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int o, d, k;
    while (cin >> o >> d >> k && (o || d || k)) {
        vector<int> proibidos(k);
        for (int i = 0; i < k; i++) cin >> proibidos[i];

        cout << bfs(o, d, proibidos) << "\n";
    }

    return 0;
}
