// SPDX-License-Identifier: BSD-3-Clause

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;

public class sol1_roy_floyd {
    static class Task {
        public static final String INPUT_FILE = "in";
        public static final String OUTPUT_FILE = "out";

        // numarul maxim de noduri
        public static final int NMAX = 105;

        // n = numar de noduri
        int n;

        // w[x]y] = constul muchiei de la x la y: (x, y, w[x][y])
        // (w[x][y] = 0 - muchia lipseste)
        //
        // In aceasta problema, costurile sunt strict pozitive.
        int w[][];

        // structura folosita pentru a stoca matricea de distante, matricea
        // de parinti folosind algoritmul RoyFloyd.
        public class RoyFloydResult {
            int d[][];
            int p[][];

            RoyFloydResult(int _d[][], int _p[][]) {
                d = _d;
                p = _p;
            }
        };

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new BufferedReader(new FileReader(
                                INPUT_FILE)));
                n = sc.nextInt();
                w = new int[n + 1][n + 1];
                for (int i = 1; i <= n; i++) {
                    for (int j = 1; j <= n; j++) {
                        w[i][j] = sc.nextInt();
                    }
                }
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(RoyFloydResult res) {
            try {
                BufferedWriter bw = new BufferedWriter(new FileWriter(
                                OUTPUT_FILE));
                StringBuilder sb = new StringBuilder();
                for (int x = 1; x <= n; x++) {
                    for (int y = 1; y <= n; y++) {
                        sb.append(res.d[x][y]).append(' ');
                    }
                    sb.append('\n');
                }
                bw.write(sb.toString());
                bw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private RoyFloydResult getResult() {
            //
            // TODO: Gasiti distantele minime intre oricare doua noduri, folosind
            // Roy-Floyd pe graful orientat cu n noduri, m arce stocat in matricea
            // ponderilor w (declarata mai sus).
            //
            // Atentie:
            // O muchie (x, y, w) este reprezentata astfel in matricea ponderilor:
            //  w[x][y] = w;
            // Daca nu exista o muchie intre doua noduri x si y, in matricea
            // ponderilor se va afla valoarea 0:
            //  w[x][y] = 0;
            //
            // Trebuie sa populati matricea d[][] (declarata mai sus):
            //  d[x][y] = distanta minima intre nodurile x si y, daca exista drum.
            //  d[x][y] = 0 daca nu exista drum intre x si y.
            //          * implicit: d[x][x] = 0 (distanta de la un nod la el insusi).
            //

            return royfloyd();
        }

        private RoyFloydResult royfloyd() {
            // Initializez matricea de distante cu matricea ponderilor.
            int d[][] = new int[n + 1][n + 1];
            int p[][] = new int[n + 1][n + 1];
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    d[i][j] = w[i][j];
                    p[i][j] = 0;
                }
            }

            // Aplic Roy-Floyd
            for (int k = 1; k <= n; k++) {
                // Fixez nodul intermediar k
                for (int i = 1; i <= n; i++) {
                    for (int j = 1; j <= n; j++) {
                        if (i == j) {
                            continue;
                        }

                        // Daca nu exista drum de la i la k sau de la k la j, sarim peste.
                        if (d[i][k] == 0 || d[k][j] == 0) {
                            continue;
                        }

                        // Fixez cele doua capete ale drumului pe care le updatez (i, j).
                        // Daca nu am drum sau daca obtin un cost mai mic intre i, j,
                        // updatez.
                        if (d[i][j] == 0 || d[i][j] > d[i][k] + d[k][j]) {
                            d[i][j] = d[i][k] + d[k][j];
                            p[i][j] = p[k][j];
                        }
                    }
                }
            }

            return new RoyFloydResult(d, p);
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
