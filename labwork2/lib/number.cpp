#include "number.h"
#include <string>
#include <algorithm>

bool less_than(const uint2022_t& a, const uint2022_t& b) {
    for (int i = uint2022_t::CAPACITY - 1; i >= 0; --i) {
        if (a.data[i] < b.data[i]) return true;
        if (a.data[i] > b.data[i]) return false;
    }
    return false;
}

bool more_than(const uint2022_t& a, const uint2022_t& b) {
    for (int i = uint2022_t::CAPACITY - 1; i >= 0; --i) {
        if (a.data[i] > b.data[i]) return true;
        if (a.data[i] < b.data[i]) return false;
    }
    return false;
}

uint2022_t from_uint(uint32_t i) {
    uint2022_t result;
    result.data[0] = i;
    return result;
}

uint2022_t from_string(const char* ch) {
    uint2022_t result;
    uint2022_t base = from_uint(10);

    for (const char* p = ch; *p; ++p) {
        result = result * base + from_uint(*p - '0');
    }
    return result;
}

uint2022_t operator+(const uint2022_t& first, const uint2022_t& second) {
    uint2022_t result;
    uint64_t x = 0;

    for (int i = 0; i < uint2022_t::CAPACITY; ++i) {
        uint64_t sum = (uint64_t)first.data[i] + second.data[i] + x;
        result.data[i] = sum & 0xFFFFFFFF;
        x = sum >> 32;
    }

    return result;
}

uint2022_t operator-(const uint2022_t& first, const uint2022_t& second) {
    uint2022_t result;
    int64_t x = 0;

    for (int i = 0; i < uint2022_t::CAPACITY; ++i) {
        int64_t diff = (int64_t)first.data[i] - second.data[i] - x;
        if (diff < 0) {
            diff += ((int64_t)1 << 32);
            x = 1;
        } else {
            x = 0;
        }
        result.data[i] = (uint32_t)diff;
    }

    return result;
}

uint2022_t operator*(const uint2022_t& first, const uint2022_t& second) {
    uint2022_t result;

    for (int i = 0; i < uint2022_t::CAPACITY; ++i) {
        uint64_t x = 0;

        for (int j = 0; j + i < uint2022_t::CAPACITY; ++j) {
            uint64_t temp = (uint64_t)first.data[i] * second.data[j] + result.data[i + j] + x;
            result.data[i + j] = temp & 0xFFFFFFFF;
            x = temp >> 32;
        }
    }

    return result;
}

uint2022_t operator/(const uint2022_t& first, const uint2022_t& second) {
    if (second == from_uint(0)) return from_uint(0); // Защита от деления на ноль

    uint2022_t result, rem;

    for (int i = uint2022_t::CAPACITY * 32 - 1; i >= 0; --i) {
        rem = rem * from_uint(2);
        rem.data[0] |= (first.data[i / 32] >> (i % 32)) & 1;

        if (!less_than(rem, second)) {
            rem = rem - second;
            result.data[i / 32] |= (1U << (i % 32));
        }
    }

    return result;
}

uint2022_t operator%(const uint2022_t& first, const uint2022_t& second) {
    if (second == from_uint(0)) return from_uint(0); // Деление на ноль

    uint2022_t rem;

    for (int i = uint2022_t::CAPACITY * 32 - 1; i >= 0; --i) {
        rem = rem * from_uint(2);
        rem.data[0] |= (first.data[i / 32] >> (i % 32)) & 1;

        if (!less_than(rem, second)) {
            rem = rem - second;
        }
    }

    return rem;
}

bool operator==(const uint2022_t& first, const uint2022_t& second) {
    for (int i = 0; i < uint2022_t::CAPACITY; ++i) {
        if (first.data[i] != second.data[i]) return false;
    }
    return true;
}

bool operator!=(const uint2022_t& first, const uint2022_t& second) {
    return !(first == second);
}

std::ostream& operator<<(std::ostream& str, const uint2022_t& val) {
    uint2022_t copy = val;
    std::string result;
    uint2022_t zero = from_uint(0);
    uint2022_t ten = from_uint(10);

    while (copy != zero) {
        uint2022_t digit = copy % ten;
        result.push_back('0' + digit.data[0]);
        copy = copy / ten;
    }

    if (result.empty()) result = "0";

    std::reverse(result.begin(), result.end());
    str << result;
    return str;
}