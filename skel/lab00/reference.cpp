#include <iostream>

using namespace std;

void modify_x(int &x)
{
    x = 123;
}

int main()
{
    int x = 9292;
    modify_x(x);
    cout << "x is " << x << endl;
    return 0;
}