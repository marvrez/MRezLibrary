#ifndef FORMAT_INT_H
#define FORMAT_INT_H

#include <iostream>
#include <inttypes.h>

template<typename T>
class format_int {
public:
        static constexpr const char*
        format() noexcept {
            return "";
        }
};


template<>
class format_int<int64_t> {
public:
        static constexpr const char*
        format() noexcept {
            return "%" PRId64;
        }
};


template<>
class format_int<intmax_t> {
public:
        static constexpr const char*
        format() noexcept {
            return "%ld" ;
        }
};

template<>
class format_int<int32_t> {
public:
        static constexpr const char*
        format() noexcept {
            return "%" PRId32;
        }
};


template<>
class format_int<int16_t> {
public:
        static constexpr const char*
        format() noexcept {
            return "%" PRId16;
        }
};

template<>
class format_int<int8_t> {
public:
        static constexpr const char*
        format() noexcept {
            return "%" PRId8;
        }
};


template<>
class format_int<uint8_t>{
public:
        static constexpr const char*
        format() noexcept {
            return "%" PRIu8;
        }
};


template<>
class format_int<uint16_t>{
public:
        static constexpr const char*
        format() noexcept {
            return "%" PRIu16;
        }
};

template<>
class format_int<uint32_t>{
public:
        static constexpr const char*
        format() noexcept {
            return "%" PRIu32;
        }
};

template<>
class format_int<uintmax_t> {
public:
        static constexpr const char*
        format() noexcept {
            return "%lu" ;
        }
};

template<>
class format_int<uint64_t> {
public:
        static constexpr const char*
        format() noexcept {
            return "%" PRIu64;
        }
};

#endif // FORMAT_INT_H
