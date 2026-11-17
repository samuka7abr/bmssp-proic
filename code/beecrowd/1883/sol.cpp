#include <bits/stdc++.h>
using namespace std;

const int dl[4] = {1, -1, 0, 0};
const int dc[4] = {0, 0, 1, -1};

typedef vector<vector<int>> Matriz;

// multi-fonte: todos os F entram com tempo 0; fogo[l][c] = minuto em que o fogo chega (-1 = nunca)
Matriz bfs_fogo(const vector<string>& sala, const vector<pair<int, int>>& focos) {
    int n = sala.size(), m = sala[0].size();
    Matriz fogo(n, vector<int>(m, -1));
    queue<pair<int, int>> fila;

    for (const pair<int, int>& f : focos) {
        fogo[f.first][f.second] = 0;
        fila.push(f);
    }

    while (!fila.empty()) {
        int l = fila.front().first;
        int c = fila.front().second;
        fila.pop();

        for (int i = 0; i < 4; i++) {
            int nl = l + dl[i];
            int nc = c + dc[i];

            if (nl < 0 || nl >= n || nc < 0 || nc >= m) continue;
            if (sala[nl][nc] == '#') continue;
            if (fogo[nl][nc] != -1) continue;

            fogo[nl][nc] = fogo[l][c] + 1;
            fila.push(make_pair(nl, nc));
        }
    }

    return fogo;
}

bool foge(const vector<string>& sala, const Matriz& fogo, pair<int, int> ini, pair<int, int> saida) {
    int n = sala.size(), m = sala[0].size();
    Matriz dist(n, vector<int>(m, -1));
    queue<pair<int, int>> fila;

    dist[ini.first][ini.second] = 0;
    fila.push(ini);

    while (!fila.empty()) {
        int l = fila.front().first;
        int c = fila.front().second;
        fila.pop();

        if (l == saida.first && c == saida.second) return true;

        for (int i = 0; i < 4; i++) {
            int nl = l + dl[i];
            int nc = c + dc[i];

            if (nl < 0 || nl >= n || nc < 0 || nc >= m) continue;
            if (sala[nl][nc] == '#') continue;
            if (dist[nl][nc] != -1) continue;

            int t = dist[l][c] + 1;
            // chegar junto com o fogo (t == fogo) tambem mata
            if (fogo[nl][nc] != -1 && fogo[nl][nc] <= t) continue;

            dist[nl][nc] = t;
            fila.push(make_pair(nl, nc));
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<string> sala(n);
        vector<pair<int, int>> focos;
        pair<int, int> ini, saida;

        for (int l = 0; l < n; l++) {
            cin >> sala[l];
            for (int c = 0; c < m; c++) {
                if (sala[l][c] == 'F') focos.push_back(make_pair(l, c));
                if (sala[l][c] == 'S') ini = make_pair(l, c);
                if (sala[l][c] == 'E') saida = make_pair(l, c);
            }
        }

        Matriz fogo = bfs_fogo(sala, focos);
        cout << (foge(sala, fogo, ini, saida) ? 'Y' : 'N') << "\n";
    }

    return 0;
}
