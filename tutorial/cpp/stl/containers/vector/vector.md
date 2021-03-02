### std::vector 
* [cppreference/vector](https://en.cppreference.com/w/cpp/container/vector)

A resizable array container which:
* uses dynamic allocation (allocations and deallocations are automatically handled by the internal logic).
* has the array interface (a.k.a. `array[i]`)

Note: probably the most used container during the PA laboratories. 

`std::vector<T>` API:
* **size()** = returns the number of elements in the array; the valid (allocated elements) are: `array[0], array[1], array[2], ..., array[ array.size() - 1 ]`
* **operator[]**: e.g. `array[i]` (access element -` O(1)`)
*  **push_back()**: e.g. `array.push_back(some_value)` (insert at the end - `O(1)`)
*  **pop_back()**: e.g. `array.pop_back()` (remove last element - `O(1)`)
* **insert / erase()** (insert / removal at a specific position - `O(n)`).
*  **front()/back()**: e.g. `auto x = array.front();` / `auto x = array.back();` (returns reference to the first / last element from array - `O(1)`).

#### How to iterate a vector

##### index-based loop
C-like iteration using index.

```cpp
#include <bits/stdc++.h>

int main() {
    std::vector<int> v;
    
    // operations on v - e.g. change elements

    for (int i = 0; i < v.size(); ++i) { // iterate over v using index-based loop
        // do stuff with v[i] - print, change, etc
    }

    return 0;
}
```

#####  for-each loop
We can do a for-each loop over most of the containers.

```cpp
for (const auto& element : container) {
     // print element or add element to a sum
     // note: because it's a const reference we cannot change element here
}
// or
for (auto& element : container) {
     // print element or add element to a sum
     // or
     // change element here (e.g. element = 2 * element); will double every element from container_
}
``` 
Example - vector of integers
```cpp
int main() {
    std::vector<int> v;

    // operations on v
    int sum = 0;
    for (const auto &x : v) {  // don't want to change x in the loop -> use const reference
        sum += x; // add the current element to the sum
    }

    for (auto &x : v) { // want to change x in the loop -> use non-const reference
       x = 2 * x; // double the current element
    }
 
    return 0;
}
```

##### C++ iteration

Most of the containers have an internal class called `iterator` which simulates a pointer. Using the start iterator (a.k.a. the start pointer) , if we use the current iterator (value) and go the next one, by doing these steps into a loop, we can traverse the entire collection until we reach the stop iterator (a.k.a. the stop pointer), which is considered to be outside the container - a.k.a. passed after the actual end of the container.

Note: You should use this method of iteration if and only if you want to remove or add elements in the middle of the container (a.k.a. not the first or the last element).

```cpp
#include <bits/stdc++.h>

int main() {
    std::vector<int> v;

    // operations on v

    for (auto it = v.begin(); it != v.end(); ++it) {
        // do stuff with *it (similar to v[i])
        // e.g. *it = 2;                    // change current element to 2
        // e.g. std::cout << *it << "\n";  // print current element
    }
    return 0;
}
```

#### Which iteration method is better?

* choose the `index-based loop` if you need to use the `index` the element (e.g. dynamic programming algorithms)
* choose the `iterator-based loop` if you need to remove / insert elements into the array, but `not` the first/last position
* otherwise, always use the `for-each loop`