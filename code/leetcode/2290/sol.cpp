#include <bits/stdc++.h>
using namespace std;

const int dl[4] = {1, -1, 0, 0};
const int dc[4] = {0, 0, 1, -1};
const int inf = 1e9;

class Solution {
public:
    int minimumObstacles(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();

        vector<vector<int>> dist(m, vector<int>(n, inf));
        deque<pair<int, int>> dq;

        dist[0][0] = 0;
        dq.push_back(make_pair(0, 0));

        while (!dq.empty()) {
            int l = dq.front().first;
            int c = dq.front().second;
            dq.pop_front();

            for (int i = 0; i < 4; i++) {
                int nl = l + dl[i];
                int nc = c + dc[i];

                if (nl < 0 || nl >= m || nc < 0 || nc >= n) continue;

                // custo 0 (celula livre) vai para a frente do deque, custo 1 (obstaculo) para tras
                int w = grid[nl][nc];
                if (dist[nl][nc] <= dist[l][c] + w) continue;

                dist[nl][nc] = dist[l][c] + w;
                if (w == 0) dq.push_front(make_pair(nl, nc));
                else dq.push_back(make_pair(nl, nc));
            }
        }

        return dist[m - 1][n - 1];
    }
};

// ---- driver local, não submeter ----
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int m, n;
    while (cin >> m >> n) {
        vector<vector<int>> grid(m, vector<int>(n));
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                cin >> grid[i][j];

        Solution sol;
        cout << sol.minimumObstacles(grid) << "\n";
    }

    return 0;
}
