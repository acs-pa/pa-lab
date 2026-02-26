// SPDX-License-Identifier: BSD-3-Clause

import java.util.HashSet;
import java.util.Set;
import java.util.TreeSet;

public class SetDemo {
    public static void main(String[] args) {
        Set<Integer> s = new HashSet<>();
        s.add(1);
        s.add(12);
        s.add(6);
        s.add(1);
        for (int x : new TreeSet<>(s)) {
            System.out.println(x);
        }
        // print: 1 6 12
    }
}
