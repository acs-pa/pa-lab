// SPDX-License-Identifier: BSD-3-Clause

import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Queue;

public class MaxHeap {
    public static void main(String[] args) {
        Queue<Integer> maxheap = new PriorityQueue<>(Comparator.reverseOrder());
        maxheap.add(1);
        maxheap.add(12);
        maxheap.add(6);
        maxheap.add(1);
        while (!maxheap.isEmpty()) {
            int top = maxheap.poll();
            System.out.println(top);
        }
        // print: 12 6 1 1
    }
}
