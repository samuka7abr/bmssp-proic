#include <bits/stdc++.h>
using namespace std;

const int N = 5;
const int dl[4] = {1, -1, 0, 0};
const int dc[4] = {0, 0, 1, -1};

bool alcanca(const int lab[N][N]) {
    if (lab[0][0] == 1 || lab[N - 1][N - 1] == 1) return false;

    int dist[N][N];
    fill(&dist[0][0], &dist[0][0] + N * N, -1);

    queue<pair<int, int>> fila;
    dist[0][0] = 0;
    fila.push(make_pair(0, 0));

    while (!fila.empty()) {
        int l = fila.front().first;
        int c = fila.front().second;
        fila.pop();

        if (l == N - 1 && c == N - 1) return true;

        for (int i = 0; i < 4; i++) {
            int nl = l + dl[i];
            int nc = c + dc[i];

            if (nl < 0 || nl >= N || nc < 0 || nc >= N) continue;
            if (lab[nl][nc] == 1) continue;
            if (dist[nl][nc] != -1) continue;

            dist[nl][nc] = dist[l][c] + 1;
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
        int lab[N][N];
        for (int l = 0; l < N; l++)
            for (int c = 0; c < N; c++) cin >> lab[l][c];

        cout << (alcanca(lab) ? "COPS" : "ROBBERS") << "\n";
    }

    return 0;
}
