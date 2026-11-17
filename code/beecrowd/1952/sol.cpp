#include <bits/stdc++.h>
using namespace std;

// os 24 saltos: {|di|, |dj|, |dk|} = {0, 1, 2} em qualquer ordem e com qualquer sinal
vector<array<int, 3>> saltos(){
    vector<array<int, 3>> s;
    for (int di = -2; di <= 2; di++)
        for (int dj = -2; dj <= 2; dj++)
            for (int dk = -2; dk <= 2; dk++) {
                array<int, 3> a = {abs(di), abs(dj), abs(dk)};
                sort(a.begin(), a.end());
                if (a[0] == 0 && a[1] == 1 && a[2] == 2) s.push_back({di, dj, dk});
            }
    return s;
}

int N, M, L;

int id(int i, int j, int k){
    return (k * N + i) * M + j;
}

int bfs(int i1, int j1, int k1, int i2, int j2, int k2){
    const vector<array<int, 3>> mov = saltos();
    vector<int> dist(N * M * L, -1);
    queue<array<int, 3>> fila;

    dist[id(i1, j1, k1)] = 0;
    fila.push({i1, j1, k1});

    while (!fila.empty()) {
        auto [i, j, k] = fila.front();
        fila.pop();

        if (i == i2 && j == j2 && k == k2) return dist[id(i, j, k)];

        for (const array<int, 3>& d : mov) {
            int ni = i + d[0], nj = j + d[1], nk = k + d[2];

            if (ni < 0 || ni >= N || nj < 0 || nj >= M || nk < 0 || nk >= L) continue;
            if (dist[id(ni, nj, nk)] != -1) continue;

            dist[id(ni, nj, nk)] = dist[id(i, j, k)] + 1;
            fila.push({ni, nj, nk});
        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> L;

    int i1, j1, k1, i2, j2, k2;
    cin >> i1 >> j1 >> k1 >> i2 >> j2 >> k2;

    cout << bfs(i1 - 1, j1 - 1, k1 - 1, i2 - 1, j2 - 1, k2 - 1) << "\n";

    return 0;
}
