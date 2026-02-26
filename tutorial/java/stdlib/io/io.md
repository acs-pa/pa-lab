<!-- SPDX-License-Identifier: BSD-3-Clause -->

### IO (file read/write)

* [docs.oracle.com: Scanner](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/Scanner.html)
* [docs.oracle.com: PrintWriter](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/io/PrintWriter.html)
* [docs.oracle.com: File](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/io/File.html)

You should use file I/O for PA (read from `in`, write to `out`).

#### Reading

```java
import java.io.File;
import java.io.IOException;
import java.util.Scanner;

public static void main(String[] args) {
    try (Scanner sc = new Scanner(new File("in"))) {
        int x = sc.nextInt();
        int a = sc.nextInt();
        int b = sc.nextInt();
        int n = sc.nextInt();
        String c = sc.next();
        String s = sc.next();
        // use x, a, b, n, c, s
    } catch (IOException e) {
        throw new RuntimeException(e);
    }
}
```

#### Writing

```java
import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;

public static void writeOutput(int x, int a, int b, String c, String s) {
    try (PrintWriter pw = new PrintWriter(new File("out"))) {
        pw.println(x + " " + a + " " + b + " " + c + " " + s);
    } catch (IOException e) {
        throw new RuntimeException(e);
    }
}
```

Runnable example: [Io.java](Io.java). From this folder: `make run`.
