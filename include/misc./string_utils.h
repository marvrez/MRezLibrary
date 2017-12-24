#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <sstream>
#include <vector>

namespace str_utils {

inline std::string str_format(const char* fmt, va_list args) {
    char buf[8192];
    vsnprintf(buf, 8192, fmt, args);
    return std::string(buf);
}

inline std::string str_format(const char* fmt, ...) {
    char buf[8192];
    va_list args;

    va_start(args, fmt);
    vsnprintf(buf, 8192, fmt, args);
    va_end(args);

    return std::string(buf);
}

inline void to_lower_case(std::string& str) {
    for (auto it = std::begin(str); it != std::end(str); it++) {
        if (*it >= 'A' && *it <= 'Z')
            *it += ('a' - 'A');
    }
}

inline void to_upper_case(std::string& str) {
    for (auto it = std::begin(str); it != std::end(str); it++) {
        if (*it >= 'a' && *it <= 'z')
            *it -= ('a' - 'A');
    }
}

inline void remove_spaces(std::string& str) {
    str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
}

inline void trim_left(std::string& str) {
    int trim_count = 0;
    for (size_t i = 0; i < str.length(); ++i) {
        if (isspace(str[i])) trim_count++;
        else if (!isspace(str[i])) break;
    }
    if (trim_count > 0) str.erase(0, trim_count);
}

inline void trim_right(std::string& str) {
    int trim_count = 0;
    for (int i = str.length() - 1; i >= 0; i--) {
        if (isspace(str[i])) trim_count++;
        else if (!isspace(str[i])) break;
    }
    if (trim_count > 0) str.erase(str.length() - trim_count, str.length() - 1);
}

inline void trim(std::string& str) {
    trim_left(str);
    trim_right(str);
}

template <typename OP>
inline void split(const std::string &s, char delim, OP op) {
    std::stringstream ss(s);
    for(std::string item; std::getline(ss, item, delim);)
        *op++ = item;
}

inline std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

inline bool ends_with(const std::string& s, char ch) {
    return !s.empty() && s.back() == ch;
}

inline bool ends_with(const std::string& s, const std::string& suffix) {
    return std::mismatch(suffix.rbegin(), suffix.rend(), s.rbegin()).first == suffix.rend();
}

inline bool starts_with(const std::string& s, char ch) {
    return !s.empty() && s.front() == ch;
}

inline bool starts_with(const std::string& s, const std::string& prefix) {
    return std::mismatch(prefix.begin(), prefix.end(), s.begin()).first == prefix.end();
}

} //namespace str_utils;

#endif // STRING_UTILS_H
