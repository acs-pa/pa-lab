// SPDX-License-Identifier: BSD-3-Clause

import java.util.Stack;

class MinStack {
    private Stack<Integer> st;      // Stiva principala pentru stocarea elementelor
    private Stack<Integer> minSt;   // Stiva auxiliara pentru stocarea elementelor minime

    // Constructor pentru initializarea obiectului MinStack
    public MinStack() {
        st = new Stack<>();
        minSt = new Stack<>();
    }

    // Adauga elementul val in stiva.
    public void push(int val) {
        st.push(val);

        // Daca stiva min este goala sau val este mai mic sau egal cu minimul curent,
        // il adaug in stiva min.
        if (minSt.isEmpty() || val <= minSt.peek()) {
            minSt.push(val);
        }
    }

    // Elimina elementul din varful stivei.
    public void pop() {
        if (st.peek().equals(minSt.peek())) {
            // Daca varful ambelor stive este acelasi, elimin si din stiva min.
            minSt.pop();
        }
        st.pop();
    }

    // Returneaza elementul din varful stivei.
    public int top() {
        return st.peek();
    }

    // Returneaza elementul minim din stiva.
    public int getMin() {
        return minSt.peek();
    }
}
