<!-- SPDX-License-Identifier: BSD-3-Clause -->

### set (HashSet)

* [docs.oracle.com: HashSet](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/HashSet.html)

Set with unique elements; order not guaranteed. Use `Set<T>` with `HashSet<T>` for O(1) add/contains on average.

* **add(T x)**: insert, O(1) avg
* **contains(Object x)**: membership, O(1) avg
* **size()**
* **forEach**, iteration

```java
import java.util.HashSet;
import java.util.Set;
import java.util.TreeSet;

Set<Integer> s = new HashSet<>();
s.add(1);
s.add(12);
s.add(6);
s.add(1);
// sorted iteration (use TreeSet or sort manually):
for (int x : new TreeSet<>(s)) {
    System.out.println(x);
}
// print: 1 6 12
```

Runnable example: [SetDemo.java](SetDemo.java).
