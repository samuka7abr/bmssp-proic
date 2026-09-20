# Lucchesi cap I, Grafos

Capítulo de definições, com dois teoremas fortes no fim (Ramsey e Amizade). O grosso é vocabulário que ele vai usar o livro inteiro, vale voltar aqui sempre que travar.

## O que preciso guardar

- A definição dele é de multigrafo: grafo é a tripla (VG, aG, psiG), com a função de incidência associando cada aresta a um par não ordenado de vértices. Aresta com extremos iguais é **laço**, senão é **ligação**. Simples só quando não tem laço nem ligações paralelas.
- **Tamanho** é |VG| + |aG|, não é só o número de arestas. Peguei isso errado na primeira leitura.
- Grau conta laço **duas vezes**. Daí sai a Proposição 1 (soma dos graus = 2|aG|) e o corolário do aperto de mãos: o número de vértices de grau ímpar é sempre par.
- Zoo de tipos: simples, completo, triângulo, regular / g-regular, biparticionável (bipartição {X,Y}), n-cubo (n-uplas em {0,1}, adjacentes quando diferem em exatamente uma coordenada).
- Subgrafos: próprio, **gerado** G[X] ou G[x] (a partir de vértices ou de arestas) e **gerador** (H gera G quando VH = VG). Notações G-Z, G-v, G-alfa aparecem o tempo todo depois.
- Ponto que mais confunde: **máximo/mínimo** é por cardinalidade, **maximal/minimal** é por inclusão. Ele usa os quatro com precisão, e no cap III isso vira a diferença entre "emparelhamento máximo" e "emparelhamento maximal".
- Hierarquia de passeios: passeio > trilha (arestas distintas) > caminho (vértices distintos). Fechado quando origem = término; circular = trilha fechada não degenerada com internos distintos; o conjunto de arestas de um circular é um **circuito**. Mais reverso, seção, rotação e produto de passeios.

## Teoremas

- **Teorema 1 (Ramsey finito).** Motivação: em toda festa com 6 pessoas existem 3 mutuamente amigas ou 3 mutuamente estranhas. Traduzido: K6 com arestas coloridas em 2 cores tem triângulo monocromático (com 5 vértices não vale). A prova geral é indução com f(m,n) = f(m-1,n) + f(m,n-1). Nas notas ele diz que o cerne é o princípio da casa dos pombos.
- **Teorema 2 (Teorema da Amizade).** Se em G simples não vazio quaisquer dois vértices têm exatamente um vizinho comum, então existe vértice adjacente a todos os demais. Prova por contradição quebrada em 6 lemas: o grafo acaba sendo g-regular, |V| = g(g-1) + 1, e aí ele conta passeios fechados de comprimento l e chega em divisibilidade contraditória usando um primo. Boa demonstração pra estudar a técnica: **dupla contagem + argumento aritmético**, não é combinatória "de grafo" pura.

## Notas do capítulo

- Euler (1736, pontes de Königsberg) como marco zero da área. A caracterização dele volta no cap IV.
- Referências que ele recomenda: Bondy e Murty (1976), Berge (1970), Harary (1969), Aho-Hopcroft-Ullman (1974) pro lado de algoritmos e estruturas, Biggs (1974) pro enfoque algébrico.
