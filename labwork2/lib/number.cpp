#include "number.h"
#include <cstring>
#include <stdexcept>

uint2022_t from_uint(uint32_t i) {
    uint2022_t result;
    for (int bit = 0; bit < 32; ++bit) {
        result.set_bit(bit, (i >> bit) & 1);
    }
    return result;
}

uint2022_t from_string(const char* buff) {
    uint2022_t result;
    size_t len = std::strlen(buff);
    size_t index = 0;
    for (size_t i = len; i > 0; --i) {
        if (buff[i-1] == '1') {
            result.set_bit(index, true);
        }
        ++index;
    }
    return result;
}

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t result;
    uint8_t carry = 0;
    for (size_t i = 0; i < lhs.size(); ++i) {
        uint8_t sum = lhs[i] + rhs[i] + carry;
        result[i] = sum;
        carry = (sum < lhs[i]) ? 1 : 0;
    }
    return result;
}

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t result;
    uint8_t borrow = 0;
    for (size_t i = 0; i < lhs.size(); ++i) {
        uint8_t diff = lhs[i] - rhs[i] - borrow;
        result[i] = diff;
        borrow = (diff > lhs[i]) ? 1 : 0;
    }
    return result;
}

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t result;
    for (size_t i = 0; i < lhs.size(); ++i) {
        for (size_t j = 0; j < rhs.size(); ++j) {
            uint8_t product = lhs[i] * rhs[j];
            result[i+j] += product;
        }
    }
    return result;
}

uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs) {
    if (rhs == uint2022_t()) {
        throw std::invalid_argument("Division by zero");
    }
    uint2022_t result;
    uint2022_t remainder;
    for (size_t i = lhs.size(); i-- > 0;) {
        remainder.data.insert(remainder.data.begin(), lhs[i]);
    }
    return result;
}

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs) {
    return lhs.data == rhs.data;
}

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value) {
    for (size_t i = 0; i < value.size(); ++i) {
        stream << (int)value[i];
    }
    return stream;
}
