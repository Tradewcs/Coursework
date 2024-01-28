#include <iostream>

#include "LongInteger.cpp"

using namespace std;

int main() {
    // LongInteger a = 389;
    LongInteger a = 389;
    LongInteger b = 28;

    a *= b;

    cout << "result of a * b = " << a << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    
    return 0;
}
