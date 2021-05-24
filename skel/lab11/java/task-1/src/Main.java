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
        public static final int NMAX = 1005;

        // n = numar de noduri, m = numar de muchii
        int n, m;

        // adj[i] = lista de adiacenta a nodului i
        @SuppressWarnings("unchecked")
        ArrayList<Integer> adj[] = new ArrayList[NMAX];

        // cap[i][j] = capacitatea arcului i -> j
        int cap[][];

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new BufferedReader(new FileReader(
                                INPUT_FILE)));
                n = sc.nextInt();
                m = sc.nextInt();

                cap = new int[n + 1][n + 1];
                for (int i = 1; i <= n; i++) {
                    adj[i] = new ArrayList<>();
                }
                for (int i = 1; i <= m; i++) {
                    // x -> y de capacitate c
                    int x, y, c;
                    x = sc.nextInt();
                    y = sc.nextInt();
                    c = sc.nextInt();
                    adj[x].add(y);
                    adj[y].add(x);

                    // Presupunem existenta mai multor arce x -> y cu capacitati c1, c2, ...
                    // Comprimam intr-un singur arc x -> y cu capacitate
                    // cap[x][y] = c1 + c2 + ...
                    cap[x][y] += c;
                }
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(int result) {
            try {
                PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(
                                OUTPUT_FILE)));
                pw.printf("%d\n", result);
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private int getResult() {
            //
            // TODO: Calculati fluxul maxim pe graful orientat dat.
            // Sursa este nodul 1.
            // Destinatia este nodul n.
            //
            // In adj este stocat graful neorientat obtinut dupa ce se elimina orientarea
            // arcelor, iar in cap sunt stocate capacitatile arcelor.
            // De exemplu, un arc (x, y) de capacitate z va fi tinut astfel:
            // cap[x][y] = z, adj[x] contine y, adj[y] contine x.
            //
            int maxFlow = 0;

            return maxFlow;
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
