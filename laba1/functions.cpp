#include "functions.h"

std::string hexDigitToBinary(char hexDigit) {
    switch (hexDigit) {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': case 'a': return "1010";
        case 'B': case 'b': return "1011";
        case 'C': case 'c': return "1100";
        case 'D': case 'd': return "1101";
        case 'E': case 'e': return "1110";
        case 'F': case 'f': return "1111";
        default: return "";
    }
}

char binaryDigitToHex(std::string hexDigit) {
    if(hexDigit == "0000") return '0';
    if(hexDigit == "0001") return '1';
    if(hexDigit == "0010") return '2';
    if(hexDigit == "0011") return '3';
    if(hexDigit == "0100") return '4';
    if(hexDigit == "0101") return '5';
    if(hexDigit == "0110") return '6';
    if(hexDigit == "0111") return '7';
    if(hexDigit == "1000") return '8';
    if(hexDigit == "1001") return '9';
    if(hexDigit == "1010") return 'a';
    if(hexDigit == "1011") return 'b';
    if(hexDigit == "1100") return 'c';
    if(hexDigit == "1101") return 'd';
    if(hexDigit == "1110") return 'e';
    if(hexDigit == "1111") return 'f';
    return '-';
}

    // Функция для перевода из шестнадцатиричной системы счисления в двоичную
std::string hexToBinary(std::string hexValue) {
    if (hexValue.substr(0, 2) == "0x") {
        hexValue = hexValue.substr(2);
    }
    std::string binaryValue;
    for (char hexDigit : hexValue) {
        std::string binaryDigit = hexDigitToBinary(hexDigit);
        binaryValue += binaryDigit;
    }
    return binaryValue;
}

// Функция для перевода из шестнадцатиричной системы счисления в двоичную
std::string binaryToHex(std::string binaryValue) {
    std::string hexValue;
    for (size_t i = 0; i < binaryValue.length(); i += 4) {
        std::string binaryDigit = binaryValue.substr(i, 4);
        char hexDigit = binaryDigitToHex(binaryDigit);
        hexValue += hexDigit;
    }
    return hexValue;
}

// Функция для перевода из двоичной системы счисления в десятичную
long long binaryToDecimal(const std::string& binary, size_t x, bool integer) {
    long long decimal = 0;
    long long power = 1;
    for (size_t i = binary.length(); i > 0; i--) {
        long long t = power * (binary[i - 1] - '0');
        power *= 2;
        if(i + x - 1 == binary.length() && integer) {
            t *= -1;
        }
        decimal += t;
    }
    return decimal;
}

// Функция для перевода из двоичной системы счисления в десятичную
std::string decimalToBinary(long long n, size_t x) {
    if(n < 0) {
        n += pow(2, x);
    }
    std::string result;
    while(n > 0) {
        result += ((n % 2) + '0');
        n /= 2;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

// Функция для разделения формата A.B
bool splitAB(const std::string& input, size_t& A, size_t& B) {
    size_t dotPos = input.find('.');
    if (dotPos != std::string::npos) {
        try {
            A = std::stoi(input.substr(0, dotPos));
            B = std::stoi(input.substr(dotPos + 1));
            return true;
        } catch (const std::invalid_argument& e) {
            return false;
        }
    } else {
        return false;
    }
}

// Функция для разделения числа в двоичной системе счисления на целую и дробную части
std::pair<std::string, std::string> splitNumber(std::string& str, size_t A, size_t B) {
    size_t len = str.length();
    if (len < A + B) {
        str.insert(0, A + B - len, '0');
    }
    str = str.substr(str.length() - A - B, A + B);
    return std::make_pair(str.substr(0, A), str.substr(A, B));
}

//Функция для перевода строки в вектор
std::vector<long long> stringToVector(std::string str) {
    std::vector<long long> vec;
    for (char c : str) {
        vec.push_back(c - '0');
    }
    return vec;
}

//Функция для перевода строки в вектор
long long stringToInt(std::string str) {
    long long vec = 0;
    for (char c : str) {
        vec = vec * 10 + (c - '0');
    }
    return vec;
}

//Функция для перевода числа в вектор
std::vector<long long> intToVector(long long n) {
    std::vector<long long> vec;
    if(n == 0){
        vec.push_back(0);
    }
    while(n != 0) {
        vec.push_back(n % 10);
        n /= 10;
    }
    std::reverse(vec.begin(), vec.end());
    return vec;
}

//Функция для перевода числа в строку
std::string intToString(long long n) {
    std::string str;
    bool sgn = false;
    if(n < 0) {
        sgn = true;
        n *= -1;
    }
    while(n != 0) {
        str += ((n % 10) + '0');
        n /= 10;
    }
    if(sgn) {
        str += "-";
    }
    std::reverse(str.begin(), str.end());
    return str;
}

//Функция для перевода вектора в строку
std::string vectorToString(std::vector<long long> vec) {
    std::string str;
    for (long long num : vec) {
        str += std::to_string(num);
    }
    return str;
}

// Функция для удаления ведущих нулей из вектора
void removeLeadingZeros(std::vector<long long>& vec) {
    std::reverse(vec.begin(), vec.end());
    while (vec.size() > 1 && vec.back() == 0) {
        vec.pop_back();
    }
    std::reverse(vec.begin(), vec.end());
}

// Функция для сложения двух векторов с переносом выхода за границу
std::vector<long long> addVectors(std::vector<long long> a, std::vector<long long> b) {
    std::vector<long long> result;
    long long carry = 0;
    long long i = a.size() - 1;
    long long j = b.size() - 1;
    while (i >= 0 || j >= 0 || carry > 0) {
        long long sum = carry;
        if (i >= 0) {
            sum += a[i];
            i--;
        }
        if (j >= 0) {
            sum += b[j];
            j--;
        }
        result.push_back(sum % 10);
        carry = sum / 10;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

// Функция для инверсии всех битов, кроме знакового
std::vector<long long> inversion(std::vector<long long> a, size_t x, size_t y) {
    size_t sz = 0;
    if(a.size() == x + y) sz = 1;
    for (size_t i = a.size(); i > sz; i--) {
        a[i - 1] ^= 1;
    }
    return a;
}

// Функция для сравнения модуля отрицательного и положительного чисел (что с одинаковыми делать??)
bool compare(std::vector<long long> a, std::vector<long long> b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 1; i < a.size(); i++)
        if(a[i] > b[i]) return true;
        else if(b[i] > a[i]) return false;
    return true;
}

// Функция для вычитания двух векторов (предполагается, что a >= b)
std::vector<long long> subtractVectors(std::vector<long long> a, std::vector<long long> b) {
    std::vector<long long> result;
    long long borrow = 0;
    long long i = a.size() - 1;
    long long j = b.size() - 1;
    while (i >= 0 || j >= 0) {
        long long diff = borrow;
        if (i >= 0) {
            diff += a[i];
            i--;
        }
        if (j >= 0) {
            diff -= b[j];
            j--;
        }
        if (diff < 0) {
            diff += 10;
            borrow = -1;
        } else {
            borrow = 0;
        }
        result.push_back(diff);
    }
    std::reverse(result.begin(), result.end());
    removeLeadingZeros(result);
    return result;
}


// Функция для умножения двух векторов
std::vector<long long> multiplyVectors(std::vector<long long> a, std::vector<long long> b) {
    removeLeadingZeros(a);
    removeLeadingZeros(b);
    std::vector<long long> result(a.size() + b.size(), 0);
    for (long long i = a.size() - 1; i >= 0; i--) {
        long long carry = 0;
        for (long long j = b.size() - 1; j >= 0; j--) {
            long long product = a[i] * b[j] + carry + result[i + j + 1];
            result[i + j + 1] = product % 10;
            carry = product / 10;
        }
        result[i] += carry;
    }

    return result;
}

std::vector<long long> fractionalPart(std::vector<long long> a, size_t n) {
    std::vector<long long> b; b.push_back(5);
    std::vector<long long> five; five.push_back(5);
    for(size_t i = 0; i + 1 < n; i++) {
        b = multiplyVectors(b, five);
    }

    std::vector<long long> result = multiplyVectors(a, b);
    if(result.size() > n) {
        std::reverse(result.begin(), result.end());
        while(result.size() > n) result.pop_back();
        std::reverse(result.begin(), result.end());
    }
    else if(result.size() < n) {
        std::reverse(result.begin(), result.end());
        while(result.size() < n) result.push_back(0);
        std::reverse(result.begin(), result.end());
    }

    return result;
}

//Фунцкия для добавления единиц в начало числа, если оно отрицательное
std::string negativeAdding (std::string first, size_t x, size_t y, size_t t) {
    if(first.length() == x + y && first[0] == '1') {
        for(size_t i = 0; i < t - x - y; i++) {
            first = "1" + first;
        }
    }
    return first;
}

//Функция для сложения двух чисел с фикс точкой
std::string sumAB(std::string first, std::string second, size_t x, size_t y) {
    first = negativeAdding(first, x, y, 32);
    second = negativeAdding(second, x, y, 32);

    std::bitset<32> firstNum(first);
    std::bitset<32> secondNum(second);

    std::bitset<32> sum = firstNum.to_ulong() + secondNum.to_ulong();
    std::string result = sum.to_string();
    result = result.substr(32 - x - y,  x + y);

    return result;
}

//Функция для вычитания двух чисел с фикс точкой
std::string diffAB(std::string first, std::string second, size_t x, size_t y) {
    first = negativeAdding(first, x, y, 32);
    second = negativeAdding(second, x, y, 32);

    std::bitset<32> firstNum(first);
    std::bitset<32> secondNum(second);

    std::bitset<32> diff = firstNum.to_ulong() - secondNum.to_ulong();
    std::string result = diff.to_string();
    result = result.substr(32 - x - y, 32);

    return result;
}

//Функция для умножения двух чисел с фикс точкой
std::string multAB(std::string first, std::string second, size_t x, size_t y) {
    first = negativeAdding(first, x, y, 64);
    second = negativeAdding(second, x, y, 64);

    std::bitset<64> firstNum(first);
    std::bitset<64> secondNum(second);
    std::bitset<64> product = static_cast<unsigned long long>(firstNum.to_ullong() * secondNum.to_ullong());
    std::string result = product.to_string();
    result = result.substr(64 - x - y - y, x + y + y);

    return result;
}

//Функция для деления двух чисел с фикс точкой
std::string quoAB(std::string first, std::string second, size_t x, size_t y) {
    for (size_t i = 0; i < y; i++) {
        first += "0";
    }
    long long fir = binaryToDecimal(first, x + y + y, true);
    long long sec = binaryToDecimal(second, x + y, true);
    bool sign = true;
    if ((fir < 0 && sec > 0) || (fir > 0 && sec < 0)) {
        sign = false;
    }
    fir = abs(fir); sec = abs(sec);
    first = decimalToBinary(fir, x + y);
    second = decimalToBinary(sec, x + y);
    std::bitset<64> firstNum(first);
    std::bitset<64> secondNum(second);

    if(secondNum.to_ullong() == 0) return "error";
    std::bitset<64> product = static_cast<unsigned long>(firstNum.to_ullong() / secondNum.to_ullong());
    if (!sign) {
        product.flip();
    }
    std::string result = product.to_string();
    result = result.substr(64 - x - y, x + y);

    return result;
}


//Функция округления к минус бесконечности
std::pair<long long, std::string> towardNegInfinity(long long intPart, std::string result, size_t x, size_t y, bool sign) {
    if(sign) {
        result = result.substr(0, y);
    }
    else {
        bool zero = true;
        for(size_t i = y; i < x; i++) {
            if(result[i] != '0') {
                zero = false;
                break;
            }
        }
        result = result.substr(0, y);
        if(!zero) {
            result = vectorToString(addVectors(stringToVector(result), {1}));
            if(result.length() > y) {
                result = result.substr(1, y);
                intPart -= 1;
            }
        }
    }
    return std::make_pair(intPart, result);
}

//Функция округления к плюс бесконечности
std::pair<long long, std::string> towardInfinity(long long intPart, std::string result, size_t x, size_t y, bool sign) {
    if (sign){
        bool zero = true;
        for(size_t i = y; i < x; i++) {
            if(result[i] != '0') {
                zero = false;
                break;
            }
        }
        result = result.substr(0, y);
        if(!zero) {
            result = vectorToString(addVectors(stringToVector(result), {1}));
            if(result.length() > y) {
                result = result.substr(1, y);
                intPart += 1;
            }
        }
    }
    else {
        result = result.substr(0, y);
    }
    return std::make_pair(intPart, result);
}

//Функция округления к ближайшему четному
std::pair<long long, std::string> nearestEven(long long intPart, std::string result, size_t x, size_t y) {
    long long zero = 0;
    if(result[y] < '5'){
        zero = -1;
    }
    else if(result[y] > '5') {
        zero = 1;
    }
    else {
        for(size_t i = y + 1; i < x; i++) {
            if(result[i] != '0') {
                zero = 1;
                break;
            }
        }
    }
    result = result.substr(0, y);
    if(zero == 1 || (zero == 0 && ((result[y - 1] - '0') % 2))) {
        result = vectorToString(addVectors(stringToVector(result), {1}));
        if(result.length() > y) {
            result = result.substr(1, y);
            intPart += 1;
        }
    }
    return std::make_pair(intPart, result);
}

//Функция округления
std::pair<long long, std::string> rounding(long long intPart, std::string input, std::string format, size_t x, size_t y, bool sign) {
    std::string result = input;
    if(format == "0") {
        result = result.substr(0, y);
    }
    else if (format == "1") {
        return nearestEven(intPart, result, x, y);
    }
    else if (format == "2") {
        return towardInfinity(intPart, result, x, y, sign);
    }
    else if (format == "3") {
        return towardNegInfinity(intPart, result, x, y, sign);
    }
    return std::make_pair(intPart, result);
}

//Функция для привидения числа с фикс точкой к нужному виду
std::pair<bool, std::pair<long long, std::string>> toFormat(std::string result, std::string format, size_t x, size_t y, size_t t) {
    std::pair<std::string, std::string> parts = splitNumber(result, x, y);
    long long intPart = binaryToDecimal(parts.first, x, true);
    bool sign = true;
    if (intPart < 0) {
        sign = false;
    }
    std::string fracPart;
    fracPart = vectorToString(fractionalPart(intToVector(binaryToDecimal(parts.second, y, false)), y));
    if (!sign) {
        std::vector<long long> additional = {1};
        for (size_t i = 0; i < y; i++) {
            additional.push_back(0);
        }
        std::vector<long long> frac = subtractVectors(additional, stringToVector(fracPart));
        if(frac.size() == y) {
            fracPart = vectorToString(frac);
            intPart++;
        }
    }
    return {sign, rounding(intPart, fracPart, format, y, t, sign)};
}

//Функция для привидения числа с фикс точкой после умножения к нужному виду
std::pair<bool, std::pair<long long, std::string>> toMultFormat(std::string result, std::string format, size_t x, size_t y) {
    std::pair<bool, std::pair<long long, std::string>> firstPart = toFormat(result, format, x + y, y, 0);
    result = decimalToBinary(firstPart.second.first, x + y);
    return toFormat(result, format, x, y, 3);
}

std::pair<std::string, std::string> splitFrac(std::string result, size_t x, size_t y) {
    while (result.length() < x + y + 1) {
        result = "0" + result;
    }
    return {result.substr(1, x), result.substr(x + 1, result.length() - x - 1)};
}

std::pair<long long, std::string> roundingFloating(std::string result, std::string format, size_t x, bool sign) {
    long long intPart = binaryToDecimal(result.substr(0, x), x, false);
    if(!sign) intPart *= -1;
    if (result.length() > x)
        return rounding(intPart, result.substr(x + 1, result.length() - x), format, x, 0, sign);
    else return {intPart, result};
}

std::string mantissa(std::string result, std::string format, size_t x, bool sign) {
    std::pair<long long, std::string> res = roundingFloating(result, format, x, sign);
    if(!sign) res.first *= -1;
    result = decimalToBinary(res.first, x);
    while (result.length() < x) result = "0" + result;
    while (result.length() % 4 != 0) result += "0";
    result = binaryToHex(result);
    return result;
}


//Функция для привидения числа с плавающей точкой
std::pair<bool, std::pair<long long, std::string>> doF(std::string result, std::string format, size_t x, size_t y, size_t t) {
    bool sign = true;
    if(result.length() >= x + y + 1 && result[0] == '1'){
        sign = false;
    }
    std::pair<std::string, std::string> parts = splitFrac(result, x, y);
    long long exp = binaryToDecimal(parts.first, x, true) - t;
    std::string mantis = mantissa(parts.second, format, y, sign);
    return {sign, {exp, mantis}};
}
