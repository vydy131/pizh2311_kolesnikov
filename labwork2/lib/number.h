#pragma once
#include <cinttypes>
#include <iostream>
#include <vector>

struct uint2022_t {
    std::vector<uint8_t> data;

    uint2022_t() : data(37, 0) {}

    void set_bit(uint32_t index, bool value) {
        size_t byte_index = index / 8;
        size_t bit_index = index % 8;
        if (value) {
            data[byte_index] |= (1 << bit_index);
        } else {
            data[byte_index] &= ~(1 << bit_index);
        }
    }

    bool get_bit(uint32_t index) const {
        size_t byte_index = index / 8;
        size_t bit_index = index % 8;
        return data[byte_index] & (1 << bit_index);
    }

    size_t size() const {
        return data.size();
    }

    uint8_t& operator[](size_t index) {
        return data[index];
    }

    const uint8_t& operator[](size_t index) const {
        return data[index];
    }
};

// Функции конвертации
uint2022_t from_uint(uint32_t i);
uint2022_t from_string(const char* buff);

// Операторы
uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs);
uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs);
uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs);
uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs);

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs);
bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs);

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value);
