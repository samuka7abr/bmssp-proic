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
  - "[[04 - BFS multi-fonte]]"
---

# 1583 - Contaminação

> **Técnica:** BFS multi-fonte · **Listas:** C · **Enunciado:** [beecrowd 1583](https://judge.beecrowd.com/pt/problems/view/1583)

## O problema em uma frase

Num mapa até 50×50 de água (`A`), rocha (`X`) e contaminante (`T`), o contaminante se espalha para a água vizinha nas 4 direções e é barrado pela rocha. Imprima o mapa final, com toda água atingida trocada por `T`, e uma linha em branco depois de cada mapa. Vários mapas até `0 0`.

## Modelando como grafo

- **Vértice:** célula que não é rocha.
- **Aresta:** duas células não-rocha vizinhas.
- **Fontes:** **todas** as células `T`.
- **Pergunta:** quais células de água estão no mesmo componente de algum `T`?

## Por que essa técnica (e não outra)

Existem várias fontes. A ideia do [[04 - BFS multi-fonte]] é colocar **todas** na fila com distância 0 antes de começar, o que equivale a uma BFS a partir de um supervértice ligado a todos os `T`. Uma BFS só, O(N·M), em vez de uma por fonte.

Repare num detalhe: este problema **não pergunta tempo**, só "quem é atingido". Então o `dist` do código serve como vetor de visitados, e flood fill a partir de cada `T` também funcionaria. Fazer multi-fonte aqui é treino para o [[1883 - Fuga de Ayutthaya]], em que o **instante** da contaminação importa.

## O algoritmo passo a passo

1. Varra o mapa; todo `T` entra na fila com `dist = 0`.
2. BFS normal, só entrando em células `A`.
3. Imprima o mapa trocando por `T` toda célula com `dist != -1`, e depois uma linha em branco.

Rastreio do primeiro mapa (só a parte que muda):

```
XXXXAXX      XXXXTXX   linha 2: (2,4) atingida no tempo 6
XAAAAAX  ->  XTTTTTX   linha 3: tempos 2, 3, 4, 5, 6 da esquerda para a direita
TAAXAAA      TTTXTTT   linha 4: fonte em (4,0); tempos 1, 2, depois 6, 7, 8 do outro lado da rocha
```

Repare que (4,4) só é atingida no tempo 6: a rocha em (4,3) obriga a contaminação a subir pela linha 3 e descer.

Repare no bloco de `A` no alto (colunas 2 e 3 das linhas 0 e 1) e no `A` isolado em (1,5): estão cercados de rocha e ficam como estão. No segundo mapa a linha de `X` separa os `T` da água, e nada muda.

## Complexidade

O(N·M) por mapa.

## Armadilhas

- **A linha em branco depois de cada mapa, inclusive o último.** É o erro mais comum nesta questão.
- Enfileirar só o primeiro `T` encontrado. A resposta fica certa aqui (porque não há tempo), mas o hábito errado custa caro no 1883.
- Tratar `T` como parede.

## Código

```cpp
#include <bits/stdc++.h>
using namespace std;

const int dl[4] = {1, -1, 0, 0};
const int dc[4] = {0, 0, 1, -1};

vector<vector<int>> contamina(const vector<string>& mapa) {
    int n = mapa.size(), m = mapa[0].size();
    vector<vector<int>> dist(n, vector<int>(m, -1));
    queue<pair<int, int>> fila;

    // multi-fonte: todo T entra na fila com dist 0 antes de a BFS comecar
    for (int l = 0; l < n; l++) {
        for (int c = 0; c < m; c++) {
            if (mapa[l][c] == 'T') {
                dist[l][c] = 0;
                fila.push(make_pair(l, c));
            }
        }
    }

    while (!fila.empty()) {
        int l = fila.front().first;
        int c = fila.front().second;
        fila.pop();

        for (int i = 0; i < 4; i++) {
            int nl = l + dl[i];
            int nc = c + dc[i];

            if (nl < 0 || nl >= n || nc < 0 || nc >= m) continue;
            if (mapa[nl][nc] != 'A') continue;
            if (dist[nl][nc] != -1) continue;

            dist[nl][nc] = dist[l][c] + 1;
            fila.push(make_pair(nl, nc));
        }
    }

    return dist;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;

        vector<string> mapa(n);
        for (int l = 0; l < n; l++) cin >> mapa[l];

        vector<vector<int>> dist = contamina(mapa);

        for (int l = 0; l < n; l++) {
            for (int c = 0; c < m; c++) {
                cout << (dist[l][c] != -1 ? 'T' : mapa[l][c]);
            }
            cout << "\n";
        }
        cout << "\n";
    }

    return 0;
}
```

Arquivos: `code/beecrowd/1583/sol.cpp` · rodar com `make test X=1583` dentro de `code/beecrowd/`.

Testado localmente com o exemplo do enunciado (`make test` deu OK); não submetido ao juiz.

## Para fixar

1. Imprima, em vez do mapa, o instante em que cada célula foi contaminada. Isso é exatamente o `dist` da BFS multi-fonte.
2. Prove que o `dist` da BFS multi-fonte é min sobre as fontes s de d(s, v). Use o supervértice e o Teorema 3 do Lucchesi com S₀ = conjunto das fontes.
3. Passe para [[1883 - Fuga de Ayutthaya]].
