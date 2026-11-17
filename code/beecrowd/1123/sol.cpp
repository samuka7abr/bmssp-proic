#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

vector<int> dijkstra(const vector<vector<pair<int, int>>>& grafo, int origem){
    vector<int> dist(grafo.size(), INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;

    dist[origem] = 0;
    heap.push(make_pair(0, origem));

    while (!heap.empty()) {
        int d = heap.top().first;
        int u = heap.top().second;
        heap.pop();

        if (d > dist[u]) continue;

        for (auto [v, p] : grafo[u]) {
            if (d + p < dist[v]) {
                dist[v] = d + p;
                heap.push(make_pair(dist[v], v));
            }
        }
    }

    return dist;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, c, k;
    while (cin >> n >> m >> c >> k && n != 0) {
        vector<vector<pair<int, int>>> grafo(n);

        // cidades 0..c-1 sao a rota: dentro dela so se anda para frente, e dela nao se sai
        for (int i = 0; i < m; i++) {
            int u, v, p;
            cin >> u >> v >> p;

            if (u >= c && v >= c) {
                grafo[u].push_back(make_pair(v, p));
                grafo[v].push_back(make_pair(u, p));
            } else if (u < c && v < c) {
                if (abs(u - v) == 1) grafo[min(u, v)].push_back(make_pair(max(u, v), p));
            } else if (u >= c) {
                grafo[u].push_back(make_pair(v, p));
            } else {
                grafo[v].push_back(make_pair(u, p));
            }
        }

        vector<int> dist = dijkstra(grafo, k);

        cout << dist[c - 1] << "\n";
    }

    return 0;
}
