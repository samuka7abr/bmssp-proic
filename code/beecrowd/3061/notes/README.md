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

# 3061 - Manchas de Pele

> **Técnica:** flood fill · **Listas:** C · **Enunciado:** [beecrowd 3061](https://judge.beecrowd.com/pt/problems/view/3061)

## O problema em uma frase

Uma imagem N×M de 0 e 1 representa a pele de um animal; cada região de 1 conectada nas 4 direções é uma mancha. Imprima quantas manchas existem.

## Modelando como grafo

- **Vértice:** pixel com valor 1.
- **Aresta:** dois pixels 1 vizinhos na horizontal ou vertical.
- **Pergunta:** quantos **componentes** tem esse grafo?

É a definição de componente do Lucchesi (cap. II, Teorema 2: subgrafo conexo maximal) e do Diestel (seção 1.4), contada.

## Por que essa técnica (e não outra)

Cada BFS a partir de um vértice não visitado pinta exatamente um componente (Lucchesi, Teorema 3 (ii) e Ex. 12). Então "número de BFS que precisei iniciar" = "número de componentes". Alternativa válida: união-busca (*union-find*), que você vai ver mais tarde no Kruskal. Para grid, BFS é o mais simples.

## O algoritmo passo a passo

1. Varra a imagem linha a linha.
2. Achou um 1 não visitado: some 1 ao contador e rode BFS a partir dele, marcando todos os 1 alcançáveis.
3. No fim, o contador é a resposta.

Mini-rastreio numa imagem 3×4:

```
1 1 0 1
0 1 0 1
1 0 0 0
```

Varredura: (0,0) inicia a mancha 1, que pinta (0,0), (0,1), (1,1). (0,3) inicia a mancha 2, que pinta (0,3), (1,3). (2,0) inicia a mancha 3. Resposta 3. Repare que (1,1) e (2,0) se tocam só na diagonal, e com 4 direções isso não liga.

## Complexidade

O(N·M): cada pixel entra na fila no máximo uma vez e cada BFS só toca o próprio componente.

## Armadilhas

- 4 ou 8 vizinhos? Aqui são 4. Ler errado a vizinhança muda a resposta.
- Marcar visitado **ao enfileirar**, senão o mesmo pixel entra várias vezes.
- A entrada vem com espaços entre os dígitos; `cin >> int` resolve.

## Código

```cpp
#include <bits/stdc++.h>
using namespace std;

const int dl[4] = {1, -1, 0, 0};
const int dc[4] = {0, 0, 1, -1};

int n, m;
vector<vector<int>> img;
vector<vector<bool>> vis;

void bfs(int li, int ci){
    queue<pair<int, int>> fila;

    // marca ao inserir: cada pixel preto entra na fila no maximo uma vez
    vis[li][ci] = true;
    fila.push(make_pair(li, ci));

    while (!fila.empty()) {
        int l = fila.front().first;
        int c = fila.front().second;
        fila.pop();

        for (int i = 0; i < 4; i++) {
            int nl = l + dl[i];
            int nc = c + dc[i];

            if (nl < 0 || nl >= n || nc < 0 || nc >= m) continue;
            if (img[nl][nc] == 0 || vis[nl][nc]) continue;

            vis[nl][nc] = true;
            fila.push(make_pair(nl, nc));
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;
    img.assign(n, vector<int>(m));
    vis.assign(n, vector<bool>(m, false));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> img[i][j];

    int manchas = 0;
    for (int l = 0; l < n; l++) {
        for (int c = 0; c < m; c++) {
            if (img[l][c] == 0 || vis[l][c]) continue;
            manchas++;
            bfs(l, c);
        }
    }

    cout << manchas << "\n";

    return 0;
}
```

Arquivos: `code/beecrowd/3061/sol.cpp` · rodar com `make test X=3061` dentro de `code/beecrowd/`.

Testado localmente com o exemplo do enunciado (`make test` deu OK); não submetido ao juiz.

## Para fixar

1. Imprima também o tamanho da maior mancha. Muda uma linha.
2. E com 8 vizinhos? Quantas manchas tem o exemplo nesse caso?
3. Passe para [[1907 - Coloracao de Cenarios de Jogos]], que é o mesmo problema num grid bem maior.
