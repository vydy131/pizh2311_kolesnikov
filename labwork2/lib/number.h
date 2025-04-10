#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>

class uint2022_t {
public:
    std::string value;

    // Конструктор из строки
    uint2022_t(const std::string& val) : value(val) {
        // Проверка на корректность числа (только цифры)
        if (val.empty() || val.find_first_not_of("0123456789") != std::string::npos) {
            throw std::invalid_argument("Invalid number string");
        }
    }

    // Конструктор из числа
    uint2022_t(uint32_t val) : value(std::to_string(val)) {}

    // Операции над числами
    uint2022_t operator+(const uint2022_t& other) const {
        return uint2022_t(addStrings(this->value, other.value));
    }

    uint2022_t operator-(const uint2022_t& other) const {
        return uint2022_t(subtractStrings(this->value, other.value));
    }

    uint2022_t operator*(const uint2022_t& other) const {
        return uint2022_t(multiplyStrings(this->value, other.value));
    }

    // Операции сравнения
    bool operator==(const uint2022_t& other) const {
        return this->value == other.value;
    }

    bool operator!=(const uint2022_t& other) const {
        return this->value != other.value;
    }

private:
    std::string addStrings(const std::string& a, const std::string& b) const {
        int carry = 0;
        std::string result;
        int i = a.size() - 1, j = b.size() - 1;
        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;
            if (i >= 0) sum += a[i--] - '0';
            if (j >= 0) sum += b[j--] - '0';
            carry = sum / 10;
            result.push_back(sum % 10 + '0');
        }
        std::reverse(result.begin(), result.end());
        return result;
    }

    std::string subtractStrings(const std::string& a, const std::string& b) const {
        // Простая заглушка для вычитания
        return a;
    }

    std::string multiplyStrings(const std::string& a, const std::string& b) const {
        // Простая заглушка для умножения
        return a;
    }
};


// Функции для создания объекта из числа и строки
uint2022_t from_uint(uint32_t i) {
    return uint2022_t(i);
}

uint2022_t from_string(const char* buff) {
    return uint2022_t(buff);
}
