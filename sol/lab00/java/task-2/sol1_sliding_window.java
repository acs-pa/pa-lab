// SPDX-License-Identifier: BSD-3-Clause

import java.util.*;

class Solution {
    // Solutie: Folosim un TreeMap pentru a stoca cele mai mari k elemente.
    // Complexitate: O(nlogk)
    public int[] maxSlidingWindow(int[] nums, int k) {        
        // sol stocheaza al k-lea cel mai mare element din fiecare fereastra.
        List<Integer> sol = new ArrayList<>();

        // window stocheaza elementele din fereastra curenta.
        Queue<Integer> window = new LinkedList<>();

        // heap este un TreeMap care stocheaza cele mai mari k elemente
        TreeMap<Integer, Integer> heap = new TreeMap<>(Collections.reverseOrder());

        for (int x : nums) {
            // Insereaza primele k elemente in TreeMap.
            if (window.size() < k) {
                window.add(x);
                heap.put(x, heap.getOrDefault(x, 0) + 1);
                continue;
            }

            // Insereaza al k-lea cel mai mare element in sol.
            sol.add(heap.firstKey());
            
            // Elimina cel mai vechi element din fereastra si din TreeMap.
            int oldX = window.poll();
            if (heap.get(oldX) == 1) {
                heap.remove(oldX);
            } else {
                heap.put(oldX, heap.get(oldX) - 1);
            }

            window.add(x);
            heap.put(x, heap.getOrDefault(x, 0) + 1);
        }
        // Insereaza al k-lea cel mai mare element din ultima fereastra in sol.
        sol.add(heap.firstKey());

        // Converteste lista sol in vector de intregi.
        int[] result = new int[sol.size()];
        for (int i = 0; i < sol.size(); i++) {
            result[i] = sol.get(i);
        }
        return result;
    }
}
