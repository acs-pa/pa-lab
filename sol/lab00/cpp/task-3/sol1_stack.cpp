// SPDX-License-Identifier: BSD-3-Clause

#include <algorithm>
#include <stack>
using namespace std;

class MinStack {
private:
    stack<int> st; // Stiva principala pentru stocarea elementelor
    stack<int> minSt; // Stiva auxiliara pentru stocarea elementelor minime

public:
    // Constructor pentru initializarea obiectului MinStack
    MinStack() { }

    // Adauga elementul val in stiva.
    void push(int val) {
        st.push(val);

        // Daca stiva min este goala sau val este mai mic sau egal cu minimul curent,
        // il adauga in stiva min.
        if (minSt.empty() || val <= minSt.top()) {
            minSt.push(val);
        }
    }

    // Elimina elementul din varful stivei.
    void pop() {
        if (st.top() == minSt.top()) {
            // Daca varful ambelor stive este acelasi, elimina si din stiva min.
            minSt.pop();
        }
        st.pop();
    }

    // Returneaza elementul din varful stivei.
    int top() { return st.top(); }

    // Returneaza elementul minim din stiva.
    int getMin() { return minSt.top(); }
};
