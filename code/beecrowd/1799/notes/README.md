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
  - "[[02 - BFS classica]]"
---

# 1799 - O Rato no Labirinto

> **Técnica:** duas BFS somadas · **Listas:** B · **Enunciado:** [beecrowd 1799](https://judge.beecrowd.com/pt/problems/view/1799)

## O problema em uma frase

Um labirinto é dado como P pontos e L ligações entre pontos com nome (`Entrada`, `Saida`, `*` para o queijo e outros nomes quaisquer). O rato sai da `Entrada`, precisa passar pelo queijo e depois chegar à `Saida`. Imprima o menor número de passos.

## Modelando como grafo

- **Vértice:** cada ponto. Os nomes são strings, então o primeiro trabalho é dar um número a cada nome (`map<string, int>`).
- **Aresta:** cada ligação, nos dois sentidos.
- **Peso:** 1 por ligação.

Este é o único problema da lista em que o grafo vem **explícito** como lista de arestas. Ele treina a parte do [[01 - Grafos e representacao]] que os grids escondem: montar a lista de adjacência.

## Por que essa técnica (e não outra)

Um caminho Entrada → queijo → Saída é a concatenação de um caminho Entrada → queijo com um caminho queijo → Saída. As duas metades não interagem, porque o rato pode repetir pontos. Então:

menor total = d(Entrada, queijo) + d(queijo, Saída)

e cada parcela é uma BFS. Repare no argumento: ele usa a propriedade de **subestrutura ótima** (subcaminho de caminho mínimo é mínimo, Lema 24.1 do Cormen na 3ª ed.). Se o enunciado proibisse repetir pontos, o argumento quebraria, e o problema viraria um caso de caminho simples por um vértice obrigatório, muito mais difícil.

Como o grafo é não direcionado, d(queijo, Saída) = d(Saída, queijo), então dá para fazer as duas BFS a partir do queijo e somar `dist[Entrada] + dist[Saida]`. O código usa duas BFS (da Entrada e do queijo) porque assim a ideia fica mais visível.

## O algoritmo passo a passo

1. Leia as ligações; dê um id a cada nome novo; adicione a aresta nos dois sentidos.
2. BFS da `Entrada` → `daEntrada`.
3. BFS do `*` → `doQueijo`.
4. Imprima `daEntrada[queijo] + doQueijo[saida]`.

Rastreio do exemplo (Entrada–A, A–B, B–C, C–\*, A–D, D–\*, \*–E, E–Saida, B–Saida):

| Ponto | da Entrada | do queijo |
|---|---|---|
| Entrada | 0 | 3 |
| A | 1 | 2 |
| B, D | 2 | 2 (B), 1 (D) |
| \* | 3 | 0 |
| Saida | 3 | 2 |

Resposta: 3 + 2 = 5. Repare que o caminho direto Entrada → A → B → Saida tem só 3 passos, mas não passa pelo queijo.

## Complexidade

Duas BFS: O(P + L). Mais O(L log P) do `map` para converter nomes.

## Armadilhas

- Os nomes especiais são exatamente `Entrada`, `Saida` (sem acento) e `*`.
- A entrada tem vários casos até o fim do arquivo: o `map` e o grafo precisam ser recriados a cada caso.
- Contar passos (arestas), não pontos visitados.

## Código

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> bfs(const vector<vector<int>>& grafo, int origem){
    vector<int> dist(grafo.size(), -1);
    queue<int> fila;

    dist[origem] = 0;
    fila.push(origem);

    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();

        for (int v : grafo[u]) {
            if (dist[v] != -1) continue;

            dist[v] = dist[u] + 1;
            fila.push(v);
        }
    }

    return dist;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int pontos, ligacoes;
    while (cin >> pontos >> ligacoes) {
        map<string, int> id;
        vector<vector<int>> grafo;

        auto pegaId = [&](const string& nome) -> int {
            auto it = id.find(nome);
            if (it != id.end()) return it->second;

            int novo = grafo.size();
            id[nome] = novo;
            grafo.emplace_back();
            return novo;
        };

        for (int i = 0; i < ligacoes; i++) {
            string a, b;
            cin >> a >> b;

            int u = pegaId(a);
            int v = pegaId(b);
            grafo[u].push_back(v);
            grafo[v].push_back(u);
        }

        int entrada = pegaId("Entrada");
        int queijo = pegaId("*");
        int saida = pegaId("Saida");

        // o melhor caminho que passa pelo queijo e a soma de dois caminhos minimos independentes
        vector<int> daEntrada = bfs(grafo, entrada);
        vector<int> doQueijo = bfs(grafo, queijo);

        cout << daEntrada[queijo] + doQueijo[saida] << "\n";
    }

    return 0;
}
```

Arquivos: `code/beecrowd/1799/sol.cpp` · rodar com `make test X=1799` dentro de `code/beecrowd/`.

Testado localmente com o exemplo do enunciado (`make test` deu OK); não submetido ao juiz.

## Para fixar

1. Reescreva com uma BFS só, a partir do queijo.
2. E se fossem **dois** queijos obrigatórios, em qualquer ordem? Quantas BFS você precisa, e quantas ordens testar?
3. Compare com [[1883 - Fuga de Ayutthaya]]: lá também há duas BFS, mas a segunda **depende** do resultado da primeira. Por que aqui elas são independentes?
