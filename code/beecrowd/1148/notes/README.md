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

# 1148 - Países em Guerra

> **Técnica:** Dijkstra com restrição / Floyd · **Listas:** A · **Enunciado:** [beecrowd 1148](https://judge.beecrowd.com/pt/problems/view/1148)

## O problema em uma frase

N cidades (até 500) e E acordos direcionados "X manda carta para Y em H horas". Duas cidades estão no **mesmo país** se uma carta consegue ir de uma à outra **e** voltar; entre cidades do mesmo país o envio é instantâneo. Responda K consultas de tempo mínimo de O a D, ou `Nao e possivel entregar a carta`, com uma linha em branco depois de cada caso.

## Modelando como grafo

- **Vértice:** cidade.
- **Aresta:** acordo X → Y com peso H. **Direcionado.**
- **"Mesmo país":** X alcança Y e Y alcança X. Isso é uma **componente fortemente conexa** (CFC). Dentro de uma CFC, o custo vira 0.

## Por que essa técnica (e não outra)

Os pesos são arbitrários, então BFS não serve ([[08 - Alem da BFS - Dijkstra e Floyd]]). Há várias consultas com origens diferentes e N ≤ 500, então **todos os pares** de uma vez é natural: Floyd-Warshall.

A solução faz Floyd **duas vezes**:

1. O primeiro Floyd responde "quem alcança quem" (`dist < INF`).
2. Para cada par mutuamente alcançável, `dist[i][j] = 0`. Isso é colocar arestas de peso 0 dentro de cada país.
3. O segundo Floyd recalcula os menores caminhos com essas arestas novas.

**Por que não basta um Floyd só?** Porque o primeiro calcula distâncias sem saber dos atalhos de custo 0. Um caminho ótimo pode atravessar um país inteiro de graça, e isso só aparece depois de zerar.

**Alternativa mais rápida:** achar as CFC com Tarjan ou Kosaraju, **contrair** cada país num vértice só (Diestel, seção 1.7) e rodar Dijkstra a partir de cada origem consultada. Para N = 500 o Floyd duplo (2 · 500³ = 2,5·10⁸) costuma passar, mas fica perto do limite.

## O algoritmo passo a passo

1. `dist` = INF, `dist[i][i] = 0`, `dist[x][y] = min(dist[x][y], h)` para cada acordo.
2. Floyd.
3. Zere `dist[i][j]` quando `dist[i][j] < INF` e `dist[j][i] < INF`.
4. Floyd de novo.
5. Responda as consultas; linha em branco no fim do caso.

Rastreio do primeiro caso: 1⇄2 (5 e 10 horas) formam um país; 3⇄4 (8 e 7) formam outro; 2 → 3 custa 6. Consultas: 1→2 = 0 (mesmo país); 1→3 = 0 + 6 = 6; 1→4 = 6 + 0 = 6; 4→3 = 0; 4→1: não há aresta do país {3,4} para o país {1,2}, então não é possível.

## Complexidade

Dois Floyd: O(N³) por caso. Memória O(N²).

## Armadilhas

- Ler "mesmo país" como "acordo direto nos dois sentidos". É **alcançabilidade** nos dois sentidos, por qualquer caminho.
- Acordo repetido entre o mesmo par: guarde o mínimo.
- `INF + INF` estoura `int` se INF for perto de 2³¹. O código usa 10⁹, e 2·10⁹ ainda cabe em `int` com sinal. Mesmo assim, o `if (dist[i][k] == INF) continue` evita a maioria das somas.
- A linha em branco depois de **cada** caso.

## Código

```cpp
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

void floydWarshall(vector<vector<int>>& dist){
    int n = dist.size();

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (dist[i][k] == INF) continue;

            for (int j = 0; j < n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, e;
    while (cin >> n >> e && n != 0) {
        vector<vector<int>> dist(n, vector<int>(n, INF));
        for (int i = 0; i < n; i++) dist[i][i] = 0;

        for (int i = 0; i < e; i++) {
            int x, y, h;
            cin >> x >> y >> h;
            dist[x - 1][y - 1] = min(dist[x - 1][y - 1], h);
        }

        // 1a passada descobre quem alcanca quem; quem se alcanca nos dois sentidos e do mesmo pais
        floydWarshall(dist);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][j] < INF && dist[j][i] < INF) dist[i][j] = 0;
            }
        }

        floydWarshall(dist);

        int k;
        cin >> k;
        for (int i = 0; i < k; i++) {
            int o, d;
            cin >> o >> d;

            int tempo = dist[o - 1][d - 1];
            if (tempo == INF) cout << "Nao e possivel entregar a carta\n";
            else cout << tempo << "\n";
        }
        cout << "\n";
    }

    return 0;
}
```

Arquivos: `code/beecrowd/1148/sol.cpp` · rodar com `make test X=1148` dentro de `code/beecrowd/`.

Testado localmente com o exemplo do enunciado (`make test` deu OK); não submetido ao juiz.

## Para fixar

1. Reescreva com Kosaraju + contração + Dijkstra. Compare os tempos num caso com N = 500 e E = N².
2. O grafo contraído (um vértice por país) nunca tem ciclo dirigido. Por quê?
3. Ligação com o [[06 - BFS 0-1]]: se todos os acordos levassem 1 hora, que algoritmo você usaria depois da contração?
