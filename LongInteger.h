#pragma once
#include "List.cpp"

class LongInteger {
private:
    List<std::byte> digits;
    bool is_negative;

public:
    LongInteger();
    LongInteger(long long num);
    LongInteger(std::string const& num);
    LongInteger(List<std::byte> digits, bool is_negative);
    LongInteger(const LongInteger &other);

    ~LongInteger();

    LongInteger& operator=(const LongInteger& other);

    static LongInteger abs(const LongInteger& num);

    friend std::ostream& operator<<(std::ostream& os, const LongInteger& obj);

    LongInteger operator+() const;
    LongInteger operator-() const;

    LongInteger& operator-(const LongInteger& b) const;
    LongInteger& operator+(const LongInteger& b) const;

    LongInteger& operator*(const LongInteger& b) const;
    LongInteger& operator/(const LongInteger& b) const;
    // + - * / % ++ -- 
    
    LongInteger& operator+=(const LongInteger& b);
    LongInteger& operator-=(const LongInteger& b);

    LongInteger& operator*=(const LongInteger& b);
    LongInteger& operator/=(const LongInteger& b);

    LongInteger& operator++();

    // LongInteger& power(const LongInteger)

    void foo(LongInteger &o) {
        make_equal_length((*this), o);

        for (std::byte num : digits) {
            std::cout << (int)num;
        }
        std::cout << std::endl;
    }

private:
public:    
    void make_equal_length(LongInteger& a, LongInteger& b);
    void make_equal_length(List<int>& a, List<int>& b);
    void make_equal_length(List<std::byte>& a, List<std::byte>& b);
    void remove_heading_zeros(List<std::byte> &result);
    void remove_heading_zeros(List<int> &result);
};
