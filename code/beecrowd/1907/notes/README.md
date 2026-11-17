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

# 1907 - Coloração de Cenários de Jogos

> **Técnica:** flood fill / componentes · **Listas:** C · **Enunciado:** [beecrowd 1907](https://judge.beecrowd.com/pt/problems/view/1907)

## O problema em uma frase

Uma imagem N×M (até 1024×1024) tem pixels `.` (branco) e `o` (preto). A ferramenta balde de tinta pinta de uma vez toda a região branca conectada (4 direções). Quantos cliques são necessários para pintar todos os pixels brancos?

## Modelando como grafo

- **Vértice:** pixel `.`.
- **Aresta:** dois pixels `.` vizinhos na horizontal ou vertical.
- **Pergunta:** cada clique pinta exatamente um componente, então a resposta é o **número de componentes**.

É o mesmo modelo do [[3061 - Manchas de Pele]]. O que muda é o tamanho: até ~10⁶ vértices.

## Por que essa técnica (e não outra)

O raciocínio de correção é idêntico ao do 3061. A diferença é de engenharia: uma DFS **recursiva** num grid 1024×1024 todo branco desce até ~10⁶ chamadas de profundidade e estoura a pilha (o padrão costuma ser 8 MB). A BFS guarda a fronteira numa `queue` no heap e não tem esse problema. Esta questão existe para você sentir isso na prática.

## O algoritmo passo a passo

1. Varra o grid. Ao achar um `.`, some 1 aos cliques e rode BFS a partir dele.
2. A BFS pinta (troca `.` por `o`) cada pixel **ao enfileirar**. Assim o próprio grid serve de vetor de visitados e não precisa de memória extra.
3. Imprima os cliques.

Rastreio do primeiro exemplo do enunciado (6×9), com cada região branca marcada pela ordem em que a varredura a encontra:

```
AoooBoooC
oDDDoDDDo
EoDDDDDoF
EEoDDDoFF
EEEoDoFFF
EEEEoFFFF
```

A, B e C são pixels sozinhos na primeira linha, cercados por `o` e pela borda. D é o interior do coração: as duas metades da linha 1 se juntam pela linha 2. E e F são o lado de fora, à esquerda e à direita, separados pela ponta do coração. Seis BFS, resposta 6. Os outros dois exemplos (`.o.o.o.o` → 4 e `o` → 0) testam os casos de borda: regiões de um pixel e imagem sem branco.

## Complexidade

O(N·M). Memória O(N·M) para o grid e, no pior caso, O(N·M) para a fila.

## Armadilhas

- DFS recursiva, como explicado acima.
- Ler o grid como `string` por linha (`cin >> grade[i]`) é bem mais rápido do que ler caractere por caractere.
- Pintar o grid de entrada destrói a imagem. Aqui não importa; num problema que pedisse a imagem depois, use um `vis` separado.

## Código

```cpp
#include <bits/stdc++.h>
using namespace std;

const int dl[4] = {1, -1, 0, 0};
const int dc[4] = {0, 0, 1, -1};

int n, m;
vector<string> grade;

void bfs(int li, int ci){
    queue<pair<int, int>> fila;

    // pinta ao inserir: cada pixel entra na fila no maximo uma vez
    grade[li][ci] = 'o';
    fila.push(make_pair(li, ci));

    while (!fila.empty()) {
        int l = fila.front().first;
        int c = fila.front().second;
        fila.pop();

        for (int i = 0; i < 4; i++) {
            int nl = l + dl[i];
            int nc = c + dc[i];

            if (nl < 0 || nl >= n || nc < 0 || nc >= m) continue;
            if (grade[nl][nc] != '.') continue;

            grade[nl][nc] = 'o';
            fila.push(make_pair(nl, nc));
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;
    grade.resize(n);
    for (int i = 0; i < n; i++) cin >> grade[i];

    int cliques = 0;
    for (int l = 0; l < n; l++) {
        for (int c = 0; c < m; c++) {
            if (grade[l][c] != '.') continue;
            cliques++;
            bfs(l, c);
        }
    }

    cout << cliques << "\n";

    return 0;
}
```

Arquivos: `code/beecrowd/1907/sol.cpp` · rodar com `make test X=1907` dentro de `code/beecrowd/`.

Testado localmente com o exemplo do enunciado (`make test` deu OK); não submetido ao juiz.

## Para fixar

1. Gere um grid 1024×1024 todo de `.` e rode uma versão com DFS recursiva. O que acontece? E com `ulimit -s unlimited`?
2. Quantas posições a fila chega a ter, no máximo, num grid todo branco começando do canto? (Pense nas camadas da BFS em grid: são diagonais.)
3. Volte ao [[07 - Componentes, flood fill e diametro]] e releia a seção sobre "isolado" no Lucchesi: por que a fila esvaziar significa que o componente acabou?
