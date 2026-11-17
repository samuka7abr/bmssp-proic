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
---

# 1550 - Inversão

> **Técnica:** BFS em espaço de estados · **Listas:** B, C · **Enunciado:** [beecrowd 1550](https://judge.beecrowd.com/pt/problems/view/1550)

## O problema em uma frase

Um visor mostra A. Um botão soma 1; o outro inverte os dígitos (123 → 321, 150 → 51). Com 0 < A < B < 10000, qual o menor número de apertos para chegar a B? Até 500 casos.

## Modelando como grafo

- **Vértice:** o número no visor.
- **Aresta:** x → x + 1 e x → inverte(x). O grafo é **direcionado**: inverter 150 dá 51, mas inverter 51 dá 15.
- **Peso:** 1 por aperto.

Ninguém desenha esse grafo. Ele existe só na função que gera os dois vizinhos ([[05 - BFS em espaco de estados]]).

## Por que essa técnica (e não outra)

"Menor número de apertos", todos com o mesmo custo: BFS. Um guloso ("inverta sempre que aproximar de B") falha, porque às vezes você precisa **somar até um número cuja inversão** seja útil. Veja `100 → 301` no exemplo: 100 → 101 → 102 → 103 → 301, quatro apertos, e o caminho passa por 103 justamente porque inverter 103 dá 301.

**Quantos estados?** B < 10000, e nenhum aperto cria um número de 5 dígitos a partir de um de 4, exceto 9999 + 1 = 10000. Então os estados cabem em [1, 10000]. Testamos empiricamente: um teto de 2 000 000 dá exatamente as mesmas respostas que 10000 em 500 casos aleatórios.

## O algoritmo passo a passo

1. `dist` = −1 em [0, 10000]; `dist[A] = 0`.
2. BFS: vizinhos de u são u + 1 e inverte(u), descartando os maiores que 10000.
3. Ao retirar B, devolva `dist[B]`.

Rastreio de `808 → 909` (resposta 3):

| Camada | Estados |
|---|---|
| 0 | 808 |
| 1 | 809 (808 invertido é ele mesmo) |
| 2 | 810, 908 |
| 3 | 811, 18, 909 ← |

## Complexidade

O(10⁴) por caso, 500 casos: 5·10⁶. Tranquilo.

## Armadilhas

- Inversão com zeros: 150 → 51, não 051. A função `inverte` trata isso naturalmente porque trabalha com inteiro, não com string.
- Esquecer de testar o limite superior antes de indexar `dist`.
- Achar que o grafo é não direcionado.

## Código

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXV = 10000;

int inverte(int x){
    int r = 0;
    while (x > 0) {
        r = r * 10 + x % 10;
        x /= 10;
    }
    return r;
}

// estado = numero no visor; arestas = apertar "+1" ou "inverter"
int bfs(int a, int b){
    vector<int> dist(MAXV + 1, -1);
    queue<int> fila;
    dist[a] = 0;
    fila.push(a);

    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();

        if (u == b) return dist[u];

        int viz[2] = {u + 1, inverte(u)};
        for (int v : viz) {
            if (v > MAXV || dist[v] != -1) continue;

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

    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        cout << bfs(a, b) << "\n";
    }

    return 0;
}
```

Arquivos: `code/beecrowd/1550/sol.cpp` · rodar com `make test X=1550` dentro de `code/beecrowd/`.

Testado localmente com o exemplo do enunciado (`make test` deu OK); não submetido ao juiz.

## Para fixar

1. São até 500 casos. Daria para fazer **uma** BFS só e responder todos? (Dica: as origens variam e o grafo é direcionado. Pense no grafo reverso.)
2. Imprima a sequência de apertos usando o vetor de pais ([[02 - BFS classica]], seção 5).
3. Compare com [[1897 - Jogo Esperto]]: lá o teto do espaço de estados **não** é óbvio.
