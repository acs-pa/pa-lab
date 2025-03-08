#include <iostream>     // cout
#include <vector>       // vector   
using namespace std;

int main() {
    vector<int> v; // a vector of ints
    v.push_back(5);
    v.push_back(1);
    v.push_back(3);
    cout << v.size() << "\n"; // 3 elements
    cout << v.back() << "\n"; // the last element is 3
    v.pop_back();
    cout << v.size() << "\n"; // the size is 2
    cout << v.back() << "\n"; // the last element is 1
    return 0;
}
