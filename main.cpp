#include <iostream>
#include <random>
#include <chrono>

using namespace std;

#include "LongInteger.cpp"

using namespace std;

int main1()
{
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
    LongInteger a("2505");
    LongInteger b("5");

    cout << a << " " << b << endl;
    cout << (a / b) << endl;

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

int main6()
{
    LongInteger a("-3");
    LongInteger b("-2");

    a %= b;

    cout << a << endl;

    return 0;
}

int generate_random_int(std::random_device &rd)
{
    std::mt19937 gen(rd());

    int lowerBound = -429496729;
    int upperBound = 4294967295;

    std::uniform_int_distribution<int> distribution(lowerBound, upperBound);
    int randomNumber = distribution(gen);

    return randomNumber;
}



int main7()
{
    // LongInteger a = 901;
    // LongInteger b = 9;

    // LongInteger a("9010009090000000042400422468");
    // LongInteger b = 304043141;

    // cout << a / b << endl; // 84


    int i = 0;
    while (i++ < 100)
    {
        std::random_device rd;

        int a_int = generate_random_int(rd);
        int b_int = generate_random_int(rd);
        b_int /= 5;

        std::cout << a_int << " " << b_int << std::endl;

        LongInteger a = a_int;
        LongInteger b = b_int;

        int res_int = a_int / b_int;
        LongInteger res = a / b;

        std::cout << a / b << std::endl;
        std::cout << a_int / b_int << std::endl;

        if (res != LongInteger(res_int))
        {
            std::cout << "palundra" << std::endl;
            break;
        }
    }

    return 0;
}

int main()
{
    // LongInteger a("7400000130000064924751000000000001");
    // LongInteger b("48327421500003472");

    LongInteger a = 9010;
    LongInteger b = 90;

    cout << a / b << endl;

    return 0;
}