#include <bits/stdc++.h>
using namespace std;

const int MAXV = 10000;

int inverte(int x){
    int r = 0;
    while (x > 0) {
        r = r * 10 + x % 10;
        x /= 10;
    }
    return r;
}

// estado = numero no visor; arestas = apertar "+1" ou "inverter"
int bfs(int a, int b){
    vector<int> dist(MAXV + 1, -1);
    queue<int> fila;
    dist[a] = 0;
    fila.push(a);

    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();

        if (u == b) return dist[u];

        int viz[2] = {u + 1, inverte(u)};
        for (int v : viz) {
            if (v > MAXV || dist[v] != -1) continue;

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

    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        cout << bfs(a, b) << "\n";
    }

    return 0;
}
