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

        if (sum > 9)
        {
            carry = 1;
            sum -= 10;
        }
        else
        {
            carry = 0;
        }

        result.insertFront(static_cast<std::byte>(sum));

        ++it1;
        ++it2;
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

void LongInteger::remove_heading_zeros()
{
    auto it = digits.begin();

    while (it != digits.end() && *it == (std::byte)0)
    {
        digits.popFront();
        ++it;
    }

    if (digits.isEmpty())
    {
        is_negative = false;
        digits.insertBack((std::byte)0);
    }
}