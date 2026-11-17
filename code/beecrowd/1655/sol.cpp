#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
double d[MAXN][MAXN];

void floydWarshall(int n) {
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                d[i][j] = max(d[i][j], d[i][k] * d[k][j]);
}

int main() {
    int n, m;
    while (scanf("%d", &n) == 1 && n != 0) {
        scanf("%d", &m);

        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                d[i][j] = (i == j) ? 1.0 : 0.0;

        for (int i = 0; i < m; i++) {
            int a, b, p;
            scanf("%d %d %d", &a, &b, &p);
            d[a][b] = d[b][a] = p / 100.0;
        }

        floydWarshall(n);
        printf("%.6f percent\n", d[1][n] * 100.0);
    }
    return 0;
}
