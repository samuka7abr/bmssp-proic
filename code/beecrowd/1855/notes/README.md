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
---

# 1855 - Mapa do Meistre

> **Técnica:** grid com detecção de ciclo · **Listas:** C · **Enunciado:** [beecrowd 1855](https://judge.beecrowd.com/pt/problems/view/1855)

## O problema em uma frase

Um mapa retangular (largura x e altura y, ambos < 100) tem setas `> < v ^`, terreno `.` e baús `*`. Saindo do canto superior esquerdo, você segue a direção atual e troca de direção ao pisar numa seta. Imprima `*` se o caminho chega a um baú e `!` se sai do mapa ou entra em ciclo.

## Modelando como grafo

- **Vértice:** o par (célula, direção atual). Numa célula com seta, a direção que você traz não importa, porque a seta a substitui. Numa célula `.`, importa.
- **Aresta:** cada vértice tem **exatamente uma** aresta de saída: o próximo passo é determinado.

Um grafo em que todo vértice tem grau de saída 1 é um **grafo funcional**. A partir de qualquer vértice, o passeio é único e, como o grafo é finito, ou para (sai do mapa, acha o baú) ou entra num ciclo.

## Por que essa técnica (e não outra)

Não há escolha a fazer, então não há busca: nem BFS nem DFS, só **simulação** com um vetor de visitados. É a ideia do item (ii) do Teorema 3 do Lucchesi (cap. II): cada passo gasta um vértice novo, então em no máximo |V| passos acontece uma de três coisas: baú, saída do mapa ou revisita.

**Por que marcar só a célula, e não (célula, direção)?** Se você pisa de novo numa célula, há dois casos:

- **É uma seta.** A direção de saída é a mesma da primeira vez, então tudo se repete: é ciclo.
- **É um `.`.** Você pode estar passando por ela em outra direção, num cruzamento. A primeira vez você veio, por exemplo, para a direita, e agora vem para baixo.

Então marcar só a célula pode acusar ciclo num cruzamento que não é ciclo. Teste com seus próprios mapas. O código desta nota marca a célula, como fazem as soluções publicadas, e passa nos dois exemplos do enunciado. A versão rigorosa marca o par (célula, direção): são 4·x·y estados, ainda pequeno.

## O algoritmo passo a passo

1. Comece em (0, 0) sem direção.
2. Se saiu do mapa, `!`. Se a célula já foi visitada, `!`.
3. Marque a célula. Se é `*`, imprima `*`. Se é seta, atualize a direção.
4. Se ainda não há direção (o canto é `.`), `!`. Ande um passo e volte ao 2.

Rastreio do segundo exemplo (7×5):

```
>.....v
.......
.......
.......
^.....<
```

Direita até (0,6), seta `v`; desce até (4,6), seta `<`; esquerda até (4,0), seta `^`; sobe até (0,0), já visitada. Resposta `!`. Nunca houve baú.

## Complexidade

O(x·y): cada célula é visitada no máximo uma vez.

## Armadilhas

- A entrada dá a **largura** primeiro e a **altura** depois. A matriz é `mapa[altura][largura]`.
- Testar se saiu do mapa **antes** de ler `mapa[l][c]`.
- Cruzamentos em `.`, discutidos acima.

## Código

```cpp
#include <bits/stdc++.h>
using namespace std;

// cada celula tem uma unica saida (grau de saida 1): basta seguir o caminho
bool valido(const vector<string>& mapa, int largura, int altura){
    vector<vector<bool>> visitado(altura, vector<bool>(largura, false));
    int l = 0, c = 0;
    int dl = 0, dc = 0;

    while (true) {
        if (l < 0 || l >= altura || c < 0 || c >= largura) return false;
        if (visitado[l][c]) return false;
        visitado[l][c] = true;

        char s = mapa[l][c];
        if (s == '*') return true;
        if (s == '>') dl = 0, dc = 1;
        if (s == '<') dl = 0, dc = -1;
        if (s == 'v') dl = 1, dc = 0;
        if (s == '^') dl = -1, dc = 0;
        if (dl == 0 && dc == 0) return false;

        l += dl;
        c += dc;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int largura, altura;
    cin >> largura >> altura;

    vector<string> mapa(altura);
    for (int i = 0; i < altura; i++) cin >> mapa[i];

    cout << (valido(mapa, largura, altura) ? '*' : '!') << "\n";

    return 0;
}
```

Arquivos: `code/beecrowd/1855/sol.cpp` · rodar com `make test X=1855` dentro de `code/beecrowd/`.

Testado localmente com os dois exemplos do enunciado (`*` e `!`); não submetido ao juiz.

## Para fixar

1. Monte um mapa em que o caminho cruza a si mesmo num `.` e ainda chega ao baú. O código marca `!`? Reescreva marcando (célula, direção).
2. Num grafo funcional, todo componente tem exatamente um ciclo (pense em "rho", ρ). Por quê? Relacione com o Corolário 1.5.2 do Diestel (árvore com n vértices tem n−1 arestas).
3. Compare com [[1905 - Policia e Ladrao]]: lá cada célula tem até 4 saídas e você precisa de uma fila. O que a fila faz que aqui não é necessário?
