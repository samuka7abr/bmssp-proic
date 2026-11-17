#include <bits/stdc++.h>
using namespace std;

const int dl[4] = {1, -1, 0, 0};
const int dc[4] = {0, 0, 1, -1};

int n, m;
vector<string> grade;

void bfs(int li, int ci){
    queue<pair<int, int>> fila;

    // pinta ao inserir: cada pixel entra na fila no maximo uma vez
    grade[li][ci] = 'o';
    fila.push(make_pair(li, ci));

    while (!fila.empty()) {
        int l = fila.front().first;
        int c = fila.front().second;
        fila.pop();

        for (int i = 0; i < 4; i++) {
            int nl = l + dl[i];
            int nc = c + dc[i];

            if (nl < 0 || nl >= n || nc < 0 || nc >= m) continue;
            if (grade[nl][nc] != '.') continue;

            grade[nl][nc] = 'o';
            fila.push(make_pair(nl, nc));
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;
    grade.resize(n);
    for (int i = 0; i < n; i++) cin >> grade[i];

    int cliques = 0;
    for (int l = 0; l < n; l++) {
        for (int c = 0; c < m; c++) {
            if (grade[l][c] != '.') continue;
            cliques++;
            bfs(l, c);
        }
    }

    cout << cliques << "\n";

    return 0;
}
