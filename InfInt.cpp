// If you run the code on Windows, you should add the following include:
// #include <windows.h>

#include "LargeIntegers.h"
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;


/* Constructors */

InfInt::InfInt(const char* num) {
    number = num;
    cutZerosFromLeft();
}

InfInt::InfInt() {
    number = "0";
}

InfInt::InfInt(const string num) {
    number = num;
    cutZerosFromLeft();
}

InfInt::InfInt(const int num) {
    string numToString = to_string(num);
    number = numToString;
}


/* Helper methods */


/*
 * Convert an InfInt with a decimal representation to an InfInt with a binary representation.
 * Use the known method of division by 2 with the following modification: in order to get InfInt/2, perform
 * division by 2 at any digit of the InfInt and not at the whole number (since an InfInt cannot be divided by 2).
 */
InfInt InfInt::convertDecimalToBinary() const {
    if (getString() == "0") {
        return (*this);
    } else {
        string binaryString = "";
        int carry = 0;
        int currentDigit = 0;
        int division = 0;
        InfInt currentDivided = getString();
        string newDivided = "";
        InfInt binaryInfInt;
        // Save the sign of the InfInt in the binary representation.
        if (getString()[0] == '-') {
            binaryInfInt.setSign(true);
        } else {
            binaryInfInt.setSign(false);
        }
        // If the InfInt is negative, delete the sign from its decimal representation for convenience.
        if (binaryInfInt.getSign()) {
            currentDivided.setString(currentDivided.getString().erase(0, 1));
        }
        // As long as the divided number is not 0
        while (currentDivided.getString() != "0") {
            // Run over the digits of the number.
            for (long int i = 0; i < currentDivided.getString().length(); i++) {
                // Convert the current digit from char to int.
                currentDigit = (int) (currentDivided.getString()[i] - '0');
                division = currentDigit / 2;
                newDivided = newDivided + (char) (division + carry + '0');
                // If the current digit is odd - save a carry of 5.
                if (currentDigit % 2 == 1) {
                    carry = 5;
                } else {
                    carry = 0;
                }
            }
            // After the inner loop we get InfInt / 2.
            currentDivided = newDivided;
            newDivided = "";
            currentDivided.cutZerosFromLeft();
            // Add the remainder of the division.
            if (carry != 0) {
                binaryString = "1" + binaryString;
            } else {
                binaryString = "0" + binaryString;
            }
            carry = 0;
        }
        binaryInfInt.setString(binaryString);
        return binaryInfInt;
    }
} // convertDecimalToBinary

/*
 * Convert an InfInt with a binary representation to an InfInt with a decimal representation by summing the
 * digits of the binary InfInt multiplied by the corresponding power of 2.
 */
InfInt InfInt::convertBinaryToDecimal() const {
    InfInt decimal;
    InfInt sum;
    string str = "";
    InfInt two = "2";
    InfInt currentInfInt;
    for (long int i = 0; i < getString().length(); i++) {
        str = getString()[i];
        InfInt strInf = str;
        sum = (sum * two) + strInf;
    }
    if (getSign()) {
        decimal =  InfInt('-' + sum.getString());
    }
    else {
        decimal = sum;
    }
    return decimal;
}

// Intended for the decimal representation.
bool InfInt::isNeg() const {
    return getString()[0] == '-';
}

// Intended for the binary representation.
bool InfInt::getSign() const {
    return sign;
}

// Intended for the binary representation.
void InfInt::setSign(bool newSign) {
    sign = newSign;
}

string InfInt::getString() const {
    return number;
}

void InfInt::setString(string str) {
    number = str;
}

// Add zeros from left to the shorter InfInt in the binary representation to make the lengths equal.
void InfInt::addZerosFromLeft(InfInt &firstBinary, InfInt &secondBinary) {
    bool flag = false;
    int numOfZeros = firstBinary.getString().length() - secondBinary.getString().length();
    if (numOfZeros < 0) {
        numOfZeros = numOfZeros * (-1);
        flag = true;
    } else if (numOfZeros > 0) {
        flag = false;
    }
    string zeros = "";
    for (long int i = 0; i < numOfZeros; i++) {
       zeros = zeros + "0";
    }
    if (flag) {
        firstBinary.setString(zeros + firstBinary.getString());
    } else {
        secondBinary.setString(zeros + secondBinary.getString());
    }
}

// Cut the unnecessary zeros from left in the binary representation.
void InfInt::cutZerosFromLeft() {
    string newString = "";
    int counter = 0;
    if (number == "0") {
        return;
    } else {
        for (long int i = 0; i < number.length(); i++) {
            if (number[i] != '0') {
                number = number.erase(0, counter);
                return;
            // If the number is 0.
            } else if (i == number.length() - 1 && number[i] == '0') {
                number = "0";
                return;
            } else {
                counter++;
            }
        }
    }
}

// Helper method for + operator.
string InfInt::additionOfPositives(string longerInfInt, string shorterInfInt) const {
    string newString = "";
    // Index for running over the digits of the longer InfInt.
    int i = longerInfInt.length() - 1;
    // Index for running over the digits of the shorter InfInt.
    int j = shorterInfInt.length() - 1;
    int carry = 0;
    int digitsSum = 0;
    while (i >= 0) {
        while (j >= 0) {
            /*
             * Use the long addition method.
             * In each iteration, sum the two curent digits and the carry.
             */
            digitsSum = carry + (longerInfInt[i] - '0') + (shorterInfInt[j] - '0');
            // The new digit in the sum is the unity digit of the sum of the two digits.
            newString = (char)((digitsSum % 10) + '0') + newString;
            // Update the carry (if the sum of the two digits is >= 10 the carry is 1).
            carry = digitsSum / 10;
            i--;
            j--;
        }
        // Keep running over the longer InfInt (if exist).
        if (i >= 0) {
            digitsSum = carry + (longerInfInt[i] - '0');
            newString = (char)((digitsSum % 10) + '0') + newString;
            carry = digitsSum / 10;
            i--;
        }
    }
    if (carry != 0) {
        newString = to_string(carry) + newString;
    }
    return newString;
} // additionOfPositives

InfInt InfInt::operator+(const InfInt &otherInfInt) const {
    InfInt newInfIntCurrent;
    InfInt newInfIntOther;
    InfInt newInfInt;
    int lengthOfCurrent = getString().length();
    int lengthOfOther = otherInfInt.getString().length();
    string str;
    // If both of the InfInts are positive, do a regular addition.
    if (!isNeg() && !otherInfInt.isNeg()) {
        if (lengthOfCurrent > lengthOfOther) {
            return InfInt(additionOfPositives(getString(), otherInfInt.getString()));
        } else {
            return InfInt(additionOfPositives(otherInfInt.getString(), getString()));
        }
    // If the current InfInt is positive and the other is negative, do a subtraction.
    } else if (!isNeg() && otherInfInt.isNeg()) {
        newInfIntOther = (otherInfInt.getString().erase(0, 1));
        return (*this - newInfIntOther);
    /*
     * If the current InfInt is negative and the other is positive, do a subtraction.
     * The order of the operands in the subtraction and the sign of the result is dependent on their values.
     */
    } else if (isNeg() && !otherInfInt.isNeg()) {
        newInfIntCurrent = (getString().erase(0, 1));
        if (newInfIntCurrent < otherInfInt) {
            return (otherInfInt - newInfIntCurrent);
        }
        return InfInt("-1")*(newInfIntCurrent - otherInfInt);
    // Else - both of the InfInts are negative - do the addition of the positive values and finally add the sign.
    } else {
        newInfIntCurrent = (getString().erase(0, 1));
        newInfIntOther = (otherInfInt.getString().erase(0, 1));
        newInfInt = newInfIntCurrent + newInfIntOther;
        if (newInfInt.getString() == "0") {
            return newInfInt;
        } else {
            newInfInt.setString("-" + newInfInt.getString());
            return newInfInt;
        }
    }
} // operator+

// Helper method for - operator.
string InfInt::normalSubtractionOfPositives(string biggerInfInt, string smallerInfInt) const {
    // A new string for the result of the subtraction.
    string newString = "";
    // Index for running over the digits of the bigger InfInt.
    int i = biggerInfInt.length() - 1;
    // Index for running over the digits of the smaller InfInt.
    int j = smallerInfInt.length() - 1;
    int carry = 0;
    int digitsSub = 0;
    while (i >= 0) {
        while (j >= 0) {
            /*
             * Use the long addition method.
             * In each iteration subtract the two curent digits and the carry.
             */
            digitsSub = (biggerInfInt[i] - '0') - (smallerInfInt[j] - '0') - carry;
            if (digitsSub < 0) {
                digitsSub = digitsSub + 10;
                carry = 1;
            } else {
                carry = 0;
            }
            i--;
            j--;
            // The new digit in the subtraction is the unity digit of the subtraction of the digits.
            newString = (to_string)(digitsSub) + newString;
        }
        // Keep running over the longer InfInt (if exist).
        if (i >= 0) {
            digitsSub = (biggerInfInt[i] - '0') - carry;
            if (digitsSub < 0) {
                digitsSub = digitsSub + 10;
                carry = 1;
            } else {
                carry = 0;
            }
            i--;
            newString = (to_string)(digitsSub) + newString;
        }
    }
    return newString;
} // normalSubtractionOfPositives

InfInt InfInt::operator-(const InfInt &otherInfInt) const {
    string newString = "";
    InfInt newInfIntCurrent;
    InfInt newInfIntOther;
    InfInt newInfInt;
    // If both of the InfInts are positive and the current is bigger, do a normal subtraction.
    if (*this >= otherInfInt && !isNeg() && !otherInfInt.isNeg()) {
        newInfInt = (normalSubtractionOfPositives(getString(), otherInfInt.getString()));
        newInfInt.cutZerosFromLeft();
        return newInfInt;
    /*
     * If both of the InfInts are positive and the current is smaller, swap them,
     * do a normal subtraction, and add the sign
     */ 
    } else if (*this < otherInfInt && !isNeg() && !otherInfInt.isNeg()) {
        newInfInt = (otherInfInt - *this);
        newInfInt.setString("-" + newInfInt.getString());
        return newInfInt;
    // Else - if the current InfInt is positive and the other is negative, do an addition.
    } else if (!isNeg() && otherInfInt.isNeg()) {
        newInfInt = (otherInfInt.getString().erase(0, 1));
        newInfInt = *this + newInfInt;
        return newInfInt;
    /*
     * Else - if the current InfInt is negative and the other is positive,
     * do an addition of positives and finally add the sign.
     */
    } else if (isNeg() && !otherInfInt.isNeg()) {
        newInfInt = (getString().erase(0, 1));
        newInfInt = newInfInt + otherInfInt;
        newInfInt.setString("-" + newInfInt.getString());
        return newInfInt;
    /*
     * Else - if both of the InfInts are negative and the current >= the other,
     * do a subtraction of positives: positive value of the other - positive value of the current.
     */
    } else if (isNeg() && otherInfInt.isNeg() && *this >= otherInfInt) {
        newInfIntCurrent = (getString().erase(0, 1));
        newInfIntOther = (otherInfInt.getString().erase(0, 1));
        newInfInt = newInfIntOther - newInfIntCurrent;
        return newInfInt;
    /*
     * Else - if both of the InfInts are negative and the current < the other,
     * do a subtraction of positives:  positive value of the current - positive value of the other,
     * and finally add the sign.
     */
    } else if (isNeg() && otherInfInt.isNeg() && *this < otherInfInt) {
        newInfIntCurrent = (getString().erase(0, 1));
        newInfIntOther = (otherInfInt.getString().erase(0, 1));
        newInfInt = newInfIntCurrent - newInfIntOther;
        newInfInt.setString("-" + newInfInt.getString());
        return newInfInt;
    }
} // operator-

bool InfInt::operator==(const InfInt &otherInfInt) const {
    // If the lengths of the InfInts are different, they are not equal.
    if (number.length() != otherInfInt.number.length()) {
        return false;
    } else {
        for (long int i = 0; i < number.length(); i++) {
            if (number[i] != otherInfInt.number[i]) {
                return false;
            }
        }
        return true;
    }
}

// Helper method for < operator.
bool InfInt::isFirstSmaller(string currentStr, string otherStr) const {
    if (currentStr.length() < otherStr.length()) {
        return true;
    } else if (currentStr.length() > otherStr.length()) {
        return false;
    // Else - if both of the InfInts have the same length.
    } else if (currentStr.length() == otherStr.length()) {
        for (int i = 0; i < currentStr.length(); i++) {
            // If the current is smaller.
            if ((int) (currentStr[i] - '0') < (int) (otherStr[i] - '0')) {
                return true;
            }
            // If the current is bigger.
            if ((int) (currentStr[i] - '0') > (int) (otherStr[i] - '0')) {
                return false;
            }
            /*
             * If it's the last digit, all the digits of the InfInts so far are equal.
             * If the last digit is also equal, the current InfInt is not smaller than the other.
             */
            if ((i == currentStr.length() - 1) && currentStr[i] == otherStr[i]) {
                return false;
            }
        }
        return false;
    }
} // isFirstSmaller

bool InfInt::operator<(const InfInt &otherInfInt) const {
    string currentStr = getString();
    string otherStr = otherInfInt.getString();
    // If the current InfInt is negative and the other InfInt is not, the current is smaller.
    if (isNeg() && !otherInfInt.isNeg()) {
        return true;
    // If the current InfInt is positive and the other InfInt is not, the current is not smaller.
    } else if (!isNeg() && otherInfInt.isNeg()) {
        return false;
        // If both of the InfInts are positive.
    } else if (!isNeg() && !otherInfInt.isNeg()) {
        // check which InfInt is smaller.
        int t =  isFirstSmaller(currentStr, otherStr);
        return isFirstSmaller(currentStr, otherStr);
    // Else - both of the InfInts are negative.
    } else {
        // Erase the sign and check which InfInt is smaller.
        currentStr.erase(0, 1);
        otherStr.erase(0, 1);
        return isFirstSmaller(currentStr, otherStr);
    }
}

// <= is < or =.
bool InfInt::operator<=(const InfInt &otherInfInt) const {
        return (*this < otherInfInt || *this == otherInfInt);
}

// > is not <=.
bool InfInt::operator>(const InfInt &otherInfInt) const {
    return !(*this <= otherInfInt);
}

// >= is > or =.
bool InfInt::operator>=(const InfInt &otherInfInt) const {
    return (*this > otherInfInt || *this == otherInfInt);
}

InfInt &InfInt::operator+=(const InfInt &otherInfInt) {
    *this = *this + otherInfInt;
    return *this;
}

// Increase the current InfInt by 1 immediately.
InfInt &InfInt::operator++() {
    InfInt one = "1";
    *this = *this + one;
    return *this;
}

// Increase the current InfInt by 1 at the next step.
InfInt InfInt::operator++(int noUse) {
    InfInt newInf = *this;
    ++*this;
    return newInf;
}

// Decrease the current InfInt by 1 immediately.
InfInt &InfInt::operator--() {
    InfInt one = "1";
    *this = *this - one;
    return *this;
}

// Decrease the current InfInt by 1 at the next step.
InfInt InfInt::operator--(int noUse) {
    InfInt newInf = *this;
    --(*this);
    return newInf;
}

// Helper method for * operator - multiply an InfInt by one digit.
string InfInt::multiplyInfIntByDigit(string infInt, int digit) const {
    string newInfInt = "";
    int currentMul = 0;
    int mod10 = 0;
    int carry = 0;
    // Use the long multiplication method.
    for (long int i = infInt.length() - 1; i >= 0; i--) {
        currentMul = (infInt[i] - '0') * digit + carry;
        carry = currentMul / 10;
        mod10 = currentMul % 10;
        newInfInt = (char) (mod10 + '0') + newInfInt;
    }
    if (carry != 0) {
        newInfInt = (char) (carry + '0') + newInfInt;
    }
    return newInfInt;
}

InfInt InfInt::operator*(const InfInt &otherInfInt) const {
    if (getString() == "0" || otherInfInt.getString() == "0") {
        return InfInt();
    } else {
        InfInt newCurrentInfInt = *this;
        InfInt newOtherInfInt = otherInfInt;
        InfInt tempInfInt;
        string currentMult = "";
        InfInt result;
        string currentStr = newCurrentInfInt.getString();
        int multiplier = 1;
        int currentDigit = 0;
        bool resultIsNegative = false;
        // If the InfInt current is negative
        if (currentStr[0] == '-') {
            resultIsNegative = !resultIsNegative;
            newCurrentInfInt = InfInt(currentStr.erase(0, 1));
            string currentStr = newCurrentInfInt.getString();
        }
        // If the other InfInt is negative
        if (otherInfInt.getString()[0] == '-') {
            resultIsNegative = !resultIsNegative;
            newOtherInfInt = InfInt(otherInfInt.getString().erase(0, 1));
        }
        // Find the current digit and use the helper method to multiply the Infint by this digit.
        for (long int i = newOtherInfInt.getString().length() - 1; i >= 0; i--) {
            currentDigit = (newOtherInfInt.getString()[i] - '0');
            currentMult = multiplyInfIntByDigit(currentStr, currentDigit);
        // Add zeros from right according to the position of the digit.
        for (int j = 1; j < multiplier; j++) {
            currentMult = currentMult + "0";
        }
        tempInfInt = InfInt(currentMult);
        // Sum the multiplications.
        result = result + tempInfInt;
        multiplier++;
        }
        if (resultIsNegative) {
            result.setString("-" + result.getString());
        }
        result.cutZerosFromLeft();
        return result;
    }
} // operator*

InfInt InfInt::operator&(const InfInt &otherInfInt) {
    InfInt newInfInt;
    // Convert the InfInts from decimal representation to binary representation.
    InfInt currentBinary = (*this).convertDecimalToBinary();
    InfInt otherBinary = otherInfInt.convertDecimalToBinary();
    string newString = "";
    addZerosFromLeft(currentBinary, otherBinary);
    for (long int i = 0; i < currentBinary.getString().length(); i++) {
        // Do the AND operation - bit-bit.
        if (currentBinary.getString()[i] == '1' && otherBinary.getString()[i] == '1') {
            newString = newString + "1";
        } else {
            newString = newString + "0";
        }
    }
    newInfInt = newString;
    // Convert the result to decimal representation.
    newInfInt = newInfInt.convertBinaryToDecimal();
    // If the result is negative, add the sign.
    if (currentBinary.getSign() && otherBinary.getSign() &&
        newInfInt.getString() != "0") {
        newInfInt.setString('-' + newInfInt.getString());
    }
    return newInfInt;
}

InfInt InfInt::operator|(const InfInt &otherInfInt) {
    InfInt newInfInt;
    // Convert the InfInts from decimal representation to binary representation.
    InfInt currentBinary = (*this).convertDecimalToBinary();
    InfInt otherBinary = otherInfInt.convertDecimalToBinary();
    string newString = "";
    addZerosFromLeft(currentBinary, otherBinary);
    // Do the OR operation - bit-bit.
    for (int i = 0; i < currentBinary.getString().length(); i++) {
        if (currentBinary.getString()[i] == '1' || otherBinary.getString()[i] == '1') {
            newString = newString + "1";
        } else {
            newString = newString + "0";
        }
    }
    newInfInt = newString;
    // Convert the result to decimal representation.
    newInfInt = newInfInt.convertBinaryToDecimal();
    // If the result is negative, add the sign.
    if ((currentBinary.getSign() || otherBinary.getSign()) &&
        newInfInt.getString() != "0") {
        newInfInt.setString('-' + newInfInt.getString());
    }
    return newInfInt;
}

InfInt InfInt::operator^(const InfInt &otherInfInt) {
    InfInt newInfInt;
    // Convert the InfInts from decimal representation to binary representation.
    InfInt currentBinary = (*this).convertDecimalToBinary();
    InfInt otherBinary = otherInfInt.convertDecimalToBinary();
    string newString = "";
    addZerosFromLeft(currentBinary, otherBinary);
    // Do the XOR operation, bit-bit.
    for (int i = 0; i < currentBinary.getString().length(); i++) {
        if (currentBinary.getString()[i] == '1' && otherBinary.getString()[i] == '1'
        || currentBinary.getString()[i] == '0' && otherBinary.getString()[i] == '0') {
            newString = newString + "0";
        } else {
            newString = newString + "1";
        }
    }
    newInfInt = newString;
    // Convert the result to decimal representation.
    newInfInt = newInfInt.convertBinaryToDecimal();
    // If the result is negative, add the sign.
    if ((!currentBinary.getSign() && otherBinary.getSign()
        || currentBinary.getSign() && !otherBinary.getSign()) &&
        newInfInt.getString() != "0") {
        newInfInt.setString('-' + newInfInt.getString());
    }
    return newInfInt;
}

InfInt InfInt::operator<<(const int number) const {
    // Convert the InfInt from decimal representation to binary representation.
    InfInt newInfInt = convertDecimalToBinary();
    string newInfIntString = newInfInt.getString();
    // Add zeros from right.
    for (int i = 0; i < number; i++) {
        newInfIntString = newInfIntString + "0";
    }
    newInfInt.setString(newInfIntString);
    // Convert the result to decimal representation.
    newInfInt = newInfInt.convertBinaryToDecimal();
    if (newInfInt.getSign() && newInfInt.getString() != "0") {
        newInfInt.setString("-" + newInfInt.getString());
    }
    return newInfInt;
}

InfInt InfInt::operator>>(const int number) const {
    // Convert the InfInt from decimal representation to binary representation.
    InfInt newInfInt = convertDecimalToBinary();
    int lengthOfInfInt = newInfInt.getString().length();
    // If the number of the bits that should be pushed from left >= the length of the InfInt, the result is 0.
    if (lengthOfInfInt - number <= 0) {
        newInfInt.setString("0");
        return newInfInt;
    }
    // Else - the rueult is the next substring:
    string newInfIntString = newInfInt.getString().substr(0, lengthOfInfInt - number);
    newInfInt.setString(newInfIntString);
    // Convert the result to decimal representation.
    newInfInt = newInfInt.convertBinaryToDecimal();
    if (newInfInt.getSign() && newInfInt.getString() != "0") {
        newInfInt.setString("-" + newInfInt.getString());
    }
    return newInfInt;
}

InfInt &InfInt::operator&=(const InfInt otherInfInt) {
    *this = (*this) & otherInfInt;
    return *this;
}

InfInt &InfInt::operator>>=(const int number) {
    *this = (*this) >> number;
    return *this;
}

/*
 * Helper method for the / , % operators.
 * Return the division if param isDivision is true, otherwise - return the modulo.
 */
InfInt InfInt::divisionAndModulo(InfInt otherInfInt, bool isDivision) const {
    if (otherInfInt.getString() == "0") {
        throw invalid_argument("The devisor cannot be 0.");
    }
    string currentBinary, otherBinary, remainder, quotient;
    InfInt remainderDecimal, otherDecimal, subResult;
    // Convert the InfInts from decimal representation to binary representation.
    currentBinary = convertDecimalToBinary().getString();
    otherBinary = otherInfInt.convertDecimalToBinary().getString();
    long length = max(currentBinary.length(), otherBinary.length());
    bool sign;
    // If just one of the InfInts is negative, the result is negative.
    if (isNeg() && !otherInfInt.isNeg() || !isNeg() && otherInfInt.isNeg()) {
        sign = true;
    } else {
        sign = false;
    }
    // Create a string of zeros that its length is the length of the longer InfInt.
    for (long i = 0; i < length; i++) {
        quotient += '0';
    }
    for (long i = 0; i < currentBinary.length(); i++) {
        remainder += '0';
        // Update the current digit of the remainder to be the current digit of currentBinary.
        remainder[remainder.size() - 1] = currentBinary[i];
        // Convert the remainder and the other InfInt to decimal representation.
        remainderDecimal = InfInt(remainder);
        remainderDecimal = remainderDecimal.convertBinaryToDecimal();
        otherDecimal = InfInt(otherBinary);
        otherDecimal = otherDecimal.convertBinaryToDecimal();
        // If the current remainder is bigger than the other InfInt -
        if (remainderDecimal >= otherDecimal) {
            // Do a subtraction.
            subResult = remainderDecimal - otherDecimal;
            // Update the remainder to be the subtraction result.
            remainder = subResult.convertDecimalToBinary().getString();
            // Set the i'th bit of the quotient.
            quotient[i] = '1';
        }
    }
    // Return the division if isDivision is true.
    if (isDivision) {
        InfInt answer = InfInt(quotient);
        answer = answer.convertBinaryToDecimal();
        // If the result is negative and not 0 - add the sign.
        if (sign && answer.getString() != "0") {
            answer.setString('-' + answer.getString());
        }
        return (answer);
    // Else - return the remainder since the operation is modulo.
    } else {
        InfInt answer = InfInt(remainder);
        answer = answer.convertBinaryToDecimal();
        if (isNeg() && answer.getString() != "0") {
            answer.setString('-' + answer.getString());
        }
        return (answer);
    }
} // divisionAndModulo

InfInt InfInt::operator/(InfInt otherInfInt) const {
    return (divisionAndModulo(otherInfInt, true));
}

InfInt InfInt::operator%(InfInt otherInfInt) const {
    return (divisionAndModulo(otherInfInt, false));
}

// Convert the InfInt to int using stoi.
InfInt::operator int() const {
    int decimalInt = stoi(getString());
    return decimalInt;
}

// Output operator.
ostream &operator<<(ostream &out, const InfInt &inf) {
    out << inf.number;
    return out;
}

// Input operator.
istream &operator>>(istream &in, InfInt &inf) {
    in >> inf.number;
    inf = InfInt(inf.getString());
    return in;
}