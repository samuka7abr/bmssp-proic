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

# 1100 - Movimentos do Cavalo

> **Técnica:** BFS em grid · **Listas:** A, B, C · **Enunciado:** [beecrowd 1100](https://judge.beecrowd.com/pt/problems/view/1100)

## O problema em uma frase

Dadas duas casas de um tabuleiro de xadrez 8×8 (como `e2` e `e4`), diga o menor número de movimentos de cavalo para ir de uma à outra. A entrada tem vários pares até o fim do arquivo.

## Modelando como grafo

- **Vértice:** cada uma das 64 casas.
- **Aresta:** u–v quando um cavalo salta de u para v. O salto é simétrico, então o grafo é não direcionado.
- **Peso:** todos iguais (1 movimento).
- **Explícito ou implícito:** implícito. Ninguém monta a lista de adjacência; os 8 vetores `dl`/`dc` geram os vizinhos.

Tamanho: 64 vértices, no máximo 8 arestas por vértice. É o menor grafo do guia, e por isso o melhor para fazer o rastreio à mão.

## Por que essa técnica (e não outra)

Pesos todos iguais e pergunta de "menor número de passos": é exatamente o caso do Teorema 3 do Lucchesi e do Teorema 22.5 do Cormen ([[02 - BFS classica]]). DFS acharia **um** caminho, não o menor. Uma fórmula fechada para a distância do cavalo existe, mas tem vários casos especiais perto das bordas e cantos; a BFS não tem caso especial nenhum.

## O algoritmo passo a passo

1. Converta a notação: coluna = letra − `'a'`, linha = dígito − `'1'`. Repare que a notação de xadrez é (coluna, linha), e a matriz é `[linha][coluna]`.
2. `dist` = −1 em todas as casas; `dist[origem] = 0`; enfileire a origem.
3. Retire u da fila. Se u é o destino, devolva `dist[u]`.
4. Para cada um dos 8 saltos, se a casa nova está no tabuleiro e tem `dist == -1`, marque `dist[v] = dist[u] + 1` e enfileire.

**Rastreio de `a1` para `b3`** (que deveria dar 1):

| Passo | Retira | Enfileira (dist) |
|---|---|---|
| 0 | | a1 (0) |
| 1 | a1 | b3 (1), c2 (1) |
| 2 | b3 | é o destino, devolve 1 |

Agora faça você `a1` → `h8` no papel até a camada 2 e veja o tamanho das camadas crescer: 1, 2, 9, ... É a mesma conta da prova da Proposição 1.3.3 do Diestel.

## Complexidade

O(64 · 8) por consulta. Constante, na prática.

## Armadilhas

- Trocar linha e coluna na conversão de `e2`.
- `f6 f6` está no exemplo: origem igual ao destino, resposta 0. O código trata isso porque testa o destino logo ao retirar da fila.
- Recriar `dist` a cada consulta. Aqui ele é local à função `bfs`, então o reset é automático.

## Código

```cpp
#include <bits/stdc++.h>
using namespace std;

const int dl[8] = {1, 1, -1, -1, 2, 2, -2, -2};
const int dc[8] = {2, -2, 2, -2, 1, -1, 1, -1};

int bfs(int li, int ci, int lf, int cf){
    int dist[8][8];
    fill(&dist[0][0], &dist[0][0] + 64, -1);

    queue<pair<int, int>> fila;
    dist[li][ci] = 0;

    fila.push(make_pair(li, ci));

    while (!fila.empty()) {
        int l = fila.front().first;
        int c = fila.front().second;
        fila.pop();

        if (l == lf && c == cf) return dist[l][c];

        for (int i = 0; i < 8; i++) {
            int nl = l + dl[i];
            int nc = c + dc[i];

            if (nl < 0 || nl >= 8 || nc < 0 || nc >= 8) continue;
            if (dist[nl][nc] != -1) continue;

            dist[nl][nc] = dist[l][c] + 1;
            fila.push(make_pair(nl, nc));
        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    string origem, destino;
    while (cin >> origem >> destino) {
        int ci = origem[0] - 'a';
        int li = origem[1] - '1';
        int cf = destino[0] - 'a';
        int lf = destino[1] - '1';

        int n = bfs(li, ci, lf, cf);

        cout << "To get from " << origem << " to " << destino
             << " takes " << n << " knight moves.\n";
    }

    return 0;
}
```

Arquivos: `code/beecrowd/1100/sol.cpp` · rodar com `make test X=1100` dentro de `code/beecrowd/`.

Testado localmente com o exemplo do enunciado (`make test` deu OK); não submetido ao juiz.

## Para fixar

1. Se você tivesse milhares de consultas, valeria a pena rodar uma BFS a partir de **cada** casa uma vez só e guardar uma tabela 64×64? Quanto custaria?
2. Qual é a maior distância possível entre duas casas (o diâmetro deste grafo, no sentido do Diestel 1.3)? Descubra rodando a BFS de todas as casas.
3. Generalize para três dimensões: [[1952 - O Cavalo no Xadrez 3D]].
