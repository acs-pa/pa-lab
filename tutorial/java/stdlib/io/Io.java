// SPDX-License-Identifier: BSD-3-Clause

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Io {
    public static void main(String[] args) {
        try (Scanner sc = new Scanner(new File("in"))) {
            int x = sc.nextInt();
            int a = sc.nextInt();
            int b = sc.nextInt();
            int n = sc.nextInt();
            String c = sc.next();
            String s = sc.next();

            try (PrintWriter pw = new PrintWriter(new File("out"))) {
                pw.println(x + " " + a + " " + b + " " + c + " " + s);
            }
            System.out.println("wrote to out");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
