<!-- SPDX-License-Identifier: BSD-3-Clause -->

# Java Tutorial

## TLDR

A short summary for what you need / should use at PA can be found at [PA Java: TLDR](tldr.md).

## Docs

Links:
* [docs.oracle.com/javase](https://docs.oracle.com/javase/tutorial/): Java Tutorials
  * [Learning the Java Language](https://docs.oracle.com/javase/tutorial/java/)
  * [Collections](https://docs.oracle.com/javase/tutorial/collections/)
* [Java API (java.util)](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/package-summary.html): ArrayList, HashMap, HashSet, PriorityQueue, etc.

This tutorial uses only the **standard library** (`java.util`, `java.io`). No external dependencies.

## Java basics

* Java is a high-level, object-oriented language.
* It supports primitive types (`int`, `boolean`, etc.) and reference types (classes, e.g. `String`, `Integer`).
* Parameters are passed **by value** (primitives are copied; object references are copied, so the same object can be modified inside a method).

### Hello Gigel in Java

```java
import java.util.Scanner;

public class Hello {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int x = sc.nextInt();
        System.out.println("Hello, Gigel! I got " + x + " from the PA team!");
        sc.close();
    }
}
```

* In PA you read/write from files — see [stdlib/io](stdlib/io/io.md).

### Class and Task skeleton

* A **class** holds fields and methods; `this` refers to the instance.

```java
import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Task {
    public static final String INPUT_FILE = "in";
    public static final String OUTPUT_FILE = "out";

    int n;
    int[] v;

    public void solve() {
        readInput();
        writeOutput(getResult());
    }

    private void readInput() {
        try (Scanner sc = new Scanner(new File(INPUT_FILE))) {
            n = sc.nextInt();
            v = new int[n];
            for (int i = 0; i < n; i++) {
                v[i] = sc.nextInt();
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private int getResult() {
        int sum = 0;
        for (int x : v) sum += x;
        return sum;
    }

    private void writeOutput(int result) {
        try (PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE))) {
            pw.println(result);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    // [ATENTIE] NU modifica functia main!
    public static void main(String[] args) {
        new Task().solve();
    }
}
```

## stdlib

Java’s standard library provides I/O and collections. Continue the tutorial from the `std` tree:

* [stdlib/io](stdlib/io/io.md) — file read/write
* [stdlib/containers](stdlib/containers/containers.md) — ArrayList, HashMap, HashSet, Queue, min-heap / max-heap (PriorityQueue), etc.
