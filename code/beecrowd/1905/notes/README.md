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
  - "[[03 - BFS em grid e grafos implicitos]]"
---

# 1905 - Polícia e Ladrão

> **Técnica:** alcançabilidade em grid · **Listas:** C · **Enunciado:** [beecrowd 1905](https://judge.beecrowd.com/pt/problems/view/1905)

## O problema em uma frase

Num labirinto 5×5 de 0 (livre) e 1 (parede), a polícia sai do canto superior esquerdo e precisa chegar ao canto inferior direito andando em 4 direções. Imprima `COPS` se ela consegue e `ROBBERS` se não. A entrada começa com o número T de labirintos.

## Modelando como grafo

- **Vértice:** célula livre (no máximo 25).
- **Aresta:** duas células livres vizinhas na horizontal ou na vertical.
- **Pergunta:** (0,0) e (4,4) estão no mesmo **componente**?

Aqui não importa a distância, só se existe caminho. É a pergunta "u e v são ligados?" do Lucchesi (cap. II, seção 1).

## Por que essa técnica (e não outra)

Qualquer busca resolve: BFS, DFS, até união-busca. Escolhemos BFS para manter um molde só no guia. O Lucchesi, no item (ii) do Teorema 3 e no Ex. 12, mostra que as camadas a partir de u cobrem exatamente o componente de u. Então basta ver se o destino aparece em alguma camada.

## O algoritmo passo a passo

1. Se (0,0) ou (4,4) é parede, já é `ROBBERS`.
2. BFS a partir de (0,0) nas 4 direções, só por células 0.
3. Se a BFS retirar (4,4) da fila, `COPS`. Se a fila esvaziar antes, `ROBBERS`.

Rastreio do primeiro labirinto do exemplo, com as camadas marcadas (`#` = parede):

```
0 1 2 3 #
# # 3 4 #
8 # 4 5 6
7 6 5 # #
# # 6 7 8
```

(4,4) recebe distância 8, então `COPS`. O segundo labirinto só troca (3,2) por parede, e isso basta para partir o grafo em três componentes: o da origem (as linhas 0 a 2 à direita), o bolsão {(2,0), (3,0), (3,1)} e o pedaço {(4,2), (4,3), (4,4)}. O destino fica fora do componente da origem, então a resposta é `ROBBERS`. Desenhe as camadas dos dois labirintos e veja onde a onda para.

## Complexidade

O(25) por labirinto.

## Armadilhas

- Esquecer de testar se a origem ou o destino são parede.
- A entrada tem linhas em branco entre os labirintos. Com `cin >> int` elas são ignoradas sozinhas; com `getline` você teria de tratar.

## Código

```cpp
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
```

Arquivos: `code/beecrowd/1905/sol.cpp` · rodar com `make test X=1905` dentro de `code/beecrowd/`.

Testado localmente com o exemplo do enunciado (`make test` deu OK); não submetido ao juiz.

## Para fixar

1. Reescreva com DFS recursiva. Em 5×5 não há risco de estourar a pilha. Por que em [[1907 - Coloracao de Cenarios de Jogos]] há?
2. E se a polícia pudesse andar na diagonal? Só muda `dl`/`dc`.
3. E se a pergunta fosse "quantos passos no mínimo"? O código já calcula: devolva `dist` em vez de `true`.
