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

int main2()
{
    LongInteger a("-51000000000000041244146780000017234546");
    LongInteger b("-0");

    cout << a << endl;
    cout << a.multiply_LongInteger_by_digit(a, -9) << endl;
    cout << a << endl;

    return 0;
}

int main3()
{
    LongInteger a = -510;
    LongInteger b = 510;

    cout << (a != b) << endl;
    // cout << (b < a) << endl;


    return 0;
}


int main4()
{
    LongInteger a("0");
    LongInteger b("-4200479067734523462498521834493485673219619999888900003");

    

    cout << a << " " << b << endl;
    cout << (a * b) << endl;
    


    return 0;
}


int main5()
{
    LongInteger a("10");
    LongInteger b("2");

    LongInteger c = a % b;
    cout << c << endl;
    // cout << (a / b) << endl;

    return 0;
}

int main()
{
    LongInteger a = 6;
    LongInteger b = 4;

    a %= b;

    cout << a << endl;


    return 0;
}