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

# 1910 - Ajude Clotilde

> **Técnica:** BFS em estados com proibidos · **Listas:** C · **Enunciado:** [beecrowd 1910](https://judge.beecrowd.com/pt/problems/view/1910)

## O problema em uma frase

O controle da TV tem os botões +1, −1, ×2, ×3 e ÷2 (só em canal par). Os canais vão de 1 a 10⁵ e K canais (até 100) são proibidos. Qual o menor número de cliques do canal O ao canal D, ou −1 se for impossível? Vários casos até `0 0 0`.

## Modelando como grafo

- **Vértice:** canal em [1, 10⁵], menos os proibidos.
- **Aresta:** os 5 botões, quando o resultado continua em [1, 10⁵].
- **Peso:** 1 por clique.

Aqui o teto vem **de graça** do enunciado ("não existe canal menor igual a 0 ou maior que 10⁵"), ao contrário do [[1897 - Jogo Esperto]].

## Por que essa técnica (e não outra)

Menor número de cliques, custo uniforme: BFS. A novidade são os canais proibidos, e o truque é tratá-los como **já visitados** antes de começar. A BFS nunca enfileira um vértice já visitado, então nunca passa por um proibido, e não é preciso nenhum `if` novo no laço.

Em linguagem de grafo: você está rodando a BFS em G − Z, o grafo sem os vértices proibidos. É a notação G − Z que o Lucchesi usa desde o cap. I.

## O algoritmo passo a passo

1. `dist` = −1 em [1, 10⁵]; marque `dist[p] = -2` para cada proibido.
2. `dist[O] = 0`; BFS com os 5 vizinhos.
3. Ao retirar D, devolva `dist[D]`. Se a fila esvaziar, −1.

Rastreio do primeiro caso, `3 → 8` com 4 e 5 proibidos:

| Camada | Estados (proibidos não entram) |
|---|---|
| 0 | 3 |
| 1 | 2, 6, 9 (o +1 daria 4, proibido; ÷2 não vale, 3 é ímpar) |
| 2 | 1, 7, 12, 18, **8**, 10, 27 |

De 2: +1 = 3 e ×3 = 6 já vistos, ×2 = 4 proibido, −1 e ÷2 dão 1. De 6: 7, 12, 18 (5 proibido, 3 visto). De 9: −1 = **8**, +1 = 10, ×3 = 27. O 8 aparece na camada 2: resposta 2.

## Complexidade

O(10⁵ · 5) por caso.

## Armadilhas

- ÷2 só em canal par.
- Testar os limites [1, 10⁵] **antes** de indexar `dist`.
- K = 0: a segunda linha do caso fica vazia. Com `cin >> int` ela é simplesmente pulada, mas com `getline` você teria problema.
- Reset de `dist` entre casos (o código cria o vetor dentro da função).

## Código

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXC = 100000;

vector<int> vizinhos(int u){
    vector<int> v = {u + 1, u - 1, u * 2, u * 3};
    if (u % 2 == 0) v.push_back(u / 2);
    return v;
}

int bfs(int origem, int destino, const vector<int>& proibidos){
    vector<int> dist(MAXC + 1, -1);
    // canal proibido entra como "ja visitado": o BFS nunca o enfileira
    for (int p : proibidos) {
        if (p >= 1 && p <= MAXC) dist[p] = -2;
    }

    queue<int> fila;
    dist[origem] = 0;
    fila.push(origem);

    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();

        if (u == destino) return dist[u];

        for (int v : vizinhos(u)) {
            if (v < 1 || v > MAXC || dist[v] != -1) continue;

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

    int o, d, k;
    while (cin >> o >> d >> k && (o || d || k)) {
        vector<int> proibidos(k);
        for (int i = 0; i < k; i++) cin >> proibidos[i];

        cout << bfs(o, d, proibidos) << "\n";
    }

    return 0;
}
```

Arquivos: `code/beecrowd/1910/sol.cpp` · rodar com `make test X=1910` dentro de `code/beecrowd/`.

Testado localmente com o exemplo do enunciado (`make test` deu OK); não submetido ao juiz.

## Para fixar

1. Por que marcar o proibido como visitado é equivalente a apagar o vértice do grafo? E se o proibido fosse a **aresta** (um botão que não funciona num canal específico)?
2. O segundo caso do exemplo dá −1. Desenhe as camadas e veja onde a busca morre.
3. Compare com o Ex. 17-18 do Lucchesi (cap. II, p. 45), em [[05 - BFS em espaco de estados]]: lá o estado ganha um bit; aqui o grafo perde vértices. São as duas formas de "editar o grafo" antes de rodar a BFS.
