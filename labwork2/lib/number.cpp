#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstring>

class uint2022_t {
public:
    std::vector<uint8_t> data;

    // Конструктор из числа
    uint2022_t() : data(32, 0) {}

    uint2022_t(uint32_t i) : data(32, 0) {
        for (int bit = 0; bit < 32; ++bit) {
            set_bit(bit, (i >> bit) & 1);
        }
    }

    // Конструктор из строки
    uint2022_t(const char* buff) : data(32, 0) {
        size_t len = std::strlen(buff);
        size_t index = 0;
        for (size_t i = len; i > 0; --i) {
            if (buff[i-1] == '1') {
                set_bit(index, true);
            }
            ++index;
        }
    }

    size_t size() const {
        return data.size();
    }

    // Операция установки бита
    void set_bit(size_t bit, uint8_t value) {
        if (bit < size()) {
            data[bit] = value;
        }
    }

    uint8_t operator[](size_t index) const {
        return data[index];
    }

    uint8_t& operator[](size_t index) {
        return data[index];
    }

    // Операции сравнения
    bool operator==(const uint2022_t& rhs) const {
        return data == rhs.data;
    }

    bool operator!=(const uint2022_t& rhs) const {
        return !(*this == rhs);
    }

    // Операция вывода
    friend std::ostream& operator<<(std::ostream& stream, const uint2022_t& value) {
        for (size_t i = value.size(); i-- > 0;) {
            stream << (int)value[i];
        }
        return stream;
    }
};

// Операции над числами
uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t result;
    uint8_t carry = 0;
    for (size_t i = 0; i < lhs.size(); ++i) {
        uint8_t sum = lhs[i] + rhs[i] + carry;
        result[i] = sum % 2;
        carry = (sum > 1) ? 1 : 0;
    }
    return result;
}

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t result;
    uint8_t borrow = 0;
    for (size_t i = 0; i < lhs.size(); ++i) {
        int8_t diff = lhs[i] - rhs[i] - borrow;
        if (diff < 0) {
            diff += 2;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result[i] = diff;
    }
    return result;
}

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t result;
    for (size_t i = 0; i < lhs.size(); ++i) {
        if (lhs[i] == 1) {
            for (size_t j = 0; j < rhs.size(); ++j) {
                result[i + j] += rhs[j];
            }
        }
    }
    return result;
}

uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs) {
    if (rhs == uint2022_t()) {
        throw std::invalid_argument("Division by zero");
    }

    uint2022_t result, remainder;
    for (size_t i = lhs.size(); i-- > 0;) {
        remainder.set_bit(0, lhs[i]);
        // Реализовать операцию деления (например, побитово)
    }
    return result;
}