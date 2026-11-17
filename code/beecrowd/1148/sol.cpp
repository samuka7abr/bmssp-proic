#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

void floydWarshall(vector<vector<int>>& dist){
    int n = dist.size();

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (dist[i][k] == INF) continue;

            for (int j = 0; j < n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, e;
    while (cin >> n >> e && n != 0) {
        vector<vector<int>> dist(n, vector<int>(n, INF));
        for (int i = 0; i < n; i++) dist[i][i] = 0;

        for (int i = 0; i < e; i++) {
            int x, y, h;
            cin >> x >> y >> h;
            dist[x - 1][y - 1] = min(dist[x - 1][y - 1], h);
        }

        // 1a passada descobre quem alcanca quem; quem se alcanca nos dois sentidos e do mesmo pais
        floydWarshall(dist);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][j] < INF && dist[j][i] < INF) dist[i][j] = 0;
            }
        }

        floydWarshall(dist);

        int k;
        cin >> k;
        for (int i = 0; i < k; i++) {
            int o, d;
            cin >> o >> d;

            int tempo = dist[o - 1][d - 1];
            if (tempo == INF) cout << "Nao e possivel entregar a carta\n";
            else cout << tempo << "\n";
        }
        cout << "\n";
    }

    return 0;
}
