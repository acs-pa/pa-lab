# Cheatsheet complexități

Maintainers:
- Miruna-Elena Banu (mirunaelena.banu@gmail.com)
- Darius Neatu (neatudarius@gmail.com)

## Clase de complexități

- Acest document are ca scop asocierea unor algoritmi / clase de algoritmi cu anumite complexități. De exemplu, pornind de la limita de timp din enunț, se poate deduce care este complexitatea optimă în funcție de variabilele date, iar de la complexitate se pot deduce câțiva posibili algoritmi pentru a rezolva problema dată.

- Pentru un procesor modern, în **C/C++**, numărul de instrucțiuni executate în 1s este în <img src="https://render.githubusercontent.com/render/math?math=[10^6, 10^7]">.
- Pentru **Java**, de obicei, timpul de execuție este cel puțin dublu (în special în problemele în care există input sau output cu dimensiuni foarte mari).

|Ordin de mărime|Complexitate|
|-|-|
| <img src="https://render.githubusercontent.com/render/math?math=[10^12, 10^18]">| <img src="https://render.githubusercontent.com/render/math?math=O(\log{n})">  |
| <img src="https://render.githubusercontent.com/render/math?math=[10^7, 10^12]"> | <img src="https://render.githubusercontent.com/render/math?math=O(\sqrt{n})"> |
| <img src="https://render.githubusercontent.com/render/math?math=[10^6, 10^7]"> | <img src="https://render.githubusercontent.com/render/math?math=O(n)">|
| <img src="https://render.githubusercontent.com/render/math?math=10^5"> | <img src="https://render.githubusercontent.com/render/math?math=O(n \log{n})">|
| <img src="https://render.githubusercontent.com/render/math?math=10^4"> | <img src="https://render.githubusercontent.com/render/math?math=O(n \sqrt{n})"> |
| <img src="https://render.githubusercontent.com/render/math?math=10^3"> | <img src="https://render.githubusercontent.com/render/math?math=O(n^2)"> |
| <img src="https://render.githubusercontent.com/render/math?math=10^2"> | <img src="https://render.githubusercontent.com/render/math?math=O(n^3)"> |
| <img src="https://render.githubusercontent.com/render/math?math=10"> | <img src="https://render.githubusercontent.com/render/math?math=O(2^n)/O(3^n)">
| <img src="https://render.githubusercontent.com/render/math?math=15"> | <img src="https://render.githubusercontent.com/render/math?math=O(n!)/O(2^n)">|
| <img src="https://render.githubusercontent.com/render/math?math=30 - 40 (par)"> | <img src="https://render.githubusercontent.com/render/math?math=O(\frac{n}{2}!)/(2 ^ {\frac{n}{2}})"> (Meet in the middle) |


Concluzie: **Ideal** este să găsim o soluție <img src="https://render.githubusercontent.com/render/math?math=O(1)">. Dacă nu se poate, căutăm <img src="https://render.githubusercontent.com/render/math?math=O(\log{n})">. Apoi <img src="https://render.githubusercontent.com/render/math?math=O(\sqrt{n})">. Și tot așa coborâm în tabel.

# Algoritmi studiați la PA

|Clasă de complexitate| Algoritmi |
|-|-|
| <img src="https://render.githubusercontent.com/render/math?math=O(1)"> | - răspunsuri directe (par, impar, etc.)<br> - formule simple (ex: suma numerelor de la 1 la n folosind formula lui Gauss)|
| <img src="https://render.githubusercontent.com/render/math?math=O(\log{n})"> | - algoritmi de tipul DEI: căutare binară (normală, lower bound, upper bound), exponențiere logaritimică, exponențiere logaritmică pe matrice (optimizarea de la DP) <br> - cmmdc, cmmmc |
| <img src="https://render.githubusercontent.com/render/math?math=O(\sqrt{n})">| - factorizarea numerelor<br>- verificare că un numar e prim |
| <img src="https://render.githubusercontent.com/render/math?math=O(n)"> = liniar| - parcurgere de vector<br>- recurențe liniare la DP: SSM, numărare<br>- greedy (ex: pe vector) |
| <img src="https://render.githubusercontent.com/render/math?math=O(n \log{n})"> | - sortări<br>- n căutări binare pe un vector deja sortat<br>- n = parcurgerea unui șir de n elemente, log n = fiecărui element i se aplică log n operații (ex: push/pop heap, compute power) |
| <img src="https://render.githubusercontent.com/render/math?math=O(n ^ 2)"> <br> <img src="https://render.githubusercontent.com/render/math?math=O(n m)">| - recurențe la DP mai complexe (ex: SCMAX)<br>- operații pe matrice<br>- BFS pe matrice |
| <img src="https://render.githubusercontent.com/render/math?math=O(n ^ 3)"> | - recurențe DP de tip PODM |
|||
|**Backtracking**||
|<img src="https://render.githubusercontent.com/render/math?math=O(2 ^ n)"> |- submulțimile unei mulțimi cu n elemente <br>- combinații în probleme de tipul "mereu se poate face stânga sau dreapta, care este numărul total de posibilități?" |
|<img src="https://render.githubusercontent.com/render/math?math=O(C(n, k)) = O(n!)*">| - probleme care se reduc la generarea combinărilor|
|<img src="https://render.githubusercontent.com/render/math?math=O(A(n, k)) = O(n!)*">|- probleme care se reduc la generarea aranjamentelor|
|<img src="https://render.githubusercontent.com/render/math?math=O(P(n)) = O(n!)">|- probleme care se reduc la generarea permutărilor|
||* = o limită relaxată (de exemplu: numărul de aranjamente este mai mic decât n!)|
|||
|**Grafuri**|
| <img src="https://render.githubusercontent.com/render/math?math=O(n %2B m)"> = liniar| - DFS/BFS<br>- orice algoritm bazat pe una sau câteva parcurgeri: ciclu în graf, TopSort, CC, CTC (SCC), BCC / CV / CE, distanțe pe grafuri particulare (arbore, DAG, costuri egale / fără cost)
| <img src="https://render.githubusercontent.com/render/math?math=O(m \log{n})"> |- Dijkstra |
| <img src="https://render.githubusercontent.com/render/math?math=O(m \log{m})">| - Kruskal / Prim |
|<img src="https://render.githubusercontent.com/render/math?math=O(n \log{n} %2B m)">| - sortarea nodurilor după un criteriu, apoi o parcurgere a grafului|
| <img src="https://render.githubusercontent.com/render/math?math=O(m \log{m} %2B n)"> | - sortarea muchiilor după un criteriu, apoi o parcurgere a grafului|
|<img src="https://render.githubusercontent.com/render/math?math=O(n m)"><br><img src="https://render.githubusercontent.com/render/math?math=O(n ^ 2)"><br><img src="https://render.githubusercontent.com/render/math?math=O(m ^ 2)">| - Bellman-Ford <br> - n parcurgeri pe un graf <img src="https://render.githubusercontent.com/render/math?math=n * O(BFS/DFS)">|
|<img src="https://render.githubusercontent.com/render/math?math=O(n ^ 3)">|- Roy-Floyd (grafuri dense)|
|<img src="https://render.githubusercontent.com/render/math?math=O(n m \log{n})">| - Johnson (grafuri rare)|
|<img src="https://render.githubusercontent.com/render/math?math=O(n m^2)">| - Edmonds-Karp|
|<img src="https://render.githubusercontent.com/render/math?math=O(b ^ d)">|- A* <br>- Minimax|
