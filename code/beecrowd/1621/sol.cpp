#include <bits/stdc++.h>
using namespace std;

const int dl[4] = {1, -1, 0, 0};
const int dc[4] = {0, 0, 1, -1};

int n, m;
vector<string> lab;
vector<vector<int>> dist;

// devolve a celula mais distante de (li, ci); dist fica preenchida
pair<int, int> bfs(int li, int ci){
    dist.assign(n, vector<int>(m, -1));
    queue<pair<int, int>> fila;
    dist[li][ci] = 0;
    fila.push(make_pair(li, ci));

    pair<int, int> longe = make_pair(li, ci);
    while (!fila.empty()) {
        int l = fila.front().first;
        int c = fila.front().second;
        fila.pop();

        if (dist[l][c] > dist[longe.first][longe.second]) longe = make_pair(l, c);

        for (int i = 0; i < 4; i++) {
            int nl = l + dl[i];
            int nc = c + dc[i];

            if (nl < 0 || nl >= n || nc < 0 || nc >= m) continue;
            if (lab[nl][nc] == '#' || dist[nl][nc] != -1) continue;

            dist[nl][nc] = dist[l][c] + 1;
            fila.push(make_pair(nl, nc));
        }
    }

    return longe;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> n >> m && (n || m)) {
        lab.assign(n, "");
        for (int i = 0; i < n; i++) cin >> lab[i];

        pair<int, int> qualquer;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (lab[i][j] == '.') qualquer = make_pair(i, j);

        // o labirinto e uma arvore: a celula mais longe de qualquer uma e ponta de um diametro
        pair<int, int> x = bfs(qualquer.first, qualquer.second);
        pair<int, int> y = bfs(x.first, x.second);

        cout << dist[y.first][y.second] << "\n";
    }

    return 0;
}
