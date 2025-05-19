#include <iostream>
#include <string>
#include <cstring>
using namespace std;


#include <string>
#include <cstring>
#include <algorithm>

class BigDecimal {
private:
    static const int MAX_DIGITS = 160;
    char digits[MAX_DIGITS];  // Store digits as characters
    int decimalPoint;         // Position of decimal point from right
    bool isNegative;

    void normalize() {
        // Remove leading zeros
        int firstNonZero = 0;
        while (firstNonZero < MAX_DIGITS && digits[firstNonZero] == '0') {
            firstNonZero++;
        }
        
        if (firstNonZero == MAX_DIGITS) {
            // Number is zero
            memset(digits, '0', MAX_DIGITS);
            decimalPoint = 0;
            isNegative = false;
            return;
        }

        // Shift digits left
        memmove(digits, digits + firstNonZero, MAX_DIGITS - firstNonZero);
        memset(digits + MAX_DIGITS - firstNonZero, '0', firstNonZero);
    }

public:
    BigDecimal() {
        memset(digits, '0', MAX_DIGITS);
        decimalPoint = 0;
        isNegative = false;
    }

    BigDecimal(const std::string& str) {
        memset(digits, '0', MAX_DIGITS);
        decimalPoint = 0;
        isNegative = false;

        int idx = 0;
        // Handle sign
        if (str[0] == '-') {
            isNegative = true;
            idx++;
        }

        // Find decimal point in input
        size_t dotPos = str.find('.');
        if (dotPos == std::string::npos) {
            dotPos = str.length();
        }

        // Copy digits before decimal point
        int destPos = MAX_DIGITS - 1;
        for (int i = dotPos - 1; i >= idx && destPos >= 0; i--) {
            digits[destPos--] = str[i];
        }

        // Copy digits after decimal point
        if (dotPos < str.length()) {
            decimalPoint = str.length() - dotPos - 1;
            destPos = MAX_DIGITS - dotPos - 1;
            for (size_t i = dotPos + 1; i < str.length() && destPos >= 0; i++) {
                digits[destPos--] = str[i];
            }
        }

        normalize();
    }

    BigDecimal operator+(const BigDecimal& other) const {
        BigDecimal result;
        
        // Handle signs
        if (isNegative != other.isNegative) {
            // Implementation of subtraction needed here
            // For brevity, not shown in this example
            return result;
        }

        result.isNegative = isNegative;

        // Align decimal points
        int maxDecimalPoint = std::max(decimalPoint, other.decimalPoint);
        result.decimalPoint = maxDecimalPoint;

        // Perform addition
        int carry = 0;
        for (int i = MAX_DIGITS - 1; i >= 0; i--) {
            int sum = (digits[i] - '0') + (other.digits[i] - '0') + carry;
            result.digits[i] = (sum % 10) + '0';
            carry = sum / 10;
        }

        result.normalize();
        return result;
    }

    std::string toString() const {
        std::string result;
        if (isNegative) {
            result += "-";
        }

        // Find first non-zero digit
        int firstNonZero = 0;
        while (firstNonZero < MAX_DIGITS && digits[firstNonZero] == '0') {
            firstNonZero++;
        }

        if (firstNonZero == MAX_DIGITS) {
            return "0";
        }

        // Add digits before decimal point
        int decimalPos = MAX_DIGITS - decimalPoint;
        for (int i = firstNonZero; i < decimalPos; i++) {
            result += digits[i];
        }

        // Add decimal point and following digits if needed
        if (decimalPoint > 0) {
            result += ".";
            for (int i = decimalPos; i < MAX_DIGITS; i++) {
                result += digits[i];
            }
            // Remove trailing zeros after decimal point
            while (result.back() == '0') {
                result.pop_back();
            }
            if (result.back() == '.') {
                result.pop_back();
            }
        }

        return result;
    }
};