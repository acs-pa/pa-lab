<!-- SPDX-License-Identifier: BSD-3-Clause -->

# PA Java - TLDR

## PA skel

During the PA laboratories, you'll receive a skeleton for each task.

NOTE: `should` on this page means tips & tricks for PA (may not apply elsewhere).

Everything below uses only the **standard library** (`java.util`, `java.io`).

```java
import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Task {
    public static final String INPUT_FILE = "in";
    public static final String OUTPUT_FILE = "out";

    // TODO: define fields

    public void solve() {
        readInput();
        writeOutput(getResult());
    }

    private void readInput() {
        try (Scanner sc = new Scanner(new File(INPUT_FILE))) {
            // TODO: read input
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private int getResult() {
        // TODO: implement the solution
        return 0;
    }

    private void writeOutput(int result) {
        try (PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE))) {
            pw.print(result);
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

Notes:
* Use only the standard library.
* You `don't` need to ever change the `main()` method!
* You `need` to complete the `Task` class (fields, `readInput`, `getResult`, `writeOutput`).
* The `check` command compiles and runs the tasks.

## Java tweaks (stdlib only)

Details and runnable examples are in the `stdlib` tree. Quick reference:

| Topic        | Java std                | See |
|-------------|--------------------------|-----|
| **IO**      | `Scanner`, `PrintWriter`, `File` | [stdlib/io/io.md](stdlib/io/io.md) |
| **arrays**  | `ArrayList<T>`          | [stdlib/containers/list/list.md](stdlib/containers/list/list.md) |
| **matrix**  | `ArrayList<ArrayList<T>>` or `T[][]` | [stdlib/containers/list/list.md](stdlib/containers/list/list.md) |
| **stack**   | `Deque<T>` (e.g. `ArrayDeque`) | [stdlib/containers/stack/stack.md](stdlib/containers/stack/stack.md) |
| **queue**   | `Queue<T>` (e.g. `ArrayDeque`) | [stdlib/containers/queue/queue.md](stdlib/containers/queue/queue.md) |
| **hashtable** | `HashMap<K, V>`       | [stdlib/containers/map/map.md](stdlib/containers/map/map.md) |
| **set**     | `HashSet<T>`            | [stdlib/containers/set/set.md](stdlib/containers/set/set.md) |
| **minheap** | `PriorityQueue<T>`      | [stdlib/containers/heap/heap.md](stdlib/containers/heap/heap.md) |
| **maxheap** | `PriorityQueue<T>` + `Comparator.reverseOrder()` | [stdlib/containers/heap/heap.md](stdlib/containers/heap/heap.md) |

Containers index: [stdlib/containers/containers.md](stdlib/containers/containers.md).

In each subfolder: `make run` to run the example; `make clean` to remove generated files.
