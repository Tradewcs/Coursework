#include <iostream>

#include "LongInteger.cpp"

using namespace std;

int main1() {
    // LongInteger a = 389;
    LongInteger a("-50102040800453248742934629742373456");
    LongInteger b("4923453443457455123423466786562341434645745");

    cout << a.isNegative() << endl;
    cout << b.isNegative() << endl;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    a *= b;

    cout << "result of a * b = " << a << endl;
    
    return 0;
}


int main()
{
    LongInteger a = 4;
    LongInteger b = -3;

    cout << (a * b) << endl;

    cout << a << " " << b << endl;
}
