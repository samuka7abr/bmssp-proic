#include <bits/stdc++.h>
using namespace std;

// dist[i][j] = menor distancia de i ate j, -1 se nao ha caminho
void floydWarshall(vector<vector<long long>> &dist)
{
    int n = dist.size();
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dist[i][k] == -1 || dist[k][j] == -1)
                    continue;
                if (dist[i][j] == -1 || dist[i][j] > dist[i][k] + dist[k][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}
