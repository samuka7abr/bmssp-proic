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
  - "[[07 - Componentes, flood fill e diametro]]"
---

# 1621 - Labirinto

> **Técnica:** BFS dupla (diâmetro) · **Listas:** A, B, C · **Enunciado:** [beecrowd 1621](https://judge.beecrowd.com/pt/problems/view/1621)

## O problema em uma frase

Num labirinto N×M (5 ≤ N, M ≤ 500) de `.` e `#`, em que **só existe um caminho entre quaisquer dois espaços vazios**, escolha a entrada e a saída para que a distância entre elas seja a maior possível. Imprima essa distância. Vários casos, até `0 0`.

## Modelando como grafo

- **Vértice:** célula `.` (até 250 000).
- **Aresta:** duas células `.` vizinhas nas 4 direções.
- **A frase-chave:** "só há um caminho entre quaisquer dois espaços vazios". Pelo **Teorema 1.5.1 (ii)** do Diestel, isso é exatamente a definição de **árvore**.
- **Pergunta:** a maior distância entre dois vértices, ou seja, o **diâmetro** (Diestel, seção 1.3).

## Por que essa técnica (e não outra)

O jeito ingênuo é rodar BFS de cada célula e pegar o máximo: 250 000 BFS de 250 000 células, ~6·10¹⁰ operações. Não passa.

Numa árvore, duas BFS bastam ([[07 - Componentes, flood fill e diametro]], seção 4):

1. BFS de uma célula qualquer u; seja x a mais distante.
2. BFS de x; seja y a mais distante. A resposta é d(x, y).

O fato que sustenta isso: **numa árvore, o vértice mais distante de qualquer u é ponta de algum caminho mais longo.** A prova está esboçada no módulo 07 e usa a unicidade do caminho (Diestel 1.5.1). O Ex. 9 do cap. II do Lucchesi (dois caminhos de comprimento máximo num grafo conexo não são disjuntos) é o aquecimento para essa prova.

Sem a garantia de árvore, a técnica pode errar. Por isso a frase do enunciado não é decoração: é ela que libera o algoritmo.

## O algoritmo passo a passo

1. Ache qualquer célula `.`.
2. BFS a partir dela; guarde a célula `x` com maior `dist`.
3. BFS a partir de `x`; a maior `dist` é a resposta.

Rastreio do primeiro exemplo:

```
.#...
...##
.#..#
.##..
#####
```

Partindo de (3,4), a célula vazia mais abaixo e à direita, a mais distante é (3,0), a 8 passos: (3,4) → (3,3) → (2,3) → (2,2) → (1,2) → (1,1) → (1,0) → (2,0) → (3,0). A segunda BFS, de (3,0), alcança no máximo 8 de novo. Resposta 8. O segundo exemplo é uma serpentina: um caminho só, sem bifurcação, com 17 células, então o diâmetro é 16.

## Complexidade

Duas BFS: O(N·M) por caso.

## Armadilhas

- Rodar a primeira BFS de uma parede.
- Esquecer de recriar `dist` entre a primeira e a segunda BFS. O código faz isso com `dist.assign` dentro da função.
- Achar que "diâmetro com duas BFS" vale em qualquer grafo. Não vale; só em árvores.

## Código

```cpp
#include <bits/stdc++.h>
using namespace std;

const int dl[4] = {1, -1, 0, 0};
const int dc[4] = {0, 0, 1, -1};

int n, m;
vector<string> lab;
vector<vector<int>> dist;

// devolve a celula mais distante de (li, ci); dist fica preenchida
pair<int, int> bfs(int li, int ci){
    dist.assign(n, vector<int>(m, -1));
    queue<pair<int, int>> fila;
    dist[li][ci] = 0;
    fila.push(make_pair(li, ci));

    pair<int, int> longe = make_pair(li, ci);
    while (!fila.empty()) {
        int l = fila.front().first;
        int c = fila.front().second;
        fila.pop();

        if (dist[l][c] > dist[longe.first][longe.second]) longe = make_pair(l, c);

        for (int i = 0; i < 4; i++) {
            int nl = l + dl[i];
            int nc = c + dc[i];

            if (nl < 0 || nl >= n || nc < 0 || nc >= m) continue;
            if (lab[nl][nc] == '#' || dist[nl][nc] != -1) continue;

            dist[nl][nc] = dist[l][c] + 1;
            fila.push(make_pair(nl, nc));
        }
    }

    return longe;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> n >> m && (n || m)) {
        lab.assign(n, "");
        for (int i = 0; i < n; i++) cin >> lab[i];

        pair<int, int> qualquer;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (lab[i][j] == '.') qualquer = make_pair(i, j);

        // o labirinto e uma arvore: a celula mais longe de qualquer uma e ponta de um diametro
        pair<int, int> x = bfs(qualquer.first, qualquer.second);
        pair<int, int> y = bfs(x.first, x.second);

        cout << dist[y.first][y.second] << "\n";
    }

    return 0;
}
```

Arquivos: `code/beecrowd/1621/sol.cpp` · rodar com `make test X=1621` dentro de `code/beecrowd/`.

Testado localmente com os dois exemplos do enunciado (8 e 16); não submetido ao juiz.

## Para fixar

1. Monte um labirinto **com ciclo** em que as duas BFS dão uma resposta menor que o diâmetro verdadeiro.
2. Use o vetor de pais da segunda BFS ([[02 - BFS classica]], seção 5) para imprimir o caminho x–y e achar o **centro** da árvore (Diestel 1.3: rad ≤ diam ≤ 2·rad).
3. Por que a resposta nunca passa de N·M − 1? Ligue com o item (ii) do Teorema 3 do Lucchesi.
