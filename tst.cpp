#include <iostream>
#include "LongInteger.cpp"

using namespace std;

#include <iostream>

int main1() {
    // LongInteger num1("12345678959412");
    // LongInteger num2(-987654321);

    LongInteger num1("508450110291000182375710100");
    LongInteger num2(987654321);

    std::cout << "num1: " << num1 << std::endl;
    std::cout << "num2: " << num2 << std::endl;
    std::cout << std::endl;

    LongInteger sum = num1 + num2;
    std::cout << "Sum: " << sum << std::endl;

    LongInteger difference = num1 - num2;
    std::cout << "Difference: " << difference << std::endl;

    LongInteger product = num1 * num2;
    std::cout << "Product: " << product << std::endl;

    LongInteger quotient = num1 / num2;
    std::cout << "Quotient: " << quotient << std::endl;

    LongInteger remainder = num1 % num2;
    std::cout << "Remainder: " << remainder << std::endl;

    if (num1 == num2) {
        std::cout << "num1 is equal to num2" << std::endl;
    } else {
        std::cout << "num1 is not equal to num2" << std::endl;
    }

    if (num1 < num2) {
        std::cout << "num1 is less than num2" << std::endl;
    } else {
        std::cout << "num1 is not less than num2" << std::endl;
    }


    return 0;
}

int main2()
{
    LongInteger num1("508450110291000182375710100");
    LongInteger num2("987654321");

    // std::cout << num1 << std::endl;
    std::cout << (num1 / num2) << std::endl;
    // std::cout << (((num1 / num2) * num2)) << std::endl;
    // std::cout << num1 << std::endl;
    // std::cout << (num1 - ((num1 / num2) * num2)) << std::endl;
    // std::cout << num1 % num2 << std::endl;

    return 0;
}

int main()
{
    LongInteger a("9001");
    LongInteger b("9");

    std::cout << a / b << std::endl;

    return 0;
}