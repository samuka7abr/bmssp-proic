# Lucchesi cap II, Conexidade e Separação

Capítulo mais interessante até agora pro [[PROIC]]: é onde aparece distância, a construção por camadas (que é o BFS) e as versões de Menger. Divide-se em componentes (o caso "binário") e conexidade (a versão quantitativa, k-conexo).

## Componentes

- "u e v são ligados" (existe passeio entre eles) é relação de equivalência, logo particiona VG. Cada subgrafo gerado por uma classe é um **componente**. Simples e é a base de tudo.
- Subgrafo **isolado** em G: todo passeio de G que toca um vértice dele já está inteiro dentro dele.
- Dois objetos centrais: **corte de arestas** delta(S) (arestas com um extremo em S e outro fora) e **corte de vértices** W(S). Corte é **separador** quando vem de um subconjunto próprio e não vazio.
- **Lema 3, o lema de paridade.** Num passeio, o número de arestas que caem no corte é ímpar se e somente se origem e término estão em lados opostos. Quase todo resultado do capítulo desce daí, inclusive "dois vértices são ligados sse o corte vazio não os separa".
- Teorema 1: conexo <=> não tem corte vazio separador <=> nenhum subgrafo próprio não vazio é isolado.
- Teorema 2: quatro caracterizações equivalentes de componente, incluindo maximal entre os conexos não vazios e minimal entre os isolados não vazios.
- **Teorema 3**: distância = comprimento do menor caminho, e definindo S_0 = {u}, S_k = Adj(S_{k-1}) menos tudo que já apareceu, então S_k é exatamente o conjunto dos vértices a distância k. Isso é o BFS escrito como teorema, e a sequência zera antes de |VG| passos. **Esse é o gancho direto com o tema da pesquisa.**

## Conexidade (versão quantitativa)

- u e v são **k-ligados** quando existem k caminhos dois a dois internamente disjuntos entre eles (com ajuste pro caso adjacente). G é **k-conexo** se todo par é k-ligado, e a **conexidade** é o maior k.
- Cuidado: k-ligação é reflexiva e simétrica mas **não é transitiva**, então não dá pra generalizar "componente" de forma ingênua. Ele mostra isso no exemplo da Figura 2.
- **Teorema 4 e Corolários 5 e 6, que são Menger.** Máximo de caminhos disjuntos = mínimo corte de vértices que separa. O Corolário 6 é a forma que eu quero lembrar: u e v não adjacentes são k-ligados se e somente se nenhum corte com menos de k vértices separa os dois sem conter nenhum deles.
- Proposição 1: grafo com n >= 2 vértices nunca é n-conexo, e é (n-1)-conexo exatamente quando tem subgrafo gerador completo.
- Teorema 5: quando não há subgrafo gerador completo, a conexidade coincide com (i) o corte mínimo de vértices separador e (ii) o menor X tal que G-X desconecta. As três definições batem.
- **Teorema 6 (Dirac).** Se G é k-conexo, por quaisquer k vértices passa um passeio circular. O caso k=2 é o ciclo por dois vértices quaisquer.
- Versão por arestas: k-aresta-ligados, aresta-conexidade, e o **Corolário 7 (Whitney)**: conexidade <= aresta-conexidade <= grau mínimo. Teorema 7 é o Menger de arestas.

## Notas do capítulo

- A definição de conexidade não é única na literatura, outros autores usam a caracterização (ii) do Teorema 5. Bom saber antes de comparar com Diestel.
- Créditos: Menger (1927), Whitney (1932), Dirac (1960), Ford e Fulkerson (1956) pro lado de arestas via fluxos em redes. E o exercício 14 é resolvido pelo **algoritmo de Dijkstra (1959)**, ou seja, o menor caminho já aparece aqui como exercício.
