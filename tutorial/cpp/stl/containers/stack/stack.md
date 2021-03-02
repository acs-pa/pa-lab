### std::stack
* [cppreference.com/stack](https://en.cppreference.com/w/cpp/container/stack)
* A generic stack implementation.

`std::stack<T>` API:
* **empty()** e.g. ```stack.empty();```(check whether the stack is empty - `O(1)`)
* **top()**: e.g. ```auto x = stack.top();``` (return the top element in the stack - `O(1)`)
* **push()**: e.g. ```stack.push(some_value)``` (insert an element at the top of the stack - `O(1)`)
* **pop()**: e.g. ```stack.pop()``` (remove the top element - `O(1)`)