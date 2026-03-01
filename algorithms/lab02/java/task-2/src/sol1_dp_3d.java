// SPDX-License-Identifier: BSD-3-Clause

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class sol1_dp_3d {
    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        private final static int MOD = 1000000007;

        int n;
        char[] expr;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextInt();
                String s = sc.next().trim();
                s = " " + s;
                expr = s.toCharArray();
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(int result) {
            try {
                PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE));
                pw.printf("%d\n", result);
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private int getResult() {
            // TODO: Calculati numarul de moduri in care se pot aseza
            // parantezele astfel incat rezultatul expresiei sa fie TRUE.
            // Numarul de moduri se va calcula modulo MOD (1000000007).
            return boolExpression();
        }

        boolean isOperator(char op) {
            return op == '&' || op == '|' || op == '^';
        }

        int evaluate(char op, int l, int r) {
            if (op == '&') return l & r;
            if (op == '|') return l | r;
            if (op == '^') return l ^ r;

            // valoare default pentru evitare warnings
            return 0;
        }

        // T = O(n ^ 3)
        // S = O(n ^ 2) - stocam n x n x 2 numere intregi in tabloul dp
        //          Obs. Chiar daca dp are 3 dimensiuni, o dimensiune este foarte mica!
        int boolExpression() {
            //      Problema seamna cu PODM, coincidenta tot vorba de parantezari...
            //      La PODM avem o dinamica de forma dp[i][j] = ..., ceea ce ar avea foarte mult sens si aici,
            // intrucat [i,j] ar reprezenta o subexpresie!
            //      Este suficient sa avem doua dimensiuni?
            //          - ar suna asa:
            //              dp[i][j] = numarul de moduri de a paranteza expr[i...j] pentru a obtine valoarea 1 (True)
            //          - privind tabela de adevar a celor 3 operatori, observam ca avem nevoie sa stim si valorile
            //              de 0 (False).
            //              Ex. La xor se obtine 1 pentru operatorii 1, 0 sau 0, 1.
            //          - din motivele mentionate anterior, vom calcula raspunsul si pentru a obtine expresia cu valoarea
            //              1, dar si pentru a obtine expresia cu valoarea 0.

            // dp[i][j][v] = numarul de moduri de a paranteza expresia expr[i...j] pentru a obtine valoarea v
            int[][][] dp = new int[n + 1][n + 1][2];

            // Asemanator problemei PODM, dorim sa plecam de la intervale cat mai mici si sa ne extindem.
            // Adica daca cunoastem parantezari pentru subexpresii, cum rezolvam expresii mai mari.

            // Cazul de baza: intervalele de forma [i, i], care nu necesita paranteze.
            // Pentru expresii de forma  "expr[i]", valorea expresiei e chiar valoarea operandului.
            for (int i = 1; i <= n; i += 2) {
                dp[i][i][0] = (expr[i] == 'F') ? 1 : 0;
                dp[i][i][1] = (expr[i] == 'T') ? 1 : 0;
            }

            //      Fie o expresie [i, j], care este de forma: expr[i] expr[i + 1] ... expr[j]
            //      Ce inseamna a paranteza aceasta expresie?
            // Obtinem o expresie de forma: (expr[i] ... expr[k - 1]) expr[k] (expr[k + 1] ... expr[j])
            //      Obs. expr[k] este un operator!
            //      Notam cu E toata expresia, L (left) si R (right) cele 2 subexpresii, cu op operatorul
            // Obtinem: E = L op R
            //      Daca am sti toate modurile de parantezare pentru L si R,
            // atunci E o sa fie o combinatie.
            //
            //      Ex. Daca avem X moduri in stanga, Y moduri in
            // dreapta, atunci se vor obtine X * Y moduri noi de a paranteza
            // subsecventa [i, j], deoarece parantezele din stanga si din
            // dreapta sunt independente.

            //      Deoarece pentru expresii mai mari avem nevoie de expresii mai mici (de lungime mai mica),
            // vom procesa intervalele in ordinea lungimii (lungime 1, 2, 3, ...)
            //      Obs. In for-ul aneterior am calculat deja intervalele de lungime 1 ([i, i])

            //      Pentru a afla solutia pentru un interval [i, j] (o expresie), avem mai multe moduri de a
            // paranteza.
            //      Fiecare parantezare inseamna separarea lui [i,j] in [i, k - 1] op [k + 1, j]
            // (observatie: pe pozitia k este un operator, care aplica o operatie intre valorile celor doua subexpresii)

            for (int len = 2; len <= n; ++len) {            // fixam lungimea intervalului (2, 3, 4, ...)
                for (int i = 1; i + len - 1 <= n; ++i) {    // fixam capatul din stanga: i
                    int j = i + len - 1;                    // capatul din dreapta se deduce: j

                    // Iteram prin indicii dintre capete, cautand un loc unde
                    // subsecventa poate fi "sparta" in 2 de un operator.
                    for (int k = i + 1; k < j; ++k) {       // k este OPERATOR intre i si j
                        if (!isOperator(expr[k])) {
                            continue;
                        }
                        char op = expr[k];                  // am extras OPERATORUL

                        // lv rv        (lv = left value, rv = right value)
                        // 0  0
                        // 0  1
                        // 1  0
                        // 1  1
                        for (int lv = 0; lv <= 1; ++lv) {
                            for (int rv = 0; rv <= 1; ++rv) {
                                //   v = lv op rv               (v = value)
                                int v = evaluate(op, lv, rv);

                                // X = moduri de parantezare pentru expresia de la stanga  ([i  , k-1])
                                // Y = moduri de parantezare pentru expresia de la dreapta ([k+1, j])
                                // numar moduri =     X           *      Y
                                int add = (int) ((1L * dp[i][k - 1][lv] * dp[k + 1][j][rv]) % MOD);

                                // Trebuie sa il adaugam la rezultatul pentru [i,j] si valoare v
                                dp[i][j][v] = (dp[i][j][v] + add) % MOD;
                            }
                        }
                    }
                }
            }

            // Rezultatul se afla in dp[1][n][1]: Numarul de parantezari pentru
            // intreg sirul cu valoarea de adevar 1 (TRUE).
            return dp[1][n][1];
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
