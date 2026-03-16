#include <iostream>
#include <vector>

int main() {
    const size_t size = 32 << 20;
    std::vector<int> buf(size / sizeof(int), 42);
    
    volatile int sum = 0;
    for (int val: buf) sum += val;

    return 0;
}