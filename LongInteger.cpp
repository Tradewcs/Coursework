#include <algorithm>
#include <cctype>
#include <cmath>
#include <iomanip>
#include <iostream>

#include "LongInteger.h"

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
        u_int16_t val = num % base;
        digits.insertFront(val);

        num /= base;
    }
}

LongInteger::LongInteger(std::string const &str_num)
{
    std::string num = str_num;
    this->is_negative = false;

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

        num.erase(num.begin());
    }

    int log10_base = log10(base);
    for (int i = num.size() - 1; i >= 0; i -= log10_base) {
        int value = 0;
        int multiplier = 1;

        for (int j = 0; j < log10_base && i - j >= 0; ++j) {
            value += (num[i - j] - '0') * multiplier;
            multiplier *= 10;
        }

        digits.insertFront(value);
    }

    printList<u_int16_t>(digits);
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
            os << std::setw(log10(obj.base)) << std::setfill('0');
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

        carry = sum / base;
        sum = sum % base;

        result.insertFront(sum);

        --it1;
        --it2;
    }

    if (carry > 0)
    {
        result.insertFront(carry);
    }

    this->digits = result;
    // printList<u_int16_t>(number1);
    // printList<u_int16_t>(number2);

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
        LongInteger tmp(num);
        tmp.is_negative = true;
        return (*this).operator+=(tmp);
    }

    List<u_int16_t> number1 = (*this).digits;
    List<u_int16_t> number2 = num.digits;

    // printList<u_int16_t>(number1);
    // printList<u_int16_t>(number2);

    make_equal_length(number1, number2);

    // printList<u_int16_t>(number1);
    // printList<u_int16_t>(number2);


    bool is_numbers_equal = *this == num;
    bool is_number1_bigger = *this > num;

    auto it1 = number1.begin();
    auto it2 = number2.begin();


    if (is_numbers_equal)
    {

        List<u_int16_t> res;
        res.insertBack(0);
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
                *it1 += base;

                auto it1_borrow = it1;
                --it1_borrow;
 
                while (it1_borrow != number1.rend() && *it1_borrow == 0)
                {
                    *it1_borrow = this->base - 1;
                    --it1_borrow;
                }

                *it1_borrow -= 1;
            }

            int r = *it1 - *it2;
            result.insertFront(r);

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
                *it2 += base;

                auto it2_borrow = it2;
                --it2_borrow;
               
                while (it2_borrow != number1.rend() && *it2_borrow == 0)
                {
                    *it2_borrow = this->base - 1;
                    --it2_borrow;
                }

                *it2_borrow -= 1;
            }

            int r = *it2 - *it1;
            result.insertFront(r);

            it1--;
            it2--;
        }

        this->is_negative = !this->is_negative;
    }


    this->digits = result;
    (*this).remove_heading_zeros();

    return *this;
}

LongInteger LongInteger::operator-(const LongInteger& other) const
{
    // std::cout << *this << "\n  " << other << std::endl << std::endl;
    LongInteger tmp = *this;
    tmp -= other;

    return tmp;
}



///===========================================================================================================

LongInteger LongInteger::multiply_LongInteger_by_digit(const LongInteger& num, int digit)
{
    bool is_digit_negative = digit < 0;
    if (is_digit_negative) {
        digit = -digit;
    }

    auto it = num.digits.rbegin();
    int carry = 0;

    List<u_int16_t> result;

    while (it != num.digits.rend())
    {
        int tmp = (*it) * digit + carry;
        result.insertFront(tmp % base);
        carry = tmp / base;

        it--;
    }

    while (carry > 0)
    {
        result.insertFront(carry % base);
        carry /= base;
    }

    bool is_result_negative = false;
    if (num.is_negative != is_digit_negative) {
        is_result_negative = true;
    }

    return LongInteger(result, is_result_negative);
}

LongInteger &LongInteger::operator*=(const LongInteger& b)
{
    if ((*this) == LongInteger(0))
    {
        return *this;
    }

    if (b == LongInteger(0))
    {
        *this = LongInteger(0);
        return *this;
    }

    List<u_int16_t> result(this->digits.getSize() + b.digits.getSize());

    int carry = 0;

    List<u_int16_t>::Iterator it_result_save = result.rbegin();

    auto it2 = b.digits.rbegin();
    while (it2 != b.digits.rend())
    {
        bool is_result_saved = false;

        auto it_result = it_result_save;
        auto it1 = this->digits.rbegin();
        while (it1 != this->digits.rend())
        {
            int tmp = (*it1) * (*it2) + carry + (*it_result);
            carry = tmp / base;

            *it_result = tmp % base;
            it_result--;

            if (!is_result_saved) {
                it_result_save = it_result;
                is_result_saved = true;
            }

            it1--;
        }

        *it_result = carry;
        carry = 0;

        it2--;
    }

    if (carry != 0)
    {
        result.insertFront(0);
        auto it_result = result.begin();
        *it_result = carry % base;
        // carry /= base;
    }

    (*this).digits = result;
    (*this).is_negative = (is_negative != b.is_negative);
    (*this).remove_heading_zeros();

    return *this;
}


LongInteger LongInteger::operator*(const LongInteger& b) const
{
    LongInteger tmp = *this;
    tmp *= b;

    return tmp;
}

LongInteger &LongInteger::operator/=(const LongInteger &b)
{
    if (b == LongInteger(0))
    {
        throw std::invalid_argument("Division by zero");
    }

    if (abs(*this) < abs(b))
    {
        *this = LongInteger(0);
        return *this;
    }

    LongInteger result;
    result.digits.popBack();

    LongInteger current_value = 0;
    for (auto it_this = (*this).digits.rbegin(); it_this != (*this).digits.rend(); --it_this)
    {
        current_value = current_value * base;
        *current_value.digits.rbegin() = *it_this;

        LongInteger x = binarySearchDivide(current_value, abs(b));
        current_value -= abs(b) * x;
        
        result.digits.insertFront(*x.digits.begin());
    }

    result.remove_heading_zeros();
    
    result.is_negative = (*this).is_negative != b.is_negative;
    *this = result;
    
    return *this;
}

// LongInteger &LongInteger::operator/=(const LongInteger &b)
// {
//     if (b == LongInteger(0))
//     {
//         throw std::invalid_argument("Division by zero");
//     }

//     if (abs(*this) < abs(b)) {
//         *this = LongInteger(0);
//         return *this;
//     }
    
//     LongInteger result = 0;
//     bool result_is_negative = is_negative != b.is_negative;

//     LongInteger number1 = abs(*this);
//     LongInteger number2 = abs(b);

//     LongInteger tmp = 0;
//     auto it_this = number1.digits.begin();
//     while (it_this != number1.digits.end())
//     {
//         while (tmp.digits.getSize() < number2.digits.getSize() && it_this != (number1).digits.end())
//         {
//             // tmp *= base;
//             // tmp += *it_this;
            
//             for (int i = 0; i < log10(base); ++i)
//             {
//                 tmp.digits.insertBack(*it_this);
//                 it_this++;
//             }

//         }

//         std::cout << "tmp " << tmp << std::endl;

//         LongInteger part_of_result = binarySearchDivide(tmp, number2);
//         // result *= base;
//         // result += part_of_result;

//         for (auto digit : part_of_result.digits)
//         {
//             result.digits.insertBack(digit);
//         }


//         std::cout << "part_of_result " << part_of_result << std::endl;

//         LongInteger num_to_substract = part_of_result * number2;
//         add_zeros_to_the_end(num_to_substract, number1.digits.getSize() - tmp.digits.getSize());
//         // reverse_make_equal_length(number1, num_to_substract);

//         std::cout << "num_to_substract " << num_to_substract << std::endl;

//         // number1 -= num_to_substract;
//         tmp -= num_to_substract;
//         tmp.remove_heading_zeros();
//         // if (tmp == LongInteger(0))
//         // {
//         //     result.digits.insertBack(0);
//         // }

//         std::cout << "num1 " << number1 << std::endl;
//     }

//     *this = result;
//     (*this).is_negative = result_is_negative;

//     return *this;
// }

LongInteger LongInteger::binarySearchDivide(const LongInteger& divident, const LongInteger& divisor)
{
    int x = 0;

    int l = 0;
    int r = base;

    while (l <= r)
    {
        int m = (l + r) >> 1;

        LongInteger current = divisor * m;
        if (current <= divident)
        {
            x = m;
            l = m + 1;
        }
        else
        {
            r = m - 1;
        }

        // std::cout << l << " " << r << " " << m << std::endl;
    }

    LongInteger result(x);

    return result;
}

LongInteger LongInteger::operator/(const LongInteger &b) const
{
    LongInteger tmp = *this;
    tmp /= b;

    return tmp;
}

LongInteger &LongInteger::operator%=(const LongInteger &b)
{
    *this = abs(*this);
    // std::cout << ((*this / abs(b)) * abs(b)) << std::endl;
    *this -= (*this / abs(b)) * abs(b);
    (*this).is_negative = b.is_negative;

    return *this;
}

LongInteger LongInteger::operator%(const LongInteger& b) const
{
    LongInteger tmp = *this;
    tmp %= b;

    return tmp;
}

bool LongInteger::operator<(const LongInteger& b) const
{
    if (this->is_negative != b.is_negative)
    {
        return this->is_negative;
    }

    List<u_int16_t> number1 = this->digits;
    List<u_int16_t> number2 = b.digits;

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
        return false;
    }

    if (this->is_negative)
    {
        return is_number1_bigger;
    }
    else
    {
        return !is_number1_bigger;
    }
}

bool LongInteger::operator>(const LongInteger& b) const
{
    return !operator<=(b);
}

bool LongInteger::operator==(const LongInteger& b) const
{
    if (this->is_negative != b.is_negative)
    {
        return false;
    }

    List<u_int16_t> number1 = this->digits;
    List<u_int16_t> number2 = b.digits;

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

    return is_numbers_equal;
}

bool LongInteger::operator!=(const LongInteger& b) const
{
    return !operator==(b);
}

bool LongInteger::operator<=(const LongInteger& b) const
{
    return operator<(b) || operator==(b);
}

bool LongInteger::operator>=(const LongInteger& b) const
{
    return !operator<(b);
}

void LongInteger::add_zeros_to_the_end(LongInteger &number, int zeros_count)
{
    for (int i = 0; i < zeros_count; ++i)
    {
        number.digits.insertBack(0);
    }
}

void LongInteger::reverse_make_equal_length(LongInteger &number1, LongInteger &number2)
{
    int diff_length = number1.digits.getSize() - number2.digits.getSize();

    if (diff_length > 0)
    {
        for (int i = 0; i < diff_length; i++)
        {
            number2.digits.insertBack((u_int16_t)0);
        }
    }
    else if (diff_length < 0)
    {
        for (int i = 0; i < -diff_length; i++)
        {
            number1.digits.insertBack((u_int16_t)0);
        }
    }
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

void LongInteger::make_equal_length(List<u_int16_t> &number1, List<u_int16_t> &number2)
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

void LongInteger::remove_heading_zeros()
{
    auto it = this->digits.begin();
    while (it != this->digits.end())
    {
        if (*it == static_cast<u_int16_t>(0))
        {
            this->digits.popFront();
            ++it;
        }
        else
        {
            break;
        }
    }

    if (this->digits.isEmpty())
    {
        is_negative = false;
        this->digits.insertBack((u_int16_t)0);
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

