#pragma once
#include <iostream>
#include "List.cpp"

class LongInteger {
private:
    List<u_int16_t> digits;
    bool is_negative;

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
    
    LongInteger& operator+=(const LongInteger& b);
    LongInteger& operator-=(const LongInteger& b);

    LongInteger& operator*=(const LongInteger& b);
    LongInteger& operator/=(const LongInteger& b);

    LongInteger& operator++();
    LongInteger operator++(int);

    // LongInteger& power(const LongInteger)

private:
public:    
    void make_equal_length(LongInteger& a, LongInteger& b);
    void make_equal_length(List<int>& a, List<int>& b);
    void make_equal_length(List<u_int16_t>& a, List<u_int16_t>& b);
    void remove_heading_zeros(List<u_int16_t> &result);
    void remove_heading_zeros(List<int> &result);
};
