### std::map
* [cppreference.com/map](https://en.cppreference.com/w/cpp/container/map)
* **sorted** associative container that contains **key-value pairs** with **unique keys**. (a.k.a `ordered keys`)

`std::map<T>` API:
* **operator []** e.g. `mp[key]` (return the value mapped to a key, performing an insertion if such key does not exist - `O(log n)`).
* **find()** e.g. `mp.find(some_value)` (return an iterator to the element having the same key or past-the-end iterator if not found - `O(log n)`).
* **erase()** e.g.`mp.erase(some_value)` (remove the element matching a key - `O(log n)`). 
