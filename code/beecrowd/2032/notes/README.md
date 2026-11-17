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

# 2032 - Jogo dos Oito

> **Técnica:** BFS em estados (8-puzzle) · **Listas:** B, C · **Enunciado:** [beecrowd 2032](https://judge.beecrowd.com/pt/problems/view/2032)

## O problema em uma frase

Dado um tabuleiro 3×3 com as peças 1 a 8 e o vazio 0, imprima o menor número de jogadas para chegar a `123/456/780` **e todos os tabuleiros intermediários**, desempatando caminhos de mesmo tamanho pela prioridade: mover a peça de **cima** do vazio, depois a de **baixo**, a da **direita** e a da **esquerda**. Se não houver solução, `Problema sem solucao`. Vários casos até o fim do arquivo.

## Modelando como grafo

- **Vértice:** uma configuração do tabuleiro, ou seja, uma permutação de 0..8. São 9! = 362 880.
- **Aresta:** trocar o 0 com um vizinho. Cada vértice tem 2, 3 ou 4 arestas, conforme o vazio esteja num canto, numa borda ou no centro.
- **Peso:** 1 por jogada.

## Por que essa técnica (e não outra)

Menor número de jogadas → BFS no espaço de estados ([[05 - BFS em espaco de estados]]). Três detalhes fazem esta questão valer nível 9.

**1. Metade dos estados é inalcançável.** Leia o tabuleiro em ordem, ignorando o 0, e conte as inversões (pares fora de ordem). Uma jogada horizontal não muda a sequência; uma vertical move uma peça duas posições, mudando a contagem em 0 ou ±2. A **paridade** das inversões é invariante. O alvo tem 0 inversões (par), então tabuleiros com número ímpar de inversões nunca chegam lá. O grafo tem **exatamente dois componentes** de 181 440 vértices cada (Lucchesi, cap. II, Teorema 2). O fórum da questão confirma esse teste.

**2. O estado precisa virar índice.** `map<string,int>` funciona, mas é lento com muitos casos. O código usa o **código de Lehmer**: a posição da permutação na ordem lexicográfica, um inteiro em [0, 9!). Assim `pai` e `estado` são vetores comuns.

**3. Desempate pela prioridade.** A BFS gera os vizinhos na ordem cima, baixo, direita, esquerda e marca cada estado na **primeira** vez que o vê. Por indução nas camadas: os estados de cada camada são retirados da fila na ordem lexicográfica (pela prioridade) dos seus caminhos, então o primeiro pai de cada estado é o do menor caminho na ordem de prioridade. É o mesmo argumento do Corolário 22.4 do Cormen, refinado para a ordem dentro da camada.

## O algoritmo passo a passo

1. Leia 9 caracteres (o código pula espaços e quebras de linha).
2. Se a paridade das inversões é ímpar, imprima `Problema sem solucao`.
3. BFS da configuração inicial até `123456780`, guardando o pai de cada estado.
4. Reconstrua o caminho do alvo até a origem pelos pais, inverta e imprima o número de passos e os tabuleiros após cada jogada.

Rastreio do exemplo:

```
123     123     123
456  →  456  →  456
078     708     780
```

O vazio está em (2,0). Cima: trocar com o 4 dá `123/056/478`. Baixo e esquerda não existem. Direita: trocar com o 7 dá `123/456/708`. Da camada 1, `123/456/708` leva ao alvo trocando com o 8. Resposta 2.

## Complexidade

No pior caso, 181 440 estados × 4 vizinhos por caso. O código calcula o índice de Lehmer em O(81) por estado. O tabuleiro mais difícil (`867/254/301`, 31 jogadas) roda em fração de segundo.

## Armadilhas

- **Formato de saída.** O exemplo mostra o cabeçalho e os tabuleiros separados por uma linha em branco. Não está claro, pelo texto extraído da página, se há linha em branco **entre casos**. O código não imprime nada entre casos. Se der *Presentation Error* no juiz, comece por aí.
- Imprimir o tabuleiro inicial (o exemplo não imprime).
- Ignorar a prioridade de desempate: a contagem sai certa, mas os tabuleiros impressos não.
- Rodar a BFS sem testar a paridade: ela vai varrer os 181 440 estados alcançáveis e só então desistir.

## Código

```cpp
#include <bits/stdc++.h>
using namespace std;

const string ALVO = "123456780";
const int TOTAL = 362880;

// ordem de prioridade: peca de cima, de baixo, da direita, da esquerda do espaco vazio
const int dl[4] = {-1, 1, 0, 0};
const int dc[4] = {0, 0, 1, -1};

int fat[9];

// posicao da permutacao na ordem lexicografica (codigo de Lehmer): vira indice de vetor
int indice(const string& s){
    int r = 0;
    for (int i = 0; i < 9; i++) {
        int menores = 0;
        for (int j = i + 1; j < 9; j++)
            if (s[j] < s[i]) menores++;
        r += menores * fat[8 - i];
    }
    return r;
}

bool temSolucao(const string& s){
    int inversoes = 0;
    for (int i = 0; i < 9; i++)
        for (int j = i + 1; j < 9; j++)
            if (s[i] != '0' && s[j] != '0' && s[i] > s[j]) inversoes++;
    return inversoes % 2 == 0;
}

vector<string> bfs(const string& origem){
    vector<int> pai(TOTAL, -2);
    vector<string> estado(TOTAL);
    queue<string> fila;

    int io = indice(origem);
    pai[io] = -1;
    estado[io] = origem;
    fila.push(origem);

    while (!fila.empty()) {
        string u = fila.front();
        fila.pop();

        if (u == ALVO) break;

        int iu = indice(u);
        int z = u.find('0');
        int l = z / 3, c = z % 3;

        for (int i = 0; i < 4; i++) {
            int nl = l + dl[i], nc = c + dc[i];
            if (nl < 0 || nl >= 3 || nc < 0 || nc >= 3) continue;

            string v = u;
            swap(v[z], v[nl * 3 + nc]);
            int iv = indice(v);
            if (pai[iv] != -2) continue;

            pai[iv] = iu;
            estado[iv] = v;
            fila.push(v);
        }
    }

    vector<string> caminho;
    for (int i = indice(ALVO); i != -1; i = pai[i]) caminho.push_back(estado[i]);
    reverse(caminho.begin(), caminho.end());
    return caminho;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    fat[0] = 1;
    for (int i = 1; i < 9; i++) fat[i] = fat[i - 1] * i;

    char ch;
    string tab;
    while (cin >> ch) {
        tab = ch;
        for (int i = 1; i < 9; i++) {
            cin >> ch;
            tab += ch;
        }

        if (!temSolucao(tab)) {
            cout << "Problema sem solucao\n";
            continue;
        }

        vector<string> caminho = bfs(tab);
        cout << "Quantidade minima de passos = " << caminho.size() - 1 << "\n";
        for (size_t p = 1; p < caminho.size(); p++) {
            if (p > 1) cout << "\n";
            for (int l = 0; l < 3; l++) cout << caminho[p].substr(l * 3, 3) << "\n";
        }
    }

    return 0;
}
```

Arquivos: `code/beecrowd/2032/sol.cpp` · rodar com `make test X=2032` dentro de `code/beecrowd/`.

Testado localmente com o exemplo do enunciado, com o caso sem solução do fórum (`103/245/678`) e com o caso mais difícil conhecido (31 jogadas); não submetido ao juiz.

## Para fixar

1. Prove que a paridade das inversões é invariante. Por que isso só vale porque a largura (3) é ímpar? O 15-puzzle (4×4) tem uma regra diferente.
2. Como a BFS a partir do **alvo** poderia responder todos os casos de uma vez? O que atrapalha aqui é o desempate pela prioridade: ele é definido a partir da origem.
3. Pesquise A\* com a distância de Manhattan como heurística. Ela visita menos estados, mas garante o mesmo desempate?
