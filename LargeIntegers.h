#ifndef INFINT_H
#define INFINT_H
#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;

class InfInt {

private:

    // Each char in the string represents a digit in the decimal InfInt number.
    string number;

    /*
     * A member that represents the sign of the InfInt.
     * True value represents a negative InfInt, false value represents a positive InfInt.
     */
    bool sign = false;

    /* Helper methods */

    /*
     * Conversion methods - from binary to decimal representation and vise versa.
     * As a default, the representation is in decimal, but in some methods,
     * the conversion to binary representation is required.
     */
    InfInt convertBinaryToDecimal() const;

    InfInt convertDecimalToBinary() const;


    // Intended for the decimal representation.
    bool isNeg() const;

    // Intended for the binary representation.
    bool getSign() const;

    // Intended for the binary representation.
    void setSign(bool newSign);

    string getString() const;

    void setString(string str);

    // Add zeros from left to the shorter InfInt in the binary representation to make the lengths equal.
    void addZerosFromLeft(InfInt& firstBinary, InfInt& secondBinary);

    // Cut the unnecessary zeros from left in the binary representation.
    void cutZerosFromLeft();

    // Helper method for + operator.
    string additionOfPositives(string currentInfInt, string otherInfInt) const;

    // Helper method for - operator.
    string normalSubtractionOfPositives(string longerInfInt, string shorterInfInt) const;

    // Helper method for * operator.
    string multiplyInfIntByDigit(string infInt, int digit) const;

    // Helper method for / and % operators.
    InfInt divisionAndModulo(InfInt otherInfInt, bool isDivision) const;

    // Helper method for < operator.
    bool isFirstSmaller(string currentStr,string otherStr) const;

public:

    /* Constructors */

    InfInt();

    InfInt(const char* num);

    InfInt(const string num);

    InfInt(const int num);


    /* Operators Overloading */

    InfInt operator+(const InfInt &otherInfInt) const;

    InfInt operator-(const InfInt &otherInfInt) const;

    InfInt operator*(const InfInt &otherInfInt) const;

    InfInt operator/(const InfInt infInt) const;

    InfInt operator%(const InfInt otherInfInt) const;

    bool operator==(const InfInt& otherInfInt) const;

    bool operator<(const InfInt& otherInfInt) const;

    bool operator<=(const InfInt& otherInfInt) const;

    bool operator>(const InfInt& otherInfInt) const;

    bool operator>=(const InfInt& otherInfInt) const;

    InfInt& operator+=(const InfInt& otherInfInt);

    InfInt& operator++();

    InfInt operator++(const int noUse);

    InfInt& operator--();

    InfInt operator--(const int noUse);

    InfInt operator&(const InfInt& otherInfInt);

    InfInt operator|(const InfInt& otherInfInt);

    InfInt operator^(const InfInt& otherInfInt);

    InfInt operator<<(const int number) const;

    InfInt operator>>(const int number) const;

    InfInt& operator&=(const InfInt otherInfInt);

    InfInt& operator>>=(const int number);

    friend ostream &operator<<(ostream &out, const InfInt &inf);

    friend istream &operator>>(istream &in, InfInt &inf);

    explicit operator int() const;

};

#endif //INFINT_H
