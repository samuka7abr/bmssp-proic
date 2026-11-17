---
type: resource
tags:
  - grafos
  - pesquisa
  - faculdade
  - idp
  - bfs
  - beecrowd
created: 2026-11-17
updated: 2026-11-17
related:
  - "[[Guia BFS]]"
  - "[[08 - Alem da BFS - Dijkstra e Floyd]]"
---

# 1123 - Desvio de Rota

> **Técnica:** Dijkstra modificado / Floyd · **Listas:** A · **Enunciado:** [beecrowd 1123](https://judge.beecrowd.com/pt/problems/view/1123)

## O problema em uma frase

Um país tem N cidades (até 250) e M estradas de mão dupla com pedágio. A rota de serviço é 0 → 1 → ... → C−1. O veículo foi consertado na cidade K, fora da rota, e precisa chegar a C−1 pagando o mínimo de pedágio, com uma regra: **se pisar numa cidade da rota, a partir dali só pode seguir a rota.** Vários casos até `0 0 0 0`.

## Modelando como grafo

O truque desta questão é que o grafo certo **não é** o grafo dado. A regra da rota vira uma edição das arestas:

| Estrada u–v | Vira |
|---|---|
| u e v fora da rota | aresta nos dois sentidos |
| u fora, v na rota | só u → v (dá para entrar na rota, não sair) |
| u e v na rota, consecutivas (v = u + 1) | só u → u + 1 (seguir a rota para a frente) |
| u e v na rota, não consecutivas | removida |

Depois dessa edição, a regra "uma vez na rota, siga a rota" está embutida no grafo, e o problema vira um **caminho mínimo comum** de K até C−1.

## Por que essa técnica (e não outra)

Pesos arbitrários (0 a 250): Dijkstra ([[08 - Alem da BFS - Dijkstra e Floyd]]). Com N ≤ 250, Floyd também passa (250³ ≈ 1,6·10⁷), mas como a origem é uma só, Dijkstra a partir de K é o natural.

Repare que a ideia é a mesma do [[05 - BFS em espaco de estados]]: quando o enunciado impõe uma regra sobre o caminho, ou você **aumenta o estado** (Lucchesi, Ex. 18) ou **edita o grafo**. Aqui editar basta, porque a regra depende só de em qual cidade você está, não do histórico.

Uma otimização comum: o custo de seguir a rota de i até C−1 é fixo, então dá para pré-calcular `resto[i]` e rodar Dijkstra só no grafo fora da rota. O código não faz isso; ele deixa a rota no grafo como arestas de mão única, que é mais simples de explicar.

## O algoritmo passo a passo

1. Monte a lista de adjacência aplicando a tabela acima.
2. Dijkstra a partir de K.
3. Imprima `dist[C-1]`.

Rastreio do primeiro caso (N = 4, rota 0 → 1 → 2, K = 3): as estradas de 3 viram 3 → 0 (custo 1), 3 → 1 (10) e 3 → 2 (10). A estrada 0–2 (custo 1) liga cidades não consecutivas da rota e some. Da rota sobram 0 → 1 (10) e 1 → 2 (10).

- 3 → 2 direto: 10.
- 3 → 0 → 1 → 2: 1 + 10 + 10 = 21.
- 3 → 1 → 2: 10 + 10 = 20.

Resposta 10. Sem a regra, 3 → 0 → 2 custaria 2. É exatamente o que a regra proíbe, porque 0 → 2 sai da rota.

## Complexidade

Dijkstra com heap: O((N + M) log N) por caso.

## Armadilhas

- Deixar a estrada entre cidades da rota não consecutivas.
- Permitir **sair** da rota para uma cidade de fora.
- Pedágio 0 é permitido: Dijkstra continua correto (pesos **não negativos**).

## Código

```cpp
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

vector<int> dijkstra(const vector<vector<pair<int, int>>>& grafo, int origem){
    vector<int> dist(grafo.size(), INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;

    dist[origem] = 0;
    heap.push(make_pair(0, origem));

    while (!heap.empty()) {
        int d = heap.top().first;
        int u = heap.top().second;
        heap.pop();

        if (d > dist[u]) continue;

        for (auto [v, p] : grafo[u]) {
            if (d + p < dist[v]) {
                dist[v] = d + p;
                heap.push(make_pair(dist[v], v));
            }
        }
    }

    return dist;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, c, k;
    while (cin >> n >> m >> c >> k && n != 0) {
        vector<vector<pair<int, int>>> grafo(n);

        // cidades 0..c-1 sao a rota: dentro dela so se anda para frente, e dela nao se sai
        for (int i = 0; i < m; i++) {
            int u, v, p;
            cin >> u >> v >> p;

            if (u >= c && v >= c) {
                grafo[u].push_back(make_pair(v, p));
                grafo[v].push_back(make_pair(u, p));
            } else if (u < c && v < c) {
                if (abs(u - v) == 1) grafo[min(u, v)].push_back(make_pair(max(u, v), p));
            } else if (u >= c) {
                grafo[u].push_back(make_pair(v, p));
            } else {
                grafo[v].push_back(make_pair(u, p));
            }
        }

        vector<int> dist = dijkstra(grafo, k);

        cout << dist[c - 1] << "\n";
    }

    return 0;
}
```

Arquivos: `code/beecrowd/1123/sol.cpp` · rodar com `make test X=1123` dentro de `code/beecrowd/`.

Testado localmente com o exemplo do enunciado (`make test` deu OK); não submetido ao juiz.

## Para fixar

1. Implemente a otimização do `resto[i]` e rode Dijkstra só nas cidades fora da rota.
2. Resolva com Floyd e compare o código. Em que ponto a edição do grafo entra no Floyd?
3. E se a regra fosse "uma vez na rota, você pode andar nela nos dois sentidos, mas não pode sair"? Que linha da tabela muda?
