# Problemas Beecrowd

Questões de grafos do PROIC, com foco em BFS e suas variações. Cada pasta tem `sol.cpp`, o exemplo do enunciado em `IO/` e uma nota comentada em `notes/README.md`.

```bash
make run X=1100    # compila e roda com IO/i.txt
make test X=1100   # compara a saída com IO/o.txt
make clean
```

## Lista

| Nº | Nome | Técnica | Listas | Link |
|----|------|---------|--------|------|
| 1100 | Movimentos do Cavalo | BFS em grid | A, B, C | https://judge.beecrowd.com/pt/problems/view/1100 |
| 1123 | Desvio de Rota | Dijkstra modificado / Floyd | A | https://judge.beecrowd.com/pt/problems/view/1123 |
| 1148 | Países em Guerra | Dijkstra com restrição / Floyd | A | https://judge.beecrowd.com/pt/problems/view/1148 |
| 1550 | Inversão | BFS em espaço de estados | B, C | https://judge.beecrowd.com/pt/problems/view/1550 |
| 1583 | Contaminação | BFS multi-fonte | C | https://judge.beecrowd.com/pt/problems/view/1583 |
| 1621 | Labirinto | BFS dupla (diâmetro) | A, B, C | https://judge.beecrowd.com/pt/problems/view/1621 |
| 1655 | 106 Milhas Para Chicago | Dijkstra/Floyd multiplicativo | A | https://judge.beecrowd.com/pt/problems/view/1655 |
| 1799 | O Rato no Labirinto | Duas BFS somadas | B | https://judge.beecrowd.com/pt/problems/view/1799 |
| 1855 | Mapa do Meistre | Grid com detecção de ciclo | C | https://judge.beecrowd.com/pt/problems/view/1855 |
| 1883 | Fuga de Ayutthaya | BFS multi-fonte + fuga | B | https://judge.beecrowd.com/pt/problems/view/1883 |
| 1897 | Jogo Esperto | BFS em grafo implícito | C | https://judge.beecrowd.com/pt/problems/view/1897 |
| 1905 | Polícia e Ladrão | Alcançabilidade em grid | C | https://judge.beecrowd.com/pt/problems/view/1905 |
| 1907 | Coloração de Cenários de Jogos | Flood fill / componentes | C | https://judge.beecrowd.com/pt/problems/view/1907 |
| 1910 | Ajude Clotilde | BFS em estados com proibidos | C | https://judge.beecrowd.com/pt/problems/view/1910 |
| 1952 | O Cavalo no Xadrez 3D | BFS em 3D | B, C | https://judge.beecrowd.com/pt/problems/view/1952 |
| 2032 | Jogo dos Oito | BFS em estados (8-puzzle) | B, C | https://judge.beecrowd.com/pt/problems/view/2032 |
| 3061 | Manchas de Pele | Flood fill | C | https://judge.beecrowd.com/pt/problems/view/3061 |

Extra (LeetCode, em `../leetcode/2290`): Minimum Obstacle Removal to Reach Corner, BFS 0-1.

**Listas:**
- **A:** Questões de menor caminho Beecrowd (20/09)
- **B:** Beecrowd shortest path BFS (17/10)
- **C:** Questões de representação implícita e BFS (27/10)
