#include <lib/number.h>
#include <iostream>

int main() {
    uint32_t x = 1000000001;

    uint2022_t value1 = from_string("99999999999999999999");

    uint2022_t value2 = from_string("0");

    uint2022_t value3 = from_string("0");

    std::cout << (value2 * value1) << std::endl;


    return 0;
}