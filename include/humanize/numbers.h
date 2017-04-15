#ifndef NUMBERS_H
#define NUMBERS_H
#include "format_int.h"

#include <iostream>
#include <string>
#include <vector>
#include <type_traits>


struct Number {
    int len;
    char suffix;
};

struct NumberWords {
    int len;
    std::string suffix;
};

namespace humanize {
std::string num_words[] = { "", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
                            "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen",
                            "eighteen", "nineteen" };
std::string ten_words[]  = {"", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety" };
std::string orders_of_magnitude_words[] = { "", " thousand", " million", " billion", " trillion", " quadrillion", " quintillion" };
Number nums[] = {{19,'E'}, {16,'P'}, {13, 'T'}, {10, 'G'}, {7, 'M'}, {4, 'K'}};
NumberWords numWords[] = {{19,"exa"}, {16,"peta"}, {13, "tera"}, {10, "giga"}, {7, "mega"}, {4, "kilo"}};

namespace numbers {

template <typename Numeral>
void numberToChars(char* str, Numeral x) {
    std::cout << format_int<Numeral>::format() << "\n";
    std::sprintf(str, format_int<Numeral>::format(), x);
}

template<bool isSigned>
class checkSigned { };

template<>
class checkSigned<true>
{
public:
    template<typename Numeral>
    static void setSuffix(char* finalStr, Numeral num, unsigned int decimals, const char* numStr,
                          int idx, const Number& numStruct) {
        if (decimals > 0)
            std::sprintf(finalStr, "%.*s.%.*s%c", idx, numStr, decimals,
                         numStr + idx, numStruct.suffix);
        else
            std::sprintf(finalStr, "%.*s%c", idx, numStr, numStruct.suffix);
    }

    template<typename Numeral>
    static void setSuffix(char* finalStr, Numeral num, unsigned int decimals, const char* numStr,
                          int idx, const NumberWords& numStruct) {
        if (decimals > 0)
            std::sprintf(finalStr, "%.*s.%.*s%c", idx, numStr, decimals,
                         numStr + idx, numStruct.suffix.c_str());
        else
            std::sprintf(finalStr, "%.*s%c", idx, numStr, numStruct.suffix.c_str());
    }
};

template<>
class checkSigned<false>
{
public:
    template<typename Numeral>
    static void setSuffix(char* finalStr, Numeral num, unsigned int decimals, const char* numStr,
                          int idx, const Number& numStruct) {
        if (decimals > 0)
            std::sprintf(finalStr, "%.*s.%.*s%c", idx, numStr, decimals,
                         numStr + idx, numStruct.suffix);
        else
            std::sprintf(finalStr, "%.*s%c", idx, numStr, numStruct.suffix);
    }

    template<typename Numeral>
    static void setSuffix(char* finalStr, Numeral num, unsigned int decimals, const char* numStr,
                          int idx, const NumberWords& numStruct) {
        if (decimals > 0)
            std::sprintf(finalStr, "%.*s.%.*s%c", idx, numStr, decimals,
                         numStr + idx, numStruct.suffix);
        else
            std::sprintf(finalStr, "%.*s%c", idx, numStr, numStruct.suffix);
    }
};


template<typename Numeral>
std::string getCompactName(const Numeral num, unsigned int decimals = 0) {
    constexpr auto maxSize = std::numeric_limits<Numeral>::digits10 +
                                   std::numeric_limits<Numeral>::is_signed + 2;
    char str[maxSize], absStr[maxSize];
    numberToChars(str, num);

    Numeral absNum = static_cast<Numeral>(std::abs(num));
    if(absNum < 1000) return str;

    numberToChars(absStr, absNum);
    int absNumLength = static_cast<int>(strlen(absStr));
    std::cout << absNumLength << "\n";

    for(const auto& numStruct : numWords) {
        if(absNumLength >= numStruct.len) {
            int idx = absNumLength - numStruct.len + 1;
            char finalStr[maxSize];
            checkSigned<std::is_signed<Numeral>::value>::setSuffix(finalStr, num, decimals, absStr, idx, numStruct);
            return finalStr;
        }
    }
    return "rip";
}

template<typename Numeral, typename = typename std::enable_if<std::is_integral<Numeral>::value>::type>
std::string getCompactSymbol(const Numeral num, unsigned int decimals = 0) {
    constexpr auto maxSize = std::numeric_limits<Numeral>::digits10 +
                                   std::numeric_limits<Numeral>::is_signed + 2;
    char str[maxSize], absStr[maxSize];
    numberToChars(str, num);

    Numeral absNum = static_cast<Numeral>(std::abs(num));
    if(absNum < 1000) return str;

    numberToChars(absStr, absNum);
    int absNumLength = static_cast<int>(strlen(absStr));
    std::cout << absNumLength << "\n";

    for(const auto& numStruct : nums) {
        if(absNumLength >= numStruct.len) {
            int idx = absNumLength - numStruct.len + 1;
            char finalStr[maxSize];
            checkSigned<std::is_signed<Numeral>::value>::setSuffix(finalStr, num, decimals, absStr, idx, numStruct);
            return finalStr;
        }
    }
    return "rip";
}

template<typename Numeral, typename = typename std::enable_if<std::is_integral<Numeral>::value>::type>
std::string spellNumberLessThanThousand(const Numeral num) {
    Numeral tmp = num;
    std::string cur;

    if (tmp % 100 < 20){
        cur = num_words[tmp % 100];
        tmp /= 100;
    }
    else {
        cur = num_words[tmp % 10];
        tmp /= 10;

        cur = ten_words[tmp % 10] + " " + cur;
        tmp /= 10;
    }
    if (tmp == 0) return cur;
    return num_words[tmp] + " hundred " + cur;
}

template<typename Numeral, typename = typename std::enable_if<std::is_integral<Numeral>::value>::type>
std::string spellNumber(const Numeral num) {
    Numeral tmp = num;
    if(tmp == 0) return "zero";

    std::string prefix, cur;
    int place = 0;

    if(tmp < 0) tmp = -tmp, prefix = "negative ";

    do {
        int n = tmp % 1000;
        if (n != 0){
            std::string s = spellNumberLessThanThousand(n);
            cur = s + orders_of_magnitude_words[place] + " " + cur;
        }
        place++;
        tmp /= 1000;
    } while (tmp > 0);
    return prefix + cur;
}

template<typename Numeral, typename = typename std::enable_if<std::is_integral<Numeral>::value>::type>
std::string getOrdinalForm(const Numeral num) {
    std::string suffix, numString = std::to_string(num);
    if(num < 0) return numString;

    if((num % 100) / 10 == 1) suffix = "th";
    else switch(num % 10) {
        case 1:  suffix = "st"; break;
        case 2:  suffix = "nd"; break;
        case 3:  suffix = "rd"; break;
        default: suffix = "th"; break;
    }
    return numString + suffix;
}

} //namespace numbers
} //namespace humanizer


#endif // NUMBERS_H
