### std::queue

* [cppreference.com/queue](https://en.cppreference.com/w/cpp/container/queue)
* A generic queue implementation.

`std::queue<T>` API:
* **empty()**: e.g. `queue.empty()` (check whether the queue is empty - `O(1)`)
* **front()**: e.g. `auto x = queue.front();` (return the first element from queue - `O(1)`).
* **back()**: e.g. `auto x = queue.back();` (return the last element from queue - `O(1)`).
* **push()**: e.g. `queue.push(some_value)` (insert element at the end - `O(1)`)
* **pop()**: e.g. `queue.pop()` (remove an element from the front of the queue - `O(1)`)
