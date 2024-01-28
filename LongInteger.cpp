#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>

#include "LongInteger.h"

LongInteger::LongInteger()
{
    is_negative = false;
    digits.insertBack((std::byte)0);
}

LongInteger::LongInteger(long long num)
{
    is_negative = false;

    if (num < 0)
    {
        is_negative = true;
        num = -num;
    }

    if (num == 0)
    {
        digits.insertBack((std::byte)0);
    }

    while (num)
    {
        digits.insertFront((std::byte)(num % 10));
        num /= 10;
    }
}

LongInteger::LongInteger(std::string const &num)
{
    int begin_num = 0;
    is_negative = false;

    if (!isdigit(num[0]))
    {
        begin_num = 1;
        is_negative = num[0] == '-' ? true : false;
    }

    for (int i = num.length() - 1; i >= begin_num; i--)
    {
        digits.insertFront((std::byte)(num[i] - '0'));
    }
}

LongInteger::LongInteger(const LongInteger &other) : is_negative(other.is_negative), digits(other.digits) {}

LongInteger::LongInteger(List<std::byte> digits, bool is_negative)
{
    this->digits = digits;
    this->is_negative = is_negative;
}

LongInteger::~LongInteger()
{
    digits.clear();
}

List<int> convertByteListToIntList(const List<std::byte>& byteList) {
    List<int> intList(byteList.getSize());

    auto it_byte = byteList.begin();
    auto it_int = intList.begin();

    while (it_byte != byteList.end())
    {
        *it_int = static_cast<int>(*it_byte);

        ++it_byte;
        ++it_int;
    }


    return intList;
}

List<std::byte> convertByteListToIntList(const List<int>& intList) {
    List<std::byte> byteList(intList.getSize());

    auto it_byte = byteList.begin();
    auto it_int = intList.begin();

    while (it_int != intList.end())
    {
        *it_byte = static_cast<std::byte>(*it_int);

        ++it_byte;
        ++it_int;
    }


    return byteList;
}


LongInteger &LongInteger::operator=(const LongInteger &other)
{
    if (this != &other)
    {
        is_negative = other.is_negative;
        digits = other.digits;
    }
    return *this;
}

LongInteger LongInteger::operator+() const {
    LongInteger tmp = *this;
    return tmp;
}

LongInteger LongInteger::operator-() const {
    LongInteger tmp = *this;
    tmp.is_negative = !tmp.is_negative;
    return tmp;
}

std::ostream &operator<<(std::ostream &os, const LongInteger &obj)
{
    if (obj.is_negative)
    {
        os << '-';
    }

    for (auto digit : obj.digits)
    {
        os << static_cast<int>(digit);
    }

    return os;
}

LongInteger LongInteger::abs(const LongInteger &num)
{
    LongInteger res = num;
    res.is_negative = false;
    return res;
}

LongInteger &LongInteger::operator++()
{
    (*this).operator+=(LongInteger(1));
    return *this;
}

LongInteger LongInteger::operator++(int)
{
    LongInteger tmp = *this;
    ++(*this);
    return tmp;
}

LongInteger &LongInteger::operator+=(const LongInteger &num)
{
    if (!is_negative && num.is_negative)
    {
        LongInteger tmp = abs(num);
        return operator-=(tmp);
    }

    if (is_negative && !num.is_negative)
    {
        LongInteger tmp_this(*this);
        tmp_this.is_negative = false;


        LongInteger tmp(num);
        tmp -= tmp_this;

        
        *this = tmp;

        return *this;
    }

    List<int> number1;
    List<int> number2;
    List<std::byte> result;

    for (std::byte digit : this->digits)
    {
        number1.insertBack(static_cast<int>(digit));
    }

    for (std::byte digit : num.digits)
    {
        number2.insertBack(static_cast<int>(digit));
    }

    int carry = 0;
    make_equal_length(number1, number2);

    auto it1 = number1.rbegin();
    auto it2 = number2.rbegin();

    while (it1 != number1.rend())
    {
        int sum = (*it1) + (*it2) + carry;

        carry = sum / 10;
        sum = sum % 10;

        result.insertFront(static_cast<std::byte>(sum));

        --it1;
        --it2;
    }

    if (carry > 0)
    {
        result.insertFront(static_cast<std::byte>(carry));
    }

    this->digits = result;

    return *this;
}

LongInteger &LongInteger::operator-=(const LongInteger &num)
{
    if (!is_negative && num.is_negative)
    {
        return (*this).operator+=(abs(num));
    }

    if (is_negative && !num.is_negative)
    {
        std::cout << "-" << std::endl;
        
        LongInteger tmp(num);
        tmp.is_negative = true;
        return (*this).operator+=(tmp);
    }

    List<int> number1;
    List<int> number2;

    for (std::byte digit : this->digits)
    {
        number1.insertBack(static_cast<int>(digit));
    }

    for (std::byte digit : num.digits)
    {
        number2.insertBack(static_cast<int>(digit));
    }

    make_equal_length(number1, number2);

    bool is_numbers_equal = true;
    bool is_number1_bigger = false;

    auto it1 = number1.begin();
    auto it2 = number2.begin();
    while (it1 != number1.end())
    {
        if (*it1 > *it2)
        {
            is_numbers_equal = false;
            is_number1_bigger = true;
            break;
        }
        else if (*it1 < *it2)
        {
            is_numbers_equal = false;
            is_number1_bigger = false;
            break;
        }

        it1++;
        it2++;
    }

    if (is_numbers_equal)
    {

        List<std::byte> res;
        res.insertBack(static_cast<std::byte>(0));
        digits = res;
        is_negative = false;

        return *this;
    }

    List<std::byte> result;

    if (is_number1_bigger)
    {
        auto it1 = number1.rbegin();
        auto it2 = number2.rbegin();

        while (it1 != number1.rend())
        {
            if (*it1 < *it2)
            {
                *it1 += 10;
                --it1;
                *it1 -= 1;
                it1++;
            }

            int r = *it1 - *it2;
            result.insertFront(static_cast<std::byte>(r));

            it1--;
            it2--;
        }
    }
    else
    {
        auto it1 = number1.rbegin();
        auto it2 = number2.rbegin();

        while (it1 != number1.rend())
        {
            if (*it2 < *it1)
            {
                *it2 += 10;
                --it2;
                *it2 -= 1;
                it2++;
            }

            int r = *it2 - *it1;
            result.insertFront(static_cast<std::byte>(r));
        }
    }

    remove_heading_zeros(result);

    this->digits = result;

    return *this;
}

// remove this sheet
template <typename T>
void printList(List<T> lst)
{
    for (auto item : lst)
    {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}


///===========================================================================================================

LongInteger &LongInteger::operator*=(const LongInteger& other) {
    List<int> number1 = convertByteListToIntList(this->digits);
    List<int> number2 = convertByteListToIntList(other.digits);

    // std::cout << "number1: ";
    // printList<int>(number1);

    
    // auto it1 = number1.rbegin();
    // while (it1 != number1.rend())
    // {
    //     std::cout << (*it1) << " ";


    //     --it1;
    // }
    // std::cout << std::endl;
    
    List<int> numbers_to_add;

    auto it2 = number2.rbegin();
    while (it2 != number2.rend())
    {
        // std::cout << "it2: " << *(it2) << " ";
        
        int res = 0;
        int digit_to_insert = 0;

        auto it1 = number1.rbegin();
        while (it1 != number1.rend())
        {
            // std::cout << "it1: " << *(it1) << " ";

            res = (*it1) * (*it2) + (res / 10);
            digit_to_insert = res % 10;
            numbers_to_add.insertBack(digit_to_insert);


            std::cout << digit_to_insert << std::endl;

            --it1;
        }

        if (res > 0)
        {

        }

        --it2;
    }
    std::cout << std::endl;
    
    int sum = 0;

    auto it = numbers_to_add.begin();
    int power = 1;
    while (it != numbers_to_add.end())
    {
        sum += (*it) * power;
        power *= 10;

        ++it;
    }

    LongInteger result(static_cast<std::string>(std::to_string(sum)));
    // printList<int>(convertByteListToIntList(result.digits));

    this->is_negative = this->is_negative && other.is_negative;
    if (!(this->is_negative || other.is_negative))
    {
        this->is_negative = false;
    }

    (*this).digits = result.digits;
    (this)->is_negative = result.is_negative;

    return *this;
}

LongInteger LongInteger::operator*(const LongInteger& b) const
{
    

    return *this;
}

void LongInteger::make_equal_length(LongInteger &number1, LongInteger &number2)
{
    int diff_length = number1.digits.getSize() - number2.digits.getSize();

    if (diff_length > 0)
    {
        for (int i = 0; i < diff_length; i++)
        {
            number2.digits.insertFront((std::byte)0);
        }
    }
    else if (diff_length < 0)
    {
        for (int i = 0; i < -diff_length; i++)
        {
            number1.digits.insertFront((std::byte)0);
        }
    }
}

void LongInteger::make_equal_length(List<int> &number1, List<int> &number2)
{
    int diff_length = number1.getSize() - number2.getSize();

    if (diff_length > 0)
    {
        for (int i = 0; i < diff_length; i++)
        {
            number2.insertFront(0);
        }
    }
    else if (diff_length < 0)
    {
        for (int i = 0; i < -diff_length; i++)
        {
            number1.insertFront(0);
        }
    }
}

void LongInteger::make_equal_length(List<std::byte> &number1, List<std::byte> &number2)
{
    int diff_length = number1.getSize() - number2.getSize();

    if (diff_length > 0)
    {
        for (int i = 0; i < diff_length; i++)
        {
            number2.insertFront((std::byte)0);
        }
    }
    else if (diff_length < 0)
    {
        for (int i = 0; i < -diff_length; i++)
        {
            number1.insertFront((std::byte)0);
        }
    }
}

void LongInteger::remove_heading_zeros(List<std::byte> &result)
{
    auto it = result.begin();
    while (it != result.end())
    {
        if (*it == static_cast<std::byte>(0))
        {
            result.popFront();
            ++it;
        }
        else
        {
            break;
        }
    }

    if (result.isEmpty())
    {
        is_negative = false;
        result.insertBack((std::byte)0);
    }
}

void LongInteger::remove_heading_zeros(List<int> &result)
{
    auto it = result.begin();
    while (it != result.end())
    {
        if (*it == 0)
        {
            result.popFront();
            ++it;
        }
        else
        {
            break;
        }
    }

    if (result.isEmpty())
    {
        is_negative = false;
        result.insertBack(0);
    }
}

