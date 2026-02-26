// SPDX-License-Identifier: BSD-3-Clause

import java.util.ArrayList;
import java.util.List;

public class ListDemo {
    public static void main(String[] args) {
        List<Integer> v = new ArrayList<>();
        v.add(5);
        v.add(1);
        v.add(3);
        System.out.println("size = " + v.size());
        System.out.println("last = " + v.get(v.size() - 1));
        int last = v.remove(v.size() - 1);
        System.out.println("pop = " + last + " size = " + v.size());
    }
}
