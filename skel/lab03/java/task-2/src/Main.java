import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {
    static class Result {
        int len;
        int[] subsequence;

        public Result() {
            len = 0;
            subsequence = null;
        }
    }

    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        int n, m;
        int[] v;
        int[] w;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextInt();
                m = sc.nextInt();

                v = new int[n + 1]; // Adaugare element fictiv - indexare de la 1
                for (int i = 1; i <= n; i++) {
                    v[i] = sc.nextInt();
                }

                w = new int[m + 1]; // Adaugare element fictiv - indexare de la 1
                for (int i = 1; i <= m; i++) {
                    w[i] = sc.nextInt();
                }
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(Result result) {
            try {
                PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE));
                pw.printf("%d\n", result.len);
                if (result.subsequence != null) {
                    for (int i = 0; i < result.len; i++) {
                        pw.printf("%d ", result.subsequence[i]);
                    }
                }
                pw.printf("\n");
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private Result getResult() {
            Result result = new Result();

            // TODO: Aflati cel mai lung subsir comun intre v (de lungime n)
            // si w (de lungime m).
            // Se puncteaza separat urmatoarele 2 cerinte:
            // 2.1. Lungimea CMLSC. Rezultatul pentru cerinta aceasta se va pune
            // in ``result.len``.
            // 2.2. Reconstructia CMLSC. Se puncteaza orice subsir comun maximal
            // valid. Solutia pentru aceasta cerinta se va pune in
            // ``result.subsequence``.

            return result;
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
