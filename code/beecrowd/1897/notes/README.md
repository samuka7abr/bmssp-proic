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
  - "[[05 - BFS em espaco de estados]]"
  - "[[1550 - Inversao]]"
---

# 1897 - Jogo Esperto

> **Técnica:** BFS em grafo implícito · **Listas:** C · **Enunciado:** [beecrowd 1897](https://judge.beecrowd.com/pt/problems/view/1897)

## O problema em uma frase

Dados N e M (0 ≤ N, M ≤ 10000), qual o menor número de operações para transformar N em M, usando ×2, ×3, ÷2, ÷3 (divisão inteira), +7 e −7?

## Modelando como grafo

- **Vértice:** um inteiro.
- **Aresta:** as 6 operações. Direcionado (÷2 desfaz ×2, mas ×2 não desfaz ÷2 de um ímpar).
- **Peso:** 1 por operação.

## Por que essa técnica (e não outra)

Mesmo raciocínio do [[1550 - Inversao]]: menor número de passos com custo uniforme → BFS no espaço de estados.

A parte difícil é **o teto**. As operações ×2, ×3 e +7 crescem sem limite, então o vetor `dist` precisa de um tamanho máximo, e um caminho ótimo pode passar **acima de M**. Exemplo do enunciado: 84 → 63 em 3 passos.

A versão que um dos subagentes escreveu usava teto 10000, igual ao limite da entrada. Testamos contra um teto de 200 000 em 3000 pares aleatórios: **149 respostas diferiam** (por exemplo, 2201 → 9325 dá 10 com teto folgado e 11 com teto 10000). Depois comparamos 200 000 contra 2 000 000 em 800 pares, sem nenhuma diferença. O código final usa 200 000.

Isso não é uma prova de que 200 000 basta, é evidência. A pergunta teórica ("qual o maior valor que um caminho ótimo pode visitar?") é um bom exercício.

## O algoritmo passo a passo

1. `dist` = −1 em [0, 200000]; `dist[N] = 0`.
2. BFS com os 6 vizinhos, descartando negativos e os acima do teto.
3. Ao retirar M, devolva `dist[M]`.

Rastreio de `45 → 15` (resposta 1): os vizinhos de 45 são 90, 135, 22, **15**, 52, 38. O 15 está na camada 1.

Rastreio de `10 → 15` (resposta 2): camada 1 = {20, 30, 5, 3, 17}; o −7 dá 3, que já apareceu como 10÷3. Camada 2 inclui 5×3 = **15**.

## Complexidade

O(teto · 6) no pior caso por consulta: ~1,2·10⁶.

## Armadilhas

- **Teto apertado demais**, como explicado acima.
- N = M: resposta 0.
- −7 pode ficar negativo; descarte.
- A entrada pode ter mais de uma linha; o código lê até o fim do arquivo.

## Código

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXV = 200000;

// estado = o numero atual (divisao inteira); teto folgado porque um caminho otimo pode passar acima de M
int bfs(int n, int m){
    vector<int> dist(MAXV + 1, -1);
    queue<int> fila;
    dist[n] = 0;
    fila.push(n);

    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();

        if (u == m) return dist[u];

        int viz[6] = {u * 2, u * 3, u / 2, u / 3, u + 7, u - 7};
        for (int v : viz) {
            if (v < 0 || v > MAXV || dist[v] != -1) continue;

            dist[v] = dist[u] + 1;
            fila.push(v);
        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    while (cin >> n >> m) {
        cout << bfs(n, m) << "\n";
    }

    return 0;
}
```

Arquivos: `code/beecrowd/1897/sol.cpp` · rodar com `make test X=1897` dentro de `code/beecrowd/`.

Testado localmente com os três exemplos do enunciado (2, 1 e 3) e com a comparação de tetos descrita acima; não submetido ao juiz.

## Para fixar

1. Encontre um par (N, M) em que o caminho ótimo passa acima de 20000. O vetor de pais ajuda.
2. Tente provar um teto: se um caminho ótimo passa por um valor muito grande, dá para trocar um trecho dele por outro mais curto?
3. Faça a BFS **bidirecional**: uma a partir de N com as operações, outra a partir de M com as operações inversas. Quais são as inversas de ÷2 com divisão inteira?
