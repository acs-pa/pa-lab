// SPDX-License-Identifier: BSD-3-Clause

import java.util.HashMap;
import java.util.Map;

public class MapDemo {
    public static void main(String[] args) {
        Map<String, Integer> frequency = new HashMap<>();
        frequency.put("gigel", frequency.getOrDefault("gigel", 0) + 1);
        frequency.put("gigel", frequency.getOrDefault("gigel", 0) + 1);
        frequency.put("not_gigel", frequency.getOrDefault("not_gigel", 0) + 1);
        for (Map.Entry<String, Integer> e : frequency.entrySet()) {
            System.out.println(e.getKey() + " " + e.getValue());
        }
    }
}
