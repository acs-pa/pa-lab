// SPDX-License-Identifier: BSD-3-Clause

// Stiva principala pentru stocarea elementelor; stiva auxiliara pentru minime.
struct MinStack {
    st: Vec<i32>,
    min_st: Vec<i32>,
}

impl MinStack {
    fn new() -> Self {
        MinStack {
            st: Vec::new(),
            min_st: Vec::new(),
        }
    }

    // Adauga elementul val in stiva.
    fn push(&mut self, val: i32) {
        self.st.push(val);
        if self.min_st.is_empty() || val <= *self.min_st.last().unwrap() {
            self.min_st.push(val);
        }
    }

    // Elimina elementul din varful stivei.
    fn pop(&mut self) {
        let top_val = *self.st.last().unwrap();
        if top_val == *self.min_st.last().unwrap() {
            self.min_st.pop();
        }
        self.st.pop();
    }

    // Returneaza elementul din varful stivei.
    fn top(&self) -> i32 {
        *self.st.last().unwrap()
    }

    // Returneaza elementul minim din stiva.
    fn get_min(&self) -> i32 {
        *self.min_st.last().unwrap()
    }
}
