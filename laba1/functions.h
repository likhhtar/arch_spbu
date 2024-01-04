#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <iostream>
#include <cassert>
#include <math.h>
#include <vector>
#include <algorithm>
#include <bitset>


std::string hexDigitToBinary(char hexDigit);
std::string hexToBinary(std::string hexValue);
long long binaryToDecimal(const std::string& binary, size_t x, bool integer);
std::string decimalToBinary(long long n, size_t x);

bool splitAB(const std::string& input, size_t& A, size_t& B);
std::pair<std::string, std::string> splitNumber(std::string& str, size_t A, size_t B);

std::vector<long long> stringToVector(std::string str);
std::vector<long long> intToVector(long long n);
std::string intToString(long long n);
std::string vectorToString(std::vector<long long> vec);

void removeLeadingZeros(std::vector<long long>& vec);
std::vector<long long> addVectors(std::vector<long long> a, std::vector<long long> b);
std::vector<long long> inversion(std::vector<long long> a, size_t x, size_t y);
bool compare(std::vector<long long> a, std::vector<long long> b);
std::vector<long long> subtractVectors(std::vector<long long> a, std::vector<long long> b);
std::vector<long long> multiplyVectors(std::vector<long long> a, std::vector<long long> b);
std::vector<long long> fractionalPart(std::vector<long long> a, size_t n);

std::string sumAB(std::string first, std::string second, size_t x, size_t y);
std::string diffAB(std::string first, std::string second, size_t x, size_t y);
std::string multAB(std::string first, std::string second, size_t x, size_t y);
std::string quoAB(std::string first, std::string second, size_t x, size_t y);

std::pair<long long, std::string> towardNegInfinity(long long intPart, std::string result, size_t x, size_t y, bool sign);
std::pair<long long, std::string> towardInfinity(long long intPart, std::string result, size_t x, size_t y, bool sign);
std::pair<long long, std::string> nearestEven(long long intPart, std::string result, size_t x, size_t y);
std::pair<long long, std::string> rounding(long long intPart, std::string input, std::string format, size_t x, size_t y, bool sign);

std::pair<bool, std::pair<long long, std::string>> toFormat(std::string result, std::string format, size_t x, size_t y, size_t t);
std::pair<bool, std::pair<long long, std::string>> toMultFormat(std::string result, std::string format, size_t x, size_t y);

std::pair<bool, std::pair<long long, std::string>> doF(std::string result, std::string format, size_t x, size_t y, size_t t);


#endif //FUNCTIONS_H
