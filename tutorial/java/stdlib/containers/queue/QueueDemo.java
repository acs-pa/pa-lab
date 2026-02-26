// SPDX-License-Identifier: BSD-3-Clause

import java.util.ArrayDeque;
import java.util.Queue;

public class QueueDemo {
    public static void main(String[] args) {
        Queue<Integer> q = new ArrayDeque<>();
        for (int i = 0; i < 5; i++) {
            q.add(i);
        }
        while (!q.isEmpty()) {
            int front = q.poll();
            System.out.print(front + " ");
        }
        System.out.println();
        // print: 0 1 2 3 4
    }
}
