#include "LongInteger.h"
#include <iostream>

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

    if (num[0] == '-')
    {
        is_negative = true;
        begin_num = 1;
    }
    else if (num[0] == '+')
    {
        begin_num = 1;
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
    return *this;
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

        // std::cout << "asdf" << std::endl;
        
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

LongInteger &LongInteger::operator*=(const LongInteger& other) {
    List<int> number1 = convertByteListToIntList(this->digits);
    List<int> number2 = convertByteListToIntList(other.digits);

    auto it1 = number1.rbegin();
    auto it2 = number2.rbegin();

    List<int> numbers_to_add;

    while (it1 != number1.rend())
    {
        int res;
        int digit_to_insert;

        numbers_to_add.insertBack(0);

        while (it2 != number2.rend())
        {
            res = *it1 + *it2 + res / 10;
            digit_to_insert = res % 10;

            res -= digit_to_insert;

            numbers_to_add.insertBack(digit_to_insert);

            it2--;
        }

        it1--;
    }

    int res = 0;

    auto it = numbers_to_add.begin();
    while (it != numbers_to_add.end())
    {
        res += *it;
    }

    List<int> result(std::to_string(res));

    this->is_negative = this->is_negative && other.is_negative;
    if (!(this->is_negative || other.is_negative))
    {
        this->is_negative = false;
    }

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

List<int> convertByteListToIntList(const List<std::byte>& byteList) {
    List<int> intList(byteList.getSize());
    
    std::transform(byteList.begin(), byteList.end(), intList.begin(),
                   [](std::byte b) { return static_cast<int>(b); });

    return intList;
}


List<std::byte> convertIntListToByteList(const List<int>& intList) {
    List<std::byte> byteList(intList.getSize());
    
    std::transform(byteList.begin(), byteList.end(), intList.begin(),
                   [](std::byte b) { return static_cast<int>(b); });

    return byteList;
}
