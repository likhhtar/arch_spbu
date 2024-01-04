#include "functions.h"

int main(int argc, char** argv) {
    std::string format = argv[1];
    std::string round = argv[2];
    std::string first_number = argv[3];
    std::string operation, second_number;
    bool is_operation = false;
    if (argc == 6) {
        is_operation = true;
        operation = argv[4];
        second_number = argv[5];
    }
    if (format == "h") {
        std::string first = hexToBinary(first_number);
        size_t a, b, pw;
        a = 5; b = 10; pw = 15;
        if (is_operation) {
            std::pair<bool, std::pair<long long, std::string>> res;
            res = doF(first, round, a, b, pw);
            bool zerof = true;
            first = "";
            for(size_t i = 0; i < res.second.second.length(); i++) {
                if(res.second.second[i] != '0'){
                    zerof = false;
                }
            }
            if (res.second.first == -(long long)pw && zerof){
                first = "0x0.000p+0";
            }
            else if (res.second.first + 1 == -(long long)pw && zerof) {
                if(res.first) first = "inf";
                else first = "-inf";
            }
            else if (res.second.first + 1 == -(long long)pw) {
                first = "nan";
            }

            std::string second = hexToBinary(second_number);
            res = doF(second, round, a, b, pw);
            bool zero = true;
            second = "";
            for(size_t i = 0; i < res.second.second.length(); i++) {
                if(res.second.second[i] != '0'){
                    zero = false;
                }
            }
            if (res.second.first == -(long long)pw && zero){
                second = "0x0.000p+0";
            }
            else if (res.second.first + 1 == -(long long)pw && zero) {
                if(res.first) second = "inf";
                else second = "-inf";
            }
            else if (res.second.first + 1 == -(long long)pw) {
                second = "nan";
            }

            if (operation == "+") {
                if(second[0] == 'i' && first == "") std::cout << "inf";
                else if(first[0] == 'i' && second == "") std::cout << "inf";
                else if(second[0] == '-' && first == "") std::cout << "-inf";
                else if(first[0] == '-' && second == "") std::cout << "-inf";
                else if(second[0] == '-' && first[0] == '-') std::cout << "-inf";
                else if(second[0] == 'i' && first[0] == 'i') std::cout << "inf";
                else std::cout << "nan";
            }
            else if (operation == "-") {
                if(second[0] == 'i' && (first == "" || first[0] == '0')) std::cout << "inf";
                else if(first[0] == 'i' && (second == "" || second[0] == '0')) std::cout << "inf";
                else if(second[0] == '-' && (first == "" || first[0] == '0')) std::cout << "-inf";
                else if(first[0] == '-' && (second == "" || second[0] == '0')) std::cout << "-inf";
                else if(second[0] == 'i' && first[0] == '-') std::cout << "inf";
                else if(second[0] == '-' && first[0] == 'i') std::cout << "-inf";
                else std::cout << "nan";
            }
            else if (operation == "*") {
                if(second[0] == '0' || first[0] == '0') std::cout << "0x0.000p+0";
                else if(second[0] == 'i' && first[0] == 'i') std::cout << "inf";
                else if(second[0] == '-' && first[0] == '-') std::cout << "inf";
                else std::cout << "nan";
            }
            else if (operation == "/") {
                if (second[0] == '0' && first[0] == '0') std::cout << "nan";
                else if(second[0] == '0' && res.first) std::cout << "inf";
                else if(second[0] == '0' && !res.first) std::cout << "-inf";
                else std::cout << "nan";
            }
        }
        else {
            std::pair<bool, std::pair<long long, std::string>> res;
            res = doF(first, round, a, b, pw);
            bool zero = true;
            for(size_t i = 0; i < res.second.second.length(); i++) {
                if(res.second.second[i] != '0'){
                    zero = false;
                }
            }

            if (res.second.first == -(long long)pw && zero){
                std::cout << "0x0.000p+0";
            }
            else if (res.second.first + 1 == -(long long)pw && zero) {
                if(res.first) std::cout << "inf";
                else std::cout << "-inf";
            }
            else if (res.second.first + 1 == -(long long)pw) {
                std::cout << "nan";
            }
            else {
                if(!res.first) std::cout << "-";
                std::cout << "0x1.";
                std::cout << res.second.second;
                std::cout << "p" << res.second.first;
            }
        }
    }
    else if (format == "f") {
        std::string first = hexToBinary(first_number);
        size_t a, b, pw;
        a = 8; b = 23; pw = 127;
        if (is_operation) {
            std::pair<bool, std::pair<long long, std::string>> res;
            res = doF(first, round, a, b, pw);
            bool zerof = true;
            first = "";
            for(size_t i = 0; i < res.second.second.length(); i++) {
                if(res.second.second[i] != '0'){
                    zerof = false;
                }
            }
            if (res.second.first == -(long long)pw && zerof){
                first = "0x0.000000p+0";
            }
            else if (res.second.first + 1 == -(long long)pw && zerof) {
                if(res.first) first = "inf";
                else first = "-inf";
            }
            else if (res.second.first + 1 == -(long long)pw) {
                first = "nan";
            }

            std::string second = hexToBinary(second_number);
            res = doF(second, round, a, b, pw);
            bool zero = true;
            second = "";
            for(size_t i = 0; i < res.second.second.length(); i++) {
                if(res.second.second[i] != '0'){
                    zero = false;
                }
            }
            if (res.second.first == -(long long)pw && zero){
                second = "0x0.000000p+0";
            }
            else if (res.second.first + 1 == -(long long)pw && zero) {
                if(res.first) second = "inf";
                else second = "-inf";
            }
            else if (res.second.first + 1 == -(long long)pw) {
                second = "nan";
            }

            if (operation == "+") {
                if(second[0] == 'i' && first == "") std::cout << "inf";
                else if(first[0] == 'i' && second == "") std::cout << "inf";
                else if(second[0] == '-' && first == "") std::cout << "-inf";
                else if(first[0] == '-' && second == "") std::cout << "-inf";
                else if(second[0] == '-' && first[0] == '-') std::cout << "-inf";
                else if(second[0] == 'i' && first[0] == 'i') std::cout << "inf";
                else std::cout << "nan";
            }
            else if (operation == "-") {
                if(second[0] == 'i' && (first == "" || first[0] == '0')) std::cout << "inf";
                else if(first[0] == 'i' && (second == "" || second[0] == '0')) std::cout << "inf";
                else if(second[0] == '-' && (first == "" || first[0] == '0')) std::cout << "-inf";
                else if(first[0] == '-' && (second == "" || second[0] == '0')) std::cout << "-inf";
                else if(second[0] == 'i' && first[0] == '-') std::cout << "inf";
                else if(second[0] == '-' && first[0] == 'i') std::cout << "-inf";
                else std::cout << "nan";
            }
            else if (operation == "*") {
                if(second[0] == '0' || first[0] == '0') std::cout << "0x0.000000p+0";
                else if(second[0] == 'i' && first[0] == 'i') std::cout << "inf";
                else if(second[0] == '-' && first[0] == '-') std::cout << "inf";
                else std::cout << "nan";
            }
            else if (operation == "/") {
                if (second[0] == '0' && first[0] == '0') std::cout << "nan";
                else if(second[0] == '0' && res.first) std::cout << "inf";
                else if(second[0] == '0' && !res.first) std::cout << "-inf";
                else std::cout << "nan";
            }
        }
        else {
            std::pair<bool, std::pair<long long, std::string>> res;
            res = doF(first, round, a, b, pw);
            bool zero = true;
            for(size_t i = 0; i < res.second.second.length(); i++) {
                if(res.second.second[i] != '0'){
                    zero = false;
                }
            }

            if (res.second.first == -(long long)pw && zero){
                std::cout << "0x0.000000p+0";
            }
            else if (res.second.first + 1 == -(long long)pw && zero) {
                if(res.first) std::cout << "inf";
                else std::cout << "-inf";
            }
            else if (res.second.first + 1 == -(long long)pw) {
                std::cout << "nan";
            }
            else {
                if(!res.first) std::cout << "-";
                std::cout << "0x1.";
                std::cout << res.second.second;
                std::cout << "p" << res.second.first;
            }
        }
    }
    else {
        std::string first = hexToBinary(first_number);
        size_t a, b;
        splitAB(format, a, b);
        if (is_operation){
            std::string second = hexToBinary(second_number);
            std::string result;
            std::pair<bool, std::pair<long long, std::string>> res;
            if (operation == "+") {
                result = sumAB(first, second, a, b);
                res = toFormat(result, round, a, b, 3);
            }
            else if (operation == "-") {
                result = diffAB(first, second, a, b);
                res = toFormat(result, round, a, b, 3);
            }
            else if (operation == "*") {
                result = multAB(first, second, a, b);
                res = toMultFormat(result, round, a, b);
            }
            else if (operation == "/") {
                 result = quoAB(first, second, a, b);
                 if(result == "error") {
                     std::cerr << result;
                     return 1;
                 }
                res = toFormat(result, round, a, b, 3);
            }
            while ((res.second.second).length() < 3) res.second.second += "0";
            if(!res.first && res.second.first == 0 && res.second.second != "000") std::cout << '-';
            std::cout << res.second.first << '.' << res.second.second;
        }
        else {
            std::pair<bool, std::pair<long long, std::string>> res;
            res = toFormat(first, round, a, b, 3);
            while ((res.second.second).length() < 3) res.second.second += "0";
            if(!res.first && res.second.first == 0 && res.second.second != "000") std::cout << '-';
            std::cout << res.second.first << '.' << res.second.second;
        }
    }
    return 0;
}
