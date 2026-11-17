#include <bits/stdc++.h>
using namespace std;

const int MAXV = 200000;

// estado = o numero atual (divisao inteira); teto folgado porque um caminho otimo pode passar acima de M
int bfs(int n, int m){
    vector<int> dist(MAXV + 1, -1);
    queue<int> fila;
    dist[n] = 0;
    fila.push(n);

    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();

        if (u == m) return dist[u];

        int viz[6] = {u * 2, u * 3, u / 2, u / 3, u + 7, u - 7};
        for (int v : viz) {
            if (v < 0 || v > MAXV || dist[v] != -1) continue;

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

    int n, m;
    while (cin >> n >> m) {
        cout << bfs(n, m) << "\n";
    }

    return 0;
}
