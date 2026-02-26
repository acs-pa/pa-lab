// SPDX-License-Identifier: BSD-3-Clause

import java.util.PriorityQueue;
import java.util.Queue;

public class MinHeap {
    public static void main(String[] args) {
        Queue<Integer> minheap = new PriorityQueue<>();
        minheap.add(1);
        minheap.add(12);
        minheap.add(6);
        minheap.add(1);
        while (!minheap.isEmpty()) {
            int top = minheap.poll();
            System.out.println(top);
        }
        // print: 1 1 6 12
    }
}
