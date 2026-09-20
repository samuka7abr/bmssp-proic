#include <bits/stdc++.h>
using namespace std;

const int dl[8] = {1, 1, -1, -1, 2, 2, -2, -2};
const int dc[8] = {2, -2, 2, -2, 1, -1, 1, -1};

int bfs(int li, int ci, int lf, int cf){
    int dist[8][8];
    fill(&dist[0][0], &dist[0][0] + 64, -1);

    queue<pair<int, int>> fila;
    dist[li][ci] = 0;

    fila.push(make_pair(li, ci));

    while (!fila.empty()) {
        int l = fila.front().first;
        int c = fila.front().second;
        fila.pop();

        if (l == lf && c == cf) return dist[l][c];

        for (int i = 0; i < 8; i++) {
            int nl = l + dl[i];
            int nc = c + dc[i];

            if (nl < 0 || nl >= 8 || nc < 0 || nc >= 8) continue;
            if (dist[nl][nc] != -1) continue;

            dist[nl][nc] = dist[l][c] + 1;
            fila.push(make_pair(nl, nc));
        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    string origem, destino;
    while (cin >> origem >> destino) {
        int ci = origem[0] - 'a';
        int li = origem[1] - '1';
        int cf = destino[0] - 'a';
        int lf = destino[1] - '1';

        int n = bfs(li, ci, lf, cf);

        cout << "To get from " << origem << " to " << destino
             << " takes " << n << " knight moves.\n";
    }

    return 0;
}

