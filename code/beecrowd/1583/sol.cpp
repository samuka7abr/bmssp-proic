#include <bits/stdc++.h>
using namespace std;

const int dl[4] = {1, -1, 0, 0};
const int dc[4] = {0, 0, 1, -1};

vector<vector<int>> contamina(const vector<string>& mapa) {
    int n = mapa.size(), m = mapa[0].size();
    vector<vector<int>> dist(n, vector<int>(m, -1));
    queue<pair<int, int>> fila;

    // multi-fonte: todo T entra na fila com dist 0 antes de a BFS comecar
    for (int l = 0; l < n; l++) {
        for (int c = 0; c < m; c++) {
            if (mapa[l][c] == 'T') {
                dist[l][c] = 0;
                fila.push(make_pair(l, c));
            }
        }
    }

    while (!fila.empty()) {
        int l = fila.front().first;
        int c = fila.front().second;
        fila.pop();

        for (int i = 0; i < 4; i++) {
            int nl = l + dl[i];
            int nc = c + dc[i];

            if (nl < 0 || nl >= n || nc < 0 || nc >= m) continue;
            if (mapa[nl][nc] != 'A') continue;
            if (dist[nl][nc] != -1) continue;

            dist[nl][nc] = dist[l][c] + 1;
            fila.push(make_pair(nl, nc));
        }
    }

    return dist;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;

        vector<string> mapa(n);
        for (int l = 0; l < n; l++) cin >> mapa[l];

        vector<vector<int>> dist = contamina(mapa);

        for (int l = 0; l < n; l++) {
            for (int c = 0; c < m; c++) {
                cout << (dist[l][c] != -1 ? 'T' : mapa[l][c]);
            }
            cout << "\n";
        }
        cout << "\n";
    }

    return 0;
}
