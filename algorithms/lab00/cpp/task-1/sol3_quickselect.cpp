// SPDX-License-Identifier: BSD-3-Clause
#include <algorithm>
#include <vector>
using namespace std;

class Solution {
    public:
    int quicksort(vector<int>& v, int st, int dr, int k){
        if (st == dr)
            return v[st];
        int pivot = st + rand() % (dr - st + 1);
        int n = v.size();
        swap(v[pivot], v[dr]);
        int p = st;
        for (int i = st; i <= dr - 1; i++){
            if (v[i] < v[dr]){
                swap(v[p], v[i]);
                p++;
            }
        }
        swap(v[p], v[dr]);
        if (k == p)
            return v[p];
        else if (k < p)
            return quicksort(v, st, p, k);
        else
            return quicksort(v, p + 1, dr, k);
    }

    int solution(vector<int>& v, int k){
        int n = v.size();
        return quicksort(v, 0, n - 1, n - k);
    }
};
