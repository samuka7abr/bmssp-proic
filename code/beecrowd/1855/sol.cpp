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
