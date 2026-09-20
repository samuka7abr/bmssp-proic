#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5;

vector<int> adj[maxn];
int vis[maxn], topo[maxn], topoLen;

// DFS com ordenacao topologica
void dfs(int u)
{
    if (vis[u])
        return;
    vis[u] = true;
    for (int v : g[u])
        dfs(v);
    topo[topoLen++] = u;
}

