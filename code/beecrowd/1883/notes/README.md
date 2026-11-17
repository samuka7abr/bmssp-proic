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
  - "[[04 - BFS multi-fonte]]"
  - "[[1583 - Contaminacao]]"
---

# 1883 - Fuga de Ayutthaya

> **Técnica:** BFS multi-fonte + fuga · **Listas:** B · **Enunciado:** [beecrowd 1883](https://judge.beecrowd.com/pt/problems/view/1883)

## O problema em uma frase

Numa sala N×M (até 10³×10³) com paredes `#`, focos de fogo `F`, o início `S` e a saída `E`, o fogo e a pessoa andam uma célula por minuto nas 4 direções. **Se a pessoa e o fogo chegam à mesma célula no mesmo instante, a pessoa morre.** Imprima `Y` se ela consegue chegar à saída e `N` se não. Começa com T instâncias.

## Modelando como grafo

Dois grafos sobre o mesmo grid:

- **Fogo:** vértices = células não-parede; fontes = todos os `F`. Uma BFS multi-fonte dá `fogo[v]`, o minuto em que o fogo chega em v (−1 se nunca chega).
- **Pessoa:** mesmo grid, mas a pessoa só pode entrar em v no minuto t se `fogo[v] == -1` ou `t < fogo[v]`.

## Por que essa técnica (e não outra)

**Por que dá para separar as duas BFS?** O fogo não reage à pessoa: `fogo[v]` não depende do que ela faz. Então você calcula o fogo inteiro primeiro e usa como tabela de horário.

**Por que a BFS da pessoa com restrição ainda é correta?** Se a pessoa consegue estar em v no minuto t, chegar antes nunca atrapalha, porque `t' < t < fogo[v]`. Então o que importa em cada célula é só o **primeiro** minuto em que ela pode estar lá, e é exatamente isso que a BFS calcula. Se esperar parado pudesse ajudar (fogo que acende e apaga), o argumento cairia e o estado teria de incluir o tempo.

**Por que multi-fonte?** Com k focos, uma BFS por foco custaria k·N·M; com todos na fila de uma vez, N·M ([[04 - BFS multi-fonte]]).

## O algoritmo passo a passo

1. Leia a sala e guarde os focos, `S` e `E`.
2. BFS multi-fonte do fogo → `fogo[][]`.
3. BFS a partir de `S`. Ao tentar entrar em v no minuto t = `dist[u] + 1`, recuse se `fogo[v] != -1 && fogo[v] <= t`.
4. Se a BFS retira `E` da fila, `Y`; senão, `N`.

Rastreio dos dois primeiros exemplos:

- **4×5, S em (0,4), E em (3,4), F em (3,0).** A pessoa desce em 3 minutos. O fogo chega a (3,4) em 4 minutos. 3 < 4: **Y**.
- **4×4, S em (0,3), E em (3,3), F em (3,0).** A pessoa leva 3; o fogo leva 3. Empate é morte: **N**.

O segundo exemplo existe só para testar o `<=`. Se você escrever `<`, ele falha.

O terceiro exemplo (paredes isolando `S`) dá **N** porque a pessoa nem alcança a saída.

## Complexidade

Duas BFS: O(N·M) por instância, até 10⁶ células.

## Armadilhas

- `<` no lugar de `<=` no teste do fogo.
- Esquecer as células que o fogo **nunca** alcança (`fogo == -1`): nelas a pessoa entra sempre.
- Sala sem nenhum `F`: a BFS do fogo fica vazia e tudo continua funcionando.
- Recriar as matrizes por instância. Com 10⁶ células e muitas instâncias, alocar dentro da função como o código faz está ok; um `static` reaproveitado é mais rápido.

## Código

```cpp
#include <bits/stdc++.h>
using namespace std;

const int dl[4] = {1, -1, 0, 0};
const int dc[4] = {0, 0, 1, -1};

typedef vector<vector<int>> Matriz;

// multi-fonte: todos os F entram com tempo 0; fogo[l][c] = minuto em que o fogo chega (-1 = nunca)
Matriz bfs_fogo(const vector<string>& sala, const vector<pair<int, int>>& focos) {
    int n = sala.size(), m = sala[0].size();
    Matriz fogo(n, vector<int>(m, -1));
    queue<pair<int, int>> fila;

    for (const pair<int, int>& f : focos) {
        fogo[f.first][f.second] = 0;
        fila.push(f);
    }

    while (!fila.empty()) {
        int l = fila.front().first;
        int c = fila.front().second;
        fila.pop();

        for (int i = 0; i < 4; i++) {
            int nl = l + dl[i];
            int nc = c + dc[i];

            if (nl < 0 || nl >= n || nc < 0 || nc >= m) continue;
            if (sala[nl][nc] == '#') continue;
            if (fogo[nl][nc] != -1) continue;

            fogo[nl][nc] = fogo[l][c] + 1;
            fila.push(make_pair(nl, nc));
        }
    }

    return fogo;
}

bool foge(const vector<string>& sala, const Matriz& fogo, pair<int, int> ini, pair<int, int> saida) {
    int n = sala.size(), m = sala[0].size();
    Matriz dist(n, vector<int>(m, -1));
    queue<pair<int, int>> fila;

    dist[ini.first][ini.second] = 0;
    fila.push(ini);

    while (!fila.empty()) {
        int l = fila.front().first;
        int c = fila.front().second;
        fila.pop();

        if (l == saida.first && c == saida.second) return true;

        for (int i = 0; i < 4; i++) {
            int nl = l + dl[i];
            int nc = c + dc[i];

            if (nl < 0 || nl >= n || nc < 0 || nc >= m) continue;
            if (sala[nl][nc] == '#') continue;
            if (dist[nl][nc] != -1) continue;

            int t = dist[l][c] + 1;
            // chegar junto com o fogo (t == fogo) tambem mata
            if (fogo[nl][nc] != -1 && fogo[nl][nc] <= t) continue;

            dist[nl][nc] = t;
            fila.push(make_pair(nl, nc));
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<string> sala(n);
        vector<pair<int, int>> focos;
        pair<int, int> ini, saida;

        for (int l = 0; l < n; l++) {
            cin >> sala[l];
            for (int c = 0; c < m; c++) {
                if (sala[l][c] == 'F') focos.push_back(make_pair(l, c));
                if (sala[l][c] == 'S') ini = make_pair(l, c);
                if (sala[l][c] == 'E') saida = make_pair(l, c);
            }
        }

        Matriz fogo = bfs_fogo(sala, focos);
        cout << (foge(sala, fogo, ini, saida) ? 'Y' : 'N') << "\n";
    }

    return 0;
}
```

Arquivos: `code/beecrowd/1883/sol.cpp` · rodar com `make test X=1883` dentro de `code/beecrowd/`.

Testado localmente com o exemplo do enunciado (`make test` deu OK); não submetido ao juiz.

## Para fixar

1. E se a pessoa pudesse ficar parada? Muda a resposta em algum caso deste problema? (Dica: o fogo só avança.)
2. E se o fogo levasse 2 minutos por célula? Só muda a comparação: `2·fogo[v]`.
3. Compare com [[1799 - O Rato no Labirinto]]: lá as duas BFS são independentes e se somam; aqui a segunda **usa** a primeira como restrição.
