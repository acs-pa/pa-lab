<!-- SPDX-License-Identifier: BSD-3-Clause -->

### map (HashMap)

* [docs.oracle.com: HashMap](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/HashMap.html)

Key-value container with unique keys. Use `Map<K, V>` with `HashMap<K, V>` for O(1) get/put on average.

* **put(K key, V value)**: insert or overwrite, O(1) avg
* **get(K key)**: value or null, O(1) avg
* **getOrDefault(K key, V defaultValue)**
* **forEach**, **entrySet()** for iteration

```java
import java.util.HashMap;
import java.util.Map;

Map<String, Integer> frequency = new HashMap<>();
frequency.put("gigel", frequency.getOrDefault("gigel", 0) + 1);
frequency.put("gigel", frequency.getOrDefault("gigel", 0) + 1);
frequency.put("not_gigel", frequency.getOrDefault("not_gigel", 0) + 1);
for (Map.Entry<String, Integer> e : frequency.entrySet()) {
    System.out.println(e.getKey() + " " + e.getValue());
}
```

Runnable example: [MapDemo.java](MapDemo.java).
