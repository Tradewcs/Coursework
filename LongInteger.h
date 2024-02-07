#pragma once
#include <iostream>
#include "List.cpp"

class LongInteger {
private:
    List<u_int16_t> digits;
    bool is_negative;
    static const int base = 10;

public:
    LongInteger();
    LongInteger(long long num);
    LongInteger(std::string const& num);
    LongInteger(List<u_int16_t> digits, bool is_negative);
    LongInteger(const LongInteger &other);

    ~LongInteger();

    bool isNegative() const;

    LongInteger& operator=(const LongInteger& other);

    static LongInteger abs(const LongInteger& num);

    friend std::ostream& operator<<(std::ostream& os, const LongInteger& obj);

    LongInteger operator+() const;
    LongInteger operator-() const;

    LongInteger operator+(const LongInteger& b) const;
    LongInteger operator-(const LongInteger& b) const;

    LongInteger operator*(const LongInteger& b) const;
    LongInteger operator/(const LongInteger& b) const;
    // + - * / % ++ -- 
    LongInteger operator%(const LongInteger& b) const;
    
    LongInteger& operator+=(const LongInteger& b);
    LongInteger& operator-=(const LongInteger& b);

    LongInteger& operator*=(const LongInteger& b);
    LongInteger& operator/=(const LongInteger& b);

    LongInteger& operator%=(const LongInteger& b);

    LongInteger& operator++();
    LongInteger operator++(int);

    bool operator<(const LongInteger& b) const;
    bool operator>(const LongInteger& b) const;

    bool operator<=(const LongInteger& b) const;
    bool operator>=(const LongInteger& b) const;

    bool operator==(const LongInteger& b) const;
    bool operator!=(const LongInteger& b) const;

    // LongInteger& power(const LongInteger)

private:
public:    

    void add_zeros_to_the_end(LongInteger &number, int zeros_count);
    LongInteger binarySearchDivide(const LongInteger& divident, const LongInteger& divisor);
    LongInteger multiply_LongInteger_by_digit(const LongInteger& num, int digit);
    static void reverse_make_equal_length(LongInteger& a, LongInteger& b);
    static void make_equal_length(LongInteger& a, LongInteger& b);
    static void make_equal_length(List<u_int16_t>& a, List<u_int16_t>& b);
    void remove_heading_zeros();
    void remove_heading_zeros(List<int> &result);
};
