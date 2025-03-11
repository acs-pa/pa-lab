#include <iostream>

using namespace std;

struct Complex
{
    int re,im;

    void print(){
        cout << re << " + i" << im << endl;
    }
};

int main()
{
    Complex c1,c2;
    c1.re = 0;
    c1.im = 3;

    c2.re = -1;
    c2.im = 19;

    c1.print();
    c2.print();

    return 0;
}
