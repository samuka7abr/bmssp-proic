# Lucchesi cap III, Grau

Capítulo mais denso dos três, e o mais longo. Três seções que na verdade são uma escada: sequências de graus, depois emparelhamentos (f = 1 em todo vértice), depois f-emparelhamentos, que generalizam as duas anteriores.

## 1. Sequências gráficas

- f é **gráfica** se é a função grau de algum grafo, **estritamente gráfica** se de algum grafo **simples**. A diferença é toda a dificuldade da seção.
- Teorema 1: f é gráfica sse f(V) é par. Sai direto do aperto de mãos do cap I, e a construção usa laços à vontade, por isso quase nunca dá um grafo simples.
- **Teorema 2 + Corolário 1 = Erdős-Gallai**: f é estritamente gráfica sse f(X) <= k(k-1) + soma de min{k, f(v)} pros vértices fora de X, para todo X de cardinalidade k. Condição de verificação, não construtiva.
- **Teorema 3 = Havel-Hakimi**: critério recursivo. Ordena não crescente, exige f1 <= n-1, abate 1 dos f1 maiores graus seguintes e recursa. Esse é o que vira algoritmo.

## 2. Emparelhamentos

- Vocabulário pareado: **emparelhamento** t (conjunto de arestas) x **conjunto independente** T (de vértices), **cobertura de arestas** x **cobertura de vértices**. V0(G) = vértices de grau zero.
- Teorema 4 junta as desigualdades entre |T|, |C|, |t|, |c| e |V0|, com as igualdades acontecendo nos casos minimax. Ele avisa que as desigualdades costumam ser **estritas** no caso geral (o triângulo é o contraexemplo padrão), e que só ficam apertadas no bipartido.
- **Teorema 5 = König (1931)**: em grafo com bipartição, cobertura mínima de arestas = emparelhamento máximo. Detalhe que gostei: ele **prova isso a partir do Menger do cap II**, adicionando um vértice x ligado a todo Y e olhando caminhos disjuntos. Boa amarração entre capítulos.
- Corolário 2 é um caso do **Dilworth (1950)**.
- **Teorema 6 = Hall (1935)**, o problema dos casamentos: existe emparelhamento cobrindo Y sse |Y inter V0(G-Z)| <= |Z| para todo Z em X. Ele frisa que **não generaliza de forma ingênua** pra grafos não biparticionáveis, de novo o triângulo mata.
- Passeios **t-alternados**, t-par e t-ímpar. Lemas 5 e 6 são a ideia dos caminhos aumentantes: dado um caminho alternado com as pontas descobertas, trocar dentro e fora do emparelhamento aumenta a cobertura. É o coração de qualquer algoritmo de emparelhamento.
- **Teorema 7 e Corolário 3 = Tutte (1947)**: G tem emparelhamento perfeito sse |I(G-Z)| <= |Z| para todo Z, onde I conta os **componentes ímpares**.
- **Corolário 4 = Berge-Tutte (1958)**: fórmula minimax do emparelhamento máximo, |I(G-Z)| = |V menos Vt| + |Z|.
- Corolário 5 é útil na prática: t é máximo sse Vt é **maximal** (inclusão), não precisa comparar cardinalidades. Volta a distinção máximo/maximal do cap I.

## 3. f-emparelhamentos

- Generalização: t é f-emparelhamento quando t(v) <= f(v) para todo v, e perfeito quando vale a igualdade. **f-deficiência** = f(V) - t(V), sempre >= 0, zero exatamente no perfeito.
- Emparelhamento comum é o caso f == 1, e a pergunta "f é estritamente gráfica?" da seção 1 vira "o completo admite f-emparelhamento perfeito?". As três seções colapsam nisso.
- **Teorema 8 (Tutte, 1952)**: condição necessária e suficiente via partição p = (S,T,U) de V e contagem de componentes ímpares I(f,p). A prova é indução sobre os vértices com f(v) != 1, "quebrando" cada um deles em vários vértices de grau 1 até cair no caso de emparelhamento comum, onde vale o Teorema 7.

## Notas do capítulo

- Linha do tempo que ele monta: Erdős-Gallai (1960), Havel (1955) e Hakimi (1962), König (1931), Dilworth (1950), Hall (1935), Tutte (1947 e 1952), Berge (1958), e o primeiro algoritmo para o Teorema 7 com **Edmonds (1965)**. A demonstração do livro se apoia em Lovász.
- Exercício 32 é uma **conjectura em aberto** (todo grafo 5-regular 5-conexo tem 2-emparelhamento perfeito), então não vale perder tempo tentando fechar.
