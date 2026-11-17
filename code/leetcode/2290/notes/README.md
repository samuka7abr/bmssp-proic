---
type: resource
tags:
  - grafos
  - pesquisa
  - faculdade
  - idp
  - bfs
  - leetcode
created: 2026-11-17
updated: 2026-11-17
related:
  - "[[Guia BFS]]"
  - "[[06 - BFS 0-1]]"
---

# LC 2290 - Minimum Obstacle Removal to Reach Corner

> **Técnica:** BFS 0-1 · **Listas:** extra · **Enunciado:** [LeetCode 2290](https://leetcode.com/problems/minimum-obstacle-removal-to-reach-corner/)

## O problema em uma frase

Num grid m×n de 0 (livre) e 1 (obstáculo), com m·n até 10⁵, qual o menor número de obstáculos que você precisa remover para ir de (0,0) a (m−1, n−1) andando nas 4 direções? (0,0) e o canto final são sempre livres.

## Modelando como grafo

- **Vértice:** célula.
- **Aresta:** para cada vizinha. O peso é o **valor da célula de destino**: entrar numa livre custa 0, entrar num obstáculo custa 1 (você o remove).
- **Pergunta:** caminho mínimo com pesos 0 e 1.

## Por que essa técnica (e não outra)

**BFS comum erra.** Ela conta passos, não obstáculos. Um caminho longo por células livres (custo 0) pode ser melhor que um curto que atravessa paredes.

**Dijkstra acerta**, em O(V log V).

**BFS 0-1 acerta em O(V + E)** ([[06 - BFS 0-1]]). Use um deque: relaxar uma aresta de peso 0 coloca o vizinho na **frente** (mesma distância do atual), de peso 1 no **fim** (distância + 1). O invariante é o do Lema 22.3 do Cormen: o deque está ordenado e contém no máximo dois valores, d e d + 1. Então a frente é sempre um vértice de distância mínima, como no Dijkstra, sem heap.

## O algoritmo passo a passo

1. `dist` = ∞; `dist[0][0] = 0`; deque com (0,0).
2. Retire a frente u. Para cada vizinha v com `w = grid[v]`: se `dist[u] + w < dist[v]`, atualize e coloque v na frente (w = 0) ou no fim (w = 1).
3. Responda `dist[m-1][n-1]`.

Rastreio do exemplo 1, `[[0,1,1],[1,1,0],[1,1,0]]` (resposta 2):

Na ordem de direções do código (baixo, cima, direita, esquerda), com `célula/dist`:

| Retira | Deque depois |
|---|---|
| (0,0)/0 | (1,0)/1, (0,1)/1 |
| (1,0)/1 | (0,1)/1, (2,0)/2, (1,1)/2 |
| (0,1)/1 | (2,0)/2, (1,1)/2, (0,2)/2 |
| (2,0)/2 | (1,1)/2, (0,2)/2, (2,1)/3 |
| (1,1)/2 | **(1,2)/2** na frente, (0,2)/2, (2,1)/3 |
| (1,2)/2 | **(2,2)/2** na frente, (0,2)/2, (2,1)/3 |
| (2,2)/2 | fim: resposta 2 |

Repare em duas coisas. As células livres (1,2) e (2,2) furam a fila e são processadas antes de (0,2), que entrou antes delas. E em nenhum momento o deque tem mais de dois valores de distância: 1 e 2, depois 2 e 3.

## Complexidade

O(m·n). Cada célula recebe distância no máximo duas vezes (o argumento está no módulo 06).

## Armadilhas

- **Não use "visitado ao enfileirar"** como na BFS. Um vértice pode entrar no deque com d + 1 e depois ser melhorado para d. O teste certo é `dist[u] + w < dist[v]`, como no Dijkstra.
- O peso é o da célula de **destino**, não da origem.
- No LeetCode só a classe `Solution` é submetida. O `main` abaixo da linha `// ---- driver local, não submeter ----` existe só para rodar com `make test` aqui.

## Código

```cpp
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
```

Arquivos: `code/leetcode/2290/sol.cpp` · rodar com `make test X=2290` dentro de `code/leetcode/`.

Testado localmente com os exemplos 1 e 2 do LeetCode (2 e 0); não submetido ao LeetCode.

## Para fixar

1. Resolva com Dijkstra e compare os tempos num grid 300×300 aleatório.
2. Variação: em vez de remover obstáculos, cada célula tem uma seta e mudar a seta custa 1 (LeetCode 1368). Qual é o peso de cada aresta?
3. Volte ao [[1148 - Paises em Guerra]]: arestas de custo 0 dentro do país e custo arbitrário entre países. Por que lá o deque não basta?
