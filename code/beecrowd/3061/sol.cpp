#include <bits/stdc++.h>
using namespace std;

const int dl[4] = {1, -1, 0, 0};
const int dc[4] = {0, 0, 1, -1};

int n, m;
vector<vector<int>> img;
vector<vector<bool>> vis;

void bfs(int li, int ci){
    queue<pair<int, int>> fila;

    // marca ao inserir: cada pixel preto entra na fila no maximo uma vez
    vis[li][ci] = true;
    fila.push(make_pair(li, ci));

    while (!fila.empty()) {
        int l = fila.front().first;
        int c = fila.front().second;
        fila.pop();

        for (int i = 0; i < 4; i++) {
            int nl = l + dl[i];
            int nc = c + dc[i];

            if (nl < 0 || nl >= n || nc < 0 || nc >= m) continue;
            if (img[nl][nc] == 0 || vis[nl][nc]) continue;

            vis[nl][nc] = true;
            fila.push(make_pair(nl, nc));
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;
    img.assign(n, vector<int>(m));
    vis.assign(n, vector<bool>(m, false));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> img[i][j];

    int manchas = 0;
    for (int l = 0; l < n; l++) {
        for (int c = 0; c < m; c++) {
            if (img[l][c] == 0 || vis[l][c]) continue;
            manchas++;
            bfs(l, c);
        }
    }

    cout << manchas << "\n";

    return 0;
}
