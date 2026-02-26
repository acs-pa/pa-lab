// SPDX-License-Identifier: BSD-3-Clause
// Run: rustc stack.rs && ./stack

fn main() {
    let mut st: Vec<i32> = Vec::new();
    st.push(1);
    st.push(2);
    st.push(3);

    while let Some(top) = st.pop() {
        println!("{}", top);
    }
    // print: 3 2 1
}
