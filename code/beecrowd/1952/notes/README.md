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
  - "[[1100 - Movimentos do Cavalo]]"
---

# 1952 - O Cavalo no Xadrez 3D

> **Técnica:** BFS em 3D · **Listas:** B, C · **Enunciado:** [beecrowd 1952](https://judge.beecrowd.com/pt/problems/view/1952)

## O problema em uma frase

São L tabuleiros N×M empilhados (8 ≤ N, M ≤ 100, 3 ≤ L ≤ 100). Um cavalo 3D salta de (i₁, j₁, k₁) para (i₂, j₂, k₂) quando {|Δi|, |Δj|, |Δk|} = {0, 1, 2}. Dadas a origem e o destino (coordenadas a partir de 1), imprima o menor número de saltos. É um caso só por entrada.

## Modelando como grafo

- **Vértice:** cada casa (i, j, k). No pior caso 100·100·100 = 10⁶ vértices.
- **Aresta:** um salto válido. A regra é simétrica, então o grafo é não direcionado.
- **Quantos saltos?** Escolha qual coordenada fica parada (3 jeitos), qual das outras duas anda 1 e qual anda 2 (2 jeitos) e os dois sinais (4 jeitos): 3 · 2 · 4 = **24 vizinhos**.

O código não escreve os 24 à mão: gera todos os (Δi, Δj, Δk) em [−2, 2]³ e guarda os que, em módulo e ordenados, dão {0, 1, 2}. Assim não dá para esquecer nenhum.

## Por que essa técnica (e não outra)

É o [[1100 - Movimentos do Cavalo]] com uma coordenada a mais. Mesma pergunta (menor número de passos), mesmos pesos (todos 1), então BFS. A única coisa que muda é o tamanho: 10⁶ vértices × 24 arestas = 2,4·10⁷ operações, que cabe com folga no limite de 1 s.

## O algoritmo passo a passo

1. Leia N, M, L e as coordenadas, e subtraia 1 de cada uma (o enunciado numera a partir de 1).
2. Achate (i, j, k) num inteiro: `id = (k·N + i)·M + j`. Assim `dist` é um `vector<int>` simples de tamanho N·M·L.
3. BFS normal com os 24 saltos; pare ao retirar o destino.

Rastreio do exemplo, de (5, 5, 1) para (3, 4, 2) num jogo 8×8×3:

- **Distância 1?** Δ = (−2, −1, +1). As três coordenadas mudam, e um salto sempre deixa uma parada. Não é vizinho.
- **Distância 2.** Na camada 1 está (5, 3, 2), com Δ = (0, −2, +1). De lá, (3, 4, 2) tem Δ = (−2, +1, 0), que é um salto. Resposta: 2.

Tente achar outros caminhos de 2 saltos à mão e você vai errar algumas vezes, porque são 24 vizinhos por casa. É por isso que você deixa a BFS procurar em vez de raciocinar caso a caso.

## Complexidade

O(N·M·L · 24) tempo e O(N·M·L) memória (4 MB para o `dist`).

## Armadilhas

- Esquecer de converter de 1-indexado para 0-indexado.
- Ordem errada no achatamento do índice. Use uma função `id(i, j, k)` e nunca escreva a conta duas vezes.
- `queue<array<int,3>>` com 10⁶ elementos ainda cabe (12 MB), mas guardar o `id` em vez da tripla economiza memória.

## Código

```cpp
#include <bits/stdc++.h>
using namespace std;

// os 24 saltos: {|di|, |dj|, |dk|} = {0, 1, 2} em qualquer ordem e com qualquer sinal
vector<array<int, 3>> saltos(){
    vector<array<int, 3>> s;
    for (int di = -2; di <= 2; di++)
        for (int dj = -2; dj <= 2; dj++)
            for (int dk = -2; dk <= 2; dk++) {
                array<int, 3> a = {abs(di), abs(dj), abs(dk)};
                sort(a.begin(), a.end());
                if (a[0] == 0 && a[1] == 1 && a[2] == 2) s.push_back({di, dj, dk});
            }
    return s;
}

int N, M, L;

int id(int i, int j, int k){
    return (k * N + i) * M + j;
}

int bfs(int i1, int j1, int k1, int i2, int j2, int k2){
    const vector<array<int, 3>> mov = saltos();
    vector<int> dist(N * M * L, -1);
    queue<array<int, 3>> fila;

    dist[id(i1, j1, k1)] = 0;
    fila.push({i1, j1, k1});

    while (!fila.empty()) {
        auto [i, j, k] = fila.front();
        fila.pop();

        if (i == i2 && j == j2 && k == k2) return dist[id(i, j, k)];

        for (const array<int, 3>& d : mov) {
            int ni = i + d[0], nj = j + d[1], nk = k + d[2];

            if (ni < 0 || ni >= N || nj < 0 || nj >= M || nk < 0 || nk >= L) continue;
            if (dist[id(ni, nj, nk)] != -1) continue;

            dist[id(ni, nj, nk)] = dist[id(i, j, k)] + 1;
            fila.push({ni, nj, nk});
        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> L;

    int i1, j1, k1, i2, j2, k2;
    cin >> i1 >> j1 >> k1 >> i2 >> j2 >> k2;

    cout << bfs(i1 - 1, j1 - 1, k1 - 1, i2 - 1, j2 - 1, k2 - 1) << "\n";

    return 0;
}
```

Arquivos: `code/beecrowd/1952/sol.cpp` · rodar com `make test X=1952` dentro de `code/beecrowd/`.

Testado localmente com o exemplo do enunciado (`make test` deu OK); não submetido ao juiz.

## Para fixar

1. O enunciado não diz o que imprimir se o destino for inalcançável. Rode a BFS a partir de (1, 1, 1) num jogo 8×8×3 e conte quantas casas recebem distância. O grafo é conexo nessas dimensões?
2. Todo salto soma ±1 e ±2 a duas coordenadas, então muda a paridade de i + j + k. Conclua que o grafo é **bipartido** (Diestel, Proposição 1.6.1, e Lucchesi, cap. I) e que a distância entre duas casas tem a mesma paridade que a diferença das somas das coordenadas. No exemplo, 11 e 9 têm a mesma paridade, e a resposta 2 é par.
3. Troque a fila por uma BFS bidirecional (uma a partir da origem, outra do destino, até as fronteiras se encontrarem). Quanto ela economiza?
