import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;
import java.util.ArrayList;

public class Main {
    static class Task {
        class Edge {
            int x, y;

            public Edge(int x, int y) {
                this.x = x;
                this.y = y;
            }
        }

        public static final String INPUT_FILE = "in";
        public static final String OUTPUT_FILE = "out";

        // numarul maxim de noduri
        public static final int NMAX = (int) 1e5 + 5; // 10^5 + 5 = 100.005

        // n = numar de noduri, m = numar de muchii/arce
        int n, m;

        // adj[node] = lista de adiacenta a nodului node
        // exemplu: daca adj[node] = {..., neigh, ...} => exista arcul (node, neigh)
        @SuppressWarnings("unchecked")
        ArrayList<Integer> adj[] = new ArrayList[NMAX];

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new BufferedReader(new FileReader(INPUT_FILE)));
                n = sc.nextInt();
                m = sc.nextInt();

                for (int i = 1; i <= n; i++) {
                    adj[i] = new ArrayList<>();
                }
                for (int i = 1; i <= m; i++) {
                    int x, y;
                    x = sc.nextInt();
                    y = sc.nextInt();
                    // muchie (x, y)
                    adj[x].add(y);
                    adj[y].add(x);
                }
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(ArrayList<Edge>  all_ces) {
            try {
                PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(OUTPUT_FILE)));
                pw.printf("%d\n", all_ces.size());
                for (Edge ce : all_ces) {
                    pw.printf("%d %d\n", ce.x, ce.y);
                }
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private ArrayList<Edge> getResult() {
            //
            // TODO: Gasiti toate muchiile critice ale grafului neorientat stocat cu liste de adiacenta in adj.
            // Rezultatul se va returna sub forma unui vector cu toate muchiile critice (ordinea nu conteaza).
            //
            // Indicatie: Folositi algoritmul lui Tarjan pentru CE.
            //

            ArrayList<Edge> all_ces = new ArrayList<>();
            return all_ces;
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
