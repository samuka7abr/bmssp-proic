#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

vector<long long> dijkstra(const vector<vector<pair<int, long long>>>& graph, int source) {
    vector<long long> dist(graph.size(), INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;

    dist[source] = 0;
    pq.emplace(0, source);

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;

        for (auto [v, w] : graph[u]) {
            if (d + w < dist[v]) {
                dist[v] = d + w;
                pq.emplace(dist[v], v);
            }
        }
    }
    return dist;
}
