// SPDX-License-Identifier: BSD-3-Clause

import java.util.Arrays;
import java.util.Collections;

class Solution {
    // Solutie: Sortam vectorul in ordine descrescatoare si returnam al k-lea cel mai mare element.
    // Complexitate: O(nlogn)
    public int findKthLargest(int[] nums, int k) {
        Integer[] numsBoxed = Arrays.stream(nums).boxed().toArray(Integer[]::new);
        Arrays.sort(numsBoxed, Collections.reverseOrder());
        return numsBoxed[k - 1];
    }
}
