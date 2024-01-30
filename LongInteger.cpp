#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>

#include "LongInteger.h"

LongInteger::LongInteger()
{
    is_negative = false;
    digits.insertBack(static_cast<u_int16_t>(0));
}

LongInteger::LongInteger(long long num)
{
    if (num == 0)
    {
        digits.insertBack(0);
        is_negative = false;
        return;
    }

    is_negative = false;
    if (num < 0)
    {
        is_negative = true;
        num = -num;
    }

    while (num > 0)
    {
        u_int16_t val = num % 10000;
        digits.insertFront(val);

        num /= 10000;
    }
}

LongInteger::LongInteger(std::string const &str_num)
{
    std::string num = str_num;
    
    if (num.empty())
    {
        LongInteger(0);
        return;
    }

    if (!isdigit(num[0]))
    {
        if (num[0] == '-')
        {
            this->is_negative = true;
        }
        else
        {
            this->is_negative = false;
        }
    }

    num.erase(num.begin());

    for (int i = num.size() - 1; i >= 0; i -= 4) {
        int value = 0;
        int multiplier = 1;

        for (int j = 0; j < 4 && i - j >= 0; ++j) {
            value += (num[i - j] - '0') * multiplier;
            multiplier *= 10;
        }

        digits.insertFront(value);
    }
}

LongInteger::LongInteger(const LongInteger &other) : is_negative(other.is_negative), digits(other.digits) {}

LongInteger::LongInteger(List<u_int16_t> digits, bool is_negative)
{
    this->digits = digits;
    this->is_negative = is_negative;
}

LongInteger::~LongInteger()
{
    digits.clear();
}

bool LongInteger::isNegative() const
{
    return is_negative;
}

List<int> convertByteListToIntList(const List<u_int16_t>& byteList) {
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

List<u_int16_t> convertByteListToIntList(const List<int>& intList) {
    List<u_int16_t> byteList(intList.getSize());

    auto it_byte = byteList.begin();
    auto it_int = intList.begin();

    while (it_int != intList.end())
    {
        *it_byte = static_cast<u_int16_t>(*it_int);

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
    if (obj.is_negative) {
        os << '-';
    }

    bool is_first_group = true;
    for (u_int16_t group : obj.digits) {
        if (!is_first_group) {
            os << std::setw(4) << std::setfill('0');
        }

        os << group;
        is_first_group = false;
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

    List<u_int16_t> number1 = (*this).digits;
    List<u_int16_t> number2 = num.digits;;

    List<u_int16_t> result;

    int carry = 0;
    make_equal_length(number1, number2);

    auto it1 = number1.rbegin();
    auto it2 = number2.rbegin();

    while (it1 != number1.rend())
    {
        int sum = (*it1) + (*it2) + carry;

        carry = sum / 10000;
        sum = sum % 10000;

        result.insertFront(static_cast<u_int16_t>(sum));

        --it1;
        --it2;
    }

    if (carry > 0)
    {
        result.insertFront(static_cast<u_int16_t>(carry));
    }

    this->digits = result;

    return *this;
}

LongInteger LongInteger::operator+(const LongInteger &num) const
{
    LongInteger tmp = *this;
    tmp += num;

    return tmp;
}

LongInteger &LongInteger::operator-=(const LongInteger &num)
{
    if (!is_negative && num.is_negative)
    {
        return (*this).operator+=(abs(num));
    }

    if (is_negative && !num.is_negative)
    {
        // std::cout << "-" << std::endl;
        
        LongInteger tmp(num);
        tmp.is_negative = true;
        return (*this).operator+=(tmp);
    }

    List<int> number1;
    List<int> number2;

    for (u_int16_t digit : this->digits)
    {
        number1.insertBack(static_cast<int>(digit));
    }

    for (u_int16_t digit : num.digits)
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

        List<u_int16_t> res;
        res.insertBack(static_cast<u_int16_t>(0));
        digits = res;
        is_negative = false;

        return *this;
    }

    List<u_int16_t> result;

    if (is_number1_bigger)
    {
        auto it1 = number1.rbegin();
        auto it2 = number2.rbegin();

        while (it1 != number1.rend())
        {
            if (*it1 < *it2)
            {
                *it1 += 10000;

                auto it1_borrow = it1;
                --it1_borrow;
 
                while (it1_borrow != number1.rend() && *it1_borrow == 0)
                {
                    *it1_borrow = 9999;
                    --it1_borrow;
                }

                *it1_borrow -= 1;
            }

            int r = *it1 - *it2;
            result.insertFront(static_cast<u_int16_t>(r));

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
                *it2 += 10000;

                auto it2_borrow = it2;
                --it2_borrow;
               
                while (it2_borrow != number1.rend() && *it2_borrow == 0)
                {
                    *it2_borrow = 9999;
                    --it2_borrow;
                }

                *it2_borrow -= 1;
            }

            int r = *it2 - *it1;
            result.insertFront(static_cast<u_int16_t>(r));

            it1--;
            it2--;
        }

        this->is_negative = true;
    }

    remove_heading_zeros(result);

    this->digits = result;

    return *this;
}

LongInteger LongInteger::operator-(const LongInteger& other) const
{
    LongInteger tmp = *this;
    tmp -= other;

    return tmp;
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
    
    List<LongInteger> numbers_to_add;

    auto it2 = number2.rbegin();
    while (it2 != number2.rend())
    {
        // std::cout << "it2: " << *(it2) << " ";
        
        int res = 0;
        int digit_to_insert = 0;

        LongInteger result;
        result.digits.popBack();

        auto it1 = number1.rbegin();
        while (it1 != number1.rend())
        {
            // std::cout << "it1: " << *(it1) << " ";

            res = (*it1) * (*it2) + (res / 10);
            digit_to_insert = res % 10;

            // std::cout << "digit: " << digit_to_insert << " ";

            result.digits.insertFront(static_cast<u_int16_t>(digit_to_insert));


            --it1;
        }

        res -= digit_to_insert;
        res /= 10;
        if (res > 0)
        {
            // std::cout << "res: " << res << std::endl;

            result.digits.insertFront(static_cast<u_int16_t>(res));
        }

        // std::cout << "result " << result << std::endl;
        numbers_to_add.insertBack(result);

        --it2;
    }
    // std::cout << std::endl;


    LongInteger sum = 0;
    int power = 0;
    for (LongInteger num : numbers_to_add)
    {
        for (int i = 0; i < power; ++i)
        {
            num.digits.insertBack(static_cast<u_int16_t>(0));
        }

        sum += num;
        ++power;
    }


    // printList<int>(convertByteListToIntList(result.digits));


    this->is_negative = this->is_negative != other.is_negative;

    if (!this->is_negative && !other.is_negative)
    {
        this->is_negative = false;
    }

    (*this).digits = sum.digits;

    return *this;
}

LongInteger LongInteger::operator*(const LongInteger& b) const
{
    LongInteger tmp = *this;
    tmp *= b;

    return tmp;
}

void LongInteger::make_equal_length(LongInteger &number1, LongInteger &number2)
{
    int diff_length = number1.digits.getSize() - number2.digits.getSize();

    if (diff_length > 0)
    {
        for (int i = 0; i < diff_length; i++)
        {
            number2.digits.insertFront((u_int16_t)0);
        }
    }
    else if (diff_length < 0)
    {
        for (int i = 0; i < -diff_length; i++)
        {
            number1.digits.insertFront((u_int16_t)0);
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

void LongInteger::make_equal_length(List<u_int16_t> &number1, List<u_int16_t> &number2)
{
    int diff_length = number1.getSize() - number2.getSize();

    if (diff_length > 0)
    {
        for (int i = 0; i < diff_length; i++)
        {
            number2.insertFront((u_int16_t)0);
        }
    }
    else if (diff_length < 0)
    {
        for (int i = 0; i < -diff_length; i++)
        {
            number1.insertFront((u_int16_t)0);
        }
    }
}

void LongInteger::remove_heading_zeros(List<u_int16_t> &result)
{
    auto it = result.begin();
    while (it != result.end())
    {
        if (*it == static_cast<u_int16_t>(0))
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
        result.insertBack((u_int16_t)0);
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

