#include <lib/number.h>
#include <iostream>

int main() {
    uint2022_t value = from_string("213418348378277859345267843");
    std::cout << value << std::endl;

    uint2022_t a = from_uint(12345);
    std::cout << "a = " << a << std::endl;

    return 0;
}
