#include <bits/stdc++.h>
using namespace std;

bool end_hour_comp(pair<int, int>& e1, pair<int, int>& e2) {
    // comparam doar dupa pozitii, tag-ul este folosit doar la identificare
    return (e1.second < e2.second);
}

vector<pair<int, int>> plan(vector<pair<int, int>>& intervals) {
    vector<pair<int, int>> plan;
    // se sorteaza intervalele pe baza orei de sfarsit a spectacolelor
    sort(intervals.begin(), intervals.end(), end_hour_comp);

    // se ia ultimul spectacol ca terminat la -oo pt a putea incepe cu
    // cel mai devreme
    int last_end = INT_MIN;
    for (auto interval : intervals) {
        // daca inceputul intervalului curent este dupa sfarsitul ultimului
        // spectacol (last_end) il adaugam in lista de spectacole la care
        // se participa
        if (interval.first >= last_end) {
            plan.push_back(interval);
            // dupa ce am adaugat un spectacol, updatam ultimul sfarsit de spectacol
            last_end = interval.second;
        }
    }
    return plan;
}

int main() {
    vector<pair<int, int>> intervals;
    intervals.push_back(make_pair(1, 19));
    intervals.push_back(make_pair(0, 2));
    intervals.push_back(make_pair(1, 7));
    intervals.push_back(make_pair(2, 6));
    intervals.push_back(make_pair(5, 14));
    intervals.push_back(make_pair(8, 16));

    vector<pair<int, int>> planned_intervals = plan(intervals);
    for (auto spectacle : planned_intervals) {
        cout << "(" << spectacle.first << " " << spectacle.second << ")";
    }
    cout << "\n";

    return 0;
}

// Compile:
// $ make
//
// Run:
// $ ./spectacole
// (0 2)(2 6)(8 16)
//
