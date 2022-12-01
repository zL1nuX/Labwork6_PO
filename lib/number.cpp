#include "number.h"


uint2022_t from_uint(uint32_t i) {
    uint2022_t result;
    std::string num = std::to_string(i);
    int counter = 0, base_digits = (int)(std::to_string(result.base).length() - 1);

    for (int x = (int)num.length(); x > 0; x -= base_digits) {
        if (x > base_digits) {
            result.mas_of_digits[counter] = atoi(num.substr(x - 9, 9).c_str());
        }
        else {
            result.mas_of_digits[counter] = atoi(num.substr(0, x).c_str());
        }
        counter++;
    }

    result.amount_of_digits = counter;

    return result;
}

uint2022_t from_string(const char* buff) {
    uint2022_t result;
    std::string num = buff;

    if ((int)num.length() > 72 * 9) {
        throw std::invalid_argument("Undefined Behaviour");
    }


    int counter = 0, base_digits = (int)(std::to_string(result.base).length() - 1);

    for (int x = (int)num.length(); x > 0; x -= base_digits) {
        if (x > base_digits) {
            result.mas_of_digits[counter] = atoi(num.substr(x - 9, 9).c_str());
        }
        else {
            result.mas_of_digits[counter] = atoi(num.substr(0, x).c_str());
        }
        counter++;
    }

    result.amount_of_digits = counter;


    return result;
}

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t result = lhs;
    int base = lhs.base;
    bool addition = false;
    int i = 0;

    while (i < std::min(lhs.amount_of_digits, rhs.amount_of_digits)) {
        int sum_of_digits = lhs.mas_of_digits[i] + rhs.mas_of_digits[i];
        if (addition) {
            sum_of_digits += 1;
        }

        if (sum_of_digits >= base) {
            result.mas_of_digits[i] = sum_of_digits - base;
            addition = true;
        }

        else {
            result.mas_of_digits[i] = sum_of_digits;
            addition = false;
        }

        i++;
    }

    while (i < lhs.amount_of_digits) {

        int lhs_add = lhs.mas_of_digits[i];

        if (addition) {
            lhs_add += 1;
        }

        if (lhs_add >= base) {
            result.mas_of_digits[i] = lhs_add - base;
            addition = true;
        }

        else {
            result.mas_of_digits[i] = lhs_add;
            addition = false;
            i = lhs.amount_of_digits;
            break;
        }

        i++;

    }

    while (i < rhs.amount_of_digits) {
        int rhs_add = rhs.mas_of_digits[i];
        if (addition) {
            rhs_add += 1;
        }

        if (rhs_add >= base) {
            result.mas_of_digits[i] = rhs_add - base ;
            addition = true;
        }

        else {
            result.mas_of_digits[i] = rhs_add;
            addition = false;
            i = rhs.amount_of_digits;
            break;
        }
        i++;
    }



    if (addition && i >= 73) {
        throw std::invalid_argument("Undefined Behaviour");
    }

    else if (addition) {
        result.mas_of_digits[i] = 1;
        result.amount_of_digits = i + 1;
    }

    else {
        result.amount_of_digits = i;
    }

    return result;
}

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs) {
    if (rhs.amount_of_digits > lhs.amount_of_digits) {
        throw std::invalid_argument("Undefined Behaviour");
    }

    uint2022_t result = lhs;
    int base = lhs.base;
    bool addition = false;

    int i = 0;

    while (i < rhs.amount_of_digits) {
        int diff_of_digits = lhs.mas_of_digits[i] - rhs.mas_of_digits[i];
        if (addition) {
            diff_of_digits -= 1;
        }

        if (diff_of_digits < 0) {
            result.mas_of_digits[i] = base + diff_of_digits;
            addition = true;
        }

        else {
            result.mas_of_digits[i] = diff_of_digits;
            addition = false;
        }
        i++;
    }

    while (i < lhs.amount_of_digits) {
        int diff_add = lhs.mas_of_digits[i];
        if (addition) {
            diff_add -= 1;
        }


        result.mas_of_digits[i] = diff_add;
        addition = false;
        i++;
    }

    if (i >= lhs.amount_of_digits && addition) {
        throw std::invalid_argument("Undefined behaviour");
    }

    while (result.mas_of_digits[i] == 0 && i != 0) {
        i--;
    }

    result.amount_of_digits = i + 1;
    return result;
}

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs) {

    if (rhs.amount_of_digits + lhs.amount_of_digits > 73) {
        throw std::invalid_argument("Undefined Behaviour");
    }

    uint2022_t result;

    if (lhs == from_string("0") || rhs == from_string("0")) {
        result.amount_of_digits = 1;
        return result;
    }

    int base = lhs.base;
    int addition;

    for (int i = 0; i < rhs.amount_of_digits; i++) {
        addition = 0;
        for (int j = 0; j < lhs.amount_of_digits || addition; j++) {
            long long mult_of_digits = 1ll * rhs.mas_of_digits[i] * lhs.mas_of_digits[j]
                                       + result.mas_of_digits[i + j] + addition;
            addition = int(mult_of_digits / base);
            result.mas_of_digits[i + j] = int(mult_of_digits % base);
        }
    }

    if (result.mas_of_digits[lhs.amount_of_digits + rhs.amount_of_digits - 1] == 0) {
        result.amount_of_digits = lhs.amount_of_digits + rhs.amount_of_digits - 1;
    }
    else {
        result.amount_of_digits = lhs.amount_of_digits + rhs.amount_of_digits;
    }


    return result;
}

uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs) {
    return uint2022_t();
}

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs) {
    if (lhs.amount_of_digits != rhs.amount_of_digits) {
        return false;
    }

    else {
        for (int i = 0; i < lhs.amount_of_digits; i++) {
            if (lhs.mas_of_digits[i] != rhs.mas_of_digits[i]) {
                return false;
            }
        }
    }
    return true;
}

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs) {
    if (lhs.amount_of_digits != rhs.amount_of_digits) {
        return true;
    }

    else {
        for (int i = 0; i < lhs.amount_of_digits; i++) {
            if (lhs.mas_of_digits[i] != rhs.mas_of_digits[i]) {
                return true;
            }
        }
    }

    return false;
}

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value) {
    if (value.amount_of_digits == 1 && value.mas_of_digits[0] == 0) {
        stream << 0;
        return stream;
    }

    for (int i = value.amount_of_digits - 1; i >= 0; i--) {
        if (i == value.amount_of_digits - 1) {
            if (value.mas_of_digits[i] == 0) {
                continue;
            }
        }
        std::string t = std::to_string(value.mas_of_digits[i]);
        for (int x = 0; x < 9 - (int)t.length() && i != value.amount_of_digits - 1; x++) {
            stream << 0;
        }
        stream << value.mas_of_digits[i];
    }

    return stream;
}