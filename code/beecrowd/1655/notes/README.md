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

# 1655 - 106 Milhas Para Chicago

> **Técnica:** Dijkstra/Floyd multiplicativo · **Listas:** A · **Enunciado:** [beecrowd 1655](https://judge.beecrowd.com/pt/problems/view/1655) (original: University of Ulm Local Contest 2005, também SPOJ CHICAGO)

## O problema em uma frase

n interseções (até 100) e m ruas de mão dupla; cada rua tem probabilidade p% de ser atravessada sem ser pego. Imprima a maior probabilidade de ir da interseção 1 à n, em porcentagem com 6 casas, seguida de `percent`. Vários casos até uma linha com `0`.

## Modelando como grafo

- **Vértice:** interseção.
- **Aresta:** rua, nos dois sentidos, com peso p/100 ∈ (0, 1].
- **Valor de um caminho:** o **produto** dos pesos, porque as ruas são eventos independentes.
- **Pergunta:** o caminho de 1 a n com **maior** produto.

## Por que essa técnica (e não outra)

Parece diferente de tudo o que veio antes (máximo em vez de mínimo, produto em vez de soma), mas é o mesmo problema disfarçado. Há duas formas de ver:

**1. Trocar a álgebra.** Floyd e Dijkstra só precisam de duas coisas da operação: que combinar caminhos seja associativo e que **estender um caminho nunca o torne melhor**. Com soma de pesos não negativos, estender nunca diminui. Com produto de valores em [0, 1], estender nunca aumenta. Então troque (min, +) por (max, ×) e os algoritmos continuam corretos. A prova do Teorema 24.6 do Cormen (correção do Dijkstra) passa sem mudança.

**2. Logaritmo.** max Π pᵢ = max Σ log pᵢ = min Σ (−log pᵢ). Como pᵢ ∈ (0, 1], −log pᵢ ≥ 0. Vira um caminho mínimo comum com pesos não negativos.

Com n ≤ 100, Floyd custa 10⁶ por caso e é o mais curto de escrever.

## O algoritmo passo a passo

1. `prob[i][i] = 1`, `prob[a][b] = prob[b][a] = p/100`, o resto 0.
2. Floyd com `prob[i][j] = max(prob[i][j], prob[i][k] * prob[k][j])`.
3. Imprima `prob[0][n-1] * 100` com 6 casas e ` percent`.

Rastreio do exemplo: o caminho 1 → 4 → 3 → 5 tem 0,85 × 0,90 × 0,80 = 0,612, ou seja, **61.200000 percent**. Compare com 1 → 3 → 5: 0,70 × 0,80 = 0,56. O caminho com mais ruas ganha, porque cada rua é mais segura. É o mesmo fenômeno de um caminho com mais arestas mas menor peso total.

## Complexidade

O(n³) por caso.

## Armadilhas

- Inicializar `prob[i][i]` com 0 em vez de 1 (o caminho vazio tem probabilidade 1).
- Esquecer o sentido duplo das ruas.
- Formato: a palavra é `percent`, em inglês, mesmo no beecrowd em português.
- `float` em vez de `double`: o produto de várias probabilidades perde precisão.

## Código

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
double d[MAXN][MAXN];

void floydWarshall(int n) {
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                d[i][j] = max(d[i][j], d[i][k] * d[k][j]);
}

int main() {
    int n, m;
    while (scanf("%d", &n) == 1 && n != 0) {
        scanf("%d", &m);

        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                d[i][j] = (i == j) ? 1.0 : 0.0;

        for (int i = 0; i < m; i++) {
            int a, b, p;
            scanf("%d %d %d", &a, &b, &p);
            d[a][b] = d[b][a] = p / 100.0;
        }

        floydWarshall(n);
        printf("%.6f percent\n", d[1][n] * 100.0);
    }
    return 0;
}
```

Arquivos: `code/beecrowd/1655/sol.cpp` · rodar com `make test X=1655` dentro de `code/beecrowd/`.

Testado com o exemplo do enunciado e com os **dados oficiais completos do juiz** do Ulm Local Contest 2005 (80 casos, `chicago.in`/`chicago.out` do repositório público [qincaicai/acm](https://github.com/qincaicai/acm)): saída idêntica byte a byte. Não submetido ao beecrowd.

## Para fixar

1. Reescreva com Dijkstra usando a álgebra (max, ×): a fila de prioridade vira um max-heap.
2. Reescreva com −log p e Dijkstra comum. Converta de volta com exp no final. A saída bate nas 6 casas?
3. Por que nenhuma das duas formas funcionaria se algum p pudesse ser maior que 100%? Relacione com pesos negativos no Dijkstra.
