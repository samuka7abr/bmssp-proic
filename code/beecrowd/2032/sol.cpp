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
