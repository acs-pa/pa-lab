import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;

public class Main {
    static class Task {
        public static final String INPUT_FILE = "in";
        public static final String OUTPUT_FILE = "out";

        // numarul maxim de noduri
        public static final int NMAX = 105;

        // n = numar de noduri
        int n;

        // w[x][y] = constul muchiei de la x la y: (x, y, w[x][y])
        // (w[x][y] = 0 - muchia lipseste)
        int w[][];

        // d[x][y] = lungimea drumului minim de la x la y
        int d[][];

        public void solve() {
            readInput();
            getResult();
            writeOutput();
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new BufferedReader(new FileReader(
                                INPUT_FILE)));
                n = sc.nextInt();
                d = new int[n + 1][n + 1];
                w = new int[n + 1][n + 1];
                for (int x = 1; x <= n; x++) {
                    for (int y = 1; y <= n; y++) {
                        w[x][y] = sc.nextInt();
                    }
                }
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput() {
            try {
                BufferedWriter bw = new BufferedWriter(new FileWriter(
                                OUTPUT_FILE));
                StringBuilder sb = new StringBuilder();
                for (int x = 1; x <= n; x++) {
                    for (int y = 1; y <= n; y++) {
                        sb.append(d[x][y]).append(' ');
                    }
                    sb.append('\n');
                }
                bw.write(sb.toString());
                bw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void getResult() {
            //
            // TODO: Gasiti distantele minime intre oricare doua noduri, folosind
            // Roy-Floyd pe graful orientat cu n noduri, m arce stocat in matricea
            // ponderilor w (declarata mai sus).
            //
            // Atentie:
            // O muchie (x, y, w) este reprezentata astfel in matricea ponderilor:
            //    w[x][y] = w;
            // Daca nu exista o muchie intre doua noduri x si y, in matricea
            // ponderilor se va afla valoarea 0:
            //    w[x][y] = 0;
            //
            // Trebuie sa populati matricea d[][] (declarata mai sus):
            //    d[x][y] = distanta minima intre nodurile x si y, daca exista drum.
            //    d[x][y] = 0 daca nu exista drum intre x si y.
            //          * implicit: d[x][x] = 0 (distanta de la un nod la el insusi).
            //
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
