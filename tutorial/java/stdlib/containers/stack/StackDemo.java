// SPDX-License-Identifier: BSD-3-Clause

import java.util.ArrayDeque;
import java.util.Deque;

public class StackDemo {
    public static void main(String[] args) {
        Deque<Integer> st = new ArrayDeque<>();
        st.push(1);
        st.push(2);
        st.push(3);
        while (!st.isEmpty()) {
            int top = st.pop();
            System.out.println(top);
        }
        // print: 3 2 1
    }
}
