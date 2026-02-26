<!-- SPDX-License-Identifier: BSD-3-Clause -->

### list (ArrayList)

* [docs.oracle.com: ArrayList](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/ArrayList.html)

Resizable array. Use at PA for arrays and matrices. Prefer `ArrayList<T>` over raw arrays when size changes.

* **size()**: number of elements, O(1)
* **get(int i)**: element at index, O(1)
* **add(T x)**: append, O(1)
* **set(int i, T x)**: replace at index, O(1)

#### Dynamic list

```java
import java.util.ArrayList;
import java.util.List;

List<Integer> v = new ArrayList<>();
v.add(5);
v.add(1);
v.add(3);
int last = v.remove(v.size() - 1);  // pop last
```

#### n elements, 0-indexed

```java
List<Integer> v = new ArrayList<>();
for (int i = 0; i < n; i++) {
    v.add(sc.nextInt());
}
```

#### 1-indexed (e.g. DP)

```java
List<Integer> v = new ArrayList<>();
v.add(0);  // dummy at 0
for (int i = 1; i <= n; i++) {
    v.add(sc.nextInt());
}
// use v.get(1) .. v.get(n)
```

#### Matrix (1-indexed)

```java
List<List<Integer>> dp = new ArrayList<>();
for (int i = 0; i <= n; i++) {
    List<Integer> row = new ArrayList<>();
    for (int j = 0; j <= m; j++) {
        row.add(0);
    }
    dp.add(row);
}
// use dp.get(i).get(j) for i in [1..n], j in [1..m]
```

Runnable example: [ListDemo.java](ListDemo.java).
