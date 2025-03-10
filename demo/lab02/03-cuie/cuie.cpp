// SPDX-License-Identifier: BSD-3-Clause

#include <algorithm> // sort
#include <iostream> // cout
#include <limits> // numeric_limits
#include <utility> // pair
#include <vector> // vector
using namespace std;

bool point_in_interval(const pair<int, int>& interval, int point) {
    return point >= interval.first && point <= interval.second;
}

bool right_edge_comparator(pair<int, int>& e1, pair<int, int>& e2) {
    // comparam scandurile dupa capatul drepata
    return (e1.second < e2.second);
}

vector<int> cover_intervals_greedy(vector<pair<int, int>>& intervals) {
    vector<int> nails; // pozitiile cuielor, a.k.a multimea M
    // ultimul punct inserat
    int last_point = numeric_limits<int>::min();

    // sortam invervalele dupa captul drepata
    sort(intervals.begin(), intervals.end(), right_edge_comparator);

    for (auto interval : intervals) {
        // daca intervalul nu contine ultimul punct adaugat
        if (!point_in_interval(interval, last_point)) {
            // il adaugam in multimea M
            nails.push_back(interval.second);
            // updatam ultimul punt inserat
            last_point = interval.second;
        }
    }

    return nails;
}

int main() {
    vector<pair<int, int>> intervals;
    intervals.push_back(make_pair(0, 2));
    intervals.push_back(make_pair(1, 7));
    intervals.push_back(make_pair(2, 6));
    intervals.push_back(make_pair(5, 14));
    intervals.push_back(make_pair(8, 16));

    cout << "Pozitiile cuielor [greedy]: ";
    auto nails2 = cover_intervals_greedy(intervals);
    for (auto nail : nails2) {
        cout << nail << " ";
    }
    cout << "\n";

    return 0;
}

// Compile:
// $ make
//
// Run:
// $ ./cuie
// Pozitiile cuielor [greedy]: 2 14
//
