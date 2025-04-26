#pragma once
#include <cinttypes>
#include <iostream>
#include <cstring>

struct uint2022_t {
    static const int CAPACITY = 70;
    uint32_t data[CAPACITY] = {0};
};

static_assert(sizeof(uint2022_t) <= 300, "[ERROR] uint2022_t must be LESS OR EQUAL than 300 bytes");


uint2022_t from_uint(uint32_t i);


uint2022_t from_string(const char* ch);


uint2022_t operator+(const uint2022_t& first, const uint2022_t& second);
uint2022_t operator-(const uint2022_t& first, const uint2022_t& second);
uint2022_t operator*(const uint2022_t& first, const uint2022_t& second);
uint2022_t operator/(const uint2022_t& first, const uint2022_t& second);
uint2022_t operator%(const uint2022_t& first, const uint2022_t& second);


bool operator==(const uint2022_t& first, const uint2022_t& second);
bool operator!=(const uint2022_t& first, const uint2022_t& second);


std::ostream& operator<<(std::ostream& str, const uint2022_t& val);
