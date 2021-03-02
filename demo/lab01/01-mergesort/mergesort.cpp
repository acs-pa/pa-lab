#include <bits/stdc++.h>
using namespace std;

vector<int> v;

void merge_halves(int left, int right) {
    int mid = (left + right) / 2;
    vector<int> aux;
    int i = left, j = mid + 1;
    while (i <= mid && j <= right) {
        if (v[i] <= v[j]) {
            aux.push_back(v[i]);
            i++;
        } else {
            aux.push_back(v[j]);
            j++;
        }
    }
    while (i <= mid) {
        aux.push_back(v[i]);
        i++;
    }
    while (j <= right) {
        aux.push_back(v[j]);
        j++;
    }

    for (int k = left; k <= right; k++) {
        v[k] = aux[k - left];
    }
}

void merge_sort(int left, int right) {
    if (left >= right)
        return;
    int mid = (left + right) / 2;
    merge_sort(left, mid);
    merge_sort(mid + 1, right);
    merge_halves(left, right);
}

int main() {
    random_device rd;
    for (auto i = 0; i < 10; i++) {
        v.push_back(rd() % 100);
    }

    cout << "Vectorul initial: ";
    for (auto i = 0u; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << "\n";

    merge_sort(0, v.size() - 1);

    cout << "Vectorul sortat: ";
    for (auto i = 0u; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << "\n";

    return 0;
}

// Compile:
// $ make
//
// Run:
// $ ./mergesort
// Vectorul initial: 84 77 18 8 46 2 52 95 39 55
// Vectorul sortat: 2 8 18 39 46 52 55 77 84 95
//
